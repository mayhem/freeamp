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
        
	$Id: esoundpmo.cpp,v 1.3 1999/07/13 18:42:08 robert Exp $
____________________________________________________________________________*/

/* system headers */
#include <stdlib.h>
#include <iostream.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <esd.h>

/* project headers */
#include <config.h>
#include "esoundpmo.h"
#include "lmc.h"
#include "eventdata.h"
#include "facontext.h"
#include "log.h"

#define PIECES 50
#define DB printf("%s:%d\n", __FILE__, __LINE__);

extern    "C"
{
   PhysicalMediaOutput *Initialize(FAContext *context)
   {
      return new EsounDPMO(context);
   }
}

EsounDPMO::EsounDPMO(FAContext *context) :
        PhysicalMediaOutput(context)
{
   m_properlyInitialized = false;

   myInfo = new OutputInfo();
   memset(myInfo, 0, sizeof(OutputInfo));

   m_pBufferThread = NULL;

   m_iOutputBufferSize = 0;
   m_iTotalBytesWritten = 0;
   m_iBytesPerSample = 0;
   m_iLastFrame = -1;
   m_iDataSize = 0;
   audio_fd = -1;

   if (!m_pBufferThread)
   {
      m_pBufferThread = Thread::CreateThread();
      assert(m_pBufferThread);
      m_pBufferThread->Create(EsounDPMO::StartWorkerThread, this);
   }
}

EsounDPMO::~EsounDPMO()
{
   m_bExit = true;
   m_pSleepSem->Signal();   
   m_pPauseSem->Signal();

   if (m_pBufferThread)
   {
      m_pBufferThread->Join();
      delete m_pBufferThread;
   }

   close(audio_fd);

   if (myInfo)
   {
      delete    myInfo;

      myInfo = NULL;
   }
}

VolumeManager *EsounDPMO::GetVolumeManager()
{
   return new ESDVolumeManager(audio_fd);
}

Error EsounDPMO::Init(OutputInfo * info)
{
   m_properlyInitialized = false;

   if (!info)
   {
      info = myInfo;
   }
   else
   {
      // got info, so this is the beginning...

      m_iDataSize = info->max_buffer_size;
   }

   channels = info->number_of_channels;

   // configure the device:
   int       esd_format = ESD_STREAM | ESD_PLAY | ESD_BITS16;

   if (info->number_of_channels == 2)
      esd_format |= ESD_STEREO;
   else if (info->number_of_channels == 1)
      esd_format |= ESD_MONO;
   else
   {
      ReportError("Unsupported number of channels.");
      return (Error) pmoError_DeviceOpenFailed;
   }

   audio_fd = esd_play_stream( esd_format, info->samples_per_second,
                               NULL, "FreeAMP" );
   if (audio_fd < 0)
   {
      ReportError("Unable to connect to EsounD server.");
      return (Error) pmoError_DeviceOpenFailed;
   }

   myInfo->bits_per_sample = info->bits_per_sample;
   myInfo->number_of_channels = info->number_of_channels;
   myInfo->samples_per_second = info->samples_per_second;
   myInfo->max_buffer_size = info->max_buffer_size;
   m_properlyInitialized = true;

   m_iOutputBufferSize = ESD_BUF_SIZE; 
   m_iBytesPerSample = info->number_of_channels * (info->bits_per_sample / 8);

   return kError_NoErr;
}

Error EsounDPMO::Reset(bool user_stop)
{
   return kError_NoErr;
}

void EsounDPMO::HandleTimeInfoEvent(PMOTimeInfoEvent *pEvent)
{
   MediaTimeInfoEvent *pmtpi;
   int32               hours, minutes, seconds;
   int                 iTotalTime = 0;

   if (pEvent->GetFrameNumber() != m_iLastFrame + 1)
   {
       m_iTotalBytesWritten = 1152 * pEvent->GetFrameNumber() * 
                              m_iBytesPerSample; 
   }
   m_iLastFrame = pEvent->GetFrameNumber();

   if (myInfo->samples_per_second <= 0 || pEvent->GetFrameNumber() < 3)
      return;

    // This should take into account what is in the esd buffers, but the
    // esd buffers are virtually nothing, so it's all basically been played
   iTotalTime = m_iTotalBytesWritten / 
      (m_iBytesPerSample * myInfo->samples_per_second);

   hours = iTotalTime / 3600;
   minutes = (iTotalTime / 60) % 60;
   seconds = iTotalTime % 60;

   if (hours < 0 || hours > 23 ||
       minutes < 0 || minutes > 59 || 
       seconds < 0 || seconds > 59)
      return;

   pmtpi = new MediaTimeInfoEvent(hours, minutes, seconds, 0, 
                                  iTotalTime, 0);
   m_pTarget->AcceptEvent(pmtpi);
}

