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

        $Id: musicbrowser.cpp,v 1.1.2.1 1999/09/09 01:25:35 ijr Exp $
____________________________________________________________________________*/

#include "musicbrowser.h" 
#include "event.h"

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
}

musicbrowserUI::~musicbrowserUI()
{
}


Error musicbrowserUI::Init(int32 startup_level) 
{
    if ((m_startupType = startup_level) != PRIMARY_UI) 
        return kError_InitFailedSafely;

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
/* Most of this is temporary */
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
    gtk_init(&m_argc, &m_argv);

    ParseArgs();

    CreatePlaylist();

    gtk_main();

    if (m_startupType == PRIMARY_UI)
        m_playerEQ->AcceptEvent(new Event(CMD_QuitPlayer));
}

void musicbrowserUI::SetArgs(int argc, char **argv)
{
    m_argc = argc;
    m_argv = argv;
    // delay arg parsing till later, except for looking for -h and --help
    // if found, set m_noStartUp to true and send the QuitPlayer message...
    for (int i = 0;i < m_argc;i++) {
        if (m_argv[i][0] == '-') {
            if ((m_argv[i][1] == 'h') || (m_argv[i][1] == 'H') ||
                !strcmp(&(m_argv[i][1]),"-help")) {
                m_noStartUp = true;
                Usage();
                m_playerEQ->AcceptEvent(new Event(CMD_QuitPlayer));
            }

        }
    }
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
