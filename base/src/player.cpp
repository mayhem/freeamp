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
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id: player.cpp,v 1.133.2.8 1999/08/30 22:35:20 ijr Exp $
____________________________________________________________________________*/

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "config.h"
#include "event.h"
#include "lmc.h"
#include "player.h"
#include "thread.h"
#include "debug.h"
#include "ui.h"
#include "queue.h"
#include "semaphore.h"
#include "eventdata.h"
#include "registrar.h"
#include "preferences.h"
#include "properties.h"
#include "facontext.h"
#include "log.h"
#include "pmo.h"

#define DB printf("%s:%d\n", __FILE__, __LINE__);

Player   *Player::m_thePlayer = NULL;

const char *szPlaylistExt = ".M3U";

#define SEND_NORMAL_EVENT(e) { Event *ev = new Event(e); GetUIManipLock();    \
                               SendToUI(ev); ReleaseUIManipLock(); delete ev; \
                             }


Player *
Player::
GetPlayer(FAContext *context)
{
   if (m_thePlayer == NULL)
      m_thePlayer = new Player(context);
   return m_thePlayer;
}

Player::
Player(FAContext *context):
EventQueue()
{
   m_context = context;
   // cout << "Creating player..." << endl;
   m_eventSem = new Semaphore();
   m_eventQueue = new Queue < Event * >();
   // cout << "Created queue" << endl;
   m_eventServiceThread = NULL;
   // cout << "Started event thread" << endl;
   m_uiList = new vector < UserInterface * >;
   // cout << "Created Lists" << endl;
   m_uiManipLock = new Mutex();
   m_lmcMutex = new Mutex();
   m_pmiMutex = new Mutex();
   m_pmoMutex = new Mutex();
   m_uiMutex = new Mutex();
   // cout << "Created mutex" << endl;
   m_imQuitting = 0;
   m_quitWaitingFor = 0;
   m_plm = new PlaylistManager(m_context);
   m_playerState = PlayerState_Stopped;

   m_lmcRegistry = NULL;
   m_pmiRegistry = NULL;
   m_pmoRegistry = NULL;
   m_uiRegistry = NULL;
   
   m_lmcExtensions = NULL;
   m_musicSearch = NULL;
   // m_musicSearch = new MusicSearch("/tmp/dbase");
 
   m_pmo = NULL;
   m_lmc = NULL;
   m_ui = NULL;

   m_argUIList = new vector < char *>();

   m_argc = 0;
   m_argv = NULL;
   m_pTermSem = NULL;

   m_didUsage = false;
   m_autoplay = true;

   m_iVolume = -1;

   m_props.RegisterPropertyWatcher("pcm_volume", (PropertyWatcher *) this);
}

#define TYPICAL_DELETE(x) /*printf("deleting...\n");*/ if (x) { delete x; x = NULL; }

Player::
~Player()
{
   TYPICAL_DELETE(m_pTermSem);
   TYPICAL_DELETE(m_argUIList);

   if (m_eventServiceThread)
   {
      m_eventServiceThread->Join();
      delete    m_eventServiceThread;

      m_eventServiceThread = NULL;
   }

   if (m_pmo)
   {
      m_pmo->Pause();
      delete    m_pmo;

      m_pmo = NULL;
   }

   TYPICAL_DELETE(m_eventSem);
   TYPICAL_DELETE(m_eventQueue);

   // Delete CIOs
   if (m_uiList)
   {
        vector<UserInterface *>::iterator i = m_uiList->begin();

        for (; i != m_uiList->end(); i++)
            delete *i; 
        delete m_uiList;

      m_uiList = NULL;
   }

   TYPICAL_DELETE(m_plm);
   TYPICAL_DELETE(m_uiManipLock);
   TYPICAL_DELETE(m_lmcMutex);
   TYPICAL_DELETE(m_pmiMutex);
   TYPICAL_DELETE(m_pmoMutex);
   TYPICAL_DELETE(m_uiMutex);
   TYPICAL_DELETE(m_lmcRegistry);
   TYPICAL_DELETE(m_pmiRegistry);
   TYPICAL_DELETE(m_pmoRegistry);
   TYPICAL_DELETE(m_uiRegistry);
   TYPICAL_DELETE(m_lmcExtensions);
   TYPICAL_DELETE(m_musicSearch);
}

void      
Player::
SetTerminationSemaphore(Semaphore * pSem)
{
   m_pTermSem = pSem;
}

/*
   return true if parsing was successful, false otherwise. 
 */

typedef char *pchar;

