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
/* */
/*    FRU Glue code interface. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/* This module implements doFRU() */


#include "avp_rvcfg.h"
/*#include "avp_decoder.h" */
/*#include "avp_rn_frumv.h" */

#ifndef DECFRU_H
#define DECFRU_H

#ifdef INCLUDE_FRU

struct FrameRateUpsampler
{

	void*                       m_pFruState;
		/* Pointer to the state structure used by the FRU library */
	uint32                      m_uFruWidth;
	uint32                      m_uFruHeight;
	uint32                      m_uFruLumaPitch;
	uint32                      m_uFruChromaPitch;

	double						m_dFruTime;
		/* How long does smoothing take? */

	uint32                      m_uFruMode;
		/* This parameter is the aggressiveness of FRU -- */
		/* i.e. higher "mode" will give more FRU frames but with */
		/* a higher probability of annoying FRU artifacts. */

	uint32                      m_uDeltaTime;
	uint32                      m_uPrevFrameTime;
	uint32                      m_uFramesToGenerate;
	uint32                      m_uCurrentFrameToGenerate;
};

void		                FrameRateUpsampler_Init(struct FrameRateUpsampler *t);

uint32                      FrameRateUpsampler_SetUpFRU
		                        (
								struct FrameRateUpsampler *t,
								struct DecodedFrame *pPrevFrame,
								struct DecodedFrame *pFutrFrame,
								struct DecodedFrame *pPrevRefFrame,
								struct DecodedFrame *pFutrRefFrame,
								struct DecoderMBInfo *pBMBInfo,
								struct DecoderMBInfo *pRefMBInfo,
								struct DecoderPackedMotionVector *pBMV,
								struct DecoderPackedMotionVector *pRefMV
								);

RV_Status                  FrameRateUpsampler_FillAFRUFrame
		                        (
								struct FrameRateUpsampler *t,
								struct DecodedFrame *pFRUFrame
								);

RV_Boolean                 FrameRateUpsampler_IsThereMoreFRUFrames(struct FrameRateUpsampler *t);

#endif
#endif
