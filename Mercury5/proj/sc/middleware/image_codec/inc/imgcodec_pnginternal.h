#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    : imgcodec_pnginternal.h                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : png header file                                               */
/****************************************************************************/


/* png.h - header file for PNG reference library
 *
 * libpng version 1.2.4 - July 8, 2002
 * Copyright (c) 1998-2002 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 *
 * Authors and maintainers:
 *  libpng versions 0.71, May 1995, through 0.88, January 1996: Guy Schalnat
 *  libpng versions 0.89c, June 1996, through 0.96, May 1997: Andreas Dilger
 *  libpng versions 0.97, January 1998, through 1.2.4 - July 8, 2002: Glenn
 *  See also "Contributing Authors", below.
 *
 * Note about libpng version numbers:
 *
 *    Due to various miscommunications, unforeseen code incompatibilities
 *    and occasional factors outside the authors' control, version numbering
 *    on the library has not always been consistent and straightforward.
 *    The following table summarizes matters since version 0.89c, which was
 *    the first widely used release:
 *
 *    source                 png.h  png.h  shared-lib
 *    version                string   int  version
 *    -------                ------ -----  ----------
 *    0.89c "1.0 beta 3"     0.89      89  1.0.89
 *    0.90  "1.0 beta 4"     0.90      90  0.90  [should have been 2.0.90]
 *    0.95  "1.0 beta 5"     0.95      95  0.95  [should have been 2.0.95]
 *    0.96  "1.0 beta 6"     0.96      96  0.96  [should have been 2.0.96]
 *    0.97b "1.00.97 beta 7" 1.00.97   97  1.0.1 [should have been 2.0.97]
 *    0.97c                  0.97      97  2.0.97
 *    0.98                   0.98      98  2.0.98
 *    0.99                   0.99      98  2.0.99
 *    0.99a-m                0.99      99  2.0.99
 *    1.00                   1.00     100  2.1.0 [100 should be 10000]
 *    1.0.0      (from here on, the   100  2.1.0 [100 should be 10000]
 *    1.0.1       png.h string is   10001  2.1.0
 *    1.0.1a-e    identical to the  10002  from here on, the shared library
 *    1.0.2       source version)   10002  is 2.V where V is the source code
 *    1.0.2a-b                      10003  version, except as noted.
 *    1.0.3                         10003
 *    1.0.3a-d                      10004
 *    1.0.4                         10004
 *    1.0.4a-f                      10005
 *    1.0.5 (+ 2 patches)           10005
 *    1.0.5a-d                      10006
 *    1.0.5e-r                      10100 (not source compatible)
 *    1.0.5s-v                      10006 (not binary compatible)
 *    1.0.6 (+ 3 patches)           10006 (still binary incompatible)
 *    1.0.6d-f                      10007 (still binary incompatible)
 *    1.0.6g                        10007
 *    1.0.6h                        10007  10.6h (testing xy.z so-numbering)
 *    1.0.6i                        10007  10.6i
 *    1.0.6j                        10007  2.1.0.6j (incompatible with 1.0.0)
 *    1.0.7beta11-14        DLLNUM  10007  2.1.0.7beta11-14 (binary compatible)
 *    1.0.7beta15-18           1    10007  2.1.0.7beta15-18 (binary compatible)
 *    1.0.7rc1-2               1    10007  2.1.0.7rc1-2 (binary compatible)
 *    1.0.7                    1    10007  (still compatible)
 *    1.0.8beta1-4             1    10008  2.1.0.8beta1-4
 *    1.0.8rc1                 1    10008  2.1.0.8rc1
 *    1.0.8                    1    10008  2.1.0.8
 *    1.0.9beta1-6             1    10009  2.1.0.9beta1-6
 *    1.0.9rc1                 1    10009  2.1.0.9rc1
 *    1.0.9beta7-10            1    10009  2.1.0.9beta7-10
 *    1.0.9rc2                 1    10009  2.1.0.9rc2
 *    1.0.9                    1    10009  2.1.0.9
 *    1.0.10beta1              1    10010  2.1.0.10beta1
 *    1.0.10rc1                1    10010  2.1.0.10rc1
 *    1.0.10                   1    10010  2.1.0.10
 *    1.0.11beta1-3            1    10011  2.1.0.11beta1-3
 *    1.0.11rc1                1    10011  2.1.0.11rc1
 *    1.0.11                   1    10011  2.1.0.11
 *    1.0.12beta1-2            2    10012  2.1.0.12beta1-2
 *    1.0.12rc1                2    10012  2.1.0.12rc1
 *    1.0.12                   2    10012  2.1.0.12
 *    1.1.0a-f                 -    10100  2.1.1.0a-f (branch abandoned)
 *    1.2.0beta1-2             2    10200  2.1.2.0beta1-2
 *    1.2.0beta3-5             3    10200  3.1.2.0beta3-5
 *    1.2.0rc1                 3    10200  3.1.2.0rc1
 *    1.2.0                    3    10200  3.1.2.0
 *    1.2.1beta1-4             3    10201  3.1.2.1beta1-4
 *    1.2.1rc1-2               3    10201  3.1.2.1rc1-2
 *    1.2.1                    3    10201  3.1.2.1
 *    1.2.2beta1-6            12    10202  12.so.0.1.2.2beta1-6
 *    1.0.13beta1             10    10013  10.so.0.1.0.13beta1
 *    1.0.13rc1               10    10013  10.so.0.1.0.13rc1
 *    1.2.2rc1                12    10202  12.so.0.1.2.2rc1
 *    1.0.13                  10    10013  10.so.0.1.0.13
 *    1.2.2                   12    10202  12.so.0.1.2.2
 *    1.2.3rc1-6              12    10203  12.so.0.1.2.3rc1-6
 *    1.2.3                   12    10203  12.so.0.1.2.3
 *    1.2.4beta1-3            13    10204  12.so.0.1.2.4beta1-3
 *    1.0.14rc1               13    10014  10.so.0.1.0.14rc1
 *    1.2.4rc1                13    10204  12.so.0.1.2.4rc1
 *    1.0.14                  10    10014  10.so.0.1.0.14
 *    1.2.4                   13    10204  12.so.0.1.2.4
 *
 *    Henceforth the source version will match the shared-library major
 *    and minor numbers; the shared-library major version number will be
 *    used for changes in backward compatibility, as it is intended.  The
 *    PNG_LIBPNG_VER macro, which is not used within libpng but is available
 *    for applications, is an unsigned integer of the form xyyzz corresponding
 *    to the source version x.y.z (leading zeros in y and z).  Beta versions
 *    were given the previous public release number plus a letter, until
 *    version 1.0.6j; from then on they were given the upcoming public
 *    release number plus "betaNN" or "rcN".
 *
 *    Binary incompatibility exists only when applications make direct access
 *    to the info_ptr or png_ptr members through png.h, and the compiled
 *    application is loaded with a different version of the library.
 *
 *    DLLNUM will change each time there are forward or backward changes
 *    in binary compatibility (e.g., when a new feature is added).
 *
 * See libpng.txt or libpng.3 for more information.  The PNG specification
 * is available as RFC 2083 <ftp://ftp.uu.net/graphics/png/documents/>
 * and as a W3C Recommendation <http://www.w3.org/TR/REC.png.html>
 */

