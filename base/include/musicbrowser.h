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

        $Id: musicbrowser.h,v 1.1.2.3 1999/09/10 02:20:14 ijr Exp $
 ____________________________________________________________________________*/

#ifndef INCLUDED_MUSICBROWSER_H_
#define INCLUDED_MUSICBROWSER_H_

#include "database.h"
#include "metadata.h"
#include "playlist.h"

class FAContext;

class MusicBrowser
{
 public:
    MusicBrowser(FAContext *context, char *path = NULL);
    ~MusicBrowser();

    void SetDatabase(const char *path);
    void SearchMusic(char *path);
    
    void WriteMetaDataToDatabase(char *path, MetaData information);
    MetaData *ReadMetaDataFromDatabase(char *path);
    
 private:
    void DoSearchMusic(char *path);
    char *Stradd(char *dest, char *src, bool delim = true);
    char *Stradd(char *dest, uint32 src, bool delim = true);

    Database *m_database;
    int m_numSymLinks;
    PlaylistManager *m_plm;
};

#endif
