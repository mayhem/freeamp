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

        $Id: gtkmusicbrowser.cpp,v 1.1.2.18 1999/10/17 05:40:23 ijr Exp $
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

struct {
    void *data;
    int type;
} TreeData;

vector<PlaylistItem *> *getTreeSelection(GtkWidget *item)
{
    int type = (int)gtk_object_get_data(GTK_OBJECT(item), "type");
    vector<PlaylistItem *> *newlist = new vector<PlaylistItem *>;
    switch (type) {
        case 1: {
            ArtistList *list = (ArtistList *)gtk_object_get_user_data(GTK_OBJECT(item));
            vector<AlbumList *>::iterator i = list->m_albumList->begin();
            for (; i != list->m_albumList->end(); i++) {
                vector<PlaylistItem *>::iterator j = (*i)->m_trackList->begin();
                for (; j != (*i)->m_trackList->end(); j++) {
                    PlaylistItem *item = new PlaylistItem(*(PlaylistItem *)*j);
                    newlist->push_back(item);
                }
            }
            break; }
        case 2: {
            AlbumList *list = (AlbumList *)gtk_object_get_user_data(GTK_OBJECT(item));
            vector<PlaylistItem *>::iterator j = list->m_trackList->begin();
            for (; j != list->m_trackList->end(); j++) {
                PlaylistItem *item = new PlaylistItem(*(PlaylistItem *)*j);
                newlist->push_back(item);
            }
            break; }
        case 3: {
            PlaylistItem *i = new PlaylistItem(*(PlaylistItem *)gtk_object_get_user_data(GTK_OBJECT(item)));
            newlist->push_back(i);
            break; }
        case 4: {
            PlaylistItem *i = new PlaylistItem(*(PlaylistItem *)gtk_object_get_user_data(GTK_OBJECT(item)));
            newlist->push_back(i);
            break; }
        case 5: {
            char *fname = (char *)gtk_object_get_user_data(GTK_OBJECT(item));
            localui->ReadPlaylist(fname, newlist);
            break; }
        case 9: {
            cout << "Danger, Wil Robinson, Danger!  To be implemented soon\n";
            break; }
        default:
            break;
    }
    return newlist;
}

gboolean list_drag_drop_internal(GtkWidget *widget, GdkDragContext *context,
                                 gint x, gint y, guint time, MusicBrowserUI *p)
{
    if (widget == gtk_drag_get_source_widget(context))
        return FALSE;
    GList *list = context->targets;
    GdkAtom atom = gdk_atom_intern("tree-drag", FALSE);
    while (list) {
        if ((int)atom == GPOINTER_TO_INT(list->data)) 
            return TRUE;
        list = list->next;
    }
    return FALSE;
}

void drag_dest_info_destroy(gpointer data)
{
    GtkCListDestInfo *info = (GtkCListDestInfo *)data;
    g_free(info);
}

#define ROW_TOP_YPIXEL(clist, row) (((clist)->row_height * (row)) + \
                                    ((row) + 1) + (clist)->voffset)
#define ROW_FROM_YPIXEL(clist, y)  (((y) - (clist)->voffset) / \
                                    ((clist)->row_height + 1))
#define GTK_CLIST_CLASS_FW(_widget_) GTK_CLIST_CLASS (((GtkObject*) (_widget_))->klass)


static gint COLUMN_FROM_XPIXEL (GtkCList * clist, gint x)
{
  gint i, cx;

  for (i = 0; i < clist->columns; i++)
    if (clist->column[i].visible)
      {
        cx = clist->column[i].area.x + clist->hoffset;

        if (x >= (cx - 4) &&
            x <= (cx + clist->column[i].area.width + 3))
          return i;
      }

  return -1;
}

