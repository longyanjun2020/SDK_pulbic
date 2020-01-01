#ifndef _VLCTAB_H_
#define _VLCTAB_H_

#include "swvenc_deftypes.h"
/* type definitions for variable length code table entries */

typedef struct
{
  uint8 code;  /* right justified */
  int8 len;	   // char??
} VLCtable;

extern VLCtable mcbpcIntraTab[9];
extern VLCtable mcbpcInterTab[25];
extern VLCtable cbpyTab[16];
extern VLCtable coeff_tab0[2][12];
extern VLCtable coeff_tab1[25][4];
extern VLCtable coeff_tab2[2][3];
extern VLCtable coeff_tab3[40];
extern VLCtable MVDTab[64];
// 14496-2
extern VLCtable DCtab_lum[13];
extern VLCtable DCtab_chrom[13];
extern VLCtable coeff_tab4[27];
extern VLCtable coeff_tab5[10];
extern VLCtable coeff_tab6[8][5];
extern VLCtable coeff_tab7[5];
extern VLCtable coeff_tab8[8];
extern VLCtable coeff_tab9[6][3];
extern VLCtable coeff_tab10[14];
extern const uint8 intra_max_level[2][64];
extern const uint8 inter_max_level[2][64];
extern const uint8 intra_max_run0[28];
extern const uint8 intra_max_run1[9];
extern const uint8 inter_max_run0[13];
extern const uint8 inter_max_run1[4];

// ---------------------------------------------------
// quantize table
#define Q_INTRA		0x00
#define Q_NONINTRA	0x01

// quant scaling factor
#define Q_SCALE		12

#define MB_INTRA	0x0001
#define MB_MVF		0x0002
#define MB_MVB		0x0004
#define MB_PATTERN	0x0008
#define MB_QUANT	0x0010
#define MB_ZERO		0x0020
#define MB_PMASK		0x0fc0

#define MB_PMASK0		0x0040
#define MB_PMASK1		0x0080
#define MB_PMASK2		0x0100
#define MB_PMASK3		0x0200
#define MB_PMASK4		0x0400
#define MB_PMASK5		0x0800

// Macroblock type
// For I-Frames
#define INTRA_D		3
#define INTRA_Q		4
// For P-Frames
#define INTER_D		0
#define INTER_Q		1
#define INTER_4V    2
#define INTRA_D     3
#define INTRA_Q     4
#define INTER_4VQ   5
#define SKIPPED		0x0000 
/***********************************/
// For P-Frames
#define PRED_MC		( MB_MVF | MB_PATTERN )
#define PRED_C		( MB_PATTERN)
#define PRED_M		MB_MVF
// For B-Frame
#define PRED_I		(MB_MVF | MB_MVB)
#define PRED_IC		(MB_MVF | MB_MVB | MB_PATTERN)
#define PRED_B		MB_MVB
#define PRED_BC		(MB_MVB | MB_PATTERN)
#define PRED_F		(MB_MVF)
#define PRED_FC		(MB_MVF | MB_PATTERN)
//#define INTRA_D	MB_INTRA | MB_PATTERN
#define PRED_ICQ	(MB_MVF | MB_MVB | MB_PATTERN | MB_QUANT)
#define PRED_FCQ	(MB_MVF | MB_PATTERN | MB_QUANT)
#define PRED_BCQ	(MB_MVB | MB_PATTERN | MB_QUANT)
//#define INTRA_Q		MB_INTRA | MB_QUANT
//#define SKIPPED		0x00

//#define MBLOCK_START	0x00000101

#define VLC_TAB0_MAX_SIZE 12
#define VLC_TAB1_MAX_SIZE 4
#define VLC_TAB2_MAX_SIZE 3


#endif
