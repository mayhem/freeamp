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

        $Id: GTKFileSelector.h,v 1.1 1999/11/17 05:45:29 ijr Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_GTKFILESELECTOR_H_
#define INCLUDED_GTKFILESELECTOR_H_

#include "config.h"

#include <string>
#include <gtk/gtk.h>

#include "facontext.h"

class GTKFileSelector {
 public:
    GTKFileSelector(char *);
  
    bool Run(bool runMain = true);
    void SetExtended() { extended = true; }
    char *GetReturnPath() { if (returnpath != "")
                                return (char *)returnpath.c_str(); 
                            else return NULL; 
                          }

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
