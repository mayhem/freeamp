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

   $Id: GTKCanvas.cpp,v 1.1.2.9 1999/10/02 00:40:14 ijr Exp $
____________________________________________________________________________*/ 

#include "GTKCanvas.h"
#include "GTKFont.h"

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

int GTKCanvas::RenderText(int iFontHeight, Rect &oClipRect,
                          string &oText, AlignEnum eAlign, 
                          Font *pFont, const Color &oColor,
                          bool bBold, bool bItalic, bool bUnderline)
{
    Erase(oClipRect);
    GTKFont *ourFont = (GTKFont *)pFont;
    Error err = ourFont->Load(iFontHeight, bBold, bItalic);
    if (IsError(err)) 
        return 0;
    int width = ourFont->GetLength(oText);
    int offset = 0;

    if (eAlign == eLeft)
        offset = 0;
    else if (eAlign == eRight)
        offset = oClipRect.Width() - width;
    else  
        offset = (oClipRect.Width() - width) / 2;
    
    return RenderOffsetText(iFontHeight, oClipRect, oText, offset, pFont, 
                            oColor, bBold, bItalic, bUnderline);
}

int GTKCanvas::RenderOffsetText(int iFontHeight, Rect &oClipRect,
                                string &oText, int iOffset,
                                Font *pFont, const Color &oColor,
                                bool bBold, bool bItalic, bool bUnderline)
{
    Erase(oClipRect);
    GTKFont *ourFont = (GTKFont *)pFont;
    Error err = ourFont->Load(iFontHeight, bBold, bItalic);
    if (IsError(err))
        return 0;
    int width = ourFont->GetLength(oText);
    
    ourFont->Render(oClipRect, oText, iOffset, oColor, m_pBufferBitmap,
                    bUnderline);

    Update();
    if (width + iOffset > oClipRect.Width())
        return width + iOffset - oClipRect.Width();
    return 0;
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
    gdk_flush();
    gdk_threads_leave();
}

void GTKCanvas::Erase(Rect &oRect)
{
    if (m_pBufferBitmap)
        m_pBufferBitmap->MaskBlitRect(m_pBGBitmap, oRect, oRect);
}
