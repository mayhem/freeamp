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
	
	$Id: prefdialog.cpp,v 1.3 1999/04/07 01:09:01 elrod Exp $
____________________________________________________________________________*/

/* system headers */
#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdlib.h>
#include <assert.h>

/* project headers */
#include "config.h"
#include "prefdialog.h"
#include "preferences.h"
#include "log.h"
#include "registrar.h"
#include "resource.h"

typedef struct PrefValues {
    // page 1
    char defaultUI[256];
    char defaultPMO[256];
    int32 inputBufferSize;
    int32 outputBufferSize;
    int32 streamInterval;
    int32 decoderThreadPriority;
    bool stayOnTop;
    bool minimizeToTray;

    // page2
    bool enableLogging;
    bool logMain;
    bool logInput;
    bool logOutput;
    bool logDecoder;
    bool logPerformance;

    PrefValues()
    {
        memset(defaultUI, 0x00, sizeof(defaultUI));
        memset(defaultPMO, 0x00, sizeof(defaultPMO));
    }

}PrefValues;

static PrefValues originalValues;
static PrefValues currentValues;


static 
void 
SavePrefValues( Preferences* prefs, 
                PrefValues* values)
{
    prefs->SetDefaultPMO(values->defaultPMO);
    prefs->SetDefaultUI(values->defaultUI);
    prefs->SetDecoderThreadPriority(values->decoderThreadPriority);
    prefs->SetInputBufferSize(values->inputBufferSize);
    prefs->SetOutputBufferSize(values->outputBufferSize);
    prefs->SetStreamBufferInterval(values->streamInterval);
    prefs->SetStayOnTop(values->stayOnTop);
    prefs->SetMinimizeToTray(values->minimizeToTray);
    prefs->SetUseDebugLog(values->enableLogging);
    prefs->SetLogMain(values->logMain);
    prefs->SetLogDecode(values->logDecoder);
    prefs->SetLogInput(values->logInput);
    prefs->SetLogOutput(values->logOutput);
    prefs->SetLogPerformance(values->logPerformance);

}

static
BOOL 
CALLBACK 
PrefPage1Proc(  HWND hwnd, 
                UINT msg, 
                WPARAM wParam, 
                LPARAM lParam)
{
    UINT result = 0;
    static PROPSHEETPAGE* psp = NULL;
    static Preferences* prefs = NULL;
    static HWND hwndUI = NULL;
    static HWND hwndPMO = NULL;
    static HWND hwndPriority = NULL;
    static HWND hwndInput = NULL;
    static HWND hwndOutput = NULL;
    static HWND hwndStreamInterval = NULL;
    static HWND hwndStayOnTop = NULL;
    static HWND hwndMinimizeToTray = NULL;
    

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            // remember these for later...
            psp = (PROPSHEETPAGE*)lParam;
            prefs = (Preferences*)psp->lParam;

            // get the handles to all our controls
            hwndUI = GetDlgItem(hwnd, IDC_UI);
            hwndPMO = GetDlgItem(hwnd, IDC_PMO);
            hwndPriority = GetDlgItem(hwnd, IDC_PRIORITY);
            hwndInput = GetDlgItem(hwnd, IDC_INPUT);
            hwndOutput = GetDlgItem(hwnd, IDC_OUTPUT);
            hwndStreamInterval = GetDlgItem(hwnd, IDC_STREAM_INTERVAL);
            hwndStayOnTop = GetDlgItem(hwnd, IDC_STAYONTOP);
            hwndMinimizeToTray = GetDlgItem(hwnd, IDC_TRAY);

            // get registries
            Registrar registrar;
            Registry pmo;
            Registry ui;

            registrar.SetSubDir("plugins");
            registrar.SetSearchString("*.pmo");
            registrar.InitializeRegistry(&pmo, prefs);
            registrar.SetSearchString("*.ui");
            registrar.InitializeRegistry(&ui, prefs);

            // initialize our controls

            int32 i = 0;
            RegistryItem *item;

            char temp[256];
            uint32 size = sizeof(temp);

            prefs->GetDefaultPMO(temp, &size);
            strcpy(originalValues.defaultPMO, temp);

            while(item = pmo.GetItem(i++))
            {
                ComboBox_AddString(hwndPMO, item->Name());

                if(!strcmp(temp, item->Name()))
                {
                    ComboBox_SetCurSel(hwndPMO, i-1);
                }
            }
            
            i = 0;
            prefs->GetDefaultUI(temp, &size);
            strcpy(originalValues.defaultUI, temp);

            while(item = ui.GetItem(i++))
            {
                ComboBox_AddString(hwndUI, item->Name());

                if(!strcmp(temp, item->Name()))
                {
                    ComboBox_SetCurSel(hwndUI, i-1);
                }
            }
            int32 priority;

            prefs->GetDecoderThreadPriority(&priority);
            originalValues.decoderThreadPriority = priority;

            SendMessage(hwndPriority, 
                        TBM_SETRANGE, 
                        (WPARAM) TRUE,                   
                        (LPARAM) MAKELONG(0, 3));

            SendMessage(hwndPriority, 
                        TBM_SETPOS, 
                        (WPARAM) TRUE,                   
                        (LPARAM) priority);

            int32 value;

            prefs->GetInputBufferSize(&value);
            sprintf(temp, "%d", value);
            Edit_LimitText(hwndInput, 4);
            Edit_SetText(hwndInput, temp);
            originalValues.inputBufferSize = value;

            prefs->GetOutputBufferSize(&value);
            sprintf(temp, "%d", value);
            Edit_LimitText(hwndOutput, 4);
            Edit_SetText(hwndOutput, temp);
            originalValues.outputBufferSize = value;

            prefs->GetStreamBufferInterval(&value);
            sprintf(temp, "%d", value);
            Edit_LimitText(hwndStreamInterval, 2);
            Edit_SetText(hwndStreamInterval, temp);
            originalValues.streamInterval = value;

            prefs->GetStayOnTop(&originalValues.stayOnTop);
            Button_SetCheck(hwndStayOnTop, originalValues.stayOnTop);

            prefs->GetMinimizeToTray(&originalValues.minimizeToTray);
            Button_SetCheck(hwndMinimizeToTray, originalValues.minimizeToTray);

            currentValues = originalValues;
            
            break;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_PMO:
                {
                    if(HIWORD(wParam) == CBN_CLOSEUP)
                    {
                        memset(currentValues.defaultPMO, 0x00, 256);
                        ComboBox_GetText(   hwndPMO, 
                                            currentValues.defaultPMO, 
                                            256);

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }

                    break;
                }

                case IDC_UI:
                {
                    if(HIWORD(wParam) == CBN_CLOSEUP)
                    {
                        memset(currentValues.defaultUI, 0x00, 256);
                        ComboBox_GetText(   hwndUI, 
                                            currentValues.defaultUI, 
                                            256);

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }

                    break;
                }

                case IDC_INPUT:
                {
                    if(HIWORD(wParam) == EN_CHANGE)
                    {
                        char text[128];

                        Edit_GetText(hwndInput, text, sizeof(text));

                        currentValues.inputBufferSize = atoi(text);

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }

                    break;
                }

                case IDC_OUTPUT:
                {
                    if(HIWORD(wParam) == EN_CHANGE)
                    {
                        char text[128];

                        Edit_GetText(hwndOutput, text, sizeof(text));

                        currentValues.outputBufferSize = atoi(text);

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }

                    break;
                }

                case IDC_STREAM_INTERVAL:
                {
                    if(HIWORD(wParam) == EN_CHANGE)
                    {
                        char text[128];

                        Edit_GetText(hwndStreamInterval, text, sizeof(text));

                        currentValues.streamInterval = atoi(text);

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }

                    break;
                }

                case IDC_STAYONTOP:
                {
                    if(Button_GetCheck(hwndStayOnTop) == BST_CHECKED)
                    {
                        currentValues.stayOnTop = true;
                    }
                    else
                    {
                        currentValues.stayOnTop = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_TRAY:
                {
                    if(Button_GetCheck(hwndMinimizeToTray) == BST_CHECKED)
                    {
                        currentValues.minimizeToTray = true;
                    }
                    else
                    {
                        currentValues.minimizeToTray = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }
            }

            break;
        }

        case WM_HSCROLL:
		{
			LRESULT position;
            HWND hwndScroll = (HWND) lParam;

			switch (LOWORD(wParam)) 
			{
				case TB_LINEUP:
				case TB_LINEDOWN:
				case TB_PAGEDOWN:
				case TB_PAGEUP:
				case TB_THUMBPOSITION:
                case TB_THUMBTRACK:
				{
                    if(hwndScroll == hwndPriority)
                    {
		  			    position = SendMessage(	hwndScroll, 
											    TBM_GETPOS, 
											    0, 
											    0);

                        currentValues.decoderThreadPriority = position;

                        if(memcmp(  &originalValues, 
                                    &currentValues, 
                                    sizeof(PrefValues)))
                        {
                            PropSheet_Changed(GetParent(hwnd), hwnd);
                        }
                        else
                        {
                            PropSheet_UnChanged(GetParent(hwnd), hwnd);
                        }
                    }
                }
			}

			break;
        }

        case WM_NOTIFY:
        {
            NMHDR* notify = (NMHDR*)lParam;

            switch(notify->code)
            {
                case PSN_SETACTIVE:
                {
                    
                    break;
                }

                case PSN_APPLY:
                {
                    SavePrefValues(prefs, &currentValues);
                    break;
                }

                case PSN_KILLACTIVE:
                {
                    
                    break;
                }

                case PSN_RESET:
                {
                    SavePrefValues(prefs, &originalValues);
                    break;
                }
            }

            break;
        }
    }

    return result;
}

