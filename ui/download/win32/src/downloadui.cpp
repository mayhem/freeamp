/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 GoodNoise

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
	
	$Id: downloadui.cpp,v 1.1.2.4 1999/09/27 01:51:24 elrod Exp $
____________________________________________________________________________*/

/* system headers */
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <iostream>

using namespace std;



/* project headers */
#include "config.h"
#include "thread.h"
#include "downloadui.h"
#include "event.h"
#include "eventdata.h"
#include "playlist.h"
#include "resource.h"

HINSTANCE g_hInstance = NULL;

BOOL CALLBACK MainProc(	HWND hwnd, 
						UINT msg, 
						WPARAM wParam, 
						LPARAM lParam ); 

extern "C" DownloadUI *Initialize(FAContext *context)
{
    return new DownloadUI(context);
}


INT WINAPI DllMain (HINSTANCE hInst,
                    ULONG ul_reason_being_called,
	                LPVOID lpReserved)
{
	switch (ul_reason_being_called)
	{
		case DLL_PROCESS_ATTACH:
			g_hInstance = hInst;
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


DownloadUI::DownloadUI(FAContext *context):UserInterface()
{
    m_context = context;
    m_prefs = context->prefs;
    m_plm = m_context->plm;
    m_target = m_context->target;
    m_propManager = m_context->props;
    m_dlm = m_context->downloadManager;

    m_uiSemaphore = new Semaphore();

    m_uiThread = Thread::CreateThread();
    m_uiThread->Create(UIThreadFunc,this);

    m_uiSemaphore->Wait();
}

DownloadUI::~DownloadUI()
{
    delete m_uiSemaphore;
}

int32 DownloadUI::AcceptEvent(Event* event)
{
    int32 result = 255;

    if(event) 
    {
        switch(event->Type()) 
        {
	        case CMD_Cleanup: 
            {
	            m_target->AcceptEvent(new Event(INFO_ReadyToDieUI));
	            break; 
            }

	        default:
	            break;
	    }

	    result = 0;

    } 

    return result;
}

void DownloadUI::ParseArgs(int32 argc, char** argv)
{
    char *arg = NULL;
    int32 count = 0;

    for(int32 i = 1;i < argc; i++) 
    {
	    arg = argv[i];

	    if(arg[0] == '-') 
        {
	        //switch(arg[1]) 
            //{
		        
            //}
        }
       
    }
}

void DownloadUI::CreateUI()
{
    InitCommonControls();

	DialogBoxParam( g_hInstance, 
                    MAKEINTRESOURCE(IDD_DIALOG),
                    NULL,
                    MainProc, 
                    (LPARAM)this);

    m_target->AcceptEvent(new Event(CMD_QuitPlayer));
}

void DownloadUI::UIThreadFunc(void* arg)
{
    DownloadUI* ui = (DownloadUI*)arg;

    ui->CreateUI();
}

Error DownloadUI::Init(int32 startup_type) 
{ 
    ParseArgs(m_context->argc, m_context->argv);
    return kError_NoErr;
}

BOOL DownloadUI::InitDialog()
{
    // get hwnds for all my controls
    m_hwndList = GetDlgItem(m_hwnd, IDC_LIST);
    m_hwndInfo = GetDlgItem(m_hwnd, IDC_INFO);
    m_hwndPause = GetDlgItem(m_hwnd, IDC_PAUSE);
    m_hwndCancel = GetDlgItem(m_hwnd, IDC_CANCEL);
    m_hwndResume = GetDlgItem(m_hwnd, IDC_RESUME);
    m_hwndClose = GetDlgItem(m_hwnd, IDC_CLOSE);

    // initialize controls
    // first let's add our columns
    RECT rect;
    GetClientRect(m_hwndList, &rect);

    LV_COLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT; // left align column
    lvc.cx = (rect.right-rect.left)/2; // width of column in pixels
    lvc.pszText = "Song Title";
    lvc.iSubItem = 0;

    ListView_InsertColumn(m_hwndList, 0, &lvc);

    if((rect.right-rect.left)%2) // squeeze out every last pixel :)
        lvc.cx += 1;

    lvc.pszText = "Status";
    lvc.iSubItem = 1;

    ListView_InsertColumn(m_hwndList, 1, &lvc);

    // init the images    
    m_imageList = ImageList_Create(16, 16, ILC_MASK, 1, 0);
    HBITMAP bmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_NOTE));
    ImageList_AddMasked(m_imageList, bmp, RGB(255,0,0));
    DeleteObject(bmp);

    ListView_SetImageList(m_hwndList, m_imageList, LVSIL_SMALL);

    // Add a test item
    LV_ITEM item;

    
    MetaData md;
    md.SetTitle("Trip Like I Do");

    DownloadItem* dli = new DownloadItem("file://c|/temp/t.mp3", "http://www.blah.com", &md);
    dli->SetState(kDownloadItemState_Queued);

    item.mask = LVIF_PARAM | LVIF_STATE;
    item.state = 0;
    item.stateMask = 0;
    item.iItem = 0;
    item.iSubItem = 0;
    item.lParam = (LPARAM)dli;

    ListView_InsertItem(m_hwndList, &item);

    md.SetTitle("That Thing You Do");
    dli = new DownloadItem("file://c|/temp/t.mp3", "http://www.blah.com", &md);
    dli->SetState(kDownloadItemState_Queued);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    m_uiSemaphore->Signal();
    return TRUE;
}

