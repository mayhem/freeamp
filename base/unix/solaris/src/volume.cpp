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
	
	$Id: volume.cpp,v 1.2 1999/04/21 06:48:32 dogcow Exp $
____________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/audioio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream.h>


#include "volume.h"

void VolumeManager::SetVolume(int32 v) {
  struct audio_info ainfo;
  int mixFd = open("/dev/audioctl",O_RDWR);
  if (mixFd != -1) {
    ioctl(mixFd, AUDIO_GETINFO, &ainfo);
    ainfo.play.gain = v;
    ioctl(mixFd, AUDIO_SETINFO, &ainfo);
    close(mixFd);
  }
}

int32 VolumeManager::GetVolume() {
  struct audio_info ainfo;
  int mixFd = open("/dev/audioctl",O_RDWR);
  int volume = 0;
  if (mixFd != -1) {
    ioctl(mixFd, AUDIO_GETINFO, &ainfo);
    volume = ainfo.play.gain;
    volume &= 0xFF;
    close(mixFd);
  }
  return volume;
}

