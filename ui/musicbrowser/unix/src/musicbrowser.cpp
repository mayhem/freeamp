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

        $Id: musicbrowser.cpp,v 1.9 1999/11/15 17:27:27 ijr Exp $
____________________________________________________________________________*/

#include "musicbrowserui.h"
#include "gtkmusicbrowser.h" 
#include "infoeditor.h"
#include "eventdata.h"

#include <algorithm>
using namespace std;

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new MusicBrowserUI(context);
}
           }

MusicBrowserUI::MusicBrowserUI(FAContext *context)
{
    m_context = context;
    searching = NULL;
}

MusicBrowserUI::~MusicBrowserUI()
{
}

Error MusicBrowserUI::Init(int32 startup_level) 
{
    if ((m_startupType = startup_level) != SECONDARY_UI_STARTUP) {
        cout << "The musicbrowser cannot run as the primary ui\n"; 
        return kError_InitFailedSafely;
    }

    if (!getenv("DISPLAY"))
        return kError_InitFailedSafely;

    m_playerEQ = m_context->target;

    m_argc = m_context->argc;
    m_argv = m_context->argv;

    gtkThread = Thread::CreateThread();
    gtkThread->Create(MusicBrowserUI::gtkServiceFunction, this);

    return kError_NoErr;
}

void MusicBrowserUI::gtkServiceFunction(void *p)
{
    assert(p);
    ((MusicBrowserUI *)p)->GTKEventService();
}

static int musicbrowser_timeout(MusicBrowserUI *p)
{
    if (p->doQuitNow)
        gtk_main_quit();
}

void MusicBrowserUI::GTKEventService(void)
{
    weAreGTK = false;
    doQuitNow = false;
 
    string URL = string("file://") + FreeampDir(NULL) + 
                 string("/currentlist.m3u");
    mainBrowser = new GTKMusicBrowser(m_context, this, URL);

    m_context->gtkLock.Acquire();
    if (!m_context->gtkInitialized) {
        m_context->gtkInitialized = true;
        g_thread_init(NULL);
        gtk_init(&m_argc, &m_argv);
        gdk_rgb_init();
        weAreGTK = true;
    }
    m_context->gtkLock.Release();

    if (weAreGTK) {
        gtk_timeout_add(250, musicbrowser_timeout, this);
        gtk_main();
        gdk_threads_leave();
    }
}

int32 MusicBrowserUI::AcceptEvent(Event *event)
{
    switch (event->Type()) {
        case CMD_Cleanup: {
            mainBrowser->Close();
            delete mainBrowser;

            vector<GTKMusicBrowser *>::iterator i = browserWindows.begin();
            for (; i != browserWindows.end(); i++) {
                (*i)->Close();
                delete (*i);
            }

            if (weAreGTK) 
                doQuitNow = true;

            if (searching)
                delete searching;

            gtkThread->Join();
            m_playerEQ->AcceptEvent(new Event(INFO_ReadyToDieUI));
            break; }
        case INFO_SearchMusicDone:
        case INFO_BrowserMessage: {
            mainBrowser->AcceptEvent(event);
            vector<GTKMusicBrowser *>::iterator i = browserWindows.begin();
            for (; i != browserWindows.end(); i++)
                (*i)->AcceptEvent(event);
            if (searching)
                searching->AcceptEvent(event);
            break; }
        case CMD_TogglePlaylistUI: {
            if (mainBrowser->Visible())
                mainBrowser->Close();
            else
                mainBrowser->ShowPlaylist();
            break; }
        case CMD_ToggleMusicBrowserUI: {
            if (mainBrowser->Visible())
                mainBrowser->Close();
            else
                mainBrowser->ShowMusicBrowser();
            break; }
        case CMD_AddFiles: {
            mainBrowser->AcceptEvent(event);
            break; }
        default:
            break;
    }
    return 0;
}

void MusicBrowserUI::CreateNewEditor(string & newPlaylist)
{
    GTKMusicBrowser *newUI = new GTKMusicBrowser(m_context, this, newPlaylist);
    gdk_threads_leave();
    newUI->ShowPlaylist();
    gdk_threads_enter();
    browserWindows.push_back(newUI);
}

void MusicBrowserUI::WindowClose(GTKMusicBrowser *oldUI)
{
    vector<GTKMusicBrowser *>::iterator
        loc = find(browserWindows.begin(), browserWindows.end(), oldUI);

    if (loc != browserWindows.end())
        browserWindows.erase(loc);
}

void MusicBrowserUI::StartSearch(bool runMain)
{
    if (searching)
        return;

    searching = new musicsearchUI(m_context);

    searching->Show(runMain);

    searching = NULL;
}
