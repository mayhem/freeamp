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
	
	$Id: metadata.h,v 1.1.2.4 1999/08/27 16:55:28 ijr Exp $
____________________________________________________________________________*/

#ifndef _METADATA_H_
#define _METADATA_H_

#include <string>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"


class MetaData {

 public:

    MetaData()
    {
        m_year = 0;
        m_track = 0;
        m_time = 0;
    }

    virtual ~MetaData(){}

    Error SetArtist(const char* artist){ m_artist = artist; return kError_NoErr;}
    Error GetArtist(char* buf, uint32* len) { return SetBuffer(buf, m_artist.c_str(), len); }
    const string& Artist() const { return m_artist; }

    Error SetAlbum(const char* album) { m_album = album; return kError_NoErr; }
    Error GetAlbum(char* buf, uint32* len) { return SetBuffer(buf, m_album.c_str(), len); }
    const string& Album() const { return m_album; }

    Error SetTitle(const char* title){ m_title = title; return kError_NoErr; }
    Error GetTitle(char* buf, uint32* len) { return SetBuffer(buf, m_title.c_str(), len); }
    const string& Title() const { return m_title; }

    Error SetComment(const char* comment){ m_comment = comment; return kError_NoErr; }
    Error GetComment(char* buf, uint32* len) { return SetBuffer(buf, m_comment.c_str(), len); }
    const string& Comment() const { return m_comment; }

    Error SetGenre(const char* genre) { m_genre = genre; return kError_NoErr; }
    Error GetGenre(char* buf, uint32* len) { return SetBuffer(buf, m_genre.c_str(), len); }
    const string& Genre() const { return m_genre; }

    Error SetYear(uint32 year) { m_year = year; return kError_NoErr;}
    uint32 Year() const { return m_year; }

    Error SetTrack(uint32 track){ m_track = track; return kError_NoErr;}
    uint32 Track() { return m_track; }

    Error SetTime(uint32 time){ m_time = time; return kError_NoErr;}
    uint32 Time() { return m_time; }
 
 protected:
    Error SetBuffer(char* dest, const char* src, uint32* len)
    {
        Error result = kError_InvalidParam;

        assert(dest);
        assert(src);
        assert(len);

        if(dest && src)
        {
            uint32 srclen = strlen(src) + 1;

            if(*len >= srclen)
            {
                strcpy(dest, src);
                result = kError_NoErr;
            }
            else
            {
                result = kError_BufferTooSmall;
            }

            *len = srclen;
        }

        return result;
    }

 private:
  
    string m_artist;
    string m_album;
    string m_title;
    string m_genre;
    string m_comment;
    uint32 m_year;
    uint32 m_track;
    uint32 m_time;

};

class MetaDataFormat {
 public:
    MetaDataFormat();
    virtual ~MetaDataFormat();

    virtual bool ReadMetaData(const char* url, MetaData* metadata);
    virtual bool WriteMetaData(const char* url, const MetaData& metadata);
};



#endif // _METADATA_H_

