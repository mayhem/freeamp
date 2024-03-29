/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 EMusic.com

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
	
	$Id: mutex.cpp,v 1.3 1999/10/19 07:12:57 elrod Exp $
____________________________________________________________________________*/

#include "mutex.h"


Mutex::
Mutex(bool createOwned)
{
	m_mutex = CreateMutex(	NULL,
							createOwned,
							NULL);
}	

Mutex::
~Mutex()
{
	CloseHandle(m_mutex);
}


bool 
Mutex::
Acquire(unsigned long timeout)
{
	bool result = false;

	switch(WaitForSingleObject(m_mutex, timeout))
	{
		case WAIT_ABANDONED:
		case WAIT_OBJECT_0:
		{
			result = true;
			break;
		}

		case WAIT_TIMEOUT:
		case WAIT_FAILED:
		{

			result = false;
			break;
		}
	}

	return result;
}

void 
Mutex::
Release()
{
	 ReleaseMutex(m_mutex);
}
