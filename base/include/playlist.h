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
	
	$Id: playlist.h,v 1.40.4.3 1999/08/23 23:04:16 elrod Exp $
____________________________________________________________________________*/

#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <assert.h>
#include <vector>

using namespace std;

#include "config.h"

#include "errors.h"
#include "event.h"
#include "registry.h"
#include "mutex.h"
#include "pmi.h"
#include "thread.h"
#include "metadata.h"

class PlaylistItem {

 public:
    PlaylistItem(char* url, MetaData* metadata = NULL);
    virtual ~PlaylistItem();

    Error SetMetaData(MetaData* metadata);
    const MetaData* GetMetaData() const;

    const char* GetURL() const;
    
 private:
    MetaData m_metadata;
    char* m_url;

};

typedef enum {
    kPlaylistSortKey_Artist,
    kPlaylistSortKey_Album,
    kPlaylistSortKey_Title,
    kPlaylistSortKey_Year,
    kPlaylistSortKey_Track,
    kPlaylistSortKey_Genre,
    kPlaylistSortKey_Time,
    kPlaylistSortKey_Random

} PlaylistSortKey;

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

class PlaylistManager {

 public:
    PlaylistManager();
    virtual ~PlaylistManager();

    // Playlist actions
    Error SetCurrentItem(PlaylistItem* item);
    const PlaylistItem* GetCurrentItem() const;
    
    Error SetCurrentIndex(uint32 index);
    uint32 GetCurrentIndex() const;

    Error GotoNextItem(bool userAction = false);
    Error GotoPreviousItem(bool userAction = false);

    Error SetShuffleMode(bool shuffle);
    bool GetShuffleMode() const {return m_shuffle;}
    Error SetRepeatMode(RepeatMode mode);
    RepeatMode GetRepeatMode() const {return m_repeat;}
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
    Error MoveItem(PlaylistItem* item, uint32 index);
    Error MoveItem(uint32 oldIndex, uint32 newIndex);
    Error MoveItems(vector<PlaylistItem*>* items, uint32 index);

    // Functions for sorting
    Error Sort(PlaylistSortKey key, bool ascending = true);

    // Which playlist are we dealing with for purposes of editing:
    // 1) Master Playlist - list of songs to play
    // 2) Secondary Playlist - a playlist that we want to edit
    //      - External playlist
    //      - Portable playlist

    Error SetActivePlaylist(PlaylistKey key);
    PlaylistKey GetActivePlaylist() const;
    Error SetExternalPlaylist(char* url);
    const char* GetExternalPlaylist() const;
    Error SetPortablePlaylist(DeviceInfo* device);
    const DeviceInfo* GetPortablePlaylist() const;

    // External playlist support
    Error GetSupportedPlaylistFormats(PlaylistFormat* format, uint32 index);
    Error ReadPlaylist(char* url, vector<PlaylistItem*>* items = NULL);
    Error WritePlaylist(char* url, PlaylistFormat* format, 
                            vector<PlaylistItem*>* items = NULL);

    // Portable player communication
    Error GetSupportedPortables(DeviceInfo* device, uint32 index);
    bool IsPortableAvailable(DeviceInfo* device);
    Error ReadPortablePlaylist(DeviceInfo* device);
    Error SyncPortablePlaylist(DeviceInfo* device);

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


    


 private:

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

    uint32      m_current;
    bool        m_shuffle;
    RepeatMode  m_repeatMode;
    PlaylistKey m_playlistKey;

    char*       m_externalPlaylist;
    DeviceInfo  m_portableDevice;

    Mutex       m_mutex;



};

#endif // _PLAYLIST_H_










