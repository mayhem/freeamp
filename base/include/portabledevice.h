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
	
	$Id: portabledevice.h,v 1.1.2.1 1999/08/23 19:18:39 elrod Exp $
____________________________________________________________________________*/

#ifndef _PORTABLE_DEVICE_H_
#define _PORTABLE_DEVICE_H_

#include <assert.h>

#include "config.h"
#include "errors.h"


class DeviceInfo {

 public:

    DeviceInfo()
    {
        m_manufacturer = NULL;
        m_device = NULL;
        m_id = 0xFFFFFFFF;
    }

    DeviceInfo(const DeviceInfo& info)
    {
        m_manufacturer = NULL;
        m_device = NULL;
        m_id = 0xFFFFFFFF;

        *this = info;
    }

    virtual ~DeviceInfo()
    {
        if(m_manufacturer) delete [] m_manufacturer;
        if(m_device) delete [] m_device;
    }

    Error SetManufacturer(const char* manufacturer){ return SetBuffer(&m_manufacturer, manufacturer); }
    const char* GetManufacturer() const { return m_manufacturer; }

    Error SetDevice(const char* device) { return SetBuffer(&m_device, device); }
    const char* GetDevice() { return m_device; }

    Error SetDeviceID(uint32 id) { m_id = id; }
    uint32 GetDeviceID() { return m_id; }

    DeviceInfo& operator = (DeviceInfo& info)
    {
        SetManufacturer(info.m_manufacturer);
        SetDevice(info.m_device);
        SetDeviceID(info.m_id);

        return *this;
    }

 protected:
    Error SetBuffer(char** buf, const char* src)
    {
        Error result = kError_InvalidParam;

        assert(buf);
        assert(src);

        if(buf && src)
        {
            if(*buf)
            {
                delete [] *buf;
                *buf = NULL;
            }

            result = kError_OutOfMemory;

            *buf = new char[strlen(src) + 1];

            if(*buf)
            {
                strcpy(buf, src);
                result = kError_NoErr;
            }
        }

        return result;
    }

 private:
  
    char* m_manufacturer;
    char* m_device;
    uint32 m_id;
};



#endif // _PORTABLE_DEVICE_H_

