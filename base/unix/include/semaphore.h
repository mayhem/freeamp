
/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998-2000 EMusic.com

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
	
	$Id: semaphore.h,v 1.2 2000/05/06 12:05:48 ijr Exp $
____________________________________________________________________________*/



#ifndef INCLUDED_SEMAPHORE_H_
#define INCLUDED_SEMAPHORE_H_

#include <pthread.h>

class Semaphore {
 private:
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

 public:
    Semaphore(int cnt = 1);
    ~Semaphore();
    bool Wait(int ms = -1);
    bool TimedWait(int iMilliSecs);
    void Signal();

};

#endif // _SEMAPHORE_H_
