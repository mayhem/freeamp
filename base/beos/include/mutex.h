/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player
	Portions copyright (C) 1998-1999 EMusic.com

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
	
	$Id: mutex.h,v 1.1.12.1 1999/10/17 05:40:08 ijr Exp $
____________________________________________________________________________*/

#ifndef MUTEX_H
#define MUTEX_H

#include <support/Locker.h>

#define WAIT_FOREVER -1

class Mutex
{
public:
					Mutex( bool createOwned = false );
					~Mutex();
	bool			Acquire( long timeout = WAIT_FOREVER );
	void			Release();
	void			DumpMutex(void);

 private:
	thread_id		m_myTid;
	BLocker			m_lock;
};

#endif /* MUTEX_H */
