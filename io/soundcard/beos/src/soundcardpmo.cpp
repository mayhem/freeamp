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
	
	$Id: soundcardpmo.cpp,v 1.2.2.2 1999/07/01 05:02:58 hiro Exp $
____________________________________________________________________________*/

#define DEBUG 0

/* system headers */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream.h>

/* BeOS Kits */
#include <media/SoundPlayer.h>
#include <support/Debug.h>

/* project headers */
#include <config.h>
#include "soundcardpmo.h"
#include "beosvolume.h"
#include "soundutils.h"
#include "thread.h"
#include "mutex.h"
#include "facontext.h"
#include "log.h"

LogFile*	g_Log;

const uint32 PCMBUFFERSIZE 			= 8 * 4096;
const int32 BUFFER_SIZE				= 32 * 1024;
const int32 ORIG_BUFFER_SIZE		= 32 * 1024;
const int32 OVERFLOW_SIZE			= 16 * 1024;
const int32 WRITE_TRIGGER_SIZE		= 8 * 1024;

extern "C" {

PhysicalMediaOutput* Initialize(FAContext *context)
{
	return new SoundCardPMO(context);
}

} /* extern "C" */

SoundCardPMO::SoundCardPMO( FAContext* context )
:	PhysicalMediaOutput(),
	EventBuffer( ORIG_BUFFER_SIZE, OVERFLOW_SIZE, WRITE_TRIGGER_SIZE, context ),
	m_initThread( NULL ),
	m_player( NULL ),
	m_dataSize( 0 ),
	m_eventSem( "EventSem" ),
	m_pauseLock( "pause lock" )
{
	PRINT(( "SoundCardPMO::ctor\n" ));
	m_properlyInitialized = false;

	m_outputInfo = new OutputInfo();

	m_context = context;

	m_eventBufferThread = Thread::CreateThread();
	m_eventBufferThread->Create( _EventBufferThreadHook, this );
}

SoundCardPMO::~SoundCardPMO()
{
	PRINT(( "SoundCardPMO::dtor\n" ));

	Lock();

	m_bExit = true;
	m_pWriteSem->Signal();
	m_pReadSem->Signal();
//	m_pauseMutex.Release();
	m_pauseLock.Unlock();

	PRINT(( "SoundCardPMO::~SoundCardPMO\n" ));
	if ( m_player )
	{
		PRINT(( "SoundCardPMO::~SoundCardPMO:stopping\n" ));
		m_player->Stop( false );
		PRINT(( "SoundCardPMO::~SoundCardPMO:stopped\n" ));

		delete m_player;
		m_player = NULL;
	}

	if ( m_outputInfo )
	{
		delete m_outputInfo;
		m_outputInfo = NULL;
	}

	PRINT(( "SoundCardPMO::~SoundCardPMO done\n" ));
}

VolumeManager*
SoundCardPMO::GetVolumeManager( void )
{
	return new BeOSVolumeManager();
}

Error
SoundCardPMO::SetPropManager( Properties* p )
{
	m_propManager = p;
	return kError_NoErr;
}

void
SoundCardPMO::SetVolume( int32 iVolume )
{
	PRINT(( "SoundCardPMO::SetVolume\n" ));
}

int32
SoundCardPMO::GetVolume( void )
{
	PRINT(( "SoundCardPMO::GetVolume\n" ));
	return 0;
}

int32
SoundCardPMO::GetBufferPercentage( void )
{
	PRINT(( "SoundCardPMO::GetBufferPercentage\n" ));
	return PullBuffer::GetBufferPercentage();
}

Error
SoundCardPMO::Pause( void )
{
	Error	err;
	PRINT(( "SoundCardPMO::Pause\n" ));
//	m_pauseMutex.Acquire();
	m_pauseLock.Lock();
	PRINT(( "SoundCardPMO::Pause:pause mutex acquired\n" ));

	if ( false && m_properlyInitialized )
	{
		err = Reset( true );
	}
	else
	{
		err = kError_NoErr;
	}
}

Error
SoundCardPMO::Resume( void )
{
//	m_pauseMutex.Release();
	m_pauseLock.Unlock();
	PRINT(( "SoundCardPMO::Resume\n" ));
	return kError_NoErr;
}

