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
	
	$Id: propimpl.cpp,v 1.1 1999/01/23 00:22:26 jdw Exp $
____________________________________________________________________________*/

#include "propimpl.h"

PropertiesImpl::PropertiesImpl() {
    m_props = new HashTable<PropElem *>(30);
}

PropertiesImpl::~PropertiesImpl() {
    if (m_props) {
	delete m_props;
	m_props = NULL;
    }
}

Error PropertiesImpl::GetProperty(const char *pProp, void **ppVal) {
    Error rtn = kError_UnknownErr;
    m_lock.Acquire();
    if (pProp) {
	if (m_props) {
	    PropElem *ppe = m_props->Value(pProp);
	    if (ppe) {
		if (ppVal) {
		    *ppVal = ppe->m_val;
		    rtn = kError_NoErr;
		}
	    }
	}
    }
    m_lock.Release();
    return rtn;
}

Error PropertiesImpl::SetProperty(const char *pProp, void *pVal, bool deleteWhenDone) {
    Error rtn = kError_UnknownErr;
    m_lock.Acquire();
    if (m_props) {
	if (pProp) {
	    PropElem *ppe = m_props->Value(pProp);
	    bool needToInsert = false;
	    if (!ppe) {
		ppe = new PropElem();
		needToInsert = true;
	    }
	    if (ppe) {
		if (ppe->m_deleteWhenDone && ppe->m_val) {
		    free(ppe->m_val);
		}
		ppe->m_val = pVal;
		ppe->m_deleteWhenDone;
		if (needToInsert) {
		    m_props->Insert(pProp, ppe);
		}
		PropertyWatcher *pw = NULL;
		for(int i = 0;i<ppe->m_propWatchers.NumElements();i++) {
		    pw = ppe->m_propWatchers.ElementAt(i);
		    if (pw) {
			pw->PropertyChange(pProp, pVal);
		    }
		}

		rtn = kError_NoErr;
	    }
	}
    }
    m_lock.Release();
    return rtn;
}

Error PropertiesImpl::RegisterPropertyWatcher(const char *pProp, PropertyWatcher *pw) {
    Error rtn = kError_UnknownErr;
    m_lock.Acquire();

    if (m_props) {
	if (pProp) {
	    PropElem *ppe = m_props->Value(pProp);
	    if (ppe) {
		ppe->m_propWatchers.Insert(pw);
		rtn = kError_NoErr;
	    }
	}
    }

    m_lock.Release();
    return rtn;
}

Error PropertiesImpl::RemovePropertyWatcher(const char *pProp, PropertyWatcher *pw) {
    Error rtn = kError_UnknownErr;
    m_lock.Acquire();

    if (m_props) {
	if (pProp) {
	    PropElem *ppe = m_props->Value(pProp);
	    if (ppe) {
		int32 endNum = ppe->m_propWatchers.NumElements();
		for (int i = 0; i < endNum ; i++) {
		    if (pw == ppe->m_propWatchers.ElementAt(i)) {
			ppe->m_propWatchers.RemoveElementAt(i);
			endNum--;
		    }
		}
		rtn = kError_NoErr;
	    }
	}
    }

    m_lock.Release();
    return rtn;

}



