/*____________________________________________________________________________

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
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  $Id: sigfft.cpp,v 1.1 2000/07/31 19:51:39 ijr Exp $
____________________________________________________________________________*/

//------------------------------------
//  fft.cpp
//  The implementation of the 
//  Fast Fourier Transform algorithm
//  modified by Sean Ward 2000
//  portions (c) Reliable Software, 1996 
//------------------------------------
#include "sigfft.h"
#include <string.h>

// log (1) = 0, log(2) = 1, log(3) = 2, log(4) = 2 ...

#define PI (2.0 * asin(1.0))

// Points must be a power of 2

FFT::FFT (int Points, long sampleRate)
: _Points (Points), _sampleRate (sampleRate)
{
    _aTape = new double [_Points];
#if 0
    // 1 kHz calibration wave
    for (int i = 0; i < _Points; i++)
        _aTape[i] = 1600 * sin (2 * PI * 1000. * i / _sampleRate);
#else
    int i = 0;
    for (i = 0; i < _Points; i++)
        _aTape[i] = 0;
#endif
    _sqrtPoints = sqrt((double)_Points);
    // calculate binary log
    _logPoints = 0;
    Points--;
    while (Points != 0)
    {
        Points >>= 1;
        _logPoints++;
    }

    _aBitRev = new int [_Points];
    _X = new Complex[_Points];
    _W = new Complex* [_logPoints+1];
    // Precompute complex exponentials
    int _2_l = 2;
    for (int l = 1; l <= _logPoints; l++)
    {
        _W[l] = new Complex [_Points];

        for ( int i = 0; i < _Points; i++ )
        {
            double re =  cos (2. * PI * i / _2_l);
            double im = -sin (2. * PI * i / _2_l);
            _W[l][i] = Complex (re, im);
        }
        _2_l *= 2;
    }

    // set up bit reverse mapping
    int rev = 0;
    int halfPoints = _Points/2;
    for (i = 0; i < _Points - 1; i++)
    {
        _aBitRev[i] = rev;
        int mask = halfPoints;
        // add 1 backwards
        while (rev >= mask)
        {
            rev -= mask; // turn off this bit
            mask >>= 1;
        }
        rev += mask;
    }
    _aBitRev [_Points-1] = _Points-1;
}

FFT::~FFT()
{
    delete []_aTape;
    delete []_aBitRev;
    for (int l = 1; l <= _logPoints; l++)
    {
        delete []_W[l];
    }
    delete []_W;
    delete []_X;
}

//void Fft::CopyIn (SampleIter& iter)
void FFT::CopyIn(char* pBuffer, int nNumSamples)
{
    if (nNumSamples > _Points)
        return;

    // make space for cSample samples at the end of tape
    // shifting previous samples towards the beginning
    memmove (_aTape, &_aTape[nNumSamples], 
              (_Points - nNumSamples) * sizeof(double));
    // copy samples from iterator to tail end of tape
    int iTail  = _Points - nNumSamples;
    int i = 0;
    for (i = 0; i < nNumSamples; i++)
    {
        _aTape [i + iTail] = (double) pBuffer[i];
    }
    // Initialize the FFT buffer
    for (i = 0; i < _Points; i++)
        PutAt (i, _aTape[i]);
}

//
//               0   1   2   3   4   5   6   7
//  level   1
//  step    1                                     0
//  increm  2                                   W 
//  j = 0        <--->   <--->   <--->   <--->   1
//  level   2
//  step    2
//  increm  4                                     0
//  j = 0        <------->       <------->      W      1
//  j = 1            <------->       <------->   2   W
//  level   3                                         2
//  step    4
//  increm  8                                     0
//  j = 0        <--------------->              W      1
//  j = 1            <--------------->           3   W      2
//  j = 2                <--------------->            3   W      3
//  j = 3                    <--------------->             3   W
//                                                              3
//

void FFT::Transform ()
{
    // step = 2 ^ (level-1)
    // increm = 2 ^ level;
    int step = 1;
    for (int level = 1; level <= _logPoints; level++)
    {
        int increm = step * 2;
        for (int j = 0; j < step; j++)
        {
            // U = exp ( - 2 PI j / 2 ^ level )
            Complex U = _W [level][j];
            for (int i = j; i < _Points; i += increm)
            {
                // butterfly
                Complex T = U;
                T *= _X [i+step];
                _X [i+step] = _X[i];
                _X [i+step] -= T;
                _X [i] += T;
            }
        }
        step *= 2;
    }
}

