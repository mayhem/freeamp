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
        
        $Id: localfileinput.cpp,v 1.18 1999/06/28 23:09:27 robert Exp $
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
#include "localfileinput.h"
#include "pullbuffer.h"
#include "facontext.h"
#include "log.h"

const int32 iBufferSize = 65536;
const int32 iOverflowSize = 8192;
const int32 iTriggerSize = 8192;

#define DB printf("%s:%d\n", __FILE__, __LINE__);

extern    "C"
{
   PhysicalMediaInput *Initialize(FAContext *context)
   {
      return new LocalFileInput(context);
   }
}

LocalFileInput::LocalFileInput(FAContext *context):
                PhysicalMediaInput(context)
{
    printf("Local ctor\n");
    m_fpFile = NULL;
    m_bLoop = false;
    m_pBufferThread = NULL;
    m_pID3Tag = NULL;
}

LocalFileInput::~LocalFileInput()
{
    printf("Local dtor\n");

    m_bExit = true;
    m_bPause = false;
    m_pSleepSem->Signal();
    m_pPauseSem->Signal();

    if (m_path)
    {
       delete m_path;
       m_path = NULL;
    }

    if (m_pBufferThread)
    {
       m_pBufferThread->Join();
       delete m_pBufferThread;
    }

    if (m_fpFile)
       fclose(m_fpFile); 

    if (m_pID3Tag)
       delete m_pID3Tag;

    if (m_pOutputBuffer)
    {
       delete m_pOutputBuffer;
       m_pOutputBuffer = NULL;
    }
}

Error LocalFileInput::Prepare(PullBuffer *&pBuffer, bool bStartThread)
{
    int   iBufferSize;
    Error result;
 
    printf("local prepare\n");
 
    if (m_pOutputBuffer)
    {
       delete m_pOutputBuffer;
       m_pOutputBuffer = NULL;
    }

DB
    m_pOutputBuffer = new PullBuffer(iBufferSize, iOverflowSize, 
                                     iTriggerSize, m_pContext);
    assert(m_pOutputBuffer);

DB
    result = Open();
    if (!IsError(result))
    {
        if (bStartThread)
        {
DB
            result = Run();
            if (IsError(result))
            {
                ReportError("Could not run the input plugin.");
                return result;
            }
        }
    }
    else
    {
       ReportError("Could not open the specified file.");
       return result;
    }
DB

    if (!IsError(m_pContext->prefs->GetInputBufferSize(&iBufferSize)))
    {
        iBufferSize *= 1024;
        m_pOutputBuffer->Resize(iBufferSize, iOverflowSize, iTriggerSize);
    }

DB
    pBuffer = m_pOutputBuffer;

    return kError_NoErr;
}

bool LocalFileInput::CanHandle(char *szUrl, char *szTitle)
{
    bool bRet;
 
    bRet = strncmp(szUrl, "file://", 7) == 0;
    if (szTitle && bRet)
       *szTitle = 0;
 
    return bRet;
}

Error LocalFileInput::SetTo(char *url)
{
    Error  result = kError_NoErr;
    int32  len = strlen(url) + 1;
    
    DB
    if (m_path)
    {
       delete m_path;
       m_path = NULL;
    }
 
    m_path = new char[len];
    if (m_path)
    {
        if (strncmp(url, "file://", 7) == 0)
           memcpy(m_path, url + 7, len);
        else
           memcpy(m_path, url, len);
    }
    else
    {
        result = kError_OutOfMemory;
    }

   return result;
}

Error LocalFileInput::GetID3v1Tag(unsigned char *pTag)
{
    Error eRet = kError_NoErr;

    DB
 
    if (m_pOutputBuffer == NULL)
    {
        eRet = Open();
        if (!IsError(eRet))
        {
            memcpy(pTag, m_pID3Tag, iID3TagSize);
        }
       
        Close();
 
        return eRet;
    }
    else
       memcpy(pTag, m_pID3Tag, iID3TagSize);

    return kError_NoErr;
}

Error LocalFileInput::Close(void)
{
    if (m_fpFile)
      fclose(m_fpFile);
 
    m_pOutputBuffer->Clear();

    return kError_NoErr;
}

