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

   $Id: BeOSBitmap.cpp,v 1.1.2.1 1999/10/01 03:28:18 hiro Exp $
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

BeOSBitmap::BeOSBitmap( string& oName )
:   Bitmap( oName ),
    m_bitmap( NULL )
{
    CHECK_POINT;
}

BeOSBitmap::BeOSBitmap( int iWidth, int iHeight, string& oName )
:   Bitmap( oName ),
    m_bitmap( NULL )
#if USE_OFFSCREEN_VIEW
   ,m_offView( NULL )
#endif
{
    CHECK_POINT;
#if USE_OFFSCREEN_VIEW
    m_offView = new BView( BRect(0,0,iWidth,iHeight), "BeOSBitmap",
                           B_FOLLOW_NONE, 0 );
    m_bitmap = new BBitmap( BRect(0,0,iWidth,iHeight), B_RGB32, true );
    m_bitmap->AddChild( m_offView );
#else
    m_bitmap = new BBitmap( BRect(0,0,iWidth,iHeight), B_RGB32 );
#endif
}

BeOSBitmap::~BeOSBitmap()
{
    CHECK_POINT_MSG( "~BeOSBitmap" );
    delete m_bitmap;
}

bool
BeOSBitmap::IsPosVisible( Pos& oPos )
{
    CHECK_POINT_MSG( "IsPosVisible" );
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

#if USE_OFFSCREEN_VIEW
    m_offView = new BView( loadedBitmap->Bounds(), "BeOSBitmap",
                           B_FOLLOW_NONE, 0 );
    m_bitmap = new BBitmap( loadedBitmap->Bounds(), loadedBitmap->ColorSpace(),
                            true );
    m_bitmap->AddChild( m_offView );
    assert( m_bitmap->BitsLength() == loadedBitmap->BitsLength() );
    memcpy( m_bitmap->Bits(), loadedBitmap->Bits(), m_bitmap->BitsLength() );
    delete loadedBitmap;
#else
    m_bitmap = loadedBitmap;
#endif

    // set transparency
    if ( m_bHasTransColor )
    {
        uint32  trans = (m_oTransColor.red << 16) |
                        (m_oTransColor.green << 8) |
                        (m_oTransColor.blue);
        uint32* pixel = (uint32*)m_bitmap->Bits();
//        while ( pixel < (pixel + m_bitmap->BitsLength() / 4) )
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
    CHECK_POINT_MSG( "BlitRect" );
    PRINT(( "Bliting (%d,%d,%d,%d) to (%d,%d,%d,%d)\n",
        oSrcRect.x1, oSrcRect.y1, oSrcRect.x2, oSrcRect.y2,
        oDestRect.x1, oDestRect.y1, oDestRect.x2, oDestRect.y2 ));

    return kError_NoErr;
}

Error
BeOSBitmap::MaskBlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect, Rect& oDestRect )
{
    CHECK_POINT_MSG( "MaskBlitRect" );
#if USE_OFFSCREEN_VIEW
    BRect srcRect( float(oSrcRect.x1), float(oSrcRect.y1),
                   float(oSrcRect.x2), float(oSrcRect.y2) );
    BRect dstRect( float(oDestRect.x1), float(oDestRect.y1),
                   float(oDestRect.x2), float(oDestRect.y2) );

    m_bitmap->Lock();

    m_offView->DrawBitmap( ((BeOSBitmap*)pSrcBitmap)->GetBBitmap(),
                           srcRect, dstRect );
    m_offView->Sync();

    m_bitmap->Unlock();
#endif
    PRINT(( "MaskBliting (%d,%d,%d,%d) to (%d,%d,%d,%d)\n",
        oSrcRect.x1, oSrcRect.y1, oSrcRect.x2, oSrcRect.y2,
        oDestRect.x1, oDestRect.y1, oDestRect.x2, oDestRect.y2 ));

    BBitmap* srcBitmap = ((BeOSBitmap*)pSrcBitmap)->GetBBitmap();

    assert( m_bitmap );
    assert( m_bitmap->ColorSpace() == srcBitmap->ColorSpace() );

    uint8* src = (uint8*)srcBitmap->Bits();
    uint8* dst = (uint8*)m_bitmap->Bits();
    int32 srcBytesPerRow = srcBitmap->BytesPerRow();
    int32 dstBytesPerRow = m_bitmap->BytesPerRow();

    size_t len = (oSrcRect.Width() + (0)) * sizeof(int32);
    src += oSrcRect.y1 * srcBytesPerRow + oSrcRect.x1 * sizeof(int32);
    dst += oDestRect.y1 * dstBytesPerRow + oDestRect.x1 * sizeof(int32);
    for ( int y = 0; y < oSrcRect.Height() + 0; y++ )
    {
//        memcpy( dst, src, len - 4 );
        uint32* ps = (uint32*)src;
        uint32* pd = (uint32*)dst;
        for ( int x = 0; x < oSrcRect.Width() - 1; x++ )
        {
            if ( *ps != B_TRANSPARENT_MAGIC_RGBA32 )
            {
                *pd++ = *ps;
            }
            ps++;
        }
        src += srcBytesPerRow;
        dst += dstBytesPerRow;
    }

    CHECK_POINT;
    return kError_NoErr;
}
