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

   $Id: ttfont.h,v 1.4.40.1 2001/02/15 06:08:01 ijr Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_TTFONT__H_
#define INCLUDED_TTFONT__H_

#include "config.h"
#include "mutex.h"

#include <gdk/gdk.h>
#include <freetype/freetype.h>

typedef struct _ft2font
  {
     FT_Library          library;
     FT_Face             face;
  }
FT2Font;

void FT2Font_draw_string(GdkPixbuf *win, int x, int y, char *text,
                         FT2Font *font, int size, int clipx, int clipy, 
                         int clipw, int cliph);
void FT2Font_free(FT2Font * f);
FT2Font *FT2Font_load(char *file);
int FT2Font_length(FT2Font *f, char *text, int size);

#endif
