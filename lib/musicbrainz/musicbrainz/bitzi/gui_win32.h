/* (PD) 2001 The Bitzi Corporation
 * Please see file COPYING or http://bitzi.com/publicdomain 
 * for more info.
 *
 * $Id: gui_win32.h,v 1.5 2001/10/30 20:19:15 robert Exp $
 */

#ifndef GUI_WIN32_H
#define GUI_WIN32_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif

DWORD WINAPI BitcolliderThread(LPVOID arg);
extern HWND init_gui(void);
extern void win32_progress_callback(int percent, const char *file, const char *message);

#ifdef __cplusplus
}
#endif

#endif
