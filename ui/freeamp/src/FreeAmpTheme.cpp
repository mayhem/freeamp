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
        
   $Id: FreeAmpTheme.cpp,v 1.1.2.43 1999/10/16 21:25:42 ijr Exp $
____________________________________________________________________________*/

#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include "config.h"
#include "downloadmanager.h"

#ifdef HAVE_GTK
#include "GTKUtility.h"
#include "GTKPreferenceWindow.h"
#elif defined(WIN32)
#include "Win32PreferenceWindow.h"
#elif defined(__BEOS__)
#include "BeOSPreferenceWindow.h"
#endif

#include "FreeAmpTheme.h"
#include "MessageDialog.h"
#include "eventdata.h"
#include "event.h"
#include "debug.h"
#include "PreferenceWindow.h"

void WorkerThreadStart(void* arg);

#define DB Debug_v("%s:%d\n", __FILE__, __LINE__);

const char *szParseError = "Parsing the Theme description failed. Cause: ";
const int iVolumeChangeIncrement = 10;

extern    "C"
{
   UserInterface *Initialize(FAContext * context)
   {
	  Debug_v("##Clear");
      return new FreeAmpTheme(context);
   }
}

FreeAmpTheme::FreeAmpTheme(FAContext * context)
             :Theme(context)
{
   m_pContext = context;
   m_iCurrentSeconds = 0;
   m_iTotalSeconds = -1;
   m_iSeekSeconds = 0;
   m_bSeekInProgress = false;
   m_oCurrentWindow = string("MainWindow");
   m_iVolume = -1;
   m_iSeekPos = -1;
   m_bPlayShown = true;
   m_oTitle = string("");

   LoadFreeAmpTheme();
}

