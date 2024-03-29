/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic
   Portions Copyright (C) 1999 Hiromasa Kato

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

   $Id: BeOSWindow.cpp,v 1.11 2000/07/12 20:10:51 hiro Exp $
____________________________________________________________________________*/ 

#define DEBUG 0

#include <be/support/Debug.h>
#include <be/app/AppDefs.h>
#include <Screen.h>
#include "Theme.h"
#include "BeOSWindow.h"
#include "BeOSCanvas.h"
#include "MainWindow.h"

#define CHECK_POINT CHECK_POINT_MSG("")
#define CHECK_POINT_MSG(a) PRINT(( "File %s Line %d: %s\n", __FILE__, __LINE__, a ))

BeOSWindow::BeOSWindow( Theme* pTheme, string& oName )
:   Window( pTheme, oName ),
    m_mainWindow( NULL ),
    m_canvasView( NULL )
{
    CHECK_POINT_MSG( "BeOSWindow ctor" );
    if ( m_bIsVulcanMindMeldHost ) { PRINT(( "and i am the host\n" )); }
    m_pCanvas = new BeOSCanvas( this );
}

BeOSWindow::~BeOSWindow()
{
    CHECK_POINT_MSG( "~BeOSWindow" );

    if ( false && m_bIsVulcanMindMeldHost )
    {
        delete m_pCanvas;
        m_pCanvas = NULL;
    }
}

Error
BeOSWindow::VulcanMindMeld( Window* other )
{
    Rect rect;
    bool windowAlreadyRunning = false;

    CHECK_POINT_MSG( "VulcanMindMeld" );

    Error err = Window::VulcanMindMeld( other );
    if ( IsError( err ) )
    {
        CHECK_POINT_MSG( "VulcanMindMeld error" );
        return err;
    }

    // by now, canvas is set to new one.

    if ( !m_mainWindow )
    {
        m_mainWindow = new MainWindow( BRect(0,0,0,0), m_oName.c_str(), this );
    }
    else
    {
        windowAlreadyRunning = true;
        assert( m_mainWindow->Lock() );
        m_mainWindow->RemoveChild( m_mainWindow->ChildAt( 0 ) );
        m_mainWindow->Unlock();
    }

    // make myself parent of the canvas
    ((BeOSCanvas*)GetCanvas())->SetParent( this );

    // set the root view
    m_canvasView = ((BeOSCanvas*)GetCanvas())->GetBView();
    assert( m_canvasView );
    assert( m_mainWindow->Lock() );
    m_mainWindow->AddChild( m_canvasView );
    m_mainWindow->Unlock();

    GetCanvas()->GetBackgroundRect( rect );
    m_mainWindow->ResizeTo( rect.x2 - rect.x1 - 1, rect.y2 - rect.y1 - 1 );

    if ( !windowAlreadyRunning )
    {
        m_mainWindow->Run();
    }

    return kError_NoErr;
}

Error
BeOSWindow::Run( Pos& oWindowPos )
{
    CHECK_POINT_MSG( "Run" );

    Rect rect;
    GetCanvas()->GetBackgroundRect( rect );
    BRect brect( rect.x1, rect.y1, rect.x2 - 1, rect.y2 - 1 );
    brect.OffsetTo( oWindowPos.x, oWindowPos.y );
    m_mainWindow->Show();
    m_mainWindow->MoveTo( brect.left, brect.top );
    m_mainWindow->ResizeTo( brect.Width(), brect.Height() );
    m_mainWindow->Sync();

    GetCanvas()->Update();

    Init();

    m_mainWindow->WaitForQuit( &brect );
    oWindowPos.x = int(brect.left);
    oWindowPos.y = int(brect.top);

    return kError_NoErr;
}

Error
BeOSWindow::Close( void )
{
    CHECK_POINT_MSG( "Close" );
    m_mainWindow->PostMessage( B_QUIT_REQUESTED );

    return kError_NoErr;
}

Error
BeOSWindow::Show( void )
{
    CHECK_POINT_MSG( "Show" );
    m_mainWindow->Show();

    return kError_NoErr;
}

Error
BeOSWindow::Hide( void )
{
    CHECK_POINT_MSG( "Hide" );
    m_mainWindow->Hide();

    return kError_NoErr;
}

Error
BeOSWindow::Enable( void )
{
    CHECK_POINT_MSG( "Enable" );
    return kError_NoErr;
}

Error
BeOSWindow::Disable( void )
{
    CHECK_POINT_MSG( "Disable" );
    return kError_NoErr;
}

Error
BeOSWindow::SetTitle( string& oTitle )
{
    CHECK_POINT_MSG( "SetTitle" );
    m_mainWindow->SetTitle(oTitle.c_str());
    return kError_NoErr;
}

Error
BeOSWindow::CaptureMouse( bool bCapture )
{
    CHECK_POINT_MSG( "CaptureMouse" );

    // currently mouse tracking outside the window is turned on
    // in the CanvasView::MouseDown thru SetMouseEventMask.

    if ( bCapture )
    {
    }
    else
    {
    }

    return kError_NoErr;
}

Error
BeOSWindow::HideMouse( bool bHide )
{
    CHECK_POINT_MSG( "HideMouse" );
    return kError_NoErr;
}

Error
BeOSWindow::Minimize( void )
{
    CHECK_POINT_MSG( "Minimize" );
    m_mainWindow->Minimize(true);
    return kError_NoErr;
}

Error
BeOSWindow::Restore( void )
{
    CHECK_POINT_MSG( "Restore" );
    m_mainWindow->Minimize(false);
    return kError_NoErr;
}

#if 0
bool
BeOSWindow::LButtonDown( void )
{
    CHECK_POINT;
    BPoint p;
    uint32 buttons;

    if ( !m_mainWindow ) return false;

    m_mainWindow->Lock();
    m_canvasView->GetMouse( &p, &buttons, false );
    m_mainWindow->Unlock();

    return ( buttons & B_PRIMARY_MOUSE_BUTTON );
}

Error
BeOSWindow::GetDesktopSize( int& x, int& y )
{
    BScreen screen;
    x = screen.Frame().IntegerWidth() + 1;
    x = screen.Frame().IntegerHeight() + 1;

    return kError_NoErr;
}
#endif

bool  
BeOSWindow::LButtonDown(void)
{
	BPoint pt;
	uint32 buttons = 0;
 	m_canvasView->GetMouse(&pt, &buttons );
 	
	return (buttons & B_PRIMARY_MOUSE_BUTTON);
}

Error
BeOSWindow::GetDesktopSize(int32 &iX, int32 &iY)
{
	BScreen s;
	BRect r = s.Frame();
	
	iX = (int)r.Width();
	iY = (int)r.Height();
	
	return kError_NoErr;
}

void
BeOSWindow::BringWindowToFront( void )
{
    m_mainWindow->Activate( true );
}

void
BeOSWindow::HandleMouseLButtonDown( Pos& oPos )
{
    Window::HandleMouseLButtonDown( oPos );
}

void
BeOSWindow::HandleMouseLButtonUp( Pos& oPos )
{
    Window::HandleMouseLButtonUp( oPos );
}

Error
BeOSWindow::SetMousePos( Pos& oMousePos )
{
    CHECK_POINT_MSG( "SetMousePos NOT SUPPORTED!!" );
    return kError_NoErr;
}

Error
BeOSWindow::GetMousePos( Pos& oMousePos )
{
    CHECK_POINT_MSG( "GetMousePos" );
    BPoint p;
    uint32 buttons;

    if ( !m_mainWindow ) return kError_NullValueInvalid;

    m_mainWindow->Lock();
    m_canvasView->GetMouse( &p, &buttons, false );
    m_mainWindow->Unlock();

    oMousePos.x = int( p.x );
    oMousePos.y = int( p.y );

    CHECK_POINT_MSG( "GetMousePos done" );
    return kError_NoErr;
}

Error
BeOSWindow::SetWindowPosition( Rect& oWindowRect )
{

    if ( !m_mainWindow ) return kError_NullValueInvalid;

    m_mainWindow->MoveTo( float(oWindowRect.x1), float(oWindowRect.y1) );
    m_mainWindow->ResizeTo( float(oWindowRect.Width()),
                            float(oWindowRect.Height()) );
    if ( m_canvasView )
    {
        m_canvasView->ResizeTo( float( oWindowRect.Width() ),
                                float( oWindowRect.Height() ) );
    }
    m_mainWindow->Sync();

    return kError_NoErr;
}

Error
BeOSWindow::GetWindowPosition( Rect& oWindowRect )
{
    if ( !m_mainWindow ) return kError_NullValueInvalid;

    m_mainWindow->Lock();
    BRect frame = m_mainWindow->Frame();
    m_mainWindow->Unlock();
    oWindowRect.x1 = int( frame.left );
    oWindowRect.y1 = int( frame.top );
    oWindowRect.x2 = int( frame.right );
    oWindowRect.y2 = int( frame.bottom );

    return kError_NoErr;
}

BWindow*
BeOSWindow::GetBWindow( void )
{
    return m_mainWindow;
}

// vi: set ts=4:
