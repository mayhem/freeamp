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

   $Id: GTKBitmap.h,v 1.1.2.2 1999/09/09 00:27:03 robert Exp $
____________________________________________________________________________*/ 

#ifndef __GTKBITMAP_H__
#define __GTKBITMAP_H__

#include <string>

#include "Bitmap.h"
#include "Types.h"
#include "errors.h"

class GTKBitmap : public Bitmap
{
    public:

              GTKBitmap(string &oName);
     virtual ~GTKBitmap(void);

     virtual Error LoadBitmapFromDisk(string &oFile);
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                            Rect &oDestRect);

    protected:

};

#endif
