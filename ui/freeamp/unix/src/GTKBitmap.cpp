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

   $Id: GTKBitmap.cpp,v 1.15.6.1 2001/02/15 06:08:01 ijr Exp $
____________________________________________________________________________*/ 

#include "config.h"
#include "GTKBitmap.h"

#include "utility.h"

#include <gdk/gdk.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>
using namespace std;

GTKBitmap::GTKBitmap(string &oName)
          :Bitmap(oName)
{
    m_oBitmapName = oName;
    m_Pixbuf = NULL;
    m_width = 0;
    m_height = 0;
}

GTKBitmap::GTKBitmap(int iWidth, int iHeight, const string &oName) 
          :Bitmap(oName)
{
    m_oBitmapName = oName;
    gdk_threads_enter();
    m_Pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, iWidth + 1, 
                              iHeight + 1);
    gint srs = gdk_pixbuf_get_rowstride(m_Pixbuf);
    guchar *s_pix = gdk_pixbuf_get_pixels(m_Pixbuf);

    int step = 4;
    guchar *sp;
    for (int i = 0; i < iHeight; i++)
    {
        sp = s_pix + i * srs + step + 3;
        for (int j = 0; j < iWidth; j++)
        {
            sp++;
            sp++;
            sp++;
            *sp = 255;
            sp++;
        }
    }
  
    gdk_threads_leave();
    m_width = iWidth;
    m_height = iHeight;
}

GTKBitmap::~GTKBitmap(void)
{
    gdk_threads_enter();
    if (m_Pixbuf)
        gdk_pixbuf_unref(m_Pixbuf);
    gdk_threads_leave();
}

Error GTKBitmap::LoadBitmapFromDisk(string &oFile)
{
    struct stat statbuf;
    string filename = oFile;

    if (stat(filename.c_str(), &statbuf) == -1) {
        filename = FindFile(filename);
        if (stat(filename.c_str(), &statbuf) == -1) 
            return kError_LoadBitmapFailed;
    }

    GdkPixbuf *pixbuf;

    gdk_threads_enter();
    pixbuf = gdk_pixbuf_new_from_file(filename.c_str(), NULL);
    if (pixbuf) {
        m_Pixbuf = gdk_pixbuf_add_alpha(pixbuf, m_bHasTransColor, 
                                        m_oTransColor.red, m_oTransColor.green,
                                        m_oTransColor.blue);
        m_width = gdk_pixbuf_get_width(m_Pixbuf);
        m_height = gdk_pixbuf_get_height(m_Pixbuf);
        gdk_pixbuf_unref(pixbuf);
        gdk_threads_leave();
        return kError_NoErr;
    }
    gdk_threads_leave();
    cout << "Gdk-Pixbuf: Could not load " << filename 
         << ".\n";

    return kError_LoadBitmapFailed;
}

bool GTKBitmap::IsPosVisible(Pos &oPos)
{
    Color col;
   
    GetColor(oPos, col);

    if (col.IsEqual(m_oTransColor))
        return false;
    return true;
}

Error GTKBitmap::BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                          Rect &oDestRect)
{
    GdkPixbuf *src = ((GTKBitmap *)pSrcBitmap)->GetPixbuf();
    GdkPixbuf *dest = m_Pixbuf;

    gdk_threads_enter();
    gdk_pixbuf_scale(src, dest, oDestRect.x1, oDestRect.y1,
                     oDestRect.Width(), oDestRect.Height(),
                     oDestRect.x1 - oSrcRect.x1, oDestRect.y1 - oSrcRect.y1,
                     1.0, 1.0, GDK_INTERP_NEAREST);
    gdk_threads_leave();

    return kError_NoErr;
}

static void pixbuf_copy_area_alpha(GdkPixbuf *src, gint sx, gint sy,
                                   GdkPixbuf *dest, gint dx, gint dy,
                                   gint w, gint h)
{
    gint sw, sh, srs;
    gint dw, dh, drs;
    guchar *s_pix;
    guchar *d_pix;
    guchar *sp;
    guchar *dp;
    guchar r, g, b, a;
    gint i, j;

    if (!src || !dest)
        return;

    sw = gdk_pixbuf_get_width(src);
    sh = gdk_pixbuf_get_height(src);

    if (sx < 0 || sx + w > sw)
        return;
    if (sy < 0 || sy + h > sh)
        return;

    dw = gdk_pixbuf_get_width(dest);
    dh = gdk_pixbuf_get_height(dest);

    if (dx < 0 || dx + w > dw)
        return;
    if (dy < 0 || dy + h > dh)
        return;

    srs = gdk_pixbuf_get_rowstride(src);
    drs = gdk_pixbuf_get_rowstride(dest);
    s_pix = gdk_pixbuf_get_pixels(src);
    d_pix = gdk_pixbuf_get_pixels(dest);

    for (i = 0; i < h; i++)
    {
        sp = s_pix + (sy + i) * srs + sx * 4;
        dp = d_pix + (dy + i) * drs + dx * 4;
        for (j = 0; j < w; j++)
        {
            r = *(sp++);
            g = *(sp++);
            b = *(sp++);
            a = *(sp++);
            *dp = (r * a + *dp * (0xff - a)) / 0xff;
            dp++;
            *dp = (g * a + *dp * (0xff - a)) / 0xff;
            dp++;
            *dp = (b * a + *dp * (0xff - a)) / 0xff;
            dp++;
            *dp = 0xff;
            dp++;
        }
    }
}

Error GTKBitmap::MaskBlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect,
                              Rect &oDestRect)
{
    GdkPixbuf *src = ((GTKBitmap *)pSrcBitmap)->GetPixbuf();
    GdkPixbuf *dest = m_Pixbuf;

    gdk_threads_enter();
    pixbuf_copy_area_alpha(src, oSrcRect.x1, oSrcRect.y1, dest, oDestRect.x1,
                           oDestRect.y1, oDestRect.Width(), oDestRect.Height());
    gdk_threads_leave();
    return kError_NoErr;
}

Error GTKBitmap::BlitRectMaskBitmap(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                                    Rect &oDestRect)
{
    GdkPixbuf *src = (((GTKBitmap *)pSrcBitmap)->m_Pixbuf);
    GdkPixbuf *dest = m_Pixbuf;

    gdk_threads_enter();
    
    gint srs = gdk_pixbuf_get_rowstride(src); 
    gint drs = gdk_pixbuf_get_rowstride(dest);

    guchar *s_pix = gdk_pixbuf_get_pixels(src);
    guchar *d_pix = gdk_pixbuf_get_pixels(dest);

    int step = 4;

    guchar *sp, *dp;
    for (int i = 0; i < oDestRect.Height(); i++)
    {
        sp = s_pix + (oSrcRect.y1 + i) * srs + (oSrcRect.x1 * step) + 3;
        dp = d_pix + (oDestRect.y1 + i) * drs + (oDestRect.x1 * step) + 3;
        for (int j = 0; j < oDestRect.Width(); j++)
            *(dp += 4) = *(sp += 4);
    }
    
    gdk_threads_leave();
    return kError_NoErr;
}

Bitmap *GTKBitmap::Clone(void)
{
   return NULL;
} 

Error GTKBitmap::MakeTransparent(Rect &oRect)
{
    gdk_threads_enter();

    gint srs = gdk_pixbuf_get_rowstride(m_Pixbuf);
    guchar *s_pix = gdk_pixbuf_get_pixels(m_Pixbuf);

    int step = 4;

    guchar *sp;
    for (int i = 0; i < oRect.Height(); i++)
    {
        sp = s_pix + (oRect.y1 + i) * srs + (oRect.x1 * step) + 3;
        for (int j = 0; j < oRect.Width(); j++) 
        {
            sp++;
            sp++;
            sp++;
            *sp = 0;
            sp++;
        }
    }

    gdk_threads_leave();
    return kError_NoErr;
}

void GTKBitmap::GetColor(Pos oPos, Color &oColor)
{
    gdk_threads_enter();

    gint rs = gdk_pixbuf_get_rowstride(m_Pixbuf);
    guchar *pix = gdk_pixbuf_get_pixels(m_Pixbuf);
 
    guchar *sp = pix + oPos.y * rs + oPos.x * 4;

    oColor.red = *(sp++);
    oColor.green = *(sp++);
    oColor.blue = *(sp++);
    gdk_threads_leave();
}

void GTKBitmap::GetSize(Pos &oPos)
{
    oPos.x = m_width;
    oPos.y = m_height;
}
