/*____________________________________________________________________________
        
   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic.com

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
        
   $Id: FreeAmpTheme.h,v 1.1.2.4 1999/09/09 02:42:10 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_FREEAMP_THEME_H
#define INCLUDED_FREEAMP_THEME_H

#include "ui.h"
#include "facontext.h"
#include "event.h"
#include "playlist.h"
#include "Theme.h"

class FreeAmpTheme : public UserInterface, public Theme
{
    public:

        FreeAmpTheme(FAContext * context);
       ~FreeAmpTheme();

        int32 AcceptEvent(Event * e);
        void  SetArgs(int argc, char **argv);
        void  SetTarget(EventQueue *pTarget)
              {
                  m_pTarget = pTarget;
              };
        Error SetPropManager(Properties *pProps)
              {
                  m_pPropManager = pProps;
                  return kError_NoErr;
              };
        void  SetPlaylistManager(PlaylistManager * plm);
        Error Init(int32 startup_type);

    protected:

        void  ParseArgs();

        Properties      *m_pPropManager;
        EventQueue      *m_pTarget;
        PlaylistManager *m_pPlaylistManager;
        FAContext       *m_pContext;
        int              m_iCurrentSeconds, m_iTotalSeconds, m_iSeekSeconds;
        int              m_iArgc, m_iStartupType;
        char           **m_pArgv;

};

#endif
