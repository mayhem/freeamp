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
	
	$Id: pmp300.cpp,v 1.1.2.4 1999/08/31 04:47:17 ijr Exp $
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
#include "rio.h"

typedef struct DeviceInfoStruct {
    char* manufacturer;
    char* device;
    ConnectionType type;
} DeviceInfoStruct; 

DeviceInfoStruct devices[] = {
    {"Diamond", "Rio PMP-300", kConnection_Parallel}
};

#define kNumDevices (sizeof(devices)/sizeof(DeviceInfoStruct))

extern "C"
{
   PortableDevice *Initialize(FAContext* context)
   {
      return new PMP300(context);
   }
}

#ifdef WIN32
bool LoadDriver(const char* driverName, const char* driverPath);
bool UnloadDriver(const char* driverName);
#endif

PMP300::PMP300(FAContext* context):PortableDevice(context)
{
    m_context = context;

#ifdef WIN32
    OSVERSIONINFO osid;

	osid.dwOSVersionInfoSize = sizeof (osid);
	GetVersionEx (&osid);

	switch (osid.dwPlatformId) 
    {
        // Window 3.x
	    case VER_PLATFORM_WIN32s:
		    break;

	    // Windows 95
	    case VER_PLATFORM_WIN32_WINDOWS:
 		    break;

	    // Windows NT
	    case VER_PLATFORM_WIN32_NT:
        {
#if !defined( _M_ALPHA )
		    if(osid.dwMajorVersion >= 4)
            {
                // this will allow us port access thru
                // inp and outp so the rio stuff will
                // work.

                const char* driver = "portio";
                char path[MAX_PATH];
                uint32 size = sizeof(path);

                context->prefs->GetInstallDirectory(path, &size);

                strcat(path, "\\");
                strcat(path, driver);
                strcat(path, ".sys");

                LoadDriver(driver, path);
            }
#endif // !defined( _M_ALPHA )
            break;
        }
    }
#endif  //WIN32
}

PMP300::~PMP300()
{
#ifdef WIN32
    // platform specific uninitialization
    OSVERSIONINFO osid;

	osid.dwOSVersionInfoSize = sizeof (osid);
	GetVersionEx (&osid);

	switch (osid.dwPlatformId) 
    {
        // Window 3.x
	    case VER_PLATFORM_WIN32s:
		    break;

	    // Windows 95
	    case VER_PLATFORM_WIN32_WINDOWS:
 		    break;

	    // Windows NT
	    case VER_PLATFORM_WIN32_NT:
        {
#if !defined( _M_ALPHA )
		    if(osid.dwMajorVersion >= 4)
            {
                UnloadDriver("portio");
            }
#endif // !defined( _M_ALPHA )
            break;
        }
    }
#endif // WIN32
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
            device->SetConnectionType(devices[index].type);

            result = kError_NoErr;
        }
    }

    return result;
}

