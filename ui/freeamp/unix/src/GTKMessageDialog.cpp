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

   $Id: GTKMessageDialog.cpp,v 1.2 1999/10/19 07:13:20 elrod Exp $
____________________________________________________________________________*/ 

#include <gtk/gtk.h>
#include <unistd.h>

#include "MessageDialog.h"


MessageDialog::MessageDialog(void)
{
}

MessageDialog::~MessageDialog(void)
{

}

MessageDialogReturnEnum MessageDialog::
                        Show(const char        *szMessage, 
                             const char        *szTitle, 
                             MessageDialogEnum  eType)
{
    string oMessage(szMessage), oTitle(szTitle);
    
    return Show(oMessage, oTitle, eType);
}

static gboolean message_destroy(GtkWidget *widget)
{
    return FALSE;
}

static void ok_click(GtkWidget *w, int *ret)
{
    *ret = 1;
}

static void yes_click(GtkWidget *w, int *ret)
{
    *ret = 2;
}

static void no_click(GtkWidget *w, int *ret)
{
    *ret = 3;
}

static void cancel_click(GtkWidget *w, int *ret)
{
    *ret = 4;
}

static void retry_click(GtkWidget *w, int *ret)
{
    *ret = 5;
}

MessageDialogReturnEnum MessageDialog::
                        Show(const string      &oMessage, 
                             const string      &oTitle, 
                             MessageDialogEnum  eType)
{
    gdk_threads_enter();
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    gtk_signal_connect(GTK_OBJECT(window), "destroy", 
                       GTK_SIGNAL_FUNC(message_destroy), NULL);
    gtk_window_set_title(GTK_WINDOW(window), oTitle.c_str());
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);

    GtkWidget *message = gtk_label_new(oMessage.c_str());
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_container_add(GTK_CONTAINER(vbox), message);
    gtk_widget_show(message);

    GtkWidget *hbox = gtk_hbox_new(FALSE, 10);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);
    gtk_widget_show(hbox);

    GtkWidget *button;
    int iRet = 0;
    switch (eType) {
        case kMessageOk: {
            button = gtk_button_new_with_label("OK");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(ok_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy), 
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);
            break; }
        case kMessageYesNo: {
            button = gtk_button_new_with_label("Yes");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(yes_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);

            button = gtk_button_new_with_label("No");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(no_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);
            break; }
        case kMessageOkCancel: {
            button = gtk_button_new_with_label("OK");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(ok_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);

            button = gtk_button_new_with_label("Cancel");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(cancel_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);
            break; }
        case kMessageMonicaSucks: {
            button = gtk_button_new_with_label("Retry");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(retry_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);

            button = gtk_button_new_with_label("Cancel");
            gtk_signal_connect(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(cancel_click), &iRet);
            gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
                               GTK_SIGNAL_FUNC(gtk_widget_destroy),
                               GTK_OBJECT(window));
            gtk_container_add(GTK_CONTAINER(hbox), button);
            gtk_widget_show(button);
            break; }
    }

    gtk_widget_show(window);

    gdk_threads_leave();

    while (iRet == 0)
        usleep(20);

    switch (iRet) {
        case 1:
            return kMessageReturnOk;
        case 2:
            return kMessageReturnYes;
        case 3:
            return kMessageReturnNo;
        case 4:
            return kMessageReturnCancel;
        case 5:
            return kMessageReturnMonicaDoesSuck;
        default:
            return kMessageReturnUnknown;
    }
}

