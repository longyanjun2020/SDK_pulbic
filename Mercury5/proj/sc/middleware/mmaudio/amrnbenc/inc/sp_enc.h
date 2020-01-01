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
 * sp_enc.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR encoder
 *
 */
#ifndef _SP_ENC_H
#define _SP_ENC_H

/*
 * include files
 */
#include "rom_enc.h"
#include "romlibTbl.h"
#include "amr_mode.h"

/*
 * Definition of structures used in encoding process
 */
typedef struct
{
  Word32 y2_hi;
  Word32 y2_lo;
  Word32 y1_hi;
  Word32 y1_lo;
  Word32 x0;
  Word32 x1;

}Pre_ProcessState;

#ifdef VAD2

/* Defines for VAD2 */
#define	FRM_LEN1		80
#define	DELAY0			24
#define	FFT_LEN1		128

#define	UPDATE_CNT_THLD1	50

#define	INIT_FRAMES		4

#define	CNE_SM_FAC1		0.1
#define	CEE_SM_FAC1		0.55

#define	HYSTER_CNT_THLD1	6	/* forced update constants... */
#define	HIGH_ALPHA1		0.9
#define	LOW_ALPHA1		0.7
#define	ALPHA_RANGE1		(HIGH_ALPHA1-LOW_ALPHA1)

#define NORM_ENRG		(4.0)	/* account for div by 2 by the HPF */
#define	MIN_CHAN_ENRG		(0.0625 / NORM_ENRG)
#define	INE			(16.0 / NORM_ENRG)
#define	NOISE_FLOOR		(1.0 / NORM_ENRG)

#define	PRE_EMP_FAC1		(-0.8)

#define	NUM_CHAN		16
#define	LO_CHAN			0
#define	HI_CHAN			15
#define	UPDATE_THLD		35

#define	SINE_START_CHAN		2
#define	P2A_THRESH		10.0
#define	DEV_THLD1		28.0

/* Defines for the FFT function */
#define	SIZE			128
#define	SIZE_BY_TWO		64
#define	NUM_STAGE		6

#define	PI			3.141592653589793

#define	TRUE			1
#define	FALSE			0

/* Macros */
#define	min(a,b)		((a)<(b)?(a):(b))
#define	max(a,b)		((a)>(b)?(a):(b))
#define	square(a)		((a)*(a))

/* structures */
typedef struct
{
  Float32 pre_emp_mem;
  Word16  update_cnt;
  Word16  hyster_cnt;
  Word16  last_update_cnt;
  Float32 ch_enrg_long_db[NUM_CHAN];
  Word32  Lframe_cnt;
  Float32 ch_enrg[NUM_CHAN];
  Float32 ch_noise[NUM_CHAN];
  Float32 tsnr;
  Word16  hangover;
  Word16  burstcount;
  Word16  fupdate_flag;
  Float32 negSNRvar;
  Float32 negSNRbias;
  Float32 R0;
  Float32 Rmax;
  Word16  LTP_flag;
}vadState;
#else
typedef struct
{
   Word32 bckr_est[COMPLEN];   /* background noise estimate */
   Word32 ave_level[COMPLEN];


   /* averaged input components for stationary estimation */
   Word32 old_level[COMPLEN];   /* input levels of the previous frame */
   Word32 sub_level[COMPLEN];


   /* input levels calculated at the end of a frame (lookahead) */
   Word32 a_data5[3][2];   /* memory for the filter bank */
   Word32 a_data3[5];   /* memory for the filter bank */
   Word32 best_corr_hp;   /* FIP filtered value */


   /* counts length of a speech burst incl HO addition */
   Word32 corr_hp_fast;   /* filtered value */
   Word32 vadreg;   /* flags for intermediate VAD decisions */
   Word32 pitch;   /* flags for pitch detection */
   Word32 oldlag_count, oldlag;   /* variables for pitch detection */
   Word32 complex_high;   /* flags for complex detection */
   Word32 complex_low;   /* flags for complex detection */
   Word32 complex_warning;   /* complex background warning */
   Word32 tone;   /* flags for tone detection */
   Word16 burst_count;   /* counts length of a speech burst */
   Word16 hang_count;   /* hangover counter */
   Word16 stat_count;   /* stationary counter */
   Word16 complex_hang_count;   /* complex hangover counter, used by VAD */
   Word16 complex_hang_timer;   /* hangover initiator, used by CAD */
   Word16 speech_vad_decision;   /* final decision */
   Word16 sp_burst_count;


}vadState;
#endif
#define DTX_HIST_SIZE 8
#define DTX_ELAPSED_FRAMES_THRESH (24 + 7 -1)
#define DTX_HANG_CONST 7   /* yields eight frames of SP HANGOVER */
typedef struct
{
   Word32 lsp_hist[M * DTX_HIST_SIZE];
   Word32 log_en_hist[DTX_HIST_SIZE];
   Word32 init_lsf_vq_index;
   Word16 hist_ptr;
   Word16 log_en_index;
   Word16 lsp_index[3];


   /* DTX handler stuff */
   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;


}dtx_encState;
typedef struct
{
   /* gain history */
   Word32 gp[N_FRAME];


   /* counters */
   Word16 count;


}tonStabState;

