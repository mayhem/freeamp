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

   $Id: font.cpp,v 1.1.2.2 1999/09/27 19:20:36 ijr Exp $
____________________________________________________________________________*/ 

#include "font.h"

Font::Font(string &oName, string &oFace)
{
   m_oName = oName;
   m_oFace = oFace;
}

Font::~Font(void)
{
}

Error Font::GetName(string &oName)
{
   oName = m_oName;
   
   return kError_NoErr;
}

Error Font::GetFace(string &oFace)
{
   oFace = m_oFace;

   return kError_NoErr;
}
