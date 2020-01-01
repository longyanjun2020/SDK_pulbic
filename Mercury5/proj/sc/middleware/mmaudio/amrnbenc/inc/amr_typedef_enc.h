/*
 * ===================================================================
 *  TS 26.104
 *  REL-5 V5.4.0 2004-03
 *  REL-6 V6.1.0 2004-03
 *  3GPP AMR Floating-point Speech Codec
 * ===================================================================
 *
 */
/* This is valid for PC */

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

//#include <pkgconf/system.h>
//#include "shellcfg.h"

#define MS_MALLOC(size)                     \
        libVarStruct->AMRHeapBuf;           \
        libVarStruct->AMRHeapBuf += size;


#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 (Word16)0x7fff
#define MIN_16 (Word16)0x8000

#define CHECK_OVERFLOW(v) ((((v)<<1) ^ (v)) & 0x80000000)

#ifdef __GNUC__
#define FORCE_INLINE    __attribute__((always_inline))
#else
#define FORCE_INLINE    __forceinline
#endif

#ifdef __mips__
#define NOMIPS16    __attribute__((nomips16))
#else
#define NOMIPS16
#endif

typedef signed char Word8;
typedef unsigned char UWord8;
typedef short Word16;
typedef int Word32;
typedef unsigned int UWord32;
#ifdef __GNUC__
typedef unsigned long long UWord64;
typedef long long Word64;
#else
typedef unsigned __int64 UWord64;
typedef __int64 Word64;
#endif
typedef float Float32;
typedef double Float64;


#include "vm_types.ht"


// [disable fopen, fclose and fxxx functions]
#ifdef  DISABLE_FILE
	#ifndef FILE
		#define FILE			char
	#endif
	#define myfopen(a,b)		0
	#define myfclose(a)
	#define myfread(a,b,c,d)	0
	#define myfwrite(a,b,c,d)	0
	#define myfseek(a,b,c)		0
	#define myftell(a)			0
	#define myfsetpos(a,b)		0
	#define myfgetpos(a,b)		0
	#define myfflush(a)			0

	#ifdef WIN32
		#define myfscanf(a,b)  0
		#define myfprintf(a,b) 0
	#else
		#define myfscanf(a,b...)  0
		#define myfprintf(a,b...) 0
	#endif

#else
	#define myfopen		fopen
	#define myfclose	fclose
	#define myfread		fread
	#define myfwrite    fwrite
	#define myfseek     fseek
	#define myftell     ftell
	#define myfsetpos   fsetpos
	#define myfgetpos   fgetpos
	#define myfflush	fflush

	#define myfscanf    fscanf
	#define myfprintf	fprintf
#endif

extern void fnAMRHeap_SetAddr(void *amrheapaddr);

extern Word32 Log2_norm( Word32 x, Word32 exp, Word32 *exponent );
extern Word32 Log2( Word32 x, Word32 *exponent );

extern Word32 Pow2( Word32 exponent, Word32 fraction );

extern void Int_lpc_1to3( Word32 lsp_old[], Word32 lsp_new[], Word32 Az[] );

extern void Lsp_Az( Word32 lsp[], Word32 a[] );

extern Word32 Inv_sqrt( Word32 x );

extern void Lsf_lsp( Word32 lsf[], Word32 lsp[] );


#define M               10    /* Order of LP filter */
#define MP1             (M+1) /* Order of LP filter + 1 */
#define L_WINDOW        240   /* Window size in LP analysis */
#define L_NEXT          40    /* Overhead in LP analysis */
#define LTPG_MEM_SIZE   5     /* number of stored past LTP coding gains + 1 */
#define N_FRAME         7     /* old pitch gains in average calculation */
#define DTX_HIST_SIZE   8     /* DTX history size */
#define L_TOTAL         320   /* Total size of speech buffer. */
#define L_FRAME         160   /* Frame size */
#define L_FRAME_BY2     80    /* Frame size divided by 2 */
#define L_SUBFR         40    /* Subframe size */
#define L_CODE          40    /* codevector length */
#define PIT_MAX         143   /* Maximum pitch lag */
#define PIT_MIN         20    /* Minimum pitch lag */
#define PIT_MIN_MR122   18    /* Minimum pitch lag (MR122 mode) */
#define L_INTERPOL      (10+1)/* Length of filter for interpolation */
#define NPRED           4     /* number of prediction taps */
#define SHARPMIN        0     /* Minimum value of pitch sharpening */
#define MAX_PRM_SIZE    57    /* max. num. of params */
#define L_INTER_SRCH    4     /* Length of filter for CL LTP search interpolation */
#define GP_CLIP         15565 /* Pitch gain clipping */
#define UP_SAMP_MAX     6
#define NB_TRACK        5     /* number of tracks */
#define NB_TRACK_MR102  4     /* number of tracks mode mr102 */
#define STEP            5     /* codebook step size */
#define STEP_MR102      4     /* codebook step size mode mr102 */
#define NC              M/2   /* Order of LP filter divided by 2 */

#define SCALE_LSP_FREQ  (Float32)(4000.0/3.141592654)
#define SCALE_FREQ_LSP  (Float32)(3.141592654/4000.0)
#define SLOPE1_WGHT_LSF (Float32)((3.347-1.8)/(450.0-0.0))
#define SLOPE2_WGHT_LSF (Float32)((1.8-1.0)/(1500.0-450.0))

