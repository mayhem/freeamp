/*_________________________________________________________________________
        
        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 2000 Relatable

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id: comsocket.cpp,v 1.6 2000/10/02 08:03:44 ijr Exp $
____________________________________________________________________________*/
/***************************************************************************
                          comsocket.cpp  -  description
                             -------------------
    begin                : Thu Mar 23 2000
    copyright            : (C) 2000 by Relatable, LLC
    programed by         : Sean Ward
    email                : sward@relatable.com
 ***************************************************************************/


#include "config.h"

#include "comsocket.h"
#ifndef WIN32

#include <netinet/tcp.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#ifndef __QNX__
#include <sys/poll.h>
#endif
#include <fcntl.h>
#include <net/if.h>
#include <sys/ioctl.h>
#endif

#ifndef SHUT_RDWR
#define SHUT_RDWR 2
#endif

/* FreeBSD uses IPPROTO_TCP */
#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

#ifdef __QNX__
struct pollfd
{
   int            fd;
   unsigned short events;
   unsigned short revents;
};

#define POLLIN   1
#define POLLOUT  4
#define POLLPRI  2
#define POLLERR  8
#define POLLHUP  16
#define POLLNVAL 32

static int poll(struct pollfd *fds, unsigned int nfds, int timeout)
{
    struct timeval tv;
    fd_set rset, wset, xset;
    struct pollfd *f;
    int ready;
    int maxfd = 0;

    FD_ZERO(&rset);
    FD_ZERO(&wset);
    FD_ZERO(&xset);

    for (f = fds; f < &fds[nfds]; ++f)
        if (f->fd >= 0)
        {
         if (f->events & POLLIN)
            FD_SET(f->fd, &rset);
         if (f->events & POLLOUT)
            FD_SET(f->fd, &wset);
         if (f->events & POLLPRI)
            FD_SET(f->fd, &xset);
         if (f->fd > maxfd && (f->events & (POLLIN|POLLOUT|POLLPRI)))
            maxfd = f->fd;
     }

  tv.tv_sec = timeout / 1000;
  tv.tv_usec = (timeout % 1000) * 1000;

  ready = select(maxfd + 1, &rset, &wset, &xset, timeout == -1 ? NULL : &tv);

  if (ready > 0)
     for (f = fds; f < &fds[nfds]; ++f)
     {
         f->revents = 0;
         if (f->fd >= 0)
         {
             if (FD_ISSET(f->fd, &rset))
                   f->revents |= POLLIN;
               if (FD_ISSET(f->fd, &wset))
                   f->revents |= POLLOUT;
               if (FD_ISSET(f->fd, &xset))
                   f->revents |= POLLPRI;
           }
       }

    return ready;
}
#endif
 
COMSocket::COMSocket(int nSocket, int nSockType)
{
	m_nSocket = nSocket;
	m_bConnected = false;
	if (m_nSocket != INVALID_SOCKET) m_bConnected = true;
	m_nSockType = nSockType;
}

COMSocket::~COMSocket()
{
	if (IsConnected()) Disconnect();
}

