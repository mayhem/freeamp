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

   $Id: GTKBitmap.cpp,v 1.1.2.4 1999/09/21 16:34:55 ijr Exp $
____________________________________________________________________________*/ 

#include "string"
#include "GTKBitmap.h"

#include <gdk/gdk.h>
#include <gdk/gdkprivate.h>
#include <sys/stat.h>
#include <unistd.h>

// This is basically bmp.c from xmms, although cleaned up and with a couple 
// additions/fixes from imlib's bmp loader.

typedef struct tagRGBQUAD
{
    guchar rgbBlue;
    guchar rgbGreen;
    guchar rgbRed;
    guchar rgbReserved;
}
RGBQUAD;

#define BI_RGB       0
#define BI_RLE8      1
#define BI_RLE4      2
#define BI_BITFIELDS 3

GTKBitmap::GTKBitmap(string &oName)
          :Bitmap(oName)
{
    m_oBitmapName = oName;
    m_Bitmap = NULL;
    m_GC = NULL;
}

GTKBitmap::~GTKBitmap(void)
{
    if (m_Bitmap)
        gdk_pixmap_unref(m_Bitmap);
    m_Bitmap = NULL;

    if (m_GC)
        gdk_gc_unref(m_GC);
    m_GC = NULL; 
}

Error GTKBitmap::ReadleShort(FILE *file, gushort *ret)
{
    guchar b[2];

    if (fread(b, sizeof(guchar), 2, file) != 2)
        return kError_LoadBitmapFailed;

    *ret = (b[1] << 8) | b[0];
    return kError_NoErr;
}

Error GTKBitmap::ReadleLong(FILE *file, gulong *ret)
{
    guchar b[4];

    if (fread(b, sizeof(guchar), 4, file) != 4)
        return kError_LoadBitmapFailed;
 
    *ret = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
    return kError_NoErr;
}

