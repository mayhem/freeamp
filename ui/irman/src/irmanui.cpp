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
	
	$Id: irmanui.cpp,v 1.6.2.1 1999/04/20 20:57:20 mhw Exp $
____________________________________________________________________________*/

#include "config.h"

#include <iostream.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include <sys/time.h>
#include <termios.h>
#include <signal.h>

#if HAVE_ERRNO_H
#include <errno.h>
#endif

#include "irmanui.h"

#include "event.h"
#include "thread.h"
#include "eventdata.h"

extern "C" {
#include "ir.h"
	   }

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new IRManUI(context);
}
    
	   }

void IRManUI::SetPlayListManager(PlayListManager *plm) {
    m_plm = plm;
}


#define ASSOCIATE(x,y) pInt = new int32; *pInt = y; m_commands.Insert(x,pInt);

#define IR_VolumeUp 9998
#define IR_VolumeDown 9999


IRManUI::IRManUI(FAContext *context) {
    m_context = context;
    m_plm = NULL;
    m_playerEQ = NULL;
    m_propManager = NULL;

    irListenThread = NULL;

    int32 *pInt = NULL;
    ASSOCIATE("4297ac000000",CMD_Play);
    ASSOCIATE("4017fc000000",CMD_Stop);
    ASSOCIATE("46173c000000",CMD_NextMediaPiece);
    ASSOCIATE("4217bc000000",CMD_PrevMediaPiece);
    ASSOCIATE("4037f8000000",CMD_QuitPlayer);
    ASSOCIATE("4237b8000000",IR_VolumeUp);
    ASSOCIATE("463738000000",IR_VolumeDown);
    ASSOCIATE("43179c000000",CMD_TogglePause);
}


IRManUI::~IRManUI() {
    m_quitIRListen = true;
    if (irListenThread) {
	irListenThread->Join();
	delete irListenThread;
	irListenThread = NULL;
    }
}


Error IRManUI::Init(int32 startupType) {
    m_startupType = startupType;
    if (m_startupType == PRIMARY_UI) {
	ProcessArgs();
    }
    m_quitIRListen = false;
    irListenThread = Thread::CreateThread();
    irListenThread->Create(IRManUI::irServiceFunction,this);
    return kError_NoErr;
}

void IRManUI::irServiceFunction(void *pclcio) {
    IRManUI *pMe = (IRManUI *)pclcio;
    char *pDevice;

    PropValue *pv = NULL;
    pMe->m_propManager->GetProperty("IRMAN-device",&pv);
    if (pv) {
	pDevice = (char *)((StringPropValue *)pv)->GetString();
    } else {
	pDevice = DEFAULT_DEVICE;
    }
    if (ir_init(pDevice) < 0) {
	cerr << "error initializing IRman: `" << strerror(errno) << "'" << endl;
	if (pMe->m_startupType == PRIMARY_UI) {
	    Event *e = new Event(CMD_QuitPlayer);
	    pMe->m_playerEQ->AcceptEvent(e);
	}
	return;
    }

    unsigned char *code;
    char *text;
    int32 lastCmd = -1;  // we'll attempt to debounce here...
    int32 lastTimeMill = 0;
    int32 lastTimeSec = 0;
    struct timeval tv;
    struct timezone tz;
    int32 bounceTime = 300000;
    while (!pMe->m_quitIRListen) {
	code = ir_poll_code();
	gettimeofday(&tv,&tz);
	if (code) {
	    text = ir_code_to_text(code);
	    //cout << "rx " << text << endl;
	    
	    int32 *cmd = pMe->m_commands.Value(text);
	    if (cmd) {
		//cout << "command: " << *cmd << endl;
		if ((*cmd != lastCmd) ||

		    ((*cmd == lastCmd) && ((tv.tv_sec - lastTimeSec) > 2)) ||
		    
		    ((*cmd == lastCmd) && ((tv.tv_sec - lastTimeSec) == 1) && (tv.tv_usec > lastTimeMill)) ||

		    ((*cmd == lastCmd) && ( ((tv.tv_usec > lastTimeMill) && ((tv.tv_usec - lastTimeMill) > bounceTime)) ||
					    ((tv.tv_usec < lastTimeMill) && ((tv.tv_usec + 1000000 - lastTimeMill) > bounceTime)) ) ) ) {

		    lastCmd = *cmd;
		    lastTimeMill = tv.tv_usec;
		    lastTimeSec = tv.tv_sec;
		    switch (*cmd) {
			case IR_VolumeUp: {
			    bounceTime = 100000;
			    
             PropValue *pv;
             pMe->m_propManager->GetProperty("pcm_volume", &pv);
             if (pv)
             {
			        int32 vol = ((Int32PropValue *) pv)->GetInt32(); 
             
			        vol += 5;
			        if (vol > 100) vol == 100;
			        Int32PropValue *ipv = new Int32PropValue(vol);
			        pMe->m_propManager->SetProperty("pcm_volume",(PropValue *)ipv);
             }
			    break; }
			case IR_VolumeDown: {
			    bounceTime = 100000;
             PropValue *pv;
             pMe->m_propManager->GetProperty("pcm_volume", &pv);
             if (pv)
             {
			        int32 vol = ((Int32PropValue *) pv)->GetInt32(); 
			        vol -= 5;
			        if (vol < 0) vol == 0;
			        Int32PropValue *ipv = new Int32PropValue(vol);
			        pMe->m_propManager->SetProperty("pcm_volume",(PropValue *)ipv);
             }
			    break; }
			default:
			    bounceTime = 300000;
			    Event *e = new Event(*cmd);
			    pMe->m_playerEQ->AcceptEvent(e);
		    }
		} else {
		    //cout << "bouncing..." << endl;
		}
	    }
	} else {
	    usleep(10000);
	}
    }
    
    ir_finish();
}

int32 IRManUI::AcceptEvent(Event *e) {
    if (e) {
	//cout << "IRManUI: processing event " << e->Type() << endl;
	switch (e->Type()) {
	    case INFO_PlayListDonePlay: {
		if (m_startupType == PRIMARY_UI) {
		    Event *e = new Event(CMD_QuitPlayer);
		    m_playerEQ->AcceptEvent(e);
		}
		break; }
	    case CMD_Cleanup: {
		m_quitIRListen = true;
		Event *e = new Event(INFO_ReadyToDieUI);
		m_playerEQ->AcceptEvent(e);
		break; }
	    default:
		break;
	}
    }
    return 0;
}

void IRManUI::SetArgs(int argc, char **argv) {
    m_argc = argc; m_argv = argv;
}

void IRManUI::ProcessArgs() {
    char *pc = NULL;
    for(int i=1;i<m_argc;i++) {
	//cout << "Adding arg " << i << ": " << argv[i] << endl;
	pc = m_argv[i];
	if (pc[0] == '-') {
	    processSwitch(&(pc[0]));
	} else {
	    m_plm->AddItem(pc,0);
	}
    }
    m_plm->SetFirst();
    Event *e = new Event(CMD_Play);
    m_playerEQ->AcceptEvent(e);
}

void IRManUI::processSwitch(char *pc) {
    return;
}

