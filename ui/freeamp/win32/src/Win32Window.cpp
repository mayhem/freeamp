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

   $Id: Win32Window.cpp,v 1.1.2.2 1999/09/08 23:26:40 elrod Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include "Theme.h"
#include "Win32Window.h"
#include "Win32Canvas.h"

Win32Window::Win32Window(Theme *pTheme, string &oName)
            :Window(pTheme, oName)
{
    m_pCanvas = new Win32Canvas();
}

Win32Window::~Win32Window(void)
{
    delete m_pCanvas;
    m_pCanvas = NULL;
}

Error Win32Window::Run(void)
{
    return kError_NoErr;
}

Error Win32Window::Create(void)
{
    return kError_NoErr;
}

Error Win32Window::Destroy(void)
{
    return kError_NoErr;
}

Error Win32Window::Enable(void)
{
    return kError_NoErr;
}

Error Win32Window::Disable(void)
{
    return kError_NoErr;
}

Error Win32Window::Show(void)
{
    return kError_NoErr;
}

Error Win32Window::Hide(void)
{
    return kError_NoErr;
}

Error Win32Window::SetTitle(string &oTitle)
{
    return kError_NoErr;
}

Error Win32Window::CaptureMouse(bool bCapture)
{
    return kError_NoErr;
}

Error Win32Window::HideMouse(bool bHide)
{
    return kError_NoErr;
}

Error Win32Window::SetMousePos(Pos &oPos)
{
    return kError_NoErr;
}

Error Win32Window::GetMousePos(Pos &oPos)
{
    return kError_NoErr;
}

