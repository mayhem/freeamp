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
	
	$Id: playlist.h,v 1.40.4.15 1999/09/03 08:31:45 elrod Exp $
____________________________________________________________________________*/

#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

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
#include "playlistformat.h"
#include "portabledevice.h"
#include "registry.h"
#include "plmevent.h"

typedef enum {
    kPlaylistSortKey_FirstKey,
    kPlaylistSortKey_Artist = kPlaylistSortKey_FirstKey,
    kPlaylistSortKey_Album,
    kPlaylistSortKey_Title,
    kPlaylistSortKey_Year,
    kPlaylistSortKey_Track,
    kPlaylistSortKey_Genre,
    kPlaylistSortKey_Time,
    kPlaylistSortKey_Location,
    kPlaylistSortKey_LastKey,
    kPlaylistSortKey_Random // not used with normal sort function

} PlaylistSortKey;

typedef enum {
    PlaylistSortType_Ascending,
    PlaylistSortType_Descending
} PlaylistSortType;

typedef enum {
    kPlaylistKey_FirstKey,
    kPlaylistKey_MasterPlaylist = kPlaylistKey_FirstKey,
    kPlaylistKey_ExternalPlaylist,
    kPlaylistKey_PortablePlaylist,
    kPlaylistKey_LastKey

} PlaylistKey;

typedef enum {
    kPlaylistMode_RepeatNone,
    kPlaylistMode_RepeatOne,
    kPlaylistMode_RepeatAll

} RepeatMode;

#define kInvalidIndex 0xFFFFFFFF

typedef enum {
    kPlaylistItemState_Normal,
    kPlaylistItemState_RetrievingMetaData,
    kPlaylistItemState_Delete

} PlaylistItemState;

class PlaylistItem {

 public:
    PlaylistItem():m_state(kPlaylistItemState_Normal){}

    PlaylistItem(const char* url, const MetaData* metadata = NULL)
    {
        assert(url);

        if(url)
            SetURL(url);

        if(metadata)
            SetMetaData(metadata);

        m_state = kPlaylistItemState_Normal;
    }

    virtual ~PlaylistItem() {}

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

    void SetState(PlaylistItemState state) { m_state = state; }
    PlaylistItemState GetState() const { return m_state; }

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
    PlaylistItemState m_state;
};

class PlaylistItemSort : public binary_function<PlaylistItem*, PlaylistItem*, bool> {

 public:
    PlaylistItemSort(PlaylistSortKey sortKey) : m_sortKey(sortKey) { }

    bool operator() (PlaylistItem* item1, PlaylistItem* item2) const;
   
 private:
    PlaylistSortKey m_sortKey;
};

class PlaylistManager {

 public:
    PlaylistManager(FAContext* context);
    virtual ~PlaylistManager();

    // Playlist actions
    Error SetCurrentItem(PlaylistItem* item);
    const PlaylistItem* GetCurrentItem();
    
    Error SetCurrentIndex(uint32 index);
    uint32 GetCurrentIndex() const;

    Error GotoNextItem(bool userAction = false);
    Error GotoPreviousItem(bool userAction = false);

    bool HasAnotherItem();

    Error SetShuffleMode(bool shuffle);
    bool GetShuffleMode() const {return m_shuffle;}
    Error SetRepeatMode(RepeatMode mode);
    RepeatMode GetRepeatMode() const {return m_repeatMode;}
    Error ToggleRepeatMode();
    Error ToggleShuffleMode();

    // Functions for adding items to playlist       
    Error AddItem(const char* url);
    Error AddItem(const char* url, uint32 index);
    Error AddItem(PlaylistItem* item);
    Error AddItem(PlaylistItem* item, uint32 index);
    Error AddItems(vector<PlaylistItem*>* list);
    Error AddItems(vector<PlaylistItem*>* list, uint32 index);

    // Functions for removing items from playlist
    Error RemoveItem(PlaylistItem* item);
    Error RemoveItem(uint32 index);
    Error RemoveItems(uint32 index, uint32 count);
    Error RemoveItems(vector<PlaylistItem*>* items);
    Error RemoveAll();

