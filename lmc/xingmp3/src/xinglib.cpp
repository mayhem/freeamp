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
	
	$Id: xinglib.cpp,v 1.8 1998/10/19 07:51:44 elrod Exp $
____________________________________________________________________________*/

/* project headers */
#include <iostream.h>

#include "lmclib.h"
#include "xinglmc.h"

void Initialize(LMCRef ref )
{
    if(ref)
    {
        LogicalMediaConverter* lmc = new XingLMC;
        ref->ref = lmc;
        
        ref->InitDecoder = InitDecoder;
        ref->SetPMI = SetPMI;
        ref->SetPMO = SetPMO;
        ref->SetTarget = SetTarget;
        ref->Decode = Decode;
        ref->Stop = Stop;
        ref->Pause = Pause;
        ref->Resume = Resume;
        ref->Reset = Reset;
        ref->ChangePosition = ChangePosition;
        ref->Cleanup = Cleanup;
    }
}

void InitDecoder(LMCRef ref)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->InitDecoder();
}

void SetPMI(LMCRef ref, PMIRef input)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->SetPMI(input);
}

void SetPMO(LMCRef ref, PMORef output)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->SetPMO(output);
}

void SetTarget(LMCRef ref, EventQueueRef queue)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->SetTarget(queue);
}

bool Decode(LMCRef ref)
{ 
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    return lmc->Decode();
}

void Stop(LMCRef ref)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->Stop();
}

void Pause(LMCRef ref)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->Pause();
}

void Resume(LMCRef ref)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->Resume();
}

void Reset(LMCRef ref)
{
    
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    lmc->Reset();
}

bool ChangePosition(LMCRef ref, int32 pos)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    return lmc->ChangePosition(pos);
}

void Cleanup(LMCRef ref)
{
    LogicalMediaConverter* lmc = (LogicalMediaConverter*)ref->ref;

    delete lmc;
}




