/*____________________________________________________________________________

        FreeAmp - The Free MP3 Player
 
        Portions Copyright (C) 1999 EMusic.com
 
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
 
       $Id: ttfont.c,v 1.1 1999/11/01 05:38:31 ijr Exp $
 ____________________________________________________________________________*/ 

/*
 * Copyright (C) 1999 Carsten Haitzler and various contributors
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#ifdef HAVE_FREETYPE

#include <stdlib.h>
#include "ttfont.h"

#define TT_VALID(handle) ((handle).z != NULL)

static unsigned char alpha_lut[5] =
{0, 64, 128, 192, 255};
static unsigned char bounded_palette[9] =
{0, 1, 2, 3, 4, 4, 4, 4, 4};

static TT_Raster_Map *
create_font_raster(int width, int height)
{
   TT_Raster_Map      *rmap;

   rmap = malloc(sizeof(TT_Raster_Map));
   rmap->width = (width + 3) & -4;
   rmap->rows = height;
   rmap->flow = TT_Flow_Down;
   rmap->cols = rmap->width;
   rmap->size = rmap->rows * rmap->width;
   if (rmap->size > 0)
     {
	rmap->bitmap = malloc(rmap->size);
	memset(rmap->bitmap, 0, rmap->size);
     }
   else
      rmap->bitmap = NULL;
   return rmap;
}

static TT_Raster_Map *
duplicate_raster(TT_Raster_Map * rmap)
{
   TT_Raster_Map      *new_rmap;

   new_rmap = malloc(sizeof(TT_Raster_Map));
   *new_rmap = *rmap;
   if (new_rmap->size > 0)
     {
	new_rmap->bitmap = malloc(new_rmap->size);
	memcpy(new_rmap->bitmap, rmap->bitmap, new_rmap->size);
     }
   else
      new_rmap->bitmap = NULL;
   return new_rmap;
}

static void
clear_raster(TT_Raster_Map * rmap)
{
   memset(rmap->bitmap, 0, rmap->size);
}

static void
destroy_font_raster(TT_Raster_Map * rmap)
{
   if (!rmap)
      return;
   if (rmap->bitmap)
      free(rmap->bitmap);
   free(rmap);
}

static TT_Raster_Map *
calc_size(Efont * f, int *width, int *height, char *text)
{
   int                 i, upm, ascent, descent, pw, ph;
   TT_Instance_Metrics imetrics;
   TT_Glyph_Metrics    gmetrics;
   TT_Raster_Map      *rtmp;

   TT_Get_Instance_Metrics(f->instance, &imetrics);
   upm = f->properties.header->Units_Per_EM;
   ascent = (f->properties.horizontal->Ascender * imetrics.y_ppem) / upm;
   descent = (f->properties.horizontal->Descender * imetrics.y_ppem) / upm;
   if (descent < 0)
      descent = -descent;
   pw = 0;
   ph = ((f->max_ascent) - f->max_descent) / 64;

   for (i = 0; text[i]; i++)
     {
	unsigned char       j = text[i];

	if (!TT_VALID(f->glyphs[j]))
	   continue;
	TT_Get_Glyph_Metrics(f->glyphs[j], &gmetrics);
	if (i == 0)
	  {
	     pw += ((-gmetrics.bearingX) / 64);
	  }
	if (text[i + 1] == 0)
	  {
	     pw += (gmetrics.bbox.xMax / 64);
	  }
	else
	   pw += gmetrics.advance / 64;
     }
   *width = pw;
   *height = ph;

   rtmp = create_font_raster(imetrics.x_ppem + 32, imetrics.y_ppem + 32);
   rtmp->flow = TT_Flow_Up;
   return rtmp;
}

static void
render_text(TT_Raster_Map * rmap, TT_Raster_Map * rchr, Efont * f, char *text,
	    int *xor, int *yor)
{
   TT_Glyph_Metrics    metrics;
   TT_Instance_Metrics imetrics;
   TT_F26Dot6          x, y, xmin, ymin, xmax, ymax;
   int                 i, ioff, iread;
   char               *off, *read, *_off, *_read;
   int                 x_offset, y_offset;
   unsigned char       j;
   TT_Raster_Map      *rtmp;

   TT_Get_Instance_Metrics(f->instance, &imetrics);

   j = text[0];
   TT_Get_Glyph_Metrics(f->glyphs[j], &metrics);
   x_offset = (-metrics.bearingX) / 64;

   y_offset = -(f->max_descent / 64);

   *xor = x_offset;
   *yor = rmap->rows - y_offset;

   rtmp = NULL;
   for (i = 0; text[i]; i++)
     {
	j = text[i];

	if (!TT_VALID(f->glyphs[j]))
	   continue;

	TT_Get_Glyph_Metrics(f->glyphs[j], &metrics);

	xmin = metrics.bbox.xMin & -64;
	ymin = metrics.bbox.yMin & -64;
	xmax = (metrics.bbox.xMax + 63) & -64;
	ymax = (metrics.bbox.yMax + 63) & -64;

	if (f->glyphs_cached[j])
	   rtmp = f->glyphs_cached[j];
	else
	  {
	     rtmp = rchr;
	     clear_raster(rtmp);
	     TT_Get_Glyph_Pixmap(f->glyphs[j], rtmp, -xmin, -ymin);
	     f->glyphs_cached[j] = duplicate_raster(rtmp);
	  }
	/* Blit-or the resulting small pixmap into the biggest one */
	/* We do that by hand, and provide also clipping.          */

	xmin = (xmin >> 6) + x_offset;
	ymin = (ymin >> 6) + y_offset;
	xmax = (xmax >> 6) + x_offset;
	ymax = (ymax >> 6) + y_offset;

	/* Take care of comparing xmin and ymin with signed values!  */
	/* This was the cause of strange misplacements when Bit.rows */
	/* was unsigned.                                             */

	if (xmin >= (int)rmap->width ||
	    ymin >= (int)rmap->rows ||
	    xmax < 0 ||
	    ymax < 0)
	   continue;

	/* Note that the clipping check is performed _after_ rendering */
	/* the glyph in the small bitmap to let this function return   */
	/* potential error codes for all glyphs, even hidden ones.     */

	/* In exotic glyphs, the bounding box may be larger than the   */
	/* size of the small pixmap.  Take care of that here.          */

	if (xmax - xmin + 1 > rtmp->width)
	   xmax = xmin + rtmp->width - 1;

	if (ymax - ymin + 1 > rtmp->rows)
	   ymax = ymin + rtmp->rows - 1;

	/* set up clipping and cursors */

	iread = 0;
	if (ymin < 0)
	  {
	     iread -= ymin * rtmp->cols;
	     ioff = 0;
	     ymin = 0;
	  }
	else
	   ioff = (rmap->rows - ymin - 1) * rmap->cols;

	if (ymax >= rmap->rows)
	   ymax = rmap->rows - 1;

	if (xmin < 0)
	  {
	     iread -= xmin;
	     xmin = 0;
	  }
	else
	   ioff += xmin;

	if (xmax >= rmap->width)
	   xmax = rmap->width - 1;

	_read = (char *)rtmp->bitmap + iread;
	_off = (char *)rmap->bitmap + ioff;

	for (y = ymin; y <= ymax; y++)
	  {
	     read = _read;
	     off = _off;

	     for (x = xmin; x <= xmax; x++)
	       {
		  *off = bounded_palette[*off | *read];
		  off++;
		  read++;
	       }
	     _read += rtmp->cols;
	     _off -= rmap->cols;
	  }
	x_offset += metrics.advance / 64;
     }
}

