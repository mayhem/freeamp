/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 GoodNoise

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
	
	$Id: downloadmanager.cpp,v 1.1.2.12 1999/09/23 16:55:40 elrod Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <algorithm>

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "downloadmanager.h"
#include "registrar.h"
#include "utility.h"

DownloadManager::DownloadManager(FAContext* context)
{
    m_context = context;
    m_current = 0;

    Registrar registrar;

    registrar.SetSubDir("plugins");
    registrar.SetSearchString("*.dlf");
    registrar.InitializeRegistry(&m_formatRegistry, context->prefs);

    const RegistryItem* module = NULL;
    DownloadFormat* dlf = NULL;
    int32 i = 0;

    while((module = m_formatRegistry.GetItem(i++)))
    {
        dlf = (DownloadFormat*) module->InitFunction()(m_context);

        if(dlf)
        {
            DownloadFormatInfo dlfi;

            uint32 index = 0;

            // error != kError_NoMoreFormats
            while(IsntError(dlf->GetSupportedFormats(&dlfi, index++)))
            {
                dlfi.SetRef(dlf);
                m_formats.push_back(new DownloadFormatInfo(dlfi));
            }
        }
    }

    m_runDownloadThread = true;

    m_downloadThread = Thread::CreateThread();

    if(m_downloadThread)
    {
        m_downloadThread->Create(download_thread_function, this);
    }
}

DownloadManager::~DownloadManager()
{
    uint32 index = 0;
    uint32 size = 0;
    DownloadItem* item = NULL;
    //uint32 count = 0;

    m_runDownloadThread = false;
    m_queueSemaphore.Signal();

    m_quitMutex.Acquire();

    size = m_itemList.size();

    for(index = 0; index < size; index++)
    {
        item = m_itemList[index];

        if(item)
        {
            delete item;
        }
    }

    size = m_formats.size();

    for(index = 0; index < size; index++)
    {
        //delete m_formats[index]->GetRef();
        delete m_formats[index];
    }

    if(m_downloadThread)
    {
        delete m_downloadThread;
    }
}

// Functions for adding items to Download Manager
// Adding an item implicitly queues it for
// downloading.
Error DownloadManager::AddItem(const char* url)
{
    Error result = kError_InvalidParam;

    assert(url);

    if(url)
    {
        result = kError_OutOfMemory;

        DownloadItem* item = new DownloadItem(url);

        if(item)
        {
            result = AddItem(item);
        }
    }

    return result;
}

Error DownloadManager::AddItem(DownloadItem* item)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    assert(item);

    if(item)
    {
        m_itemList.push_back(item);
        QueueDownload(item);

        result = kError_NoErr;
    }

    m_mutex.Release();
    return result;
}

Error DownloadManager::AddItems(vector<DownloadItem*>* list)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    assert(list);

    if(list)
    {
        m_itemList.insert( m_itemList.end(),
                            list->begin(), 
                            list->end());

        uint32 count = list->size();

        for(uint32 i = 0; i < count; i++)
        {
            QueueDownload((*list)[i]);
        }

        result = kError_NoErr;
    }

    m_mutex.Release();

    return result;
}

// Changes item state to queued if it is cancelled or error.
// This will indicate to the download thread that it should
// attempt to retrieve this item. Has no effect if the item's
// state is Done, or Downloading.
Error DownloadManager::QueueDownload(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {
        //cout << "Queue item: " << item->SourceURL() << endl;

        if(item->GetState() != kDownloadItemState_Downloading &&
           item->GetState() != kDownloadItemState_Done &&
           item->GetState() != kDownloadItemState_Queued)
        {
            item->SetState(kDownloadItemState_Queued);

            m_queueList.push_back(item);

            m_queueSemaphore.Signal();

            result = kError_NoErr;
        }
    }

    return result;
}

Error DownloadManager::QueueDownload(uint32 index)
{
    return QueueDownload(ItemAt(index));
}


// Changes item state to cancelled if it is queued or downloading.
// If allowResume is true then data is retained for later download.
// Has no effect if the item's state is Done, Cancelled, or Error.
Error DownloadManager::CancelDownload(DownloadItem* item, bool allowResume)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {
        if(item->GetState() == kDownloadItemState_Downloading ||
           item->GetState() == kDownloadItemState_Queued)
        {
            m_queueMutex.Acquire();

            // remove from download queue
            if(item->GetState() == kDownloadItemState_Queued)
            {
                deque<DownloadItem*>::iterator position;
                
                if((position = find(m_queueList.begin(), 
                                    m_queueList.end(), 
                                    item)) != m_queueList.end())
                {
                    m_queueList.erase(position); 
                }
            }

            m_queueMutex.Release();

            if(!allowResume)
            {
                item->SetState(kDownloadItemState_Cancelled);
            }
            else
            {
                item->SetState(kDownloadItemState_Paused);
            }

            result = kError_NoErr;
        }
    }

    return result;
}