void EsounDPMO::StartWorkerThread(void *pVoidBuffer)
{
   ((EsounDPMO*)pVoidBuffer)->WorkerThread();
}

void EsounDPMO::WorkerThread(void)
{
   void       *pBuffer;
   Error       eErr;
   size_t      iRet;
   Event      *pEvent;
   bool           bPerfWarn = false;

   // Don't do anything until resume is called
   m_pPauseSem->Wait();

   // Wait a specified prebuffer time...
   PreBuffer();

   // The following should be abstracted out into the general thread
   // classes:
#ifdef __linux__
   struct sched_param sParam;

   sParam.sched_priority = sched_get_priority_max(SCHED_OTHER);
   pthread_setschedparam(pthread_self(), SCHED_OTHER, &sParam);
#endif

   for(; !m_bExit;)
   {
      if (m_bPause)
      {
          m_pPauseSem->Wait();
          continue;
      }

      // Loop until we get an Init event from the LMC
      if (!m_properlyInitialized)
      {
          pEvent = ((EventBuffer *)m_pInputBuffer)->GetEvent();

          if (pEvent == NULL)
          {
              m_pLmc->Wake();
              WasteTime();

              continue;
          }

          if (pEvent->Type() == PMO_Init)
          {
              if (IsError(Init(((PMOInitEvent *)pEvent)->GetInfo())))
              {
                  delete pEvent;
                  break;
              }
          }
          delete pEvent;

          continue;
      }

      for(;;)
      {
          eErr = ((EventBuffer *)m_pInputBuffer)->BeginRead(pBuffer, 
                                                            m_iDataSize);
          if (eErr == kError_EndOfStream || eErr == kError_Interrupt)
             break;
      
          if (eErr == kError_NoDataAvail)
          {
             m_pLmc->Wake();

             if (!bPerfWarn)
             {
                 time_t t;

                 time(&t);
                 m_pContext->log->Log(LogPerf, "Output buffer underflow: %s", 
                           ctime(&t));
                 bPerfWarn = true;
             }

             WasteTime();
             continue;
         }
         
         // Is there an event pending that we need to take care of
         // before we play this block of samples? 
         if (eErr == kError_EventPending)
         {
             pEvent = ((EventBuffer *)m_pInputBuffer)->GetEvent();

             if (pEvent->Type() == PMO_Init)
                 Init(((PMOInitEvent *)pEvent)->GetInfo());

             if (pEvent->Type() == PMO_Info) 
                HandleTimeInfoEvent((PMOTimeInfoEvent *)pEvent);

             if (pEvent->Type() == PMO_Quit) 
             {
                 delete pEvent;
                 m_pTarget->AcceptEvent(new Event(INFO_DoneOutputting));
              
                 return;
             }
  
             delete pEvent;

             continue;
         }

         if (IsError(eErr))
         {
             ReportError("Internal error occured.");
             m_pContext->log->Error("Cannot read from buffer in PMO "
                                  "worker tread: %d\n", eErr);
             break;
         }
         bPerfWarn = false;
         break;
      }
  
      if (m_bExit || m_bPause)
      {
          m_pInputBuffer->EndRead(0);
          continue;
      }

      iRet = write(audio_fd, pBuffer, m_iDataSize);
      if (iRet < 0) 
      {
          m_pInputBuffer->EndRead(0);
          ReportError("Could not write sound data to EsounD.");
          m_pContext->log->Error("Failed to write to EsounD: %s\n",
                                strerror(errno));
          break; 
      }

      m_iTotalBytesWritten += iRet;
      m_pInputBuffer->EndRead(iRet);
      m_pLmc->Wake();
   }
}
  
