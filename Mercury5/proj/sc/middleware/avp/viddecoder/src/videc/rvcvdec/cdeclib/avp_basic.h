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
/*    Various simple functions. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/*///////////////////////////////////////////////////////////////////////////// */
/*    INTEL Corporation Proprietary Information */
/* */
/*    This listing is supplied under the terms of a license */
/*    agreement with INTEL Corporation and may not be copied */
/*    nor disclosed except in accordance with the terms of */
/*    that agreement. */
/* */
/*    Copyright (c) 2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////////////////////// */
#ifndef BASIC_H__
#define BASIC_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"


/* 4x4 Block add */
typedef void (RV_FASTCALL T_Add4x4)(
    uint8       *pPred,     /* predictor pels */
    COEF_TYPE   *pErr,      /* error pels */
    const uint32 uPitch,    /* reconstruct pitch */
    uint8       *pRec       /* reconstruct block */
) GNUFASTCALL;

/* 4x4 Block copy */
typedef void (RV_FASTCALL T_Copy4x4)(
    uint8       *pSrc,
    const uint32 uPitch,
    uint8       *pDst
) GNUFASTCALL;

#ifdef __cplusplus
extern "C"
{
#endif

T_Copy4x4 C_Copy4x4;
T_Copy4x4 C_Copy4x4_PredPitch4;
T_Copy4x4 C_Copy4x4_SrcDstPitch;

#ifdef INTERLACED_CODE

T_Add4x4 C_Add4x4i;
T_Add4x4 C_Add4x4i_PredPitch4;

T_Copy4x4 C_Copy4x4i;
T_Copy4x4 C_Copy4x4i_PredPitch4;
#endif


#ifdef __cplusplus
}
#endif

#endif /* BASIC_H__ */
