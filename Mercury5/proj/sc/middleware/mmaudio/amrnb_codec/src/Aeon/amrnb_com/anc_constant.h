#ifndef __AMRNB_COMMON_CONSTANT_INCLUDE_FILE__
#define __AMRNB_COMMON_CONSTANT_INCLUDE_FILE__



/* start of USER profile define*/
#define VAD1            /* using VAD1 */


#define DOWN_TO_13BIT

#ifndef NULL
#define NULL 0
#endif


#define OPT_DTX 1
#define OPT_475 1    //bit-exact ok
#define OPT_515 1    //bit-exact ok
#define OPT_59  1    //bit-exact ok
#define OPT_67  1    //bit-exact ok
#define OPT_74  1    //bit-exact ok
#define OPT_795 1    //bit-exact ok
#define OPT_102 1   //bit-exact ok
#define OPT_122 1    //bit-exact ok

#define INLINE __inline 

/* end of USER profile define*/
#ifdef __aeon__
typedef long long S64;
#else
typedef __int64 S64;
#endif

typedef unsigned char UWord8;
typedef signed char Word8;
typedef short Word16;
typedef int Word32;
typedef int Flag;


/* Macro define */

//#define MABS(x) (((x) ^ (((int)x) >> 31)) - (((int)x) >> 31))


#define L_TOTAL      320       /* Total size of speech buffer.             */
#define L_WINDOW     240       /* Window size in LP analysis               */
#define L_FRAME      160       /* Frame size                               */
#define L_FRAME_BY2  80        /* Frame size divided by 2                  */
#define L_SUBFR      40        /* Subframe size                            */
#define L_CODE       40        /* codevector length                        */
#define NB_TRACK     5         /* number of tracks                         */
#define STEP         5         /* codebook step size                       */
#define NB_TRACK_MR102  4      /* number of tracks mode mr102              */
#define STEP_MR102      4      /* codebook step size mode mr102            */
#define M            10        /* Order of LP filter                       */
#define MP1          (M+1)     /* Order of LP filter + 1                   */
#define LSF_GAP      205       /* Minimum distance between LSF after quan-
                                  tization; 50 Hz = 205                    */
#define LSP_PRED_FAC_MR122 21299 /* MR122 LSP prediction factor (0.65 Q15) */
#define AZ_SIZE       (4*M+4)  /* Size of array of LP filters in 4 subfr.s */
#define PIT_MIN_MR122 18       /* Minimum pitch lag (MR122 mode)           */
#define PIT_MIN       20       /* Minimum pitch lag (all other modes)      */
#define PIT_MAX       143      /* Maximum pitch lag                        */
#define L_INTERPOL    (10+1)   /* Length of filter for interpolation       */
#define L_INTER_SRCH  4        /* Length of filter for CL LTP search
                                  interpolation                            */
        
#define MU       26214         /* Factor for tilt compensation filter 0.8  */
#define AGC_FAC  29491         /* Factor for automatic gain control 0.9    */
        
#define L_NEXT       40        /* Overhead in LP analysis                  */
#define SHARPMAX  13017        /* Maximum value of pitch sharpening        */
#define SHARPMIN  0            /* Minimum value of pitch sharpening        */
                                                                          
                                                                          
#define MAX_PRM_SIZE    57     /* max. num. of params                      */
#define MAX_SERIAL_SIZE 244    /* max. num. of serial bits                 */

#define GP_CLIP   15565        /* Pitch gain clipping = 0.95               */
#define N_FRAME   7            /* old pitch gains in average calculation   */

#define EHF_MASK 0x0008        /* encoder homing frame pattern             */
#define EHF_MASK_INT 0x00080008   

#define MR475  0
#define MR515  1         
#define MR59   2
#define MR67   3
#define MR74   4
#define MR795  5
#define MR102  6
#define MR122  7        
#define MRDTX  8
#define N_MODES   9

#define BIT_0      0
#define BIT_1      1

#define PRMNO_MR475 17
#define PRMNO_MR515 19
#define PRMNO_MR59  19
#define PRMNO_MR67  19
#define PRMNO_MR74  19
#define PRMNO_MR795 23
#define PRMNO_MR102 39
#define PRMNO_MR122 57
#define PRMNO_MRDTX 5

