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
 
       $Id: ttfont.cpp,v 1.8.6.1 2001/02/15 06:08:01 ijr Exp $
 ____________________________________________________________________________*/ 

#include "config.h"

#include <iostream>

using namespace std;

#include <stdio.h>
#include "ttfont.h"


#define UTF8_LENGTH(Char)              \
 (((Char) < 128) ? 1 :                 \
 ((((Char) & 0xe0) == 0xc0) ? 2 :      \
 ((((Char) & 0xf0) == 0xe0) ? 3 :      \
 ((((Char) & 0xf8) == 0xf0) ? 4 :      \
 ((((Char) & 0xfc) == 0xf8) ? 5 :      \
 ((((Char) & 0xfe) == 0xfc) ? 6 : -1))))))
Mutex ttfLock;

void
FT2Font_draw_string(GdkPixbuf *win, int x, int y, char *text, FT2Font * font,
                    int size, int clipx, int clipy, int clipw, int cliph)
{
   FT_GlyphSlot   slot = font->face->glyph;
   FT_UInt        glyph_index, previous;
   FT_Bool        use_kerning;
   FT_Error       error;
   int            pen_x, pen_y;
   int            start_x, start_y, end_x, end_y;
   int            i, j;
   gint           dest_w, dest_h, dest_rs;
   guchar        *dest_pix;
   guchar        *dp, *sp;
   guchar         r, g, b, a;

   dest_w = gdk_pixbuf_get_width(win);
   dest_h = gdk_pixbuf_get_height(win);
   dest_rs = gdk_pixbuf_get_rowstride(win);
   dest_pix = gdk_pixbuf_get_pixels(win);

   pen_x = x+1;
   pen_y = y;

   use_kerning = FT_HAS_KERNING(font->face);
   previous = 0;

   ttfLock.Acquire();

   FT_Set_Char_Size(font->face, size << 6, size << 6, 72, 72);

   unsigned char *p = (unsigned char *)text; 
   while (*p)
   {
       gunichar guc = g_utf8_get_char((char *)p);
       glyph_index = FT_Get_Char_Index(font->face, guc);

       if (!glyph_index) {
           //glyph_index = FT_Get_Char_Index(font->face, ' ');
           p += UTF8_LENGTH(*p);
           continue;
       }

       if (use_kerning && previous && glyph_index)
       {
           FT_Vector delta;
           FT_Get_Kerning(font->face, previous, glyph_index, 
                          0, &delta);

           pen_x += delta.x >> 6;
       }

       error = FT_Load_Glyph(font->face, glyph_index, FT_LOAD_RENDER);
       if (error)
           continue;

       start_x = pen_x + slot->bitmap_left;
       start_y = pen_y - slot->bitmap_top;

       end_x = start_x + slot->bitmap.width;
       if (end_x >= dest_w)
           end_x = dest_w - 1;

       end_y = start_y + slot->bitmap.rows;
       if (end_y >= dest_h)
           end_y = dest_h - 1;

      for (i = 0; i < end_y - start_y; i++)
      {
          dp = dest_pix + (start_y + i) * dest_rs + start_x * 4;
          sp = slot->bitmap.buffer + (i * slot->bitmap.pitch);
          for (j = start_x; j < end_x; j++)
          {
              if (j < clipx || j > (clipx + clipw))
              {
                  sp++;
                  dp++; dp++; dp++; dp++;
                  continue;
              }
              r = g = b = 0;
              a = *sp;
              sp++;
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
      pen_x += slot->advance.x >> 6;
      previous = glyph_index;
      p += UTF8_LENGTH(*p);
   }

   ttfLock.Release();
}

void
FT2Font_free(FT2Font * f)
{
   ttfLock.Acquire();

   FT_Done_Face(f->face); 
   FT_Done_FreeType(f->library);

   delete f;
   ttfLock.Release();
}

FT2Font *
FT2Font_load(char *file)
{
   FT_Error            error;
   FT2Font            *f;

   ttfLock.Acquire();

   f = new FT2Font;

   error = FT_Init_FreeType(&(f->library));
   if (error) {
       ttfLock.Release();
       return NULL;
   }

   error = FT_New_Face(f->library, file, 0, &f->face);
   if (error)
   {
       FT_Done_FreeType(f->library);
       delete f;
       ttfLock.Release();
       return NULL;
   }

   error = FT_Select_Charmap(f->face, ft_encoding_unicode);
   if (error)
   {
       FT_Select_Charmap(f->face, ft_encoding_none);
   }

   ttfLock.Release();

   return f;
}

int 
FT2Font_length(FT2Font *f, char *text, int size)
{
   FT_GlyphSlot   slot = f->face->glyph;
   FT_UInt        glyph_index, previous;
   FT_Bool        use_kerning;
   int            pen_x;
   unsigned int   n;

   pen_x = 0;

   use_kerning = FT_HAS_KERNING(f->face);
   previous = 0;

   ttfLock.Acquire();

   FT_Set_Char_Size(f->face, size << 6, size << 6, 72, 72);

   for (n = 0; n < strlen(text); n++)
   {
       glyph_index = FT_Get_Char_Index(f->face, text[n]);
       if (!glyph_index) {
           glyph_index = FT_Get_Char_Index(f->face, ' ');
       }

       if (use_kerning && previous && glyph_index)
       {
           FT_Vector delta;
           FT_Get_Kerning(f->face, previous, glyph_index, 0, &delta);

           pen_x += delta.x >> 6;
       }

       FT_Load_Glyph(f->face, glyph_index, FT_LOAD_DEFAULT);

      pen_x += (slot->advance.x >> 6);
      previous = glyph_index;
   }

   ttfLock.Release();

   return pen_x;
}
