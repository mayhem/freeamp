/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player
	Portions copyright (C) 1998 GoodNoise

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
	
	$Id: soundcardpmo.h,v 1.2 1998/10/17 18:26:11 jdw Exp $
____________________________________________________________________________*/


#ifndef _SOUNDCARDPMO_H_
#define _SOUNDCARDPMO_H_

/* system headers */
#include <stdlib.h>

/* project headers */
#include <config.h>
#include "pmo.h"
#include "buffer.h"


#define BIT_SELECT  0x1f
#define SLEEPTIME   256

static const uint32 OBUFFERSIZE = 2 * 1152;


class SoundCardPMO : public PhysicalMediaOutput{

public:
    SoundCardPMO();
    virtual ~SoundCardPMO();
    
    virtual bool Init(OutputInfo* info);
    virtual bool Reset(bool user_stop);
    virtual int32 Write(void *,int32);
    virtual void Clear();
    
    
 private:
    int16 buffer[OBUFFERSIZE];
    int16 *bufferp[MAXCHANNELS];
    uint32 channels;
    static int audio_fd;
    static Mutex refcountMutex;
    static int refCount;
    OutputInfo *myInfo;
    int32 getprocessed(void);
    
};

#endif /* _SOUNDCARDPMO_H_ */



