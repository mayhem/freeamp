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
	
	$Id: pthreadthread.h,v 1.1.2.1 2000/03/16 07:37:39 tdilliga Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_PTHREAD_THREAD_H
#define INCLUDED_PTHREAD_THREAD_H

#include <pthread.h>
#include "thread.h"

#include "mutex.h"


class pthreadThread : public Thread{

public:
	pthreadThread();
	~pthreadThread();


	virtual bool Create(thread_function function, void* arg);
	virtual void Destroy();
	virtual void Suspend();
	virtual void Resume();
	virtual void Join();
	virtual uint32 GetPriority() const;
	virtual uint32 SetPriority(uint32 priority);

	static void *internalThreadFunction(void *);
	void *InternalThreadFunction();

private:
	pthread_t   m_threadHandle;
	unsigned	m_threadId;
	bool        m_suspended;
	Mutex *     m_suspendMutex;
	thread_function m_function;
	void *m_arg;
};

#endif /* _PTHREAD_THREAD_H */




