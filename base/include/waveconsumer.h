/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Copyright (C) 2000 EMusic.com

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
	
	$Id: waveconsumer.h,v 1.1.2.1 2000/07/27 17:35:00 robert Exp $
____________________________________________________________________________*/

#ifndef __WAVECONSUMER_H_INCLUDED__
#define __WAVECONSUMER_H_INCLUDED__

#include "config.h"

class WaveConsumer 
{
   public:
  
             WaveConsumer() {};
    virtual ~WaveConsumer() {};

    virtual void BeginWaveData(void) = 0;
    virtual void PumpWaveData(int channels, int numSamples, 
                              unsigned char *data) = 0;
    virtual void EndWaveData(bool bFinished) = 0;

};

#endif