/** Connects a socket to pIP, on nPort, of type nType. */
int COMSocket::Connect(const char* pIP, int nPort, int nType, bool
	bBroadcast)
{
	if (this->IsConnected()) this->Disconnect();
	
	sockaddr_in addr;
		
	hostent* pServer;
	int nErr = 0;
	m_nSockType = nType;
	m_nSocket = socket(AF_INET, nType, 0);
	if (m_nSocket < 0) return m_nSocket;
		
	pServer = gethostbyname(pIP);
	if (pServer == NULL)
	{
		close(m_nSocket);
		m_nSocket = -1;
		return -1;
	}
	memset((char*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy((char*)&(addr.sin_addr.s_addr), (char*)(pServer->h_addr), pServer->h_length);
	addr.sin_port = htons(nPort);

	int nflag = 1;
	if (nType == SOCK_STREAM)
	{
		nErr = setsockopt(m_nSocket, SOL_TCP, TCP_NODELAY, &nflag, sizeof(int));
		if (nErr == -1) cout << "failed TCP_NODELAY " << endl;
	}
	if (bBroadcast)
	{
		nErr = setsockopt(m_nSocket, SOL_SOCKET, SO_BROADCAST,
			&nflag, sizeof(int));
		if (nErr == -1) cout << "failed SO_BROADCAST " << endl;
	}
	
	nErr = connect(m_nSocket, (sockaddr*)&addr, sizeof(sockaddr_in));
	if (nErr != 0)
	{
		
		close(m_nSocket);
		m_nSocket = -1;
		return -1;
	}
		
	m_bConnected = true;
	return 0;
}

/** Disconnects the current socket */
int COMSocket::Disconnect()
{
	int nErr = 0;
	if (!IsConnected()) return -1;
	if (m_nSockType == SOCK_STREAM)
	{
		nErr = shutdown(m_nSocket, SHUT_RDWR);
	}
	
	nErr = close(m_nSocket);
	m_nSocket = -1;
	m_bConnected = false;
	return (nErr != -1);
}

/** Checks if there is a current open connection */
bool COMSocket::IsConnected()
{
	return m_bConnected;
}

/** Reads from a socket, into pbuffer, up to a max of nLen byte, and writes how many were actually written to nBytesWritten. */
int COMSocket::Read(char* pBuffer, int nLen, int* nBytesWritten)
{
	if (!IsConnected()) return -1;	// no connection
	int nErr = 0;
	nErr = recv(m_nSocket, (void*)pBuffer, nLen, 0);
	if ((nErr != -1) && (nBytesWritten != NULL))
	{
		*nBytesWritten = nErr;
	}
	else
	{
		cout << "error with read " << endl;
	}
	return ((nErr != -1) - 1);
}

/** Writes to a socket, from buffer pBuffer, up to nLen bytes, and returns the number of written bytes in pnBytesWritten. */
int COMSocket::Write(const char* pBuffer, int nLen, int* pnBytesWritten)
{
	if (!IsConnected()) return -1; // no connection
	int nErr = 0;
	bool bRepeat = true;
	while (bRepeat)
	{
		nErr = send(m_nSocket, (void*)pBuffer, nLen, 0);
		bRepeat = false;
		if ((nErr == -1) && (errno == EINTR))
		{
			cout << "EINTR" << endl;
			bRepeat = true;
		}
	}
	if ((nErr != -1) && (pnBytesWritten != NULL))
	{
		*pnBytesWritten = nErr;
	}
	else
	{
		cout << "error with write" << endl;
	}
	return ((nErr != -1) - 1);
}
/** Sets TCPNODELAY to nFlag */
int COMSocket::SetNoDelay(int nFlag)
{
	if (!IsConnected()) return -1;
	int nErr = 0;
	if (m_nSockType == SOCK_STREAM)
	{
		nErr = setsockopt(m_nSocket, SOL_TCP, TCP_NODELAY, &nFlag, sizeof(int));
		if (nErr == -1) cout << "failed TCP_NODELAY " << endl;
	}
  return nErr;
}

/** Reads in a non blocking fashion (ie, selects and polls) for nTimeout seconds */
int COMSocket::NBRead(char* pBuffer, int nLen, int* nBytesWritten, int nTimeout)
{
	struct pollfd pfd;
	pfd.fd = m_nSocket;
	pfd.events = POLLIN;
	
	int retval;
	
	retval = poll(&pfd, 1, nTimeout*1000);
	if (retval > 0)
	{
		return this->Read(pBuffer, nLen, nBytesWritten);
	}
	else
	{
		return -1;
	}
}

/** Polls the socket for nMsec milliseconds, and returns if data is available */
bool COMSocket::Poll(int nMSec, bool bType)
{
	struct pollfd pfd;
	pfd.fd = m_nSocket;
	if (bType) pfd.events = POLLIN;
	else
	{
		pfd.events = POLLOUT;
	}
	int retval = 0;
	retval = poll(&pfd, 1, nMSec);
	if (retval > 0) return true;
	else
	return false;
}

int COMSocket::SetNonBlocking(bool bType)
{
	int nRes = 0;
	int flags = 0;
	flags = fcntl(m_nSocket, F_GETFL, 0);
	if (bType)
	{
		nRes = fcntl(m_nSocket, F_SETFL, flags | O_NONBLOCK);
	}
	else
	{
		flags &= ~O_NONBLOCK;
		nRes = fcntl(m_nSocket, F_SETFL, flags);
	}
	return nRes;
}

int COMSocket::NBConnect(const char* pIP, int nPort, int nType, int nTimeout)
{
	if (this->IsConnected()) this->Disconnect();
	
	sockaddr_in addr;
	hostent* pServer;
	int nErr = 0;
	m_nSockType = nType;
	m_nSocket = socket(AF_INET, nType, 0);
	if (m_nSocket < 0) return m_nSocket;
		
	pServer = gethostbyname(pIP);
	if (pServer == NULL)
	{
		close(m_nSocket);
		m_nSocket = -1;
		return -1;
	}
	memset((char*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy((char*)&(addr.sin_addr.s_addr), (char*)(pServer->h_addr), pServer->h_length);
	addr.sin_port = htons(nPort);

	int nflag = 1;
	if (nType == SOCK_STREAM)
	{
		nErr = setsockopt(m_nSocket, SOL_TCP, TCP_NODELAY, &nflag, sizeof(int));
		if (nErr == -1) cout << "failed TCP_NODELAY " << endl;
	}
	nErr = this->SetNonBlocking(true);
	cout << "Set Nonblocking " << nErr << endl;

	nErr = connect(m_nSocket, (sockaddr*)&addr, sizeof(sockaddr_in));
	
	if (nErr == 0)
	{ // connected immediately
		m_bConnected = true;
		this->SetNonBlocking(false);
		return 1;
	}
	else
	{
		if (errno != EINPROGRESS)
		{
			close(m_nSocket);
			m_nSocket = -1;
			return -1;
		}
		fd_set rset, wset;
		FD_ZERO(&rset);
		FD_SET(m_nSocket, &rset);
		wset = rset;
		struct timeval tval;
		tval.tv_sec = nTimeout;
		tval.tv_usec = 0;
		
		if (( nErr = select(m_nSocket + 1, &rset, &wset, NULL,
			nTimeout ? &tval : NULL) ) == 0) 
		{
			errno = ETIMEDOUT;
			close(m_nSocket);
			m_nSocket = -1;
			cout << "error after select " << endl;
			return -1;
		}
		if (FD_ISSET(m_nSocket, &rset) || FD_ISSET(m_nSocket,
&wset))
		{
			int error = 0;
                        fa_socklen_t len = sizeof(error);

		if (getsockopt(m_nSocket, SOL_SOCKET, SO_ERROR, &error,
&len) < 0)
		{	
		errno = ETIMEDOUT;
			close(m_nSocket);
			m_nSocket = -1;
			cout << "error after FD_ISSET " << endl;
			return -1;
		}
		}
	}
		
	m_bConnected = true;
	this->SetNonBlocking(false);
	cout << "successful connect " << endl;
	return 1;
}

/** Sets multicast packets to only go through the NIC labeled pNIC */
int COMSocket::SetMCastInterface(const char* pNIC)
{
#ifndef __linux__
#warning WARNING COMSocket::SetMCastInterface is NOT IMPLEMENTED
    return -1;
#else
	struct ip_mreqn mReq;
	memset(&mReq, 0, sizeof(ip_mreq));
	int nErr = -1;
	if (m_nSockType == SOCK_DGRAM)
	{
		mReq.imr_ifindex = if_nametoindex(pNIC);
		nErr = setsockopt(m_nSocket, SOL_IP, IP_MULTICAST_IF,
				&mReq, sizeof(ip_mreqn));
		if (nErr == -1) cout << "failed IP_MULTICAST_IF " << endl;
	}
	return ((nErr != -1) - 1);
#endif
}
