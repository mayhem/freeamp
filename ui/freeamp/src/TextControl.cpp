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

   $Id: TextControl.cpp,v 1.1.2.8 1999/09/26 03:23:39 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "TextControl.h"
#include "Window.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

static TransitionInfo pTransitions[] =
{  
    { CS_Normal,    CT_SetValue,         CS_Normal    },
    { CS_Normal,    CT_Hide,             CS_Hidden    },
    { CS_Hidden,    CT_Show,             CS_Normal    },
    { CS_LastState, CT_LastTransition,   CS_LastState } 
};

TextControl::TextControl(Window *pWindow, string &oName) : 
             Control(pWindow, oName, pTransitions)
{
	m_pFont = NULL;
}

void TextControl::SetStyle(Font *pFont, string &oAlign, 
                           Color &oColor, bool bBold,
                           bool bItalic, bool bUnderline)
{
    m_oColor = oColor;
    m_bBold = bBold;
    m_bItalic = bItalic;
    m_bUnderline = bUnderline;
    m_pFont = pFont;
       
	if (strcasecmp(oAlign.c_str(), "right") == 0)
       m_eAlign = eRight;
    else   
	if (strcasecmp(oAlign.c_str(), "center") == 0)
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
    string oFontFace;
    
    m_pFont->GetFace(oFontFace);

    pCanvas = m_pParent->GetCanvas();
    pCanvas->Erase(m_oRect);
    pCanvas->RenderText(m_oRect.Height(), m_oRect, 
                        m_oValue, m_eAlign, oFontFace, m_oColor); 
}
