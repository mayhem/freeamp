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

        $Id: Win32MusicBrowser.cpp,v 1.6 1999/10/25 09:58:28 elrod Exp $
____________________________________________________________________________*/

#include <windows.h>
#include <windowsx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

#include "config.h"
#include "utility.h"
#include "resource.h"
#include "Win32MusicBrowser.h"
#include "debug.h"

static HINSTANCE g_hinst = NULL;
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
   IDC_UP,            
   IDC_DELETE,        
   IDC_ADD,           
   IDC_DOWN,          
   IDC_NEWLIST,       
   IDC_CLEARLIST,
   -1     
};   

#define DB Debug_v("%d", __LINE__);
#define WM_EMPTYDBCHECK WM_USER + 69

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
void ClientToWindow(HWND hWnd, POINT *Pt); 

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
    MusicBrowserUI* ui = (MusicBrowserUI*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (msg)
    {
        case WM_INITDIALOG:
        {
            ui = (MusicBrowserUI*)lParam;
            assert(ui != NULL);
            SetWindowLong(hwnd, GWL_USERDATA, (LONG)ui);
            
        	ui->InitDialog(hwnd);
        	ui->SetMinMaxInfo();
            return 1;
        }

		case WM_CLOSE:
        {
			ui->Close();
            return 1;
        }    

		case WM_SIZE:
        {
            ui->SizeWindow(LOWORD(lParam), HIWORD(lParam));
            return 1;
        } 
		case WM_NOTIFY:
            return ui->Notify(wParam, (LPNMHDR)lParam);
            
//		case WM_GETMINMAXINFO:
//            ui->GetMinMaxInfo((MINMAXINFO *)lParam);
//            break;

        case WM_MOUSEMOVE:
        {
            POINT sPoint;   
            sPoint.x = LOWORD(lParam);
            sPoint.y = HIWORD(lParam);  
            ui->MouseMove((uint32)wParam, sPoint);
            return 1;
        }
        case WM_LBUTTONUP:
            ui->MouseButtonUp();
            return 1;
            
        case WM_EMPTYDBCHECK:
            ui->EmptyDBCheck();
            return 1;
            
        case WM_COMMAND:
        {
        	switch(LOWORD(wParam))
            {
                case IDC_COLLAPSE:
                   ui->ExpandCollapseEvent();
                return 1;
                case ID_FILE_SEARCHFORMUSIC:
                case IDC_SEARCH:
                   ui->StartMusicSearch();
                return 1;
                case ID_EDIT_MOVEUP:
                case IDC_UP:
                   ui->MoveUpEvent();
                return 1;
                case ID_EDIT_MOVEDOWN:
                case IDC_DOWN:
                   ui->MoveDownEvent();
                return 1;
                case IDC_DELETE:
                   ui->DeleteEvent();
                return 1;
                case ID_EDIT_ADDTRACK:
                case IDC_ADD:
                   ui->AddEvent();
                return 1;
                case ID_EDIT_CLEARPLAYLIST:
                case IDC_CLEARLIST:
                   ui->DeleteListEvent();
                return 1;
                case ID_VIEW_MUSICCATALOG:
                   ui->ExpandCollapseEvent();
                return 1;
                case ID_FILE_OPENPLAYLIST:
                   ui->OpenPlaylist();
                return 1;
                case ID_FILE_EXIT:
                   ui->Close();
                return 1;
                case ID_FILE_SAVEPLAYLIST:
                   ui->WritePlaylist();
                return 1;
                case ID_FILE_SAVEASPLAYLIST:
                   ui->SaveAsPlaylist();
                return 1;
                case IDC_NEWLIST:
                case ID_FILE_NEWPLAYLIST:
                   ui->NewPlaylist();
                return 1;
                case ID_SORT_ARTIST:
                case ID_SORT_ALBUM:
                case ID_SORT_TITLE:
                case ID_SORT_LENGTH:
                case ID_SORT_YEAR:
                case ID_SORT_TRACK:
                case ID_SORT_GENRE:
                case ID_SORT_LOCATION:
                case ID_SORT_RANDOMIZE:
                case IDC_RANDOMIZE:
                   ui->SortEvent(LOWORD(wParam));
                return 1;
                case ID_EDIT_EDIT:
                   ui->EditEvent();
                return 1;
                case ID_EDIT_REMOVE:
                   ui->RemoveEvent();
                return 1;
                case ID_EDIT_REMOVEFROMDISK:
                   ui->RemoveFromDiskEvent();
                return 1;
                case ID_FILE_IMPORT:
                   ui->ImportEvent();
                return 1;
            }    
        }     

        case WM_DRAWITEM:
        {
            return ui->DrawItem(wParam, (DRAWITEMSTRUCT*) lParam);

            break;
        }
        
        case WM_MEASUREITEM:
        {
            MEASUREITEMSTRUCT* mis = (MEASUREITEMSTRUCT*) lParam;
            TEXTMETRIC tm;
            HDC hdc;
	        HFONT hFont;
	        HWND hwndLV;


            // Make sure the control is the listview control
            if (mis->CtlType != ODT_LISTVIEW || mis->CtlID == IDC_PLAYLISTBOX)
                return FALSE;

	        // Get the handle of the ListView control we're using
	        hwndLV = GetDlgItem(hwnd, mis->CtlID);

	        // Get the font the control is currently using
	        hFont = (HFONT)(DWORD) SendMessage(hwndLV, WM_GETFONT, 0, 0L);

	        // Set the font of the DC to the same font the control is using
            hdc = GetDC(hwndLV);
	        SelectObject(hdc, hFont);

            // Get the height of the font used by the control
            if (!GetTextMetrics(hdc, &tm))
                return FALSE;

            // Add a little extra space between items
            mis->itemHeight = tm.tmHeight + 1;

            // Make sure there is enough room for the images which are CY_SMICON high
            if (mis->itemHeight < 17)
    	        mis->itemHeight = 17;

	        // Clean up
	        ReleaseDC(hwndLV, hdc);

            return TRUE;

            break;
        }

    }
    
    return 0;
}

bool MusicBrowserUI::CreateMainDialog(void)
{
    MSG   msg;

	m_hWnd = CreateDialogParam( g_hinst, 
                    MAKEINTRESOURCE(IDD_MUSICBROWSER),
                    NULL,
                    (DLGPROC)MainDlgProc, 
                    (LPARAM)this);
    if(m_hWnd)
    {
        if (m_pParent)
        {
            RECT sRect;
            
            GetWindowRect(m_hParent, &sRect);
            SetWindowPos(m_hWnd, NULL, sRect.left + 20, sRect.top + 20,
                         0, 0, SWP_NOZORDER|SWP_NOSIZE);
            ShowWindow(m_hWnd, SW_NORMAL);
            UpdateWindow(m_hWnd);
        }    
        while(GetMessage(&msg,NULL,0,0))
        {
            if(!IsDialogMessage(m_hWnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    
    ImageList_Destroy(TreeView_SetImageList(
                      GetDlgItem(m_hWnd, IDC_MUSICTREE),
                          NULL, TVSIL_NORMAL)); 
    ImageList_Destroy(ListView_SetImageList(
                      GetDlgItem(m_hWnd, IDC_PLAYLISTBOX),
                          NULL, LVSIL_SMALL)); 
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;

    if (m_pParent)
    {
       m_pParent->RemoveMusicBrowserWindow(this);
       return true;
    }
    
    return false;
}

void MusicBrowserUI::UIThreadFunc(void* arg)
{
    MusicBrowserUI* ui = (MusicBrowserUI*)arg;

    if (ui->CreateMainDialog())
       delete ui;
}

Error MusicBrowserUI::CloseMainDialog(void)
{ 
    if (m_pParent)
    {
       if (m_bListChanged)
       {
           ShowWindow(m_hWnd, SW_RESTORE);
           SetForegroundWindow(m_hWnd);
           if (MessageBox(m_hWnd, "Would you like to save this playlist?",
                          BRANDING, MB_YESNO) == IDYES)
              WritePlaylist();
       }    
    }
    else      
       if (m_bListChanged)
           WritePlaylist();

    m_bListChanged = false;   
    PostMessage(m_hWnd, WM_QUIT, 0, 0);
       
    return kError_NoErr;
}

void MusicBrowserUI::ShowBrowser(bool bShowExpanded)
{
    PostMessage(m_hWnd, WM_EMPTYDBCHECK, 0, 0);
    ShowWindow(m_hWnd, SW_RESTORE);
	ShowWindow(m_hWnd, SW_SHOW);
    SetForegroundWindow(m_hWnd);
}

void MusicBrowserUI::HideBrowser(void)
{
	isVisible = false;
	ShowWindow(m_hWnd, SW_HIDE);
}

void MusicBrowserUI::Close(void)
{
    if (m_pParent == NULL)
    {
       HideBrowser();
    }   
    else
       CloseMainDialog();
}

void MusicBrowserUI::ExpandCollapseEvent(void)
{
    RECT         sWindow;
    HMENU        hMenu;
    MENUITEMINFO sItem;
    
    GetWindowRect(m_hWnd, &sWindow);
    if (m_state == STATE_COLLAPSED)
    {
       m_state = STATE_EXPANDED;
       SetWindowText(GetDlgItem(m_hWnd, IDC_COLLAPSE), "<< Collapse");
       SetWindowText(m_hWnd, "Music Browser");
       sItem.dwTypeData = "View &playlist only";
       
       SetWindowPos(m_hWnd, NULL, 0, 0, 
        			(sWindow.right - sWindow.left) + m_iCollapseMoveAmount,
                    sWindow.bottom - sWindow.top,
                    SWP_NOMOVE);
       
	   MoveControls(m_iCollapseMoveAmount);
    }            
    else
    {                
       m_state = STATE_COLLAPSED;
       SetWindowText(GetDlgItem(m_hWnd, IDC_COLLAPSE), "Expand >>");
       SetWindowText(m_hWnd, "Playlist Manager");
       sItem.dwTypeData = "View &music browser";
       
       SetWindowPos(m_hWnd, NULL, 0, 0, 
        			(sWindow.right - sWindow.left) - m_iCollapseMoveAmount,
                    sWindow.bottom - sWindow.top,
                    SWP_NOMOVE);
       
	   MoveControls(-m_iCollapseMoveAmount);
    }

    hMenu = GetMenu(m_hWnd);
    hMenu = GetSubMenu(hMenu, 2);
    sItem.cbSize = sizeof(MENUITEMINFO);
    sItem.fMask = MIIM_TYPE;
    sItem.fType = MFT_STRING;
    sItem.cch = strlen(sItem.dwTypeData);
    SetMenuItemInfo(hMenu, ID_VIEW_MUSICCATALOG, false, &sItem);
    
    SendMessage(m_hStatus, SB_SETTEXT, 0, (LPARAM)"");
    InvalidateRect(m_hWnd, NULL, true);
    UpdateWindow(m_hWnd);
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
	RECT  sLoc, sLoc2;
    
	GetWindowRect(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sLoc);
	GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sLoc2);
    m_iCollapseMoveAmount = sLoc2.left - sLoc.left;
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
    
    hList = ImageList_Create(16, 16, ILC_COLOR24|ILC_MASK, 4, 0);
    dwIcon = 4;     // 'Closed folder' Icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 5; 	   // 'Open folder' icon
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    dwIcon = 152; 	   // 'File folder' icon (hopefully)
    ImageList_AddIcon(hList, LoadIcon(hShell, MAKEINTRESOURCE(dwIcon)));
    ImageList_AddIcon(hList, LoadIcon(g_hinst, MAKEINTRESOURCE(IDI_ACTIVELIST)));
 
    TreeView_SetImageList(GetDlgItem(m_hWnd, IDC_MUSICTREE),
                          hList, TVSIL_NORMAL); 
	FreeLibrary(hShell);
    
    hList = ImageList_Create(16, 16, ILC_COLOR24|ILC_MASK, 1, 0);

    HBITMAP bmp = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_PLAYING));
    ImageList_AddMasked(hList, bmp, RGB(255,0,0));
    DeleteObject(bmp);
 
    ListView_SetImageList(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX),
                          hList, LVSIL_SMALL); 

    if (m_pParent == NULL)
    {
//       string lastPlaylist = FreeampDir(m_context->prefs);
//       lastPlaylist += "\\currentlist.m3u";
//       LoadPlaylist(lastPlaylist);
        m_oPlm->SetActivePlaylist(kPlaylistKey_MasterPlaylist);
    }   
    else   
    {
        char   url[MAX_PATH];
        uint32 len = MAX_PATH;
        FilePathToURL(m_currentListName.c_str(), url, &len);
        m_oPlm->SetActivePlaylist(kPlaylistKey_ExternalPlaylist);
        LoadPlaylist(url);
    }   

    InitTree();                      
    InitList();
    SetTitles();
    
    m_hStatus= CreateStatusWindow(WS_CHILD | WS_VISIBLE,
                                  "", m_hWnd, IDC_STATUS);

    SendMessage(m_hStatus, SB_SETPARTS, kNumPanes, (LPARAM) panes);
    m_currentindex = -1;
    UpdateButtonStates();
    
    if (m_pParent)
        ShowWindow(m_hWnd, SW_SHOW);
}

