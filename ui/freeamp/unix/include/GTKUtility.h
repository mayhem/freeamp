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

   $Id: GTKUtility.h,v 1.1.2.1 1999/09/27 19:20:36 ijr Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_GTKUTILITY__H_
#define INCLUDED_GTKUTILITY__H_

#include <gdk/gdk.h>
void IconifyWindow(GdkWindow *win);
void WarpPointer(GdkWindow *win, int x, int y);

#endif
