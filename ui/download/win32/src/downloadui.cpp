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
	
	$Id: downloadui.cpp,v 1.1.2.8 1999/09/27 22:54:42 elrod Exp $
____________________________________________________________________________*/

/* system headers */
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/* project headers */
#include "config.h"
#include "thread.h"
#include "downloadui.h"
#include "event.h"
#include "eventdata.h"
#include "playlist.h"
#include "resource.h"

static const int32 kProgressHeight = 8;
static const int32 kProgressWidth = 7;

static const int32 kPrePadding = 4;
static const int32 kElementPadding = 5;
static const int32 kPostPadding = 5;
static const int32 kMinProgressWidth = 3;
static const int32 kTotalPadding = kPrePadding + kElementPadding + kPostPadding;

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

    m_progressBitmap = NULL;

    m_uiSemaphore->Wait();
}

DownloadUI::~DownloadUI()
{
    DeleteObject(m_progressBitmap);
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


    HICON appIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_EXE_ICON));

    SetClassLong(m_hwnd, GCL_HICON, (LONG)appIcon);

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

    lvc.pszText = "";
    lvc.cx = (rect.right-rect.left); // width of column in pixels
    lvc.iSubItem = 0;

    ListView_InsertColumn(m_hwndInfo, 0, &lvc);

    // init the images    
    m_noteImage = ImageList_Create(16, 16, ILC_MASK, 1, 0);
    HBITMAP bmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_NOTE));
    ImageList_AddMasked(m_noteImage, bmp, RGB(255,0,0));
    DeleteObject(bmp);

    m_progressBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_PROGRESS));

    ListView_SetImageList(m_hwndList, m_noteImage, LVSIL_SMALL);

    // Add items to info view
    LV_ITEM item;

    item.mask = LVIF_PARAM | LVIF_STATE;
    item.state = 0;
    item.stateMask = 0;
    item.iSubItem = 0;
    item.lParam = NULL;

    for(int32 i = 0; i < 7; i++)
    {
        item.iItem = i;
        ListView_InsertItem(m_hwndInfo, &item);
    }


    // Add a few test items to the list view
    MetaData md;

    md.SetArtist("The Crystal Method");
    md.SetAlbum("Vegas");
    md.SetGenre("Electronica");
    md.SetTitle("Trip Like I Do");

    DownloadItem* dli = new DownloadItem("http://www.blah.com","a.mp3", &md);
    dli->SetState(kDownloadItemState_Queued);
    dli->SetTotalBytes(2221568);
    dli->SetBytesReceived(54432);

    item.mask = LVIF_PARAM | LVIF_STATE;
    item.state = 0;
    item.stateMask = 0;
    item.iItem = ListView_GetItemCount(m_hwndList);
    item.iSubItem = 0;
    item.lParam = (LPARAM)dli;

    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("The Oneders");
    md.SetAlbum("One Hit Wonders...");
    md.SetGenre("Classic Rock");
    md.SetTitle("That Thing You Do");
    dli = new DownloadItem("http://www.blah.com","b.mp3", &md);
    dli->SetState(kDownloadItemState_Downloading);
    dli->SetTotalBytes(61952);
    dli->SetBytesReceived(32567);

    item.iItem = ListView_GetItemCount(m_hwndList);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("The Glimmers");
    md.SetAlbum("Where are you now?");
    md.SetGenre("Classic Rock");
    md.SetTitle("Rhyme and Reason By the Bank of the River");
    dli = new DownloadItem("http://www.blah.com","c.mp3", &md);
    dli->SetState(kDownloadItemState_Paused);
    dli->SetTotalBytes(1000);
    dli->SetBytesReceived(800);
    item.iItem = ListView_GetItemCount(m_hwndList);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("Various Artist");
    md.SetAlbum("The Commitments");
    md.SetGenre("Sound Track");
    md.SetTitle("Mustang Sally");
    dli = new DownloadItem("http://www.blah.com","d.mp3",  &md);
    dli->SetState(kDownloadItemState_Queued);
    dli->SetTotalBytes(6345634);
    dli->SetBytesReceived(0);
    item.iItem = ListView_GetItemCount(m_hwndList);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("Pink Floyd");
    md.SetAlbum("The Wall");
    md.SetGenre("Classic Rock");
    md.SetTitle("Another Brick in the Wall");
    dli = new DownloadItem("http://www.blah.com","e.mp3", &md);
    dli->SetState(kDownloadItemState_Done);
    dli->SetTotalBytes(245352343);
    dli->SetBytesReceived(245352343);
    item.iItem = ListView_GetItemCount(m_hwndList);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("Guns & Roses");
    md.SetAlbum("Lose Your Illusion, Disc 1");
    md.SetGenre("Hard Rock");
    md.SetTitle("Welcome to the Jungle");
    dli = new DownloadItem("http://www.blah.com", "f.mp3", &md);
    dli->SetState(kDownloadItemState_Cancelled);
    dli->SetTotalBytes(34534343);
    dli->SetBytesReceived(45345);
    item.iItem = ListView_GetItemCount(m_hwndList);
    item.lParam = (LPARAM)dli;
    
    ListView_InsertItem(m_hwndList, &item);

    md.SetArtist("The gang");
    md.SetAlbum("Songs that make your smile");
    md.SetGenre("Classics");
    md.SetTitle("Happy Birthday To You...");
    dli = new DownloadItem("http://www.blah.com", "g.mp3",  &md);
    dli->SetState(kDownloadItemState_Error);
    dli->SetTotalBytes(34534343);
    dli->SetBytesReceived(45345);
    item.iItem = ListView_GetItemCount(m_hwndList);
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
                               ListView_GetColumnWidth(m_hwndList, 0) - (cxImage + 1));

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

            // draw the progress column

            rcClip.left += ListView_GetColumnWidth(m_hwndList, 0);

            int32 progressWidth = 0;

            switch(dli->GetState())
            {
                case kDownloadItemState_Queued:
                {
                    if(!(dis->itemState & ODS_SELECTED))
                        SetTextColor(dis->hDC, RGB(0, 127, 0));

                    ostringstream ost;
                    float total;
                    
                    ost.precision(2);
                    ost.flags(ios_base::fixed);

                    total = dli->GetTotalBytes();

                    if(total >= 1048576)
                    {
                        total /= 1048576;
                        ost << "Queued (" << total << " MB)";
                    }
                    else if(total >= 1024)
                    {
                        total /= 1024;
                        ost << "Queued (" << total << " KB)";
                    }
                    else
                    {
                        ost << "Queued (" << dli->GetTotalBytes() << " Bytes)";
                    }
                   
                    displayString = ost.str();

                    break;
                }

                case kDownloadItemState_Downloading:
                {
                    if(!(dis->itemState & ODS_SELECTED))
                        SetTextColor(dis->hDC, RGB(0, 0, 192));

                    ostringstream ost;
                    float total;
                    float recvd;
                    uint32 percent;
                    
                    ost.precision(2);
                    ost.flags(ios_base::fixed);

                    total = dli->GetTotalBytes();
                    recvd = dli->GetBytesReceived();
                    percent= (uint32)recvd/total*100;

                    if(total >= 1048576)
                    {
                        total /= 1048576;
                        recvd /= 1048576;
                        ost  << percent << "% (" << recvd << " of "<< total << " MB) ";
                    }
                    else if(total >= 1024)
                    {
                        total /= 1024;
                        recvd /= 1024;
                        ost << percent << "% ("<< recvd << " of "<< total << " MB)";
                    }
                    else
                    {
                        ost << percent << "% (" << dli->GetBytesReceived() << " of " << 
                            dli->GetTotalBytes() << " Bytes)";
                    }
                   
                    displayString = ost.str();

                    SIZE stringSize;
                    
                    GetTextExtentPoint32(dis->hDC, displayString.c_str(), 
                                            displayString.size(), &stringSize);
                    
                    int32 leftoverWidth = ListView_GetColumnWidth(m_hwndList, 1) - (stringSize.cx + kTotalPadding);

                    // do we have room to show a progress bar?
                    if(leftoverWidth - kMinProgressWidth > 0)
                    {
                        progressWidth = leftoverWidth; // padding on ends and between elements
                        int32 bmpWidth = (float)(progressWidth - 3) * (float)percent/(float)100;
                        int32 count = bmpWidth/(kProgressWidth);
                        int32 remainder = bmpWidth%(kProgressWidth);

                        //ostringstream debug;
                        //debug << "bmpWidth: " << bmpWidth << endl << "progressWidth: " << progressWidth << endl;
                        //OutputDebugString(debug.str().c_str());

                        HDC memDC = CreateCompatibleDC(dis->hDC);
                        SelectObject(memDC, m_progressBitmap);

                        rcClip.left += kPrePadding;

                        RECT progressRect = rcClip;

                        progressRect.top += ((rcClip.bottom - rcClip.top) - kProgressHeight)/2 - 1;
                        progressRect.bottom = progressRect.top + kProgressHeight + 2;
                        progressRect.right = progressRect.left + progressWidth;


                        if(dis->itemState & ODS_SELECTED)
                        {
                            HBRUSH brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

                            FillRect(dis->hDC, &progressRect, brush);
                            DeleteObject(brush);
                        }

                        DrawEdge(dis->hDC, &progressRect, EDGE_SUNKEN, BF_RECT);

                        uint32 i = 0;

                        for(i = 0; i< count; i++)
                        {
                            BitBlt(dis->hDC, progressRect.left + 2 + i*kProgressWidth, progressRect.top + 2, kProgressWidth, kProgressHeight, 
                                   memDC, 0, 0, SRCCOPY);

                        }

                        if(remainder)
                        {
                            BitBlt(dis->hDC, progressRect.left + 2 + i*kProgressWidth, progressRect.top + 2, remainder, kProgressHeight, 
                                   memDC, 0, 0, SRCCOPY);
                        }


                        DeleteDC(memDC);
                    }

                    break;
                }

                case kDownloadItemState_Cancelled:
                    if(!(dis->itemState & ODS_SELECTED))
                        SetTextColor(dis->hDC, RGB(192, 0, 0));

                    displayString = "Cancelled";
                    break;
                case kDownloadItemState_Paused:
                {
                    if(!(dis->itemState & ODS_SELECTED))
                        SetTextColor(dis->hDC, RGB(0, 128, 128));

                    ostringstream ost;
                    float total;
                    float recvd;
                    uint32 percent;
                    
                    ost.precision(2);
                    ost.flags(ios_base::fixed);

                    total = dli->GetTotalBytes();
                    recvd = dli->GetBytesReceived();
                    percent= (uint32)recvd/total*100;

                    if(total >= 1048576)
                    {
                        total /= 1048576;
                        recvd /= 1048576;
                        ost << "Paused (" << recvd << " of "<< total << " MB - " << percent << "%)";
                    }
                    else if(total >= 1024)
                    {
                        total /= 1024;
                        recvd /= 1024;
                        ost << "Paused (" << recvd << " of "<< total << " MB - " << percent << "%)";
                    }
                    else
                    {
                        ost << "Paused (" << dli->GetBytesReceived() << " of " << 
                            dli->GetTotalBytes() << " Bytes - " << percent << "%)";
                    }
                   
                    displayString = ost.str();

                    break;
                }

                case kDownloadItemState_Error:
                    if(!(dis->itemState & ODS_SELECTED))
                        SetTextColor(dis->hDC, RGB(192, 0, 0));

                    displayString = "Error";
                    break;

                case kDownloadItemState_Done:
                    displayString = "Download Complete";
                    break;

                default:
                    break;
            }

            uint32 pad = 0;

            if(progressWidth)
                pad = (progressWidth + kElementPadding);

            CalcStringEllipsis(dis->hDC, 
                               displayString, 
                               ListView_GetColumnWidth(m_hwndList, 1) - pad);

            rcClip.left += pad;

            ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

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

        case IDC_INFO:
        {
            SetTextColor(dis->hDC, RGB(0, 0, 128));
            SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
            string displayString;

            string longestString = "File Name :";

            SIZE stringSize;
                    
            GetTextExtentPoint32(dis->hDC, longestString.c_str(), 
                                    longestString.size(), &stringSize);

            uint32 dataOffset = stringSize.cx + 15;


            RECT rcClip = dis->rcItem;  

            rcClip.left += 2;

            uint32 itemCount =  ListView_GetItemCount(m_hwndList);
            DownloadItem* dli = NULL;

            ostringstream debug;
            //debug << "itemCount: " << itemCount << endl;
            //OutputDebugString(debug.str().c_str());

            if(itemCount)
            {
                LV_ITEM item;

                for(uint32 i = 0; i < itemCount; i++)
                {
                    if(ListView_GetItemState(m_hwndList, i, LVIS_FOCUSED) & LVIS_FOCUSED)
                    {
                        item.mask = LVIF_PARAM;
                        item.iItem = i;
                        item.lParam = 0;

                        if(ListView_GetItem(m_hwndList, &item))
                        {
                            dli = (DownloadItem*)item.lParam;
                            break;
                        }
                    }
                }

                if(!dli)
                {
                    item.mask = LVIF_PARAM;
                    item.iItem = 0;
                    item.lParam = 0;

                    ListView_GetItem(m_hwndList, &item);

                    dli = (DownloadItem*)item.lParam;
                }
            }

            switch(dis->itemID)
            {
                case 0:
                {
                    displayString = "Artist :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->GetMetaData().Artist();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    break;
                }

                case 1:
                {
                    displayString = "Album :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->GetMetaData().Album();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);
                    break;
                }

                case 2:
                {
                    displayString = "Title :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->GetMetaData().Title();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);
                    break;
                }

                case 3:
                {
                    displayString = "Genre :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->GetMetaData().Genre();


                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);
                    break;
                }

                case 4:
                {
                    displayString = "Playlist :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->PlaylistName();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);
                    break;
                }

                case 5:
                {
                    displayString = "File Name :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    displayString = "";

                    if(dli)
                        displayString = dli->DestinationFile();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);
                    break;
                }

                case 6:
                {
                    displayString = "File Size :";
                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    rcClip.left = dis->rcItem.left + dataOffset;

                    ostringstream ost;
                    float total;
                    
                    ost.precision(2);
                    ost.flags(ios_base::fixed);

                    total = dli->GetTotalBytes();

                    if(total >= 1048576)
                    {
                        total /= 1048576;
                        ost <<  total << " MB";
                    }
                    else if(total >= 1024)
                    {
                        total /= 1024;
                        ost  << total << " KB";
                    }
                    else
                    {
                        ost <<  dli->GetTotalBytes() << " Bytes";
                    }
                   
                    displayString = ost.str();

                    SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));

                    ExtTextOut( dis->hDC, 
                        rcClip.left, rcClip.top + 1, 
                        ETO_CLIPPED | ETO_OPAQUE,
                        &rcClip, 
                        displayString.c_str(),
                        displayString.size(),
                        NULL);

                    break;
                }
            }

            SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
            SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));

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

