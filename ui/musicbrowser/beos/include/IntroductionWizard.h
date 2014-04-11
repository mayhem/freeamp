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

        $Id: IntroductionWizard.h,v 1.1 2000/03/24 01:18:41 hiro Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_INTRODUCTION_WIZARD_H__
#define INCLUDED_INTRODUCTION_WIZARD_H__

#include <be/interface/Window.h>
#include "ResourceManager.h"

class BButton;
class MusicBrowserUI;
class FAContext;

class IntroductionWizard : public BWindow
{
public:
                    IntroductionWizard( BRect frame, const char* title,
                                        MusicBrowserUI* ui,
                                        FAContext* context );
    virtual         ~IntroductionWizard();
    virtual void    MessageReceived( BMessage* message );
    virtual void    Quit( void );
    status_t        GotoPage( int32 page );

protected:
    void            BuildIntroPage( BView* root, float* height = NULL );
    void            BuildSearchPage( BView* root );
    BString*        SimpleParse( const char* src ); // caller need to delete.

private:
    MusicBrowserUI* m_ui;
    FAContext*      m_context;
    ResourceManager m_rsrcs;
    int32           m_currentPage;
    BButton*        m_next;
    BButton*        m_back;
};

#endif // INCLUDED_INTRODUCTION_WIZARD_H__