static void
merge_text_16(GdkImage * xim, TT_Raster_Map * rmap, int offset_x, int offset_y,
	      unsigned long col)
{
   int                 x, y, tmp;
   unsigned char      *ptr;
   unsigned char       cr, cg, cb, a, r, g, b, nr, ng, nb;
   unsigned long       pixel;

   cr = (col >> 8) & 0xf8;
   cg = (col >> 3) & 0xfc;
   cb = (col << 3) & 0xf8;
   for (y = 0; y < xim->height; y++)
     {
	ptr = (unsigned char *)rmap->bitmap + offset_x + ((y + offset_y) * rmap->cols);
	for (x = 0; x < xim->width; x++)
	  {
	     if ((a = alpha_lut[*ptr]) > 0)
	       {
		  if (a < 255)
		    {
		       pixel = gdk_image_get_pixel(xim, x, y);
		       r = (pixel >> 8) & 0xf8;
		       g = (pixel >> 3) & 0xfc;
		       b = (pixel << 3) & 0xf8;

		       tmp = (cr - r) * a;
		       nr = r + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cg - g) * a;
		       ng = g + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cb - b) * a;
		       nb = b + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       pixel = ((nr & 0xf8) << 8) | ((ng & 0xfc) << 3) | ((nb & 0xf8) >> 3);
		       gdk_image_put_pixel(xim, x, y, pixel);
		    }
		  else
		     gdk_image_put_pixel(xim, x, y, col);
	       }
	     ptr++;
	  }
     }
}

