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
	
	$Id: lcdui.cpp,v 1.5 1999/01/22 06:02:52 jdw Exp $
____________________________________________________________________________*/

#include <iostream.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include <sys/time.h>
#include <termios.h>
#include <signal.h>


#include "config.h"
#include "lcdui.h"

#include "event.h"
#include "playlist.h"
#include "thread.h"
#include "eventdata.h"

#define LCDPROC_4 1

#if LCDPROC_4
extern "C" {
#include "sockets.h"
	   }
#else
extern "C" {
#include "MtxOrb.h"
#include "lcd.h"
#include "drv_base.h"
	   }
#endif
#define stdinfd 0

extern "C" {

UserInterface *Initialize() {
    return new LcdUI();
}

	   }

static struct termios normalTTY;
static struct termios rawTTY;
int getKey() {
    fd_set rdfs;

    FD_ZERO(&rdfs);
    FD_SET(stdinfd, &rdfs);
    if (select (stdinfd+1,&rdfs,NULL,NULL,NULL) == 1) {
	if (FD_ISSET(stdinfd, &rdfs)) return 1;
    }
    return 0;
}


void LcdUI::SetPlayListManager(PlayListManager *plm) {
    m_plm = plm;
}

LcdUI::LcdUI() {
    m_timeType = TIME_CURR;
    m_plm = NULL;
    m_playerEQ = NULL;
    m_lcdLock = new Mutex();

    keyboardListenThread = NULL;

    m_currHours = m_currMinutes = m_currSeconds = m_totalHours = m_totalMinutes = m_totalSeconds = 0;

//    cout << endl << "Command Line Interface" << endl << endl;
//    cout << " * q    Quit" << endl;
//    cout << " * +/=  Next Song" << endl;
//    cout << " * -    Prev Song" << endl;
//    cout << " * p    Pause / UnPause" << endl;
//    cout << " * s    Shuffle" << endl << endl;
}


LcdUI::~LcdUI() {
    if (m_startupType == PRIMARY_UI) {
	tcsetattr(stdinfd, TCSANOW, &normalTTY);
    }
    //cout << "LcdUI: begin deleted..." << endl;
    
    m_lcdLock->Acquire();
#if LCDPROC_4
    sock_close(m_sock);
#else
    lcd.clear();
    lcd.string(1,2,"  Thanks for using  ");
    lcd.string(1,3,"       FreeAmp      ");
    lcd.flush();
#endif
    
    if (keyboardListenThread) {
	keyboardListenThread->Destroy();
	delete keyboardListenThread;
	keyboardListenThread = NULL;
    }
    if (m_lcdLock) {
	delete m_lcdLock;
	m_lcdLock = NULL;
    }
}

#define STOCK_CONTRAST 140

Error LcdUI::Init(int32 startupType) {
#if !LCDPROC_4
    lcd_init("/dev/lcd","MtxOrb");
    lcd.contrast(STOCK_CONTRAST);
#endif
    cout << "startup..." << endl;
    m_lcdLock->Acquire(WAIT_FOREVER);
#if LCDPROC_4
    m_sock = sock_connect("localhost",LCDPORT);
    cout << "connecting" << endl;
    if (m_sock <= 0) {
	//screwwwwed
	return kError_InitFailed;
    }
    cout << "done connecting" << endl;
    sock_send_string(m_sock, "hello\n");
    sock_send_string(m_sock, "screen_add FA\n");
    sock_send_string(m_sock, "screen_set FA name {FreeAmp}\n");
    sock_send_string(m_sock, "widget_add FA songname string\n");
    sock_send_string(m_sock, "widget_add FA timeline string\n");
    sock_send_string(m_sock, "widget_add FA artist string\n");
    sock_send_string(m_sock, "widget_set FA songname 1 1 {Welcome To FreeAmp}\n");
    sock_send_string(m_sock, "widget_set FA timeline 4 1 {total       00:00:00}\n");
    sock_send_string(m_sock, "widget_del FA heartbeat\n");
#else 
    lcd.string(1,1," Welcome To FreeAmp");
    lcd.flush();
#endif
    m_lcdLock->Release();

    if ((m_startupType = startupType) == PRIMARY_UI) {
	cout << "LCD Startup Type: PRIMARY_UI" << endl;
	ProcessArgs();
	tcgetattr(stdinfd, &::normalTTY);
	::rawTTY = ::normalTTY;
	::rawTTY.c_lflag &= ~ICANON;
	::rawTTY.c_lflag &= ~ECHO;
	tcsetattr(stdinfd, TCSANOW, &rawTTY);
	
	
	keyboardListenThread = Thread::CreateThread();
	keyboardListenThread->Create(LcdUI::keyboardServiceFunction,this);
    }

    return kError_NoErr;
}