Error DownloadManager::CancelDownload(uint32 index, bool allowResume)
{
    return CancelDownload(ItemAt(index), allowResume);
}


// File Format support
Error DownloadManager::GetSupportedDownloadFormats(DownloadFormatInfo* format,
                                                   uint32 index)
{
    Error result = kError_InvalidParam;

    assert(format);

    if(format)
    {
        result = kError_NoMoreFormats;

        uint32 numFormats = m_formats.size();

        if(index < numFormats)
        {
            result = kError_NoErr;

            *format = *m_formats[index];
        }
    }

    return result;
}

Error DownloadManager::ReadDownloadFile(char* url, 
                                        vector<DownloadItem*>* items)
{
    Error result = kError_InvalidParam;

    assert(url);

    if(url)
    {
        // find a suitable plugin
        result = kError_FormatNotSupported;
        char* extension = strrchr(url, '.');

        if(extension)
        {
            extension++;

            uint32 numFormats = m_formats.size();

            for(uint32 index = 0; index < numFormats; index++)
            {
                DownloadFormatInfo* format = m_formats[index];
                
                if(!strcmp(extension, format->GetExtension()))
                {
                    bool addToInternalList = false;

                    if(!items)
                    {
                        items = new vector<DownloadItem*>;
                        addToInternalList = true;
                    }

                    result = format->GetRef()->ReadDownloadFile(url, 
                                                                items);

                    if(addToInternalList)
                    {
                        AddItems(items);
                        delete items;
                    }

                    break;
                }
            }
        }
    }

    return result;
}

// Utility Functions
bool DownloadManager::IsEmpty()
{
    bool result;
    m_mutex.Acquire();

    result = m_itemList.empty();

    m_mutex.Release();
    return result;
}

uint32 DownloadManager::CountItems()
{
    uint32 result;
    m_mutex.Acquire();

    result = m_itemList.size();

    m_mutex.Release();
    return result;
}

DownloadItem* DownloadManager::ItemAt(uint32 index)
{
    DownloadItem* result = NULL;
    m_mutex.Acquire();
    
    index = CheckIndex(index);

    if(index != kInvalidIndex)
    {
        result = m_itemList[index];
    }
    
    m_mutex.Release();
    return result;
}

uint32 DownloadManager::IndexOf(DownloadItem* item)
{
    return InternalIndexOf(&m_itemList, item);
}

uint32 DownloadManager::InternalIndexOf(vector<DownloadItem*>* list,
                                        DownloadItem* item)
{
    uint32 result = kInvalidIndex;
    uint32 index = 0;
    uint32 size = 0;

    assert(list);
    assert(item);

    if(list && item)
    {
        size = list->size();

        for(index = 0; index < size; index++)
        {
            if(item == (*list)[index])
            {
                result = index;
                break;
            }
        }
    }
    
    return result;
}

bool DownloadManager::HasItem(DownloadItem* item)
{
    return (IndexOf(item) != kInvalidIndex);
}

// Internal functions

inline uint32 DownloadManager::CheckIndex(uint32 index)
{
	// If we're dealing with a bogus index then set it to -1.
	if(index >= CountItems())
    {
		index = kInvalidIndex;
    }

	return index;
}

DownloadItem* DownloadManager::GetNextQueuedItem()
{
    DownloadItem* result = NULL;

    m_queueMutex.Acquire();

    if(m_queueList.size())
    {
        result = m_queueList[0];

        m_queueList.pop_front();

        cout << "Queue count: " << m_queueList.size() << endl;
    }

    m_queueMutex.Release();

    return result;
}

const uint8 kHttpPort = 80;
const uint32 kMaxHostNameLen = 64;

