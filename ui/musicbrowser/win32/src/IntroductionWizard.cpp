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

        $Id: IntroductionWizard.cpp,v 1.18 2000/08/25 13:40:13 sward Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

// system includes
#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

// project includes
#include "config.h"
#include "resource.h"
#include "Win32MusicBrowser.h"


static BOOL CALLBACK IntroWizardHello(HWND hwnd, 
                                      UINT msg, 
                                      WPARAM wParam, 
                                      LPARAM lParam)
{
    BOOL result = FALSE;

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            break;
        }

        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
            UINT ctrlId = wParam;
            const char* kCaption1 = "Welcome!";
            const char* kCaption2 = "What is \'My Music\'?";
            const char* kMsg1 = "This wizard will help you begin organizing your "
                                "music collection and get you started playing "
                                "your music.";
            const char* kMsg2 = "My Music helps you organize the music you have "
                                "on your computer. The My Music window is divided "
                                "into two panes: "
                                "My Music Collection and Currently Listening To.";
                                //"\r\n"
            const char* kMsg3 = "My Music Collection provides a convenient, "
                                "organized view of the music you have on your "
                                "computer. It might help to think of this pane "
                                "as a CD rack for your computer.";
                                //"\r\n"
            const char* kMsg4 = "Currently Listening To displays a list of the "
                                "songs you have chosen to play. In order to listen "
                                "to music all you have to do is add items to the "
                                "list by dragging them from the My Music Collection "
                                "pane on the left to the Currently Listening To "
                                "pane on the right.";
                                //"\r\n"
            const char* kMsg5 = "For a more detailed explanation of how to use "
                                "the My Music window you should access the "
                                "application\'s help system through the Help menu "
                                "or by clicking the \'?\' in the main player window.";


            switch(ctrlId)
            {
                case IDC_CAPTION1:
                case IDC_CAPTION2:
                {
                    HFONT font, oldFont;

                    LOGFONT lf;

                    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

                    lf.lfWeight = FW_BOLD;

                    font = CreateFontIndirect(&lf);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    const char* caption;

                    if(ctrlId == IDC_CAPTION1)
                        caption = kCaption1;
                    else if(ctrlId == IDC_CAPTION2)
                        caption = kCaption2;

                    DrawText(dis->hDC, 
                             caption,
                             strlen(caption),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);

                    break;
                } 

                case IDC_TEXT1:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    DrawText(dis->hDC, 
                             kMsg1,
                             strlen(kMsg1),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }

                case IDC_TEXT2:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    RECT halfHeightRect = clientRect;
                    int halfHeight = DrawText(
                                         dis->hDC, 
                                         kMsg2,
                                         strlen(kMsg2),
                                         &halfHeightRect,
                                         DT_LEFT|DT_SINGLELINE|DT_CALCRECT)/2;
                    int height;

                    height = DrawText(
                             dis->hDC, 
                             kMsg2,
                             strlen(kMsg2),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    clientRect.top += height + halfHeight;

                    height = DrawText(
                             dis->hDC, 
                             kMsg3,
                             strlen(kMsg3),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    clientRect.top += height + halfHeight;

                    height = DrawText(
                             dis->hDC, 
                             kMsg4,
                             strlen(kMsg4),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    clientRect.top += height + halfHeight;

                    height = DrawText(
                             dis->hDC, 
                             kMsg5,
                             strlen(kMsg5),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }
            }

            break;
        }

        case WM_NOTIFY:
        {
            switch(((NMHDR*)lParam)->code)
            {
                case PSN_KILLACTIVE:
                {
                    SetWindowLong(hwnd,	DWL_MSGRESULT, FALSE);
                    result = TRUE;
                    break;
                }

                case PSN_RESET:
                {
                    SetWindowLong(hwnd,	DWL_MSGRESULT, FALSE);
                    break;
                }

                case PSN_SETACTIVE:
                {
                    PropSheet_SetWizButtons(GetParent(hwnd), PSWIZB_NEXT);
                    break;
                }

                case PSN_WIZNEXT:
                {
                    break;
                }

                case PSN_WIZBACK:
                {
                    break;
                }
            }

            break;
        }

    }

	return result;
}   

