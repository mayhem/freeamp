/*____________________________________________________________________________
        
        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 1998-1999 EMusic.com

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
        
        $Id: pmo.cpp,v 1.14 1999/12/29 01:11:54 ijr Exp $
____________________________________________________________________________*/

/* system headers */
#include <stdlib.h>
#include <iostream.h>
#include <fcntl.h>
//#include <sys/soundcard.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/* project headers */
#include <config.h>
#include "pipeline.h"
#include "pullbuffer.h"
#include "preferences.h"
#include "eventbuffer.h"
#include "eventdata.h"
#include "facontext.h"
#include "log.h"
#include "debug.h"

#define DB printf("%s:%d\n", __FILE__, __LINE__);  

PhysicalMediaOutput::PhysicalMediaOutput(FAContext *context) :
                     PipelineUnit(context)
{
    m_pPmi = NULL;
    m_pLmc = NULL;
	m_iBufferUpdate = -1;
    m_pPmiBuffer = NULL;

    if (context->prefs->GetPrefInt32(kPreBufferPref, &m_iPreBuffer) == 
        kError_NoPrefValue)
         m_iPreBuffer = 0;
}

PhysicalMediaOutput::~PhysicalMediaOutput()
{
    m_bExit = true;

    if (m_pLmc)
        m_pLmc->Pause();
    if (m_pPmi)
        m_pPmi->Pause();

    m_pPauseSem->Signal();
    m_pSleepSem->Signal();

    delete m_pLmc;
    delete m_pPmi;
}

Error PhysicalMediaOutput::SetTo(const char *url)
{
    Error       eRet;

    m_pMutex->Acquire();

    assert(m_pPmi != NULL);
    assert(m_pLmc != NULL);

    m_pPmi->SetTo(url);
    eRet = m_pPmi->Prepare(m_pPmiBuffer);
    if (!IsError(eRet))
    {
         eRet = m_pLmc->Prepare(m_pPmiBuffer, m_pInputBuffer);
    }     

    m_pMutex->Release();

    return eRet;
}

void PhysicalMediaOutput::SetLMC(LogicalMediaConverter *pLMC)
{
    m_pMutex->Acquire();

    m_pLmc = pLMC;

    m_pMutex->Release();
}

void PhysicalMediaOutput::SetPMI(PhysicalMediaInput *pPMI)
{
    m_pMutex->Acquire();

    m_pPmi = pPMI;

    m_pMutex->Release();
}

void PhysicalMediaOutput::Pause(void)
{
    PipelineUnit::Pause();
    m_pPmi->PauseLoop(true);
    Reset(true);
}

void PhysicalMediaOutput::Resume(void)
{
    if (m_pPmi->PauseLoop(false))
    {
        m_pLmc->Pause();
        m_pPmi->Pause();
        m_pLmc->Clear();
        m_pPmi->Resume();
        m_pLmc->Resume();
    }

    PipelineUnit::Resume();
}

void PhysicalMediaOutput::PreBuffer(void)
{
    usleep(m_iPreBuffer * 1000);
}

bool PhysicalMediaOutput::WasteTime()
{
    usleep(1000);

    return m_bExit || m_bPause;
}       

Error PhysicalMediaOutput::ChangePosition(int32 position)
{
   Error     error = kError_NoErr;

   if (m_pPmi->IsStreaming())
      return kError_FileSeekNotSupported;

   m_pMutex->Acquire();

   Pause();
   m_pLmc->Pause();
   m_pPmi->Pause();

   Clear();
   m_pLmc->Clear();
   m_pPmi->Clear();

   m_pLmc->ChangePosition(position);

   m_pPmi->Resume();
   m_pLmc->Resume();
   Resume();

   m_pMutex->Release();

   return error;
}  

void PhysicalMediaOutput::UpdateBufferStatus(void)
{
   time_t iNow;

   if (m_pPmi->IsStreaming())
   {
      time(&iNow);
      if (iNow != m_iBufferUpdate)
      {
          m_pTarget->AcceptEvent(new StreamBufferEvent(false, 
                            m_pPmiBuffer->GetBufferPercentage(), 
                            m_pInputBuffer->GetBufferPercentage()));
          m_iBufferUpdate = iNow;
      }
   }   
}
