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

   $Id: GTKCanvas.cpp,v 1.1.2.7 1999/09/28 05:16:53 ijr Exp $
____________________________________________________________________________*/ 

#include "GTKCanvas.h"

GTKCanvas::GTKCanvas(GTKWindow *pParent)
{
    m_pParent = pParent;
    m_pBufferBitmap = NULL;
    shape_set = false;
}

GTKCanvas::~GTKCanvas(void)
{
    delete m_pBufferBitmap;
}

void GTKCanvas::Init(void)
{
    Rect oDestRect;
    string oName("DoubleBuffer");

    assert(m_pBGBitmap);

    if (m_pBufferBitmap)
        delete m_pBufferBitmap;

    m_pBufferBitmap = new GTKBitmap(m_oBGRect.Width(), 
                                    m_oBGRect.Height(),
                                    oName);

    oDestRect.x1 = oDestRect.y1 = 0;
    oDestRect.x2 = m_oBGRect.Width();
    oDestRect.y2 = m_oBGRect.Height();
    m_pBufferBitmap->MaskBlitRect(m_pBGBitmap, m_oBGRect, oDestRect);
}

Error GTKCanvas::RenderText(int iFontHeight, Rect &oClipRect,
                            string &oText, AlignEnum eAlign, 
                            string &oFont, const Color &oColor)
{
   Erase(oClipRect);
   return kError_NoErr;
}

Error GTKCanvas::Invalidate(Rect &oRect)
{
//   Paint(oRect);

   return kError_NoErr;
}

Error GTKCanvas::Update(void)
{
   Rect foo;  
   Paint(foo);

   return kError_NoErr;
}

Error GTKCanvas::BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRec)
{
   if (!m_pBufferBitmap)
       return kError_NoErr;

   return m_pBufferBitmap->BlitRect(pSrcBitmap, oSrcRect, oDestRec);
}

Error GTKCanvas::MaskBlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, Rect &oDestRec)
{
   if (!m_pBufferBitmap)
       return kError_NoErr;

   return m_pBufferBitmap->MaskBlitRect(pSrcBitmap, oSrcRect, oDestRec);
}

void GTKCanvas::Paint(Rect &oRect)
{
    GtkWidget *w = m_pParent->GetWindow();
    gdk_threads_enter();
    if (!shape_set) {
        shape_set = true;
        GdkBitmap *mask = ((GTKBitmap *)m_pBGBitmap)->GetMask();
        if (mask)
            gdk_window_shape_combine_mask(w->window, mask, 0, 0);
    }
    gdk_window_set_back_pixmap(w->window, m_pBufferBitmap->GetBitmap(), 0);
    gdk_window_clear(w->window);
    gdk_threads_leave();
}

void GTKCanvas::Erase(Rect &oRect)
{
    if (m_pBufferBitmap)
        m_pBufferBitmap->MaskBlitRect(m_pBGBitmap, oRect, oRect);
}
