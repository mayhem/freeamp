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

   $Id: GTKFont.h,v 1.1.2.1 1999/10/01 15:22:34 ijr Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_GTKFONT_H__
#define INCLUDED_GTKFONT_H__

#include <string>
#include <gdk/gdk.h>
#include "GTKBitmap.h"

using namespace std;

#include "Font.h"

enum FontTypeEnum 
{
    kFontTypeGdk,
    kFontTypeGdkFontSet,
    kFontTypeTTF,
    kFontTypeBitmap,
    kFontTypeUnknown
}; 

class GTKFont : public Font
{
    public:

               GTKFont(string &oName, string &oFace, string &oDefault);
      virtual ~GTKFont(void);

      Error    RenderFont(int iFontHeight, Rect &oClipRect, string &oText,
		          int iOffset, const Color &oColor, bool bBold, 
			  bool bItalic, bool bUnderline, GTKBitmap *bitmap);
    private:
      FontTypeEnum type;

      GdkFont *gfont;
      string   BuildFontString(bool bBold, bool bItalic, bool bUnderLine, 
		               int iFontHeight);

      bool bold;
      bool italic;
      bool underline;
      bool first;
};

#endif
