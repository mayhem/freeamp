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

   $Id: Win32Bitmap.cpp,v 1.1.2.6 1999/09/23 18:13:52 robert Exp $
____________________________________________________________________________*/ 

#include "string"
#include "Win32Bitmap.h"
#include "debug.h"

Win32Bitmap::Win32Bitmap(string &oName)
          :Bitmap(oName)
{
   m_oBitmapName = oName;
   m_hBitmap = NULL;
}

Win32Bitmap::Win32Bitmap(int iWidth, int iHeight, string &oName)
           :Bitmap(oName)
{
   HDC hDc;
   
   hDc = GetDC(NULL);
   m_hBitmap = CreateCompatibleBitmap(hDc, iWidth, iHeight);
   ReleaseDC(NULL, hDc);
}

Win32Bitmap::~Win32Bitmap(void)
{
   if (m_hBitmap)
       DeleteObject(m_hBitmap);
}

Error Win32Bitmap::LoadBitmapFromDisk(string &oFile)
{
   m_hBitmap = (HBITMAP)LoadImage(NULL, oFile.c_str(), IMAGE_BITMAP,
                                  0, 0, LR_LOADFROMFILE);
   if (m_hBitmap == NULL)
   	   return kError_LoadBitmapFailed;

   return kError_NoErr;
}

HBITMAP Win32Bitmap::GetBitmapHandle(void)
{
   return m_hBitmap;
}

Error Win32Bitmap::BlitRect(Bitmap *pOther, Rect &oSrcRect, 
                            Rect &oDestRect)
{
   HDC hRootDC, hSrcDC, hDestDC;
   Win32Bitmap *pSrcBitmap = (Win32Bitmap *)pOther;
   
   hRootDC = GetDC(NULL);
   hSrcDC = CreateCompatibleDC(hRootDC);
   hDestDC = CreateCompatibleDC(hRootDC);
   ReleaseDC(NULL, hRootDC);
   
   DeleteObject(SelectObject(hSrcDC, pSrcBitmap->m_hBitmap));
   DeleteObject(SelectObject(hDestDC, m_hBitmap));

   BitBlt(hDestDC, oDestRect.x1, oDestRect.y1, 
          oDestRect.Width(), oDestRect.Height(),
   	      hSrcDC, oSrcRect.x1, oSrcRect.y1, SRCCOPY);

   DeleteDC(hSrcDC);
   DeleteDC(hDestDC);

   return kError_NoErr;
}

