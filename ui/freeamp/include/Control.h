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

   $Id: Control.h,v 1.1.2.10 1999/09/28 22:59:30 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_CONTROL_H__
#define INCLUDED_CONTROL_H__

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "Types.h"
#include "Bitmap.h"
#include "Canvas.h"

enum ControlMessageEnum
{
    CM_Pressed,
    CM_MouseEnter,
    CM_MouseLeave,
    CM_SliderUpdate,
    CM_ValueChanged,
    CM_ChangeWindow,

    CM_LastValue
};

enum ControlTransitionEnum
{
    CT_Show,
    CT_Hide,
    CT_Enable,
    CT_Disable,
    CT_MouseMove,
    CT_MouseEnter,
    CT_MouseLeave,
    CT_MouseLButtonUp,
    CT_MouseLButtonDown,
    CT_SetValue,
    CT_Timer,

    CT_None,

    CT_LastTransition
};

enum ControlStateEnum
{
    CS_Normal,
    CS_MouseOver,
    CS_Pressed,
    CS_Disabled,
    CS_DisabledMO,
    CS_Dragging,
    CS_Hidden,
    CS_HiddenMO,

    CS_Any,			 // These states allow a transition message to be
    CS_Same,		 // sent to the control without actually changing state.

    CS_LastState
};

class TransitionInfo
{
    public:

       ControlStateEnum      eState;
       ControlTransitionEnum eAction;
       ControlStateEnum      eNextState;
};

// I HATE MICROSOFT   I HATE MICROSOFT   I HATE MICROSOFT   I HATE MICROSOFT
// These two functions are not necessary under gcc 2.95, but MSVC++ won't compile
// without them. BILL GATES MUST DIE!
bool operator<(const TransitionInfo &A, const TransitionInfo &b);
bool operator==(const TransitionInfo &A, const TransitionInfo &b);
// I HATE MICROSOFT   I HATE MICROSOFT   I HATE MICROSOFT   I HATE MICROSOFT

class Window;
class Control
{
    public:

               Control(Window *pParent, string &oName, 
                       TransitionInfo *pTransitions);
      virtual ~Control(void);
 
      void  SetRect(Rect &oRect);
      void  SetBitmap(Bitmap *pBitmap, Rect &oBitmapRect);
      void  GetName(string &oName);
      void  SetDesc(const string &oDesc);
      void  SetTip(const string &oTip);
      void  GetDesc(string &oDesc);
      void  GetTip(string &oTip);
 
      Error Show(bool bSet, bool &bShow);
      Error Enable(bool bHide, bool &bEnable);
      Error IntValue(bool bSet, int &iValue);
      Error StringValue(bool bSet, string &oValue);

      virtual bool PosInControl(Pos &oPos);
      virtual bool WantsTimingMessages(void);
      virtual void Init(void) = 0;
      virtual void AcceptTransition(ControlTransitionEnum eTrans,
                                    Pos *pMousePos = NULL);

    protected:

      virtual void Transition(ControlTransitionEnum eTrans,
                              Pos *pMousePos = NULL) = 0;

      // Call this function to hide the control. It causes the
      // area occupied by the control to be painted with the
      // background bitmap
      virtual void Erase(void);

      // Call this function to blit the face of the control
      // Args: iFrame: Which frame to blit
      //       iNumFrames: how many frames in the x direction in the bitmap
      virtual void BlitFrame(int iFrame, int iNumFrames, Rect *pRect = NULL); 

      string                 m_oName, m_oDesc, m_oToolTip;
      Rect                   m_oRect, m_oBitmapRect;
      Bitmap                *m_pBitmap;
      ControlStateEnum       m_eCurrentState, m_eLastState;
      vector<TransitionInfo> m_oTransitions;
      Window                *m_pParent;
      bool                   m_bShow, m_bEnable, m_bWantsTimingMessages;
      int                    m_iValue;
      string                 m_oValue;
};

#endif
