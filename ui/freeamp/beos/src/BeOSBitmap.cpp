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

   $Id: BeOSBitmap.cpp,v 1.8 2000/07/12 20:10:51 hiro Exp $
____________________________________________________________________________*/ 

#include "BeOSBitmap.h"
#define DEBUG 0
#include <be/support/Debug.h>
#include <be/translation/TranslationUtils.h>
#include <be/support/Archivable.h>
#include <be/interface/Bitmap.h>
#include <be/interface/View.h>

#define CHECK_POINT CHECK_POINT_MSG("")
#define CHECK_POINT_MSG(a) PRINT(( "File %s Line %d: %s\n", __FILE__, __LINE__, a ))

bool Contains( const BRect& super, const Rect& sub )
{
    return ( super.left <= sub.x1 && sub.x2 <= super.right &&
             super.top <= sub.y1 && sub.y2 <= super.bottom );
}

BeOSBitmap::BeOSBitmap( const string& oName )
:   Bitmap( oName ),
    m_bitmap( NULL )
{
    CHECK_POINT;
}

BeOSBitmap::BeOSBitmap( int iWidth, int iHeight, const string& oName,
                        bool acceptViews )
:   Bitmap( oName ),
    m_bitmap( NULL ),
    m_offView( NULL ),
    m_hasOffscreenView( acceptViews )
{
    CHECK_POINT;
    if ( acceptViews )
    {
        m_offView = new BView( BRect(0,0,iWidth,iHeight), "BeOSBitmap",
                               B_FOLLOW_NONE, 0 );
        m_bitmap = new BBitmap( BRect(0,0,iWidth,iHeight), B_RGB32, true );
        m_bitmap->AddChild( m_offView );
    }
    else
    {
        m_bitmap = new BBitmap( BRect(0,0,iWidth,iHeight), B_RGB32 );
    }
}

BeOSBitmap::~BeOSBitmap()
{
    CHECK_POINT_MSG( "~BeOSBitmap" );
    delete m_bitmap;
}

bool
BeOSBitmap::IsPosVisible( Pos& oPos )
{
    char* bits = (char*)m_bitmap->Bits();
    int32 bytesPerPixel;
    color_space space = m_bitmap->ColorSpace();
	
    switch ( space )
    {
        case B_RGB32:
            bytesPerPixel = 4;
            break;
        case B_CMAP8:
            bytesPerPixel = 1;
            break;
        default:
            bytesPerPixel = 0; 
            break;
    }
	
	
	uint32* pixel = (uint32*)( bits + m_bitmap->BytesPerRow() * oPos.y +
                               bytesPerPixel * oPos.x );

    if ( *pixel == B_TRANSPARENT_MAGIC_RGBA32 )
    {
        return false;
    }
	
    return true;
}

Error
BeOSBitmap::LoadBitmapFromDisk( string& oFile )
{
    CHECK_POINT_MSG( "LoadBitmapFromDisk" );

    if ( m_bitmap )
    {
        delete m_bitmap;
        m_bitmap = NULL;
    }

    PRINT(( "Loading bitmap from file %s\n", oFile.c_str() ));
    BBitmap* loadedBitmap = BTranslationUtils::GetBitmap( oFile.c_str() );
    if ( loadedBitmap == NULL )
    {
        CHECK_POINT_MSG( "error loading bitmap" );
        return kError_LoadBitmapFailed;
    }
    PRINT(( "Bitmap's colorspace is %x\n", loadedBitmap->ColorSpace() ));

    if ( m_hasOffscreenView )
    {
        m_offView = new BView( loadedBitmap->Bounds(), "BeOSBitmap",
                               B_FOLLOW_NONE, 0 );
        m_bitmap = new BBitmap( loadedBitmap->Bounds(),
                                loadedBitmap->ColorSpace(),
                                true );
        m_bitmap->AddChild( m_offView );
        assert( m_bitmap->BitsLength() == loadedBitmap->BitsLength() );
        memcpy( m_bitmap->Bits(), loadedBitmap->Bits(), m_bitmap->BitsLength() );
        delete loadedBitmap;
    }
    else
    {
        m_bitmap = loadedBitmap;
    }

    // set transparency
    if ( m_bHasTransColor )
    {
        uint32  trans = (0xff << 24) |
                        (m_oTransColor.red << 16) |
                        (m_oTransColor.green << 8) |
                        (m_oTransColor.blue);
                                                
        uint32* pixel = (uint32*)m_bitmap->Bits();
        
        for ( int i = 0; i < m_bitmap->BitsLength(); i += 4 )
        {
            if ( *pixel == trans )
            {
                *pixel = B_TRANSPARENT_MAGIC_RGBA32;
            }
            pixel++;
        }
    }

    return kError_NoErr;
}

