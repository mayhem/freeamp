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

   $Id: Bitmap.h,v 1.1.2.2 1999/09/08 22:46:13 robert Exp $
____________________________________________________________________________*/ 

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <string>

#include "Types.h"
#include "errors.h"

using namespace std;

class Bitmap
{
    public:

              Bitmap(string &oName);
     virtual ~Bitmap(void);

     virtual void  GetName(string &oName);
     virtual void  GetErrorString(string &oName);
     virtual Error LoadBitmapFromDisk(string &oFile) = 0;
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                            Rect &oDestRect) = 0;

    protected:

     string  m_oBitmapName, m_oLastError;
};

#endif
