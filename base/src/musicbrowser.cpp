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

        $Id: musicbrowser.cpp,v 1.1.2.4 1999/09/10 02:20:15 ijr Exp $
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

MusicBrowser::MusicBrowser(FAContext *context, char *path)
{
    m_database = NULL;
    m_plm = context->plm;

    if (path)
        SetDatabase(path);
}

MusicBrowser::~MusicBrowser()
{
    if (m_database)
        delete m_database;
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
}

void MusicBrowser::DoSearchMusic(char *path)
{
    WIN32_FIND_DATA find;
    HANDLE handle;
    char search[MAX_PATH];
  
    Player *m_player = Player::GetPlayer(0);
 
    strcpy(search, path);

    if (search[strlen(search) - 1] != DIR_MARKER)
       strcat(search, DIR_MARKER_STR);

    strcat(search, "*");

    handle = FindFirstFile(search, &find);

    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            char *fileExt = m_player->GetExtension(find.cFileName);

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

                    char *newDir = new char[MAX_PATH];

                    if (path[strlen(path) - 1] != DIR_MARKER)
                        sprintf(newDir, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);
                    else
                        sprintf(newDir, "%s%s", path, find.cFileName);
                    
                    DoSearchMusic(newDir);
#ifndef WIN32
                    if (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
                        m_numSymLinks--;
#endif
                    delete newDir;
                }
            }
            else if (fileExt)
            {
                if (!strncmp("m3u", fileExt, 3))
                {
                    // FIXME: Add to database as playlist item
                }
                else if (m_player->IsSupportedExtension(fileExt))
                {
                    char *file = new char[MAX_PATH]; 

                    sprintf(file, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);

                    PlaylistItem *plist = new PlaylistItem(file);
                    m_plm->RetrieveMetaData(plist);

                    while (plist->GetState() != kPlaylistItemState_Normal)
                       usleep(5);

                    WriteMetaDataToDatabase(file, (MetaData)(plist->GetMetaData()));
                    ReadMetaDataFromDatabase(file);
 
                    delete file;
                    delete plist;
                }
                delete fileExt;
            }
        }
        while (FindNextFile(handle, &find));

        FindClose(handle);
    }
    m_database->Sync();
}

char *MusicBrowser::Stradd(char *dest, char *src, bool delim)
{
    if (delim) {
       dest = (char *)realloc(dest, strlen(dest) + strlen(src) + strlen(DBASEDELIM) + 2);
       strcat(dest, DBASEDELIM);
    }
    else
       dest = (char *)realloc(dest, strlen(dest) + strlen(src) + 2);
    strcat(dest, src);
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

    tempstr = (char *)(information.Artist()).c_str();
    data = strdup(tempstr);
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
    char *temp = data;
    char *info; 

    info = strtok(temp, DBASEDELIM);
    new_metadata->SetArtist(info);
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetAlbum(info);
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetTitle(info);
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetComment(info);
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetGenre(info);
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetYear(atoi(info));
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetTrack(atoi(info));
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetTime(atoi(info));
    info = strtok(temp, DBASEDELIM);
    new_metadata->SetSize(atoi(info));

    delete data;
    return new_metadata;
}
