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
	
	$Id: downloadmanager.cpp,v 1.1.2.7 1999/09/21 01:03:15 elrod Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <iostream>
#include <algorithm>

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "downloadmanager.h"
#include "registrar.h"

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

Error DownloadManager::Download(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {
        char hostname[kMaxHostNameLen + 1];
        uint8  port;
        struct sockaddr_in  addr;
        struct hostent      host;
        

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
        }

        cout << "Downloading item: " << item->SourceURL() << endl;

    }

    return result;
}

void DownloadManager::CleanUpDownload(DownloadItem* item)
{
    cout << "Cleaning item: " << item->SourceURL() << endl;
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


