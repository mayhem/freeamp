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

        $Id: musicbrowser.h,v 1.1.2.1 1999/09/09 01:25:35 ijr Exp $
____________________________________________________________________________*/

#ifndef _MUSICBROWSER_H_
#define _MUSICBROWSER_H_

#include <gtk/gtk.h>

#include "ui.h"
#include "event.h"
#include "thread.h"
#include "playlist.h"

class FAContext;

#define STATE_COLLAPSED 0
#define STATE_EXPANDED  1

class musicbrowserUI : public UserInterface {
 public:
    musicbrowserUI(FAContext *);
    virtual int32 AcceptEvent(Event *);
    virtual void SetArgs(int32, char **);
    virtual void SetTarget(EventQueue *eqr) { m_playerEQ = eqr; }
    virtual Error Init(int32);
    virtual void SetPlaylistManager(PlaylistManager *plm) { m_plm = plm; }
    static void gtkServiceFunction(void *);
    virtual ~musicbrowserUI();
 
    EventQueue *m_playerEQ;
    virtual Error SetPropManager(Properties *p) { m_propManager = p; if (p) return kError_NoErr; else return kError_UnknownErr; }

    uint32 m_currentindex;

 protected:
    FAContext *m_context;

 private:
    void UpdatePlaylistList(void);

    Properties *m_propManager;
    int32 m_startupType;
    bool m_noStartUp;
    void Usage();

    bool m_initialized;
    bool m_browserCreated;

    void GTKEventService(void);

    int32 m_argc;
    char **m_argv;
    void ParseArgs();

    Thread *gtkThread;

    PlaylistManager *m_plm;
 
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
    GtkWidget *musicBrowserTree;
    GtkWidget *playlistList;
    GtkWidget *expandLabel;
    
  public:
    /* event callbacks */

    /* gtk-specific code in callbacl*/
    void ExpandCollapseEvent();
    
    /* no gtk specific code */
    void DeleteListEvent();
    void DeleteEvent();
    void MoveUpEvent();
    void MoveDownEvent();
    void MoveItemEvent(int source, int dest);
    void AddTrackPlaylistEvent(char *path);
    void PlayEvent();
};

#endif
