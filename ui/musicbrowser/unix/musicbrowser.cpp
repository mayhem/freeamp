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

        $Id: musicbrowser.cpp,v 1.1.2.6 1999/09/23 02:09:55 ijr Exp $
____________________________________________________________________________*/

#include "gtkmusicbrowser.h" 
#include "eventdata.h"
#include "infoeditor.h"

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new musicbrowserUI(context);
}
           }

musicbrowserUI::musicbrowserUI(FAContext *context)
{
    m_context = context;
    m_plm = NULL;
    m_noStartUp = false;
    m_browserCreated = false;
    m_currentindex = 0;
    statusContext = 0;
}

musicbrowserUI::~musicbrowserUI()
{
}


Error musicbrowserUI::Init(int32 startup_level) 
{
    if ((m_startupType = startup_level) != PRIMARY_UI) 
        return kError_InitFailedSafely;

    m_argc = m_context->argc;
    m_argv = m_context->argv;
    m_plm = m_context->plm;
    m_playerEQ = m_context->target;
    m_musicCatalog = NULL;

    gtkThread = Thread::CreateThread();
    gtkThread->Create(musicbrowserUI::gtkServiceFunction, this);

    return kError_NoErr;
}

void musicbrowserUI::gtkServiceFunction(void *p) 
{
    assert(p);
    ((musicbrowserUI *)p)->GTKEventService();
}

void musicbrowserUI::ParseArgs(void)
{
/* Most of this is temporary, and shouldn't be here */
    char *arg = NULL;
 
    for (int32 i = 1; i < m_argc; i++) {
        arg = m_argv[i];
        if (m_startupType == PRIMARY_UI) 
            m_plm->AddItem(arg, 0);
    }
    if (m_startupType == PRIMARY_UI)
        m_plm->SetCurrentIndex(0); 
}

void musicbrowserUI::GTKEventService(void)
{
    g_thread_init(NULL);

    gtk_init(&m_argc, &m_argv);

    ParseArgs();

    CreatePlaylist();

    gtk_main();

    if (m_startupType == PRIMARY_UI)
        m_playerEQ->AcceptEvent(new Event(CMD_QuitPlayer));
}

void musicbrowserUI::Usage(void)
{
    cout << "FreeAmp MusicBrowser UI Plugin usage: " << endl;
    cout << " NONE! You don't use this, really. " << endl;
    cout << endl;
}

int32 musicbrowserUI::AcceptEvent(Event *event)
{
    switch (event->Type()) {
        case CMD_Cleanup: {
            gtkThread->Join();
            m_playerEQ->AcceptEvent(new Event(INFO_ReadyToDieUI));
            break; }
        case INFO_SearchMusicDone: {
            gdk_threads_enter();
            UpdateCatalog();
            SetStatusText("");
            gdk_threads_leave();
            break; }
        case INFO_BrowserMessage: {
            gdk_threads_enter();
            SetStatusText(((BrowserMessageEvent *)event)->GetBrowserMessage());
            gdk_threads_leave();
            break; }
        default:
            break;
    }
    return 0;
}

void musicbrowserUI::DeleteListEvent(void)
{
    m_plm->RemoveAll();
    UpdatePlaylistList();
}

void musicbrowserUI::DeleteEvent(void)
{
    m_plm->RemoveItem(m_currentindex);
    UpdatePlaylistList();
}

void musicbrowserUI::MoveUpEvent(void)
{
    if (m_currentindex == 0)
        return;

    m_plm->SwapItems(m_currentindex, m_currentindex - 1);
    m_currentindex--;
    UpdatePlaylistList();
}

void musicbrowserUI::MoveDownEvent(void)
{
    if (m_currentindex == m_plm->CountItems() - 1)
        return;

    m_plm->SwapItems(m_currentindex, m_currentindex + 1);
    m_currentindex++;
    UpdatePlaylistList();
}

void musicbrowserUI::MoveItemEvent(int source, int dest)
{
    m_plm->MoveItem(source, dest);
    UpdatePlaylistList();
}

void musicbrowserUI::AddTrackPlaylistEvent(char *path)
{
    m_plm->AddItem(path, m_currentindex);
    UpdatePlaylistList();
}

void musicbrowserUI::PlayEvent(void)
{
    m_plm->SetCurrentIndex(m_currentindex);
    m_playerEQ->AcceptEvent(new Event(CMD_Play));
}

void musicbrowserUI::StartMusicSearch(void)
{
    m_context->browser->SearchMusic(ROOT_DIR);
}

void musicbrowserUI::SortPlaylistEvent(PlaylistSortKey order, PlaylistSortType
                                       type)
{
    if (order == kPlaylistSortKey_Random)
        m_plm->SetShuffleMode(true);
    else
        m_plm->Sort(order, type);
    UpdatePlaylistList();
}

void musicbrowserUI::PopUpInfoEditor(void)
{
    infoeditorUI *infoedit = new infoeditorUI(m_context, 
                                              m_plm->ItemAt(m_currentindex));
    
    infoedit->DisplayInfo();
}

