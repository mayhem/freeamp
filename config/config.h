/* config/config.h.  Generated automatically by configure.  */
/*
 * FreeAMP - The Free MP3 Player
 * Portions copyright (C) 1998 GoodNoise
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */


#ifndef CONFIG_H
#define CONFIG_H

#include <limits.h>


#define HAVE_UNISTD_H 1
#define HAVE_IO_H 0

#define HAVE_BASELINUXTHREADS 1
#define HAVE_ENHLINUXTHREADS 1
#define HAVE_MITPTHREADS 0


#ifdef __linux__ /* Linux requires thread support */
#if HAVE_BASELINUXTHREADS == 1 && HAVE_MITPTHREADS == 1
#error "Can't have both MIT Pthreads and LinuxThreads!! (i.e. I don't know which to use...)"
#endif

#if HAVE_MITPTHREADS == 0 && HAVE_BASELINUXTHREADS == 0
#error "Must have threads support!  (i.e. I can't find evidence of MIT pthreads or LinuxThreads)"
#endif
#endif /* __linux__ */

#if HAVE_UNISTD_H
#define RD_BNRY_FLAGS O_RDONLY
#elif HAVE_IO_H
#define RD_BNRY_FLAGS O_RDONLY | O_BINARY
#endif

/* Endian Issues */
#ifdef LINUX
#include <endian.h>
#endif /* LINUX */

#ifdef WIN32
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __PDP_ENDIAN    3412
#define __BYTE_ORDER    __LITTLE_ENDIAN
#endif

/* define our datatypes */
// real number
typedef double real;

#if UCHAR_MAX == 0xff

typedef unsigned char	uint8;
typedef signed char		int8;

#else
#error This machine has no 8-bit type
#endif

#if UINT_MAX == 0xffff

typedef unsigned int	uint16;
typedef int				int16;

#elif USHRT_MAX == 0xffff

typedef unsigned short	uint16;
typedef short			int16;

#else
#error This machine has no 16-bit type
#endif


#if UINT_MAX == 0xfffffffful

typedef unsigned int	uint32;
typedef int				int32;

#elif ULONG_MAX == 0xfffffffful

typedef unsigned long	uint32;
typedef long			int32;

#elif USHRT_MAX == 0xfffffffful

typedef unsigned short	uint32;
typedef short			int32;

#else
#error This machine has no 32-bit type
#endif


// What character marks the end of a directory entry? For DOS and
// Windows, it is "\"; in UNIX it is "/".
#if defined(WIN32) || defined(OS2) || defined(__DOS__)
#define DIR_MARKER '\\'
#define DIR_MARKER_STR "\\"
#else
#define DIR_MARKER '/'
#define DIR_MARKER_STR "/"
#endif /* WIN32 */

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif /* NULL */

#endif /* CONFIG_H */