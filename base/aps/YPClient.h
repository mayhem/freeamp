/*_______________________________________________________________________        
        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 2000 Relatable

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id: YPClient.h,v 1.4 2000/09/29 12:13:57 ijr Exp $
____________________________________________________________________________*/

#ifndef YPCLIENT_H
#define YPCLIENT_H

#include <iostream>
#include <string>
#include <vector>
// Any other includes go here
#include "apsconvert.h"

using namespace std;

class COMHTTPSocket;
class Mutex;
// Any other class declares for function params go here
typedef vector<pair<string, string> > StreamList;

class YPClient
{
public:
    YPClient();
   ~YPClient();
    void SetAddress(string strIP, int nPort) 
    { m_strIP = strIP, m_nPort = nPort; }
    void SetProxy(string strAddr, int nPort)
    { m_proxyAddr = strAddr; m_proxyPort = nPort; }
    int SoundsLike(APSPlaylist& ResultList, APSPlaylist& SeedList, 
			string& strCollectionID);
    int GeneratePlayList(APSPlaylist& ResultList, APSPlaylist& SeedList,
                         int nMaxItems, int bLocalOnly, string& strUID,
                         string& CollectionID);
    int SubmitPlaylist(APSPlaylist& SeedList, string& strUID);
    int GetGUID(string& strGUID, int nSeed);
    int GetStreams(StreamList& ResultList, string& strUID, 
			string& strCollectionID);
    int DeleteProfile(string& strUID);
    int SyncLog(EventLog& TheLog, string& strUID);

protected:
    int Connect(string& strIP, int nPort);
    int Disconnect();

private:
    COMHTTPSocket* m_pSocket;
    Mutex* m_pMutex;
    string m_strIP;
    int m_nPort;
    string m_proxyAddr;
    int m_proxyPort;
};

#endif
