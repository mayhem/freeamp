/*___________________________________________________________________________
 
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
        
        $Id: sigxdr.cpp,v 1.1 2000/07/31 19:51:38 ijr Exp $
____________________________________________________________________________*/

#include "config.h"
#include "sigxdr.h"

#ifdef WIN32
#include <winsock.h>
#else
#undef socklen_t
#include <netinet/in.h>
#endif

SigXDR::SigXDR(void)
{
    m_buffer = m_position = NULL;
    m_size = 0;
}

SigXDR::~SigXDR(void)
{
}

char *SigXDR::FromSig(AudioSig *sig)
{
    m_size = NUMSIGFIELDS * FIELDSIZE;
    m_buffer = new char[m_size];
    m_position = m_buffer;

    float temp;
 
    temp = sig->Energy();
    PutFloat(&temp);

    temp = sig->ZXing();
    PutFloat(&temp);

    temp = sig->Length();
    PutFloat(&temp);

    for (int i = 0; i < 32; i++)  
        PutInt32(&sig->Spectrum()[i]);

    return m_buffer;
}

string SigXDR::ToStrGUID(char *buffer, long size)
{
    string ret = "";

    m_size = 16 * FIELDSIZE;
    if (size != m_size)
        return ret;
  
    char c;
 
    m_position = m_buffer = buffer;
    for (int i = 0; i < 16; i++) {
        GetInt32((int32 *)&c);
        ret.append(1, c);
    }

    return ret;
}

void SigXDR::PutInt32(int32 *data)
{
    if ((m_size -= 4) < 0)
        return;
 
    *(int32 *)m_position = htonl(*data);
    m_position += 4;
}

void SigXDR::GetInt32(int32 *data)
{
    if ((m_size -= 4) < 0)
        return;
   
    *data = (int32)ntohl((*((int32 *)(m_position))));
    m_position += 4;
}

void SigXDR::PutFloat(float *data)
{
    if (sizeof(float) == sizeof(int32))
        PutInt32((int32 *)data);
    else if (sizeof(float) == sizeof(int)) {
        int32 tmp = *(int *)data;
        PutInt32(&tmp);
    }
}

void SigXDR::GetFloat(float *data)
{
    if (sizeof(float) == sizeof(int32))
        GetInt32((int32 *)data);
    else if (sizeof(float) == sizeof(int)) {
        int32 tmp;
        GetInt32(&tmp);
        *(int *)data = tmp;
    }
}

