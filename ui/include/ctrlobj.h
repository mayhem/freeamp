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
	
	$Id: ctrlobj.h,v 1.9 1998/10/19 07:51:44 elrod Exp $
____________________________________________________________________________*/

#ifndef _CTRLOBJ_H_
#define _CTRLOBJ_H_

#include "event.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct UI{
    void*   ref;

    void        (*SetTarget)    (struct UI*, EventQueueRef);
    void        (*SetArgs)      (struct UI*,int32 /*argc*/,char ** /*argv*/);
    int32       (*AcceptEvent)  (struct UI*,Event *);
    void        (*Cleanup)      (struct UI*);

}UI, *UIRef;

#ifdef __cplusplus
} // extern "C"
#endif

class UserInterface {
 public:
    virtual int32 AcceptEvent(Event *) = 0;
    virtual void  SetArgs(int32,char **) = 0;
    virtual void SetTarget(EventQueueRef) = 0;
    virtual void SetRef(UIRef) = 0;
    virtual ~UserInterface() {}
};

#endif // _CTRLOBJ_H_

