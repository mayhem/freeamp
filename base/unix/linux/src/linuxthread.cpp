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
	
	$Id: linuxthread.cpp,v 1.8 2000/02/16 02:20:47 ijr Exp $
____________________________________________________________________________*/


#include "config.h"

#include <pthread.h>
#include <signal.h>
#include <iostream.h>

#include "linuxthread.h"
#include "mutex.h"

void linuxThread::Join() {
    pthread_join(m_threadHandle,NULL);
}

linuxThread::
linuxThread():
Thread()
{
    m_threadHandle	= (pthread_t) NULL;
    m_threadId		= 0;
    m_suspended         = false;
    m_suspendMutex      = new Mutex();
}

linuxThread::
~linuxThread()
{
    //pthread_cancel(m_threadHandle);
    if (m_suspendMutex) {
	delete m_suspendMutex;
	m_suspendMutex = NULL;
    }
}

void *
linuxThread::
internalThreadFunction(void* arg)
{
    linuxThread* thread = (linuxThread*) arg;
    thread->InternalThreadFunction();
    return NULL;
}

void *
linuxThread::
InternalThreadFunction()
{
    if (!m_function) {
//	cout << "screwwwwwwwwwwwed..." << endl;
	return 0;
    } else {
//	cout << "fine..." << endl;
    }
    m_function(m_arg);

    return 0;
}

bool 
linuxThread::
Create(thread_function function, void* arg)
{
//    cout << "Thread: Create" << endl;
    bool result = true;
    m_function = function;
    m_arg = arg;
    if(pthread_create(&m_threadHandle, NULL,linuxThread::internalThreadFunction, this))
    {
//	cout << "Create failed!!" << endl;
	result = false;
    }
//    cout << "Thread: Create: done" << endl;
    return result;
}

void 
linuxThread::
Destroy()
{
    pthread_cancel(m_threadHandle);
}

void 
linuxThread::
Suspend()
{
    m_suspendMutex->Acquire();
    if (!m_suspended) {
	pthread_kill(m_threadHandle, SIGSTOP);
	m_suspended = true;
    }
    m_suspendMutex->Release();
}

void 
linuxThread::
Resume()
{
    m_suspendMutex->Acquire();
    if (m_suspended) {
	pthread_kill(m_threadHandle, SIGCONT);
	m_suspended = false;
    }
    m_suspendMutex->Release();
}


uint32 
linuxThread::
GetPriority() const
{
    return( 0);
}

uint32 
linuxThread::
SetPriority(uint32 priority)
{
    return( 0);
}