static void drag_dest_cell (GtkCList *clist, gint x, gint y, 
                     GtkCListDestInfo *dest_info)
{
    GtkWidget *widget;

    widget = GTK_WIDGET (clist);
    dest_info->insert_pos = GTK_CLIST_DRAG_NONE;

    y -= (GTK_CONTAINER (clist)->border_width + 
          widget->style->klass->ythickness + clist->column_title_area.height);

    dest_info->cell.row = ROW_FROM_YPIXEL (clist, y);
    if (dest_info->cell.row >= clist->rows) {
        dest_info->cell.row = clist->rows - 1;
        y = ROW_TOP_YPIXEL (clist, dest_info->cell.row) + clist->row_height;
    }
    if (dest_info->cell.row < -1)
        dest_info->cell.row = -1;

    x -= GTK_CONTAINER (widget)->border_width + 
         widget->style->klass->xthickness;
    dest_info->cell.column = COLUMN_FROM_XPIXEL (clist, x);

    if (dest_info->cell.row >= 0) {
        gint y_delta;
        gint h = 0;

        y_delta = y - ROW_TOP_YPIXEL (clist, dest_info->cell.row);

        if (GTK_CLIST_DRAW_DRAG_RECT(clist)) {
            dest_info->insert_pos = GTK_CLIST_DRAG_INTO;
            h = clist->row_height / 4;
        }
        else if (GTK_CLIST_DRAW_DRAG_LINE(clist)) {
            dest_info->insert_pos = GTK_CLIST_DRAG_BEFORE;
            h = clist->row_height / 2;
        }
 
        if (GTK_CLIST_DRAW_DRAG_LINE(clist)) {
            if (y_delta < h)
                dest_info->insert_pos = GTK_CLIST_DRAG_BEFORE;
            else if (clist->row_height - y_delta < h)
                dest_info->insert_pos = GTK_CLIST_DRAG_AFTER;
        }
    }
}

void list_drag_rec_internal(GtkWidget *widget, GdkDragContext *context,
                            gint x, gint y, GtkSelectionData *data,
                            guint info, guint time, MusicBrowserUI *p)
{
    if (widget == gtk_drag_get_source_widget(context))
        return;
    if (data->length == sizeof(vector<PlaylistItem *> *)) {
        vector<PlaylistItem *> *newlist = *((vector<PlaylistItem *> **)(data->data));
        if (newlist) {
            GtkCListDestInfo dest_info;

            drag_dest_cell(GTK_CLIST(widget), x, y, &dest_info);
            if (dest_info.insert_pos == GTK_CLIST_DRAG_AFTER)
                dest_info.cell.row++;

            p->m_currentindex = dest_info.cell.row;
            p->AddTracksPlaylistEvent(newlist);

            g_dataset_remove_data(context, "gtk-clist-drag-dest");
        }
    }
}

void list_drag_leave_internal(GtkWidget *widget, GdkDragContext *context,
                              guint time, MusicBrowserUI *p)
{
    if (widget == gtk_drag_get_source_widget(context))
        return;

    GtkCList *clist = GTK_CLIST(widget);
    GtkCListDestInfo *dest_info;
    dest_info = (GtkCListDestInfo *)g_dataset_get_data(context, 
                                                       "gtk-clist-drag-dest");
    if (dest_info) {
        if (dest_info->cell.row >= 0) {
            GList *list = context->targets;
            GdkAtom atom = gdk_atom_intern("tree-drag", FALSE);
            while (list) {
                if ((int)atom == GPOINTER_TO_INT(list->data)) {
                    GTK_CLIST_CLASS_FW(clist)->draw_drag_highlight(clist,
                            (GtkCListRow *)g_list_nth(clist->row_list,
                                                     dest_info->cell.row)->data,
                             dest_info->cell.row, dest_info->insert_pos); 
                    break;
                }
                list = list->next;
            }
        }
        g_dataset_remove_data(context, "gtk-clist-drag-dest");
    }
}

