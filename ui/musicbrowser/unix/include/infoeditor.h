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

        $Id: infoeditor.h,v 1.2 1999/10/19 07:13:28 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_INFOEDITOR_H_
#define INCLUDED_INFOEDITOR_H_

#include "config.h"

#include <gtk/gtk.h>

#include "facontext.h"
#include "playlist.h"

class infoeditorUI {
 public:
    infoeditorUI(FAContext *, PlaylistItem *);
   ~infoeditorUI();
  
    void DisplayInfo();
 
    GtkWidget *m_okButton;
    GtkWidget *m_applyButton;
  
    void DoApplyInfoEdit();

    bool changed;
 protected:
     FAContext *m_context;

 private:
     GtkWidget *m_window;
     GtkWidget *m_titleEntry;
     GtkWidget *m_artistEntry;
     GtkWidget *m_albumEntry;
     GtkWidget *m_yearEntry;
     GtkWidget *m_commentEntry;
     GtkWidget *m_genreEntry;
     GtkWidget *m_trackEntry;

     PlaylistItem *m_playlistItem;
};
   

#endif
