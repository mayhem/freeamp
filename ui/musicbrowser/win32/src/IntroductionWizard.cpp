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

        $Id: IntroductionWizard.cpp,v 1.2 1999/12/17 07:53:16 elrod Exp $
____________________________________________________________________________*/

// system includes
#define STRICT
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
            const char* kCaption2 = "What is My Music?";
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

static BOOL CALLBACK IntroWizardSearch(HWND hwnd, 
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
            const char* kCaption1 = "Search Computer For Music";
            const char* kCaption2 = "Where Would You Like to Look for Music?";
            const char* kMsg1 = "In order to populate the My Music Collection pane "
                                BRANDING" will search your computer for supported music "
                                "files. The files will not be moved or modified during "
                                "this process. Their location will be remembered in "
                                "order to provide you with an organized view of your "
                                "music collection.";
                               
            const char* kMsg2 = "By default "BRANDING" will search all the disk drives on "
                                "your computer. If you would like to limit the "
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

bool MusicBrowserUI::IntroductionWizard()
{
    PROPSHEETPAGE psp[2];
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
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_INTROWIZARD_SEARCH);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = IntroWizardSearch;
    psp[1].pszTitle = NULL;
    psp[1].lParam = (LPARAM)0;

    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD | PSH_NOAPPLYNOW;
    psh.hwndParent = m_hWnd;
    psh.hInstance = hinst;
    psh.pszIcon = NULL;
    psh.pszCaption = "Welcome to "BRANDING;
    psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE);
    psh.nStartPage = 0;
    psh.ppsp = psp;
    psh.pfnCallback = NULL;

    return (PropertySheet(&psh) > 0);
}