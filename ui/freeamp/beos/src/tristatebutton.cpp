/* $Id: tristatebutton.cpp,v 1.1.2.2 1999/08/14 08:06:05 hiro Exp $ */

#define DEBUG 1
#include <be/support/Debug.h>
#include <be/interface/Bitmap.h>
#include "tristatebutton.h"

#if DEBUG
#include <string.h>
#define REPORT_ERROR(a) fprintf( stderr, "ERROR: %s at line %d : %s\n", __FILE__, __LINE__, strerror(a) )
#else
static inline void REPORT_ERROR( int a ) {}
#endif

TriStateButton::TriStateButton(
							BRect		frame,
							const char*	name,
							BBitmap*	offBitmap,
							BBitmap*	onBitmap,
							BBitmap*	glowBitmap,
							bool		ownsBitmaps,
							BMessage*	message
							)
:	BControl( frame, name, name, message, B_FOLLOW_NONE, B_WILL_DRAW ),
	m_offBitmap( offBitmap ),
	m_onBitmap( onBitmap ),
	m_glowBitmap( glowBitmap ),
	m_ownsBitmaps( ownsBitmaps ),
	m_state( TriStateButton::OFF ),
	m_mouseDown( false )
{
	// Find the largest bound rect that encloses the all three bitmaps.
	BRect	bounds;
	if ( m_offBitmap && m_onBitmap && m_glowBitmap )
	{
		bounds = m_offBitmap->Bounds();
		if ( m_onBitmap->Bounds().Contains( bounds ) )
		{
			bounds = m_onBitmap->Bounds();
		}
		if ( m_glowBitmap->Bounds().Contains( bounds ) )
		{
			bounds = m_glowBitmap->Bounds();
		}
	}

	// then resize to fit the bitmaps
	ResizeTo( bounds.Width(), bounds.Height() );
}

TriStateButton::~TriStateButton()
{
	CleanBitmaps();
}

void
TriStateButton::AttachedToWindow( void )
{
	BControl::AttachedToWindow();
	SetViewColor( B_TRANSPARENT_COLOR );
}

void
TriStateButton::Draw( BRect updateRect )
{
	if ( m_state == TriStateButton::OFF )
	{
		if ( m_offBitmap ) DrawBitmap( m_offBitmap );
	}
	else if ( m_state == TriStateButton::ON )
	{
		if ( m_onBitmap ) DrawBitmap( m_onBitmap );
	}
	else
	{
		if ( m_glowBitmap ) DrawBitmap( m_glowBitmap );
	}
}

void
TriStateButton::MouseDown( BPoint point )
{
	// We need to keep track of the mouse events happening outside our
	// bound rect, to keep us notified of mouseup event outside the bound
	// rect. See the comment below too.
	status_t err = SetMouseEventMask( B_POINTER_EVENTS );
	if ( err < B_NO_ERROR )
	{
		REPORT_ERROR( err );
		return;
	}

	// MouseDown state must be remembered to handle the case where the user
	// moved the pointer outside the boundary and then back inside again
	// while pressing the button.
	m_mouseDown = true;

	m_state = TriStateButton::ON;
	Invalidate();
}

void
TriStateButton::MouseMoved(
						BPoint			point,
						uint32			transit,
						const BMessage*	message
						)
{
	if ( transit == B_EXITED_VIEW )
	{
		m_state = TriStateButton::OFF;
		Invalidate();
	}
	else if ( transit == B_ENTERED_VIEW ||
			( transit == B_INSIDE_VIEW && m_state == TriStateButton::OFF ) )
	{
		if ( m_mouseDown )
		{
			m_state = TriStateButton::ON;
			Invalidate();
		}
		else
		{
			m_state = TriStateButton::GLOW;
			Invalidate();
		}
	}
}

void
TriStateButton::MouseUp( BPoint point )
{
	m_mouseDown = false;

	if ( m_state == TriStateButton::ON )
	{
		// m_state being ON means the mouseup event happen within the bound
		// rect, so we need to invoke.
		Invoke();
		m_state = TriStateButton::OFF;
		Invalidate();
	}
}

status_t
TriStateButton::SetBitmaps(
						BBitmap*	offBitmap,
						BBitmap*	onBitmap,
						BBitmap*	glowBitmap,
						bool		ownsBitmaps
						)
{
	status_t	err = B_NO_ERROR;

	if ( Looper() && ( err = LockLooperWithTimeout( 1000000 ) ) < B_OK )
	{
		REPORT_ERROR( err );
		return err;
	}

	if ( ( err = CleanBitmaps() ) < B_OK )
	{
		REPORT_ERROR( err );
		return err;
	}

	m_offBitmap  = offBitmap;
	m_onBitmap   = onBitmap;
	m_glowBitmap = glowBitmap;

	if ( Looper() ) UnlockLooper();

	// Reflect the latest bitmaps.
	Invalidate();

	return err;
}

status_t
TriStateButton::CleanBitmaps( void )
{
	status_t	err = B_NO_ERROR;

	if ( Looper() && ( err = LockLooperWithTimeout( 1000000 ) ) < B_OK )
	{
		REPORT_ERROR( err );
		return err;
	}

	if ( m_ownsBitmaps )
	{
		if ( m_offBitmap )
		{
			delete m_offBitmap;
			m_offBitmap = NULL;
		}
		if ( m_onBitmap )
		{
			delete m_onBitmap;
			m_onBitmap = NULL;
		}
		if ( m_glowBitmap )
		{
			delete m_glowBitmap;
			m_glowBitmap = NULL;
		}
	}

	if ( Looper() ) UnlockLooper();

	return err;
}

// vi: set ts=4:
