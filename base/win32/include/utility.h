/*____________________________________________________________________________
	
	FreeAMP - The Free MP3 Player
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
	
	$Id: utility.h,v 1.3 1998/10/16 00:33:02 elrod Exp $
____________________________________________________________________________*/

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "config.h"
#include "error.h"

Error InitWindowsRegistry(void);

Error GetInstallDirectory(char* path, int32 len);


#endif // _UTILITY_H_