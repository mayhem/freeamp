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
	
	$Id: downloadmanager.cpp,v 1.1.2.1 1999/09/15 21:31:23 elrod Exp $
____________________________________________________________________________*/

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

}

// Functions for adding items to Download Manager
// Adding an item implicitly queues it for
// downloading.
Error DownloadManager::AddItem(const char* url)
{

}

Error DownloadManager::AddItem(DownloadItem* item)
{

}

Error DownloadManager::AddItems(vector<DownloadItem*>* list)
{

}


// Functions for removing items from Download Manager
// Removing an item implicitly cancels a download
// that is occurring.
Error DownloadManager::RemoveItem(DownloadItem* item)
{

}

Error DownloadManager::RemoveItem(uint32 index)
{

}

Error DownloadManager::RemoveItems(uint32 index, uint32 count)
{

}

Error DownloadManager::RemoveItems(vector<DownloadItem*>* items)
{

}

Error DownloadManager::RemoveAll()
{

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

}

Error DownloadManager::ImportDownloadFile(char* url, 
                                          vector<DownloadItem*>* items)
{

}

