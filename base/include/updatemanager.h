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
	
	$Id: updatemanager.h,v 1.1.2.1 1999/10/04 17:56:23 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_UPDATE_MANAGER_H_
#define INCLUDED_UPDATE_MANAGER_H_

#include <assert.h>
#include <string>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "mutex.h"
#include "semaphore.h"
#include "thread.h"

#define kInvalidIndex 0xFFFFFFFF



class UpdateManager {

 public:
    UpdateManager(FAContext* context);
    virtual ~UpdateManager();

   

 protected:
    

 private:

    FAContext* m_context;

    Mutex m_mutex;

    vector<UpdateItem*> m_itemList;

    Registry m_formatRegistry;
   
    Thread* m_downloadThread;
    volatile bool m_runUpdateThread;

    Mutex m_quitMutex;

};

#endif // INCLUDED_UPDATE_MANAGER_H_










