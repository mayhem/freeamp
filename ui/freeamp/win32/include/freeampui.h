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
	
	$Id: freeampui.h,v 1.10 1999/01/24 01:37:17 jdw Exp $
____________________________________________________________________________*/

#ifndef _FREEAMP_UI_H_
#define _FREEAMP_UI_H_

/* system headers */
#include <stdlib.h>

/* project headers */
#include "config.h"
#include "ui.h"
#include "semaphore.h"
#include "event.h"
#include "thread.h"
#include "mutex.h"
#include "queue.h"
#include "playlist.h"
#include "errors.h"
#include "properties.h"

enum { STATE_Stopped = 1, STATE_Playing, STATE_Paused };

class FreeAmpUI : public UserInterface {
 public:
    FreeAmpUI();
    ~FreeAmpUI();

    virtual Error Init(int32 startup_type) { return kError_NoErr; }
    virtual void SetTarget(EventQueue*);
    virtual int32 AcceptEvent(Event *);
    virtual void SetArgs(int32,char **);
	virtual void SetPlayListManager(PlayListManager *);

    virtual Error SetPropManager(Properties *p) { m_propManager = p; if (p) return kError_NoErr; else return kError_UnknownErr; }


    void CreateUI();

    static BOOL CALLBACK MainProc(	HWND hwnd, 
						            UINT msg, 
						            WPARAM wParam, 
						            LPARAM lParam );
    
    void SetHwnd(HWND hwnd);

    Semaphore*      m_uiSemaphore;

    bool            m_scrolling;

    EventQueue*     m_target;
	int32			m_state;
	PlayListManager *m_plm;
    float			m_secondsPerFrame;

 protected:
      static void UIThreadFunc(void *);


 private:
	 Properties *   m_propManager;
    int32			m_totalSeconds;
    
    Thread*         m_uiThread;

    HWND            m_hwnd;

    
};


#endif // _SIMPLE_UI_H_
