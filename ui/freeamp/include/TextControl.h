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

   $Id: TextControl.h,v 1.1.2.6 1999/09/23 01:29:52 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_TEXTCONTROL_H__
#define INCLUDED_TEXTCONTROL_H__

#include "Control.h"
#include "Canvas.h"


class TextControl : public Control
{
    public:

               TextControl(Window *pWindow, string &oName, 
                           string &oAlign, Color *pColor);
      virtual ~TextControl(void);

      void Transition(ControlTransitionEnum eTrans, Pos *pMousePos);
      virtual void Init(void);

    private:

      void      TextChanged(void);
      AlignEnum	m_eAlign;
      Color     m_oColor;
};

#endif
