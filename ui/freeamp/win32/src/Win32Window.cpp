/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic

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

   $Id: Win32Window.cpp,v 1.1.2.8 1999/09/29 20:12:52 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include "Theme.h"
#include "Win32Window.h"
#include "Win32Canvas.h"
#include "debug.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

const static char szAppName[] = "FreeAmp";
HINSTANCE g_hinst = NULL;
#define IDI_EXE_ICON 101


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

static LRESULT WINAPI MainWndProc(HWND hwnd, UINT msg, 
                                  WPARAM wParam, LPARAM lParam )
{
    LRESULT result = 0;
    Win32Window* ui = (Win32Window*)GetWindowLong(hwnd, GWL_USERDATA);

    switch (msg)
    {
        case WM_CREATE:
        {
            // When we create the window we pass in a pointer to our
            // UserInterface object...
            // Tuck away the pointer in a safe place
            
            ui = (Win32Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;

            assert(ui != NULL);
          
            result = SetWindowLong(hwnd, GWL_USERDATA, (LONG)ui);
            ui->Init();
            
            SetTimer(hwnd, 0, 250, NULL);
            
            break;
        }

		case WM_CLOSE:
        {
            Rect oRect;
            Pos  oPos;

            KillTimer(hwnd, 0);
 
            ui->GetWindowPosition(oRect);
            oPos.x = oRect.x1;
            oPos.y = oRect.y1;
            ui->SaveWindowPos(oPos);
            PostQuitMessage(0);
            break;
        }    

		case WM_TIMER:
            ui->TimerEvent();
            break;

        case WM_DESTROY:
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hDc;
            Rect        oRect;
            
        	hDc = BeginPaint(hwnd, &ps);
            oRect.x1 = ps.rcPaint.left;
            oRect.y1 = ps.rcPaint.top;
            oRect.x2 = ps.rcPaint.right;
            oRect.y2 = ps.rcPaint.bottom;
            
            ((Win32Canvas *)(ui->GetCanvas()))->Paint(hDc, oRect);
            EndPaint(hwnd, &ps);
            
            break;
        }    

        case WM_MOUSEMOVE:
        {
            POINT pt;
        	Pos oPos;

            pt.x = (int16)LOWORD(lParam);
            pt.y = (int16)HIWORD(lParam);

            ClientToScreen(hwnd, &pt);
            oPos.x = pt.x;
            oPos.y = pt.y;
            
            ui->HandleMouseMove(oPos);
            break;
        }


        case WM_NCMOUSEMOVE:
        {
        	Pos oPos;
            
        	oPos.x = (int16)LOWORD(lParam);
            oPos.y = (int16)HIWORD(lParam);  
            ui->HandleMouseMove(oPos);

            break;
        }		

        case WM_LBUTTONDOWN:
        {
            POINT pt;
        	Pos oPos;

            pt.x = (int16)LOWORD(lParam);
            pt.y = (int16)HIWORD(lParam);

            ClientToScreen(hwnd, &pt);
            oPos.x = pt.x;
            oPos.y = pt.y;
            
            ui->HandleMouseLButtonDown(oPos);
            
            break;
        }

        case WM_LBUTTONUP:
        {
            POINT pt;
        	Pos oPos;

            pt.x = (int16)LOWORD(lParam);
            pt.y = (int16)HIWORD(lParam);

            ClientToScreen(hwnd, &pt);
            oPos.x = pt.x;
            oPos.y = pt.y;
            
            ui->HandleMouseLButtonUp(oPos);
            
            break;
        }

        default:
            result = DefWindowProc( hwnd, msg, wParam, lParam );
            break;

    }

    return result;
}


Win32Window::Win32Window(Theme *pTheme, string &oName)
            :Window(pTheme, oName)
{
    m_pCanvas = new Win32Canvas(this);
}

Win32Window::~Win32Window(void)
{
    delete m_pCanvas;
    m_pCanvas = NULL;
}

