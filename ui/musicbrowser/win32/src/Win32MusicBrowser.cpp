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

        $Id: Win32MusicBrowser.cpp,v 1.1.2.12 1999/10/15 23:15:14 elrod Exp $
____________________________________________________________________________*/

#include <windows.h>
#include <windowsx.h>

#include "config.h"
#include "utility.h"
#include "resource.h"
#include "Win32MusicBrowser.h"
#include "debug.h"

static HINSTANCE g_hinst = NULL;
static MusicBrowserUI *g_ui = NULL;
const int iSpacer = 15;

static int pControls[] =
{
   IDOK,
   IDC_PLAYLISTTEXT,
   IDC_MUSICCATALOGTEXT,
   IDC_MUSICTREE,
   IDC_PLAYLISTBOX,
   IDC_PLAYLISTCOMBO,
   IDC_SEARCH,        
   IDC_COLLAPSE,      
   IDC_UP,            
   IDC_DELETE,        
   IDC_ADD,           
   IDC_DOWN,          
   IDC_NEWLIST,       
   IDC_CLEARLIST,
   -1     
};   

static int pBottomControls[] =
{
   IDC_COLLAPSE,      
   IDC_SEARCH,        
   -1     
};   

static int pSideControls[] =
{
   IDC_UP,            
   IDC_DELETE,        
   IDC_ADD,           
   IDC_DOWN,          
   IDC_NEWLIST,       
   IDC_CLEARLIST,
   -1     
};   

const char* kAudioFileFilter =
            "MPEG Audio Streams (.mpg, .mp1, .mp2, .mp3, .mpp)\0"
            "*.mpg;*.mp1;*.mp2;*.mp3;*.mpp\0"
            "All Files (*.*)\0"
            "*.*\0";

bool  FileOpenDialog(HWND hwnd, 
                     const char* title,
                     const char* filter,
                     vector<char*>* fileList,
                     Preferences* prefs);

bool operator<(const TreeCrossRef &A, const TreeCrossRef &b)
{
    assert(0);
    return 0;
}
bool operator==(const TreeCrossRef &A, const TreeCrossRef &b)
{
    assert(0);
    return 0;
}

INT WINAPI DllMain (HINSTANCE hInstance,
                    ULONG ul_reason_being_called,
                    LPVOID lpReserved)
{
	switch (ul_reason_being_called)
	{
		case DLL_PROCESS_ATTACH:
			g_hinst = hInstance;
	    	break;

		case DLL_THREAD_ATTACH:
		    break;

		case DLL_THREAD_DETACH:
		    break;

		case DLL_PROCESS_DETACH:
		    break;
	}

    return 1;                 
}

static BOOL CALLBACK MainDlgProc(HWND hwnd, UINT msg, 
                                 WPARAM wParam, LPARAM lParam )
{
    switch (msg)
    {
        case WM_INITDIALOG:
        {
        	g_ui->InitDialog(hwnd);
            return 1;
        }

		case WM_CLOSE:
        {
			g_ui->HideBrowser();
            return 1;
        }    

		case WM_SIZE:
        {
            g_ui->SizeWindow(LOWORD(lParam), HIWORD(lParam));
            return 1;
        } 
		case WM_NOTIFY:
            return g_ui->Notify(wParam, (LPNMHDR)lParam);
            
        case WM_SHOWWINDOW:
        {
            assert(g_ui != NULL);
            
        	g_ui->SetMinMaxInfo();
            return 1;
		}
//		case WM_GETMINMAXINFO:
//            g_ui->GetMinMaxInfo((MINMAXINFO *)lParam);
//            break;
            
        case WM_COMMAND:
        {
        	switch(LOWORD(wParam))
            {
                case IDC_COLLAPSE:
                   g_ui->ExpandCollapseEvent();
                return 1;
                case IDOK:
                   g_ui->HideBrowser();
                return 1;
                case IDC_SEARCH:
                   g_ui->StartMusicSearch();
                return 1;
                case IDC_UP:
                   g_ui->MoveUpEvent();
                return 1;
                case IDC_DOWN:
                   g_ui->MoveDownEvent();
                return 1;
                case IDC_DELETE:
                   g_ui->DeleteEvent();
                return 1;
                case IDC_ADD:
                   g_ui->AddEvent();
                return 1;
                case IDC_NEWLIST:
                return 1;
                case IDC_CLEARLIST:
                   g_ui->DeleteListEvent();
                return 1;
                case IDC_PLAYLISTCOMBO:
                   if (HIWORD(wParam) == CBN_SELCHANGE)
                       g_ui->PlaylistComboChanged();
            }    
        }        
    }
    
    return 0;
}

