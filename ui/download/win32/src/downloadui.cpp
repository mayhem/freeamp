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
	
	$Id: downloadui.cpp,v 1.1.2.2 1999/09/26 03:38:08 elrod Exp $
____________________________________________________________________________*/

/* system headers */
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <math.h>


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

extern "C" SimpleUI *Initialize(FAContext *context)
{
    return new SimpleUI(context);
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


SimpleUI::
SimpleUI(FAContext *context):
     UserInterface()
{
    m_context = context;
    m_prefs = context->prefs;
    m_plm = m_context->plm;
    m_target = m_context->target;
    m_propManager = m_context->props;

    m_uiSemaphore = new Semaphore();

    m_uiThread = Thread::CreateThread();
    m_uiThread->Create(UIThreadFunc,this);

    m_uiSemaphore->Wait();
}

SimpleUI::
~SimpleUI()
{
    delete m_uiSemaphore;
}

void 
SimpleUI::
SetHwnd(HWND hwnd)
{
    m_hwnd = hwnd;

    m_hwndPlay	    = GetDlgItem(m_hwnd, IDC_PLAY);
	m_hwndStop	    = GetDlgItem(m_hwnd, IDC_STOP);
	m_hwndPause	    = GetDlgItem(m_hwnd, IDC_PAUSE);
	m_hwndNext	    = GetDlgItem(m_hwnd, IDC_NEXTSONG);
	m_hwndLast	    = GetDlgItem(m_hwnd, IDC_LASTSONG);
	m_hwndSlider    = GetDlgItem(m_hwnd, IDC_SLIDER);
    m_hwndCurrent   = GetDlgItem(m_hwnd, IDC_CURRENT_TIME);
    m_hwndTotal		= GetDlgItem(m_hwnd, IDC_TOTAL_TIME);
	m_hwndStatus	= GetDlgItem(m_hwnd, IDC_STATUS);
}

int32 
SimpleUI::
AcceptEvent(Event* event)
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

void  
SimpleUI::
ParseArgs(int32 argc, char** argv)
{
    PlaylistManager* Playlist = m_plm;
    char *arg = NULL;
    bool shuffle = false;
    bool autoplay = false;
    int32 count = 0;

    for(int32 i = 1;i < argc; i++) 
    {
	    arg = argv[i];

	    if (arg[0] == '-') 
        {
	        switch (arg[1]) 
            {
		        case 's':
                {
                    shuffle = true;
		            break;
	            } 

                case 'p':
                {
                    autoplay = true;
		            break;
	            } 
            }
        }
        else 
        {
            Playlist->AddItem(arg,0);
            count++;
	    }
    }

    Playlist->SetCurrentIndex(0);

    if(shuffle) 
        Playlist->SetShuffleMode(true);
    
    if(count)
    {
        EnableWindow(m_hwndPlay, TRUE);

        if(count > 1)
			EnableWindow(m_hwndNext, TRUE);
    }
}

void
SimpleUI::
CreateUI()
{
    InitCommonControls();

	DialogBoxParam( g_hInstance, 
                    MAKEINTRESOURCE(IDD_PLAYER),
                    NULL,
                    MainProc, 
                    (LPARAM)this);

    m_target->AcceptEvent(new Event(CMD_QuitPlayer));
}

void 
SimpleUI::
UIThreadFunc(void* arg)
{
    SimpleUI* ui = (SimpleUI*)arg;

    ui->CreateUI();
}

Error 
SimpleUI::
Init(int32 startup_type) 
{ 
    ParseArgs(m_context->argc, m_context->argv);
    return kError_NoErr;
}


BOOL CALLBACK SimpleUI::MainProc(	HWND hwnd, 
						            UINT msg, 
						            WPARAM wParam, 
						            LPARAM lParam )
{
	BOOL result = FALSE;
    static SimpleUI* m_ui = NULL;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			HWND hwndStatus = NULL;
			HWND hwndPlay	= GetDlgItem(hwnd, IDC_PLAY);
			HWND hwndStop	= GetDlgItem(hwnd, IDC_STOP);
			HWND hwndPause	= GetDlgItem(hwnd, IDC_PAUSE);
			HWND hwndNext	= GetDlgItem(hwnd, IDC_NEXTSONG);
			HWND hwndLast	= GetDlgItem(hwnd, IDC_LASTSONG);
			HWND hwndSlider	= GetDlgItem(hwnd, IDC_SLIDER);

			EnableWindow(hwndPlay, FALSE);
			EnableWindow(hwndNext, FALSE);
			EnableWindow(hwndLast, FALSE);

			EnableWindow(hwndStop, FALSE);
			EnableWindow(hwndPause, FALSE);
			EnableWindow(hwndSlider, FALSE);

			hwndStatus= CreateStatusWindow(	WS_CHILD | WS_VISIBLE, 
											"", 
											hwnd, 
											IDC_STATUS);
			const int32 kNumPanes = 3;
			int32 panes[kNumPanes]= {60, 125,-1};

			SendMessage(hwndStatus, SB_SETPARTS, kNumPanes, (LPARAM) panes);

            m_ui = (SimpleUI*)lParam;

            m_ui->SetHwnd(hwnd);

			result = TRUE;

            m_ui->m_uiSemaphore->Signal();

			break;
		}

		case WM_COMMAND:
		{
            static bool isPaused = false;

			switch(wParam)
			{
				case IDC_PLAY:
				{
                    if(isPaused)
                    {
                        m_ui->m_target->AcceptEvent(new Event(CMD_TogglePause));
                        isPaused = false;
                    }
                    else
                    {
                        m_ui->m_target->AcceptEvent(new Event(CMD_Play));
                    }

					break;
				}

				case IDC_PAUSE:
				{
                    isPaused = true;
                    m_ui->m_target->AcceptEvent(new Event(CMD_TogglePause));
					break;
				}

				case IDC_STOP:
				{
                    m_ui->m_target->AcceptEvent(new Event(CMD_Stop));
					break;
				}

				case IDC_NEXTSONG:
				{
                    m_ui->m_target->AcceptEvent(new Event(CMD_NextMediaPiece));
					break;
				}

				case IDC_LASTSONG:
				{
                    m_ui->m_target->AcceptEvent(new Event(CMD_PrevMediaPiece));
					break;
				}

				case IDC_EXIT:
				{
					PostQuitMessage(0);
					break;
				}
			}

			result = TRUE;
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
