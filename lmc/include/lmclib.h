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
	
	$Id: lmclib.h,v 1.4 1998/10/15 13:33:51 elrod Exp $
____________________________________________________________________________*/

#ifndef _LMCLIB_H_
#define _LMCLIB_H_

/* project headers */
#include "config.h"
#include "event.h"
#include "pmo.h"
#include "pmi.h"
#include "lmc.h"

extern "C" {

void Initialize(LMCRef ref);

void Init(LMCRef ref);
void SetPMI(LMCRef ref, PMIRef);
void SetPMO(LMCRef ref, PMORef);
void SetInfoEventQueue(LMCRef ref, EventQueue*);

bool Decode(LMCRef ref);
void Stop(LMCRef ref);
void Pause(LMCRef ref);
void Resume(LMCRef ref);
void Reset(LMCRef ref);
bool ChangePosition(LMCRef ref, int32 pos);
void Cleanup(LMCRef ref);

} //extern "C"

#endif /* _LMCLIB_H_ */






