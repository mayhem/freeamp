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

   $Id: SliderControl.cpp,v 1.1.2.3 1999/09/08 23:26:40 elrod Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "SliderControl.h"
#include "Window.h"

// Bitmap Info:
// Frame 0: Normal slider
// Frame 1: Selected slider
// Frame 2: Disabled slider

static const TransitionInfo pTransitions[] =
{  
    { CS_Normal,    CT_MouseEnter,       CS_MouseOver }, 
    { CS_Normal,    CT_Disable,          CS_Disabled  }, 
    { CS_Normal,    CT_Hide,             CS_Hidden    },
    { CS_MouseOver, CT_MouseLeave,       CS_Normal    }, 
    { CS_MouseOver, CT_MouseLButtonDown, CS_Dragging  }, 
    { CS_MouseOver, CT_Disable,          CS_Disabled  }, 
    { CS_Dragging,  CT_MouseMove,        CS_Dragging  }, 
    { CS_Dragging,  CT_MouseLButtonUp,   CS_MouseOver }, 
    { CS_Disabled , CT_Enable,           CS_Normal    },
    { CS_Hidden,    CT_Show,             CS_Normal    },
    { CS_LastState, CT_LastTransition,   CS_LastState }
};

SliderControl::SliderControl(Window *pWindow, string &oName) :
               Control(pWindow, oName, pTransitions)
{
     m_iRange = -1;
     m_iCurrentPos = 0;
};

SliderControl::~SliderControl(void)
{

}

void SliderControl::Transition(ControlTransitionEnum  eTrans,
                               Pos                   *pPos)
{
    Rect oRect;

    oRect.x1 = m_iCurrentPos;
    oRect.x2 = m_iCurrentPos + m_iThumbWidth;
    oRect.y1 = m_oRect.y1;
    oRect.y2 = m_oRect.y2;

    switch(eTrans)
    {
       case CT_MouseEnter:
          m_pParent->SendControlMessage(this, CM_MouseEnter);
          break;
       case CT_MouseLeave:
          m_pParent->SendControlMessage(this, CM_MouseLeave);

       default:
          break;
    }  

    if (m_eCurrentState != CS_Dragging && m_eLastState == CS_Dragging)
    {
        m_pParent->SetMousePos(m_oOrigin);
        m_pParent->HideMouse(false);
        m_pParent->EndMouseCapture();
    }

    switch(m_eCurrentState)
    {
       case CS_Normal:
          BlitFrame(0, 3, &oRect);
          break;

       case CS_MouseOver:
          BlitFrame(1, 3, &oRect);
          break;

       case CS_Dragging:
          HandleDrag(eTrans, pPos); 
          break;

       case CS_Disabled:
          BlitFrame(2, 3, &oRect);
          break;

       default:
          break;
    }
}

void SliderControl::HandleDrag(ControlTransitionEnum  eTrans,
                               Pos                   *pPos)
{
    Canvas *pCanvas;
    int     iDelta, iNewPos;
    Rect    oRect;

    // Is this the beginning of a drag?
    if (m_eCurrentState != CS_Dragging)
    {
        m_oOrigin = *pPos;

        m_iRange = m_oRect.Width() - m_oBitmapRect.Width();
        m_iThumbWidth = m_oBitmapRect.Width() / 3;
        m_pParent->HideMouse(true);
        m_pParent->StartMouseCapture(this);

        return;
    }

    iDelta = pPos->x - m_oOrigin.x; 
    iNewPos = max(min(m_iCurrentPos + iDelta, 0), m_iRange);

    if (iNewPos == m_iCurrentPos)
       return;

    oRect.x1 = m_iCurrentPos;
    oRect.x2 = m_iCurrentPos + m_iThumbWidth;
    oRect.y1 = m_oRect.y1;
    oRect.y2 = m_oRect.y2;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->Erase(oRect);

    oRect.x1 = iNewPos;
    oRect.x2 = iNewPos + m_iThumbWidth;
    BlitFrame(1, 3, &oRect);

    m_iCurrentPos = iNewPos;
}