#define kPrePadding 5

BOOL MusicBrowserUI::DrawItem(int32 controlId, DRAWITEMSTRUCT* dis)
{
    BOOL result = TRUE;

    switch(controlId)
    {
        case IDC_PLAYLISTBOX:
        {
            uint32 uiFlags = ILD_TRANSPARENT;
            RECT rcClip;
            HIMAGELIST himl;
            int32 cxImage = 0, cyImage = 0;

            // Get Image List
            himl = ListView_GetImageList(dis->hwndItem, LVSIL_SMALL);
            ImageList_GetIconSize(himl, &cxImage, &cyImage);

            // Check to see if this item is selected
            if(dis->itemState & ODS_SELECTED)
            {
                // Set the text background and foreground colors
                SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
                SetBkColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHT));

		        // Also add the ILD_BLEND50 so the images come out selected
		        //uiFlags |= ILD_BLEND50;
            }
            else
            {
                // Set the text background and foreground colors to the
                // standard window colors
                SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
            }

            rcClip = dis->rcItem;   
        
            HWND hwndList = GetDlgItem(m_hWnd, IDC_PLAYLISTBOX);
            LV_ITEM lv_item;
            char* buf = new char[1024]; // MS is so dumb they do not give you a way to query text length
            string displayString;

            lv_item.mask = LVIF_TEXT;
            lv_item.state = 0;
            lv_item.stateMask = 0;
            lv_item.iItem = dis->itemID;
            lv_item.iSubItem = 0;
            lv_item.pszText = buf;
            lv_item.cchTextMax = 2;
            lv_item.lParam = NULL;

            // Item index
            ListView_GetItemText(hwndList, dis->itemID, 0, buf, 1024);
            displayString = buf;

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(hwndList, 0) - (cxImage + 1));

            ExtTextOut( dis->hDC, 
                        rcClip.left + cxImage + 2, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // Draw the icon. Drawing it after the first item allows us
            // to let ExtTextOut draw the correct background 
            if(himl && dis->itemID == m_oPlm->GetCurrentIndex())
            {
                uint32 top = rcClip.top + ((rcClip.bottom - rcClip.top) - cyImage)/2;
                ImageList_Draw( himl, 0, dis->hDC, 
                                rcClip.left, top,
                                uiFlags);
            }

            // Move over to the next column
            rcClip.left += ListView_GetColumnWidth(hwndList, 0);

            // Title
            ListView_GetItemText(hwndList, dis->itemID, 1, buf, 1024);
            displayString = buf;

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(hwndList, 1) - kPrePadding);

            ExtTextOut( dis->hDC, 
                        rcClip.left + kPrePadding, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // Move over to the next column
            rcClip.left += ListView_GetColumnWidth(hwndList, 1);

            // Artist
            ListView_GetItemText(hwndList, dis->itemID, 2, buf, 1024);
            displayString = buf;

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(hwndList, 2) - kPrePadding);

            ExtTextOut( dis->hDC, 
                        rcClip.left + kPrePadding, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // Move over to the next column
            rcClip.left += ListView_GetColumnWidth(hwndList, 2);

            // Album
            ListView_GetItemText(hwndList, dis->itemID, 3, buf, 1024);

            displayString = buf;

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(hwndList, 3) - kPrePadding);

            ExtTextOut( dis->hDC, 
                        rcClip.left + kPrePadding, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // Move over to the next column
            rcClip.left += ListView_GetColumnWidth(hwndList, 3);

            // Length
            ListView_GetItemText(hwndList, dis->itemID, 4, buf, 1024);

            displayString = buf;

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(hwndList, 4) - kPrePadding);

            ExtTextOut( dis->hDC, 
                        rcClip.left + kPrePadding, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // Move over to the next column
            rcClip.left += ListView_GetColumnWidth(hwndList, 4);


            // If we changed the colors for the selected item, undo it
            if(dis->itemState & ODS_SELECTED)
            {
                // Set the text background and foreground colors
                SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
            }

            // If the item is focused draw a focus rect around the entire row
            if(dis->itemState & ODS_FOCUS)
            {
                // Draw the focus rect
                DrawFocusRect(dis->hDC, &dis->rcItem);
            }

            break;
        }


    }

    return result;
}

void MusicBrowserUI::SetTitles(void)
{
    if (m_pParent == NULL)
    {
       SetWindowText(GetDlgItem(m_hWnd, IDC_PLAYLISTTITLE), 
                     "Currently listening to:");
       SetWindowText(m_hWnd, 
                     "Music Catalog: Current listening list");
    }   
    else
    {
       string oTitle, oName;
       
       if (m_currentListName.length() == 0)
          oName = "New Playlist";
       else
       {
          char szBase[MAX_PATH];
       
          _splitpath(m_currentListName.c_str(), NULL, NULL, szBase, NULL);
          oName = szBase;
       }
       
       oTitle = string("Editing playlist: ") + oName;
       SetWindowText(GetDlgItem(m_hWnd, IDC_PLAYLISTTITLE), 
                     oTitle.c_str());
       oTitle = string("Music Catalog editing playlist: ") + oName;
       SetWindowText(m_hWnd, oTitle.c_str());
    }   
}

