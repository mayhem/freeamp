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

   $Id: Theme.h,v 1.2 1999/10/19 07:13:16 elrod Exp $
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

#include "facontext.h"
#include "Parse.h"
#include "Window.h"
#include "Bitmap.h"
#include "Font.h"
#include "ThemeManager.h"

typedef map<string, string, less<string> > AttrMap;

enum ControlTypeEnum
{
    eButtonControl,
    eTextControl,
    eSliderControl,
    eDialControl,
    eMultiStateControl,
    
    eUndefinedControl
};

class Theme : public Parse
{
    public:

               Theme(FAContext *context);
      virtual ~Theme(void);

      virtual Error SwitchWindow(const string &oWindowName); 
      virtual Error Run(Pos &oWindowPos); 
      virtual Error Close(void);
      virtual Error LoadTheme(string &oFile, string &oWindowName);
      virtual Error HandleControlMessage(string &oControlName, 
                                         ControlMessageEnum eMesg) = 0;
      virtual void  HandleKeystroke(unsigned char cKey) = 0;
      virtual void  InitControls(void) = 0;
      virtual void  InitWindow(void) = 0;
      virtual void  SetDefaultFont(const string &oFont);

    protected:
     
      virtual void  SetThemePath(string &oPath);
      virtual Error BeginElement(string &oElement, AttrMap &oAttrMap);  
      virtual Error PCData(string &oData);
      virtual Error EndElement(string &oElement);
      ThemeManager *m_pThemeMan;
      string        m_oThemePath;
      Window       *m_pWindow;
      FAContext    *m_pContext;
      

    private:

      Bitmap *FindBitmap(string &oName);
      Font   *FindFont(string &oName);
      Error   ParseRect(string &oRectString, Rect &oRect);
      Error   ParseColor(string &oColorString, Color &oColor);
      Error   ParsePos(string &oPosString, Pos &oPos);
      void    ClearWindows(void);
      void    ClearBitmaps(void);
      void    ClearFonts(void);

      Window          *m_pCurrentWindow;
      Control         *m_pCurrentControl;

      vector<Window *> *m_pWindows, *m_pParsedWindows;
      vector<Bitmap *> *m_pBitmaps, *m_pParsedBitmaps;
      vector<Font *>   *m_pFonts, *m_pParsedFonts;
      bool              m_bReloadTheme, m_bReloadWindow;
      string            m_oReloadWindow, m_oReloadFile;
      ControlTypeEnum   m_eCurrentControl;
      string            m_oDefaultFont;
};

#endif
