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

   $Id: MainWindow.h,v 1.5 2000/02/09 16:58:15 hiro Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_BEOSMAINWINDOW_H
#define INCLUDED_BEOSMAINWINDOW_H

#include <be/interface/Window.h>

class Semaphore;
class BeOSWindow;
class BMessageRunner;

class MainWindow : public BWindow
{
public:
                        MainWindow( BRect frame, const char* name,
                                    BeOSWindow* parent );
    virtual             ~MainWindow();
    virtual bool        QuitRequested( void );
    virtual void        MessageReceived( BMessage* message );
    virtual void        WaitForQuit( BRect* windowRectOnExit );

protected:

private:
    BeOSWindow*         m_parent;
    Semaphore*          m_quitSem;
    BRect               m_frame;
    BMessageRunner*	m_timer;
};

#endif // INCLUDED_BEOSMAINWINDOW_H
