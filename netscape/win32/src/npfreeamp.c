/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Copyright (C) 2000 EMusic.com

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
	
	$Id: npfreeamp.c,v 1.1.2.2 2000/03/02 00:00:24 robert Exp $
____________________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "npapi.h"

#ifdef _WINDOWS /* Windows Includes */
#include <windows.h>
#include "resource.h"
#endif /* _WINDOWS */

#ifdef XP_UNIX
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#endif /* XP_UNIX */

// Get rid of the silly benign redef of type warnings
#ifdef WIN32
#pragma warning(disable:4142)
#endif

#include "config.h"

const int iBoxWidth = 175;
const int iBoxLines = 6;
const int iDeleteButton = 0;
const int iImportButton = 1;
HINSTANCE g_hInst = NULL;

const HKEY  kMainKey = HKEY_CURRENT_USER;
const char* kFreeAmpKey = "SOFTWARE\\"BRANDING_COMPANY;
const char* kFreeAmpVersionKey = BRANDING" v"FREEAMP_MAJOR_VERSION"."FREEAMP_MINOR_VERSION;
const char* kMainComponentKey = "Main";
const char *szText1 = "Now downloading";
const char *szText2 = "into "the_BRANDING;
const char *szSponsor = "The development of FreeAmp is sponsored by:";

/*------------------------------------------------------------------------------
 * Windows PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_PC
typedef struct _PlatformInstance
{
	HWND			fhWnd, hImportWnd, hDeleteWnd;
	WNDPROC			fDefaultWindowProc;
    RECT            sProgressRect, sBorder, sDeleteRect, sImportRect;
    HBITMAP         hEmusic, hFreeamp;
} PlatformInstance;
#endif /* XP_PC */
/*------------------------------------------------------------------------------
 * UNIX PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
typedef struct _PlatformInstance
{
    Window 			window;
    Display *		display;
    uint32 			x, y;
    uint32 			width, height;
} PlatformInstance;
#endif /* XP_UNIX */
/*------------------------------------------------------------------------------
 * Macintosh PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_MAC
typedef struct _PlatformInstance
{
	int				placeholder;
} PlatformInstance;
#endif /* macintosh */
/*------------------------------------------------------------------------------
 * Cross-Platform PluginInstance
 *----------------------------------------------------------------------------*/
typedef struct _PluginInstance
{
	NPWindow*			fWindow;
	uint16				fMode;
    FILE               *fpFile;
    BOOL                bFreeAmp;
    int                 iBytesReceived, iPercentDone;
    char                szFileName[_MAX_PATH];
    char                szFreeAmpExe[_MAX_PATH];
    char                szTargetFile[_MAX_PATH];
	PlatformInstance	fPlatform;
} PluginInstance;


/******************************************************************************
 * Method Declarations
 ******************************************************************************/
void        UpdateProgress(PluginInstance* This, int iPercentDone);
void		PlatformNew( PluginInstance* This );
NPError		PlatformDestroy( PluginInstance* This );
NPError		PlatformSetWindow( PluginInstance* This, NPWindow* window );
int16		PlatformHandleEvent( PluginInstance* This, void* event );


/*******************************************************************************
 * SECTION 3 - API Plugin Implementations
 ******************************************************************************/

static HWND hDebugWind;

void DebugInit_v(void)
{
    hDebugWind = FindWindow("#32770", "Debug32");
}

void Debug_v(char * format, ...)
{
    char szBuffer[4096];
    va_list argptr;
    ATOM hAtom;
    
    if (hDebugWind == NULL) 
    {
        DebugInit_v();
        if (hDebugWind == NULL) 
           return;
    }

    va_start(argptr, format);
    vsprintf(szBuffer, format, argptr);
    va_end(argptr);

    szBuffer[254] = 0;
    hAtom = GlobalAddAtom(szBuffer);
    SendMessage( hDebugWind, WM_USER + 1, 0, (LPARAM)hAtom);
    GlobalDeleteAtom(hAtom);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, 
                    DWORD fdwReason, 
                    LPVOID lpvReserved)
{                         
    switch(fdwReason)
    { 
         case DLL_PROCESS_ATTACH:
            g_hInst = hinstDLL;
         break;
    }
    
    return TRUE;
} 