bool PMP300::IsDeviceAvailable(DeviceInfo* device)
{
    bool result = false;

    assert(device);

    if(device)
    {
        if(!strcasecmp(device->GetDevice(), devices[0].device))
        {
            uint32 ports[] = { 0x378, 0x278, 0x03BC };
            CRio rio;

            for(uint32 count = 0; count < sizeof(ports); count++)
            {
                if(rio.Set(ports[count]) && rio.CheckPresent())
                {
                    device->SetPortAddress(ports[count]);
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

Error PMP300::GetDeviceInfo(DeviceInfo* device)
{
    Error result = kError_InvalidParam;

    if(!strcasecmp(device->GetDevice(), devices[0].device))
    {
        result = kError_DeviceNotFound;

        uint32 ports[] = { 0x378, 0x278, 0x03BC };
        CRio rio;
        bool rioPresent = false;

        if(device->GetPortAddress() && 
           rio.Set(device->GetPortAddress()) && 
           rio.CheckPresent())
        {
            rioPresent = true;
        }
        else // brute force it...
        {
            for(uint32 count = 0; count < sizeof(ports); count++)
            {
                if(rio.Set(ports[count]) && rio.CheckPresent())
                {
                    device->SetPortAddress(ports[count]);
                    rioPresent = true;
                    break;
                }
            }
        }

        if(rioPresent)
        {
            if( rio.RxDirectory() )
	        {
		        CDirBlock& cDirBlock = rio.GetDirectoryBlock();
                CDirHeader& cDirHeader = cDirBlock.m_cDirHeader;

                uint32 numEntries, totalMem, usedMem; 

                numEntries = cDirHeader.m_usCountEntry;
                totalMem = ((long)cDirHeader.m_usCount32KBlockAvailable * CRIO_SIZE_32KBLOCK);
                usedMem = ((long)cDirHeader.m_usCount32KBlockUsed * CRIO_SIZE_32KBLOCK);

                rio.UseExternalFlash( true );

                if( rio.RxDirectory() )
	            {
                    CDirBlock& cDirBlock = rio.GetDirectoryBlock();
                    CDirHeader& cDirHeader = cDirBlock.m_cDirHeader;

                    numEntries += cDirHeader.m_usCountEntry;
                    totalMem += ((long)cDirHeader.m_usCount32KBlockAvailable * CRIO_SIZE_32KBLOCK);
                    usedMem += ((long)cDirHeader.m_usCount32KBlockUsed * CRIO_SIZE_32KBLOCK);
                }

                device->SetNumEntries(numEntries);
                device->SetCapacity(totalMem, usedMem);
	        }

            result = kError_NoErr;
        }

    }

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

#ifdef WIN32

#include <windows.h>

static 
bool
InstallDriver(  SC_HANDLE  scManager,
                const char* driverName,
                const char* driverPath)

{
    bool result = false;
    SC_HANDLE  service;

    service = CreateService(scManager,              // SCManager database
                            driverName,             // name of service
                            driverName,             // name to display
                            SERVICE_ALL_ACCESS,     // desired access
                            SERVICE_KERNEL_DRIVER,  // service type
                            SERVICE_DEMAND_START,   // start type
                            SERVICE_ERROR_NORMAL,   // error control type
                            driverPath,             // service's binary
                            NULL,                   // no load ordering group
                            NULL,                   // no tag identifier
                            NULL,                   // no dependencies
                            NULL,                   // LocalSystem account
                            NULL);                  // no password


                                
    if(service || ERROR_SERVICE_EXISTS == GetLastError())
    {
        result = true;
    }
    /*else
    {
        LPVOID lpMessageBuffer;
        int32 error = GetLastError();

		FormatMessage(
		  FORMAT_MESSAGE_ALLOCATE_BUFFER |
		  FORMAT_MESSAGE_FROM_SYSTEM,
		  NULL,
		  error,
		  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  (LPTSTR) &lpMessageBuffer,
		  0,
		  NULL );

		// now display this string
 		MessageBox(NULL, (char*)lpMessageBuffer, 0, MB_OK);

		// Free the buffer allocated by the system
		LocalFree( lpMessageBuffer );

    }*/
    
    CloseServiceHandle(service);

    return result;
}

static
bool
StartDriver(SC_HANDLE scManager,
            const char* driverName)
{
    bool result = false;
    SC_HANDLE  service;

    service = OpenService(  scManager,
                            driverName,
                            SERVICE_ALL_ACCESS);

    if(service)
    {
        BOOL error;

        error = StartService(service, // service identifier
                             0,       // number of arguments
                             NULL);   // pointer to arguments

        result = (error > 0);

        CloseServiceHandle(service);    
    }
    
    return result;
}

static
bool
OpenDevice(const char* driverName)
{
    bool    result = false;
    char    path[MAX_PATH];
    HANDLE  handle;

    sprintf(path, "\\\\.\\%s", driverName);

    handle = CreateFile(path,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

    if(handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(handle);
        result = true;
    }
   
    return result;
}


bool 
LoadDriver(const char* driverName, 
           const char* driverPath)
{

    bool result = false;
    SC_HANDLE scManager;

    scManager = OpenSCManager(NULL,
                              NULL,
                              SC_MANAGER_ALL_ACCESS);

    if(scManager)
    {
        result = InstallDriver( scManager,
                                driverName,
                                driverPath);
        if(result)
        {
            result = StartDriver(scManager,
                                 driverName);

            if(result)
            {
                result = OpenDevice(driverName);
            }
        }

        CloseServiceHandle(scManager);
    }

    return result;
}

static
bool
StopDriver( SC_HANDLE scManager,
            const char* driverName)
{
    bool result = false;
    SC_HANDLE service;
    SERVICE_STATUS  serviceStatus;

    service = OpenService(  scManager,
                            driverName,
                            SERVICE_ALL_ACCESS);

    if(service)
    {
        BOOL error;

        error = ControlService( service,
                                SERVICE_CONTROL_STOP,
                                &serviceStatus);

        result = (error > 0);

        CloseServiceHandle(service);
    }

    return result;
}

static
bool
RemoveDriver(   SC_HANDLE scManager,
                const char* driverName)
{
    bool result = false;
    SC_HANDLE  service;

    service = OpenService(  scManager,
                            driverName,
                            SERVICE_ALL_ACCESS);
    if(service)
    {
        BOOL error;

        error = DeleteService(service);

        result = (error > 0);

        CloseServiceHandle(service);
    }

    return result;
}

bool 
UnloadDriver(const char* driverName)
{
    bool result = false;
    SC_HANDLE scManager;

    scManager = OpenSCManager(NULL,
                              NULL,
                              SC_MANAGER_ALL_ACCESS);

    if(scManager)
    {
        result = StopDriver(scManager,
                            driverName);

        if(result)
        {
            result = RemoveDriver(  scManager, 
                                    driverName);
        }

        CloseServiceHandle(scManager);
    }

    return result;
}

#endif
