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

        $Id: browserlist.cpp,v 1.3 2000/03/22 23:02:35 ijr Exp $
____________________________________________________________________________*/

#include "gtkmusicbrowser.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <algorithm>
using namespace std;

PlaylistManager *BADPLM = NULL;

class comp_pi_pos {
  public:
    bool operator()(PlaylistItem *a, PlaylistItem *b)
    {
        if (!BADPLM)
            return false;
        return (BADPLM->IndexOf(a) < BADPLM->IndexOf(b));
    }
};

void GTKMusicBrowser::RenumberPlaylistList(int starting)
{
    if (starting > GTK_CLIST(playlistList)->rows)
        return;

    gtk_clist_freeze(GTK_CLIST(playlistList));

    for (int i = starting; i < GTK_CLIST(playlistList)->rows; i++) {
        char location[50];

        sprintf(location, "%d", i + 1);
        gtk_clist_set_text(GTK_CLIST(playlistList), i, 0, location);
    }
    
    gtk_clist_thaw(GTK_CLIST(playlistList));
}

void GTKMusicBrowser::UpdatePlaylistItem(PlaylistItem *item)
{
    if (!item)
        return;

    uint32 pos = m_plm->IndexOf(item);

    if (pos == kInvalidIndex)
        return;

    MetaData mdata = item->GetMetaData();
    char *iText[4];
    char position[10];
    char *title;
    char *artist;
    char length[50];

    sprintf(position, "%d", pos + 1);
    title = (char *)mdata.Title().c_str();
    artist = (char *)mdata.Artist().c_str();

    if (mdata.Time() == 0)
        sprintf(length, "Unknown");
    else {
        int secs = mdata.Time();
        if (secs > 3600)
           sprintf(length, "%d:%02d:%02d", secs / 3600, (secs / 60) % 60,
                    secs % 60);
        else
            sprintf(length, "%d:%02d", (secs / 60) % 60, secs % 60);
    }

    iText[0] = position;
    iText[1] = title;
    iText[2] = artist;
    iText[3] = length;

    for (uint32 count = 0; count < 4; count++)
         gtk_clist_set_text(GTK_CLIST(playlistList), pos, count, iText[count]);
}

void GTKMusicBrowser::AddPlaylistItems(vector<PlaylistItem *> *items)
{
    if (!items)
        return;

    uint32 minpos = (uint32)-1;

    // hack hack hack hack
    BADPLM = m_plm;
    sort(items->begin(), items->end(), comp_pi_pos());
    BADPLM = NULL;

    gtk_clist_freeze(GTK_CLIST(playlistList));

    vector<PlaylistItem *>::iterator i = items->begin();
    for (; i != items->end(); i++) {
        PlaylistItem *item = *i;

       if (!item)
            continue;

        MetaData mdata = item->GetMetaData();
        char *iText[4];
        char position[10];
        char *title;
        char *artist;
        char length[50];

        uint32 pos = m_plm->IndexOf(item);

        sprintf(position, "%d", pos + 1);
        title = (char *)mdata.Title().c_str();
        artist = (char *)mdata.Artist().c_str();

        if (mdata.Time() == 0)
            sprintf(length, "Unknown");
        else {
            int secs = mdata.Time();
            if (secs > 3600)
                sprintf(length, "%d:%02d:%02d", secs / 3600, (secs / 60) % 60,
                        secs % 60);
            else
                sprintf(length, "%d:%02d", (secs / 60) % 60, secs % 60);
        }

        iText[0] = position;
        iText[1] = title;
        iText[2] = artist;
        iText[3] = length;

        gtk_clist_insert(GTK_CLIST(playlistList), pos, iText);

        if (pos < minpos)
            minpos = pos;
    }

    RenumberPlaylistList(minpos + 1);

    gtk_clist_columns_autosize(GTK_CLIST(playlistList));
    gtk_clist_select_row(GTK_CLIST(playlistList), m_currentindex, 0);
    gtk_clist_moveto(GTK_CLIST(playlistList), m_currentindex, 0, 0.5, -1);
    gtk_clist_thaw(GTK_CLIST(playlistList));
}

