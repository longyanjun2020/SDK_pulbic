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
/*    Interpolation function interface. */
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
#ifndef SPINTERP_H__
#define SPINTERP_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Subpel interpolation function pointer modified */
#ifdef _AG_S32_
typedef void (RV_FASTCALL T_InterpFnx)(
    const uint8 *RESTRICT src,
    uint8 *RESTRICT dst,
    uint32 stride,
    int32 type
) GNUFASTCALL;
#else
/* Subpel interpolation function pointer */
typedef void (RV_FASTCALL T_InterpFnx)(
    const uint8 *pSrc,
    uint8 *pDst,
    uint32 uSrcPitch,
    int32 iSize
) GNUFASTCALL;
#endif

/* Subpel chroma interpolation function pointer */
typedef void (RV_FASTCALL T_InterpChromaFnx)(
    const uint8 *pSrc,
    uint8 *pDst,
    uint32 uSrcPitch
) GNUFASTCALL;

typedef void (RV_FASTCALL T_InterpChromaFnx_UV)(
    const uint8 *pSrc,
    uint8 *pDst,
    uint32 uSrcPitch,
    const uint8 *pSrc2,
    uint8 *pDst2, 
    int32 type
) GNUFASTCALL;

typedef T_InterpFnx *T_InterpFnxTable[4][4];
typedef T_InterpChromaFnx * T_InterpChromaFnxTable[4][4];
typedef T_InterpChromaFnx_UV * T_InterpChromaFnxTable_UV[4][4];


extern const T_InterpFnxTable gc_C_InterpolateTableRnd;
extern const T_InterpChromaFnxTable_UV gc_C_InterpolateChromaTableRnd;

extern const T_InterpFnxTable gc_C_InterpolateTable4_16;
extern const T_InterpChromaFnxTable_UV gc_C_InterpolateChromaTable4;

extern const T_InterpFnxTable gc_C_InterpolateTable4_16_Cif;
extern const T_InterpChromaFnxTable_UV gc_C_InterpolateChromaTable4_Cif;

extern const T_InterpFnxTable gc_C_InterpolateTable4_16_D1;
extern const T_InterpChromaFnxTable_UV gc_C_InterpolateChromaTable4_D1;

void rv8_mocomp_chroma(const uint8 *src1, uint8 *dst1, uint32 pitch, const uint8 *src2, uint8 *dst2, int32 type);

/* legacy functions */
extern const T_InterpFnxTable gc_C_InterpolateTable;

#ifdef INTERLACED_CODE
/* Interlaced interpolation functions */
extern const T_InterpFnxTable gc_C_InterpolateTable4i2;
extern const T_InterpChromaFnxTable gc_C_InterpolateChromaTable4i2;
#endif

#ifdef BFRAME_USE_BILINEAR_INTERPOLATION
T_InterpFnx C_Interpolate2_H02V00;
T_InterpFnx C_Interpolate2_H00V02;
T_InterpFnx C_Interpolate2_H02V02;

T_InterpChromaFnx C_MCCopyChroma2_H02V00;
T_InterpChromaFnx C_MCCopyChroma2_H00V02;
T_InterpChromaFnx C_MCCopyChroma2_H02V02;
#endif

#ifdef _AG_S32_
T_InterpFnx rv9_CopyBlockQHxVx_X_N;
T_InterpFnx rv9_CopyBlockQH0VQ_X_N;
T_InterpFnx rv9_CopyBlockQH0V0_X_N;
T_InterpFnx rv9_CopyBlockQHQV0_X_N;
T_InterpFnx rv9_CopyBlockQHQVQ_X_N;
T_InterpFnx rv9_CopyBlockQH2V2_X_N;
T_InterpFnx rv9_CopyBlockQH1V1_X_N;
T_InterpFnx rv9_CopyBlockQH2V1_X_N;
T_InterpFnx rv9_CopyBlockQH3V1_X_N;
T_InterpFnx rv9_CopyBlockQH1V2_X_N;
T_InterpFnx rv9_CopyBlockQH3V2_X_N;
T_InterpFnx rv9_CopyBlockQH1V3_X_N;
T_InterpFnx rv9_CopyBlockQH2V3_X_N;
T_InterpFnx rv9_CopyBlockQH3V3_X_N;

