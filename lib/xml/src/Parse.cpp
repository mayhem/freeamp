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

   $Id: Parse.cpp,v 1.1.2.1 1999/09/21 02:44:59 elrod Exp $
____________________________________________________________________________*/ 

#include "stdio.h"
#include "map"
#include "assert.h"
#include "Parse.h"

const int iMaxElementLineLength = 2048;
const int iMaxElementNameLength = 255;
const int iMaxAttrLength = 255;
const int iMaxValueLength = 1024;

Parse::Parse(void)
{
}

Parse::~Parse(void)
{
}

Error Parse::ParseFile(string &oFile)
{
    FILE    *fpFile;
    char    *szElement, *szElementName, *szAttr, *szValue;
    string   oElementName, oAttr, oValue;
    int      iRet, iOffset, iTemp;
    bool     bError = false, bEmptyTag = false;
    AttrMap  oAttrMap; 
    Error    eRet;

    fpFile = fopen(oFile.c_str(), "r");
    if (fpFile == NULL)
       return kError_FileNotFound;

    szElement = new char[iMaxElementLineLength];
    szElementName = new char[iMaxElementNameLength];
    szAttr = new char[iMaxAttrLength];
    szValue = new char[iMaxValueLength];
    for(; !bError;)
    {
        iRet = fscanf(fpFile, " < %2048[^>] > ", szElement);
        if (iRet < 1)
        {
           if (feof(fpFile))
              break;

           bError = true;
           break;
        }

        iTemp = 0;
        sscanf(szElement, " /%255[A-Za-z0-9]%n", szElementName, &iTemp);
        if (iTemp > 0)
        {
            oElementName = szElementName;
            eRet = EndElement(oElementName);
            if (IsError(eRet))
               bError = true;

            continue;
        }

        sscanf(szElement, " %255[A-Za-z0-9] %n", szElementName, &iOffset);
        oElementName = szElementName;

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
                          " %255[A-Za-z0-9] = \"%255[^\"] \" %n", 
                          szAttr, szValue, &iTemp);
            if (iRet < 2)
            {
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

    if (bError)
    {
        return kError_ParseError;
    }

    delete szElement;
    delete szElementName,
    delete szAttr;
    delete szValue;

    fclose(fpFile);

    return kError_NoErr;
}

void Parse::GetErrorString(string &oError)
{
    oError = m_oLastError;
}