bool      
Player::
SetArgs(int32 argc, char **argv)
{
   vector < char *>argList;
   bool      justGotArgvZero = false;
   char     *arg = NULL;
   char     *argUI = NULL;

#ifndef WIN32
   
   if (argc == 1)
   {
       Usage(argv[0]);
       exit(0);
   }

#if 0
   // grab the UI name from how we are invoked.
   argUI = new char[strlen(argv[0]) + 1 + 3];
   char     *pBegin = strrchr(argv[0], '/');

   if (pBegin)
   {
      pBegin++;
   }
   else
   {
      pBegin = argv[0];
   }
   strcpy(argUI, pBegin);
   m_argUIList->AddItem(argUI);
#endif

   justGotArgvZero = true;
#endif	// ndef WIN32

   argList.push_back(argv[0]);
   for (int32 i = 1; i < argc; i++)
   {
      arg = argv[i];

      if (arg[0] == '-')
      {
         switch (arg[1])
         {
         case 'h':
         case 'H':
         case '-':
            if (!strcmp(arg + 1, "help") || !strcmp(arg + 2, "help"))
            {
               Usage(argv[0]);
               exit(0);
            }
	    else
	       goto normalArg;
            break;
         case 'u':
         case 'U':
            {
               if (arg[2] == 'i' ||
                   arg[2] == 'I')
               {
                  i++;
                  if (i >= argc)
                  {
                     Usage(argv[0]);
                     AcceptEvent(new Event(CMD_QuitPlayer));
                     return false;
                  }
                  arg = argv[i];
                  // if (m_argUI) delete m_argUI;
                  argUI = new char[strlen(arg) + 1];

                  strcpy(argUI, arg);

                  if (justGotArgvZero)
                  {
                     vector<char *>::iterator i = m_argUIList->begin();

                     for (; i != m_argUIList->end(); i++)
                         delete *i;

                     justGotArgvZero = false;
                  }
                  m_argUIList->push_back(argUI);
               }
	       else
		  goto normalArg;
               break;
            }
	 case 's':
	 case 'S':
	    if (!strcmp(&(arg[2]), "ave"))
		m_context->argFlags |= FAC_ARGFLAGS_SAVE_STREAMS;
	    else
		goto normalArg;
	    break;
#if 0				// We use the prefs file now
         case 'p':
            if (!strcmp(&(arg[2]), "rop"))
            {
               // add in a Property=Value property
               i++;
               if (i >= argc)
               {
                  Usage(argv[0]);
                  AcceptEvent(new Event(CMD_QuitPlayer));
                  return false;
               }
               char     *pProp = argv[i];

               if (pProp)
               {
                  char     *pVal = strchr(pProp, '=');

                  if (pVal)
                  {
                     *pVal = '\0';
                     pVal++;
                     StringPropValue *spv = new StringPropValue(pVal);

                     m_props.SetProperty(pProp, (PropValue *) spv);
                  }
                  else
                  {
                     cerr << "Property string '" << pProp << "' is not valid.  Needs to be of the form Property=Value." << endl;
                     break;
                  }
               }
            }
            else
	       goto normalArg;
            break;
#endif
         default:
	 normalArg:
            argList.push_back(argv[i]);
	    break;
         }
      }
      else
	  {
		 char *pPtr;

		 pPtr = strrchr(argv[i], '.');
		 if (pPtr && strcasecmp(pPtr, szPlaylistExt) == 0)
		 { 
		 	/* 
            Error eRet;

		     eRet = m_plm->ExpandM3U(argv[i], argList);

		     if (IsError(eRet))
#ifndef WIN32
                printf("Error: Cannot open file '%s'.\n", argv[i]);
#else
                MessageBox(NULL, "Cannot open playlist file", argv[i], MB_OK); 
#endif
            */
		 }
		 else
             argList.push_back(argv[i]);
      }
   }
   m_argc = argList.size();
   if (m_argc)
   {
	   //LEAK-2
	   m_argv = new pchar[m_argc];
      for (int f = 0; f < m_argc; f++)
      {
         m_argv[f] = argList[f];
         // cerr << "Adding argument (" << f << "): " << m_argv[f] << endl;
      }
   }

   return true;
}

void      
Player::
Usage(const char *progname)
{
   if (m_didUsage)
      return;

   printf("FreeAmp version " FREEAMP_VERSION " -- Usage:\n\n");
   printf("freeamp [-save] [-ui <UI plugin name>] <MP3 file/stream> "
	  "[MP3 file/stream] ...\n\n");
   printf("Example command line:\n\n");
   printf("   freeamp -ui freeamp-linux.ui mysong1.mp3 mysong2.mp3\n\n");

   m_didUsage = true;
}