Error
SoundCardPMO::Break( void )
{
	PRINT(( "SoundCardPMO::Break\n" ));
	m_eventSem.Signal();
	m_bExit = true;
	PullBuffer::BreakBlocks();

	PRINT(( "SoundCardPMO::Break done\n" ));
	return kError_NoErr;
}

void
SoundCardPMO::WaitToQuit( void )
{
	PRINT(( "SoundCardPMO::WaitToQuit:**************************************\n" ));
	if ( m_eventBufferThread )
	{
		m_eventBufferThread->Join();
		delete m_eventBufferThread;
		m_eventBufferThread = NULL;
	}
	PRINT(( "SoundCardPMO::WaitToQuit:event buffer terminated\n" ));

	if ( m_player )
	{
		m_player->SetHasData( false );
		m_player->Stop( false );
	}
	PRINT(( "SoundCardPMO::WaitToQuit:sound player terminated\n" ));

}

Error
SoundCardPMO::Clear( void )
{
	PRINT(( "SoundCardPMO::Clear\n" ));
	return kError_NoErr;
}

Error
SoundCardPMO::Init( OutputInfo* info )
{
	PRINT(( "SoundCardPMO::Init\n" ));
	PRINT(( "OI: bits_per_sample: %d\n", info->bits_per_sample ));
	PRINT(( "OI: number_of_channels: %d\n", info->number_of_channels ));
	PRINT(( "OI: samples_per_second: %d\n", info->samples_per_second ));
	PRINT(( "OI: max_buffer_size: %d\n", info->max_buffer_size ));

	m_properlyInitialized = false;
	if ( !info )
	{
		info = m_outputInfo;
	}
	else
	{
		// got info, so this is the beginning..
		int32	newSize;
		Error	result;

		m_dataSize = info->max_buffer_size;

		m_context->prefs->GetOutputBufferSize( &newSize );
		PRINT(( "SoundCardPMO::Init:FIXME: beospref not done yet\n" ));
		newSize = 512;
		newSize *= 1024;
		PRINT(( "SoundCardPMO::Init:newSize = %d bytes\n", newSize ));

		// round off the buffer size to mutiples of data size.
		newSize -= newSize % m_dataSize;

		// resize the buffer...
		result = Resize( newSize, 0, m_dataSize );
		if ( IsError( result ) )
		{
			ReportError( "Internal Buffer sizing error occurred." );
			m_context->log->Error( "Resize output buffer failed" );
			return result;
		}
	}

	m_outputInfo->bits_per_sample = info->bits_per_sample;
	m_outputInfo->number_of_channels = info->number_of_channels;
	m_outputInfo->samples_per_second = info->samples_per_second;
	m_outputInfo->max_buffer_size = info->max_buffer_size;

	if ( ::get_audio_format( m_outputInfo, &m_format ) < B_NO_ERROR )
	{
		printf( "error in output info\n" );
	}

	if ( m_player )
	{
		delete m_player;
	}

	m_player = new BSoundPlayer(
							&m_format,
							"FreeAmp",
							_PlayerHook,
							_NotifierHook,
							this
							);

	if ( m_player->InitCheck() < B_NO_ERROR )
	{
		PRINT(( "SoundPlayerPMO::Init:error constructing BSOundPlayer\n" ));
		return kError_InitFailed;
	}

	printf( "Frame Rate : %f\n", m_format.frame_rate );
	printf( "Format : %x\n", (int)m_format.format );
	printf( "Channel Count : %d\n", (int)m_format.channel_count );

#if USE_DUMMY_PLAYER
	m_dummyPlayerThread = Thread::CreateThread();
	m_dummyPlayerThread->Create( _DummyPlayerHook, this );
#else
	m_player->Start();
	m_player->SetHasData( true );
#endif

	m_properlyInitialized = true;

	return kError_NoErr;
}

Error
SoundCardPMO::Reset( bool user_stop )
{
	PRINT(( "SoundCardPMO::Reset...\n" ));

#if USE_DUMMY_PLAYER
#else
	if ( !m_player ) return kError_YouScrewedUp;

	if ( m_player )
	{
		m_player->SetHasData( false );
		PRINT(( "SetHasData done\n" ));
		m_player->Stop( false );
		PRINT(( "player stop done\n" ));
	}

	if ( false &&  m_eventBufferThread )
	{
		m_eventSem.Signal();
		m_eventBufferThread->Join();
	}

	if ( user_stop )
	{
	}
	else
	{
	}
#endif

	cout << "Reset done..." << endl;
	return kError_NoErr;
}

