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

        $Id: gtkmusicbrowser.cpp,v 1.1.2.9 1999/10/02 15:57:45 ijr Exp $
____________________________________________________________________________*/

#include "config.h"

#include <gtk/gtk.h>
#include <unistd.h>
#include <iostream>

#include "utility.h"
#include "gtkmusicbrowser.h"
#include "fileselector.h"
#include "browsermenu.h"

extern "C" {
void new_plist();
void open_list();
void save_list();
void import_list();
void export_list();
void music_search();
void quit_menu();
void infoedit();
void catalog_tog();
void sort_random();
void sort_location();
void sort_time();
void sort_genre();
void sort_track();
void sort_year();
void sort_title();
void sort_album();
void sort_artist();
void about();
}

/* evil, yes */
MusicBrowserUI *localui = NULL;

void MusicBrowserUI::UpdateCatalog(void)
{
    m_musicCatalog = m_context->browser->m_catalog;

    if (musicBrowserTree) {
        gtk_widget_destroy(musicBrowserTree);
        musicBrowserTree = gtk_tree_new();
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(musicBrowserWindow),
                                              musicBrowserTree);
        gtk_widget_show(musicBrowserTree);
    }

    GtkWidget *item_subtree1, *item_subtree2, *item_subtree3;
    GtkWidget *item_new1, *item_new2, *item_new3;

    artistSubTree = gtk_tree_item_new_with_label("Music Catalog");
    gtk_tree_append(GTK_TREE(musicBrowserTree), artistSubTree);
    gtk_widget_show(artistSubTree);

    vector<ArtistList *>::iterator i = m_musicCatalog->m_artistList->begin();
    item_subtree1 = gtk_tree_new();
    gtk_tree_item_set_subtree(GTK_TREE_ITEM(artistSubTree), item_subtree1);

    for (; i != m_musicCatalog->m_artistList->end(); i++) {
        item_new1 = gtk_tree_item_new_with_label((char *)(*i)->name.c_str());
        gtk_object_set_user_data(GTK_OBJECT(item_new1), *i);
        gtk_tree_append(GTK_TREE(item_subtree1), item_new1);

        vector<AlbumList *>::iterator j = (*i)->m_albumList->begin();
        item_subtree2 = gtk_tree_new();
        gtk_tree_item_set_subtree(GTK_TREE_ITEM(item_new1), item_subtree2);

        for (; j != (*i)->m_albumList->end(); j++) {
            item_new2 = gtk_tree_item_new_with_label((char *)(*j)->name.c_str());
            gtk_object_set_user_data(GTK_OBJECT(item_new2), *j);
            gtk_tree_append(GTK_TREE(item_subtree2), item_new2);

            vector<PlaylistItem *>::iterator k = (*j)->m_trackList->begin();
            item_subtree3 = gtk_tree_new();
            gtk_tree_item_set_subtree(GTK_TREE_ITEM(item_new2), item_subtree3);

            for (;k != (*j)->m_trackList->end(); k++) {
                item_new3 = gtk_tree_item_new_with_label((char *)(*k)->GetMetaData().Title().c_str());
                gtk_object_set_user_data(GTK_OBJECT(item_new3), *k);
                gtk_tree_append(GTK_TREE(item_subtree3), item_new3);
                gtk_widget_show(item_new3);
            }
            gtk_widget_show(item_new2);
        }
        gtk_widget_show(item_new1);
    }

    vector<PlaylistItem *>::iterator l = m_musicCatalog->m_unsorted->begin();
    item_new1 = gtk_tree_item_new_with_label("Unsorted Songs");
    gtk_tree_append(GTK_TREE(item_subtree1), item_new1);
    item_subtree2 = gtk_tree_new();
    gtk_tree_item_set_subtree(GTK_TREE_ITEM(item_new1), item_subtree2);

    for (; l != m_musicCatalog->m_unsorted->end(); l++) {
        item_new2 = gtk_tree_item_new_with_label((char *)(*l)->URL().c_str());
        gtk_object_set_user_data(GTK_OBJECT(item_new2), *l);
        gtk_tree_append(GTK_TREE(item_subtree2), item_new2);
        gtk_widget_show(item_new2);
    }
    gtk_widget_show(item_new1);

    playlistSubTree = gtk_tree_item_new_with_label("Playlists");
    gtk_tree_append(GTK_TREE(musicBrowserTree), playlistSubTree);
    gtk_widget_show(playlistSubTree);
    
    item_subtree1 = gtk_tree_new();
    gtk_tree_item_set_subtree(GTK_TREE_ITEM(playlistSubTree), item_subtree1);
    vector<string>::iterator m = m_musicCatalog->m_playlists->begin();

    for (; m != m_musicCatalog->m_playlists->end(); m++) {
        item_new1 = gtk_tree_item_new_with_label((char *)(*m).c_str());
        gtk_tree_append(GTK_TREE(item_subtree1), item_new1);
        gtk_widget_show(item_new1);
    }
}

void music_search_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->StartMusicSearch();
}

void music_search()
{
    localui->StartMusicSearch();
}

void MusicBrowserUI::CreateExpanded(void)
{
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

    musicBrowserWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(musicBrowserWindow),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(browservbox), musicBrowserWindow, TRUE, TRUE, 0);
    gtk_widget_set_usize(musicBrowserWindow, 200, 200);
    gtk_widget_show(musicBrowserWindow);

    musicBrowserTree = gtk_tree_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(musicBrowserWindow),
                                          musicBrowserTree);
    gtk_widget_show(musicBrowserTree);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(masterBrowserBox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    button = gtk_button_new_with_label("Music Search");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 3);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(music_search_internal), this);

    gtk_widget_show(button);
}

void MusicBrowserUI::ExpandCollapseEvent(void)
{
    if (m_state == STATE_COLLAPSED) {
        CreateExpanded();
        m_state = STATE_EXPANDED;
        gtk_widget_show(masterBrowserBox);
        gtk_label_set_text(GTK_LABEL(expandLabel), "<< Collapse");
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "Music Browser");
        UpdateCatalog();
    }
    else {
        m_state = STATE_COLLAPSED;

        gtk_widget_hide(masterBrowserBox);
        gtk_label_set_text(GTK_LABEL(expandLabel), "<< Expand");
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "Playlist Editor");
    }
}

void expand_collapse_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->ExpandCollapseEvent();
}

void MusicBrowserUI::ToggleVisEvent(void)
{
    Event *e;
    if (m_state == STATE_COLLAPSED)
        e = new Event(CMD_TogglePlaylistUI);
    else
        e = new Event(CMD_ToggleMusicBrowserUI);
    gdk_threads_leave();
    AcceptEvent(e);
    gdk_threads_enter();
    delete e;
}

void toggle_vis_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->ToggleVisEvent();
}

void delete_list_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->DeleteListEvent();
}

void delete_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->DeleteEvent();
}

void add_track_plist_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    FileSelector *filesel = new FileSelector("Add a Track");
    filesel->SetExtended();
    if (filesel->Run()) {
        char *filereturn = strdup_new(filesel->GetReturnPath());

        if (filereturn) {
            char *temp;

            temp = strtok(filereturn, "\n");
            p->AddTrackPlaylistEvent(temp);
            while ((temp = strtok(NULL, "\n")))
                p->AddTrackPlaylistEvent(temp);
       }
       delete filereturn;
    }
    delete filesel;
}

void move_up_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->MoveUpEvent();
}

void move_down_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->MoveDownEvent();
}

void playlist_row_move_internal(GtkWidget *widget, int source, int dest, MusicBrowserUI *p)
{
    p->MoveItemEvent(source, dest);
}

void set_current_index_internal(GtkWidget *widget, int row, int column, 
                                GdkEventButton *button, MusicBrowserUI *p)
{
    p->m_currentindex = row;
    if (button && button->type == GDK_2BUTTON_PRESS)
        p->PlayEvent();
}

void quit_menu()
{
    gtk_main_quit();
}

void sort_playlist_internal(int column, MusicBrowserUI *p, PlaylistSortType type                            = PlaylistSortType_Ascending)
{
    PlaylistSortKey key;

    /* Not a one-to-one, but I suppose I could write it to be...  */
    switch (column) {
        case 0: key = kPlaylistSortKey_Title; break;
        case 1: key = kPlaylistSortKey_Artist; break;
        case 2: key = kPlaylistSortKey_Time; break;
        case 3: key = kPlaylistSortKey_Album; break;
        case 4: key = kPlaylistSortKey_Year; break;
        case 5: key = kPlaylistSortKey_Track; break;
        case 6: key = kPlaylistSortKey_Genre; break;
        case 7: key = kPlaylistSortKey_Location; break;
        default: key = kPlaylistSortKey_Random; break;
    }

    p->SortPlaylistEvent(key, type);
}

void sort_artist()
{
    sort_playlist_internal(1, localui);
}

void sort_album()
{
    sort_playlist_internal(3, localui);
}

void sort_title()
{
    sort_playlist_internal(0, localui);
}

void sort_year()
{
    sort_playlist_internal(4, localui);
}

void sort_track()
{
    sort_playlist_internal(5, localui);
}

void sort_genre()
{
    sort_playlist_internal(6, localui);
}

void sort_time()
{
    sort_playlist_internal(3, localui);
}

void sort_location()
{
    sort_playlist_internal(7, localui);
}

void sort_random()
{
    sort_playlist_internal(8, localui);
}

void catalog_tog()
{
    localui->ExpandCollapseEvent();
}

