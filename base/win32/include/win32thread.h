
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
	
	$Id: win32thread.h,v 1.2 1998/11/03 00:05:21 jdw Exp $
____________________________________________________________________________*/


#ifndef _WIN32_THREAD_H
#define _WIN32_THREAD_H

#include <windows.h>
#include "config.h"
#include "thread.h"



class win32Thread : public Thread {

public:
	win32Thread();
	~win32Thread();


	virtual bool Create(thread_function function, void* arg);
	virtual void Destroy();
	virtual void Suspend();
	virtual void Resume();
	virtual void Join();

	virtual Priority GetPriority() const;
	virtual Priority SetPriority(Priority priority);

    static unsigned long __stdcall internalThreadFunction(void* arg);

    uint32 InternalThreadFunction(); 

private:
	Priority	    m_priority;
	HANDLE		    m_threadHandle;	
	unsigned long	    m_threadId;

    thread_function m_function;
    void*           m_arg;


};

#endif /* _WIN32_THREAD_H */