static int CALLBACK BrowseCallbackProc(HWND hwnd, 
                                       UINT uMsg, 
                                       LPARAM lParam,
                                       LPARAM lpData)
{
        // Called just after the dialog is initialized
        // Select the dir passed in BROWSEINFO.lParam
        // TAKE CARE THAT IF THE DIR STRING ENDS WITH \ IT WILL NOT WORK ???
        if (uMsg == BFFM_INITIALIZED)
                ::SendMessage(hwnd, BFFM_SETSELECTION, FALSE, lpData);

        return 0;
}

//const char* kAllDrives = "All Drives";
//const char* kAllFolders = "All Folders";

static BOOL CALLBACK IntroWizardSearch( HWND hwnd,
                                        UINT msg, 
                                        WPARAM wParam, 
                                        LPARAM lParam)
{
	BOOL result = FALSE;
    static vector<string>* searchPaths;

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            HWND hwndDrives = GetDlgItem(hwnd, IDC_DRIVES);
            HWND hwndDirectory = GetDlgItem(hwnd, IDC_DIRECTORY);
            DWORD  dwDrives;
            //char   szDrive[3] = "X:";
            char *szDrive = new char[4];
            memset(szDrive, 0, 4);
            szDrive[1] = ':';
            int32  i, ret;

            i = ComboBox_AddString(hwndDrives, "All Drives");
            ComboBox_SetCurSel(hwndDrives, i);

            dwDrives = GetLogicalDrives();
            for(i = 0; i < sizeof(DWORD) * 8; i++)
            {
               if (dwDrives & (1 << i))
               {
                  szDrive[0] = 'A' + i;
                  ret = GetDriveType(szDrive);
                  if (ret != DRIVE_CDROM && ret != DRIVE_REMOVABLE)
                  {
                      ComboBox_AddString(hwndDrives, szDrive);
                  }
               }   
            }

            Edit_SetText(hwndDirectory, "All Folders");

            PROPSHEETPAGE* psp = (PROPSHEETPAGE*)lParam;
            searchPaths = (vector<string>*)psp->lParam;

            delete [] szDrive;
            break;
        }

        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
            UINT ctrlId = wParam;
            const char* kCaption1 = "Search Computer For Music";
            const char* kCaption2 = "Where Would You Like to Look for Music?";
            const char* kMsg1 = "In order to populate the My Music Collection pane "
                                the_BRANDING" will search your computer for supported music "
                                "files. The files will not be moved or modified during "
                                "this process. Their location will be remembered in "
                                "order to provide you with an organized view of your "
                                "music collection.";
                               
            const char* kMsg2 = "By default "the_BRANDING" will search all the disk drives on "
                                "your computer for music. If you would like to limit the "
                                "scope of the search you may do so by selecting a "
                                "disk drive for us to search. If you wish, you may "
                                "also select a specific folder on that drive.";
                                
            switch(ctrlId)
            {
                case IDC_CAPTION1:
                case IDC_CAPTION2:
                {
                    HFONT font, oldFont;

                    LOGFONT lf;

                    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

                    lf.lfWeight = FW_BOLD;

                    font = CreateFontIndirect(&lf);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    const char* caption;

                    if(ctrlId == IDC_CAPTION1)
                        caption = kCaption1;
                    else if(ctrlId == IDC_CAPTION2)
                        caption = kCaption2;

                    DrawText(dis->hDC, 
                             caption,
                             strlen(caption),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);

                    break;
                } 

                case IDC_TEXT1:
                case IDC_TEXT2:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    const char* text;

                    if(ctrlId == IDC_TEXT1)
                        text = kMsg1;
                    else if(ctrlId == IDC_TEXT2)
                        text = kMsg2;

                    DrawText(dis->hDC, 
                             text,
                             strlen(text),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }
            }

            break;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_DRIVES:
                {
                    if(HIWORD(wParam) == CBN_CLOSEUP)
                    {
                        HWND hwndCombo = (HWND) lParam;
                        char temp[MAX_PATH];
                        int32 sel = ComboBox_GetCurSel(hwndCombo);

                        ComboBox_GetText( hwndCombo, 
                                          temp, 
                                          MAX_PATH);

                        HWND hwndDirectory = GetDlgItem(hwnd, IDC_DIRECTORY);
                        HWND hwndBrowse = GetDlgItem(hwnd, IDC_BROWSE);
                        
                        BOOL enable = strcmp(temp, "All Drives");

                        if(!enable)
                            strcpy(temp, "All Folders");
                        else
                            sprintf(temp, "%s\\", temp);
                            
                        Edit_SetText(hwndDirectory, temp);

                        //EnableWindow(hwndText, enable);
                        //EnableWindow(hwndDirectory, enable);
                        EnableWindow(hwndBrowse, enable);
                    }

                    break;
                }          

                case IDC_DIRECTORY:
                {
                    /*if(HIWORD(wParam) == EN_CHANGE)
                    {
                        char temp[MAX_PATH];
                        HWND hwndEdit = (HWND) lParam;

                        Edit_GetText( hwndEdit, 
                                      temp,
                                      MAX_PATH);
                    }*/

                    break;
                }



                case IDC_BROWSE:
                {
                    LPMALLOC pMalloc;

                    if(SUCCEEDED(SHGetMalloc(&pMalloc)))
                    {
                        HWND hwndDrives = GetDlgItem(hwnd, IDC_DRIVES);
                        HWND hwndDirectory = GetDlgItem(hwnd, IDC_DIRECTORY);
                        char temp[MAX_PATH];

                        LPITEMIDLIST pidlDrive;

                        // get the PIDL for this dir and set the root
                        LPSHELLFOLDER desktop;

                        if(SUCCEEDED(SHGetDesktopFolder(&desktop)))
                        {
                            OLECHAR drive[MAX_PATH];
                            OLECHAR path[MAX_PATH];
                            ULONG eaten;
                            LPITEMIDLIST pidlPath;

                            ComboBox_GetText(hwndDrives, 
                                             temp, 
                                             MAX_PATH);

                            strcat(temp, "\\");

                            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, temp,
                                                -1, drive, sizeof(drive));

                            desktop->ParseDisplayName(hwnd, NULL, drive, &eaten, &pidlDrive, NULL);                            

                            Edit_GetText(hwndDirectory, 
                                         temp,
                                         MAX_PATH);

                            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, temp, 
                                                -1, path, sizeof(path));

                            desktop->ParseDisplayName(hwnd, NULL, path, &eaten, &pidlPath, NULL);

                            BROWSEINFO bi; 
                            LPITEMIDLIST browseId;
                            char displayName[MAX_PATH + 1];

                            bi.hwndOwner = hwnd;
                            bi.pidlRoot = pidlDrive;
                            bi.pszDisplayName = displayName;
                            bi.lpszTitle = "Please select the folder in which you want to search.";
                            bi.ulFlags = BIF_RETURNONLYFSDIRS;
                            bi.lpfn = BrowseCallbackProc;
                            bi.lParam = (LPARAM)pidlPath;

                            browseId = SHBrowseForFolder(&bi);
        
                            if(browseId)
                            {
                                SHGetPathFromIDList(browseId, temp);
                        
                                Edit_SetText(hwndDirectory, temp);

                                pMalloc->Free(browseId);
                            }

                            // clean up
                            if(pidlPath)
                                pMalloc->Free(pidlPath);

                            if(pidlDrive)
                                pMalloc->Free(pidlDrive);

                            desktop->Release();
                        }                        
                    }

                    break;
                }
            }

            break;
        }
                 
        case WM_NOTIFY:
        {
            switch(((NMHDR*)lParam)->code)
            {
                case PSN_KILLACTIVE:
                {
                    SetWindowLong(hwnd,	DWL_MSGRESULT, FALSE);
                    result = TRUE;
                    break;
                }

                case PSN_RESET:
                {
                    SetWindowLong(hwnd,	DWL_MSGRESULT, FALSE);
                    break;
                }

                case PSN_SETACTIVE:
                {
                    
                    PropSheet_SetWizButtons(GetParent(hwnd), PSWIZB_BACK | PSWIZB_FINISH);
                    //HWND hwndFinish = GetDlgItem(GetParent(hwnd), 3025);
                    HWND hwndFinish = FindWindowEx(GetParent(hwnd), NULL, NULL, "Finish");

                    SetWindowText(hwndFinish, "Search");
                    break;
                }

                case PSN_WIZFINISH:
                {
                    HWND hwndDrives = GetDlgItem(hwnd, IDC_DRIVES);
                    HWND hwndDirectory = GetDlgItem(hwnd, IDC_DIRECTORY);
                    char temp[MAX_PATH];

                    ComboBox_GetText(hwndDrives, 
                                     temp, 
                                     MAX_PATH);

                    BOOL allDrives = !strcmp(temp, "All Drives");

                    if(allDrives)
                    {
                        DWORD  dwDrives;
                        char   *szDrive = "X:\\";
                        int32  i, ret;

                        dwDrives = GetLogicalDrives();
                        for(i = 0; i < sizeof(DWORD) * 8; i++)
                        {
                           if (dwDrives & (1 << i))
                           {
                              szDrive[0] = 'A' + i;
                              ret = GetDriveType(szDrive);
                              if (ret != DRIVE_CDROM && ret != DRIVE_REMOVABLE)
                              {
                                  searchPaths->push_back(szDrive);
                              }
                           }   
                        }
                    }
                    else
                    {
                        Edit_GetText(hwndDirectory, 
                                     temp,
                                     MAX_PATH);

                        searchPaths->push_back(temp);
                    }
                    break;
                }

                case PSN_WIZBACK:
                {
                    break;
                }
            }

            break;
        }

    }

	return result;
}   

