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

   $Id: ThemeManager.cpp,v 1.1.2.1 1999/10/05 19:08:23 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif
#include "ThemeManager.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

ThemeManager::ThemeManager(void)
{
	m_oCurrentTheme = "Larry";
}

ThemeManager::~ThemeManager(void)
{
}

Error ThemeManager::GetThemeList(vector<string *> &oThemeFileList)
{
	oThemeFileList.push_back(new string("Larry"));
	oThemeFileList.push_back(new string("Curly"));
	oThemeFileList.push_back(new string("Moe"));
    
	return kError_NoErr;
}

Error ThemeManager::UseTheme(string &oThemeFile)
{
	m_oCurrentTheme = oThemeFile;
	return kError_NoErr;
}

Error ThemeManager::AddTheme(string &oThemeFile)
{
	return kError_NoErr;
}

Error ThemeManager::DeleteTheme(string &oThemeFile)
{
	return kError_NoErr;
}

Error ThemeManager::GetCurrentTheme(string &oTheme)
{
	oTheme = m_oCurrentTheme;
	return kError_NoErr;
}

    

