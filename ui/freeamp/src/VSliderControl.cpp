/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999-2000 EMusic

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

   $Id: VSliderControl.cpp,v 1.20 2001/01/10 20:08:58 ijr Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "VSliderControl.h"
#include "Window.h"
#include "debug.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

// Bitmap Info:
// Frame 0: Normal slider
// Frame 1: Selected slider
// Frame 2: Disabled slider

static TransitionInfo pTransitions[] =
{  
    { CS_Normal,     CT_MouseEnter,       CS_MouseOver  }, 
    { CS_Normal,     CT_Disable,          CS_Disabled   }, 
    { CS_Normal,     CT_Hide,             CS_Hidden     },
    { CS_Normal,     CT_Show,             CS_Normal     }, 
    { CS_MouseOver,  CT_MouseLeave,       CS_Normal     }, 
    { CS_MouseOver,  CT_MouseLButtonDown, CS_Dragging   }, 
    { CS_MouseOver,  CT_Disable,          CS_Disabled   }, 
    { CS_Dragging,   CT_MouseMove,        CS_Dragging   }, 
    { CS_Dragging,   CT_MouseLButtonUp,   CS_MouseOver  }, 
    { CS_Disabled ,  CT_Show,             CS_Disabled   },
    { CS_Disabled ,  CT_Enable,           CS_Normal     },
    { CS_Disabled ,  CT_MouseEnter,       CS_DisabledMO },
    { CS_DisabledMO, CT_MouseLeave,       CS_Disabled   },
    { CS_DisabledMO, CT_Enable,           CS_MouseOver  },
    { CS_Hidden,     CT_Show,             CS_Normal     },
    { CS_Any,        CT_SetValue,         CS_Same       },
    { CS_LastState,  CT_LastTransition,   CS_LastState  }
};

VSliderControl::VSliderControl(Window *pWindow, string &oName, int iThumbs,
                               int iNumFrames, int iNotchPercent, int iNotchWidth) :
               Control(pWindow, oName, pTransitions)
{
     m_iRange = -1;
     m_iCurrentPos = 0;
     m_iValue = -1;
     m_oOrigin.y = -1;
     m_iNumThumbStates = iThumbs;
     m_iNumFrames = iNumFrames;
     m_bIsDrag = false;
     m_bInUpdate = false;
     m_bHasTroughBitmap = false;
     m_bTroughMiddle = false;
     m_iCurrentTroughFrame = -1;
     m_iNotchPercent = iNotchPercent;
     m_iNotchWidth = iNotchWidth / 2;
};

VSliderControl::~VSliderControl(void)
{

}

void VSliderControl::SetTroughBitmap(Bitmap *pBitmap, Rect &oBitmapRect,
                                     int iFrames, bool bHoriz, int iDelta,
                                     bool bMiddle)
{
    m_oMutex.Acquire();
    m_pTroughBitmap = pBitmap;
    m_iTroughFrames = iFrames;
    m_oTroughBitmapRect = oBitmapRect;
    m_bHorizontalTroughBitmap = bHoriz;
    m_iTroughDelta = iDelta;
    m_bHasTroughBitmap = true;
    m_bTroughMiddle = bMiddle;
    m_oMutex.Release();
}

void VSliderControl::Init(void)
{
    m_oMutex.Acquire();
   
    if (!m_bUsesStateBitmapRects) {
        for (int row = 0; row < m_iNumThumbStates; row++) {
            for (int i = 0; i < m_iNumFrames; i++) {
                int iFrameWidth, iFrameHeight;
                Rect oFrameRect;

                if (m_bHorizontalBitmap) {
                    iFrameWidth = (m_oBitmapRect.Width() + 1) / 3;
                    iFrameHeight = (m_oBitmapRect.Height() + 1) /
                                   m_iNumThumbStates;
                    oFrameRect = m_oBitmapRect;
                    oFrameRect.x1 += i * iFrameWidth;
                    oFrameRect.x2 = oFrameRect.x1 + iFrameWidth - 1;
                    oFrameRect.y1 += row * iFrameHeight;
                    oFrameRect.y2 = oFrameRect.y1 + iFrameHeight - 1;
                }
                else {
                    iFrameHeight = (m_oBitmapRect.Height() + 1) / 3;
                    iFrameWidth = (m_oBitmapRect.Width() + 1) /
                                  m_iNumThumbStates;
                    oFrameRect = m_oBitmapRect;
                    oFrameRect.x1 += row * iFrameWidth;
                    oFrameRect.x2 = oFrameRect.x1 + iFrameWidth - 1;
                    oFrameRect.y1 += i * iFrameHeight;
                    oFrameRect.y2 = oFrameRect.y1 + iFrameHeight - 1;
                }

                switch (i) {
                    case 0:
                        SetStateBitmap(m_pBitmap, oFrameRect, CS_Normal, row);
                        break;
                    case 1:
                        SetStateBitmap(m_pBitmap, oFrameRect, CS_MouseOver, row);
                        SetStateBitmap(m_pBitmap, oFrameRect, CS_Dragging, row);
                        break;
                    case 2:
                        SetStateBitmap(m_pBitmap, oFrameRect, CS_Disabled, row);
                        break;
                    default:
                        break;
                }
           }
        }
    }

    m_iThumbHeight = m_oStateBitmapRect[0][CS_Normal].Height(); 
    m_iRange = m_oRect.Height() - m_iThumbHeight;

    m_oMutex.Release();
    
    Transition(CT_None, NULL);
}

