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
/*    Various tables. */
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
/*    Copyright (c) 1995 - 1999 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/* This file contains all table definitions used for the new algo. */
/* Implementation in ttables.cpp */


#ifndef TTABLES_H__
#define TTABLES_H__

#include "avp_beginhdr.h"
#include "avp_rvtypes.h"
#include "avp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*//////////////////////////////////////////////////////// */
/* Mapping from luma QP to chroma QP */
extern const uint8 chroma_quant[32];
//extern const uint8 chroma_quant_DC[32];

/* Mapping for QP applied to luma DC coefs */
//extern const uint8 luma_intra_quant_DC[32];
extern const uint8 luma_quant_DC_RV8[32];
//extern const uint8 luma_inter_quant_DC[32];
extern const uint8 luma_quant_DC[64];

/* Legacy Intra prediction probabilities */
extern const uint8 dec_iprob_rv8[162];
extern const uint8 dec_aic_prob_rv8[10/*A*/][10/*B*/][9/*prob*/];

#define CBP4x4Mask(k)   (1<<(k))

/* Mapping from 8x8 block number to 4x4 block number */
extern const uint8 block_subblock_mapping[16];
/* Mapping from chroma block number to luma block number where the vector */
/* to be used for chroma can be found */
#ifdef SUPPORT_RV8
extern const uint8 chroma_block_address[4];
#endif
#ifdef INTERLACED_CODE
extern const uint8 chroma_block_address_i[4];
#endif

/*////////////////////////////////////////////////////////////////// */
/* Quantization tables */
extern const uint16 BquantTable[32];

/* Tables used for finding if a block is on the edge */
/* of a macroblock */
//extern const uint8 left_edge_tab4[4];
#define LEFT_EDGE_TAB4(x) (((x)&1)==0)
//extern const uint8 top_edge_tab4[4];
#define TOP_EDGE_TAB4(x) ((x)<2)
//extern const uint8 left_edge_tab16[16];
#define LEFT_EDGE_TAB16(x) (((x)&3)==0)
//extern const uint8 top_edge_tab16[16];
#define TOP_EDGE_TAB16(x) ((x)<4)

#if 1//def __TCS__ //always use UCLIPI for our Win32 version
#define ClampVal(x)          UCLIPI_255(x)
#define ClampTblLookup(x, y) UCLIPI_255((x)+(y))
#else

#ifdef COMPLIANCE_CLIP
#define CLAMP_BIAS  (128+128+32) /* Bias in clamping table */
#else
#define CLAMP_BIAS  128 /* Bias in clamping table */
#endif
#define CLIP_RANGE  (CLAMP_BIAS + 256 + CLAMP_BIAS)

extern const uint8  ClampTbl[CLIP_RANGE];

#define ClampVal(x)          (ClampTbl[CLAMP_BIAS + (x)])
#define ClampTblLookup(x, y) ClampVal((x) + (y))
#endif

#ifdef INTERLACED_CODE
//extern const uint8 top_edge_tab16i[16];
#define TOP_EDGE_TAB16I(x) (((x)&4) == 0)
extern const uint32 uIBlockEdgeAdj[16];
extern const uint32 uModeAboveFactI[16];
extern const int32 iModeLeftFactI[16];
#endif

extern const unsigned char  aic_top_vlc[16]; /* Flawfinder: ignore */
extern const unsigned short aic_table_index[20];
extern const unsigned short aic_2mode_vlc[20][81];
extern const unsigned char  aic_1mode_vlc[90/*100*/][9]; /* Flawfinder: ignore */

#if defined(_WIN32) && defined(_M_IX86)

#define GET_VLC_LENGTH_INFO_SHORT(info,length)\
	_asm mov eax, (info)					\
	_asm bsr edx, eax						\
	_asm btr eax, edx						\
	_asm mov (info), eax					\
	_asm mov (length), edx  \
    ; assert(info<=0x1f);

#define GET_VLC_LENGTH_INFO_CHAR(info,length)\
	_asm mov eax, (info)					\
	_asm bsr edx, eax						\
	_asm btr eax, edx						\
	_asm mov (info), eax					\
	_asm mov (length), edx \
; \
assert(info<=0x1f); 

#else
#define GET_VLC_LENGTH_INFO_SHORT(info,length)      \
    assert(info);                                   \
    (length) = 31 - CLSAME(info, 0);                \
    info -= 1 << (length);

#define GET_VLC_LENGTH_INFO_CHAR(info,length)       \
    assert(info);                                   \
    (length) = 31 - CLSAME(info, 0);                \
    info -= 1 << (length);

#endif /* defined(_WIN32) && defined(_M_IX86) */


extern const unsigned char mbtype_pb_enc_tab[12+12];
extern const uint16 mbtype_pframe_vlc [7][8]; /* Flawfinder: ignore */
extern const uint16 mbtype_bframe_vlc [6][7]; /* Flawfinder: ignore */

#ifdef INTERLACED_CODE
//extern const unsigned char mbtype_pi_dec_tab[10]; /* Flawfinder: ignore */
//extern const unsigned char mbtype_bi_dec_tab[10]; /* Flawfinder: ignore */
//extern const unsigned char  mbtype_pi_enc_tab[15];
//extern const unsigned char  mbtype_bi_enc_tab[19]; /* Flawfinder: ignore */
extern const unsigned char mbtype_pbi_dec_tab[10+10];
extern const unsigned char mbtype_pi_enc_tab[15+19];
extern const unsigned char  mbtype_pframei_vlc [10][11][2]; /* Flawfinder: ignore */
extern const unsigned char  mbtype_bframei_vlc [10][11][2]; /* Flawfinder: ignore */
/* mapping of DeblockingQPAdjust */
extern const uint8 DBQPA[6];
#endif


#ifdef __cplusplus
}
#endif



#endif /* TTABLES_H__ */
