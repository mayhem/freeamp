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

   $Id: Win32Canvas.cpp,v 1.1.2.3 1999/09/09 00:27:12 robert Exp $
____________________________________________________________________________*/ 

#include "Win32Canvas.h"

Win32Canvas::Win32Canvas(void)
{

}

Win32Canvas::~Win32Canvas(void)
{

}

Error Win32Canvas::RenderText(int iFontHeight, Rect &oClipRect, string &oText)
{
   return kError_NoErr;
}

Error Win32Canvas::Invalidate(Rect &oRect)
{
   return kError_NoErr;
}

Error Win32Canvas::Update(void)
{
   return kError_NoErr;
}

Error Win32Canvas::BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRec)
{
   return kError_NoErr;
}

void Win32Canvas::Paint(Rect &oRect)
{
}

void Win32Canvas::Erase(Rect &oRect)
{
}

