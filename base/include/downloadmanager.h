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
	
	$Id: downloadmanager.h,v 1.1.2.7 1999/09/19 07:48:55 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_DOWNLOAD_MANAGER_H_
#define INCLUDED_DOWNLOAD_MANAGER_H_

#include <assert.h>
#include <string>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "mutex.h"
#include "thread.h"
#include "metadata.h"
#include "registry.h"
#include "downloadformat.h"

class DownloadItem;

typedef enum {
    kDLMEvent_AddItem,
    kDLMEvent_RemoveItem,
    kDLMEvent_Status,
    kDLMEvent_Progress,
    kDLMEvent_Error
} DLMEventType;

#define kDLMProgressInfinity -1

typedef struct DLMEventAddItemData {
    uint32 index;
    uint32 total;
    DownloadItem* item;
} DLMEventAddItemData;

typedef struct DLMEventRemoveItemData {
    uint32 index;
    uint32 total;
    DownloadItem* item;
} DLMEventRemoveItemData;

typedef struct DLMEventProgressData {
    uint32 position;
    uint32 total;
    DownloadItem* item;
} DLMEventProgressData;

typedef struct DLMEventStatusData {
    DownloadItem* item;
} DLMEventStatusData;

typedef struct DLMEventErrorData {
    Error errorCode;
    DownloadItem* item;
} DLMEventErrorData;

typedef union DLMEventData {
    DLMEventAddItemData     addItemData;
    DLMEventRemoveItemData  removeItemData;
    DLMEventProgressData    progressData;
    DLMEventStatusData      statusData;
    DLMEventErrorData       errorData;
} DLMEventData;

typedef struct DLMEvent {
    DLMEventType type;
    DLMEventData data;
    string eventString;
} DLMEvent;

typedef bool (*DLMCallBackFunction)(DLMEvent* event, void* userData);

#define kInvalidIndex 0xFFFFFFFF

typedef enum {
    kDownloadItemState_Queued,
    kDownloadItemState_Downloading,
    kDownloadItemState_Cancelled,
    kDownloadItemState_Error,
    kDownloadItemState_Done

} DownloadItemState;

class DownloadItem {
 friend class DownloadManager;

 public:
    DownloadItem():m_state(kDownloadItemState_Queued){}

    DownloadItem(const char* src, const char* dest = NULL, const MetaData* metadata = NULL)
    {
        assert(src);

        m_allowResume = false;

        if(src)
            SetSourceURL(src);

        if(dest)
            SetDestinationURL(dest);

        if(metadata)
            SetMetaData(metadata);
    }

    virtual ~DownloadItem() {}

    Error SetMetaData(const MetaData* metadata)
    {
        Error result = kError_InvalidParam;
        assert(metadata);

        if(metadata)
        {
            result = kError_NoErr;

            m_metadata = *metadata;
        }

        return result;
    }

    const MetaData& GetMetaData() const { return m_metadata; }

    Error SetSourceURL(const char* url) { m_src = url; return kError_NoErr;}
    Error GetSourceURL(char* buf, uint32* len) { return SetBuffer(buf, m_src.c_str(), len); }
    const string& SourceURL() const { return m_src; }

    Error SetDestinationURL(const char* url) { m_dest = url; return kError_NoErr;}
    Error GetDestinationURL(char* buf, uint32* len) { return SetBuffer(buf, m_dest.c_str(), len); }
    const string& DestinationURL() const { return m_dest; }

    DownloadItemState GetState() const { return m_state; }
    void SetState(DownloadItemState state) { m_state = state; }

    void SetResumeable(bool allowResume) { m_allowResume = allowResume; }
    bool IsResumable()  const { return m_allowResume; }

 protected:
    Error SetBuffer(char* dest, const char* src, uint32* len)
    {
        Error result = kError_InvalidParam;

        assert(dest);
        assert(src);
        assert(len);

        if(dest && src)
        {
            uint32 srclen = strlen(src) + 1;

            if(*len >= srclen)
            {
                strcpy(dest, src);
                result = kError_NoErr;
            }
            else
            {
                result = kError_BufferTooSmall;
            }

            *len = srclen;
        }

        return result;
    }

 private:
    MetaData m_metadata;
    string m_src;
    string m_dest;
    DownloadItemState m_state;
    bool m_allowResume;
};

class DownloadManager {

 public:
    DownloadManager(FAContext* context);
    virtual ~DownloadManager();

    // Functions for adding items to Download Manager
    // Adding an item implicitly queues it for
    // downloading.
    Error AddItem(const char* url);
    Error AddItem(DownloadItem* item);
    Error AddItems(vector<DownloadItem*>* list);

    // Functions for removing items from Download Manager
    // Removing an item implicitly cancels a download
    // that is occurring.
    Error RemoveItem(DownloadItem* item);
    Error RemoveItem(uint32 index);
    Error RemoveItems(uint32 index, uint32 count);
    Error RemoveItems(vector<DownloadItem*>* items);
    Error RemoveAll();

    // Changes item state to queued if it is cancelled or error.
    // This will indicate to the download thread that it should
    // attempt to retrieve this item. Has no effect if the item's
    // state is Done, or Downloading.
    Error QueueDownload(DownloadItem* item);
    Error QueueDownload(uint32 index);

    // Changes item state to cancelled if it is queued or downloading.
    // If allowResume is true then data is retained for later download.
    // Has no effect if the item's state is Done, Cancelled, or Error.
    Error CancelDownload(DownloadItem* item, bool allowResume = false);
    Error CancelDownload(uint32 index, bool allowResume = false);

 
    // File Format support
    Error GetSupportedDownloadFormats(DownloadFormatInfo* format, uint32 index);
    Error ReadDownloadFile(char* url, vector<DownloadItem*>* items = NULL);

    // Utility Functions
    bool            IsEmpty();
    uint32          CountItems();
    DownloadItem*   ItemAt(uint32 index);
	uint32          IndexOf(DownloadItem* item);
    bool            HasItem(DownloadItem* item);

 protected:
    inline uint32 CheckIndex(uint32 index);
    uint32 InternalIndexOf(vector<DownloadItem*>* list, DownloadItem* item);    

    static void download_thread_function(void* arg);
    void DownloadThreadFunction();

    void QueueItem(DownloadItem* item);
    DownloadItem* GetNextQueuedItem();

    Error Download(DownloadItem* item);
    void CleanUpDownload(DownloadItem* item);
    Error SubmitToDatabase(DownloadItem* item);

 private:

    FAContext* m_context;

    Mutex m_mutex;

    vector<DownloadItem*> m_itemList;
    deque<DownloadItem*> m_queueList;

    Registry m_formatRegistry;

    vector<DownloadFormatInfo*> m_formats;
   
    uint32 m_current;

    Thread* m_downloadThread;

};

#endif // INCLUDED_DOWNLOAD_MANAGER_H_










