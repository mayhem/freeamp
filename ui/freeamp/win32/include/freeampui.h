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
	
	$Id: freeampui.h,v 1.24 1999/03/18 03:44:36 elrod Exp $
____________________________________________________________________________*/

#ifndef _FREEAMP_UI_H_
#define _FREEAMP_UI_H_

/* system headers */
#define STRICT
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
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
#include "control.h"
#include "controlinfo.h"
#include "view.h"
#include "dib.h"
#include "linkedlist.h"

#include "bitmapview.h"
#include "buttonview.h"
#include "dialview.h"
#include "statusview.h"
#include "textview.h"
#include "timeview.h"
#include "volumeview.h"
#include "listview.h"
#include "scrollview.h"

enum {	STATE_Stopped = 0, 
		STATE_Playing, 
		STATE_Paused };


class FreeAmpUI : public UserInterface {
 public:
    FreeAmpUI();
    ~FreeAmpUI();

    virtual Error Init(int32 startup_type) { return kError_NoErr;}
    virtual void SetTarget(EventQueue* eq){m_target = eq;}
    virtual int32 AcceptEvent(Event*);
    virtual void SetArgs(int32,char**);
	virtual void SetPlayListManager(PlayListManager*);
    virtual Error SetPropManager(Properties *p) 
    { m_propManager = p; if (p) return kError_NoErr; else return kError_UnknownErr; }

    void SetWindowHandle(HWND hwnd){m_hwnd = hwnd;}
    HCURSOR SetCursor(HCURSOR cursor)
    {HCURSOR result = m_cursor; m_cursor = cursor; return result;}

    HCURSOR Cursor(void) const { return m_cursor;}
    HPALETTE Palette(void) const { return m_palette; }

    PlayListManager* GetPlayListManager() const { return m_plm; }

    /* handle window messages */
    void Create();
    void Destroy();
    int32 Paint();
    int32 HitTest(int32 xPos, int32 yPos);
    bool MouseMove(int32 xPos, int32 yPos, int32 modifiers);
    bool LeftButtonDown(int32 xPos, int32 yPos, int32 modifiers);
    bool LeftButtonUp(int32 xPos, int32 yPos, int32 modifiers);
    bool LeftButtonDoubleClick(int32 xPos, int32 yPos, int32 modifiers);
    void Command(int32 command, View* source);
    void Notify(int32 command, LPNMHDR notifyMsgHdr);
    void KeyDown(int32 keyCode);
    void DropFiles(HDROP dropHandle);
    void CancelMode();
    void Timer(int32 timerID);

    bool MouseCaptured() const { return m_mouseCaptured; }
    void SetMouseCapture(bool capture) { m_mouseCaptured = capture; }

    EventQueue* Target() const { return m_target; }
    int32 State() const { return m_state; }

 protected:
    static void ui_thread_function(void*);
    void UIThreadFunction();

    void LoadBitmaps();
    void DeleteBitmaps();
    void InitializeRegions();
    void DeleteRegions();

    void CreateControls();

    void CreatePalette();

    void CreateTooltips();

    void UpdatePlayList();

    bool OpenSong(List<char*>* fileList);

    void AddFileListToPlayList(List<char*>* fileList);

 public:
    
	
 private:
	int32				m_totalFrames;
    int32               m_currentFrame;
    int32               m_seekFrame;
    float			    m_secondsPerFrame;

    int32               m_seekAcceleration;
    int32               m_volumeAcceleration;

    TimeDisplay         m_lastTimeDisplay;

    Semaphore*          m_uiSemaphore;
    int32			    m_state;
    EventQueue*         m_target;

    bool                m_mouseCaptured;


    PlayListManager*    m_plm;
    Properties*         m_propManager;
    Thread*             m_uiThread;
    HWND                m_hwnd;
    HPALETTE            m_palette;
    HCURSOR             m_cursor;

    LinkedList<View*>*  m_viewList;

    HRGN                m_windowRegion;
    HRGN                m_playerRegion;
    HRGN                m_playListRegion;
    HRGN                m_playlistBodyRegion;

    HRGN                m_controlRegions[kNumControls];

    BITMAPINFO          m_bufferBitmapInfo;
    void*               m_bufferBits;

    DIB*                m_playerCanvas;
    DIB*                m_bodyBitmap;
    DIB*                m_playlistBodyBitmap;
    DIB*                m_playBitmap;
    DIB*                m_stopBitmap;
    DIB*                m_pauseBitmap;
    DIB*                m_nextBitmap;
    DIB*                m_lastBitmap;
    DIB*                m_modeBitmap;
    DIB*                m_minimizeBitmap;
    DIB*                m_closeBitmap;
    DIB*                m_repeatBitmap;
    DIB*                m_shuffleBitmap;
    DIB*                m_openBitmap;
    DIB*                m_dialBitmap;
    DIB*                m_shuffleIconBitmap;
    DIB*                m_repeatIconBitmap;
    DIB*                m_repeatAllIconBitmap;

    DIB*                m_smallFontBitmap;
    DIB*                m_largeFontBitmap;
    DIB*                m_timeBackgroundBitmap;

    DIB*                m_panelBackingBitmap;
    DIB*                m_panelBackingMaskBitmap;

    DIB*                m_drawerBitmap;
    DIB*                m_drawerMaskBitmap;

    DIB*                m_scrollbarBitmap;

    DIB*                m_addBitmap;
    DIB*                m_deleteBitmap;
    DIB*                m_saveBitmap;
    DIB*                m_loadBitmap;


	int32			    m_width;
	int32			    m_height;

    View*               m_captureView;
    View*               m_mouseView;

    BitmapView*         m_backgroundView;
    BitmapView*         m_playlistBackView;

    ButtonView*         m_playView;
    ButtonView*         m_stopView;
    ButtonView*         m_pauseView;
    ButtonView*         m_nextView;
    ButtonView*         m_lastView;

    ButtonView*         m_modeView;
    ButtonView*         m_minimizeView;
    ButtonView*         m_closeView;
    ButtonView*         m_repeatView;
    ButtonView*         m_shuffleView;
    ButtonView*         m_openView;

    DialView*           m_volumeView;
    DialView*           m_seekView;

    StatusView*         m_shuffleIconView;
    StatusView*         m_repeatIconView;
    StatusView*         m_repeatAllIconView;

    TextView*           m_songTitleView;

    TimeView*           m_timeView;
    VolumeView*         m_volumeInfoView;

    BitmapView*         m_drawerView;
    BitmapView*         m_panelBackingView;

    ListView*           m_playlistView;

    ScrollView*         m_scrollbarView;

    ButtonView*         m_addView;
    ButtonView*         m_deleteView;
    ButtonView*         m_loadView;
    ButtonView*         m_saveView;


};


#endif /* _FREEAMP_UI_H_ */
