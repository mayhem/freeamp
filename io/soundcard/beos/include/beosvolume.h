/*
 $Id: beosvolume.h,v 1.1.2.1 1999/06/29 05:34:35 hiro Exp $
*/
#ifndef _BEOS_VOLUME_H
#define _BEOS_VOLUME_H

#include "config.h"
#include "volume.h"

class BeOSVolumeManager : public VolumeManager
{
public:
					BeOSVolumeManager();
	virtual			~BeOSVolumeManager();
	virtual void	SetVolume( int32 vol );
	virtual int32	GetVolume( void );

protected:

private:
};

#endif // _BEOS_VOLUME_H
