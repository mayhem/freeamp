/* $Id: playerview.cpp,v 1.1.2.2 1999/08/14 08:06:05 hiro Exp $ */

#define DEBUG 1
#include <be/support/Debug.h>
#include <be/interface/Window.h>
#include <be/interface/Bitmap.h>

#include "playerview.h"

#if DEBUG
#include <string.h>
#define REPORT_ERROR(a) fprintf( stderr, "ERROR: %s at line %d : %s\n", __FILE__, __LINE__, strerror(a) )
#else
static inline void REPORT_ERROR( int a ) {}
#endif

PlayerView::PlayerView( BBitmap* bitmap )
:	BView( BRect(0,0,0,0), "PlayerView", B_FOLLOW_NONE, B_WILL_DRAW ),
	m_bitmap( bitmap ),
	m_dragging( false )
{
	BRect	bounds;
	if ( m_bitmap )
	{
		bounds = m_bitmap->Bounds();
	}
	else
	{
		bounds.Set( 0, 0, 100, 100 );
		REPORT_ERROR( 0 );
	}
	ResizeTo( bounds.Width(), bounds.Height() );
}

PlayerView::~PlayerView()
{
	if ( m_bitmap )
	{
		delete m_bitmap;
		m_bitmap = NULL;
	}
}

void
PlayerView::AttachedToWindow( void )
{
	BView::AttachedToWindow();

	if ( LockLooper() )
	{
		BRect	bounds( Bounds() );
		Window()->ResizeTo( bounds.Width(), bounds.Height() );
		UnlockLooper();
	}
	else
	{
		REPORT_ERROR( 0 );
	}

	SetViewColor( B_TRANSPARENT_COLOR );
}

void
PlayerView::Draw( BRect updateRect )
{
	if ( m_bitmap )
	{
		MovePenTo( B_ORIGIN );
		DrawBitmap( m_bitmap );
	}
	else
	{
		MovePenTo( 10, 10 ); DrawString( "FreeAmp" );
	}
}

void
PlayerView::MouseDown( BPoint point )
{
	// Activate the window.
	Window()->Activate( true );

	// Start mouse tracking
	status_t err = SetMouseEventMask( B_POINTER_EVENTS, B_NO_POINTER_HISTORY );
	if ( err < B_NO_ERROR )
	{
		REPORT_ERROR( err );
	}
	else
	{
		// Turn on the window dragging mode
		m_dragging = true;
		m_hotSpot = point;
	}
}

void
PlayerView::MouseMoved(
					BPoint			point,
					uint32			transit,
					const BMessage*	message
					)
{
	if ( !m_dragging ) return;

	// Compute the new top-left corner of the window
	BPoint	pt = ConvertToScreen( point );
	pt.x -= m_hotSpot.x;
	pt.y -= m_hotSpot.y;
	Window()->MoveTo( pt );

	// This Sync is very important, otherwise the above BWindow::MoveTo don't
	// get sent to app_server and executed right away, causing the subsequent
	// BView::ConvertToScreen to use the wrong value for the window's framerect.
	Sync();
}

void
PlayerView::MouseUp( BPoint point )
{
	// Turn off the window dragging mode
	m_dragging = false;
	m_hotSpot = B_ORIGIN;
}
