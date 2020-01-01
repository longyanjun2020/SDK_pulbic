/* ***** BEGIN LICENSE BLOCK *****
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
/*    Decoder interface. */
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
/*    Copyright (c) 1995 - 2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */
#ifndef DECODER_H__
#define DECODER_H__


#include "avp_beginhdr.h"

#if !defined(ARM) && !defined(_ARM_)

#if defined(RELIEF_CALLBACK)
#include "avp_rmaengin.h"
#endif

#endif	/*  !defined(ARM) && !defined(_ARM_) */

/* The following undefs are required because windows.h is included */
/* with pmonctrs.h, and RV_Boolean will later be defined to use */
/* TRUE and FALSE in an enum. */
#undef TRUE
#undef FALSE

#include "avp_rvstatus.h"
#include "avp_cdrvdefs.h"
#include "avp_rvmsg.h"
#include "avp_decdefs.h"
#include "avp_rvfid.h"

#if defined(_MSC_VER)
#pragma pack(push, 8)
#endif


#ifdef __cplusplus
extern "C" 
{
#endif
/* */
/* CPU Scalability Threshold definitions. */
/* */
/* These constants define the thresholds for certain functionality based */
/* on the CPU Scalability parameter in */
/*             m_options.CPU_Scalability_Setting. */
/* For thresholds less than 50, the action is performed when the scalability */
/* setting is less than or equal to the threshold value. For thresholds greater */
/* than 50, the actions are performed when the scalability setting is greater */
/* than or equal to the threshold value. */
/* */
#define CPU_Scalability_UseSmoothingPostFilter   70

#define CPU_Scalability_NoBFrameDeblocking       45

#define CPU_Scalability_NoBFrameSubpel           40

#define MAX_NUM_RPR_SIZES  8

#define TR_WRAP  256
#define TR_WRAP_RV  8192
    /* RealVideo bitstreams as of "G2 with SVT" use a 13-bit TR, */
    /* giving millisecond granularity.  RealVideo "G2 Gold", and */
    /* RV89Combo use an 8-bit TR. */

#ifdef INTERLACED_CODE
RV_Status
Decoder_reconstructLumaIntraMacroblocki
    (
    struct RVDecoder *t, 
	const struct DecoderMBInfo *pMB,
    const uint32 mbXOffset,
    const uint32 mbYOffset,
	const DecoderIntraType *pMBIntraTypes,
    const int8 *nz_coeff,
	COEF_TYPE *pQuantBuf,
	uint8 *pPredBuf
    );

RV_Status Decoder_reconstructLumaMacroblocki
				(
				struct RVDecoder *t,
				uint32 mbType,
				/*struct*/ DecoderPackedMotionVector*, /* subblock 0's */
				const uint8 *pRefYPlane,
				const uint32 mbXOffset,
				const uint32 mbYOffset,
				const uint8 *pIsSubBlockEmpty,
				const COEF_TYPE *pQuantBuf,
				uint8 *pPredBuf
				);
#endif

RV_Status ATTR_INST16 Decoder_reconstructInterMacroblock_RV8(
                                    RVC_HANDLE *hp,
                                    struct RVDecoder *t, uint32 mbType,
                                    DecoderPackedMotionVector *pMV,
                                    const uint8 *pRefYPlane, const uint8 *pRefUPlane, const uint8 *pRefVPlane,
                                    const uint32 mbXOffset, const uint32 mbYOffset,
                                    uint8 *dst[3]);

RV_Status ATTR_INST16 Decoder_reconstructInterMacroblock(
                                    RVC_HANDLE *hp,
                                    struct RVDecoder *t, uint32 mbType,
                                    DecoderPackedMotionVector *pMV,
                                    const uint8 *pRefYPlane, const uint8 *pRefUPlane, const uint8 *pRefVPlane,
                                    const uint32 mbXOffset, const uint32 mbYOffset,
                                    uint8 *dst[3]);

RV_Status Decoder_reconstructDirectMacroblock
    (
    RVC_HANDLE              *hp,
    struct RVDecoder        *t,
	const uint32            mbType,
    const uint32            mbTypeRef,
    const DecoderPackedMotionVector *pMV,
    const uint32            mbXOffset,
    const uint32            mbYOffset,
	const int32				iRatio0,
	const int32				iRatio1,
    uint8 *dst[3],
    uint8 *pRefYPlanePrevious, uint8 *pRefUPlanePrevious, uint8 *pRefVPlanePrevious,
    uint32 offset, uint32 offset_cr
    );

	/* Reconstructs one direct mode luma macroblock */
	/* Macroblock type must be MBTYPE_SKIPPED or MBTYPE_DIRECT */

RV_Status Decoder_reconstructDirectMacroblock_RV8
    (
    RVC_HANDLE              *hp,
    struct RVDecoder        *t,
	const uint32            mbType,
    const uint32            mbTypeRef,
      /* We must not be called for intra and skipped macroblocks */
    const DecoderPackedMotionVector *pMV,
    const uint32            mbXOffset,
    const uint32            mbYOffset,
	const int32				iRatio0,
	const int32				iRatio1,
    uint8 *dst[3],
    uint8 *pRefYPlanePrevious, uint8 *pRefUPlanePrevious, uint8 *pRefVPlanePrevious,
    uint32 offset_y, uint32 offset_c
    );

RV_Status Decoder_reconstructBidirMacroblock
(
    RVC_HANDLE              *hp,
    struct RVDecoder        *t,
    const uint32            mbType,
    DecoderPackedMotionVector *pMVp,
    DecoderPackedMotionVector *pMVf,
    const uint32            mbXOffset,
    const uint32            mbYOffset,
    uint8 *dst[3],
    uint8 *pRefYPlanePrevious, uint8 *pRefUPlanePrevious, uint8 *pRefVPlanePrevious,
    uint32 offset, uint32 offset_cr
    );


RV_Status /*ATTR_INST16*/ Decoder_decodeIntraTypes
                    (
                    RVC_HANDLE *hp,
                    struct RVDecoder *t, 
                    const struct DecoderMBInfo*,
					DecoderIntraType *pMBIntraTypes,
					struct CRealVideoBs *pBitstream
#ifdef INTERLACED_CODE
					, int bIsInterlaced
#endif
                    );

RV_Status Decoder_decodeIntraTypes_RV8
                    (
                    RVC_HANDLE *hp,
                    struct RVDecoder *t,
                    const struct DecoderMBInfo*,
					DecoderIntraType *pMBIntraTypes,
					struct CRealVideoBs *pBitstream
                    );
    /* Decode the intra-coding type for each subblock in the given */
    /* macroblock, storing the results in m_pMBIntraTypes. */
    /* pAboveIntraTypes contains the subblock intra-types for */
    /* subblocks 12..15 in the macroblock above.  The right column */
    /* of m_pMBIntraTypes contains the subblock intra-types for */
    /* the macroblock to the left (though this column will get */
    /* updated with the current MB's intra types upon return). */

RV_Status ATTR_INST16 Decoder_decodeMacroBlockType(RVC_HANDLE *hp,
                                        struct RVDecoder *t,
                                        struct DecoderMBInfo *pMBInfo,
                                        uint8 quant_prev,
                                        struct CRealVideoBs *pBitstream,
                                        uint32 *ulSkipModesLeft
                                        );

RV_Status Decoder_decodeMacroBlockType_RV8(
                                        RVC_HANDLE *hp,
                                        struct RVDecoder *t,
                                        struct DecoderMBInfo *pMB,
                                        uint8 quant_prev,
                                        struct CRealVideoBs *pBitstream
                                        );

RV_Status Decoder_decodeMotionVectors
                    (
                    RVC_HANDLE *hp,
                    struct RVDecoder *t,
                    struct DecoderMBInfo*,
                    /*struct*/ DecoderPackedMotionVector*, /* subblock 0's */
					const uint32 mbnum,
					struct CRealVideoBs *pBitstream
                    );

void /*ATTR_INST16*/ Decoder_decodeLumaAndChromaCoefficients_SVLC
                    (
                    RVC_HANDLE *hp,
                    struct RVDecoder *t,
                    BITSBUF *bs,
                    uint32  cbp,
                    uint32  QP,
					uint32	EntropyQP,
					COEF_TYPE *	buf,
                    uint8 *dst[3], uint32 ypitch, uint32 cpitch, 
                    int     intra,
                    int     is16x16
                    );

void Decoder_decodeAndReconstructIntra4x4
                    (
                     struct RVDecoder *t,
                     BITSBUF *bs,
                     uint32  cbp,
                     uint32  QP,
                     uint32  EntropyQP,
                     COEF_TYPE *buf,
                     uint8 *dst[3], uint32 ypitch, uint32 cpitch,
                     const struct DecoderMBInfo *pMB,
                     const DecoderIntraType *pMBIntraTypes
                     );

void Decoder_setMacroBlockEdgeType(struct RVDecoder *t, const uint32, const uint32, const uint32);

void ATTR_INST16 Decoder_setDeblockCoefs(
                    RVC_HANDLE *hp,
                    struct RVDecoder *t,
                    struct DecoderMBInfo  *pMB,
					/*struct*/ DecoderPackedMotionVector *pMV,
					uint32 mbnum
					);
void Decoder_setDeblockCoefs_RV8(
                    RVC_HANDLE *hp,
                    struct RVDecoder *t,
                    struct DecoderMBInfo  *pMB,
					/*struct*/ DecoderPackedMotionVector *pMV,
					uint32 mbnum
					);
           /* Set cbpcoef MB info for one MB */

void Decoder_startNextFrame(RVC_HANDLE *hp, struct RVDecoder *t);
			/* expands planes and resets edge types */
			
RV_Status Decoder_parseBitStream(RVC_HANDLE *hp, struct RVDecoder *t, int32 iSliceNum);
            /* Decode m_BitStream into m_pCurrentFrame */


#ifdef __cplusplus
}
#endif

#if defined(_MSC_VER)
#pragma pack(pop)
#endif



#endif /* DECODER_H__ */