Error
SoundCardPMO::BeginWrite( void*& pBuffer, size_t& iBytesToWrite )
{
	PRINT(( "SoundCardPMO::BeginWrite\n" ));
	return EventBuffer::BeginWrite( pBuffer, iBytesToWrite );
}

Error
SoundCardPMO::EndWrite( size_t iNumBytesWritten )
{
	PRINT(( "SoundCardPMO::EndWrite\n" ));
	return EventBuffer::EndWrite( iNumBytesWritten );
}

Error
SoundCardPMO::AcceptEvent( Event* pEvent )
{
	return EventBuffer::AcceptEvent( pEvent );
}

void
SoundCardPMO::HandleTimeInfoEvent( PMOTimeInfoEvent* pEvent )
{
	printf( "SoundCardPMO::HandleTimeInfoEvent: FIXME\n" );
}

void
SoundCardPMO::_InitThreadHook( void* arg )
{
	((SoundCardPMO*)arg)->InitThread();
}

void
SoundCardPMO::InitThread( void )
{
	Event*	event;

	PRINT(( "SoundPlayerPMO::InitThread\n" ));
	while ( !m_bExit )
	{
		// Wait until SoundPlayer gets initialized..
		if ( !m_properlyInitialized )
		{
			PRINT(( "SoundCardPMO::InitThread: waiting for init event\n" ));
			event = GetEvent();

			if ( event == NULL )
			{
				m_pReadSem->Wait();
				continue;
			}

			if ( event->Type() == PMO_Init )
			{
				PRINT(( "SoundCardPMO::InitThread:trying to init\n" ));
				if ( IsError( Init( ((PMOInitEvent*)event)->GetInfo() ) ) )
				{
					PRINT(( "SoundCardPMO::InitThread:Init error\n" ));
					delete event;
					break;
				}
				PRINT(( "SoundCardPMO::InitThread:init succeeded\n" ));
			}

			delete event;

			// this thread is only for init.
			return;
		}
		else
		{
			event = GetEvent();

			if ( event == NULL )
			{
				m_pReadSem->Wait();
				continue;
			}

			PRINT(( "SoundCardPMO::InitThread:Event received\n" ));

			m_pReadSem->Signal();

			delete event;
		}
	}
}

void
SoundCardPMO::_EventBufferThreadHook( void* arg )
{
	return ((SoundCardPMO*)arg)->EventBufferThread();
}

void
SoundCardPMO::EventBufferThread( void )
{
	while ( !m_bExit )
	{
		if ( !m_properlyInitialized )
		{
			Event* event = GetEvent();
			if ( event == NULL )
			{
				m_pReadSem->Wait();
				continue;
			}

			if ( event->Type() == PMO_Init )
			{
				if ( IsError( Init( ((PMOInitEvent*)event)->GetInfo() ) ) )
				{
					delete event;
					break;
				}
			}
			delete event;

			continue;
		}

		m_eventSem.Wait();
		PRINT(( "SoundCardPMO::EventBufferThread:event is waiting to be dispatched\n" ));

//		m_pauseMutex.Acquire();
		PRINT(( "SoundCardPMO::EventBufferThread:pause mutex acquired\n" ));
		Event*	event = GetEvent();
		if ( event == NULL )
		{
//			m_pauseMutex.Release();
		}
		else
		{
//			m_pauseMutex.Release();
			if ( event->Type() == PMO_Init )
			{
				PRINT(( "SoundCardPMO::EventBufferThread:PMO_Init recv'd\n" ));
			}
			else if ( event->Type() == PMO_Reset )
			{
				PRINT(( "SoundCardPMO::EventBufferThread:PMO_Reset recv'd\n" ));
			}
			else if ( event->Type() == PMO_Info )
			{
				PRINT(( "SoundCardPMO::EventBufferThread:PMO_Info recv'd\n" ));
			}
			else if ( event->Type() == PMO_Quit )
			{
				PRINT(( "SoundCardPMO::EventBufferThread:PMO_Quit recv'd\n" ));
				delete event;
				m_eventSem.Signal();
				break;
			}
			delete event;
		}
		m_eventSem.Signal();
	}
}

