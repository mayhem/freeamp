/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998 GoodNoise

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
	
	$Id: GTKPreferenceWindow.cpp,v 1.1.2.3 1999/10/11 04:20:00 ijr Exp $
____________________________________________________________________________*/

/* system headers */
#include <stdlib.h>
#include <assert.h>

#include "ThemeManager.h"
#include "GTKPreferenceWindow.h"
#include "GTKWindow.h"

static GTKPreferenceWindow *g_pCurrentPrefWindow = NULL;

GTKPreferenceWindow::GTKPreferenceWindow(FAContext *context,
                                         ThemeManager *pThemeMan) :
     PreferenceWindow(context, pThemeMan)
{     
    g_pCurrentPrefWindow = this;
}

GTKPreferenceWindow::~GTKPreferenceWindow(void)
{
    g_pCurrentPrefWindow = NULL;

    vector<string *>::iterator i;
    for (i = m_oThemeList.begin(); i != m_oThemeList.end(); i++)
        delete (*i);
} 

bool GTKPreferenceWindow::Show(Window *pWindow)
{
}

void GTKPreferenceWindow::GetPrefsValues(Preferences* prefs, 
                                         PrefsStruct* values)
{
    uint32 size = 256;

    prefs->GetDefaultPMO(values->defaultPMO, &size);
    size = 256;
    prefs->GetDefaultUI(values->defaultUI, &size);
    prefs->GetDecoderThreadPriority(&values->decoderThreadPriority);
    prefs->GetInputBufferSize(&values->inputBufferSize);
    prefs->GetOutputBufferSize(&values->outputBufferSize);
    prefs->GetPrebufferLength(&values->preBufferLength);

    prefs->GetStreamBufferInterval(&values->streamInterval);
    prefs->GetSaveStreams(&values->saveStreams);
    size = 256;
    prefs->GetProxyServerAddress(values->proxyServer, &size);
    prefs->GetUseProxyServer(&values->useProxyServer);
    size = MAX_PATH;
    prefs->GetSaveStreamsDirectory(values->saveStreamsDirectory, &size);
    size = 16;
    prefs->GetAlternateNICAddress(values->alternateIP, &size);
    prefs->GetUseAlternateNIC(&values->useAlternateIP);

    prefs->GetUseDebugLog(&values->enableLogging);
    prefs->GetLogMain(&values->logMain);
    prefs->GetLogDecode(&values->logDecoder);
    prefs->GetLogInput(&values->logInput);
    prefs->GetLogOutput(&values->logOutput);
    prefs->GetLogPerformance(&values->logPerformance);

    size = 256;
    prefs->GetThemeDefaultFont(values->defaultFont, &size);
    m_pThemeMan->GetCurrentTheme(values->currentTheme);
}

void GTKPreferenceWindow::SavePrefsValues(Preferences* prefs, 
                                          PrefsStruct* values)
{
    prefs->SetDefaultPMO(values->defaultPMO);
    prefs->SetDefaultUI(values->defaultUI);
    prefs->SetDecoderThreadPriority(values->decoderThreadPriority);
    prefs->SetInputBufferSize(values->inputBufferSize);
    prefs->SetOutputBufferSize(values->outputBufferSize);
    prefs->SetPrebufferLength(values->preBufferLength);

    prefs->SetStreamBufferInterval(values->streamInterval);
    prefs->SetSaveStreams(values->saveStreams);
    prefs->SetSaveStreamsDirectory(values->saveStreamsDirectory);
    prefs->SetProxyServerAddress(values->proxyServer);
    prefs->SetUseProxyServer(values->useProxyServer);
    prefs->SetAlternateNICAddress(values->alternateIP);
    prefs->SetUseAlternateNIC(values->useAlternateIP);

    prefs->SetUseDebugLog(values->enableLogging);
    prefs->SetLogMain(values->logMain);
    prefs->SetLogDecode(values->logDecoder);
    prefs->SetLogInput(values->logInput);
    prefs->SetLogOutput(values->logOutput);
    prefs->SetLogPerformance(values->logPerformance);

    prefs->SetThemeDefaultFont(values->defaultFont);
    m_pThemeMan->UseTheme(currentValues.currentTheme);
}
