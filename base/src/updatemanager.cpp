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
	
	$Id: updatemanager.cpp,v 1.1.2.1 1999/10/05 00:40:16 elrod Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <assert.h>
#ifdef WIN32
#include <io.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define closesocket(x) close(x)
#define O_BINARY 0
#endif
#ifdef unix
#include <strstream>
typedef ostrstream ostringstream;
#else
#include <sstream>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <algorithm>
//#include <iterators>

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "UpdateManager.h"
#include "registrar.h"
#include "utility.h"
#include "event.h"
#include "eventdata.h"
#include "musicbrowser.h"


UpdateManager::~UpdateManager()
{
    uint32 index = 0;
    uint32 size = 0;
    UpdateItem* item = NULL;

    m_runDownloadThread = false;

    m_quitMutex.Acquire();

    SaveResumableUpdateItems();

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

// Functions for adding items to Update Manager
Error UpdateManager::AddItem(UpdateItem* item)
{
    Error result = kError_InvalidParam;
    m_mutex.Acquire();

    assert(item);

    if(item)
    {
        m_itemList.push_back(item);
        //SendItemAddedMessage(item);
        result = kError_NoErr;
    }

    m_mutex.Release();
    return result;
}

Error UpdateManager::AddItems(vector<UpdateItem*>* list)
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

        /*for(uint32 i = 0; i < count; i++)
        {
            SendItemAddedMessage((*list)[i]);
        }*/

        result = kError_NoErr;
    }

    m_mutex.Release();

    return result;
}


// Utility Functions
bool UpdateManager::IsEmpty()
{
    bool result;
    m_mutex.Acquire();

    result = m_itemList.empty();

    m_mutex.Release();
    return result;
}

uint32 UpdateManager::CountItems()
{
    uint32 result;
    m_mutex.Acquire();

    result = m_itemList.size();

    m_mutex.Release();
    return result;
}

UpdateItem* UpdateManager::ItemAt(uint32 index)
{
    UpdateItem* result = NULL;
    m_mutex.Acquire();
    
    index = CheckIndex(index);

    if(index != kInvalidIndex)
    {
        result = m_itemList[index];
    }
    
    m_mutex.Release();
    return result;
}

uint32 UpdateManager::IndexOf(UpdateItem* item)
{
    return InternalIndexOf(&m_itemList, item);
}

uint32 UpdateManager::InternalIndexOf(vector<UpdateItem*>* list,
                                      UpdateItem* item)
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

bool UpdateManager::HasItem(UpdateItem* item)
{
    return (IndexOf(item) != kInvalidIndex);
}

// Internal functions

inline uint32 UpdateManager::CheckIndex(uint32 index)
{
	// If we're dealing with a bogus index then set it to -1.
	if(index >= CountItems())
    {
		index = kInvalidIndex;
    }

	return index;
}