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

   $Id: Win32Bitmap.h,v 1.1.2.1 1999/09/08 22:46:39 robert Exp $
____________________________________________________________________________*/ 

#ifndef __WIN32BITMAP_H__
#define __WIN32BITMAP_H__

#include <string>

#include "Bitmap.h"
#include "Types.h"
#include "errors.h"

class Win32Bitmap : public Bitmap
{
    public:

              Win32Bitmap(string &oName);
     virtual ~Win32Bitmap(void);

     virtual Error LoadBitmap(string &oFile);
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                            Rect &oDestRect);

    protected:

};

#endif