static BOOL CALLBACK IntroWizardRelatable(HWND hwnd,
                                          UINT msg,
                                          WPARAM wParam,
                                          LPARAM lParam)
{
    BOOL result = FALSE;
    static HWND hwndOptIn = NULL;
    static HWND hwndOptOut = NULL;

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            hwndOptIn = GetDlgItem(hwnd, IDC_RELATABLE_YES);
            hwndOptOut = GetDlgItem(hwnd, IDC_RELATABLE_NO);

            PROPSHEETPAGE *psp = (PROPSHEETPAGE*)lParam;

            Button_SetCheck(hwndOptIn, TRUE);
            Button_SetCheck(hwndOptOut, FALSE);
            break;
        }
        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
            UINT ctrlId = wParam;
            const char* kCaption1 = "Check out Relatable's new recommendation features";
            const char* kMsg1 = "This version of "the_BRANDING" offers Relatable features that automatically\n"
                                "recommend music playlists and streams. It's our first public test of\n"
                                "an exciting new approach to discovering music. Relatable's system\n"
                                "'learns' listener preferences through "the_BRANDING" and compares them\n"
                                "with the preferences of like-minded listeners. Like virtual 'word of\n"
                                "mouth', Relatable introduces you to music that people like\n"
                                "you have enjoyed.";
            const char* kCaption2 = "Private by Design";
            const char* kMsg2 = "Please note that Relatable profiles are totally anonymous and\n"
                                "individual profiles are never shared with third parties. We\n"
                                "don't collect any personally identifiable information. Each\n"
                                "anonymous profile is stored on Relatable's secure servers, and\n"
                                "we're continually adding safeguards to protect our users. To\n"
                                "enjoy these features and help us test the system, just opt-in.\n"
                                "You will never be contacted by Relatable or anyone else (unless\n"
                                "you ask, of course!). That's Relatable's privacy promise. If you\n"
                                "have any questions, please contact us at info@relatable.com";
				
            switch(ctrlId)
            {
                case IDC_RELATABLE_TEXT1:
				case IDC_RELATABLE_TEXT2:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

					const char *msg;
					if (ctrlId == IDC_RELATABLE_TEXT1)
						msg = kMsg1;
					else if (ctrlId == IDC_RELATABLE_TEXT2)
						msg = kMsg2;

                    DrawText(dis->hDC,
                             msg,
                             strlen(msg),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }
                //case IDC_RELATABLE_CAPTION1:
                case IDC_RELATABLE_CAPTION2:
                {
                    HFONT font, oldFont;

                    LOGFONT lf;

                    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

                    lf.lfWeight = FW_BOLD;

                    font = CreateFontIndirect(&lf);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    const char* caption;

                    if(ctrlId == IDC_RELATABLE_CAPTION1)
                        caption = kCaption1;
                    else if(ctrlId == IDC_RELATABLE_CAPTION2)
                        caption = kCaption2;

                    DrawText(dis->hDC, 
                             caption,
                             strlen(caption),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);

                    break;
                } 
            }

            break;
        }
        case WM_NOTIFY:
        {
            switch(((NMHDR*)lParam)->code)
            {
                case PSN_KILLACTIVE:
                {
                    SetWindowLong(hwnd,        DWL_MSGRESULT, FALSE);
                    result = TRUE;
                    break;
                }
                case PSN_RESET:
                {
                    SetWindowLong(hwnd,        DWL_MSGRESULT, FALSE);
                    break;
                }

                case PSN_SETACTIVE:
                {
                    PropSheet_SetWizButtons(GetParent(hwnd), PSWIZB_BACK | PSWIZB_NEXT);
                    break;
                }
                case PSN_WIZNEXT:
                {
                    if (Button_GetCheck(hwndOptOut) == BST_CHECKED)
                    {
                        PropSheet_RemovePage(GetParent(hwnd), 2, NULL);
                    }
                    break;
                }

                case PSN_WIZBACK:
                {
                    break;
                }
            }
            break;
        }
    }
    return result;
}

