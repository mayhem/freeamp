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

   $Id: ThemeManager.cpp,v 1.1.2.1 1999/10/11 22:01:23 ijr Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <netinet/in.h>
#include "ThemeManager.h"
#include "debug.h"
#include "win32impl.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

ThemeManager::ThemeManager(FAContext *pContext)
{
    m_pContext = pContext;
    m_oCurrentTheme = "";
}

ThemeManager::~ThemeManager(void)
{
}

Error ThemeManager::GetDefaultTheme(string &oThemePath)
{
    char              dir[MAX_PATH];
    uint32            len = sizeof(dir);

    m_pContext->prefs->GetInstallDirectory(dir, &len);
    oThemePath = string(dir);
    oThemePath += string("/themes/freeamp.fat");    

    return kError_NoErr;
}

Error ThemeManager::GetThemeList(map<string, string> &oThemeFileMap)
{
    WIN32_FIND_DATA find;
    HANDLE          handle;
    char            dir[MAX_PATH], *ptr;
    uint32          len = sizeof(dir);
    string          oThemePath, oThemeBasePath, oThemeFile;

    m_pContext->prefs->GetInstallDirectory(dir, &len);
    oThemeBasePath = string(dir) + "../freeamp/themes";
    oThemePath = oThemeBasePath + string("/*.fat");    

    handle = FindFirstFile((char *)oThemePath.c_str(), &find);
    if(handle == INVALID_HANDLE_VALUE)
        return kError_NoErr;

    do
    {
	oThemeFile = oThemeBasePath + string("/") + string(find.cFileName);
    	ptr = strrchr(find.cFileName, '.');
        if (ptr)
           *ptr = 0;

        oThemeFileMap[find.cFileName] = oThemeFile;
    }
    while(FindNextFile(handle, &find));

    return kError_NoErr;
}

Error ThemeManager::UseTheme(string &oThemeFile)
{
    char   dir[_MAX_PATH];
    string oThemePath;

    char *temp_dir;
    temp_dir = strrchr(oThemeFile.c_str(), '/');
    if (!temp_dir) {
        temp_dir = temp_dir + 1;
	strcpy(dir, temp_dir);
        if (strcmp(dir, m_oCurrentTheme.c_str()) == 0)
        {
            return kError_NoErr;
        }
    }

    m_pContext->prefs->SetThemePath((char *)oThemeFile.c_str());
    m_oCurrentTheme = string(dir);
    
    return kError_NoErr;
}

Error ThemeManager::AddTheme(string &oThemeFile)
{
    Debug_v("Add theme: %s", oThemeFile.c_str());
    return kError_NoErr;
}

Error ThemeManager::DeleteTheme(string &oThemeFile)
{
    Debug_v("Delete theme: %s", oThemeFile.c_str());
    return kError_NoErr;
}

Error ThemeManager::GetCurrentTheme(string &oTheme)
{
    oTheme = m_oCurrentTheme;
    return kError_NoErr;
}
