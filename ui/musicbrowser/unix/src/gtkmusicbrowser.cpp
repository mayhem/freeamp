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

        $Id: gtkmusicbrowser.cpp,v 1.1.2.1 1999/09/09 01:25:35 ijr Exp $
____________________________________________________________________________*/

#include <gtk/gtk.h>
#include <unistd.h>

#include "musicbrowser.h"

char *filereturn = NULL;

void musicbrowserUI::CreateExpanded(void)
{
    GtkWidget *browserwindow;
    GtkWidget *hbox;
    GtkWidget *browserlabel;
    GtkWidget *browservbox;
    GtkWidget *button;

    if (m_browserCreated)
        return;

    m_browserCreated = true;

    masterBrowserBox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(masterBox), masterBrowserBox, TRUE, TRUE, 0);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(masterBrowserBox), hbox, FALSE, FALSE, 6);
    gtk_widget_show(hbox);

    browserlabel = gtk_label_new("My Music Catalog:");
    gtk_box_pack_start(GTK_BOX(hbox), browserlabel, FALSE, FALSE, 10);
    gtk_widget_show(browserlabel);

    browservbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(masterBrowserBox), browservbox);
    gtk_container_set_border_width(GTK_CONTAINER(browservbox), 5);
    gtk_widget_show(browservbox);

    browserwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(browserwindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(browservbox), browserwindow, TRUE, TRUE, 0);
    gtk_widget_set_usize(browserwindow, 200, 200);
    gtk_widget_show(browserwindow);

    musicBrowserTree = gtk_tree_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(browserwindow),
                                          musicBrowserTree);
    gtk_widget_show(musicBrowserTree);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(masterBrowserBox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    button = gtk_button_new_with_label("Music Search");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 3);
    gtk_widget_show(button);
}

void musicbrowserUI::ExpandCollapseEvent(void)
{
    if (m_state == STATE_COLLAPSED) {
        CreateExpanded();
        m_state = STATE_EXPANDED;
        gtk_widget_show(masterBrowserBox);
        gtk_label_set_text(GTK_LABEL(expandLabel), "Collapse >>");
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "Music Browser");
    }
    else {
        m_state = STATE_COLLAPSED;

        gtk_widget_hide(masterBrowserBox);
        gtk_label_set_text(GTK_LABEL(expandLabel), "<< Expand");
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "Playlist Editor");
    }
}

void expand_collapse_internal(GtkWidget *widget, musicbrowserUI *p)
{
    p->ExpandCollapseEvent();
}

void delete_list_internal(GtkWidget *widget, musicbrowserUI *p)
{
    p->DeleteListEvent();
}

void delete_internal(GtkWidget *widget, musicbrowserUI *p)
{
    p->DeleteEvent();
}

gboolean filesel_destroy(GtkWidget *widget)
{
    gtk_main_quit();
    return FALSE;
}


void add_ok_internal(GtkWidget *widget, GtkFileSelection *file)
{
    char *raw_path = NULL;
    GList *row = GTK_CLIST(file->file_list)->row_list;
    gint rownum = 0;
    char *temp, *path_temp;

    filereturn = strdup(gtk_file_selection_get_filename(file));
    path_temp = strdup(filereturn);

    char *tempdir = strrchr(path_temp, '/');
    if (!tempdir) {
        strcpy(path_temp, "./");
        path_temp = (char *)realloc(path_temp, strlen(path_temp) + 1);
    }
    else
        tempdir[0] = '\0';

    raw_path = gtk_entry_get_text(GTK_ENTRY(file->selection_entry));
    while (row) {
        if (GTK_CLIST_ROW(row)->state == GTK_STATE_SELECTED) {
            if (gtk_clist_get_cell_type(GTK_CLIST(file->file_list), rownum, 0) 
                == GTK_CELL_TEXT) {
                gtk_clist_get_text(GTK_CLIST(file->file_list), rownum, 0, &temp);
                if (!strcmp(temp, raw_path))
                    goto next_iter;
                filereturn = (char *)realloc(filereturn, strlen(filereturn) + 
                                     strlen(path_temp) + strlen(temp) + 3);
                strcat(filereturn, "\n");
                strcat(filereturn, path_temp);
                strcat(filereturn, "/");
                strcat(filereturn, temp);
            }
        }
    next_iter:
        rownum++;
        row = g_list_next(row);
    }
    gtk_widget_destroy(GTK_WIDGET(file));
    free(path_temp);
}

void add_track_plist_internal(GtkWidget *widget, musicbrowserUI *p)
{
    GtkWidget *filesel;

    filesel = gtk_file_selection_new("Add a Track");

    gtk_window_set_modal(GTK_WINDOW(filesel), TRUE);
    gtk_signal_connect(GTK_OBJECT(filesel), "destroy",
                       GTK_SIGNAL_FUNC(filesel_destroy), NULL);
    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filesel)->cancel_button), 
                       "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), 
                       GTK_OBJECT(filesel));
    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filesel)->ok_button),
                       "clicked", GTK_SIGNAL_FUNC(add_ok_internal), 
                       GTK_OBJECT(filesel));

    gtk_clist_set_selection_mode(GTK_CLIST(GTK_FILE_SELECTION(filesel)->file_list), GTK_SELECTION_EXTENDED);
    gtk_widget_show(filesel);

    gtk_main();

    if (filereturn) {
        char *temp;

        temp = strtok(filereturn, "\n");
        p->AddTrackPlaylistEvent(temp);
        while ((temp = strtok(NULL, "\n")))
            p->AddTrackPlaylistEvent(temp);
        free(filereturn);
    }
}

void move_up_internal(GtkWidget *widget, musicbrowserUI *p)
{
    p->MoveUpEvent();
}

void move_down_internal(GtkWidget *widget, musicbrowserUI *p)
{
    p->MoveDownEvent();
}

void playlist_row_move_internal(GtkWidget *widget, int source, int dest, musicbrowserUI *p)
{
    p->MoveItemEvent(source, dest);
}

void set_current_index_internal(GtkWidget *widget, int row, int column, 
                                GdkEventButton *button, musicbrowserUI *p)
{
    p->m_currentindex = row;
    if (button && button->type == GDK_2BUTTON_PRESS)
        p->PlayEvent();
}

void musicbrowserUI::CreateMenu(GtkWidget *topbox)
{
    GtkWidget *menubar;
    GtkWidget *menuitem;
    GtkWidget *separator;

    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(topbox), menubar, FALSE, TRUE, 0);

    menuitem = gtk_menu_item_new_with_label("File");
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_label("Edit");
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_label("View");
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_label("Playlist");
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_right_justify(GTK_MENU_ITEM(menuitem));
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menuitem);
    gtk_widget_show(menuitem);

    gtk_widget_show(menubar);

    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(topbox), separator, FALSE, TRUE, 0);
    gtk_widget_show(separator);
}

void musicbrowserUI::UpdatePlaylistList(void)
{
    gtk_clist_freeze(GTK_CLIST(playlistList));

    gtk_clist_clear(GTK_CLIST(playlistList));

    uint32 iLoop = m_plm->CountItems();

    for (uint32 i = 0; i < iLoop; i++) {
        PlaylistItem *item = m_plm->ItemAt(i);

        if (!item)
            continue;

        while (item->GetState() == kPlaylistItemState_RetrievingMetaData)
           usleep(10);

        MetaData mdata = item->GetMetaData();

        char *iText[3];

        char *title = (char *)mdata.Title().c_str();
        char *artist = (char *)mdata.Artist().c_str();
        char length[50];
        sprintf(length, "%d", mdata.Time());

        iText[0] = title;
        iText[1] = artist;
        iText[2] = length;

        gtk_clist_append(GTK_CLIST(playlistList), iText);
    }

    gtk_clist_columns_autosize(GTK_CLIST(playlistList));
    gtk_clist_select_row(GTK_CLIST(playlistList), m_currentindex, 0);
    gtk_clist_thaw(GTK_CLIST(playlistList));
}

void musicbrowserUI::CreatePlaylistList(GtkWidget *box)
{
    static char *titles[] =
    {
      "Title", "Artist", "Length"
    };

    playlistList = gtk_clist_new_with_titles(3, titles);
    gtk_container_add(GTK_CONTAINER(box), playlistList);
    gtk_signal_connect(GTK_OBJECT(playlistList), "row_move",
                       GTK_SIGNAL_FUNC(playlist_row_move_internal), this);   
    gtk_signal_connect(GTK_OBJECT(playlistList), "select_row",
                       GTK_SIGNAL_FUNC(set_current_index_internal), this);
    gtk_clist_set_reorderable(GTK_CLIST(playlistList), 1);
    gtk_widget_show(playlistList);

    m_currentindex = (uint32)m_plm->GetCurrentIndex();

    UpdatePlaylistList();
}

