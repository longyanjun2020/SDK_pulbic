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
/*    Copyright (c) 1999 - 2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*    DESCRIPTION: */
/*		Header file corresponding to RV89Combo inloop 4x4 deblocking filter  */
/*		class implementation. */
/*////////////////////////////////////////////////////////////////////////// */

#ifndef DCDBLOK8_H__
#define DCDBLOK8_H__


#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_rvstatus.h"
#include "avp_rvstruct.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SUPPORT_RV8

/* Apply deblocking filter to a frame of YUV12 format. */
RV_Status DeblockingFilterRV8_FilterYUVFrame(
    uint8           *pPlane[3],
    const uint32     uWidth,
    const uint32     uHeight,
    const uint32     uPitchY,
    const uint32     uPitchC,
    const struct DecoderMBInfo *pMB,
    const RV_Boolean bIsKeyFrame
);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif	/* DCDBLOK8_H__ */