void MusicBrowserUI::InitList(void)
{
    LV_COLUMN lvc;
    RECT      sRect;
    
    ListView_DeleteAllItems(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
    GetWindowRect(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sRect);

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
    lvc.fmt = LVCFMT_LEFT; // left align column

    lvc.pszText = "#";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 0;
    lvc.cx = (sRect.right-sRect.left)/8; // width of column in pixels
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 0, &lvc);

    lvc.pszText = "Title";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 1;
    lvc.cx = (sRect.right-sRect.left)*3/8; // width of column in pixels
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 1, &lvc);
    
    lvc.pszText = "Artist";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 2;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 2, &lvc);

    lvc.pszText = "Album";
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 3;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 3, &lvc);

    lvc.pszText = "Length";
    lvc.cx = ((sRect.right-sRect.left)/4) - 3; // width of column in pixels
    lvc.cchTextMax = strlen(lvc.pszText);
    lvc.iSubItem = 4;
    ListView_InsertColumn(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), 4, &lvc);
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
    sItem.cchTextMax = lstrlen(sItem.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
    sItem.lParam = 0;
        
    sInsert.item = sItem;
    sInsert.hInsertAfter = TVI_FIRST;
    sInsert.hParent = NULL;
    m_hCatalogItem = TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);

    sItem.pszText = "<All>";
    sItem.cchTextMax = lstrlen(sItem.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
    sItem.lParam = 0;
        
    sInsert.item = sItem;
    sInsert.hInsertAfter = TVI_FIRST;
    sInsert.hParent = m_hCatalogItem;
    m_hAllItem = TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);

    sItem.pszText = "<Uncategorized>";
    sItem.cchTextMax = lstrlen(sItem.pszText);
    sItem.iImage = 0;
    sItem.iSelectedImage = 1;
    sItem.cChildren= 1;
    sItem.lParam = 0;
        
    sInsert.item = sItem;
    sInsert.hInsertAfter = TVI_LAST;
    sInsert.hParent = m_hCatalogItem;
    m_hUncatItem = TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);

    sItem.pszText = "My Playlists";
    sItem.cchTextMax = lstrlen(sItem.pszText);
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
//	    if (pTreeView->hdr.code == TVN_BEGINDRAG &&
//            pTreeView->itemNew.lParam >= 0 &&
//            m_oMusicCrossRefs.size() > 0 &&
//            m_oMusicCrossRefs[pTreeView->itemNew.lParam].iLevel == 3)
//        {
//            TreeView_SelectItem(GetDlgItem(m_hWnd, IDC_MUSICTREE),
//                                pTreeView->itemNew.hItem);
//
//            BeginDrag(pTreeView);
//            return 0;
//        }    
 
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hPlaylistItem)
        {    
            if (TreeView_GetChild(GetDlgItem(m_hWnd, IDC_MUSICTREE), 
                m_hPlaylistItem) == NULL)
            {    
                FillPlaylists();
                return 0;
            }
            return 0;
        }    

	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hAllItem)
        {    
            if (TreeView_GetChild(GetDlgItem(m_hWnd, IDC_MUSICTREE), 
                m_hAllItem) == NULL)
            {    
                FillAllTracks();
                return 0;
            }
            return 0;
        }    

	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hUncatItem)
        {    
            if (TreeView_GetChild(GetDlgItem(m_hWnd, IDC_MUSICTREE), 
                m_hUncatItem) == NULL)
            {    
                FillUncatTracks();
                return 0;
            }
            return 0;
        }    
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.hItem == m_hCatalogItem)
        { 
            if (TreeView_GetNextSibling(GetDlgItem(m_hWnd, IDC_MUSICTREE), 
                m_hUncatItem) == NULL)
            {    
                FillArtists();
                return 0;
            }
            return 0;
        }    
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.lParam >= 0 &&
            m_oMusicCrossRefs[pTreeView->itemNew.lParam].iLevel == 1 &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), pTreeView->itemNew.hItem) == NULL)
        {    
            FillAlbums(&pTreeView->itemNew);
            return 0;
        }
        
	    if (pTreeView->hdr.code == TVN_ITEMEXPANDING && 
            pTreeView->itemNew.lParam >= 0 &&
            m_oMusicCrossRefs[pTreeView->itemNew.lParam].iLevel == 2 &&
            TreeView_GetChild(
            GetDlgItem(m_hWnd, IDC_MUSICTREE), pTreeView->itemNew.hItem) == NULL)
        {    
            FillTracks(&pTreeView->itemNew);
            return 0;
        }
        
	    if (pTreeView->hdr.code == TVN_SELCHANGED)
        {
            UpdateMenuItems();
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
                    sItem.hItem != m_hCatalogItem &&
                    sItem.hItem != m_hAllItem &&
                    sItem.hItem != m_hUncatItem)
                {    
                    if (sItem.lParam < 0)
                    { 
                        const vector<string> *p;
                        int                   i = -sItem.lParam;
                        
                        p = m_context->browser->m_catalog->GetPlaylists();
                        AddPlaylist((*p)[(-sItem.lParam) - 1]);
                            
                        SetFocus(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
                    }    
                    else    
                        if (m_oMusicCrossRefs[sItem.lParam].iLevel == 3)
                        {
                            PlaylistItem *item;
                            
                            item = new PlaylistItem(*m_oMusicCrossRefs[sItem.lParam].pTrack);
                            
                            m_oPlm->AddItem(item, false);
                            UpdatePlaylistList();
                            m_bListChanged = true;
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
	    if (pListView->hdr.code == NM_DBLCLK)
        {
            m_playerEQ->AcceptEvent(new Event(CMD_Stop));
            m_oPlm->SetCurrentIndex(pListView->iItem);
            m_playerEQ->AcceptEvent(new Event(CMD_Play));
        }    
            
        return 0;
    }
    
	return 1;
}

void MusicBrowserUI::BeginDrag(NM_TREEVIEW *pTreeView)
{
    POINT      sPoint;
    
    m_hTreeDragItem = pTreeView->itemNew;
    sPoint = pTreeView->ptDrag;

    m_hDragCursor = LoadCursor(g_hinst, MAKEINTRESOURCE(IDC_DRAG));
    m_hNoDropCursor = LoadCursor(g_hinst, MAKEINTRESOURCE(IDC_NODROP));
    m_hSavedCursor = SetCursor(m_hDragCursor);
    
    SetCapture(m_hWnd);
    m_bDragging = true;
}

void MusicBrowserUI::MouseMove(uint32 uFlags, POINT &sPoint)
{
    if (m_bDragging)
    {
        TV_HITTESTINFO sHit;
        
        sHit.flags = TVHT_ONITEM;
        
        ClientToWindow(m_hWnd, &sPoint); 
        sHit.pt = sPoint;
        m_hDropTarget = TreeView_HitTest(GetDlgItem(m_hWnd, IDC_MUSICTREE),
                                         &sHit);
        if (m_hDropTarget != NULL)
        {
            TV_ITEM sItem;
            
            sItem.hItem = m_hDropTarget;
            sItem.mask = TVIF_PARAM;
            TreeView_GetItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sItem);
            if (sItem.lParam < 0)
               SetCursor(m_hDragCursor);
            else    
            {
               SetCursor(m_hNoDropCursor);
               m_hDropTarget = NULL;
            }
        }       
        else    
            SetCursor(m_hNoDropCursor);
    }
} 

void MusicBrowserUI::MouseButtonUp(void)
{
    int i;
    
    if (m_bDragging)
    {
        ReleaseCapture();
        SetCursor(m_hSavedCursor);
        m_bDragging = false; 
        
        if (m_hDropTarget)
        {
            TV_ITEM sItem;
            PlaylistItem *item;
            
            sItem.hItem = m_hDropTarget;
            sItem.mask = TVIF_PARAM;
            TreeView_GetItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sItem);

            assert(sItem.lParam < 0);
            
            i = -sItem.lParam;
                 
            if (i != 1)
            {
                const vector<string> *p;
                
                p = m_context->browser->m_catalog->GetPlaylists();
                LoadPlaylist((*p)[(-sItem.lParam) - 1]);
            }
            else
                LoadPlaylist(string(""));

            item = new PlaylistItem(*m_oMusicCrossRefs[m_hTreeDragItem.lParam].pTrack);
            
            m_oPlm->AddItem(item, false);
            UpdatePlaylistList();
            m_bListChanged = true;
                     
            SetFocus(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
        }    
    }    
}

