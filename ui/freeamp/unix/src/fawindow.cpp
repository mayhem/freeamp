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
	
	$Id: fawindow.cpp,v 1.5 1998/11/23 03:05:13 jdw Exp $
____________________________________________________________________________*/


#include <stdlib.h>
#include <memory.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>


#include "fawindow.h"
#include "lcd_display_mask.xbm"
#include "lcd_icons_mask.xbm"


FAWindow::FAWindow() { 
    m_mapped = false;
}

FAWindow::~FAWindow() { }

void FAWindow::SetTarget(EventQueue *eq) { m_playerEQ = eq; }

Window FAWindow::GetParent() { return m_parent; } 

Window FAWindow::GetWindow() { return m_me; }

GC FAWindow::GetGC() { return m_gc; }

void FAWindow::SetGC(GC gc) { m_gc = gc; }

void FAWindow::SetPixmap(Pixmap pm) { m_pixmap = pm; }

void FAWindow::SetMask(Pixmap mask) { XShapeCombineMask(m_display,m_me,ShapeBounding,0,0,mask,ShapeSet); }

void FAWindow::SelectInput(int32 mask) { XSelectInput(m_display,m_me,mask); }

void FAWindow::MapWindow() { 
    XMapWindow(m_display,m_me); 
    m_mapped = true;
}

void FAWindow::UnMapWindow() { 
    XUnmapWindow(m_display,m_me); 
    m_mapped = false;
}

FAMainWindow::FAMainWindow(Display *display, int32 screen_num,GC gc, Window parent,int32 x,int32 y,int32 w, int32 h) {
    m_display = display;
    m_screenNum = screen_num;
    m_gc = gc;
    m_parent = parent;
    m_xParent = x;
    m_yParent = y;
    m_width = w;
    m_height = h;
    m_me = XCreateSimpleWindow(m_display,m_parent,m_xParent,m_yParent,m_width,m_height,0,BlackPixel(m_display,m_screenNum),WhitePixel(m_display,m_screenNum));
    //fprintf(stderr,"created main win\n");
}

FAMainWindow::~FAMainWindow() { }
void FAMainWindow::DoEvent(XEvent e) {
    switch (e.type) {
	case MotionNotify:
	    if (e.xmotion.state & Button1Mask) {
		XMoveWindow(m_display,m_me,e.xmotion.x_root-m_buttonClickSpotX,e.xmotion.y_root-m_buttonClickSpotY);
	    }
	    break;
	case Expose:
	    if (e.xexpose.count != 0)
		return;
	    Draw();
	    break;
	case ButtonPress:
	    m_buttonClickSpotX = e.xbutton.x;
	    m_buttonClickSpotY = e.xbutton.y;
	    break;
	case KeyRelease: {
	    char foo[32];
	    //fprintf(stderr,"key released\n");
	    XLookupString(&(e.xkey),foo,sizeof(foo),NULL,NULL);
	    if (foo[0] == 'q') {
		m_playerEQ->AcceptEvent(new Event(CMD_QuitPlayer));
	    }
	    //fprintf(stderr,"done key release\n");
	    break;
	}
    }
}

