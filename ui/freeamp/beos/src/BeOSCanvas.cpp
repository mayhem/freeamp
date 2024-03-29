/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic

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

   $Id: BeOSCanvas.cpp,v 1.11 2000/07/12 20:10:51 hiro Exp $
____________________________________________________________________________*/ 

#include "BeOSCanvas.h"
#include "BeOSBitmap.h"
#include "CanvasView.h"
#define DEBUG 0
#include <be/support/Debug.h>
#include <be/interface/Bitmap.h>
#include <be/interface/Region.h>
#include <assert.h>
#include <string>

#define CHECK_POINT CHECK_POINT_MSG("")
#define CHECK_POINT_MSG(a) PRINT(( "File %s Line %d, %x: %s\n", __FILE__, __LINE__, this, a ))

BeOSCanvas::BeOSCanvas( BeOSWindow* pParent )
:   Canvas(),
    m_pParent( pParent ),
    m_pBufferBitmap( NULL ),
    m_canvasView( NULL ),
    m_initialized( false )
{
}

BeOSCanvas::~BeOSCanvas()
{
    delete m_pBufferBitmap;
}

void
BeOSCanvas::Init( void )
{
    if ( m_initialized ) return;

    Rect destRect;

    m_canvasView = new CanvasView(
                        m_pParent,
                        BRect( 0, 0, m_oBGRect.Width(), m_oBGRect.Height() ),
                        "CanvasView",
                        B_FOLLOW_NONE,
                        B_WILL_DRAW
                        );

    InitBufferBitmap();

    m_initialized = true;
}

void
BeOSCanvas::Erase( Rect& oPaintRect )
{
    if ( m_pBufferBitmap )
    {
        m_pBufferBitmap->MaskBlitRect( m_pBGBitmap, oPaintRect, oPaintRect );
    }
}

// This function returns the number of pixels of the text that
// were clipped if the text does not fit into the clipping rect.
// If the text all fit, it returns 0.
int
BeOSCanvas::RenderText( int iFontHeight, Rect& oClipRect,
                        string& oText, AlignEnum eAlign,
                        Font* pFont, const Color& oColor,
                        bool bBold, bool bItalic, bool bUnderline )
{
    Erase( oClipRect );

    BView* v = m_pBufferBitmap->OffscreenView();
    if ( !v ) return 0;

    BBitmap* bitmap = m_pBufferBitmap->GetBBitmap();
    assert( bitmap );

    BFont font;
    font_height fontHeight;
    BRect clipRect( float(oClipRect.x1), float(oClipRect.y1),
                    float(oClipRect.x2-1), float(oClipRect.y2-1) );
    BRegion clipRegion;
    clipRegion.Set( clipRect );

    if ( !bitmap->Lock() )
    {
        puts( "lock failed" );
        return 0;
    }

    v->ConstrainClippingRegion( &clipRegion );
    v->SetDrawingMode( B_OP_OVER );
    if ( bBold )
    {
        v->SetFont( be_bold_font );
    }
    else
    {
        v->SetFont( be_plain_font );
    }
    v->SetFontSize( (float)iFontHeight - 1 );
    v->GetFont( &font );
    font.GetHeight( &fontHeight );
    
    float width = v->StringWidth(oText.c_str(), oText.size());
    
    if(eAlign == eCenter)
        v->MovePenTo( float(oClipRect.x1) +
                      (float(oClipRect.x2 - oClipRect.x1) - width)/2,
                      float(oClipRect.y2-fontHeight.descent) );	
    else if (eAlign == eRight)
        v->MovePenTo( float(oClipRect.x2) - width,
                      float(oClipRect.y2-fontHeight.descent) );
    else
        v->MovePenTo( float(oClipRect.x1),
                      float(oClipRect.y2-fontHeight.descent) );

    v->DrawString( oText.c_str() );
    v->Sync();

    bitmap->Unlock();

    Invalidate( oClipRect );

    return (width < oClipRect.Width()) ? 0 : int(width - oClipRect.Width());
}