BOOL DownloadUI::DrawItem(int32 controlId, DRAWITEMSTRUCT* dis)
{
    BOOL result = TRUE;

    switch(controlId)
    {
        case IDC_LIST:
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
                // Set the text background and foreground colors to the standard window
                // colors
                SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
            }
      
            rcClip = dis->rcItem;            

            //LV_ITEM* item = (LV_ITEM*)dis->itemData;
            DownloadItem* dli = (DownloadItem*)dis->itemData;

            // Check to see if the string fits in the clip rect.  If not, truncate
            // the string and add "...".
            string displayString = dli->GetMetaData().Title();

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(m_hwndList, 0) - cxImage + 1);

            ExtTextOut( dis->hDC, 
                        rcClip.left + cxImage + 1, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

            // draw the icon
            if (himl)
            {
                ImageList_Draw( himl, 0, dis->hDC, 
                                rcClip.left, rcClip.top,
                                uiFlags);
            }

            // If we changed the colors for the selected item, undo it
            if(dis->itemState & ODS_SELECTED)
            {
                // Set the text background and foreground colors
                SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
            }

            // If the item is focused, now draw a focus rect around the entire row
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


BOOL DownloadUI::Command(int32 command, HWND src)
{
    switch(command)
	{
		case IDC_PAUSE:
		{
			break;
		}

        case IDC_CANCEL:
		{
			break;
		}

        case IDC_RESUME:
		{
			break;
		}

		case IDC_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return TRUE;		
}


BOOL CALLBACK DownloadUI::MainProc(	HWND hwnd, 
						            UINT msg, 
						            WPARAM wParam, 
						            LPARAM lParam )
{
	BOOL result = FALSE;
    static DownloadUI* m_ui = NULL;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
            m_ui = (DownloadUI*)lParam;

            m_ui->SetWindowHandle(hwnd);

            result = m_ui->InitDialog();

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
            if (mis->CtlType != ODT_LISTVIEW)
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

            result =  TRUE;
            break;
        }

        case WM_DRAWITEM:
        {
            result = m_ui->DrawItem(wParam, (DRAWITEMSTRUCT*) lParam);
            break;
        }

		case WM_COMMAND:
		{
            result = m_ui->Command(wParam, (HWND)lParam);
        }

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			result = TRUE;
			break;
		}

        case WM_DESTROY:
        {
            break;
        }
	
	}

	return result;
}

void DownloadUI::CalcStringEllipsis(HDC hdc, string& displayString, uint32 columnWidth)
{
    const TCHAR szEllipsis[] = TEXT("...");
    SIZE   sizeString;
    SIZE   sizeEllipsis;
    string temp;
    
    // Adjust the column width to take into account the edges
    columnWidth -= 4;

    temp = displayString;        

    GetTextExtentPoint32(hdc, temp.c_str(), temp.size(), &sizeString);       

    // If the width of the string is greater than the column width shave
    // the string and add the ellipsis
    if((uint32)sizeString.cx > columnWidth)
    {
        GetTextExtentPoint32(hdc, szEllipsis, strlen(szEllipsis), &sizeEllipsis);
       
        while(temp.size() > 0)
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
        }
    }
}
