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

   $Id: Theme.cpp,v 1.1.2.4 1999/09/17 20:31:02 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "map"
#include "assert.h"
#include "Theme.h"
#include "ButtonControl.h"
#include "DialControl.h"
#include "SliderControl.h"
#include "TextControl.h"

#ifdef WIN32
#include "Win32Window.h"
#include "Win32Bitmap.h"
#else
#include "GTKWindow.h"
#include "GTKBitmap.h"
#endif

const int iThemeVersionMajor = 1;
const int iThemeVersionMinor = 0;

Theme::Theme(void)
{
    m_pWindow = NULL;
    m_pCurrentWindow = NULL;
    m_pCurrentControl = NULL;
}

Theme::~Theme(void)
{
    while(m_oWindows.size() > 0)
    {
       delete m_oWindows[0];
       m_oWindows.erase(m_oWindows.begin());
    }
    while(m_oBitmaps.size() > 0)
    {
       delete m_oBitmaps[0];
       m_oBitmaps.erase(m_oBitmaps.begin());
    }
}

void Theme::SetThemePath(string &oThemePath)
{
#ifdef WIN32
	m_oThemePath = oThemePath + string("\\");
#else    
	m_oThemePath = oThemePath + string("/");
#endif
}

Error Theme::ParseFile(string &oFile)
{
    string oCompleteFile;
    
    oCompleteFile = m_oThemePath + oFile;
    return Parse::ParseFile(oCompleteFile);
}

Error Theme::BeginElement(string &oElement, AttrMap &oAttrMap)
{
    Error  eRet;
    string oCompleteFile;

    if (oElement == string("Version"))
    {
       int iRet, iVersionMajor, iVersionMinor;

       iRet = sscanf(oAttrMap["Version"].c_str(), " %d.%d", &iVersionMajor,
                                                    &iVersionMinor);
       if (iRet != 2)
       {
           m_oLastError = string("Improperly formatted version number "
                                 "in the <Version> tag.");
           return kError_ParseError;
       }

       if (iVersionMajor != iThemeVersionMajor ||
           iVersionMinor != iThemeVersionMinor)
       {
           char szError[512];

           
           sprintf(szError, "This ThemeManager cannot use version %d.%d "
                            "themes.", iVersionMajor, iVersionMinor);
           m_oLastError = string(szError);

           return kError_ParseError;
       }

       return eRet;
    }

    if (oElement == string("Bitmap"))
    {
       Bitmap *pBitmap;

#ifndef WIN32
       pBitmap = new GTKBitmap(oAttrMap["Name"]);
#else
       pBitmap = new Win32Bitmap(oAttrMap["Name"]);
#endif

       oCompleteFile = m_oThemePath + oAttrMap["File"];
       eRet = pBitmap->LoadBitmapFromDisk(oCompleteFile);
       if (eRet != kError_NoErr)
       {
           string oBitmapErr;

           pBitmap->GetErrorString(oBitmapErr);
           m_oLastError = string("Cannot load bitmap ") +
                          oAttrMap["File"] + string(": ") + oBitmapErr;
           return eRet;
       }
       m_oBitmaps.push_back(pBitmap);

       return eRet;
    }
    if (oElement == string("Window"))
    {
       if (m_pCurrentWindow)
       {
           m_oLastError = string("<Window> tags cannot be nested.");
           return kError_InvalidParam;
       }

#ifndef WIN32
       m_pCurrentWindow = new GTKWindow(this, oAttrMap["Name"]);
#else
       m_pCurrentWindow = new Win32Window(this, oAttrMap["Name"]);
#endif

       return kError_NoErr;
    }
    if (oElement == string("BackgroundBitmap"))
    {
       Canvas *pCanvas;
       Bitmap *pBitmap;
       Rect    oRect;

       if (m_pCurrentWindow == NULL)
       {
           m_oLastError = string("<BackgroundBitmap> must occur inside "
                                 "of a <Window> tag.");
           return kError_InvalidParam;
       }

       pBitmap = FindBitmap(oAttrMap["Name"]);
       if (pBitmap == NULL)
       {
           m_oLastError = string("Undefined bitmap ") + 
                          oAttrMap["Name"] + 
                          string("in tag <BackgroundBitmap>");
           return kError_InvalidParam;
       }

       eRet = ParseRect(oAttrMap["Rect"], oRect);
       if (eRet != kError_NoErr)
       {
           m_oLastError = string("Improperly formatted rect coordinates: ") +
                          oAttrMap["Rect"];
           return kError_InvalidParam;
       }
       pCanvas = m_pCurrentWindow->GetCanvas();
       pCanvas->SetBackgroundBitmap(pBitmap);
       pCanvas->SetBackgroundRect(oRect);

       return kError_NoErr;
    }
    if (oElement == string("MaskBitmap"))
    {
       Canvas *pCanvas;
       Bitmap *pBitmap;
       Rect    oRect;

       if (m_pCurrentWindow == NULL)
       {
           m_oLastError = string("<MaskBitmap> must occur inside "
                                 "of a <Window> tag.");
           return kError_InvalidParam;
       }

       pBitmap = FindBitmap(oAttrMap["Name"]);
       if (pBitmap == NULL)
       {
           m_oLastError = string("Undefined bitmap ") + 
                          oAttrMap["Name"] + 
                          string("in tag <MaskBitmap>");
           return kError_InvalidParam;
       }

       pCanvas = m_pCurrentWindow->GetCanvas();
       pCanvas->SetMaskBitmap(pBitmap);

       return kError_NoErr;
    }
    if (oElement == string("Controls"))
    {
       if (m_pCurrentWindow == NULL)
       {
           m_oLastError = string("<Controls> must occur inside of a "
                          "<Window> tag.");
           return kError_InvalidParam;
       }

       return kError_NoErr;
    }

    if (oElement == string("ButtonControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested.");
           return kError_InvalidParam;
       }

       m_pCurrentControl = new ButtonControl(m_pCurrentWindow, 
                                             oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("DialControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested.");
           return kError_InvalidParam;
       }

       m_pCurrentControl = new DialControl(m_pCurrentWindow, 
                                           oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("SliderControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested.");
           return kError_InvalidParam;
       }

       m_pCurrentControl = new SliderControl(m_pCurrentWindow,
                                             oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("TextControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested.");
           return kError_InvalidParam;
       }

       m_pCurrentControl = new TextControl(m_pCurrentWindow,
                                           oAttrMap["Name"],
                                           oAttrMap["Align"]);
       return kError_NoErr;
    }

    if (oElement == string("Position"))
    {
       Rect oRect;

       if (m_pCurrentControl == NULL)
       {
          m_oLastError = string("The <Position> tag must be inside of a "
                                "<XXXXControl> tag.");
          return kError_InvalidParam;
       }

       eRet = ParseRect(oAttrMap["Rect"], oRect);
       if (eRet != kError_NoErr)
       {
          m_oLastError = string("Improperly formatted Rect coordinates: ") +
                         oAttrMap["Rect"];
          return kError_InvalidParam;
       }

       m_pCurrentControl->SetRect(oRect);
       return kError_NoErr;
    }

    if (oElement == string("ControlBitmap"))
    {
       Bitmap *pBitmap = NULL;
       Rect oRect;

       if (m_pCurrentControl == NULL)
       {
          m_oLastError = string("The <ControlBitmap> tag must be inside of a "
                                "<XXXXControl> tag.");
          return kError_InvalidParam;
       }

       eRet = ParseRect(oAttrMap["Rect"], oRect);
       if (eRet != kError_NoErr)
       {
           m_oLastError = string("Improperly formatted Rect coordinates: ") +
                                 oAttrMap["Rect"];
           return kError_InvalidParam;
       }

       pBitmap = FindBitmap(oAttrMap["Name"]);
       if (pBitmap == NULL)
       {
           m_oLastError = string("Undefined bitmap ") +
                          oAttrMap["Name"] +
                          string(" in tag <BackgroundBitmap>");
           return kError_InvalidParam;
       }

       m_pCurrentControl->SetBitmap(pBitmap, oRect);
       return kError_NoErr;
    }

    m_oLastError = string("Invalid tag: ") + oElement;

    return kError_InvalidParam;
}

