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

   $Id: Types.h,v 1.1.2.1 1999/08/25 23:01:52 robert Exp $
____________________________________________________________________________*/ 

#ifndef __TYPES_H__
#define __TYPES_H__

struct Pos
{
    int x, y;
};

struct Rect
{
    int x1, y1;
    int x2, y2;

    Rect(void) { };
    Rect(Rect &other)
    {
         x1 = other.x1;
         x2 = other.x2;
         y1 = other.y1;
         y2 = other.y2;
    };
    int Width(void)
    {
         return x2 - x1;
    };
    int Height(void)
    {
         return y2 - y1;
    }
    bool IsPosInRect(Pos &oPos)
    {
         if (oPos.x >= x1 && oPos.x <= x2 &&
             oPos.y >= y1 && oPos.y <= y2)
             return true;

         return false;
    }
};


#endif
