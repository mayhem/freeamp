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
	
	$Id: pmp300.h,v 1.1.2.2 1999/08/30 08:43:34 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_PMP300_H
#define INCLUDED_PMP300_H

#include <string>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"
#include "facontext.h"

#include "portabledevice.h"
#include "playlist.h"

class PMP300 : public PortableDevice {
 public:
    PMP300(FAContext *context);
    virtual ~PMP300();

    virtual Error GetSupportedDevices(DeviceInfo* device, uint32 index);

    virtual bool IsDeviceAvailable(DeviceInfo* device);

    virtual Error InitializeDevice(DeviceInfo* device, 
                                   callback_function function = NULL);

    virtual Error ReadPlaylist(DeviceInfo* device, 
                               vector<PlaylistItem*>* items,
                               callback_function function = NULL);

    virtual Error WritePlaylist(DeviceInfo* device, 
                                vector<PlaylistItem*>* items,
                                callback_function function = NULL);

    virtual Error DownloadSong(DeviceInfo* device, 
                               PlaylistItem* item,
                               char* url,
                               callback_function function = NULL);

 private:
     FAContext* m_context;
};



#endif // INCLUDED_PMP300_H