void LcdUI::keyboardServiceFunction(void *pclcio) {
    LcdUI *pMe = (LcdUI *)pclcio;
    char *buf = new char[8000];
    char *pkey = new char[1];
    char chr;
    size_t rtn;
    int fn = STDIN_FILENO;

//#if LCDPROC_4    
#if 0
    while(1) {
	len = sock_recv(m_sock,buf,8000);
	if (len) {
	    printf(buf);
	}
    }
#else 
    for (;;) {
	::getKey();
	read(stdinfd,&chr,1);
	switch (chr) {
	    case ' ': {
		pMe->m_timeType = (pMe->m_timeType + 1) % TIME_MAX;
		pMe->m_lcdLock->Acquire();
		pMe->BlitTimeLine();
#if !LCDPROC_4
		lcd.flush();
#endif
		pMe->m_lcdLock->Release();
		break;
	    }
	    case 'p':
	    case 'P': {
		Event *e = new Event(CMD_TogglePause);
		pMe->m_playerEQ->AcceptEvent(e);
		break;
	    }
	    case '-': {
		Event *e = new Event(CMD_PrevMediaPiece);
		pMe->m_playerEQ->AcceptEvent(e);
		break;
	    }
	    case '=':
	    case '+':
	    case 'n':
	    case 'N': {
		Event *e = new Event(CMD_NextMediaPiece);
		pMe->m_playerEQ->AcceptEvent(e);
		break; }
	    case 'q':
	    case 'Q': {
		Event *e = new Event(CMD_QuitPlayer);
		pMe->m_playerEQ->AcceptEvent(e);
		break; }
	    case 's':
	    case 'S': {
		if (pMe->m_plm) {
		    pMe->m_plm->SetShuffle(SHUFFLE_SHUFFLED);
		    pMe->m_plm->SetFirst();
		}
		Event *e = new Event(CMD_Stop);
		pMe->m_playerEQ->AcceptEvent(e);
		e = new Event(CMD_Play);
		pMe->m_playerEQ->AcceptEvent(e);
		break;}
//	    case 'f':{
//		Event *e = new Event(CMD_ChangePosition,(void *)200);
//		pMe->m_playerEQ->AcceptEvent(pMe->m_playerEQ,e);
//	    }
	    default:
		break;
	}
    }
#endif
}

