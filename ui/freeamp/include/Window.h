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

   $Id: Window.h,v 1.1.2.5 1999/09/09 00:26:56 robert Exp $
____________________________________________________________________________*/ 

#ifndef __WINDOW__H_
#define __WINDOW__H_

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

typedef map<string, Control *> ControlMap;
typedef map<string, Control *>::iterator ControlMapIterator;

class Theme;

class Window
{
    public:

              Window(Theme *pTheme, string &oName);
     virtual ~Window(void);

     void    GetName(string &oName);
     Canvas *GetCanvas(void);
     void    AddControl(Control *pControl);


     // The following functions are designed to give access to the 
     // controls via the control's name. 
     Error   SendControlMessage(Control *pControl, ControlMessageEnum eMsg);

     Error   ControlEnable(string &oControlName, bool bSet, bool &bEnable);
     Error   ControlShow(string &oControlName, bool bSet, bool &bShow);
     Error   ControlIntValue(string &oControlName, bool bSet, 
                            int &iValue);
     Error   ControlStringValue(string &oControlName, bool bSet,
                                string &oValue);

     // These functions should be called from the OS dependent event
     // loop to handle mouse messages
     virtual void  HandleMouseMove(Pos &oPos);
     virtual void  HandleMouseLButtonDown(Pos &oPos);
     virtual void  HandleMouseLButtonUp(Pos &oPos);

     virtual Error StartMouseCapture(Control *);
     virtual Error EndMouseCapture(void);


      // Run handles OS dependent messages and calls the functions below
      // or passes the messages on to child controls
      virtual Error Run(void) = 0;
      virtual Error Create(void) = 0;
      virtual Error Destroy(void) = 0;
      virtual Error Show(void) = 0;
      virtual Error Hide(void) = 0;
      virtual Error Enable(void) = 0;
      virtual Error Disable(void) = 0;
      virtual Error SetTitle(string &oTitle) = 0;
      virtual Error CaptureMouse(bool bCapture) = 0;
      virtual Error HideMouse(bool bHide) = 0;
      virtual Error SetMousePos(Pos &oMousePos) = 0;
      virtual Error GetMousePos(Pos &oMousePos) = 0;

    protected:

      Control *ControlFromPos(Pos &oPos);

     
      string                    m_oName;
      vector<Control *>         m_oControls;
      ControlMap                m_oControlMap;
      Canvas                   *m_pCanvas;
      Mutex                     m_oMutex;
      Semaphore                 m_oSleepSem;
      bool                      m_bExit;
      Theme                    *m_pTheme;
      Control                  *m_pMouseInControl, *m_pCaptureControl;
};

#endif
