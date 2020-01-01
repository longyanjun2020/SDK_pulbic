#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    : imgcodec_pngconf.h                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : png configuration                                             */
/****************************************************************************/


/* pngconf.h - machine configurable file for libpng
 *
 * libpng 1.2.4 - July 8, 2002
 * For conditions of distribution and use, see copyright notice in png.h
 * Copyright (c) 1998-2002 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 */

/* Any machine specific code is near the front of this file, so if you
 * are configuring libpng for a machine, you may want to read the section
 * starting here down to where it starts to typedef png_color, png_text,
 * and png_info.
 */
#ifndef _IMGCODEC_PNGCONF_H_
#define _IMGCODEC_PNGCONF_H_

#include "imgcodec_common.h"
#define png_malloc_ext img_malloc
#define png_free_ext   img_free
#define png_strcpy     img_strcpy
#define png_strlen     img_strlen
#define png_memcmp     img_memcmp
#define png_memcpy     img_memcpy
#define png_memset     img_memset

#define png_trace1 img_trace1
#define png_trace2 img_trace2
#define png_error1 img_error1
#define png_error2 img_error2

#define size_t unsigned int

#define PNG_USE_ZSTREAM_BUF
#ifdef PNG_USE_ZSTREAM_BUF
#define ZSTREAM_BUF_SIZE 4096
#endif

#define PNG_READ_16_TO_8_SUPPORTED
#define PNG_NO_ZALLOC_ZERO

/* This is the size of the compression buffer, and thus the size of
 * an IDAT chunk.  Make this whatever size you feel is best for your
 * machine.  One of these will be allocated per png_struct.  When this
 * is full, it writes the data to the disk, and does some other
 * calculations.  Making this an extremely small size will slow
 * the library down, but you may want to experiment to determine
 * where it becomes significant, if you are concerned with memory
 * usage.  Note that zlib allocates at least 32Kb also.  For readers,
 * this describes the size of the buffer available to read the data in.
 * Unless this gets smaller than the size of a row (compressed),
 * it should not make much difference how big this is.
 */

#ifndef PNG_ZBUF_SIZE
#  define PNG_ZBUF_SIZE 8192
#endif


/* If you are running on a machine where you cannot allocate more
 * than 64K of memory at once, uncomment this.  While libpng will not
 * normally need that much memory in a chunk (unless you load up a very
 * large file), zlib needs to know how big of a chunk it can use, and
 * libpng thus makes sure to check any memory allocation to verify it
 * will fit into memory.
#define PNG_MAX_MALLOC_64K
 */
#if defined(MAXSEG_64K) && !defined(PNG_MAX_MALLOC_64K)
#  define PNG_MAX_MALLOC_64K
#endif

/* Special munging to support doing things the 'cygwin' way:
 * 'Normal' png-on-win32 defines/defaults:
 *   PNG_BUILD_DLL -- building dll
 *   PNG_USE_DLL   -- building an application, linking to dll
 *   (no define)   -- building static library, or building an
 *                    application and linking to the static lib
 * 'Cygwin' defines/defaults:
 *   PNG_BUILD_DLL -- (ignored) building the dll
 *   (no define)   -- (ignored) building an application, linking to the dll
 *   PNG_STATIC    -- (ignored) building the static lib, or building an
 *                    application that links to the static lib.
 *   ALL_STATIC    -- (ignored) building various static libs, or building an
 *                    application that links to the static libs.
 * Thus,
 * a cygwin user should define either PNG_BUILD_DLL or PNG_STATIC, and
 * this bit of #ifdefs will define the 'correct' config variables based on
 * that. If a cygwin user *wants* to define 'PNG_USE_DLL' that's okay, but
 * unnecessary.
 *
 * Also, the precedence order is:
 *   ALL_STATIC (since we can't #undef something outside our namespace)
 *   PNG_BUILD_DLL
 *   PNG_STATIC
 *   (nothing) == PNG_USE_DLL
 *
 * CYGWIN (2002-01-20): The preceding is now obsolete. With the advent
 *   of auto-import in binutils, we no longer need to worry about
 *   __declspec(dllexport) / __declspec(dllimport) and friends.  Therefore,
 *   we don't need to worry about PNG_STATIC or ALL_STATIC when it comes
 *   to __declspec() stuff.  However, we DO need to worry about
 *   PNG_BUILD_DLL and PNG_STATIC because those change some defaults
 *   such as CONSOLE_IO and whether GLOBAL_ARRAYS are allowed.

 * This macro protects us against machines that don't have function
 * prototypes (ie K&R style headers).  If your compiler does not handle
 * function prototypes, define this macro and use the included ansi2knr.
 * I've always been able to use _NO_PROTO as the indicator, but you may
 * need to drag the empty declaration out in front of here, or change the
 * ifdef to suit your own needs.
 */
#ifndef PNGARG

#ifdef OF /* zlib prototype munger */
#  define PNGARG(arglist) OF(arglist)
#else

#ifdef _NO_PROTO
#  define PNGARG(arglist) ()
#  ifndef PNG_TYPECAST_NULL
#     define PNG_TYPECAST_NULL
#  endif
#else
#  define PNGARG(arglist) arglist
#endif /* _NO_PROTO */

#endif /* OF */

#endif /* PNGARG */


/* Other defines for things like memory and the like can go here.  */

/* The functions exported by PNG_EXTERN are PNG_INTERNAL functions, which
 * aren't usually used outside the library (as far as I know), so it is
 * debatable if they should be exported at all.  In the future, when it is
 * possible to have run-time registry of chunk-handling functions, some of
 * these will be made available again.
 */
#define PNG_EXTERN


/* The following uses const char * instead of char * for error
 * and warning message functions, so some compilers won't complain.
 * If you do not want to use const, define PNG_NO_CONST here.
 */

#ifndef PNG_NO_CONST
#  define PNG_CONST const
#else
#  define PNG_CONST
#endif

/* Some typedefs to get us started.  These should be safe on most of the
 * common platforms.  The typedefs should be at least as large as the
 * numbers suggest (a png_uint_32 must be at least 32 bits long), but they
 * don't have to be exactly that size.  Some compilers dislike passing
 * unsigned shorts as function parameters, so you may be better off using
 * unsigned int for png_uint_16.  Likewise, for 64-bit systems, you may
 * want to have unsigned int for png_uint_32 instead of unsigned long.
 */

typedef unsigned long png_uint_32;
typedef long png_int_32;
typedef unsigned short png_uint_16;
typedef short png_int_16;
typedef unsigned char png_byte;

/* This is usually size_t.  It is typedef'ed just in case you need it to
   change (I'm not sure if you will or not, so I thought I'd be safe) */
typedef size_t png_size_t;

/* The following is needed for medium model support.  It cannot be in the
 * PNG_INTERNAL section.  Needs modification for other compilers besides
 * MSC.  Model independent support declares all arrays and pointers to be
 * large using the far keyword.  The zlib version used must also support
 * model independent data.  As of version zlib 1.0.4, the necessary changes
 * have been made in zlib.  The USE_FAR_KEYWORD define triggers other
 * changes that are needed. (Tim Wegner)
 */

/* Suggest testing for specific compiler first before testing for
 * FAR.  The Watcom compiler defines both __MEDIUM__ and M_I86MM,
 * making reliance oncertain keywords suspect. (SJT)
 */

/* SJT: default case */
#ifndef FAR
#  define FAR
#endif

/* At this point FAR is always defined */
#ifndef FARDATA
#  define FARDATA
#endif

/* Typedef for floating-point numbers that are converted
   to fixed-point with a multiple of 100,000, e.g., int_gamma */
typedef png_int_32 png_fixed_point;

/* Add typedefs for pointers */
typedef void            FAR * png_voidp;
typedef png_byte        FAR * png_bytep;
typedef png_uint_32     FAR * png_uint_32p;
typedef png_int_32      FAR * png_int_32p;
typedef png_uint_16     FAR * png_uint_16p;
typedef png_int_16      FAR * png_int_16p;
typedef PNG_CONST char  FAR * png_const_charp;
typedef char            FAR * png_charp;
typedef png_fixed_point FAR * png_fixed_point_p;

/* Pointers to pointers; i.e. arrays */
typedef png_byte        FAR * FAR * png_bytepp;
typedef png_uint_32     FAR * FAR * png_uint_32pp;
typedef png_int_32      FAR * FAR * png_int_32pp;
typedef png_uint_16     FAR * FAR * png_uint_16pp;
typedef png_int_16      FAR * FAR * png_int_16pp;
typedef PNG_CONST char  FAR * FAR * png_const_charpp;
typedef char            FAR * FAR * png_charpp;
typedef png_fixed_point FAR * FAR * png_fixed_point_pp;

/* Pointers to pointers to pointers; i.e., pointer to array */
typedef char            FAR * FAR * FAR * png_charppp;

/* libpng typedefs for types in zlib. If zlib changes
 * or another compression library is used, then change these.
 * Eliminates need to change all the source files.
 */
typedef char *         png_zcharp;
typedef char * FAR *   png_zcharpp;
typedef z_stream FAR *  png_zstreamp;


/* Do not use global arrays (helps with building DLL's)
 * They are no longer used in libpng itself, since version 1.0.5c,
 * but might be required for some pre-1.0.5c applications.
 */
#define PNG_USE_GLOBAL_ARRAYS


/* If you define PNGAPI, e.g., with compiler option "-DPNGAPI=__stdcall",
 * you may get warnings regarding the linkage of png_zalloc and png_zfree.
 * Don't ignore those warnings; you must also reset the default calling
 * convention in your compiler to match your PNGAPI, and you must build
 * zlib and your applications the same way you build libpng.
 */

#ifndef PNGAPI
#  define PNGAPI
#endif

#ifndef PNG_IMPEXP
#  define PNG_IMPEXP
#endif

#ifndef PNG_EXPORT
#  define PNG_EXPORT(type,symbol) PNG_IMPEXP type PNGAPI symbol
#endif

#ifdef PNG_USE_GLOBAL_ARRAYS
#  ifndef PNG_EXPORT_VAR
#    define PNG_EXPORT_VAR(type) extern PNG_IMPEXP type
#  endif
#endif

/* User may want to use these so they are not in PNG_INTERNAL. Any library
 * functions that are passed far data must be model independent.
 */

#ifndef PNG_ABORT
#  define PNG_ABORT() {}
#endif


/* End of memory model independent support */

/* Just a little check that someone hasn't tried to define something
 * contradictory.
 */
#if (PNG_ZBUF_SIZE > 65536) && defined(PNG_MAX_MALLOC_64K)
#  undef PNG_ZBUF_SIZE
#  define PNG_ZBUF_SIZE 65536
#endif


#endif /* PNGCONF_H */
#endif

