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
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id: log.cpp,v 1.1 1999/02/13 01:35:36 robert Exp $
____________________________________________________________________________*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "log.h"

const int iMaxLogLineLen = 2048;
const char *szLogLevelNames[] = 
{
    "Main",
    "Decode",
    "Input",
    "Output"
};

LogFile::LogFile(char *m_szLogFileArg)
{
    m_szLogFile = strdup(m_szLogFileArg);
    m_fpLog = NULL;

    // Log nothing but errors on default
    m_iLogLevelFlags = 0x0;
}

LogFile::~LogFile(void)
{
    if (m_fpLog)
       fclose(m_fpLog);
}

bool LogFile::Open(void)
{
    m_fpLog = fopen(m_szLogFile, "a");
    return m_fpLog != NULL;
}

void LogFile::AddLogLevel(int iLogLevelFlags)
{
    if (iLogLevelFlags < 0 || iLogLevelFlags >= LogLast)
       return;

    m_iLogLevelFlags |= 1 << iLogLevelFlags;
}

void LogFile::Error(char *format, ...)
{
    char *szBuffer;
    va_list argptr;

    if (m_fpLog == NULL)
        if (!Open())
           return;

    szBuffer = new char[iMaxLogLineLen];

    va_start(argptr, format);
    vsprintf(szBuffer, format, argptr);
    va_end(argptr);

    fprintf(m_fpLog, "Error: %s", szBuffer);
    fflush(m_fpLog);

    delete szBuffer;
}

void LogFile::Log(int iLogLevel, char *format, ...)
{
    char *szBuffer;
    va_list argptr;

    if (m_fpLog == NULL || (m_iLogLevelFlags & ( 1 << iLogLevel)) == 0)
       return;

    szBuffer = new char[iMaxLogLineLen];

    va_start(argptr, format);
    vsprintf(szBuffer, format, argptr);
    va_end(argptr);

    fprintf(m_fpLog, "%s: %s", szLogLevelNames[iLogLevel], szBuffer);
    fflush(m_fpLog);

    delete szBuffer;
}
