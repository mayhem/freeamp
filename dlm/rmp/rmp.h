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
	
	$Id: rmp.h,v 1.1.2.2 1999/09/25 21:48:05 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_RMP_H
#define INCLUDED_RMP_H

#include <string>

using namespace std;

#include <assert.h>

#include "config.h"
#include "errors.h"
#include "facontext.h"

#include "downloadformat.h"

class RMP : public DownloadFormat {
 public:
    RMP(FAContext *context);
    virtual ~RMP();

    virtual Error GetSupportedFormats(DownloadFormatInfo* info, uint32 index);
    virtual Error ReadDownloadFile(char* url, vector<DownloadItem*>* items);

 private:
     FAContext* m_context;
};



#endif // INCLUDED_RMP_H