void GTKMusicBrowser::RemovePlaylistItems(vector<uint32> *indices)
{
    if (!indices)
        return;

    uint32 minpos = (uint32)-1;

    sort(indices->begin(), indices->end(), greater<uint32>());

    gtk_clist_freeze(GTK_CLIST(playlistList));
    vector<uint32>::iterator i = indices->begin();
    for (; i != indices->end(); i++) {
        gtk_clist_remove(GTK_CLIST(playlistList), *i);
        if (*i < minpos)
            minpos = *i;
    }

    RenumberPlaylistList(minpos);

    gtk_clist_columns_autosize(GTK_CLIST(playlistList));
    gtk_clist_select_row(GTK_CLIST(playlistList), m_currentindex, 0);
    gtk_clist_moveto(GTK_CLIST(playlistList), m_currentindex, 0, 0.5, -1);
    gtk_clist_thaw(GTK_CLIST(playlistList));
}

void GTKMusicBrowser::UpdatePlaylistList(void)
{
    if (!playlistList || !m_plm)
        return;

    gtk_clist_freeze(GTK_CLIST(playlistList));
    gtk_clist_clear(GTK_CLIST(playlistList));

    uint32 iLoop = m_plm->CountItems();

    for (uint32 i = 0; i < iLoop; i++) {
        PlaylistItem *item = m_plm->ItemAt(i);

        if (!item)
            continue;

        MetaData mdata = item->GetMetaData();
        char *iText[4];
        char position[40];
        char *title;
        char *artist;
        char length[50];

        sprintf(position, "%d", i + 1);
        title = (char *)mdata.Title().c_str();
        artist = (char *)mdata.Artist().c_str();

        if (mdata.Time() == 0)
            sprintf(length, "Unknown");
        else {
            int secs = mdata.Time();
            if (secs > 3600)
                sprintf(length, "%d:%02d:%02d", secs / 3600, (secs / 60) % 60,
                        secs % 60);
            else
                sprintf(length, "%d:%02d", (secs / 60) % 60, secs % 60);
        }

        iText[0] = position;
        iText[1] = title;
        iText[2] = artist;
        iText[3] = length;

        gtk_clist_append(GTK_CLIST(playlistList), iText);
    }

    if (iLoop == 0) {
        gtk_clist_set_column_width(GTK_CLIST(playlistList), 0, 10);
        gtk_clist_set_column_width(GTK_CLIST(playlistList), 1, 45);
        gtk_clist_set_column_width(GTK_CLIST(playlistList), 2, 45);
    }
    else
        gtk_clist_columns_autosize(GTK_CLIST(playlistList));

    gtk_clist_select_row(GTK_CLIST(playlistList), m_currentindex, 0);
    gtk_clist_moveto(GTK_CLIST(playlistList), m_currentindex, 0, 0.5, -1);
    ChangeCurrentPlayingIndex(m_playingindex, m_playingindex);
    gtk_clist_thaw(GTK_CLIST(playlistList));
}

void GTKMusicBrowser::ChangeCurrentPlayingIndex(uint32 oldindex,
                                                uint32 newindex)
{
    if (oldindex != kInvalidIndex)
        gtk_clist_set_row_style(GTK_CLIST(playlistList), oldindex, normStyle);
    gtk_clist_set_row_style(GTK_CLIST(playlistList), newindex, boldStyle);
    gtk_clist_columns_autosize(GTK_CLIST(playlistList));
}

void list_keypress(GtkWidget *w, GdkEventKey *ev, GTKMusicBrowser *p)
{
    if (ev->keyval == GDK_Delete)
        p->DeleteEvent();
}

static void playlist_row_move_internal(GtkWidget *widget, int source, int dest,
                                       GTKMusicBrowser *p)
{
    p->MoveItemEvent(source, dest);
    p->SetClickState(kContextPlaylist);
}

static void set_current_index_internal(GtkWidget *widget, int row, int column,
                                       GdkEventButton *button,
                                       GTKMusicBrowser *p)
{
    p->m_currentindex = row;
    if (button && button->type == GDK_2BUTTON_PRESS)
        p->PlayEvent();
    p->SetClickState(kContextPlaylist);
}

static gboolean list_drag_drop_internal(GtkWidget *widget,
                                        GdkDragContext *context,
                                        gint x, gint y, guint time,
                                        GTKMusicBrowser *p)
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

static void drag_dest_info_destroy(gpointer data)
{
    GtkCListDestInfo *info = (GtkCListDestInfo *)data;
    free(info);
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

static void list_drag_rec_internal(GtkWidget *widget, GdkDragContext *context,
                                   gint x, gint y, GtkSelectionData *data,
                                   guint info, guint time, GTKMusicBrowser *p)
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

            p->SetClickState(kContextPlaylist);

            g_dataset_remove_data(context, "gtk-clist-drag-dest");
        }
    }
}

static void list_drag_leave_internal(GtkWidget *widget, GdkDragContext *context,
                                     guint time, GTKMusicBrowser *p)
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

