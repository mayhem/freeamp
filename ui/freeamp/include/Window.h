/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic

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

   $Id: Window.h,v 1.25 2000/05/15 16:38:23 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_WINDOW__H_
#define INCLUDED_WINDOW__H_

#include "config.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <string> 
#include <vector>
#include <map>

using namespace std;

#include "Bitmap.h"
#include "Control.h"
#include "Canvas.h"
#include "thread.h"
#include "semaphore.h"
#include "mutex.h"

typedef multimap<string, Control *> ControlMap;
typedef multimap<string, Control *>::iterator ControlMapIterator;

class Theme;

struct Panel
{
    Panel::Panel() 
    { 
        memset(&m_oOpenRect, 0, sizeof(Rect));
        memset(&m_oClosedRect, 0, sizeof(Rect));
        memset(&m_oOffset, 0, sizeof(Pos));
        m_pOpenBitmap = m_pClosedBitmap = NULL;
        m_bIsOpen = false;
    };
    string  m_oName;
    Rect    m_oOpenRect, m_oClosedRect;
    Pos     m_oOffset;
    Bitmap *m_pOpenBitmap, *m_pClosedBitmap;
    bool    m_bIsOpen;
};

class Window
{
    public:

               Window(Theme *pTheme, string &oName);
      virtual ~Window(void);

      void    GetName(string &oName);
      Canvas *GetCanvas(void);
      void    AddControl(Control *pControl);
      void    ClearControls(void);
      void    Keystroke(unsigned char cKey);
      bool    MenuCommand(uint32 uCommand);
      void    VolumeChanged(void);
      void    EnableTimer(bool bEnable);
 
      // Panel related functions
      void    AddPanel(Panel *pPanel);

      virtual void SetStayOnTop(bool bStay);
      virtual void SetLiveInToolbar(bool bLive);

      // The following functions are designed to give access to the 
      // controls via the control's name. 
      Error   SendControlMessage(Control *pControl, ControlMessageEnum eMsg);

      Error   ControlEnable(const string &oControlName, bool bSet, bool &bEnable);
      Error   ControlShow(const string &oControlName, bool bSet, bool &bShow);
      Error   ControlIntValue(const string &oControlName, bool bSet, 
                             int &iValue);
      Error   ControlStringValue(const string &oControlName, bool bSet,
                                 string &oValue);
      Error   ControlGetTip(const string &oName, string &oTip);
      Error   ControlGetDesc(const string &oName, string &oDesc);
      bool    DoesControlExist(const string &oName);

      // These functions should be called from the OS dependent event
      // loop to handle mouse messages
      virtual void  HandleMouseMove(Pos &oPos);
      virtual void  HandleMouseLButtonDown(Pos &oPos);
      virtual void  HandleMouseLButtonUp(Pos &oPos);
      virtual void  MouseHasEnteredWindow(void);
      virtual void  MouseHasLeftWindow(void);

      virtual Error StartMouseCapture(Control *);
      virtual Error EndMouseCapture(void);
     
      // This init call is made after the window is created
      virtual void  Init(void);
      virtual void  TimerEvent(void);
      
      // VulcanMinkMeld is called when this window should 'become' the
      // other window. 
      virtual Error VulcanMindMeld(Window *pOther);
              void  VulcanMindMeldHost(bool bIsHost);

      // Run handles OS dependent messages and calls the functions below
      // or passes the messages on to child controls
      virtual Error Run(Pos &oWindowPos) = 0;
      virtual Error Close(void) = 0;
      virtual Error Show(void) = 0;
      virtual Error Hide(void) = 0;
      virtual Error Enable(void) = 0;
      virtual Error Disable(void) = 0;
      virtual Error SetTitle(string &oTitle) = 0;
      virtual Error CaptureMouse(bool bCapture) = 0;
      virtual Error HideMouse(bool bHide) = 0;
      virtual Error Minimize(void) = 0;
      virtual Error Restore(void) = 0;
      virtual bool  LButtonDown(void) = 0;
      virtual Error GetDesktopSize(int32 &iX, int32 &iY) = 0;
      virtual void  BringWindowToFront(void) = 0;
      virtual void  PanelStateChanged(void);
      
      // Mouse position is in screen coordinates
      virtual Error SetMousePos(Pos &oMousePos) = 0;
      virtual Error GetMousePos(Pos &oMousePos) = 0;
      virtual Error SetWindowPosition(Rect &oWindowRect) = 0;
      virtual Error GetWindowPosition(Rect &oWindowRect) = 0;

      // Call this function whenever the are pending GUI messages
      // that might cause a deadlock
      virtual void  ProcessWaitingMessages(void) { ; };

      // For deadlock avaoidance
      virtual void  IncUsageRef(void);
      virtual void  DecUsageRef(void);

    protected:

      Control *ControlFromPos(Pos &oPos);
      void     GetReloadWindowPos(Rect &oOldRect, 
                                  int iNewWidth, int iNewHeight, 
                                  Rect &oNewRect);
      void     GetWindowVisibleArea(Rect &oRect);

      // For locking the window in preparatiom for a VMM
      virtual void  LockUsageRef(void);
      virtual void  UnlockUsageRef(void);
     
      string                    m_oName;
      vector<Panel *>           m_oPanels;
      vector<Control *>         m_oControls;
      ControlMap                m_oControlMap;
      Canvas                   *m_pCanvas;
      bool                      m_bExit, m_bWindowMove, m_bLButtonDown;
      Theme                    *m_pTheme;
      Control                  *m_pMouseInControl, *m_pMouseDownControl;
      Control                  *m_pCaptureControl;
      Pos                       m_oMovePos;
      bool                      m_bStayOnTop, m_bLiveInToolbar;
      bool                      m_bIsVulcanMindMeldHost;
      Rect                      m_oMoveStart;
      int32                     m_iDesktopWidth, m_iDesktopHeight;
      bool                      m_bMindMeldInProgress, m_bTimerEnabled;
      Mutex                    *m_pUsageMutex;
      Semaphore                *m_pUsageSem;
      int32                     m_iUsageCount;
};

#endif