void MusicBrowserUI::FillArtists(void)
{
    TV_INSERTSTRUCT                 sInsert;
    vector<ArtistList *>           *pList;
    vector<ArtistList *>::iterator  i;
    int                             iIndex;
    TreeCrossRef                    oCrossRef;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oCrossRef.iLevel = 1;
    pList = (vector<ArtistList *> *)m_context->browser->
                                    m_catalog->GetMusicList();
    for(i = pList->begin(), iIndex = 0; i != pList->end(); i++,iIndex++)
    {
       oCrossRef.pArtist = (*i);
       m_oMusicCrossRefs.push_back(oCrossRef);
       
       sInsert.item.pszText = (char *)(*i)->name.c_str();
       sInsert.item.cchTextMax = (*i)->name.length();
       sInsert.item.iImage = 0;
       sInsert.item.iSelectedImage = 1;
       sInsert.item.cChildren= 1;
       sInsert.item.lParam = m_oMusicCrossRefs.size() - 1;
       sInsert.hInsertAfter = TVI_LAST;
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

void MusicBrowserUI::FillAllTracks(void)
{
    TV_INSERTSTRUCT                   sInsert;
    vector<ArtistList *>             *pArtistList;
    vector<ArtistList *>::iterator    i;    
    vector<AlbumList *>              *pAlbumList;
    vector<AlbumList *>::iterator     j;
    vector<PlaylistItem *>           *pList;
    vector<PlaylistItem *>::iterator  k;
    TreeCrossRef                      oCrossRef;
    MetaData                          oData;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oCrossRef.iLevel = 3;
    pArtistList = (vector<ArtistList *>*)m_context->browser->
                                         m_catalog->GetMusicList();
    for(i = pArtistList->begin(); i != pArtistList->end(); i++)
    {
        pAlbumList = (vector<AlbumList *>*)(*i)->m_albumList;
        for(j = pAlbumList->begin(); j != pAlbumList->end(); j++)
        {
            pList = (vector<PlaylistItem *>*)(*j)->m_trackList; 
            for(k = pList->begin(); k != pList->end(); k++)
            {
                oCrossRef.pArtist = (*i);
                oCrossRef.pAlbum = (*j);
                oCrossRef.pTrack = (*k);
                m_oMusicCrossRefs.push_back(oCrossRef);
            
                oData = (*k)->GetMetaData();
            
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
                sInsert.hParent = m_hAllItem;
                TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
            }
        }
    }       
    
    oCrossRef.iLevel = 3;
    oCrossRef.pArtist = NULL;
    oCrossRef.pAlbum = NULL;
    
    pList = (vector<PlaylistItem *>*)m_context->browser->
                                     m_catalog->GetUnsortedMusic();
    for(k = pList->begin(); k != pList->end(); k++)
    {
        oCrossRef.pTrack = (*k);
        m_oMusicCrossRefs.push_back(oCrossRef);

        oData = (*k)->GetMetaData();

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
        sInsert.hParent = m_hAllItem;
        TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }
}

void MusicBrowserUI::FillUncatTracks(void)
{
    TV_INSERTSTRUCT                   sInsert;
    vector<PlaylistItem *>           *pList;
    vector<PlaylistItem *>::iterator  i;
    int                               iIndex;
    TreeCrossRef                      oCrossRef;
    MetaData                          oData;

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                 TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    oCrossRef.iLevel = 3;
    oCrossRef.pArtist = NULL;
    oCrossRef.pAlbum = NULL;
    
    pList = (vector<PlaylistItem *>*)m_context->browser->
                                     m_catalog->GetUnsortedMusic();
    for(i = pList->begin(), iIndex = 0; i != pList->end(); i++, iIndex++)
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
        sInsert.hParent = m_hUncatItem;
        TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }
}

void MusicBrowserUI::FillPlaylists(void)
{
    TV_INSERTSTRUCT           sInsert;
    vector<string>::iterator  i;
    vector<string>           *pList;
    int                       iIndex;
    char                      szBase[MAX_PATH];

    sInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN |
                        TVIF_SELECTEDIMAGE | TVIF_PARAM; 

    pList = (vector<string>*)m_context->browser->
                             m_catalog->GetPlaylists(); 

    for(i = pList->begin(), iIndex = 0; i != pList->end(); i++,iIndex++)
    {
       if (!iIndex) 
          continue;

       _splitpath((char *)(*i).c_str(), NULL, NULL, szBase, NULL);   
       sInsert.item.pszText = szBase;
       sInsert.item.cchTextMax = strlen(szBase);
       sInsert.item.iImage = 2;
       sInsert.item.iSelectedImage = 2;
       sInsert.item.cChildren= 0;
       sInsert.item.lParam = -(iIndex+1);
       sInsert.hInsertAfter = TVI_SORT;
       sInsert.hParent = m_hPlaylistItem;
       TreeView_InsertItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sInsert);
    }    
}

void MusicBrowserUI::AddPlaylist(const string &oName)
{
    vector<PlaylistItem *>            oList;
    vector<PlaylistItem *>::iterator  j;
    int                               i;
    char                              url[MAX_PATH];
    uint32                            len = MAX_PATH;

    FilePathToURL(oName.c_str(), url, &len);
    m_oPlm->SetActivePlaylist(kPlaylistKey_ExternalPlaylist);
    m_oPlm->SetExternalPlaylist(url);
    for(i = 0; i < m_oPlm->CountItems(); i++)
        oList.push_back(m_oPlm->ItemAt(i));

    m_oPlm->SetActivePlaylist(kPlaylistKey_MasterPlaylist);
    for(j = oList.begin(); j != oList.end(); j++)
        m_oPlm->AddItem(new PlaylistItem(*(*j)), true);

    m_bListChanged = true;

    UpdatePlaylistList();
}

void MusicBrowserUI::LoadPlaylist(const string &oPlaylist)
{
    m_oPlm->RemoveAll();
    m_oPlm->ReadPlaylist((char *)oPlaylist.c_str());
       
    m_currentindex = 0;
    UpdatePlaylistList();
}

