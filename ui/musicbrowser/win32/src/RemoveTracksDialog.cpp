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

        $Id: RemoveTracksDialog.cpp,v 1.3 1999/12/03 21:07:57 elrod Exp $
____________________________________________________________________________*/

// system includes
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

// project includes
#include "config.h"
#include "resource.h"

BOOL CALLBACK RemoveTracksDlgProc(HWND hwnd, 
                                  UINT msg, 
                                  WPARAM wParam, 
                                  LPARAM lParam )
{
    BOOL result = FALSE;
    static bool* deleteTracks = false;

    switch (msg)
    {
        case WM_INITDIALOG:
        {
            deleteTracks = (bool*)lParam;
            break;
        }      

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDCANCEL:
                    EndDialog(hwnd, FALSE);
                    break;

                case IDOK:
                {
                    HWND hwndDelete = GetDlgItem(hwnd, IDC_DELETE);
                    
                    *deleteTracks = (BST_CHECKED == Button_GetCheck(hwndDelete));

                    EndDialog(hwnd, TRUE);
                    break;
                }
            }
  
            break;
        }
    }

    return result;
}