static void
merge_text_15(GdkImage * xim, TT_Raster_Map * rmap, int offset_x, int offset_y,
	      unsigned long col)
{
   int                 x, y, tmp;
   unsigned char      *ptr;
   unsigned char       cr, cg, cb, a, r, g, b, nr, ng, nb;
   unsigned long       pixel;

   cr = (col >> 7) & 0xf8;
   cg = (col >> 2) & 0xf8;
   cb = (col << 3) & 0xf8;
   for (y = 0; y < xim->height; y++)
     {
	ptr = (unsigned char *)rmap->bitmap + offset_x + ((y + offset_y) * rmap->cols);
	for (x = 0; x < xim->width; x++)
	  {
	     if ((a = alpha_lut[*ptr]) > 0)
	       {
		  if (a < 255)
		    {
		       pixel = gdk_image_get_pixel(xim, x, y);
		       r = (pixel >> 7) & 0xf8;
		       g = (pixel >> 2) & 0xf8;
		       b = (pixel << 3) & 0xf8;

		       tmp = (cr - r) * a;
		       nr = r + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cg - g) * a;
		       ng = g + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cb - b) * a;
		       nb = b + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       pixel = ((nr & 0xf8) << 7) | ((ng & 0xf8) << 2) | ((nb & 0xf8) >> 3);
		       gdk_image_put_pixel(xim, x, y, pixel);
		    }
		  else
		     gdk_image_put_pixel(xim, x, y, col);
	       }
	     ptr++;
	  }
     }
}

static void
merge_text_24(GdkImage * xim, TT_Raster_Map * rmap, int offset_x, int offset_y,
	      unsigned long col)
{
   int                 x, y, tmp;
   unsigned char      *ptr;
   unsigned char       cr, cg, cb, a, r, g, b, nr, ng, nb;
   unsigned long       pixel;

   cr = (col >> 16) & 0xff;
   cg = (col >> 8) & 0xff;
   cb = col & 0xff;
   for (y = 0; y < xim->height; y++)
     {
	ptr = (unsigned char *)rmap->bitmap + offset_x + ((y + offset_y) * rmap->cols);
	for (x = 0; x < xim->width; x++)
	  {
	     if ((a = alpha_lut[*ptr]) > 0)
	       {
		  if (a < 255)
		    {
		       pixel = gdk_image_get_pixel(xim, x, y);
		       r = (pixel >> 16) & 0xff;
		       g = (pixel >> 8) & 0xff;
		       b = pixel & 0xff;

		       tmp = (cr - r) * a;
		       nr = r + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cg - g) * a;
		       ng = g + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       tmp = (cb - b) * a;
		       nb = b + ((tmp + (tmp >> 8) + 0x80) >> 8);
		       pixel = ((nr << 16) | (ng << 8) | (nb));
		       gdk_image_put_pixel(xim, x, y, pixel);
		    }
		  else
		     gdk_image_put_pixel(xim, x, y, col);
	       }
	     ptr++;
	  }
     }
}

static void
merge_text_1(GdkImage * xim, TT_Raster_Map * rmap, int offset_x, int offset_y,
	     unsigned long col)
{
   int                 x, y;
   unsigned char      *ptr;

   for (y = 0; y < xim->height; y++)
     {
	ptr = (unsigned char *)rmap->bitmap + offset_x + ((y + offset_y) * rmap->cols);
	for (x = 0; x < xim->width; x++)
	  {
	     if (alpha_lut[*ptr] > 2)
		gdk_image_put_pixel(xim, x, y, col);
	     ptr++;
	  }
     }
}

