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
	
	$Id: ctrlobj.h,v 1.4 1998/10/16 19:35:35 elrod Exp $
____________________________________________________________________________*/

#ifndef _CTRLOBJ_H_
#define _CTRLOBJ_H_

#include "event.h"


class CommandInterface {
 public:
    virtual int32 AcceptEvent(Event *) = 0;
    virtual void SetTarget(EventQueue* queue);
    virtual ~CommandInterface() {}
};

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CIO{
    void*   ref;

    void    (*SetTarget)        (struct CIO*, EventQueue*);
    int32   (*AcceptEvent)      (struct CIO*, Event *);
    void    (*Cleanup)          (struct CIO*);

}CIO, *CIORef;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _CTRLOBJ_H_