Error MusicBrowserUI::CreateMainDialog(void)
{
    MSG   msg;
    
	g_ui = this;
	m_hWnd = CreateDialogParam( g_hinst, 
                    MAKEINTRESOURCE(IDD_MUSICBROWSER),
                    NULL,
                    (DLGPROC)MainDlgProc, 
                    (LPARAM)this);

    if(m_hWnd)
    {
        while(GetMessage(&msg,NULL,0,0))
        {
            if(!IsDialogMessage(m_hWnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return kError_NoErr;
}

void MusicBrowserUI::UIThreadFunc(void* arg)
{
    MusicBrowserUI* ui = (MusicBrowserUI*)arg;

    ui->CreateMainDialog();
}

Error MusicBrowserUI::CloseMainDialog(void)
{ 
    if (m_hWnd)
       DestroyWindow(m_hWnd);
	m_hWnd = NULL;
       
    return kError_NoErr;
}

void MusicBrowserUI::ShowBrowser(bool bShowExpanded)
{
	ShowWindow(m_hWnd, SW_SHOW);
    SetForegroundWindow(m_hWnd);
}

void MusicBrowserUI::HideBrowser(void)
{
	isVisible = false;
	ShowWindow(m_hWnd, SW_HIDE);
}

void MusicBrowserUI::ExpandCollapseEvent(void)
{
    RECT sControl, sWindow;
    
    GetWindowRect(m_hWnd, &sWindow);
    if (m_state == STATE_COLLAPSED)
    {
       GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sControl);
	   MoveControls(sControl.right - sControl.left + iSpacer);
       
       m_state = STATE_EXPANDED;
       SetWindowText(GetDlgItem(m_hWnd, IDC_COLLAPSE), "<< Collapse");
       SetWindowText(m_hWnd, "Music Browser");
    }            
    else
    {                
       RECT sTemp;
       
       GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sTemp);
	   MoveControls(-(sTemp.right - sWindow.left));
       m_state = STATE_COLLAPSED;
       SetWindowText(GetDlgItem(m_hWnd, IDC_COLLAPSE), "Expand >>");
       SetWindowText(m_hWnd, "Playlist Manager");
    }
       
    GetWindowRect(GetDlgItem(m_hWnd, IDC_UP), &sControl);
    SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 
    			(sControl.right - sWindow.left) + iSpacer,
                 sWindow.bottom - sWindow.top,
                 SWP_NOMOVE);
}

void MusicBrowserUI::MoveControls(int iPixelsToMove)
{
	RECT  sLoc;
    POINT sCorner;
    int  *iIndex;
    
    for(iIndex = pControls; *iIndex >= 0; iIndex++)
    {
	    GetWindowRect(GetDlgItem(m_hWnd, *iIndex), &sLoc);
        sCorner.x = sLoc.left;
        sCorner.y = sLoc.top;
        ScreenToClient(m_hWnd, &sCorner);
    	SetWindowPos(GetDlgItem(m_hWnd, *iIndex), NULL,
                     sCorner.x + iPixelsToMove,
                     sCorner.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }                 
}

void MusicBrowserUI::SizeWindow(int iWidth, int iHeight)
{
#if 0
    RECT   sRect, sClient;
    POINT  sPoint, sClientPoint;
    int   *iIndex, iSpaceLeftX, iSpaceLeftY, iCenterPost;

    GetWindowRect(m_hWnd, &sClient);
    sPoint.x = sClient.right;
    sPoint.y = sClient.bottom;
    ScreenToClient(m_hWnd, &sPoint);

	// Move the close button
    GetWindowRect(GetDlgItem(m_hWnd, IDOK), &sRect);
	SetWindowPos(GetDlgItem(m_hWnd, IDOK), NULL,
       sPoint.x - m_iXMargin - (sRect.right - sRect.left),
       sPoint.y - m_iYMargin - (sRect.bottom - sRect.top),
       0, 0, SWP_NOZORDER | SWP_NOSIZE);

    GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sRect);
    iSpaceLeftX = (sClient.right - sClient.left) - m_iXListMargin;
    iSpaceLeftY = (sClient.bottom - sRect.top) - m_iYListMargin;

	SetWindowPos(GetDlgItem(m_hWnd, IDC_MUSICTREE), NULL,
       0, 0,
       (iSpaceLeftX - (m_iLeftListMargin + m_iCenterListMargin)) / 2,
       iSpaceLeftY,
       SWP_NOMOVE | SWP_NOZORDER);

	// move the combo box
  	GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sRect);
    sClientPoint.x = sRect.right;
  	GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), &sRect);
    sClientPoint.y = sRect.top;
    ScreenToClient(m_hWnd, &sClientPoint);
	SetWindowPos(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), NULL,
       sClientPoint.x + m_iCenterListMargin, sClientPoint.y,
       (iSpaceLeftX - (m_iLeftListMargin + m_iCenterListMargin)) / 2,
       sRect.bottom - sRect.top,
       SWP_NOZORDER);

	// Move the playlistbox
  	GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sRect);
    sClientPoint.x = sRect.right;
  	GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sRect);
    sClientPoint.y = sRect.top;
    ScreenToClient(m_hWnd, &sClientPoint);
	SetWindowPos(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), NULL,
       sClientPoint.x + m_iCenterListMargin, 
       sClientPoint.y,
       (iSpaceLeftX - (m_iLeftListMargin + m_iCenterListMargin)) / 2,
       sClient.bottom - sRect.top - m_iYListMargin,
       SWP_NOZORDER);

	iCenterPost = sClientPoint.x + m_iCenterListMargin; 

	// Move search button
    GetWindowRect(GetDlgItem(m_hWnd, IDC_SEARCH), &sRect);
    sClientPoint.x = sRect.left;
    sClientPoint.y = sRect.top;
    ScreenToClient(m_hWnd, &sClientPoint);

	SetWindowPos(GetDlgItem(m_hWnd, IDC_SEARCH), NULL,
       sClientPoint.x,
       sPoint.y - m_iYMargin - (sRect.bottom - sRect.top),
       0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// Move collapse/expand button
	SetWindowPos(GetDlgItem(m_hWnd, IDC_COLLAPSE), NULL,
       iCenterPost,
       sPoint.y - m_iYMargin - (sRect.bottom - sRect.top),
       0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// Move the playlist text
    GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTTEXT), &sRect);
    sClientPoint.x = sRect.left;
    sClientPoint.y = sRect.top;
    ScreenToClient(m_hWnd, &sClientPoint);
	SetWindowPos(GetDlgItem(m_hWnd, IDC_PLAYLISTTEXT), NULL,
       iCenterPost, sClientPoint.y,
       0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// move the side controls
    for(iIndex = pSideControls; *iIndex >= 0; iIndex++)
    {
    	GetWindowRect(GetDlgItem(m_hWnd, *iIndex), &sRect);
        sClientPoint.x = sRect.left;
        sClientPoint.y = sRect.top;
        ScreenToClient(m_hWnd, &sClientPoint);
        
	    SetWindowPos(GetDlgItem(m_hWnd, *iIndex), NULL,
           sPoint.x - m_iXMargin - (sRect.right - sRect.left),
           sClientPoint.y,
           0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
#endif                     
}

void MusicBrowserUI::GetMinMaxInfo(MINMAXINFO *pInfo)
{
    pInfo->ptMaxSize.x = 10000; 
    pInfo->ptMaxSize.y = 10000; 
    pInfo->ptMaxPosition.x = 10000; 
    pInfo->ptMaxPosition.y = 10000; 
    pInfo->ptMinTrackSize = m_sMinSize;
    pInfo->ptMaxTrackSize.x = 10000; 
    pInfo->ptMaxTrackSize.y = 10000; 
}

void MusicBrowserUI::SetMinMaxInfo(void)
{
    RECT         sRect, sCloseRect, sListRect, sTreeRect;
    
    if (m_sMinSize.x >= 0)
       return;
       
    GetWindowRect(m_hWnd, &sRect);
    m_sMinSize.x = sRect.right - sRect.left;
    m_sMinSize.y = sRect.bottom - sRect.top;
    
    GetWindowRect(GetDlgItem(m_hWnd, IDOK), &sCloseRect);
    m_iXMargin = sRect.right - sCloseRect.right;
    m_iYMargin = sRect.bottom - sCloseRect.bottom;

    GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sListRect);
    m_iXListMargin = sRect.right - sListRect.right;
    m_iYListMargin = sRect.bottom - sListRect.bottom;

    GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sTreeRect);
    m_iLeftListMargin = sTreeRect.left - sRect.left;
    m_iCenterListMargin	= sListRect.left - sTreeRect.right;
}

