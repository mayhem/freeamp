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

   $Id: Font.h,v 1.1.2.1 1999/09/29 08:40:56 robert Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_FONT_H__
#define INCLUDED_FONT_H__

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Types.h"
#include "errors.h"

class Font
{
    public:

               Font(string &oName, string &oFace, string &oDefault);
      virtual ~Font(void);
      
      virtual Error GetName(string &oName);
      virtual Error GetFace(string &oFace);

	protected:
    
      string   m_oName, m_oFace, m_oDefault;
};

#endif