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

   $Id: Win32Font.cpp,v 1.2 1999/10/19 07:13:26 elrod Exp $
____________________________________________________________________________*/ 

#include "Win32Font.h"
#include "debug.h"

int CALLBACK IHateMicrosoft(ENUMLOGFONTEX *lpelfe,   
                            NEWTEXTMETRICEX *lpntme, 
                            int FontType,            
                            LPARAM lParam)
{
   Win32Font *pFont = (Win32Font *)lParam;
   
   return pFont->Callback((unsigned char *)lpelfe->elfFullName);
}                               

Win32Font::Win32Font(string &oName, string &oFace, string &oDefault) :
                Font(oName, oFace, oDefault)
{
   HDC     hRootDC, hMemDC;
   LOGFONT sFont;
   char   *szDup, *szToken;
   
   hRootDC = GetDC(NULL);
   hMemDC = CreateCompatibleDC(hRootDC);
   ReleaseDC(NULL, hRootDC);

   sFont.lfCharSet = DEFAULT_CHARSET;
   sFont.lfPitchAndFamily = 0;

   szDup = strdup(m_oFace.c_str());
   szToken = strtok(szDup, ",");
   for(m_bFound = false;;)
   {
       strcpy(sFont.lfFaceName, szToken);
       EnumFontFamiliesEx(hMemDC, &sFont, (FONTENUMPROC)IHateMicrosoft, (LPARAM)this, 0);
       if (m_bFound)
          break;
          
       szToken = strtok(NULL, ",");
       if (szToken == NULL)
          break;
   }

   if (m_bFound)
       m_oFace = szToken;
   else
   	   m_oFace = m_oDefault;
       
   free(szDup);
   
   DeleteDC(hMemDC);
}

Win32Font::~Win32Font(void)
{

}

Win32Font::Callback(unsigned char *szFontFace)
{
   m_bFound = true;
   return 0;
}

