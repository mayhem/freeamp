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

        $Id: musicbrowser.h,v 1.1.2.9 1999/10/12 00:04:54 ijr Exp $
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

    void AddPlaylist(const char *path);
    void AddSong(const char *path);
    void AddOneFromDatabase(char *key);    
    void PopulateFromDatabase();
    
    vector<ArtistList *> *m_artistList;
    vector<PlaylistItem *> *m_unsorted;
    vector<string> *m_playlists;

private:
    FAContext *m_context;
};

class MusicBrowser : public EventQueue
{
 public:
    MusicBrowser(FAContext *context, char *path = NULL);
    virtual ~MusicBrowser();

    void SetDatabase(const char *path);
    void SearchMusic(char *path);
    
    void WriteMetaDataToDatabase(char *path, MetaData  information);
    MetaData *ReadMetaDataFromDatabase(char *path);
    virtual int32 AcceptEvent(Event *e);
    
    MusicCatalog *m_catalog;
    Database *GetDatabase() { return m_database; }

 protected:
    static void musicsearch_thread_function(void *arg);
    void DoSearchMusic(char *path);
    
    int m_numSymLinks;
    Mutex *m_mutex;
    
    FAContext *m_context;
    Player *m_player;

 private:   
    Database *m_database;
    PlaylistManager *m_plm;
};

#endif
