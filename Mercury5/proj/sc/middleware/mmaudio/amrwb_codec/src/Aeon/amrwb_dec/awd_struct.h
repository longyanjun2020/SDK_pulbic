#ifndef AMR_DECODER_BITEXACT_STRUCT_INCLUDE
#define AMR_DECODER_BITEXACT_STRUCT_INCLUDE





#define ROUNDING

#define L_FIR 31

#define NBBITS_7k     132                  /* 6.60k  */
#define NBBITS_9k     177                  /* 8.85k  */
#define NBBITS_12k    253                  /* 12.65k */
#define NBBITS_14k    285                  /* 14.25k */
#define NBBITS_16k    317                  /* 15.85k */
#define NBBITS_18k    365                  /* 18.25k */
#define NBBITS_20k    397                  /* 19.85k */
#define NBBITS_23k    461                  /* 23.05k */
#define NBBITS_24k    477                  /* 23.85k */

#define NBBITS_SID    35
#define NB_BITS_MAX   NBBITS_24k
#define NB_WORD32_MAX  (NBBITS_24k/32+1)      //15x32 bits

#define BIT_0     (Word16)-127
#define BIT_1     (Word16)127
#define BIT_0_ITU (Word16)0x007F
#define BIT_1_ITU (Word16)0x0081

//#define SIZE_MAX  (3+NB_BITS_MAX)          /* serial size max */
#define TX_FRAME_TYPE (Word16)0x6b21
#define RX_FRAME_TYPE (Word16)0x6b20

typedef struct
{
    Word16 prev_ft;
    Word16 prev_mode;
} RX_State;


#define DTX_MAX_EMPTY_THRESH 50
#define DTX_HIST_SIZE 8
#define DTX_HIST_SIZE_MIN_ONE 7
#define DTX_ELAPSED_FRAMES_THRESH (24 + 7 -1)
#define DTX_HANG_CONST 7                   /* yields eight frames of SP HANGOVER  */
#define INV_MED_THRESH 14564
#define ISF_GAP  128                       /* 50 */
#define ONE_MINUS_ISF_GAP 16384 - ISF_GAP

#define ISF_GAP   128
#define ISF_DITH_GAP   448
#define ISF_FACTOR_LOW 256
#define ISF_FACTOR_STEP 2

#define GAIN_THR 180
#define GAIN_FACTOR 75


#define SPEECH 0
#define DTX 1
#define DTX_MUTE 2

#define TX_SPEECH 0
#define TX_SID_FIRST 1
#define TX_SID_UPDATE 2
#define TX_NO_DATA 3

#define RX_SPEECH_GOOD 0
#define RX_SPEECH_PROBABLY_DEGRADED 1
#define RX_SPEECH_LOST 2
#define RX_SPEECH_BAD 3
#define RX_SID_FIRST 4
#define RX_SID_UPDATE 5
#define RX_SID_BAD 6
#define RX_NO_DATA 7

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
extern const Word16 isf_init[M];


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

#define SIZE_BK1  256
#define SIZE_BK2  256
#define SIZE_BK21 64
#define SIZE_BK22 128
#define SIZE_BK23 128
#define SIZE_BK24 32
#define SIZE_BK25 32

#define SIZE_BK21_36b 128
#define SIZE_BK22_36b 128
#define SIZE_BK23_36b 64

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

#define UP_SAMP      4
#define L_INTERPOL2  16
extern const Word16 inter4_2[UP_SAMP * 2 * L_INTERPOL2];
extern const Word16 mean_isf[16];


#define SIZE_BK_NOISE1  64
#define SIZE_BK_NOISE2  64
#define SIZE_BK_NOISE3  64
#define SIZE_BK_NOISE4  32
#define SIZE_BK_NOISE5  32
#define ORDER   16 
extern const Word16 dico1_isf_noise[SIZE_BK_NOISE1*2];
extern const Word16 dico2_isf_noise[SIZE_BK_NOISE2*3];
extern const Word16 dico3_isf_noise[SIZE_BK_NOISE3*3];
extern const Word16 dico4_isf_noise[SIZE_BK_NOISE4*4];
extern const Word16 dico5_isf_noise[SIZE_BK_NOISE5*4];
extern const Word16 mean_isf_noise[ORDER];

#define DHF_PARMS_MAX 32 /* homing frame pattern             */
#define NUM_OF_SPMODES 9

#define PRML 15
#define PRMN_7k NBBITS_7k/PRML + 1
#define PRMN_9k NBBITS_9k/PRML + 1
#define PRMN_12k NBBITS_12k/PRML + 1
#define PRMN_14k NBBITS_14k/PRML + 1
#define PRMN_16k NBBITS_16k/PRML + 1
#define PRMN_18k NBBITS_18k/PRML + 1
#define PRMN_20k NBBITS_20k/PRML + 1
#define PRMN_23k NBBITS_23k/PRML + 1
#define PRMN_24k NBBITS_24k/PRML + 1

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
extern const Word16 *awd_dhf[];

extern const Word16 nb_of_bits[NUM_OF_MODES];
extern const Word16 awb_packed_size[16];
extern const Word16 awb_unpacked_size[16];
extern const Word16 *awb_sort_ptr[16];

extern const Word16 mean_isf_noise[ORDER];
extern const Word16 dico1_isf_noise[SIZE_BK_NOISE1*2];
extern const Word16 dico2_isf_noise[SIZE_BK_NOISE2*3];
extern const Word16 dico3_isf_noise[SIZE_BK_NOISE3*3];
extern const Word16 dico4_isf_noise[SIZE_BK_NOISE4*4];
extern const Word16 dico5_isf_noise[SIZE_BK_NOISE5*4];
extern const Word16 isp_init[M];
extern const Word16 isf_init[M];



extern S64 macr_a0,macr_a1;
#endif
