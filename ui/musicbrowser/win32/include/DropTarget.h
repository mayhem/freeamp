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

        $Id: DropTarget.h,v 1.1 1999/11/07 02:06:23 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_DROPTARGET_H_
#define INCLUDED_DROPTARGET_H_

#include <ole2.h>

#define WM_DROPURLS WM_USER + 92173

class FAR DropTarget : public IDropTarget
{
 public:    
    DropTarget(HWND hwnd);
	~DropTarget ();
    void Enable(BOOL bEnable);

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);

    /* IDropTarget methods */
    STDMETHOD(DragEnter)(LPDATAOBJECT pDataObj, DWORD grfKeyState, 
        POINTL pt, LPDWORD pdwEffect);
    STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect);
    STDMETHOD(DragLeave)();
    STDMETHOD(Drop)(LPDATAOBJECT pDataObj, DWORD grfKeyState, 
        POINTL pt, LPDWORD pdwEffect); 
 
 private:
    ULONG m_refs;  
	HWND m_hwnd;
    BOOL m_bAcceptFmt;
	BOOL m_bEnabled;
	POINT m_ptPrevious;
	ULONG m_uDEPrevious;
};  

#endif // INCLUDED_DROPTARGET_H_