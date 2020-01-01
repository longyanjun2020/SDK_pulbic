#ifndef __AMRNB_ENCODER_STRUCT_INCLUDE_FILE__
#define __AMRNB_ENCODER_STRUCT_INCLUDE_FILE__



/* state variable */
typedef struct {
   
   Word16 bckr_est[COMPLEN];    /* background noise estimate                */
   Word16 ave_level[COMPLEN];   /* averaged input components for stationary */
                                /*    estimation                            */
   Word16 old_level[COMPLEN];   /* input levels of the previous frame       */
   Word16 sub_level[COMPLEN];   /* input levels calculated at the end of
                                      a frame (lookahead)                   */
   Word16 a_data5[3][2];        /* memory for the filter bank               */
   Word16 a_data3[5];           /* memory for the filter bank               */

   Word16 burst_count;          /* counts length of a speech burst          */
   Word16 hang_count;           /* hangover counter                         */
   Word16 stat_count;           /* stationary counter                       */

   /* Note that each of the following three variables (vadreg, pitch and tone)
      holds 15 flags. Each flag reserves 1 bit of the variable. The newest
      flag is in the bit 15 (assuming that LSB is bit 1 and MSB is bit 16). */
   Word16 vadreg;               /* flags for intermediate VAD decisions     */
   Word16 pitch;                /* flags for pitch detection                */
   Word16 tone;                 /* flags for tone detection                 */
   Word16 complex_high;         /* flags for complex detection              */
   Word16 complex_low;          /* flags for complex detection              */

   Word16 oldlag_count, oldlag; /* variables for pitch detection            */
 
   Word16 complex_hang_count;   /* complex hangover counter, used by VAD    */
   Word16 complex_hang_timer;   /* hangover initiator, used by CAD          */
    
   Word16 best_corr_hp;         /* FIP filtered value Q15                   */ 

   Word16 speech_vad_decision;  /* final decision                           */
   Word16 complex_warning;      /* complex background warning               */

   Word16 sp_burst_count;       /* counts length of a speech burst incl
                                   HO addition                              */
   Word16 corr_hp_fast;         /* filtered value                           */ 
} vadState1;




typedef struct
{
   Word16 pre_emp_mem;
   Word16 update_cnt;
   Word16 hyster_cnt;
   Word16 last_update_cnt;
   Word16 ch_enrg_long_db[NUM_CHAN];   /* scaled as 7,8  */

   Word32 Lframe_cnt;
   Word32 Lch_enrg[NUM_CHAN]; /* scaled as 22,9 or 27,4 */
   Word32 Lch_noise[NUM_CHAN];   /* scaled as 22,9 */

   Word16 last_normb_shift;   /* last block norm shift count */

   Word16 tsnr;         /* total signal-to-noise ratio in dB (scaled as 7,8) */
   Word16 hangover;
   Word16 burstcount;
   Word16 fupdate_flag;    /* forced update flag from previous frame */
   Word16 negSNRvar;    /* Negative SNR variance (scaled as 7,8) */
   Word16 negSNRbias;      /* sensitivity bias from negative SNR variance (scaled as 15,0) */

   Word16 shift_state;     /* use 22,9 or 27,4 scaling for ch_enrg[] */

   Word32 L_R0;
   Word32 L_Rmax;
   Flag   LTP_flag;     /* Use to indicate the the LTP gain is > LTP_THRESH */

} vadState2;

#ifndef  AMRNB_VAD2
#define vadState vadState1
#else
#define vadState vadState2
#endif

/*
********************************************************************************
*                         DEFINITION OF DATA TYPES
********************************************************************************
*/
typedef struct {
   Word16 lsp_hist[M * DTX_HIST_SIZE];
   Word16 log_en_hist[DTX_HIST_SIZE];
   Word16 hist_ptr;
   Word16 log_en_index;
   Word16 init_lsf_vq_index;
   Word16 lsp_index[3];

   /* DTX handler stuff */
   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;
   Word16 vadFlagLatch;
} dtx_encState;




#define LTPG_MEM_SIZE 5 /* number of stored past LTP coding gains + 1 */

typedef struct {
    Word16 onset;                   /* onset state,                   Q0  */
    Word16 prev_alpha;              /* previous adaptor output,       Q15 */
    Word16 prev_gc;                 /* previous code gain,            Q1  */

    Word16 ltpg_mem[LTPG_MEM_SIZE]; /* LTP coding gain history,       Q13 */
                                    /* (ltpg_mem[0] not used for history) */
} GainAdaptState;
 