void MusicBrowserUI::InitDialog(HWND hWnd)
{
    HIMAGELIST      hList;
    HMODULE         hShell;
    DWORD           dwIcon;
    const int32     kNumPanes = 1;
    int32           panes[kNumPanes]= {-1};

    m_hWnd = hWnd;
    
    hShell = GetModuleHandle("SHELL32.DLL");
    
    hList = ImageList_Create(16, 16, ILC_COLOR24|ILC_MASK, 3, 0);
    dwIcon = 4;     // 'Closed folder' Icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 5; 	   // 'Open folder' icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 152; 	   // 'File folder' icon (hopefully)
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
 
    TreeView_SetImageList(GetDlgItem(m_hWnd, IDC_MUSICTREE),
                          hList, TVSIL_NORMAL); 
    
    hList = ImageList_Create(16, 16, ILC_COLOR24|ILC_MASK, 1, 0);
    dwIcon = 152; 	   // 'File folder' icon (hopefully)
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
 
    ListView_SetImageList(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX),
                          hList, TVSIL_NORMAL); 
    
	FreeLibrary(hShell);
                          
    InitTree();                      
    InitList();
    FillPlaylistCombo();
    
    m_hStatus= CreateStatusWindow(WS_CHILD | WS_VISIBLE,
                                  "", m_hWnd, IDC_STATUS);

    SendMessage(m_hStatus, SB_SETPARTS, kNumPanes, (LPARAM) panes);
    m_currentindex = -1;
    UpdateButtonStates();
}

