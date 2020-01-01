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
/* dec4x4m.h -- functions for 4x4 transform coefficients decoding */
/* 03-21-00 06:38pm, written by Yuriy A. Reznik */
/* 12-15-00 07:42pm, standalone decoder version (for embedded apps) */

#ifndef DEC4X4M_H__
#define DEC4X4M_H__    1

#ifdef __cplusplus
extern "C" {  /* be nice to our friends in C++ */
#endif

#include "avp_rvtypes.h"

#include "avp_dec4x4t.h"

/*
 * Initializes 4x4 decoding engine.
 * Use:
 *  void decode_4x4_init ();
 * Returns:
 *  none.
 */
#ifdef USE_DECOMP_TABLE
void ATTR_INST16 decode_4x4_init(const INTRA_DECODE_TABLES **p_intra_decode_tables, const INTER_DECODE_TABLES **p_inter_decode_tables);
#else
void ATTR_INST16 decode_4x4_init(INTRA_DECODE_TABLES *intra_decode_tables, INTER_DECODE_TABLES *inter_decode_tables);
#endif
/*
 * Decodes a 4x4 block.
 * Use:
 *  void decode_4x4_block (int *block, int intra, int chroma, int qp,
 *      uchar **p_pbs, unsigned int *p_bitOffset);
 * Input:
 *  block - a pointer to 4x4 progressively scanned coefficients
 *  intra - 0, if inter coded block
 *          1, if normal intra block
 *          2, if DC-removed intra block
 *          3, if double-transformed intra DC block
 *  chroma - 1, if chroma block, 0 if luma
 *  qp    - quantization parameter (1..31)
 *  p_pbs - pointer to pointer to the current position in the bitstream
 *  p_bitOffset - pointer to the bit position in the byte pointed by *p_pbs
 * Returns:
 *  none.
 */
int decode_4x4_block(COEF_TYPE *block, int intra,
                     const _4x4_DSC_DECODE_TABLE *p_4x4_dsc,
                     const _2x2_DSC_DECODE_TABLE *p_2x2_dsc,
                     const LEVEL_DSC_DECODE_TABLE *p_level_dsc,
                     BITSBUF *bs, int32 BqT_QP0, int32 BqT_QP);

/*
 * Decodes a cbp descriptor.
 * Use:
 *  unsigned int decode_cbp (int intra, int qp,
 *      unsigned char **p_pbs, unsigned int *p_bitOffset);
 * Input:
 *  intra - 0, if inter coded macroblock
 *          1, if normal intra macroblock
 *          2, if DC-removed intra macroblock
 *  qp    - quantization parameter (1..31)
 *  p_pbs - pointer to pointer to the current position in the bitstream
 *  p_bitOffset - pointer to the bit position in the byte pointed by *p_pbs
 * Returns:
 *  decoded cbp descriptor
 */
unsigned int decode_cbp(const CBP_DECODE_TABLE *ct, int intra, int qp, BITSBUF *bs);

#ifdef __cplusplus
}
#endif

#endif /* DEC4X4M_H__ */
