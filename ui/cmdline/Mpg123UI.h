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
	
	$Id: Mpg123UI.h,v 1.1 1998/10/15 16:00:58 elrod Exp $
____________________________________________________________________________*/

// Mpg123UI.h


#ifndef _Mpg123UI_H_
#define _Mpg123UI_H_

#include "ctrlobj.h"
#include "event.h"

class Mpg123UI : public CIO,public COO {
 public:
    Mpg123UI();
    virtual int32 acceptCIOEvent(Event *);
    virtual int32 acceptCOOEvent(Event *);
    virtual void setArgs(int argc, char **argv);
    ~Mpg123UI();
 private:
    bool verboseMode;
    int32 totalFrames;
    float totalTime;
    int32 skipFirst;
    char fileName[512];
    float lastSeconds;
};


#endif // _Mpg123UI_H_
