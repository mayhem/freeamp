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

   $Id: GTKWindow.cpp,v 1.1.2.9 1999/10/02 00:40:14 ijr Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <unistd.h>
#include "facontext.h"
#include "Theme.h"
#include "GTKWindow.h"
#include "GTKCanvas.h"
#include "GTKUtility.h" 

void mouse_move(GtkWidget *w, GdkEvent *e, GTKWindow *ui)
{
    Pos oPos;

    oPos.x = (int)e->motion.x_root;
    oPos.y = (int)e->motion.y_root;
    gdk_threads_leave();
    ui->HandleMouseMove(oPos);
    gdk_threads_enter();
}

void button_down(GtkWidget *w, GdkEvent *e, GTKWindow *ui)
{
    Pos oPos;

    oPos.x = (int)e->button.x_root;
    oPos.y = (int)e->button.y_root;
    gdk_threads_leave();
    if (e->button.button == 1) 
        ui->HandleMouseLButtonDown(oPos);
    gdk_threads_enter();
}

void button_up(GtkWidget *w, GdkEvent *e, GTKWindow *ui)
{
    Pos oPos;
    oPos.x = (int)e->button.x_root;
    oPos.y = (int)e->button.y_root;
    gdk_threads_leave();
    if (e->button.button == 1)
        ui->HandleMouseLButtonUp(oPos);
    gdk_threads_enter();
}

GTKWindow::GTKWindow(Theme *pTheme, string &oName)
          :Window(pTheme, oName)
{
    m_pCanvas = new GTKCanvas(this);
    initialized = false;
}

GTKWindow::~GTKWindow(void)
{
    Close();
    delete m_pCanvas;
    m_pCanvas = NULL;
}

Error GTKWindow::Run(Pos &oPos)
{
    Rect oRect;
    int iMaxX, iMaxY;

    m_oWindowPos = oPos;
    m_pCanvas->Init();

    gdk_threads_enter();
    iMaxX = gdk_screen_width();
    iMaxY = gdk_screen_height();
 
    GetCanvas()->GetBackgroundRect(oRect);

    if (m_oWindowPos.x > iMaxX || m_oWindowPos.x + oRect.Width() < 0)
       m_oWindowPos.x = 0;
    if (m_oWindowPos.y > iMaxY || m_oWindowPos.y + oRect.Height() < 0)
       m_oWindowPos.y = 0;

    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_app_paintable(mainWindow, TRUE);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "FreeAmp");
    gtk_window_set_policy(GTK_WINDOW(mainWindow), TRUE, TRUE, TRUE);
    gtk_signal_connect(GTK_OBJECT(mainWindow), "destroy",
                       GTK_SIGNAL_FUNC(gtk_widget_destroy), NULL);
    gtk_widget_set_uposition(mainWindow, m_oWindowPos.x, m_oWindowPos.y);
    gtk_widget_set_usize(mainWindow, oRect.Width(), oRect.Height());
    gtk_widget_set_events(mainWindow, GDK_SUBSTRUCTURE_MASK | GDK_STRUCTURE_MASK
                          | GDK_POINTER_MOTION_MASK | GDK_BUTTON_MOTION_MASK | 
                          GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
    gtk_widget_realize(mainWindow);

    gtk_signal_connect(GTK_OBJECT(mainWindow), "motion_notify_event",
                       GTK_SIGNAL_FUNC(mouse_move), this);
    gtk_signal_connect(GTK_OBJECT(mainWindow), "button_press_event",
                       GTK_SIGNAL_FUNC(button_down), this);
    gtk_signal_connect(GTK_OBJECT(mainWindow), "button_release_event",
                       GTK_SIGNAL_FUNC(button_up), this);
    gdk_window_set_decorations(mainWindow->window, (GdkWMDecoration)0);
    gdk_threads_leave();
    
    Init();
    ((GTKCanvas *)GetCanvas())->Paint(oRect);

    gdk_threads_enter();
    gtk_widget_show(mainWindow);
    gdk_flush(); 

    gdk_threads_leave();
 
    initialized = true;

    while (mainWindow) 
       sleep(1);
    return kError_NoErr;
}

void GTKWindow::SaveWindowPos(Pos &oPos)
{
    m_oWindowPos = oPos;
}

Error GTKWindow::Close(void)
{
    Rect oRect;
    Pos oPos;
    
    GetWindowPosition(oRect);
    oPos.x = oRect.x1;
    oPos.y = oRect.y1;
    SaveWindowPos(oPos);
    gtk_widget_destroy(mainWindow);
    gdk_flush();
    mainWindow = NULL;
    return kError_NoErr;
}

Error GTKWindow::Enable(void)
{
    return kError_NoErr;
}

Error GTKWindow::Disable(void)
{
    return kError_NoErr;
}

Error GTKWindow::Show(void)
{
    gtk_widget_show(mainWindow);
    return kError_NoErr;
}

Error GTKWindow::Hide(void)
{
    gtk_widget_hide(mainWindow);
    return kError_NoErr;
}

Error GTKWindow::SetTitle(string &oTitle)
{
    gtk_window_set_title(GTK_WINDOW(mainWindow), oTitle.c_str());
    return kError_NoErr;
}

Error GTKWindow::CaptureMouse(bool bCapture)
{
    if (bCapture) {
        gdk_pointer_grab(mainWindow->window, FALSE, (GdkEventMask)(GDK_SUBSTRUCTURE_MASK | GDK_STRUCTURE_MASK | GDK_POINTER_MOTION_MASK | GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK), mainWindow->window, NULL, 0);
    }
    else {
        gdk_pointer_ungrab(0);
    }
    return kError_NoErr;
}

Error GTKWindow::HideMouse(bool bHide)
{
    return kError_NoErr;
}

Error GTKWindow::SetMousePos(Pos &oPos)
{
    WarpPointer(mainWindow->window, oPos.x, oPos.y);
    return kError_NoErr;
}

Error GTKWindow::GetMousePos(Pos &oPos)
{
    if (initialized)
        gtk_widget_get_pointer(mainWindow, &oPos.x, &oPos.y);
    return kError_NoErr;
}

Error GTKWindow::SetWindowPosition(Rect &oWindowRect)
{
    gdk_window_move(mainWindow->window, oWindowRect.x1, oWindowRect.y1);
    return kError_NoErr;
}

Error GTKWindow::GetWindowPosition(Rect &oWindowRect) 
{
    gdk_window_get_position(mainWindow->window, &oWindowRect.x1, 
                            &oWindowRect.y1);
    return kError_NoErr;
}

Error GTKWindow::Minimize(void)
{
    IconifyWindow(mainWindow->window);
    return kError_NoErr;
}

Error GTKWindow::Restore(void)
{
    return kError_NoErr;
}