int32 LcdUI::AcceptEvent(Event *e) {
    if (e) {
	//cout << "LcdUI: processing event " << e->Type() << endl;
	switch (e->Type()) {
	    case INFO_PlayListDonePlay: {
		if (m_startupType == PRIMARY_UI) {
		    Event *e = new Event(CMD_QuitPlayer);
		    m_playerEQ->AcceptEvent(e);
		}
		break; }
	    case CMD_Cleanup: {
		Event *e = new Event(INFO_ReadyToDieUI);
		m_playerEQ->AcceptEvent(e);
		break; }
	    case INFO_Stopped: {
		m_currHours = m_currMinutes = m_currSeconds = 0;
		m_lcdLock->Acquire();
		BlitTimeLine();
#if !LCDPROC_4
		lcd.flush();
#endif
		m_lcdLock->Release();
		break;
	    }
	    case INFO_UserMessage: {
		if (!strcmp("time_curr_mode",((UserMessageEvent *)e)->GetInfo())) {
		    m_timeType = TIME_CURR;
		    m_lcdLock->Acquire();
		    BlitTimeLine();
#if !LCDPROC_4
		    lcd.flush();
#endif
		    m_lcdLock->Release();
		} else if (!strcmp("time_remain_mode",((UserMessageEvent *)e)->GetInfo())) {
		    m_timeType = TIME_REMAIN;
		    m_lcdLock->Acquire();
		    BlitTimeLine();
#if !LCDPROC_4
		    lcd.flush();
#endif
		    m_lcdLock->Release();

		}else if (!strcmp("time_total_mode",((UserMessageEvent *)e)->GetInfo())) {
		    m_timeType = TIME_TOTAL;
		    m_lcdLock->Acquire();
		    BlitTimeLine();
#if !LCDPROC_4
		    lcd.flush();
#endif
		    m_lcdLock->Release();

		}
		break;
	    }
	    case INFO_MediaInfo: {
		MediaInfoEvent *pmvi = (MediaInfoEvent *)e;
		if (pmvi) {
		    //cout << "writing lcd" << endl;
		    //cout << "total seconds" << pmvi->m_totalSeconds << endl;
		    m_totalHours = (int32)pmvi->m_totalSeconds / 3600;
		    m_totalMinutes = ((int32)pmvi->m_totalSeconds - m_totalHours*3600) / 60;
		    m_totalSeconds = ((int32)pmvi->m_totalSeconds - m_totalHours*3600 - m_totalMinutes*60);
		    //cout << "total hours " << m_totalHours << " " << m_totalMinutes << " " << m_totalSeconds << endl;
		    m_lcdLock->Acquire(WAIT_FOREVER);
#if !LCDPROC_4
		    lcd.clear();
#endif
		    char *foo = strrchr(pmvi->m_filename,'/');
		    if (foo) foo++; else foo = pmvi->m_filename;
#if LCDPROC_4
		    char bar[128];
		    sprintf(bar,"widget_set FA songname 1 1 {%s}\n",foo);
		    sock_send_string(m_sock,bar);
		    sock_send_string(m_sock,"widget_set FA artist 1 3 {}\n");
#else
		    lcd.string(1,1,foo);
#endif
		    BlitTimeLine();
#if !LCDPROC_4		    
		    lcd.flush();
#endif
		    m_lcdLock->Release();
		    //cout << "wrote lcd" << endl;
		    //cout << "Playing: " << pmvi->m_filename << endl;
		}
		break; }
	    case INFO_MediaTimeInfo: {
		MediaTimeInfoEvent *info = (MediaTimeInfoEvent *)e;
		if ( (m_currHours != info->m_hours) || (m_currMinutes != info->m_minutes) || (m_currSeconds != info->m_seconds)) {
		    m_currHours = info->m_hours;
		    m_currMinutes = info->m_minutes;
		    m_currSeconds = info->m_seconds;
		    m_lcdLock->Acquire();
		    BlitTimeLine();
#if !LCDPROC_4
		    lcd.flush();
#endif
		    m_lcdLock->Release();
		}
		break;
	    }
	    case INFO_ID3TagInfo: {
		ID3TagEvent *ite = (ID3TagEvent *)e;
		if (ite) {
		    Id3TagInfo ti = ite->GetId3Tag();
		    if (ti.m_containsInfo) {
			m_lcdLock->Acquire(WAIT_FOREVER);
#if !LCDPROC_4
			lcd.clear();
#endif
#if LCDPROC_4
		    char bar[64];
		    sprintf(bar,"widget_set FA artist 1 1 {%s}\n",ti.m_artist);
		    sock_send_string(m_sock,bar);
		    sprintf(bar,"widget_set FA songname 1 2 {%s}\n",ti.m_songName);
		    sock_send_string(m_sock,bar);
#else
			lcd.string(1,1,ti.m_artist);
			lcd.string(1,2,ti.m_songName);
#endif
			BlitTimeLine();
#if !LCDPROC_4
			lcd.flush();
#endif
			m_lcdLock->Release();
			//cout << "Title  : " << ti.m_songName << endl;
			//cout << "Artist : " << ti.m_artist << endl;
			//cout << "Album  : " << ti.m_album << endl;
			//cout << "Year   : " << ti.m_year << endl;
			//cout << "Comment: " << ti.m_comment << endl;
		    }
		}
		break;
	    }
	    default:
		break;
	}
    }
    return 0;
}

void LcdUI::BlitTimeLine() {
    char foo[32];
    switch (m_timeType) {
	case TIME_CURR:
	    sprintf(foo,"current     %.02d:%.02d:%.02d",m_currHours, m_currMinutes, m_currSeconds);
	    break;
	case TIME_TOTAL:
	    sprintf(foo,"total       %.02d:%.02d:%.02d",m_totalHours,m_totalMinutes,m_totalSeconds);
	    break;
	case TIME_REMAIN: {
	    int32 s,m,h;
	    s = ((m_totalHours * 3600) + (m_totalMinutes * 60) + m_totalSeconds) - ((m_currHours * 3600) + (m_currMinutes * 60) + m_currSeconds);
	    h = s / 3600;
	    m = (s % 3600) / 60;
	    s = (s % 3600) % 60;
	    sprintf(foo,"remain      %.02d:%.02d:%.02d",h,m,s);
	    break; }
	default:
	    sprintf(foo,"Screwed up!!");
    }
#if LCDPROC_4
    char bar[64];
    sprintf(bar,"widget_set FA timeline 1 4 {%s}\n",foo);
    sock_send_string(m_sock,bar);
#else 
    lcd.string(1,4,foo);
#endif
}

void LcdUI::SetArgs(int argc, char **argv) {
    m_argc = argc; m_argv = argv;
}
void LcdUI::ProcessArgs() {
    char *pc = NULL;
    for(int i=1;i<m_argc;i++) {
	//cout << "Adding arg " << i << ": " << argv[i] << endl;
	pc = m_argv[i];
	if (pc[0] == '-') {
	    processSwitch(&(pc[0]));
	} else {
	    m_plm->Add(pc,0);
	}
    }
    m_plm->SetFirst();
    Event *e = new Event(CMD_Play);
    m_playerEQ->AcceptEvent(e);
}

void LcdUI::processSwitch(char *pc) {
    return;
}





