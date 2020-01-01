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

/*/////////////////////////////////////////////////////////////////////////// */
/*    INTEL Corporation Proprietary Information */
/* */
/*    This listing is supplied under the terms of a license */
/*    agreement with INTEL Corporation and may not be copied */
/*    nor disclosed except in accordance with the terms of */
/*    that agreement. */
/* */
/*    Copyright (c) 1995 - 1999 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */
#ifndef DECDEFS_H__
#define DECDEFS_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"

/* This file defines some data structures and constants used by the decoder, */
/* that are also needed by other classes, such as post filters and */
/* error concealment. */

#define INTERP_FACTOR 4
#define INTERP_FACTOR_RV8 3
#define INTERP_ROUND  1




/* The decoder stores motion vectors for each luma 4x4 subblock in an */
/* entire picture. */
/* A motion vector is defined as 2 signed components in third-pel */
/* units - one for x and one for y. */

typedef int16 DecoderPackedMotionVectorComponent;
    /* An int16 is sufficient to hold any subpel motion vector for */
    /* our supported image dimensions. */
    /* Note that "our" encoder currently only emits motion vectors that */
    /* fit in an int8.  However, we use an int16 to allow decoding bitstreams */
    /* from other sources, such as Telenor. */

#define DecoderPackedMotionVector mvpair

#if 0
struct DecoderPackedMotionVector
{
        DecoderPackedMotionVectorComponent  mvx;
        DecoderPackedMotionVectorComponent  mvy;
};
#endif


/* Provide a way to get at the motion vectors for subblock 0 of a */
/* macroblock, given the macroblock's pel position in the luma plane. */

#define getMBMotionVectors(pMVOrigin, mbXOffset, mbYOffset, MVPitch) \
    ((pMVOrigin) + ((mbXOffset) >> 2) + (MVPitch) * ((mbYOffset) >> 2))


/* The decoder stores intra-coding types (0..4) in uint8's. */

typedef uint8 DecoderIntraType;




/* */
/* Declare some reconstruction functionality used across several files. */
/* */

#ifdef __cplusplus
extern "C"
{
#endif

extern void
MV_Sub2FullPels(const int32 mv, int32 *mv_intg, int32 *mv_frac);
    /* MV_Sub2FullPels extracts the integer and fractional components */
    /* of a motion vector that's in subpel units. */

extern void
MV_Sub2FullPelsChromaYi(const int32 mv, int32 *mv_intg, int32 *mv_frac);
    /* MV_Sub2FullPels extracts the integer and fractional components */
    /* of a motion vector that's in subpel units. */

/* versions for B frames and B frames chroma, since these might want to do
   some shortcuts for CPU scalability */

#if defined(BFRAME_ALWAYS_NO_SUBPEL) || defined(BFRAME_ALWAYS_HALF_PEL)
extern void
MV_Sub2FullPels_B(const int32 mv, int32 *mv_intg, int32 *mv_frac);
#else
#define MV_Sub2FullPels_B MV_Sub2FullPels
#endif

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* DECDEFS_H__ */