/*------------------------------------------------------------------------------
 * Cross-Platform Plug-in API Calls
 *----------------------------------------------------------------------------*/
 
NPError
NPP_Initialize(void)
{
    return NPERR_NO_ERROR;
}

jref
NPP_GetJavaClass(void)
{
	return NULL;
}

void
NPP_Shutdown(void)
{
}

NPError 
NPP_New(NPMIMEType pluginType,
	NPP instance,
	uint16 mode,
	int16 argc,
	char* argn[],
	char* argv[],
	NPSavedData* saved)
{
	NPError result = NPERR_NO_ERROR;
	PluginInstance* This;

	if (instance == NULL) {
		return NPERR_INVALID_INSTANCE_ERROR;
	}
	instance->pdata = NPN_MemAlloc(sizeof(PluginInstance));
	This = (PluginInstance*) instance->pdata;
	if (This == NULL) {
	    return NPERR_OUT_OF_MEMORY_ERROR;
	}
	/* mode is NP_EMBED, NP_FULL, or NP_BACKGROUND (see npapi.h) */
	This->fWindow = NULL;
	This->fMode = mode;
    This->fpFile = NULL;
    This->iBytesReceived = 0;
    This->iPercentDone = 0;
    This->bFreeAmp = !strcasecmp(BRANDING, "FreeAmp");
    This->fPlatform.sProgressRect.left = -1;
    This->fPlatform.sProgressRect.top = -1;
    This->fPlatform.hImportWnd = NULL;
    This->fPlatform.hDeleteWnd = NULL;
    This->fPlatform.hEmusic = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EMUSIC));
    This->fPlatform.hFreeamp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_FREEAMP));
	
	PlatformNew( This ); 	/* Call Platform-specific initializations */

		/* PLUGIN DEVELOPERS:
		 *	Initialize fields of your plugin
		 *	instance data here.  If the NPSavedData is non-
		 *	NULL, you can use that data (returned by you from
		 *	NPP_Destroy to set up the new plugin instance).
		 */

	return result;
}

NPError 
NPP_Destroy(NPP instance, NPSavedData** save)
{
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	This = (PluginInstance*) instance->pdata;
	PlatformDestroy( This ); /* Perform platform specific cleanup */
	
	/* PLUGIN DEVELOPERS:
	 *	If desired, call NP_MemAlloc to create a
	 *	NPSavedDate structure containing any state information
	 *	that you want restored if this plugin instance is later
	 *	recreated.
	 */

	if (This != NULL) {
		NPN_MemFree(instance->pdata);
		instance->pdata = NULL;
	}

	return NPERR_NO_ERROR;
}

NPError 
NPP_SetWindow(NPP instance, NPWindow* window)
{
	NPError result = NPERR_NO_ERROR;
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	This = (PluginInstance*) instance->pdata;

	/*
	 * PLUGIN DEVELOPERS:
	 *	Before setting window to point to the
	 *	new window, you may wish to compare the new window
	 *	info to the previous window (if any) to note window
	 *	size changes, etc.
	 */
	result = PlatformSetWindow( This, window );
	
	This->fWindow = window;
	return result;
}

