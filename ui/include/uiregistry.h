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
	
	$Id: uiregistry.h,v 1.1 1998/10/13 08:46:11 elrod Exp $
____________________________________________________________________________*/

#ifndef _UI_REGISTRY_H_
#define _UI_REGISTRY_H_

#include "config.h"
#include "registry.h"

class UIInfo : public RegistryInfo {
 public:
    UIInfo(){}
    ~UIInfo(){}
};

class UIRegistry : public Registry{
 public:
    UIRegistry();
    ~UIRegistry();
};


#endif // _UI_REGISTRY_H_
