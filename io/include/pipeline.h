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
	
	$Id: pipeline.h,v 1.1 1999/06/28 23:09:21 robert Exp $
____________________________________________________________________________*/

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

/* system headers */
#include <stdlib.h>
#include <assert.h>


#if HAVE_UNISTD_H
#include <unistd.h>
#elif HAVE_IO_H
#include <io.h>
#else 
#error Must have unistd.h or io.h!
#endif // HAVE_UNISTD_H


/* project headers */
#include "semaphore.h"
#include "mutex.h"
#include "config.h"
#include "errors.h"
#include "facontext.h"
#include "event.h"
#include "properties.h"
#include "pullbuffer.h"

class PipelineUnit
{
public:
            PipelineUnit(FAContext *);
    virtual ~PipelineUnit();

    virtual void  Pause(void);
    virtual void  Resume(void);
    virtual void  Wake(void);
    virtual void  Clear(void);

    virtual void  SetPropManager(Properties *);
    virtual void  SetTarget(EventQueue *target);
    virtual void  SetInputBuffer(PullBuffer *pBuffer);

    virtual void  ReportError(const char *szError);
    virtual void  DebugPrint(void);

protected:

    virtual bool  Sleep(void);

    Semaphore             *m_pSleepSem;
    Semaphore             *m_pPauseSem;
    Mutex                 *m_pMutex;

    EventQueue            *m_pTarget;
    PullBuffer            *m_pOutputBuffer; 
    PullBuffer            *m_pInputBuffer;
    Properties            *m_pPropManager;
    bool                   m_bPause, m_bExit;
    FAContext             *m_pContext;

private:
 
    bool                   m_bSleeping;
};

#endif /* _PMO_H_ */
