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
	
	$Id: downloadui.h,v 1.1.2.4 1999/09/27 09:40:52 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_DOWNLOAD_UI_H_
#define INCLUDED_DOWNLOAD_UI_H_

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
#include "facontext.h"
#include "preferences.h"
#include "downloadmanager.h"


class DownloadUI : public UserInterface {
 public:
    DownloadUI(FAContext *context);
    ~DownloadUI();

    virtual Error Init(int32 startup_type);
    virtual int32 AcceptEvent(Event*);
    void CreateUI();

    static BOOL CALLBACK MainProc(	HWND hwnd, 
						            UINT msg, 
						            WPARAM wParam, 
						            LPARAM lParam );

    void SetWindowHandle(HWND hwnd){m_hwnd = hwnd;}

    BOOL InitDialog();
    BOOL Command(int32 command, HWND src);
    BOOL DrawItem(int32 controlId, DRAWITEMSTRUCT* dis);
    BOOL MeasureItem(HWND hwnd, MEASUREITEMSTRUCT* mis);

   
 protected:

    void ParseArgs(int32 argc, char** argv);

    static void UIThreadFunc(void *);

    uint32 CalcStringEllipsis(HDC hdc, string& displayString, int32 columnWidth);

    FAContext*		m_context;

 private:
    Semaphore*          m_uiSemaphore;
    PlaylistManager*    m_plm;
    Preferences*        m_prefs;
    Properties*         m_propManager;
    Thread*             m_uiThread;
    EventQueue*         m_target;
    DownloadManager*    m_dlm;

    HWND    m_hwnd;
    HWND    m_hwndList;
    HWND    m_hwndInfo;
    HWND    m_hwndPause;
    HWND    m_hwndCancel;
    HWND    m_hwndResume;
    HWND    m_hwndClose;

    HIMAGELIST  m_noteImage;
    HBITMAP  m_progressBitmap;
};


#endif // INCLUDED_DOWNLOAD_UI_H_
