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
	
	$Id: consoleCOO.h,v 1.2.12.1 1999/09/09 02:42:08 elrod Exp $
____________________________________________________________________________*/

// CommandLineCOO.h


#ifndef INCLUDED_CONSOLE_COO_H_
#define INCLUDED_CONSOLE_COO_H_

#include "ui.h"
#include "event.h"

class ConsoleCOO : public COO {
 public:
    ConsoleCOO();
    virtual int32 acceptCOOEvent(Event *);
    virtual void setArgs(int, char **);
    ~ConsoleCOO();
 private:

};


#endif // _CONSOLE_COO_H_
