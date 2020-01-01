/***************************************************************************/
/*                                                                         */
/*  ftheader.h                                                             */
/*                                                                         */
/*    Build macros of the FreeType 2 library.                              */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 by       */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/
/*  MStar Semiconductor, Inc. hereby chooses to receive license on the     */
/*  FreeType 2 font engine under the FreeType License, found in the file   */
/*  'FTL.TXT'                                                              */
/***************************************************************************/

#ifndef __FT_HEADER_H__
#define __FT_HEADER_H__


  /*@***********************************************************************/
  /*                                                                       */
  /* <Macro>                                                               */
  /*    FT_BEGIN_HEADER                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This macro is used in association with @FT_END_HEADER in header    */
  /*    files to ensure that the declarations within are properly          */
  /*    encapsulated in an `extern "C" { .. }' block when included from a  */
  /*    C++ compiler.                                                      */
  /*                                                                       */
#ifdef __cplusplus
#define FT_BEGIN_HEADER  extern "C" {
#else
#define FT_BEGIN_HEADER  /* nothing */
#endif


  /*@***********************************************************************/
  /*                                                                       */
  /* <Macro>                                                               */
  /*    FT_END_HEADER                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    This macro is used in association with @FT_BEGIN_HEADER in header  */
  /*    files to ensure that the declarations within are properly          */
  /*    encapsulated in an `extern "C" { .. }' block when included from a  */
  /*    C++ compiler.                                                      */
  /*                                                                       */
#ifdef __cplusplus
#define FT_END_HEADER  }
#else
#define FT_END_HEADER  /* nothing */
#endif


  /*************************************************************************/
  /*                                                                       */
  /* Aliases for the FreeType 2 public and configuration files.            */
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Section>                                                             */
  /*    header_file_macros                                                 */
  /*                                                                       */
  /* <Title>                                                               */
  /*    Header File Macros                                                 */
  /*                                                                       */
  /* <Abstract>                                                            */
  /*    Macro definitions used to #include specific header files.          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The following macros are defined to the name of specific           */
  /*    FreeType~2 header files.  They can be used directly in #include    */
  /*    statements as in:                                                  */
  /*                                                                       */
  /*    {                                                                  */
  /*      #include <freetype.h>                                           */
  /*      #include FT_MULTIPLE_MASTERS_H                                   */
  /*      #include <ftglyph.h>                                              */
  /*    }                                                                  */
  /*                                                                       */
  /*    There are several reasons why we are now using macros to name      */
  /*    public header files.  The first one is that such macros are not    */
  /*    limited to the infamous 8.3~naming rule required by DOS (and       */
  /*    `FT_MULTIPLE_MASTERS_H' is a lot more meaningful than `ftmm.h').   */
  /*                                                                       */
  /*    The second reason is that it allows for more flexibility in the    */
  /*    way FreeType~2 is installed on a given system.                     */
  /*                                                                       */
  /*************************************************************************/


  /* configuration files */

  /*************************************************************************
   *
   * @macro:
   *   <ftconfig.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing
   *   FreeType~2 configuration data.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftstdlib.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing
   *   FreeType~2 interface to the standard C library functions.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftoption.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing
   *   FreeType~2 project-specific configuration options.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftmodule.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   list of FreeType~2 modules that are statically linked to new library
   *   instances in @FT_Init_FreeType.
   *
   */

  /* */

  /* public headers */

  /*************************************************************************
   *
   * @macro:
   *   <freetype.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   base FreeType~2 API.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <fterrors.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   list of FreeType~2 error codes (and messages).
   *
   *   It is included by @<freetype.h>.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftmoderr.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   list of FreeType~2 module error offsets (and messages).
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftsystem.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 interface to low-level operations (i.e., memory management
   *   and stream i/o).
   *
   *   It is included by @<freetype.h>.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftimage.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing type
   *   definitions related to glyph images (i.e., bitmaps, outlines,
   *   scan-converter parameters).
   *
   *   It is included by @<freetype.h>.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <fttypes.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   basic data types defined by FreeType~2.
   *
   *   It is included by @<freetype.h>.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftlist.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   list management API of FreeType~2.
   *
   *   (Most applications will never need to include this file.)
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftoutln.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   scalable outline management API of FreeType~2.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftsizes.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   API which manages multiple @FT_Size objects per face.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftmodapi.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   module management API of FreeType~2.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftrender.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   renderer module management API of FreeType~2.
   *
   */


  /*************************************************************************
   *
   * @macro:
   *   <t1tables.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   types and API specific to the Type~1 format.
   *
   */


  /*************************************************************************
   *
   * @macro:
   *   <ttnameid.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   enumeration values which identify name strings, languages, encodings,
   *   etc.  This file really contains a _large_ set of constant macro
   *   definitions, taken from the TrueType and OpenType specifications.
   *
   */


  /*************************************************************************
   *
   * @macro:
   *   <tttables.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   types and API specific to the TrueType (as well as OpenType) format.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <tttags.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of TrueType four-byte `tags' which identify blocks in
   *   SFNT-based font formats (i.e., TrueType and OpenType).
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   FT_BDF_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of an API which accesses BDF-specific strings from a
   *   face.
   *
   */
#define FT_BDF_H  <ftbdf.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_CID_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of an API which access CID font information from a
   *   face.
   *
   */
#define FT_CID_H  <ftcid.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_GZIP_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of an API which supports gzip-compressed files.
   *
   */
#define FT_GZIP_H  <ftgzip.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_LZW_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of an API which supports LZW-compressed files.
   *
   */