void
SoundCardPMO::_DummyPlayerHook( void* arg )
{
	return ((SoundCardPMO*)arg)->DummyPlayer();
}

void
SoundCardPMO::DummyPlayer( void )
{
	void*	bufferIn;
	size_t	bytesToCopy = WRITE_TRIGGER_SIZE;
	size_t	bytesCopied;
	Error	err;

	while ( !m_bExit )
	{
		err = BeginRead( bufferIn, bytesToCopy );
		if ( IsError( err ) )
		{
			PRINT(( "SoundCardPMO::DummyPlayer: read from the interim buffer failed(%d)\n", err ));
			bytesCopied = 0;
		}
		else
		{
			bytesCopied = bytesToCopy;
		}
		EndRead( bytesCopied );
		PRINT(( "FIXME: %d bytes read\n", bytesCopied ));
	}
}

void
SoundCardPMO::_PlayerHook(
				void*							cookie,
				void*							buffer,
				size_t							size,
				const media_raw_audio_format&	format
				)
{
	((SoundCardPMO*)cookie)->Player( buffer, size, format );
}

void
SoundCardPMO::Player(
				void*							bufferOut,
				size_t							size,
				const media_raw_audio_format&	format
				)
{
	Error	err;
	size_t	bytesToCopy;
	size_t	bytesCopied;
	void*	bufferIn;
//	bool	perfWarn = false;

	PRINT(( "SoundCardPMO::Player:entry\n" ));

	if ( format.format != m_format.format )
	{
		PRINT(( "SoundCardPMO::Player:invalid format\n" ));
		return;
	}

	bytesToCopy = size;

	if ( m_pauseLock.LockWithTimeout( 0.1e6 ) != B_OK )
	{
		return;
	}

	PRINT(( "SoundCardPMO::Player:trying to read from the buffer\n" ));
	err = BeginRead( bufferIn, bytesToCopy );
	while ( err == kError_EventPending )
	{
		Event*	event = PeekEvent();
		switch ( event->Type() )
		{
		case PMO_Init:
			PRINT(( "SoundCardPMO::Player: PMO_Init recv'd\n" ));
			m_eventSem.Signal();
			m_eventSem.Wait();
			break;
		case PMO_Reset:
			PRINT(( "SoundCardPMO::Player: PMO_Reset recv'd\n" ));
			m_eventSem.Signal();
			m_eventSem.Wait();
			break;
		case PMO_Info:
			PRINT(( "SoundCardPMO::Player: PMO_Info recv'd\n" ));
			event = GetEvent();
			delete event;
			break;
		case PMO_Quit:
			PRINT(( "SoundCardPMO::Player: PMO_Quit recv'd\n" ));
			m_eventSem.Signal();
			m_eventSem.Wait();
			break;
		}
		bytesToCopy = size;
		err = BeginRead( bufferIn, bytesToCopy );
	}

	if ( IsError( err ) )
	{
		PRINT(( "SoundCardPMO::Player: error reading from the interim buffer(%d)\n", err ));
		bytesCopied = 0;
	}
	else
	{
		if ( bytesToCopy < size )
		{
			PRINT(( "SoundCardPMO::Player: end of data?\n" ));
		}
		memcpy( bufferOut, bufferIn, bytesToCopy );
		bytesCopied = bytesToCopy;
	}
	EndRead( bytesCopied );
	m_pauseLock.Unlock();
	PRINT(( "SoundCardPMO::Player: %d bytes copied\n", bytesCopied ));

	return;
}

void
SoundCardPMO::_NotifierHook(
				void*						cookie,
				BSoundPlayer::sound_player_notification
											what,
				...
				)
{
	((SoundCardPMO*)cookie)->Notifier( what );
}

void
SoundCardPMO::Notifier( BSoundPlayer::sound_player_notification what )
{
	switch ( what )
	{
	case BSoundPlayer::B_STARTED:
		PRINT(( "Notifier: SoundPlayer started\n" ));
		break;
	case BSoundPlayer::B_STOPPED:
		PRINT(( "Notifier: SoundPlayer stoped\n" ));
		break;
	case BSoundPlayer::B_SOUND_DONE:
		PRINT(( "Notifier: SoundPlayer sound done\n" ));
		break;
	default:
		PRINT(( "Notifier: unknown event is reported\n" ));
		break;
	}
}
// vi: set ts=4:
