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

   $Id: MultiStateControl.cpp,v 1.4 1999/11/02 20:25:02 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "MultiStateControl.h"
#include "Window.h"
#include "debug.h"

// Bitmap info:
// For each 'state'
// Frame 0: Normal
// Frame 1: MouseOver
// Frame 2: Pressed
// Frame 3: Disabled
// Frames are horizontal, states are vertical

static TransitionInfo pTransitions[] =
{
    { CS_Normal,     CT_MouseEnter,       CS_MouseOver  },
    { CS_Normal,     CT_Disable,          CS_Disabled   },
    { CS_Normal,     CT_Hide,             CS_Hidden     },
    { CS_Normal,     CT_Show,             CS_Normal     },
    { CS_MouseOver,  CT_MouseLeave,       CS_Normal     },
    { CS_MouseOver,  CT_MouseLButtonDown, CS_Pressed    },
    { CS_MouseOver,  CT_Disable,          CS_Disabled   },
    { CS_MouseOver,  CT_Hide,             CS_Hidden     },
    { CS_Pressed,    CT_MouseLButtonUp,   CS_MouseOver  },
    { CS_Pressed,    CT_Disable,          CS_Disabled   },
    { CS_Pressed,    CT_MouseLeave,       CS_Normal     },
    { CS_Disabled,   CT_Enable,           CS_Normal     },
    { CS_Disabled ,  CT_MouseEnter,       CS_DisabledMO },
    { CS_DisabledMO, CT_MouseLeave,       CS_Disabled   },
    { CS_Hidden,     CT_Show,             CS_Normal     },
    { CS_Any,        CT_SetValue,         CS_Same       },
    { CS_LastState,  CT_LastTransition,   CS_LastState  }
};

MultiStateControl::MultiStateControl(Window *pWindow, 
                                     string &oName, 
                                     int iNumStates) :
               Control(pWindow, oName, pTransitions)
{
	m_iState = 0;
    m_iNumStates = iNumStates;
}

MultiStateControl::~MultiStateControl(void)
{

}

void MultiStateControl::GetDesc(string &oDesc)
{
    int i = m_iState;

    if (m_oDescs.size() == 0)
    {
       oDesc = "";
       return;
    }
    
    if (i >= m_oDescs.size())
      i = 0;
       
    oDesc = m_oDescs[i];
}    

void MultiStateControl::GetTip(string &oTip)
{
    int i = m_iState;
    
    if (m_oTips.size() == 0)
    {
       oTip = "";
       return;
    }
    
    if (i >= m_oTips.size())
      i = 0;
       
    oTip = m_oTips[i];
}    

void MultiStateControl::Init(void)
{
    int   iOffset, iRet;
    char *szDup;

    szDup = strdup(m_oDesc.c_str());
    iOffset = 0;
    for(;;)
    {
        iRet = sscanf((char *)m_oDesc.c_str() + iOffset, "%[^|]", szDup);
        if (iRet < 1) 
            break;
            
        m_oDescs.push_back(string(szDup));
            
        iOffset += strlen(szDup) + 2;
        if (iOffset > m_oDesc.length())
            break;
    }
    free(szDup);

    szDup = strdup(m_oToolTip.c_str());
    iOffset = 0;
    for(;;)
    {
        iRet = sscanf((char *)m_oToolTip.c_str() + iOffset, "%[^|]", szDup);
        if (iRet < 1) 
            break;
            
        m_oTips.push_back(string(szDup));
            
        iOffset += strlen(szDup) + 2;
        if (iOffset > m_oToolTip.length())
            break;
    }
    free(szDup);

    if (m_oRect.x2 == -1 && m_oRect.y2 == -1)
    {
        m_oRect.x2 = m_oRect.x1 + 
                     (m_oBitmapRect.x2 - m_oBitmapRect.x1)/4;
        m_oRect.y2 = m_oRect.y1 + 
                     (m_oBitmapRect.y2 - m_oBitmapRect.y1)/m_iNumStates;
    }    
    
    BlitMultiStateFrame(0, 4, m_iState, m_iNumStates);
}

void MultiStateControl::Transition(ControlTransitionEnum  eTrans,
                                   Pos                   *pMousePos)
{
	Canvas *pCanvas;
    
    switch(eTrans)
    {
       case CT_MouseEnter:
          m_pParent->SendControlMessage(this, CM_MouseEnter);
          break;
       case CT_MouseLeave:
          m_pParent->SendControlMessage(this, CM_MouseLeave);
          break;
       case CT_SetValue:
       	  m_iState = min(max(m_iValue, 0), m_iNumStates);
          break;
       case CT_Hide:
       {
       	  Rect oRect = m_oRect;
          pCanvas = m_pParent->GetCanvas();
          pCanvas->Erase(oRect);
          pCanvas->Invalidate(oRect);
       	  break;
       }   

       default:
          break;
    }

	if (m_eCurrentState == CS_MouseOver && 
        eTrans == CT_MouseLButtonUp)
        m_pParent->SendControlMessage(this, CM_Pressed);

    switch(m_eCurrentState)
    {
       case CS_Normal:
          BlitMultiStateFrame(0, 4, m_iState, m_iNumStates);
          break;

       case CS_MouseOver:
          BlitMultiStateFrame(1, 4, m_iState, m_iNumStates);
          break;

       case CS_Pressed:
          BlitMultiStateFrame(2, 4, m_iState, m_iNumStates);
          break;

       case CS_Disabled:
          BlitMultiStateFrame(3, 4, m_iState, m_iNumStates);
          break;

       default:
          break;
    }
}

bool MultiStateControl::PosInControl(Pos &oPos)
{
    bool bRet;
    
    bRet = m_oRect.IsPosInRect(oPos);
    if (bRet && m_pBitmap)
    {
    	Pos oLocalPos;
        
        oLocalPos.x = (oPos.x - m_oRect.x1) + m_oBitmapRect.x1;
        oLocalPos.y = (oPos.y - m_oRect.y1) + m_oBitmapRect.y1;
        return m_pBitmap->IsPosVisible(oLocalPos);
    }    
    
    return bRet;    
}        

