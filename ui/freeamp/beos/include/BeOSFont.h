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

   $Id: BeOSFont.h,v 1.1.2.1 1999/10/01 03:28:18 hiro Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_BEOSFONT_H
#define INCLUDED_BEOSFONT_H

#include <string>
#include "Font.h"

using namespace std;

class BeOSFont : public Font
{
public:
                    BeOSFont( string& oNme, string& oFace, string& oDefault );
    virtual         ~BeOSFont();

protected:

private:
};

#endif // INCLUDED_BEOSFONT_H