void
EFont_draw_string(GdkPixmap *win, GdkGC *gc, int x, int y, char *text,
		  Efont * font)
{
   GdkImage             *xim = NULL;
   int                  width, height, w, h, inx, iny, clipx, clipy, rx;
   int                  depth;
   TT_Raster_Map       *rmap, *rtmp;
   unsigned long        col = 0;
   GdkGCValues          gcv;
   char                 is_pixmap = 0;

   inx = 0;
   iny = 0;

   rtmp = calc_size(font, &w, &h, text);
   rmap = create_font_raster(w, h);

   render_text(rmap, rtmp, font, text, &inx, &iny);

   is_pixmap = 1;
   gdk_window_get_geometry((GdkWindow *)win, &rx, &rx,
	     &width, &height,
	     &depth);
   gdk_flush();
   gdk_gc_get_values(gc, &gcv);
   col = gcv.foreground.pixel;

   clipx = 0;
   clipy = 0;

   x = x - inx;
   y = y - iny;

   width = width - x;
   height = height - y;
   if (width > w)
      width = w;
   if (height > h)
      height = h;

   if (x < 0)
     {
	clipx = -x;
	width += x;
	x = 0;
     }
   if (y < 0)
     {
	clipy = -y;
	height += y;
	y = 0;
     }
   if ((width <= 0) || (height <= 0))
     {
	destroy_font_raster(rmap);
	destroy_font_raster(rtmp);
	return;
     }

   xim = gdk_image_get((GdkWindow *)win, x, y, width, height);

   if (depth == 16)
     {
/*	if (id->x.render_depth == 15)
	   merge_text_15(xim, rmap, clipx, clipy, col);
	else */
	   merge_text_16(xim, rmap, clipx, clipy, col);
     }
   else if ((depth == 24) || (depth == 32))
      merge_text_24(xim, rmap, clipx, clipy, col);
   else if (depth == 15)
      merge_text_15(xim, rmap, clipx, clipy, col);
   else if (depth <= 8)
      merge_text_1(xim, rmap, clipx, clipy, col);

   gdk_draw_image((GdkWindow *)win, gc, xim, 0, 0, x, y, width, height);

   destroy_font_raster(rmap);
   destroy_font_raster(rtmp);
   gdk_image_destroy(xim);
}

void
Efont_free(Efont * f)
{
   int                 i;

   if (!f)
      return;
   TT_Done_Instance(f->instance);
   TT_Close_Face(f->face);
   for (i = 0; i < 256; i++)
     {
	if (f->glyphs_cached[i])
	   destroy_font_raster(f->glyphs_cached[i]);
	if (!TT_VALID(f->glyphs[i]))
	   TT_Done_Glyph(f->glyphs[i]);
     }
   if (f->glyphs)
      free(f->glyphs);
   if (f->glyphs_cached)
      free(f->glyphs_cached);
   free(f);
}