void FAMainWindow::Draw() {
    if (m_mapped) {
	XCopyArea(m_display,m_pixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	XFlush(m_display);
    }
}

FADumbWindow::FADumbWindow(Display *display, int32 screen_num,GC gc, Window parent,int32 x,int32 y,int32 w, int32 h) {
    m_display = display;
    m_screenNum = screen_num;
    m_gc = gc;
    m_parent = parent;
    m_xParent = x;
    m_yParent = y;
    m_width = w;
    m_height = h;
    m_me = XCreateSimpleWindow(m_display,m_parent,m_xParent,m_yParent,m_width,m_height,0,BlackPixel(m_display,m_screenNum),WhitePixel(m_display,m_screenNum));
    //fprintf(stderr,"created main win\n");
}
FADumbWindow::~FADumbWindow() { }

void FADumbWindow::DoEvent(XEvent e) {
    //cout << "Got Event" << endl;
    switch (e.type) {
	case Expose:
	    if (e.xexpose.count != 0)
		return;
	    Draw();
	    break;
    }
}

void FADumbWindow::Draw() {
    //cout << "attempting to draw" << endl;
    if (m_mapped) {
	//cout << "drawing..." << endl;
	XCopyArea(m_display,m_pixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	XFlush(m_display);
    }
}

FATriStateWindow::FATriStateWindow(Display *display, int32 screen_num,GC gc, Window parent,int32 x,int32 y,int32 w, int32 h) {
    m_display = display;
    m_screenNum = screen_num;
    m_gc = gc;
    m_parent = parent;
    m_xParent = x;
    m_yParent = y;
    m_width = w;
    m_height = h;
    m_me = XCreateSimpleWindow(m_display,m_parent,m_xParent,m_yParent,m_width,m_height,0,BlackPixel(m_display,m_screenNum),WhitePixel(m_display,m_screenNum));
    m_activated = false;
    m_pressed = false;
    m_insideButton = false;
    //fprintf(stderr,"Created tristate window\n");
}

FATriStateWindow::~FATriStateWindow() { }

void FATriStateWindow::SetPartialHeight(int32 ph) {
    m_partialHeight = ph;
}

void FATriStateWindow::SetActivated() {
    //cerr << "SetActivated" << endl;
    m_activated = true;
    Draw();
//    XEvent x;
//    x.xexpose.count = 0;
//    XSendEvent(m_display,m_me,false,ExposureMask,&x);
//    XFlush(m_display);
}

void FATriStateWindow::ClearActivated() {
    //cerr << "ClearActivated" << endl;
    m_activated = false;
    Draw();
//    XEvent x;
//    x.xexpose.count = 0;
//    XSendEvent(m_display,m_me,false,ExposureMask,&x);
//    XFlush(m_display);
}

void FATriStateWindow::DoEvent(XEvent e) {
    switch (e.type) {
	case Expose:
	    //cerr << "got exposure" << endl;
	    if (e.xexpose.count != 0)
		return;
	    Draw();
	    break;
	case ButtonPress:
	    m_pressed = true;
	    Draw();
	    break;
	case ButtonRelease:
	    //cerr << "button release" << endl;
	    m_pressed = false;
	    if (m_insideButton) {
		m_clickFunction(m_cookie);
	    }
	    //cerr << "about to draw" << endl;
	    Draw();
	    //cerr << "done drawing" << endl;
	    break;
	case EnterNotify:
	    m_insideButton = true;
	    Draw();
	    break;
	case LeaveNotify:
	    m_insideButton = false;
	    Draw();
	    break;

    }
}

void FATriStateWindow::Draw() {
    //cerr << "Drawing..." << endl;
    if (m_mapped) {
	int32 theInt;
	if (m_activated) {
	    theInt = 2;
	} else {
	    if (m_pressed) {
		if (m_insideButton) {
		    theInt = 2;
		} else {
		    theInt = 0;
		}
	    } else {
		if (m_insideButton) {
		    theInt = 1;
		} else {
		    theInt = 0;
		}
	    }
	}
	//fprintf(stderr, "tristate: window: %x  pixmap: %x  src_y: %x\n",m_me,m_pixmap,theInt*m_partialHeight);
	XCopyArea(m_display,m_pixmap,m_me,m_gc,
		  0, //src_x
		  theInt*m_partialHeight, // src_y
		  m_width, // width
		  m_partialHeight, //height
		  0,  //dest_x
		  0); // dest_y
	XFlush(m_display);
    }
}

void FATriStateWindow::SetClickAction(action_function f, void *p) {
    m_cookie = p;
    m_clickFunction = f;
}

#define TIME_CLIP_X 85
#define TIME_CLIP_Y 17
#define TIME_CLIP_WIDTH 70
#define TIME_CLIP_HEIGHT 12

FALcdWindow::FALcdWindow(Display *display, int32 screen_num,GC gc, Window parent,int32 x,int32 y,int32 w, int32 h) {
    m_display = display;
    m_screenNum = screen_num;
    m_parent = parent;
    m_xParent = x;
    m_yParent = y;
    m_width = w;
    m_height = h;
    m_gc = gc;
    m_me = XCreateSimpleWindow(m_display,m_parent,m_xParent,m_yParent,m_width,m_height,0,BlackPixel(m_display,m_screenNum),WhitePixel(m_display,m_screenNum));
    m_doubleBufferPixmap = XCreatePixmap(m_display,m_me,m_width,m_height,DefaultDepth(m_display,m_screenNum));

    XGCValues gcv;
//    gcv.fill_style = FillSolid;
    gcv.foreground = BlackPixel(m_display,m_screenNum);
    gcv.background = WhitePixel(m_display,m_screenNum);
    m_timeGC = XCreateGC(m_display,m_me, GCForeground | GCBackground,&gcv);
    XRectangle r;
    r.x = 0; r.y = 0; r.width = TIME_CLIP_WIDTH; r.height = TIME_CLIP_HEIGHT;
    XSetClipRectangles(m_display,m_timeGC,TIME_CLIP_X,TIME_CLIP_Y,&r,1,Unsorted);

//    m_mainTextMask = XCreateBitmapFromData(m_display,m_me,(char *)lcd_display_mask_bits,lcd_display_mask_width,lcd_display_mask_height);
//    m_iconMask = XCreateBitmapFromData(m_display,m_me,(char *)lcd_icons_mask_bits,lcd_icons_mask_width,lcd_icons_mask_height);

    m_text = new char[19];
    strcpy(m_text,"Welcome to FreeAmp");
    m_displayState = TotalTimeState;
    m_totalHours = m_totalMinutes = m_totalSeconds = m_currHours = m_currMinutes = m_currSeconds = 0;
};

FALcdWindow::~FALcdWindow() { 
    XFreePixmap(m_display,m_doubleBufferPixmap);
    XFreeGC(m_display,m_gc);
}

void FALcdWindow::DoEvent(XEvent e) {
    switch (e.type) {
	case Expose:
	    //cerr << "got exposure" << endl;
	    if (e.xexpose.count != 0)
		return;
	    Draw(FullRedraw);
	    break;
	case ButtonPress:
	    break;
	case ButtonRelease: {
	    if (m_insideDisplay) {
		int32 nextStateArray[] = { 5, 5, 4, 2, 5, 2};
		SetState(nextStateArray[m_displayState]);
	    }
	    break;  }
	case EnterNotify:
	    m_insideDisplay = true;
	    break;
	case LeaveNotify:
	    m_insideDisplay = false;
	    break;
    }
}

void FALcdWindow::SetState(int32 state) {
    if (m_displayState != state) {
	m_displayState = state;
	Draw(FullRedraw);
    }
}

void FALcdWindow::SetMainText(const char *pText) {
    if (m_text) delete m_text;
    int32 l = strlen(pText);
    m_text = new char[l+1];
    memcpy(m_text,pText,l*sizeof(char));
}

void FALcdWindow::SetSmallFontPixmap(Pixmap p) {
    m_smallFontPixmap = p;
}

void FALcdWindow::SetSmallFontWidth(int *i) {
    m_smallFontWidth = i;
}

void FALcdWindow::SetLargeFontPixmap(Pixmap p) {
    m_largeFontPixmap = p;
}

void FALcdWindow::SetLargeFontWidth(int *i) {
    m_largeFontWidth = i;
}

void FALcdWindow::SetCurrentTime(int32 h, int32 m, int32 s) {
    m_currHours = h;
    m_currMinutes = m;
    m_currSeconds = s;
}

void FALcdWindow::SetTotalTime(int32 h, int32 m, int32 s) {
    m_totalHours = h;
    m_totalMinutes = m;
    m_totalSeconds = s;
}

#define UPPER_LEFT_X 4
#define UPPER_LEFT_Y 2

#define DESCRIPTION_TEXT_X 4
#define DESCRIPTION_TEXT_Y 18

#define RIGHT_SIDE_CLIP 142

void FALcdWindow::DrawIntroState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,"Welcome To FreeAmp",SmallFont);
	case TimeOnly:
	    break;
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}
void FALcdWindow::DrawVolumeState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,m_text,SmallFont);
	    BlitText(m_doubleBufferPixmap,m_gc,DESCRIPTION_TEXT_X,DESCRIPTION_TEXT_Y,"volume",SmallFont);
	case TimeOnly:
	    break;
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}
void FALcdWindow::DrawCurrentTimeState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,m_text,SmallFont);
	    BlitText(m_doubleBufferPixmap,m_gc,DESCRIPTION_TEXT_X,DESCRIPTION_TEXT_Y,"current time",SmallFont);
	case TimeOnly:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_timeGC,TIME_CLIP_X,TIME_CLIP_Y,TIME_CLIP_WIDTH,TIME_CLIP_HEIGHT,TIME_CLIP_X,TIME_CLIP_Y);
	    if (m_currHours) {
		char foo[16];
		sprintf(foo,"%d:%.02d:%.02d",m_currHours,m_currMinutes,m_currSeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,75,DESCRIPTION_TEXT_Y - 1,foo,LargeFont);
	    } else {
		char foo[16];
		sprintf(foo,"%.02d:%.02d",m_currMinutes,m_currSeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,85,DESCRIPTION_TEXT_Y - 1, foo, LargeFont);
	    }
	    break;
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}
void FALcdWindow::DrawSeekTimeState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,m_text,SmallFont);
	    BlitText(m_doubleBufferPixmap,m_gc,DESCRIPTION_TEXT_X,DESCRIPTION_TEXT_Y,"seek time",SmallFont);
	case TimeOnly:
	    break;
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}

