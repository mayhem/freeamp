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
	
	$Id: portabledevice.h,v 1.1.2.7 1999/08/30 12:23:17 elrod Exp $
____________________________________________________________________________*/

#ifndef _PORTABLE_DEVICE_H_
#define _PORTABLE_DEVICE_H_

#include <string>
#include <vector>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"
#include "facontext.h"

typedef enum {
    kConnection_Unknown, 
    kConnection_Parallel, 
    kConnection_USB
} ConnectionType;

class PortableDevice;

typedef PortableDevice* DeviceRef;

typedef bool (*callback_function)(void * cookie);

class PlaylistItem;

class DeviceInfo {
 public:

    DeviceInfo():m_ref(NULL),m_type(kConnection_Unknown),
                 m_bytesTotal(0),m_bytesUsed(0),m_port(0),
                 m_numEntries(0) {}
    
    virtual ~DeviceInfo() {}

    Error SetManufacturer(const char* manufacturer)
    {m_manufacturer = manufacturer; return kError_NoErr; }
    const char* GetManufacturer() const { return m_manufacturer.c_str(); }

    Error SetDevice(const char* device) 
    { m_device = device; return kError_NoErr; }
    const char* GetDevice() { return m_device.c_str(); }

    Error SetCapacity(uint32 bytesTotal, uint32 bytesUsed) 
    { m_bytesTotal = bytesTotal; m_bytesUsed = bytesUsed; return kError_NoErr; }
    void GetCapacity(uint32* bytesTotal, uint32* bytesUsed) 
    { if(bytesTotal) *bytesTotal = m_bytesTotal; if(bytesTotal) *bytesUsed = m_bytesUsed; }

    Error SetNumEntries(uint32 count) { m_numEntries = count; return kError_NoErr; }
    uint32 GetNumEntries() const { return m_numEntries; }

    Error SetConnectionType(ConnectionType type) { m_type = type; return kError_NoErr; }
    ConnectionType GetConnectionType() const { return m_type; }

    Error SetPortAddress(uint32 port) { m_port = port; return kError_NoErr; }
    uint32 GetPortAddress() const { return m_port; }

    Error SetRef(DeviceRef ref) { m_ref = ref; return kError_NoErr; }
    DeviceRef GetRef() { return m_ref; }

 private:
  
    string m_manufacturer;
    string m_device;
    DeviceRef m_ref;
    uint32 m_bytesTotal;
    uint32 m_bytesUsed;
    ConnectionType m_type;
    uint32 m_port;
    uint32 m_numEntries;
};

class PortableDevice {
 
 public:

    PortableDevice(FAContext *context) {}
    virtual ~PortableDevice() {}

    virtual Error GetSupportedDevices(DeviceInfo* device, uint32 index) = 0;

    virtual bool IsDeviceAvailable(DeviceInfo* device) = 0;

    virtual Error GetDeviceInfo(DeviceInfo* device) = 0;

    virtual Error InitializeDevice(DeviceInfo* device, 
                                   callback_function function = NULL) = 0;

    virtual Error ReadPlaylist(DeviceInfo* device, 
                               vector<PlaylistItem*>* items,
                               callback_function function = NULL) = 0;

    virtual Error WritePlaylist(DeviceInfo* device, 
                                vector<PlaylistItem*>* items,
                                callback_function function = NULL) = 0;

    virtual Error DownloadSong(DeviceInfo* device, 
                               PlaylistItem* item,
                               char* url,
                               callback_function function = NULL) = 0;
};


#endif // _PORTABLE_DEVICE_H_

