/*____________________________________________________________________________
        
   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic.com

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
        
   $Id: FreeAmpTheme.cpp,v 1.1.2.6 1999/09/17 20:30:59 robert Exp $
____________________________________________________________________________*/

#include <stdio.h>

#include "FreeAmpTheme.h"
#include "eventdata.h"
#include "event.h"
#include "id3v1.h"

void WorkerThreadStart(void* arg);

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

extern    "C"
{
   UserInterface *Initialize(FAContext * context)
   {
      return new FreeAmpTheme(context);
   }
}

FreeAmpTheme::FreeAmpTheme(FAContext * context)
{
   char          szTemp[255];
   unsigned int  iLen = 255;
   string        oThemePath, oThemeFile("theme.xml");
   Error         eRet;
   string        oName("MainWindow");

   m_pContext = context;

   m_pContext->prefs->GetPrefString(kThemePath, szTemp, &iLen);
   oThemePath = szTemp;
   SetThemePath(oThemePath);

   m_pContext->prefs->GetPrefString(kMainWindowPos, szTemp, &iLen);
   sscanf(szTemp, " %d , %d", &m_oWindowPos.x, &m_oWindowPos.y);

   eRet = ParseFile(oThemeFile);
   if (IsError(eRet))
   {
   	   string oErr;
   	   // THis code needs to be cross-platform!
   	   GetErrorString(oErr);
       MessageBox(NULL, oErr.c_str(), "FreeAmp", MB_OK);
       //Debug_v("ParseError: %s", oErr.c_str());
   }
   SelectWindow(oName);
   
   m_iCurrentSeconds = 0;
   m_iTotalSeconds = 0;
   m_iSeekSeconds = 0;
   m_bSeekInProgress = false;
}

FreeAmpTheme::~FreeAmpTheme()
{

}

Error FreeAmpTheme::Run(void)
{
   char   szTemp[255];
   Error  eRet;
   string oName("Volume");
   bool   bSet = false;

   assert(m_pWindow);
   m_pWindow->ControlEnable(oName, true, bSet);
   oName = string("Seek");
   m_pWindow->ControlEnable(oName, true, bSet);

   eRet = Theme::Run(m_oWindowPos);
   if (!IsError(eRet))
   {
       sprintf(szTemp, "%d,%d", m_oWindowPos.x, m_oWindowPos.y);
       m_pContext->prefs->SetPrefString(kMainWindowPos, szTemp);
   }    
   
   m_pContext->target->AcceptEvent(new Event(CMD_QuitPlayer));

   return eRet;
}

Error FreeAmpTheme::Init(int32 startup_type)
{
   assert(this);

   m_iStartupType = startup_type;
   ParseArgs();

   m_uiThread = Thread::CreateThread();
   m_uiThread->Create(WorkerThreadStart, this);

   return kError_NoErr;
}


void WorkerThreadStart(void* arg)
{
    FreeAmpTheme* ui = (FreeAmpTheme*)arg;
    ui->Run();
}

Error FreeAmpTheme::Close(string &oWindowName)
{
	Theme::Close(oWindowName);
    
    m_uiThread->Join();

    return kError_NoErr;
}

void FreeAmpTheme::ParseArgs()
{
    char     *arg = NULL;

    bool      shuffle = false;
    bool      autoplay = false;

    for (int32 i = 1; i < m_pContext->argc; i++)
    {
       arg = m_pContext->argv[i];

       if (arg[0] == '-')
       {
          switch (arg[1])
          {
          case 's':
             shuffle = true;
             break;
          case 'p':
             autoplay = true;
             break;
          }
       }
       else
       {
          if (m_iStartupType == PRIMARY_UI)
          {
          	 char *szTemp = new char[strlen(arg) + 1];
             strcpy(szTemp, arg);
             
             m_pContext->plm->AddItem(szTemp, 0);
          }
       }
    }
    if (m_iStartupType == PRIMARY_UI)
    {
       //m_pContext->plm->SetFirst();
       //if (shuffle)
       //   m_pContext->plm->SetShuffle(SHUFFLE_RANDOM);

       if (autoplay)
          m_pContext->target->AcceptEvent(new Event(CMD_Play));
    }
}

int32 FreeAmpTheme::AcceptEvent(Event * e)
{
   switch (e->Type())
   {
      case CMD_Cleanup:
      {
         string oName("MainWindow");
      	 Close(oName);
         m_pContext->target->AcceptEvent(new Event(INFO_ReadyToDieUI));
         
         break;
      }   
      case INFO_Playing:
         break;
      case INFO_Paused:
         break;
      case INFO_Stopped:
         break;
      case INFO_MediaInfo:
      {
         MediaInfoEvent *info = (MediaInfoEvent *) e;
         string oName("Title"), oText;
         char  *pFoo = strrchr(info->m_filename, '/');
         bool   bSet = true;

         pFoo = (pFoo ? ++pFoo : info->m_filename);
         oText = string(pFoo);
         m_pWindow->ControlStringValue(oName, true, oText);

		 // Enable/disable the seek slider
         m_iTotalSeconds = (int32) info->m_totalSeconds;
         bSet = (m_iTotalSeconds < 0) ? false : true;
         oName = string("Seek");
         m_pWindow->ControlEnable(oName, true, bSet);

         m_pContext->target->AcceptEvent(new Event(CMD_GetVolume));

         bSet = true;
         oName = string("Volume");
         m_pWindow->ControlEnable(oName, true, bSet);

         break;
      }
      case INFO_StreamInfo:
      {
         char szTitle[100];
         string oName("Title"), oText;

         StreamInfoEvent *pInfo = (StreamInfoEvent *) e;

         pInfo->GetTitle(szTitle, 100);
         oText = string(szTitle);
         m_pWindow->ControlStringValue(oName, true, oText);

         break;
      }
      case INFO_BufferStatus:
      {
         StreamBufferEvent *info = (StreamBufferEvent *) e;
         char szTemp[100];
         string oName("BufferInfo"), oText;

		 sprintf(szTemp, "I: %3d O: %3d %c", 
                 info->GetInputPercent(),
                 info->GetOutputPercent(),
                 info->IsBufferingUp() ? '^' : ' ');
         oText = string(szTemp);
         m_pWindow->ControlStringValue(oName, true, oText);

         break;
      }
      case INFO_MediaTimeInfo:
      {
         MediaTimeInfoEvent *info = (MediaTimeInfoEvent *) e;
         int                 iSeconds, iSeekPos;
         char                szText[100];
         string              oName("Time"), oText;

         iSeconds = (info->m_hours * 3600) + (info->m_minutes * 60) + 
                     info->m_seconds;
         if (iSeconds == m_iCurrentSeconds || m_bSeekInProgress)
             break;
             
         m_iCurrentSeconds = iSeconds;            
         sprintf(szText, "%d:%02d:%02d", info->m_hours, 
              info->m_minutes, info->m_seconds);
         oText = string(szText);
         m_pWindow->ControlStringValue(oName, true, oText);

         if (m_iTotalSeconds > 0)
         {
            iSeekPos = (iSeconds * 100) / m_iTotalSeconds;
            oName = string("Seek");
            m_pWindow->ControlIntValue(oName, true, iSeekPos);
         }   

         break;
      }
      case INFO_MPEGInfo:
      {
         MpegInfoEvent *info = (MpegInfoEvent *) e;

         m_fSecondsPerFrame = info->GetSecondsPerFrame();
         break;
      }
      case INFO_PlaylistRepeat:
      {
         //PlayListRepeatEvent *plre = (PlayListRepeatEvent *) e;

         //switch (plre->GetRepeatMode())
         //{
         //    case REPEAT_CURRENT:
         //       break;
         //    case REPEAT_ALL:
         //       break;
         //    case REPEAT_NOT:
         //    default:
         //       break;
         //}
         break;
      }
      case INFO_PlaylistShuffle:
      {
         //PlayListShuffleEvent *plse = (PlayListShuffleEvent *) e;

         //switch (plse->GetShuffleMode())
         //{
         //    case SHUFFLE_NOT_SHUFFLED:
         //       break;
         //    case SHUFFLE_RANDOM:
         //       break;
         //    default:
         //};
         break;
      }

      case INFO_VolumeInfo:
      {
      	 int    iValue;
         string oName("Volume");
         
         iValue = ((VolumeEvent *) e)->GetVolume();
         m_pWindow->ControlIntValue(oName, true, iValue);
         break;
      }
      
      default:
         break;
   }
   return 0;
}

Error FreeAmpTheme::HandleControlMessage(string &oControlName, 
                                         ControlMessageEnum eMesg)
{
   char szTemp[255];

   if (eMesg == CM_MouseEnter)
   {
       string oName("Info");
       
       m_pWindow->ControlStringValue(oName, true, oControlName);
                                
       return kError_NoErr;
   }    
   if (eMesg == CM_MouseLeave)
   {
       string oName("Info"), oEmpty("");
       
       m_pWindow->ControlStringValue(oName, true, oEmpty);
                                
       return kError_NoErr;
   }    
   if (oControlName == string("Volume") && 
       (eMesg == CM_ValueChanged || eMesg == CM_SliderUpdate))
   {
   	   int iValue;
       
       m_pWindow->ControlIntValue(oControlName, false, iValue);
       m_pContext->target->AcceptEvent(new 
           VolumeEvent(CMD_SetVolume, iValue));
       return kError_NoErr;
   }    
   if (oControlName == string("Seek") && eMesg == CM_ValueChanged)
   {
       string oName("Info"), oEmpty("");
   	   int    iValue, iFrame;
       
       m_pWindow->ControlIntValue(oControlName, false, iValue);
       iFrame = (int)(((float)iValue * (float)m_iTotalSeconds) / 
                      ((float)100 * m_fSecondsPerFrame));
       m_bSeekInProgress = false;
       
       m_pContext->target->AcceptEvent(new 
              VolumeEvent(CMD_ChangePosition, iFrame));
       
       m_pWindow->ControlStringValue(oName, true, oEmpty);
              
       return kError_NoErr;
   }    
   if (oControlName == string("Seek") && eMesg == CM_SliderUpdate)
   {
       string oName("Time"), oText("");
   	   int    iValue, iTime;
       
       m_pWindow->ControlIntValue(oControlName, false, iValue);
       iTime = (iValue * m_iTotalSeconds) / 100;
       sprintf(szTemp, "%d:%02d:%02d", iTime / 3600,
               (iTime % 3600) / 60, iTime % 60);
       oText = string(szTemp);        
       m_bSeekInProgress = true;
       
       m_pWindow->ControlStringValue(oName, true, oText);
              
       return kError_NoErr;
   }    
   if (oControlName == string("Play") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_Play));
       return kError_NoErr;
   }
   if (oControlName == string("Stop") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_Stop));
       return kError_NoErr;
   }
   if (oControlName == string("Next") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_NextMediaPiece));
       return kError_NoErr;
   }
   if (oControlName == string("Prev") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_PrevMediaPiece));
       return kError_NoErr;
   }
   if (oControlName == string("Quit") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_QuitPlayer));
       return kError_NoErr;
   }
   
   return kError_NoErr;
}
