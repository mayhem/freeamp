/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Portions Copyright (C) 1999 EMusic

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

   $Id: SocketLink.h,v 1.1.2.2 2000/07/08 14:46:40 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_SOCKETLINK_H__
#define INCLUDED_SOCKETLINK_H__

#include "errors.h" 
#include "thread.h" 
#include "semaphore.h" 
#include <string>

using namespace std;

class SocketLink
{
    public:

       SocketLink(unsigned short iPortNum);
       ~SocketLink(void);

       Error Run(void);

       bool  HasConnection(void);
       void  Disconnect(void);
       bool  SendCommand(const string &st);

    private:

       unsigned short m_port;
       int            m_socket, m_newSocket;
       Thread        *m_decoderThread;
       Semaphore     *m_sem;

       Error CreateSocket(void);

    public:

       void  WorkerThread(void);
};

#endif

