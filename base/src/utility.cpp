/*____________________________________________________________________________
	
	FreeAMP - The Free MP3 Player
	Portions copyright (C) 1998 GoodNoise

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
	
	$Id: utility.cpp,v 1.1 1998/10/15 21:40:38 jdw Exp $
____________________________________________________________________________*/

/* System Includes */
#define STRICT
#ifdef WIN32
#include <windows.h>
#include <commctrl.h>
#else 
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>
#include <iostream.h>

/* Project Includes */
#include "utility.h"
#include "error.h"

#define MAIN_KEY    HKEY_CURRENT_USER
#define SUB_KEY     "SOFTWARE\\FreeAmp\\FreeAmp v1.0"
#define INSTALL     "InstallDirectory"
#define UI          "UI"
#define DEFAULT_UI  "freeamp"

Error InitWindowsRegistry()
{
#ifdef WIN32

    Error   error = kError_UnknownErr;
    HKEY    hkey;
	DWORD   type;
	DWORD   size;
	LONG    result;
    char    temp[MAX_PATH] = {0x00};
    char    cwd[MAX_PATH]= {0x00};

    GetCurrentDirectory(sizeof(cwd), cwd);

	result = RegOpenKeyEx(	MAIN_KEY,
							SUB_KEY,
							0, 
							KEY_ALL_ACCESS,
							&hkey);

	if(result == ERROR_SUCCESS)
	{
		result = RegQueryValueEx(   hkey,
                                    INSTALL, 
                                    NULL, 
                                    &type, 
                                    (LPBYTE)temp, 
                                    &size);

        if(strcmp(cwd, temp))
        {
            result = RegSetValueEx( hkey,
                                    INSTALL, 
                                    NULL, 
                                    REG_SZ, 
                                    (LPBYTE)cwd, 
                                    strlen(cwd) + 1);
        }
        
        error = kError_NoErr;
        RegCloseKey(hkey);
    }
    else // keys need to be created for the first time
    {
        DWORD disposition;

        result = RegCreateKeyEx(MAIN_KEY,
                                SUB_KEY,
                                NULL, 
                                "",
                                REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS,
                                NULL,
                                &hkey,
                                &disposition);

        if(result == ERROR_SUCCESS)
        {
            result = RegSetValueEx( hkey,
                                    INSTALL, 
                                    NULL, 
                                    REG_SZ, 
                                    (LPBYTE)cwd, 
                                    strlen(cwd) + 1);

            result = RegSetValueEx( hkey,
                                    UI, 
                                    NULL, 
                                    REG_SZ, 
                                    (LPBYTE)DEFAULT_UI, 
                                    strlen(DEFAULT_UI) + 1);

            error = kError_NoErr;
            RegCloseKey(hkey);
        }
    }

    return error;
#else // WIN32

    return kError_NoErr;

#endif // WIN32
}



Error GetInstallDirectory(char* path, int32 len)
{
#ifdef WIN32
    Error   error = kError_UnknownErr;
    HKEY    hkey;
	DWORD   type;
	DWORD   size;
	LONG    result;
	char    temp[MAX_PATH];

	size = sizeof(temp);

    if(path)
        *path = 0x00;

	result = RegOpenKeyEx(	MAIN_KEY,
							SUB_KEY,
							0, 
							KEY_ALL_ACCESS,
							&hkey);

	if(result == ERROR_SUCCESS)
	{
		result = RegQueryValueEx(   hkey,
                                    INSTALL, 
                                    NULL, 
                                    &type, 
                                    (LPBYTE)temp, 
                                    &size);

                    
        if(result == ERROR_SUCCESS)
	    {
		    strcpy(path,temp);

            error = kError_NoErr;
	    }

        RegCloseKey(hkey);
    }
  
    return error;
#else // WIN32

    if (path) {
	getcwd(path,len);
	return kError_NoErr;
    }
    return kError_UnknownErr;

#endif
}












