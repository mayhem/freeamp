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
	
	$Id: downloadui.cpp,v 1.1.2.3 1999/09/26 06:33:17 elrod Exp $
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
    
    m_uiSemaphore->Signal();

    return TRUE;
}


BOOL DownloadUI::Command(int32 command, HWND src)
{
    switch(command)
	{
		case IDC_PLAY:
		{
			break;
		}

		case IDC_EXIT:
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

		case WM_COMMAND:
		{
            m_ui->Command(wParam, (HWND)lParam);
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