Error LocalFileInput::GetLength(size_t &iSize)
{
    iSize = m_iFileSize;
    return kError_NoErr;
}; 

Error LocalFileInput::Seek(int32 &iRet, int32 iPos, int32 iFrom) 
{ 
    Error eRet = kError_NoErr;

    iRet = fseek(m_fpFile, iPos, iFrom);
    if (iRet < 0)
       eRet = kError_SeekFailed;
    else
       iRet = ftell(m_fpFile);

    m_pOutputBuffer->Clear();

    return eRet;
}

void LocalFileInput::Clear(void) 
{ 
    fseek(m_fpFile, SEEK_SET, 0); 
    m_pOutputBuffer->Clear();
    PipelineUnit::Clear();
}

Error LocalFileInput::Open(void)
{
    if (strcmp(m_path, "-") == 0)
    {
       m_fpFile = stdin;
    }
    else
       m_fpFile = fopen(m_path, "rb");

    if (m_fpFile == NULL)
    {
        switch (errno)
        {
            case EACCES:
               m_pContext->log->Error("Access to the file was denied.\n");
               return kError_FileNoAccess;
               break;

            case EINVAL:
               m_pContext->log->Error("Internal error: The file could not be opened.\n");
               return kError_FileInvalidArg;
               break;

            case EMFILE:
               m_pContext->log->Error("Internal error: The file could not be opened.\n");
               return kError_FileNoHandles;
               break;

            case ENOENT:
               m_pContext->log->Error("File not found.\n");
               return kError_FileNotFound;
               break;

            default:
               return kError_UnknownErr;
               break;
        }
    }

    fseek(m_fpFile, 0, SEEK_END);
    m_iFileSize = ftell(m_fpFile);

    fseek(m_fpFile, -iID3TagSize, SEEK_CUR);

    if (m_pID3Tag == NULL)
        m_pID3Tag = new unsigned char[iID3TagSize];

    int iRet = fread(m_pID3Tag, sizeof(char), iID3TagSize, m_fpFile);
    if (iRet == iID3TagSize)
    {
        if (strncmp((char *)m_pID3Tag, "TAG", 3))
        {
            delete m_pID3Tag;
            m_pID3Tag = NULL;
        }
        else
            m_iFileSize -= iID3TagSize;
    }
    else
    {
        delete m_pID3Tag;
        m_pID3Tag = NULL;
    }

    fseek(m_fpFile, 0, SEEK_SET);

    return kError_NoErr;
}

Error LocalFileInput::Run(void)
{
    if (!m_pBufferThread)
    {
       m_pBufferThread = Thread::CreateThread();
       if (!m_pBufferThread)
       {
           m_pContext->log->Error("Could not create filebuffer thread.");
           return (Error)kError_CreateThreadFailed;
       }
       m_pBufferThread->Create(LocalFileInput::StartWorkerThread, this);
    }

    return kError_NoErr;
}

void LocalFileInput::StartWorkerThread(void *pVoidBuffer)
{
   ((LocalFileInput*)pVoidBuffer)->WorkerThread();
}

void LocalFileInput::WorkerThread(void)
{
   size_t  iToCopy, iRead; 
   void   *pBuffer;
   Error   eError;

   m_pSleepSem->Wait();

   for(; !m_bExit;)
   {
      if (m_pOutputBuffer->IsEndOfStream())
      {
          m_pSleepSem->Wait();
          continue;
      }
      if (m_bPause)
      {
          m_pPauseSem->Wait();
          continue;
      }
          
      eError = m_pOutputBuffer->BeginWrite(pBuffer, iToCopy);
      if (eError == kError_NoErr)
      {
          iRead = fread((unsigned char *)pBuffer, 1, iToCopy, m_fpFile);
          eError = m_pOutputBuffer->EndWrite(iRead);
          if (IsError(eError))
          {
              m_pContext->log->Error("local: EndWrite returned: %d\n", eError);
              break;
          }

          if (iRead < iToCopy)
             m_pOutputBuffer->SetEndOfStream(true);
      }
      if (eError == kError_BufferTooSmall)
      {
          m_pSleepSem->Wait();
      }
   }
   m_pContext->log->Log(LogInput, "PMI: filebuffer thread exit\n");
}

