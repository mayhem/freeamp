/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Portions Copyright (C) 1999 EMusic

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

   $Id: Control.cpp,v 1.1.2.2 1999/09/08 22:46:27 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include "Control.h"
#include "Window.h"

#ifdef WIN32
#pragma warning(disable:4786)
#endif

Control::Control(Window *pWindow, string &oName, const TransitionInfo *pInfo)
{
    int iLoop;

    m_pParent = pWindow;
    m_eCurrentState = CS_Normal;
    m_eLastState = CS_LastState; 
    m_oName = oName; 
    m_bShow = true;
    m_bEnable = true;
    m_iValue = 0;

    for(iLoop = 0; ; iLoop++, pInfo++)
    {
        if (pInfo->eState == CS_LastState)
            break;

        m_oTransitions.push_back(*pInfo);
    }
}

Control::~Control(void)
{
}

Error Control::Show(bool bSet, bool &bShow)
{
    if (bSet)
    {
        m_bShow = bShow;
        AcceptTransition(bShow ? CT_Show : CT_Hide);
    }
    else
        bShow = m_bShow;

    return kError_NoErr;
}

Error Control::Enable(bool bSet, bool &bEnable)
{
    if (bSet)
    {
        m_bEnable = bEnable;
        AcceptTransition(bEnable ? CT_Enable : CT_Disable);
    }
    else
        bEnable = m_bEnable;

    return kError_NoErr;
}

Error Control::IntValue(bool bSet, int &iValue)
{
    if (bSet)
    {
        m_iValue = iValue;
        AcceptTransition(CT_SetValue);
    }
    else
        iValue = m_iValue;

    return kError_NoErr;
}

Error Control::StringValue(bool bSet, string &oValue)
{
    if (bSet)
    {
        m_oValue = oValue;
        AcceptTransition(CT_SetValue);
    }
    else
        oValue = m_oValue;

    return kError_NoErr;
}

void Control::AcceptTransition(ControlTransitionEnum eTrans, Pos *pPos)
{
    vector<TransitionInfo>::iterator i;

    for(i = m_oTransitions.begin(); i < m_oTransitions.end(); i++)
    {
        if ((*i).eState == m_eCurrentState && (*i).eAction == eTrans)   
        {
            m_eLastState = m_eCurrentState;
            m_eCurrentState = (*i).eNextState;
            Transition(eTrans, pPos);

            return;
        }
    }
}

void Control::SetRect(Rect &oRect)
{
    m_oRect = oRect;
}

void Control::SetBitmap(Bitmap *pBitmap, Rect &oBitmapRect)
{
    m_pBitmap = pBitmap;
    m_oBitmapRect = oBitmapRect;
}

void Control::GetName(string &oName)
{
    oName = m_oName;
};

void Control::Erase(void)
{
    Canvas *pCanvas;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->Erase(m_oRect);
}

void Control::BlitFrame(int iFrame, int iNumFramesInBitmap, Rect *pRect)
{
    Canvas *pCanvas;
    int     iFrameWidth;
    Rect    oFrameRect, oDestRect;

    if (pRect == NULL)
        oDestRect = m_oRect;
    else
        oDestRect = *pRect;

    iFrameWidth = m_oBitmapRect.Width() / iNumFramesInBitmap;
    oFrameRect = m_oBitmapRect;
    oFrameRect.x1 += iFrame * iFrameWidth;
    oFrameRect.x2 = oFrameRect.x1 + iFrameWidth;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->BlitRect(m_pBitmap, oFrameRect, oDestRect);
}

bool Control::PosInControl(Pos &oPos)
{
    return m_oRect.IsPosInRect(oPos);
}
