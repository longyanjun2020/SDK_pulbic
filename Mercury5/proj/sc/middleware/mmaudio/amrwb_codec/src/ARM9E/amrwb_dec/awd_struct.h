#ifndef AMR_DECODER_BITEXACT_STRUCT_INCLUDE
#define AMR_DECODER_BITEXACT_STRUCT_INCLUDE

#define NB_WORD32_MAX  (NBBITS_24k/32+1)      //15x32 bits

typedef struct
{
    Word16 prev_ft;
    Word16 prev_mode;
} RX_State;


/*****************************************************************************
 *
 * DEFINITION OF DATA TYPES
 *****************************************************************************/

typedef struct
{
    Word16 since_last_sid;
    Word16 true_sid_period_inv;
    Word16 log_en;
    Word16 old_log_en;
    Word16 level;
    Word16 isf[M];
    Word16 isf_old[M];
    Word16 cng_seed;

    Word16 isf_hist[M * DTX_HIST_SIZE];
    Word16 log_en_hist[DTX_HIST_SIZE];
    Word16 hist_ptr;

    Word16 dtxHangoverCount;
    Word16 decAnaElapsedCount;

    Word16 sid_frame;
    Word16 valid_data;
    Word16 dtxHangoverAdded;

    Word16 dtxGlobalState;                 /* contains previous state */
    /* updated in main decoder */

    Word16 data_updated;                   /* marker to know if CNI data is ever renewed */

    Word16 dither_seed;
    Word16 CN_dith;
    Word16 dtx_vad_hist;
} dtx_decState;

typedef struct
{
    Word16 old_exc[PIT_MAX + L_INTERPOL];  /* old excitation vector */
    Word16 ispold[M];                      /* old isp (immittance spectral pairs) */
    Word16 isfold[M];                      /* old isf (frequency domain) */
    Word16 isf_buf[L_MEANBUF * M];         /* isf buffer(frequency domain) */
    Word16 past_isfq[M];                   /* past isf quantizer */
    Word16 tilt_code;                      /* tilt of code */
    Word16 Q_old;                          /* old scaling factor */
    Word16 Qsubfr[4];                      /* old maximum scaling factor */
    Word32 L_gc_thres;                     /* threshold for noise enhancer */
    Word16 mem_syn_hi[M];                  /* modified synthesis memory (MSB) */
    Word16 mem_syn_lo[M];                  /* modified synthesis memory (LSB) */
    Word16 mem_deemph;                     /* speech deemph filter memory */
    Word16 mem_sig_out[6];                 /* hp50 filter memory for synthesis */
    Word16 mem_oversamp[2 * L_FILT];       /* synthesis oversampled filter memory */
    Word16 mem_syn_hf[M16k];               /* HF synthesis memory */
    Word16 mem_hf[2 * L_FILT16k];          /* HF band-pass filter memory */
    Word16 mem_hf2[2 * L_FILT16k];         /* HF band-pass filter memory */
    Word16 mem_hf3[2 * L_FILT16k];         /* HF band-pass filter memory */
    Word16 seed;                           /* random memory for frame erasure */
    Word16 seed2;                          /* random memory for HF generation */
    Word16 old_T0;                         /* old pitch lag */
    Word16 old_T0_frac;                    /* old pitch fraction lag */
    Word16 lag_hist[5];
    Word16 dec_gain[23];                   /* gain decoder memory */
    Word16 seed3;                          /* random memory for lag concealment */
    Word16 disp_mem[8];                    /* phase dispersion memory */
    Word16 mem_hp400[6];                   /* hp400 filter memory for synthesis */

    Word16 prev_bfi;
    Word16 state;
    Word16 first_frame;

    dtx_decState dtx_decSt;

    Word16 vad_hist;

   unsigned int *ado_cache_ptr;
   unsigned int ado_cache[NB_WORD32_MAX];
   int ado_cache_left;

   Word32 mem_syn32[M]; 
   RX_State rx_state;
} Decoder_State;

