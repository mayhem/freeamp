// $Id: misc_support.h,v 1.2 2000/05/22 14:05:02 robert Exp $

// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug

// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
// License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

// The id3lib authors encourage improvements and optimisations to be sent to
// the id3lib coordinator.  Please see the README file for details on where to
// send such submissions.  See the AUTHORS file for a list of people who have
// contributed to id3lib.  See the ChangeLog file for a list of changes to
// id3lib.  These files are distributed with id3lib at
// http://download.sourceforge.net/id3lib/

#ifndef __ID3LIB_MISC_SUPPORT_H__
#define __ID3LIB_MISC_SUPPORT_H__

#include "tag.h"

char*      ID3_GetString(const ID3_Frame *, ID3_FieldID, size_t nItems = 1);

// defined in 'id3_misc_support.cpp'
// these are 'convenience functions,' to make using the library easier for the 
// most common of operations
char*      ID3_GetArtist(const ID3_Tag*);
ID3_Frame* ID3_AddArtist(ID3_Tag*, const char*, bool replace = false);
size_t     ID3_RemoveArtists(ID3_Tag*);

char*      ID3_GetAlbum(const ID3_Tag*);
ID3_Frame* ID3_AddAlbum(ID3_Tag*, const char*, bool replace = false);
size_t     ID3_RemoveAlbums(ID3_Tag*);

char*      ID3_GetTitle(const ID3_Tag*);
ID3_Frame* ID3_AddTitle(ID3_Tag*, const char*, bool replace = false);
size_t     ID3_RemoveTitles(ID3_Tag*);

char*      ID3_GetYear(const ID3_Tag*);
ID3_Frame* ID3_AddYear(ID3_Tag*, const char*, bool replace = false);
size_t     ID3_RemoveYears(ID3_Tag*);

char*      ID3_GetComment(const ID3_Tag*);
ID3_Frame* ID3_AddComment(ID3_Tag *, const char*, 
                          const char* desc = "", bool replace = false);
size_t     ID3_RemoveComments(ID3_Tag*, const char * = NULL);

char*      ID3_GetTrack(const ID3_Tag*);
luint      ID3_GetTrackNum(const ID3_Tag*);
ID3_Frame* ID3_AddTrack(ID3_Tag*, uchar ucTrack, uchar ucTotal = 0,
                        bool replace = false);
ID3_Frame* ID3_AddTrack(ID3_Tag*, uchar ucTrack, bool replace);
size_t     ID3_RemoveTracks(ID3_Tag*);

char*      ID3_GetGenre(const ID3_Tag*);
luint      ID3_GetGenreNum(const ID3_Tag*);
ID3_Frame* ID3_AddGenre(ID3_Tag*, luint ucGenre, bool replace = false);
size_t     ID3_RemoveGenres(ID3_Tag*);

char*      ID3_GetLyrics(const ID3_Tag*);
ID3_Frame* ID3_AddLyrics(ID3_Tag*, const char *, bool replace = false);
size_t     ID3_RemoveLyrics(ID3_Tag*);

char*      ID3_GetLyricist(const ID3_Tag*);
ID3_Frame* ID3_AddLyricist(ID3_Tag *, const char *, bool replace = false);
size_t     ID3_RemoveLyricist(ID3_Tag*);

ID3_Frame* ID3_AddSyncLyrics(ID3_Tag *tag, const char *lang, const char *desc,
                             const uchar *text, luint textsize, 
                             bool bReplace = false);
ID3_Frame* ID3_GetSyncLyricsInfo(const ID3_Tag *tag, const char *lang, 
                                 const char *desc, char &stampformat, 
                                 char &type, luint &size);
ID3_Frame* ID3_GetSyncLyrics(const ID3_Tag *tag, const char *lang, 
                             const char *desc, char *pData, luint &size);

#endif /* __ID3LIB_MISC_SUPPORT_H__ */
