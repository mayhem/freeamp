/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 GoodNoise

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
	
	$Id: preferences.cpp,v 1.10 1999/03/20 10:33:18 elrod Exp $
____________________________________________________________________________*/

#include <stdio.h>

#include "preferences.h"

// location
const HKEY  kMainKey = HKEY_CURRENT_USER;
const char* kPrefsKey = "SOFTWARE\\FreeAmp\\FreeAmp v1.2";
const char* kFreeAmpKey = "SOFTWARE\\FreeAmp";
const char* kFreeAmpVersionKey = "FreeAmp v1.2";

// preferences
const char* kInstallDirPref = "InstallDirectory";
const char* kUIPref = "UI";
const char* kPMOPref = "PMO";
const char* kOpenSaveDirPref = "OpenSaveDirectory";
const char* kStayOnTopPref = "StayOnTop";

// default values
const char* kDefaultUI = "freeamp.ui";
const char* kDefaultPMO = "soundcard.pmo";
const bool  kDefaultStayOnTop = false;


Preferences::
Preferences()
{
    LONG    result;

    m_prefsKey = NULL;

    result = RegOpenKeyEx(	kMainKey,
							kPrefsKey,
							0, 
							KEY_ALL_ACCESS,
							&m_prefsKey);

    if(result != ERROR_SUCCESS)
    {
        m_prefsKey = NULL;
    }
}

Preferences::
~Preferences()
{
    if(m_prefsKey)
    {
        RegCloseKey(m_prefsKey);
    }
}

Error
Preferences::
Initialize()
{
    LONG    result;
	uint32  length;
    char    path[MAX_PATH] = {0x00};
    char    cwd[MAX_PATH]= {0x00};
    Error   error = kError_UnknownErr;

    // Where are we starting the program from?
    GetCurrentDirectory(sizeof(cwd), cwd);


    if(m_prefsKey)
	{
        // people DO move their apps around on windows
        length = sizeof(path);

        error = GetInstallDirectory(path, &length);

		char foo[MAX_PATH] = {0x00};
		sprintf(foo,"%s\\plugins",cwd);
		WIN32_FIND_DATA win32fd;

        // check for plugins directory in cwd

		/*LEAK*/HANDLE h = FindFirstFile(foo,&win32fd);

		if (h != INVALID_HANDLE_VALUE) 
        {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
            {
				if(IsError(error) || strcmp(cwd, path))
				{
					result = RegSetValueEx( m_prefsKey,
											kInstallDirPref, 
											NULL, 
											REG_SZ, 
											(LPBYTE)cwd, 
											strlen(cwd) + 1);
				}
			}
		}
        error = kError_NoErr;
    }
    else // keys need to be created for the first time
    {
        DWORD disposition;
        HKEY freeampKey;

        // create the main key in the windows registry
        result = RegCreateKeyEx(kMainKey,
                                kFreeAmpKey,
                                NULL, 
                                "",
                                REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS,
                                NULL,
                                &freeampKey,
                                &disposition);

        if(result == ERROR_SUCCESS)
        {
            // create the version key under the freeamp key
            result = RegCreateKeyEx(freeampKey,
                                    kFreeAmpVersionKey,
                                    NULL, 
                                    "",
                                    REG_OPTION_NON_VOLATILE,
                                    KEY_ALL_ACCESS,
                                    NULL,
                                    &m_prefsKey,
                                    &disposition);
        }

        if(result == ERROR_SUCCESS)
        {
            // set install directory value
            SetPrefString(kInstallDirPref, cwd);
            
            // set default ui value
            SetPrefString(kUIPref, kDefaultUI);
            
            // set default pmo value
            SetPrefString(kPMOPref, kDefaultPMO);

            // set default open/save dlg path value
            SetPrefString(kOpenSaveDirPref, cwd);

            // set default for window staying on top
            SetPrefBoolean(kStayOnTopPref, kDefaultStayOnTop);

             error = kError_NoErr;
        }
        else
        {
             error = kError_NoPrefs;
        }

        RegCloseKey(freeampKey);
    }

    return error;
}


Error 
Preferences::
GetInstallDirectory(char* path, uint32* len)
{
    return GetPrefString(kInstallDirPref, path, len);
}


