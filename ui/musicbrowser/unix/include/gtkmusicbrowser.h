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

        $Id: gtkmusicbrowser.h,v 1.5 1999/10/24 04:19:57 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_GTKMUSICBROWSER_H_
#define INCLUDED_GTKMUSICBROWSER_H_

#include "config.h"

#include <gtk/gtk.h>

#include "ui.h"
#include "event.h"
#include "thread.h"
#include "playlist.h"
#include "musicbrowser.h"

class FAContext;

#define STATE_COLLAPSED 0
#define STATE_EXPANDED  1

class GTKMusicBrowser {
 public:
    GTKMusicBrowser(FAContext *, string playlistURL = string(""));
    virtual ~GTKMusicBrowser();

    void ShowPlaylist(void);
    void ShowMusicBrowser(void);
    void Close(void);
 
    bool Visible(void) { return isVisible; }
    int32 AcceptEvent(Event *e);

    uint32 m_currentindex;
    
    PlaylistSortType m_playlistColumnSort;
    int m_playlistLastSort;
    string m_currentListName;

 protected:
    FAContext *m_context;

 private:
    bool isVisible;
    void UpdatePlaylistList(void);
    void UpdateCatalog(void);

    Properties *m_propManager;

    bool m_initialized;
    bool m_browserCreated;

    PlaylistManager *m_plm;
    MusicCatalog *m_musicCatalog;
 
    int32 m_state;
	    
    /* Widget creation */
    void CreateExpanded(void);
    void CreateMenu(GtkWidget *);
    void CreatePlaylistList(GtkWidget *);
    void CreatePlaylist(void);

    GtkWidget *musicBrowser;
    GtkWidget *masterBox;
    GtkWidget *masterBrowserBox;
    GtkWidget *masterPlaylistBox;
    GtkWidget *musicBrowserWindow;
    GtkWidget *musicBrowserTree;
    GtkWidget *playlistList;
    GtkWidget *playlistOMenu;
    GtkWidget *playlistMenu;    

    void SetStatusText(const char *text);
    GtkWidget *statusBar;
    unsigned int statusContext;

    GtkWidget *artistSubTree;
    GtkWidget *playlistSubTree;
  
  public:
    /* event callbacks */
    void ReadPlaylist(char *filename, vector<PlaylistItem *> *plist);

    /* gtk-specific code in callbacl*/
    void ExpandCollapseEvent();
    void ToggleVisEvent();
    void ToggleVisEventDestroyed();

    /* no gtk specific code */
    void DeleteListEvent();
    void DeleteEvent();
    void MoveUpEvent();
    void MoveDownEvent();
    void MoveItemEvent(int source, int dest);
    void AddTrackPlaylistEvent(char *path);
    void AddTrackPlaylistEvent(PlaylistItem *newitem);
    void AddTracksPlaylistEvent(vector<PlaylistItem *> *newlist);
    void PlayEvent();
    void StartMusicSearch();
    void SortPlaylistEvent(PlaylistSortKey order, PlaylistSortType type);
    void PopUpInfoEditor();
    void SaveCurrentPlaylist(char *path = NULL);
    void LoadPlaylist(string &oPlaylist);
    void ImportPlaylist(char *path);
};

#endif
