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
        
   $Id: FreeAmpTheme.cpp,v 1.1.2.1 1999/09/08 18:48:35 robert Exp $
____________________________________________________________________________*/

#include <stdio.h>

#include "FreeAmpTheme.h"
#include "eventdata.h"

extern    "C"
{
   UserInterface *Initialize(FAContext * context)
   {
      return new FreeAmpTheme(context);
   }
}

FreeAmpTheme::FreeAmpTheme(FAContext * context)
{
   m_pContext = context;
   m_iCurrentSeconds = 0;
   m_iTotalSeconds = 0;
   m_iSeekSeconds = 0;
}

FreeAmpTheme::~FreeAmpTheme()
{

}

void FreeAmpTheme::SetPlaylistManager(PlaylistManager * plm)
{
   m_pPlaylistManager = plm;
}

Error FreeAmpTheme::Init(int32 startup_type)
{
   assert(this);

   m_iStartupType = startup_type;

   return kError_NoErr;
}

void FreeAmpTheme::ParseArgs()
{
   char     *arg = NULL;

   bool      shuffle = false;
   bool      autoplay = false;

   for (int32 i = 1; i < m_iArgc; i++)
   {
      arg = m_pArgv[i];

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
            m_pPlaylistManager->AddItem(arg, 0);
         }
      }
   }
   if (m_iStartupType == PRIMARY_UI)
   {
      //m_pPlaylistManager->SetFirst();
      //if (shuffle)
      //   m_pPlaylistManager->SetShuffle(SHUFFLE_RANDOM);

      if (autoplay)
         m_pTarget->AcceptEvent(new Event(CMD_Play));
   }
}

int32 FreeAmpTheme::AcceptEvent(Event * e)
{
   switch (e->Type())
   {
      case CMD_Cleanup:
         break;
      case INFO_Playing:
         break;
      case INFO_Paused:
         break;
      case INFO_Stopped:
         break;
      case INFO_MediaInfo:
      {
         //MediaInfoEvent *info = (MediaInfoEvent *) e;
         //char *pFoo = strrchr(info->m_filename, '/');

         //pFoo = (pFoo ? ++pFoo : info->m_filename);
         //m_lcdWindow->SetMainText(pFoo);

         //m_iTotalSeconds = (int32) info->m_totalSeconds;
         //int32     s = (int32) info->m_totalSeconds;
         //int32     h = s / 3600;
         //int32     m = (s % 3600) / 60;
         //s = ((s % 3600) % 60);

         break;
      }
      case INFO_StreamInfo:
      {
         //char      szTitle[100];

         //StreamInfoEvent *pInfo = (StreamInfoEvent *) e;

         //pInfo->GetTitle(szTitle, 100);
         //m_lcdWindow->SetMainText(szTitle);

         break;
      }
      case INFO_BufferStatus:
      {
         //StreamBufferEvent *info = (StreamBufferEvent *) e;

         //m_lcdWindow->SetBufferStatus(info->IsBufferingUp(),
         //                             info->GetInputPercent(),
         //                             info->GetOutputPercent());

         break;
      }
      case INFO_MediaTimeInfo:
      {
         //MediaTimeInfoEvent *info = (MediaTimeInfoEvent *) e;

         //m_lcdWindow->SetCurrentTime(info->m_hours, 
         //             info->m_minutes, info->m_seconds);
         //m_iCurrentSeconds = (info->m_hours * 3600) + (info->m_minutes * 60) + 
         //                    info->m_seconds;
         break;
      }
      case INFO_MPEGInfo:
      {
         //MpegInfoEvent *info = (MpegInfoEvent *) e;

         //m_secondsPerFrame = info->GetSecondsPerFrame();
         break;
      }
      case INFO_ID3TagInfo:
      {
         //ID3TagEvent *info = (ID3TagEvent *) e;
         //Id3TagInfo p = info->GetId3Tag();
         //char     *pEnd = &((p.m_songName)[strlen(p.m_songName)]);
         //while ((pEnd != p.m_songName) && (*(pEnd - sizeof(char *)) == ' '))
         //             pEnd--;
         //char      end = *pEnd;

         //*pEnd = '\0';
         //m_lcdWindow->SetMainText(p.m_songName);
         //*pEnd = end;
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
         //m_volume = ((VolumeEvent *) e)->GetVolume();
         break;
      }
      default:
         break;
   }
   return 0;
}

void FreeAmpTheme::SetArgs(int argc, char **argv)
{
   m_iArgc = argc;
   m_pArgv = argv;

   for (int i = 0; i < m_iArgc; i++)
   {
      if (m_pArgv[i][0] == '-')
      {
         if ((m_pArgv[i][1] == 'h') ||
             (m_pArgv[i][1] == 'H') ||
             !strcmp(&(m_pArgv[i][1]), "-help"))
         {
            m_pTarget->AcceptEvent(new Event(CMD_QuitPlayer));
         }

      }
   }

}

