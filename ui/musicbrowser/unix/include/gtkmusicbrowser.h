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

        $Id: gtkmusicbrowser.h,v 1.24.2.1.2.1 2000/03/04 05:33:34 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_GTKMUSICBROWSER_H_
#define INCLUDED_GTKMUSICBROWSER_H_

#include "config.h"

#include <gtk/gtk.h>

#include "ui.h"
#include "event.h"
#include "thread.h"
#include "playlist.h"
#include "musiccatalog.h"

class FAContext;
class MusicBrowserUI;

typedef enum {
    kStateCollapsed,
    kStateExpanded
} MusicBrowserView;

typedef enum {
    kContextNone,
    kContextPlaylist,
    kContextBrowser
} ClickState;

typedef enum {
    kClickNone,
    kClickPlaylist,
    kClickTrack
} TreeClickState;

typedef enum {
   kTreeMyMusic,
   kTreeAll,
   kTreeUncat,
   kTreeArtist,
   kTreeAlbum,
   kTreeTrack,
   kTreePlaylistHead,
   kTreePlaylist
} TreeNodeType;

typedef struct {
    int type;
    MusicCatalog *catalog;
    ArtistList   *artist;
    AlbumList    *album;
    PlaylistItem *track;
    string        playlistname;
    string        message;
} TreeData;

class GTKMusicBrowser {
 public:
    GTKMusicBrowser(FAContext *, MusicBrowserUI *masterUI,
                    string playlistURL = string(""));
    virtual ~GTKMusicBrowser();

    void ShowPlaylist(void);
    void ShowMusicBrowser(void);
    void Close(bool inMain = true);
 
    bool Visible(void) { return isVisible; }
    Error AcceptEvent(Event *e);

    uint32 m_currentindex;
    
    PlaylistSortType m_playlistColumnSort;
    int m_playlistLastSort;
    string m_currentListName;

    TreeData *mbSelection;
    GtkCTree *musicBrowserTree;
 
    FAContext *GetContext(void) { return m_context; }
    void UpdateCatalog(void);

    int pauseState;
    int stopState;

 private:
    FAContext *m_context;
    MusicBrowserUI *parentUI;

    bool isVisible;
    void UpdatePlaylistList(void);
    void AddPlaylistItems(vector<PlaylistItem *> *items);
    void RemovePlaylistItems(vector<uint32> *indices);
    void RenumberPlaylistList(int starting);
    void UpdatePlaylistItem(PlaylistItem *item);

    Properties *m_propManager;

    bool m_initialized;
    bool m_browserCreated;

    bool master;

    bool iSetRepeatMode;

    uint32 m_playingindex;

    PlaylistManager *m_plm;
    MusicCatalog *m_musicCatalog;
 
    MusicBrowserView m_state;
    ClickState m_clickState;
    TreeClickState m_mbState;

    int32 lastPanedPosition;
    int32 lastPanedHandle;

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
    GtkWidget *playlistList;
    GtkWidget *playlistOMenu;
    GtkWidget *playlistMenu;
    GtkWidget *addTrack;
    GtkWidget *addFile;
    GtkWidget *toolRemove;
    GtkWidget *toolUp;
    GtkWidget *toolDown;
    GtkWidget *toolbar;
    GtkItemFactory *menuFactory;

    GtkCTreeNode *mainTree;
    GtkCTreeNode *allTree;
    GtkCTreeNode *uncatTree;
    GtkCTreeNode *playlistTree;

    GtkWidget *NewPixmap(char **data);

    void SetStatusText(const char *text);
    GtkWidget *statusBar;
    unsigned int statusContext;

    GtkWidget *artistSubTree;
    GtkWidget *playlistSubTree;
  
    void UpdatePlayPause();
    TreeData *NewTreeData(int type, MusicCatalog *cat = NULL, 
                          ArtistList *art = NULL, AlbumList *alb = NULL, 
                          PlaylistItem *tr = NULL, char *pname = NULL,
                          char *message = NULL);

    void SetToolbarType();

    GtkCTreeNode *FindNode(TreeNodeType type, ArtistList *artist,
                           AlbumList *album, PlaylistItem *item,
                           GtkCTreeNode *searchFrom = NULL);
    GtkCTreeNode *FindPlaylistNode(string playlist);

    void CreateMainTreeItems(void);

    void ClearTree(void);
    void AddCatTrack(ArtistList *artist, AlbumList *album, PlaylistItem *item,
                     bool expand = false);
    void RemoveCatTrack(ArtistList *artist, AlbumList *album, 
                        PlaylistItem *item);
    void AddCatPlaylist(string playlist);
    void RemoveCatPlaylist(string playlist);
    void SetRepeatType(RepeatMode mode);
    void SetShuffleType(bool shuffled);
    bool CheckEmptyDatabase(void);
    
  public:
    bool iSetShuffleMode;

    ClickState GetClickState() { return m_clickState; }
    void SetClickState(ClickState newState);

    TreeClickState GetTreeClick() { return m_mbState; }
    void SetTreeClick(TreeClickState newState) { m_mbState = newState; }

    /* event callbacks */
    void ReadPlaylist(char *filename, vector<PlaylistItem *> *plist);

    void ExpandCollapseEvent();
    void ToggleVisEvent();

    void AddFileCMD();
    void DeleteListEvent();
    void DeleteEvent();
    void MoveUpEvent();
    void MoveDownEvent();
    void MoveItemEvent(int source, int dest);
    void AddTrackPlaylistEvent(char *path);
    void AddTrackPlaylistEvent(PlaylistItem *newitem);
    void AddTracksPlaylistEvent(vector<PlaylistItem *> *newlist, 
                                bool end = false);
    void PlayEvent();
    void StartMusicSearch(bool runMain = true, bool intro = false);
    void SortPlaylistEvent(PlaylistSortKey order, PlaylistSortType type);
    void PopUpInfoEditor(PlaylistItem *editee = NULL);
    void SaveCurrentPlaylist(char *path = NULL);
    void LoadPlaylist(string &oPlaylist);
    void ImportPlaylist(char *path);

    void CreateNewEditor(char *playlisturl);

    void ShowOptions(int page = 0);
    void StopMenu(void);
    void PlayMenu(void);
    void NextMenu(void);
    void PrevMenu(void);
    void SetRepeat(int numrepeat);
};

#endif