/*
 * COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
 *
 * If you modify libpng you may insert additional notices immediately following
 * this sentence.
 *
 * libpng versions 1.0.7, July 1, 2000, through 1.2.4, July 8, 2002, are
 * Copyright (c) 2000-2002 Glenn Randers-Pehrson, and are
 * distributed according to the same disclaimer and license as libpng-1.0.6
 * with the following individuals added to the list of Contributing Authors
 *
 *    Simon-Pierre Cadieux
 *    Eric S. Raymond
 *    Gilles Vollant
 *
 * and with the following additions to the disclaimer:
 *
 *    There is no warranty against interference with your enjoyment of the
 *    library or against infringement.  There is no warranty that our
 *    efforts or the library will fulfill any of your particular purposes
 *    or needs.  This library is provided with all faults, and the entire
 *    risk of satisfactory quality, performance, accuracy, and effort is with
 *    the user.
 *
 * libpng versions 0.97, January 1998, through 1.0.6, March 20, 2000, are
 * Copyright (c) 1998, 1999, 2000 Glenn Randers-Pehrson
 * Distributed according to the same disclaimer and license as libpng-0.96,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    Tom Lane
 *    Glenn Randers-Pehrson
 *    Willem van Schaik
 *
 * libpng versions 0.89, June 1996, through 0.96, May 1997, are
 * Copyright (c) 1996, 1997 Andreas Dilger
 * Distributed according to the same disclaimer and license as libpng-0.88,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    John Bowler
 *    Kevin Bracey
 *    Sam Bushell
 *    Magnus Holmgren
 *    Greg Roelofs
 *    Tom Tanner
 *
 * libpng versions 0.5, May 1995, through 0.88, January 1996, are
 * Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.
 *
 * For the purposes of this copyright and license, "Contributing Authors"
 * is defined as the following set of individuals:
 *
 *    Andreas Dilger
 *    Dave Martindale
 *    Guy Eric Schalnat
 *    Paul Schmidt
 *    Tim Wegner
 *
 * The PNG Reference Library is supplied "AS IS".  The Contributing Authors
 * and Group 42, Inc. disclaim all warranties, expressed or implied,
 * including, without limitation, the warranties of merchantability and of
 * fitness for any purpose.  The Contributing Authors and Group 42, Inc.
 * assume no liability for direct, indirect, incidental, special, exemplary,
 * or consequential damages, which may result from the use of the PNG
 * Reference Library, even if advised of the possibility of such damage.
 *
 * Permission is hereby granted to use, copy, modify, and distribute this
 * source code, or portions hereof, for any purpose, without fee, subject
 * to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented.
 *
 * 2. Altered versions must be plainly marked as such and
 * must not be misrepresented as being the original source.
 *
 * 3. This Copyright notice may not be removed or altered from
 *    any source or altered source distribution.
 *
 * The Contributing Authors and Group 42, Inc. specifically permit, without
 * fee, and encourage the use of this source code as a component to
 * supporting the PNG file format in commercial products.  If you use this
 * source code in a product, acknowledgment is not required but would be
 * appreciated.
 */

/*
 * Libpng is OSI Certified Open Source Software.  OSI Certified is a
 * certification mark of the Open Source Initiative.
 */

/*
 * The contributing authors would like to thank all those who helped
 * with testing, bug fixes, and patience.  This wouldn't have been
 * possible without all of you.
 *
 * Thanks to Frank J. T. Wojcik for helping with the documentation.
 */

/*
 * Y2K compliance in libpng:
 * =========================
 *
 *    July 8, 2002
 *
 *    Since the PNG Development group is an ad-hoc body, we can't make
 *    an official declaration.
 *
 *    This is your unofficial assurance that libpng from version 0.71 and
 *    upward through 1.2.4 are Y2K compliant.  It is my belief that earlier
 *    versions were also Y2K compliant.
 *
 *    Libpng only has three year fields.  One is a 2-byte unsigned integer
 *    that will hold years up to 65535.  The other two hold the date in text
 *    format, and will hold years up to 9999.
 *
 *    The integer is
 *        "png_uint_16 year" in png_time_struct.
 *
 *    The strings are
 *        "png_charp time_buffer" in png_struct and
 *        "near_time_buffer", which is a local character string in png.c.
 *
 *    There are seven time-related functions:
 *        png.c: png_convert_to_rfc_1123() in png.c
 *          (formerly png_convert_to_rfc_1152() in error)
 *        png_convert_from_struct_tm() in pngwrite.c, called in pngwrite.c
 *        png_convert_from_time_t() in pngwrite.c
 *        png_get_tIME() in pngget.c
 *        png_handle_tIME() in pngrutil.c, called in pngread.c
 *        png_set_tIME() in pngset.c
 *        png_write_tIME() in pngwutil.c, called in pngwrite.c
 *
 *    All handle dates properly in a Y2K environment.  The
 *    png_convert_from_time_t() function calls gmtime() to convert from system
 *    clock time, which returns (year - 1900), which we properly convert to
 *    the full 4-digit year.  There is a possibility that applications using
 *    libpng are not passing 4-digit years into the png_convert_to_rfc_1123()
 *    function, or that they are incorrectly passing only a 2-digit year
 *    instead of "year - 1900" into the png_convert_from_struct_tm() function,
 *    but this is not under our control.  The libpng documentation has always
 *    stated that it works with 4-digit years, and the APIs have been
 *    documented as such.
 *
 *    The tIME chunk itself is also Y2K compliant.  It uses a 2-byte unsigned
 *    integer to hold the year, and can hold years as large as 65535.
 *
 *    zlib, upon which libpng depends, is also Y2K compliant.  It contains
 *    no date-related code.
 *
 *       Glenn Randers-Pehrson
 *       libpng maintainer
 *       PNG Development Group
 */

#ifndef _IMGCODEC_PNGINTERNAL_H_
#define _IMGCODEC_PNGINTERNAL_H_


#define ABS(a)           ((a)<0?-(a):(a))
#define abs(a)           (ABS(a))
/* This is not the place to learn how to use libpng.  The file libpng.txt
 * describes how to use libpng, and the file example.c summarizes it
 * with some code on which to build.  This file is useful for looking
 * at the actual function definitions and structure components.
 */

/* Version information for png.h - this should match the version in png.c */
#define PNG_LIBPNG_VER_STRING "1.2.4"

#define PNG_LIBPNG_VER_SONUM   0
#define PNG_LIBPNG_VER_DLLNUM  %DLLNUM%

/* These should match the first 3 components of PNG_LIBPNG_VER_STRING: */
#define PNG_LIBPNG_VER_MAJOR   1
#define PNG_LIBPNG_VER_MINOR   2
#define PNG_LIBPNG_VER_RELEASE 4
/* This should match the numeric part of the final component of
 * PNG_LIBPNG_VER_STRING, omitting any leading zero: */

#define PNG_LIBPNG_VER_BUILD  0

#define PNG_LIBPNG_BUILD_ALPHA    1
#define PNG_LIBPNG_BUILD_BETA     2
#define PNG_LIBPNG_BUILD_RC       3
#define PNG_LIBPNG_BUILD_STABLE   4
#define PNG_LIBPNG_BUILD_TYPEMASK 7
#define PNG_LIBPNG_BUILD_PATCH    8 /* Can be OR'ed with STABLE only */
#define PNG_LIBPNG_BUILD_TYPE 4

/* Careful here.  At one time, Guy wanted to use 082, but that would be octal.
 * We must not include leading zeros.
 * Versions 0.7 through 1.0.0 were in the range 0 to 100 here (only
 * version 1.0.0 was mis-numbered 100 instead of 10000).  From
 * version 1.0.1 it's    xxyyzz, where x=major, y=minor, z=release */