void MusicBrowserUI::InitList(void)
{
    LV_COLUMN lvc;
    RECT      sRect;
    
    SendMessage(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), CB_RESETCONTENT, 0, 0);
    ListView_DeleteAllItems(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
    GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sRect);

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
    lvc.fmt = LVCFMT_LEFT; // left align column
    lvc.cx = (sRect.right-sRect.left)*3/8; // width of column in pixels
    lvc.pszText = "Title";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 0;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 0, &lvc);
    
    lvc.pszText = "Artist";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 1;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 1, &lvc);

    lvc.pszText = "Length";
    lvc.cx = ((sRect.right-sRect.left)/4) - 3; // width of column in pixels
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 2;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 2, &lvc);
}

void MusicBrowserUI::InitTree(void)
{                          
    TV_ITEM         sItem;
    TV_INSERTSTRUCT sInsert;
    
    TreeView_DeleteAllItems(GetDlgItem(m_hWnd, IDC_MUSICTREE));
    m_oMusicCrossRefs.clear();
    
    sItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 
        
    sItem.pszText = "My Music Catalog";
    sItem.cchTextMax = lstrlen(sInsert.item.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
    sItem.lParam = 0;
        
    sInsert.item = sItem;
    sInsert.hInsertAfter = TVI_FIRST;
    sInsert.hParent = NULL;
    m_hCatalogItem = TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);

    sItem.pszText = "My Playlists";
    sItem.cchTextMax = lstrlen(sInsert.item.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
        
    sInsert.item = sItem;
    sInsert.hInsertAfter = m_hPlaylistItem;
    sInsert.hParent = NULL;
    m_hPlaylistItem = TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
}

int32 MusicBrowserUI::Notify(WPARAM command, NMHDR *pHdr)
{
	NM_TREEVIEW *pTreeView;
	NM_LISTVIEW *pListView;
    
    pTreeView = (NM_TREEVIEW *)pHdr;
    if (pTreeView->hdr.idFrom == IDC_MUSICTREE)
    {
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hPlaylistItem &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), m_hPlaylistItem) == NULL)
        {    
            FillPlaylists();
            return 0;
        }
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hCatalogItem &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), m_hCatalogItem) == NULL)
        {    
            FillArtists();
            return 0;
        }
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.lParam > 0 &&
            m_oMusicCrossRefs[pTreeView->itemNew.lParam].iLevel == 1 &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), pTreeView->itemNew.hItem) == NULL)
        {    
            FillAlbums(&pTreeView->itemNew);
            return 0;
        }
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.lParam > 0 &&
            m_oMusicCrossRefs[pTreeView->itemNew.lParam].iLevel == 2 &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), pTreeView->itemNew.hItem) == NULL)
        {    
            FillTracks(&pTreeView->itemNew);
            return 0;
        }
	    if (pTreeView->hdr.code == NM_DBLCLK)
        {
            TV_ITEM sItem;
            TV_HITTESTINFO tv_htinfo;

            GetCursorPos(&tv_htinfo.pt);

            ScreenToClient(GetDlgItem(m_hWnd, IDC_MUSICTREE), &tv_htinfo.pt);

            if(TreeView_HitTest(GetDlgItem(m_hWnd, IDC_MUSICTREE), &tv_htinfo))
            {
            
                sItem.hItem = TreeView_GetSelection(GetDlgItem(m_hWnd, IDC_MUSICTREE)); 
                sItem.mask = TVIF_PARAM | TVIF_HANDLE;
                TreeView_GetItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sItem);
        
                if (sItem.hItem != m_hPlaylistItem &&
                    sItem.hItem != m_hCatalogItem)
                {    
                    if (sItem.lParam < 0)
                    { 
                        vector<string> *p;
                        p = m_context->browser->m_catalog->m_playlists;
                        LoadPlaylist((*p)[(-sItem.lParam) - 1]);
                        SetFocus(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
                    }    
                    else    
                        if (m_oMusicCrossRefs[sItem.lParam].iLevel == 3)
                        {
                            m_context->plm->AddItem(m_oMusicCrossRefs[sItem.lParam].pTrack);
                            UpdatePlaylistList();
                        }    
                }          
            }
        }
        return 0;
    }    

    pListView = (NM_LISTVIEW *)pHdr;
    if (pListView->hdr.idFrom == IDC_PLAYLISTBOX)
    {
	    if (pListView->hdr.code == LVN_ITEMCHANGED)
        {
            m_currentindex = pListView->lParam;
            UpdateButtonStates();
        }
            
        return 0;
    }
    
	return 1;
}

