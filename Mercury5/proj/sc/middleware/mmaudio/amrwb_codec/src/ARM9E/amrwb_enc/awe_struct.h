#ifndef __AMR_WB_ENCODER_STRUCTURE_INCLUDE_FILE__
#define __AMR_WB_ENCODER_STRUCTURE_INCLUDE_FILE__


typedef struct
{
    Word16 sid_update_counter;
    Word16 sid_handover_debt;
    Word16 prev_ft;
} TX_State;


typedef struct
{
    Word16 prev_ft;
    Word16 prev_mode;
} RX_State;

typedef struct
{
    Word16 isf_hist[M * DTX_HIST_SIZE];
    Word16 log_en_hist[DTX_HIST_SIZE];
    Word16 hist_ptr;
    Word16 log_en_index;
    Word16 cng_seed;

    /* DTX handler stuff */
    Word16 dtxHangoverCount;
    Word16 decAnaElapsedCount;
    Word32 D[28];
    Word32 sumD[DTX_HIST_SIZE];
} dtx_encState;

typedef struct
{
    Word16 bckr_est[COMPLEN];              /* background noise estimate                */
    Word16 ave_level[COMPLEN];             /* averaged input components for stationary */
                                           /* estimation                               */
    Word16 old_level[COMPLEN];             /* input levels of the previous frame       */
    Word16 sub_level[COMPLEN];             /* input levels calculated at the end of a frame (lookahead)  */
    Word16 a_data5[F_5TH_CNT][2];          /* memory for the filter bank               */
    Word16 a_data3[F_3TH_CNT];             /* memory for the filter bank               */

    Word16 burst_count;                    /* counts length of a speech burst          */
    Word16 hang_count;                     /* hangover counter                         */
    Word16 stat_count;                     /* stationary counter                       */

    /* Note that each of the following two variables holds 15 flags. Each flag reserves 1 bit of the
     * variable. The newest flag is in the bit 15 (assuming that LSB is bit 1 and MSB is bit 16). */
    Word16 vadreg;                         /* flags for intermediate VAD decisions     */
    Word16 tone_flag;                      /* tone detection flags                     */

    Word16 sp_est_cnt;                     /* counter for speech level estimation      */
    Word16 sp_max;                         /* maximum level                            */
    Word16 sp_max_cnt;                     /* counts frames that contains speech       */
    Word16 speech_level;                   /* estimated speech level                   */
    Word32 prev_pow_sum;                   /* power of previous frame                  */

} VadVars;

