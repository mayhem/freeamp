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

        $Id: musicsearch.cpp,v 1.1.2.1 1999/08/18 04:18:07 ijr Exp $
____________________________________________________________________________*/


#ifdef WIN32
#include <windows.h>
#else
#include "win32impl.h"
#endif

#include <string.h>

#include "config.h"
#include "musicsearch.h"
#include "player.h"

MusicSearch::MusicSearch(char *path)
{
    m_database = NULL;

    if (path)
        SetDatabase(path);
}

MusicSearch::~MusicSearch()
{
    if (m_database)
        delete m_database;
}

void MusicSearch::SetDatabase(const char *path)
{
    if (m_database)
        delete m_database;

    m_database = new Database<SearchMetaData>(path);
}
   
void MusicSearch::SearchMusic(char *path)
{
    m_numSymLinks = 0;
    DoSearchMusic(path);
}

void MusicSearch::DoSearchMusic(char *path)
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
                char newDir[MAX_PATH];

                if (!(!strcmp("." , find.cFileName) || !strcmp("..", find.cFileName)))
                {
                    if (path[strlen(path) - 1] != DIR_MARKER)
                        sprintf(newDir, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);
                    else
                        sprintf(newDir, "%s%s", path, find.cFileName);
#ifndef WIN32
                    if (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
                    {
                        m_numSymLinks++;
                        if (m_numSymLinks > 4)
                            return;
                    }
#endif
                    DoSearchMusic(newDir);
#ifndef WIN32
                    if (find.dwFileAttributes == FILE_ATTRIBUTE_SYMLINK)
                        m_numSymLinks--;
#endif
                }
            }
            else if (fileExt)
            {
                if (!strncmp("m3u", fileExt, 3))
                {
                    // FIXME: Add to playlist manager
                }
                else if (m_player->IsSupportedExtension(fileExt))
                {
                    char file[MAX_PATH];
 
                    sprintf(file, "%s%s%s", path, DIR_MARKER_STR, find.cFileName);

                    SearchMetaData songMetaData;
                    // FIXME: get file info, fill songMetaData

                    m_database->Insert(file, songMetaData);
                }
                delete fileExt;
            }
        }
        while (FindNextFile(handle, &find));

        FindClose(handle);
    }
}