void MusicBrowserUI::FillArtists(void)
{
    TV_INSERTSTRUCT                sInsert;
    vector<ArtistList *>::iterator i;
    int                            iIndex;
    TreeCrossRef                   oCrossRef;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oCrossRef.iLevel = 1;
    for(i = m_context->browser->m_catalog->m_artistList->begin(), 
        iIndex = 0; 
        i != m_context->browser->m_catalog->m_artistList->end(); 
        i++,iIndex++)
    {
       oCrossRef.pArtist = (*i);
       m_oMusicCrossRefs.push_back(oCrossRef);
       
       sInsert.item.pszText = (char *)(*i)->name.c_str();
       sInsert.item.cchTextMax = (*i)->name.length();
       sInsert.item.iImage = 0;
       sInsert.item.iSelectedImage = 1;
       sInsert.item.cChildren= 1;
       sInsert.item.lParam = m_oMusicCrossRefs.size() - 1;
       sInsert.hInsertAfter = TVI_SORT;
       sInsert.hParent = m_hCatalogItem;
       TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }    
}

void MusicBrowserUI::FillAlbums(TV_ITEM *pItem)
{
    TV_INSERTSTRUCT                sInsert;
    vector<AlbumList *>::iterator  i;
    int                            iIndex;
    TreeCrossRef                   oCrossRef, oParentRef;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oParentRef = m_oMusicCrossRefs[pItem->lParam];
    oCrossRef.iLevel = 2;
    oCrossRef.pArtist = oParentRef.pArtist;
    
    for(i = oParentRef.pArtist->m_albumList->begin(), iIndex = 0; 
        i != oParentRef.pArtist->m_albumList->end(); i++, iIndex++)
    {
        oCrossRef.pAlbum = (*i);
        m_oMusicCrossRefs.push_back(oCrossRef);
        
        if ((*i)->name == string(" ") || 
            (*i)->name.length() == 0)
            sInsert.item.pszText = "Unknown";
        else    
            sInsert.item.pszText = (char *)(*i)->name.c_str();
            
        sInsert.item.cchTextMax = (*i)->name.length();
        sInsert.item.iImage = 0;
        sInsert.item.iSelectedImage = 1;
        sInsert.item.cChildren= 1;
        sInsert.item.lParam = m_oMusicCrossRefs.size() - 1;
        sInsert.hInsertAfter = TVI_SORT;
        sInsert.hParent = pItem->hItem;
        TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }
}