void FALcdWindow::DrawRemainingTimeState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,m_text,SmallFont);
	    BlitText(m_doubleBufferPixmap,m_gc,DESCRIPTION_TEXT_X,DESCRIPTION_TEXT_Y,"remaining time",SmallFont);
	case TimeOnly: {
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_timeGC,TIME_CLIP_X,TIME_CLIP_Y,TIME_CLIP_WIDTH,TIME_CLIP_HEIGHT,TIME_CLIP_X,TIME_CLIP_Y);
	    int32 totalSeconds = m_totalHours * 3600;
	    totalSeconds += m_totalMinutes * 60;
	    totalSeconds += m_totalSeconds;
	    int32 currSeconds = m_currHours * 3600;
	    currSeconds += m_currMinutes * 60;
	    currSeconds += m_currSeconds;
	    
	    int32 displaySeconds = totalSeconds - currSeconds;
	    int32 displayHours = displaySeconds / 3600;
	    int32 displayMinutes = (displaySeconds - (displayHours * 3600)) / 60;
	    displaySeconds = displaySeconds - (displayHours * 3600) - (displayMinutes * 60);
	    if (displayHours) {
		char foo[16];
		sprintf(foo,"%d:%.02d:%.02d",displayHours,displayMinutes,displaySeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,75,DESCRIPTION_TEXT_Y - 1,foo,LargeFont);
	    } else {
		char foo[16];
		sprintf(foo,"%.02d:%.02d",displayMinutes,displaySeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,85,DESCRIPTION_TEXT_Y - 1, foo, LargeFont);
	    }
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	}
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}
void FALcdWindow::DrawTotalTimeState(int32 type) {
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_gc,0,0,m_width,m_height,0,0);
	    BlitText(m_doubleBufferPixmap,m_gc,UPPER_LEFT_X,UPPER_LEFT_Y,m_text,SmallFont);
	    BlitText(m_doubleBufferPixmap,m_gc,DESCRIPTION_TEXT_X,DESCRIPTION_TEXT_Y,"total time",SmallFont);
	case TimeOnly:
	    XCopyArea(m_display,m_pixmap,m_doubleBufferPixmap,m_timeGC,TIME_CLIP_X,TIME_CLIP_Y,TIME_CLIP_WIDTH,TIME_CLIP_HEIGHT,TIME_CLIP_X,TIME_CLIP_Y);
	    if (m_totalHours) {
		char foo[16];
		sprintf(foo,"%d:%.02d:%.02d",m_totalHours,m_totalMinutes,m_totalSeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,75,DESCRIPTION_TEXT_Y - 1,foo,LargeFont);
	    } else {
		char foo[16];
		sprintf(foo,"%.02d:%.02d",m_totalMinutes,m_totalSeconds);
		BlitText(m_doubleBufferPixmap,m_timeGC,85,DESCRIPTION_TEXT_Y - 1, foo, LargeFont);
	    }
	    break;
    }
    switch (type) {
	case FullRedraw:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
	case TimeOnly:
	    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_timeGC,0,0,m_width,m_height,0,0);
	    XFlush(m_display);
	    break;
    }
}