static BOOL CALLBACK IntroWizardRelatableTwo(HWND hwnd,
                                             UINT msg,
                                             WPARAM wParam,
                                             LPARAM lParam)
{
    BOOL result = FALSE;

    static APSInterface *pInterface;
  
    switch(msg)
    {
        case WM_INITDIALOG:
        {
            PROPSHEETPAGE *psp = (PROPSHEETPAGE*)lParam;
            pInterface = (APSInterface *)psp->lParam;
            break;
        }
        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)lParam;
            UINT ctrlId = wParam;
            const char* kCaption3 = "Here's how to enjoy Relatable Features";
            const char* kMsg1 = "Relatable automatically generates personalized playlists that are\n"
                                "based on the files located on your computer and the music you\n"
                                "listen to on the Web. The more you use the player, the better it\n"
                                "works! Enter a profile name in the window below.  Then start\n"
                                "listening to music.  After you have listened to a few songs, hit\n"
                                "'Recommend Playlist' on the Relatable menu to hear a personalized\n"
                                "playlist. If you'd like to find music streams that are playing\n"
                                "songs you like, check out the 'Recommended Streams' item in the\n"
                                "'My Music' tree.\n\n"
                                "Note: You can create additional music profiles by selecting\n"
			                    "'Profiles' under the 'Options' menu in the My Music window. Check\n"
								"out the Help menu for details on all the Relatable features,\n"
								"or drop us a note with questions to info@relatable.com\n";

            const char* kCaption1 = "Profile Name: ";
            switch(ctrlId)
            {
                case IDC_RELATABLE_TEXT1:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    DrawText(dis->hDC,
                             kMsg1,
                             strlen(kMsg1),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }
                case IDC_RELATABLE_CAPTION1:
                {
                    HFONT font, oldFont;

                    font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    RECT halfHeightRect = clientRect;
                    int halfHeight = DrawText(
                                         dis->hDC,
                                         kCaption1,
                                         strlen(kCaption1),
                                         &halfHeightRect,
                                         DT_LEFT|DT_SINGLELINE|DT_CALCRECT)/2;
                    int height;

                    height = DrawText(
                             dis->hDC,
                             kCaption1,
                             strlen(kCaption1),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    clientRect.top += height + halfHeight;

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);
                    break;
                }
                case IDC_RELATABLE_CAPTION3:
                {
                    HFONT font, oldFont;

                    LOGFONT lf;

                    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

                    lf.lfWeight = FW_BOLD;

                    font = CreateFontIndirect(&lf);

                    oldFont = (HFONT)SelectObject(dis->hDC, font);

                    RECT clientRect;
                    GetClientRect(dis->hwndItem, &clientRect);

                    DrawText(dis->hDC, 
                             kCaption3,
                             strlen(kCaption3),
                             &clientRect,
                             DT_LEFT|DT_WORDBREAK);

                    SelectObject(dis->hDC, oldFont);

                    DeleteObject(font);

                    break;
                }              
                case IDC_RELATABLE_EDIT1:
                {
                    break;
                }
            }

            break;
        }
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_RELATABLE_WEB:
                {
                  ShellExecute(hwnd, "open", "http://beta.relatable.com", NULL,
                               NULL, SW_SHOWNORMAL);
                  break;
                }
            }
            break;
        }
        case WM_NOTIFY:
        {
            switch(((NMHDR*)lParam)->code)
            {
                case PSN_KILLACTIVE:
                {
                    SetWindowLong(hwnd,        DWL_MSGRESULT, FALSE);
                    result = TRUE;
                    break;
                }
                case PSN_RESET:
                {
                    SetWindowLong(hwnd,        DWL_MSGRESULT, FALSE);
                    break;
                }

                case PSN_SETACTIVE:
                {
                    PropSheet_SetWizButtons(GetParent(hwnd), PSWIZB_BACK | PSWIZB_NEXT);
                    break;
                }
                case PSN_WIZNEXT:
                {
                    HWND hwndProfileEdit = GetDlgItem(hwnd, IDC_RELATABLE_EDIT1);
                    char temp[MAX_PATH];

                    Edit_GetText( hwndProfileEdit,
                                  temp,
                                  MAX_PATH);
                                       
                    //MessageBox(NULL, temp, "Value", MB_OK | MB_SYSTEMMODAL);
                    if (!string(temp).empty())
                    {
                        pInterface->CreateProfile(temp);
                    }
                    break;
                }

                case PSN_WIZBACK:
                {
                    break;
                }
            }
            break;
        }
    }

    return result;
}

