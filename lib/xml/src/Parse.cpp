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

   $Id: Parse.cpp,v 1.1.2.7 1999/10/01 20:55:53 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include <map>
#include <assert.h>
#include "Parse.h"
#include "debug.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

const int iMaxElementLineLength = 2048;
const int iMaxElementNameLength = 255;
const int iMaxAttrLength = 255;
const int iMaxValueLength = 1024;
const int iMaxPCDataLength = 4096;

Parse::Parse(void)
{
}

Parse::~Parse(void)
{
}

Error Parse::ParseFile(const string &oFile)
{
    FILE    *fpFile;
    char    *szElement, *szElementName, *szAttr, *szValue, *szData;
    char     szDummy[10];
    string   oElementName, oAttr, oValue, oData;
    int      iRet, iOffset, iTemp;
    bool     bError = false, bEmptyTag = false;
    AttrMap  oAttrMap; 
    Error    eRet;

	m_oLastError = string("");
    m_iErrorLine = 1;
    
    fpFile = fopen(oFile.c_str(), "r");
    if (fpFile == NULL)
    {
       m_oLastError = string("File ") + oFile + string(" not found"); 
       return kError_FileNotFound;
    }   

    szElement = new char[iMaxElementLineLength];
    szElementName = new char[iMaxElementNameLength];
    szAttr = new char[iMaxAttrLength];
    szValue = new char[iMaxValueLength];
    szData = new char[iMaxPCDataLength];
    for(szElement[0] = 0; !bError;)
    {
    	m_iErrorLine += CountNewlines(szElement);
        
        iRet = fscanf(fpFile, " < %1024[^>] >", szElement);
        if (iRet < 1)
        {
            if (feof(fpFile))
               break;

		    iRet = fscanf(fpFile, " %4095[^<]", szData);
            if (iRet < 1)
		    {
		        m_oLastError = string("Unrecognized characters found");
                bError = true;
                break;
            }
            m_iErrorLine += CountNewlines(szData);
            oData = string(szData);
            eRet = PCData(oData);
            if (IsError(eRet))
            {
                bError = true;
                break;
            }   
            continue; 
        }

        iRet = fscanf(fpFile, "%[\n\t \r]", szElementName);
        if (iRet > 0)
    	    m_iErrorLine += CountNewlines(szElementName);

        iTemp = 0;
        sscanf(szElement, " /%254[A-Za-z0-9_]%n", szElementName, &iTemp);
        if (iTemp > 0)
        {
            oElementName = szElementName;
            eRet = EndElement(oElementName);
            if (IsError(eRet))
               bError = true;

            continue;
        }

        if (sscanf(szElement, "%[!-]", szDummy))
        {
            continue;
        }
        
		iOffset = 0;
        int iRet = sscanf(szElement, " %254[A-Za-z0-9_] %n", szElementName, &iOffset);
        oElementName = szElementName;
        if (iOffset == 0)
            iOffset = strlen(szElementName);

        oAttrMap.clear();
        bEmptyTag = false;

        for(;;)
        {
            iTemp = 0;
            sscanf(szElement + iOffset, " /%n", &iTemp);
            if (iTemp > 0)
            {
               bEmptyTag = true;
               iOffset += iTemp;
            }

            iTemp = 0;
            sscanf(szElement + iOffset, " >%n", &iTemp);
            if (strlen(szElement + iOffset) == 0 || iTemp > 0)
                break;

            iRet = sscanf(szElement + iOffset, 
                          " %254[A-Za-z0-9] = \"%254[^\"] \" %n", 
                          szAttr, szValue, &iTemp);
            if (iRet < 2 || iTemp == 0)
            {
               m_oLastError = string("Improperly formatted attribute list");
               bError = true;
               break;
            }

            iOffset += iTemp;
            oAttr = szAttr;
            oValue = szValue;
            oAttrMap[szAttr] = szValue;
        }

        if (!bError)
        {
             eRet = BeginElement(oElementName, oAttrMap);
             if (bEmptyTag && !IsError(eRet))
                eRet = EndElement(oElementName);

             if (IsError(eRet))
                bError = true;
        }
    }

    delete szElement;
    delete szElementName,
    delete szAttr;
    delete szValue;
    delete szData;

    fclose(fpFile);

    if (bError)
    {
        return kError_ParseError;
    }

    return kError_NoErr;
}

void Parse::GetErrorString(string &oError)
{
	char *szError;
    
    szError = new char[m_oLastError.length() + 100];
    sprintf(szError, "%s on line %d.", 
            m_oLastError.c_str(), m_iErrorLine);
    oError = string(szError);
    delete szError;
}


int Parse::CountNewlines(char *szElement)
{
	int   iCount;
    char *pPtr;
    
    for(iCount = 0, pPtr = szElement; *pPtr; pPtr++)
       if (*pPtr == '\n')
          iCount++;

    return iCount;
}

int Parse::GetErrorLine(void)
{
    return m_iErrorLine;
}
