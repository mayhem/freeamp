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
	
	$Id: portabledevice.h,v 1.1.2.2 1999/08/24 23:42:46 elrod Exp $
____________________________________________________________________________*/

#ifndef _PORTABLE_DEVICE_H_
#define _PORTABLE_DEVICE_H_

#include <string>
#include <assert.h>

#include "config.h"
#include "errors.h"


class DeviceInfo {

 public:

    DeviceInfo():m_id(0xFFFFFFFF) {}
    
    virtual ~DeviceInfo() {}

    Error SetManufacturer(const char* manufacturer){m_manufacturer = manufacturer; return kError_NoErr; }
    const char* GetManufacturer() const { return m_manufacturer.c_str(); }

    Error SetDevice(const char* device) { m_device = device; return kError_NoErr; }
    const char* GetDevice() { return m_device.c_str(); }

    Error SetDeviceID(uint32 id) { m_id = id; return kError_NoErr; }
    uint32 GetDeviceID() { return m_id; }

 private:
  
    string m_manufacturer;
    string m_device;
    uint32 m_id;
};



#endif // _PORTABLE_DEVICE_H_

