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

        $Id: Win32MusicBrowser.cpp,v 1.1.2.3 1999/10/13 23:08:16 robert Exp $
____________________________________________________________________________*/


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
    BOOL result = 0;
    
    switch (msg)
    {
        case WM_INITDIALOG:
        {
            break;
        }

		case WM_CLOSE:
        {
			g_ui->HideBrowser();
            break;
        }    

		case WM_SIZE:
        {
            g_ui->SizeWindow(LOWORD(lParam), HIWORD(lParam));
            break;
        } 
		case WM_NOTIFY:
            return g_ui->Notify(wParam, (LPNMHDR)lParam);
            
        case WM_SHOWWINDOW:
        {
            assert(g_ui != NULL);
            
        	g_ui->InitDialog();
        	g_ui->SetMinMaxInfo();
            break;
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
                break;
                case IDOK:
                   g_ui->HideBrowser();
                break;
                case IDC_SEARCH:
                   g_ui->StartMusicSearch();
                break;
            }    
        }        
    }

    return result;
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

    while(GetMessage(&msg,m_hWnd,0,0))
    {
        if(m_hWnd)
        {
            IsDialogMessage(m_hWnd, &msg);
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

void MusicBrowserUI::InitDialog(void)
{
    HIMAGELIST      hList;
    HMODULE         hShell;
    DWORD           dwIcon;
    TV_ITEM         sItem;
    TV_INSERTSTRUCT sInsert;
    
    hList = ImageList_Create(14, 14, ILC_COLOR8, 3, 0);
    hShell = GetModuleHandle("SHELL32.DLL");
    dwIcon = 4;     // 'Closed folder' Icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 5; 	   // 'Open folder' icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 6; 	   // 'File folder' icon (hopefully)
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
	FreeLibrary(hShell);
 
    TreeView_SetImageList(GetDlgItem(m_hWnd, IDC_MUSICTREE),
                          hList, TVSIL_NORMAL); 
                          
    sItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE; 
        
    sItem.pszText = "My Music Catalog";
    sItem.cchTextMax = lstrlen(sInsert.item.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
        
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
    
    pTreeView = (NM_TREEVIEW *)pHdr;
    
	if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
        pTreeView->itemNew.hItem == m_hPlaylistItem)
        Debug_v("Expand playlist");

	if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
        pTreeView->itemNew.hItem == m_hCatalogItem)
        Debug_v("Expand catalog");

	return 1;
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

void MusicBrowserUI::UpdatePlaylistList(void)
{
    uint32 iLoop = m_plm->CountItems();

    for (uint32 i = 0; i < iLoop; i++) 
    {
        PlaylistItem *item = m_plm->ItemAt(i);

        if (!item)
            continue;

        while (item->GetState() == kPlaylistItemState_RetrievingMetaData)
           usleep(10);

        MetaData mdata = item->GetMetaData();
        char *iText[3];

        char *title = (char *)mdata.Title().c_str();
        char *artist = (char *)mdata.Artist().c_str();
        char length[50];
        sprintf(length, "%d", mdata.Time());

        iText[0] = title;
        iText[1] = artist;
        iText[2] = length;
    }
}

void MusicBrowserUI::SetStatusText(const char *text)
{
}

void MusicBrowserUI::CreatePlaylist(void)
{
}