void infoedit()
{
    localui->PopUpInfoEditor();
}

void new_plist(void)
{
    localui->SaveCurrentPlaylist();
    localui->DeleteListEvent();
    localui->m_currentListName = "";
}

void new_list_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->SaveCurrentPlaylist();
    p->DeleteListEvent();
    p->m_currentListName = "";
}

void open_list()
{
    localui->SaveCurrentPlaylist();

    FileSelector *filesel = new FileSelector("Open a New Playlist");
    if (filesel->Run())
        localui->LoadPlaylist(filesel->GetReturnPath());
    delete filesel;
}

void save_list()
{
    FileSelector *filesel = new FileSelector("Save This Playlist");
    if (filesel->Run())
        localui->SaveCurrentPlaylist(filesel->GetReturnPath());
    delete filesel;
}

void about()
{
   cout << "TODO:\n";
   cout << " - Drag'N'Drop between tree and clist.\n";
   cout << endl;
   cout << "BUGS:\n";
   cout << " - Need to parse file if no metadata exists.\n";
}

void MusicBrowserUI::CreateMenu(GtkWidget *topbox)
{
    GtkItemFactory *item_factory;
    GtkAccelGroup *accel_group;
    GtkWidget *separator;

    accel_group = gtk_accel_group_new();
    item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<blah>", 
                                        accel_group); 
    CreateMenuItems(item_factory);
    
    gtk_accel_group_attach(accel_group, GTK_OBJECT(musicBrowser));
    gtk_box_pack_start(GTK_BOX(topbox), gtk_item_factory_get_widget(
                       item_factory, "<blah>"), FALSE, TRUE, 0);
    gtk_widget_show(gtk_item_factory_get_widget(item_factory, "<blah>"));
    
    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(topbox), separator, FALSE, TRUE, 0);
    gtk_widget_show(separator);
}

void MusicBrowserUI::UpdatePlaylistList(void)
{
    if (!playlistList)
        return;

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


void playlist_column_click_internal(GtkCList *clist, gint column, MusicBrowserUI                                    *p)
{
    if (column == p->m_playlistLastSort) {
        if (p->m_playlistColumnSort == PlaylistSortType_Ascending)
            p->m_playlistColumnSort = PlaylistSortType_Descending;
        else
            p->m_playlistColumnSort = PlaylistSortType_Ascending;
    }
    else
        p->m_playlistColumnSort = PlaylistSortType_Ascending;
    p->m_playlistLastSort = column;

    sort_playlist_internal(column, p, p->m_playlistColumnSort);
}
    
void MusicBrowserUI::CreatePlaylistList(GtkWidget *box)
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
    gtk_signal_connect(GTK_OBJECT(playlistList), "click_column", 
                       GTK_SIGNAL_FUNC(playlist_column_click_internal), this);
    gtk_clist_set_reorderable(GTK_CLIST(playlistList), 1);
    gtk_widget_show(playlistList);

    m_currentindex = (uint32)m_plm->GetCurrentIndex();

    UpdatePlaylistList();
}

void MusicBrowserUI::SetStatusText(const char *text)
{
    if (statusContext > 0) 
        gtk_statusbar_pop(GTK_STATUSBAR(statusBar), statusContext);
    else
        statusContext = 1;

    gtk_statusbar_push(GTK_STATUSBAR(statusBar), 1, text);
}

void MusicBrowserUI::CreatePlaylist(void)
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

    localui = this;

    musicBrowser = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(musicBrowser), "Playlist Editor");
    gtk_window_set_policy(GTK_WINDOW(musicBrowser), TRUE, TRUE, TRUE);
    gtk_signal_connect(GTK_OBJECT(musicBrowser), "destroy",
                       GTK_SIGNAL_FUNC(toggle_vis_internal), this);
    gtk_container_set_border_width(GTK_CONTAINER(musicBrowser), 5);


    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(musicBrowser), vbox);
    gtk_widget_show(vbox);

    statusBar = gtk_statusbar_new();
    gtk_box_pack_end(GTK_BOX(vbox), statusBar, FALSE, TRUE, 5);
    gtk_widget_show(statusBar);

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

    button = gtk_button_new_with_label("Clear List");
    gtk_box_pack_end(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", 
                       GTK_SIGNAL_FUNC(delete_list_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("New List");
    gtk_box_pack_end(GTK_BOX(buttonvbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", 
                       GTK_SIGNAL_FUNC(new_list_internal), this);
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
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(expand_collapse_internal), this);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("  Close  ");
    gtk_box_pack_end(GTK_BOX(controlhbox), button, FALSE, FALSE, 3);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(toggle_vis_internal), this);
    gtk_widget_show(button);

    gtk_widget_show(musicBrowser);

    m_state = STATE_COLLAPSED;
}
