/* $Id: playerwindow.cpp,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $ */

#include <assert.h>

#define DEBUG 1
#include <be/support/Debug.h>
#include <be/interface/Bitmap.h>

#include "playerwindow.h"
#include "playerview.h"
#include "tristatebutton.h"
#include "resourceutils.h"
#include "uiresources.h"
#include "freeamp-beos.h"

#if DEBUG
#include <string.h>
#define REPORT_ERROR(a) fprintf( stderr, "ERROR: %s at line %d : %s\n", __FILE__, __LINE__, strerror(a) )
#else
static inline void REPORT_ERROR( int a ) {}
#endif

PlayerWindow::PlayerWindow( const char* title )
:	BWindow(
			BRect(10,10,100,100),
			title,
			B_NO_BORDER_WINDOW_LOOK,
			B_NORMAL_WINDOW_FEEL,
			B_WILL_ACCEPT_FIRST_CLICK
			),
	m_target( NULL ),
	m_bitmapPlayOff( NULL ),
	m_bitmapPlayOn( NULL ),
	m_bitmapPlayGlow( NULL ),
	m_bitmapStopOff( NULL ),
	m_bitmapStopOn( NULL ),
	m_bitmapStopGlow( NULL ),
	m_isPlaying( false )
{

	PlayerView*	root = new PlayerView(
				ResourceUtils::GetBitmap(
										kBeOSUIName,
										B_RAW_TYPE,
										kResBitmapPlayer
										)
				);
	AddChild( root );

	// Place controls.

	// We own the Play/Stop button bitmaps.
	m_bitmapPlayOff  = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPlayButtonOff );
	m_bitmapPlayOn   = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPlayButtonOn );
	m_bitmapPlayGlow = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPlayButtonGlow );
	m_bitmapStopOff  = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapStopButtonOff );
	m_bitmapStopOn   = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapStopButtonOn );
	m_bitmapStopGlow = ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapStopButtonGlow );

	// Play button.
	TriStateButton*	playButton = new TriStateButton(
						BRect( 29, 15, 29, 15 ),
						"PlayStop",
						m_bitmapPlayOff,
						m_bitmapPlayOn,
						m_bitmapPlayGlow,
						false,
						new BMessage( kBeOSUIMsg_PlayStop )
						);
	root->AddChild( playButton );

	// Pause button.
	TriStateButton*	pauseButton = new TriStateButton(
						BRect( 56, 15, 29, 15 ),
						"Pause",
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPauseButtonOff ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPauseButtonOn ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPauseButtonGlow ),
						true,
						new BMessage( kBeOSUIMsg_Pause )
						);
	root->AddChild( pauseButton );

	// Prev button.
	TriStateButton*	prevButton = new TriStateButton(
						BRect( 82, 15, 29, 15 ),
						"Prev",
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPrevButtonOff ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPrevButtonOn ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapPrevButtonGlow ),
						true,
						new BMessage( kBeOSUIMsg_Prev )
						);
	root->AddChild( prevButton );

	// Next button.
	TriStateButton*	nextButton = new TriStateButton(
						BRect( 109, 15, 109, 15 ),
						"Prev",
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapNextButtonOff ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapNextButtonOn ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapNextButtonGlow ),
						true,
						new BMessage( kBeOSUIMsg_Next )
						);
	root->AddChild( nextButton );

	// Close button.
	TriStateButton*	closeButton = new TriStateButton(
						BRect( 392, 9, 392, 9 ),
						"Prev",
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapCloseButtonOff ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapCloseButtonOn ),
						ResourceUtils::GetBitmap( kBeOSUIName, B_RAW_TYPE,
												kResBitmapCloseButtonGlow ),
						true,
						new BMessage( kBeOSUIMsg_Close )
						);
	root->AddChild( closeButton );
}

PlayerWindow::~PlayerWindow()
{
	delete m_bitmapPlayOff;
	delete m_bitmapPlayOn;
	delete m_bitmapPlayGlow;
	delete m_bitmapStopOff;
	delete m_bitmapStopOn;
	delete m_bitmapStopGlow;
}

void
PlayerWindow::MessageReceived( BMessage* message )
{
	switch ( message->what )
	{
		case kBeOSUIMsg_PlayStop:
			PRINT(( "play/stop button\n" ));
			if ( m_isPlaying )
			{
				if ( m_target ) m_target->Stop();
			}
			else
			{
				if ( m_target ) m_target->Play();
			}
			break;
		case kBeOSUIMsg_Pause:
			PRINT(( "pause button\n" ));
			if ( m_target ) m_target->Pause();
			break;
		case kBeOSUIMsg_Prev:
			PRINT(( "prev button\n" ));
			if ( m_target ) m_target->PreviousMediaPiece();
			break;
		case kBeOSUIMsg_Next:
			PRINT(( "prev button\n" ));
			if ( m_target ) m_target->NextMediaPiece();
			break;
		case kBeOSUIMsg_Close:
			PRINT(( "Close button\n" ));
			if ( m_target ) m_target->QuitPlayer();
			break;
		case kBeOSUIMsg_InfoPlaying:
			PRINT(( "info playing\n" ));
			TogglePlayStop( true );
			break;
		case kBeOSUIMsg_InfoStopped:
			PRINT(( "info stopped\n" ));
			TogglePlayStop( false );
			break;
		default:
			BWindow::MessageReceived( message );
			break;
	}
}

void
PlayerWindow::SetTarget( FreeAmpUI* target )
{
	m_target = target;
}

void
PlayerWindow::TogglePlayStop( bool isPlaying )
{
	status_t err;

	m_isPlaying = isPlaying;

	TriStateButton*	b = dynamic_cast<TriStateButton*>(
							FindView( "PlayStop" )
							);
	assert( b );

	if ( m_isPlaying )
	{
		err = b->SetBitmaps(
						m_bitmapStopOff,
						m_bitmapStopOn,
						m_bitmapStopGlow,
						false
						);
	}
	else
	{
		err = b->SetBitmaps(
						m_bitmapPlayOff,
						m_bitmapPlayOn,
						m_bitmapPlayGlow,
						false
						);
	}

	if ( err < B_OK ) REPORT_ERROR( err );
}

// vi: set ts=4:
