#ifndef __AMR_WB_COMMON_CONSTANT_INCLUDE_FILE__
#define __AMR_WB_COMMON_CONSTANT_INCLUDE_FILE__

#ifdef WIN32
#define INLINE __inline
typedef __int64 Word64;
typedef __int64 int64_t;
typedef __int64 S64;
#else
#define INLINE __inline
typedef long long Word64;
typedef long long int64_t;
typedef long long S64;
#endif


typedef signed char Word8;
typedef short Word16;
typedef int Word32;
typedef unsigned char UWord8;
typedef unsigned short UWord16;
typedef unsigned int UWord32;

#ifdef __MIPS_4KE__
#define ATTR_NOMIPS16 __attribute__((nomips16))
#else
#define ATTR_NOMIPS16
#endif

#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 ((Word16)+32767)	/* 0x7fff */
#define MIN_16 ((Word16)-32768)	/* 0x8000 */


/*-------------------------------------------------------------------*
 *                         WB_VAD_C.H								 *
 *-------------------------------------------------------------------*
 * Constants for Voice Activity Detection.							 *
 *-------------------------------------------------------------------*/
#define FRAME_LEN 256                      /* Length (samples) of the input frame          */
#define COMPLEN 12                         /* Number of sub-bands used by VAD              */

#define UNIRSHFT 7                         /* = log2(MAX_16/UNITY), UNITY = 256      */
#define SCALE 128                          /* (UNITY*UNITY)/512 */

#define TONE_THR (Word16)(0.65*MAX_16)     /* Threshold for tone detection   */

/* constants for speech level estimation */
#define SP_EST_COUNT 80
#define SP_ACTIVITY_COUNT 25
#define ALPHA_SP_UP (Word16)((1.0 - 0.85)*MAX_16)
#define ALPHA_SP_DOWN (Word16)((1.0 - 0.85)*MAX_16)

#define NOM_LEVEL 2050                     /* about -26 dBov Q15 */
#define SPEECH_LEVEL_INIT NOM_LEVEL        /* initial speech level */
#define MIN_SPEECH_LEVEL1  (Word16)(NOM_LEVEL * 0.063)  /* NOM_LEVEL -24 dB */
#define MIN_SPEECH_LEVEL2  (Word16)(NOM_LEVEL * 0.2)    /* NOM_LEVEL -14 dB */
#define MIN_SPEECH_SNR 4096                /* 0 dB, lowest SNR estimation, Q12 */

/* Time constants for background spectrum update */
#define ALPHA_UP1   (Word16)((1.0 - 0.95)*MAX_16)       /* Normal update, upwards:   */
#define ALPHA_DOWN1 (Word16)((1.0 - 0.936)*MAX_16)      /* Normal update, downwards  */
#define ALPHA_UP2   (Word16)((1.0 - 0.985)*MAX_16)      /* Forced update, upwards    */
#define ALPHA_DOWN2 (Word16)((1.0 - 0.943)*MAX_16)      /* Forced update, downwards  */
#define ALPHA3      (Word16)((1.0 - 0.95)*MAX_16)       /* Update downwards          */
#define ALPHA4      (Word16)((1.0 - 0.9)*MAX_16)        /* For stationary estimation */
#define ALPHA5      (Word16)((1.0 - 0.5)*MAX_16)        /* For stationary estimation */

/* Constants for VAD threshold */
#define THR_MIN  (Word16)(1.6*SCALE)       /* Minimum threshold               */
#define THR_HIGH (Word16)(6*SCALE)         /* Highest threshold               */
#define THR_LOW (Word16)(1.7*SCALE)        /* Lowest threshold               */
#define NO_P1 31744                        /* ilog2(1), Noise level for highest threshold */
#define NO_P2 19786                        /* ilog2(0.1*MAX_16), Noise level for lowest threshold */
#define NO_SLOPE (Word16)(MAX_16*(float)(THR_LOW-THR_HIGH)/(float)(NO_P2-NO_P1))

#define SP_CH_MIN (Word16)(-0.75*SCALE)
#define SP_CH_MAX (Word16)(0.75*SCALE)
#define SP_P1 22527                        /* ilog2(NOM_LEVEL/4) */
#define SP_P2 17832                        /* ilog2(NOM_LEVEL*4) */
#define SP_SLOPE (Word16)(MAX_16*(float)(SP_CH_MAX-SP_CH_MIN)/(float)(SP_P2-SP_P1))

/* Constants for hangover length */
#define HANG_HIGH  12                      /* longest hangover               */
#define HANG_LOW  2                        /* shortest hangover               */
#define HANG_P1 THR_LOW                    /* threshold for longest hangover */
#define HANG_P2 (Word16)(4*SCALE)          /* threshold for shortest hangover */
#define HANG_SLOPE (Word16)(MAX_16*(float)(HANG_LOW-HANG_HIGH)/(float)(HANG_P2-HANG_P1))

/* Constants for burst length */
#define BURST_HIGH 8                       /* longest burst length         */
#define BURST_LOW 3                        /* shortest burst length        */
#define BURST_P1 THR_HIGH                  /* threshold for longest burst */
#define BURST_P2 THR_LOW                   /* threshold for shortest burst */
#define BURST_SLOPE (Word16)(MAX_16*(float)(BURST_LOW-BURST_HIGH)/(float)(BURST_P2-BURST_P1))

/* Parameters for background spectrum recovery function */
#define STAT_COUNT 20                      /* threshold of stationary detection counter         */

#define STAT_THR_LEVEL 184                 /* Threshold level for stationarity detection        */
#define STAT_THR 1000                      /* Threshold for stationarity detection              */