/* number of parameters to first subframe */
#define PRMNOFSF_MR475 7
#define PRMNOFSF_MR515 7
#define PRMNOFSF_MR59  7
#define PRMNOFSF_MR67  7
#define PRMNOFSF_MR74  7
#define PRMNOFSF_MR795 8
#define PRMNOFSF_MR102 12
#define PRMNOFSF_MR122 18


#define NB_QUA_PITCH 16
#define NB_QUA_CODE 32
#define PAST_RQ_INIT_SIZE 8

#define MR515_3_SIZE  128
#define MR795_1_SIZE  512


#define MR475_VQ_SIZE 256

#define VQ_SIZE_HIGHRATES 128
/* table used in 'low' rates: MR475, MR515, MR59 */
#define VQ_SIZE_LOWRATES 64


#define RX_SPEECH_GOOD     0
#define RX_SPEECH_DEGRADED 1
#define RX_ONSET           2
#define RX_SPEECH_BAD      3
#define RX_SID_FIRST       4
#define RX_SID_UPDATE      5
#define RX_SID_BAD         6
#define RX_NO_DATA         7
#define RX_N_FRAMETYPES    8

#define TX_SPEECH_GOOD     0
#define TX_SID_FIRST       1
#define TX_SID_UPDATE      2
#define TX_NO_DATA         3
#define TX_SPEECH_DEGRADED 4
#define TX_SPEECH_BAD      5
#define TX_SID_BAD         6
#define TX_ONSET           7
#define TX_N_FRAMETYPES    8



/* For uplink the status word contains return values: */
#define  AU_RESET            0x0001
#define  AU_DTX              0x0002
#define  AU_ECHO_ENABLE      0x0004
#define  AU_TAF              0x0008
#define  AU_BFI              0x0010
#define  AU_UFI              0x0020
#define  AU_PDFI             0x0020

#define  AU_SP               0x0100
#define  AU_VAD              0x0200
#define  AU_FLAGS_VALID      0x0400
#define  AU_FLAGS_VALID_BIT  10
#define  AU_SID              0x1800
#define  AU_SID_SHIFT        11

#define EFR_SERIAL_SIZE 260

// add for GAS 
/* EncSpeechBuffer frameType enumerations used by the AMR speech codec. */
#define AU_AMR_FRAME_TYPE_SPEECH_GOOD                  0
#define AU_AMR_FRAME_TYPE_SPEECH_DEGRADED              1
#define AU_AMR_FRAME_TYPE_ONSET                        2
#define AU_AMR_FRAME_TYPE_SPEECH_BAD                   3
#define AU_AMR_FRAME_TYPE_SID_FIRST                    4
#define AU_AMR_FRAME_TYPE_SID_UPDATE                   5
#define AU_AMR_FRAME_TYPE_SID_BAD                      6
#define AU_AMR_FRAME_TYPE_NO_DATA                      7


#define SERIAL_FRAMESIZE (1+MAX_SERIAL_SIZE+5)

#define MAX_PACKED_SIZE (MAX_SERIAL_SIZE / 8 + 2)



#define FRAME_LEN 160    /* Length (samples) of the input frame          */
#define COMPLEN 9        /* Number of sub-bands used by VAD              */
#define INV_COMPLEN 3641 /* 1.0/COMPLEN*2^15                             */
#define LOOKAHEAD 40     /* length of the lookahead used by speech coder */

#define UNITY 512        /* Scaling used with SNR calculation            */
#define UNIRSHFT 6       /* = log2(MAX_16/UNITY)                         */

#define TONE_THR (Word16)(0.65*MAX_16) /* Threshold for tone detection   */

/* Constants for background spectrum update */
#define ALPHA_UP1   (Word16)((1.0 - 0.95)*MAX_16)  /* Normal update, upwards:   */
#define ALPHA_DOWN1 (Word16)((1.0 - 0.936)*MAX_16) /* Normal update, downwards  */
#define ALPHA_UP2   (Word16)((1.0 - 0.985)*MAX_16) /* Forced update, upwards    */
#define ALPHA_DOWN2 (Word16)((1.0 - 0.943)*MAX_16) /* Forced update, downwards  */
#define ALPHA3      (Word16)((1.0 - 0.95)*MAX_16)  /* Update downwards          */
#define ALPHA4      (Word16)((1.0 - 0.9)*MAX_16)   /* For stationary estimation */
#define ALPHA5      (Word16)((1.0 - 0.5)*MAX_16)   /* For stationary estimation */

