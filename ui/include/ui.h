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
	
	$Id: ui.h,v 1.7 1998/12/14 19:58:30 jdw Exp $
____________________________________________________________________________*/

#ifndef _UI_H_
#define _UI_H_

#include "event.h"
#include "errors.h"

#include "playlist.h"

enum {
    PRIMARY_UI = 0,  // passed to Init method of Primary UI at startup
    SECONDARY_UI_STARTUP = 1, // passed to Init methods of other UIs loaded at startup
    SECONDARY_UI_RUNTIME = 2  // passed to Init method of UI loaded some other time
};

class UserInterface : public EventQueue {
 public:
    virtual int32 AcceptEvent(Event *) = 0;
    virtual void SetArgs(int32,char **) = 0;
    virtual void SetTarget(EventQueue *) = 0;
    virtual void SetPlayListManager(PlayListManager *) = 0;
    virtual Error Init(int32) = 0;
    virtual ~UserInterface() {}
};

#endif // _UI_H_