/* Limits for background noise estimate */
#define NOISE_MIN 40                       /* minimum */
#define NOISE_MAX 20000                    /* maximum */
#define NOISE_INIT 150                     /* initial */

/* Thresholds for signal power (now calculated on 2 frames) */
#define VAD_POW_LOW (Word32)30000L         /* If input power is lower than this, VAD is set to 0 */
#define POW_TONE_THR (Word32)686080L       /* If input power is lower,tone detection flag is ignored */

/* Constants for the filter bank */
#define COEFF3   13363                     /* coefficient for the 3rd order filter     */
#define COEFF5_1 21955                     /* 1st coefficient the for 5th order filter */
#define COEFF5_2 6390                      /* 2nd coefficient the for 5th order filter */
#define F_5TH_CNT 5                        /* number of 5th order filters */
#define F_3TH_CNT 6                        /* number of 3th order filters */

//-----------------------------------------------------------
//---------------------dtx.h------------------------------
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

#define ORDER   16            /* order of linear prediction filter */
#define ISF_GAP 128

#define SIZE_BK_NOISE1  64
#define SIZE_BK_NOISE2  64
#define SIZE_BK_NOISE3  64
#define SIZE_BK_NOISE4  32
#define SIZE_BK_NOISE5  32
#define ISF_GAP 128           /* 50 Hz */
#define N_SURV  4

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

#define nb_qua_gain6b  64     /* Number of quantization level */
#define nb_qua_gain7b  128    /* Number of quantization level */
#define CODEC_VERSION "6.0.0"
#define L_DOWNSAMP1  256
#define L_DOWNSAMP2  12
#define L_FRAME16k   320                   /* Frame size at 16kHz                        */
#define L_FRAME      256                   /* Frame size                                 */
#define L_SUBFR16k   80                    /* Subframe size at 16kHz                     */
#define L_SUBFR      64                    /* Subframe size                              */
#define NB_SUBFR     4                     /* Number of subframe per frame               */
#define L_NEXT       64                    /* Overhead in LP analysis                    */
#define L_WINDOW     384                   /* window size in LP analysis                 */
#define L_TOTAL      384                   /* Total size of speech buffer.               */
#define M            16                    /* Order of LP filter                         */
#define NC  (M/2)
#define M16k             20
#define L_FILT16k    15                    /* Delay of down-sampling filter              */
#define L_FILT       12                    /* Delay of up-sampling filter                */
#define GP_CLIP      15565                 /* Pitch gain clipping = 0.95 Q14             */
#define PIT_SHARP    27853                 /* pitch sharpening factor = 0.85 Q15         */
#define PIT_MIN      34                    /* Minimum pitch lag with resolution 1/4      */
#define PIT_FR2      128                   /* Minimum pitch lag with resolution 1/2      */
#define PIT_FR1_9b   160                   /* Minimum pitch lag with resolution 1        */
#define PIT_FR1_8b   92                    /* Minimum pitch lag with resolution 1        */
#define PIT_MAX      231                   /* Maximum pitch lag                          */
#define L_INTERPOL   (16+1)                /* Length of filter for interpolation         */
#define OPL_DECIM    2                     /* Decimation in open-loop pitch analysis     */
#define PREEMPH_FAC  22282                 /* preemphasis factor (0.68 in Q15)           */
#define GAMMA1       30147                 /* Weighting factor (numerator) (0.92 in Q15) */
#define TILT_FAC     22282                 /* tilt factor (denominator) (0.68 in Q15)    */
#define Q_MAX        8                     /* scaling max for signal (see syn_filt_32)   */
#define RANDOM_INITSEED  21845             /* own random init value                      */
#define L_MEANBUF        3
#define ONE_PER_MEANBUF 10923

#define MODE_7k       0
#define MODE_9k       1
#define MODE_12k      2
#define MODE_14k      3
#define MODE_16k      4
#define MODE_18k      5
#define MODE_20k      6
#define MODE_23k      7
#define MODE_24k      8
#define MRDTX         9
#define NUM_OF_MODES  10                   /* see bits.h for bits definition             */

#define EHF_MASK (Word16)0x0008            /* homing frame pattern                       */
#define EHF_MASK_INT 0x00080008    
// new definitions
#define MASK_H15 0x7fff0000
#define DIST_ISF_MAX    307                /* 120 Hz (6400Hz=16384) */
#define MU         10923

#define DIST_ISF_MAX    307                /* 120 Hz (6400Hz=16384) */
#define DIST_ISF_THRES  154                /* 60     (6400Hz=16384) */
#define GAIN_PIT_THRES  14746              /* 0.9 in Q14 */
#define GAIN_PIT_MIN    9830               /* 0.6 in Q14 */

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

#define BIT_0     (Word16)-127
#define BIT_1     (Word16)127
#define BIT_0_ITU (Word16)0x007F
#define BIT_1_ITU (Word16)0x0081

#define WB_SIZE_MAX  (3+NB_BITS_MAX)          /* serial size max */
#define TX_FRAME_TYPE (Word16)0x6b21
#define RX_FRAME_TYPE (Word16)0x6b20

#define BS_BUF_SIZE 15
#define NC (M/2)
#define NC16k (M16k/2)

#define ROUNDING
#define DTX_FUNCTION
//#define BIT_EXACT_16

#define L_FIR 31
#define UP_SAMP      4
#define L_INTERPOL2  16

#define DISABLE_LINT_530  /*lint -e{530} */
#define DISABLE_LINT_644  /*lint -e{644} */
#endif

