/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998-1999 GoodNoise
	Portions Copyright (C) 1999 Mark H. Weaver <mhw@netris.org>

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
	
	$Id: unixprefs.cpp,v 1.1.2.1 1999/04/16 08:14:44 mhw Exp $
____________________________________________________________________________*/

#include "config.h"

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "unixprefs.h"
#include "prefixprefs.h"


// default values
const char*  kDefaultUI = "freeamp-" AC_HOST_OS ".ui";
const char*  kDefaultTextUI = "freeampcmd-" AC_HOST_OS ".ui";
const char*  kDefaultPMO = "soundcard-" AC_HOST_OS ".pmo";


class LibDirFindHandle {
 public:
    List <char *> *m_pLibDirs;
    int32 m_current;
};


static
int
CompareLines(char *const &a, char *const &b)
{
    return strcasecmp(a, b) > 0;
}

UnixPrefs::
UnixPrefs()
     : m_prefsFilePath(0), m_saveEnable(false), m_changed(false)
{
    const char *suffix = "/.freeamp_prefs";
    char *homeDir = getenv("HOME");

    if (!homeDir)
	return;

    // Compute pathname of preferences file
    m_prefsFilePath = new char[strlen(homeDir) + strlen(suffix) + 1];
    strcpy(m_prefsFilePath, homeDir);
    strcat(m_prefsFilePath, suffix);

    FILE *prefsFile = fopen(m_prefsFilePath, "r");
    if (!prefsFile)
    {
	if (errno == ENOENT)
	{
	    m_saveEnable = true;
	    SetDefaults();
	}
	return;
    }

    m_saveEnable = true;

    char buffer[1024];
    char dummy;

    while (fgets(buffer, sizeof(buffer), prefsFile))
	if (buffer[0])		// Skip blank lines
	{
	    // Strip trailing newline if any
	    int i = strlen(buffer) - 1;
	    if (buffer[i] == '\n')
		buffer[i] = '\0';
	    m_lines.AddItem(strdup(buffer));
	}
    fclose(prefsFile);
    m_lines.SortItems(CompareLines);
}

UnixPrefs::
~UnixPrefs()
{
    Save();

    int32 numLines = m_lines.CountItems();
    int32 i;

    for (i = 0; i < numLines; i++)
	free(m_lines.ItemAt(i));

    delete[] m_prefsFilePath;
}

Error
UnixPrefs::
SetDefaults()
{
    // set install directory value
    SetPrefString(kInstallDirPref, UNIX_LIBDIR);
    
    // set default ui value
    SetPrefString(kUIPref, kDefaultUI);
    
    // set default text ui value
    SetPrefString(kTextUIPref, kDefaultTextUI);
    
    // set default pmo value
    SetPrefString(kPMOPref, kDefaultPMO);

    Preferences::SetDefaults();
}

Error
UnixPrefs::
Save()
{
    if (!m_saveEnable || !m_changed)
	return kError_NoErr;

    m_changed = false;

    const char *tmpSuffix = ".tmp";
    char *tmpFilePath = new char[strlen(m_prefsFilePath) +
				 strlen(tmpSuffix) + 1];
    strcpy(tmpFilePath, m_prefsFilePath);
    strcat(tmpFilePath, tmpSuffix);

    const char *bakSuffix = ".bak";
    char *bakFilePath = new char[strlen(m_prefsFilePath) +
				 strlen(bakSuffix) + 1];
    strcpy(bakFilePath, m_prefsFilePath);
    strcat(bakFilePath, bakSuffix);

    {
	FILE *prefsFile = fopen(tmpFilePath, "w");
	if (!prefsFile)
	{
	    delete[] tmpFilePath;
	    delete[] bakFilePath;
	    return kError_UnknownErr; // XXX: Be more informative
	}

	m_mutex.Acquire();
		
	int32 numLines = m_lines.CountItems();
	int32 i;
	
	for (i = 0; i < numLines; i++)
	{
	    fputs(m_lines.ItemAt(i), prefsFile);
	    putc('\n', prefsFile);
	}
	
	m_mutex.Release();

	if (ferror(prefsFile))
	{
	    fclose(prefsFile);
	    delete[] tmpFilePath;
	    delete[] bakFilePath;
	    return kError_UnknownErr; // XXX: Be more informative
	}
	
	fclose(prefsFile);
    }

    if (rename(m_prefsFilePath, bakFilePath) && errno != ENOENT)
    {
	delete[] tmpFilePath;
	delete[] bakFilePath;
	return kError_UnknownErr; // XXX: Be more informative
    }

    if (rename(tmpFilePath, m_prefsFilePath))
	rename(bakFilePath, m_prefsFilePath);

    delete[] tmpFilePath;
    delete[] bakFilePath;
    return kError_NoErr;
}