Efont              *
Efont_load(char *file, int size)
{
   TT_Error            error;
   TT_CharMap          char_map;
   TT_Glyph_Metrics    metrics;
   static TT_Engine    engine;
   static char         have_engine = 0;
   int                 dpi = 96;
   Efont              *f;
   unsigned short      i, n, code, load_flags;
   unsigned short      num_glyphs = 0, no_cmap = 0;
   unsigned short      platform, encoding;

   if (!have_engine)
     {
	error = TT_Init_FreeType(&engine);
	if (error)
	   return NULL;
	have_engine = 1;
     }
   f = malloc(sizeof(Efont));
   f->engine = engine;
   error = TT_Open_Face(f->engine, file, &f->face);
   if (error)
     {
	free(f);
/*      fprintf(stderr, "Unable to open font\n"); */
	return NULL;
     }
   error = TT_Get_Face_Properties(f->face, &f->properties);
   if (error)
     {
	TT_Close_Face(f->face);
	free(f);
/*      fprintf(stderr, "Unable to get face properties\n"); */
	return NULL;
     }
   error = TT_New_Instance(f->face, &f->instance);
   if (error)
     {
	TT_Close_Face(f->face);
	free(f);
/*      fprintf(stderr, "Unable to create instance\n"); */
	return NULL;
     }
   TT_Set_Instance_Resolutions(f->instance, dpi, dpi);
   TT_Set_Instance_CharSize(f->instance, size * 64);

   n = f->properties.num_CharMaps;

   for (i = 0; i < n; i++)
     {
	TT_Get_CharMap_ID(f->face, i, &platform, &encoding);
	if ((platform == 3 && encoding == 1) ||
	    (platform == 0 && encoding == 0))
	  {
	     TT_Get_CharMap(f->face, i, &char_map);
	     break;
	  }
     }
   if (i == n)
     {
	no_cmap = 1;
	num_glyphs = f->properties.num_Glyphs;
	TT_Done_Instance(f->instance);
	TT_Close_Face(f->face);
	free(f);
/*      fprintf(stderr, "Sorry, but this font doesn't contain any Unicode mapping table\n"); */
	return NULL;
     }
   f->num_glyph = 256;
   f->glyphs = (TT_Glyph *) malloc(256 * sizeof(TT_Glyph));
   memset(f->glyphs, 0, 256 * sizeof(TT_Glyph));
   f->glyphs_cached = (TT_Raster_Map **) malloc(256 * sizeof(TT_Raster_Map *));
   memset(f->glyphs_cached, 0, 256 * sizeof(TT_Raster_Map *));

   load_flags = TTLOAD_SCALE_GLYPH | TTLOAD_HINT_GLYPH;

   f->max_descent = 0;
   f->max_ascent = 0;

   for (i = 0; i < 256; ++i)
     {
	if (TT_VALID(f->glyphs[i]))
	   continue;

	if (no_cmap)
	  {
	     code = (i - ' ' + 1) < 0 ? 0 : (i - ' ' + 1);
	     if (code >= num_glyphs)
		code = 0;
	  }
	else
	   code = TT_Char_Index(char_map, i);

	TT_New_Glyph(f->face, &f->glyphs[i]);
	TT_Load_Glyph(f->instance, f->glyphs[i], code, load_flags);
	TT_Get_Glyph_Metrics(f->glyphs[i], &metrics);

	if ((metrics.bbox.yMin & -64) < f->max_descent)
	   f->max_descent = (metrics.bbox.yMin & -64);
	if (((metrics.bbox.yMax + 63) & -64) > f->max_ascent)
	   f->max_ascent = ((metrics.bbox.yMax + 63) & -64);
     }
   return f;
}

void
Efont_extents(Efont * f, char *text, int *font_ascent_return,
	      int *font_descent_return, int *width_return,
	      int *max_ascent_return, int *max_descent_return,
	      int *lbearing_return, int *rbearing_return)
{
   int                 i, upm, ascent, descent, pw;
   TT_Instance_Metrics imetrics;
   TT_Glyph_Metrics    gmetrics;

   if (!f)
      return;

   TT_Get_Instance_Metrics(f->instance, &imetrics);
   upm = f->properties.header->Units_Per_EM;
   ascent = (f->properties.horizontal->Ascender * imetrics.y_ppem) / upm;
   descent = (f->properties.horizontal->Descender * imetrics.y_ppem) / upm;
   if (ascent < 0)
      ascent = -ascent;
   if (descent < 0)
      descent = -descent;
   pw = 0;

   for (i = 0; text[i]; i++)
     {
	unsigned char       j = text[i];

	if (!TT_VALID(f->glyphs[j]))
	   continue;
	TT_Get_Glyph_Metrics(f->glyphs[j], &gmetrics);
	if (i == 0)
	  {
	     if (lbearing_return)
		*lbearing_return = ((-gmetrics.bearingX) / 64);
	  }
	if (text[i + 1] == 0)
	  {
	     if (rbearing_return)
		*rbearing_return = ((gmetrics.bbox.xMax - gmetrics.advance) / 64);
	  }
	pw += gmetrics.advance / 64;
     }
   if (font_ascent_return)
      *font_ascent_return = ascent;
   if (font_descent_return)
      *font_descent_return = descent;
   if (width_return)
      *width_return = pw;
   if (max_ascent_return)
      *max_ascent_return = f->max_ascent;
   if (max_descent_return)
      *max_descent_return = f->max_descent;
}

#endif
