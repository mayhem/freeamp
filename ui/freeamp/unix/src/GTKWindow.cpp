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

   $Id: GTKWindow.cpp,v 1.1.2.1 1999/08/25 23:02:09 robert Exp $
____________________________________________________________________________*/ 

#include <stdio.h>
#include "Theme.h"
#include "GTKWindow.h"
#include "GTKCanvas.h"

GTKWindow::GTKWindow(Theme *pTheme, string &oName)
          :Window(pTheme, oName)
{
    m_pCanvas = new GTKCanvas();
}

GTKWindow::~GTKWindow(void)
{
    delete m_pCanvas;
    m_pCanvas = NULL;
}

Error GTKWindow::Run(void)
{
    return kError_NoErr;
}

Error GTKWindow::Create(void)
{
    return kError_NoErr;
}

Error GTKWindow::Destroy(void)
{
    return kError_NoErr;
}

Error GTKWindow::Enable(void)
{
    return kError_NoErr;
}

Error GTKWindow::Disable(void)
{
    return kError_NoErr;
}

Error GTKWindow::Show(void)
{
    return kError_NoErr;
}

Error GTKWindow::Hide(void)
{
    return kError_NoErr;
}

Error GTKWindow::SetTitle(string &oTitle)
{
    return kError_NoErr;
}

Error GTKWindow::CaptureMouse(bool bCapture)
{
    return kError_NoErr;
}

Error GTKWindow::HideMouse(bool bHide)
{
    return kError_NoErr;
}

Error GTKWindow::SetMousePos(Pos &oPos)
{
    return kError_NoErr;
}

Error GTKWindow::GetMousePos(Pos &oPos)
{
    return kError_NoErr;
}

