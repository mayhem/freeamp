/*____________________________________________________________________________

  FreeAmp - The Free MP3 Player

  Portions Copyright (C) 1998-1999 EMusic.com
  Portions Copyright (C) 1998.Sylvain Rebaud (soothe@jps.net)

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

  $Id: wav.h,v 1.1 2000/03/17 01:29:32 robert Exp $
____________________________________________________________________________*/

#ifndef INCLUDED_WAV_H_
#define INCLUDED_WAV_H_

struct WaveHeader
{
	DWORD MainChunkID;			// it will be 'RIFF'
	DWORD Length;
	DWORD ChunkTypeID;			// it will be 'WAVE'
	DWORD SubChunkID;			// it will be 'fmt '
	DWORD SubChunkLength;
	unsigned short Format;
	unsigned short Modus;
	DWORD SampleFreq;
	DWORD BytesPerSec;
	unsigned short BytesPerSample;
	unsigned short BitsPerSample;
	DWORD DataChunkID;			// it will be 'data'
	DWORD DataLength;
};

class WaveWriter
{
public:
	WaveWriter();
	~WaveWriter();

	int Create(const char *FileName, WAVEFORMATEX *waveformat);
	void Close();

	DWORD Write(const char *data, DWORD data_size);

private:
	MMIOINFO	m_mmioinfoWrite;
	MMIOINFO	m_mmioinfo;
	HMMIO		m_hmmio;

	FILE		*m_FP;
	struct WaveHeader	m_WH;
};

#endif /* INCLUDED_WAV_H_ */
