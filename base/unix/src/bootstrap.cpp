/*____________________________________________________________________________
	
	FreeAmp - The Free MP3 Player

	Portions Copyright (C) 1998-1999 EMusic.com

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
	
	$Id: bootstrap.cpp,v 1.20.2.1 2000/02/26 23:03:14 robert Exp $
____________________________________________________________________________*/

#include "config.h"

#include <iostream.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h> 
#include <sys/shm.h> 

#include <sys/types.h>
#include <signal.h>

#include "player.h"
#include "event.h"
#include "ui.h"
#include "list.h"
#include "hashtable.h"
#include "semaphore.h"
#include "registrar.h"
#include "facontext.h"
#include "log.h"
#include "unixprefs.h"

const int iSemKey = 0xFA000000;
const int iMemKey = 0xFA000001;
const int iSharedMemSize = 4096;

#if MP3_PROF
extern "C" {
   Initialize();
}
#endif

#ifdef DEBUG_MUTEXES
static void PrintMutexDebugInfo(int sig)
{
    Mutex newmutex;
    newmutex.DumpAllMutexes();
}
#endif

int main(int argc, char **argv) 
{
    FAContext *context = new FAContext;
    UnixPrefs *unixPrefs = new UnixPrefs;
    key_t      tSemKey = iSemKey;
    key_t      tMemKey = iMemKey;
    int        iCmdSem, iCmdMem;
    int        iProcess, i;
    char      *pCmdLine = NULL, *pPtr;

    iCmdSem = semget(tSemKey, 1, IPC_CREAT | 0666);
    if (iCmdSem < 0)
    {
       printf("Cannot create/open a semaphore. Is SYS V IPC installed?\n");
       exit(0);
    }

    // Check to see if the process that created that semaphore still
    // exists
    iProcess = semctl(iCmdSem, 0, GETVAL, 0);
    if (iProcess > 0)
    {
        if (kill(iProcess, 0) >= 0)
        {
            iCmdMem = shmget(tMemKey, iSharedMemSize, 0666);
            pCmdLine = (char *)shmat(iCmdMem, NULL, 0); 
            for(i = 1, pPtr = pCmdLine; i < argc; i++)
            {
                strcpy(pPtr, argv[i]);
                pPtr += strlen(pPtr) + 1;
            }
            *pPtr = 0;

            // Now wait for the main freeamp to parse the args and then exit
            while(*pCmdLine != 0)
            {
                if (kill(iProcess, 0) < 0)
                   break;

                sleep(1);
            }

            shmdt(pCmdLine);

            exit(0);
        }
    }

    // Set the current pid into the semaphore
    semctl(iCmdSem, 0, SETVAL, getpid());

    // Create the shared memory segment
    iCmdMem = shmget(tMemKey, iSharedMemSize, IPC_CREAT | 0666);
    if (iCmdMem != -1)
    {
        pCmdLine = (char *)shmat(iCmdMem, NULL, 0); 
        pCmdLine[0] = 0;
    }

    int errLine;
    if ((errLine = unixPrefs->GetErrorLineNumber()))
    	cerr << "ERROR parsing line " << errLine 
             << " of ~/.freeamp/preferences\n";

#ifdef DEBUG_MUTEXES
    struct sigaction sigact;
    sigact.sa_handler = PrintMutexDebugInfo;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGUSR1, &sigact, 0);

    cout << The_BRANDING << " has been compiled with mutex debugging enabled.\n"
         << "To dump mutex info: kill -SIGUSR1 " << getpid() << endl;
#endif
    
    context->prefs = unixPrefs;
    context->log = new LogFile("freeamp.log");

    Registrar *registrar= new Registrar();
    Registry *lmc;
    Registry *pmi;
    Registry *pmo;
    Registry* ui;
    
    lmc = new Registry();
#if MP3_PROF
    RegistryItem* item = new RegistryItem;
    item->SetPath("[builtin]");
    item->SetName("xingmp3.lmc");
    item->SetDescription("xingmp3.lmc");
    item->SetInitFunction((InitializeFunction)Initialize);
    lmc->Add(item);
#else
    registrar->SetSubDir("plugins");
    registrar->SetSearchString("*.lmc");
    registrar->InitializeRegistry(lmc,context->prefs);
#endif

    registrar->SetSubDir("plugins");
    registrar->SetSearchString("*.pmi");
    pmi = new Registry;
    registrar->InitializeRegistry(pmi,context->prefs);

    registrar->SetSearchString("*.pmo");
    pmo = new Registry;
    registrar->InitializeRegistry(pmo,context->prefs);

    registrar->SetSubDir("plugins");
    registrar->SetSearchString("*.ui");
    ui = new Registry;
    registrar->InitializeRegistry(ui,context->prefs);

    delete registrar;

    Semaphore *termSemaphore;
    termSemaphore = new Semaphore();
    Player *pP = Player::GetPlayer(context);

    pP->RegisterLMCs(lmc);
    pP->RegisterPMIs(pmi);
    pP->RegisterPMOs(pmo);
    pP->RegisterUIs(ui);

    if (pP->SetArgs(argc,argv)) 
    {
        pP->SetTerminationSemaphore(termSemaphore);
        pP->Run();

        for(;;)
        {
            if (!termSemaphore->TimedWait(1000))
            {
                if (pCmdLine && strlen(pCmdLine) > 0)
                {
                    int iItems = context->plm->CountItems();
                    bool bPlay;

                    context->prefs->GetPlayImmediately(&bPlay);
                    if (bPlay)
                        context->plm->RemoveAll();

                    for(i = 0, pPtr = pCmdLine; *pPtr; i++)
                    {
                        pP->HandleSingleArg(pPtr);
                        pPtr += strlen(pPtr) + 1;
                    }
                    pCmdLine[0] = 0;

                    if (iItems == 0 || bPlay)
                        context->target->AcceptEvent(new Event(CMD_Play));
                }
            }
            else
                break;
        }
    }

    if (pCmdLine)
       shmdt(pCmdLine); 
    semctl (iCmdSem, IPC_RMID, 0);

    delete pP;
    delete context;

    return 0;
}
