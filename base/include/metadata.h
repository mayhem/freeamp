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
	
	$Id: metadata.h,v 1.8.6.1 2000/09/28 13:13:27 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_METADATA_H_
#define INCLUDED_METADATA_H_

#include <string>
#include <iostream>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"
#include "facontext.h"


class MetaData {
public:
    static HashStore *m_store;  // CEK
    MetaData()
    {
        m_artist    = NULL;
        m_album     = NULL;
        m_title     = NULL;
        m_genre     = NULL;
        m_comment   = NULL;
        m_extension = NULL;
        m_guid      = NULL;
        m_store->set_entry(&m_artist,    NULL);
        m_store->set_entry(&m_album,     NULL);
        m_store->set_entry(&m_title,     NULL);
        m_store->set_entry(&m_genre,     NULL);
        m_store->set_entry(&m_comment,   NULL);
        m_store->set_entry(&m_extension, NULL);
        m_store->set_entry(&m_guid,      NULL);
        m_year      = 0;
        m_track     = 0;
        m_time      = 0;
        m_size      = 0;
        m_playcount = 0;
    }

    MetaData(const MetaData& other) 
    {
        m_artist    = NULL;
        m_album     = NULL;
        m_title     = NULL;
        m_genre     = NULL;
        m_comment   = NULL;
        m_extension = NULL;
        m_guid      = NULL;
        m_store->set_entry(&m_artist,    other.m_artist);
        m_store->set_entry(&m_album,     other.m_album);
        m_store->set_entry(&m_title,     other.m_title);
        m_store->set_entry(&m_genre,     other.m_genre);
        m_store->set_entry(&m_comment,   other.m_comment);
        m_store->set_entry(&m_extension, other.m_extension);
        m_store->set_entry(&m_guid,      other.m_guid);
        m_year      = other.m_year;
        m_track     = other.m_track;
        m_time      = other.m_time;
        m_size      = other.m_size;
        m_playcount = other.m_playcount;
    }

    virtual ~MetaData()
    {
        cerr << "\n~Metadata\n";
        // unref to free memory and balance the books
        m_store->unref(m_artist);
        m_store->unref(m_album);
        m_store->unref(m_title);
        m_store->unref(m_genre);
        m_store->unref(m_comment);
        m_store->unref(m_extension);
        m_store->unref(m_guid);
    }

    // I hate assignment operators...but the program expects it
    MetaData& operator=(const MetaData& other) 
    {
        m_store->set_entry(&m_artist,    other.m_artist);
        m_store->set_entry(&m_album,     other.m_album);
        m_store->set_entry(&m_title,     other.m_title);
        m_store->set_entry(&m_genre,     other.m_genre);
        m_store->set_entry(&m_comment,   other.m_comment);
        m_store->set_entry(&m_extension, other.m_extension);
        m_store->set_entry(&m_guid,      other.m_guid);
        m_year      = other.m_year;
        m_track     = other.m_track;
        m_time      = other.m_time;
        m_size      = other.m_size;
        m_playcount = other.m_playcount;
        return *this; 
    }

    static void SetCharStore(HashStore* store)
    {
        assert(store);
        if (!m_store)
        {
            m_store = store;
        }
        cerr << "MetaData::SetCharStore: m_store. Currently:" << endl << *m_store << endl;
    }

    Error SetArtist(const char* artist){ 
            m_store->set_entry(&m_artist,artist);
            return kError_NoErr;}
    Error GetArtist(char* buf, uint32* len) const { return SetBuffer(buf, m_artist, len); }
    const char* PeekArtist() const { return m_artist; }
    const string Artist() const { return m_artist; }
    size_t Artist_length() const { return (m_artist?strlen(m_artist):0); }

    Error SetAlbum(const char* album) { 
        m_store->set_entry(&m_album,album);
        return kError_NoErr; }
    Error GetAlbum(char* buf, uint32* len) const { return SetBuffer(buf, m_album, len); }
    const char* PeekAlbum() const { return m_album; }
    const string Album() const { return m_album; }
    size_t Album_length() const { return (m_album?strlen(m_album):0); }

    Error SetTitle(const char* title){ 
        m_store->set_entry(&m_title,title);
        return kError_NoErr; }
    Error GetTitle(char* buf, uint32* len) const { return SetBuffer(buf, m_title, len); }
    const char* PeekTitle() const { return m_title; }
    const string Title() const { return m_title; }
    size_t Title_length() const { return (m_title?strlen(m_title):0); }

    Error SetComment(const char* comment){ 
        m_store->set_entry(&m_comment,comment);
        return kError_NoErr; }
    Error GetComment(char* buf, uint32* len) const { return SetBuffer(buf, m_comment, len); }
    const char* PeekComment() const { return m_comment; }
    const string Comment() const { return m_comment; }
    size_t Comment_length() const { return (m_comment?strlen(m_comment):0); }