/* Constants for VAD threshold */
#define VAD_THR_HIGH 1260 /* Highest threshold                 */
#define VAD_THR_LOW  720  /* Lowest threshold                  */
#define VAD_P1 0          /* Noise level for highest threshold */
#define VAD_P2 6300       /* Noise level for lowest threshold  */
#define VAD_SLOPE (Word16)(MAX_16*(float)(VAD_THR_LOW-VAD_THR_HIGH)/(float)(VAD_P2-VAD_P1))

/* Parameters for background spectrum recovery function */
#define STAT_COUNT 20         /* threshold of stationary detection counter         */
#define STAT_COUNT_BY_2 10    /* threshold of stationary detection counter         */
#define CAD_MIN_STAT_COUNT 5  /* threshold of stationary detection counter         */

#define STAT_THR_LEVEL 184    /* Threshold level for stationarity detection        */
#define STAT_THR 1000         /* Threshold for stationarity detection              */

/* Limits for background noise estimate */
#define NOISE_MIN 40          /* minimum */
#define NOISE_MAX 16000       /* maximum */
#define NOISE_INIT 150        /* initial */

/* Constants for VAD hangover addition */
#define HANG_NOISE_THR 100
#define BURST_LEN_HIGH_NOISE 4
#define HANG_LEN_HIGH_NOISE 7
#define BURST_LEN_LOW_NOISE 5
#define HANG_LEN_LOW_NOISE 4

/* Thresholds for signal power */
#define VAD_POW_LOW (Word32)15000     /* If input power is lower,                    */
                                      /*     VAD is set to 0                         */
#define POW_PITCH_THR (Word32)343040  /* If input power is lower, pitch              */
                                      /*     detection is ignored                    */

#define POW_COMPLEX_THR (Word32)15000 /* If input power is lower, complex            */
                                      /* flags  value for previous frame  is un-set  */
 

/* Constants for the filter bank */
#define LEVEL_SHIFT 0      /* scaling                                  */
#define COEFF3   13363     /* coefficient for the 3rd order filter     */
#define COEFF5_1 21955     /* 1st coefficient the for 5th order filter */
#define COEFF5_2 6390      /* 2nd coefficient the for 5th order filter */

/* Constants for pitch detection */
#define LTHRESH 4
#define NTHRESH 4

/* Constants for complex signal VAD  */
#define CVAD_THRESH_ADAPT_HIGH  (Word16)(0.6 * MAX_16) /* threshold for adapt stopping high    */
#define CVAD_THRESH_ADAPT_LOW  (Word16)(0.5 * MAX_16)  /* threshold for adapt stopping low     */
#define CVAD_THRESH_IN_NOISE  (Word16)(0.65 * MAX_16)  /* threshold going into speech on
                                                          a short term basis                   */

#define CVAD_THRESH_HANG  (Word16)(0.70 * MAX_16)      /* threshold                            */
#define CVAD_HANG_LIMIT  (Word16)(100)                 /* 2 second estimation time             */
#define CVAD_HANG_LENGTH  (Word16)(250)                /* 5 second hangover                    */

#define CVAD_LOWPOW_RESET (Word16) (0.40 * MAX_16)     /* init in low power segment            */
#define CVAD_MIN_CORR (Word16) (0.40 * MAX_16)         /* lowest adaptation value              */

#define CVAD_BURST 20                                  /* speech burst length for speech reset */
#define CVAD_ADAPT_SLOW (Word16)(( 1.0 - 0.98) * MAX_16)        /* threshold for slow adaption */
#define CVAD_ADAPT_FAST (Word16)((1.0 - 0.92) * MAX_16)         /* threshold for fast adaption */
#define CVAD_ADAPT_REALLY_FAST (Word16)((1.0 - 0.80) * MAX_16)  /* threshold for really fast
                                                                   adaption                    */
#define NPRED 4  /* number of prediction taps */
#define UP_SAMP_MAX  6
#define inter_36_FIR_SIZE     (UP_SAMP_MAX*L_INTER_SRCH+1)

#define L_INTER10    (L_INTERPOL-1)
#define pred_lt_FIR_SIZE     (UP_SAMP_MAX*L_INTER10+1)

