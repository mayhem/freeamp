/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player
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
	
	$Id: soundcardpmo.h,v 1.2.2.1 1999/06/29 03:48:48 hiro Exp $
____________________________________________________________________________*/


#ifndef _SOUNDCARDPMO_H_
#define _SOUNDCARDPMO_H_

/* system headers */
#include <stdlib.h>
#include <stdio.h>

/* BeOS Kits */
#include <media/MediaDefs.h>
#include <media/SoundPlayer.h>

/* project headers */
#include <config.h>
#include "mutex.h"
#include "pmo.h"
#include "pmoevent.h"
#include "pullbuffer.h"
#include "eventbuffer.h"

#define BIT_SELECT  0x1f
#define SLEEPTIME   256
#define USE_DUMMY_PLAYER 0

class Thread;
class FAContext;
class VolumeManager;

class SoundCardPMO : public PhysicalMediaOutput, public EventBuffer
{
public:
							SoundCardPMO( FAContext* context );
	virtual					~SoundCardPMO();
	virtual Error			Init( OutputInfo* info );
	virtual VolumeManager*	GetVolumeManager( void );
	virtual Error			Pause( void );
	virtual Error 			Resume( void );
	virtual Error			Break( void );
	virtual void			WaitToQuit( void );
	virtual Error			Clear( void );
	virtual Error			SetPropManager( Properties* p );
	virtual void			SetVolume( int32 iVolume );
	virtual int32			GetVolume( void );
	virtual int32			GetBufferPercentage( void );

	virtual Error			BeginWrite( void*& pBuffer, size_t& iBytesToWrite );
	virtual Error			EndWrite( size_t iNumBytesWritten );
	virtual Error			AcceptEvent( Event* pEvent );

protected:
	void					Lock( void );
	void					Unlock( void );
	FAContext *				m_context;

private:
	virtual Error			Reset( bool user_stop );
	void					HandleTimeInfoEvent( PMOTimeInfoEvent* pEvent );

	static void				_InitThreadHook( void* arg );
	void					InitThread( void );

	static void				_EventBufferThreadHook( void* arg );
	void					EventBufferThread( void );

	static void				_DummyPlayerHook( void* arg );
	void					DummyPlayer( void );

	static void				_PlayerHook(
								void*							cookie,
								void*							buffer,
								size_t							size,
								const media_raw_audio_format&	format
								);
	void					Player(
								void*							buffer,
								size_t							size,
								const media_raw_audio_format&	format
								);
	static void				_NotifierHook(
								void*							cookie,
								BSoundPlayer::sound_player_notification
																what,
								...
								);
	void					Notifier(
								BSoundPlayer::sound_player_notification
																what
								);

	Thread*					m_initThread;
	Thread*					m_eventBufferThread;
	Thread*					m_dummyPlayerThread;
	Properties *			m_propManager;
	bool					m_properlyInitialized;
	uint32					channels;
	OutputInfo *			m_outputInfo;
	media_raw_audio_format	m_format;
	BSoundPlayer *			m_player;
	Mutex					m_lock;
	Mutex					m_pauseMutex;
	size_t					m_dataSize;
	Semaphore				m_eventSem;
};

inline void
SoundCardPMO::Lock( void )
{
	m_lock.Acquire();
}

inline void
SoundCardPMO::Unlock( void )
{
	m_lock.Release();
}

#endif /* _SOUNDCARDPMO_H_ */