Error Win32Window::Run(Pos &oPos)
{
    WNDCLASS wc;
    MSG      msg;
    Rect     oRect;
    HRGN     hRgn;
    HDC      hDc;
    int      iMaxX, iMaxY;

	m_oWindowPos = oPos;

	m_pCanvas->Init();

    memset(&wc, 0x00, sizeof(WNDCLASS));

    wc.style = CS_OWNDC|CS_DBLCLKS ;
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = g_hinst;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hIcon = LoadIcon( g_hinst, MAKEINTRESOURCE(IDI_EXE_ICON) );
    wc.hbrBackground = NULL;
    wc.lpszClassName = szAppName;

    RegisterClass(&wc);
         
    hDc = GetDC(NULL);
	iMaxX = GetDeviceCaps(hDc, HORZRES);
	iMaxY = GetDeviceCaps(hDc, VERTRES);
    ReleaseDC(NULL, hDc);
    
    GetCanvas()->GetBackgroundRect(oRect);
    
    if (m_oWindowPos.x > iMaxX || m_oWindowPos.x + oRect.Width() < 0)
       m_oWindowPos.x = 0;
    if (m_oWindowPos.y > iMaxY || m_oWindowPos.y + oRect.Height() < 0)
       m_oWindowPos.y = 0;

    m_hWnd = CreateWindow(szAppName, 
                    szAppName,
                    WS_POPUP | WS_VISIBLE | WS_SYSMENU, 
                    m_oWindowPos.x, 
                    m_oWindowPos.y, 
                    oRect.Width(), 
                    oRect.Height(),
                    NULL, 
                    NULL, 
                    g_hinst, 
                    this);

    hRgn = ((Win32Canvas *)m_pCanvas)->GetMaskRgn(); 
    if (hRgn)
        SetWindowRgn(m_hWnd, hRgn, false);

    if( m_hWnd )
    {
        ShowWindow( m_hWnd, SW_NORMAL );
        UpdateWindow( m_hWnd );

        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }
	DestroyWindow(m_hWnd);

	oPos = m_oWindowPos;

    return kError_NoErr;
}			

void Win32Window::SaveWindowPos(Pos &oPos)
{
    m_oWindowPos = oPos;
}									

Error Win32Window::Close(void)
{
	SendMessage(m_hWnd, WM_CLOSE, 0, 0);

    return kError_NoErr;
}

Error Win32Window::Enable(void)
{
	return EnableWindow(m_hWnd, false) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::Disable(void)
{
	return EnableWindow(m_hWnd, true) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::Show(void)
{
	return ShowWindow(m_hWnd, SW_SHOWNORMAL) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::Hide(void)
{
	return ShowWindow(m_hWnd, SW_HIDE) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::SetTitle(string &oTitle)
{
	return SetWindowText(m_hWnd, oTitle.c_str()) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::CaptureMouse(bool bCapture)
{
	if (bCapture)
    {
        SetCapture(m_hWnd);
        return kError_NoErr;
    }
    else    
        return ReleaseCapture() ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::HideMouse(bool bHide)
{
	return ShowCursor(!bHide) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::SetMousePos(Pos &oPos)
{
	return SetCursorPos(oPos.x, oPos.y) ? kError_NoErr : kError_InvalidParam;
}

Error Win32Window::GetMousePos(Pos &oPos)
{
	POINT oPoint;
    BOOL  bRet;
    
    bRet = GetCursorPos(&oPoint);
    oPos.x = oPoint.x;
    oPos.y = oPoint.y;
    
	return bRet ? kError_NoErr : kError_InvalidParam;
}

HWND Win32Window::GetWindowHandle(void)
{
	return m_hWnd;
}

Error Win32Window::SetWindowPosition(Rect &oWindowRect)
{
    MoveWindow(m_hWnd, oWindowRect.x1, oWindowRect.y1,
                       oWindowRect.Width(), oWindowRect.Height(),
                       true);
    return kError_NoErr;
}

Error Win32Window::GetWindowPosition(Rect &oWindowRect)
{
	RECT sRect;
    
    GetWindowRect(m_hWnd, &sRect);
    oWindowRect.x1 = sRect.left;
    oWindowRect.x2 = sRect.right;
    oWindowRect.y1 = sRect.top;
    oWindowRect.y2 = sRect.bottom;

    return kError_NoErr;
}

Error Win32Window::Minimize(void)
{
	ShowWindow(m_hWnd, SW_MINIMIZE);

    return kError_NoErr;
}

Error Win32Window::Restore(void)
{
	ShowWindow(m_hWnd, SW_RESTORE);

    return kError_NoErr;
}