#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 (Word16)0x7fff
#define MIN_16 (Word16)0x8000

#define DTX_HIST_SIZE 8
#define DTX_ELAPSED_FRAMES_THRESH (24 + 7 -1)
#define DTX_HANG_CONST 7             /* yields eight frames of SP HANGOVER  */


#define grid_points 60
#define NMAX 9
/* average innovation energy.                               */
/* MEAN_ENER  = 36.0/constant, constant = 20*Log10(2)       */
#define MEAN_ENER_MR122  783741L  /* 36/(20*log10(2)) (Q17) */

/* minimum quantized energy: -14 dB */
#define MIN_ENERGY       -14336       /* 14                 Q10 */
#define MIN_ENERGY_MR122  -2381       /* 14 / (20*log10(2)) Q10 */ 



#define     YES      1
#define     NO    0
#define     ON    1
#define     OFF      0
#define     TRUE     1
#define     FALSE    0

#define         FRM_LEN                 80
#define         DELAY                   24
#define         FFT_LEN                 128

#define         NUM_CHAN                16
#define         LO_CHAN                 0
#define         HI_CHAN                 15

#define         UPDATE_THLD             35
#define         HYSTER_CNT_THLD         6
#define         UPDATE_CNT_THLD         50

#define     SHIFT_STATE_0     0     /* channel energy scaled as 22,9 */
#define     SHIFT_STATE_1     1     /* channel energy scaled as 27,4 */

#define     NOISE_FLOOR_CHAN_0   512      /* 1.0    scaled as 22,9 */
#define     MIN_CHAN_ENRG_0      32    /* 0.0625 scaled as 22,9 */
#define     MIN_NOISE_ENRG_0  32    /* 0.0625 scaled as 22,9 */
#define     INE_NOISE_0    8192     /* 16.0   scaled as 22,9 */
#define     FRACTIONAL_BITS_0 9     /* used as input to fn10Log10() */

#define     NOISE_FLOOR_CHAN_1   16    /* 1.0    scaled as 27,4 */
#define     MIN_CHAN_ENRG_1      1     /* 0.0625 scaled as 27,4 */
#define     MIN_NOISE_ENRG_1  1     /* 0.0625 scaled as 27,4 */
#define     INE_NOISE_1    256      /* 16.0   scaled as 27,4 */
#define     FRACTIONAL_BITS_1 4     /* used as input to fn10Log10() */

#define     STATE_1_TO_0_SHIFT_R (FRACTIONAL_BITS_1-FRACTIONAL_BITS_0)  /* state correction factor */
#define     STATE_0_TO_1_SHIFT_R (FRACTIONAL_BITS_0-FRACTIONAL_BITS_1)  /* state correction factor */

#define         HIGH_ALPHA              29491      /* 0.9 scaled as 0,15 */
#define         LOW_ALPHA               22938      /* 0.7 scaled as 0,15 */
#define         ALPHA_RANGE             (HIGH_ALPHA - LOW_ALPHA)
#define         DEV_THLD                7168    /* 28.0 scaled as 7,8 */

#define         PRE_EMP_FAC             (-26214)   /* -0.8 scaled as 0,15 */

#define         CEE_SM_FAC              18022      /* 0.55 scaled as 0,15 */
#define         ONE_MINUS_CEE_SM_FAC    14746      /* 0.45 scaled as 0,15 */

#define         CNE_SM_FAC              3277    /* 0.1 scaled as 0,15 */
#define         ONE_MINUS_CNE_SM_FAC    29491      /* 0.9 scaled as 0,15 */

#define         FFT_HEADROOM            2


#define POS_CODE  8191 
#define NEG_CODE  8191 
#ifndef __aeon__
extern S64 amrnb_macr_a0, amrnb_macr_a1;
extern S64 amrnb_macr_a2, amrnb_macr_a3;
#endif



#define PN_INITIAL_SEED 0x70816958L   /* Pseudo noise generator seed value  */

#define CN_INT_PERIOD 24              /* Comfort noise interpolation period
                                         (nbr of frames between successive
                                         SID updates in the decoder) */

#define DTX_HANGOVER 7                /* Period when SP=1 although VAD=0.
                                         Used for comfort noise averaging */


