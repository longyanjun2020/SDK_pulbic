#ifndef __MP3_ENC_CONSTANT_INCLUDE_FILE__
#define __MP3_ENC_CONSTANT_INCLUDE_FILE__



#ifdef WIN32
#define ATTR_NOINLINE
#define ATTR_NOMIPS16
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
typedef __int64 S64;

#else
#define ATTR_NOINLINE 
#define ATTR_NOMIPS16 
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef long long S64;

#endif


#define inline __inline

typedef signed char schar;

#ifndef FLOAT
#define        FLOAT             double
#endif

#ifndef PI
#define        PI                3.14159265358979
#endif
#define        PI64              PI/64
#define        SB_SIZE              32
#define        FFT_SIZE          1024
#define        HAN_SIZE          512
#define        SCALE_BLOCK          12

#define        SCALE             32768
#define        CRC16_POLYNOMIAL     0x8005


#define        MIN(A, B)      ((A) < (B) ? (A) : (B))
#define        MAX(A, B)      ((A) > (B) ? (A) : (B))


/* This is the smallest MNR a subband can have before it is counted
   as 'noisy' by the logic which chooses the number of JS subbands */

//#define NOISY_MIN_MNR   0.0
#define FRAC_MAX 0x7FFFFFFF

#define BITS_31 31
#define PRECISION_31 ((unsigned int)(1 << BITS_31))
#define SCALE_31(A) (((A) == 1.00) ? ((int)FRAC_MAX) : (((A) >= 0) ? ((int)((A)*(PRECISION_31)+0.5)) : ((int)((A)*(PRECISION_31)-0.5))))

#define BITS_30    30
#define PRECISION_30 (1 << BITS_30)
#define SCALE_30(A) (((A) >= 0) ? ((int)((A)*(PRECISION_30)+0.5)) : ((int)((A)*(PRECISION_30)-0.5)))

#define BITS_29    29
#define PRECISION_29 (1 << BITS_29)
#define SCALE_29(A) (((A) >= 0) ? ((int)((A)*(PRECISION_29)+0.5)) : ((int)((A)*(PRECISION_29)-0.5)))

#define BITS_28    28
#define PRECISION_28 (1 << BITS_28)
#define SCALE_28(A) (((A) >= 0) ? ((int)((A)*(PRECISION_28)+0.5)) : ((int)((A)*(PRECISION_28)-0.5)))

#define BITS_24    24 
#define PRECISION_24 (1 << BITS_24)
#define SCALE_24(A) (((A) >= 0) ? ((int)((A)*(PRECISION_24)+0.5)) : ((int)((A)*(PRECISION_24)-0.5)))


#define BITS_23    23 
#define PRECISION_23 (1 << BITS_23)
#define SCALE_23(A) (((A) >= 0) ? ((int)((A)*(PRECISION_23)+0.5)) : ((int)((A)*(PRECISION_23)-0.5)))


#define BITS_15    15 
#define PRECISION_15 (1 << BITS_15)
#define SCALE_15(A) (((A) >= 0) ? ((int)((A)*(PRECISION_15)+0.5)) : ((int)((A)*(PRECISION_15)-0.5)))

#define BITS_14    14 
#define PRECISION_14 (1 << BITS_14)
#define SCALE_14(A) (((A) >= 0) ? ((int)((A)*(PRECISION_14)+0.5)) : ((int)((A)*(PRECISION_14)-0.5)))

#define BITS_11    11
#define PRECISION_11 (1 << BITS_11)
#define SCALE_11(A) (((A) >= 0) ? ((int)((A)*(PRECISION_11)+0.5)) : ((int)((A)*(PRECISION_11)-0.5)))

#define SCALE_SB1 SCALE_31
#define SCALE_SB2 SCALE_30
#define SCALE_SB3 SCALE_31
#ifdef USING_MAC_32x32
#define SCALE_SB2_14 SCALE_30
#else
#define SCALE_SB2_14 SCALE_14
#endif

#define SCALE_SF  SCALE_28
#define SCALE_SNR  SCALE_23
#define PRECISION_SNR   PRECISION_23

#define SCALE_SFI    SCALE_11
#define BITS_SFI     BITS_11

#define SCALE_Q1  SCALE_31
#define PRECISION_Q1 PRECISION_31

#define SCALE_Q2  SCALE_28
#define BITS_Q2   BITS_28


#define MP3E_STEREO        0
#define MP3E_JOINT_STEREO  1
#define MP3E_DUAL_CHANNEL  2
#define MP3E_MONO          3


#define MP3E_MPEG2   0 
#define MP3E_MPEG1   1 


/** Number of samples per frame of Layer 2 MPEG Audio */
#define MP3E_SAMPLES_PER_FRAME      (1152)
#define MAX_FRAME_BUF    1632
#define SQRT2    1.4142135623730951454746218587388284504414
#define mp3e_abs(x) (((x) < 0)?(-(x)): (x))

#endif


