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

   $Id: Theme.h,v 1.1.2.5 1999/09/17 20:30:52 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_THEME_H__
#define INCLUDED_THEME_H__

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Parse.h"
#include "Window.h"
#include "Bitmap.h"

typedef map<string, string, less<string> > AttrMap;

class Theme : public Parse
{
    public:

               Theme(void);
      virtual ~Theme(void);

      virtual Error SelectWindow(string &oWindowName); 
      virtual Error Run(Pos &oWindowPos); 
      virtual Error Close(string &oWindowName);
      virtual void  SetThemePath(string &oPath);
      virtual Error ParseFile(string &oFile);
      virtual Error HandleControlMessage(string &oControlName, 
                                         ControlMessageEnum eMesg) = 0;
      

    protected:
     
      virtual Error BeginElement(string &oElement, AttrMap &oAttrMap);  
      virtual Error EndElement(string &oElement);
      string        m_oThemePath;
      Window       *m_pWindow;
      

    private:

      Bitmap *FindBitmap(string &oName);
      Error   ParseRect(string &oRectString, Rect &oRect);

      Window          *m_pCurrentWindow;
      Control         *m_pCurrentControl;

      vector<Window *> m_oWindows;
      vector<Bitmap *> m_oBitmaps;
};

#endif
