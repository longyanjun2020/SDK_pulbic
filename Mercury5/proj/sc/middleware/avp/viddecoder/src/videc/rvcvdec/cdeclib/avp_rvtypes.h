/* ***** BEGIN LICENSE BLOCK *****
 * 
 * REALNETWORKS CONFIDENTIAL--NOT FOR DISTRIBUTION IN SOURCE CODE FORM
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc.
 * All Rights Reserved.
 * 
 * The contents of this file, and the files included with this file,
 * are subject to the current version of the Real Format Source Code
 * Porting and Optimization License, available at
 * https://helixcommunity.org/2005/license/realformatsource (unless
 * RealNetworks otherwise expressly agrees in writing that you are
 * subject to a different license).  You may also obtain the license
 * terms directly from RealNetworks.  You may not use this file except
 * in compliance with the Real Format Source Code Porting and
 * Optimization License. There are no redistribution rights for the
 * source code of this file. Please see the Real Format Source Code
 * Porting and Optimization License for the rights, obligations and
 * limitations governing use of the contents of the file.
 * 
 * RealNetworks is the developer of the Original Code and owns the
 * copyrights in the portions it created.
 * 
 * This file, and the files included with this file, is distributed and
 * made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL
 * SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT
 * OR NON-INFRINGEMENT.
 * 
 * Technology Compatibility Kit Test Suite(s) Location:
 * https://rarvcode-tck.helixcommunity.org
 * 
 * Contributor(s):
 * 
 * ***** END LICENSE BLOCK ***** */

/*/////////////////////////////////////////////////////////////////////////// */
/*    RealNetworks, Inc. Confidential and Proprietary Information. */
/* */
/*    Copyright (c) 1995-2002 RealNetworks, Inc. */
/*    All Rights Reserved. */
/* */
/*    Do not redistribute. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */
/*////////////////////////////////////////////////////////// */
/* */
/*    INTEL Corporation Proprietary Information */
/* */
/*    This listing is supplied under the terms of a license */
/*    agreement with INTEL Corporation and may not be copied */
/*    nor disclosed except in accordance with the terms of */
/*    that agreement. */
/* */
/*    Copyright (c) 1997 - 2001 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////// */

#ifndef RVTYPES_H__
#define RVTYPES_H__

/* This file defines the fundamental types used by the HIVE/RV interfaces. */
/* These types are intended to be portable across a wide variety of */
/* compilation environments. */
/* */
/* The following identifiers define scalar data types having a known size */
/* and known range of values, regardless of the host compiler. */
/* */
/*          NOTE:  floating point representations are compiler specific */
/* */
/* The following identifiers define scalar data types whose size is */
/* compiler specific.  They should only be used in contexts where size */
/* is not relevant. */
/* */
/* RV_Boolean       boolean                 0 ..   non-zero */
/* */
/* */
/* The following macros are defined to support compilers that provide */
/* a variety of calling conventions.  They expand to nothing (i.e., empty) */
/* for compilation environments where they are not needed. */
/* */
/*     RV_CDECL */
/*     RV_FASTCALL */
/*     RV_STDCALL */
/*         These are the _WIN32 __cdecl, __fastcall and __stdcall conventions. */
/* */
/*     RV_CALL */
/* */
/*         This is the calling convention for HIVE/RV functions. */
/*         We use an explicit calling convention so that the HIVE/RV */
/*         functionality could be packaged in library, and linked to by */
/*         a codec built with an arbitrary calling convention. */
/* */
/*     RV_FREE_STORE_CALL */
/* */
/*         This represents the host compiler's calling convention for */
/*         the C++ new and delete operators. */

#include "avp_common.h" /* for integer types */

#if (defined(ARM) || defined(_ARM_)) && defined(_WIN32_WCE)

#define RV_CDECL               __cdecl
#define RV_FASTCALL            __fastcall
#define RV_FREE_STORE_CALL
#define RV_STDCALL

#elif (defined(_WIN32) && defined(_M_IX86)) || (defined(_WIN64) && defined(_M_IA64))

#define RV_CDECL               __cdecl
#define RV_FASTCALL            __fastcall
#define RV_STDCALL             __stdcall

    /* The Microsoft compiler uses the __cdecl convention for new */
    /* and delete. */

#define RV_FREE_STORE_CALL     __cdecl

#else /* (defined(_WIN32) && defined(_M_IX86)) || (defined(_WIN64) && defined(_M_IA64)) */

#define RV_CDECL
#define RV_FASTCALL
#define RV_STDCALL
#define RV_FREE_STORE_CALL

#endif /* (defined(_WIN32) && defined(_M_IX86)) || (defined(_WIN64) && defined(_M_IA64)) */


/* GNU variants of STDCALL, CDECL and FASTCALL */
/* GD 1/15/01 not supported by SA linux gnu at this point */
#if defined __GNUC__ && !defined(ARM) && !defined(_ARM_) && !defined(_MIPS_) && !defined(_AEON)

#define GNUSTDCALL __attribute__ ((stdcall))
#define GNUCDECL   __attribute__ ((cdecl))
#define GNUFASTCALL __attribute__ ((regparm (2)))

#else /* defined __GNUC__ */

#define GNUSTDCALL
#define GNUCDECL
#define GNUFASTCALL

#endif /* defined __GNUC__ */


#define RV_CALL                RV_STDCALL


/* RV_Boolean values */
/* */
/* "TRUE" is defined here for assignment purposes only, for example */
/* "is_valid = TRUE;".  As per the definition of C and C++, any */
/* non-zero value is considered to be TRUE.  So "TRUE" should not be used */
/* in tests such as "if (is_valid == TRUE)".  Use "if (is_valid)" instead. */

#undef  FALSE
#undef  TRUE

#if defined(_AIX)
    /* Work around some porting problems with booleans under _AIX */

typedef int         RV_Boolean;
enum                { FALSE, TRUE };

#if !defined(_bool_is_defined)
#define _bool_is_defined

typedef int         bool;
enum                { false, true };

#endif /* !defined(_bool_is_defined) */

#else  /* defined(_AIX) */

/*typedef enum        { FALSE, TRUE } RV_Boolean; */
typedef int         RV_Boolean;
enum                { FALSE, TRUE };

#endif /* defined(_AIX) */


/* NULL is defined here so that you don't always have to */
/* include <stdio.h> or some other standard include file. */

#undef  NULL
#define NULL 0


/* */
/* Define some useful macros */
/* */

#undef  ABS
#define ABS(a)          (((a) < 0) ? (-(a)) : (a))

#define COEF_TYPE int16
//typedef int16 COEF_TYPE;
typedef int16 *PCOEF_TYPE;

#define RV_SMALL_BINARY

#endif /* RVTYPES_H__ */
