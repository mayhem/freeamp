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
   
   $Id: pullbuffer.h,v 1.12.2.1 1999/04/20 20:57:08 mhw Exp $
____________________________________________________________________________*/

#ifndef _PULLBUFFER_H_
#define _PULLBUFFER_H_

/* system headers */
#include <stdlib.h>

#include "errors.h"
#include "mutex.h"
#include "semaphore.h"

class FAContext;

// Notes:
//   If the number of requested bytes are not in the buffer at the
//   beginning of a BeginRead call, the call will block. To get out
//   of this block, set EOS to true, and signal the reader semaphore.
class PullBuffer
{
    public:

               PullBuffer(size_t iBufferSize, 
                          size_t iOverflowSize,
                          size_t iWriteTriggerSize,
			  FAContext *context);
      virtual ~PullBuffer(void);

      virtual  Error    BeginWrite (void *&pBuffer, size_t &iBytesToWrite);
      virtual  Error    EndWrite   (size_t iNumBytesWritten);

      virtual  Error    BeginRead  (void *&pBuffer, size_t &iBytesNeeded,
                                    bool bBlock = true);
      virtual  Error    EndRead    (size_t iBytesUsed);

      virtual  Error    DiscardBytes();
      virtual  void     BreakBlocks();

      Error    Clear        (void);
      Error    Resize       (size_t iNewSize,
                             size_t iNewOverflowSize,
                             size_t iWriteTriggerSize);

      bool     IsEndOfStream(void);
      void     SetEndOfStream(bool bEOS);
      size_t   GetNumBytesInBuffer(void)
               {
                   return m_iBytesInBuffer;
               };
      size_t   GetBufferSize(void)
               {
                   return m_iBufferSize;
               };
      int32    GetBufferPercentage(void)
		         {
					    return (100 * m_iBytesInBuffer) / m_iBufferSize;
					};
      void     WrapPointer(void *&pBuffer);

    protected:

      int32      GetWriteIndex();
      int32      GetReadIndex();

      FAContext *m_context;
      Semaphore *m_pWriteSem, *m_pReadSem;
      Mutex     *m_pMutex;
      bool       m_bExit;

    private:

      int32          m_iReadIndex, m_iWriteIndex;
      bool           m_bEOS, m_bReadOpPending, m_bWriteOpPending;
      unsigned char *m_pPullBuffer;
      size_t         m_iBytesInBuffer, m_iOverflowSize, m_iBufferSize;
      size_t         m_iWriteTriggerSize, m_iOrigBufferSize;
};

#endif
