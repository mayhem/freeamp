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
	
	$Id: freeamp-beos.cpp,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $
____________________________________________________________________________*/

#include <iostream.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>
#include <termios.h>
#include <signal.h>


#include "config.h"
#include "freeamp-beos.h"
#include "event.h"
#include "playlist.h"
#include "thread.h"
#include "eventdata.h"

#include "playerwindow.h"

#define stdinfd 0

extern "C" {

UserInterface *Initialize(FAContext *context) {
    return new FreeAmpUI(context);
}

	   }
static struct termios normalTTY;
static struct termios rawTTY;
#if __BEOS__
int getKey() { return 1; }
#else
int getKey() {
    fd_set rdfs;

    FD_ZERO(&rdfs);
    FD_SET(stdinfd, &rdfs);
    if (select (stdinfd+1,&rdfs,NULL,NULL,NULL) == 1) {
	if (FD_ISSET(stdinfd, &rdfs)) return 1;
    }
    return 0;
}
#endif

void FreeAmpUI::SetPlayListManager(PlayListManager *plm) {
    m_plm = plm;
}

FreeAmpUI::FreeAmpUI(FAContext *context)
:	m_playerWindow( NULL )
{
    m_context = context;
    m_plm = NULL;
    m_playerEQ = NULL;
    m_lastIndexPlayed = -1;
    m_id3InfoPrinted = false;

    keyboardListenThread = NULL;
}

Error FreeAmpUI::Init(int32 startup_level)
{
    if ((m_startupLevel = startup_level) == PRIMARY_UI) {
	tcgetattr(stdinfd, &::normalTTY);
	::rawTTY = ::normalTTY;
	::rawTTY.c_lflag &= ~ICANON;
	::rawTTY.c_lflag &= ~ECHO;
	tcsetattr(stdinfd, TCSANOW, &rawTTY);
	
	
	keyboardListenThread = Thread::CreateThread();
	keyboardListenThread->Create(FreeAmpUI::keyboardServiceFunction,this);
	
	cout << endl << "Command Line Interface" << endl << endl;
	cout << " * q    Quit" << endl;
	cout << " * +/=  Next Song" << endl;
	cout << " * -    Prev Song" << endl;
	cout << " * p    Pause / UnPause" << endl;
	cout << " * s    Shuffle" << endl << endl;
	ProcessArgs();
    }

	// Put the player window.
	m_playerWindow = new PlayerWindow( "FreeAmp" );
	m_playerWindow->SetTarget( this );
	m_playerWindow->Show();

    return kError_NoErr;
}

FreeAmpUI::~FreeAmpUI()
{
    if (m_startupLevel == PRIMARY_UI) {
tcsetattr(stdinfd, TCSANOW, &normalTTY);
    }
    //cout << "FreeAmpUI: begin deleted..." << endl;
    if (keyboardListenThread) {
        keyboardListenThread->Destroy();
        delete keyboardListenThread;
        keyboardListenThread = NULL;
    }

	// Player window
	if ( m_playerWindow )
	{
		m_playerWindow->Lock();
		m_playerWindow->Quit();	// blocks until everything's kosher.
		m_playerWindow = NULL;
	}
}

void
FreeAmpUI::keyboardServiceFunction(void *pclcio)
{
    FreeAmpUI *pMe = (FreeAmpUI *)pclcio;
    //char *pkey = new char[1];
    char chr;
    //size_t rtn;
    //int fn = STDIN_FILENO;
    for (;;) {
	::getKey();
	read(stdinfd,&chr,1);
	switch (chr) {
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
		    pMe->m_plm->SetShuffle(SHUFFLE_RANDOM);
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

}

int32
FreeAmpUI::AcceptEvent(Event *e)
{
    if (!e) return 0;

	//cout << "FreeAmpUI: processing event " << e->getEvent() << endl;
	switch (e->Type())
	{
		case INFO_Playing:
			m_playerWindow->PostMessage( kBeOSUIMsg_InfoPlaying );
			break;
		case INFO_Stopped:
			m_playerWindow->PostMessage( kBeOSUIMsg_InfoStopped );
			break;
		case INFO_PlayListDonePlay: {
			Event *e = new Event(CMD_QuitPlayer);
			m_playerEQ->AcceptEvent(e);
			break; }
	    case CMD_Cleanup: {
			Event *e = new Event(INFO_ReadyToDieUI);
			m_playerEQ->AcceptEvent(e);
			break; }
	    case INFO_MediaInfo: {
			MediaInfoEvent *pmvi = (MediaInfoEvent *)e;
			if (pmvi && m_lastIndexPlayed != pmvi->m_indexOfSong) {
				m_lastIndexPlayed = pmvi->m_indexOfSong;
				m_id3InfoPrinted = false;
				cout << "Playing: " << pmvi->m_filename << endl;
			}
			break; }
	    case INFO_ID3TagInfo: {
			ID3TagEvent *ite = (ID3TagEvent *)e;
			if (ite)
			{
				Id3TagInfo ti = ite->GetId3Tag();
				if (ti.m_containsInfo && !m_id3InfoPrinted)
				{
					m_id3InfoPrinted = true;
					cout << "Title  : " << ti.m_songName << endl;
					cout << "Artist : " << ti.m_artist << endl;
					cout << "Album  : " << ti.m_album << endl;
					cout << "Year   : " << ti.m_year << endl;
					cout << "Comment: " << ti.m_comment << endl;
				}
			}
			break; }
	    default:
			break;
	}
    return 0;
}

void
FreeAmpUI::SetArgs(int32 argc, char **argv)
{
    m_argc = argc; m_argv = argv;
}

void
FreeAmpUI::ProcessArgs()
{
    char *pc = NULL;
    for(int i=1;i<m_argc;i++)
	{
		//cout << "Adding arg " << i << ": " << argv[i] << endl;
		pc = m_argv[i];
		if (pc[0] == '-')
		{
			processSwitch(&(pc[0]));
		}
		else
		{
			m_plm->AddItem(pc,0);
		}
    }
    m_plm->SetFirst();
    Event *e = new Event(CMD_Play);
    m_playerEQ->AcceptEvent(e);
}

void
FreeAmpUI::processSwitch(char *pc)
{
    return;
}

void
FreeAmpUI::Play( void )
{
	Event *e = new Event( CMD_Play );
	m_playerEQ->AcceptEvent( e );
}

void
FreeAmpUI::Stop( void )
{
	Event *e = new Event( CMD_Stop );
	m_playerEQ->AcceptEvent( e );
}

void
FreeAmpUI::Pause( void )
{
	Event *e = new Event( CMD_TogglePause );
	m_playerEQ->AcceptEvent( e );
}

void
FreeAmpUI::QuitPlayer( void )
{
	Event *e = new Event(CMD_QuitPlayer);
	m_playerEQ->AcceptEvent(e);
}

void
FreeAmpUI::NextMediaPiece( void )
{
	Event *e = new Event(CMD_NextMediaPiece);
	m_playerEQ->AcceptEvent(e);
}

void
FreeAmpUI::PreviousMediaPiece( void )
{
	Event *e = new Event(CMD_PrevMediaPiece);
	m_playerEQ->AcceptEvent(e);
}
