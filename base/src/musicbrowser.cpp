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

        $Id: musicbrowser.cpp,v 1.1.2.6 1999/09/17 18:20:18 ijr Exp $
____________________________________________________________________________*/


#ifdef WIN32
#include <windows.h>
#else
#include "win32impl.h"
#endif

#include <string.h>

#include "config.h"
#include "musicbrowser.h"
#include "player.h"
#include "utility.h"

#define DBASEDELIM ":"

MusicCatalog::MusicCatalog()
{
    m_artistList = new vector<ArtistList *>;
    m_unsorted = new vector<PlaylistItem *>;
    m_playlists = new vector<char *>;
}

MusicCatalog::~MusicCatalog()
{
    delete m_artistList;
    delete m_unsorted;
    delete m_playlists;
}

void MusicCatalog::PopulateFromDatabase(MusicBrowser *mb, Database *dbase)
{
    assert(mb);
    assert(dbase);

    delete m_artistList;
    delete m_unsorted;
    delete m_playlists;

    m_artistList = new vector<ArtistList *>;
    m_unsorted = new vector<PlaylistItem *>;
    m_playlists = new vector<char *>;
 
    char *key = dbase->NextKey(NULL);
    while (key) {
        char *data = dbase->Value(key);
        if (!strncmp("P", data, 1)) {
            m_playlists->push_back(data);
        }
        else if (!strncmp("M", data, 1)) {
            MetaData *meta = mb->ReadMetaDataFromDatabase(key);
           
            assert(meta);
 
            PlaylistItem *newtrack = new PlaylistItem(key, meta);
            
            if (!strcmp(" ", meta->Artist().c_str())) {
                m_unsorted->push_back(newtrack);
            }
            else {
                bool found_artist = false;
                vector<ArtistList *>::iterator i = m_artistList->begin();
                for (; i != m_artistList->end(); i++) {
                    if (!strcmp(meta->Artist().c_str(), (*i)->name)) {
                        bool found_album = false;

                        found_artist = true;
                        vector<AlbumList *> *alList = (*i)->m_albumList;
                        vector<AlbumList *>::iterator j = alList->begin();
                        for (; j != alList->end(); j++) {
                            if (!strcmp(meta->Album().c_str(), (*j)->name)) {
                                found_album = true;
                                (*j)->m_trackList->push_back(newtrack);
                             }
                        }
                        if (!found_album) {
                            AlbumList *newalbum = new AlbumList;
                            newalbum->name = new char[strlen(meta->Album().c_str()) 
                                                      + 1];
                            strcpy(newalbum->name, meta->Album().c_str());
                            newalbum->m_trackList->push_back(newtrack);
                            alList->push_back(newalbum);
                        }
                    }
                }
                if (!found_artist) {
                    ArtistList *newartist = new ArtistList;
                    newartist->name = new char[strlen(meta->Artist().c_str()) 
                                               + 1];
                    strcpy(newartist->name, meta->Artist().c_str());
                    AlbumList *newalbum = new AlbumList;
                    newalbum->name = new char[strlen(meta->Album().c_str()) 
                                              + 1];
                    strcpy(newalbum->name, meta->Album().c_str());
                    newalbum->m_trackList->push_back(newtrack);

                    newartist->m_albumList->push_back(newalbum);
                    m_artistList->push_back(newartist);
                }
            }
        }
        key = dbase->NextKey(key);
    }
}

MusicBrowser::MusicBrowser(FAContext *context, char *path)
{
    m_database = NULL;
    m_plm = context->plm;
    m_catalog = new MusicCatalog;
    
    if (path)
        SetDatabase(path);

    if (m_database)
        m_catalog->PopulateFromDatabase(this, m_database);
}

MusicBrowser::~MusicBrowser()
{
    if (m_database)
        delete m_database;
    delete m_catalog;
}

void MusicBrowser::SetDatabase(const char *path)
{
    if (m_database)
        delete m_database;

    m_database = new Database(path);
}
   
void MusicBrowser::SearchMusic(char *path)
{
    m_numSymLinks = 0;
    DoSearchMusic(path);

    m_database->Sync();
    m_catalog->PopulateFromDatabase(this, m_database);
}

void MusicBrowser::DoSearchMusic(char *path)
{
    WIN32_FIND_DATA find;
    HANDLE handle;
    char *search;

    search = new char[strlen(path) + strlen(DIR_MARKER_STR) + 3];

  
    Player *m_player = Player::GetPlayer(0);
    strcpy(search, path);

    if (search[strlen(search) - 1] != DIR_MARKER)
       strcat(search, DIR_MARKER_STR);

    strcat(search, "*");

    handle = FindFirstFile(search, &find);

    delete search;

    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            char *fileExt;

            if ((find.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
#ifndef WIN32
                || (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
#endif
               )
            {
                if (!(!strcmp("." , find.cFileName) || !strcmp("..", find.cFileName)))
                {
#ifndef WIN32
                    if (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
                    {
                        m_numSymLinks++;
                        if (m_numSymLinks > 4)
                            return;
                    }
#endif

                    char *newDir = new char[strlen(path) + strlen(find.cFileName) 
                                            + strlen(DIR_MARKER_STR) + 1];

                    if (path[strlen(path) - 1] != DIR_MARKER)
                        sprintf(newDir, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);
                    else
                        sprintf(newDir, "%s%s", path, find.cFileName);

                    if (!strcmp(newDir, path)) {
                        delete newDir;
                        continue;
                    } 

                    DoSearchMusic(newDir);
#ifndef WIN32
                    if (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
                        m_numSymLinks--;
#endif
                    delete newDir;
                }
            }
            else if ((fileExt = m_player->GetExtension(find.cFileName)))
            {
                if (!strncmp("m3u", fileExt, 3))
                {
                    char *file = new char[strlen(path) + strlen(find.cFileName)
                                          + strlen(DIR_MARKER_STR) + 1];
                    sprintf(file, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);
                    m_database->Insert(file, "P");

                    delete file;
                }
                else if (m_player->IsSupportedExtension(fileExt))
                {
                    char *file = new char[strlen(path) + strlen(DIR_MARKER_STR) 
                                          + strlen(find.cFileName) + 1]; 

                    sprintf(file, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);

                    PlaylistItem *plist = new PlaylistItem(file);
                    m_plm->RetrieveMetaData(plist);

                    while (plist->GetState() != kPlaylistItemState_Normal)
                       usleep(5);

                    WriteMetaDataToDatabase(file, (MetaData)(plist->GetMetaData()));
 
                    delete file;
                    delete plist;
                }
                delete fileExt;
            }
        }
        while (FindNextFile(handle, &find));

        FindClose(handle);
    }
}

char *MusicBrowser::Stradd(char *dest, char *src, bool delim)
{
    char *copy = src;
    if (src[0] == '\0')
        copy = " ";
    if (delim) {
       dest = (char *)realloc(dest, strlen(dest) + strlen(copy) + strlen(DBASEDELIM) + 1);
       strcat(dest, DBASEDELIM);
    }
    else
       dest = (char *)realloc(dest, strlen(dest) + strlen(copy) + 1);
    strcat(dest, copy);
    return dest;
}

char *MusicBrowser::Stradd(char *dest, uint32 src, bool delim)
{
    char inthold[11];

    sprintf(inthold, "%u", src);
    dest = Stradd(dest, inthold);
    return dest;
}
   
void MusicBrowser::WriteMetaDataToDatabase(char *path, MetaData information)
{
    char *data;
    char *tempstr;
    uint32 tempint;

    data = (char *)malloc(2);
    sprintf(data, "M");
    tempstr = (char *)(information.Artist()).c_str();
    data = Stradd(data, tempstr);
    tempstr = (char *)(information.Album()).c_str();
    data = Stradd(data, tempstr);
    tempstr = (char *)(information.Title()).c_str();
    data = Stradd(data, tempstr);
    tempstr = (char *)(information.Comment()).c_str();
    data = Stradd(data, tempstr);
    tempstr = (char *)(information.Genre()).c_str();
    data = Stradd(data, tempstr);

    tempint = information.Year();
    data = Stradd(data, tempint);
    tempint = information.Track();
    data = Stradd(data, tempint);
    tempint = information.Time();
    data = Stradd(data, tempint);
    tempint = information.Size();
    data = Stradd(data, tempint, false);

    m_database->Insert(path, data);

    free(data);
}

MetaData *MusicBrowser::ReadMetaDataFromDatabase(char *path)
{
    char *data = m_database->Value(path);

    if (!data)
        return NULL;

    MetaData *new_metadata = new MetaData();
    char *temp = data + 1;
    char *info; 

    info = strtok(temp, DBASEDELIM);
    new_metadata->SetArtist(info);
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetAlbum(info);
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetTitle(info);
    info = strtok(NULL, DBASEDELIM);

    new_metadata->SetComment(info);
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetGenre(info);
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetYear(atoi(info));
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetTrack(atoi(info));
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetTime(atoi(info));
    info = strtok(NULL, DBASEDELIM);
    new_metadata->SetSize(atoi(info));

    delete data;
    return new_metadata;
}