static gint list_drag_motion_internal(GtkWidget *widget,
                                      GdkDragContext *context,
                                      gint x, gint y, guint time,
                                      GTKMusicBrowser *p)
{
    if (widget == gtk_drag_get_source_widget(context))
        return FALSE;

    GtkCList *clist = GTK_CLIST(widget);
    GtkCListDestInfo new_info;
    GtkCListDestInfo *dest_info;

    dest_info = (GtkCListDestInfo *)g_dataset_get_data(context,
                                                       "gtk-clist-drag-dest");
    if (!dest_info) {
        dest_info = (GtkCListDestInfo *)malloc(sizeof(GtkCListDestInfo));
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

static void play_now_pop(GTKMusicBrowser *p, guint action, GtkWidget *w)
{
    p->PlayEvent();
}

static void move_up_pop(GTKMusicBrowser *p, guint action, GtkWidget *w)
{
    p->MoveUpEvent();
}

static void move_down_pop(GTKMusicBrowser *p, guint action, GtkWidget *w)
{
    p->MoveDownEvent();
}

static void delete_pop(GTKMusicBrowser *p, guint action, GtkWidget *w)
{
    p->DeleteEvent();
}

static void edit_pop(GTKMusicBrowser *p, guint action, GtkWidget *w)
{
    p->PopUpInfoEditor();
}

void GTKMusicBrowser::PlaylistRightClick(int x, int y, uint32 time)
{
    gtk_item_factory_popup(playlistPopup, x, y, 3, time);
}

static void list_clicked(GtkWidget *w, GdkEventButton *event,
                         GTKMusicBrowser *p)
{
    if (!event)
        return;

    g_return_if_fail(w != NULL);
    g_return_if_fail(GTK_IS_CLIST(w));
    g_return_if_fail(event != NULL);

    GtkCList *clist = GTK_CLIST(w);

    if (event->window != clist->clist_window)
        return;

    p->SetClickState(kContextPlaylist);

    if (event->button == 3) {
        int row;

        gtk_clist_get_selection_info(clist, (int)event->x, 
                                     (int)event->y, &row, NULL);
        p->m_currentindex = row;
        gtk_clist_select_row(clist, row, 0);
        p->PlaylistRightClick((int)event->x_root, 
                              (int)event->y_root,
                              event->time);
    }
}

void GTKMusicBrowser::CreatePlaylistList(GtkWidget *box)
{
    GtkItemFactoryEntry popup_items[] = {
     {"/Play Now",     NULL,      (void(*)())play_now_pop,  0, 0 },
     {"/Move Up",      NULL,      (void(*)())move_up_pop,   0, 0 },
     {"/Move Down",    NULL,      (void(*)())move_down_pop, 0, 0 },
     {"/sep1",         NULL,      0,                        0, "<Separator>" },
     {"/Remove",       NULL,      (void(*)())delete_pop,     0, 0 },
     {"/sep2",         NULL,      0,                        0, "<Separator>" },
     {"/Edit Info",    NULL,      (void(*)())edit_pop,      0, 0 }
    };
 
    int nmenu_items = sizeof(popup_items) / sizeof(popup_items[0]);
 
    static char *titles[] =
    {
      "# ", "Title", "Artist", "Length"
    };

    playlistList = gtk_clist_new_with_titles(4, titles);
    gtk_container_add(GTK_CONTAINER(box), playlistList);
    gtk_signal_connect(GTK_OBJECT(playlistList), "row_move",
                       GTK_SIGNAL_FUNC(playlist_row_move_internal), this);
    gtk_signal_connect(GTK_OBJECT(playlistList), "select_row",
                       GTK_SIGNAL_FUNC(set_current_index_internal), this);
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
    gtk_signal_connect(GTK_OBJECT(playlistList), "key_press_event",
                       GTK_SIGNAL_FUNC(list_keypress), this);
    gtk_signal_connect(GTK_OBJECT(playlistList), "button_press_event",
                       GTK_SIGNAL_FUNC(list_clicked), this);

    playlistPopup = gtk_item_factory_new(GTK_TYPE_MENU, "<plist_popup>",
                                         NULL);
    gtk_item_factory_create_items(playlistPopup, nmenu_items, popup_items, 
                                  (void *)this);

    gtk_clist_columns_autosize(GTK_CLIST(playlistList));
    gtk_widget_show(playlistList);

    m_currentindex = m_plm->GetCurrentIndex();

    UpdatePlaylistList();
}
