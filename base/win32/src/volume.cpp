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
	
	$Id: volume.cpp,v 1.3 1999/03/11 02:53:28 robert Exp $
____________________________________________________________________________*/

#include <windows.h>
#include <mmsystem.h>

#include "volume.h"

void VolumeManager::SetVolume(int32 v) {
	waveOutSetVolume( (HWAVEOUT)WAVE_MAPPER , MAKELPARAM(0xFFFF*v, 0xFFFF*v));
}

int32 VolumeManager::GetVolume() {
    int32 volume = 0;
	waveOutGetVolume((HWAVEOUT)WAVE_MAPPER, (DWORD*)&volume);
	volume = (int32)(100 * ((float)LOWORD(volume)/(float)0xffff));
    return volume;
}

