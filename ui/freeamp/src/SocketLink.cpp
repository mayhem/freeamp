/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic

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

   $Id: SocketLink.cpp,v 1.1.2.2 2000/07/08 14:46:40 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <iostream.h>
#include <errno.h>
#include <assert.h>
#ifdef WIN32
#include <winsock.h>
#include <time.h>
#else
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef __BEOS__
#include <arpa/inet.h> 
#endif
#include <netdb.h>
#include <fcntl.h>
#endif 

#include "config.h"

#if HAVE_UNISTD_H
#include <unistd.h>
#elif HAVE_IO_H
#include <io.h>
#else
#error Must have unistd.h or io.h!
#endif // HAVE_UNISTD_H

#include "SocketLink.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

SocketLink::SocketLink(unsigned short iPortNum)
{
   m_port = iPortNum;
   m_socket = -1;
   m_decoderThread = NULL;
   m_newSocket = -1;
   m_sem = new Semaphore();
}

SocketLink::~SocketLink(void)
{
   if (m_decoderThread)
   {
      m_sem->Signal();
   }
   if (m_socket >= 0)
      close(m_socket);

   delete m_sem;
}

bool SocketLink::HasConnection(void)
{
   return m_newSocket != -1;
}

void SocketLink::Disconnect(void)
{
   m_sem->Signal();
}

void StartWorkerThread(void *pVoidBuffer)
{
   ((SocketLink *)pVoidBuffer)->WorkerThread();
}

Error SocketLink::Run(void)
{
   if (!m_decoderThread)
   {
      m_decoderThread = Thread::CreateThread();
      if (!m_decoderThread)
      {
         return kError_CreateThreadFailed;
      }
      m_decoderThread->Create(StartWorkerThread, this);
   }   

   return kError_NoErr;
}

Error SocketLink::CreateSocket(void)
{ 
    int    iRet;
    struct sockaddr_in sa;
    char   cReUse = true;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family= AF_INET;
    sa.sin_port= htons(m_port);

    m_socket = socket(AF_INET,SOCK_STREAM,0);
    if (m_socket < 0)
	 {
       return kError_CantCreateSocket;
    }

    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &cReUse, sizeof(cReUse));

    iRet = bind(m_socket,(const struct sockaddr *)&sa,sizeof(sa));
    if (iRet < 0)
	 {
       return kError_CannotBind;
    }

    listen(m_socket, 3);

    return kError_NoErr;
}

void SocketLink::WorkerThread(void)
{
   int                 uRet;
   Error               eError;
   struct sockaddr_in  sOther;

   eError = CreateSocket();
   if (eError != kError_NoErr)
      return;

   for(;;)
   {
      uRet = sizeof(sockaddr_in);
      m_newSocket = accept(m_socket, (struct sockaddr *)&sOther, &uRet);
      if (m_newSocket < 0)
      {
          usleep(1000000);
          continue;
      }

      m_sem->Wait();

      shutdown(m_newSocket, 2);
      close(m_newSocket);
      m_newSocket = -1;
   }
}

bool SocketLink::SendCommand(const string &str)
{
   int iRet, iErr;

   if (m_newSocket == -1)
      return false;

#ifndef WIN32
   unsigned len = sizeof(int);
   iRet = getsockopt(m_newSocket, SOL_SOCKET, SO_ERROR, &iErr, &len);
   if (iRet == 0 && iErr != 0)
   {
      m_sem->Signal();
      return false;
   }
#endif

   iRet = send(m_newSocket, str.c_str(), str.length(), 0);
   if (iRet < 0 || iRet < (int)str.length())
   {
      m_sem->Signal();
      return false;
   }

   return true;
}
