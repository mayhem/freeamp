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

        $Id: database.h,v 1.1.2.2 1999/08/18 23:00:23 elrod Exp $
____________________________________________________________________________*/


#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <sys/stat.h>
#include "gdbm.h"
#include "mutex.h"
#include "errors.h"

#ifdef WIN32
#define S_IRWXU _S_IREAD|_S_IWRITE
#endif

template<class T> class Database
{
 public:
   Database(const char *name = NULL);
   ~Database();
  
   int   Insert(const char *key, T content);
   void  Remove(const char *key);
   T     Value(const char *key);
   int   Exists(const char *key);
   char *NextKey(const char *key);
   void  Sync(void);

 private:
   GDBM_FILE m_dbase;
   Mutex     *m_lock;
};


template<class T> Database<T>::Database(const char *name)
{
    if (name == NULL)
        return;
    m_lock = new Mutex();
    m_dbase = gdbm_open((char *)name, 0, GDBM_WRCREAT, S_IRWXU, NULL);
}

template<class T> Database<T>::~Database()
{
    m_lock->Acquire();
    gdbm_close(m_dbase);
    delete m_lock;
}

template<class T> int Database<T>::Insert(const char *key, T content)
{
    datum gdbmKey;
    datum gdbmContent;
    int returnValue;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;
    gdbmContent.dptr = (char *)&content;
    gdbmContent.dsize = sizeof(T);

    m_lock->Acquire();
    returnValue = gdbm_store(m_dbase, gdbmKey, gdbmContent, GDBM_REPLACE);
    m_lock->Release();

   if (returnValue != 0)
       return kError_DbaseItemNotStored;
   return kError_NoErr;
}

template<class T> void Database<T>::Remove(const char *key)
{
    datum gdbmKey;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;

    m_lock->Acquire();
    gdbm_delete(m_dbase, gdbmKey);
    m_lock->Release();
}

template<class T> T Database<T>::Value(const char *key)
{
    datum gdbmKey;
    datum returnData;
    T     Info;

    gdbmKey.dptr = (char *)key;
    gdbmKey.dsize = strlen(key) + 1;

    m_lock->Acquire();
    returnData = gdbm_fetch(m_dbase, gdbmKey);
    m_lock->Release();

    if (returnData.dptr == NULL)
       return NULL; // deal with not found error..

    memcpy(&Info, returnData.dptr, returnData.dsize);
    free(returnData.dptr);

    return Info;
}

template<class T> int Database<T>::Exists(const char *key)
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

template<class T> char *Database<T>::NextKey(const char *key)
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
  
    nextKey = strdup_new(gdbmKey.dptr);
    free(gdbmKey.dptr);

    m_lock->Release();

    return nextKey;
}

template<class T> void Database<T>::Sync(void)
{
    m_lock->Acquire();
    gdbm_sync(m_dbase);
    m_lock->Release();
}

#endif
   
