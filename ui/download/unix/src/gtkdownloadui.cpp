/*____________________________________________________________________________

        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 1999 EMusic.com

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

        $Id: gtkdownloadui.cpp,v 1.1.2.1 1999/10/06 16:42:16 ijr Exp $
____________________________________________________________________________*/

#include "config.h"

#include <gtk/gtk.h>
#include <strstream>
#include <iostream>

#include "utility.h"
#include "downloadui.h"

void DownloadUI::ToggleVisEvent(void)
{
    Event *e = new Event(CMD_ToggleDownloadUI);
    gdk_threads_leave();
    AcceptEvent(e);
    gdk_threads_enter();
    delete e;
}

void toggle_vis_internal(GtkWidget *widget, DownloadUI *p)
{
    p->ToggleVisEvent();
}

void DownloadUI::UpdateInfo(void)
{
}

void DownloadUI::UpdateDownloadList(void)
{
    if (!m_List)
        return;

    gtk_clist_freeze(GTK_CLIST(m_List));
    gtk_clist_clear(GTK_CLIST(m_List));

    uint32 iLoop = downloadList.size();

    for (uint32 i = 0; i < iLoop; i++) {
        DownloadItem *dli = downloadList[i];
        char *iText[2];

        string displayString = dli->GetMetaData().Title();
        string statusString;

        iText[0] = (char *)displayString.c_str();  
  
        switch (dli->GetState()) {
            case kDownloadItemState_Queued: {
                ostrstream ost;
                float total;
 
                ost.precision(2);
                ost.flags(ios::fixed);
 
                total = dli->GetTotalBytes();
 
                if (total >= 1048576) {
                    total /= 1048576;
                    ost << "Queued (" << total << " MB)";
                }
                else if (total >= 1024) {
                    total /= 1024;
                    ost << "Queued (" << total << " KB)";
                }
                else 
                    ost << "Queued (" << total << " Bytes)";
                
                statusString = ost.str();
                break; }
            case kDownloadItemState_Downloading: {
                float total;
                float recvd;
                uint32 percent;
                ostrstream ost;

                ost.precision(2);
                ost.flags(ios::fixed);
                total = dli->GetTotalBytes();
                recvd = dli->GetBytesReceived();
                percent = (uint32)(recvd/total*100);

                if (total >= 1048576) {
                    total /= 1048576;
                    recvd /= 1048576;
                    ost << percent << "% (" << recvd << " of " << total << " MB) ";
                }
                else if(total >= 1024) {
                    total /= 1024;
                    recvd /= 1024;
                    ost << percent << "% ("<< recvd << " of "<< total << " KB)";
                }
                else
                    ost << percent << "% (" << recvd << " of " << total << " Bytes)";
                
                statusString = ost.str();
                break; }
            case kDownloadItemState_Cancelled: {
                statusString = "Cancelled";
                break; }
            case kDownloadItemState_Paused: {
                ostrstream ost;
                float total;
                float recvd;
                uint32 percent;
 
                ost.precision(2);
                ost.flags(ios::fixed);
  
                total = dli->GetTotalBytes();
                recvd = dli->GetBytesReceived();
                percent = (uint32)(recvd/total*100);

                if (total >= 1048576) {
                    total /= 1048576;
                    recvd /= 1048576;
                    ost << "Paused (" << recvd << " of "<< total << " MB - " << percent << "%)";
                }
                else if(total >= 1024) {
                    total /= 1024;
                    recvd /= 1024;
                    ost << "Paused (" << recvd << " of "<< total << " KB - " << percent << "%)";
                }
                else
                    ost << "Paused (" << recvd << " of " << total << " Bytes - " << percent << "%)";

                statusString = ost.str();
                break; }
            case kDownloadItemState_Error: {
                ostrstream ost;
                ost << "Error: " << dli->GetDownloadError();
                statusString = ost.str();
                break; }
            case kDownloadItemState_Done: {
                statusString = "Download Complete";
                break; }
            default:
                break;
        }
        iText[1] = (char *)statusString.c_str();

        gtk_clist_append(GTK_CLIST(m_List), iText);
    }

    gtk_clist_select_row(GTK_CLIST(m_List), m_currentindex, 0);
    UpdateInfo();
    gtk_clist_thaw(GTK_CLIST(m_List));
}

