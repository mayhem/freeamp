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

   $Id: Theme.cpp,v 1.1.2.20 1999/10/06 03:07:15 hiro Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <map>
#include <assert.h>
#include "Theme.h"
#include "ButtonControl.h"
#include "DialControl.h"
#include "SliderControl.h"
#include "TextControl.h"
#include "MultiStateControl.h"
#include "debug.h"
#include "config.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

#ifdef WIN32
#include "Win32Window.h"
#include "Win32Bitmap.h"
#include "Win32Font.h"
#elif defined(HAVE_GTK)
#include "GTKWindow.h"
#include "GTKBitmap.h"
#include "GTKFont.h"
#elif defined(__BEOS__)
#include "BeOSWindow.h"
#include "BeOSBitmap.h"
#include "BeOSFont.h"
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
    m_pParsedFonts = m_pFonts = NULL;
	m_bReloadTheme = false;
    m_bReloadWindow = false;
    m_oReloadWindow = string("");
    m_eCurrentControl = eUndefinedControl;
}

Theme::~Theme(void)
{
	delete m_pCurrentWindow;
	delete m_pCurrentControl;
    
	ClearWindows();
    ClearBitmaps();
    ClearFonts();
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

void Theme::ClearFonts(void)
{  
  	if (m_pFonts)
    {
       while(m_pFonts->size() > 0)
       {
          delete (*m_pFonts)[0];
          m_pFonts->erase(m_pFonts->begin());
       }
       delete m_pFonts;
       m_pFonts = NULL;
    }
}

void Theme::SetThemePath(string &oThemePath)
{
	m_oThemePath = oThemePath + string(DIR_MARKER_STR);
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
       delete m_pParsedFonts;
       m_pParsedWindows = NULL;
       m_pParsedBitmaps = NULL;
       m_pParsedFonts = NULL;
       
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
       m_pFonts = m_pParsedFonts;
       m_pParsedWindows = NULL;
       m_pParsedBitmaps = NULL;
       m_pParsedFonts = NULL;
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
           
        if (m_oReloadWindow.size() > 0 && m_oReloadWindow == string(""))   
            m_pWindow->GetName(m_oReloadWindow);   

	InitWindow();

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
            m_pFonts = m_pParsedFonts;
            m_pParsedWindows = NULL;
            m_pParsedBitmaps = NULL;
            m_pParsedFonts = NULL;
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
       Color   oColor;

#ifdef WIN32
       pBitmap = new Win32Bitmap(oAttrMap["Name"]);
#elif defined(HAVE_GTK)
       pBitmap = new GTKBitmap(oAttrMap["Name"]);
#elif defined(__BEOS__)
       pBitmap = new BeOSBitmap(oAttrMap["Name"]);
#endif

	   if (oAttrMap.find("TransColor") != oAttrMap.end())
       {
           eRet = ParseColor(oAttrMap["TransColor"], oColor);
           if (eRet == kError_NoErr)
               pBitmap->SetTransColor(oColor);
       }

           
	   if (oAttrMap.find("File") == oAttrMap.end())
       {
           m_oLastError = string("the <Bitmap> tag needs a File attribute");
           return kError_ParseError;
       }        

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

       return kError_NoErr;
    }
    if (oElement == string("Font"))
    {
       Font *pFont;

	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <Font> tag needs a Name attribute");
           return kError_ParseError;
       }        
	   if (oAttrMap.find("Face") == oAttrMap.end())
       {
           m_oLastError = string("the <Font> tag needs a Face attribute");
           return kError_ParseError;
       }        

#ifdef WIN32
       pFont = new Win32Font(oAttrMap["Name"], oAttrMap["Face"], m_oDefaultFont);
#elif defined (HAVE_GTK)
       pFont = new GTKFont(oAttrMap["Name"], oAttrMap["Face"], m_oDefaultFont);
#elif defined (__BEOS__)
       pFont = new BeOSFont(oAttrMap["Name"], oAttrMap["Face"], m_oDefaultFont);
#endif
       if (!m_pParsedFonts)
           m_pParsedFonts = new vector<Font *>;
           
       m_pParsedFonts->push_back(pFont);

       return kError_NoErr;
    }
    if (oElement == string("Window"))
    {
       if (m_pCurrentWindow)
       {
           m_oLastError = string("<Window> tags cannot be nested");
           return kError_InvalidParam;
       }
	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <Window> tag needs a Name attribute");
           return kError_ParseError;
       }        

