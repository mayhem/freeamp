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

   $Id: Win32Bitmap.h,v 1.7 1999/12/13 12:49:48 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_WIN32BITMAP_H__
#define INCLUDED_WIN32BITMAP_H__

#include <string>

#include <windows.h>
#include "Bitmap.h"
#include "Types.h"
#include "errors.h"

class Win32Bitmap : public Bitmap
{
    public:

              Win32Bitmap(const string &oName);
			  Win32Bitmap(int iWidth, int iHeight, const string &oName);
     virtual ~Win32Bitmap(void);

     virtual Error LoadBitmapFromDisk(string &oFile);
     virtual Error BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                            Rect &oDestRect);
     virtual Error MaskBlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                                Rect &oDestRect);
     virtual bool  IsPosVisible(Pos &oPos);

     HBITMAP       GetBitmapHandle(void);
     BITMAPINFO   *GetBitmapInfo(void) { return &m_sBitmapInfo; };
     void         *GetBitmapBits(void) { return m_pBitmapData; };
     HBITMAP       GetMaskBitmapHandle(void);
     BYTE         *Bits(int32 x, int32 y);
     void          SaveBitmap(char *szFile);

    protected:

     void          CreateMaskBitmap(void);
	 int32         BytesPerLine(void);
    
     HBITMAP     m_hBitmap;
     HBITMAP     m_hMaskBitmap;
	 BITMAPINFO  m_sBitmapInfo;
	 void       *m_pBitmapData;
	 int32       m_iBytesPerLine, m_iHeight, m_iWidth;
};

#endif