gint list_drag_motion_internal(GtkWidget *widget, GdkDragContext *context,
                               gint x, gint y, guint time, MusicBrowserUI *p)
{
    if (widget == gtk_drag_get_source_widget(context))
        return FALSE;

    GtkCList *clist = GTK_CLIST(widget);
    GtkCListDestInfo new_info;
    GtkCListDestInfo *dest_info;

    dest_info = (GtkCListDestInfo *)g_dataset_get_data(context, 
                                                       "gtk-clist-drag-dest");
    if (!dest_info) {
        dest_info = g_new(GtkCListDestInfo, 1);
        dest_info->insert_pos = GTK_CLIST_DRAG_NONE;
        dest_info->cell.row = -1;
        dest_info->cell.column = -1;
        g_dataset_set_data_full(context, "gtk-clist-drag-dest", dest_info,
                                drag_dest_info_destroy);
    }
    drag_dest_cell(clist, x, y, &new_info);
    
    GList *list = context->targets;
    GdkAtom atom = gdk_atom_intern("tree-drag", FALSE);
    list = context->targets;
    while (list) {
        if ((int)atom == GPOINTER_TO_INT(list->data))
            break;
        list = list->next;
    }
    if (list) {
        if (new_info.insert_pos == GTK_CLIST_DRAG_NONE) {
            if (dest_info->cell.row < 0) {
                gdk_drag_status(context, GDK_ACTION_DEFAULT, time);
                return FALSE;
            }
        return TRUE;
        }
        if (new_info.cell.row != dest_info->cell.row ||
            (new_info.cell.row == dest_info->cell.row &&
             dest_info->insert_pos != new_info.insert_pos)) {
            if (dest_info->cell.row >= 0)
                GTK_CLIST_CLASS_FW(clist)->draw_drag_highlight(clist,
                        (GtkCListRow *)g_list_nth(clist->row_list, 
                                                  dest_info->cell.row)->data,
                        dest_info->cell.row, dest_info->insert_pos);
            dest_info->insert_pos = new_info.insert_pos;
            dest_info->cell.row = new_info.cell.row;
            dest_info->cell.column = new_info.cell.column;
 
            GTK_CLIST_CLASS_FW(clist)->draw_drag_highlight(clist,
                        (GtkCListRow *)g_list_nth(clist->row_list, 
                                                  dest_info->cell.row)->data,
                        dest_info->cell.row, dest_info->insert_pos);
            gdk_drag_status(context, context->suggested_action, time);
        }
        return TRUE;
    }

    dest_info->insert_pos = new_info.insert_pos;
    dest_info->cell.row = new_info.cell.row;
    dest_info->cell.column = new_info.cell.column;
    return TRUE;
}

void tree_clicked(GtkWidget *widget, GdkEventButton *event, MusicBrowserUI *p)
{
    GtkWidget *item;

    if (!event || (event->type != GDK_2BUTTON_PRESS))
        return;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_TREE(widget));
    g_return_if_fail(event != NULL);

    item = gtk_get_event_widget((GdkEvent *)event);

    while (item && !GTK_IS_TREE_ITEM(item))
        item = item->parent;
 
    if (!item || (item->parent != widget))
        return;

    vector<PlaylistItem *> *newlist = getTreeSelection(item);

    p->AddTracksPlaylistEvent(newlist);
}

static void tree_source_destroy(gpointer data)
{
}

void tree_drag_begin(GtkWidget *w, GdkDragContext *context)
{
    GList *selected = GTK_TREE_SELECTION(GTK_TREE(w));

    if (selected == NULL)
        return;

    GtkWidget *item = GTK_WIDGET(selected->data);

    if (!item && !GTK_IS_TREE_ITEM(item))
        return;

    vector<PlaylistItem *> *newlist = getTreeSelection(item);

    vector<PlaylistItem *> *test = 
         (vector<PlaylistItem *> *)g_dataset_get_data(context, 
                                                      "tree-drag-source");
    if (!test) 
        g_dataset_set_data_full(context, "tree-drag-source", newlist,
                                tree_source_destroy);
}

void tree_drag_data_get(GtkWidget *w, GdkDragContext *context,
                        GtkSelectionData *selection_data, guint info,
                        guint time, GtkWidget *widget)
{
    if (selection_data->target == gdk_atom_intern("tree-drag", FALSE)) {
        vector<PlaylistItem *> *newlist = 
                (vector<PlaylistItem *> *)g_dataset_get_data(context,
                                                             "tree-drag-source");
        gtk_selection_data_set(selection_data, selection_data->target,
                               0, (guchar *)&newlist, sizeof(vector<PlaylistItem *>*));
    }
}
        