void MusicBrowserUI::FillTracks(TV_ITEM *pItem)
{
    TV_INSERTSTRUCT                   sInsert;
    vector<PlaylistItem *>::iterator  i;
    int                               iIndex;
    TreeCrossRef                      oCrossRef, oParentRef;
    MetaData                          oData;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oParentRef = m_oMusicCrossRefs[pItem->lParam];
    oCrossRef.iLevel = 3;
    oCrossRef.pArtist = oParentRef.pArtist;
    oCrossRef.pAlbum = oParentRef.pAlbum;
    
    for(i = oParentRef.pAlbum->m_trackList->begin(), iIndex = 0; 
        i != oParentRef.pAlbum->m_trackList->end(); i++, iIndex++)
    {
        oCrossRef.pTrack = (*i);
        m_oMusicCrossRefs.push_back(oCrossRef);

        oData = (*i)->GetMetaData();

        if (oData.Title() == string(" ") || 
            oData.Title().length() == 0)
            sInsert.item.pszText = "Unknown";
        else    
            sInsert.item.pszText = (char *)(oData.Title().c_str());
            
        sInsert.item.cchTextMax = oData.Title().length();
        sInsert.item.iImage = 2;
        sInsert.item.iSelectedImage = 2;
        sInsert.item.cChildren= 0;
        sInsert.item.lParam = m_oMusicCrossRefs.size() - 1;
        sInsert.hInsertAfter = TVI_SORT;
        sInsert.hParent = pItem->hItem;
        TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }
}

void MusicBrowserUI::FillPlaylists(void)
{
    TV_INSERTSTRUCT          sInsert;
    vector<string>::iterator i;
    int                      iIndex;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    for(i = m_context->browser->m_catalog->m_playlists->begin(), 
        iIndex = 0; 
        i != m_context->browser->m_catalog->m_playlists->end(); 
        i++,iIndex++)
    {
       if (!iIndex) 
          continue;
          
       sInsert.item.pszText = (char *)(*i).c_str();
       sInsert.item.cchTextMax = (*i).length();
       sInsert.item.iImage = 2;
       sInsert.item.iSelectedImage = 2;
       sInsert.item.cChildren= 0;
       sInsert.item.lParam = -(iIndex+1);
       sInsert.hInsertAfter = TVI_SORT;
       sInsert.hParent = m_hPlaylistItem;
       TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }    
}

void MusicBrowserUI::PlaylistComboChanged(void)
{
    int sel;
    
    HWND hwndCombo = GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO); 
    sel = ComboBox_GetCurSel(hwndCombo);
    if (sel == 0)
        LoadPlaylist(string(""));
    else
    {
        vector<string> *p;
        p = m_context->browser->m_catalog->m_playlists;
        
        LoadPlaylist((*p)[sel]);
    }
}

void MusicBrowserUI::FillPlaylistCombo(void)
{
    vector<string>::iterator i;
    int                      iIndex;

    HWND hwndCombo = GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO); 
    ComboBox_AddString(hwndCombo, "Master Playlist");

    for(i = m_context->browser->m_catalog->m_playlists->begin(), iIndex = 0; 
        i != m_context->browser->m_catalog->m_playlists->end(); 
        i++, iIndex++)
    {
        if (!iIndex)
           continue;
        
        ComboBox_AddString(hwndCombo, (*i).c_str());
    } 
        
    ComboBox_SetCurSel(hwndCombo, 0);
}

void MusicBrowserUI::LoadPlaylist(string &oPlaylist)
{
    if (oPlaylist == m_currentListName)
       return;

    WritePlaylist();

    if (oPlaylist.length() == 0)
    {
        m_context->plm->SetActivePlaylist(kPlaylistKey_MasterPlaylist);
        ComboBox_SetCurSel(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), 0);
    }
    else
    {   
        int sel;

        m_context->plm->RemoveAll();
        m_context->plm->ReadPlaylist((char *)oPlaylist.c_str());
        sel = ComboBox_FindString(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), 0, 
                                  (char *)oPlaylist.c_str());
        ComboBox_SetCurSel(GetDlgItem(m_hWnd, IDC_PLAYLISTCOMBO), sel);
    }
        
    m_currentListName = oPlaylist;
    m_currentindex = 0;
    UpdatePlaylistList();
}

