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

   $Id: Win32Canvas.cpp,v 1.1.2.8 1999/09/26 03:23:49 robert Exp $
____________________________________________________________________________*/ 

#include <windows.h>
#include "Win32Canvas.h"
#include "Win32Bitmap.h"
#include "debug.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

Win32Canvas::Win32Canvas(Win32Window *pParent)
{
   m_pParent = pParent;
   m_pBufferBitmap = NULL;
}

Win32Canvas::~Win32Canvas(void)
{
   delete m_pBufferBitmap;
}

void Win32Canvas::Init(void)
{
   Rect oDestRect;
   string oName("DoubleBuffer");
   
   assert(m_pBGBitmap);
   
   if (m_pBufferBitmap)
      delete m_pBufferBitmap;

   m_pBufferBitmap = new Win32Bitmap(m_oBGRect.Width(), 
                                     m_oBGRect.Height(),
                                     oName);
   
   oDestRect.x1 = oDestRect.y1 = 0;
   oDestRect.x2 = m_oBGRect.Width();
   oDestRect.y2 = m_oBGRect.Height();
   m_pBufferBitmap->BlitRect(m_pBGBitmap, m_oBGRect, oDestRect);
}

Error Win32Canvas::RenderText(int iFontHeight, Rect &oClipRect, 
                              string &oText, AlignEnum eAlign,
                              string &oFont, const Color &oColor)
{
   HDC   hRootDC, hMemDC;
   HFONT hFont;
   RECT  sClip;
   
   sClip.left = oClipRect.x1;
   sClip.right = oClipRect.x2;
   sClip.top = oClipRect.y1;
   sClip.bottom = oClipRect.y2;

   Erase(oClipRect);
   
   hRootDC = GetDC(NULL);
   hMemDC = CreateCompatibleDC(hRootDC);
   ReleaseDC(NULL, hRootDC);
   
   DeleteObject(SelectObject(hMemDC, m_pBufferBitmap->GetBitmapHandle()));
   
   hFont = CreateFont(iFontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
 					  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                      DEFAULT_PITCH, oFont.c_str()); 
                      
   if (!hFont)
   {
       Debug_v("usgin default: %s", m_oDefaultFont.c_str());
       hFont = CreateFont(iFontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
 	     				  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                          DEFAULT_PITCH, m_oDefaultFont.c_str()); 
   }                       

   DeleteObject(SelectObject(hMemDC, hFont));

   SetBkMode(hMemDC, TRANSPARENT);
   SetTextColor(hMemDC, RGB(oColor.red, oColor.green, oColor.blue));
   DrawText(hMemDC, oText.c_str(), oText.length(), &sClip, 
            (eAlign == eLeft) ? DT_LEFT :
		    (eAlign == eRight) ? DT_RIGHT : DT_CENTER);
          
   DeleteDC(hMemDC);
   DeleteObject(hFont);

   Invalidate(oClipRect);
   Update();

   return kError_NoErr;
}

Error Win32Canvas::Invalidate(Rect &oRect)
{
   RECT sRect;
   
   sRect.left = oRect.x1;
   sRect.right = oRect.x2;
   sRect.top = oRect.y1;
   sRect.bottom = oRect.y2;
   InvalidateRect(m_pParent->GetWindowHandle(), &sRect, FALSE);

   return kError_NoErr;
}

Error Win32Canvas::Update(void)
{
   UpdateWindow(m_pParent->GetWindowHandle());

   return kError_NoErr;
}

Error Win32Canvas::BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRect)
{
   if (!m_pBufferBitmap)
      return kError_NoErr;
      
   return m_pBufferBitmap->BlitRect(pSrcBitmap, oSrcRect, oDestRect);
}

Error Win32Canvas::MaskBlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRect)
{
   if (!m_pBufferBitmap)
      return kError_NoErr;
      
   return m_pBufferBitmap->MaskBlitRect(pSrcBitmap, oSrcRect, oDestRect);
}

void Win32Canvas::Paint(HDC hDC, Rect &oRect)
{
   HDC   hMemDC;

   hMemDC = CreateCompatibleDC(hDC);
   
   DeleteObject(SelectObject(hMemDC, m_pBufferBitmap->GetBitmapHandle()));
   BitBlt(hDC, oRect.x1, oRect.y1, oRect.Width(), oRect.Height(),
          hMemDC, oRect.x1, oRect.y1, SRCCOPY);
   DeleteDC(hMemDC);       
}

void Win32Canvas::Erase(Rect &oRect)
{
   Rect oMine = oRect;
   
   if (m_pBufferBitmap)
       m_pBufferBitmap->BlitRect(m_pBGBitmap, oRect, oRect);
}

HRGN Win32Canvas::GetMaskRgn(void)
{
   HDC         hRootDC, hMemDC;
   int         iScanLine, iRet, iLine, iStart;
   char       *pData;
   BITMAPINFO *pInfo;
   BITMAP      sInfo;
   HRGN        hMask, hTemp;
   HBITMAP     hMaskBitmap;

   hMask = CreateRectRgn(0,0,0,0);
   
   hRootDC = GetDC(NULL);
   hMemDC = CreateCompatibleDC(hRootDC);
   ReleaseDC(NULL, hRootDC);

   hMaskBitmap = ((Win32Bitmap *)m_pBGBitmap)->GetMaskBitmapHandle();

   GetObject(hMaskBitmap, sizeof(BITMAP), (LPSTR)&sInfo);

   pInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER) + 2 * 
                                  sizeof(RGBQUAD)];
   pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   pInfo->bmiHeader.biWidth = sInfo.bmWidth;
   pInfo->bmiHeader.biHeight = sInfo.bmHeight;
   pInfo->bmiHeader.biPlanes = 1;
   pInfo->bmiHeader.biBitCount = 1;
   pInfo->bmiHeader.biCompression = BI_RGB;
   
   pData = new char[sInfo.bmWidth * 4];
   for(iScanLine = 0; iScanLine < sInfo.bmHeight; iScanLine++)
   {
       iRet = GetDIBits(hMemDC, hMaskBitmap, 
                        (sInfo.bmHeight - 1)- iScanLine, 
                        1, pData, pInfo, DIB_PAL_COLORS);
       if (iRet == 0)
       {
           return NULL;
       }    
           
       for(iLine = 0, iStart = -1; iLine < sInfo.bmWidth; iLine++)
       {
       	  if ((pData[iLine / 8] & (0x80 >> (iLine % 8))) == 0)
          {
             if (iStart == -1)
                iStart = iLine;
             continue;
          }
          else
          {
             if (iStart >= 0)
             {
                 hTemp = CreateRectRgn(iStart, iScanLine, iLine, iScanLine + 1);
                 CombineRgn(hMask, hTemp, hMask, RGN_OR);
                 DeleteObject(hTemp);
                 iStart = -1;
             }
          }
       }    
       if (iStart >= 0)
       {
           hTemp = CreateRectRgn(iStart, iScanLine, iLine, iScanLine + 1);
           CombineRgn(hMask, hTemp, hMask, RGN_OR);
           DeleteObject(hTemp);
           iStart = -1;
       }
   }
   
   delete pData;
   delete pInfo;

   DeleteDC(hMemDC);

   return hMask;
}