static bool IsHTTPHeaderComplete(char* buffer, uint32 length)
{
    bool result = false;

    if(length >= 4)
    {
        if( (buffer[0] == 'H' && buffer[1] == 'T' 
               && buffer[2] == 'T' && buffer[3] == 'P'))
        {
            //cout << "buffer is HTTP" << endl;

            for(char* cp = buffer; cp < buffer + length; cp++)
            {
                if(!strncmp(cp, "\n\n", 2) || !strncmp(cp, "\r\n\r\n", 4))
                {
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

Error DownloadManager::Download(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {
        cout << "Downloading item: " << item->SourceURL() << endl;

        char hostname[kMaxHostNameLen + 1];
        char localname[kMaxHostNameLen + 1];
        uint8  port;
        struct sockaddr_in  addr;
        struct hostent      host;
        SOCKET s;
        char* file;
        

        result = kError_ProtocolNotSupported;

        // where should we connect to?
        if(!strncasecmp(item->SourceURL().c_str(), "http://", 7))
        {
            int32 numFields;

            result = kError_NoErr;  

            numFields = sscanf(item->SourceURL().c_str(), 
                               "http://%[^:/]:%d", hostname, &port);

            if(numFields < 1)
            {
                result = kError_InvalidURL;     
            }

            if(numFields < 2)
            {
                port = kHttpPort;
            }

            file = strchr(item->SourceURL().c_str() + 7, '/');
        }

        // get hostname
        if(IsntError(result))
        {
            struct hostent* hostByName;
            struct hostent  hostByIP;
            hostByName = gethostbyname(hostname);

            // On some stacks a numeric IP address
            // will not parse with gethostbyname.  
            // If that didn't work try to convert it as a
            // numeric address before giving up.
            if(!hostByName)
            {
                static unsigned long ip;
                static char *addr_ptr[2] = {(char*)&ip, NULL};

                if((ip = inet_addr(hostname)) < 0) 
                    result =  kError_CantFindHost;
                else
                {
                    hostByIP.h_length = sizeof(uint32);
                    hostByIP.h_addrtype = AF_INET;
                    hostByIP.h_addr_list = (char**)&addr_ptr;
                    hostByName = &hostByIP;
                }
            }

            if(IsntError(result))
            {
                memcpy(&host, hostByName, sizeof(struct hostent));
            }
        }

        // open socket
        if(IsntError(result))
        {
            memset(&addr, 0x00, sizeof(struct sockaddr_in));
            memcpy(&addr.sin_addr, host.h_addr, host.h_length);
            addr.sin_family= host.h_addrtype;
            addr.sin_port= htons(port); 

            s = socket(host.h_addrtype, SOCK_STREAM, 0);

            if(s < 0)
                result = kError_CantCreateSocket;
        }

        // connect and send request
        if(IsntError(result))
        {
            if(connect(s,(const struct sockaddr*)&addr, sizeof(struct sockaddr)))
                result = kError_CannotBind;
            else
            {
                gethostname(localname, kMaxHostNameLen);    

                const char* kHTTPQuery = "GET %s HTTP/1.1\n"
                                         "Host: %s\n"
                                         "Accept: */*\n" 
                                         "User-Agent: FreeAmp/%s\n";

                char* query = new char[ strlen(kHTTPQuery) + 
                                        strlen(file) +
                                        strlen(localname) +
                                        strlen(FREEAMP_VERSION) + 2];
            
                sprintf(query, kHTTPQuery, file, localname, FREEAMP_VERSION);
            
                strcat(query, "\n");

                int count;

                //cout << query << endl;

                count = send(s, query, strlen(query), 0);

                if(count != strlen(query))
                {
                    closesocket(s);
                    result = kError_IOError;
                }

                delete [] query;
            }
        }


        // receive response
        if(IsntError(result))
        {
            uint32 bufferSize = 2048;
            char* buffer = NULL;
            int count;
            uint32 total = 0;

            buffer = (char*)malloc(bufferSize);

            result = kError_OutOfMemory;

            if(buffer)
            {
                result = kError_NoErr;

                do
                {
                    if(total >= bufferSize - 1)
                    {
                        bufferSize *= 2;

                        buffer = (char*) realloc(buffer, bufferSize);

                        if(!buffer)
                        {
                            result = kError_OutOfMemory;
                            break;
                        }
                    }

                    count = recv(s, buffer + total, bufferSize - total - 1, 0);

                    if(count > 0)
                        total += count;
                    else
                    {
                        result = kError_UnknownErr;
                        break;
                    }

                }while(!IsHTTPHeaderComplete(buffer, total));
            }

            // parse header
            if(IsntError(result))
            {
                uint32 returnCode = atoi(buffer+9);
                buffer[total] = 0x00;
                //cout << buffer << endl;

                cout << returnCode << endl;

                switch(buffer[9])
                {
                    // 1xx: Informational - Request received, continuing process
                    case '1':
                    {
                        // not sure what to do here... continue receiving???
                    }    

                    // 2xx: Success - The action was successfully received,
                    // understood, and accepted
                    case '2':
                    {
                        result = kError_UnknownErr;

                        char path[MAX_PATH];
                        uint32 length = sizeof(path);

                        URLToFilePath(item->DestinationURL().c_str(), path, &length);

                        cout << path << endl;

                        int fd = open(path, _O_BINARY|_O_CREAT|_O_RDWR);

                        if(fd >= 0)
                        {
                            char* cp = strstr(buffer, "\n\n");

                            if(cp)
                                cp += 2;
                            else
                            {
                                cp = strstr(buffer, "\r\n\r\n");

                                if(cp)
                                    cp += 4;
                            }

                            if(cp)
                            {
                                if(cp - buffer < total)
                                {
                                    write(fd, cp, total - (cp - buffer));
                                }
                            }

                            do
                            {
                                count = recv(s, buffer, bufferSize, 0);

                                if(count > 0)
                                    write(fd, buffer, count);

                                cout << "bytes recvd:" << count << endl;

                            }while(count > 0 && 
                                   item->GetState() == kDownloadItemState_Downloading);

                            close(fd);

                            result = kError_NoErr;
                        }
                        
                        break;
                    }

                    // 3xx: Redirection - Further action must be taken in order to
                    // complete the request
                    case '3':
                    {
                        char* cp = strstr(buffer, "Location:");
                        //int32 length;

                        if(cp)
                        {
                            cp += 9;

                            if(*cp == 0x20)
                                cp++;

                            for(char* end = cp; end < buffer + total; end++)
                                if(*end=='\r' || *end == '\n') break;

                            *end = 0x00;

                            //cout << cp << endl;

                            item->SetSourceURL(cp);

                            result = Download(item);
                        }
                        
                        break;
                    }

                    // 4xx: Client Error - The request contains bad syntax or cannot
                    // be fulfilled
                    case '4':
                    {
                        switch(returnCode)
                        {
                            case 400:
                                result = kError_BadHTTPRequest;
                                break;

                            case 401:
                                result = kError_AccessNotAuthorized;
                                break;                           

                            case 403:
                                result = kError_AccessForbidden;
                                break;

                            case 404:
                                result = kError_FileNotFound;
                                break;

                            case 416:
                                result = kError_RangeNotExceptable;
                                break;

                            default:
                                result = kError_UnknownErr;
                                break;
                        }

                        break;
                    }

                    // 5xx: Server Error - The server failed to fulfill an apparently
                    // valid request
                    case '5':
                    {
                        result = kError_UnknownServerError;
                        break;
                    }
                }

            }

           
            if(buffer)
                free(buffer);
        }

    }

    return result;
}

void DownloadManager::CleanUpDownload(DownloadItem* item)
{
    cout << "Cleaning item: " << item->SourceURL() << endl;

    char path[MAX_PATH];
    uint32 length = sizeof(path);

    URLToFilePath(item->DestinationURL().c_str(), path, &length);

    remove(path);
}

Error DownloadManager::SubmitToDatabase(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {
        cout << "Submitting item: " << item->SourceURL() << endl;
    }

    return result;
}

void DownloadManager::DownloadThreadFunction()
{
    m_quitMutex.Acquire();

    while(m_runDownloadThread)
    {
        m_queueSemaphore.Wait();

        DownloadItem* item = GetNextQueuedItem();
        Error result;

        if(item)
        {
            result = Download(item);

            if(IsError(result))
            {
                cout << "Error: " << (int)result << endl;
            }

            if(IsntError(result))
            {
                item->SetState(kDownloadItemState_Done);

                result = SubmitToDatabase(item);
            }
            else if(result == kError_UserCancel)
            {
                if(item->GetState() == kDownloadItemState_Cancelled)
                {
                    CleanUpDownload(item);
                }
            }
            else
            {
                item->SetState(kDownloadItemState_Error);
            }

            item->SetDownloadError(result);
        }
    }

    cout << "Exiting download thread..." << endl;

    m_quitMutex.Release();
}

void DownloadManager::download_thread_function(void* arg)
{
    DownloadManager* dlm = (DownloadManager*)arg;

    dlm->DownloadThreadFunction();
}


