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

        $Id: EditTrackInfoDialog.cpp,v 1.1 1999/11/18 10:40:11 elrod Exp $
____________________________________________________________________________*/

// system includes
#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

// project includes
#include "config.h"
#include "utility.h"
#include "resource.h"
#include "Win32MusicBrowser.h"


BOOL CALLBACK EditTrackInfoDlgProc(HWND hwnd, 
                                   UINT msg, 
                                   WPARAM wParam, 
                                   LPARAM lParam )
{
    MusicBrowserUI* ui = (MusicBrowserUI*)GetWindowLong(hwnd, GWL_USERDATA);

    switch (msg)
    {
        case WM_INITDIALOG:
        {
            ui = (MusicBrowserUI*)lParam;
            assert(ui != NULL);
            SetWindowLong(hwnd, GWL_USERDATA, (LONG)ui);
            break;
        }            
    }

    return ui->EditTrackInfoDlgProc(hwnd, msg, wParam, lParam);
}        



BOOL MusicBrowserUI::EditTrackInfoDlgProc(HWND hwnd, 
                                          UINT msg, 
                                          WPARAM wParam, 
                                          LPARAM lParam )
{
    BOOL result = FALSE;

    switch (msg)
    {
        case WM_INITDIALOG:
        {
            
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
                    
                    EndDialog(hwnd, TRUE);
                    break;
                }
            }
  
            break;
        }
    }

    return result;
}

void MusicBrowserUI::CreateArtistList(vector<string>& artists)
{

}

void MusicBrowserUI::CreateAlbumList(vector<string>& albums)
{

}

void MusicBrowserUI::CreateGenreList(set<string> genres)
{

}
