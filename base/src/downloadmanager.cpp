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
	
	$Id: downloadmanager.cpp,v 1.1.2.2 1999/09/15 22:19:50 elrod Exp $
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

DownloadManager::DownloadManager(FAContext* context)
{
    m_context = context;
}

DownloadManager::~DownloadManager()
{
    uint32 index = 0;
    uint32 size = 0;
    DownloadItem* item = NULL;
    //uint32 count = 0;

    size = m_itemList.size();

    for(index = 0; index < size; index++)
    {
        item = m_itemList[index];

        if(item)
        {
            delete item;
        }
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
        m_itemList->push_back(item);

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
        m_itemList->insert( m_itemList->end(),
                            list->begin(), 
                            list->end());

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
        DownloadItem* item = (*m_itemList)[index];

        m_itemList->erase(&(*m_itemList)[index]);

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
            DownloadItem* item = (*m_itemList)[index + i];

            delete item;
        }

        m_itemList->erase(&(*m_itemList)[index], &(*m_itemList)[index + count]);

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
                m_itemList->erase(&(*m_itemList)[IndexOf(item)]);

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

    size = m_itemList->size();

    for(index = 0; index < size; index++)
    {
        item = (*m_itemList)[index];

        if(item)
        {            
            delete item;
        }
    }  

    m_itemList->clear();

    m_mutex.Release();
    return result;
}


// Changes item state to queued if it is cancelled or error.
// This will indicate to the download thread that it should
// attempt to retrieve this item. Has no effect if the item's
// state is Done, or Downloading.
Error DownloadManager::QueueDownload(DownloadItem* item)
{

}

Error DownloadManager::QueueDownload(uint32 index)
{

}


// Changes item state to cancelled if it is queued or downloading.
// If allowResume is true then data is retained for later download.
// Has no effect if the item's state is Done, Cancelled, or Error.
Error DownloadManager::CancelDownload(DownloadItem* item, bool allowResume)
{

}

Error DownloadManager::CancelDownload(uint32 index, bool allowResume)
{

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

        uint32 numFormats = m_downloadFormats.size();

        if(index < numFormats)
        {
            result = kError_NoErr;

            *format = *m_downloadFormats[index];
        }
    }

    return result;
}

Error DownloadManager::ImportDownloadFile(char* url, 
                                          vector<DownloadItem*>* items)
{

}

