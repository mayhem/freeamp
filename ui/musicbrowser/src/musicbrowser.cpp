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

        $Id: musicbrowser.cpp,v 1.1.2.7 1999/10/15 23:03:04 robert Exp $
____________________________________________________________________________*/

#ifdef WIN32
#define gdk_threads_enter() 
#define gdk_threads_leave()
#include "Win32MusicBrowser.h"
#include "debug.h"
#include "resource.h"
#else
#include "gtkmusicbrowser.h" 
#include "infoeditor.h"
#endif

#include "eventdata.h"

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new MusicBrowserUI(context);
}
           }

MusicBrowserUI::MusicBrowserUI(FAContext *context)
{
    m_context = context;
    m_initialized = false;
    isVisible = false;
    m_currentindex = 0;
    m_currentListName = "";

#ifdef HAVE_GTK
    m_state = STATE_COLLAPSED;
    m_plm = NULL;
    m_browserCreated = false;
    statusContext = 0;
#else
    m_state = STATE_EXPANDED;
    m_hWnd = NULL;    
    m_sMinSize.x = -1;
    m_bListChanged = false;
#endif
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

    m_playerEQ = m_context->target;
    m_plm = m_context->plm;

#ifdef HAVE_GTK
    m_argc = m_context->argc;
    m_argv = m_context->argv;
    m_musicCatalog = NULL;

    gtkThread = Thread::CreateThread();
    gtkThread->Create(MusicBrowserUI::gtkServiceFunction, this);

    return kError_NoErr;

#else
    m_initialized = true;
    m_uiThread = Thread::CreateThread();
    m_uiThread->Create(MusicBrowserUI::UIThreadFunc, this);
    return kError_NoErr;
#endif    
}

#ifdef HAVE_GTK
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

    if (weAreGTK)
        gtk_main();
}

#endif

int32 MusicBrowserUI::AcceptEvent(Event *event)
{
    
    switch (event->Type()) {
        case CMD_Cleanup: {
#ifdef HAVE_GTK        
            if (weAreGTK) {
                gdk_threads_enter();
                gtk_main_quit();
                gdk_threads_leave();
            }

            gtkThread->Join();
#else            
            WritePlaylist();
            CloseMainDialog();
#endif            
            
            string lastPlaylist = FreeampDir(m_context->prefs);
            lastPlaylist += "/currentlist.m3u";
            SaveCurrentPlaylist((char *)lastPlaylist.c_str());  

            m_playerEQ->AcceptEvent(new Event(INFO_ReadyToDieUI));

            break; }

#ifdef WIN32
        case INFO_PlaylistItemUpdated: {
            UpdatePlaylistList();
            break; }

#endif

        case INFO_SearchMusicDone: {
#if HAVE_GTK
            if (m_initialized) {
                gdk_threads_enter();
                UpdateCatalog();
                SetStatusText("");
                gdk_threads_leave();
            }
#else
            SendMessage(m_hStatus, SB_SETTEXT, 0, 
                        (LPARAM)"Music search completed.");
            InitTree();
            FillPlaylistCombo();
#endif                
            break; }
        case INFO_BrowserMessage: {
#if HAVE_GTK
            if (m_initialized) {
                gdk_threads_enter();
                SetStatusText(((BrowserMessageEvent *)event)->GetBrowserMessage());
                gdk_threads_leave();
            }
#else
            SendMessage(m_hStatus, SB_SETTEXT, 0, (LPARAM)
                          ((BrowserMessageEvent *)event)->GetBrowserMessage());
#endif                
            break; }
        case CMD_TogglePlaylistUI: {
            gdk_threads_enter();
            if (m_initialized && isVisible) {
#if HAVE_GTK
                gtk_widget_hide(musicBrowser);
#else

#endif                
                isVisible = false;
            }
            else {
                isVisible = true;
                if (m_initialized)
                {
#if HAVE_GTK
                    gtk_widget_show(musicBrowser);
#else
					ShowBrowser(true);
#endif                
                }
                else 
                {
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
#if HAVE_GTK
                gtk_widget_hide(musicBrowser);
#else
				HideBrowser();
#endif                
                isVisible = false;
            }
            else {
                isVisible = true;
                if (m_initialized)
                {
#if HAVE_GTK
                    gtk_widget_show(musicBrowser);
#else
					ShowBrowser(true);
#endif                
                }
                else 
                {
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
#if WIN32
    m_bListChanged = true;
#endif    
    m_plm->RemoveAll();
    UpdatePlaylistList();
}

void MusicBrowserUI::DeleteEvent(void)
{
#if WIN32
    m_bListChanged = true;
#endif    
    m_plm->RemoveItem(m_currentindex);
    UpdatePlaylistList();
}

void MusicBrowserUI::MoveUpEvent(void)
{
    if (m_currentindex == 0)
        return;

#if WIN32
    m_bListChanged = true;
#endif    

    m_plm->SwapItems(m_currentindex, m_currentindex - 1);
    m_currentindex--;
    UpdatePlaylistList();
}

void MusicBrowserUI::MoveDownEvent(void)
{
    if (m_currentindex == m_plm->CountItems() - 1)
        return;

#if WIN32
    m_bListChanged = true;
#endif    

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
#if HAVE_GTK
    m_context->browser->SearchMusic(ROOT_DIR);
#else
    DWORD  dwDrives;
    char  *szPath = "X:\\";
    int32  i, ret;

    dwDrives = GetLogicalDrives();
    for(i = 0; i < sizeof(DWORD) * 8; i++)
    {
       if (dwDrives & (1 << i))
       {
          szPath[0] = 'A' + i;
          ret = GetDriveType(szPath);
          if (ret != DRIVE_CDROM && ret != DRIVE_REMOVABLE)
             m_context->browser->SearchMusic(szPath);
       }   
    }
#endif    
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
#if HAVE_GTK
    infoeditorUI *infoedit = new infoeditorUI(m_context, 
                                              m_plm->ItemAt(m_currentindex));
    
    infoedit->DisplayInfo();
#else


#endif    
}

void MusicBrowserUI::SaveCurrentPlaylist(char *path)
{
    if (path)
        m_currentListName = path;

    if (m_currentListName == "")
        return;

    char *ext = strrchr(m_currentListName.c_str(), '.');
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

void MusicBrowserUI::ImportPlaylist(char *path)
{
    if (!path)
        return;
//    m_context->browser->m_catalog->AddPlaylist(path);
    UpdateCatalog();
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

void MusicBrowserUI::ReadPlaylist(char *path, vector<PlaylistItem *> *plist)
{
    m_plm->ReadPlaylist(path, plist);
}

