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
        
        $Id: player.cpp,v 1.110 1999/04/15 22:06:46 robert Exp $
____________________________________________________________________________*/

#include <iostream.h>
#include <assert.h>

#include "event.h"
#include "lmc.h"
#include "player.h"
#include "thread.h"
#include "debug.h"
#include "list.h"
#include "ui.h"
#include "queue.h"
#include "semaphore.h"
#include "eventdata.h"
#include "registrar.h"
#include "preferences.h"
#include "properties.h"
#include "volume.h"
#include "log.h"

Player   *Player::m_thePlayer = NULL;
LogFile *g_Log = NULL;

const char *szPlaylistExt = ".M3U";

#define SEND_NORMAL_EVENT(e) { Event *ev = new Event(e); GetUIManipLock();    \
                               SendToUI(ev); ReleaseUIManipLock(); delete ev; \
                             }


Player *
Player::
GetPlayer()
{
   if (m_thePlayer == NULL)
   {
      m_thePlayer = new Player();
   }
   return m_thePlayer;
}

Player::
Player():
EventQueue()
{
   g_Log = new LogFile("freeamp.log");
   assert(g_Log);
   // cout << "Creating player..." << endl;
   m_eventSem = new Semaphore();
   m_eventQueue = new Queue < Event * >();
   // cout << "Created queue" << endl;
   m_eventServiceThread = NULL;
   // cout << "Started event thread" << endl;
   m_uiList = new List < UserInterface * >();
   // cout << "Created Lists" << endl;
   m_uiManipLock = new Mutex();
   m_lmcMutex = new Mutex();
   m_pmiMutex = new Mutex();
   m_pmoMutex = new Mutex();
   m_uiMutex = new Mutex();
   // cout << "Created mutex" << endl;
   m_imQuitting = 0;
   m_quitWaitingFor = 0;
   m_plm = new PlayListManager((EventQueue *) this);
   m_playerState = PlayerState_Stopped;

   m_lmcRegistry = NULL;
   m_pmiRegistry = NULL;
   m_pmoRegistry = NULL;
   m_uiRegistry = NULL;

   m_lmc = NULL;
   m_ui = NULL;

   m_argUIList = new List < char *>();

   m_argc = 0;
   m_argv = NULL;
   m_prefs = NULL;
   m_pTermSem = NULL;

   m_didUsage = false;
   m_autoplay = true;

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

   if (m_lmc)
   {
      m_lmc->Stop();
      delete    m_lmc;

      m_lmc = NULL;
   }

   TYPICAL_DELETE(m_eventSem);
   TYPICAL_DELETE(m_eventQueue);

   // Delete CIOs
   if (m_uiList)
   {
      m_uiList->DeleteAll();
      delete    m_uiList;

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
   TYPICAL_DELETE(m_prefs);
   TYPICAL_DELETE(g_Log);
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
   List < char *>argList;
   bool      justGotArgvZero = false;
   char     *arg = NULL;
   char     *argUI = NULL;

#ifndef WIN32
   
   if (argc == 1)
   {
       Usage(argv[0]);
       exit(0);
   }

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
   // sprintf(m_argUI,"%s",pBegin);
   strcpy(argUI, pBegin);
   m_argUIList->AddItem(argUI);
   justGotArgvZero = true;
#endif

   argList.AddItem(argv[0]);
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
               argList.AddItem(argv[i]);
            }
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
                     m_argUIList->DeleteAll();
                     justGotArgvZero = false;
                  }
                  m_argUIList->AddItem(argUI);
               }
               break;
            }
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
            {
               argList.AddItem(argv[i]);
            }
            break;
         default:
             argList.AddItem(argv[i]);
         }
      }
      else
	  {
		 char *pPtr;

		 pPtr = strrchr(argv[i], '.');
		 if (pPtr && strcasecmp(pPtr, szPlaylistExt) == 0)
		 { 
		 	 Error eRet;

		     eRet = m_plm->ExpandM3U(argv[i], argList);
		     if (IsError(eRet))
#ifndef WIN32
                printf("Error: Cannot open file '%s'.\n", argv[i]);
#else
                MessageBox(NULL, "Cannot open playlist file", argv[i], MB_OK); 
#endif
		 }
		 else
             argList.AddItem(argv[i]);
      }
   }
   m_argc = argList.CountItems();
   if (m_argc)
   {
	   //LEAK-2
	   m_argv = new pchar[m_argc];
      for (int f = 0; f < m_argc; f++)
      {
         m_argv[f] = argList.ItemAt(f);
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

   printf("FreeAmp version 1.20 -- Usage:\n\n");
   printf("freeamp [-ui <UI plugin name>] "
          "[-prop <PropertyName>=<PropertyValue>]\n");
   printf("        <MP3 file/stream> [MP3 file/stream] ...\n\n");
   printf("The following properties can be set:\n\n");
   printf("  InputBuffer      - the size (in Kb) of the input buffer\n");
   printf("  OutputBuffer     - the size (in Kb) of the output buffer\n");
   printf("  BufferUpInterval - how many seconds to buffer up for streaming\n");
   printf("  Logging          - a value of 'yes' turns on logging\n");
   printf("  LoggingInput     - a value of 'yes' logs input events\n");
   printf("  LoggingDecode    - a value of 'yes' logs decode events\n\n");
   printf("Example command line:\n\n");
   printf("   freeamp -prop OutputBuffer=256 mysong1.mp3 mysong2.mp3\n\n");
   printf("Note:\n\n");
   printf("   The default output buffer size is set to 512Kb.\n\n");

   m_didUsage = true;
}

#ifdef __linux__
#define ARCH_NAME "linux"
#else
#define ARCH_NAME "unknown"
#endif

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

         sprintf(foo, "%s-%s.ui", p2, ARCH_NAME);
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
SetPreferences(Preferences * pP)
{
   m_prefs = pP;
}

Preferences* 
Player::
GetPreferences() const
{
    return m_prefs;
}

void      
Player::
Run()
{
   int32     uiListIndex = 0;
   Preferences *prefs;
   char     *name = NULL;
   uint32    len = 256;
   Error     error = kError_NoErr;
   int32     uisActivated = 0;
   bool      bValue;

   prefs = new Preferences;

   prefs->GetUseDebugLog(&bValue);
   if (bValue)
      g_Log->Open();
   
   prefs->GetLogInput(&bValue);
   if (bValue)
      g_Log->AddLogLevel(LogInput);
   
   prefs->GetLogOutput(&bValue);
   if (bValue)
      g_Log->AddLogLevel(LogOutput);
   
   prefs->GetLogDecode(&bValue);
   if (bValue)
      g_Log->AddLogLevel(LogDecode);
   
   prefs->GetLogPerformance(&bValue);
   if (bValue)
      g_Log->AddLogLevel(LogPerf);
   
   // which ui should we instantiate first??
   if (m_argUIList->CountItems() == 0)
   {
      name = new char[len];


      while ((error = prefs->GetDefaultUI(name, &len)) ==
             kError_BufferTooSmall)
      {
         delete[]name;
         len++;

         name = new char[len];
      }

   }
   else
   {
      name = new char[1024];

      strcpy(name, m_argUIList->ItemAt(uiListIndex));
   }
   delete    prefs;

   if (IsntError(error))
   {
      while (*name)
      {
         RegistryItem *item = NULL;
         UserInterface *ui = NULL;
         int32     i = 0;

         while (item = m_uiRegistry->GetItem(i++))
         {
            if (!CompareNames(item->Name(), name))
            {
               m_ui = (UserInterface *) item->InitFunction()(g_Log);

               m_ui->SetTarget((EventQueue *) this);
               m_ui->SetPropManager((Properties *) this);
               m_ui->SetPlayListManager(m_plm);
               m_ui->SetArgs(m_argc, m_argv);
               Error     er = m_ui->Init((uiListIndex == 0) ? PRIMARY_UI : SECONDARY_UI_STARTUP);  
               if (er == kError_NoErr)
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
         char     *p = m_argUIList->ItemAt(++uiListIndex);

         if (p)
         {
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

         m_prefs->GetInstallDirectory(bar, &size);
         sprintf(foo, "No UI plugin matched 'plugins\\%s' or 'plugins\\%s.ui' in '%s'.  FreeAmp will quit.", name, name, bar);
         MessageBox(NULL, foo, "FreeAmp Error", MB_OK);
#else
         const char *thePath = getenv(FREEAMP_PATH_ENV);

         if (thePath == NULL)
          thePath = Preferences::GetLibDirs();
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
      m_uiList->AddItem(ui);
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
RegisterLMCs(LMCRegistry * registry)
{
   int32     result = 0;

   m_lmcMutex->Acquire();

   if (m_lmcRegistry)
   {
    Registrar::CleanupRegistry(m_lmcRegistry);
      delete    m_lmcRegistry;
   }

   m_lmcRegistry = registry;

   m_lmcMutex->Release();

   return result;
}

int32     
Player::
RegisterPMIs(PMIRegistry * registry)
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
RegisterPMOs(PMORegistry * registry)
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
RegisterUIs(UIRegistry * registry)
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

LMCRegistry* 
Player::
GetLMCRegistry() const
{
    return m_lmcRegistry;
}

PMIRegistry* 
Player::
GetPMIRegistry() const
{
    return m_pmiRegistry;
}

PMORegistry* 
Player::
GetPMORegistry() const
{
    return m_pmoRegistry;
}

UIRegistry*  
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

RegistryItem *
Player::
ChoosePMI(char *szUrl, char *szTitle)
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

   for (iLoop = 0; iLoop < m_pmiRegistry->GetNumItems(); iLoop++)
   {
      pmi_item = m_pmiRegistry->GetItem(iLoop);

      pmi = (PhysicalMediaInput *) pmi_item->InitFunction()(g_Log);
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
CreateLMC(PlayListItem * pc, Event * pC)
{
   Error     error = kError_NoErr;
   Event    *e;
   PhysicalMediaOutput *pmo = NULL;
   PhysicalMediaInput *pmi = NULL;
   LogicalMediaConverter *lmc = NULL;
   RegistryItem *pmi_item = pc->GetPMIRegistryItem();
   RegistryItem *lmc_item = pc->GetLMCRegistryItem();
   RegistryItem *item;
   int32           iVolume;

   if (!pc)
   {
      m_plm->SetFirst();
      if (m_lmc)
      {
         m_lmc->Stop();
         delete m_lmc;

         m_lmc = NULL;
      }
      if (SetState(PlayerState_Stopped))
      {
         SEND_NORMAL_EVENT(INFO_Stopped);
      }
      GetUIManipLock();

      e = new Event(INFO_PlayListDonePlay);
      SendToUI(e);

      ReleaseUIManipLock();

      delete e;
   }

   if (m_lmc)
   {
      m_lmc->Stop();
      delete    m_lmc;

      m_lmc = NULL;
   }

   pmi_item = ChoosePMI(pc->URL());
   if (!pmi_item)
   {
      g_Log->Error("Cannot determine what pmi to use for %s\n",
                   pc->URL());
      return;
   }

   lmc_item = m_lmcRegistry->GetItem(0);

   if (pmi_item)
   {
      pmi = (PhysicalMediaInput *) pmi_item->InitFunction()(g_Log);
      pmi->SetPropManager((Properties *) this);
      pmi->SetTarget((EventQueue *)this);
   }

   char defaultPMO[256];
   uint32 size = sizeof(defaultPMO);

   m_prefs->GetDefaultPMO(defaultPMO, &size);

   int32 i = 0;

   while(item = m_pmoRegistry->GetItem(i++))
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
      pmo = (PhysicalMediaOutput *) item->InitFunction()(g_Log);
      pmo->SetPropManager((Properties *) this);
      pmo->SetTarget((EventQueue *)this);
   }

   error = kError_NoErr;
   if (lmc_item)
   {
      lmc = (LogicalMediaConverter *) lmc_item->InitFunction()(g_Log);

      if ((error = lmc->SetTarget((EventQueue *) this)) != kError_NoErr)
      {
         goto epilogue;
      }
      if ((error = lmc->SetPMI(pmi)) != kError_NoErr)
      {
         goto epilogue;
      }
      pmi = NULL;

      if ((error = lmc->SetPMO(pmo)) != kError_NoErr)
      {
         goto epilogue;
      }
      pmo = NULL;

      error = lmc->SetTo(pc->URL());
      if (IsError(error))
      {
         g_Log->Error("Cannot initialize input lmc: %d\n", error);

         goto epilogue;
      }

      lmc->SetPropManager((Properties *) this);
   }

   if ((error = lmc->Pause()) != kError_NoErr)
   {
      goto epilogue;
   }

   if ((error = lmc->Decode(m_plm->GetSkip())) != kError_NoErr)
   {
      goto epilogue;
   }

   iVolume = lmc->GetVolume();
   if (iVolume < 0)
	   iVolume = VolumeManager::GetVolume();

   m_props.SetProperty("pcm_volume", new Int32PropValue(iVolume));

   m_lmc = lmc;
   lmc = NULL;

   epilogue:

   if (pmi)
       delete pmi;

   if (pmo)
   {
       delete pmo;
   }

   if (lmc)
       delete lmc;
}

void 
Player::
DoneOutputting(Event *pEvent)
{
   // LMC or PMO sends this when its done
   // outputting whatever.  Now, go on to next
   // piece in playlist

   if (m_lmc)
   {
      delete m_lmc;
      m_lmc = NULL;
   }

   if (SetState(PlayerState_Stopped))
   {
       SEND_NORMAL_EVENT(INFO_Stopped);
   }

   SEND_NORMAL_EVENT(INFO_DoneOutputting);

   if (m_plm->HasAnotherSong())
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
      m_plm->SetFirst();
      SEND_NORMAL_EVENT(INFO_PlayListDonePlay);
   }
   
   delete pEvent;
}


void 
Player::
Stop(Event *pEvent)
{
    if (m_lmc)
    {
       m_lmc->Stop();

       delete    m_lmc;
 
       m_lmc = NULL;
    }

    if (SetState(PlayerState_Stopped))
    {
       SEND_NORMAL_EVENT(INFO_Stopped);
    }

    delete pEvent;
}

void 
Player::
ChangePosition(Event *pEvent)
{
    if (m_lmc)
       m_lmc->ChangePosition(((ChangePositionEvent *) pEvent)->GetPosition());

    delete pEvent;
}

void 
Player::
GetMediaInfo(Event *pEvent)
{
     PlayListItem *pItem;

     if (m_playerState == PlayerState_Stopped)
     {
         pItem = m_plm->GetCurrent();
         if (pItem)
            CreateLMC(pItem, pEvent);
     }
     delete pEvent;
}

void 
Player::
GetMediaTitle(Event *pEventArg)
{
     PLMGetMediaTitleEvent *pEvent;
     PlayListItem          *pItem;
     RegistryItem          *pRegItem;
     PhysicalMediaInput    *pPmi;
     char                   szTitle[1024];
     unsigned char          szTagBuffer[128];
     Id3TagInfo            *pID3Tag;
     Error                  eRet;

     szTitle[0] = 0;

     pEvent = (PLMGetMediaTitleEvent *)pEventArg;

     pItem = pEvent->GetPlayListItem();
     pRegItem = ChoosePMI(pItem->URL(), szTitle);
     if (!strlen(szTitle))
     {
         pPmi = (PhysicalMediaInput *)pRegItem->InitFunction()(g_Log);

         pPmi->SetTarget((EventQueue *)this);
         eRet = pPmi->SetTo(pItem->URL(), false);
         if (!IsError(eRet))
         {
            eRet = pPmi->GetID3v1Tag(szTagBuffer);
            if (!IsError(eRet))
            {
                pID3Tag = new Id3TagInfo((char *)szTagBuffer);

                strcpy(szTitle, pID3Tag->m_artist);

                strcat(szTitle, " - ");

                strcat(szTitle, pID3Tag->m_songName);

                delete pID3Tag;
             }
         }

         delete pPmi;
     }

     if(*szTitle)
     {
        pItem->SetDisplayString(szTitle);

        SendEventToUI(new PlayListItemUpdatedEvent(pItem) );
     }

     delete pEvent;
}

void 
Player::
Play(Event *pEvent)
{
    PlayListItem *pItem;

    if (m_playerState == PlayerState_Playing)
    {
       delete m_lmc;
       m_lmc = NULL;

       if (SetState(PlayerState_Stopped))
       {
           SEND_NORMAL_EVENT(INFO_Stopped);
       }
    }

    if (!m_lmc)
    {
       pItem = m_plm->GetCurrent();
       if (pItem)
          CreateLMC(pItem, pEvent);

       if (!m_lmc)
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
        m_lmc->Resume();
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

   m_plm->SetNext(true);

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

   m_plm->SetPrev(true);

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
   if (m_lmc)
   {
      m_lmc->Pause();
      if (SetState(PlayerState_Paused))
         SEND_NORMAL_EVENT(INFO_Paused);
   }
   delete pEvent;
}

void 
Player::
UnPause(Event *pEvent)
{
   if (m_lmc)
   {
      m_lmc->Resume();
      if (SetState(PlayerState_Playing))
         SEND_NORMAL_EVENT(INFO_Playing);
   }
   delete pEvent;
}

void 
Player::
TogglePause(Event *pEvent)
{
    if (m_lmc)
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
   m_quitWaitingFor = m_uiList->CountItems();
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
   pmvi->m_indexOfSong = m_plm->Current() + 1;         // zero based
   pmvi->m_totalSongs = m_plm->CountItems();

   SendToUI(pEvent);

   for (int foobar = 0; foobar < pmvi->m_childEvents->CountItems(); foobar++)
   {
      pe = pmvi->m_childEvents->ItemAt(foobar);
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
   if (m_lmc)
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
   if (m_lmc)
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

   //print("Got event %d\n", pC->Type());
   switch (pC->Type())
   {
      case INFO_DoneOutputting:
           DoneOutputting(pC);
           break;

      case CMD_Stop:
           Stop(pC);
           break;

      case CMD_ChangePosition:
           ChangePosition(pC);
           break;

      case CMD_PLMGetMediaInfo:
           GetMediaInfo(pC);
           break;

      case CMD_PLMGetMediaTitle:
           GetMediaTitle(pC);
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

      case INFO_PlayListShuffle:
      case INFO_PlayListRepeat:
      case INFO_PlayListUpdated:
      case INFO_BufferingBegin:
      case INFO_BufferingEnd:
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
           g_Log->Error("serviceEvent: Unknown event: %d\n", pC->Type());
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

   if (!strcmp(pProp, "pcm_volume"))
   {
      int32     newVol = ((Int32PropValue *) ppv)->GetInt32();

      if (m_lmc)
         m_lmc->SetVolume(newVol);
	  else
	     VolumeManager::SetVolume(newVol);


      rtn = kError_NoErr;
   }
   return rtn;
}

void      
Player::
SendToUI(Event * pe)
{
   int32     i;

   for (i = 0; i < m_uiList->CountItems(); i++)
   {
      m_uiList->ItemAt(i)->AcceptEvent(pe);
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