Error 
Preferences::
SetInstallDirectory(char* path)
{
    return SetPrefString(kInstallDirPref, path);
}

Error 
Preferences::
GetDefaultUI(char* name, uint32* len)
{
    return GetPrefString(kUIPref, name, len);
}

Error 
Preferences::
SetDefaultUI(char* name)
{
    return SetPrefString(kUIPref, name);
}

Error 
Preferences::
GetDefaultPMO(char* name, uint32* len)
{
    return GetPrefString(kPMOPref, name, len);
}

Error 
Preferences::
SetDefaultPMO(char* name)
{
    return SetPrefString(kPMOPref, name);
}

Error 
Preferences::
GetOpenSaveDirectory(char* path, uint32* len)
{
    return GetPrefString(kOpenSaveDirPref, path, len);
}

Error 
Preferences::
SetOpenSaveDirectory(char* path)
{
    return SetPrefString(kOpenSaveDirPref, path);
}

Error 
Preferences::
GetStayOnTop(bool* value)
{
    return GetPrefBoolean(kStayOnTopPref, value);
}

Error 
Preferences::
SetStayOnTop(bool value)
{
    return SetPrefBoolean(kStayOnTopPref, value);
}

Error
Preferences::
GetPrefString(const char* pref, char* buf, uint32* len)
{
    Error   error = kError_UnknownErr;
	DWORD   type;
	LONG    result;

    if(!buf || !len || !pref)
    {
        error = kError_InvalidParam;
        return error;
    }

    *buf = 0x00;

	if(m_prefsKey)
	{
		result = RegQueryValueEx(   m_prefsKey,
                                    pref, 
                                    NULL, 
                                    &type, 
                                    (LPBYTE)buf, 
                                    (DWORD*)len);

        if(result == ERROR_SUCCESS)
            error = kError_NoErr;
        else if(result == ERROR_MORE_DATA)
            error = kError_BufferTooSmall;    
	    
    }
    else
    {
        error = kError_NoPrefs;
    }
  
    return error;
}

Error
Preferences::
SetPrefString(const char* pref, const char* buf)
{
    Error   error = kError_UnknownErr;
	LONG    result;

    if(!buf || !pref)
    {
        error = kError_InvalidParam;
        return error;
    }

	if(m_prefsKey)
	{
		// set install directory value
        result = RegSetValueEx( m_prefsKey,
                                pref, 
                                NULL, 
                                REG_SZ, 
                                (LPBYTE)buf, 
                                strlen(buf) + 1);

        if(result == ERROR_SUCCESS)
            error = kError_NoErr;
    }
    else
    {
        error = kError_NoPrefs;
    }
  
    return error;
}

Error 
Preferences::
GetPrefBoolean(const char* pref, bool* value)
{
    Error   error = kError_UnknownErr;
	DWORD   type;
	LONG    result;
    DWORD   buf = 0;
    DWORD   len = sizeof(DWORD);

    if(!value || !pref)
    {
        error = kError_InvalidParam;
        return error;
    }

	if(m_prefsKey)
	{
		result = RegQueryValueEx(   m_prefsKey,
                                    pref, 
                                    NULL, 
                                    &type, 
                                    (LPBYTE)&buf, 
                                    (DWORD*)&len);

        if(result == ERROR_SUCCESS)
        {
            error = kError_NoErr;

            *value = (buf == 0 ? false : true);
        }
        else if(result == ERROR_MORE_DATA)
            error = kError_BufferTooSmall;    
    }
    else
    {
        error = kError_NoPrefs;
    }
  
    return error;
}

Error
Preferences:: 
SetPrefBoolean(const char* pref, bool value)
{
    Error   error = kError_UnknownErr;
	LONG    result;
    DWORD   buf = (value ? 1 : 0);

    if(!pref)
    {
        error = kError_InvalidParam;
        return error;
    }


	if(m_prefsKey)
	{
		// set install directory value
        result = RegSetValueEx( m_prefsKey,
                                pref, 
                                NULL, 
                                REG_DWORD , 
                                (LPBYTE)&buf, 
                                sizeof(DWORD));

        if(result == ERROR_SUCCESS)
            error = kError_NoErr;
    }
    else
    {
        error = kError_NoPrefs;
    }
  
    return error;
}
