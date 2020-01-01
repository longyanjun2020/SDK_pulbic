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
/*    Copyright (c) 1995 - 1998 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/* H.263+ decoder Reference picture resampling (annex P) function prototypes */

#ifndef DRPRSCAL_H__
#define DRPRSCAL_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_rvstruct.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RPR frame descriptions */
typedef struct
{
	T_YUVFrame PlanePtrs;
	uint32 uPitchY;
    uint32 uPitchC;
	uint32 uYWidth;			/* actual picture */
	uint32 uYPaddedWidth;		/* padded to MB boundary */
	uint32 uYHeight;
	uint32 uYPaddedHeight;
} T_RPR_Frame;

/* plane descriptor */
typedef struct
{
	uint8 *pPlane;
	uint32 uPitch;
	uint32 uWidth;
	uint32 uHeight;
} T_Plane;

/* Warning to callers: This function will reference memory outside of the */
/* source and destination planes, in the padding area which is used for the */
/* H.263 video buffers. Attempting to use these functions on unpadded frames */
/* is likely to provide undesired results. */

/* */
/* ResampleYUVFrame */
/* */
/*	Resamples a YUV12 frame using the annex P algorithm. */
/* */
/*	Fills edge pad areas per annex P fill mode. */
/* */
/*	The input and ouput frames are expected to be in the YUV12 planar format */
/*	used by the codec, with padding around all plane edges, and the chroma */
/*	planes in memory side by side following the luma plane with a pitch same */
/*	as the luma plane. */
/* */
/*	The input parameters include original width and height so that resampling */
/*	ratios can be correctly computed and used. The padded width and height */
/*	are used to determine fill requirements for creating a valid reference */
/*	frame. */
/* */
/*	The padding around the input planes may be used by this function. */
/* */
/*	If the usage does not require the output padded areas (to macroblock dimensions) */
/*	to be filled then the padded parameters should be set equal to the actual */
/*	width and height, which will result in a slight CPU performance gain. An */
/*	example of when this would be desirable is when the resulting frame will */
/*	be used for display only and not as a reference frame. */
/* */
/*	Notes: */
/*	1. Rotational warping is not supported. */
/*	2. Displacement accuracy is 1/16 pel only (1/2 pel not supported). */
/* */
extern void ResampleYUVFrame(
	T_RPR_Frame *pSrcFrame,
	T_RPR_Frame *pDstFrame,
	RV_Boolean bRounding);	/* rounding type from PLUSPTYPE of H.263+ picture header */

#ifdef __cplusplus
}
#endif

#endif	/* DRPRSCAL_H__ */