#define PNG_LIBPNG_VER 10204 /* 1.2.4 */

#ifndef PNG_VERSION_INFO_ONLY

/* include the compression library's header */
#include "imgcodec_png_zlib.h"

/* include all user configurable info, including optional assembler routines */
#include "imgcodec_pngconf.h"

/* Inhibit C++ name-mangling for libpng functions but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* This file is arranged in several sections.  The first section contains
 * structure and type definitions.  The second section contains the external
 * library functions, while the third has the internal library functions,
 * which applications aren't expected to use directly.
 */

#ifndef PNG_NO_TYPECAST_NULL
    #define int_p_NULL                (int *)NULL
    #define png_bytep_NULL            (png_bytep)NULL
    #define png_bytepp_NULL           (png_bytepp)NULL
    #define png_doublep_NULL          (png_doublep)NULL
    #define png_error_ptr_NULL        (png_error_ptr)NULL
    #define png_flush_ptr_NULL        (png_flush_ptr)NULL
    #define png_free_ptr_NULL         (png_free_ptr)NULL
    #define png_infopp_NULL           (png_infopp)NULL
    #define png_malloc_ptr_NULL       (png_malloc_ptr)NULL
    #define png_read_status_ptr_NULL  (png_read_status_ptr)NULL
    #define png_rw_ptr_NULL           (png_rw_ptr)NULL
    #define png_structp_NULL          (png_structp)NULL
    #define png_uint_16p_NULL         (png_uint_16p)NULL
    #define png_voidp_NULL            (png_voidp)NULL
    #define png_write_status_ptr_NULL (png_write_status_ptr)NULL
#else
    #define int_p_NULL                NULL
    #define png_bytep_NULL            NULL
    #define png_bytepp_NULL           NULL
    #define png_doublep_NULL          NULL
    #define png_error_ptr_NULL        NULL
    #define png_flush_ptr_NULL        NULL
    #define png_free_ptr_NULL         NULL
    #define png_infopp_NULL           NULL
    #define png_malloc_ptr_NULL       NULL
    #define png_read_status_ptr_NULL  NULL
    #define png_rw_ptr_NULL           NULL
    #define png_structp_NULL          NULL
    #define png_uint_16p_NULL         NULL
    #define png_voidp_NULL            NULL
    #define png_write_status_ptr_NULL NULL
#endif

/* variables declared in png.c - only it needs to define PNG_NO_EXTERN */
#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
#ifdef PNG_USE_GLOBAL_ARRAYS
/* This was removed in version 1.0.5c */
/* Structures to facilitate easy interlacing.  See png.c for more details */
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_start[7];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_inc[7];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_ystart[7];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_yinc[7];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_mask[7];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pass_dsp_mask[7];

/* This isn't currently used.  If you need it, see png.c for more details.
PNG_EXPORT_VAR (const int FARDATA) png_pass_height[7];
*/
#endif
#endif /* PNG_NO_EXTERN */

/* Three color definitions.  The order of the red, green, and blue, (and the
 * exact size) is not important, although the size of the fields need to
 * be png_byte or png_uint_16 (as defined below).
 */
typedef struct png_color_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
} png_color;
typedef png_color FAR * png_colorp;
typedef png_color FAR * FAR * png_colorpp;

typedef struct png_color_16_struct
{
   png_byte     index;    /* used for palette files */
   png_uint_16  red;   /* for use in red green blue files */
   png_uint_16  green;
   png_uint_16  blue;
   png_uint_16  gray;  /* for use in grayscale files */
} png_color_16;
typedef png_color_16 FAR * png_color_16p;
typedef png_color_16 FAR * FAR * png_color_16pp;

typedef struct png_color_8_struct
{
   png_byte red;   /* for use in red green blue files */
   png_byte green;
   png_byte blue;
   png_byte gray;  /* for use in grayscale files */
   png_byte alpha; /* for alpha channel files */
} png_color_8;
typedef png_color_8 FAR * png_color_8p;
typedef png_color_8 FAR * FAR * png_color_8pp;

/*
 * The following two structures are used for the in-core representation
 * of sPLT chunks.
 */