Error Theme::EndElement(string &oElement)
{
    if (oElement == string("Bitmap") ||
        oElement == string("BackgroundBitmap") ||
        oElement == string("MaskBitmap"))
       return kError_NoErr;

    if (oElement == string("Controls"))
    {
       if (m_pCurrentWindow == NULL)
       {
           m_oLastError = string("The <Controls> tag must be inside a "
                                 "<Window> tag.");
           return kError_InvalidParam;
       }
       return kError_NoErr;
    }

    if (oElement == string("Action") ||
        oElement == string("Position") ||
        oElement == string("ControlBitmap"))
    {
       if (m_pCurrentControl == NULL)
       {
           m_oLastError = string("The <") + 
                          oElement.c_str()+ 
                          string("> tag must be inside a <XXXXControl>");
           return kError_InvalidParam;
       }
       return kError_NoErr;
    }

    if (oElement == string("ButtonControl") ||
        oElement == string("DialControl") ||
        oElement == string("SliderControl") ||
        oElement == string("TextControl"))
    {
       m_pCurrentWindow->AddControl(m_pCurrentControl);
       m_pCurrentControl = NULL;

       return kError_NoErr;
    }

    if (oElement == string("Window"))
    {
       m_oWindows.push_back(m_pCurrentWindow);
       m_pCurrentWindow = NULL;

       return kError_NoErr;
    }

    m_oLastError = string("Invalid close tag: ") + oElement;

    return kError_InvalidParam;
}    

Bitmap *Theme::FindBitmap(string &oName)
{
    vector<Bitmap *>::iterator i;
    string                     oTemp;

    for(i = m_oBitmaps.begin(); i != m_oBitmaps.end(); i++)
    {
       (*i)->GetName(oTemp);
       if (oTemp == oName)
          return *i;
    }

    return NULL;
}

Error Theme::ParseRect(string &oRectstring, Rect &oRect)
{
    int iRet;

    iRet = sscanf(oRectstring.c_str(), " %d , %d , %d , %d",
             &oRect.x1, &oRect.y1, &oRect.x2, &oRect.y2);

    return (iRet == 4) ? kError_NoErr : kError_InvalidParam;
}

Error Theme::SelectWindow(string &oWindowName)
{
    vector<Window *>::iterator i;
    string                     oTemp;

    for(i = m_oWindows.begin(); i != m_oWindows.end(); i++)
    {
        (*i)->GetName(oTemp);
        if (oTemp == oWindowName)
        {
            m_pWindow = *i;
            return kError_NoErr;
        }    
    }

    return kError_NotFound;
}

Error Theme::Run(Pos &oWindowPos)
{
    return m_pWindow->Run(oWindowPos);
}

Error Theme::Close(string &oWindowName)
{
    vector<Window *>::iterator i;
    string                     oTemp;

    for(i = m_oWindows.begin(); i != m_oWindows.end(); i++)
    {
        (*i)->GetName(oTemp);
        if (oTemp == oWindowName)
            return (*i)->Close();
    }

    return kError_NotFound;
}
