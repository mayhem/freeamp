/*____________________________________________________________________________

        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 1999-2000 EMusic.com

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

        $Id: musicbrowserui.h,v 1.11 2000/02/19 06:04:58 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_MUSICBROWSERUI_H_
#define INCLUDED_MUSICBROWSERUI_H_

#include "config.h"

#include "ui.h"
#include "event.h"
#include "thread.h"
#include "playlist.h"
#include "musiccatalog.h"
#include "gtkmusicbrowser.h"
#include "musicsearchui.h"
#include "introwizard.h"

class FAContext;

class MusicBrowserUI : public UserInterface {
 public:
    MusicBrowserUI(FAContext *);
    virtual Error AcceptEvent(Event *);
    virtual Error Init(int32);
    static void gtkServiceFunction(void *);
    virtual ~MusicBrowserUI();
 
    EventQueue *m_playerEQ;

    void CreateNewEditor(string & newPlaylist);
    void WindowClose(GTKMusicBrowser *oldUI);

    void StartSearch(bool runMain = true, bool intro = false);
    void SetRunning(void);
  
    void SearchClose(void);
    void WizardClose(void);

    void DoCDCheck(void);

    bool doQuitNow;

 protected:
    FAContext *m_context;

 private:
    bool isVisible;
    bool weAreGTK;

    Properties *m_propManager;
    int32 m_startupType;

    bool m_initialized;

    void GTKEventService(void);

    int32 m_argc;
    char **m_argv;

    Thread *gtkThread;

    GTKMusicBrowser *mainBrowser;
    vector<GTKMusicBrowser *> browserWindows;

    IntroWizardUI *wiz;
    musicsearchUI *searching;
};

#endif