typedef struct png_sPLT_entry_struct
{
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 alpha;
   png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry FAR * png_sPLT_entryp;
typedef png_sPLT_entry FAR * FAR * png_sPLT_entrypp;

/*  When the depth of the sPLT palette is 8 bits, the color and alpha samples
 *  occupy the LSB of their respective members, and the MSB of each member
 *  is zero-filled.  The frequency member always occupies the full 16 bits.
 */

typedef struct png_sPLT_struct
{
   png_charp name;           /* palette name */
   png_byte depth;           /* depth of palette samples */
   png_sPLT_entryp entries;  /* palette entries */
   png_int_32 nentries;      /* number of palette entries */
} png_sPLT_t;
typedef png_sPLT_t FAR * png_sPLT_tp;
typedef png_sPLT_t FAR * FAR * png_sPLT_tpp;


/* png_info is a structure that holds the information in a PNG file so
 * that the application can find out the characteristics of the image.
 * If you are reading the file, this structure will tell you what is
 * in the PNG file.  If you are writing the file, fill in the information
 * you want to put into the PNG file, then call png_write_info().
 * The names chosen should be very close to the PNG specification, so
 * consult that document for information about the meaning of each field.
 *
 * With libpng < 0.95, it was only possible to directly set and read the
 * the values in the png_info_struct, which meant that the contents and
 * order of the values had to remain fixed.  With libpng 0.95 and later,
 * however, there are now functions that abstract the contents of
 * png_info_struct from the application, so this makes it easier to use
 * libpng with dynamic libraries, and even makes it possible to use
 * libraries that don't have all of the libpng ancillary chunk-handing
 * functionality.
 *
 * In any case, the order of the parameters in png_info_struct should NOT
 * be changed for as long as possible to keep compatibility with applications
 * that use the old direct-access method with png_info_struct.
 *
 * The following members may have allocated storage attached that should be
 * cleaned up before the structure is discarded: palette, trans, text,
 * pcal_purpose, pcal_units, pcal_params, hist, iccp_name, iccp_profile,
 * splt_palettes, scal_unit, row_pointers, and unknowns.   By default, these
 * are automatically freed when the info structure is deallocated, if they were
 * allocated internally by libpng.  This behavior can be changed by means
 * of the png_data_freer() function.
 *
 * More allocation details: all the chunk-reading functions that
 * change these members go through the corresponding png_set_*
 * functions.  A function to clear these members is available: see
 * png_free_data().  The png_set_* functions do not depend on being
 * able to point info structure members to any of the storage they are
 * passed (they make their own copies), EXCEPT that the png_set_text
 * functions use the same storage passed to them in the text_ptr or
 * itxt_ptr structure argument, and the png_set_rows and png_set_unknowns
 * functions do not make their own copies.
 */
typedef struct png_info_struct
{
   /* the following are necessary for every PNG file */
   png_uint_32 width;       /* width of image in pixels (from IHDR) */
   png_uint_32 height;      /* height of image in pixels (from IHDR) */
   png_uint_32 valid;       /* valid chunk data (see PNG_INFO_ below) */
   png_uint_32 rowbytes;    /* bytes needed to hold an untransformed row */
   png_colorp palette;      /* array of color values (valid & PNG_INFO_PLTE) */
   png_uint_16 num_palette; /* number of color entries in "palette" (PLTE) */
   png_uint_16 num_trans;   /* number of transparent palette color (tRNS) */
   png_byte bit_depth;      /* 1, 2, 4, 8, or 16 bits/channel (from IHDR) */
   png_byte color_type;     /* see PNG_COLOR_TYPE_ below (from IHDR) */
   /* The following three should have been named *_method not *_type */
   png_byte compression_type; /* must be PNG_COMPRESSION_TYPE_BASE (IHDR) */
   png_byte filter_type;    /* must be PNG_FILTER_TYPE_BASE (from IHDR) */
   png_byte interlace_type; /* One of PNG_INTERLACE_NONE, PNG_INTERLACE_ADAM7 */

   /* The following is informational only on read, and not used on writes. */
   png_byte channels;       /* number of data channels per pixel (1, 2, 3, 4) */
   png_byte pixel_depth;    /* number of bits per pixel */
   png_byte spare_byte;     /* to align the data, and for future use */
   png_byte signature[8];   /* magic bytes read by libpng from start of file */

   /* The rest of the data is optional.  If you are reading, check the
    * valid field to see if the information in these are valid.  If you
    * are writing, set the valid field to those chunks you want written,
    * and initialize the appropriate fields below.
    */

   /* The tRNS chunk supplies transparency data for paletted images and
    * other image types that don't need a full alpha channel.  There are
    * "num_trans" transparency values for a paletted image, stored in the
    * same order as the palette colors, starting from index 0.  Values
    * for the data are in the range [0, 255], ranging from fully transparent
    * to fully opaque, respectively.  For non-paletted images, there is a
    * single color specified that should be treated as fully transparent.
    * Data is valid if (valid & PNG_INFO_tRNS) is non-zero.
    */
   png_bytep trans; /* transparent values for paletted image */
   png_color_16 trans_values; /* transparent color for non-palette image */

} png_info;

typedef png_info FAR * png_infop;
typedef png_info FAR * FAR * png_infopp;

/* Maximum positive integer used in PNG is (2^31)-1 */
#define PNG_MAX_UINT ((png_uint_32)0x7fffffffL)


/* This is for compression type. PNG 1.0-1.2 only define the single type. */
#define PNG_COMPRESSION_TYPE_BASE 0 /* Deflate method 8, 32K window */
#define PNG_COMPRESSION_TYPE_DEFAULT PNG_COMPRESSION_TYPE_BASE

/* This is for filter type. PNG 1.0-1.2 only define the single type. */
#define PNG_FILTER_TYPE_BASE      0 /* Single row per-byte filtering */
#define PNG_INTRAPIXEL_DIFFERENCING 64 /* Used only in MNG datastreams */
#define PNG_FILTER_TYPE_DEFAULT   PNG_FILTER_TYPE_BASE

/* These are for the interlacing type.  These values should NOT be changed. */
#define PNG_INTERLACE_NONE        0 /* Non-interlaced image */
#define PNG_INTERLACE_ADAM7       1 /* Adam7 interlacing */
#define PNG_INTERLACE_LAST        2 /* Not a valid value */

/* Maximum number of entries in PLTE/sPLT/tRNS arrays */
#define PNG_MAX_PALETTE_LENGTH    256

/* These determine if an ancillary chunk's data has been successfully read
 * from the PNG header, or if the application has filled in the corresponding
 * data in the info_struct to be written into the output file.  The values
 * of the PNG_INFO_<chunk> defines should NOT be changed.
 */
#define PNG_INFO_gAMA 0x0001
#define PNG_INFO_sBIT 0x0002
#define PNG_INFO_cHRM 0x0004
#define PNG_INFO_PLTE 0x0008
#define PNG_INFO_tRNS 0x0010
#define PNG_INFO_bKGD 0x0020
#define PNG_INFO_hIST 0x0040
#define PNG_INFO_pHYs 0x0080
#define PNG_INFO_oFFs 0x0100
#define PNG_INFO_tIME 0x0200
#define PNG_INFO_pCAL 0x0400
#define PNG_INFO_sRGB 0x0800   /* GR-P, 0.96a */
#define PNG_INFO_iCCP 0x1000   /* ESR, 1.0.6 */
#define PNG_INFO_sPLT 0x2000   /* ESR, 1.0.6 */
#define PNG_INFO_sCAL 0x4000   /* ESR, 1.0.6 */
#define PNG_INFO_IDAT 0x8000L  /* ESR, 1.0.6 */

/* This is used for the transformation routines, as some of them
 * change these values for the row.  It also should enable using
 * the routines for other purposes.
 */
typedef struct png_row_info_struct
{
   png_uint_32 width; /* width of row */
   png_uint_32 rowbytes; /* number of bytes in row */
   png_byte color_type; /* color type of row */
   png_byte bit_depth; /* bit depth of row */
   png_byte channels; /* number of channels (1, 2, 3, or 4) */
   png_byte pixel_depth; /* bits per pixel (depth * channels) */
} png_row_info;

typedef png_row_info FAR * png_row_infop;
typedef png_row_info FAR * FAR * png_row_infopp;

/* These are the function types for the I/O functions and for the functions
 * that allow the user to override the default I/O functions with his or her
 * own.  The png_error_ptr type should match that of user-supplied warning
 * and error functions, while the png_rw_ptr type should match that of the
 * user read/write data functions.
 */
typedef struct png_struct_def png_struct;
typedef png_struct FAR * png_structp;

typedef void (PNGAPI *png_error_ptr) PNGARG((png_structp, png_const_charp));
typedef void (PNGAPI *png_rw_ptr) PNGARG((png_structp, png_bytep, png_size_t));
typedef void (PNGAPI *png_flush_ptr) PNGARG((png_structp));
typedef void (PNGAPI *png_read_status_ptr) PNGARG((png_structp, png_uint_32,
   int));

/* Transform masks for the high-level interface */
#define PNG_TRANSFORM_IDENTITY       0x0000    /* read and write */
#define PNG_TRANSFORM_STRIP_16       0x0001    /* read only */
#define PNG_TRANSFORM_STRIP_ALPHA    0x0002    /* read only */
#define PNG_TRANSFORM_PACKING        0x0004    /* read and write */
#define PNG_TRANSFORM_PACKSWAP       0x0008    /* read and write */
#define PNG_TRANSFORM_EXPAND         0x0010    /* read only */
#define PNG_TRANSFORM_INVERT_MONO    0x0020    /* read and write */
#define PNG_TRANSFORM_SHIFT          0x0040    /* read and write */
#define PNG_TRANSFORM_BGR            0x0080    /* read and write */
#define PNG_TRANSFORM_SWAP_ALPHA     0x0100    /* read and write */
#define PNG_TRANSFORM_SWAP_ENDIAN    0x0200    /* read and write */
#define PNG_TRANSFORM_INVERT_ALPHA   0x0400    /* read and write */
#define PNG_TRANSFORM_STRIP_FILLER   0x0800    /* WRITE only */

typedef png_voidp (*png_malloc_ptr) PNGARG((png_structp, png_size_t));
typedef void (*png_free_ptr) PNGARG((png_structp, png_voidp));

/* The structure that holds the information to read and write PNG files.
 * The only people who need to care about what is inside of this are the
 * people who will be modifying the library for their own special needs.
 * It should NOT be accessed directly by an application, except to store
 * the jmp_buf.
 */

struct png_struct_def
{
    png_rw_ptr      read_data_fn;   /* function for reading input data */
    png_bytep       io_ptr;          /* ptr to application struct for I/O functions */
    png_uint_32     io_pos;
    png_uint_32     io_pos_fcTL;

    png_uint_32     mode;          /* tells us where we are in the PNG file */
    png_uint_32     flags;         /* flags indicating various things to libpng */
    png_uint_32     transformations; /* which transformations to perform */

    z_stream        zstream;          /* pointer to decompression structure (below) */
    png_bytep       zbuf;            /* buffer for zlib */
    png_size_t      zbuf_size;      /* size of zbuf */
    int             zlib_level;            /* holds zlib compression level */
    int             zlib_method;           /* holds zlib compression method */
    int             zlib_window_bits;      /* holds zlib compression window bits */
    int             zlib_mem_level;        /* holds zlib compression memory level */
    int             zlib_strategy;         /* holds zlib compression strategy */

    png_uint_32     width;         /* width of image in pixels */
    png_uint_32     height;        /* height of image in pixels */
    png_uint_32     num_rows;      /* number of rows in current pass */
    png_uint_32     usr_width;     /* width of row at start of write */
    png_uint_32     rowbytes;      /* size of row in bytes */
    png_uint_32     irowbytes;     /* size of current interlaced row in bytes */
    png_uint_32     iwidth;        /* width of current interlaced row in pixels */
    png_uint_32     row_number;    /* current row in interlace pass */
    png_bytep       prev_row;        /* buffer to save previous (unfiltered) row */
    png_bytep       row_buf;         /* buffer to save current (unfiltered) row */
    png_bytep       sub_row;         /* buffer to save "sub" row when filtering */
    png_bytep       up_row;          /* buffer to save "up" row when filtering */
    png_bytep       avg_row;         /* buffer to save "avg" row when filtering */
    png_bytep       paeth_row;       /* buffer to save "Paeth" row when filtering */
    png_row_info    row_info;     /* used for transformation routines */

    png_uint_32     idat_size;     /* current IDAT size for read */
    png_uint_32     crc;           /* current chunk CRC value */
    png_colorp      palette;        /* palette from the input file */
    png_colorp      palette_buf;    /* buffer used by png_handle_PLTE */
    png_uint_16     num_palette;   /* number of color entries in palette */
    png_uint_16     num_trans;     /* number of transparency values */
    png_byte        chunk_name[5];    /* null-terminated name of current chunk */
    png_byte        compression;      /* file compression type (always 0) */
    png_byte        filter;           /* file filter type (always 0) */
    png_byte        interlaced;       /* PNG_INTERLACE_NONE, PNG_INTERLACE_ADAM7 */
    png_byte        pass;             /* current interlace pass (0 - 6) */
    png_byte        do_filter;        /* row filter flags (see PNG_FILTER_ below ) */
    png_byte        color_type;       /* color type of file */
    png_byte        bit_depth;        /* bit depth of file */
    png_byte        usr_bit_depth;    /* bit depth of users row */
    png_byte        pixel_depth;      /* number of bits per pixel */
    png_byte        channels;         /* number of channels in file */
    png_byte        usr_channels;     /* channels at start of write */
    png_byte        sig_bytes;        /* magic bytes read/written from start of file */

    png_bytep                   trans;           /* transparency values for paletted files */
    png_color_16                trans_values; /* transparency values for non-paletted files */

    png_read_status_ptr         read_row_fn;   /* called after each row is decoded */


/* New member added in libpng-1.0.13 and 1.2.0 */
   png_bytep big_row_buf;         /* buffer to save current (unfiltered) row */

   png_byte err_flags;
   png_info *info_ptr;

   // for apng
   png_uint_32 default_w;
   png_uint_32 default_h;
   png_uint_32 num_frames;
   png_uint_32 num_plays;
   png_uint_32 frame_num;
   png_uint_32 frame_seq;
   png_uint_32 frame_w;
   png_uint_32 frame_h;
   png_uint_32 frame_x;
   png_uint_32 frame_y;
   png_uint_32 frame_delay;
   png_byte    frame_dispose;
   png_byte    frame_blend;

   // add for part management
   png_uint_32 x1;
   png_uint_32 x2;
   png_uint_32 y1;
   png_uint_32 y2;
#ifdef PNG_USE_ZSTREAM_BUF
   png_bytep   zstream_buf;
   png_bytep   zstream_ptr_cur;
   png_bytep   zstream_ptr_end;
   png_uint_32 zstream_buf_size;
#endif
   void *pRender;
};


/* This prevents a compiler error in png.c if png.c and png.h are both at
   version 1.2.4
 */
typedef png_structp version_1_2_4;

typedef png_struct FAR * FAR * png_structpp;

/* Here are the function definitions most commonly used.  This is not
 * the place to find out how to use libpng.  See libpng.txt for the
 * full explanation, see example.c for the summary.  This just provides
 * a simple one line description of the use of each function.
 */

/* Tell lib we have already handled the first <num_bytes> magic bytes.
 * Handling more than 8 bytes from the beginning of the file is an error.
 */
//extern PNG_EXPORT(void,png_set_sig_bytes) PNGARG((png_structp png_ptr,
//   int num_bytes));

/* Check sig[start] through sig[start + num_to_check - 1] to see if it's a
 * PNG file.  Returns zero if the supplied bytes match the 8-byte PNG
 * signature, and non-zero otherwise.  Having num_to_check == 0 or
 * start > 7 will always fail (ie return non-zero).
 */
extern PNG_EXPORT(int,png_sig_cmp) PNGARG((png_bytep sig, png_size_t start,
   png_size_t num_to_check));

/* Allocate and initialize png_ptr struct for reading, and any other memory. */
extern PNG_EXPORT(png_structp,png_create_read_struct) PNGARG((png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn));

extern PNG_EXPORT(void,png_set_compression_buffer_size)
   PNGARG((png_structp png_ptr, png_uint_32 size));

/* Reset the compression stream */
extern PNG_EXPORT(int,png_reset_zstream) PNGARG((png_structp png_ptr));

/* Allocate and initialize the info structure */
extern PNG_EXPORT(png_infop,png_create_info_struct)
   PNGARG((png_structp png_ptr));

/* Initialize the info structure */
extern PNG_EXPORT(void,png_info_init_3) PNGARG((png_infopp info_ptr,
    png_size_t png_info_struct_size));

/* read the information before the actual image data. */
extern PNG_EXPORT(void,png_read_info) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

#if defined(PNG_READ_16_TO_8_SUPPORTED)
/* strip the second byte of information from a 16-bit depth file. */
extern PNG_EXPORT(void,png_set_strip_16) PNGARG((png_structp png_ptr));
#endif

/* optional call to update the users info structure */
extern PNG_EXPORT(void,png_read_update_info) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

/* read a row of data. */
extern PNG_EXPORT(void,png_read_row) PNGARG((png_structp png_ptr));

/* read the end of the PNG file. */
extern PNG_EXPORT(void,png_read_end) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

/* free any memory associated with the png_info_struct */
extern PNG_EXPORT(void,png_destroy_info_struct) PNGARG((png_structp png_ptr,
   png_infopp info_ptr_ptr));

/* free any memory associated with the png_struct and the png_info_structs */
extern PNG_EXPORT(void,png_destroy_read_struct) PNGARG((png_structpp
   png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr));

/* free all memory used by the read (old method - NOT DLL EXPORTED) */
extern void png_read_destroy PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_infop end_info_ptr));

