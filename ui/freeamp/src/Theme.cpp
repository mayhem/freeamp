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

   $Id: Theme.cpp,v 1.1.2.5 1999/09/23 01:30:03 robert Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "map"
#include "assert.h"
#include "Theme.h"
#include "ButtonControl.h"
#include "DialControl.h"
#include "SliderControl.h"
#include "TextControl.h"
#include "debug.hpp"

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
    m_pParsedWindows = m_pWindows = NULL;
    m_pParsedBitmaps = m_pBitmaps = NULL;
	m_bReloadTheme = false;
    m_bReloadWindow = false;
}

Theme::~Theme(void)
{
	delete m_pCurrentWindow;
	delete m_pCurrentControl;
    
	ClearWindows();
    ClearBitmaps();
}

void Theme::ClearWindows(void)
{
	if (m_pWindows)
    {
       while(m_pWindows->size() > 0)
       {
          delete (*m_pWindows)[0];
          m_pWindows->erase(m_pWindows->begin());
       }
       delete m_pWindows;
       m_pWindows = NULL;
    }   
}

void Theme::ClearBitmaps(void)
{  
  	if (m_pBitmaps)
    {
       while(m_pBitmaps->size() > 0)
       {
          delete (*m_pBitmaps)[0];
          m_pBitmaps->erase(m_pBitmaps->begin());
       }
       delete m_pBitmaps;
       m_pBitmaps = NULL;
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

Error Theme::LoadTheme(string &oFile)
{
    string oCompleteFile;
    Error  eRet;

	if (m_pWindow)
    {
       oCompleteFile = m_oThemePath + oFile;
       eRet = Parse::ParseFile(oCompleteFile);
       delete m_pParsedWindows;
       delete m_pParsedBitmaps;
       m_pParsedWindows = NULL;
       m_pParsedBitmaps = NULL;
       
       if (IsError(eRet))
          return eRet;

	   m_bReloadTheme = true;
	   Theme::Close();
       m_oReloadFile = oFile;
       
       return kError_NoErr;
    }   
    
    oCompleteFile = m_oThemePath + oFile;
    eRet = Parse::ParseFile(oCompleteFile);
    if (!IsError(eRet))
    {
       m_pWindows = m_pParsedWindows;
       m_pBitmaps = m_pParsedBitmaps;
       m_pParsedWindows = NULL;
       m_pParsedBitmaps = NULL;
    }   
    return eRet;
}

Error Theme::SelectWindow(const string &oWindowName)
{
    vector<Window *>::iterator i;
    string                     oTemp;

	if (!m_pWindows)
        return kError_NotFound;

	if (m_pWindow && !m_bReloadWindow)
    {
	   m_bReloadWindow = true;
	   Theme::Close();
       m_oReloadWindow = oWindowName;
       
       return kError_NoErr;
    }   
    
    for(i = m_pWindows->begin(); i != m_pWindows->end(); i++)
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
	string oCurrentWindow;
    string oCompleteFile;
	Error  eRet;
    
    for(;;)
    {
    	if (m_pWindow == NULL)
           return kError_UnknownErr;
           
        if (m_oReloadWindow == string(""))   
            m_pWindow->GetName(m_oReloadWindow);   

    	eRet = m_pWindow->Run(oWindowPos);
        if (IsError(eRet))
            return eRet;
    
    	if (!m_bReloadTheme && !m_bReloadWindow)
           break;
           
        if (m_bReloadTheme)
        {   
            m_bReloadTheme = false;

 	        ClearWindows();
            ClearBitmaps();
            m_pWindow = NULL;

            oCompleteFile = m_oThemePath + m_oReloadFile;
            eRet = Parse::ParseFile(oCompleteFile);
            assert(!IsError(eRet));
        
            m_pWindows = m_pParsedWindows;
            m_pBitmaps = m_pParsedBitmaps;
            m_pParsedWindows = NULL;
            m_pParsedBitmaps = NULL;
        }    
        
        SelectWindow(m_oReloadWindow);
        m_bReloadWindow = false;
    }
}

Error Theme::Close(void)
{
	if (m_pWindow)
       return m_pWindow->Close();
    else
       return kError_NoErr;
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
                                 "in the <Version> tag");
           return kError_ParseError;
       }

       if (iVersionMajor != iThemeVersionMajor ||
           iVersionMinor != iThemeVersionMinor)
       {
           char szError[512];

           
           sprintf(szError, "This ThemeManager cannot use version %d.%d "
                            "themes", iVersionMajor, iVersionMinor);
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
       
       if (!m_pParsedBitmaps)
           m_pParsedBitmaps = new vector<Bitmap *>;
           
       m_pParsedBitmaps->push_back(pBitmap);

       return eRet;
    }
    if (oElement == string("Window"))
    {
       if (m_pCurrentWindow)
       {
           m_oLastError = string("<Window> tags cannot be nested");
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
                                 "of a <Window> tag");
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
                                 "of a <Window> tag");
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
                          "<Window> tag");
           return kError_InvalidParam;
       }

       return kError_NoErr;
    }

    if (oElement == string("ButtonControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested");
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
           m_oLastError = string("Controls cannot be nested");
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
           m_oLastError = string("Controls cannot be nested");
           return kError_InvalidParam;
       }

       m_pCurrentControl = new SliderControl(m_pCurrentWindow,
                                             oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("TextControl"))
    {
       Color oColor;
       
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested");
           return kError_InvalidParam;
       }

	   if (oAttrMap["Color"] != string(""))
       {
           eRet = ParseColor(oAttrMap["Color"], oColor);
           if (eRet != kError_NoErr)
    	   {
    	       m_oLastError = string("Improperly formatted color info: ") +
    	                      oAttrMap["Color"];
    	       return kError_InvalidParam;
    	   }
           m_pCurrentControl = new TextControl(m_pCurrentWindow,
                                               oAttrMap["Name"],
                                               oAttrMap["Align"],
                                               &oColor);
       }
       else
           m_pCurrentControl = new TextControl(m_pCurrentWindow,
                                               oAttrMap["Name"],
                                               oAttrMap["Align"],
                                               NULL);
                                               
       return kError_NoErr;
    }

    if (oElement == string("Position"))
    {
       Rect oRect;

       if (m_pCurrentControl == NULL)
       {
          m_oLastError = string("The <Position> tag must be inside of a "
                                "<XXXXControl> tag");
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
                                "<XXXXControl> tag");
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
                                 "<Window> tag");
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
       if (!m_pParsedWindows)
           m_pParsedWindows = new vector<Window *>;
           
       m_pParsedWindows->push_back(m_pCurrentWindow);
           
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

	if (!m_pParsedBitmaps)
		return NULL;
        
    for(i = m_pParsedBitmaps->begin(); i != m_pParsedBitmaps->end(); i++)
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

Error Theme::ParseColor(string &oColorstring, Color &oColor)
{
    int iRet;

    iRet = sscanf(oColorstring.c_str(), "#%02X%02X%02X",
    		&oColor.red, &oColor.green, &oColor.blue);

    return (iRet == 3) ? kError_NoErr : kError_InvalidParam;
}