bool
UnixPrefs::
FindPref(const char *pref, int32 *index)
{
    int32 lo = 0, hi = m_lines.CountItems();

    while (lo < hi)
    {
	int32 pivot = (lo + hi) / 2;
	char *p = m_lines.ItemAt(pivot);
	int i = 0;

	while (tolower(pref[i]) == tolower(p[i]) && pref[i])
	    i++;

	if (pref[i] == '\0' && p[i] == '=')
	{
	    *index = pivot;
	    return true;
	}
	else if (tolower(pref[i]) < tolower(p[i]))
	    hi = pivot;
	else
	    lo = pivot + 1;
    }
    *index = lo;
    return false;
}

Preferences *
UnixPrefs::
ComponentPrefs(const char *componentName)
{
    return new PrefixPrefs(this, componentName);
}

Error
UnixPrefs::
GetPrefString(const char* pref, char* buf, uint32* len)
{
    int32 index;

    m_mutex.Acquire();
	
    buf[0] = '\0';
    if (!FindPref(pref, &index))
    {
	*len = 0;
	m_mutex.Release();
	return kError_NoErr;	// XXX: Should this return an error?
    }

    char *value = m_lines.ItemAt(index) + strlen(pref) + 1;
    uint32 value_len = strlen(value) + 1;

    if (value_len > *len)
    {
	m_mutex.Release();
	return kError_BufferTooSmall;
    }

    memcpy(buf, value, value_len);
    *len = value_len;
    m_mutex.Release();
    return kError_NoErr;
}

Error
UnixPrefs::
SetPrefString(const char* pref, const char* buf)
{
    int32 prefLen = strlen(pref);
    int32 bufLen = strlen(buf);
    char *newLine = (char *) malloc(prefLen + bufLen + 2);
    int32 index;

    memcpy(newLine, pref, prefLen);
    newLine[prefLen] = '=';
    memcpy(newLine + prefLen + 1, buf, bufLen);
    newLine[prefLen + bufLen + 1] = '\0';

    m_mutex.Acquire();

    if (FindPref(pref, &index))
    {
	free(m_lines.ItemAt(index));
	m_lines.SetItemAt(newLine, index);
    }
    else
	m_lines.AddItem(newLine, index);

    m_changed = true;

    m_mutex.Release();
    return kError_NoErr;
}

char *UnixPrefs::m_libDirs = 0;

const char *
UnixPrefs::
GetLibDirs()
{
    if (!m_libDirs) {
	m_libDirs = new char[1024];
	strcpy(m_libDirs,".:~/.freeamp:");
	strcat(m_libDirs,UNIX_LIBDIR);
	strcat(m_libDirs,"/freeamp");
    }
    return m_libDirs;
}

LibDirFindHandle *
UnixPrefs::
GetFirstLibDir(char *path, uint32 *len)
{
    // if no FREEAMP_PATH, libdirs = ~/.freeamp : @lib_installdir@/freeamp : .
    // if FREEAMP_PATH, then its FREEAMP_PATH
    char *pEnv = getenv("FREEAMP_PATH");
    char *pPath = NULL;
    if (pEnv) {
//	cout << "Using env: " << pEnv << endl;
	pPath = strdup(pEnv);
    } else {
	pPath = strdup(GetLibDirs());
    }
    pEnv = pPath;
    LibDirFindHandle *hLibDirFind = new LibDirFindHandle();
    hLibDirFind->m_pLibDirs = new List<char *>();
    hLibDirFind->m_current = 0;

    char *pCol = (char *)1;
    char *pPart = pPath;
    while (pCol) {
	pCol = strchr(pPart,':');
	if (pCol) *pCol = '\0';
	char *pFoo = strdup(pPart);
	hLibDirFind->m_pLibDirs->AddItem(pFoo);
	pPart = pCol + sizeof(char);
    }

    pPath = hLibDirFind->m_pLibDirs->ItemAt(0);
    if (pPath) {
	strncpy(path,pPath,*len);
	*len = strlen(pPath);
    } else {
	*path = '\0';
	*len = 0;
	delete hLibDirFind->m_pLibDirs;
	delete hLibDirFind;
	hLibDirFind = 0;
    }

    if (pEnv) delete pEnv;
    //cout << "returning " << path << endl;
    return hLibDirFind;
}

Error
UnixPrefs::
GetNextLibDir(LibDirFindHandle *hLibDirFind, char *path, uint32 *len)
{
    if (hLibDirFind) {
	hLibDirFind->m_current++;
	char *pPath = hLibDirFind->m_pLibDirs->ItemAt(hLibDirFind->m_current);
	if (pPath) {
	    strncpy(path,pPath,*len);
	    *len = strlen(pPath);
//	    cout << "returning next: " << path << endl;
	    return kError_NoErr;
	} else {
	    *path = '\0';
	    *len = 0;
//	    cout << "returning no next " << path << endl;
	    return kError_NoMoreLibDirs;
	}
    }
    return kError_NoMoreLibDirs;
}

Error
UnixPrefs::
GetLibDirClose(LibDirFindHandle *hLibDirFind)
{
    if (hLibDirFind) {
	hLibDirFind->m_pLibDirs->DeleteAll();
	delete hLibDirFind->m_pLibDirs;
	delete hLibDirFind;
    }
    return kError_NoErr;
}