    Error SetGenre(const char* genre) { 
        m_store->set_entry(&m_genre,genre);
        return kError_NoErr; }
    Error GetGenre(char* buf, uint32* len) const { return SetBuffer(buf, m_genre, len); }
    const char* PeekGenre() const { return m_genre; }
    const string Genre() const { return m_genre; }
    size_t Genre_length() const { return (m_genre?strlen(m_genre):0); }

    Error SetFormatExtension(const char* extension){ 
        m_store->set_entry(&m_extension,extension);
        return kError_NoErr; }
    Error GetFormatExtension(char* buf, uint32* len) const { return SetBuffer(buf, m_extension, len); }
    const char* PeekFormatExtension() const { return m_extension; }
    const string FormatExtension() const { return m_extension; }
    size_t FormatExtension_length() const { return (m_extension?strlen(m_extension):0); }

    Error SetYear(uint32 year) { m_year = year; return kError_NoErr;}
    uint32 Year() const { return m_year; }

    Error SetTrack(uint32 track){ m_track = track; return kError_NoErr;}
    uint32 Track() const { return m_track; }

    Error SetTime(uint32 time){ m_time = time; return kError_NoErr;}
    uint32 Time() const { return m_time; }

    Error SetSize(uint32 bytes){ m_size = bytes; return kError_NoErr;}
    uint32 Size() const { return m_size; }

    Error SetGUID(const char *guid) { 
        m_store->set_entry(&m_guid,guid);
        return kError_NoErr; }
    Error GetGUID(char *buf, uint32 *len) { return SetBuffer(buf, m_guid, len); }
    const char* PeekGUID() const { return m_guid; }
    const string GUID() const { return m_guid; }
    size_t GUID_length() const { return (m_guid?strlen(m_guid):0); }

    Error SetPlayCount(uint32 playcount) { m_playcount = playcount; return kError_NoErr; }
    uint32 PlayCount() const { return m_playcount; }
    void AddPlayCount() { m_playcount++; }

    bool operator==(const MetaData& data) const
    {
        bool result = false;

        result = ( compare(m_artist,data.m_artist) &&
                   compare(m_album,data.m_album) &&
                   compare(m_title,data.m_title) &&
                   compare(m_genre,data.m_genre) &&
                   compare(m_comment,data.m_comment) &&
                   m_year == data.m_year &&
                   m_track == data.m_track &&
                   m_time == data.m_time &&
                   m_size == data.m_size &&
		   compare(m_extension,data.m_extension) );

        return result;
    }

    bool operator!=(const MetaData& data) const
    {
	    return !(*this == data);
    } 

    static bool compare(const char* a, const char* b) 
    {
        if (a&&b)
            return (0==strcmp(a,b));
        if ((!a) && (!b))
            return true;
        return false;
    }

    ostream& print_stream(ostream& out);
    friend ostream& operator<< (ostream& out, MetaData& metadata);

protected:
    static Error SetBuffer(char* dest, const char* src, uint32* len) 
    {
        assert(dest);
        assert(len);
        Error result = kError_InvalidParam;
        if(src)
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
        else 
        {
            uint32 srclen = 1;
            if (*len >= srclen)
            {
                dest[0] = 0;
                result = kError_NoErr;
            }
            else
            {
                result = kError_BufferTooSmall;
            }
            *len=srclen;
        }
        return result;
    }

private:
    char * m_artist;
    char * m_album;
    char * m_title;
    char * m_genre;
    char * m_comment;
    char * m_extension;
    char * m_guid;
    uint32 m_year;
    uint32 m_track;
    uint32 m_time;
    uint32 m_size;
    uint32 m_playcount;
};

typedef enum MetaDataOrder {
    MetaDataOrder_First  =    0,  // for some reason this plugin should be called before others
    MetaDataOrder_Low    =    25, // not very reliable, perhaps parsing the filename
    MetaDataOrder_Medium =    50, // not too reliable, perhaps limited in the amount of data allowed
    MetaDataOrder_High   =    75, // reliable, no restrictions on length of data
    MetaDataOrder_Last   =    100 // for some reason this plugin should be called after others
} MetaDataOrder;

class MetaDataFormat {
 public:
    MetaDataFormat(FAContext *context) { m_context = context; }
    virtual ~MetaDataFormat() {}

    virtual bool ReadMetaData(const char* url, MetaData* metadata) = 0;
    virtual bool WriteMetaData(const char* url, const MetaData& metadata) = 0;
    virtual MetaDataOrder Order() = 0;

 protected:
    FAContext *m_context;
};



#endif // _METADATA_H_

