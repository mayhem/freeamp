
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
	
	$Id: fawindow.h,v 1.1 1998/11/19 03:27:20 jdw Exp $
____________________________________________________________________________*/


#ifndef _FAWindow_H_
#define _FAWindow_H_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/xpm.h>

#include <X11/extensions/shape.h>

#include "config.h"
#include "event.h"

class FAWindow {
 protected:
    Display *m_display;
    int32 m_screenNum;
    GC m_gc;
    Window m_parent;
    Window m_me;
    int32 m_xParent,m_yParent;
    int32 m_width,m_height;
    Pixmap m_pixmap;
    FAWindow();
    EventQueue *m_playerEQ;
 public:
    virtual ~FAWindow();
    Window GetParent();
    Window GetWindow();
    GC GetGC();
    void SetTarget(EventQueue *);
    void SetGC(GC);
    void SetPixmap(Pixmap);
    void SetMask(Pixmap);
    void MapWindow();
    void SelectInput(int32);
    virtual void DoEvent(XEvent) = 0;
};

class FAMainWindow : public FAWindow {
 private:
    int32 m_buttonClickSpotX,m_buttonClickSpotY;
    void Draw();
 public:
    FAMainWindow(Display *, int32,GC, Window,int32,int32,int32,int32);
    virtual ~FAMainWindow();
    virtual void DoEvent(XEvent);
};

class FATriStateWindow : public FAWindow {
 private:
    int32 m_state;
    bool m_activated;
    bool m_pressed;
    bool m_insideButton;
    int32 m_partialHeight;
    void Draw();
 public:
    FATriStateWindow(Display *,int32,GC,Window,int32,int32,int32,int32);
    virtual ~FATriStateWindow();
    void SetPartialHeight(int32);
    void SetActivated();
    void ClearActivated();
    virtual void DoEvent(XEvent);
};
#endif // _WindowHash_H_


















