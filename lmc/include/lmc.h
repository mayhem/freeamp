
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
	
	$Id: lmc.h,v 1.8 1998/10/27 02:28:44 jdw Exp $
____________________________________________________________________________*/

#ifndef _LMC_H_
#define _LMC_H_


#include "event.h"
#include "pmo.h"
#include "pmi.h"

class LogicalMediaConverter {
 public:
    virtual ~LogicalMediaConverter() {}
    virtual bool Decode() = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Reset() = 0;
    virtual bool ChangePosition(int32) = 0;

    virtual void SetPMI(PhysicalMediaInput *) = 0;
    virtual void SetPMO(PhysicalMediaOutput *) = 0;
    virtual void SetTarget(EventQueue *) = 0;
    virtual void InitDecoder() = 0;
};

#if 0

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LMC{
    void*   ref;

    void    (*InitDecoder)       (struct LMC*);

    void    (*SetPMI)            (struct LMC*, PMIRef);
    void    (*SetPMO)            (struct LMC*, PMORef);
    void    (*SetTarget) (struct LMC*, EventQueueRef);

    bool    (*Decode)            (struct LMC*);
    void    (*Stop)              (struct LMC*);
    void    (*Pause)             (struct LMC*);
    void    (*Resume)            (struct LMC*);
    void    (*Reset)             (struct LMC*);
    bool    (*ChangePosition)    (struct LMC*, int32);
    void    (*Cleanup)           (struct LMC*);

}LMC, *LMCRef;

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#endif // _LMC_H_
