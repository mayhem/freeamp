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

   $Id: BeOSMessageDialog.cpp,v 1.3 1999/10/23 08:25:00 hiro Exp $
____________________________________________________________________________*/ 

#include "MessageDialog.h"
#include <stdio.h>

MessageDialog::MessageDialog()
{
}

MessageDialog::~MessageDialog()
{
}

MessageDialogReturnEnum
MessageDialog::Show( const char* szMessage,
                     const char* szTitle,
                     MessageDialogEnum eType )
{
    printf( "MessageDialog: %s\n", szMessage );
}

MessageDialogReturnEnum
MessageDialog::Show( const string& oMessage,
                     const string& oTitle,
                     MessageDialogEnum eType )
{
    printf( "MessageDialog: %s\n", oMessage.c_str() );
}