void set_current_sel_internal(GtkWidget *widget, int row, int column,
                              GdkEventButton *button, DownloadUI *p)
{
   p->SelChangeEvent(row);
}

void DownloadUI::CreateDownloadList(GtkWidget *box)
{
    static char *titles[] =
    {
      "Song Title", "Status"
    };

    m_List = gtk_clist_new_with_titles(2, titles);
    gtk_container_add(GTK_CONTAINER(box), m_List);
    gtk_signal_connect(GTK_OBJECT(m_List), "select_row",
                       GTK_SIGNAL_FUNC(set_current_sel_internal), this);
    gtk_widget_show(m_List);

    UpdateDownloadList();
}

void cancel_internal(GtkWidget *w, DownloadUI *p)
{
    p->CancelEvent();
}

void pause_internal(GtkWidget *w, DownloadUI *p)
{
    p->PauseEvent();
}

void resume_internal(GtkWidget *w, DownloadUI *p)
{
    p->ResumeEvent();
}

void DownloadUI::CreateDownloadUI(void)
{
    m_downloadUI = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(m_downloadUI), "FreeAmp - DownloadManager");
    gtk_window_set_policy(GTK_WINDOW(m_downloadUI), TRUE, TRUE, TRUE);
    gtk_signal_connect(GTK_OBJECT(m_downloadUI), "destroy",
                       GTK_SIGNAL_FUNC(toggle_vis_internal), this);
    gtk_container_set_border_width(GTK_CONTAINER(m_downloadUI), 5);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(m_downloadUI), vbox);
    gtk_widget_show(vbox);

    GtkWidget *listwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(listwindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), listwindow, TRUE, TRUE, 0);
    gtk_widget_set_usize(listwindow, 400, 140);
    gtk_widget_show(listwindow);

    CreateDownloadList(listwindow);

    GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_end(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    gtk_widget_show(hbox);

    m_CancelButton = gtk_button_new_with_label("Cancel Download");
    gtk_box_pack_start(GTK_BOX(hbox), m_CancelButton, FALSE, FALSE, 5);
    gtk_signal_connect(GTK_OBJECT(m_CancelButton), "clicked",
                       GTK_SIGNAL_FUNC(cancel_internal), this);
    gtk_widget_show(m_CancelButton);

    m_PauseButton = gtk_button_new_with_label("Pause Download");
    gtk_box_pack_start(GTK_BOX(hbox), m_PauseButton, FALSE, FALSE, 5);
    gtk_signal_connect(GTK_OBJECT(m_PauseButton), "clicked",
                       GTK_SIGNAL_FUNC(pause_internal), this);
    gtk_widget_show(m_PauseButton);

    m_ResumeButton = gtk_button_new_with_label("Resume Download");
    gtk_box_pack_start(GTK_BOX(hbox), m_ResumeButton, FALSE, FALSE, 5);
    gtk_signal_connect(GTK_OBJECT(m_ResumeButton), "clicked", 
                       GTK_SIGNAL_FUNC(resume_internal), this);
    gtk_widget_show(m_ResumeButton);

    m_CloseButton = gtk_button_new_with_label("Close");
    gtk_box_pack_end(GTK_BOX(hbox), m_CloseButton, FALSE, FALSE, 5);
    gtk_signal_connect(GTK_OBJECT(m_CloseButton), "clicked",
                       GTK_SIGNAL_FUNC(toggle_vis_internal), this);
    gtk_widget_show(m_CloseButton);

    gtk_widget_show(m_downloadUI);
}