typedef struct
{
   Decoder_State st;
   Word16 mode, frame_type, frame_length;
   Word16 reset_flag;
   Word16 reset_flag_old;
   Word16 mode_old;
   Word16 prms[NB_BITS_MAX];
}AMRWB_Dec_state;


extern int awd_frame, subframe;
extern const Word16 awc_isf_init[M];


extern const Word16 table_pow2[33];
extern const Word16 table_isqrt[49];
extern const Word16 table_log2[33];
extern const Word16 fir_7k[L_FIR];
extern const Word16 fir_6k_7k[L_FIR];
extern const Word16 HP_gain[16];
extern const Word16 gamma1[M16k];
extern const Word16 gamma2[M];
extern const Word16 table_cos[129];

extern const Word16 cdown_unusable[7];
extern const Word16 pred[4];
extern const Word16 t_qua_gain7b[128*2];
extern const Word16 t_qua_gain6b[64*2];
extern const Word16 ph_imp_low[L_SUBFR];
extern const Word16 ph_imp_mid[L_SUBFR];



extern const Word16 dico1_isf[SIZE_BK1*9];
extern const Word16 dico2_isf[SIZE_BK2*7];
extern const Word16 dico21_isf[SIZE_BK21*3];
extern const Word16 dico22_isf[SIZE_BK22*3];
extern const Word16 dico23_isf[SIZE_BK23*3];
extern const Word16 dico24_isf[SIZE_BK24*3];
extern const Word16 dico25_isf[SIZE_BK25*4];
extern const Word16 dico21_isf_36b[SIZE_BK21_36b*5];
extern const Word16 dico22_isf_36b[SIZE_BK22_36b*4];
extern const Word16 dico23_isf_36b[SIZE_BK23_36b*7];


extern const Word16 inter4_2[UP_SAMP * 2 * L_INTERPOL2];
extern const Word16 mean_isf[16];




extern const Word16 dico1_isf_noise[SIZE_BK_NOISE1*2];
extern const Word16 dico2_isf_noise[SIZE_BK_NOISE2*3];
extern const Word16 dico3_isf_noise[SIZE_BK_NOISE3*3];
extern const Word16 dico4_isf_noise[SIZE_BK_NOISE4*4];
extern const Word16 dico5_isf_noise[SIZE_BK_NOISE5*4];
extern const Word16 mean_isf_noise[ORDER];



extern const Word16 awb_prmnofsf[NUM_OF_SPMODES];
extern const Word16 dfh_M7k[PRMN_7k];
extern const Word16 dfh_M9k[PRMN_9k];
extern const Word16 dfh_M12k[PRMN_12k];
extern const Word16 dfh_M14k[PRMN_14k];
extern const Word16 dfh_M16k[PRMN_16k];
extern const Word16 dfh_M18k[PRMN_18k];
extern const Word16 dfh_M20k[PRMN_20k];
extern const Word16 dfh_M23k[PRMN_23k];
extern const Word16 dfh_M24k[PRMN_24k];
extern const Word16 *awb_dhf[];

extern const Word16 nb_of_bits[NUM_OF_MODES];
extern const Word16 awb_packed_size[16];
extern const Word16 awb_unpacked_size[16];
extern const Word16 *awb_sort_ptr[16];

//extern const Word16 mean_isf_noise[ORDER];
//extern const Word16 dico1_isf_noise[SIZE_BK_NOISE1*2];
//extern const Word16 dico2_isf_noise[SIZE_BK_NOISE2*3];
//extern const Word16 dico3_isf_noise[SIZE_BK_NOISE3*3];
//extern const Word16 dico4_isf_noise[SIZE_BK_NOISE4*4];
//extern const Word16 dico5_isf_noise[SIZE_BK_NOISE5*4];
extern const Word16 isp_init[M];
extern const Word16 awc_isf_init[M];



extern S64 macr_a0,macr_a1;
#endif
