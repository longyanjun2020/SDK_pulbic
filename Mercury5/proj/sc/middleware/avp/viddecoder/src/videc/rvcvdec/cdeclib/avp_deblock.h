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
/*    Copyright (c) 2001 RealNetworks, Inc. */
/*    All Rights Reserved. */
/* */
/*    Do not redistribute. */
/* */
/*    Inloop Deblocking Filter interface. */
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
/*    Copyright (c) 1999 - 2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*    DESCRIPTION: */
/*		Header file corresponding to RV89Combo inloop 4x4 deblocking filter  */
/*		class implementation. */
/*////////////////////////////////////////////////////////////////////////// */

#ifndef DCDBLOCK_H__
#define DCDBLOCK_H__

#include "avp_beginhdr.h"

#include "avp_rvtypes.h"
#include "avp_rvstatus.h"
#include "avp_rvstruct.h"

#if defined(DEC_TIMING_DETAIL)
#include "avp_cdrvdefs.h"
#endif

/*#define REFERENCE_FILTER */
#define DITHER
#define QP_LEVELS 32

#ifdef __cplusplus
extern "C" {
#endif


typedef void (RV_CDECL T_EdgeFilter4)(
		uint8 *pPels,		/* first of 4 */
		uint32 uPitch,
		uint32 uMBPos,		/* offset in position from MB zero pixel for this edge (0,4,8,or 12) */
		uint32 uClipR,		/* clip for right/above */
		uint32 uClipL,		/* clip for left/below */
		int32 alpha,
		int32 betaX,
		int32 beta2,
		RV_Boolean bChroma,
		RV_Boolean bStrong		/* true when strong filter enabled */
	);

T_EdgeFilter4 C_EdgeFilter4V;
T_EdgeFilter4 C_EdgeFilter4H;

RV_Status ATTR_INST16 DeblockingFilter_FilterYUVFrameNew(
	uint8       *pPlane[3],
	const uint32 uWidth,
	const uint32 uHeight,
	const uint32 uPitchY,
	const uint32 uPitchC,
    struct DecoderMBInfo *pMB,
	const uint32 uFrameType,
	const uint32 refQP
#ifdef INTERLACED_CODE
    , const uint32 adjustQP
#endif
);

#ifdef __cplusplus
}
#endif

#endif	/* DCDBLOCK_H__ */
