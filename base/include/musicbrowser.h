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

        $Id: musicbrowser.h,v 1.1.2.4 1999/09/16 00:03:58 ijr Exp $
 ____________________________________________________________________________*/

#ifndef INCLUDED_MUSICBROWSER_H_
#define INCLUDED_MUSICBROWSER_H_

#include <vector>
using namespace std;

#include "database.h"
#include "metadata.h"
#include "playlist.h"

class FAContext;

class AlbumList {
 public:
     AlbumList() { m_trackList = new vector<PlaylistItem *>; }
    ~AlbumList() {
                      vector<PlaylistItem *>::iterator i = m_trackList->begin();
		      for (; i != m_trackList->end(); i++)
                          delete (*i);
                      delete name;
                  }

    vector<PlaylistItem *> *m_trackList;
    char *name;
};

class ArtistList {
 public:
    ArtistList() { m_albumList = new vector<AlbumList *>; }
   ~ArtistList() {
                     vector<AlbumList *>::iterator i = m_albumList->begin();
           	     for (; i != m_albumList->end(); i++)
                         delete (*i);
		     delete name;
		 }
    
    vector<AlbumList *> *m_albumList;
    char *name;
};

class MusicBrowser;

class MusicCatalog
{
 public:
    MusicCatalog();
    ~MusicCatalog();
    
    void PopulateFromDatabase(MusicBrowser *mb, Database *dbase);
    
    vector<ArtistList *> *m_artistList;
    vector<PlaylistItem *> *m_unsorted;
    vector<char *> *m_playlists;
};

class MusicBrowser
{
 public:
    MusicBrowser(FAContext *context, char *path = NULL);
    ~MusicBrowser();

    void SetDatabase(const char *path);
    void SearchMusic(char *path);
    
    void WriteMetaDataToDatabase(char *path, MetaData information);
    MetaData *ReadMetaDataFromDatabase(char *path);
    
    MusicCatalog *m_catalog;

 private:
    void DoSearchMusic(char *path);
    char *Stradd(char *dest, char *src, bool delim = true);
    char *Stradd(char *dest, uint32 src, bool delim = true);

    Database *m_database;
    int m_numSymLinks;
    
    PlaylistManager *m_plm;
};

#endif