static
BOOL 
CALLBACK 
PrefPage2Proc(  HWND hwnd, 
                UINT msg, 
                WPARAM wParam, 
                LPARAM lParam)
{
    UINT result = 0;
    static PROPSHEETPAGE* psp = NULL;
    static Preferences* prefs = NULL;
    static HWND hwndLog = NULL;
    static HWND hwndLogDecoder = NULL;
    static HWND hwndLogInput = NULL;
    static HWND hwndLogOutput = NULL;
    static HWND hwndLogMain = NULL;
    static HWND hwndLogPerformance = NULL;
    
    switch(msg)
    {
        case WM_INITDIALOG:
        {
            // remember these for later...
            psp = (PROPSHEETPAGE*)lParam;
            prefs = (Preferences*)psp->lParam;

            // get the handles to all our controls
            hwndLog = GetDlgItem(hwnd, IDC_LOG);
            hwndLogDecoder = GetDlgItem(hwnd, IDC_LOGDECODER);
            hwndLogInput = GetDlgItem(hwnd, IDC_LOGINPUT);
            hwndLogOutput = GetDlgItem(hwnd, IDC_LOGOUTPUT);
            hwndLogMain = GetDlgItem(hwnd, IDC_LOGMAIN);
            hwndLogPerformance = GetDlgItem(hwnd, IDC_LOGPERFORMANCE);

            // initialize our controls
            bool value;

            prefs->GetUseDebugLog(&value);
            originalValues.enableLogging = value;
            Button_SetCheck(hwndLog, value); 
            Button_Enable(hwndLogDecoder, value); 
            Button_Enable(hwndLogInput, value);
            Button_Enable(hwndLogOutput, value);
            Button_Enable(hwndLogMain, value);
            Button_Enable(hwndLogPerformance, value);

            prefs->GetLogMain(&value);
            originalValues.logMain = value;
            Button_SetCheck(hwndLogMain, value); 

            prefs->GetLogDecode(&value);
            originalValues.logDecoder = value;
            Button_SetCheck(hwndLogDecoder, value); 

            prefs->GetLogInput(&value);
            originalValues.logInput = value;
            Button_SetCheck(hwndLogInput, value); 

            prefs->GetLogOutput(&value);
            originalValues.logOutput = value;
            Button_SetCheck(hwndLogOutput, value); 

            prefs->GetLogPerformance(&value);
            originalValues.logPerformance = value;
            Button_SetCheck(hwndLogPerformance, value); 
           
            currentValues = originalValues;
            
            break;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_LOG:
                {
                    BOOL enabled;

                    if(Button_GetCheck(hwndLog) == BST_CHECKED)
                    {
                        currentValues.enableLogging = true;
                       
                    }
                    else
                    {
                        currentValues.enableLogging = false;
                    }

                    enabled = (currentValues.enableLogging ? TRUE : FALSE);

                    Button_Enable(hwndLogDecoder, enabled); 
                    Button_Enable(hwndLogInput, enabled);
                    Button_Enable(hwndLogOutput, enabled);
                    Button_Enable(hwndLogMain, enabled);
                    Button_Enable(hwndLogPerformance, enabled);

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_LOGDECODER:
                {
                    if(Button_GetCheck(hwndLogDecoder) == BST_CHECKED)
                    {
                        currentValues.logDecoder = true;
                    }
                    else
                    {
                        currentValues.logDecoder = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_LOGINPUT:
                {
                    if(Button_GetCheck(hwndLogInput) == BST_CHECKED)
                    {
                        currentValues.logInput = true;
                    }
                    else
                    {
                        currentValues.logInput = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_LOGOUTPUT:
                {
                    if(Button_GetCheck(hwndLogOutput) == BST_CHECKED)
                    {
                        currentValues.logOutput = true;
                    }
                    else
                    {
                        currentValues.logOutput = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_LOGPERFORMANCE:
                {
                    if(Button_GetCheck(hwndLogPerformance) == BST_CHECKED)
                    {
                        currentValues.logPerformance = true;
                    }
                    else
                    {
                        currentValues.logPerformance = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }

                case IDC_LOGMAIN:
                {
                    if(Button_GetCheck(hwndLogMain) == BST_CHECKED)
                    {
                        currentValues.logMain = true;
                    }
                    else
                    {
                        currentValues.logMain = false;
                    }

                    if(memcmp(  &originalValues, 
                                &currentValues, 
                                sizeof(PrefValues)))
                    {
                        PropSheet_Changed(GetParent(hwnd), hwnd);
                    }
                    else
                    {
                        PropSheet_UnChanged(GetParent(hwnd), hwnd);
                    }

                    break;
                }
            }

            break;
        }

        case WM_NOTIFY:
        {
            NMHDR* notify = (NMHDR*)lParam;

            switch(notify->code)
            {
                case PSN_SETACTIVE:
                {
                    
                    break;
                }

                case PSN_APPLY:
                {
                    SavePrefValues(prefs, &currentValues);
                    break;
                }

                case PSN_KILLACTIVE:
                {
                    
                    break;
                }

                case PSN_RESET:
                {
                    SavePrefValues(prefs, &originalValues);
                    break;
                }
            }

            break;
        }
    }

    return result;
}

bool DisplayPreferences(HWND hwndParent)
{
    bool result = false;
    PROPSHEETPAGE psp[2];
    PROPSHEETHEADER psh;
    HINSTANCE hinst = (HINSTANCE)GetWindowLong(hwndParent, GWL_HINSTANCE);
    Preferences prefs;

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = 0;
    psp[0].hInstance = hinst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_PREF1);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = PrefPage1Proc;
    psp[0].pszTitle = NULL;
    psp[0].lParam = (LPARAM)&prefs;

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = 0;
    psp[1].hInstance = hinst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_PREF2);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = PrefPage2Proc;
    psp[1].pszTitle = NULL;
    psp[1].lParam = (LPARAM)&prefs;

    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE;
    psh.hwndParent = hwndParent;
    psh.hInstance = hinst;
    psh.pszIcon = NULL;
    psh.pszCaption = "FreeAmp Preferences";
    psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE);
    psh.ppsp = psp;

    result = (PropertySheet(&psh) > 0);

    return result;
}