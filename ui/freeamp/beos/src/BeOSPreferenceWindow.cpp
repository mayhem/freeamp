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

   $Id: BeOSPreferenceWindow.cpp,v 1.1 1999/10/26 06:18:04 hiro Exp $
____________________________________________________________________________*/ 

#include "BeOSPreferenceWindow.h"

BeOSPreferenceWindow::BeOSPreferenceWindow( FAContext* context,
                                            ThemeManager* themeMan )
:   PreferenceWindow( context, themeMan )
{
}

BeOSPreferenceWindow::~BeOSPreferenceWindow()
{
}

bool
BeOSPreferenceWindow::Show( Window* parent )
{
    return true;
}
