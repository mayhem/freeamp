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
	
	$Id: pmilib.h,v 1.1 1998/10/14 08:53:19 elrod Exp $
____________________________________________________________________________*/

#ifndef _PMILIB_H_
#define _PMILIB_H_

#include <stdlib.h>

/* project headers */
#include "config.h"
#include "pmi.h"

extern "C" {

typedef struct PMISTRUCT {
    void*       ref;
    int32       (*Read)     (struct PMISTRUCT*, void*, size_t);
    int32       (*Seek)     (struct PMISTRUCT*, int32, int32);
    bool        (*SetTo)    (struct PMISTRUCT*, char*);
    bool        (*Close)    (struct PMISTRUCT*);
    const char* (*Url)      (struct PMISTRUCT*);

}PMISTRUCT, *PMIRef;

void Initialize(PMIRef ref);

int32 Read(PMIRef ref, void* buf, size_t numbytes);
int32 Seek(PMIRef ref, int32 offset, int32 origin);
bool SetTo(PMIRef ref, char* url);
bool Close(PMIRef ref);
const char* Url(PMIRef ref);

}

#endif /* _PMILIB_H_ */






