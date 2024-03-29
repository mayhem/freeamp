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

        $Id: fileselector.h,v 1.6 2002/04/16 17:14:28 robert Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_FILESELECTOR_H_
#define INCLUDED_FILESELECTOR_H_

#include "config.h"

#include <string>
using namespace std;
#include <gtk/gtk.h>

#include "facontext.h"

class FileSelector {
 public:
    FileSelector(FAContext *,const char *);
    bool Run(bool runMain = true);
    void SetExtended() { extended = true; }
    char *GetReturnPath() { if (returnpath != "")
                                return (char *)returnpath.c_str(); 
                            else return NULL; 
                          }

 	FAContext *GetContext(void) { return m_context; }
 protected:
    FAContext *m_context;
 private:
    string returnpath;
    string title;
    bool extended;
    bool ok;
    bool done;

    GtkWidget *filesel;
 public:
    void AddEvent();
    void CancelEvent();
};
   

#endif
