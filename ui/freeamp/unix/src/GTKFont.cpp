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

   $Id: GTKFont.cpp,v 1.1.2.1 1999/10/01 15:22:34 ijr Exp $
____________________________________________________________________________*/ 

#include "GTKFont.h"
#include "GTKUtility.h"
#include "debug.h"

GTKFont::GTKFont(string &oName, string &oFace, string &oDefault) :
                Font(oName, oFace, oDefault)
{
    type = kFontTypeUnknown;
    
    char *dup = strdup(m_oFace.c_str());
    char *token = strtok(dup, ",");
    bool found = false;
    gdk_threads_enter();
    for (;;) {
        if (found = ListFonts(token))
            break;
        token = strtok(NULL, ",");
        if (token == NULL)
            break;
    }
    gdk_threads_leave();
    if (found) {
        m_oFace = token;
        type = kFontTypeGdk;
    }
    else {
        m_oFace = "default";
        type = kFontTypeGdk;
    }
    free(dup);

    gfont = NULL;
    bold = false;
    italic = false;
    underline = false;
    first = true;
}

Error GTKFont::RenderFont(int iFontHeight, Rect &oClipRect, string &oText,
                          int iOffset, const Color &oColor, bool bBold,
                          bool bItalic, bool bUnderline, GTKBitmap *bitmap)
{
    string fontname = BuildFontString(bBold, bItalic, bUnderline, iFontHeight);
    GdkGC *gc = gdk_gc_new((GdkWindow *)bitmap->GetBitmap());
    gfont = gdk_font_load(fontname.c_str());
    if (!gfont) {
        fontname = "-*-" + m_oFace + string("-*");
        gfont = gdk_font_load(fontname.c_str());
        if (!gfont) {
            gfont = gdk_font_load("default");  
            if (!gfont) {
                cout << "oops, couldn't load a font...\n";
                return kError_NoErr;
            }
        }
    } 
    return kError_NoErr;
}

string GTKFont::BuildFontString(bool bBold, bool bItalic, bool bUnderline,
                                int iFontHeight)
{
   // This isn't the greatest method, as it will probably return stuff we
   // don't have....
   string retstring = "-*-" + m_oFace;
   if (bBold)
       retstring += string("-bold-");
   else
       retstring += string("-medium-");
   if (bItalic)
       retstring += string("i-normal-*-");
   else 
       retstring += string("r-normal-*-");
   char tempstr[16];
   sprintf(tempstr, "%d", iFontHeight);
   retstring += string(tempstr) + string("-*");
   return retstring;
}

GTKFont::~GTKFont(void)
{
    if (type == kFontTypeGdk)
        if (gfont)
            gdk_font_unref(gfont);
}