void MusicBrowserUI::WritePlaylist(void)
{
    PlaylistFormatInfo     oInfo;              
    char                   ext[MAX_PATH];
    Error                  eRet = kError_NoErr;
    vector<PlaylistItem *> oTempList;
    int                    i;
    bool                   bNewList = false;

    if (!m_bListChanged)
        return;

    if (!m_pParent)
    {
//        string lastPlaylist = FreeampDir(m_context->prefs);
//        lastPlaylist += "\\currentlist.m3u";
    
//        SaveCurrentPlaylist((char *)lastPlaylist.c_str());  

        m_bListChanged = false;
        return;
    }
  
    Debug_v("items: %d", m_oPlm->CountItems());
    if (m_currentListName.length() == 0)
    {
        if (SaveNewPlaylist(m_currentListName))
           bNewList = true;
        else
        {
           return;
        }   
        Debug_v("items: %d", m_oPlm->CountItems());
        SetTitles();
        Debug_v("items: %d", m_oPlm->CountItems());
    }

    Debug_v("items: %d", m_oPlm->CountItems());
    _splitpath(m_currentListName.c_str(), NULL, NULL, NULL, ext);
    for(i = 0; ; i++)
    {
        eRet = m_oPlm->GetSupportedPlaylistFormats(&oInfo, i);
        if (IsError(eRet))
           break;

        if (strcasecmp(oInfo.GetExtension(), ext + 1) == 0)
           break;   
    }
    Debug_v("items: %d", m_oPlm->CountItems());
    if (!IsError(eRet))
    {
        char   url[MAX_PATH];
        uint32 len = MAX_PATH;
        
        FilePathToURL(m_currentListName.c_str(), url, &len);
        Debug_v("items: %d", m_oPlm->CountItems());
        Debug_v("Writing playlist to: %s", url);
        eRet = m_oPlm->WritePlaylist(url, &oInfo);   
        if (IsError(eRet))
        {
           MessageBox(m_hWnd, "Cannot save playlist to disk. Out of disk space?", BRANDING, MB_OK);                              
           return;
        }
    }
    if (bNewList)
    {
        m_context->browser->m_catalog->AddPlaylist(m_currentListName.c_str());
    }

    m_bListChanged = false;
}

void MusicBrowserUI::SaveAsPlaylist(void)
{
    string oName;
    
    if (SaveNewPlaylist(oName))
    {
       m_currentListName = oName;
       SetTitles();
       WritePlaylist();
    }   
}

void MusicBrowserUI::UpdatePlaylistList(void)
{
    LV_ITEM       sItem;
    int           i;
    PlaylistItem *pItem;
    char          szText[100];

    ListView_DeleteAllItems(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX));
    sItem.state = sItem.stateMask = 0;
    for(i = 0; pItem = m_oPlm->ItemAt(i); i++)
    {
        sprintf(szText, "%d", i + 1);
        sItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
        sItem.pszText = szText;
        sItem.cchTextMax = strlen(szText);
        sItem.iSubItem = 0;
        sItem.iItem = i;
        sItem.lParam = i;
        sItem.iImage = 0;

        ListView_InsertItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        sItem.mask = LVIF_TEXT;
        sItem.pszText = (char *)pItem->GetMetaData().Title().c_str();
        sItem.cchTextMax = pItem->GetMetaData().Title().length();
        sItem.iSubItem = 1;
        ListView_SetItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        sItem.mask = LVIF_TEXT;
        sItem.pszText = (char *)pItem->GetMetaData().Artist().c_str();
        sItem.cchTextMax = pItem->GetMetaData().Artist().length();
        sItem.iSubItem = 2;
        ListView_SetItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        sItem.mask = LVIF_TEXT;
        sItem.pszText = (char *)pItem->GetMetaData().Album().c_str();
        sItem.cchTextMax = pItem->GetMetaData().Album().length();
        sItem.iSubItem = 3;
        ListView_SetItem(GetDlgItem(m_hWnd, IDC_PLAYLISTBOX), &sItem);

        if (pItem->GetMetaData().Time() != 0)
            sprintf(szText, "%d", pItem->GetMetaData().Time());
        else    
            strcpy(szText, "Unknown");
        sItem.pszText = szText;
        sItem.cchTextMax = strlen(szText);
        sItem.iSubItem = 4;
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
    HMENU hMenu;
    
    hMenu = GetMenu(m_hWnd);
    hMenu = GetSubMenu(hMenu, 1);
    
    EnableWindow(GetDlgItem(m_hWnd, IDC_DELETE), m_currentindex != -1);

    EnableWindow(GetDlgItem(m_hWnd, IDC_UP), m_currentindex > 0);
    EnableMenuItem(hMenu, ID_EDIT_MOVEUP, 
                   (m_currentindex > 0) ? MF_ENABLED : MF_GRAYED);
    
    EnableWindow(GetDlgItem(m_hWnd, IDC_DOWN), 
                 m_currentindex < m_oPlm->CountItems() - 1);
    EnableMenuItem(hMenu, ID_EDIT_MOVEDOWN, 
                 (m_currentindex < m_oPlm->CountItems() - 1) ? 
                 MF_ENABLED : MF_GRAYED);

}

