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
/*    Bitstream functionality. */
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
**    Copyright (c) 1995 - 1999 Intel Corporation.
**    All Rights Reserved.
**
** *************************************************************************
*/

#ifndef BSX_H__
#define BSX_H__

#include <stdint.h>
#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_rvstatus.h"
#include "avp_rvstruct.h"
#include "avp_rvfid.h"
#include "avp_bitsbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* LossRecovery return status */
typedef enum
{
	BSLR_STATUS_ERROR,	/* Loss recovery did not detect lost packet, or */
						/* couldn't recover. */
	BSLR_STATUS_OK,		/* Loss recovery detected lost packet and recovered */
	BSLR_STATUS_EOS		/* Loss recovery detected lost packet but end of */
						/* stream encountered (i.e. no more packet avail.) */
} BSLR_Status;


/**/
/* Functions from CBaseBitstream */
/**/


/* Returns the bit position of the buffer pointer relative to the 
   beginning of the buffer. */
#define CB_GetBsOffset(bs) \
    (uint32) (FACTOR_8((bs)->rdptr - (bs)->buf1 - 4) - (bs)->bitcnt)

/* Returns the maximum bitstream size.*/
#define CB_GetMaxBsSize(bs) ((bs)->len1)

/* Obtains current position of the buffer pointer.  This is only
   used to maintain the bitstream state when calling an assembly
   routine that accesses the bitstream.*/
void CB_GetState(
	struct CRealVideoBs *t,
	uint8**		pbs,
	uint32*		bitOffset);

/* Reads one general VLC code from bitstream and returns its length.
   The info portion of the code is returned via the 'info' paramter.*/ 
uint32 CB_GetVLCBits(RVC_HANDLE *hp, uint32 *info); 


#define CB_Get1Bit(bs)       bsGetBits_short_without_escape(bs, 1)
#define CB_GetBits(bs, n)    bsGetBits_short_without_escape(bs, n)

/*
 *  Start of C translated portion 
 */

void CB_Init2(
	struct CRealVideoBs *t,
	const RV_FID	fid);

RV_Boolean		CB_GetForcedKeyState(struct CRealVideoBs *t);

void			CB_PutSliceOffsets(
					struct CRealVideoBs *t,
					const uint32       nOffsets,
					Bitstream_Segment_Info *pOffsets);

void			CB_SetSliceOffset(struct CRealVideoBs *t, int32 iSliceNum);


void			CB_GetDQUANT(
                    RVC_HANDLE *hp,
                    struct CRealVideoBs *t,
                    uint8	*quant,
                    const uint8	quant_prev);

void			CB_SetRPRSizes(struct CRealVideoBs *t, uint8_t, uint16_t *);

RV_Status		CB_GetPictureHeader(RVC_HANDLE *hp, struct CRealVideoBs *t, struct PictureHeader* hdr);
RV_Status		CB_GetPictureHeader_RV8(RVC_HANDLE *hp, struct CRealVideoBs *t, struct PictureHeader* hdr);


RV_Boolean		CB_GetSSC(RVC_HANDLE *hp, struct CRealVideoBs *t, RV_Boolean isRV8);

RV_Boolean		CB_GetSliceHeader(
                    RVC_HANDLE *hp,
                    struct CRealVideoBs *t,
                    RV_Boolean	bFirst,
                    int32       *iMBA,
                    int32       *iSQUANT,
                    struct PictureHeader *hdr);

RV_Boolean		CB_GetSliceHeader_RV8(
                    RVC_HANDLE *hp,
                    struct CRealVideoBs *t,
                    RV_Boolean	bFirst,
                    int32       *iMBA,
                    int32       *iSQUANT,
                    struct PictureHeader *hdr);

BSLR_Status		ATTR_INST16 CB_LossRecovery(RVC_HANDLE *hp, struct CRealVideoBs *t, RV_Boolean bUpdateState);

RV_Boolean		ATTR_INST16 CB_IsSegmentValid(RVC_HANDLE *hp, struct CRealVideoBs *t);

#ifdef __cplusplus
} 
#endif


#endif /* BSX_H__ */
