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
       
       $Id: esdvolume.h,v 1.3 1999/07/13 18:42:04 robert Exp $
____________________________________________________________________________*/

#ifndef _ESDVOLUME_H_
#define _ESDVOLUME_H_

#include "config.h"
#include "volume.h"

class ESDVolumeManager : public VolumeManager
{
    public:

    ESDVolumeManager(int iStream);

    virtual void SetVolume(int32);
    virtual int32 GetVolume(void);
    
    private:
    
    int iStream, iVolume;
};

#endif // _ESDVOLUME_H_