#define FRAME_LEN 160    /* Length (samples) of the input frame          */
#define COMPLEN 9        /* Number of sub-bands used by VAD              */
#define INV_COMPLEN 3641 /* 1.0/COMPLEN*2^15                             */
#define LOOKAHEAD 40     /* length of the lookahead used by speech coder */

#define UNITY 512        /* Scaling used with SNR calculation            */
#define UNIRSHFT 6       /* = log2(MAX_16/UNITY)                         */

#define TONE_THR  (Word16)(0.65*MAX_16) /* Threshold for tone detection   */

#define ALPHA_UP1   (Word16)((1.0 - 0.95)*MAX_16)  /* Normal update, upwards:   */
#define ALPHA_DOWN1 (Word16)((1.0 - 0.936)*MAX_16) /* Normal update, downwards  */
#define ALPHA_UP2   (Word16)((1.0 - 0.985)*MAX_16) /* Forced update, upwards    */
#define ALPHA_DOWN2 (Word16)((1.0 - 0.943)*MAX_16) /* Forced update, downwards  */
#define ALPHA3      (Word16)((1.0 - 0.95)*MAX_16)  /* Update downwards          */
#define ALPHA4      (Word16)((1.0 - 0.9)*MAX_16)   /* For stationary estimation */
#define ALPHA5      (Word16)((1.0 - 0.5)*MAX_16)   /* For stationary estimation */

#if 0
/* Constants for background spectrum update */
#define ALPHA_UP1   (Float32)(1.0 - 0.95)  /* Normal update, upwards:   */
#define ALPHA_DOWN1 (Float32)(1.0 - 0.936) /* Normal update, downwards  */
#define ALPHA_UP2   (Float32)(1.0 - 0.985) /* Forced update, upwards    */
#define ALPHA_DOWN2 (Float32)(1.0 - 0.943) /* Forced update, downwards  */
#define ALPHA3      (Float32)(1.0 - 0.95)  /* Update downwards          */
#define ALPHA4      (Float32)(1.0 - 0.9)   /* For stationary estimation */
#define ALPHA5      (Float32)(1.0 - 0.5)   /* For stationary estimation */
#endif

/* Constants for VAD threshold */
#define VAD_THR_HIGH 1260 /* Highest threshold                 */
#define VAD_THR_LOW  720  /* Lowest threshold                  */
#define VAD_P1 0          /* Noise level for highest threshold */
#define VAD_P2 6300       /* Noise level for lowest threshold  */
//#define VAD_SLOPE (float)(VAD_THR_LOW-VAD_THR_HIGH)/(float)(VAD_P2-VAD_P1)
#define VAD_SLOPE (Word32)(32768 * (float)(VAD_THR_LOW-VAD_THR_HIGH)/(float)(VAD_P2-VAD_P1))

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
#define VAD_POW_LOW (Word32)15000/2    /* If input power is lower,                    */
                                       /*     VAD is set to 0                         */
#define POW_PITCH_THR (Word32)343040/2 /* If input power is lower, pitch              */
                                       /*     detection is ignored                    */

#define POW_COMPLEX_THR (Word32)15000/2/* If input power is lower, complex            */
                                       /* flags  value for previous frame  is un-set  */
/*
 * VAD Constants
 */

/* Constants for the filter bank */
#define LEVEL_SHIFT 0                     /* scaling                                  */
#define COEFF3   13363     /* Q15 coefficient for the 3rd order filter     */
#define COEFF5_1 21955     /* Q15 1st coefficient the for 5th order filter */
#define COEFF5_2 6390      /* Q15 2nd coefficient the for 5th order filter */

/* Constants for pitch detection */
#define LTHRESH 4
#define NTHRESH 4

#if 0
/* Constants for complex signal VAD  */
#define CVAD_THRESH_ADAPT_HIGH  0.6F            /* threshold for adapt stopping high */
#define CVAD_THRESH_ADAPT_LOW  0.5F             /* threshold for adapt stopping low */
#define CVAD_THRESH_IN_NOISE  0.65F * 32768.0F  /* threshold going into speech on
                                                   a short term basis */
#define CVAD_THRESH_HANG  0.70F           /* threshold */
#define CVAD_HANG_LIMIT  (Word16)(100)    /* 2 second estimation time */
#define CVAD_HANG_LENGTH  (Word16)(250)   /* 5 second hangover */

#define CVAD_LOWPOW_RESET 0.40F  /* init in low power segment */
#define CVAD_MIN_CORR 0.40F      /* lowest adaptation value */

#define CVAD_BURST 20                        /* speech burst length for speech reset */
#define CVAD_ADAPT_SLOW 1.0F - 0.98F         /* threshold for slow adaption */
#define CVAD_ADAPT_FAST 1.0F - 0.92F         /* threshold for fast adaption */
#define CVAD_ADAPT_REALLY_FAST 1.0F - 0.80F  /* threshold for really fast adaption */
#endif

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
#define CVAD_ADAPT_REALLY_FAST (Word16)((1.0 - 0.80) * MAX_16)  /* threshold for really fast   */


typedef struct
{
   Word32 past_qua_en[4];
   Word32 past_qua_en_MR122[4];

   /* normal MA predictor memory, (contains 20*log10(qua_err)) */
}gc_predState;

#endif
