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
	
	$Id: metadata.h,v 1.1.2.1 1999/08/23 19:18:39 elrod Exp $
____________________________________________________________________________*/

#ifndef _METADATA_H_
#define _METADATA_H_

#include <assert.h>

#include "config.h"
#include "errors.h"


class MetaData {

 public:

    MetaData()
    {
        m_artist = NULL;
        m_album = NULL;
        m_title = NULL;
        m_comment = NULL;
        m_genre = NULL;
        m_year = -1;
        m_track = -1;
        m_time = -1;
        
    }

    MetaData(const MetaData& metadata)
    {
        m_artist = NULL;
        m_album = NULL;
        m_title = NULL;
        m_comment = NULL;
        m_genre = NULL;
        m_year = -1;
        m_track = -1;
        m_time = -1;

        *this = metadata;
    }

    virtual ~MetaData()
    {
        if(m_artist) delete [] m_artist;
        if(m_album) delete [] m_album;
        if(m_title) delete [] m_title;
        if(m_comment) delete [] m_comment;
    }

    Error SetArtist(const char* artist){ return SetBuffer(&m_artist, artist); }
    const char* GetArtist() const { return m_artist; }

    Error SetAlbum(const char* album) { return SetBuffer(&m_album, album); }
    const char* GetAlbum() { return m_album; }

    Error SetTitle(const char* title){ return SetBuffer(&m_title, title); }
    const char* GetTitle() { return m_title; }

    Error SetYear(uint32 year) { m_year = year; }
    uint32 Year() { return m_year; }

    Error SetGenre(const char* genre) { return SetBuffer(&m_genre, genre); }
    const char* GetGenre() { return m_genre; }

    Error SetTrack(uint32 track){ m_track = track; }
    uint32 GetTrack() { return m_track; }

    Error SetTime(uint32 time){ m_time = time; }
    uint32 GetTime() { return m_time; }

    Error SetComment(const char* comment){ return SetBuffer(&m_comment, comment); }
    const char* GetComment() { return m_comment; }

    MetaData& operator = (MetaData& metadata)
    {
        SetArtist(metadata.m_artist);
        SetAlbum(metadata.m_album);
        SetTitle(metadata.m_title);
        SetComment(metadata.m_comment);
        SetGenre(metadata.m_genre);
        SetYear(metadata.m_year);
        SetTrack(metadata.m_track);
        SetTime(metadata.m_time);

        return *this;
    }

 protected:
    Error SetBuffer(char** buf, const char* src)
    {
        Error result = kError_InvalidParam;

        assert(buf);
        assert(src);

        if(buf && src)
        {
            if(*buf)
            {
                delete [] *buf;
                *buf = NULL;
            }

            result = kError_OutOfMemory;

            *buf = new char[strlen(src) + 1];

            if(*buf)
            {
                strcpy(buf, src);
                result = kError_NoErr;
            }
        }

        return result;
    }

 private:
  
    char* m_artist;
    char* m_album;
    char* m_title;
    char* m_genre;
    char* m_comment;
    uint32 m_year;
    uint32 m_track;
    uint32 m_time;

};



#endif // _METADATA_H_