void VSliderControl::Transition(ControlTransitionEnum  eTrans,
                               Pos                   *pPos)
{
    Rect oRect;

    if (m_eCurrentState == CS_Dragging && eTrans == CT_SetValue)
        return;

    switch(eTrans)
    {
       case CT_MouseEnter:
           m_pParent->SendControlMessage(this, CM_MouseEnter);
           break;
       case CT_MouseLeave:
           m_pParent->SendControlMessage(this, CM_MouseLeave);
           break;

       case CT_SetValue:
       {
           int iNewPos;    

           if (m_iValue < 0 || m_iValue > 100)
               return;

           m_oMutex.Acquire();
           if (m_bInUpdate)
           {
              m_oMutex.Release();
              return;
           }
           m_bInUpdate = true;

           iNewPos = ((100 - m_iValue) * m_iRange) / 100;
           if (iNewPos == m_iCurrentPos)
           {
              m_bInUpdate = false;
              m_oMutex.Release();
              return;
           }

           m_iCurrentPos = iNewPos;
           m_bInUpdate = false;
           m_oMutex.Release();

           if (!m_pPanel->IsHidden())
               MoveThumb(iNewPos);
           
           return;
       }   

       default:
          break;
    }  

    if (m_pPanel->IsHidden())
       return;

    oRect.x1 = m_oRect.x1;
    oRect.x2 = m_oRect.x2;
    oRect.y1 = m_oRect.y1 + m_iCurrentPos;
    oRect.y2 = oRect.y1 + m_iThumbHeight;

    m_oMutex.Acquire();
    if (m_eCurrentState != CS_Dragging && 
        m_eLastState == CS_Dragging)
    {    
        if (m_oOrigin.y != -1)
        {
            Rect oRect;
     
            m_oMutex.Release();
            m_pParent->GetWindowPosition(oRect);
            m_oMutex.Acquire();
            
            m_oOrigin.y = m_oRect.y1 + m_iCurrentPos + (m_iThumbHeight / 2);
            m_oOrigin.y += oRect.y1;
            m_oOrigin.x += oRect.x1;
            
            m_oMutex.Release();
            m_pParent->EndMouseCapture();
            m_pParent->HideMouse(false);
            m_oMutex.Acquire();
            
            m_oOrigin.y = -1;
        }    
        m_iValue = 100 - ((m_iCurrentPos * 100) / m_iRange);

        m_oMutex.Release();
        m_pParent->SendControlMessage(this, CM_ValueChanged);
        m_oMutex.Acquire();
    }    

    if (m_eCurrentState == CS_Dragging && 
        m_eLastState != CS_Dragging)
       m_bIsDrag = oRect.IsPosInRect(*pPos);

    m_oMutex.Release();

    int iThumbNumber = m_iNumThumbStates * (1 - m_iCurrentPos / m_iRange);
    iThumbNumber = min(m_iNumThumbStates - 1, iThumbNumber);

    if (m_eCurrentState != CS_MouseOver && m_eCurrentState != CS_DisabledMO) 
        BlitTrough(m_iCurrentPos);

    switch(m_eCurrentState)
    {
       case CS_Normal:
          BlitFrame(CS_Normal, iThumbNumber, &oRect);
          break;

       case CS_MouseOver:
          BlitFrame(CS_MouseOver, iThumbNumber, &oRect);
          break;

       case CS_Dragging:
       
          m_oMutex.Acquire();
          if (m_bInUpdate)
          {
              m_oMutex.Release();
              return;
          }
              
          m_bInUpdate = true;
          m_oMutex.Release();

          if (m_bIsDrag)
              HandleDrag(eTrans, pPos); 
          else
              HandleJump(eTrans, pPos);    

          m_oMutex.Acquire();
          m_bInUpdate = false;
          m_oMutex.Release();
          break;
          
       case CS_Disabled:
          BlitFrame(CS_Disabled, iThumbNumber, &oRect);
          break;

       default:
          break;
    }
}

void VSliderControl::HandleJump(ControlTransitionEnum  eTrans,
                               Pos                   *pPos)
{
    int     iNewPos;

    m_oMutex.Acquire();

    iNewPos = pPos->y - m_oRect.y1 - (m_iThumbHeight / 2);
    iNewPos = min(max(iNewPos, 0), m_iRange);

    if (iNewPos == m_iCurrentPos)
    {
       m_oMutex.Release();
       return;
    }   
    m_oMutex.Release();

    MoveThumb(iNewPos);

    m_oMutex.Acquire();

    m_iCurrentPos = iNewPos;
    
    m_iValue = 100 - ((m_iCurrentPos * 100) / m_iRange);
    m_bIsDrag = true;
    
    m_oMutex.Release();
}

