#ifndef _OS_TYPES_H
#define _OS_TYPES_H
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE Ogg Vorbis SOFTWARE CODEC SOURCE CODE.  *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS SOURCE IS GOVERNED BY *
 * THE GNU PUBLIC LICENSE 2, WHICH IS INCLUDED WITH THIS SOURCE.    *
 * PLEASE READ THESE TERMS DISTRIBUTING.                            *
 *                                                                  *
 * THE OggSQUISH SOURCE CODE IS (C) COPYRIGHT 1994-2000             *
 * by Monty <monty@xiph.org> and The XIPHOPHORUS Company            *
 * http://www.xiph.org/                                             *
 *                                                                  *
 ********************************************************************

 function: #ifdef jail to whip a few platforms into the UNIX ideal.
 last mod: $Id: os_types.h,v 1.4 2000/09/28 08:08:01 ijr Exp $

 ********************************************************************/

#ifndef vorbis_size32_t
#define vorbis_size32_t int
#endif

#if defined (WIN32) 
#if !defined(__GNUC__)

/* MSVC/Borland */
typedef __int64 ogg_int64_t;
typedef __int32 ogg_int32_t;
typedef unsigned __int32 ogg_uint32_t;
typedef __int16 ogg_int16_t;

#else

/* Cygwin */
#include <_G_config.h>
typedef _G_int64_t ogg_int64_t;
typedef _G_int32_t ogg_int32_t;
typedef unsigned _G_int32_t ogg_uint32_t;
typedef _G_int16_t ogg_int16_t;
#endif
#else

#if defined(__BEOS__) || defined(__QNX__)
/* Be + QNX */
#include <inttypes.h>
#endif

#include <sys/types.h>

/* filled in by configure */
typedef int16_t ogg_int16_t;
typedef int32_t ogg_int32_t;
#ifdef __QNX__
typedef uint32_t ogg_uint32_t;
#else
typedef u_int32_t ogg_uint32_t;
#endif
typedef int64_t ogg_int64_t;

#endif

#endif 