NPError 
NPP_NewStream(NPP instance,
	      NPMIMEType type,
	      NPStream *stream, 
	      NPBool seekable,
	      uint16 *stype)
{
	PluginInstance* This;
    LONG            result, len;
    char            szBuf[_MAX_PATH];
    char            szBase[_MAX_PATH], szExt[_MAX_PATH];
    char           *pPtr;
    HKEY            hKey;
    DWORD           dwType;
    int             i;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	This = (PluginInstance*) instance->pdata;

    sprintf(szBuf, "%s\\%s\\%s", kFreeAmpKey, 
            kFreeAmpVersionKey, kMainComponentKey);
    result = RegOpenKeyEx(HKEY_CURRENT_USER, szBuf, 
						  0, 
                          KEY_READ,
                          &hKey);
    if (result != ERROR_SUCCESS)
    {
        MessageBox(NULL, "Cannot determine where player is installed.\r\nPlease check you player installation.",
                   "Download Plugin", MB_OK);
        return NPERR_GENERIC_ERROR;
    }    
        
    len = sizeof(szBuf);
	result = RegQueryValueEx(hKey, "SaveMusicDirectory", NULL, &dwType, (LPBYTE)szBuf, &len);
    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        MessageBox(NULL, "Cannot determine where player is installed.\r\nPlease check you player installation.",
                   "Download Plugin", MB_OK);
        return NPERR_GENERIC_ERROR;
    }    

    len = sizeof(This->szFreeAmpExe); 
	result = RegQueryValueEx(hKey, "InstallDirectory", NULL, &dwType, (LPBYTE)This->szFreeAmpExe, &len);
    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        MessageBox(NULL, "Cannot determine where player is installed.\r\nPlease check you player installation.",
                   "Download Plugin", MB_OK);
        return NPERR_GENERIC_ERROR;
    }    
    
    strcat(This->szFreeAmpExe, "\\");
    strcat(This->szFreeAmpExe, BRANDING_EXE_FILE);
    
    RegCloseKey(hKey);

    Debug_v("url: '%s'", stream->url);

    pPtr = strrchr(stream->url, '/');
    if (pPtr == NULL)
    {
        MessageBox(NULL, "Cannot determine the name of the file to be downloaded.",
                   "Download Plugin", MB_OK);
        return NPERR_GENERIC_ERROR;
    }

    strcpy(szBase, pPtr + 1);
    pPtr = strrchr(szBase, '.');
    if (pPtr)
    {
        strcpy(szExt, pPtr + 1);
        *pPtr = 0;
    }
    else
        szExt[0] = 0;

    sprintf(This->szFileName, "%s.%s", szBase, szExt);
        
    for(i = 0;; i++)
    {  
        if (i == 0)
           sprintf(This->szTargetFile, "%s\\%s.%s", szBuf, szBase, szExt);
        else   
           sprintf(This->szTargetFile, "%s\\%s-%d.%s", szBuf, szBase, i + 1, szExt);
           
        if (_access(This->szTargetFile, 0))
           break;
    }

    This->fpFile = fopen(This->szTargetFile, "wb");
    if (This->fpFile == NULL)
    {
        MessageBox(NULL, "Cannot create the download file. Please check you player installation.",
                   "Download Plugin", MB_OK);
        return NPERR_GENERIC_ERROR;
    }

	return NPERR_NO_ERROR;
}


int32 STREAMBUFSIZE = 0X0FFFFFFF; /* If we are reading from a file in NPAsFile
								   * mode so we can take any size stream in our
								   * write call (since we ignore it) */

int32 
NPP_WriteReady(NPP instance, NPStream *stream)
{
	PluginInstance* This;
	if (instance != NULL)
		This = (PluginInstance*) instance->pdata;

	/* Number of bytes ready to accept in NPP_Write() */
	return STREAMBUFSIZE;
}