typedef struct
{
    //Word16 mem_decim[2 * L_FILT16k];       // speech decimated filter memory
    Word16 mem_decim[4 * L_FILT16k];  

    Word16 mem_sig_in[6];                  // hp50 filter memory
    //Word32 mem_sig_y[2]; 
    //Word16 mem_sig_x[2]; 

    Word16 mem_preemph;                    // speech preemph filter memory
    //Word16 old_speech[L_TOTAL - L_FRAME];  // old speech vector at 12.8kHz
    //Word16 old_wsp[PIT_MAX / OPL_DECIM];   // old decimated weighted speech vector
    //Word16 old_exc[PIT_MAX + L_INTERPOL];  // old excitation vector
    Word16 mem_levinson[M + 2];            // levinson routine memory
    Word16 ispold[M];                      // old isp (immittance spectral pairs)
    Word16 ispold_q[M];                    // quantized old isp
    Word16 past_isfq[M];                   // past isf quantizer
    Word16 mem_wsp;                        // wsp vector memory
    Word16 mem_decim2[9];                  // wsp decimation filter memory
    Word16 mem_w0;                         // target vector memory
    Word16 mem_syn[M];                     // synthesis memory
    Word16 tilt_code;                      // tilt of code
    Word16 old_wsp_max;                    // old wsp maximum value
    Word16 old_wsp_shift;                  // old wsp shift
    Word16 Q_old;                          // old scaling factor
    Word16 Q_max[2];                       // old maximum scaling factor
    Word16 gp_clip[2];                     // gain of pitch clipping memory
    Word16 qua_gain[4];                    // gain quantizer memory

    Word16 old_T0_med;
    //Word16 ol_gain;
    Word16 ada_w;
    Word16 ol_wght_flg;
    Word16 old_ol_lag[5];
    Word16 hp_wsp_mem[9];
    Word16 old_hp_wsp[L_FRAME / OPL_DECIM + (PIT_MAX / OPL_DECIM)];
    VadVars vadSt;
    dtx_encState dtx_encSt;
    Word16 first_frame;

    Word16 isfold[M];                      // old isf (frequency domain)
    Word32 L_gc_thres;                     // threshold for noise enhancer
#ifdef BIT_EXACT_16
    Word16 mem_syn_hi[M];                  // modified synthesis memory (MSB)
    Word16 mem_syn_lo[M];                  // modified synthesis memory (LSB)
#else
    Word32 mem_syn_hilo[M]; 
#endif
    Word16 mem_deemph;                     // speech deemph filter memory
    Word16 mem_sig_out[6];                 // hp50 filter memory for synthesis
    Word16 mem_hp400[6];                   // hp400 filter memory for synthesis
    Word16 mem_oversamp[2 * L_FILT];       // synthesis oversampled filter memory
    Word16 mem_syn_hf[M];                  // HF synthesis memory
    Word16 mem_hf[2 * L_FILT16k];          // HF band-pass filter memory
    Word16 mem_hf2[2 * L_FILT16k];         // HF band-pass filter memory
    Word16 seed2;                          // random memory for HF generation
    Word16 vad_hist;

    Word16 gain_alpha;
    Word32 bs_buf[BS_BUF_SIZE];
    Word32 *ado_cache_ptr;
    Word32 ado_cache_left;
    TX_State tx_state;
} Coder_State;


extern Word32 *A1_f;
extern Word32 *A2;
extern Word16 *err_excf;            // tmp buffer or convolved excitation
extern Word16 *code_corr;               // codebook search vectors or 
extern int frame,subframe;
extern S64 amrwb_macr_a0;

extern const Word16 awe_frac[NB_SUBFR];
extern const Word16 HP_gain[16];
extern const Word16 mean_isf[ORDER];
extern const Word16 nb_of_bits[NUM_OF_MODES];
extern const Word16 table_cos[129];
extern const Word16 dico1_isf_noise[SIZE_BK_NOISE1*2];
extern const Word16 dico2_isf_noise[SIZE_BK_NOISE2*3];
extern const Word16 dico3_isf_noise[SIZE_BK_NOISE3*3];
extern const Word16 dico4_isf_noise[SIZE_BK_NOISE4*4];
extern const Word16 dico5_isf_noise[SIZE_BK_NOISE5*4];
extern const Word16 mean_isf_noise[ORDER];
extern const Word16 dico1_isf[SIZE_BK1*9];
extern const Word16 dico21_isf[SIZE_BK21*3];
extern const Word16 dico22_isf[SIZE_BK22*3];
extern const Word16 dico23_isf[SIZE_BK23*3];
extern const Word16 dico2_isf[SIZE_BK2*7];
extern const Word16 dico24_isf[SIZE_BK24*3];
extern const Word16 dico25_isf[SIZE_BK25*4];
extern const Word16 dico21_isf_36b[SIZE_BK21_36b*5];
extern const Word16 dico22_isf_36b[SIZE_BK22_36b*4];
extern const Word16 dico23_isf_36b[SIZE_BK23_36b*7];
extern const Word16 awb_unpacked_size[16];
extern const Word16 *awb_sort_ptr[16];
extern const Word16 awb_packed_size[16];
extern const Word16 isp_init[M];
extern const Word16 awc_isf_init[M];
extern const Word16 t_qua_gain7b[128*2];
extern const Word16 t_qua_gain6b[64*2];


#endif