/* Frame classification constants */

#define VALID_SID_FRAME          1
#define INVALID_SID_FRAME        2
#define GOOD_SPEECH_FRAME        3
#define UNUSABLE_FRAME           4

/* Encoder DTX control flags */

//#define TX_SP_FLAG               0x0001
//#define TX_VAD_FLAG              0x0002
//#define TX_HANGOVER_ACTIVE       0x0004
//#define TX_PREV_HANGOVER_ACTIVE  0x0008
//#define TX_SID_UPDATE            0x0010
//#define TX_USE_OLD_SID           0x0020
#define EFR_TX_SP_FLAG               0x0001
#define EFR_TX_VAD_FLAG              0x0002
#define EFR_TX_HANGOVER_ACTIVE       0x0004
#define EFR_TX_PREV_HANGOVER_ACTIVE  0x0008
#define EFR_TX_SID_UPDATE            0x0010
#define EFR_TX_USE_OLD_SID           0x0020
/* Decoder DTX control flags */

#define RX_SP_FLAG               0x0001
#define RX_UPD_SID_QUANT_MEM     0x0002
#define RX_FIRST_SID_UPDATE      0x0004
#define RX_CONT_SID_UPDATE       0x0008
#define RX_LOST_SID_FRAME        0x0010
#define RX_INVALID_SID_FRAME     0x0020
#define RX_NO_TRANSMISSION       0x0040
#define RX_DTX_MUTING            0x0080
#define RX_PREV_DTX_MUTING       0x0100
#define RX_CNI_BFI               0x0200
#define RX_FIRST_SP_FLAG         0x0400


/* Constants for the bit packing algorithm. */
/* Bit positions in table. */
#define B0  1
#define B1  2
#define B2  4
#define B3  8
#define B4  16
#define B5  32
#define B6  64
#define B7  128
#define B8  256

/* Table sizes */
/* Number of rows in table */
#define POS_TABLE_ENTRIES_CRC_PROTECTED       32
#define POS_TABLE_ENTRIES_CRC                 1
#define POS_TABLE_ENTRIES_REPEATED_BITS       1
#define POS_TABLE_ENTRIES_CLASS1B_UNPROTECTED 31
#define POS_TABLE_ENTRIES_CLASS2_UNPROTECTED  14

/* Total table size */
#define POS_TABLE_SZ_CRC_PROTECTED        (POS_TABLE_ENTRIES_CRC_PROTECTED*5)
#define POS_TABLE_SZ_CRC                  (POS_TABLE_ENTRIES_CRC*5)
#define POS_TABLE_SZ_REPEATED_BITS        (POS_TABLE_ENTRIES_REPEATED_BITS*5)
#define POS_TABLE_SZ_CLASS1B_UNPROTECTED  (POS_TABLE_ENTRIES_CLASS1B_UNPROTECTED*5)
#define POS_TABLE_SZ_CLASS2_UNPROTECTED   (POS_TABLE_ENTRIES_CLASS2_UNPROTECTED*5)

/* Bit offsets into packed array */
#define PACKED_BIT_OFFSET_0                   0     /* LTP-LAG1 (8)  */
#define PACKED_BIT_OFFSET_CRC                 65    /* CRC-POLY      */
#define PACKED_BIT_OFFSET_Ib                  73    /* LTP-GAIN1 (2) */
#define PACKED_BIT_OFFSET_REPEATED            182   /* PULSE_1_5 (1) */
#define PACKED_BIT_OFFSET_II                  194   /* PULSE_4_2 (1) */


/* The CRC polynomial is bit reversed and shifted right by one */
#define EFR_CRC_POLY      0x00b8   /* 100011101            */
#define EFR_CRC_INPUT_LEN 65
#define EFR_CRC_BITS      8
#define EFR_CRC_MAP_TABLE_LENGTH  33

#define ENC_SPEECH_SIZE           17     /**< 260 bits make < 17 words */

#define AU_SIDMSB_SHIFT           6

#define BUF_REQ_ALIGN_BITS 9
#define BUF_REQ_ALIGN_BYTE ((1<<BUF_REQ_ALIGN_BITS)-1)
#define BUF_REQ_ALIGN_MASK (~BUF_REQ_ALIGN_BYTE)

#define SID_CODE_TABLE_SZ 56
#endif