void musicbrowserUI::CreatePlaylist(void)
{
    GtkWidget *vbox;
    GtkWidget *buttonvbox;
    GtkWidget *hbox;
    GtkWidget *playlistwindow;
    GtkWidget *controlhbox;
    GtkWidget *arrow;
    GtkWidget *optionmenu;
    GtkWidget *item;
    GtkWidget *menu;
    GtkWidget *label;
    GtkWidget *button;

    musicBrowser = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(musicBrowser), "Playlist Editor");
    gtk_window_set_policy(GTK_WINDOW(musicBrowser), TRUE, TRUE, TRUE);
    gtk_signal_connect(GTK_OBJECT(musicBrowser), "destroy",
                       GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(musicBrowser), 5);


    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(musicBrowser), vbox);
    gtk_widget_show(vbox);

    CreateMenu(vbox);

    masterBox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), masterBox, TRUE, TRUE, 0);
    gtk_widget_show(masterBox);

    masterPlaylistBox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_end(GTK_BOX(masterBox), masterPlaylistBox, TRUE, TRUE, 0);
    gtk_widget_show(masterPlaylistBox);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(masterPlaylistBox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    optionmenu = gtk_option_menu_new();
    menu = gtk_menu_new();
    item = gtk_menu_item_new_with_label("Master Playlist");
    gtk_widget_show(item);
    gtk_menu_append(GTK_MENU(menu), item);
    gtk_option_menu_set_menu(GTK_OPTION_MENU(optionmenu), menu);
    gtk_box_pack_end(GTK_BOX(hbox), optionmenu, FALSE, FALSE, 10);
    gtk_widget_show(optionmenu);

    label = gtk_label_new("View Playlist:");
    gtk_box_pack_end(GTK_BOX(hbox), label, FALSE, FALSE, 10);
    gtk_widget_show(label);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(masterPlaylistBox), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_widget_show(vbox);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    gtk_widget_show(hbox);

    playlistwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(playlistwindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(hbox), playlistwindow, TRUE, TRUE, 0);
    gtk_widget_set_usize(playlistwindow, 200, 200);
    gtk_widget_show(playlistwindow);

    CreatePlaylistList(playlistwindow);

    buttonvbox = gtk_vbox_new(FALSE, 10);
    gtk_container_set_border_width(GTK_CONTAINER(buttonvbox), 5);
    gtk_box_pack_start(GTK_BOX(hbox), buttonvbox, FALSE, FALSE, 0);
    gtk_widget_show(buttonvbox);

    button = gtk_button_new();
    arrow = gtk_arrow_new(GTK_ARROW_UP, GTK_SHADOW_IN);
    gtk_widget_show(arrow);
    gtk_container_add(GTK_CONTAINER(button), arrow);
    gtk_box_pack_start(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(move_up_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Delete");
    gtk_box_pack_start(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(delete_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Add Track");
    gtk_box_pack_start(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(add_track_plist_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new();
    arrow = gtk_arrow_new(GTK_ARROW_DOWN, GTK_SHADOW_IN);
    gtk_widget_show(arrow);
    gtk_container_add(GTK_CONTAINER(button), arrow);
    gtk_box_pack_start(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(move_down_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("New List");
    gtk_box_pack_end(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Delete List");
    gtk_box_pack_end(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", 
                       GTK_SIGNAL_FUNC(delete_list_internal), this);
    gtk_widget_show(button);

    controlhbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(masterPlaylistBox), controlhbox, FALSE, FALSE, 0);
    gtk_widget_show(controlhbox);

    expandLabel = gtk_label_new("<< Expand");
    gtk_misc_set_alignment(GTK_MISC(expandLabel), 0.5, 0.5);
    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), expandLabel);
    gtk_widget_show(expandLabel);
    gtk_box_pack_start(GTK_BOX(controlhbox), button, FALSE, FALSE, 3);
/*    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(expand_collapse_internal), this);
*/    gtk_widget_show(button);

    button = gtk_button_new_with_label("  Close  ");
    gtk_box_pack_end(GTK_BOX(controlhbox), button, FALSE, FALSE, 3);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
    gtk_widget_show(button);

    gtk_widget_show(musicBrowser);

    m_state = STATE_COLLAPSED;
}
