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
	
	$Id: utility.cpp,v 1.2.2.8 1999/09/24 00:16:12 elrod Exp $
____________________________________________________________________________*/

#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#ifdef WIN32
#include <direct.h>
#endif

#include "config.h"
#include "utility.h"

void RFC822GMTTimeString(struct tm* time, char buf[32])
{
    const char* day[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* month[] = {"Jan", "Feb",  "Mar", "Apr", "May", "Jun",  
                           "Jul", "Aug", "Sep", "Oct",  "Nov", "Dec"};

    // Example: Sun, 06 Nov 1994 08:49:37 GMT
    const char* k822Format = "%s, %2d %s %4d %2d:%2d:%2d GMT";

    sprintf(buf, k822Format, day[time->tm_wday],
                             time->tm_mday,
                             month[time->tm_mon],
                             time->tm_hour,
                             time->tm_min,
                             time->tm_sec);
}

char *strdup_new(const char *str)
{
    char *n;

    n = new char[strlen(str) + 1];
    strcpy(n, str);
 
    return n;
}

#ifdef WIN32

char *FreeampDir(Preferences *pref)
{
    char path[_MAX_PATH] = {0x00};
    uint32 len = sizeof(path);
    char *s;

    pref->GetInstallDirectory(path, &len);

    s = new char[strlen(path) + 1];
    strcpy(s, path);

    return s;
}

#else

#include <stdlib.h>

char *FreeampDir(Preferences *prefs)
{
    char *homeDir = getenv("HOME");
    const char *fadir = "/.freeamp";
    char *s;

    if (!homeDir) {
        s = new char[2];
        strcpy(s, "/");
        return s;
    }

    s = new char[strlen(homeDir) + strlen(fadir) + 1];
    strcpy(s, homeDir);
    strcat(s, fadir);

    return s;
}
#endif    

const char* protocol = "file://";

Error FilePathToURL(const char* path, char* url, uint32* length)
{
    Error result = kError_InvalidParam;

    assert(path);
    assert(url);
    assert(length);

    if(path && url && length)
    {
        result = kError_BufferTooSmall;
        int32 extra = 0;

#ifdef WIN32
         if(path[0] == '\\')
         {
             extra = 2;
         }
#endif

        if(*length >= strlen(path) + strlen(protocol) + 1 + extra)
        {

            strcpy(url, protocol);

#ifdef WIN32
            if(extra)
            {
                int32 drive = _getdrive();
           
                url[7] = drive + 'A' - 1;
                url[8] = '|';
                url[9] = 0x00;
            }
#endif

            strcat(url, path);

#ifdef WIN32
            if(strlen(path) > 1 && path[1] == ':')
            {
                url[8] = '|';
            }

            for(int32 index = strlen(url) - 1; index >=0; index--)
            {
                if(url[index] == '\\')
                    url[index] = '/';
            }
#endif  
        }

        *length = strlen(path) + strlen(protocol) + 1 + extra;
    }

    return result;
}

Error URLToFilePath(const char* url, char* path, uint32* length)
{
    Error result = kError_InvalidParam;

    assert(path);
    assert(url);
    assert(length);

    if(path && url && length && !strncasecmp(url, protocol, strlen(protocol)))
    {
        result = kError_BufferTooSmall;

        if(*length >= strlen(url) - strlen(protocol) + 1)
        {
            strcpy(path, url + strlen(protocol));
#ifdef WIN32
            if(strlen(path) > 1 && path[1] == '|')
            {
                path[1] = ':';
            }

            for(int32 index = strlen(path) - 1; index >=0; index--)
            {
                if(path[index] == '/')
                    path[index] = '\\';
            }
#endif  
        }

        *length = strlen(url) - strlen(protocol) + 1;
    }

    return result;
}