/* set the libpng method of handling chunk CRC errors */
extern PNG_EXPORT(void,png_set_crc_action) PNGARG((png_structp png_ptr,
   int crit_action, int ancil_action));

/* Values for png_set_crc_action() to say how to handle CRC errors in
 * ancillary and critical chunks, and whether to use the data contained
 * therein.  Note that it is impossible to "discard" data in a critical
 * chunk.  For versions prior to 0.90, the action was always error/quit,
 * whereas in version 0.90 and later, the action for CRC errors in ancillary
 * chunks is warn/discard.  These values should NOT be changed.
 *
 *      value                       action:critical     action:ancillary
 */
#define PNG_CRC_DEFAULT       0  /* error/quit          warn/discard data */
#define PNG_CRC_ERROR_QUIT    1  /* error/quit          error/quit        */
#define PNG_CRC_WARN_DISCARD  2  /* (INVALID)           warn/discard data */
#define PNG_CRC_WARN_USE      3  /* warn/use data       warn/use data     */
#define PNG_CRC_QUIET_USE     4  /* quiet/use data      quiet/use data    */
#define PNG_CRC_NO_CHANGE     5  /* use current value   use current value */

/* These functions give the user control over the scan-line filtering in
 * libpng and the compression methods used by zlib.  These functions are
 * mainly useful for testing, as the defaults should work with most users.
 * Those users who are tight on memory or want faster performance at the
 * expense of compression can modify them.  See the compression library
 * header file (zlib.h) for an explination of the compression functions.
 */

/* set the filtering method(s) used by libpng.  Currently, the only valid
 * value for "method" is 0.
 */
extern PNG_EXPORT(void,png_set_filter) PNGARG((png_structp png_ptr, int method,
   int filters));

/* Flags for png_set_filter() to say which filters to use.  The flags
 * are chosen so that they don't conflict with real filter types
 * below, in case they are supplied instead of the #defined constants.
 * These values should NOT be changed.
 */
#define PNG_NO_FILTERS     0x00
#define PNG_FILTER_NONE    0x08
#define PNG_FILTER_SUB     0x10
#define PNG_FILTER_UP      0x20
#define PNG_FILTER_AVG     0x40
#define PNG_FILTER_PAETH   0x80
#define PNG_ALL_FILTERS (PNG_FILTER_NONE | PNG_FILTER_SUB | PNG_FILTER_UP | PNG_FILTER_AVG | PNG_FILTER_PAETH)

/* Filter values (not flags) - used in pngwrite.c, pngwutil.c for now.
 * These defines should NOT be changed.
 */
#define PNG_FILTER_VALUE_NONE  0
#define PNG_FILTER_VALUE_SUB   1
#define PNG_FILTER_VALUE_UP    2
#define PNG_FILTER_VALUE_AVG   3
#define PNG_FILTER_VALUE_PAETH 4
#define PNG_FILTER_VALUE_LAST  5

/* Heuristic used for row filter selection.  These defines should NOT be
 * changed.
 */
#define PNG_FILTER_HEURISTIC_DEFAULT    0  /* Currently "UNWEIGHTED" */
#define PNG_FILTER_HEURISTIC_UNWEIGHTED 1  /* Used by libpng < 0.95 */
#define PNG_FILTER_HEURISTIC_WEIGHTED   2  /* Experimental feature */
#define PNG_FILTER_HEURISTIC_LAST       3  /* Not a valid value */

/* Replace the (error and abort), and warning functions with user
 * supplied functions.  If no messages are to be printed you must still
 * write and use replacement functions. The replacement error_fn should
 * still do a longjmp to the last setjmp location if you are using this
 * method of error handling.  If error_fn or warning_fn is NULL, the
 * default function will be used.
 */

/* Replace the default data input function with a user supplied one. */
extern PNG_EXPORT(void,png_set_read_fn) PNGARG((png_structp png_ptr,
   unsigned char *io_ptr, png_rw_ptr read_data_fn));

/* Return the user pointer associated with the I/O functions */
extern PNG_EXPORT(png_voidp,png_get_io_ptr) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_set_read_status_fn) PNGARG((png_structp png_ptr,
   png_read_status_ptr read_row_fn));

extern PNG_EXPORT(png_voidp,png_malloc) PNGARG((png_structp png_ptr,
   png_uint_32 size));

/* Added at libpng version 1.2.4 */
extern PNG_EXPORT(png_voidp,png_malloc_warn) PNGARG((png_structp png_ptr,
   png_uint_32 size));

/* frees a pointer allocated by png_malloc() */
extern PNG_EXPORT(void,png_free) PNGARG((png_structp png_ptr, png_voidp ptr));

/* Free data that was allocated internally */
extern PNG_EXPORT(void,png_free_data) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 free_me, int num));
/* assignments for png_data_freer */
#define PNG_DESTROY_WILL_FREE_DATA 1
#define PNG_SET_WILL_FREE_DATA 1
#define PNG_USER_WILL_FREE_DATA 2
/* Flags for png_ptr->free_me and info_ptr->free_me */
#define PNG_FREE_HIST 0x0008
#define PNG_FREE_ICCP 0x0010
#define PNG_FREE_SPLT 0x0020
#define PNG_FREE_ROWS 0x0040
#define PNG_FREE_PCAL 0x0080
#define PNG_FREE_SCAL 0x0100
#define PNG_FREE_UNKN 0x0200
#define PNG_FREE_LIST 0x0400
#define PNG_FREE_PLTE 0x1000
#define PNG_FREE_TRNS 0x2000
#define PNG_FREE_TEXT 0x4000
#define PNG_FREE_ALL  0x7fff
#define PNG_FREE_MUL  0x4220 /* PNG_FREE_SPLT|PNG_FREE_TEXT|PNG_FREE_UNKN */

extern PNG_EXPORT(png_voidp,png_memcpy_check) PNGARG((png_structp png_ptr,
   png_voidp s1, png_voidp s2, png_uint_32 size));

extern PNG_EXPORT(png_voidp,png_memset_check) PNGARG((png_structp png_ptr,
   png_voidp s1, int value, png_uint_32 size));

extern PNG_EXPORT(void,png_error_set) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(png_byte,png_error_check) PNGARG((png_structp png_ptr));

/* The png_set_<chunk> functions are for storing values in the png_info_struct.
 * Similarly, the png_get_<chunk> calls are used to read values from the
 * png_info_struct, either storing the parameters in the passed variables, or
 * setting pointers into the png_info_struct where the data is stored.  The
 * png_get_<chunk> functions return a non-zero value if the data was available
 * in info_ptr, or return zero and do not change any of the parameters if the
 * data was not available.
 *
 * These functions should be used instead of directly accessing png_info
 * to avoid problems with future changes in the size and internal layout of
 * png_info_struct.
 */
extern PNG_EXPORT(png_uint_32,png_get_IHDR) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 *width, png_uint_32 *height,
   int *bit_depth, int *color_type, int *interlace_method,
   int *compression_method, int *filter_method));

extern PNG_EXPORT(void,png_set_IHDR) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth,
   int color_type, int interlace_method, int compression_method,
   int filter_method));

extern PNG_EXPORT(png_uint_32,png_get_PLTE) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_colorp *palette, int *num_palette));

extern PNG_EXPORT(void,png_set_PLTE) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_colorp palette, int num_palette));

