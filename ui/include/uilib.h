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
	
	$Id: uilib.h,v 1.3 1998/10/16 19:35:35 elrod Exp $
____________________________________________________________________________*/

#ifndef _UILIB_H_
#define _UILIB_H_

/* project headers */
#include "config.h"
#include "event.h"
#include "ctrlobj.h"

#ifdef __cplusplus
extern "C" {
#endif

void Initialize(CIORef inputRef, CIORef outputRef);

void SetTarget(CIORef ref, EventQueue* queue);
int32 AcceptEvent(CIORef ref, Event* event);
void Cleanup(CIORef ref);

#ifdef __cplusplus
} //extern "C"
#endif



#endif /* _UILIB_H_ */






