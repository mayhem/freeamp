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
	
	$Id: soundcardpmo.h,v 1.22 2000/01/20 00:48:47 robert Exp $
____________________________________________________________________________*/


#ifndef INCLUDED_SOUNDCARDPMO_H_
#define INCLUDED_SOUNDCARDPMO_H_

/* system headers */
#include <stdlib.h>
#include <windows.h>

/* project headers */
#include "config.h"
#include "pmo.h"
#include "thread.h"
#include "mutex.h"
#include "properties.h"
#include "eventbuffer.h"
#include "preferences.h"
#include "facontext.h"

class SoundCardPMO : public PhysicalMediaOutput
{

public:
    SoundCardPMO(FAContext *context);
    virtual ~SoundCardPMO();
    
    virtual Error Init(OutputInfo* info);
    virtual int32 GetVolume(void);
	virtual void  SetVolume(int32);

    static void   StartWorkerThread(void *);

 
 private:

	void          WorkerThread(void); 
    virtual Error Reset(bool user_stop);
    void          HandleTimeInfoEvent(PMOTimeInfoEvent *pEvent);
    WAVEHDR      *NextHeader(bool bFreeHeadersOnly = false);
    Error         FreeHeader();
    Error         AllocHeader(void *&pBuffer);
    Error         Write(void *pBuffer);
	void          Pause(void);
	void          Resume(void);
	void          Clear(void);
	bool          WaitForDrain(void);

 private:
//    FAContext*      m_context;

	WAVEFORMATEX*	m_wfex;
	LPWAVEHDR*		m_wavehdr_array;
	HWAVEOUT		m_hwo;

	uint32			m_buffer[MAXCHANNELS];
	uint32			m_channels;
	uint32          m_samples_per_second;
	uint32			m_hdr_size;
	uint32			m_data_size;
	uint32			m_num_headers;
	uint32          m_samples_per_frame;
	bool			m_initialized, m_bPaused;

    Thread         *m_pBufferThread;
    int             m_iOutputBufferSize, m_iBaseTime, m_iBytesPerSample;
	int             m_iHead, m_iTail, m_iOffset;
};

#endif /* _SOUNDCARDPMO_H_ */



