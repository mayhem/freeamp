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

   $Id: ButtonControl.cpp,v 1.1.2.7 1999/09/23 18:13:44 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "ButtonControl.h"
#include "Window.h"
#include "debug.h"

// Bitmap info:
// Frame 0: Normal
// Frame 1: MouseOver
// Frame 2: Pressed
// Frame 3: Disabled


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
    { CS_LastState,  CT_LastTransition,   CS_LastState  }
};

ButtonControl::ButtonControl(Window *pWindow, string &oName) :
               Control(pWindow, oName, pTransitions)
{
}

ButtonControl::~ButtonControl(void)
{

}

void ButtonControl::Init(void)
{
    BlitFrame(0, 4);
}

void ButtonControl::Transition(ControlTransitionEnum  eTrans,
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
          BlitFrame(0, 4);
          break;

       case CS_MouseOver:
          BlitFrame(1, 4);
          break;

       case CS_Pressed:
          BlitFrame(2, 4);
          break;

       case CS_Disabled:
          BlitFrame(3, 4);
          break;

       default:
          break;
    }
}

