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
	
	$Id: playlistformat.h,v 1.1.2.1 1999/08/23 19:18:39 elrod Exp $
____________________________________________________________________________*/

#ifndef _PLAYLIST_FORMAT_H_
#define _PLAYLIST_FORMAT_H_

#include <assert.h>

#include "config.h"
#include "errors.h"


class PlaylistFormat {

 public:

    PlaylistFormat()
    {
        m_extension = NULL;
        m_description = NULL;
    }

    PlaylistFormat(const PlaylistFormat& format)
    {
        m_extension = NULL;
        m_description = NULL;

        *this = format;
    }

    virtual ~PlaylistFormat()
    {
        if(m_extension) delete [] m_extension;
        if(m_description) delete [] m_description;
    }

    Error SetExtension(const char* extension){ return SetBuffer(&m_extension, extension); }
    const char* GetExtension() const { return m_extension; }

    Error SetDescription(const char* description) { return SetBuffer(&m_description, description); }
    const char* GetDescription() { return m_description; }

    PlaylistFormat& operator = (PlaylistFormat& format)
    {
        SetExtension(format.m_extension);
        SetDescription(format.m_description);

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
  
    char* m_extension;
    char* m_description;
};



#endif // _PLAYLIST_FORMAT_H_

