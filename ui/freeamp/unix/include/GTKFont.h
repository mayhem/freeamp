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

   $Id: GTKFont.h,v 1.2 1999/10/19 07:13:19 elrod Exp $
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

      Error    Load(int iFontHeight, bool bBold, bool bItalic);
      int      GetLength(string &oText);
      int      GetHeight(string &oText);
      void     Render(Rect &oClipRect, string &oText, int iOffset, 
                      const Color &oColor, GTKBitmap *bitmap, bool bUnderline);
      
    private:
      FontTypeEnum type;

      GdkFont *gfont;
      string   BuildFontString(bool bBold, bool bItalic, int iFontHeight);

      bool bold;
      bool italic;
      bool underline;
      int  size;
      bool first;
};

#endif
