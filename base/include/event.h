
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
	
	$Id: event.h,v 1.11 1998/10/27 21:07:49 jdw Exp $
____________________________________________________________________________*/

// event.h

#ifndef _EVENT_H_
#define _EVENT_H_

#include "config.h"

class Event {

 public:
    Event(int32 c) { m_type = c; }

    virtual ~Event() {}
    int32 Type() { return m_type; }

 protected:
    Event() {}
    int32 m_type;
 
};

class EventQueue {
 public:
    virtual int32 AcceptEvent(Event *) = 0;
};


#define CMD_Stop                1  // stop current play  (no arg)
#define CMD_Play                2  // Play current media piece from beginning (no arg)
#define CMD_NextMediaPiece      3  // set pointer in playlist to next mediapiece (no arg)
#define CMD_PrevMediaPiece      4  // set pointer in playlist to prev mediapiece (no arg)
#define CMD_Pause               5  // pause current play (no arg)
#define CMD_SetPlaylist         6  // sets current playlist.  (arg is *PlayList)
#define CMD_QuitPlayer          7  // tells player to quit (no arg)
#define CMD_Cleanup             8  // player tells modules to cleanup and get ready for termination (no arg)
//#define CMD_Terminate           9  // is sent by player to COOs, and the DummyCOO makes the main thread delete player and exit (no arg)
#define INFO_ReadyToDieUI      10 // sent by CIO to player notifying it that their cleanup has completed. (if arg !null, it is a ptr to this module, it wants to be deleted)
#define INFO_PlayListDonePlay   11 // sent by player when the playlist has been exhausted (no arg)
#define INFO_DoneOutputting     12 // sent by PMO (or LMC controlling PMO) to Player when its done outputing (i.e. playing is done)
#define CMD_KillEventThread     13 // sent by player to various modules so they kill their event threads before deletion (no arg)
#define CMD_StartRead           14 // sent by player to PMI to start/continue reading bytes from source to its output buffer (no arg)
#define CMD_StopRead            15 // sent by player to PMI to stop reading bytes from source to its output buffer (no arg)
#define CMD_ResetRead           16 // sent by player to PMI to set read pointer back to beginning (no arg)
#define CMD_SeekRead            17 // sent to PMI to tell it to reset read stream to a particular point (arg = that point)
#define INFO_MediaInfo          18 // info about media title, length, etc... (arg = MediaVitalInfo)
#define INFO_MediaTimeInfo      19 // info about current time during play, etc (arg = MediaTimePositionInfo)
#define INFO_Stopped            20 // sent by player to COOs when it stops playing the current song (no arg)
#define INFO_Paused             21 // sent by player to COOs when it pauses playing the current song (no arg)
#define CMD_UnPause             22 // sent by CIO to player to tell it to unpause current song.  Note: a play causes the current song to be played from beginning (no arg)
#define CMD_TogglePause         24 // sent by CIO to player to change the boolean state Paused (no arg)
#define INFO_Playing            26 // sent by player to COO to say that it is beginning to play a song
#define CMD_ChangePosition      27 // sent by CIO to player to change the position in the song to decode from (arg = frame position)
#define INFO_LMCError           28 // sent by LMC to player to signal an error condition in the decoder
#endif // _EVENT_H_










