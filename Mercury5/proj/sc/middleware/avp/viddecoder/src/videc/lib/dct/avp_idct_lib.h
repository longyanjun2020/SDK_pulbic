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
#ifndef IDCT_LIB_H
#define IDCT_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

// divx
void __stdcall idct_mmx(int16*);

// REF IDCT
#define DCTELEM int16	/* must be at least 16 bits */
typedef DCTELEM *DCTBLOCK;

void __stdcall ref_dct_init(void);
void __stdcall ref_idct (DCTBLOCK inout);

// JPEG Group Reference IDCT
void __stdcall j_rev_dct (DCTBLOCK inout);

// CW Row-Column IDCT
void __stdcall cwrcidct(int16* in,int16* out);

// Lee IDCT algo implemented by C int16
void __stdcall LeeIDct(int16* in,int16* out);

// AAN IDCT algo implemented by ASM MMX int16
void __stdcall AanIDct(int16* in,int16* out);
void __stdcall AanIDctT(int16* in,int16* out);

// AAN IDCT algo with TLPB implemented by ASM MMX int16
void __stdcall AanIDct_Clear(int16*);
void __stdcall AanIDct_PBTL(int32 QFS,int32 index);
void __stdcall AanIDctCol();
void __stdcall AanTLPBIDCT(int16* in,int16* out);

void __stdcall AanIDctCol_MMXE();
void __stdcall AanIDct_PBTL_MMXE(int32 QFS,int32 index);

// AAN IDCT algo with TLPB implemented by ASM MMX2 floating
extern float PB_AANIDCT_MMX2_Table_Q[64*8];
extern float PB_AANIDCT_MMX2_Table[64][8];
void __stdcall AanIDct_Init_MMX2();
void __stdcall AanIDct_Clear_MMX2();
void __stdcall AanIDct_PBTL_MMX2(int32 QFS,int32 index);
void __stdcall AanIDctCol_MMX2(int16*);
void __stdcall AanTLPBIDCT_MMX2(int16* in,int16* out);

#ifdef _INTEL_IPL_
// IPL IDCT
int __stdcall IPL_IDCT_Init();
void __stdcall IPL_IDCT(int16* in,int16* out);
void __stdcall IPL_IDCT_End();
#endif

void __stdcall idct_chen_mmx1(int16 *x);

// MPEG-2 Reference Software : double precision reference IDCT
void __stdcall idct_mpeg2_init();
void __stdcall idct_mpeg2_ref(int16*);

// MPEG-4 Reference Software : Microsft version
void __stdcall idct_mpeg4_ref(int16*);

// 23002-2 integer 8x8 IDCT
void __stdcall idct_Z0(int16*);
void __stdcall idct_23002_2(int16*);

void __stdcall tm_idct(int16*);
void __stdcall tm_idct_vx(int16*);
void __stdcall tm_idct_org(int16*);

void __stdcall tm_idct_v2(int16 *blk);

// 4x4 IDCT
void __stdcall ref_dct44_init(void);
void __stdcall ref_idct44 (DCTBLOCK inout);

//Sean: add ffdshow idct
void __stdcall ffdshow_idct(int16 *block);

// DivX IDCT
void divx_idct_generic(int16 *block);
void divx_idct_generic_c(int16 *block);


#ifdef __cplusplus
}
#endif

/*interface CIDCT_Handle : public IUnknown
{
    // module init
    STDMETHOD_(int,init)(void*)PURE;

    // genenral algo
    STDMETHOD_(int,GIDct)(int16*,int16*)PURE;

    // transposed
    STDMETHOD_(int,TIDct)(int16*,int16*)PURE;

    // pattern-based algo
    STDMETHOD_(void,PBAanIDct_Clear)()PURE;
    STDMETHOD_(void,PBAanIDctRow_TL)(int32,int)PURE;
	STDMETHOD_(void,PBAanIDctCol)(int16*,int16*)PURE;

    // export method
    STDMETHOD_(void,ExportMethod)()PURE;

};*/

#endif