Error
BeOSBitmap::BlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect, Rect& oDestRect )
{
    if ( !Contains( m_bitmap->Bounds(), oDestRect ) )
    {
        CHECK_POINT_MSG( "Dest rect outside the bounds" );
        return kError_InvalidParam;
    }

    BBitmap* srcBitmap = ((BeOSBitmap*)pSrcBitmap)->GetBBitmap();

    ASSERT( m_bitmap && m_bitmap->IsValid() );
    ASSERT( srcBitmap && srcBitmap->IsValid() );
    ASSERT( m_bitmap->ColorSpace() == srcBitmap->ColorSpace() );

    uint8* src = (uint8*)srcBitmap->Bits();
    uint8* dst = (uint8*)m_bitmap->Bits();
    int32 srcBytesPerRow = srcBitmap->BytesPerRow();
    int32 dstBytesPerRow = m_bitmap->BytesPerRow();

    src += oSrcRect.y1 * srcBytesPerRow + oSrcRect.x1 * 4;
    dst += oDestRect.y1 * dstBytesPerRow + oDestRect.x1 * 4;
    for ( int y = 0; y < oDestRect.Height(); y++ )
    {
        uint32* ps = (uint32*)src;
        uint32* pd = (uint32*)dst;
        for ( int x = 0; x < oDestRect.Width(); x++ )
        {
            *pd++ = *ps++;
        }
        src += srcBytesPerRow;
        dst += dstBytesPerRow;
    }

    return kError_NoErr;
}

Error
BeOSBitmap::MaskBlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect, Rect& oDestRect )
{
    if ( !Contains( m_bitmap->Bounds(), oDestRect ) )
    {
        CHECK_POINT_MSG( "Dest rect outside the bounds" );
        return kError_InvalidParam;
    }

    BBitmap* srcBitmap = ((BeOSBitmap*)pSrcBitmap)->GetBBitmap();

    ASSERT( m_bitmap && m_bitmap->IsValid() );
    ASSERT( srcBitmap && srcBitmap->IsValid() );
    ASSERT( m_bitmap->ColorSpace() == srcBitmap->ColorSpace() );

    uint8* src = (uint8*)srcBitmap->Bits();
    uint8* dst = (uint8*)m_bitmap->Bits();
    int32 srcBytesPerRow = srcBitmap->BytesPerRow();
    int32 dstBytesPerRow = m_bitmap->BytesPerRow();

    //size_t len = (oSrcRect.Width() + (0)) * sizeof(int32);
    src += oSrcRect.y1 * srcBytesPerRow + oSrcRect.x1 * 4;
    dst += oDestRect.y1 * dstBytesPerRow + oDestRect.x1 * 4;
    for ( int y = 0; y < oDestRect.Height(); y++ )
    {
        uint32* ps = (uint32*)src;
        uint32* pd = (uint32*)dst;
        for ( int x = 0; x < oDestRect.Width(); x++ )
        {
            if ( *ps != B_TRANSPARENT_MAGIC_RGBA32 )
            {
                *pd = *ps;
            }
            ps++;
            pd++;
        }
        src += srcBytesPerRow;
        dst += dstBytesPerRow;
    }

    return kError_NoErr;
}

Error
BeOSBitmap::BlitRectMaskBitmap( Bitmap* pSrcBitmap, Rect& oSrcRect, 
                                Rect& oDestRect )
{
	return kError_NoErr;
}

Bitmap*
BeOSBitmap::Clone( void )
{
    PRINT(( "BeOSBitmap::Clone: %x\n", this ));
    BeOSBitmap* tmp = new BeOSBitmap( m_oBitmapName );
    tmp->m_oTransColor = m_oTransColor;
    tmp->m_bHasTransColor = m_bHasTransColor;
    if ( OffscreenView() )
    {
        tmp->m_bitmap = new BBitmap( m_bitmap, true );
        tmp->m_offView = new BView( tmp->m_bitmap->Bounds(), "BeOSBitmap",
                                    B_FOLLOW_NONE, 0 );
        tmp->m_bitmap->AddChild( tmp->m_offView );
        tmp->m_hasOffscreenView = true;
    }
    else
    {
        tmp->m_bitmap = new BBitmap( m_bitmap );
        tmp->m_offView = NULL;
        tmp->m_hasOffscreenView = false;
    }

    return tmp;
}

Error
BeOSBitmap::MakeTransparent( Rect& oRect )
{
    PRINT(( "MakeTransparent: %x\n", this ));

    uint8* bits = (uint8*)m_bitmap->Bits();
    int32 bytesPerRow = m_bitmap->BytesPerRow();
    bits += oRect.y1 * bytesPerRow + oRect.x1 * 4;
    for ( int y = 0; y < oRect.Height(); y++ )
    {
        uint32* ps = (uint32*)bits;
        for ( int x = 0; x < oRect.Width(); x++ )
        {
           *ps++ = B_TRANSPARENT_MAGIC_RGBA32;
        }
        bits += bytesPerRow; 
    }

    return kError_NoErr;
}

void
BeOSBitmap::GetColor( Pos oPos, Color& oColor )
{
}

void
BeOSBitmap::GetSize( Pos& oPos )
{
    oPos.x = m_bitmap->Bounds().IntegerWidth();
    oPos.y = m_bitmap->Bounds().IntegerHeight();
}

// vi: set ts=4:
