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
/* *************************************************************************
**    INTEL Corporation Proprietary Information
**
**    This listing is supplied under the terms of a license
**    agreement with INTEL Corporation and may not be copied
**    nor disclosed except in accordance with the terms of
**    that agreement.
**
**    Copyright (c) 1999 Intel Corporation.
**    All Rights Reserved.
**
** *************************************************************************
*/
#ifndef DCSPF_H__
#define DCSPF_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_rvstatus.h"
#include "avp_rvstruct.h"


#ifdef __cplusplus
extern "C" {
#endif

struct SmoothingFilter;

typedef void (RV_FASTCALL T_SmoothingFilter4x4)(
	uint8           *pSrc,
	uint8           *pDst,
	uint8           *pStrength,
	const uint32	uMapPitch,
	const uint32	uSrcPitch,
	const uint32	uDstPitch,
	const uint32	uWidth,
	const uint32	uHeight,
	const uint32	uMBSize) GNUFASTCALL;

T_SmoothingFilter4x4 C_SmoothingFilter4x4;


/* Default constructor */
void SmoothingFilter_Init(struct SmoothingFilter *t, RV_Boolean bHasMMX);

/* Destructor. */
void SmoothingFilter_Delete(struct SmoothingFilter *t);

/* Perform smoothing filtering on a corrupted frame */
RV_Status SmoothingFilter_FilterYUVFrame(
	struct SmoothingFilter *t,
	uint8           *pSrc[3],
	const uint32	uPitchYSrc,
	const uint32	uPitchVSrc,
	uint8           *pYDst,
	uint8           *pVDst,
	uint8           *pUDst,
	const uint32	uPitchYDst,
	const uint32	uPitchVDst,
	const uint32	uWidth,							
	const uint32	uHeight,						
	struct DecoderMBInfo  *pMBData,
	const uint32	fidFormat);

/* Enable/Disable MMX technology enhancement */
void SmoothingFilter_SetMMX(struct SmoothingFilter *t, 
							RV_Boolean impl_id);

/* Enable RV8 postfilter */
void SmoothingFilter_SetRV8(struct SmoothingFilter *t, 
							const RV_Boolean bIsRV8);

/* Set filter strength level */
RV_Status SmoothingFilter_SetStrength(struct SmoothingFilter *t, 
									   const uint32 strength);

/* Check the output buffer */
RV_Status SmoothingFilter_CheckOutput(struct SmoothingFilter *t,
									   const uint32 width,
									   const uint32 height, 
									   const uint32 ypitch,
									   const uint32 upitch,
									   const uint32 vpitch);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* DCSPF_H__ */
