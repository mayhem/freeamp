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
	
	$Id: playlistformat.h,v 1.1.2.4 1999/08/26 11:02:01 elrod Exp $
____________________________________________________________________________*/

#ifndef _PLAYLIST_FORMAT_H_
#define _PLAYLIST_FORMAT_H_

#include <string>
#include <vector>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"

typedef bool (*callback_function)(void * cookie);

class PlaylistFormatInfo;
class PlaylistItem;

class PlaylistFormat {

 public:

    PlaylistFormat();
    virtual ~PlaylistFormat();

    virtual Error GetSupportedFormats(PlaylistFormatInfo* info, uint32 index);
    virtual Error ReadPlaylist(char* url, vector<PlaylistItem*>* items,
                                callback_function function = NULL);
    virtual Error WritePlaylist(char* url, PlaylistFormatInfo* format, 
                                vector<PlaylistItem*>* items,
                                callback_function function = NULL);

 private:
  
};

typedef PlaylistFormat* FormatRef;

class PlaylistFormatInfo {

 public:

    PlaylistFormatInfo() {}
    
    virtual ~PlaylistFormatInfo() {}

    Error SetExtension(const char* extension)
    { m_extension = extension; return kError_NoErr; }
    const char* GetExtension() const { return m_extension.c_str(); }

    Error SetDescription(const char* description) 
    { m_description = description; return kError_NoErr; }
    const char* GetDescription() { return m_description.c_str(); }

    Error SetRef(FormatRef ref) { m_ref = ref; return kError_NoErr; }
    const FormatRef GetRef() const { return m_ref; }

 private:
  
    string m_extension;
    string m_description;
    FormatRef m_ref;
};



#endif // _PLAYLIST_FORMAT_H_

