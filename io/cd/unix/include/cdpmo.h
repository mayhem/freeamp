/*____________________________________________________________________________
        
        FreeAmp - The Free MP3 Player
        Portions copyright (C) 1999-2000 EMusic.com

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
        
        $Id: cdpmo.h,v 1.3 2000/02/19 06:04:56 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_CDPMO_H_
#define INCLUDED_CDPMO_H_

/* system headers */
#include <stdlib.h>

/* project headers */
#include <config.h>
#include "thread.h"
#include "mutex.h"
#include "pmo.h"
#include "pmoevent.h"
#include "eventbuffer.h"

static const uint32 OBUFFERSIZE = 2 * 1152;

enum
{
   pmoError_MinimumError = 4000,
   pmoError_DeviceOpenFailed,
   pmoError_MaximumError
};

class FAContext;

class CDPMO:public PhysicalMediaOutput
{
 public:

            CDPMO(FAContext *context);
   virtual ~CDPMO();

   virtual Error Init(OutputInfo * info);
   static  void  StartWorkerThread(void *);
   virtual int32 GetVolume(void);
   virtual void  SetVolume(int32);
   virtual void  Pause(void);
   virtual void  Resume(void);
   virtual Error ChangePosition(int32);
   virtual Error SetTo(const char *url); 

   uint32  GetNumTracks();
   uint32  GetCDDBDiscID();
   char   *GetcdindexDiscID();

 private:
   void          WorkerThread(void); 
   virtual Error Reset(bool user_stop);
   void          HandleTimeInfoEvent(PMOTimeInfoEvent *pEvent);

   bool          m_properlyInitialized;
   Thread       *m_pBufferThread;

   int           m_cdDesc;
   int           m_track;
   bool          sentData;
   bool          trackDone;
};

#endif /* _SOUNDCARDPMO_H_ */
