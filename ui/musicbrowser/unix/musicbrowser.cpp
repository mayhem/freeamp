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

        $Id: musicbrowser.cpp,v 1.1.2.15 1999/10/11 22:01:23 ijr Exp $
____________________________________________________________________________*/

#include "gtkmusicbrowser.h" 
#include "eventdata.h"
#include "infoeditor.h"

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new MusicBrowserUI(context);
}
           }

MusicBrowserUI::MusicBrowserUI(FAContext *context)
{
    m_context = context;
    m_plm = NULL;
    m_browserCreated = false;
    m_initialized = false;
    m_currentindex = 0;
    m_currentListName = "";
    statusContext = 0;
    m_state = STATE_COLLAPSED;
    isVisible = false;
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

    m_argc = m_context->argc;
    m_argv = m_context->argv;
    m_plm = m_context->plm;
    m_playerEQ = m_context->target;
    m_musicCatalog = NULL;

    gtkThread = Thread::CreateThread();
    gtkThread->Create(MusicBrowserUI::gtkServiceFunction, this);

    return kError_NoErr;
}

void MusicBrowserUI::gtkServiceFunction(void *p) 
{
    assert(p);
    ((MusicBrowserUI *)p)->GTKEventService();
}

void MusicBrowserUI::GTKEventService(void)
{
    string lastPlaylist = FreeampDir(m_context->prefs);
    lastPlaylist += "/currentlist.m3u";

    LoadPlaylist((char *)lastPlaylist.c_str());

    weAreGTK = false;

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
        gtk_main();
    }
}

int32 MusicBrowserUI::AcceptEvent(Event *event)
{
    
    switch (event->Type()) {
        case CMD_Cleanup: {
            if (weAreGTK) {
                gdk_threads_enter();
                gtk_main_quit();
                gdk_threads_leave();
            }

            gtkThread->Join();
            
            string lastPlaylist = FreeampDir(m_context->prefs);
            lastPlaylist += "/currentlist.m3u";
            SaveCurrentPlaylist((char *)lastPlaylist.c_str());  

            m_playerEQ->AcceptEvent(new Event(INFO_ReadyToDieUI));

            break; }
        case INFO_SearchMusicDone: {
            if (m_initialized) {
                gdk_threads_enter();
                UpdateCatalog();
                SetStatusText("");
                gdk_threads_leave();
            }
            break; }
        case INFO_BrowserMessage: {
            if (m_initialized) {
                gdk_threads_enter();
                SetStatusText(((BrowserMessageEvent *)event)->GetBrowserMessage());
                gdk_threads_leave();
            }
            break; }
        case CMD_TogglePlaylistUI: {
            gdk_threads_enter();
            if (m_initialized && isVisible) {
                gtk_widget_hide(musicBrowser);
                isVisible = false;
            }
            else {
                isVisible = true;
                if (m_initialized)
                    gtk_widget_show(musicBrowser);
                else {
                    CreatePlaylist();
                    m_initialized = true;
                }
            }
            if (m_state == STATE_EXPANDED)
                ExpandCollapseEvent();
            gdk_threads_leave();
            break; }
        case CMD_ToggleMusicBrowserUI: {
            gdk_threads_enter();
            if (m_initialized && isVisible) {
                gtk_widget_hide(musicBrowser);
                isVisible = false;
            }
            else {
                isVisible = true;
                if (m_initialized)
                    gtk_widget_show(musicBrowser);
                else {
                    CreatePlaylist();
                    m_initialized = true;
                }
            }
            if (m_state == STATE_COLLAPSED)
                ExpandCollapseEvent();
            gdk_threads_leave();
            break; }
        default:
            break;
    }
    return 0;
}

void MusicBrowserUI::DeleteListEvent(void)
{
    m_plm->RemoveAll();
    UpdatePlaylistList();
}

void MusicBrowserUI::DeleteEvent(void)
{
    m_plm->RemoveItem(m_currentindex);
    UpdatePlaylistList();
}

void MusicBrowserUI::MoveUpEvent(void)
{
    if (m_currentindex == 0)
        return;

    m_plm->SwapItems(m_currentindex, m_currentindex - 1);
    m_currentindex--;
    UpdatePlaylistList();
}

void MusicBrowserUI::MoveDownEvent(void)
{
    if (m_currentindex == m_plm->CountItems() - 1)
        return;

    m_plm->SwapItems(m_currentindex, m_currentindex + 1);
    m_currentindex++;
    UpdatePlaylistList();
}

void MusicBrowserUI::MoveItemEvent(int source, int dest)
{
    m_plm->MoveItem(source, dest);
    UpdatePlaylistList();
}

void MusicBrowserUI::AddTrackPlaylistEvent(char *path)
{
    m_plm->AddItem(path, m_currentindex);
    UpdatePlaylistList();
}

void MusicBrowserUI::AddTrackPlaylistEvent(PlaylistItem *newitem)
{
    m_plm->AddItem(newitem, m_currentindex);
    UpdatePlaylistList();
}

void MusicBrowserUI::AddTracksPlaylistEvent(vector<PlaylistItem *> *newlist)
{
    m_plm->AddItems(newlist, m_currentindex);
    UpdatePlaylistList();
}

void MusicBrowserUI::PlayEvent(void)
{
    m_plm->SetCurrentIndex(m_currentindex);
    m_playerEQ->AcceptEvent(new Event(CMD_Play));
}

void MusicBrowserUI::StartMusicSearch(void)
{
    m_context->browser->SearchMusic(ROOT_DIR);
}

void MusicBrowserUI::SortPlaylistEvent(PlaylistSortKey order, PlaylistSortType
                                       type)
{
    if (order == kPlaylistSortKey_Random)
        m_plm->SetShuffleMode(true);
    else
        m_plm->Sort(order, type);
    UpdatePlaylistList();
}

void MusicBrowserUI::PopUpInfoEditor(void)
{
    infoeditorUI *infoedit = new infoeditorUI(m_context, 
                                              m_plm->ItemAt(m_currentindex));
    
    infoedit->DisplayInfo();
}

void MusicBrowserUI::SaveCurrentPlaylist(char *path)
{
    if (path)
        m_currentListName = path;

    if (m_currentListName == "")
        return;

    char *ext = strrchr(path, '.');
    if (ext)
        ext = ext + 1;
    Error result = kError_NoErr;
    int i = 0;
    bool found = false;

    PlaylistFormatInfo format;
    while (ext && result == kError_NoErr) {
        result = m_plm->GetSupportedPlaylistFormats(&format, i);
        if (!strcmp(ext, format.GetExtension())) {
            found = true;
            break;
        }
        i++;
    }
    if (!found) {
        m_plm->GetSupportedPlaylistFormats(&format, 0);
        m_currentListName += "." ;
        m_currentListName += format.GetExtension();
    }

    m_plm->WritePlaylist((char *)m_currentListName.c_str(), &format);
}

void MusicBrowserUI::LoadPlaylist(char *path)
{
    Error err;

    if (!path)
        return;


    err = m_plm->ReadPlaylist(path);
    if (err == kError_NoErr) {
        m_currentListName = path;
        if (m_initialized) {
            gdk_threads_enter();
            UpdatePlaylistList();
            gdk_threads_leave();
        }
    }
}
