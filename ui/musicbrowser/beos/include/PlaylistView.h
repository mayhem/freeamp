/*____________________________________________________________________________

        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 1999 EMusic.com

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

        $Id: PlaylistView.h,v 1.1 2000/03/24 01:18:41 hiro Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_PLAYLIST_VIEW_H__
#define INCLUDED_PLAYLIST_VIEW_H__

#include <be/interface/ListView.h>

class PlaylistView : public BListView
{
public:
                    PlaylistView( BRect frame, const char* name,
                                  uint32 resizingMode );
    virtual         ~PlaylistView();
    virtual bool    InitiateDrag( BPoint point, int32 index, bool wasSelected );

    void            SetCurrentlyPlaying( int32 index );

protected:

private:
    int32           m_currentIndex;
};

#endif // INCLUDED_PLAYLIST_VIEW_H__