void MusicBrowserUI::WritePlaylist(void)
{
    PlaylistFormatInfo oInfo;              
    char               ext[MAX_PATH];
    int                i;
    Error              eRet = kError_NoErr;

    if (!m_bListChanged || m_currentListName.length() == 0)
       return;
    
    _splitpath(m_currentListName.c_str(), NULL, NULL, NULL, ext);
    for(i = 0; ; i++)
    {
       eRet = m_context->plm->GetSupportedPlaylistFormats(&oInfo, i);
       if (IsError(eRet))
          break;

       if (strcasecmp(oInfo.GetExtension(), ext + 1) == 0)
          break;   
    }
    if (!IsError(eRet))
        m_context->plm->WritePlaylist((char *)m_currentListName.c_str(),
                                      &oInfo);   
    m_bListChanged = false;
}

void MusicBrowserUI::UpdatePlaylistList(void)
{
    LV_ITEM       sItem;
    int           i;
    PlaylistItem *pItem;
    char          szText[100];

    ListView_DeleteAllItems(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));

    sItem.iImage = 0;
    sItem.state = sItem.stateMask = 0;
    for(i = 0; pItem = m_context->plm->ItemAt(i); i++)
    {
        while (pItem->GetState() == kPlaylistItemState_RetrievingMetaData)
           usleep(100);
           
        sItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
        sItem.pszText = (char *)pItem->GetMetaData().Title().c_str();
        sItem.cchTextMax = pItem->GetMetaData().Title().length();
        sItem.iSubItem = 0;
        sItem.iItem = i;
        sItem.lParam = i;
        ListView_InsertItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        sItem.mask = LVIF_TEXT | LVIF_IMAGE;
        sItem.pszText = (char *)pItem->GetMetaData().Artist().c_str();
        sItem.cchTextMax = pItem->GetMetaData().Artist().length();
        sItem.iSubItem = 1;
        ListView_SetItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        sprintf(szText, "%d", pItem->GetMetaData().Time());
        sItem.pszText = szText;
        sItem.cchTextMax = strlen(szText);
        sItem.iSubItem = 2;
        ListView_SetItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);
    }

    if (m_currentindex >= i)
       m_currentindex = i - 1;
        
    ListView_SetItemState(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 
                    m_currentindex, 
                    LVIS_FOCUSED|LVIS_SELECTED,
                    LVIS_FOCUSED|LVIS_SELECTED);
    SetFocus(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
    UpdateButtonStates();
}

void MusicBrowserUI::UpdateButtonStates()
{
    EnableWindow(GetDlgItem(m_hWnd, IDC_DELETE), m_currentindex != -1);
    EnableWindow(GetDlgItem(m_hWnd, IDC_UP), m_currentindex > 0);
    EnableWindow(GetDlgItem(m_hWnd, IDC_DOWN), 
                 m_currentindex < m_context->plm->CountItems() - 1);
}

void MusicBrowserUI::UpdateCatalog(void)
{
}

void MusicBrowserUI::ToggleVisEvent(void)
{
    Event *e;

    if (m_state == STATE_COLLAPSED)
        e = new Event(CMD_TogglePlaylistUI);
    else
        e = new Event(CMD_ToggleMusicBrowserUI);

    AcceptEvent(e);
    
    delete e;
}

void MusicBrowserUI::NewPlaylist(void)
{
    //SaveCurrentPlaylist();
    DeleteListEvent();
    m_currentListName = "";
}

void MusicBrowserUI::SetStatusText(const char *text)
{
}

void MusicBrowserUI::CreatePlaylist(void)
{
}


void MusicBrowserUI::AddEvent(void)
{
    vector<char*>           oFileList;
    vector<char*>::iterator i;
    Error                   eRet;

    if (FileOpenDialog(m_hWnd, "Add playlist item",
                       kAudioFileFilter, 
                       &oFileList,
                       m_context->prefs))
    {
        for(i = oFileList.begin(); i != oFileList.end(); i++)
           eRet = m_context->plm->AddItem(*i);
        m_bListChanged = true;
        UpdatePlaylistList();
    }
}

