/*____________________________________________________________________________
	
	FreeAMP - The Free MP3 Player
	Portions copyright (C) 1998 GoodNoise

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
	
	$Id: registrar.h,v 1.2 1998/10/15 13:33:50 elrod Exp $
____________________________________________________________________________*/

#ifndef _REGISTRAR_H_
#define _REGISTRAR_H_

#include "error.h"
#include "registry.h"
/*#include "lmcregistry.h"
#include "pmoregistry.h"
#include "pmiregistry.h"
#include "uiregistry.h"*/

class Registrar{
 public:
    Registrar(){m_subdir = NULL; m_search = NULL;}
    ~Registrar(){}

    Error InitializeRegistry(Registry* registry);
    static Error CleanupRegistry(Registry* registry);

    void SetSubDir(const char* subdir){m_subdir = subdir;}
    const char* SubDir(void) const {return m_subdir;}
    void SetSearchString(const char* search){m_search = search;}
    const char* SearchString(void) const {return m_search;}

 private:
    const char* m_subdir;
    const char* m_search;
    
};

//Error InitializeLMCRegistry(LMCRegistry* registry);
//Error InitializePMORegistry(PMORegistry* registry);
//Error InitializePMIRegistry(PMIRegistry* registry);
//Error InitializeUIRegistry(UIRegistry* registry);


#endif // _REGISTRAR_H_