BOOL DownloadUI::Notify(int32 controlId, NMHDR* nmh)
{
    BOOL result = TRUE;

    switch(controlId)
    {
        case IDC_LIST:
        {
            NM_LISTVIEW* nmlv = (NM_LISTVIEW*)nmh;

            if(nmh->code == LVN_ITEMCHANGED)
            {
                 ListView_RedrawItems(m_hwndInfo, 0, ListView_GetItemCount(m_hwndInfo) - 1);
                 //OutputDebugString("LVN_ITEMCHANGING\r\n");
            }

            break;
        }

    }

    return result;
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

        case WM_INITMENUPOPUP:
        {
            HMENU menuPopup = (HMENU)wParam;
            BOOL fSystemMenu = (BOOL) HIWORD(lParam);

            if(fSystemMenu)
            {
                int32 count = GetMenuItemCount(menuPopup);

                for(int32 i = 0; i < count; i++)
                {
                    int32 id = GetMenuItemID(menuPopup, i);

                    if(61488 == id || id == 61440) // MAXIMIZE & SIZE COMMAND
                    {
                        EnableMenuItem(menuPopup, id, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
                    }
                }
            }

            result = TRUE;
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
            if (mis->CtlType != ODT_LISTVIEW || mis->CtlID == IDC_INFO)
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
            break;
        }       

        case WM_NOTIFY:
        {
            result = m_ui->Notify(wParam, (NMHDR*)lParam);
            break;
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

uint32 DownloadUI::CalcStringEllipsis(HDC hdc, string& displayString, int32 columnWidth)
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
