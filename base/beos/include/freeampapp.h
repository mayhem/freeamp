/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1999, 2000 EMusic.com 

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
	
	$Id: freeampapp.h,v 1.1 2000/03/12 06:00:26 hiro Exp $
____________________________________________________________________________*/

#ifndef INCLUDE_FREEAMP_APP_H__
#define INCLUDE_FREEAMP_APP_H__

#include <be/app/Application.h>

class FAContext;

class FreeAmpApp : public BApplication
{
public:
                    FreeAmpApp( const char* signature, FAContext* context );
    virtual         ~FreeAmpApp();
    virtual void    MessageReceived( BMessage* message );
    virtual void    RefsReceived( BMessage* message );

protected:

private:
    FAContext*      m_context;
};

#endif // INCLUDE_FREEAMP_APP_H__
