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

   $Id: BeOSBitmap.h,v 1.6 2000/07/12 20:10:50 hiro Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_BEOSBITMAP_H__
#define INCLUDED_BEOSBITMAP_H__

#include <string>
#include "Bitmap.h"

class BBitmap;
class BView;

class BeOSBitmap : public Bitmap
{
public:
                        BeOSBitmap( const string& oName );
                        BeOSBitmap( int iWidth, int iHeight, const string& oName,
                                    bool acceptViews = false );
    virtual             ~BeOSBitmap();
    virtual bool        IsPosVisible( Pos& oPos );
    virtual Error       LoadBitmapFromDisk( string& oFile );
    virtual Error       BlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect,
                                  Rect& oDestRect );
    virtual Error       MaskBlitRect( Bitmap* pSrcBitmap, Rect& oSrcRect,
                                      Rect& oDestRect );
    virtual Error       BlitRectMaskBitmap( Bitmap* pSrcBitmap, Rect& oSrcRect, 
                                            Rect& oDestRect );
    virtual Bitmap*     Clone( void );
    virtual Error       MakeTransparent( Rect& oRect );
    virtual void        GetColor( Pos oPos, Color& oColor );
    virtual void        GetSize( Pos& oPos );

    BBitmap*            GetBBitmap( void ) { return m_bitmap; }
    BView*              OffscreenView( void ) { return m_offView; }

    const char*         Name( void ) const { return m_oBitmapName.c_str(); }

protected:

private:
    BBitmap*            m_bitmap;
    BView*              m_offView;
    bool                m_hasOffscreenView;
};

#endif // INCLUDED_BEOSBITMAP_H__
