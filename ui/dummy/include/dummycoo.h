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
	
	$Id: dummycoo.h,v 1.4 1998/10/16 22:58:29 jdw Exp $
____________________________________________________________________________*/

#ifndef _DUMMY_COO_H_
#define _DUMMY_COO_H_

#include "ctrlobj.h"
#include "player.h"
#include "semaphore.h"

class DummyCOO : public UserInterface {
 public:
    virtual int32 AcceptEvent(Event *);
    virtual void  SetArgs(int32 i, char **c) { return; }
    DummyCOO(Semaphore*);
    virtual ~DummyCOO();

 private:
    Semaphore* m_termSemaphore;

};

#endif // _DUMMY_COO_H_
