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

   $Id: Win32Canvas.h,v 1.1.2.2 1999/09/09 00:27:09 robert Exp $
____________________________________________________________________________*/ 

#ifndef __WIN32CANVAS_H__
#define __WIN32CANVAS_H__

#include "Types.h"
#include "Bitmap.h"
#include "Canvas.h"

class Win32Canvas : public Canvas
{
    public:

              Win32Canvas(void);
     virtual ~Win32Canvas(void);

     virtual Error RenderText(int iFontHeight, Rect &oClipRect, string &oText);
     virtual Error Invalidate(Rect &oRect);
     virtual Error Update(void);
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRec);
     virtual void  Paint(Rect &oRect);
     virtual void  Erase(Rect &oRect);

    protected:

};

#endif
