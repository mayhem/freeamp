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
	
	$Id: updatemanager.h,v 1.1.2.2 1999/10/04 23:15:07 elrod Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_UPDATE_MANAGER_H_
#define INCLUDED_UPDATE_MANAGER_H_

#include <assert.h>
#include <string>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

#include "config.h"
#include "facontext.h"

#include "errors.h"
#include "mutex.h"
#include "semaphore.h"
#include "thread.h"

#define kInvalidIndex 0xFFFFFFFF

typedef enum {
    kUMEvent_Status,
    kUMEvent_Progress,
    kUMEvent_Error,
    kUMEvent_Done

} UMEventType;

#define kUMProgressInfinity -1

class UpdateItem;

typedef struct UMEventProgressData {
    uint32 position;
    uint32 total;
    UpdateItem* item;
} UMEventProgressData;

typedef struct UMEventErrorData {
    uint32 errorCode;
} UMEventErrorData;

typedef union UMEventData {
    UMEventProgressData progressData;
    UMEventErrorData    errorData;
} UMEventData;

typedef struct UMEvent {
    UMEventType type;
    UMEventData data;
    string eventString;
} UMEvent;

typedef bool (*UMCallBackFunction)(UMEvent* event, void* userData);

class UpdateItem {
 public:
    virtual ~UpdateItem() { }
    
    void SetLocalFile(const string& path) { m_localFile = path; }
    const string& GetLocalFile() const { return m_localFile; }

    void SetCurrentFile(const string& url) { m_currentFile = url; }
    const string& GetCurrentFile() const { return m_currentFile; }

    void SetLocalFileVersion(const string& version) { m_localVersion = version; }
    const string& GetLocalFileVersion() const { return m_localVersion; }

    void SetCurrentFileVersion(const string& version) { m_currentVersion = version; }
    const string& GetCurrentFileVersion() const { return m_currentVersion; }

 protected:

 private:
    string m_localVersion;
    string m_localFile;
    string m_currentVersion;
    string m_currentFile;
};

class UpdateManager {

 public:
    virtual ~UpdateManager();
    
    virtual Error DetermineLocalVersions() { return kError_FeatureNotSupported; }
    virtual Error RetrieveLatestVersionInfo(UMCallBackFunction function,
                                            void* cookie);
    virtual Error UpdateComponents(UMCallBackFunction function,
                                   void* cookie);

    // Utility Functions
    bool            IsEmpty();
    uint32          CountItems();
    UpdateItem*     ItemAt(uint32 index);
	uint32          IndexOf(UpdateItem* item);
    bool            HasItem(UpdateItem* item);

 protected:

 private:

    FAContext* m_context;

    Mutex m_mutex;

    vector<UpdateItem*> m_itemList;

    Registry m_formatRegistry;
   
    Thread* m_downloadThread;
    volatile bool m_runUpdateThread;

    Mutex m_quitMutex;

};

#endif // INCLUDED_UPDATE_MANAGER_H_










