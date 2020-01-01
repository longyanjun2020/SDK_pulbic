/*
 * MPEG4 encoder / MPEG4 decoder
 * Copyright (c) 2000,2001 CMLab, NTU. (http://www.cmlab.csie.ntu.edu.tw)
 *
 * This development of this library is supported under the contact 
 * NSC 90-2622-E-002-008, NSC91-2622-E-002-040 and NSC91-2213-E-002-089.
 *
 * This library is distributed in the hope that it will be referable,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 * Any redistribution is prohibited except for the authorization by the authors.
 *
 */
 
/*****************************************************************************\
 * Implementation							             *
 *                                                                           *
 * Author: Yi-Shin Tung (tung@cmlab.csie.ntu.edu.tw)                           *
\\*****************************************************************************/
#ifndef DCT_LIB_H
#define DCT_LIB_H

#include "avp_idct_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif

// divx
void __stdcall fdct_mmx(short*);

// REF IDCT
void __stdcall ref_dct_init(void);
void __stdcall ref_fdct(DCTBLOCK block);

// Lee DCT algo implemented by C int16
void __stdcall LeeDct(int16* InAddr,int16* OutBuf);

void __stdcall jfwddct(int16* data);

extern int16 finalQ[64];
//int16* InAddr,*OutAddr;
extern int16 initQ[64];

// AAN DCT algo implemented by ASM MMX int16
void __stdcall AanDct_init(void);
void __stdcall AanDct(int16*,int16*);
void __stdcall AanDct_C(int16*,int16*);

// AAN DCT algo implemented by ASM MMX2 floating
extern float AANDCT_MMX2_Table_Q[64];
extern float finalQf[64];

void __stdcall AanDct_MMX2_init(void);
void __stdcall AanDct_MMX2(int16*,int16*);

// MPEG-4 Reference Software : Microsft version
void __stdcall dct_mpeg4_ref(int16*);

// 4x4 DCT
void __stdcall ref_dct44_init(void);
void __stdcall ref_fdct44(DCTBLOCK block);

void __stdcall ref_fdct44_mul2 (DCTBLOCK block);

#ifdef __cplusplus
}
#endif


#endif