typedef struct {
    Word16 sf0_exp_gcode0;
    Word16 sf0_frac_gcode0;
    Word16 sf0_exp_target_en;
    Word16 sf0_frac_target_en;
    Word16 sf0_exp_coeff[5];
    Word16 sf0_frac_coeff[5];
    Word16 *gain_idx_ptr;
    
    gc_predState     gc_predSt;
    gc_predState     gc_predUnqSt;
    GainAdaptState   adaptSt;
} gainQuantState;

//typedef struct {
//   Word16 T0_prev_subframe;   /* integer pitch lag of previous sub-frame */
//} Pitch_frState;
//typedef struct {
//    Pitch_frState *pitchSt;
//} clLtpState;

typedef struct {
   Word16 old_T0_med;
   Word16 ada_w;
   Word16 wght_flg; 
} pitchOLWghtState;

typedef struct {
  Word16 old_A[M + 1];     /* Last A(z) for case of unstable filter */
} LevinsonState;
 
typedef struct {
   LevinsonState levinsonSt;
} lpcState;

typedef struct {
    Word16 past_rq[M];    /* Past quantized prediction error, Q15 */

} Q_plsfState;
 
typedef struct {

   /* Past LSPs */
   Word16 lsp_old[M];
   Word16 lsp_old_q[M];

   /* Quantization state */
   Q_plsfState qSt;

} lspState;

typedef struct {

   /* counters */
   Word16 count;
   
   /* gain history Q11 */
   Word16 gp[N_FRAME];
   
} tonStabState;

typedef struct {
   /* Speech vector */
   Word16 old_speech[L_TOTAL];
   Word16 *speech, *p_window, *p_window_12k2;
   Word16 *new_speech;             /* Global variable */
   
   /* Weight speech vector */
   Word16 old_wsp[L_FRAME + PIT_MAX];
   Word16 *wsp;

   /* OL LTP states */
   Word16 old_lags[5];
   Word16 ol_gain_flg[2];

   /* Excitation vector */
   Word16 old_exc[L_FRAME + PIT_MAX + L_INTERPOL];
   Word16 *exc;

   /* Zero vector */
   Word16 ai_zero[L_SUBFR + MP1];
   Word16 *zero;

   /* Impulse response vector */
   Word16 *h1;
   Word16 hvec[L_SUBFR * 2];

   /* Substates */
   lpcState   lpcSt;
   lspState   lspSt;
   //clLtpState clLtpSt;
   //Pitch_frState pitchSt;   
   Word16 T0_prev_subframe;

   gainQuantState  gainQuantSt;
   pitchOLWghtState pitchOLWghtSt;
   tonStabState tonStabSt;
   vadState vadSt;
   Flag allow_dtx;
   dtx_encState dtx_encSt;
   EFR_DTX_VAD_ENC_DATA efr_dtx_enc_State;
   /* Filter's memory */
   Word16 mem_syn[M], mem_w0[M], mem_w[M];
   Word16 mem_err[M + L_SUBFR], *error;

   Word16 sharp;
} cod_amrState;


typedef struct {
  Word16 y2_hi;
  Word16 y2_lo;
  Word16 y1_hi;
  Word16 y1_lo;
  Word16 x0;
  Word16 x1;
} Pre_ProcessState;

typedef struct {
    Word16 sid_update_rate;  /* Send SID Update every sid_update_rate frame */
    Word16 sid_update_counter; /* Number of frames since last SID          */
    Word16 sid_handover_debt;  /* Number of extra SID_UPD frames to schedule*/
    Word16 prev_ft;
} sid_syncState;

typedef struct{
    Pre_ProcessState pre_state;
    cod_amrState   cod_amr_state;
    //Flag allow_dtx;
    sid_syncState sid_state;
    Word16 amrenc_used_mode;
} Speech_Encode_FrameState;




extern const Word16 window_160_80[];
extern const Word16 window_232_8[];
extern const Word16 corrweight[251];


extern const Word8 packed_size[16];
extern const Word8 packed_size_IF2[16];

extern const Word16 gamma1_12k2[M];
extern const Word16 T_gamma2[M];
extern const Word16 T_gamma1[M];
extern const Word8 T_trackTable[4*5];
extern const Word8 T_startPos1[2];
extern const Word8 T_startPos2[4];
extern const Word8 T_gray[8];
extern const Word16 T_lag_l[10];
extern const Word16 T_lag_h[10];
extern const Word16 T_inter_36_inter_6[inter_36_FIR_SIZE];
extern const Word16 T_grid[grid_points + 1];

#endif