void FALcdWindow::Draw(int32 t) {
    if (!m_mapped) return;

    switch (m_displayState) {
	case IntroState:
	    DrawIntroState(t);
	    break;
	case VolumeState:
	    DrawVolumeState(t);
	    break;
	case CurrentTimeState:
	    DrawCurrentTimeState(t);
	    break;
	case SeekTimeState:
	    DrawSeekTimeState(t);
	    break;
	case RemainingTimeState:
	    DrawRemainingTimeState(t);
	    break;
	case TotalTimeState:
	    DrawTotalTimeState(t);
	    break;
    }

    XCopyArea(m_display,m_doubleBufferPixmap,m_me,m_gc,0,0,m_width,m_height,0,0);
    XFlush(m_display);
}

void FALcdWindow::BlitText(Drawable d, GC gc,int32 x, int32 y, const char *text, int32 font) {
    switch (font) {
	case LargeFont: {
	    int32 offset = x;
	    for (int i=0;text[i];i++) {
		if ((offset + m_largeFontWidth[text[i] - 32]) > RIGHT_SIDE_CLIP)
		    break;
		XCopyArea(m_display,m_largeFontPixmap,d,gc,
			  0,(text[i] - 32)*12,
			  m_largeFontWidth[text[i] - 32], 12,
			  offset, y);
		offset += m_largeFontWidth[text[i] - 32];
	    }
	    break;
	}
	case SmallFont: {
	    int32 offset = x;
	    for (int i=0;text[i];i++) {
		if ((offset + m_smallFontWidth[text[i] - 32]) > RIGHT_SIDE_CLIP)
		    break;
		XCopyArea(m_display,m_smallFontPixmap,d,gc,
			  0,(text[i] - 32)*10,
			  m_smallFontWidth[text[i] - 32], 10,
			  offset, y);
		offset += m_smallFontWidth[text[i] - 32];
	    }
	    break;
	}
    }
}