#else
T_InterpFnx rv9_CopyBlockQH0V0_16;
T_InterpFnx rv9_CopyBlockQH1V0_16;
T_InterpFnx rv9_CopyBlockQH2V0_16;
T_InterpFnx rv9_CopyBlockQH3V0_16;
T_InterpFnx rv9_CopyBlockQH0V1_16;
T_InterpFnx rv9_CopyBlockQH0V2_16;
T_InterpFnx rv9_CopyBlockQH0V3_16;
T_InterpFnx rv9_CopyBlockQH2V2_16;
T_InterpFnx rv9_CopyBlockQH1V1_16;
T_InterpFnx rv9_CopyBlockQH2V1_16;
T_InterpFnx rv9_CopyBlockQH3V1_16;
T_InterpFnx rv9_CopyBlockQH1V2_16;
T_InterpFnx rv9_CopyBlockQH3V2_16;
T_InterpFnx rv9_CopyBlockQH1V3_16;
T_InterpFnx rv9_CopyBlockQH2V3_16;
T_InterpFnx rv9_CopyBlockQH3V3_16;

T_InterpFnx rv9_CopyBlockQH0V0_8;
T_InterpFnx rv9_CopyBlockQH1V0_8;
T_InterpFnx rv9_CopyBlockQH2V0_8;
T_InterpFnx rv9_CopyBlockQH3V0_8;
T_InterpFnx rv9_CopyBlockQH0V1_8;
T_InterpFnx rv9_CopyBlockQH0V2_8;
T_InterpFnx rv9_CopyBlockQH0V3_8;
T_InterpFnx rv9_CopyBlockQH2V2_8;
T_InterpFnx rv9_CopyBlockQH1V1_8;
T_InterpFnx rv9_CopyBlockQH2V1_8;
T_InterpFnx rv9_CopyBlockQH3V1_8;
T_InterpFnx rv9_CopyBlockQH1V2_8;
T_InterpFnx rv9_CopyBlockQH3V2_8;
T_InterpFnx rv9_CopyBlockQH1V3_8;
T_InterpFnx rv9_CopyBlockQH2V3_8;
T_InterpFnx rv9_CopyBlockQH3V3_8;
#endif

T_InterpChromaFnx_UV rv9_CopyBlockEH0V0_UV;

T_InterpFnx rv8_CopyBlockQH0V0_16;
T_InterpFnx rv8_CopyBlockQH1V0_16;
T_InterpFnx rv8_CopyBlockQH2V0_16;
T_InterpFnx rv8_CopyBlockQH0V1_16;
T_InterpFnx rv8_CopyBlockQH0V2_16;
T_InterpFnx rv8_CopyBlockQH2V2_16;
T_InterpFnx rv8_CopyBlockQH1V1_16;
T_InterpFnx rv8_CopyBlockQH2V1_16;
T_InterpFnx rv8_CopyBlockQH1V2_16;

T_InterpFnx rv8_CopyBlockQH0V0_8;
T_InterpFnx rv8_CopyBlockQH1V0_8;
T_InterpFnx rv8_CopyBlockQH2V0_8;
T_InterpFnx rv8_CopyBlockQH0V1_8;
T_InterpFnx rv8_CopyBlockQH0V2_8;
T_InterpFnx rv8_CopyBlockQH2V2_8;
T_InterpFnx rv8_CopyBlockQH1V1_8;
T_InterpFnx rv8_CopyBlockQH2V1_8;
T_InterpFnx rv8_CopyBlockQH1V2_8;
T_InterpFnx rv8_CopyBlockQHQVQ_8;

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* SPINTERP_H__ */