void VSliderControl::HandleDrag(ControlTransitionEnum  eTrans,
                               Pos                   *pPos)
{
    int iNewPos;

    m_oMutex.Acquire();

    // Is this the beginning of a drag?
    if (m_oOrigin.y == -1)
    {
        m_oOrigin = *pPos;
        m_oMutex.Release();

        m_pParent->HideMouse(true);
        m_pParent->StartMouseCapture(this);

        return;
    }

    if (pPos->y < 0)
    {
        m_oMutex.Release();
        return;
    }    

    iNewPos = min(max(m_iRange - (m_oRect.y2 - pPos->y), 0), m_iRange);
    if (iNewPos == m_iCurrentPos)
    {
        m_oMutex.Release();
        return;
    }    

    if (m_iNotchPercent > 0)
    {
        int iNotch;
        
        iNotch = ((m_iRange * m_iNotchPercent) / 100);
        if (iNewPos >= (iNotch - m_iNotchWidth) &&
            iNewPos <= (iNotch + m_iNotchWidth))
           iNewPos = iNotch;
    }
    m_iCurrentPos = iNewPos;

    m_iValue = 100 - ((m_iCurrentPos * 100) / m_iRange);

    m_oMutex.Release();
    
    MoveThumb(iNewPos);
    m_pParent->SendControlMessage(this, CM_SliderUpdate);
}

void VSliderControl::MoveThumb(int iNewPos)
{
    Canvas *pCanvas;
    Rect    oRect;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->Erase(m_oRect);

    oRect.y1 = m_oRect.y1 + iNewPos;
    oRect.y2 = oRect.y1 + m_iThumbHeight;
    oRect.x1 = m_oRect.x1;
    oRect.x2 = m_oRect.x2;
    
    int iThumbNumber = m_iNumThumbStates * (1 - iNewPos / m_iRange);
    iThumbNumber = min(m_iNumThumbStates - 1, iThumbNumber);

    BlitTrough(iNewPos);

    switch(m_eCurrentState)
    {
       case CS_Normal:
          BlitFrame(CS_Normal, iThumbNumber, &oRect, false);
          break;

       case CS_Dragging:
       case CS_MouseOver:
          BlitFrame(CS_MouseOver, iThumbNumber, &oRect, false);
          break;

       case CS_Disabled:
       case CS_DisabledMO:
          BlitFrame(CS_Disabled, iThumbNumber, &oRect, false);
          break;

       default:
          break;
    }
    pCanvas->Invalidate(m_oRect);
}

void VSliderControl::BlitTrough(int iPos)
{
    if (!m_bHasTroughBitmap)
        return;

    Canvas *pCanvas;
    Rect    oFrameRect, oDestRect;

    oDestRect = m_oRect;
    
    int iTotFrames = m_iTroughFrames;
    if (m_bTroughMiddle)
        iTotFrames *= 2;

    int iFrameNumber = iTotFrames * (1 - iPos / m_iRange);
    iFrameNumber = min(iTotFrames - 1, iFrameNumber);

    if (m_bTroughMiddle) {
        if (iFrameNumber >= m_iTroughFrames)
            iFrameNumber = iFrameNumber - m_iTroughFrames;
        else
            iFrameNumber = (m_iTroughFrames - 1) - iFrameNumber;
    }
            
    m_iCurrentTroughFrame = iFrameNumber;

    if (m_bHorizontalTroughBitmap) {
        int iFrameWidth = (m_oBitmapRect.Width() + 1 - 
                           (m_iTroughDelta * (m_iTroughFrames - 1))) /
                           m_iTroughFrames;
        oFrameRect = m_oTroughBitmapRect;
        oFrameRect.x1 += (iFrameWidth + m_iTroughDelta) * iFrameNumber;
        oFrameRect.x2 = oFrameRect.x1 + iFrameWidth;
    }
    else {
        int iFrameHeight = (m_oBitmapRect.Height() + 1 -
                            (m_iTroughDelta * (m_iTroughFrames - 1))) / 
                            m_iTroughFrames;

        oFrameRect = m_oTroughBitmapRect;
        oFrameRect.y1 += (iFrameHeight + m_iTroughDelta) * iFrameNumber;
        oFrameRect.y2 = oFrameRect.y2 + iFrameHeight;
    }

    oFrameRect.y2++;
    oFrameRect.x2++;

    oDestRect.y2++;
    oDestRect.x2++;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->MaskBlitRect(m_pTroughBitmap, oFrameRect, oDestRect);

    pCanvas->Invalidate(oDestRect);
    pCanvas->Update();
}