FADialWindow::FADialWindow(Display *display, int32 screen_num,GC gc, Window parent,int32 x,int32 y,int32 w, int32 h) {
    m_display = display;
    m_screenNum = screen_num;
    m_gc = gc;
    m_parent = parent;
    m_xParent = x;
    m_yParent = y;
    m_width = w;
    m_height = h;
    m_me = XCreateSimpleWindow(m_display,m_parent,m_xParent,m_yParent,m_width,m_height,0,BlackPixel(m_display,m_screenNum),WhitePixel(m_display,m_screenNum));
    //fprintf(stderr,"created main win\n");
    m_currentDial = 0;
}
FADialWindow::~FADialWindow() { }

void FADialWindow::DoEvent(XEvent e) {
    //cout << "Got Event" << endl;
    switch (e.type) {
	case MotionNotify:
	    if (e.xmotion.state & Button1Mask) {
		//XMoveWindow(m_display,m_me,e.xmotion.x_root-m_buttonClickSpotX,e.xmotion.y_root-m_buttonClickSpotY);
		int32 tmpInts[] = { 5, 4, 3, 2, 1, 0 };
		int32 tmpInt = (e.xmotion.y_root - m_buttonClickSpotY) % 6;
		m_currentDial = tmpInts[tmpInt];
		Draw();
	    }
	    break;
	case Expose:
	    if (e.xexpose.count != 0)
		return;
	    Draw();
	    break;
	case ButtonPress:
	    m_buttonClickSpotX = e.xbutton.x;
	    m_buttonClickSpotY = e.xbutton.y;
	    break;
    }
}

void FADialWindow::Draw() {
    //cout << "attempting to draw" << endl;
    if (m_mapped) {
	//cout << "drawing..." << endl;
	XCopyArea(m_display,m_pixmap,m_me,m_gc,m_currentDial * m_width,0,m_width,m_height,0,0);
	XFlush(m_display);
    }
}





