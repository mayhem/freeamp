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
   
   $Id: streambuffer.h,v 1.9 1999/10/19 07:13:00 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_STREAMBUFFER_H_
#define INCLUDED_STREAMBUFFER_H_

/* system headers */
#include <stdlib.h>

#include "pullbuffer.h"

const int iReceiveTimeout = 1;

class StreamBuffer : public PullBuffer
{
    public:

               StreamBuffer(size_t iBufferSize, 
                            size_t iOverflowSize,
                            FAContext *context);
      virtual ~StreamBuffer(void);

      virtual  Error    BeginWrite (void *&pBuffer, size_t iBytesNeeded);

      virtual  bool     IsBufferingUp(int32 iBytesNeeded);
		virtual  void     Pause()
		                  { m_bPause = true; };     
		virtual  void     Resume()
		                  { m_bPause = false; };     
      virtual  bool     DidDiscardBytes();

    protected:

	   bool      m_bBufferingUp, m_bPause, m_bDiscardedBytes;
		Mutex    *m_pStreamMutex;
};

#endif
