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
   
   $Id: streambuffer.h,v 1.2 1999/02/13 01:35:40 robert Exp $
____________________________________________________________________________*/

#ifndef _STREAMBUFFER_H_
#define _STREAMBUFFER_H_

/* system headers */
#include <stdlib.h>

#include "pullbuffer.h"

const int iReceiveTimeout = 1;

class StreamBuffer : public PullBuffer
{
    public:

               StreamBuffer(size_t iBufferSize, 
                            size_t iOverflowSize,
                            size_t iWriteTriggerSize);
      virtual ~StreamBuffer(void);

      virtual  Error    BeginRead  (void *&pBuffer, size_t &iBytesNeeded);
      virtual  Error    BeginWrite (void *&pBuffer, size_t &iBytesNeeded);

      virtual  bool     IsBufferingUp(int iBytesNeeded);
		virtual  void     Pause()
		                  { m_bPause = true; };     
		virtual  void     Resume()
		                  { m_bPause = false; };     

    protected:

	   bool      m_bBufferingUp, m_bPause;
		Mutex    *m_pStreamMutex;
};

#endif
