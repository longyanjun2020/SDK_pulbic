#ifndef __AMRNB_DECODER_STRUCT_INCLUDE_FILE__
#define __AMRNB_DECODER_STRUCT_INCLUDE_FILE__




#define SPEECH    0
#define DTX       1
#define DTX_MUTE  2

#define DTX_MAX_EMPTY_THRESH 50

/*
*****************************************************************************
*                         DEFINITION OF DATA TYPES
*****************************************************************************
*/

typedef struct {
   Word16 dtxGlobalState;     /* contains previous state */

   Word32 log_en;
   Word32 old_log_en;
   Word32 pn_seed_rx; 
   Word32 lsp[M];
   Word32 lsp_old[M]; 
   Word32 lsf_hist[M*DTX_HIST_SIZE];
   Word32 lsf_hist_mean[M*DTX_HIST_SIZE]; 
   Word32 log_en_hist[DTX_HIST_SIZE];
   Word32 true_sid_period_inv;
   Word16 since_last_sid;
   Word16 lsf_hist_ptr;
   Word16 log_pg_mean;
   Word16 log_en_hist_ptr;
   Word16 log_en_adjust;
   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;
   Word16 sid_frame;       
   Word16 valid_data;          
   Word16 dtxHangoverAdded;
 
   Word16 data_updated;      /* marker to know if CNI data is ever renewed */ 

} dtx_decState;

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#define PHDGAINMEMSIZE 5
#define PHDTHR1LTP     9830  /* 0.6 in Q14 */
#define PHDTHR2LTP     14746 /* 0.9 in Q14 */
#define ONFACTPLUS1    16384 /* 2.0 in Q13   */
#define ONLENGTH 2

typedef struct {
  Word32 gainMem[PHDGAINMEMSIZE];
  Word32 prevState;
  Word32 prevCbGain;
  Word16 lockFull;
  Word16 onset;
} ph_dispState;

typedef struct {
  Word32 pbuf[5];
  Word32 past_gain_pit;
  Word32 prev_gp;
} ec_gain_pitchState;
 
typedef struct {
  Word32 gbuf[5];
  Word32 past_gain_code;
  Word32 prev_gc;
} ec_gain_codeState;


typedef struct {
  Word32 past_r_q[M];   /* Past quantized prediction error, Q15 */
  Word32 past_lsf_q[M]; /* Past dequantized lsfs,           Q15 */
} D_plsfState;


#define EXPCONST          5243               /* 0.16 in Q15 */
typedef struct {
  Word32 lsp_meanSave[M];          /* Averaged LSPs saved for efficiency  */
} lsp_avgState;

#define L_CBGAINHIST 7
typedef struct{
   /* history vector of past synthesis speech energy */
   Word32 cbGainHistory[L_CBGAINHIST];
   
   /* state flags */
   Word32 hangVar;       /* counter; */
   Word16 hangCount;     /* counter; */

} Cb_gain_averageState;


#define L_ENERGYHIST 60
#define INV_L_FRAME 102


/* 2*(160*x)^2 / 65536  where x is FLP values 150,5 and 50 */
#define FRAMEENERGYLIMIT  17578         /* 150 */
#define LOWERNOISELIMIT      20         /*   5 */
#define UPPERNOISELIMIT    1953         /*  50 */
typedef struct{
   /* history vector of past synthesis speech energy */
   Word32 frameEnergyHist[L_ENERGYHIST];
   
   /* state flags */
   Word16 bgHangover;       /* counter; number of frames after last speech frame */

} Bgn_scdState;


typedef struct{
  /* Excitation vector */
  Word32 old_exc[L_SUBFR + PIT_MAX + L_INTERPOL];
  Word32 *exc;
  Word32 lsp_old[M];
 
  /* Filter's memory */
  Word32 mem_syn[M];

  /* pitch sharpening */
  Word32 sharp;
  Word32 old_T0;

  /* Variable holding received ltpLag, used in background noise and BFI */
  Word32 T0_lagBuff;

  /* Variables for the source characteristic detector (SCD) */
  Word32 inBackgroundNoise;
  Word32 voicedHangover;
  Word32 ltpGainHistory[9];

  Word32 excEnergyHist[9];
  Word16 prev_bf;
  Word16 prev_pdf;   
  Word16 state;
  Word16 nodataSeed;

  Bgn_scdState background_state;
  Cb_gain_averageState Cb_gain_averState;
  lsp_avgState lsp_avg_st;
  D_plsfState lsfState;
  ec_gain_pitchState ec_gain_p_st;
  ec_gain_codeState ec_gain_c_st;  
  gc_predState pred_state;
  ph_dispState ph_disp_st;
  dtx_decState dtxDecoderState;
  EFR_DTX_VAD_DEC_DATA efr_dtx_dec_State;
} Decoder_amrState;

typedef struct {
    Word32 past_gain;
} agcState;


typedef struct {
  Word32 mem_pre;          /* filter state */
} preemphasisState;

typedef struct{
  Word32 res2[L_SUBFR];
  Word32 mem_syn_pst[M];
  //preemphasisState preemph_state;
  Word32 preemph_state_mem_pre;
  agcState agc_state;
  Word32 synth_buf[M + L_FRAME];  
} Post_FilterState;


typedef struct {
   Word32 y2_hi;
   Word32 y2_lo;
   Word32 y1_hi;
   Word32 y1_lo;
   Word32 x0;
   Word32 x1;
} Post_ProcessState; 


typedef struct{
  Decoder_amrState decoder_amrState;
  Post_FilterState  post_state;
  Post_ProcessState postHP_state;
  Word16 prev_mode;
  Word16 amrdec_frame_type;
  Word16 amrdec_mode;
  Word16 dec_reset_flag;
  Word16 dec_reset_flag_old;
} Speech_Decode_FrameState;






extern Word16 amrdec_frame_type;




extern const Word16 T_ph_imp_mid[]; 
extern const Word16 T_ph_imp_low[];

extern const Word8 T_dgray[8];

extern const Word16 *const dhf[];
extern const Word16 prmnofsf[];
extern const Word16 ph_imp_low_MR795[]; 
extern const Word16 ph_imp_mid_MR795[];


extern const UWord8 table_speech_bad[9];
extern const UWord8 table_SID[9];
extern const UWord8 table_mute[9];
extern const UWord8 table_DTX[9];
extern const Word16 dtx_log_en_adjust[9];
extern const Word16 lsf_hist_mean_scale[M];


#endif
