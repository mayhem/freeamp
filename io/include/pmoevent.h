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
   
   $Id: pmoevent.h,v 1.1 1999/03/04 07:23:46 robert Exp $
____________________________________________________________________________*/

#ifndef _PMOEVENTS_H_
#define _PMOEVENTS_H_

/* system headers */
#include <stdlib.h>

#include "event.h"
#include "pmo.h"

enum
{
    PMO_Init,
    PMO_Info,
    PMO_Reset,
    PMO_Quit
};

class PMOInitEvent : public Event
{
    public:

               PMOInitEvent(OutputInfo *pInfo)
               {
                  m_pInfo = pInfo;
                  m_type = PMO_Init;
               };
      virtual ~PMOInitEvent(void)
               {
                  if (m_pInfo)
                     delete m_pInfo;
               };

      OutputInfo *GetInfo(void)
               {
                  return m_pInfo;
               };

    protected:

      OutputInfo *m_pInfo;
};

class PMOTimeInfoEvent : public Event
{
    public:

               PMOTimeInfoEvent(int iFrameNumber)
               {
                  m_type = PMO_Info;
                  m_iFrameNumber = iFrameNumber;
               };
      virtual ~PMOTimeInfoEvent(void) { ; };

      int      GetFrameNumber(void)
               {
                  return m_iFrameNumber;
               };

    protected:

      int      m_iFrameNumber;
};

class PMOResetEvent : public Event
{
    public:

               PMOResetEvent(void)
               {
                  m_type = PMO_Reset;
               };
      virtual ~PMOResetEvent(void) { ; };

    protected:
};

class PMOQuitEvent : public Event
{
    public:

               PMOQuitEvent(void)
               {
                  m_type = PMO_Quit;
               };
      virtual ~PMOQuitEvent(void) { ; };

    protected:
};

#endif