FreeAmpTheme::~FreeAmpTheme()
{
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

void FreeAmpTheme::WorkerThread(void)
{
   char   szTemp[255];
   uint32 iLen = 255;
   Error  eRet;

   m_pContext->prefs->GetPrefString(kMainWindowPosPref, szTemp, &iLen);
   sscanf(szTemp, " %d , %d", &m_oWindowPos.x, &m_oWindowPos.y);

   eRet = Theme::Run(m_oWindowPos);
   if (!IsError(eRet))
   {
       sprintf(szTemp, "%d,%d", m_oWindowPos.x, m_oWindowPos.y);
       m_pContext->prefs->SetPrefString(kMainWindowPosPref, szTemp);
   }    

   m_pContext->target->AcceptEvent(new Event(CMD_QuitPlayer));
}

void WorkerThreadStart(void* arg)
{
    FreeAmpTheme* ui = (FreeAmpTheme*)arg;
    ui->WorkerThread();
}

void FreeAmpTheme::LoadFreeAmpTheme(void)
{
   char          szTemp[255];
   uint32        iLen = 255;
   string        oThemePath;
   Error         eRet;

   m_pContext->prefs->GetPrefString(kThemePathPref, szTemp, &iLen);
   oThemePath = szTemp;
  
   iLen = 255; 
   m_pContext->prefs->GetPrefString(kThemeDefaultFontPref, szTemp, &iLen);
   SetDefaultFont(string(szTemp));

   eRet = LoadTheme(oThemePath, m_oCurrentWindow);
   if (IsError(eRet))					   
   {
       MessageDialog oBox;
       string        oErr, oMessage(szParseError);

       GetErrorString(oErr);
       oMessage += oErr;
       oBox.Show(oMessage.c_str(), string("FreeAmp"), kMessageOk);
   }
}


Error FreeAmpTheme::Close(void)
{
    Theme::Close();
    
    m_uiThread->Join();
#ifdef HAVE_GTK 
    ShutdownGTK();
#endif
    return kError_NoErr;
}

void FreeAmpTheme::ParseArgs()
{
}

int32 FreeAmpTheme::AcceptEvent(Event * e)
{
   switch (e->Type())
   {
      case CMD_Cleanup:
      {
         string oName("MainWindow");
      	 Close();
         m_pContext->target->AcceptEvent(new Event(INFO_ReadyToDieUI));
         
         break;
      }   
      case INFO_Playing:
      {
         int iState = 1;
         m_pWindow->ControlIntValue(string("Play"), true, iState);
         m_bPlayShown = true;
         break;
      }   
      case INFO_Paused:
      case INFO_Stopped:
      {
         int iState = 0;
         m_pWindow->ControlIntValue(string("Play"), true, iState);
         m_bPlayShown = true;
         break;
      }   
      case INFO_DoneOutputting:
         break;
      case INFO_MediaInfo:
      {
         MediaInfoEvent *info = (MediaInfoEvent *) e;
         string oName("Title"), oText;
         char  *pFoo = strrchr(info->m_filename, '/');
         bool   bSet = true;

         pFoo = (pFoo ? ++pFoo : info->m_filename);
         m_oTitle = string(pFoo);
         m_pWindow->ControlStringValue(oName, true, m_oTitle);
         oText = string("FreeAmp: ") + string(pFoo);
         m_pWindow->SetTitle(oText);

		 // Enable/disable the seek slider
         m_iTotalSeconds = (int32) info->m_totalSeconds;
         bSet = (m_iTotalSeconds < 0) ? false : true;
         oName = string("Seek");
         m_pWindow->ControlEnable(oName, true, bSet);

         m_pContext->target->AcceptEvent(new Event(CMD_GetVolume));

         bSet = true;
         m_pWindow->ControlEnable(string("Volume"), true, bSet);
         m_pWindow->ControlEnable(string("VolumePlus"), true, bSet);
         m_pWindow->ControlEnable(string("VolumeMinus"), true, bSet);

         break;
      }
      case INFO_StreamInfo:
      {
         char szTitle[100];
         string oName("Title"), oText;

         StreamInfoEvent *pInfo = (StreamInfoEvent *) e;

         pInfo->GetTitle(szTitle, 100);
         m_oTitle = string(szTitle);
         m_pWindow->ControlStringValue(oName, true, m_oTitle);
         oText = string("FreeAmp: ") + string(szTitle);
         m_pWindow->SetTitle(oText);

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
         int                 iSeconds;
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
            m_iSeekPos = (iSeconds * 100) / m_iTotalSeconds;
            oName = string("Seek");
            m_pWindow->ControlIntValue(oName, true, m_iSeekPos);
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
         PlaylistRepeatEvent *plre = (PlaylistRepeatEvent *) e;
         int iState;

         switch (plre->GetRepeatMode())
         {
             case kPlaylistMode_RepeatNone:
                iState = 0;
                break;
             case kPlaylistMode_RepeatOne:
                iState = 1;
                break;
             case kPlaylistMode_RepeatAll:
                iState = 2;
                break;
             default:
                break;
         }
         m_pWindow->ControlIntValue(string("Repeat"), true, iState);
         break;
      }
      case INFO_PlaylistShuffle:
      {
         PlaylistShuffleEvent *plse = (PlaylistShuffleEvent *) e;
         int iState;

         iState = plse->GetShuffleMode() ? 1 : 0;
         m_pWindow->ControlIntValue(string("Shuffle"), true, iState);
         break;
      }
      case INFO_VolumeInfo:
      {
         m_iVolume = ((VolumeEvent *) e)->GetVolume();
         m_pWindow->ControlIntValue(string("Volume"), true, m_iVolume);
         break;
      }

      case INFO_PrefsChanged:
      {
         ReloadTheme();
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
       string oName("Info"), oDesc("");
       
       m_pWindow->ControlGetDesc(oControlName, oDesc);
       m_pWindow->ControlStringValue(oName, true, oDesc);
                                
       return kError_NoErr;
   }    
   if (eMesg == CM_MouseLeave)
   {
       string oName("Info"), oEmpty("");
       
       m_pWindow->ControlStringValue(oName, true, oEmpty);
                                
       return kError_NoErr;
   }    
   if (oControlName == string("Minimize") && eMesg == CM_Pressed)
   {
       m_pWindow->Minimize();
       
       return kError_NoErr;
   }
   if (oControlName == string("Volume") && 
       (eMesg == CM_ValueChanged || eMesg == CM_SliderUpdate))
   {
   	   int iVol;
       
       m_pWindow->ControlIntValue(oControlName, false, iVol);
       SetVolume(iVol);
           
       return kError_NoErr;
   }    
   if (oControlName == string("VolumePlus") && eMesg == CM_Pressed)
   {
   	   int iVol;
       
	   iVol = min(m_iVolume + iVolumeChangeIncrement, 100);
       SetVolume(iVol);
           
       return kError_NoErr;
   }    
   if (oControlName == string("VolumeMinus") && eMesg == CM_Pressed)
   {
   	   int iVol;
       
	   iVol = max(m_iVolume - iVolumeChangeIncrement, 0);
       SetVolume(iVol);
           
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
   	   int iState = 0;

       m_pWindow->ControlIntValue(oControlName, false, iState);
       if (iState == 0)
       {
       	   iState = 1;
           m_pWindow->ControlIntValue(oControlName, true, iState);
           m_pContext->target->AcceptEvent(new Event(CMD_Play));
           m_bPlayShown = false;
       }    
	   else
       {
       	   iState = 0;
           m_pWindow->ControlIntValue(oControlName, true, iState);
           m_pContext->target->AcceptEvent(new Event(CMD_Pause));
           m_bPlayShown = true;
       }    
       return kError_NoErr;
   }
   if (oControlName == string("Stop") && eMesg == CM_Pressed)
   {
   	   int iState = 0;
       m_pWindow->ControlIntValue(oControlName, true, iState);
       m_pContext->target->AcceptEvent(new Event(CMD_Stop));
       m_bPlayShown = true;
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
   if (oControlName == string("MyMusic") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_ToggleMusicBrowserUI));
       return kError_NoErr;
   }
   if (oControlName == string("Playlist") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_TogglePlaylistUI));
       return kError_NoErr;
   }
   if (oControlName == string("Download") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_ToggleDownloadUI));
       return kError_NoErr;
   }
   if (oControlName == string("Options") && eMesg == CM_Pressed)
   {
   	   ShowOptions();

       return kError_NoErr;
   }
   if (oControlName == string("Quit") && eMesg == CM_Pressed)
   {
       m_pContext->target->AcceptEvent(new Event(CMD_QuitPlayer));
       return kError_NoErr;
   }
   if (eMesg == CM_ChangeWindow)
   {
       m_pWindow->ControlStringValue(oControlName, false, m_oCurrentWindow);
       SwitchWindow(m_oCurrentWindow);
   
       return kError_NoErr;
   }
   if (oControlName == string("ReloadTheme") && eMesg == CM_Pressed)
   {
       ReloadTheme();
       return kError_NoErr;
   }
   if (oControlName == string("Shuffle") && eMesg == CM_Pressed)
   {
       int iState = 0;
       string oStatus;

       m_pWindow->ControlIntValue(oControlName, false, iState);
       iState = (iState + 1) % 2;
       m_pContext->plm->SetShuffleMode(iState == 1);
       m_pWindow->ControlIntValue(oControlName, true, iState);
       
       switch(iState)
       {
          case 0:  
              oStatus = string("Dont shuffle tracks");
              break;
          case 1:  
              oStatus = string("Shuffle track");
              break;
       }
       m_pWindow->ControlStringValue(string("Info"), true, oStatus);
       
       return kError_NoErr;
   }    
   if (oControlName == string("Repeat") && eMesg == CM_Pressed)
   {
       int        iState = 0;
       string     oStatus;
       RepeatMode eMode = kPlaylistMode_RepeatNone;

       m_pWindow->ControlIntValue(oControlName, false, iState);
       iState = (iState + 1) % 3;
       m_pWindow->ControlIntValue(oControlName, true, iState);
       
       switch(iState)
       {
          case 0:  
              oStatus = string("Repeat none");
              eMode = kPlaylistMode_RepeatNone;
              break;
          case 1:  
              oStatus = string("Repeat current track");
              eMode = kPlaylistMode_RepeatOne;
              break;
          case 2:  
              oStatus = string("Repeat all");
              eMode = kPlaylistMode_RepeatAll;
              break;
       }
       m_pContext->plm->SetRepeatMode(eMode);
       m_pWindow->ControlStringValue(string("Info"), true, oStatus);
       
       return kError_NoErr;
   }    
       
   
   return kError_NoErr;
}