int32 
NPP_Write(NPP instance, NPStream *stream, int32 offset, 
          int32 len, void *buffer)
{
    int iRet;
    
	if (instance != NULL) 
    {
		PluginInstance* This = (PluginInstance*) instance->pdata;
        RECT            sRect;

        if (This->fpFile == NULL)
            return -1;

        iRet = fwrite(buffer, sizeof(char), len, This->fpFile);
        if (iRet != len)
            MessageBox(NULL, "Cannot write file to disk. Disk Full?",
                   "Download Plugin", MB_OK);
            
        This->iBytesReceived += len;
        This->iPercentDone = This->iBytesReceived * 100 / stream->end;
        sRect = This->fPlatform.sProgressRect;
        sRect.right += 100;
        InvalidateRect(This->fPlatform.fhWnd, &sRect, FALSE);
        UpdateWindow(This->fPlatform.fhWnd);

        len = iRet;
	}
    else
       len = -1;
       
	return len;		/* The number of bytes accepted */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_DestroyStream:
 * Indicates the closure and deletion of a stream, and returns an error value. 
 * 
 * The NPP_DestroyStream function is called when the stream identified by
 * stream for the plug-in instance denoted by instance will be destroyed. You
 * should delete any private data allocated in stream->pdata at this time. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_DestroyStream(NPP instance, NPStream *stream, NPError reason)
{
    STARTUPINFO          sInfo;
    PROCESS_INFORMATION  sProcess;
	PluginInstance      *This;
    char                 szArgs[_MAX_PATH];
    BOOL                 bRet;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
	This = (PluginInstance*) instance->pdata;

    if (This->fpFile)
        fclose(This->fpFile);

    if (reason == NPRES_DONE)
    {
        BOOL bImport;
        
        bImport = SendMessage(This->fPlatform.hImportWnd, BM_GETCHECK, 0, 0);

        memset(&sInfo, 0, sizeof(sInfo));
        sInfo.cb = sizeof(STARTUPINFO);
        
        if (bImport)
           sprintf(szArgs, "%s -import \"%s\"", This->szFreeAmpExe, This->szTargetFile);
        else   
           sprintf(szArgs, "%s -delete \"%s\"", This->szFreeAmpExe, This->szTargetFile);
        //sprintf(szArgs, "%s \"%s\"", This->szFreeAmpExe, This->szTargetFile);
           
        bRet = CreateProcess(NULL, szArgs, NULL, NULL, FALSE,
                         CREATE_NEW_PROCESS_GROUP, NULL, NULL, &sInfo, &sProcess);
    }
    else
        unlink(This->szTargetFile);
        
    EnableWindow(This->fPlatform.hDeleteWnd, FALSE);
    EnableWindow(This->fPlatform.hImportWnd, FALSE);

	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_StreamAsFile:
 * Provides a local file name for the data from a stream. 
 * 
 * NPP_StreamAsFile provides the instance with a full path to a local file,
 * identified by fname, for the stream specified by stream. NPP_StreamAsFile is
 * called as a result of the plug-in requesting mode NP_ASFILEONLY or
 * NP_ASFILE in a previous call to NPP_NewStream. If an error occurs while
 * retrieving the data or writing the file, fname may be NULL. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void 
NPP_StreamAsFile(NPP instance, NPStream *stream, const char* fname)
{
	PluginInstance* This;
	if (instance != NULL)
		This = (PluginInstance*) instance->pdata;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Print:
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void 
NPP_Print(NPP instance, NPPrint* printInfo)
{
	if(printInfo == NULL)
		return;

	if (instance != NULL) {
		PluginInstance* This = (PluginInstance*) instance->pdata;
	
		if (printInfo->mode == NP_FULL) {
		    /*
		     * PLUGIN DEVELOPERS:
		     *	If your plugin would like to take over
		     *	printing completely when it is in full-screen mode,
		     *	set printInfo->pluginPrinted to TRUE and print your
		     *	plugin as you see fit.  If your plugin wants Netscape
		     *	to handle printing in this case, set
		     *	printInfo->pluginPrinted to FALSE (the default) and
		     *	do nothing.  If you do want to handle printing
		     *	yourself, printOne is true if the print button
		     *	(as opposed to the print menu) was clicked.
		     *	On the Macintosh, platformPrint is a THPrint; on
		     *	Windows, platformPrint is a structure
		     *	(defined in npapi.h) containing the printer name, port,
		     *	etc.
		     */

			void* platformPrint =
				printInfo->print.fullPrint.platformPrint;
			NPBool printOne =
				printInfo->print.fullPrint.printOne;
			
			/* Do the default*/
			printInfo->print.fullPrint.pluginPrinted = FALSE;
		}
		else {	/* If not fullscreen, we must be embedded */
		    /*
		     * PLUGIN DEVELOPERS:
		     *	If your plugin is embedded, or is full-screen
		     *	but you returned false in pluginPrinted above, NPP_Print
		     *	will be called with mode == NP_EMBED.  The NPWindow
		     *	in the printInfo gives the location and dimensions of
		     *	the embedded plugin on the printed page.  On the
		     *	Macintosh, platformPrint is the printer port; on
		     *	Windows, platformPrint is the handle to the printing
		     *	device context.
		     */

			NPWindow* printWindow =
				&(printInfo->print.embedPrint.window);
			void* platformPrint =
				printInfo->print.embedPrint.platformPrint;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_URLNotify:
 * Notifies the instance of the completion of a URL request. 
 * 
 * NPP_URLNotify is called when Netscape completes a NPN_GetURLNotify or
 * NPN_PostURLNotify request, to inform the plug-in that the request,
 * identified by url, has completed for the reason specified by reason. The most
 * common reason code is NPRES_DONE, indicating simply that the request
 * completed normally. Other possible reason codes are NPRES_USER_BREAK,
 * indicating that the request was halted due to a user action (for example,
 * clicking the "Stop" button), and NPRES_NETWORK_ERR, indicating that the
 * request could not be completed (for example, because the URL could not be
 * found). The complete list of reason codes is found in npapi.h. 
 * 
 * The parameter notifyData is the same plug-in-private value passed as an
 * argument to the corresponding NPN_GetURLNotify or NPN_PostURLNotify
 * call, and can be used by your plug-in to uniquely identify the request. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
	/* Not used in the Simple plugin. */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_HandleEvent:
 * Mac-only, but stub must be present for Windows
 * Delivers a platform-specific event to the instance. 
 * 
 * On the Macintosh, event is a pointer to a standard Macintosh EventRecord.
 * All standard event types are passed to the instance as appropriate. In general,
 * return TRUE if you handle the event and FALSE if you ignore the event. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef XP_UNIX
int16
NPP_HandleEvent(NPP instance, void* event)
{
	PluginInstance* This;
	int16 eventHandled = FALSE;
	
	if (instance == NULL)
		return eventHandled;
	
	This = (PluginInstance*) instance->pdata;
	eventHandled = PlatformHandleEvent(This, event);
	return eventHandled;
}
#endif /* ndef XP_UNIX */
/*******************************************************************************/


LRESULT CALLBACK PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
const char* gInstanceLookupString = "instance->pdata";

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
PlatformNew( PluginInstance* This )
{
	This->fPlatform.fhWnd = NULL;
	This->fPlatform.fDefaultWindowProc = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformDestroy( PluginInstance* This )
{

	if( This->fWindow != NULL ) { /* If we have a window, clean

								 * it up. */

		SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);

		This->fPlatform.fDefaultWindowProc = NULL;
		This->fPlatform.fhWnd = NULL;
        
        DeleteObject(This->fPlatform.hEmusic);
        DeleteObject(This->fPlatform.hFreeamp);
        DestroyWindow(This->fPlatform.hImportWnd); 
        DestroyWindow(This->fPlatform.hDeleteWnd); 
	}

	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformSetWindow( PluginInstance* This, NPWindow* window )
{
    SIZE sSize;
    HDC  hDc;
    RECT sRect;
    
	if( This->fWindow != NULL ) /* If we already have a window, clean
								 * it up before trying to subclass
								 * the new window. */
	{
		if( (window == NULL) || ( window->window == NULL ) ) {
			/* There is now no window to use. get rid of the old
			 * one and exit. */
			SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);
			This->fPlatform.fDefaultWindowProc = NULL;
			This->fPlatform.fhWnd = NULL;
			return NPERR_NO_ERROR;
		}

		else if ( This->fPlatform.fhWnd == (HWND) window->window ) {
			/* The new window is the same as the old one. Redraw and get out. */

			InvalidateRect( This->fPlatform.fhWnd, NULL, TRUE );

			UpdateWindow( This->fPlatform.fhWnd );


			return NPERR_NO_ERROR;
		}
		else {
			/* Clean up the old window, so that we can subclass the new
			 * one later. */
			SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);
			This->fPlatform.fDefaultWindowProc = NULL;
			This->fPlatform.fhWnd = NULL;
		}
	}
	else if( (window == NULL) || ( window->window == NULL ) ) {
		/* We can just get out of here if there is no current
		 * window and there is no new window to use. */
		return NPERR_NO_ERROR;
	}

	/* At this point, we will subclass
	 * window->window so that we can begin drawing and
	 * receiving window messages. */
	This->fPlatform.fDefaultWindowProc = (WNDPROC)SetWindowLong( (HWND)window->window, GWL_WNDPROC, (LONG)PluginWindowProc);
	This->fPlatform.fhWnd = (HWND) window->window;
	SetProp( This->fPlatform.fhWnd, gInstanceLookupString, (HANDLE)This);


    hDc = GetDC(This->fPlatform.fhWnd);
    GetTextExtentPoint32(hDc, "j100%", 4, &sSize);
    ReleaseDC(This->fPlatform.fhWnd, hDc);
    GetClientRect(This->fPlatform.fhWnd, &sRect);

    This->fPlatform.sBorder.left = (sRect.right - sRect.left) / 2 - iBoxWidth;
    This->fPlatform.sBorder.right = (sRect.right - sRect.left) / 2 + iBoxWidth;
    This->fPlatform.sBorder.top = (sRect.bottom - sRect.top) / 2 - (sSize.cy * 8);
    This->fPlatform.sBorder.bottom = (sRect.bottom - sRect.top) / 2 + (sSize.cy * 7);

    This->fPlatform.sImportRect.left = This->fPlatform.sBorder.left + 10; 
    This->fPlatform.sImportRect.top = This->fPlatform.sBorder.top + (sSize.cy * 9) + (sSize.cy / 2);
    This->fPlatform.sImportRect.right = This->fPlatform.sImportRect.left +
        ((This->fPlatform.sBorder.right - This->fPlatform.sBorder.left) / 2) - 20;
    This->fPlatform.sImportRect.bottom = This->fPlatform.sImportRect.top + 20;

    This->fPlatform.sDeleteRect.left = 
       (This->fPlatform.sBorder.left + (This->fPlatform.sBorder.right - This->fPlatform.sBorder.left) / 2) + 10,
    This->fPlatform.sDeleteRect.top = This->fPlatform.sImportRect.top;
    This->fPlatform.sDeleteRect.right = This->fPlatform.sBorder.right - 10;
    This->fPlatform.sDeleteRect.bottom = This->fPlatform.sImportRect.bottom;
    
    This->fPlatform.hImportWnd = CreateWindow("BUTTON", "Import into MyMusic", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,  
        This->fPlatform.sImportRect.left, This->fPlatform.sImportRect.top,
        This->fPlatform.sImportRect.right - This->fPlatform.sImportRect.left,
        This->fPlatform.sImportRect.bottom - This->fPlatform.sImportRect.top,
        This->fPlatform.fhWnd, (HMENU)iImportButton, (HANDLE)g_hInst, NULL);
    This->fPlatform.hDeleteWnd = CreateWindow("BUTTON", "Delete after playing", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 
        This->fPlatform.sDeleteRect.left, This->fPlatform.sDeleteRect.top,
        This->fPlatform.sDeleteRect.right - This->fPlatform.sDeleteRect.left,
        This->fPlatform.sDeleteRect.bottom - This->fPlatform.sDeleteRect.top,
        This->fPlatform.fhWnd, (HMENU)iDeleteButton, (HANDLE)g_hInst, NULL);

    SendMessage(This->fPlatform.hImportWnd, BM_SETCHECK, 1, 0);
    SendMessage(This->fPlatform.hDeleteWnd, BM_SETCHECK, 0, 0);

    //EnableWindow(This->fPlatform.hDeleteWnd, FALSE);
    //EnableWindow(This->fPlatform.hImportWnd, FALSE);

	InvalidateRect( This->fPlatform.fhWnd, NULL, TRUE );
	UpdateWindow( This->fPlatform.fhWnd );
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int16
PlatformHandleEvent( PluginInstance* This, void* event )
{
	/* Windows Plugins use the Windows event call-back mechanism
	   for events. (See PluginWindowProc) */
	return 0;
}

void Paint(PluginInstance* This, HWND hWnd, HDC hdc)
{
    RECT    sRect, sBorder, sFill;
    HDC     hMemDc;
    SIZE    sSize;
    LOGFONT sFont;
    HFONT   hFont, hSmallFont, hOldFont;
    HBRUSH  hBrush, hOldBrush;
    BITMAP  sInfo;
    char    szPercent[16];

    sBorder = This->fPlatform.sBorder;

    memset(&sFont, 0, sizeof(LOGFONT));
    sFont.lfHeight = 20;
    strcpy(sFont.lfFaceName, "Arial");
    hFont = CreateFontIndirect(&sFont);
    sFont.lfHeight = 12;
    hSmallFont = CreateFontIndirect(&sFont);

    hOldFont = SelectObject(hdc, hFont);
    GetClientRect(hWnd, &sRect);

    // Fill the left side
    sFill.left = 0;
    sFill.top = 0;
    sFill.bottom = sRect.bottom;
    sFill.right = sBorder.left;
    FillRect(hdc, &sFill, GetStockObject(BLACK_BRUSH));

    // Fill the top side
    sFill.left = sBorder.left;
    sFill.top = 0;
    sFill.bottom = sBorder.top;
    sFill.right = sBorder.right;
    FillRect(hdc, &sFill, GetStockObject(BLACK_BRUSH));

    // Fill the right side
    sFill.left = sBorder.right;
    sFill.top = 0;
    sFill.bottom = sRect.bottom;
    sFill.right = sRect.right;
    FillRect(hdc, &sFill, GetStockObject(BLACK_BRUSH));

    // Fill the bottom side
    sFill.left = sBorder.left;
    sFill.top = sBorder.bottom;
    sFill.right = sBorder.right;
    sFill.bottom = sRect.bottom;
    FillRect(hdc, &sFill, GetStockObject(BLACK_BRUSH));

    if (This->fPlatform.sProgressRect.left == -1)
    {
        This->fPlatform.sProgressRect.left = 
           ((sRect.right - sRect.left) / 2) - 100;
        This->fPlatform.sProgressRect.right = 
            This->fPlatform.sProgressRect.left + 200; 
    }

    GetTextExtentPoint32(hdc, "j100%", 4, &sSize);
    sSize.cy -= 3;
    
    sRect.top = (sRect.bottom - sRect.top) / 2 - (sSize.cy * 7);
    sRect.left = sBorder.left;
    sRect.right = sBorder.right;

    DrawText(hdc, szText1, strlen(szText1), &sRect, DT_CENTER);
    sRect.top += sSize.cy * 2;
    
    DrawText(hdc, This->szFileName, strlen(This->szFileName), &sRect, DT_CENTER);
    sRect.top += sSize.cy * 2;
    
    DrawText(hdc, szText2, strlen(szText2), &sRect, DT_CENTER);
    sRect.top += sSize.cy * 2;

    if (This->fPlatform.sProgressRect.top == -1)
    {
        This->fPlatform.sProgressRect.top = sRect.top;
        This->fPlatform.sProgressRect.bottom = sRect.top + 20;
    }

    sRect = This->fPlatform.sProgressRect;
    MoveToEx(hdc, sRect.left, sRect.top, NULL);
    LineTo(hdc, sRect.right, sRect.top);
    LineTo(hdc, sRect.right, sRect.bottom);
    LineTo(hdc, sRect.left, sRect.bottom);
    LineTo(hdc, sRect.left, sRect.top);

    hBrush = CreateSolidBrush(GetSysColor(COLOR_ACTIVECAPTION));

    hOldBrush = SelectObject(hdc, hBrush);
    Rectangle(hdc, sRect.left, sRect.top, 
              sRect.left + (This->iPercentDone * 2) + 1, sRect.bottom + 1);

    sprintf(szPercent, "%d%%   ", This->iPercentDone);
    TextOut(hdc, sRect.right + 5, sRect.top, szPercent, strlen(szPercent));
    
    DeleteObject(hBrush);

    hMemDc = CreateCompatibleDC(hdc);

    GetObject(This->fPlatform.hEmusic, sizeof(BITMAP), &sInfo);
    SelectObject(hMemDc, This->fPlatform.hEmusic);
    BitBlt(hdc, sBorder.right - sInfo.bmWidth, 
                sBorder.bottom - sInfo.bmHeight,
                sInfo.bmWidth, sInfo.bmHeight,
           hMemDc, 0, 0, SRCCOPY);

    if (This->bFreeAmp)
    {
        GetObject(This->fPlatform.hFreeamp, sizeof(BITMAP), &sInfo);
        SelectObject(hMemDc, This->fPlatform.hFreeamp);
        BitBlt(hdc, sBorder.left,
                    sBorder.bottom - sInfo.bmHeight,
                    sInfo.bmWidth, sInfo.bmHeight,
               hMemDc, 0, 0, SRCCOPY);

        sRect.left = sBorder.left + sInfo.bmWidth;
        sRect.top = sBorder.bottom - sInfo.bmHeight;
        sRect.right = sBorder.right - sInfo.bmWidth;
        sRect.bottom = sBorder.bottom;
    }
    else
    {
        sRect.left = sBorder.left;
        sRect.top = sBorder.bottom - sInfo.bmHeight;
        sRect.right = sBorder.right - sInfo.bmWidth;
        sRect.bottom = sBorder.bottom;
    }    

    hBrush = CreateSolidBrush(RGB(153, 153, 153));
    FillRect(hdc, &sRect, hBrush);
    DeleteObject(hBrush);
          
    hBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    sRect = This->fPlatform.sBorder;
    sRect.top = This->fPlatform.sImportRect.top - 2;
    sRect.bottom = This->fPlatform.sBorder.bottom - sInfo.bmHeight;
    FillRect(hdc, &sRect, hBrush);
    DeleteObject(hBrush);

    if (This->bFreeAmp)
    {
       SelectObject(hdc, hSmallFont);
       GetTextExtentPoint32(hdc, szSponsor, strlen(szSponsor), &sSize);
       SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
       TextOut(hdc, sBorder.right - (sSize.cx + 2), 
            This->fPlatform.sBorder.bottom - sInfo.bmHeight - (sSize.cy + 2),
            szSponsor, strlen(szSponsor));
    }

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldFont);      
    DeleteObject(hFont);
    DeleteObject(hSmallFont);
    DeleteDC(hMemDc);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PluginWindowProc
 *
 * Handle the Windows window-event loop.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
LRESULT CALLBACK PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	PluginInstance* This = (PluginInstance*) GetProp(hWnd, gInstanceLookupString);

	switch( Msg ) {
		case WM_PAINT: {
			PAINTSTRUCT paintStruct;
			HDC hdc;

			hdc = BeginPaint( hWnd, &paintStruct );
            Paint(This, hWnd, hdc);
			EndPaint( hWnd, &paintStruct );
			break;
		}
        case WM_SIZE: {
            RECT sRect;
            HDC  hDc;
            SIZE sSize;
            
            hDc = GetDC(This->fPlatform.fhWnd);
            GetTextExtentPoint32(hDc, "j100%", 4, &sSize);
            ReleaseDC(This->fPlatform.fhWnd, hDc);
            GetClientRect(hWnd, &sRect);
            
            This->fPlatform.sProgressRect.top = -1;
            This->fPlatform.sProgressRect.left = -1;
            
            This->fPlatform.sBorder.left = (sRect.right - sRect.left) / 2 - iBoxWidth;
            This->fPlatform.sBorder.right = (sRect.right - sRect.left) / 2 + iBoxWidth;
            This->fPlatform.sBorder.top = (sRect.bottom - sRect.top) / 2 - (sSize.cy * 8);
            This->fPlatform.sBorder.bottom = (sRect.bottom - sRect.top) / 2 + (sSize.cy * 7);
        
            This->fPlatform.sImportRect.left = This->fPlatform.sBorder.left + 10; 
            This->fPlatform.sImportRect.top = This->fPlatform.sBorder.top + (sSize.cy * 9) + (sSize.cy / 2);
            This->fPlatform.sImportRect.right = This->fPlatform.sImportRect.left +
                ((This->fPlatform.sBorder.right - This->fPlatform.sBorder.left) / 2) - 20;
            This->fPlatform.sImportRect.bottom = This->fPlatform.sImportRect.top + 20;
        
            This->fPlatform.sDeleteRect.left = 
               (This->fPlatform.sBorder.left + (This->fPlatform.sBorder.right - This->fPlatform.sBorder.left) / 2) + 10,
            This->fPlatform.sDeleteRect.top = This->fPlatform.sImportRect.top;
            This->fPlatform.sDeleteRect.right = This->fPlatform.sBorder.right - 10;
            This->fPlatform.sDeleteRect.bottom = This->fPlatform.sImportRect.bottom;
            
            SetWindowPos(This->fPlatform.hImportWnd, NULL, 
                This->fPlatform.sImportRect.left,
                This->fPlatform.sImportRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            SetWindowPos(This->fPlatform.hDeleteWnd, NULL, 
                This->fPlatform.sDeleteRect.left,
                This->fPlatform.sDeleteRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == iImportButton)
            {
               SendMessage(This->fPlatform.hImportWnd, BM_SETCHECK, 1, 0);
               SendMessage(This->fPlatform.hDeleteWnd, BM_SETCHECK, 0, 0);
            }   
            if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == iDeleteButton)
            {
               SendMessage(This->fPlatform.hImportWnd, BM_SETCHECK, 0, 0);
               SendMessage(This->fPlatform.hDeleteWnd, BM_SETCHECK, 1, 0);
            }   
        
        }
		default: {
			This->fPlatform.fDefaultWindowProc( hWnd, Msg, wParam, lParam);
		}
	}
	return 0;
}

