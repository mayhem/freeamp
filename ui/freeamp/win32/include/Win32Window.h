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

   $Id: Win32Window.h,v 1.1.2.4 1999/09/27 17:47:34 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_WIN32WINDOW__H_
#define INCLUDED_WIN32WINDOW__H_

#include <string>
#include <vector>
#include <map>
#include <deque>
#include <windows.h>

#include "Window.h"

using namespace std;

class Win32Window : public Window
{
    public:

              Win32Window(Theme *pTheme, string &oName);
     virtual ~Win32Window(void);

     virtual Error Run(Pos &oWindowPos);
     virtual Error Close(void);
     virtual Error Show(void);
     virtual Error Hide(void);
     virtual Error Enable(void);
     virtual Error Disable(void);
     virtual Error SetTitle(string &oTitle);
     virtual Error CaptureMouse(bool bCapture);
     virtual Error HideMouse(bool bHide);
     virtual Error SetMousePos(Pos &oPos);
     virtual Error GetMousePos(Pos &oPos);
     virtual Error SetWindowPosition(Rect &oWindowRect);
     virtual Error GetWindowPosition(Rect &oWindowRect);
     virtual Error Minimize(void);
     virtual Error Restore(void);

	 virtual HWND  GetWindowHandle(void);
             void  SaveWindowPos(Pos &oPos);

    protected:

     HWND     m_hWnd;
     Pos      m_oWindowPos;
};

#endif
