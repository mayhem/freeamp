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
	
	$Id: downloadmanager.cpp,v 1.1.2.5 1999/09/20 18:23:34 elrod Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <assert.h>

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
        m_downloadThread->Suspend();
    }
}

DownloadManager::~DownloadManager()
{
    uint32 index = 0;
    uint32 size = 0;
    DownloadItem* item = NULL;
    //uint32 count = 0;

    m_runDownloadThread = false;
    m_downloadThread->Resume();

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


// Functions for removing items from Download Manager
// Removing an item implicitly cancels a download
// that is occurring.
Error DownloadManager::RemoveItem(DownloadItem* item)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    assert(item);

    if(item)
    {
        result = RemoveItem(IndexOf(item));
    }

    m_mutex.Release();
    return result;
}

Error DownloadManager::RemoveItem(uint32 index)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    index = CheckIndex(index);

    if(index != kInvalidIndex)
    {
        DownloadItem* item = m_itemList[index];

        m_itemList.erase(&m_itemList[index]);

        delete item;

        result = kError_NoErr;
    }

    m_mutex.Release();
    return result;
}

Error DownloadManager::RemoveItems(uint32 index, uint32 count)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    index = CheckIndex(index);

    if(index != kInvalidIndex)
    {
        for(uint32 i = 0; i < count; i++)
        {
            DownloadItem* item = m_itemList[index + i];

            delete item;
        }

        m_itemList.erase(&m_itemList[index], &m_itemList[index + count]);

        result = kError_NoErr;
    }

    m_mutex.Release();
    return result;
}

Error DownloadManager::RemoveItems(vector<DownloadItem*>* items)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    assert(items);

    if(items)
    {
        uint32 index = 0;
        uint32 size = 0;
        DownloadItem* item = NULL;

        size = items->size();

        for(index = 0; index < size; index++)
        {
            item = (*items)[index];

            if(item)
            {
                m_itemList.erase(&m_itemList[IndexOf(item)]);

                delete item;

                result = kError_NoErr;
            }
        }  
    }

    m_mutex.Release();
    return result;
}

Error DownloadManager::RemoveAll()
{
    Error result = kError_NoErr;
    uint32 index = 0;
    uint32 size = 0;
    DownloadItem* item = NULL;
    m_mutex.Acquire();

    size = m_itemList.size();

    for(index = 0; index < size; index++)
    {
        item = m_itemList[index];

        if(item)
        {            
            delete item;
        }
    }  

    m_itemList.clear();

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
        if(item->GetState() != kDownloadItemState_Downloading &&
           item->GetState() != kDownloadItemState_Done &&
           item->GetState() != kDownloadItemState_Queued)
        {
            item->SetState(kDownloadItemState_Queued);

            m_queueList.push_back(item);

            m_downloadThread->Resume();

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
            if(!allowResume)
            {
                item->SetState(kDownloadItemState_Cancelled);
            }
            else
            {
                item->SetState(kDownloadItemState_Paused);
            }

            m_queueList.push_back(item);

            m_downloadThread->Resume();

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

    if(m_queueList.size())
    {
        result = m_queueList[0];

        m_queueList.pop_front();


    }

    return result;
}

Error DownloadManager::Download(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {

    }

    return result;
}

void DownloadManager::CleanUpDownload(DownloadItem* item)
{

}

Error DownloadManager::SubmitToDatabase(DownloadItem* item)
{
    Error result = kError_InvalidParam;

    assert(item);

    if(item)
    {

    }

    return result;
}

void DownloadManager::DownloadThreadFunction()
{
    while(m_runDownloadThread)
    {
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

        m_downloadThread->Suspend();
    }
}

void DownloadManager::download_thread_function(void* arg)
{
    DownloadManager* dlm = (DownloadManager*)arg;

    dlm->DownloadThreadFunction();
}


