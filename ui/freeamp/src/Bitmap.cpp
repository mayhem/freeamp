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

   $Id: Bitmap.cpp,v 1.1.2.5 1999/09/26 03:23:35 robert Exp $
____________________________________________________________________________*/ 

#include "string"
#include "Bitmap.h"


Bitmap::Bitmap(string &oName)
{
   m_oBitmapName = oName;
   m_oTransIndexPos.x = m_oTransIndexPos.y = -1;
}

Bitmap::~Bitmap(void)
{
}

void Bitmap::GetName(string &oName)
{
    oName = m_oBitmapName;
}

void Bitmap::GetErrorString(string &oError)
{
    oError = m_oLastError;
}

void Bitmap::SetTransIndexPos(Pos &oPos)
{
    m_oTransIndexPos = oPos;
}