int32     
Player::
CompareNames(const char *p1, const char *p2)
{
// windows plugins and unix plugins are named differently...
#ifdef WIN32
   return strcmp(p1, p2);
#else
   // ut << "Comparing: " << p1 << " to " << p2 << endl;
   if (strcmp(p1, p2))
   {
      // no direct match, try w/ .ui appended...
      char      foo[512];

      sprintf(foo, "%s.ui", p2);
      // ut << "Comparing: " << p1 << " to " << foo << endl;
      if (strcmp(p1, foo))
      {
         // no plugin.ui match, try  plugin-arch.ui
         char      foo[512];

         sprintf(foo, "%s.ui", p2);
         // cout << "Comparing: " << p1 << " to " << foo << endl;
         if (strcmp(p1, foo))
         {
            // no match
            return 1;
         }
         else
         {
            return 0;
         }
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return 0;
   }
#endif
}

void      
Player::
Run()
{
   uint32    uiListIndex = 0;
   char     *name = NULL;
   uint32    len = 256;
   Error     error = kError_NoErr;
   int32     uisActivated = 0;
   bool      bValue;

   m_context->prefs->GetUseDebugLog(&bValue);
   if (bValue)
      m_context->log->Open();
   
   m_context->prefs->GetLogInput(&bValue);
   if (bValue)
      m_context->log->AddLogLevel(LogInput);
   
   m_context->prefs->GetLogOutput(&bValue);
   if (bValue)
      m_context->log->AddLogLevel(LogOutput);
   
   m_context->prefs->GetLogDecode(&bValue);
   if (bValue)
      m_context->log->AddLogLevel(LogDecode);
   
   m_context->prefs->GetLogPerformance(&bValue);
   if (bValue)
      m_context->log->AddLogLevel(LogPerf);

   // which ui should we instantiate first??
   if (m_argUIList->size() == 0)
   {
      const char *pref = kUIPref;
      name = new char[len];

#ifdef unix
      if (!getenv("DISPLAY"))
	  pref = kTextUIPref;
#endif
      while ((error = m_context->prefs->GetPrefString(pref, name, &len)) ==
             kError_BufferTooSmall)
      {
         delete[] name;
         len++;

         name = new char[len];
      }
   }
   else
   {
      char *orig = (*m_argUIList)[uiListIndex++];
      name = new char[strlen(orig) + 1];

      strcpy(name, orig);
   }

   if (IsntError(error))
   {
      while (*name)
      {
         RegistryItem *item = NULL;
//       UserInterface *ui = NULL;
         int32     i = 0;

         while (NULL != (item = m_uiRegistry->GetItem(i++)))
         {
            if (!CompareNames(item->Name(), name))
            {
               m_ui = (UserInterface *) item->InitFunction()(m_context);

               m_ui->SetTarget((EventQueue *) this);
               m_ui->SetPropManager((Properties *) this);
               m_ui->SetPlaylistManager(m_plm);
               m_ui->SetArgs(m_argc, m_argv);
               Error     er = m_ui->Init((uisActivated == 0) ? PRIMARY_UI
					 : SECONDARY_UI_STARTUP);
               if (IsntError(er))
               {
                  RegisterActiveUI(m_ui);
                  uisActivated++;
               }
               else
               {
                  delete    m_ui;

                  m_ui = NULL;
               }
               break;
            }
         }

         if(uiListIndex < m_argUIList->size())
         {
            char *p = (*m_argUIList)[uiListIndex++];
            strcpy(name, p);
         }
         else
         {
            *name = '\0';
         }
      }

      if (!uisActivated)
      {
#ifdef WIN32
         char      foo[1024];
         char      bar[MAX_PATH];
         uint32    size = MAX_PATH - 1;

         m_context->prefs->GetInstallDirectory(bar, &size);
         sprintf(foo, "No UI plugin matched 'plugins\\%s' or 'plugins\\%s.ui' in '%s'.  FreeAmp will quit.", name, name, bar);
         MessageBox(NULL, foo, "FreeAmp Error", MB_OK);
#else
         const char *thePath = getenv(FREEAMP_PATH_ENV);

         if (thePath == NULL)
          thePath = m_context->prefs->GetLibDirs();
         cerr << "No UI plugin in '" << thePath << "' matched 'plugins/" << name << "' or 'plugins/" << name << ".ui'" << endl;
         cerr << "FreeAmp will quit." << endl;
#endif
         Event    *e = new Event(CMD_QuitPlayer);

         AcceptEvent(e);
         e = new Event(INFO_ReadyToDieUI);
         AcceptEvent(e);
      }
   }
   m_eventServiceThread = Thread::CreateThread();
   m_eventServiceThread->Create(Player::EventServiceThreadFunc, this);

   delete[]name;
}

void 
Player::
EventServiceThreadFunc(void *pPlayer)
{
   Player   *pP = (Player *) pPlayer;
   Event    *pC;
   int32     rtnVal = 0x0;

   while (rtnVal == 0)
   {                            // serviceEvent will return 1 if error or time
      if (pP->m_eventQueue->Peek() == NULL)
          pP->m_eventSem->Wait();

      pC = pP->m_eventQueue->Read();
      if (pC)
      {
         rtnVal = pP->ServiceEvent(pC);
      }
   }
}

int32     
Player::
RegisterActiveUI(UserInterface * ui)
{
   GetUIManipLock();
   if (m_uiList && ui)
   {
      m_uiList->push_back(ui);
      ReleaseUIManipLock();
      return 0;
   }
   else
   {
      ReleaseUIManipLock();
      return 255;
   }
}

int32     
Player::
RegisterLMCs(Registry * registry)
{
   int32     result = 0;

   m_lmcMutex->Acquire();

   if (m_lmcRegistry)
   {
    Registrar::CleanupRegistry(m_lmcRegistry);
      delete    m_lmcRegistry;
   }

   if (m_lmcExtensions)
      delete m_lmcExtensions;

   m_lmcExtensions = new HashTable<RegistryItem *>();

   m_lmcRegistry = registry;

   RegistryItem *lmc_item;
   LogicalMediaConverter *lmc;
   int iItems = registry->CountItems();

   for (int iLoop = 0; iLoop < iItems; iLoop++)
   {
      RegistryItem* temp = registry->GetItem(iLoop);

      lmc = (LogicalMediaConverter *)temp->InitFunction()(m_context);
      vector<char *> *extList = lmc->GetExtensions();

      for (uint32 iextLoop = 0; iextLoop < extList->size(); iextLoop++)
      {
          lmc_item = new RegistryItem(*temp);
          m_lmcExtensions->Insert((*extList)[iextLoop], lmc_item);
      }

      delete extList;
      delete lmc;
   }

   m_lmcMutex->Release();

   return result;
}

int32     
Player::
RegisterPMIs(Registry * registry)
{
   int32     result = 0;

   m_pmiMutex->Acquire();

   if (m_pmiRegistry)
   {
    Registrar::CleanupRegistry(m_pmiRegistry);
      delete    m_pmiRegistry;
   }

   m_pmiRegistry = registry;

   m_pmiMutex->Release();

   return result;
}

int32     
Player::
RegisterPMOs(Registry * registry)
{
   int32     result = 0;

   m_pmoMutex->Acquire();

   if (m_pmoRegistry)
   {
    Registrar::CleanupRegistry(m_pmoRegistry);
      delete    m_pmoRegistry;
   }

   m_pmoRegistry = registry;

   m_pmoMutex->Release();

   return result;
}

int32     
Player::
RegisterUIs(Registry * registry)
{
   int32     result = 0;

   m_uiMutex->Acquire();

   if (m_uiRegistry)
   {
    Registrar::CleanupRegistry(m_uiRegistry);
      delete    m_uiRegistry;
   }

   m_uiRegistry = registry;

   m_uiMutex->Release();

   return result;
}

Registry* 
Player::
GetLMCRegistry() const
{
    return m_lmcRegistry;
}

Registry* 
Player::
GetPMIRegistry() const
{
    return m_pmiRegistry;
}

Registry* 
Player::
GetPMORegistry() const
{
    return m_pmoRegistry;
}

Registry*  
Player::
GetUIRegistry() const
{
    return m_uiRegistry;
}

void 
Player::
GetUIManipLock()
{
   m_uiManipLock->Acquire(WAIT_FOREVER);
}

void 
Player::
ReleaseUIManipLock()
{
   m_uiManipLock->Release();
}

int32 
Player::
AcceptEvent(Event * e)
{
   m_eventQueue->Write(e);
   m_eventSem->Signal();
   return 0;
}

bool 
Player::
SetState(PlayerState ps)
{
#if 0
   printf("Player state: ");
   switch(ps)
   {
       case PlayerState_Stopped:
          printf("Stopped.\n");
          break;
       case PlayerState_Paused:
          printf("Paused.\n");
          break;
       case PlayerState_Playing:
          printf("Playing.\n");
          break;
       default:
          printf("Unknown.\n");
          break;
   }
#endif
   if (ps == m_playerState)
      return false;
   m_playerState = ps;
   return true;
}

char *
Player::
GetExtension(const char *title)
{
   char *temp_ext;
   char *ext_return = NULL;

   temp_ext = strrchr(title, '.');
   if (temp_ext)
   {
      temp_ext = temp_ext + 1;
      ext_return = new char [strlen(temp_ext) + 1];
      strcpy(ext_return, temp_ext);
      char *p = ext_return;
      while (*p) {
         *p = toupper(*p);
         p++;
      }
   }
   return ext_return;
}

bool
Player::
IsSupportedExtension(const char *ext)
{
   RegistryItem *lmc_item = m_lmcExtensions->Value(ext);

   if (lmc_item)
       return true;
   return false;
}

RegistryItem *
Player::
ChooseLMC(const char *szUrl, char *szTitle)
{
   RegistryItem *lmc_item = NULL;
   char     *iExt;


   iExt = GetExtension(szUrl);
   if (!iExt)
      return lmc_item;

   lmc_item = m_lmcExtensions->Value(iExt);

   delete iExt;

   if (lmc_item)
      fprintf(stderr, "found plugin..\n");

   return lmc_item;
}

RegistryItem *
Player::
ChoosePMI(const char *szUrl, char *szTitle)
{
   PhysicalMediaInput *pmi;
   RegistryItem *pmi_item, *ret = NULL;
   int       iLoop;
   char     *szNewUrl = NULL;

   if (strstr(szUrl, "://") == NULL)
   {
      szNewUrl = new char[strlen(szUrl) + strlen("file:// ") + 1];

      sprintf(szNewUrl, "file://%s", szUrl);

      szUrl = szNewUrl;
   }

   for (iLoop = 0; iLoop < m_pmiRegistry->CountItems(); iLoop++)
   {
      pmi_item = m_pmiRegistry->GetItem(iLoop);

      pmi = (PhysicalMediaInput *) pmi_item->InitFunction()(m_context);
      if (pmi->CanHandle(szUrl, szTitle))
      {
         ret = pmi_item;
         delete pmi;

         break;
      }
      delete pmi;
   }

   if (szNewUrl)
      delete szNewUrl;

   return ret;
}

void 
Player::
CreatePMO(const PlaylistItem * pc, Event * pC)
{
   Error     error = kError_NoErr;
   Event    *e;
   PhysicalMediaOutput *pmo = NULL;
   PhysicalMediaInput *pmi = NULL;
   LogicalMediaConverter *lmc = NULL;
   RegistryItem *pmi_item = NULL;
   RegistryItem *lmc_item = NULL;
   RegistryItem *item;

   if (!pc)
   {
      m_plm->SetCurrentIndex(0);
      if (m_pmo)
      {
         m_pmo->Pause();
         delete m_pmo;

         m_pmo = NULL;
      }
      if (SetState(PlayerState_Stopped))
      {
         SEND_NORMAL_EVENT(INFO_Stopped);
      }
      GetUIManipLock();

      e = new Event(INFO_PlaylistDonePlay);
      SendToUI(e);

      ReleaseUIManipLock();

      delete e;
   }

   if (m_pmo)
   {
      m_pmo->Pause();
      delete    m_pmo;

      m_pmo = NULL;
   }

   pmi_item = ChoosePMI(pc->URL().c_str());
   if (!pmi_item)
   {
      char szErr[1024];

      sprintf(szErr, "Cannot determine what pmi to use for %s\n", pc->URL().c_str());
      m_context->log->Error(szErr);
      AcceptEvent(new LMCErrorEvent(szErr));

      return;
   }

   lmc_item = ChooseLMC(pc->URL().c_str());
   if (!lmc_item)
   // FIXME: Should probably have a user definable default LMC
      lmc_item = m_lmcRegistry->GetItem(0);

   if (pmi_item)
   {
      pmi = (PhysicalMediaInput *) pmi_item->InitFunction()(m_context);
      pmi->SetPropManager((Properties *) this);
      pmi->SetTarget((EventQueue *)this);
   }

   char defaultPMO[256];
   uint32 size = sizeof(defaultPMO);

   m_context->prefs->GetDefaultPMO(defaultPMO, &size);

   int32 i = 0;

   while (NULL != (item = m_pmoRegistry->GetItem(i++)))
   {
        if(!strcmp(defaultPMO, item->Name()))
        {
            break;
        }
   }

   // if the default isn't around then just use first one 
   // is there a better way?
   if(!item)
      item = m_pmoRegistry->GetItem(0);

   if (item)
   {
      pmo = (PhysicalMediaOutput *) item->InitFunction()(m_context);
      pmo->SetPropManager((Properties *) this);
      pmo->SetTarget((EventQueue *)this);
      if (m_iVolume < 0)
         m_iVolume = pmo->GetVolume();
      
      pmo->SetVolume(m_iVolume);
   }

   error = kError_NoErr;
   if (lmc_item)
   {
      lmc = (LogicalMediaConverter *) lmc_item->InitFunction()(m_context);

      lmc->SetPropManager((Properties *) this);
      lmc->SetTarget((EventQueue *) this);
   }

   lmc->SetPMI(pmi);
   lmc->SetPMO(pmo);

   pmo->SetPMI(pmi);
   pmo->SetLMC(lmc);

   pmi = NULL;
   m_lmc = lmc;
   lmc = NULL;

   error = pmo->SetTo(pc->URL().c_str());
   if (IsError(error))
   {
      char szErr[1024];

      sprintf(szErr, "Cannot initialize pmo: %d\n", error);
      m_context->log->Error(szErr);
      AcceptEvent(new LMCErrorEvent(szErr));

      goto epilogue;
   }

   m_pmo = pmo;
   pmo = NULL;

   epilogue:

   if (pmo)
   {
       delete pmo;
   }

   if (pmi)
   {
       delete pmi;
   }

   if (lmc)
   {
       delete lmc;
   }
}

void 
Player::
DoneOutputting(Event *pEvent)
{
   // LMC or PMO sends this when its done
   // outputting whatever.  Now, go on to next
   // piece in playlist

   if (m_pmo)
   {
      delete m_pmo;
      m_pmo = NULL;
   }

   if (SetState(PlayerState_Stopped))
   {
       SEND_NORMAL_EVENT(INFO_Stopped);
   }

   SEND_NORMAL_EVENT(INFO_DoneOutputting);

   if (m_plm->HasAnotherItem())
   {
      AcceptEvent(new Event(CMD_NextMediaPiece));

      if (m_playerState == PlayerState_Paused)
      {
         AcceptEvent(new Event(CMD_PlayPaused));
      }
      else
      {
         AcceptEvent(new Event(CMD_Play));
      }
   }
   else
   {
      m_plm->SetCurrentIndex(0);
      SEND_NORMAL_EVENT(INFO_PlaylistDonePlay);
   }
   
   delete pEvent;
}


void 
Player::
Stop(Event *pEvent)
{
    if (m_pmo)
    {
       m_pmo->Pause();
       delete    m_pmo;
 
       m_pmo = NULL;
    }

    if (SetState(PlayerState_Stopped))
    {
       SEND_NORMAL_EVENT(INFO_Stopped);
    }

    delete pEvent;
}

void
Player::
GetVolume(Event *pEvent)
{
    int iVolume = 0;

    delete pEvent;
    if (m_pmo) 
    {
       iVolume = m_iVolume = m_pmo->GetVolume();
    }
    else
    {
       if (m_iVolume < 0)
          iVolume = 0;
       else
          iVolume = m_iVolume;
    }
    SendToUI(new VolumeEvent(INFO_VolumeInfo,iVolume));
}

void
Player::
SetVolume(Event *pEvent)
{
    int32 v=((VolumeEvent *) pEvent)->GetVolume();
    if (m_pmo) 
    {
        m_pmo->SetVolume(v);
    }
    m_iVolume = v;
    delete pEvent;
}

void 
Player::
ChangePosition(Event *pEvent)
{
    if (m_pmo)
       m_pmo->ChangePosition(((ChangePositionEvent *) pEvent)->GetPosition());

    delete pEvent;
}

void 
Player::
GetMediaInfo(Event *pEvent)
{
     const PlaylistItem *pItem;

     if (m_playerState == PlayerState_Stopped)
     {
         pItem = m_plm->GetCurrentItem();
         if (pItem)
            CreatePMO(pItem, pEvent);
     }
     delete pEvent;
}

void 
Player::
Play(Event *pEvent)
{
    const PlaylistItem *pItem;

    if (m_playerState == PlayerState_Playing)
    {
       delete m_pmo;
       m_pmo = NULL;

       if (SetState(PlayerState_Stopped))
       {
           SEND_NORMAL_EVENT(INFO_Stopped);
       }
    }

    if (!m_pmo)
    {
       pItem = m_plm->GetCurrentItem();
       if (pItem)
          CreatePMO(pItem, pEvent);

       if (!m_pmo)
          return;
    }

    if (pEvent->Type() == CMD_PlayPaused)
    {
        if (SetState(PlayerState_Paused))
        {
           SEND_NORMAL_EVENT(INFO_Playing); 
           SEND_NORMAL_EVENT(INFO_Paused);
        }
    }
    else
    {
        m_pmo->Resume();
        if (SetState(PlayerState_Playing))
        {
           SEND_NORMAL_EVENT(INFO_Playing);
        }
    }

    delete pEvent;
}

void 
Player::
Next(Event *pEvent)
{
   if (m_playerState != PlayerState_Stopped)
   {
      AcceptEvent(new Event(CMD_Stop));
   }

   m_plm->GotoNextItem(true);

   if (m_playerState != PlayerState_Stopped)
   {
       if (m_playerState == PlayerState_Paused)
          AcceptEvent(new Event(CMD_PlayPaused));
       else
          AcceptEvent(new Event(CMD_Play));
   }

   delete pEvent;
}

void 
Player::
Previous(Event *pEvent)
{
   if (m_playerState != PlayerState_Stopped)
   {
      AcceptEvent(new Event(CMD_Stop));
   }

   m_plm->GotoPreviousItem(true);

   if (m_playerState != PlayerState_Stopped)
   {
       if (m_playerState == PlayerState_Paused)
          AcceptEvent(new Event(CMD_PlayPaused));
       else
          AcceptEvent(new Event(CMD_Play));
   }

   delete pEvent;
}

void 
Player::
Pause(Event *pEvent)
{
   if (m_pmo)
   {
      m_pmo->Pause();
      if (SetState(PlayerState_Paused))
         SEND_NORMAL_EVENT(INFO_Paused);
   }
   delete pEvent;
}

void 
Player::
UnPause(Event *pEvent)
{
   if (m_pmo)
   {
      m_pmo->Resume();
      if (SetState(PlayerState_Playing))
         SEND_NORMAL_EVENT(INFO_Playing);
   }
   delete pEvent;
}

void 
Player::
TogglePause(Event *pEvent)
{
    if (m_pmo)
    {
       if (m_playerState == PlayerState_Playing)
           Pause(NULL);
       else
       if (m_playerState == PlayerState_Paused)
           UnPause(NULL);
    }

    delete pEvent;
}

int 
Player::
Quit(Event *pEvent)
{
   Event *pe;

   Stop(NULL);
   // 1) Set "I'm already quitting flag" (or exit if its already Set)
   m_imQuitting = 1;
   // 2) Get CIO/COO manipulation lock
   GetUIManipLock();
   // 3) Count CIO/COO, put into m_quitWaitingFor.
   m_quitWaitingFor = m_uiList->size();
   // 4) Send CMD_Cleanup event to all CIO/COOs

   pe = new Event(CMD_Cleanup);

   SendToUI(pe);
   delete    pe;

   delete  pEvent;

   if (m_quitWaitingFor == 0)
   {
      if (m_pTermSem)
      {
         m_pTermSem->Signal();
      }
      return 1;
   }
   else
   {
      ReleaseUIManipLock();
      return 0;
   }
}

int 
Player::
ReadyToDieUI(Event *pEvent)
{
   delete pEvent;

   if (!m_imQuitting)
       return 0;

   m_quitWaitingFor--;
   if (m_quitWaitingFor > 0)
       return 0;

   GetUIManipLock();
   if (m_pTermSem)
      m_pTermSem->Signal();

   return 1;
}

void 
Player::
UserMessage(Event *pEvent)
{
   GetUIManipLock();
   SendToUI(pEvent);
   ReleaseUIManipLock();
   delete pEvent;
}

void 
Player::
HandleMediaInfo(Event *pEvent)
{
   MediaInfoEvent *pmvi;
   Event          *pe = NULL;
   
   GetUIManipLock();

   pmvi = (MediaInfoEvent *)pEvent;
   pmvi->m_indexOfSong = m_plm->GetCurrentIndex() + 1;         // zero based
   pmvi->m_totalSongs = m_plm->CountItems();

   SendToUI(pEvent);

   for (uint32 foobar = 0; foobar < pmvi->m_childEvents->size(); foobar++)
   {
      pe = (*pmvi->m_childEvents)[foobar];
      SendToUI(pe);
   }

   ReleaseUIManipLock();

   if (m_autoplay)
   {
      m_autoplay = false;
      AcceptEvent(new Event(CMD_Play));
   }

   delete pEvent;
}

void 
Player::
HandleMediaTimeInfo(Event *pEvent)
{
   if (m_playerState == PlayerState_Playing)
   {
      GetUIManipLock();
      SendToUI(pEvent);
      ReleaseUIManipLock();
   }

   delete pEvent;
}

void 
Player::
SendEventToUI(Event *pEvent)
{
   GetUIManipLock();
   SendToUI(pEvent);
   ReleaseUIManipLock();
   delete pEvent;
}

#define _EQUALIZER_ENABLE_
#ifdef  _EQUALIZER_ENABLE_
void 
Player::
SetEQData(Event *pEvent)
{
   if (m_pmo)
   {
       if (((SetEqualizerDataEvent *) pEvent)->IsEQData())
           m_lmc->SetEQData(((SetEqualizerDataEvent *) pEvent)->GetEQData());
       else
           m_lmc->SetEQData(((SetEqualizerDataEvent *) pEvent)->GetEnableState());
   }
   delete pEvent;
}
#endif // _EQUALIZER_ENABLE_
#undef  _EQUALIZER_ENABLE_

#define _VISUAL_ENABLE_
#ifdef  _VISUAL_ENABLE_
void 
Player::
SendVisBuf(Event *pEvent)
{
   if (m_playerState == PlayerState_Playing)
   {
      GetUIManipLock();
      SendToUI(pEvent);
      ReleaseUIManipLock();
   }
   delete pEvent;
}
#endif // _VISUAL_ENABLE_
#undef  _VISUAL_ENABLE_

void 
Player::
LMCError(Event *pEvent)
{      
#ifndef WIN32
   printf("Error: %s\n", ((LMCErrorEvent *) pEvent)->GetError()); 
#else
   MessageBox(NULL, ((LMCErrorEvent *) pEvent)->GetError() ,NULL,MB_OK); 
#endif
   if (m_pmo)
      Stop(pEvent);
   else
      delete pEvent;
}

int32 
Player::
ServiceEvent(Event * pC)
{
   if (!pC)
   {
      return 255;
   }

   //printf("Got event %d\n", pC->Type());
   switch (pC->Type())
   {
      case INFO_DoneOutputting:
           DoneOutputting(pC);
           break;

      case CMD_Stop:
           Stop(pC);
           break;

      case CMD_GetVolume:
           GetVolume(pC);
           break;

      case CMD_SetVolume:
           SetVolume(pC);
           break;

      case CMD_ChangePosition:
           ChangePosition(pC);
           break;

      case CMD_PLMGetMediaInfo:
           GetMediaInfo(pC);
           break;

      case CMD_PlayPaused:
           Play(pC);
           break;

      case CMD_Play:
           Play(pC);
           break;

      case CMD_NextMediaPiece:
           Next(pC); 
           break;

      case CMD_PrevMediaPiece:
           Previous(pC);
           break;

      case CMD_Pause:
           Pause(pC);
           break;

      case CMD_UnPause:
           UnPause(pC);
           break;

      case CMD_TogglePause:
           TogglePause(pC);
           break;

      case CMD_QuitPlayer:
           return Quit(pC);

      case INFO_ReadyToDieUI:
           return ReadyToDieUI(pC);

      case INFO_UserMessage:
      case INFO_StatusMessage:
           UserMessage(pC);
           break;

      case INFO_MediaInfo:
           HandleMediaInfo(pC);
           break;

      case INFO_MediaTimeInfo:
           HandleMediaTimeInfo(pC);
           break;

      case INFO_StreamInfo:
      case INFO_PlaylistShuffle:
      case INFO_PlaylistRepeat:
      case INFO_PlaylistUpdated:
      case INFO_BufferStatus:
           SendEventToUI(pC);
           break;

      case INFO_LMCError:
           LMCError(pC);
           break;

#define _EQUALIZER_ENABLE_
#ifdef  _EQUALIZER_ENABLE_
      case CMD_SetEQData:
           SetEQData(pC);
           break;

#endif // _EQUALIZER_ENABLE_
#undef  _EQUALIZER_ENABLE_

#define _VISUAL_ENABLE_
#ifdef  _VISUAL_ENABLE_
      case CMD_SendVisBuf:
           SendVisBuf(pC);
           break;
#endif // _VISUAL_ENABLE_
#undef  _VISUAL_ENABLE_

      default:
           m_context->log->Error("serviceEvent: Unknown event: %d\n",
				 pC->Type());
           delete  pC;
           break;
   }

   return 0;
}

Error     
Player::
PropertyChange(const char *pProp, PropValue * ppv)
{
   Error     rtn = kError_UnknownErr;

   return rtn;
}

void      
Player::
SendToUI(Event * pe)
{
   uint32     i;

   for (i = 0; i < m_uiList->size(); i++)
   {
      (*m_uiList)[i]->AcceptEvent(pe);
   }
}

Error     
Player::
GetProperty(const char *pProp, PropValue ** ppVal)
{
   return m_props.GetProperty(pProp, ppVal);
}

Error     
Player::
SetProperty(const char *pProp, PropValue * pVal)
{
   return m_props.SetProperty(pProp, pVal);
}

Error     
Player::
RegisterPropertyWatcher(const char *pProp, PropertyWatcher * pPropWatch)
{
   return m_props.RegisterPropertyWatcher(pProp, pPropWatch);
}

Error     
Player::
RemovePropertyWatcher(const char *pProp, PropertyWatcher * pPropWatch)
{
   return m_props.RemovePropertyWatcher(pProp, pPropWatch);
}
/*
   void Player::testQueue() {
   Event *pC;

   pC = m_eventQueue->Read();
   if (pC) {
   cout << "testQueue: First failed!!" << endl;
   } else {
   cout << "testQueue: First succeded!!" << endl;
   }
   cout << "testQueue: IsEmpty(): " << m_eventQueue->IsEmpty() << endl;

   pC = new Event(CMD_Play);
   AcceptEvent(pC);
   pC = new Event(CMD_Play);
   AcceptEvent(pC);
   pC = new Event(CMD_NextMediaPiece);
   AcceptEvent(pC);

   pC = m_eventQueue->Read();
   cout << "testQueue: " << pC->GetEvent() << endl;
   delete pC;
   pC = m_eventQueue->Read();
   cout << "testQueue: " << pC->GetEvent() << endl;
   delete pC;
   cout << "testQueue: IsEmpty(): " << m_eventQueue->IsEmpty() << endl;
   pC = m_eventQueue->Read();
   cout << "testQueue: " << pC->GetEvent() << endl;
   delete pC;
   pC = m_eventQueue->Read();
   if (pC) {
   cout << "testQueue: Failed!!!" << endl;
   } else {
   cout << "testQueue: Final Succeeded!!" << endl;
   }
   cout << "testQueue: IsEmpty(): " << m_eventQueue->IsEmpty() << endl;
   }
 */
