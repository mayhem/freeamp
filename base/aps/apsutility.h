/*_________________________________________________________________________
         
        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 2000 Relatable

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
        
        $Id: apsutility.h,v 1.1 2000/07/31 19:51:38 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_APSUTILITY_H
#define INCLUDED_APSUTILITY_H

#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <winsock.h>
#include <time.h>
#else
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef __BEOS__
#include <arpa/inet.h>
#include <unistd.h>
#define Sleep(x) usleep(x*1000)
#else
#include <be/kernel/OS.h>
#define Sleep(x) snooze(x*1000)
#endif
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "apsmetadata.h"

/** Generates a CRC code from the buffer, for integrety checks. */
unsigned short int GenCRC(const char* pBuffer, int nLen);

// NetToHost will convert the buffer from the client to the APSMetaData format.
const char* HostToNet(vector<APSMetaData*>* pAPSList, string& strCollectionGUID,
                      int& nBufferLen);

// NetToHost will convert the buffer from the client to the APSMetaData format.
vector<APSMetaData*>* NetToHost(const char* pBuffer, string& strCollectionGUID);

// The WriteToLogFile function takes three arguments, a text line, the file name
// to be written to, and the log directory path.  The log file name will 
// automatically have the timestamp appended to it.
int WriteToLogFile(string strRecordLine, string strFileName, string strLogDir);

#endif
