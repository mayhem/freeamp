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
	
	$Id: beosthread.cpp,v 1.6 2000/07/10 04:19:06 hiro Exp $
____________________________________________________________________________*/


#include "config.h"

#include <signal.h>
#include <iostream.h>

#include "beosthread.h"
#include "mutex.h"
#include <support/Autolock.h>
#define DEBUG 0
#include <support/Debug.h>

void
beosThread::Join()
{
    status_t    thread_return_value;
    PRINT(( "beosThread::Join\n" ));

    BAutolock    autolock( m_lock );
    if ( !autolock.IsLocked() )
    {
        perror( "beosThread::Join:coulnd't lock the thread" );
    }

    if ( wait_for_thread( m_threadHandle, &thread_return_value ) < B_NO_ERROR )
    {
        PRINT(( "Thread::Join failed\n" ));
    }
}

beosThread::
beosThread():
Thread()
{
    m_priority        = B_NORMAL_PRIORITY; // FIXME!!
    m_threadHandle    = (thread_id) NULL;
    m_threadId        = 0;
    m_suspended        = false;
}

beosThread::
~beosThread()
{
    Destroy();
}

int32
beosThread::
internalThreadFunction( void* arg )
{
    beosThread* thread = (beosThread*) arg;
    thread->InternalThreadFunction();
    return B_NO_ERROR; 
}

void *
beosThread::
InternalThreadFunction()
{
    if ( !m_function )
    {
        return 0;
    }
    m_function( m_arg );

    return (void *)0;
}

bool 
beosThread::
Create( thread_function function, void* arg, bool detach )
{
    BAutolock    autolock( m_lock );
    if ( !autolock.IsLocked() )
    {
        perror( "beosThread::Create:couldn't lock the thread" );
    }

    bool    result = true;
    m_function = function;
    m_arg = arg;
    m_threadHandle = spawn_thread(
                        beosThread::internalThreadFunction,
                        BRANDING,
                        beos_priority( m_priority ),
                        this
                        );
    if ( m_threadHandle < B_NO_ERROR ) {
        PRINT(( "Thread creation failed\n" ));
        result = false;
    }

    PRINT(( "Thread successfully created\n" ));

    if ( resume_thread( m_threadHandle ) < B_NO_ERROR ) {
        PRINT(( "couldn't start(resume) thread\n" ));
        result = false;
    }

    PRINT(( "Thread started successfully\n" ));

    return result;
}

void 
beosThread::
Destroy()
{
    kill_thread( m_threadHandle );
}

void 
beosThread::
Suspend()
{
    PRINT(( "beosThread::Suspend\n" ));
    if ( Lock() )
    {
        if ( !m_suspended ) {
            suspend_thread( m_threadHandle );
            m_suspended = true;
        }
        Unlock();
    }
    else
    {
        perror( "beosThread::Suspend:couldn't lock the thread" );
    }
    PRINT(( "beosThread::Suspend done\n" ));
}

void 
beosThread::
Resume()
{
    PRINT(( "beosThread::Resume\n" ));
    if ( Lock() )
    {
        if ( m_suspended )
        {
            resume_thread( m_threadHandle );
            m_suspended = false;
        }
        Unlock();
    }
    else
    {
        perror( "beosThread::Resume:couldn't lock the thread" );
    }
    PRINT(( "beosThread::Resume done\n" ));
}


uint32 
beosThread::
GetPriority( void ) const
{
    return m_priority;
}

uint32 
beosThread::
SetPriority( uint32 priority )
{
    uint32 old;

    m_priority = priority;
    old = (uint32)set_thread_priority( m_threadHandle, (int32)m_priority );

    if ( old < 0 )
    {
        PRINT(( "SetPriority failed\n" ));
    }
    else
    {
        PRINT(( "Priority set to %d\n", m_priority ));
    }

    return old;
}

void
beosThread::
DumpThreadInfo( void ) const
{
    //printf( "Thread ID = %d, %x\n", m_threadHandle, m_threadHandle );
}
