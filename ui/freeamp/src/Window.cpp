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

   $Id: Window.cpp,v 1.1.2.4 1999/09/17 20:31:03 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <algorithm>
#include "Window.h"
#include "Theme.h"

Window::Window(Theme *pTheme, string &oName)
{
    m_oName = oName;
    m_bExit = false;
    m_pTheme = pTheme;
	m_bMouseButtonDown = false;

    m_pCanvas = NULL;
    m_pMouseInControl = NULL;
    m_pCaptureControl = NULL;
}

Window::~Window(void)
{
    m_oMutex.Acquire();

    while(m_oControls.size() > 0)
    {
        delete m_oControls[0];
        m_oControls.erase(m_oControls.begin());
    }

    delete m_pCanvas;
    m_oMutex.Release();
}

void Window::Init(void)
{
    ControlMapIterator i;

    for(i = m_oControlMap.begin(); i != m_oControlMap.end(); i++)
        (*i).second->Init();
}

void Window::AddControl(Control *pControl)
{
    string oName;

    m_oMutex.Acquire();

    pControl->GetName(oName);
    m_oControlMap[oName] = pControl;
    m_oControls.push_back(pControl);

    m_oMutex.Release();
}

Canvas *Window::GetCanvas(void)
{
    return m_pCanvas;
}

void Window::GetName(string &oName)
{
    m_oMutex.Acquire();

    oName = m_oName;

    m_oMutex.Release();
}

Error Window::ControlEnable(string &oTarget, bool bSet, bool &bEnable)
{
    Control *pControl;

    pControl = m_oControlMap[oTarget];
    if (pControl == NULL)
       return kError_InvalidParam;

    return pControl->Enable(bSet, bEnable);
}

Error Window::ControlShow(string &oTarget, bool bSet, bool &bShow)
{
    Control *pControl;

    pControl = m_oControlMap[oTarget];
    if (pControl == NULL)
       return kError_InvalidParam;

    return pControl->Show(bSet, bShow);
}

Error Window::ControlIntValue(string &oTarget, bool bSet, int &iValue)
{
    Control *pControl;

    pControl = m_oControlMap[oTarget];
    if (pControl == NULL)
       return kError_InvalidParam;

    return pControl->IntValue(bSet, iValue);
}

Error Window::ControlStringValue(string &oTarget, bool bSet, string &oValue)
{
    Control *pControl;

    pControl = m_oControlMap[oTarget];
    if (pControl == NULL)
       return kError_InvalidParam;

    return pControl->StringValue(bSet, oValue);
}

Error Window::SendControlMessage(Control *pControl, 
                                 ControlMessageEnum eMesg)
{
	string oControlName;
    
    pControl->GetName(oControlName);

    return m_pTheme->HandleControlMessage(oControlName, eMesg);
}

Control *Window::ControlFromPos(Pos &oPos)
{
    ControlMapIterator i;

    for(i = m_oControlMap.begin(); i != m_oControlMap.end(); i++)
    {
        if ((*i).second->PosInControl(oPos))
            return (*i).second;
    }

    return NULL;
}

Error Window::StartMouseCapture(Control *pControl)
{
    m_pCaptureControl = pControl;
    return CaptureMouse(true);
}

Error Window::EndMouseCapture(void)
{
    m_pCaptureControl = NULL;
    return CaptureMouse(false);
}

void Window::HandleMouseMove(Pos &oPos)
{
    Control *pControl;

	if (m_bMouseButtonDown)
    {
       Rect oRect;
       Pos  oScreenPos;
       
       GetWindowPosition(oRect);
       oScreenPos.x = oRect.x1 + oPos.x;
       oScreenPos.y = oRect.y1 + oPos.y;

       oRect.x1 += (oScreenPos.x - m_oMovePos.x);
       oRect.x2 += (oScreenPos.x - m_oMovePos.x);
       oRect.y1 += (oScreenPos.y - m_oMovePos.y);
       oRect.y2 += (oScreenPos.y - m_oMovePos.y);
       SetWindowPosition(oRect);

       m_oMovePos = oScreenPos;
       
       return; 
	}

    if (m_pCaptureControl)
    {
       m_pCaptureControl->AcceptTransition(CT_MouseMove, &oPos);
       return;
    }

    pControl = ControlFromPos(oPos);
    if (pControl)
    {
       if (m_pMouseInControl && m_pMouseInControl != pControl)
       {
           m_pMouseInControl->AcceptTransition(CT_MouseLeave);
           m_pMouseInControl = pControl;
           m_pMouseInControl->AcceptTransition(CT_MouseEnter);
       }

       if (m_pMouseInControl == NULL)
       {
           m_pMouseInControl = pControl;
           m_pMouseInControl->AcceptTransition(CT_MouseEnter);
       }

       pControl->AcceptTransition(CT_MouseMove, &oPos);
       return;
    }
    else
    {
       if (m_pMouseInControl)
       {
           m_pMouseInControl->AcceptTransition(CT_MouseLeave);
           m_pMouseInControl = NULL;
       }
    }

    return;
}

void Window::HandleMouseLButtonDown(Pos &oPos)
{
    Control *pControl;
    Rect     oRect;

    if (m_pCaptureControl)
    {
       m_pCaptureControl->AcceptTransition(CT_MouseLButtonDown, &oPos);
       return;
    }

    pControl = ControlFromPos(oPos);
    if (pControl)
    {
       pControl->AcceptTransition(CT_MouseLButtonDown, &oPos);
       return;
    }

	m_bMouseButtonDown = true;
    CaptureMouse(true);
       
    GetWindowPosition(oRect);
    m_oMovePos.x = oRect.x1 + oPos.x;
    m_oMovePos.y = oRect.y1 + oPos.y;

    return;
}

void Window::HandleMouseLButtonUp(Pos &oPos)
{
    Control *pControl;

	if (m_bMouseButtonDown)
    {
       m_bMouseButtonDown = false;
       CaptureMouse(false);
          
       return; 
	}
    
    if (m_pCaptureControl)
    {
       m_pCaptureControl->AcceptTransition(CT_MouseLButtonUp, &oPos);
       return;
    }

    pControl = ControlFromPos(oPos);
    if (pControl)
    {
       pControl->AcceptTransition(CT_MouseLButtonUp, &oPos);
       return;
    }

    return;
}

