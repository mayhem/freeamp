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
	
	$Id: main.cpp,v 1.1.2.1 1999/10/07 06:52:52 elrod Exp $
____________________________________________________________________________*/

/* System Includes */
#define STRICT
#include <windows.h>
#include <winsock.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

/* Project Includes */
#include "win32prefs.h"
#include "updatemanager.h"

const char* kMessage = "An instance of FreeAmp is currently running. Please "
                       "close the application before continuing the update.";

int APIENTRY WinMain(	HINSTANCE hInstance, 
						HINSTANCE hPrevInstance,
		 				LPSTR lpszCmdLine, 
						int cmdShow)
{
    HANDLE runOnceMutex;

    runOnceMutex = CreateMutex(	NULL,
							    TRUE,
							    "FreeAmp Should Only Run One Time!");

    
    while(WAIT_TIMEOUT == WaitForSingleObject(runOnceMutex, 0))
    {
        int32 result;

        result = MessageBox(NULL, kMessage, "Updating FreeAmp", MB_RETRYCANCEL);

        if(result == IDCANCEL)
        {
            CloseHandle(runOnceMutex);
            return 0;
        }
    }
    


    CloseHandle(runOnceMutex);

	return 0;
}