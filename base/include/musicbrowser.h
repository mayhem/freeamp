/*____________________________________________________________________________
 
        FreeAmp - The Free MP3 Player
 
        Portions Copyright (C) 1999 EMusic.com

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

        $Id: musicbrowser.h,v 1.4 1999/10/23 04:54:42 ijr Exp $
 ____________________________________________________________________________*/

#ifndef INCLUDED_MUSICBROWSER_H_
#define INCLUDED_MUSICBROWSER_H_

#include <vector>
#include <string>
using namespace std;

#include "event.h"
#include "database.h"
#include "metadata.h"
#include "playlist.h"

class FAContext;
class Player;

class AlbumList {
 public:
     AlbumList() { m_trackList = new vector<PlaylistItem *>; }
    ~AlbumList() {
                      vector<PlaylistItem *>::iterator i = m_trackList->begin();
		      for (; i != m_trackList->end(); i++)
                          delete (*i);
                  }

    vector<PlaylistItem *> *m_trackList;
    string name;
};

class ArtistList {
 public:
    ArtistList() { m_albumList = new vector<AlbumList *>; }
   ~ArtistList() {
                     vector<AlbumList *>::iterator i = m_albumList->begin();
           	     for (; i != m_albumList->end(); i++)
                         delete (*i);
		 }
    
    vector<AlbumList *> *m_albumList;
    string name;
};

class MusicBrowser;

class MusicCatalog
{
 public:
    MusicCatalog(FAContext *context);
    ~MusicCatalog();

    Error AddPlaylist(const char *url);
    Error AddSong(const char *url);
    Error Add(const char *url);    

    Error RePopulateFromDatabase();

    Error RemovePlaylist(const char *url);
    Error RemoveSong(const char *url);
    Error Remove(const char *url);

    void  ClearCatalog(void);

    const vector<ArtistList *> *GetMusicList(void) { return m_artistList; }
    const vector<PlaylistItem *> *GetUnsortedMusic(void) { return m_unsorted; }
    const vector<string> *GetPlaylists(void) { return m_playlists; }

private:
    vector<ArtistList *> *m_artistList;
    vector<PlaylistItem *> *m_unsorted;
    vector<string> *m_playlists;
   
    FAContext *m_context;
};

class MusicBrowser : public EventQueue
{
 public:
    MusicBrowser(FAContext *context, char *path = NULL);
    virtual ~MusicBrowser();

    void SetDatabase(const char *path);
    void SearchMusic(vector<string> &pathList);
    void StopSearchMusic(void);
    
    void WriteMetaDataToDatabase(const char *url, const MetaData information);
    MetaData *ReadMetaDataFromDatabase(const char *url);

    virtual int32 AcceptEvent(Event *e);
    
    MusicCatalog *m_catalog;
    Database *GetDatabase() { return m_database; }

 protected:
    static void musicsearch_thread_function(void *arg);
    void DoSearchMusic(char *path);
    void DoSearchPaths(vector<string> &pathList);
    void PruneDatabase(void);
    
    bool m_exit;
    Mutex *m_mutex;
    
    FAContext *m_context;

 private:   
    Database *m_database;
    PlaylistManager *m_plm;
};

#endif
