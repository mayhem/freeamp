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
	
	$Id: testitem.h,v 1.1 1999/03/03 09:03:41 elrod Exp $
____________________________________________________________________________*/

#ifndef _TEST_ITEM_H
#define _TEST_ITEM_H

#include "config.h"
#include "listitem.h"

class TestItem : public ListItem {

 public:
     TestItem();

    virtual ~TestItem();

    virtual	void DrawItem(DIB* canvas, RECT* bounds);

 private:
     int32 m_r, m_g, m_b;
};

#endif /* _TEST_ITEM_H */