void MusicBrowserUI::SortEvent(int id)
{
    PlaylistSortKey key;
    
    switch(id)
    {
        case ID_SORT_ARTIST:
             key = kPlaylistSortKey_Artist;
        break;     
        case ID_SORT_ALBUM:
             key = kPlaylistSortKey_Album;
        break;     
        case ID_SORT_TITLE:
             key = kPlaylistSortKey_Title;
        break;     
        case ID_SORT_LENGTH:
             key = kPlaylistSortKey_Time;
        break;     
        case ID_SORT_YEAR:
             key = kPlaylistSortKey_Year;
        break;     
        case ID_SORT_TRACK:
             key = kPlaylistSortKey_Track;
        break;     
        case ID_SORT_GENRE:
             key = kPlaylistSortKey_Genre;
        break;     
        case ID_SORT_LOCATION:
             key = kPlaylistSortKey_Location;
        break;     
        case IDC_RANDOMIZE:
        case ID_SORT_RANDOMIZE:
             key = kPlaylistSortKey_Random;
        break;     
        default:
             return;
    }
    m_oPlm->Sort(key);
    UpdatePlaylistList();
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

bool MusicBrowserUI::SaveNewPlaylist(string &oName)
{
    int32              i, iOffset = 0;
    uint32             size;
    PlaylistFormatInfo format;
    char               szFilter[512];
    OPENFILENAME       sOpen;
    char               szFile[MAX_PATH], szInitialDir[MAX_PATH];
        
    for(i = 0; ; i++)
    {
       if (m_oPlm->GetSupportedPlaylistFormats(&format, i) != kError_NoErr)
          break;
    
       sprintf(szFilter + iOffset, "%s (.%s)", 
            format.GetDescription(),
            format.GetExtension());
       iOffset += strlen(szFilter + iOffset) + 1;     

       sprintf(szFilter + iOffset, "*.%s", 
            format.GetExtension());
       iOffset += strlen(szFilter + iOffset) + 1;     
    }
    
    strcpy(szFilter + iOffset, "All Files (*.*)\0");
    iOffset += strlen(szFilter + iOffset) + 1;     
    strcpy(szFilter + iOffset, "*.*\0");
    iOffset += strlen(szFilter + iOffset) + 1;     
    szFilter[iOffset] = 0;

    size = MAX_PATH;
    if (!IsError(m_context->prefs->GetInstallDirectory(szInitialDir, &size)))
    {
        struct _stat buf;
        
        strcat(szInitialDir, "\\Playlists");
        if (_stat(szInitialDir, &buf) != 0)
           _mkdir(szInitialDir);
           
        sOpen.lpstrInitialDir = szInitialDir;
    }
    else
        sOpen.lpstrInitialDir = NULL;
    
    szFile[0] = 0;
    sOpen.lStructSize = sizeof(OPENFILENAME);
    sOpen.hwndOwner = m_hWnd;
    sOpen.hInstance = NULL;
    sOpen.lpstrFilter = szFilter;
    sOpen.lpstrCustomFilter = NULL;
    sOpen.nMaxCustFilter = 0;
    sOpen.nFilterIndex = 1;
    sOpen.lpstrFile = szFile;
    sOpen.nMaxFile = MAX_PATH;
    sOpen.lpstrFileTitle = NULL;
    sOpen.lpstrTitle = "Save Playlist as";
    sOpen.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY |
                  OFN_PATHMUSTEXIST;
    sOpen.lpstrDefExt = "m3u";
      
    if (GetSaveFileName(&sOpen))
    {
        oName = sOpen.lpstrFile;
        return true;
    }
    return false;
}

void MusicBrowserUI::OpenPlaylist(void)
{
    int32              i, iOffset = 0;
    PlaylistFormatInfo format;
    char               szFilter[512];
    OPENFILENAME       sOpen;
    char               szFile[MAX_PATH];
        
    for(i = 0; ; i++)
    {
       if (m_oPlm->GetSupportedPlaylistFormats(&format, i) != kError_NoErr)
          break;
    
       sprintf(szFilter + iOffset, "%s (.%s)", 
            format.GetDescription(),
            format.GetExtension());
       iOffset += strlen(szFilter + iOffset) + 1;     

       sprintf(szFilter + iOffset, "*.%s", 
            format.GetExtension());
       iOffset += strlen(szFilter + iOffset) + 1;     
    }
    
    strcpy(szFilter + iOffset, "All Files (*.*)\0");
    iOffset += strlen(szFilter + iOffset) + 1;     
    strcpy(szFilter + iOffset, "*.*\0");
    iOffset += strlen(szFilter + iOffset) + 1;     
    szFilter[iOffset] = 0;
    
    szFile[0] = 0;
    sOpen.lStructSize = sizeof(OPENFILENAME);
    sOpen.hwndOwner = m_hWnd;
    sOpen.hInstance = NULL;
    sOpen.lpstrFilter = szFilter;
    sOpen.lpstrCustomFilter = NULL;
    sOpen.nMaxCustFilter = 0;
    sOpen.nFilterIndex = 1;
    sOpen.lpstrFile = szFile;
    sOpen.nMaxFile = MAX_PATH;
    sOpen.lpstrFileTitle = NULL;
    sOpen.lpstrInitialDir = NULL;
    sOpen.lpstrTitle = "Open Playlist";
    sOpen.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    sOpen.lpstrDefExt = "m3u";
      
    if (GetOpenFileName(&sOpen))
    {
        string playlist = sOpen.lpstrFile;
        
        m_context->browser->m_catalog->AddPlaylist(sOpen.lpstrFile);
        InitTree();
        //FillPlaylistCombo();
        LoadPlaylist(playlist);
    }
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
           eRet = m_oPlm->AddItem(*i);
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

                char* foo = new char[strlen(file) + 8];

                strcpy(foo, "file://");
                strcat(foo, file);

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

void ClientToWindow(HWND hWnd, POINT *Pt) 
{
    RECT wRect, cRect;
 
    GetWindowRect(hWnd, &wRect);
    GetClientRect(hWnd, &cRect);
    MapWindowPoints(hWnd, HWND_DESKTOP, (LPPOINT)&cRect, 2);
    Pt->x += (wRect.left - cRect.left);
    Pt->y += (wRect.top - cRect.top);
}

void MusicBrowserUI::EmptyDBCheck(void)
{
    int iRet;
    
    if (m_context->browser->m_catalog->GetPlaylists()->size() > 0 ||
        m_context->browser->m_catalog->GetMusicList()->size() > 0 ||
        m_context->browser->m_catalog->GetUnsortedMusic()->size() > 0)
        return;
        
    iRet = MessageBox(m_hWnd, "Your music database does not contain any items. "
                       "Would you like to\r\nstart a music search to find "
                       "music and playlists on your machine?",
                       "MusicBrowser", MB_YESNO);
    if (iRet == IDYES)
        StartMusicSearch();
}

void MusicBrowserUI::EditEvent(void)
{
    TV_ITEM   sItem;
    
    sItem.mask = TVIF_PARAM;
    sItem.hItem = TreeView_GetSelection(GetDlgItem(m_hWnd, IDC_MUSICTREE));
    if (sItem.hItem != m_hPlaylistItem &&
        sItem.hItem != m_hCatalogItem &&
        sItem.hItem != m_hAllItem &&
        sItem.hItem != m_hUncatItem)
    {
       TreeView_GetItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sItem);
       
       if (sItem.lParam < 0)
       { 
           const vector<string> *p;
           int                   i = -sItem.lParam;
           
           p = m_context->browser->m_catalog->GetPlaylists();
           EditPlaylist((*p)[(-sItem.lParam) - 1]);
       }    
    }
}

HTREEITEM MusicBrowserUI::GetMusicTreeIndices(int &iTrack, int &iPlaylist)
{
    TV_ITEM      sItem;
    
    iTrack = -1;
    iPlaylist = -1;
    
    sItem.mask = TVIF_PARAM;
    sItem.hItem = TreeView_GetSelection(GetDlgItem(m_hWnd, IDC_MUSICTREE));
    if (sItem.hItem != m_hPlaylistItem &&
        sItem.hItem != m_hCatalogItem &&
        sItem.hItem != m_hAllItem &&
        sItem.hItem != m_hUncatItem)
    {
       TreeView_GetItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), &sItem);
       if (sItem.lParam < 0)
          iPlaylist = (-sItem.lParam) - 1;
       else   
          iTrack = sItem.lParam;
          
       return sItem.hItem;   
    }
    else
       return NULL;
}    

