
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
	
	$Id: playlist.h,v 1.6 1998/10/14 17:33:24 jdw Exp $
____________________________________________________________________________*/

#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "vector.h"

class PlayListItem {
 public:
    char *url;
    int32 type;
    int32 startFrame;

    PlayListItem();
    ~PlayListItem();
};

class PlayList {
 private:
    Vector<PlayListItem *> *pMediaElems;
    int32 current;
    int32 skipNum;
 public:
    PlayList();
    ~PlayList();
    void Add(char *,int);
    void SetSkip(int32 f) { skipNum = f; } // logical media units to skip at beginning
    void Shuffle();
    int32 GetSkip() { return skipNum; }
    PlayListItem *GetFirst();
    PlayListItem *GetNext();
    PlayListItem *GetPrev();
    PlayListItem *GetCurrent();
    void SetFirst();
    void SetNext();
    void SetPrev();
};


#endif // _PLAYLIST_H_