#ifdef WIN32
       m_pCurrentWindow = new Win32Window(this, oAttrMap["Name"]);
#elif defined(HAVE_GTK)
       m_pCurrentWindow = new GTKWindow(this, oAttrMap["Name"]);
#elif defined(__BEOS__)
       m_pCurrentWindow = new BeOSWindow(this, oAttrMap["Name"]);
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

	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <BackgroundBitmap> tag needs a Name attribute");
           return kError_ParseError;
       }        

       pBitmap = FindBitmap(oAttrMap["Name"]);
       if (pBitmap == NULL)
       {
           m_oLastError = string("Undefined bitmap ") + 
                          oAttrMap["Name"] + 
                          string("in tag <BackgroundBitmap>");
           return kError_InvalidParam;
       }

	   if (oAttrMap.find("Rect") == oAttrMap.end())
       {
           m_oLastError = string("the <BackgroundBitmap> tag needs a Rect attribute");
           return kError_ParseError;
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

	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <ButtonControl> tag needs a Name attribute");
           return kError_ParseError;
       }        

       m_eCurrentControl = eButtonControl;
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

	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <DialControl> tag needs a Name attribute");
           return kError_ParseError;
       }        

       m_eCurrentControl = eDialControl;
       m_pCurrentControl = new DialControl(m_pCurrentWindow, 
                                           oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("MultiStateControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested");
           return kError_InvalidParam;
       }

	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <MultiStateControl> tag needs a Name attribute");
           return kError_ParseError;
       }        
	   if (oAttrMap.find("NumStates") == oAttrMap.end())
       {
           m_oLastError = string("the <MultiStateControl> tag needs a NumStates attribute");
           return kError_ParseError;
       }        

       m_eCurrentControl = eMultiStateControl;
       m_pCurrentControl = new MultiStateControl(m_pCurrentWindow, 
                                                 oAttrMap["Name"],
                                                 atoi(oAttrMap["NumStates"].
                                                 c_str()));
       return kError_NoErr;
    }

    if (oElement == string("SliderControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested");
           return kError_InvalidParam;
       }
	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <SliderControl> tag needs a Name attribute");
           return kError_ParseError;
       }        

       m_eCurrentControl = eSliderControl;
       m_pCurrentControl = new SliderControl(m_pCurrentWindow,
                                             oAttrMap["Name"]);
       return kError_NoErr;
    }

    if (oElement == string("TextControl"))
    {
       if (m_pCurrentControl)
       {
           m_oLastError = string("Controls cannot be nested");
           return kError_InvalidParam;
       }
	   if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <TextControl> tag needs a Name attribute");
           return kError_ParseError;
       }        

       m_eCurrentControl = eTextControl;
       m_pCurrentControl = new TextControl(m_pCurrentWindow,
                                           oAttrMap["Name"]);
                                               
       return kError_NoErr;
    }

    if (oElement == string("Style"))
    {
       Color  oColor(0, 0, 0);
       Font  *pFont;
       bool   bBold = false, bItalic = false, bUnderline = false;
       string oAlign("");
       
       if (m_pCurrentControl == NULL || m_eCurrentControl != eTextControl)
       {
           m_oLastError = string("The <Style> tag must be inside of a "
                                 "<TextControl> tag");
           return kError_InvalidParam;
       }

	   if (oAttrMap.find("Font") == oAttrMap.end())
       {
           m_oLastError = string("the <Style> tag needs a Font attribute");
           return kError_ParseError;
       }        

       pFont = FindFont(oAttrMap["Font"]);
       if (pFont == NULL)
       {
           m_oLastError = string("Undefined font ") + 
                          oAttrMap["Name"] + 
                          string("in tag <Style>");
           return kError_InvalidParam;
       }
       
	   if (oAttrMap.find("Color") != oAttrMap.end() && 
           oAttrMap["Color"] != string(""))
       {
           eRet = ParseColor(oAttrMap["Color"], oColor);
           if (eRet != kError_NoErr)
    	   {
    	       m_oLastError = string("Improperly formatted color info: ") +
    	                      oAttrMap["Color"];
    	       return kError_InvalidParam;
    	   }
       }

       if (oAttrMap.find("Bold") != oAttrMap.end())
       	  bBold = strcasecmp(oAttrMap["Bold"].c_str(), "yes") == 0;
       if (oAttrMap.find("Italic") != oAttrMap.end())
       	  bItalic = strcasecmp(oAttrMap["Italic"].c_str(), "yes") == 0;
       if (oAttrMap.find("Underline") != oAttrMap.end())
       	  bUnderline = strcasecmp(oAttrMap["Underline"].c_str(), "yes") == 0;

       if (oAttrMap.find("Align") != oAttrMap.end()) 
          oAlign = oAttrMap["Align"]; 

       ((TextControl *)m_pCurrentControl)->SetStyle(pFont, oAlign,
               oColor, bBold, bItalic, bUnderline);
       
       return kError_NoErr;
	}

    if (oElement == string("ChangeWindow"))
    {
       if (m_pCurrentControl == NULL || m_eCurrentControl != eButtonControl)
       {
           m_oLastError = string("The <Style> tag must be inside of a "
                                 "<ButtonControl> tag");
           return kError_InvalidParam;
       }

       if (oAttrMap.find("Window") == oAttrMap.end())
       {
           m_oLastError = string("the <ChangeWindow> tag needs a Window attribute");
           return kError_ParseError;
       }        

       ((ButtonControl *)m_pCurrentControl)->SetTargetWindow(oAttrMap["Window"]);
       
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

       if (oAttrMap.find("Rect") == oAttrMap.end())
       {
           m_oLastError = string("the <Position> tag needs a Rect attribute");
           return kError_ParseError;
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

       if (oAttrMap.find("Rect") == oAttrMap.end())
       {
           m_oLastError = string("the <ControlBitmap> tag needs a Rect attribute");
           return kError_ParseError;
       }        
       if (oAttrMap.find("Name") == oAttrMap.end())
       {
           m_oLastError = string("the <ControlBitmap> tag needs a Name attribute");
           return kError_ParseError;
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

    if (oElement == string("Info"))
    {
       if (m_pCurrentControl == NULL)
       {
          m_oLastError = string("The <Info> tag must be inside of a "
                                "<XXXXControl> tag");
          return kError_InvalidParam;
       }

	   if (oAttrMap.find("Desc") != oAttrMap.end())
           m_pCurrentControl->SetDesc(oAttrMap["Desc"]);
	   if (oAttrMap.find("Tip") != oAttrMap.end())
           m_pCurrentControl->SetTip(oAttrMap["Tip"]);
       
       return kError_NoErr;
    }

    m_oLastError = string("Invalid tag: ") + oElement;

    return kError_InvalidParam;
}

Error Theme::EndElement(string &oElement)
{
    if (oElement == string("Bitmap") ||
        oElement == string("BackgroundBitmap") ||
        oElement == string("Font") ||
        oElement == string("ChangeWindow") ||
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
        oElement == string("Style") ||
        oElement == string("Info") ||
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
        oElement == string("MultiStateControl") ||
        oElement == string("TextControl")) 
    {
       m_pCurrentWindow->AddControl(m_pCurrentControl);
       m_pCurrentControl = NULL;
       m_eCurrentControl = eUndefinedControl;

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

Error Theme::PCData(string &oData)
{
    m_oLastError = string("Invalid character data: ") + oData;
    
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

Font *Theme::FindFont(string &oName)
{
    vector<Font *>::iterator i;
    string                   oTemp;

	if (!m_pParsedFonts)
		return NULL;
        
    for(i = m_pParsedFonts->begin(); i != m_pParsedFonts->end(); i++)
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

Error Theme::ParsePos(string &oPosstring, Pos &oPos)
{
    int iRet;

    iRet = sscanf(oPosstring.c_str(), " %d , %d",
    		&oPos.x, &oPos.y);

    return (iRet == 2) ? kError_NoErr : kError_InvalidParam;
}

void Theme::SetDefaultFont(const string &oFont)
{ 
	m_oDefaultFont = oFont;
}