void FreeAmpTheme::InitControls(void)
{
	bool   bSet;
    int    iState;
    string oWelcome("Welcome to FreeAmp!");
    
    assert(m_pWindow);
    
    // Set the volume control
	if (m_iVolume >= 0)
    {  
       bSet = true;
       m_pWindow->ControlIntValue(string("Volume"), true, m_iVolume);
    }
    else 
       bSet = false;   
       
    m_pWindow->ControlEnable(string("Volume"), true, bSet);
    m_pWindow->ControlEnable(string("VolumePlus"), true, bSet);
    m_pWindow->ControlEnable(string("VolumeMinus"), true, bSet);

    // Set the seek control
    bSet = (m_iTotalSeconds < 0) ? false : true;
    if (bSet)
       m_pWindow->ControlIntValue(string("Seek"), true, m_iSeekPos);
    m_pWindow->ControlEnable(string("Seek"), true, bSet);
    
    // Set the Play/Pause buttons
    iState = m_bPlayShown ? 0 : 1;
    m_pWindow->ControlIntValue(string("Play"), true, iState);
    
    if (m_oTitle.length() == 0)
        m_pWindow->ControlStringValue(string("Title"), true, oWelcome);
    else    
        m_pWindow->ControlStringValue(string("Title"), true, m_oTitle);
        
    oWelcome = "Current time";
    m_pWindow->ControlStringValue(string("TimeType"), true, oWelcome);
}

