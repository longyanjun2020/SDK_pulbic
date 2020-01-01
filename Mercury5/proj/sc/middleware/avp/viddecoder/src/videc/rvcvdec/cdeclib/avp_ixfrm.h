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
/*    Inverse transform interface. */
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
/*    Copyright (c) 1999-2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////////////////////// */
#ifndef IXFRM_H__
#define IXFRM_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_common.h"

/* Inverse 4x4 transform function type declarations */
typedef void (RV_FASTCALL /*ATTR_INST_MODE*/ T_ITransform4x4)(COEF_TYPE*, uint8 *, uint32) GNUFASTCALL;
typedef void (RV_FASTCALL ATTR_INST16 T_ITransform4x4_DC)(COEF_TYPE*, uint8 *, uint32) GNUFASTCALL;

T_ITransform4x4     C_ITransform4x4;
T_ITransform4x4     MMX_ITransform4x4;
T_ITransform4x4     KNI_ITransform4x4;
T_ITransform4x4     AltiVec_ITransform4x4;
void RV_FASTCALL /*ATTR_INST16*/ C_Intra16x16ITransform4x4(COEF_TYPE *in);
T_ITransform4x4_DC     C_ITransform4x4_DCOnly;
T_ITransform4x4     C_ITransform4x4_2x2Only;

#endif /* IXFRM_H__ */
