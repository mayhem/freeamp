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

   $Id: DialControl.h,v 1.1.2.2 1999/09/08 22:46:17 robert Exp $
____________________________________________________________________________*/ 

#ifndef __DIALCONTROL_H__
#define __DIALCONTROL_H__

#include "Control.h"

using namespace std;

class DialControl : public Control
{
    public:

               DialControl(Window *pParent, string &oName);
      virtual ~DialControl(void);

      void Transition(ControlTransitionEnum eTrans, Pos *pMousePos);

    private:

};

#endif
