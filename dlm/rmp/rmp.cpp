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
	
	$Id: rmp.cpp,v 1.1.2.2 1999/09/25 21:48:04 elrod Exp $
____________________________________________________________________________*/

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

#include "config.h"
#include "errors.h"
#include "errno.h"

#include "rmp.h"

typedef struct FormatInfoStruct {
    char* extension;
    char* description;

} FormatInfoStruct; 

FormatInfoStruct formats[] = {
    {"rmp", "RMP Download Format"}
};

#define kNumFormats (sizeof(formats)/sizeof(FormatInfoStruct))

extern "C"
{
   DownloadFormat *Initialize(FAContext* context)
   {
      return new RMP(context);
   }
}

RMP::RMP(FAContext* context):DownloadFormat(context)
{
    m_context = context;
}

RMP::~RMP()
{

}

Error RMP::GetSupportedFormats(DownloadFormatInfo* info, uint32 index)
{
    Error result = kError_InvalidParam;

    assert(info);

    if(info)
    {
        result = kError_NoMoreFormats;

        if(index < kNumFormats)
        {
            info->SetExtension(formats[index].extension);
            info->SetDescription(formats[index].description);
            result = kError_NoErr;
        }
    }

    return result;
}

Error RMP::ReadDownloadFile(char* url, vector<DownloadItem*>* list)
{
    Error result = kError_InvalidParam;

    assert(url);
    assert(list);

    if(url && list)
    {
        
    }

    return result;

}