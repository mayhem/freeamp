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
	
	$Id: alsavolume.h,v 1.1 1999/04/26 00:51:40 robert Exp $
____________________________________________________________________________*/

#ifndef _ALSAVOLUME_H_
#define _ALSAVOLUME_H_

#include "config.h"
#include "volume.h"

class ALSAVolumeManager : public VolumeManager
{
    public:

    ALSAVolumeManager(int iCard, int iDevice);

    virtual void SetVolume(int32);
    virtual int32 GetVolume(void);

    private:

    int iCard, iDevice;
};

#endif // _ALSAVOLUME_H_
