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
	
	$Id: win32volume.cpp,v 1.1 1999/04/26 00:51:55 robert Exp $
____________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "win32volume.h"

Win32VolumeManager::Win32VolumeManager()
                 :VolumeManager()
{

}

void Win32VolumeManager::SetVolume(int32 v) 
{
    waveOutSetVolume((HWAVEOUT)WAVE_MAPPER , MAKELPARAM(0xFFFF*v, 0xFFFF*v)); 
}

int32 Win32VolumeManager::GetVolume() 
{
    int32 volume = 0;

    waveOutGetVolume((HWAVEOUT)WAVE_MAPPER, (DWORD*)&volume);
    volume = (int32)(100 * ((float)LOWORD(volume)/(float)0xffff));

    return volume;
}                   