void MusicBrowserUI::UpdateMenuItems(void)
{
    HMENU        hMenu;
    MENUITEMINFO sMenuItem;
    string       oType(""), oText;
    int          iPlaylist, iTrack;

    GetMusicTreeIndices(iTrack, iPlaylist);
    if (iTrack >= 0)
       oType = " Track";
       
    if (iPlaylist >= 0)
       oType = " Playlist";

    hMenu = GetMenu(m_hWnd);
    hMenu = GetSubMenu(hMenu, 1);
 
    sMenuItem.cbSize = sizeof(MENUITEMINFO);
    sMenuItem.fMask = MIIM_TYPE | MIIM_STATE;
    sMenuItem.fType = MFT_STRING;
    sMenuItem.fState = (oType.length() == 0) ? MFS_GRAYED : MFS_ENABLED;

    oText = string("&Edit") + oType + string("...");
    sMenuItem.dwTypeData = (char *)oText.c_str();
    sMenuItem.cch = strlen(sMenuItem.dwTypeData);
    SetMenuItemInfo(hMenu, ID_EDIT_EDIT, false, &sMenuItem);

    oText = string("&Remove") + oType + string(" from Catalog...");
    sMenuItem.dwTypeData = (char *)oText.c_str();
    sMenuItem.cch = strlen(sMenuItem.dwTypeData);
    SetMenuItemInfo(hMenu, ID_EDIT_REMOVE, false, &sMenuItem);
    
    oText = string("Remove") + oType + string(" from &Disk...");
    sMenuItem.dwTypeData = (char *)oText.c_str();
    sMenuItem.cch = strlen(sMenuItem.dwTypeData);
    SetMenuItemInfo(hMenu, ID_EDIT_REMOVEFROMDISK, false, &sMenuItem);
}

void MusicBrowserUI::RemoveEvent(void)
{
    int       iPlaylist, iTrack;
    HTREEITEM hItem;

    hItem = GetMusicTreeIndices(iTrack, iPlaylist);
    if (iTrack >= 0)
    {
        m_context->browser->m_catalog->RemoveSong(
             m_oMusicCrossRefs[iTrack].pTrack->URL().c_str());
        TreeView_DeleteItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), hItem);
    }        
    if (iPlaylist >= 0)
    {
        const vector<string> *p;
        
        p = m_context->browser->m_catalog->GetPlaylists();
        m_context->browser->m_catalog->RemovePlaylist( 
                 (*p)[iPlaylist].c_str());
        TreeView_DeleteItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), hItem);
    }             
}

void MusicBrowserUI::RemoveFromDiskEvent(void)
{
    int       iPlaylist, iTrack;
    char      szConfirm[MAX_PATH];
    char      szBase[MAX_PATH];
    HTREEITEM hItem;

    hItem = GetMusicTreeIndices(iTrack, iPlaylist);
    if (iTrack >= 0)
    {
        _splitpath(m_oMusicCrossRefs[iTrack].pTrack->URL().c_str(),
                   NULL, NULL, szBase, NULL);
        sprintf(szConfirm, "Are you sure you want to remove track\r\n"
                           "%s from the music catalog and the disk?",
                           szBase);
        if (MessageBox(m_hWnd, szConfirm, BRANDING, MB_YESNO) == IDYES)
        {
           unlink(m_oMusicCrossRefs[iTrack].pTrack->URL().c_str());
           m_context->browser->m_catalog->RemoveSong(
                m_oMusicCrossRefs[iTrack].pTrack->URL().c_str());
           TreeView_DeleteItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), hItem);
        }   
    }        
    if (iPlaylist >= 0)
    {
        const vector<string> *p;

        p = m_context->browser->m_catalog->GetPlaylists();
        _splitpath((*p)[iPlaylist].c_str(),
                   NULL, NULL, szBase, NULL);
        sprintf(szConfirm, "Are you sure you want to remove the playlist\r\n"
                           "%s from the music catalog and the disk?",
                           szBase);
        if (MessageBox(m_hWnd, szConfirm, BRANDING, MB_YESNO) == IDYES)
        {
            unlink((*p)[iPlaylist].c_str());
            m_context->browser->m_catalog->RemovePlaylist( 
                    (*p)[iPlaylist].c_str());
            TreeView_DeleteItem(GetDlgItem(m_hWnd, IDC_MUSICTREE), hItem);
        }            
    }             
}

void MusicBrowserUI::ImportEvent(void)
{
    vector<char*>           oFileList;
    vector<char*>::iterator i;

    if (FileOpenDialog(m_hWnd, "Import Track",
                       kAudioFileFilter, 
                       &oFileList,
                       m_context->prefs))
    {
        for(i = oFileList.begin(); i != oFileList.end(); i++)
            m_context->browser->m_catalog->AddSong(*i);
        InitTree();    
    }
}

uint32 MusicBrowserUI::CalcStringEllipsis(HDC hdc, string& displayString, int32 columnWidth)
{
    const TCHAR szEllipsis[] = TEXT("...");
    SIZE   sizeString;
    SIZE   sizeEllipsis;
    string temp;
    
    // Adjust the column width to take into account the edges
    //columnWidth -= 4;

    temp = displayString;        

    GetTextExtentPoint32(hdc, temp.c_str(), temp.size(), &sizeString);       

    // If the width of the string is greater than the column width shave
    // the string and add the ellipsis
    if(sizeString.cx > columnWidth)
    {
        GetTextExtentPoint32(hdc, szEllipsis, strlen(szEllipsis), &sizeEllipsis);
       
        while(temp.size() > 1)
        {
            temp.erase(temp.size() - 1, 1);

            GetTextExtentPoint32(hdc, temp.c_str(), temp.size(), &sizeString);
            
            if ((uint32)(sizeString.cx + sizeEllipsis.cx) <= columnWidth)
            {
                // The string with the ellipsis finally fits                
                // Concatenate the two strings and break out of the loop
                temp += szEllipsis;
                displayString = temp;
                break;
            }
            else if(temp.size() == 1)
            {
                temp += szEllipsis;
                displayString = temp;
                break;
            }
        }
    }

    GetTextExtentPoint32(hdc, displayString.c_str(), displayString.size(), &sizeString);

    return sizeString.cx;
}