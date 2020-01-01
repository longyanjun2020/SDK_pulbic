#ifndef __MP3_L3_ENCODER_CONSTANT_INCLUDE_FILE__
#define __MP3_L3_ENCODER_CONSTANT_INCLUDE_FILE__



#ifdef WIN32
#define ATTR_NOINLINE
#define ATTR_NOMIPS16
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
typedef __int64 S64;
#define INLINE __inline
#else

#define ATTR_NOINLINE 
#define ATTR_NOMIPS16 
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef long long S64;
#define INLINE __inline
#endif
typedef signed char schar;


#define ENCDELAY      576
#define POSTDELAY   1152
#define MDCTDELAY     48
#define FFTOFFSET     (224+MDCTDELAY)



#define DECDELAY      528
#define SBPSY_l       21
#define SBMAX_l       22



#define MPG_MD_LR_LR  0
#define MPG_MD_LR_I   1
#define MPG_MD_MS_LR  2
#define MPG_MD_MS_I   3


#define         CRC16_POLYNOMIAL        0x8005
    
#define MAX_BITS_PER_CHANNEL 4095
#define MAX_BITS_PER_GRANULE 7680

#define         mp3e_Min(A, B)       ((A) < (B) ? (A) : (B))
#define         mp3e_Max(A, B)       ((A) > (B) ? (A) : (B))
#define         mp3e_abs(x) (((x) < 0)? (-(x)):(x))

#define MAX_CHANNELS  2

#define LARGE_BITS 100000

#define LOG2_SIZE       (512)
#define LOG2_SIZE_L2    (9)
#define SQRT_SIZE       (512)
#define SQRT_SIZE_L2    (9)

#define mp3e_ilog2(x,ib,ob) mp3e_l3_ifast_log2(x,ib,ob)
#define SQRT2    1.4142135623730951454746218587388284504414

#define SCALE28_SQRT2      SCALE_28(SQRT2)
#define SCALE28_SQRT2_D2   SCALE_28(SQRT2/2)

#define MAX_BITS 4095


#define FRAC_MAX 0x7FFFFFFF


#define BITS_47 47
#define PRECISION_47 ((S64)1 << BITS_47)
#define SCALE_47(A) (((A) >= 0) ? ((int)((A)*(PRECISION_47)+0.5)) : ((int)((A)*(PRECISION_47)-0.5)))

#define BITS_43 43
#define PRECISION_43 ((S64)1 << BITS_43)
#define SCALE_43(A) (((A) >= 0) ? ((int)((A)*(PRECISION_43)+0.5)) : ((int)((A)*(PRECISION_43)-0.5)))

#define BITS_39 39
#define PRECISION_39 ((S64)1 << BITS_39)
#define SCALE_39(A) (((A) >= 0) ? ((int)((A)*(PRECISION_39)+0.5)) : ((int)((A)*(PRECISION_39)-0.5)))

#define BITS_33 33
#define PRECISION_33 ((S64)1 << BITS_33)
#define SCALE_33(A) (((A) >= 0) ? ((int)((A)*(PRECISION_33)+0.5)) : ((int)((A)*(PRECISION_33)-0.5)))

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

#define BITS_26    26
#define PRECISION_26 (1 << BITS_26)
#define SCALE_26(A) (((A) >= 0) ? ((int)((A)*(PRECISION_26)+0.5)) : ((int)((A)*(PRECISION_26)-0.5)))

#define BITS_24    24 
#define PRECISION_24 (1 << BITS_24)
#define SCALE_24(A) (((A) >= 0) ? ((int)((A)*(PRECISION_24)+0.5)) : ((int)((A)*(PRECISION_24)-0.5)))


#define BITS_23    23 
#define PRECISION_23 (1 << BITS_23)
#define SCALE_23(A) (((A) >= 0) ? ((int)((A)*(PRECISION_23)+0.5)) : ((int)((A)*(PRECISION_23)-0.5)))

#define BITS_16    16
#define PRECISION_16 (1 << BITS_16)
#define SCALE_16(A) (((A) >= 0) ? ((int)((A)*(PRECISION_16)+0.5)) : ((int)((A)*(PRECISION_16)-0.5)))

#define BITS_15    15 
#define PRECISION_15 (1 << BITS_15)
#define SCALE_15(A) (((A) >= 0) ? ((int)((A)*(PRECISION_15)+0.5)) : ((int)((A)*(PRECISION_15)-0.5)))

#define BITS_14    14 
#define PRECISION_14 (1 << BITS_14)
#define SCALE_14(A) (((A) >= 0) ? ((int)((A)*(PRECISION_14)+0.5)) : ((int)((A)*(PRECISION_14)-0.5)))

#define BITS_11    11
#define PRECISION_11 (1 << BITS_11)
#define SCALE_11(A) (((A) >= 0) ? ((int)((A)*(PRECISION_11)+0.5)) : ((int)((A)*(PRECISION_11)-0.5)))

#define BITS_8    8
#define PRECISION_8 (1 << BITS_8)
#define SCALE_8(A) (((A) >= 0) ? ((int)((A)*(PRECISION_8)+0.5)) : ((int)((A)*(PRECISION_8)-0.5)))

#define BITS_4    4
#define PRECISION_4 (1 << BITS_4)
#define SCALE_4(A) (((A) >= 0) ? ((int)((A)*(PRECISION_4)+0.5)) : ((int)((A)*(PRECISION_4)-0.5)))

#define SCALE_SB1 SCALE_31
#define SCALE_SB2 SCALE_30
#define SCALE_SB3 SCALE_31


#ifdef USING_MAC_32x32
#define SCALE_SB2_14 SCALE_30
#else
#define SCALE_SB2_14 SCALE_14
#endif

#define SCALE_CX     SCALE_31
#define BIT_CX       BITS_31

//#define BIT_WIN   24
//#define SCALE_WIN SCALE_39


//#define SCALE_WIN SCALE_47
//#define SCALE_WIN SCALE_31


#define SCALE_ALIAS  SCALE_31
#define BIT_ALIAS    BITS_31

#define SCALE_TAN    SCALE_26
#define BIT_TAN      BITS_26


#define SCALE_LOG    SCALE_28
#define BIT_LOG      BITS_28

#define SCALE_SQRT    SCALE_28
#define BIT_SQRT      BITS_28

#define SCALE_POW43    SCALE_28
#define BIT_POW43      BITS_28

#define SCALE_STEP   SCALE_28
#define BIT_STEP     BITS_28


#define SCALE_PE   SCALE_4
#define BIT_PE     BITS_4

#define BUF_REQ_ALIGN_BITS 9
#define BUF_REQ_ALIGN_BYTE ((1<<BUF_REQ_ALIGN_BITS)-1)
#define BUF_REQ_ALIGN_MASK (~BUF_REQ_ALIGN_BYTE)

#define SHORT_INT(x,y)  (((unsigned int)y & 0xffff0000) | (((unsigned int)x>>16) & 0x0000ffff))

#define SH_INT_L(x,y)  (((y & 0xffff)<<16) | (x & 0x0000ffff))

#define HUFF(x) (x)
#define HLEN(x) (x)
#endif

