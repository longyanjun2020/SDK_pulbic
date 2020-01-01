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
/*    Copyright (c) 1999-2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////// */

#ifndef RVCFG_H__
#define RVCFG_H__


/* This file encapsulates most of the preprocessor macros that tailor the */
/* build of the RV89Combo codec via #ifdef's.  In general, to turn a feature */
/* on or off, it is only necessary to change a #define in this file, and */
/* rebuild. */
/* */
/* Notes to developers: */
/* */
/* This file should only contain preprocessor directives (#if, #define, etc). */
/* It should not contain any C or C++ declarations.  In this way, this file */
/* can be safely #include'd in non-C/C++ files, like the resource file. */
/* */
/* The macros defined here should only be related to RV89Combo-specific coding */
/* features, in essence those which affect the bitstream format.  Examples */
/* of classes of names that should *not* be defined here are the HIVE_* */
/* and RV_* macros, and APK, CPK and EXK.  Such macros must be defined */
/* in the makefile, and may be tested in this file via #ifdef's. */


#define REMOVE_INLOOP_ASSUMPTION
/* Even though the bitstream signals the use of inloop deblocking filter */
/* the decoder has always assumed it ON for Key Frames. */
/* This is a BUG,.. this assumption is a bug and is being removed from */
/* RP10 Gold. */

#define QUANTIZER_CHANGE_ALLOWED
/* Old DLLs (rv8,rv9,rv10) did not allow QP changes inside a frame due to incomplete support for dquants. */
/* Interlace / x10 dlls will allow for Quantizer change using dquants and squants */


/* Tweaks for CPU scalability in RV9 */
/*#define BFRAME_ALWAYS_NO_DEBLOCK*/
	/* no deblocking for B frames (not recommended) */
	/* visually very unpleasant */

//#define BFRAME_ALWAYS_FAST_DEBLOCK
	/* always use Fast deblocking for B frames */
	/* recommended only when necessary */

//#define BFRAME_ALWAYS_NO_SUBPEL
//#define BFRAME_ALWAYS_NO_SUBPEL_CHROMA 
	/* no subpel interpolation for B frames */
	/* (not recommended for luma) very ugly artifacts */

//#define BFRAME_ALWAYS_HALF_PEL
//#define BFRAME_ALWAYS_HALF_PEL_CHROMA
	/* always half pel pel interpolation for B frames */

#if defined BFRAME_ALWAYS_HALF_PEL
#define BFRAME_USE_BILINEAR_INTERPOLATION
	/* for B frames where the BFRAME_HALF_PEL is used, 
	   use a simple bi-linear interpolation filter for
       the half pel positions */

#endif

#define BITSTREAM_ERROR_RESILIENT
	/* handle bitstream errors without knowledge of bad slices */

#ifdef BITSTREAM_ERROR_RESILIENT
//#define TEST_BITSTREAM_ERROR_RESILIENT
#endif


#if defined (BFRAME_ALWAYS_NO_DEBLOCK) && defined (BFRAME_ALWAYS_FAST_DEBLOCK)
#error "can not have both NO_DEBLOCK and FAST_DEBLOCK for B frames"
#endif

//#define INTERLACED_CODE

#ifdef INTERLACED_CODE

#define SKIPPED_RV10i
// Skipped MBs in P frames are now assumed to have motion vector the 
// same as the MV predictor.

//#define RV10i_RAW_BITSTREAM
// There was a bug in the old raw bitstream picture header, which
// did not include the 'x10' (interlaced) bit. In order to not
// break the decoding of old bitstreams, this define is left
// commented out by default. In order to decode interlaced
// raw bitstreams, it has to be enabled.
#endif

#if (defined(THREADS_SUPPORTED) || defined (_UNIX_THREADS_SUPPORTED)) 
#define MULTI_THREADED_DECODER 
	/* parse bitstream for each slice separately.  On a multi (n) CPU
	// system (or with FORCE_THREADS), n threads decode n slices in 
	// parallell.*/
	/* This requires one C++ file to be included in the otherwise ANSI
	// C decoder, since the portable Helix multi-threading is all C++
	// based.  This one C++ file then contains the layer between the 
	// C++ code and the ANSI C decoder (rv89thread.cpp) */

/*#define MULTI_THREADED_DECODER_SUPPORT_BETA_BITSTREAMS*/
	/*There was a bug in bitstreams created with a beta version of the RV9
	  encoder, in some cases introducing certain slice dependencies.
	  We wanted to have support for those for the first version of
	  the multi-threaded decoder, because there were quite a few of those
	  bitstreams out there, and this requires additional synchronization.
      If this is not defined, and such a bitstream is decoded with a 
	  dual CPU system, there will be occasional visual artifacts. */

/*#define FORCE_THREADS*/
	/* Enabling FORCE_THREADS will force the decoder to use 
    // multiple threads, even if only one processor is detected. */

#define DECODE_FRAME_LIST_MUTEX
	/* This mutex is needed for multi-threaded decoding to prevent
	// the framelist append and detachHead to clobber each other
	// when called from the two threads */

/*#define DEBUG_THREADING*/
#endif /* defined(THREADS_SUPPORTED) */


	/* even though no smoothing postfilter is currently used, the larger */
	/* framequeue should be able to improve playback jitter  */
#if defined(INTERLACED_CODE)
#define INTERLACED_BOB
/*#define DEBUG_NEWMODE*/ 
#endif

/*#define DEBUG_ADAPTIVE_SMOOTHING */
    /* Debug log for RV8 specific adaptive smoothing */


/*#define ERROR_CONCEALMENT*/
	/* the ability to perform error concealment when packets (slices)
	   are lost */
	   
#define RPR_REQUIRED
	/* Reference Picture Resampling */

#define COMPLIANCE_CLIP
	/* needed for the C decoder to clip values correctly.  Without */
	/* this define, the clamping table is too small for the  */
	/* transform coefficient reference bitstream. */

/*#define DECODE_FRAME_LIST_MUTEX */



#if (defined(ARM) || defined(_ARM_))
#define MAX_DEC_BATCH_MB 100
#else
#define MAX_DEC_BATCH_MB 1
#endif
	/* The main decode loop over macroblocks is broken */
	/* into two loops in the interest of cache localization for the */
	/* VLC tables, significantly improving performance on some systems. */
	/* This define indicates how many macroblocks to process per loop */
	/* iteration. */

/*#define DISABLE_INLOOP */


/*#define ENABLE_COMPILE_WNI */
	/* Enables use of SSE2 (Willamette new instructions) instructions */
	/* in APK. Disabling this allows building APK without having installed */
	/* the Intel compiler for SSE2, and is provided as an interim */
	/* developer convenience. Do not disable if building an APK which may */
	/* be run on a processor with SSE2 support, as incorrect results will */
	/* be obtained. */

/*#define RELIEF_CALLBACK */

//#define SUPPORT_RV8

#endif /* RVCFG_H__ */