int
BeOSCanvas::RenderOffsetText( int iFontHeight, Rect& oClipRect,
                              string& oText, int iOffset,
                              Font* pFont, const Color& oColor,
                              bool bBold, bool bItalic,
                              bool bUnderline )
{
    Erase( oClipRect );

    BView* v = m_pBufferBitmap->OffscreenView();
    if ( !v ) return 0;

    BBitmap* bitmap = m_pBufferBitmap->GetBBitmap();

    BFont font;
    font_height fontHeight;
    BRect clipRect( float(oClipRect.x1), float(oClipRect.y1),
                    float(oClipRect.x2-1), float(oClipRect.y2-1) );
    BRegion clipRegion;
    clipRegion.Set( clipRect );

    if ( !bitmap->Lock() )
    {
        puts( "Lock Failed" );
        return 0;
    }

    v->ConstrainClippingRegion( &clipRegion );
    if ( bBold )
    {
        v->SetFont( be_bold_font );
    }
    else
    {
        v->SetFont( be_plain_font );
    }
    v->SetFontSize( (float)iFontHeight - 1 );
    v->GetFont( &font );
    font.GetHeight( &fontHeight );

    float width = v->StringWidth(oText.c_str(), oText.size());
    width += iMarqueeSpacer;

    if ( iOffset > width )
    {
        bitmap->Unlock();
        return int( width ) - iOffset;
    }

    v->MovePenTo( float(oClipRect.x1 - iOffset),
                  float(oClipRect.y2 - fontHeight.descent) );
    v->DrawString( oText.c_str() );
    int ret = int( width ) - iOffset - oClipRect.Width();
    if ( ret < 0 )
    {
        v->MovePenTo( float(oClipRect.x1 - iOffset + width),
                      float(oClipRect.y2 - fontHeight.descent) );
        v->DrawString( oText.c_str() );
    }

    v->Sync();
    bitmap->Unlock();

    Invalidate( oClipRect );

    return MAX( 0, ret );
}

Error
BeOSCanvas::Invalidate( Rect& oRect )
{
    if ( m_canvasView->Window() )
    {
        if ( m_canvasView->LockLooper() )
        {
            m_canvasView->Invalidate();
            m_canvasView->UnlockLooper();
        }
    }
    else
    {
        return kError_NullValueInvalid;
    }
    return kError_NoErr;
}

Error
BeOSCanvas::Update( void )
{
    if ( m_canvasView->Window() && m_canvasView->LockLooper() )
    {
        m_canvasView->Invalidate();
        m_canvasView->UnlockLooper();
    }
    else
    {
        CHECK_POINT_MSG( "locklooper error or no window??" );
        return kError_NullValueInvalid;
    }
    return kError_NoErr;
}

Error
BeOSCanvas::BlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect, Rect& oDestRec )
{
    if ( !m_pBufferBitmap ) return kError_NoErr;

    return m_pBufferBitmap->BlitRect( pSrcBitmap, oSrcRect, oDestRec );
}

Error
BeOSCanvas::MaskBlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect, Rect& oDestRec )
{
    if ( !m_pBufferBitmap ) return kError_NoErr;

    return m_pBufferBitmap->MaskBlitRect( pSrcBitmap, oSrcRect, oDestRec );
}

void
BeOSCanvas::InitBackgrounds( vector<Panel*>* panels )
{
    Canvas::InitBackgrounds( panels );

    PRINT(( "pBGBitmap = %x\n", m_pBGBitmap ));
    InitBufferBitmap();
}

void
BeOSCanvas::InitBufferBitmap( void )
{
    bool needToUnlock = false;
    if ( m_canvasView && m_canvasView->Window() )
    {
        if ( !( needToUnlock = m_canvasView->LockLooper() ) )
        {
            DEBUGGER( "Geez, LockLooper failed" );
        }
    }

    if ( m_pBufferBitmap )
    {
        delete m_pBufferBitmap;
    }

    m_pBufferBitmap = new BeOSBitmap(
                        m_oBGRect.Width(),
                        m_oBGRect.Height(),
                        string( "BufferBitmap" ),
                        true // has offscreen BView for text rendering
                        );
    m_pBufferBitmap->BlitRect( m_pBGBitmap, m_oBGRect, m_oBGRect );

    if ( m_canvasView )
    {
        m_canvasView->SetCanvasBitmap( m_pBufferBitmap->GetBBitmap() );
        if ( needToUnlock )
        {
            m_canvasView->UnlockLooper();
        }
    }
}

void
BeOSCanvas::SetParent( BeOSWindow* parent )
{
    m_pParent = parent;
    m_canvasView->SetParent( m_pParent );
}