#define FT_LZW_H  <ftlzw.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_WINFONTS_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   definitions of an API which supports Windows FNT files.
   *
   */
#define FT_WINFONTS_H   <ftwinfnt.h>


  /*************************************************************************
   *
   * @macro:
   *   <ftglyph.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   API of the optional glyph management component.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftbitmap.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   API of the optional bitmap conversion component.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftbbox.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   API of the optional exact bounding box computation routines.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftcache.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   API of the optional FreeType~2 cache sub-system.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftcache.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   `glyph image' API of the FreeType~2 cache sub-system.
   *
   *   It is used to define a cache for @FT_Glyph elements.  You can also
   *   use the API defined in @<ftcache.h> if you only need to
   *   store small glyph bitmaps, as it will use less memory.
   *
   *   This macro is deprecated.  Simply include @<ftcache.h> to have all
   *   glyph image-related cache declarations.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftcache.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   `small bitmaps' API of the FreeType~2 cache sub-system.
   *
   *   It is used to define a cache for small glyph bitmaps in a relatively
   *   memory-efficient way.  You can also use the API defined in
   *   @<ftcache.h> if you want to cache arbitrary glyph images,
   *   including scalable outlines.
   *
   *   This macro is deprecated.  Simply include @<ftcache.h> to have all
   *   small bitmaps-related cache declarations.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftcache.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   `charmap' API of the FreeType~2 cache sub-system.
   *
   *   This macro is deprecated.  Simply include @<ftcache.h> to have all
   *   charmap-based cache declarations.
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   FT_MAC_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   Macintosh-specific FreeType~2 API.  The latter is used to access
   *   fonts embedded in resource forks.
   *
   *   This header file must be explicitly included by client applications
   *   compiled on the Mac (note that the base API still works though).
   *
   */
#define FT_MAC_H  <ftmac.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_MULTIPLE_MASTERS_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   optional multiple-masters management API of FreeType~2.
   *
   */
#define FT_MULTIPLE_MASTERS_H  <ftmm.h>


  /*************************************************************************
   *
   * @macro:
   *   <ftsnames.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   optional FreeType~2 API which accesses embedded `name' strings in
   *   SFNT-based font formats (i.e., TrueType and OpenType).
   *
   */

  /*************************************************************************
   *
   * @macro:
   *   FT_OPENTYPE_VALIDATE_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   optional FreeType~2 API which validates OpenType tables (BASE, GDEF,
   *   GPOS, GSUB, JSTF).
   *
   */
#define FT_OPENTYPE_VALIDATE_H  <ftotval.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_GX_VALIDATE_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   optional FreeType~2 API which validates TrueTypeGX/AAT tables (feat,
   *   mort, morx, bsln, just, kern, opbd, trak, prop).
   *
   */
#define FT_GX_VALIDATE_H  <ftgxval.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_PFR_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which accesses PFR-specific data.
   *
   */
#define FT_PFR_H  <ftpfr.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_STROKER_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which provides functions to stroke outline paths.
   */
#define FT_STROKER_H  <ftstroke.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_SYNTHESIS_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which performs artificial obliquing and emboldening.
   */
#define FT_SYNTHESIS_H  <ftsynth.h>


  /*************************************************************************
   *
   * @macro:
   *   FT_XFREE86_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which provides functions specific to the XFree86 and
   *   X.Org X11 servers.
   */
#define FT_XFREE86_H  <ftxf86.h>


  /*************************************************************************
   *
   * @macro:
   *   <fttrigon.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which performs trigonometric computations (e.g.,
   *   cosines and arc tangents).
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftlcdfil.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which performs color filtering for subpixel rendering.
   */

  /*************************************************************************
   *
   * @macro:
   *   <ttunpat.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which performs color filtering for subpixel rendering.
   */

  /*************************************************************************
   *
   * @macro:
   *   <ftincrem.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which performs color filtering for subpixel rendering.
   */

  /*************************************************************************
   *
   * @macro:
   *   FT_GASP_H
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which returns entries from the TrueType GASP table.
   */
#define FT_GASP_H  <ftgasp.h>


  /*************************************************************************
   *
   * @macro:
   *   <ftadvanc.h>
   *
   * @description:
   *   A macro used in #include statements to name the file containing the
   *   FreeType~2 API which returns individual and ranged glyph advances.
   */

  /* */

  /* The internals of the cache sub-system are no longer exposed.  We */
  /* default to <ftcache.h> at the moment just in case, but we know of */
  /* no rogue client that uses them.                                  */
  /*                                                                  */
#define FT_CACHE_MANAGER_H           <ftcache.h>
#define FT_CACHE_INTERNAL_MRU_H      <ftcache.h>
#define FT_CACHE_INTERNAL_MANAGER_H  <ftcache.h>
#define FT_CACHE_INTERNAL_CACHE_H    <ftcache.h>
#define FT_CACHE_INTERNAL_GLYPH_H    <ftcache.h>
#define FT_CACHE_INTERNAL_IMAGE_H    <ftcache.h>
#define FT_CACHE_INTERNAL_SBITS_H    <ftcache.h>

#define FT_TRUETYPE_UNPATENTED_H  <ttunpat.h>


  /*
   * Include internal headers definitions from <freetype/internal/...>
   * only when building the library.
   */
//#ifdef FT2_BUILD_LIBRARY
#if 1
#include <internal.h>
#endif /* FT2_BUILD_LIBRARY */


#endif /* __FT2_BUILD_H__ */


/* END */