extern PNG_EXPORT(void,png_set_tRNS) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytep trans, int num_trans,
   png_color_16p trans_values));

/* Png_free_data() will turn off the "valid" flag for anything it frees.
   If you need to turn it off for a chunk that your application has freed,
   you can use png_set_invalid(png_ptr, info_ptr, PNG_INFO_CHNK); */
extern PNG_EXPORT(void, png_set_invalid) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int mask));

#ifndef png_debug
#define png_debug(l, m)
#endif
#ifndef png_debug1
#define png_debug1(l, m, p1)
#endif
#ifndef png_debug2
#define png_debug2(l, m, p1, p2)
#endif

//extern PNG_EXPORT(png_bytep,png_sig_bytes) PNGARG((void));

/* Various modes of operation.  Note that after an init, mode is set to
 * zero automatically when the structure is created.
 */
#define PNG_HAVE_IHDR               0x01
#define PNG_HAVE_PLTE               0x02
#define PNG_HAVE_IDAT               0x04
#define PNG_AFTER_IDAT              0x08
#define PNG_HAVE_IEND               0x10
#define PNG_HAVE_gAMA               0x20
#define PNG_HAVE_cHRM               0x40
#define PNG_HAVE_sRGB               0x80
#define PNG_HAVE_CHUNK_HEADER      0x100
#define PNG_WROTE_tIME             0x200
#define PNG_WROTE_INFO_BEFORE_PLTE 0x400
#define PNG_BACKGROUND_IS_GRAY     0x800
#define PNG_HAVE_PNG_SIGNATURE    0x1000
#define PNG_HAVE_acTL             0x2000
#define PNG_HAVE_fcTL             0x4000

/* flags for the transformations the PNG library does on the image data */
#define PNG_BGR                0x0001
#define PNG_INTERLACE          0x0002
#define PNG_PACK               0x0004
#define PNG_SHIFT              0x0008
#define PNG_SWAP_BYTES         0x0010
#define PNG_INVERT_MONO        0x0020
#define PNG_DITHER             0x0040
#define PNG_BACKGROUND         0x0080
#define PNG_BACKGROUND_EXPAND  0x0100
                          /*   0x0200 unused */
#define PNG_16_TO_8            0x0400
#define PNG_RGBA               0x0800
#define PNG_EXPAND             0x1000
#define PNG_GAMMA              0x2000
#define PNG_GRAY_TO_RGB        0x4000
#define PNG_FILLER             0x8000L
#define PNG_PACKSWAP          0x10000L
#define PNG_SWAP_ALPHA        0x20000L
#define PNG_STRIP_ALPHA       0x40000L
#define PNG_INVERT_ALPHA      0x80000L
#define PNG_USER_TRANSFORM   0x100000L
#define PNG_RGB_TO_GRAY_ERR  0x200000L
#define PNG_RGB_TO_GRAY_WARN 0x400000L
#define PNG_RGB_TO_GRAY      0x600000L  /* two bits, RGB_TO_GRAY_ERR|WARN */

/* flags for png_create_struct */
#define PNG_STRUCT_PNG   0x0001
#define PNG_STRUCT_INFO  0x0002

/* Scaling factor for filter heuristic weighting calculations */
#define PNG_WEIGHT_SHIFT 8
#define PNG_WEIGHT_FACTOR (1<<(PNG_WEIGHT_SHIFT))
#define PNG_COST_SHIFT 3
#define PNG_COST_FACTOR (1<<(PNG_COST_SHIFT))

/* flags for the png_ptr->flags rather than declaring a byte for each one */
#define PNG_FLAG_ZLIB_CUSTOM_STRATEGY     0x0001
#define PNG_FLAG_ZLIB_CUSTOM_LEVEL        0x0002
#define PNG_FLAG_ZLIB_CUSTOM_MEM_LEVEL    0x0004
#define PNG_FLAG_ZLIB_CUSTOM_WINDOW_BITS  0x0008
#define PNG_FLAG_ZLIB_CUSTOM_METHOD       0x0010
#define PNG_FLAG_ZLIB_FINISHED            0x0020
#define PNG_FLAG_ROW_INIT                 0x0040
#define PNG_FLAG_FILLER_AFTER             0x0080
#define PNG_FLAG_CRC_ANCILLARY_USE        0x0100
#define PNG_FLAG_CRC_ANCILLARY_NOWARN     0x0200
#define PNG_FLAG_CRC_CRITICAL_USE         0x0400
#define PNG_FLAG_CRC_CRITICAL_IGNORE      0x0800
#define PNG_FLAG_FREE_PLTE                0x1000
#define PNG_FLAG_FREE_TRNS                0x2000
#define PNG_FLAG_FREE_HIST                0x4000
#define PNG_FLAG_KEEP_UNKNOWN_CHUNKS      0x8000L
#define PNG_FLAG_KEEP_UNSAFE_CHUNKS       0x10000L
#define PNG_FLAG_LIBRARY_MISMATCH         0x20000L
#define PNG_FLAG_STRIP_ERROR_NUMBERS      0x40000L
#define PNG_FLAG_STRIP_ERROR_TEXT         0x80000L
#define PNG_FLAG_MALLOC_NULL_MEM_OK       0x100000L

/* flags for the png_ptr->err_flags */
#define PNG_ERR_FATAL                     0x0001
#define PNG_ERR_MALLOC_FAIL               0x0002


/* For use in png_set_keep_unknown, png_handle_as_unknown */
#define HANDLE_CHUNK_AS_DEFAULT   0
#define HANDLE_CHUNK_NEVER        1
#define HANDLE_CHUNK_IF_SAFE      2
#define HANDLE_CHUNK_ALWAYS       3

#define PNG_FLAG_CRC_ANCILLARY_MASK (PNG_FLAG_CRC_ANCILLARY_USE | \
                                     PNG_FLAG_CRC_ANCILLARY_NOWARN)

#define PNG_FLAG_CRC_CRITICAL_MASK  (PNG_FLAG_CRC_CRITICAL_USE | \
                                     PNG_FLAG_CRC_CRITICAL_IGNORE)

#define PNG_FLAG_CRC_MASK           (PNG_FLAG_CRC_ANCILLARY_MASK | \
                                     PNG_FLAG_CRC_CRITICAL_MASK)

/* save typing and make code easier to understand */
#define PNG_COLOR_DIST(c1, c2) (abs((int)((c1).red) - (int)((c2).red)) + \
   abs((int)((c1).green) - (int)((c2).green)) + \
   abs((int)((c1).blue) - (int)((c2).blue)))

/* variables declared in png.c - only it needs to define PNG_NO_EXTERN */
#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
/* place to hold the signature string for a PNG file. */
#ifdef PNG_USE_GLOBAL_ARRAYS
   PNG_EXPORT_VAR (const png_byte FARDATA) png_sig[8];
#endif
#endif /* PNG_NO_EXTERN */

/* Constant strings for known chunk types.  If you need to add a chunk,
 * define the name here, and add an invocation of the macro in png.c and
 * wherever it's needed.
 */