// This function gets called after the window object is created,
// but before the window itself gets created
void FreeAmpTheme::InitWindow(void)
{        
	bool   bValue;
    
    m_pContext->prefs->GetStayOnTop(&bValue);
    m_pWindow->SetStayOnTop(bValue);

    m_pContext->prefs->GetLiveInTray(&bValue);
    m_pWindow->SetLiveInToolbar(bValue);
}

void FreeAmpTheme::ReloadTheme(void)
{
    char          szTemp[255];
    uint32        iLen = 255;
    string        oThemePath, oThemeFile("theme.xml");
    Error         eRet;

    m_pContext->prefs->GetPrefString(kThemePathPref, szTemp, &iLen);
    oThemePath = szTemp;

    iLen = 255;
    m_pContext->prefs->GetPrefString(kThemeDefaultFontPref, szTemp, &iLen);
    SetDefaultFont(string(szTemp));

    eRet = LoadTheme(oThemePath, m_oCurrentWindow);
    if (IsError(eRet))					   
    {
        MessageDialog oBox;
	    string        oErr, oMessage(szParseError);
  
        GetErrorString(oErr);
        oMessage += oErr;
        oBox.Show(oMessage.c_str(), string("FreeAmp"), kMessageOk);
    }	
}

void FreeAmpTheme::SetVolume(int iVolume)
{       
    string oVol("Volume: ");
    char   szPercent[10];
    
    m_iVolume = iVolume;
    m_pContext->target->AcceptEvent(new 
        VolumeEvent(CMD_SetVolume, m_iVolume));

    m_pWindow->ControlIntValue(string("Volume"), true, m_iVolume);

    sprintf(szPercent, "%d%%", iVolume);
    oVol += string(szPercent);
    m_pWindow->ControlStringValue(string("Info"), true, oVol);
}    

void FreeAmpTheme::HandleKeystroke(unsigned char cKey)
{
    switch(cKey)
    {
     case 'O':
     case 'o':
        m_pContext->target->AcceptEvent(new Event(CMD_TogglePlaylistUI));
        break;
        
     case 'p':
     case 'P':
        m_pContext->target->AcceptEvent(new Event(CMD_Play));
        break;

     case 'S':
     case 's':
        m_pContext->target->AcceptEvent(new Event(CMD_Stop));
        break;

     case 'u':
     case 'U':
        m_pContext->target->AcceptEvent(new Event(CMD_Pause));
        break;

     case 'b':
     case 'B':
        m_pContext->target->AcceptEvent(new Event(CMD_ToggleMusicBrowserUI));
        break;

     case 'n':
     case 'N':
        m_pContext->target->AcceptEvent(new Event(CMD_NextMediaPiece));
        break;

     case 'r':
     case 'R':
        m_pContext->target->AcceptEvent(new Event(CMD_PrevMediaPiece));
        break;

     case 'd':
     case 'D':
        m_pContext->target->AcceptEvent(new Event(CMD_ToggleDownloadUI));
        break;
        
     case 'e':
     case 'E':
     	ShowOptions();
        break;
    }
}

void FreeAmpTheme::ShowOptions(void)
{
    PreferenceWindow *pWindow;
       
#ifdef WIN32
    pWindow = new Win32PreferenceWindow(m_pContext, m_pThemeMan);
#elif defined(__BEOS__)
    pWindow = new BeOSPreferenceWindow(m_pContext, m_pThemeMan);
#else
    pWindow = new GTKPreferenceWindow(m_pContext, m_pThemeMan);
#endif       
    pWindow->Show(m_pWindow);
          
    delete pWindow;
}
