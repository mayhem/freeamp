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

        $Id: database.cpp,v 1.1.2.2 1999/09/16 00:03:58 ijr Exp $
____________________________________________________________________________*/


#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "gdbm_fa.h"
#include "mutex.h"
#include "errors.h"
#include "database.h"

#ifdef WIN32
#define S_IRWXU _S_IREAD|_S_IWRITE
#endif

Database::Database(const char *name)
{
    m_dbase = NULL;

    assert(name);

    m_lock = new Mutex();
    m_dbase = gdbm_open((char *)name, 0, GDBM_WRCREAT, S_IRWXU, NULL);
    
    assert(m_dbase);
}

Database::~Database()
{
    m_lock->Acquire();
    if (m_dbase)
        gdbm_close(m_dbase);
    delete m_lock;
}

int Database::Insert(const char *key, char *content)
{
    datum gdbmKey;
    datum gdbmContent;
    int returnValue;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;
    gdbmContent.dptr = content;
    gdbmContent.dsize = strlen(content) + 1;

    m_lock->Acquire();
    returnValue = gdbm_store(m_dbase, gdbmKey, gdbmContent, GDBM_REPLACE);
    m_lock->Release();

   if (returnValue != 0)
       return kError_DbaseItemNotStored;
   return kError_NoErr;
}

void Database::Remove(const char *key)
{
    datum gdbmKey;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;

    m_lock->Acquire();
    gdbm_delete(m_dbase, gdbmKey);
    m_lock->Release();
}

char *Database::Value(const char *key)
{
    datum gdbmKey;
    datum returnData;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;

    m_lock->Acquire();
    returnData = gdbm_fetch(m_dbase, gdbmKey);
    m_lock->Release();

    if (returnData.dptr == NULL)
       return NULL; // deal with not found error..

    char *returninfo = new char[returnData.dsize];
    strcpy(returninfo, returnData.dptr);
    free(returnData.dptr);

    return returninfo;
}

int Database::Exists(const char *key)
{
    datum gdbmKey;
    int found;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;

    m_lock->Acquire();
    found = gdbm_exists(m_dbase, gdbmKey);
    m_lock->Release();

    return found;
}

char *Database::NextKey(const char *key)
{
    datum returnKey;
    char *nextKey;

    m_lock->Acquire();
    if (key)
    {
        datum gdbmKey;
        gdbmKey.dptr = (char *)key;
        gdbmKey.dsize = strlen(key) + 1;

        returnKey = gdbm_nextkey(m_dbase, gdbmKey);
    }
    else
        returnKey = gdbm_firstkey(m_dbase);

    if (!returnKey.dptr) {
        m_lock->Release();
        return NULL;
    }
 
    nextKey = new char[returnKey.dsize]; 
    strcpy(nextKey, returnKey.dptr);

    free(returnKey.dptr);

    m_lock->Release();

    return nextKey;
}

void Database::Sync(void)
{
    m_lock->Acquire();
    gdbm_sync(m_dbase);
    m_lock->Release();
}
