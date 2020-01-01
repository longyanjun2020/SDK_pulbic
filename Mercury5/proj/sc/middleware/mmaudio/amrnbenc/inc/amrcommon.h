/*
 * ===================================================================
 *  TS 26.104
 *  REL-5 V5.4.0 2004-03
 *  REL-6 V6.1.0 2004-03
 *  3GPP AMR Floating-point Speech Codec
 * ===================================================================
 *
 */

/*
 * interf_rom.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Tables:           Subjective importance
 *                      Homing frames
 *
 *
 */

#ifndef _amr_common_h_
#define _amr_common_h_


extern AMRLIB_VARSTRUCT        amrLibVarStruct;
extern void Int_lpc_1to3_2( Word32 lsp_old[], Word32 lsp_new[], Word32 az[] );
extern Word32 Log2_norm( Word32 x, Word32 exp, Word32 *exponent );

extern Word32 Log2( Word32 x, Word32 *exponent );

extern Word32 Pow2( Word32 exponent, Word32 fraction );

extern void gc_pred( gc_predState *st, enum Mode mode, Word32 *code, Word32 *
      exp_gcode0, Word32 *frac_gcode0, Word32 *exp_en, Word32 *frac_en );

extern void Int_lpc_1to3( Word32 lsp_old[], Word32 lsp_new[], Word32 Az[] );

extern Word32 Inv_sqrt( Word32 x );

extern void Lsf_lsp( Word32 lsf[], Word32 lsp[] );





#endif