void MusicBrowserUI::UpdateCatalog(void)
{
    m_musicCatalog = m_context->browser->m_catalog;
    GtkTargetEntry tree_target_table = {"tree-drag", 0, 1};

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
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "button_press_event",
                       GTK_SIGNAL_FUNC(tree_clicked), this);
    gtk_drag_source_set(item_subtree1, GDK_BUTTON1_MASK, &tree_target_table, 1,
                        GDK_ACTION_MOVE);
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "drag_data_get",
                       GTK_SIGNAL_FUNC(tree_drag_data_get), this);
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "drag_begin",
                       GTK_SIGNAL_FUNC(tree_drag_begin), this);

    gtk_tree_item_set_subtree(GTK_TREE_ITEM(artistSubTree), item_subtree1);

    for (; i != m_musicCatalog->m_artistList->end(); i++) {
        item_new1 = gtk_tree_item_new_with_label((char *)(*i)->name.c_str());
        gtk_object_set_user_data(GTK_OBJECT(item_new1), *i);
        gtk_object_set_data(GTK_OBJECT(item_new1), "type", (gpointer)1);
        gtk_tree_append(GTK_TREE(item_subtree1), item_new1);

        vector<AlbumList *>::iterator j = (*i)->m_albumList->begin();
        item_subtree2 = gtk_tree_new();
        gtk_tree_item_set_subtree(GTK_TREE_ITEM(item_new1), item_subtree2);
        gtk_signal_connect(GTK_OBJECT(item_subtree2), "button_press_event",
                           GTK_SIGNAL_FUNC(tree_clicked), this);
        gtk_drag_source_set(item_subtree2, GDK_BUTTON1_MASK, &tree_target_table,
                            1, GDK_ACTION_MOVE);
        gtk_signal_connect(GTK_OBJECT(item_subtree2), "drag_data_get",
                           GTK_SIGNAL_FUNC(tree_drag_data_get), this);
        gtk_signal_connect(GTK_OBJECT(item_subtree2), "drag_begin",
                           GTK_SIGNAL_FUNC(tree_drag_begin), this);

        for (; j != (*i)->m_albumList->end(); j++) {
            item_new2 = gtk_tree_item_new_with_label((char *)(*j)->name.c_str());
            gtk_object_set_user_data(GTK_OBJECT(item_new2), *j);
            gtk_object_set_data(GTK_OBJECT(item_new2), "type", (gpointer)2);
            gtk_tree_append(GTK_TREE(item_subtree2), item_new2);

            vector<PlaylistItem *>::iterator k = (*j)->m_trackList->begin();
            item_subtree3 = gtk_tree_new();
            gtk_tree_item_set_subtree(GTK_TREE_ITEM(item_new2), item_subtree3);
            gtk_signal_connect(GTK_OBJECT(item_subtree3), "button_press_event",
                               GTK_SIGNAL_FUNC(tree_clicked), this);
            gtk_drag_source_set(item_subtree3, GDK_BUTTON1_MASK, 
                                &tree_target_table, 1, GDK_ACTION_MOVE);
            gtk_signal_connect(GTK_OBJECT(item_subtree3), "drag_data_get",
                               GTK_SIGNAL_FUNC(tree_drag_data_get), this);
            gtk_signal_connect(GTK_OBJECT(item_subtree3), "drag_begin",
                               GTK_SIGNAL_FUNC(tree_drag_begin), this);

            for (;k != (*j)->m_trackList->end(); k++) {
                item_new3 = gtk_tree_item_new_with_label((char *)(*k)->GetMetaData().Title().c_str());
                gtk_object_set_user_data(GTK_OBJECT(item_new3), *k);
                gtk_object_set_data(GTK_OBJECT(item_new3), "type", (gpointer)3);
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
    gtk_signal_connect(GTK_OBJECT(item_subtree2), "button_press_event",
                       GTK_SIGNAL_FUNC(tree_clicked), this);
    gtk_drag_source_set(item_subtree2, GDK_BUTTON1_MASK, &tree_target_table, 1,
                        GDK_ACTION_MOVE);
    gtk_signal_connect(GTK_OBJECT(item_subtree2), "drag_data_get",
                       GTK_SIGNAL_FUNC(tree_drag_data_get), this);
    gtk_signal_connect(GTK_OBJECT(item_subtree2), "drag_begin",
                       GTK_SIGNAL_FUNC(tree_drag_begin), this);

    for (; l != m_musicCatalog->m_unsorted->end(); l++) {
        item_new2 = gtk_tree_item_new_with_label((char *)(*l)->URL().c_str());
        gtk_object_set_user_data(GTK_OBJECT(item_new2), *l);
        gtk_object_set_data(GTK_OBJECT(item_new2), "type", (gpointer)4);
        gtk_tree_append(GTK_TREE(item_subtree2), item_new2);
        gtk_widget_show(item_new2);
    }
    gtk_widget_show(item_new1);

    playlistSubTree = gtk_tree_item_new_with_label("Playlists");
    gtk_tree_append(GTK_TREE(musicBrowserTree), playlistSubTree);
    gtk_widget_show(playlistSubTree);
    
    item_subtree1 = gtk_tree_new();
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "button_press_event",
                       GTK_SIGNAL_FUNC(tree_clicked), this);
    gtk_drag_source_set(item_subtree1, GDK_BUTTON1_MASK, &tree_target_table, 1,
                        GDK_ACTION_MOVE);
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "drag_data_get",
                       GTK_SIGNAL_FUNC(tree_drag_data_get), this);
    gtk_signal_connect(GTK_OBJECT(item_subtree1), "drag_begin",
                       GTK_SIGNAL_FUNC(tree_drag_begin), this);

    gtk_tree_item_set_subtree(GTK_TREE_ITEM(playlistSubTree), item_subtree1);
    vector<string>::iterator m = m_musicCatalog->m_playlists->begin();

    for (; m != m_musicCatalog->m_playlists->end(); m++) {
        if (m == m_musicCatalog->m_playlists->begin()) {
            item_new1 = gtk_tree_item_new_with_label("Master Playlist");
            gtk_object_set_user_data(GTK_OBJECT(item_new1), NULL);
            gtk_object_set_data(GTK_OBJECT(item_new1), "type", (gpointer)9);
        }
        else {
            char *fullname = new char[_MAX_PATH];
            strcpy(fullname, (*m).c_str());
            char *listname = fullname;
            char *temp = strrchr(fullname, '.');
            if (temp)
                *temp = '\0';
            temp = strrchr(fullname, '/');
            if (temp)
                listname = temp + 1;
            item_new1 = gtk_tree_item_new_with_label(listname);
            delete [] fullname;
            gtk_object_set_user_data(GTK_OBJECT(item_new1), 
                                     (char *)(*m).c_str());
            gtk_object_set_data(GTK_OBJECT(item_new1), "type", (gpointer)5);
        }
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
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "FreeAmp - Music Browser");
        UpdateCatalog();
    }
    else {
        m_state = STATE_COLLAPSED;

        gtk_widget_hide(masterBrowserBox);
        gtk_label_set_text(GTK_LABEL(expandLabel), "<< Expand");
        gtk_window_set_title(GTK_WINDOW(musicBrowser), "FreeAmp - Playlist Editor");
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
    localui->ToggleVisEvent();
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

void new_list_internal(GtkWidget *widget, MusicBrowserUI *p)
{
    p->SaveCurrentPlaylist();
    p->DeleteListEvent();
    p->m_currentListName = "";

    FileSelector *filesel = new FileSelector("Choose Name for New Playlist");
    if (filesel->Run()) 
        p->ImportPlaylist(filesel->GetReturnPath());
    delete filesel;
}

void new_plist(void)
{
    new_list_internal(NULL, localui);
}

void open_list()
{
    localui->SaveCurrentPlaylist();

    FileSelector *filesel = new FileSelector("Import a Playlist from Disk");
    if (filesel->Run())
        localui->ImportPlaylist(filesel->GetReturnPath());
    delete filesel;
}

void save_list()
{
    FileSelector *filesel = new FileSelector("Save This Playlist to Disk");
    if (filesel->Run())
        localui->SaveCurrentPlaylist(filesel->GetReturnPath());
    delete filesel;
}

void about()
{
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
        char *title;
        char *artist;
        char length[50];

        if (mdata.Title() == " ") {
            char *filename = new char[_MAX_PATH];
            char *tempdir = strrchr(item->URL().c_str(), '/');
            if (tempdir)
                strcpy(filename, tempdir + 1);
            else 
                strcpy(filename, item->URL().c_str());
            tempdir = strrchr(filename, '.');
            if (tempdir)
                *tempdir = '\0';
            mdata.SetTitle(filename);
            delete [] filename;
        }
        title = (char *)mdata.Title().c_str();
        artist = (char *)mdata.Artist().c_str();
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
    GtkTargetEntry new_clist_target_table[2] = {
        {"gtk-clist-drag-reorder", 0, 0},
        {"tree-drag", 0, 1} 
    };
    GTK_CLIST_SET_FLAG(GTK_CLIST(playlistList), CLIST_REORDERABLE);
    gtk_drag_dest_set(playlistList, (GtkDestDefaults)(GTK_DEST_DEFAULT_MOTION | 
                      GTK_DEST_DEFAULT_DROP), 
                      (GtkTargetEntry *)&new_clist_target_table, 2,
                      GDK_ACTION_MOVE);
    gtk_signal_connect(GTK_OBJECT(playlistList), "drag_leave",  
                       GTK_SIGNAL_FUNC(list_drag_leave_internal), this);
    gtk_signal_connect(GTK_OBJECT(playlistList), "drag_drop", 
                       GTK_SIGNAL_FUNC(list_drag_drop_internal), this);
    gtk_signal_connect(GTK_OBJECT(playlistList), "drag_data_received",
                       GTK_SIGNAL_FUNC(list_drag_rec_internal), this);
    gtk_signal_connect(GTK_OBJECT(playlistList), "drag_motion",
                       GTK_SIGNAL_FUNC(list_drag_motion_internal), this);
    
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

void MusicBrowserUI::LoadToMaster(string &oPlaylist)
{
    if (oPlaylist.length() == 0)
        return;

    m_plm->ReadPlaylist((char *)oPlaylist.c_str());
}

void MusicBrowserUI::LoadPlaylist(string &oPlaylist)
{
    if (oPlaylist == m_currentListName) 
        return;

    SaveCurrentPlaylist(NULL);

    if (oPlaylist.length() == 0) {
        m_context->plm->SetActivePlaylist(kPlaylistKey_MasterPlaylist);
        gtk_option_menu_set_history(GTK_OPTION_MENU(playlistOMenu), 0);
    }
    else {
        m_context->plm->SetExternalPlaylist((char *)oPlaylist.c_str());
        m_context->plm->SetActivePlaylist(kPlaylistKey_ExternalPlaylist);
        SetComboSelection(oPlaylist);
    }
    m_currentListName = oPlaylist;
    m_currentindex = 0;
    UpdatePlaylistList();
}

void combo_select(GtkWidget *w, char *newPath)
{
    string Path;
    if (!newPath)
        Path = "";
    else
        Path = newPath;
    localui->LoadPlaylist(Path);
}

void MusicBrowserUI::SetComboSelection(string &oName)
{
    vector<string>::iterator i = m_context->browser->m_catalog->m_playlists->begin();
    int iIndex = 0;
    bool found = false;

    for (; i != m_context->browser->m_catalog->m_playlists->end(); i++,
          iIndex++) {
        if (!iIndex)
            continue;
        if (oName == (*i)) {
            found = true;
            break;
        }
    }
    if (!found)
        iIndex = 0;
    gtk_option_menu_set_history(GTK_OPTION_MENU(playlistOMenu), iIndex);
}

void MusicBrowserUI::UpdateCombo(void)
{
    vector<string>::iterator i = m_context->browser->m_catalog->m_playlists->begin();
    int iIndex = 0;

    if (playlistMenu)
        gtk_widget_destroy(playlistMenu);

    playlistMenu = gtk_menu_new();
    GtkWidget *menuitem = gtk_menu_item_new_with_label("Master Playlist");
    gtk_signal_connect(GTK_OBJECT(menuitem), "activate", 
                       GTK_SIGNAL_FUNC(combo_select), NULL);
    gtk_widget_show(menuitem);
    gtk_menu_append(GTK_MENU(playlistMenu), menuitem);
    
    for (; i != m_context->browser->m_catalog->m_playlists->end(); i++, 
          iIndex++) {
        if (!iIndex)
            continue;
        menuitem = gtk_menu_item_new_with_label((*i).c_str());
        gtk_signal_connect(GTK_OBJECT(menuitem), "activate", 
                           GTK_SIGNAL_FUNC(combo_select), (char *)(*i).c_str());
        gtk_widget_show(menuitem);
        gtk_menu_append(GTK_MENU(playlistMenu), menuitem);
    }
    gtk_option_menu_set_menu(GTK_OPTION_MENU(playlistOMenu), playlistMenu);
    gtk_option_menu_set_history(GTK_OPTION_MENU(playlistOMenu), 0);
}
       
void MusicBrowserUI::CreatePlaylist(void)
{
    GtkWidget *vbox;
    GtkWidget *buttonvbox;
    GtkWidget *hbox;
    GtkWidget *playlistwindow;
    GtkWidget *controlhbox;
    GtkWidget *arrow;
    GtkWidget *label;
    GtkWidget *button;

    localui = this;

    musicBrowser = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(musicBrowser), "FreeAmp - Playlist Editor");
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

    playlistOMenu = gtk_option_menu_new();
    gtk_box_pack_end(GTK_BOX(hbox), playlistOMenu, FALSE, FALSE, 10);
    gtk_widget_show(playlistOMenu);

    playlistMenu = NULL;
    UpdateCombo();

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
