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

   $Id: GTKWindow.h,v 1.9 2000/03/19 06:44:45 ijr Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_GTKWINDOW__H_
#define INCLUDED_GTKWINDOW__H_

#include <gtk/gtk.h>
#include "facontext.h"
#include "Window.h"
#include "thread.h"

class GTKWindow : public Window
{
    public:

              GTKWindow(Theme *pTheme, string &oName);
     virtual ~GTKWindow(void);

     virtual Error VulcanMindMeld(Window *pOther);
     virtual void  SaveWindowPos(Pos &oPos);
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
     virtual bool  LButtonDown(void);    
     virtual Error GetDesktopSize(int32 &iX, int32 &iY);
     virtual void  BringWindowToFront(void);

     GtkWidget *GetWindow(void) { return mainWindow; }

     void SetMouseIn(void);
     void SetMouseOut(void);   
     void MouseLeaveCheck(void); 
     void ModifyTimer(bool stop);

     void DropFiles(char *filename);

     Mutex *m_pMindMeldMutex;
 
   protected:
     Pos m_oWindowPos;
      
   private:
     void GTKEventService(void);

     GtkWidget *mainWindow;
     int gtkTimer;
     bool quitLoop;
     bool initialized;
     bool m_bMouseInWindow;
};

#endif