Error GTKBitmap::LoadBitmapFromDisk(string &oFile)
{
    FILE *file;
    gchar type[2];
    gulong size, offset, headSize, w, h, comp, imgsize, j, k, l;
    gushort tmpShort, planes, bitcount, ncols, skip;
    guchar tempchar, *data, *data_end, byte = 0, g, b, r, *buffer, *buffer_end;
    struct stat statbuf;
    register guchar *ptr, *buffer_ptr;
    register gulong i;
    register gushort x, y;
    RGBQUAD rgbQuads[256];

    if (stat(oFile.c_str(), &statbuf) == -1)
        return kError_LoadBitmapFailed;
    size = statbuf.st_size;

    file = fopen(oFile.c_str(), "rb");
    if (!file)
        return kError_LoadBitmapFailed;

    if (fread(type, 1, 2, file) != 2) {
        fclose(file);
        return kError_LoadBitmapFailed;
    }
    if (strncmp(type, "BM", 2)) {
        fclose(file);
        return kError_LoadBitmapFailed;
    }
    fseek(file, 8, SEEK_CUR);
    ReadleLong(file, &offset);
    ReadleLong(file, &headSize);
    if (headSize == 12) {
        ReadleShort(file, &tmpShort);
        w = tmpShort;
        ReadleShort(file, &tmpShort);
        h = tmpShort;
        ReadleShort(file, &planes);
        ReadleShort(file, &bitcount);
        imgsize = size - offset;
        comp = BI_RGB;
    }
    else if (headSize == 40) {
        ReadleLong(file, &w);
        ReadleLong(file, &h);
        ReadleShort(file, &planes);
        ReadleShort(file, &bitcount);
        ReadleLong(file, &comp);
        ReadleLong(file, &imgsize);
        imgsize = size - offset;

        fseek(file, 16, SEEK_CUR);
    }
    else {
        fclose(file);
        return kError_LoadBitmapFailed;
    }

    if (bitcount != 24) {
        ncols = (offset - headSize - 14);
        if (headSize == 12) {
            ncols /= 3;
            for (i = 0; i < ncols; i++)
                fread(&rgbQuads[i], 3, 1, file);
        }
        else {
            ncols /= 4;
            fread(rgbQuads, 4, ncols, file);
        }
    }

    fseek(file, offset, SEEK_SET);
    buffer = (guchar *)g_malloc(imgsize);
    fread(buffer, imgsize, 1, file);
    fclose(file);
    buffer_ptr = buffer;
    buffer_end = buffer + imgsize;
    data = (guchar *)g_malloc0((w * 3 * h) + 3);   /* +3 is just for safety
 */
    data_end = data + (w * 3 * h);
    if (!data) {
        fclose(file);
        return kError_LoadBitmapFailed;
    }
        
    ptr = data + ((h - 1) * w * 3);
    if (bitcount == 4) {
        if (comp == BI_RLE4) {
            x = 0;
            y = 0;
            for (i = 0, g = 1; i < imgsize && g && buffer_ptr < buffer_end; i++) {
                byte = *(buffer_ptr++);
                if (byte) {
                    guchar t1, t2;

                    l = byte;
                    byte = *(buffer_ptr++);
                    t1 = byte & 0xF;
                    t2 = (byte >> 4) & 0xF;
                    for (j = 0; j < l; j++) {
                        k = (j & 1) ? t1 : t2;

                        if (x >= w)
                            break;

                        *ptr++ = rgbQuads[k].rgbRed;
                        *ptr++ = rgbQuads[k].rgbGreen;
                        *ptr++ = rgbQuads[k].rgbBlue;
                        x++;
                        if (ptr > data_end)
                            ptr = data_end;

                    }
                }
                else {
                    byte = *(buffer_ptr++);
                    switch (byte) {
                        case 0:
                            x = 0;
                            y++;
                            ptr = data + ((h - y - 1) * w * 3) + (x * 3);
                            if (ptr > data_end)
                                ptr = data_end;
                            break;
                        case 1:
                            g = 0;
                            break;
                        case 2:
                            x += *(buffer_ptr++);
                            y += *(buffer_ptr++);
                            ptr = data + ((h - y - 1) * w * 3) + (x * 3);
                            if (ptr > data_end)
                                ptr = data_end;
                            break;
                        default:
                            l = byte;
                            for (j = 0; j < l; j++) {
                                guchar t1 = '\0', t2 = '\0';
 
                                if ((j & 1) == 0) {
                                    byte = *(buffer_ptr++);
                                    t1 = byte & 0xF;
                                    t2 = (byte >> 4) & 0xF;
                                }
                                k = (j & 1) ? t1 : t2;

                                if (x >= w) {
                                    buffer_ptr += (l - j) / 2;
                                    break;
                                }

                                *ptr++ = rgbQuads[k].rgbRed;
                                *ptr++ = rgbQuads[k].rgbGreen;
                                *ptr++ = rgbQuads[k].rgbBlue;

                                x++;

                                if (ptr > data_end)
                                    ptr = data_end;

                            }

                            if ((l & 3) == 1) {
                                tempchar = *(buffer_ptr++);
                                tempchar = *(buffer_ptr++);
                            }
                            else if ((l & 3) == 2)
                                buffer_ptr++;
                            break;
                    }
                }
            }
        }
        else if (comp == BI_RGB) {
            skip = ((((w + 7) / 8) * 8) - w) / 2;
            for (y = 0; y < h; y++) {
                for (x = 0; x < w && buffer_ptr < buffer_end; x++) {
                    if ((x & 1) == 0)
                        byte = *(buffer_ptr++);
                    k = (byte & 0xF0) >> 4;
                    *ptr++ = rgbQuads[k].rgbRed;
                    *ptr++ = rgbQuads[k].rgbGreen;
                    *ptr++ = rgbQuads[k].rgbBlue;
                    byte <<= 4;
                }
                buffer_ptr += skip;
                ptr -= w * 6;
            }
        }
    }
    if (bitcount == 8) {
        if (comp == BI_RLE8) {
            x = 0;
            y = 0;
            for (i = 0, g = 1; i < imgsize && buffer_ptr < buffer_end && g; i++) {
                byte = *(buffer_ptr++);
                if (byte) {
                    l = byte;
                    byte = *(buffer_ptr++);
                    for (j = 0; j < l; j++) {
                        if (x >= w)
                            break;

                        *ptr++ = rgbQuads[byte].rgbRed;
                        *ptr++ = rgbQuads[byte].rgbGreen;
                        *ptr++ = rgbQuads[byte].rgbBlue;
                        x++;
                        if (ptr > data_end)
                            ptr = data_end;
                    }
                }
                else {
                    byte = *(buffer_ptr++);
                    switch (byte) {
                        case 0:
                            x = 0;
                            y++;
                            ptr = data + ((h - y - 1) * w * 3) + (x * 3);
                            if (ptr > data_end)
                                ptr = data_end;
                            break;
                        case 1:
                            g = 0;
                            break;
                        case 2:
                            x += *(buffer_ptr++);
                            y += *(buffer_ptr++);
                            ptr = data + ((h - y - 1) * w * 3) + (x * 3);
                            if (ptr > data_end)
                                ptr = data_end;
                            break;
                        default:
                            l = byte;
                            for (j = 0; j < l; j++) {
                                byte = *(buffer_ptr++);

                                if (x >= w) {
                                    buffer_ptr += l - j;
                                    break;
                                }

                                *ptr++ = rgbQuads[byte].rgbRed;
                                *ptr++ = rgbQuads[byte].rgbGreen;
                                *ptr++ = rgbQuads[byte].rgbBlue;
                                x++;

                                if (ptr > data_end)
                                    ptr = data_end;
                            }
                            if (l & 1)
                                buffer_ptr++;
                            break;
                    }
                }
            }
        }
        else if (comp == BI_RGB) {
            skip = (((w + 3) / 4) * 4) - w;
            for (y = 0; y < h; y++) {
                for (x = 0; x < w && buffer_ptr < buffer_end; x++) {
                    byte = *(buffer_ptr++);
                    *ptr++ = rgbQuads[byte].rgbRed;
                    *ptr++ = rgbQuads[byte].rgbGreen;
                    *ptr++ = rgbQuads[byte].rgbBlue;
                }
                ptr -= w * 6;
                buffer_ptr += skip;
            }
        }

    }
    else if (bitcount == 24) {
        skip = (4 - ((w * 3) % 4)) & 3;
        for (y = 0; y < h; y++) {
            for (x = 0; x < w && buffer_ptr < buffer_end; x++) {
                b = *(buffer_ptr++);
                g = *(buffer_ptr++);
                r = *(buffer_ptr++);
                *ptr++ = r;
                *ptr++ = g;
                *ptr++ = b;
            }
            ptr -= w * 6;
            buffer_ptr += skip;
        }
    }

    m_Bitmap = gdk_pixmap_new(NULL, w, h, gdk_visual_get_best_depth());

    if (!m_GC) 
        m_GC = gdk_gc_new((GdkWindow *)&gdk_root_parent); // naughty naughty

    gdk_draw_rgb_image(m_Bitmap, m_GC, 0, 0, w, h, GDK_RGB_DITHER_MAX, data, w * 3);

    g_free(data);
    g_free(buffer);

    return kError_NoErr;
}

Error GTKBitmap::BlitRect(Bitmap *pSrcBitmap, Rect &oSrcRect, 
                          Rect &oDestRect)
{
    GdkWindow *src = (GdkWindow *)(((GTKBitmap *)pSrcBitmap)->m_Bitmap);
    GdkWindow *dest = (GdkWindow *)m_Bitmap;

    gdk_window_copy_area(dest, m_GC, oDestRect.x1, oDestRect.y1, src,
                         oSrcRect.x1, oSrcRect.y1, oDestRect.Width(),
                         oDestRect.Height());

    return kError_NoErr;
}

