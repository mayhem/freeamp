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
	
	$Id: win32updatemanager.cpp,v 1.1.2.2 1999/10/11 06:22:27 elrod Exp $
____________________________________________________________________________*/

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif


#include <assert.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <errno.h>
#include <iostream>
#include <algorithm>
#include <sstream>


using namespace std;

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "win32updatemanager.h"
#include "utility.h"
#include "event.h"
#include "eventdata.h"
#include "zlib.h"


Win32UpdateManager::Win32UpdateManager(FAContext* context):
UpdateManager(context)
{
    m_context = context;
}

Win32UpdateManager::~Win32UpdateManager()
{
  
}

Error Win32UpdateManager::DetermineLocalVersions()
{
    Error result = kError_AlreadyUpdating;

    if(m_mutex.Acquire(0))
    {
        char appPath[MAX_PATH];
        uint32 length = sizeof(appPath);
        m_context->prefs->GetPrefString(kInstallDirPref, appPath, &length);

        // paths i need to ignore
        length = sizeof(m_musicPath);
        m_context->prefs->GetPrefString(kSaveMusicDirPref, m_musicPath, &length);
   
        strcpy(m_updatePath, appPath);
        strcat(m_updatePath, "\\update");

        // Analyze all these files
        result = GetFileVersions(appPath);

        m_mutex.Release();
    }

    return result;
}

Error Win32UpdateManager::GetFileVersions(const char* path)
{
    Error result = kError_NoErr;
    
    HANDLE findFileHandle = NULL;
    WIN32_FIND_DATA findData;  
    char filePath[MAX_PATH];
    char* fp;

    strcpy(filePath, path);
    strcat(filePath, "\\*.*");
    fp = strrchr(filePath, '\\') + 1;
    
    findFileHandle = FindFirstFile(filePath, &findData);

    cout << "searching in "<< path << ":" << endl;

    if(findFileHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            strcpy(fp, findData.cFileName);

            // skip these two special entries && music dir
            if( strcmp(findData.cFileName, ".") && 
                strcmp(findData.cFileName, "..") &&
                strcmp(filePath, m_updatePath) &&
                strcmp(filePath, m_musicPath))
            {
                if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
                {
                    // call ourselves on that directory
                    GetFileVersions(filePath);      
                }
                else 
                {
                    DWORD versionSize;
                    DWORD dummyHandle;
                    void* data;

                    versionSize = GetFileVersionInfoSize(filePath, &dummyHandle);
                    
                    data = malloc(versionSize);

                    // actually get the verionsinfo for the file
                    if(data)
                    {
                        if(GetFileVersionInfo(filePath, dummyHandle, 
                                               versionSize, data))
                        {
                            VS_FIXEDFILEINFO* fileInfo;
                            char* fileDescription;
                            uint32 size;

                            if(VerQueryValue(data, "\\", (void**)&fileInfo, &size))
                            {                                
                                cout << filePath << ":" << endl;
                                //cout << "dwFileVersionLS: " << fileInfo->dwFileVersionLS << endl;
                                //cout << "dwFileVersionMS: " << fileInfo->dwFileVersionMS << endl;
                                //cout << "hi: " << HIWORD(fileInfo->dwFileVersionLS) << " lo: "<< LOWORD(fileInfo->dwFileVersionLS) << endl;
                                //cout << "hi: " << HIWORD(fileInfo->dwFileVersionMS) << " lo: "<< LOWORD(fileInfo->dwFileVersionMS) << endl << endl;

                                uint32 major = HIWORD(fileInfo->dwFileVersionMS);
                                uint32 minor = LOWORD(fileInfo->dwFileVersionMS);
                                uint32 rev = HIWORD(fileInfo->dwFileVersionLS);

                                cout << "version: " << major << "." << minor << "." << rev << endl;
                            }

                            if(VerQueryValue(data, "\\StringFileInfo\\040904B0\\FileDescription", (void**)&fileDescription, &size))
                            {     
                                cout << fileDescription << endl;
                            }

                            cout << endl;
                        }

                        free(data);
                    }
                }
            }

        }while(FindNextFile(findFileHandle, &findData));

        FindClose(findFileHandle);
    }

    return result;
}