/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Copyright (C) 1999 Mark H. Weaver <mhw@netris.org>

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
	
	$Id: facontext.h,v 1.3.8.8 1999/10/13 23:07:51 robert Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_FACONTEXT_H_
#define INCLUDED_FACONTEXT_H_

#include "config.h"
#include "preferences.h"
#include "log.h"
#include "mutex.h"

static const int32 c_majorVersion = 1;
static const int32 c_minorVersion = 0;

// argFlags bits
#define FAC_ARGFLAGS_SAVE_STREAMS 1

class PlaylistManager;
class Properties;
class EventQueue;
class MusicBrowser;
class DownloadManager;
class UpdateManager;
class Player;

class FAContext
{
 public:
    FAContext()
	: majorVersion(c_majorVersion),
	  minorVersion(c_minorVersion),
	  prefs(0),
	  log(0),
      props(0),
      plm(0),
      target(0),
	  browser(0),
      downloadManager(0),
      updateManager(0),
#ifndef WIN32	  
	  gtkInitialized(false),
#endif	  
	  argc(0),
          argv(0),	  
	  argFlags(0),
      player(0) { }
    
    ~FAContext()
    {
	    if (log)
	        delete log;
	    if (prefs)
	        delete prefs;
    }

    bool CompatibleVersion() { return majorVersion == c_majorVersion; }

    int32 majorVersion, minorVersion;
    Preferences *prefs;
    LogFile *log;
    Properties *props;
    PlaylistManager *plm;
    EventQueue *target;
    MusicBrowser *browser;
    DownloadManager *downloadManager;
    UpdateManager *updateManager;
    Player *player;
#ifndef WIN32
    Mutex gtkLock;
    bool gtkInitialized;
#endif    
    int32 argc;
    char** argv;
    uint32 argFlags;
};

#endif // _FACONTEXT_H_
