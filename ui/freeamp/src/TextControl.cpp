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

   $Id: TextControl.cpp,v 1.1.2.5 1999/09/17 20:31:01 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "TextControl.h"
#include "Window.h"

static TransitionInfo pTransitions[] =
{  
    { CS_Normal,    CT_SetValue,         CS_Normal    },
    { CS_Normal,    CT_Hide,             CS_Hidden    },
    { CS_Hidden,    CT_Show,             CS_Normal    },
    { CS_LastState, CT_LastTransition,   CS_LastState } 
};

TextControl::TextControl(Window *pWindow, string &oName, 
                         string &oAlign) :
             Control(pWindow, oName, pTransitions)
{
	strlwr((char *)oAlign.c_str());
	if (oAlign == string("right"))
       m_eAlign = eRight;
    else   
	if (oAlign == string("center"))
       m_eAlign = eCenter;
    else   
       m_eAlign = eLeft;
}

TextControl::~TextControl(void)
{

}

void TextControl::Init(void)
{
    TextChanged();
}

void TextControl::Transition(ControlTransitionEnum  eTrans,
                             Pos                   *pMousePos)
{
    switch(eTrans)
    {
        case CT_SetValue:
            TextChanged();
            break;

        default:
            break;
    }
}

void TextControl::TextChanged(void)
{
    Canvas *pCanvas;

    pCanvas = m_pParent->GetCanvas();
    pCanvas->Erase(m_oRect);
    pCanvas->RenderText(m_oRect.Height(), m_oRect, 
                        m_oValue, m_eAlign); 
}