bool MusicBrowserUI::IntroductionWizard(vector<string>* searchPaths,
                                        APSInterface *pInterface)
{
    PROPSHEETPAGE psp[4];
    PROPSHEETHEADER psh;

    HINSTANCE hinst = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = 0;
    psp[0].hInstance = hinst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_INTROWIZARD_HELLO);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = IntroWizardHello;
    psp[0].pszTitle = NULL;
    psp[0].lParam = (LPARAM)0;   

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = 0;
    psp[1].hInstance = hinst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_INTROWIZARD_RELATABLE);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = IntroWizardRelatable;
    psp[1].pszTitle = NULL;
    psp[1].lParam = (LPARAM)0 ;

    psp[2].dwSize = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags = 0;
    psp[2].hInstance = hinst;
    psp[2].pszTemplate = MAKEINTRESOURCE(IDD_INTROWIZARD_RELATABLETWO);
    psp[2].pszIcon = NULL;
    psp[2].pfnDlgProc = IntroWizardRelatableTwo;
    psp[2].pszTitle = NULL;
    psp[2].lParam = (LPARAM)pInterface;

    psp[3].dwSize = sizeof(PROPSHEETPAGE);
    psp[3].dwFlags = 0;
    psp[3].hInstance = hinst;
    psp[3].pszTemplate = MAKEINTRESOURCE(IDD_INTROWIZARD_SEARCH);
    psp[3].pszIcon = NULL;
    psp[3].pfnDlgProc = IntroWizardSearch;
    psp[3].pszTitle = NULL;
    psp[3].lParam = (LPARAM)searchPaths;

    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD | PSH_NOAPPLYNOW;
    psh.hwndParent = m_hWnd;
    psh.hInstance = hinst;
    psh.pszIcon = NULL;
    psh.pszCaption = "Welcome to "the_BRANDING;
    psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE);
    psh.nStartPage = 0;
    psh.ppsp = psp;
    psh.pfnCallback = NULL;

    return (PropertySheet(&psh) > 0);
}
