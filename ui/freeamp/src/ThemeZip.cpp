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

   $Id: ThemeZip.cpp,v 1.1.2.2 1999/10/01 15:22:34 ijr Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif
#include "zlib.h"
#include "ThemeZip.h"

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

const int iMajorVersion = 1;
const int iMinorVersion = 0;
const int iBufferSize = 8192;

ThemeZip::ThemeZip(void)
{
}

ThemeZip::~ThemeZip(void)
{
}
Error ThemeZip::CompressThemeZip(const string &oDestFile, 
                                 vector<string *> &oFileList)
{
   gzFile  pOut;
   FILE   *pIn;
   char   *pBuffer;
   string  oFile;
   vector<string *>::iterator i;
   int     iNetworkInt, iWrite, iRead, iSize, iBlock;

   pOut = gzopen(oDestFile.c_str(), "wb");
   if (pOut == NULL)
       return kError_FileNoAccess;

   iNetworkInt = htonl(oFileList.size());
   if (gzwrite(pOut, (void *)&iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pOut);
       return kError_WriteFile;
   }
   iNetworkInt = htonl(iMajorVersion);
   if (gzwrite(pOut, (void *)&iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pOut);
       return kError_WriteFile;
   }
   iNetworkInt = htonl(iMinorVersion);
   if (gzwrite(pOut, (void *)&iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pOut);
       return kError_WriteFile;
   }

   pBuffer = new char[iBufferSize];
   for(i = oFileList.begin(); i != oFileList.end(); i++)
   {
       char *pPtr;

       oFile = *(*i);
       printf("File: %s\n", oFile.c_str());
#ifndef WIN32
       pPtr = strrchr(oFile.c_str(), '/');
#else
       pPtr = strrchr(oFile.c_str(), '\\');
#endif
       if (pPtr)
           oFile.erase(0, ((int)pPtr - (int)oFile.c_str()) + 1);
       printf("File: %s\n", oFile.c_str());

       pIn = fopen((*i)->c_str(), "rb");
       if (pIn == NULL)
       {
           gzclose(pOut);
           delete pBuffer;
           return kError_FileNotFound;
       }

       iSize = oFile.length() + 1;
       iNetworkInt = htonl(iSize);
       if (gzwrite(pOut, (void *)&iNetworkInt, sizeof(int32)) != sizeof(int32))
       {
           fclose(pIn);
           gzclose(pOut);
           delete pBuffer;
           return kError_WriteFile;
       }
       if (gzwrite(pOut, (void *)oFile.c_str(), iSize) != iSize)
       {
           fclose(pIn);
           gzclose(pOut);
           delete pBuffer;
           return kError_WriteFile;
       }

       fseek(pIn, 0, SEEK_END);
       iSize = ftell(pIn);
       fseek(pIn, 0, SEEK_SET);

       iNetworkInt = htonl(iSize);
       if (gzwrite(pOut, (void *)&iNetworkInt, sizeof(int32)) != sizeof(int32))
       {
           fclose(pIn);
           gzclose(pOut);
           delete pBuffer;
           return kError_WriteFile;
       }
       for(; iSize > 0;)
       {
           iBlock = min(iSize, iBufferSize);
           iRead = fread(pBuffer, 1, iBlock, pIn);
           if (iRead != iBlock)
           {
               fclose(pIn);
               gzclose(pOut);
               delete pBuffer;
               return kError_ReadFile;
           }
           iWrite = gzwrite(pOut, pBuffer, iBlock);
           if (iWrite != iBlock)
           {
               fclose(pIn);
               gzclose(pOut);
               delete pBuffer;
               return kError_WriteFile;
           }

           iSize -= iBlock;
       }          
       fclose(pIn);
   }
   delete pBuffer;
   gzclose(pOut);

   return kError_NoErr;
}

Error ThemeZip::DecompressThemeZip(const string &oSrcFile,
                                   const string &oDestPath)
{
   FILE   *pOut;
   gzFile  pIn;
   char   *pBuffer;
   int     iNetworkInt, iWrite, iRead, iSize, iBlock;
   int     iMajor, iMinor, iNumFiles, i;
   string  oFile;

   pIn = gzopen(oSrcFile.c_str(), "rb");
   if (pIn == NULL)
       return kError_FileNotFound;

   if (gzread(pIn, &iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pIn);
       return kError_ReadFile;
   }
   iNumFiles = ntohl(iNetworkInt); 

   if (gzread(pIn, &iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pIn);
       return kError_ReadFile;
   }
   iMajor = ntohl(iNetworkInt); 

   if (gzread(pIn, &iNetworkInt, sizeof(int32)) != sizeof(int32))
   {
       gzclose(pIn);
       return kError_ReadFile;
   }
   iMinor = ntohl(iNetworkInt); 

   if (iMajor != iMajorVersion || iMinor != iMinorVersion)
   {
       gzclose(pIn);
       return kError_InvalidVersion;
   }

   pBuffer = new char[iBufferSize];
   for(i = 0; i < iNumFiles; i++)
   {
       char *pFileBuffer;

       if (gzread(pIn, &iNetworkInt, sizeof(int32)) != sizeof(int32))
       {
           gzclose(pIn);
           return kError_ReadFile;
       }
       iSize = ntohl(iNetworkInt); 

       pFileBuffer = new char[iSize];
       if (gzread(pIn, pFileBuffer, iSize) != iSize)
       {
           gzclose(pIn);
           delete pBuffer;
           return kError_ReadFile;
       }
#ifdef WIN32
       oFile = oDestPath + string("\\") + string(pFileBuffer);
#else
       oFile = oDestPath + string("/") + string(pFileBuffer);
#endif       
       delete pFileBuffer;

       pOut = fopen(oFile.c_str(), "wb");
       if (pOut == NULL)
       {
           gzclose(pIn);
           delete pBuffer;
           return kError_FileNotFound;
       }

       if (gzread(pIn, &iNetworkInt, sizeof(int32)) != sizeof(int32))
       {
           fclose(pOut);
           gzclose(pIn);
           return kError_ReadFile;
       }
       iSize = ntohl(iNetworkInt); 

       for(; iSize > 0;)
       {
           iBlock = min(iSize, iBufferSize);
           iRead = gzread(pIn, pBuffer, iBlock);
           if (iRead != iBlock)
           {
               gzclose(pIn);
               fclose(pOut);
               delete pBuffer;
               return kError_ReadFile;
           }
           iWrite = fwrite(pBuffer, 1, iBlock, pOut);
           if (iWrite != iBlock)
           {
               gzclose(pIn);
               fclose(pOut);
               delete pBuffer;
               return kError_WriteFile;
           }

           iSize -= iBlock;
       }          
       fclose(pOut);
   }
   delete pBuffer;
   gzclose(pIn);

   return kError_NoErr;
}

#if 0
void main(int argc, char **argv)
{
   ThemeZip a;
   vector<string *> list;
   string src;

   if (argv[1][0] == 'e')
   {
       int i;

       for(i = 3; i < argc; i++)
       {
           string *p;

           p = new string(argv[i]);
           list.push_back(p);
       }
       int r = a.CompressThemeZip(string(argv[2]), list);
       printf("ret: %d", r);
       exit(0);
   }  
   if (argv[1][0] == 'd')
   {
       int r = a.DecompressThemeZip(string(argv[2]), string(argv[3]));
       printf("ret: %d", r);
       exit(0);
   }  
   printf("Did nothing\n");
}
#endif