typedef struct
{
   Word32 prev_alpha;   /* previous adaptor output, */
   Word32 prev_gc;   /* previous code gain, */
   Word32 ltpg_mem[LTPG_MEM_SIZE];   /* LTP coding gain history, */
   Word16 onset;   /* onset state, */


   /* (ltpg_mem[0] not used for history) */
}gain_adaptState;
typedef struct
{

   Word32 sf0_target_en;
   Word32 sf0_coeff[5];
   Word32 sf0_gcode0_exp;
   Word32 sf0_gcode0_fra;
   Word16 *gain_idx_ptr;


   gc_predState * gc_predSt;
   gc_predState * gc_predUncSt;
   gain_adaptState * adaptSt;
}gainQuantState;


typedef struct
{
   Word32 T0_prev_subframe;   /* integer pitch lag of previous sub-frame */


}Pitch_frState;
typedef struct
{
   Pitch_frState * pitchSt;
}clLtpState;
typedef struct
{
   Word32 ada_w;
   Word32 old_T0_med;
   Word16 wght_flg;


}pitchOLWghtState;
typedef struct
{
   Word32 past_rq[M];   /* Past quantized prediction error */


}Q_plsfState;
typedef struct
{
#define LSP_OLDNEW0     0
#define LSP_OLDNEW1     1
#define LSP_OLDNEW_Q0   2
#define LSP_OLDNEW_Q1   3
   /* Past LSPs */
   Word32 lsps[4][M];
   Word32 *lsp_old_q, *lsp_new_q;
   Word32 *lsp_old, *lsp_new;

   /* Quantization state */
   Q_plsfState * qSt;
}lspState;
typedef struct
{
   Word32 old_A[M + 1];   /* Last A(z) for case of unstable filter */


}LevinsonState;
typedef struct
{
   LevinsonState * LevinsonSt;
}lpcState;
typedef struct
{
   /* Speech vector */
   Word32 old_speech[L_TOTAL];
   Word32 *speech, *p_window, *p_window_12k2;
   Word32 *new_speech;   /* Global variable */


   /* Weight speech vector */
   Word32 old_wsp[L_FRAME + PIT_MAX];
   Word32 *wsp;


   /* OL LTP states */
   Word32 old_lags[5];
   Word32 ol_gain_flg[2];


   /* Excitation vector */
   Word32 old_exc[L_FRAME + PIT_MAX + L_INTERPOL];
   Word32 *exc;


   /* Zero vector */
   Word32 ai_zero[L_SUBFR + MP1];
   Word32 *zero;


   /* Impulse response vector */
   Word32 *h1;
   Word32 hvec[L_SUBFR * 2];


   /* Substates */
   lpcState * lpcSt;
   lspState * lspSt;
   clLtpState * clLtpSt;
   gainQuantState * gainQuantSt;
   pitchOLWghtState * pitchOLWghtSt;
   tonStabState * tonStabSt;
   vadState * vadSt;

   int dtx;


   dtx_encState * dtxEncSt;

   /* Filter's memory */
   Word32 mem_syn[M], mem_w0[M], mem_w[M];
   Word32 mem_err[M + L_SUBFR], *error;
   Word32 sharp;


}cod_amrState;
typedef struct
{
   cod_amrState * cod_amr_state;
   Pre_ProcessState * pre_state;

   int dtx;

}Speech_Encode_FrameState;


/*
 * Function prototypes
 */

/*
 * initialize one instance of the speech encoder
 * Stores pointer to filter status struct in *st. This pointer has to
 * be passed to Speech_Encode_Frame in each call.
 * returns 0 on success
 */
Speech_Encode_FrameState *Speech_Encode_Frame_init (AMRLIB_VARSTRUCT *libVarStruct, int dtx);
/*
 * reset speech encoder (i.e. set state memory to zero)
 * returns 0 on success
 */
int Speech_Encode_Frame_reset(Speech_Encode_FrameState *state, int dtx);

/*
 * de-initialize speech encoder (i.e. free status struct)
 * stores NULL in *st
 */
//void Speech_Encode_Frame_exit (void **st);

/*
 * Encodes one speech frame
 * Returns analysis parameters
 */
void Speech_Encode_Frame (Speech_Encode_FrameState *state, enum Mode mode, short *newSpeech,
                   short *prm, enum Mode *usedMode);
/*
//void L_Extract (Word32 L_32, Word32 *hi, Word32 *lo);
#define L_Extract_hi(L_32) ((L_32)>>16)
#define L_Extract_lo(L_32, hi) (((L_32)>>1)-((hi)<<15))

//Word32 round16 (Word32 L_var1);
#define round16(L_var1) (((L_var1) + 0x00008000L)>>16)

//Word32 L_Comp (Word16 hi, Word16 lo);
#define L_Comp(hi, lo) (((hi)<<16) + ((lo)<<1))

//Word32 L_negate (Word32 L_var1);
#define L_negate(L_var1) (((L_var1) == MIN_32) ? MAX_32 : (-(L_var1)) )

Word16 div_s (Word16 var1, Word16 var2);

Word16 norm_s (Word16 var1);

Word16 norm_l (Word32 L_var1);

//Word32 mult (Word32 var1, Word32 var2);
#define mult1(var1, var2) (((((Word32)var1)*((Word32)var2)) ) >> 15)
#define mult2(var) ( ((var) >>16) ? ((var) | 0xffff0000L): (var) )

Word32 Mpy_32 (Word32 hi1, Word32 lo1, Word32 hi2, Word32 lo2);

Word32 Div_32 (Word32 L_num, Word32 denom_hi, Word32 denom_lo);*/

//void gc_pred( gc_predState *st, enum Mode mode, Word32 *code, Word32 *
//      exp_gcode0, Word32 *frac_gcode0, Word32 *exp_en, Word32 *frac_en );


#endif
