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

   $Id: ButtonControl.h,v 1.1.2.1 1999/08/25 23:01:43 robert Exp $
____________________________________________________________________________*/ 

#ifndef __BUTTONCONTROL_H__
#define __BUTTONCONTROL_H__

#include <string>

#include "Control.h"

class ButtonControl : public Control
{
    public:

               ButtonControl(Window *pParent, string &oName);
      virtual ~ButtonControl(void);

      void Transition(ControlTransitionEnum eTrans, Pos *pMousePos);

    private:

};

#endif
