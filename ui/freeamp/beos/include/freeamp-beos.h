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
	
	$Id: freeamp-beos.h,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $
____________________________________________________________________________*/

// hacked up from cmdlineUI.h

#ifndef _UI_FREEAMP_BEOS_H_
#define _UI_FREEAMP_BEOS_H_

#include "ui.h"
#include "event.h"
#include "thread.h"
#include "playlist.h"

class FAContext;
class PlayerWindow;

class FreeAmpUI : public UserInterface
{
public:
    FreeAmpUI(FAContext *context);
    virtual int32 AcceptEvent(Event *);
    virtual void SetArgs(int32 argc, char **argv);
    virtual void SetTarget(EventQueue *eqr) { m_playerEQ = eqr; }
    virtual Error Init(int32);
    virtual void SetPlayListManager(PlayListManager *);
    static void keyboardServiceFunction(void *);
    virtual ~FreeAmpUI();
    virtual Error SetPropManager(Properties *p) { m_propManager = p; if (p) return kError_NoErr; else return kError_UnknownErr; }
	void Play( void );
	void Stop( void );
	void Pause( void );
	void QuitPlayer( void );
	void NextMediaPiece( void );
	void PreviousMediaPiece( void );

protected:
   FAContext *m_context;

private:
	Properties *m_propManager;
	void ProcessArgs();
	int32 m_startupLevel;
	int32 m_argc;
	char **m_argv;
	EventQueue *m_playerEQ;
	void processSwitch(char *);
	Thread *keyboardListenThread;
	PlayListManager *m_plm;
	int32 m_lastIndexPlayed;
	bool m_id3InfoPrinted;
	PlayerWindow*		m_playerWindow;
};

#endif // _UI_FREEAMP_BEOS_H_
