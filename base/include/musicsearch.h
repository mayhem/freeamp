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

        $Id: musicsearch.h,v 1.1.2.1 1999/08/18 04:18:07 ijr Exp $
____________________________________________________________________________*/


#ifndef _MUSICSEARCH_H_
#define _MUSICSEARCH_H_

#include "database.h"

class SearchMetaData
{
 public:
    char m_songName[256];
    char m_artist[256];
    char m_album[256];
    char m_year[5];
    char m_comment[256];
    char m_genre;
    int  m_songLength;
};

class MusicSearch 
{
 public:
    MusicSearch(char *path = NULL);
    ~MusicSearch();
    
    void SetDatabase(const char *path);
    void SearchMusic(char *path);

 private:
    void DoSearchMusic(char *path);
    Database<SearchMetaData> *m_database;
#ifndef WIN32    
    int m_numSymLinks;
#endif    
};

#endif
   
