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
	
	$Id: xinglib.cpp,v 1.1 1998/10/14 02:50:37 elrod Exp $
____________________________________________________________________________*/

/* project headers */
#include "lmclib.h"
#include "xinglmc.h"

void Initialize(LMCRef* ref, LMCFunctionTable* table)
{
    if(ref && table)
    {
        LMC* lmc = new XingLMC;
        *ref = lmc;

        table->SetPMI = SetPMI;
        table->SetPMO = SetPMO;
        table->SetInfoEventQueue = SetInfoEventQueue;
        table->Decode = Decode;
        table->Stop = Stop;
        table->Pause = Pause;
        table->Resume = Resume;
        table->Reset = Reset;
        table->ChangePosition = ChangePosition;

        lmc->Init();
    }
}

void SetPMI(LMCRef ref, PhysicalMediaInput* input)
{
    LMC* lmc = (LMC*)ref;

    lmc->SetPMI(input);
}

void SetPMO(LMCRef ref, PhysicalMediaOutput* output)
{
    LMC* lmc = (LMC*)ref;

    lmc->SetPMO(output);
}

void SetInfoEventQueue(LMCRef ref, EventQueue* queue)
{
    LMC* lmc = (LMC*)ref;

    lmc->SetInfoEventQueue(queue);
}

bool Decode(LMCRef ref)
{ 
    LMC* lmc = (LMC*)ref;

    return lmc->Decode();
}

void Stop(LMCRef ref)
{
    LMC* lmc = (LMC*)ref;

    lmc->Stop();
}

void Pause(LMCRef ref)
{
    LMC* lmc = (LMC*)ref;

    lmc->Pause();
}

void Resume(LMCRef ref)
{
    LMC* lmc = (LMC*)ref;

    lmc->Resume();
}

void Reset(LMCRef ref)
{
    
    LMC* lmc = (LMC*)ref;

    lmc->Reset();
}

bool ChangePosition(LMCRef ref, int32 pos)
{
    LMC* lmc = (LMC*)ref;

    return lmc->ChangePosition(pos);
}



