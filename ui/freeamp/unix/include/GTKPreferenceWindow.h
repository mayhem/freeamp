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

   $Id: GTKPreferenceWindow.h,v 1.1.2.1 1999/10/01 15:22:34 ijr Exp $
____________________________________________________________________________*/ 

#ifndef INCLUDED_GTKPREFERENCEWINDOW_H__
#define INCLUDED_GTKPREFERENCEWINDOW_H__

#include "config.h"
#include "PreferenceWindow.h"
#include "preferences.h"
#include "log.h"
#include "registrar.h"

typedef struct PrefsStruct 
{
    Preferences* prefs;

    // page 1
    char defaultUI[256];
    char defaultPMO[256];
    int32 inputBufferSize;
    int32 outputBufferSize;
    int32 preBufferLength;
    int32 decoderThreadPriority;
    bool stayOnTop;
    bool liveInTray;

    // page 2
    int32 streamInterval;
    bool saveStreams;
    char saveStreamsDirectory[MAX_PATH + 1];
    bool useProxyServer;
    char proxyServer[256]; // is there a domain name length limit???
    bool useAlternateIP;
    char alternateIP[16];
    
    // page 3
    bool enableLogging;
    bool logMain;
    bool logInput;
    bool logOutput;
    bool logDecoder;
    bool logPerformance;

    PrefsStruct()
    {
        memset(defaultUI, 0x00, sizeof(defaultUI));
        memset(defaultPMO, 0x00, sizeof(defaultPMO));
        memset(saveStreamsDirectory, 0x00, sizeof(saveStreamsDirectory));
        memset(proxyServer, 0x00, sizeof(proxyServer));
        memset(alternateIP, 0x00, sizeof(alternateIP));
    }

} PrefsStruct;

class GTKPreferenceWindow : public PreferenceWindow
{
    public:

               GTKPreferenceWindow(FAContext *context);
      virtual ~GTKPreferenceWindow(void); 
      
      virtual  bool Show(Window *pParent);

               void GetPrefsValues(Preferences* prefs, 
                                   PrefsStruct* values);

               void SavePrefsValues(Preferences* prefs, 
                                    PrefsStruct* values);

	protected:
    
      FAContext   *m_pContext;
      PrefsStruct  originalValues;
      PrefsStruct  currentValues;
};

#endif
