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
        
        $Id: httpinput.h,v 1.22.2.1 2000/10/24 09:46:11 robert Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_HTTPINPUT_H_
#define INCLUDED_HTTPINPUT_H_

/* system headers */
#include <stdlib.h>
#ifdef WIN32
 #include <windows.h>
#endif

/* project headers */
#include "config.h"
#include "pmi.h"
#include "thread.h"
#include "semaphore.h"
#include "pullbuffer.h"  
#include "tstream.h"  

const int iMaxUrlLen = 1024;
const int iMaxErrorLen = 1024;   

enum
{
   httpError_MinimumError = 2000,
   httpError_BadUrl,
   httpError_GetHostByNameFailed,
   httpError_CannotOpenSocket,
   httpError_CannotConnect,
   httpError_SocketRead,
   httpError_SocketWrite,
   httpError_CustomError,
   httpError_MaximumError
};

class FAContext;

class HttpInput:public PhysicalMediaInput
{
   public:

   HttpInput(FAContext *context);
   HttpInput(char *path);
   virtual ~ HttpInput(void);

   virtual Error Prepare(PullBuffer *&pBuffer);  
   virtual Error Run(void);  

   virtual bool  CanHandle(const char *szUrl, char *szTitle);
   virtual bool  IsStreaming(void)
                 { return m_bIsStreaming; };
   virtual bool  UseBufferReduction(void)
                 { return m_bUseBufferReduction; };
				 
   virtual bool  PauseLoop(bool bLoop);  
   virtual Error Close(void);
   virtual const char *Url(void) const
   {
      return m_path;
   }

   void            WorkerThread(void); 

   virtual vector<string> *GetProtocols(void);

protected:

   virtual Error      Open(void);
   static  void       StartWorkerThread(void *);
   void               LogError(char *);
   TitleStreamServer *m_pTitleStream;
   int                WriteData(char *, int, char **);
   int                ReopenFile(char *);
   int                OpenPlaylist(char *);
#ifdef WIN32
   Error              Win32GetHostByName(char *szHostName, struct hostent *pHostInfo);
#endif
   Error              GetHostByName(char *szHostName, struct hostent *pResult);

private:

   int             m_hHandle, m_iMetaDataInterval;
   Thread         *m_pBufferThread;
   bool            m_bLoop, m_bDiscarded;
   FILE           *m_fpSave;
   FILE           *m_fpPlaylist;
   char           *m_szError;
   bool            m_bUseProxy, m_bIsStreaming;
   char            m_szProxyHost[iMaxUrlLen];
   bool            m_bUseBufferReduction;
   int             m_uBytesReceived;
   int             m_Mode;
   bool            m_bSave;
   bool            m_bSplit;
   int             m_bSongOnlyOnce;
   char           *m_CurrentFile;
   unsigned char   m_HeadBuf[4];
#define MODE_HUNT	1
#define MODE_FRAME	2
   int             m_Len;
#ifdef WIN32
   HWND            m_hWnd;
#endif
};

#endif /* _HTTPFILEINPUT_H_ */
