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

   $Id: SocketLink.cpp,v 1.1.2.1 2000/07/08 14:20:57 robert Exp $
____________________________________________________________________________*/ 

#include <errno.h> 
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>
#include <string>

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

bool SocketLink::Disconnect(void)
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
   unsigned            uRet;
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
          sleep(1);
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
