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
        
        $Id: obsinput.cpp,v 1.14 1999/04/21 04:20:50 elrod Exp $
____________________________________________________________________________*/

/* system headers */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <iostream.h>
#include <errno.h>
#include <assert.h>

#include <config.h>

#if HAVE_UNISTD_H
#include <unistd.h>
#elif HAVE_IO_H
#include <io.h>
#else
#error Must have unistd.h or io.h!
#endif // HAVE_UNISTD_H

/* project headers */
#include "obsinput.h"

const int iBufferSize = 8192;
const int iOverflowSize = 1536;
const int iTriggerSize = 1024;
const char *szDefaultStreamTitle = "RTP Stream";

extern    "C"
{
   PhysicalMediaInput *Initialize(FAContext *context)
   {
      return new ObsInput(context);
   }
}

ObsInput::ObsInput(FAContext *context): 
          PhysicalMediaInput()
{
    m_context = context;
    m_path = NULL;
    m_pPullBuffer = NULL;
}

ObsInput::ObsInput(char *path):
          PhysicalMediaInput()
{
   if (path)
   {
      assert(0);
   }
   else
   {
      m_path = NULL;
      m_pPullBuffer = NULL;
   }
}

ObsInput::~ObsInput()
{
   if (m_path)
   {
      delete[]m_path;
      m_path = NULL;
   }
   if (m_pPullBuffer >= 0)
   {
      delete m_pPullBuffer;
      m_pPullBuffer = NULL;
   }
}

bool ObsInput::CanHandle(char *szUrl, char *szTitle)
{
   bool bRet;

   bRet = strncmp(szUrl, "rtp://", 6) == 0;
   if (szTitle && bRet)
      strcpy(szTitle, szDefaultStreamTitle);


   return bRet;
}

Error ObsInput::SetTo(char *url, bool bStartThread)
{
   Error     result = kError_NoErr;

   if (m_pPullBuffer)
   {
      delete m_pPullBuffer;
      m_pPullBuffer = NULL;
   }

   if (m_path)
   {
      delete[]m_path;
      m_path = NULL;
   }

   if (url)
   {
      int32     len = strlen(url) + 1;
      m_path = new char[len];

      if (m_path)
      {
         memcpy(m_path, url, len);
      }
      else
      {
         result = kError_OutOfMemory;
      }

      if (IsntError(result))
      {
         m_pPullBuffer = new ObsBuffer(iBufferSize, iOverflowSize, 
                                       iTriggerSize, url, this, m_context);
         assert(m_pPullBuffer);

         result = m_pPullBuffer->Open();
         if (!IsError(result) && bStartThread)
            result = m_pPullBuffer->Run();
      }
   }
   else
   {
      result = kError_InvalidParam;
   }

   return result;
}

Error ObsInput::
SetBufferSize(size_t iNewSize)
{
    assert(m_pPullBuffer);
    return m_pPullBuffer->Resize(iNewSize, iNewSize / 6, iNewSize / 8);
}

Error ObsInput::
GetLength(size_t &iSize)
{
    iSize = 0;

    return kError_FileSeekNotSupported;
}

Error ObsInput::
GetID3v1Tag(unsigned char *pTag)
{
    assert(m_pPullBuffer);
    return m_pPullBuffer->GetID3v1Tag(pTag);
}

Error ObsInput::
BeginRead(void *&buf, size_t &bytesneeded)
{
   assert(m_pPullBuffer);
   return m_pPullBuffer->BeginRead(buf, bytesneeded);
}

Error ObsInput::
EndRead(size_t bytesused)
{
   assert(m_pPullBuffer);
   return m_pPullBuffer->EndRead(bytesused);
}

int32 ObsInput::GetBufferPercentage()
{
   if (m_pPullBuffer)
      return m_pPullBuffer->GetBufferPercentage();

   return 0;
}

int32 ObsInput::GetNumBytesInBuffer()
{
   if (m_pPullBuffer)
       return m_pPullBuffer->GetNumBytesInBuffer();

   return 0;
}

void ObsInput::Pause()
{
   if (m_pPullBuffer)
   {
      m_pPullBuffer->DidDiscardBytes();
      m_pPullBuffer->Pause();
   }
}

void ObsInput::Break()
{
   if (m_pPullBuffer)
       m_pPullBuffer->BreakBlocks();
}

bool ObsInput::Resume()
{
   bool bRet;

   if (!m_pPullBuffer)
      return false;

   bRet = m_pPullBuffer->DidDiscardBytes();

   m_pPullBuffer->Resume();

   return bRet;
}

Error     ObsInput::
Seek(int32 & rtn, int32 offset, int32 origin)
{
   return kError_FileSeekNotSupported;
}

Error     ObsInput::
Close(void)
{
   delete m_pPullBuffer;
   m_pPullBuffer = NULL;

   return kError_NoErr;
}