static
UINT 
APIENTRY 
OpenFileHookProc(   HWND hwnd, 
                    UINT msg, 
                    WPARAM wParam, 
                    LPARAM lParam)
{
    UINT result = 0;
    static OPENFILENAME* ofn = NULL;

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            ofn = (OPENFILENAME*)lParam;

            break;
        }

        case WM_COMMAND:
        {
            switch(wParam)
            {
                case IDC_OPEN_URL:
                {
                    char* url = new char[ofn->nMaxFile + 1];

                    if(GetDlgItemText(  hwnd,
                                        IDC_URL,
                                        url,
                                        ofn->nMaxFile))
                    {
                        *ofn->lpstrFile = 0x00;

                        if(!strstr(url, "://"))
                        {
                            strcpy(ofn->lpstrFile, "http://");
                        }

                        strcat(ofn->lpstrFile, url);

                        PostMessage(GetParent(hwnd), 
                                    WM_COMMAND, 
                                    IDCANCEL,
                                    0);

                        ofn->lCustData = 1;
                    }

                    delete url;
                    
                    result = 1;
                    break;
                }
            }

            break;
        }

        case WM_NOTIFY:
        {
            OFNOTIFY* notify = (OFNOTIFY*)lParam;

            switch(notify->hdr.code)
            {
                case CDN_FILEOK:
                {
                    
                    break;
                }
            }

            break;
        }
    }

    return result;
}

bool 
FileOpenDialog(HWND hwnd, 
               const char* title,
               const char* filter,
               vector<char*>* fileList,
               Preferences* prefs)
{
    bool result = false;
    OPENFILENAME ofn;
    char szInitialDir[MAX_PATH + 1] = {0x00};
    uint32 initialDirSize = sizeof(szInitialDir);
    const int32 kBufferSize = MAX_PATH * 128;
    char* fileBuffer = new char[kBufferSize];

    *fileBuffer = 0x00;

    if(prefs)
    {
        prefs->GetOpenSaveDirectory( szInitialDir, &initialDirSize);
    }

    // Setup open file dialog box structure
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hwnd;
    ofn.hInstance         = (HINSTANCE)GetWindowLong(hwnd, 
                                                     GWL_HINSTANCE);
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = fileBuffer;
    ofn.nMaxFile          = kBufferSize;
    ofn.lpstrFileTitle    = NULL;
    ofn.nMaxFileTitle     = 0;
    ofn.lpstrInitialDir   = szInitialDir;
    ofn.lpstrTitle        = title;
    ofn.Flags             = OFN_FILEMUSTEXIST | 
					        OFN_PATHMUSTEXIST |
  	     			        OFN_HIDEREADONLY | 
					        OFN_ALLOWMULTISELECT |
					        OFN_EXPLORER |
                            OFN_ENABLEHOOK |
                            OFN_ENABLETEMPLATE;
    ofn.nFileOffset       = 0;
    ofn.nFileExtension    = 0;
    ofn.lpstrDefExt       = "MP3";
    ofn.lCustData         = 0;
    ofn.lpfnHook          = OpenFileHookProc;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_OPENURL);

    if(GetOpenFileName(&ofn) || ofn.lCustData)
    {
        char file[MAX_PATH + 1];
        char* cp = NULL;

        if(ofn.lCustData) // URL
        {
            char* foo = new char[strlen(fileBuffer) + 1];

            strcpy(foo, fileBuffer);

            fileList->push_back(foo);
        }
        else // potential list of files
        {
            strncpy(file, fileBuffer, ofn.nFileOffset);

            if(*(fileBuffer + ofn.nFileOffset - 1) != DIR_MARKER)
                strcat(file, DIR_MARKER_STR);

            cp = fileBuffer + ofn.nFileOffset;

            while(*cp)
            {
	            strcpy(file + ofn.nFileOffset, cp);

                char* foo = new char[strlen(file) + 1];

                strcpy(foo, file);

                fileList->push_back(foo);

	            cp += strlen(cp) + 1;
            }

            *(fileBuffer + ofn.nFileOffset - 1) = 0x00;

            if(prefs)
            {
                prefs->SetOpenSaveDirectory(fileBuffer);
            }
        }

        result = true;
    }

    delete [] fileBuffer;

    return result;
}
