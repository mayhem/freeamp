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
	
	$Id: pmp300.cpp,v 1.1.2.2 1999/08/30 08:43:34 elrod Exp $
____________________________________________________________________________*/

#include <assert.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#include "config.h"
#include "errors.h"
#include "errno.h"

#include "pmp300.h"

typedef struct DeviceInfoStruct {
    char* manufacturer;
    char* device;

} DeviceInfoStruct; 

DeviceInfoStruct devices[] = {
    {"Diamond", "Rio PMP-300"}
};

#define kNumDevices (sizeof(devices)/sizeof(DeviceInfoStruct))

extern "C"
{
   PortableDevice *Initialize(FAContext* context)
   {
      return new PMP300(context);
   }
}

PMP300::PMP300(FAContext* context):PortableDevice(context)
{
    m_context = context;
}

PMP300::~PMP300()
{

}

Error PMP300::GetSupportedDevices(DeviceInfo* device, uint32 index)
{
    Error result = kError_InvalidParam;

    assert(device);

    if(device)
    {
        result = kError_NoMoreDevices;

        if(index < kNumDevices)
        {
            device->SetManufacturer(devices[index].manufacturer);
            device->SetDevice(devices[index].device);
            device->SetCapacity(0);

            result = kError_NoErr;
        }
    }

    return result;
}

bool PMP300::IsDeviceAvailable(DeviceInfo* device)
{
    bool result = false;


    return result;
}

Error PMP300::InitializeDevice(DeviceInfo* device, 
                               callback_function function)
{
    Error result = kError_InvalidParam;

    assert(device);

    if(device)
    {
       
    }

    return result;

}


Error PMP300::ReadPlaylist(DeviceInfo* device, 
                           vector<PlaylistItem*>* list,
                           callback_function function)
{
    Error result = kError_InvalidParam;

    assert(device);
    assert(list);

    if(device && list)
    {
       

    }

    return result;
}

Error PMP300::WritePlaylist(DeviceInfo* device, 
                            vector<PlaylistItem*>* list,
                            callback_function function)
{
    Error result = kError_InvalidParam;

    assert(device);
    assert(list);

    if(device && list)
    {
        
    }

    return result;
}


Error PMP300::DownloadSong(DeviceInfo* device, 
                           PlaylistItem* item,
                           char* url,
                           callback_function function)

{
    Error result = kError_InvalidParam;

    assert(device);
    assert(url);
    assert(item);

    if(device && url && item)
    {
        
    }

    return result;
}