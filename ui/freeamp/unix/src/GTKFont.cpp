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

   $Id: GTKFont.cpp,v 1.2 1999/10/19 07:13:20 elrod Exp $
____________________________________________________________________________*/ 

#include "GTKFont.h"
#include "GTKUtility.h"
#include <unistd.h>

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
        m_oFace = m_oDefault;
        type = kFontTypeGdk;
    }
    free(dup);

    gfont = NULL;
    bold = false;
    italic = false;
    underline = false;
    first = true;
}

Error GTKFont::Load(int iFontHeight, bool bBold, bool bItalic)
{
    if (bold != bBold || italic != bItalic || size != iFontHeight || !gfont) {
        bold = bBold;
        italic = bItalic;
        size = iFontHeight;
        gdk_threads_enter();
        if (gfont)
            gdk_font_unref(gfont);
        string fontname = BuildFontString(bold, italic, size);
        gfont = gdk_font_load(fontname.c_str());
        if (!gfont) {
            fontname = "-*-" + m_oFace + string("-*");
            gfont = gdk_font_load(fontname.c_str());
            if (!gfont) {
                gfont = gdk_font_load("default");  
                if (!gfont) {
                    gdk_threads_leave();
                    cout << "oops, couldn't load _any_ fonts...\n";
                    return kError_YouScrewedUp;
                }
            }
        } 
        gdk_threads_leave();
    }
    return kError_NoErr;
}

int GTKFont::GetLength(string &oText)
{
    assert(gfont);
    
    gdk_threads_enter();
    int retvalue = gdk_string_measure(gfont, oText.c_str());
    gdk_threads_leave();
 
    return retvalue;
}

int GTKFont::GetHeight(string &oText)
{
    assert(gfont);
   
    gdk_threads_enter();
    int retvalue = gdk_string_height(gfont, oText.c_str());
    gdk_threads_leave();
   
    return retvalue;
}

void GTKFont::Render(Rect &oClipRect, string &oText, int iOffset, 
                     const Color &oColor, GTKBitmap *bitmap, bool bUnderline)
{
    assert(gfont);

    gdk_threads_enter();
    GdkGC *gc = gdk_gc_new((GdkWindow *)bitmap->GetBitmap());
    gdk_rgb_gc_set_foreground(gc, (oColor.red << 16) | (oColor.green << 8) |
                              oColor.blue);

    GdkRectangle clipRect;
    clipRect.x = oClipRect.x1;
    clipRect.y = oClipRect.y1;
    clipRect.width = oClipRect.Width();
    clipRect.height = oClipRect.Height();

    gdk_gc_set_clip_rectangle(gc, &clipRect);

    gdk_draw_string(bitmap->GetBitmap(), gfont, gc, oClipRect.x1 + iOffset, 
                    oClipRect.y1 + oClipRect.Height() - 3, oText.c_str());

// TODO: Underline...

    gdk_flush();
    gdk_gc_unref(gc);
    gdk_threads_leave();

    return;
}

string GTKFont::BuildFontString(bool bBold, bool bItalic, int iFontHeight)
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
    gdk_threads_enter();
    if (type == kFontTypeGdk)
        if (gfont)
            gdk_font_unref(gfont);
    gdk_threads_leave();
}
