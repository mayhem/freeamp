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
	
	$Id: downloadmanager.h,v 1.1.2.1 1999/09/09 16:31:00 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_DOWNLOAD_MANAGER_H_
#define INCLUDED_DOWNLOAD_MANAGER_H_

#include <assert.h>
#include <string>
#include <vector>
#include <functional>

using namespace std;

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "mutex.h"
#include "thread.h"
#include "metadata.h"
#include "registry.h"

#define kInvalidIndex 0xFFFFFFFF

typedef enum {
    kDownloadItemState_Queued,
    kDownloadItemState_Downloading,
    kDownloadItemState_Cancelled,
    kDownloadItemState_Done

} DownloadItemState;

class DownloadItem {

 public:
    DownloadItem():m_state(kDownloadItemState_Queued){}

    DownloadItem(const char* url, const MetaData* metadata = NULL)
    {
        assert(url);

        if(url)
            SetURL(url);

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

    Error SetURL(const char* url) { m_url = url; return kError_NoErr;}
    Error GetURL(char* buf, uint32* len) { return SetBuffer(buf, m_url.c_str(), len); }
    const string& URL() const { return m_url; }

    void SetState(DownloadItemState state) { m_state = state; }
    DownloadItemState GetState() const { return m_state; }

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
    string m_url;
    DownloadItemState m_state;
};

class DownloadManager {

 public:
    DownloadManager(FAContext* context);
    virtual ~DownloadManager();

    Error SetCallbackFunction(DLMCallBackFunction function,
                              void* cookie = NULL);    
   
    // Functions for adding items to Download Manager       
    Error AddItem(const char* url);
    Error AddItem(const char* url, uint32 index);
    Error AddItem(DownloadItem* item);
    Error AddItem(DownloadItem* item, uint32 index);
    Error AddItems(vector<DownloadItem*>* list);
    Error AddItems(vector<DownloadItem*>* list, uint32 index);

    // Functions for removing items from Download Manager
    Error RemoveItem(DownloadItem* item);
    Error RemoveItem(uint32 index);
    Error RemoveItems(uint32 index, uint32 count);
    Error RemoveItems(vector<DownloadItem*>* items);
    Error RemoveAll();

    // File Format support
    Error GetSupportedDownloadFormats(DownloadFormatInfo* format, uint32 index);
    Error ImportDownloadFile(char* url, vector<DownloadItem*>* items = NULL, 
                       DLMCallBackFunction function = NULL,
                       void* cookie = NULL);

    Error ExportDownloadFile(char* url, DownloadFormatInfo* format, 
                        vector<DownloadItem*>* items = NULL,
                        DLMCallBackFunction function = NULL,
                        void* cookie = NULL);

    
    // Utility Functions
    bool            IsEmpty();
    uint32          CountItems();
    DownloadItem*   ItemAt(uint32 index);
	uint32          IndexOf(DownloadItem* item);
    bool            HasItem(DownloadItem* item);

 protected:
    inline uint32 CheckIndex(uint32 index);
    uint32 InternalIndexOf(vector<DownloadItem*>* list, DownloadItem* item);

    Error Download(DownloadItem* item,
                   DLMCallBackFunction function,
                   void* cookie = NULL);

    Error Download(uint32 index,
                   DLMCallBackFunction function,
                   void* cookie = NULL);

 private:

    FAContext* m_context;

    vector<DownloadItem*> m_downloadList;
   
    uint32 m_current;
   
};

#endif // INCLUDED_DOWNLOAD_MANAGER_H_










