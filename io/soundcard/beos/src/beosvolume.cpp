/*
 $Id: beosvolume.cpp,v 1.1.2.1 1999/06/29 05:34:35 hiro Exp $
 */

#include <stdio.h>
#include "beosvolume.h"

BeOSVolumeManager::BeOSVolumeManager()
:	VolumeManager()
{
}

BeOSVolumeManager::~BeOSVolumeManager()
{
}

void
BeOSVolumeManager::SetVolume( int32 vol )
{
	printf( "SetVolume( %d )\n", vol );
}

int32
BeOSVolumeManager::GetVolume( void )
{
	return 0;
}