    // Functions for moving items around
    Error SwapItems(uint32 index1, uint32 index2);
    Error SwapItems(PlaylistItem* item1, PlaylistItem* item2);
    Error MoveItem(PlaylistItem* item, uint32 index);
    Error MoveItem(uint32 oldIndex, uint32 newIndex);
    Error MoveItems(vector<PlaylistItem*>* items, uint32 index);

    // Functions for sorting
    Error Sort(PlaylistSortKey key, PlaylistSortType type = PlaylistSortType_Ascending);
    PlaylistSortKey GetPlaylistSortKey() const;

    // Which playlist are we dealing with for purposes of editing:
    // 1) Master Playlist - list of songs to play
    // 2) Secondary Playlist - a playlist that we want to edit
    //      - External playlist
    //      - Portable playlist

    Error SetActivePlaylist(PlaylistKey key);
    PlaylistKey GetActivePlaylist() const;
    Error SetExternalPlaylist(char* url);
    Error GetExternalPlaylist(char* url, uint32* length);
    Error SetPortablePlaylist(DeviceInfo* device, 
                              PLMCallBackFunction function = NULL,
                              void* cookie = NULL);
    Error GetPortablePlaylist(DeviceInfo* device);

    // External playlist support
    Error GetSupportedPlaylistFormats(PlaylistFormatInfo* format, uint32 index);
    Error ReadPlaylist(char* url, vector<PlaylistItem*>* items = NULL, 
                       PLMCallBackFunction function = NULL,
                       void* cookie = NULL);

    Error WritePlaylist(char* url, PlaylistFormatInfo* format, 
                        vector<PlaylistItem*>* items = NULL,
                        PLMCallBackFunction function = NULL,
                        void* cookie = NULL);

    // Portable player communication
    Error GetSupportedPortables(DeviceInfo* device, uint32 index);
    bool IsPortableAvailable(DeviceInfo* device);

    Error GetDeviceInfo(DeviceInfo* device);

    Error InitializeDevice(DeviceInfo* device, 
                           PLMCallBackFunction function = NULL,
                           void* cookie = NULL);

    Error ReadPortablePlaylist(DeviceInfo* device, 
                               PLMCallBackFunction function = NULL,
                               void* cookie = NULL);
    Error SyncPortablePlaylist(DeviceInfo* device, 
                               PLMCallBackFunction function = NULL,
                               void* cookie = NULL);

    Error DownloadItemFromPortable(DeviceInfo* device,
                                   PlaylistItem* item,
                                   char* url,
                                   PLMCallBackFunction function = NULL,
                                   void* cookie = NULL);
    // Utility Functions
    bool            IsEmpty();
    uint32          CountItems();
    PlaylistItem*   ItemAt(uint32 index);
	uint32          IndexOf(PlaylistItem* item);
    bool            HasItem(PlaylistItem* item);

 protected:
    inline uint32 CheckIndex(uint32 index);
    uint32 InternalIndexOf(vector<PlaylistItem*>* list, PlaylistItem* item);

    void AddItemToShuffleList(PlaylistItem* item);
    void AddItemsToShuffleList(vector<PlaylistItem*>* list);

    void RetrieveMetaData(PlaylistItem* item);
    void RetrieveMetaData(vector<PlaylistItem*>* list);

    static void metadata_thread_function(void* arg);
    void MetaDataThreadFunction(vector<PlaylistItem*>* list);


 private:

    FAContext* m_context;

    class ShuffleItem {

      public:
        PlaylistItem* m_item;
        uint32 m_index;
    };

    vector<PlaylistItem*>   m_masterList;
    vector<PlaylistItem*>   m_externalList;
    vector<PlaylistItem*>   m_portableList;
    vector<PlaylistItem*>*  m_activeList; 
    vector<PlaylistItem*>   m_shuffleList;

    uint32          m_current;
    bool            m_shuffle;
    RepeatMode      m_repeatMode;
    PlaylistKey     m_playlistKey;
    PlaylistSortKey m_sortKey;

    string      m_externalPlaylist;
    DeviceInfo  m_portableDevice;

    Mutex       m_mutex;

    Registry m_playlistRegistry;
    Registry m_portableRegistry;
    Registry m_metadataRegistry;

    vector<MetaDataFormat*>         m_metadataFormats;
    vector<PlaylistFormatInfo*>     m_playlistFormats;
    vector<DeviceInfo*>             m_portablePlayers;

};

#endif // _PLAYLIST_H_










