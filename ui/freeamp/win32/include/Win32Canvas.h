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

   $Id: Win32Canvas.h,v 1.1.2.4 1999/09/17 20:31:05 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_WIN32CANVAS_H__
#define INCLUDED_WIN32CANVAS_H__

#include <windows.h>
#include <assert.h>
#include "Types.h"
#include "Canvas.h"
#include "Win32Window.h"
#include "Win32Bitmap.h"

class Win32Canvas : public Canvas
{
    public:

              Win32Canvas(Win32Window *pParent);
     virtual ~Win32Canvas(void);

	 virtual void  Init(void);
     virtual Error RenderText(int iFontHeight, Rect &oClipRect, 
                              string &oText, AlignEnum eAlign);
     virtual Error Invalidate(Rect &oRect);
     virtual Error Update(void);
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRec);
     virtual void  Paint(HDC hDC, Rect &oRect);
     virtual void  Erase(Rect &oRect);
     virtual HRGN  GetMaskRgn(void);

    protected:

	 Win32Bitmap *m_pBufferBitmap;
     Win32Window *m_pParent;
};

#endif