#define PNG_IHDR const png_byte png_IHDR[5] = { 'I',  'H',  'D',  'R', '\0'}
#define PNG_IDAT const png_byte png_IDAT[5] = { 73,  68,  65,  84, '\0'}
#define PNG_IEND const png_byte png_IEND[5] = { 73,  69,  78,  68, '\0'}
#define PNG_PLTE const png_byte png_PLTE[5] = { 80,  76,  84,  69, '\0'}
#define PNG_bKGD const png_byte png_bKGD[5] = { 98,  75,  71,  68, '\0'}
#define PNG_cHRM const png_byte png_cHRM[5] = { 99,  72,  82,  77, '\0'}
#define PNG_gAMA const png_byte png_gAMA[5] = {103,  65,  77,  65, '\0'}
#define PNG_hIST const png_byte png_hIST[5] = {104,  73,  83,  84, '\0'}
#define PNG_iCCP const png_byte png_iCCP[5] = {105,  67,  67,  80, '\0'}
#define PNG_iTXt const png_byte png_iTXt[5] = {105,  84,  88, 116, '\0'}
#define PNG_oFFs const png_byte png_oFFs[5] = {111,  70,  70, 115, '\0'}
#define PNG_pCAL const png_byte png_pCAL[5] = {112,  67,  65,  76, '\0'}
#define PNG_sCAL const png_byte png_sCAL[5] = {115,  67,  65,  76, '\0'}
#define PNG_pHYs const png_byte png_pHYs[5] = {112,  72,  89, 115, '\0'}
#define PNG_sBIT const png_byte png_sBIT[5] = {115,  66,  73,  84, '\0'}
#define PNG_sPLT const png_byte png_sPLT[5] = {115,  80,  76,  84, '\0'}
#define PNG_sRGB const png_byte png_sRGB[5] = {115,  82,  71,  66, '\0'}
#define PNG_tEXt const png_byte png_tEXt[5] = {116,  69,  88, 116, '\0'}
#define PNG_tIME const png_byte png_tIME[5] = {116,  73,  77,  69, '\0'}
#define PNG_tRNS const png_byte png_tRNS[5] = {116,  82,  78,  83, '\0'}
#define PNG_zTXt const png_byte png_zTXt[5] = {122,  84,  88, 116, '\0'}
#define PNG_acTL const png_byte png_acTL[5] = {'a', 'c', 'T', 'L', '\0'}
#define PNG_fcTL const png_byte png_fcTL[5] = {'f', 'c', 'T', 'L', '\0'}
#define PNG_fdAT const png_byte png_fdAT[5] = {'f', 'd', 'A', 'T', '\0'}

#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (const png_byte FARDATA) png_IHDR[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_IDAT[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_IEND[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_PLTE[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_bKGD[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_cHRM[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_gAMA[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_hIST[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_iCCP[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_iTXt[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_oFFs[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pCAL[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_sCAL[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_pHYs[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_sBIT[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_sPLT[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_sRGB[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_tEXt[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_tIME[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_tRNS[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_zTXt[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_acTL[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_fcTL[5];
PNG_EXPORT_VAR (const png_byte FARDATA) png_fdAT[5];
#endif /* PNG_USE_GLOBAL_ARRAYS */


/* Inline macros to do direct reads of bytes from the input buffer.  These
 * require that you are using an architecture that uses PNG byte ordering
 * (MSB first) and supports unaligned data storage.  I think that PowerPC
 * in big-endian mode and 680x0 are the only ones that will support this.
 * The x86 line of processors definitely do not.  The png_get_int_32()
 * routine also assumes we are using two's complement format for negative
 * values, which is almost certainly true.
 */
PNG_EXTERN png_uint_32 png_get_uint_32 PNGARG((png_bytep buf));
PNG_EXTERN png_uint_16 png_get_uint_16 PNGARG((png_bytep buf));

/* Allocate memory for an internal libpng struct */
PNG_EXTERN png_voidp png_create_struct PNGARG((int type));

/* Free memory from internal libpng struct */
PNG_EXTERN void png_destroy_struct PNGARG((png_voidp struct_ptr));

/* Free any memory that info_ptr points to and reset struct. */
PNG_EXTERN void png_info_destroy PNGARG((png_structp png_ptr,
   png_infop info_ptr));
/* Function to allocate memory for zlib. */
PNG_EXTERN voidpf png_zalloc PNGARG((voidpf png_ptr, uInt items, uInt size));

/* Function to free memory for zlib */
PNG_EXTERN void png_zfree PNGARG((voidpf png_ptr, voidpf ptr));

/* Reset the CRC variable */
PNG_EXTERN void png_reset_crc PNGARG((png_structp png_ptr));

/* Read data from whatever input you are using into the "data" buffer */
PNG_EXTERN void png_read_data PNGARG((png_structp png_ptr, png_bytep data,
   png_size_t length));

/* Read bytes into buf, and update png_ptr->crc */
PNG_EXTERN void png_crc_read PNGARG((png_structp png_ptr, png_bytep buf,
   png_size_t length));

/* Read "skip" bytes, read the file crc, and (optionally) verify png_ptr->crc */
PNG_EXTERN int png_crc_finish PNGARG((png_structp png_ptr, png_uint_32 skip));

/* Read the CRC from the file and compare it to the libpng calculated CRC */
PNG_EXTERN int png_crc_error PNGARG((png_structp png_ptr));

/* Calculate the CRC over a section of data.  Note that we are only
 * passing a maximum of 64K on systems that have this as a memory limit,
 * since this is the maximum buffer size we can specify.
 */
PNG_EXTERN void png_calculate_crc PNGARG((png_structp png_ptr, png_bytep ptr,
   png_size_t length));

/* combine a row of data, dealing with alpha, etc. if requested */
PNG_EXTERN void png_combine_row PNGARG((png_structp png_ptr, png_bytep row,
   int mask));

/* unfilter a row */
PNG_EXTERN void png_read_filter_row PNGARG((png_structp png_ptr,
   png_row_infop row_info, png_bytep row, png_bytep prev_row, int filter));

/* finish a row while reading, dealing with interlacing passes, etc. */
PNG_EXTERN void png_read_finish_row PNGARG((png_structp png_ptr));

/* initialize the row buffers, etc. */
PNG_EXTERN void png_read_start_row PNGARG((png_structp png_ptr));
/* optional call to update the users info structure */
PNG_EXTERN void png_read_transform_info PNGARG((png_structp png_ptr,
   png_infop info_ptr));

#if defined(PNG_READ_16_TO_8_SUPPORTED)
PNG_EXTERN void png_do_chop PNGARG((png_row_infop row_info, png_bytep row));
#endif

/* The following decodes the appropriate chunks, and does error correction,
 * then calls the appropriate callback for the chunk if it is valid.
 */

/* decode the IHDR chunk */
PNG_EXTERN void png_handle_IHDR PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
PNG_EXTERN void png_handle_PLTE PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
PNG_EXTERN void png_handle_IEND PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
PNG_EXTERN void png_handle_tRNS PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));

#ifdef IMGCODEC_COMPILE_APNG
PNG_EXTERN void png_handle_acTL PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
PNG_EXTERN void png_handle_fcTL PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
#endif

PNG_EXTERN void png_handle_unknown PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length));


PNG_EXTERN void png_check_chunk_name PNGARG((png_structp png_ptr,
   png_bytep chunk_name));

/* handle the transformations for reading and writing */
PNG_EXTERN void png_do_read_transformations PNGARG((png_structp png_ptr));

PNG_EXTERN void png_init_read_transformations PNGARG((png_structp png_ptr));


/* Maintainer: Put new private prototypes here ^ and in libpngpf.3 */


#ifdef __cplusplus
}
#endif

#endif /* PNG_VERSION_INFO_ONLY */
/* do not put anything past this line */
#endif /* _IMGCODEC_PNGINTERNAL_H_ */
#endif

