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
	
	$Id: utility.h,v 1.2.2.2 1999/09/16 00:03:58 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_UTILITY_H
#define INCLUDED_UTILITY_H

#include "config.h"
#include "errors.h"

char *FreeampDir(void);
Error FilePathToURL(const char* path, char* url, uint32* length);
Error URLToFilePath(const char* url, char* path, uint32* length);


#endif /* INCLUDED_UTILITY_H */
