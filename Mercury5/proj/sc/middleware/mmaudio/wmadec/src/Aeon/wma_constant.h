
//====================================================================
// Copyright (C) Mstar Semiconductor  Corporation. All rights reserved.
// WMA decoder wma_constant.h
// Creat Date: 2009/08/12
//====================================================================

#ifndef __WMA_CONSTANT_H__
#define __WMA_CONSTANT_H__

//#define iVersion_1  // for m_iVersion == 1
#define OUTPUT_2CHANNELS  // for output is always 2 channel
#define BUILD_WMASTD
#define BUILD_INTEGER_LPC
#define BUILD_INTEGER
#define ENABLE_LPC

typedef int WMA_I32;
typedef int tWMA_I32;
typedef int tWMA_Bool;
typedef WMA_I32         WMA_Bool;
typedef int WMARESULT;
typedef int WMA_BOOl;


typedef unsigned int WMA_U32;
typedef unsigned int tWMA_U32;
typedef unsigned int    DWORD;


typedef short I16;
typedef short WMA_I16;
typedef short tWMA_I16;
typedef unsigned short WMA_U16;
typedef unsigned short tWMA_U16;
typedef unsigned short WORD;


typedef unsigned char tWMA_U8;
typedef unsigned char WMA_U8;
typedef signed char I8;
typedef unsigned char   BYTE;

#ifdef __aeon__

#define USE_MIPS32
typedef unsigned long long  tWMA_U64;
typedef unsigned long long  U64;
typedef long long  tWMA_I64;
#else
#define USE_MIPS32
typedef unsigned __int64 tWMA_U64;
typedef unsigned __int64 U64;
typedef __int64    tWMA_I64;
#endif



#define SHRT_MAX      32767
typedef struct tQWORD
{
    tWMA_U32   dwLo;
    tWMA_U32   dwHi;
}   QWORD;

#define U32_MAX ((WMA_U32)0xffffffffu)
#define I32_MIN ((tWMA_I32)0x80000000)
#define I32_MAX ((tWMA_I32)0x7fffffff)
#define U16_MAX ((tWMA_I32)0x0000ffff)
#define I16_MIN ((tWMA_I32)0xffff8000)
#define I16_MAX ((tWMA_I32)0x00007fff)
#define U8_MAX ((tWMA_I32)0x000000ff)
#define I8_MIN ((tWMA_I32)0xffffff80)
#define I8_MAX ((tWMA_I32)0x0000007f)

//typedef double  Double;
typedef float   Float;
typedef WMA_U32  UInt;
typedef tWMA_I32     Int;
typedef tWMA_I32     Bool; // In Win32, WMA_BOOl is an "int" == 4 bytes. Keep it this way to reduce problems.



typedef tWMA_I32 BP1Type;
typedef tWMA_I32 BP2Type;
typedef tWMA_I32 CoefType;
typedef tWMA_I32 FracBitsType;
typedef struct {
    //I8 exponent;  Old exponent was shift from binary point at 24th position
   FracBitsType iFracBits;
   tWMA_I32 iFraction;
} FastFloat;
typedef tWMA_I32 ChDnMixType;
typedef tWMA_I64 XBP1Type;
typedef tWMA_I64 XBP2Type;
typedef WMA_U32 WtType;
typedef UInt WeightType;
typedef UInt FinalWeightType;
typedef tWMA_U64 LpSpecPowerType;
typedef Int LpType;
typedef Int LspType;
typedef FastFloat QuantFloat;
typedef Int LpSpecType;


// SUCCESS codes
#define WMA_OK                   0x00000000
#define WMA_S_FALSE              0x00000001
#define WMA_S_BUFUNDERFLOW       0x00000002
#define WMA_S_NEWPACKET          0x00000003
#define WMA_S_NO_MORE_FRAME      0x00000004
#define WMA_S_NO_MORE_SRCDATA    0x00000005
#define WMA_S_LOSTPACKET         0x00000006

// ERROR codes
#define WMA_E_FAIL               0x80004005
#define WMA_E_OUTOFMEMORY        0x8007000E
#define WMA_E_INVALIDARG         0x80070057
#define WMA_E_NOTSUPPORTED       0x80040000
#define WMA_E_BROKEN_FRAME       0x80040002
#define WMA_E_BUFFEROVERFLOW     0x80040003
#define WMA_E_ONHOLD             0x80040004
#define WMA_E_NO_MORE_SRCDATA    0x80040005
#define WMA_E_WRONGSTATE         0x8004000A
////////////////////////////////////


#ifndef WMAB_TRUE
#define WMAB_TRUE 1
#endif //WMAB_TRUE
#ifndef WMAB_FALSE
#define WMAB_FALSE 0
#endif //WMAB_FALSE

#define PCMSAMPLE_MAX(iValidBits)   ((1 << ((iValidBits) - 1)) - 1)
#define PCMSAMPLE_MIN(iValidBits)   (~((1 << ((iValidBits) - 1)) - 1))



// **************************************************************************
// Overridable Compiler Directives
// **************************************************************************
#define INLINE __inline

#define DEBUG_ONLY(x)   x


#define SWAP_WORD( w )      (w) = ((w) << 8) | ((w) >> 8)

#define SWAP_DWORD( dw )    (dw) = ((dw) << 24) | ( ((dw) & 0xFF00) << 8 ) | ( ((dw) & 0xFF0000) >> 8 ) | ( ((dw) & 0xFF000000) >> 24);

// WMARESULT macros (stolen from winerror.h)
#ifndef WMA_SUCCEEDED
#define WMA_SUCCEEDED(Status) ((WMARESULT)(Status) >= 0)
#endif //WMA_SUCCEEDED
#ifndef WMA_FAILED
#define WMA_FAILED(Status) ((WMARESULT)(Status)<0)
#endif //WMA_FAILED

#ifdef COEF64BIT
//#define HIGHBIT_CH
//#define HIGHBIT_IQ
#define HIGHBIT_FFT
#else
#undef HIGHBIT_CH
#undef HIGHBIT_IQ
#undef HIGHBIT_FFT
#endif


typedef Int CBT;


#define PLAYOPT_HALFTRANSFORM      0x0002
#define PLAYOPT_PAD2XTRANSFORM     0x0008
#define PLAYOPT_DYNAMICRANGECOMPR  0x0080
#define PLAYOPT_IGNOREFREQEX       0x0200
#define PLAYOPT_IGNORECX           0x0400


// ****************************************************
// Dynamic Range Control settings
// ****************************************************
//#define WMA_DRC_HIGH 0
//#define WMA_DRC_MED 1
//#define WMA_DRC_LOW 2


#define FFT_LOOKUPTBL                   0
#define DCT_LOOKUPTBL                   0
#define BITREVERSAL_FFTDCT_LOOKUPTBL    0
#define SMALL_BR128TWIDDLE_LOOKUPTBL    0

#define CAP_NODISCARDSILENCE    0
#define CAP_DISCARDSILENCE      1
#define CAP_SUBFRAMELVL         0
#define CAP_ENTIREFRAME         1


#define I17_MIN ((signed) 0xFFFF0000)
#define I17_MAX ((signed) 0x0000FFFF)

#define INTERPOL_FRACTBITS  30

#define PRECESSION_BITS_FOR_INVQUADROOT 12

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
#endif

#ifndef WAVE_FORMAT_EXTENSIBLE
#define WAVE_FORMAT_EXTENSIBLE 65534
#endif

// Angle can go from -MAX_ROTATION_ANGLE_INDEX to (MAX_ROTATION_ANGLE_INDEX-1).
#define ROTATION_ANGLE_BITS 6
#define MAX_ROTATION_ANGLES (1<<ROTATION_ANGLE_BITS)
#define MAX_ROTATION_ANGLE_INDEX (MAX_ROTATION_ANGLES>>1)

#define MAX_CHANNEL 8

#ifdef  PI
#undef  PI
#endif
#define PI  3.1415926535897932384626433832795
// value prior to 10/5/99 as a float: #define PI  3.14159265359F

#ifdef  BITS_PER_BYTE
#undef  BITS_PER_BYTE
#endif
#define BITS_PER_BYTE 8

#ifdef  BITS_PER_DWORD
#undef  BITS_PER_DWORD
#endif
#define BITS_PER_DWORD      32

#ifdef  BITS_PER_QWORD
#undef  BITS_PER_QWORD
#endif
#define BITS_PER_QWORD      64

#ifdef  NBITS_PACKET_CNT
#undef  NBITS_PACKET_CNT
#endif
#define NBITS_PACKET_CNT    4

#ifdef  NBITS_FRM_CNT
#undef  NBITS_FRM_CNT
#endif
#define NBITS_FRM_CNT       4

#ifdef  NUM_BARK_BAND
#undef  NUM_BARK_BAND
#endif
#define NUM_BARK_BAND 28

#ifdef  LOW_CUTOFF_V1
#undef  LOW_CUTOFF_V1
#endif
#define LOW_CUTOFF_V1 3        //TBD

#ifdef  LOW_CUTOFF
#undef  LOW_CUTOFF
#endif
#define LOW_CUTOFF 0        //wchen: no more due to bug#19144

// power reduction factor in dB for masking @ same frequency
#define MIN_THRESHOLD_IN_DB_V1  25

#ifdef  MIN_MASKQ_IN_DB_V1
#undef  MIN_MASKQ_IN_DB_V1
#endif
#define MIN_MASKQ_IN_DB_V1 (Int) (MIN_THRESHOLD_IN_DB_V1 / MASK_QUANT)

#ifdef  MASK_QUANT      // in db
#undef  MASK_QUANT
#endif

// MASK_QUANT is used only in V1, V2.
#define MASK_QUANT 2.5f

#ifdef  NBITS_FIRST_MASKQUANT
#undef  NBITS_FIRST_MASKQUANT
#endif
#define NBITS_FIRST_MASKQUANT 5

#ifdef  FIRST_V2_MASKQUANT
#undef  FIRST_V2_MASKQUANT
#endif
#define FIRST_V2_MASKQUANT 36
#define FIRST_V3_MASKQUANT 45

#ifdef  MAX_MASKQUANT_DIFF
#undef  MAX_MASKQUANT_DIFF
#endif
#define MAX_MASKQUANT_DIFF 60  // limited by the huffman table

#ifdef  NUM_BITS_QUANTIZER
#undef  NUM_BITS_QUANTIZER
#endif
#define NUM_BITS_QUANTIZER 7

#ifdef  NUM_BITS_QUANTIZER_V3
#undef  NUM_BITS_QUANTIZER_V3
#endif
#define NUM_BITS_QUANTIZER_V3 5


// both as the escape code and the range...
#ifdef  MSA_MAX_QUANT_ESC
#undef  MSA_MAX_QUANT_ESC
#endif
#define MSA_MAX_QUANT_ESC ((1<<NUM_BITS_QUANTIZER) - 1)

#ifdef  MSA_MAX_QUANT_ESC_V3
#undef  MSA_MAX_QUANT_ESC_V3
#endif
#define MSA_MAX_QUANT_ESC_V3 ((1<<NUM_BITS_QUANTIZER_V3) - 1)

#ifdef  MAX_QUANT
#undef  MAX_QUANT
#endif
#define MAX_QUANT 129   /* 138 has been seen by decoder */

#ifdef  MAX_QUANTSTEPSIZE
#undef  MAX_QUANTSTEPSIZE
#endif
#define MAX_QUANTSTEPSIZE (2 * MAX_QUANT + 1)

#ifdef  MIN_QUANT
#undef  MIN_QUANT
#endif
#define MIN_QUANT 1     /*  was once 10; 22 is lowest value seen by decoder */

#define MAX_RUNLEVEL_44SM_QB 60
#define MAX_RUNLEVEL_44SS_QB 40
#define MAX_RUNLEVEL_44SM_OB 340
#define MAX_RUNLEVEL_44SS_OB 180
#define MAX_RUNLEVEL_16SM_OB 70
#define MAX_RUNLEVEL_16SS_OB 40

//lpc constants;need clean up
#define LPCORDER 10
#define FOURTYFOURS_QB 1
#define FOURTYFOURS_OB 2
#define SIXTEENS_OB 3

#define MSA_STEREO_WEIGHT 1.6F
// Assumes subwoofer presence: 30Kbps savings@128 kbps wrt independent coding (158/128) * 6/5
#define MSA_MULTICH_WEIGHT 1.48F

#define CX_BITRATE 2300

#define MIN_EQ -35
#define MAX_EQ 15
#define MIN_RATE BITS_PER_BYTE

#define NUM_PREV_POWER 8
#define NUM_TRANS_FILTER 4

// Constants
#define QUANTSTEP_DENOMINATOR 20
#define QUANTSTEP_FRACT_BITS 28

#define TRANSFORM_FRACT_BITS    5

#define TRANSIENT_THRFRACTBITS  4       // Allows 1/16 precision (see threshold init)

#define UNFILTERED_STRONG_DETECTED -4
#define POSTECHO_DETECTED -3
#define NOT_DETECTED_YET -2
#define NO_TRANSIENT     -1

#define HOLE_FILL_BITS  7 //hole filling

// Moved here from msaudio.h
#define MAX_SUBFRAMES       32

// V3 LLM. Chao. Add.
#define MAX_LPC_ORDER_UNIFIED       32
#define MIN_LPC_ORDER_UNIFIED       1
#define LPC_ORDER_UNIFIED_BITS      5 // 5 bits can represent order from 1 to 32.

#define MAX_LPC_INTBITS_UNIFIED     8
#define MIN_LPC_INTBITS_UNIFIED     1
#define BITS_LPC_INTBITS_UNIFIED    3


#define LLM_LPC_ORDER               (WMA_U32)40
#define LLM_LPC_ORDER_MLLM          4   // must less than LLM_LPC_ORDER!

#define MAX_LSP_ORDER_WMA 50
#define MAX_LPC_ORDER_WMA 50

#define LSQ_QUAN_STEPSIZE           0.0025F
#define LOSSY_OR_MIXEDLOSSLESS_MODE 0x0000

#define NO_CHANNEL_MIXING           WMAB_FALSE
#define DO_CHANNEL_MIXING           WMAB_TRUE
#define NO_MCLMS                    WMAB_FALSE
#define DO_MCLMS                    WMAB_TRUE
#define NO_ARITHMETIC_CODING        WMAB_FALSE
#define DO_ARITHMETIC_CODING        WMAB_TRUE


typedef enum {CH_MIX_INDPDT, CH_MIX_S_TRAN, CH_MIX_DIFF_L, CH_MIX_DIFF_R} ChannelMixingMode;
typedef enum {COLOMB_CODING, COLOMB_ARITHMATIC_CODING} EntropyCodingScheme;

//V3 LLMA
#define MAX_CHANNEL_MIXING_ROUND 0

#define MLLM_FILTER_SCALING             6   // 24+1 = 25 bits. 32-25 = 7. We use 6 bits for scaling.
#define MLLM_QUANTSTEPSIZE_BITS         8   // Bits for quantization stepsize.

//  4 (2 bits) is the maximum value in its worst case (24 bits audio) since we use tWMA_I32 and scaling factor is 6. (2 + 6 + 24 = 32)
#define LLM_VERB_ACFILTER_ORDER_MIN     1
#define LLM_VERB_ACFILTER_ORDER_MAX     4  //max length (order) of AC filter in LLM_VERB.
#define LLM_VERB_ACFILTER_ORDER_BITS    4  // 2+2 We give 2 more bits. Then the actuall ORDER_MAX is 2^4=16.

//#define LLM_VERB_ACFILTER_SCALING       6   //scaling factor of AC filter coefficients.

//V3 LLM-B. Chao. Add. 03-18-02
#define LLMB_MCLMS_TTL_MAX              1  // sorry, only 1 right now.
//we set all filter order and scaling in ResetAll.
//#define LLMB_MCLMS_ORDER_EACHCH         2
#define LLMB_MCLMS_MIN_ORDER_EACHCH     2
#define LLMB_MCLMS_MAX_ORDER_EACHCH     8  //Multi-channel LMS's max order in each channel. The total order is LLMB_MCLMS_ORDER_EACHCH * cChannel
#define LLMB_MCLMS_ORDER_BITS           4 //8/2=4   We give 2 more bits. Then the actuall ORDER_MAX is 2*2^4=32.
//#define LLMB_MCLMS_ORDER_EACHCH         2
//#define LLMB_MCLMS_LAMDA         20

//V3 LLM-B. Chao. Add. 03-15-02
#define LLMB_CLMSFLT_TTL_MIN            1

#define LLMB_CLMSFLT_TTL_MAX            4        // we support up to 4 cascaded LMS filters.

#define LLMB_CLMSFLT_TTL_BITS           3       // 1,2,3,4 2 bits. We give 1 more bit. Then the actual TTL_MAX is 2^3 = 8;

#define LLMB_CLMSFLT_MIN_ORDER          8       // This is the limitation for bitstream.
#define LLMB_CLMSFLT_MIN_ORDER_REAL     8      // This is the actuall limitation due to MMX implementation.

#define LLMB_CLMSFLT_MAX_ORDER          256

#define LLMB_CLMSFLT_ORDER_BITS         7   //256/8=32 We give 2 more bits. Then the actual MAX_ORDER is 8*2^7 = 1024;

#define LLMB_INTEGERIZATION_SCALING_MAX     12  // actuall speed 1/2^12
#define LLMB_INTEGERIZATION_SCALING_MIN     0   // actuall speed 1/2^0
#define LLMB_INTEGERIZATION_SCALING_BITS    4   // 12-0+1 = 13. And I give one more bit. The actuall SCALING_MAX is 15

#define LLMB_QUANTSTEPSIZE_B4_PLLM          1
#define LLMB_QUANTSTEPSIZE_B4_PLLM_MIN      1
#define LLMB_QUANTSTEPSIZE_B4_PLLM_MAX      128
#define LLMB_QUANTSTEPSIZE_B4_PLLM_BITS     8   // we give one more bit. The actuall MAX is 2^8 = 256

// I don't know how to define an array. I just hard coded them in msaudio.c files.
// Search LLMB_CLMS_ORDERS[LLMB_CLMS_TTL] in msaudio.c
//LLMB_CLMS_ORDERS[LLMB_CLMS_TTL] = { 600, 60 , 6};
//#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_HALF      (WMA_U32)16
//#define LLMB_RESIDUE_MEMORY_TTLWEIGHT           (WMA_U32)32
#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_SCALING   5
//#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_X_2       (WMA_U32)64
//#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_X_1_5      (WMA_U32)48
//#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_X_3       (WMA_U32)96
#define LLMB_RESIDUE_MEMORY_TTLWEIGHT_BITS      3 // 3 bits can support 2^(0-7) = 1-128 scaling.

#define LLMA_RESIDUE_MEMORY_TTLWEIGHT (WMA_U32)32
// V3 LLMB
#define TRANSIENT_POSITION_DELAY 32
#define RESQ_ESCAPE_VALUE   32

// default v3 stereo channel xform
#define INT_SQRT2 362
#define INT_SQRT2_BITS 8
#define FLT_SQRT2 (362.0F / 256.0F)
#define FLT_INV_SQRT2 (1.0F / FLT_SQRT2)
//#define FLT_SQRT2 1.4142135623730950488016887242097F
//#define FLT_INV_SQRT2 0.70710678118654752440084436210485F

// **************************************************************************
// Encoding Options
// **************************************************************************
//v2
#define ENCOPT_BARK             0x0001
#define ENCOPT_V5LPC            0x0020
#define ENCOPT_SUPERFRAME       0x0002
#define ENCOPT_SUBFRAME         0x0004
#define ENCOPT_SUBFRAMEDIVMASK  0x0018
#define ENCOPT_SUBFRAMEDIVSHR   3
//v3
#define ENCOPT3_PURE_LOSSLESS          0x0001
#define ENCOPT3_FRM_SIZE_MOD           0x0006
#define ENCOPT3_SUBFRM_DIV             0x0038
#define ENCOPT3_WRITE_FRAMESIZE_IN_HDR 0x0040
#define ENCOPT3_GENERATE_DRC_PARAMS    0x0080
#define ENCOPT3_RTMBITS                0x0100

// ========================================================================
// v3+ versioning -- use wReserved3 (WORD)
#define ENCOPT4_PLUSVER   0xe000
#define ENCOPT4_PLUSV1    0xc000
#define ENCOPT4_PLUSV1ALT 0x8000
#define ENCOPT4_PLUSV2    0x2000
#define ENCOPT4_PLUSV3    0x4000
// Note: 4/21/06
//       Old decoders  V1 decoders   Vista Beta2  Vista
// 000 : base_only     base_only     base_only    base_only
// 001 : base_only     base_only     v2           v2
// 010 : base_only     base_only     base_only    v2a
// 011 : base_only     base_only     v2           base_only   (can be reused after Vista B2 is time-bomped out)
// 100 : base_only     base_only     base_only    base_only
// 101 : base_only     base_only     v2           base_only   (can be reused after Vista B2 is time-bomped out)
// 110 : base_only     v1            v1           v1
// 111 : base_only     v1            v1+v2*       disallowed  *It will be failed somewhere in decoding

// ========================================================================
// Bits in v1 plus syntax, can reuse these bits if no PLUSV1 in syntax ====

// default number of mv bins
#define ENCOPT4_FEXMVBINS_BITSOFFSET 0
// 3 bits
#define ENCOPT4_FEXMVBINS 0x0007

// default number of sc bins
#define ENCOPT4_FEXSCBINS_BITSOFFSET 3
// 3 bits
#define ENCOPT4_FEXSCBINS 0x0038

// default number of max bands
#define ENCOPT4_FEXMAXBANDS_BITSOFFSET 6
// 3 bits
#define ENCOPT4_FEXMAXBANDS 0x01c0

// ========================================================================
// Bits in v2 plus syntax -- wAdvancedEncodeOpt goes into wReserved3 ======

#define ENCOPT4_PLUSV2_BASEPLUS    0x0001 // 1b
#define ENCOPT4_PLUSV2_RFEX        0x0002 // 1b
#define ENCOPT4_PLUSV2_CHEX        0x0004 // 1b

// Recon domain tile params
#define ENCOPT4_PLUSV2_RTILE_BITSOFFSET       3
#define ENCOPT4_PLUSV2_RTILE       0x0078 // 4b

// Bits in v2 plus syntax -- dwAdvancedEncodeOpt2 goes into dwReserved2
// Chex specific
#define ENCOPT4_PLUSV2_CXLCCHMASK_BITSOFFSET 0
#define ENCOPT4_PLUSV2_CXLCCHMASK 0x00000007 // 3b

// chex max bands
#define ENCOPT4_PLUSV2_CXMAXBANDS_BITSOFFSET 3
#define ENCOPT4_PLUSV2_CXMAXBANDS 0x00000038 // 3b

// used bits 0x    efff --  wReserved3 -  wAdvancedEncodeOpt
//           0x0000003f -- dwReserved2 - dwAdvancedEncodeOpt2
//           0x00000000 -- dwReserved1
#define ENCOPT4_PLUSV2_UNUSEDOPT  0x1000
#define ENCOPT4_PLUSV2_UNUSEDOPT2 0xffffffc0

// Upper limit of buffer size (Bucket buffer, Vbb buffer, cbOutputBuffer)/ Raw PCM size.
// can be changed to 1.1 to save space.
// FrmBucket buffer is Raw PCM size * LLM_BUFSIZE_OVER_RAWPCM. So theoretically, vbb's buffer size
// should be cBitPCM * LLM_BUFSIZE_OVER_RAWPCM + overhead bits. But since we already leave enough
// room in FrmBucket buffer, we are safe.
#define LLM_BUFSIZE_OVER_RAWPCM      2
#define MLLM_BUFSIZE_OVER_RAWPCM     1.5
// This value is also defined in upper layer. For example in liteencoder.
// I hope upper layer can use this define.
#define MAX_PACKET_SIZE             64000

#define MCMASK_MONO   SPEAKER_FRONT_CENTER
#define MCMASK_STEREO (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)
#define MCMASK_THREE  (SPEAKER_FRONT_CENTER | MCMASK_STEREO)
#define MCMASK_BACK   (SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define MCMASK_QUAD   (MCMASK_STEREO | MCMASK_BACK)
#define MCMASK_5      (MCMASK_THREE | MCMASK_BACK)
#define MCMASK_5DOT1  (MCMASK_5 | SPEAKER_LOW_FREQUENCY)
#define MCMASK_6DOT1  (MCMASK_5DOT1 | SPEAKER_BACK_CENTER)
#define MCMASK_7DOT1  (MCMASK_5DOT1 | SPEAKER_FRONT_LEFT_OF_CENTER | SPEAKER_FRONT_RIGHT_OF_CENTER)

/////////////////////////////////////////////////////////////////////////////////////////////////////
#define GetUnalignedWord( pb, w ) \
            (w) = ((WORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedDword( pb, dw ) \
            (dw) = ((DWORD) *(pb + 3) << 24) + \
                   ((DWORD) *(pb + 2) << 16) + \
                   ((DWORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedQword( pb, qw ) \
            GetUnalignedDword( pb, (qw).dwLo ); \
            GetUnalignedDword( (pb + 4), (qw).dwHi );

//#define GetUnalignedDouble( pb, d ) (d) = *(double*)(pb);


#define GetUnalignedWordEx( pb, w )     GetUnalignedWord( pb, w ); (pb) += sizeof(WORD);
#define GetUnalignedDwordEx( pb, dw )   GetUnalignedDword( pb, dw ); (pb) += sizeof(DWORD);
#define GetUnalignedQwordEx( pb, qw )   GetUnalignedQword( pb, qw ); (pb) += sizeof(QWORD);
//#define GetUnalignedDoubleEx( pb, d )   GetUnalignedDouble( pb, d ); (pb) += sizeof(double);

#define LoadBYTE( b, p )    b = *(BYTE *)(p);  (p) += sizeof( BYTE )

#define LoadWORD( w, p )    GetUnalignedWordEx( p, w )
#define LoadDWORD( dw, p )  GetUnalignedDwordEx( p, dw )
#define LoadQWORD( qw, p )  GetUnalignedQwordEx( p, qw )

#define LoadGUID( g, p ) \
        { \
            LoadDWORD( (g).Data1, p ); \
            LoadWORD( (g).Data2, p ); \
            LoadWORD( (g).Data3, p ); \
            LoadBYTE( (g).Data4[0], p ); \
            LoadBYTE( (g).Data4[1], p ); \
            LoadBYTE( (g).Data4[2], p ); \
            LoadBYTE( (g).Data4[3], p ); \
            LoadBYTE( (g).Data4[4], p ); \
            LoadBYTE( (g).Data4[5], p ); \
            LoadBYTE( (g).Data4[6], p ); \
            LoadBYTE( (g).Data4[7], p ); \
        }

////////////////////////////////////////////////////////////////////////////////////////////

// **************************************************************************
// Overridable Compiler Directives
// **************************************************************************
#ifndef PLATFORM_SPECIFIC_INLINE
// This should hopefully work for most compilers. It works for VC
#define INLINE __inline
#endif  // PLATFORM_SPECIFIC_INLINE

#define LSP_CONST16(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
   {LSP_FROM_FLOAT(a),LSP_FROM_FLOAT(b),LSP_FROM_FLOAT(c),LSP_FROM_FLOAT(d),LSP_FROM_FLOAT(e), \
    LSP_FROM_FLOAT(f),LSP_FROM_FLOAT(g),LSP_FROM_FLOAT(h),LSP_FROM_FLOAT(i),LSP_FROM_FLOAT(j), \
    LSP_FROM_FLOAT(k),LSP_FROM_FLOAT(l),LSP_FROM_FLOAT(m),LSP_FROM_FLOAT(n),LSP_FROM_FLOAT(o), \
   LSP_FROM_FLOAT(p)}


#ifndef _SPEAKER_POSITIONS_
#define _SPEAKER_POSITIONS_

#define SPEAKER_FRONT_LEFT              0x1
#define SPEAKER_FRONT_RIGHT             0x2
#define SPEAKER_FRONT_CENTER            0x4
#define SPEAKER_LOW_FREQUENCY           0x8
#define SPEAKER_BACK_LEFT               0x10
#define SPEAKER_BACK_RIGHT              0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER    0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER   0x80
#define SPEAKER_BACK_CENTER             0x100
#define SPEAKER_SIDE_LEFT               0x200
#define SPEAKER_SIDE_RIGHT              0x400
#define SPEAKER_TOP_CENTER              0x800
#define SPEAKER_TOP_FRONT_LEFT          0x1000
#define SPEAKER_TOP_FRONT_CENTER        0x2000
#define SPEAKER_TOP_FRONT_RIGHT         0x4000
#define SPEAKER_TOP_BACK_LEFT           0x8000
#define SPEAKER_TOP_BACK_CENTER         0x10000
#define SPEAKER_TOP_BACK_RIGHT          0x20000
#endif

#define WMAAPI_DEMO_LIMIT 60
#define CALLBACK_BUFFERSIZE WMA_MAX_DATA_REQUESTED*2

#define WMAFileGetInputParam WmaGetDataParam

//***********************************************************************
// Exercising Rapier Special Modes, not everything available all the time
//***********************************************************************
#define DECOPT_CHANNEL_DOWNMIXING      0x00000001
#define DECOPT_DRC                     0x00000002
#define DECOPT_INTERPOLATED_DOWNSAMPLE 0x00000004
#define DECOPT_HALF_TRANSFORM          0x00000008
#define DECOPT_HALF_UP_TRANSFORM       0x00000010
#define DECOPT_2X_TRANSFORM            0x00000020
#define DECOPT_REQUANTTO16             0x00000040
#define DECOPT_DOWNSAMPLETO44OR48      0x00000080
#define DECOPT_LTRTDOWNMIX             0x00000100
#define DECOPT_FLOAT_OUT               0x00000200
#define DECOPT_PCM24_OUT               0x00000400
#define DECOPT_PCM32_OUT               0x00000800
#define DECOPT_IGNOREFREQEX            0x00001000
#define DECOPT_IGNORECX                0x00002000



#define MIN_OBJECT_SIZE     24
#define DATA_OBJECT_SIZE    50

#ifndef _WMAERR_DEFINED
#define _WMAERR_DEFINED
typedef int WMAERR;
#endif /* _WMAERR_DEFINED */

#define WMAERR_OK               0
#define WMAERR_FAIL             1
#define WMAERR_INVALIDARG       2
#define WMAERR_BUFFERTOOSMALL   3
#define WMAERR_INVALIDHEADER    4
#define WMAERR_OUTOFMEMORY      5
#define WMAERR_CORRUPTDATA      6
#define WMAERR_NOTDONE          7 /* need more data to finish the work */
#define WMAERR_INVALIDSTATE     8

#define WMA_NONSDMI_LIC 0x02
#define WMA_SDMI_LIC    0x10
#define WMA_BURNCD_LIC  0x08


#define WMA_MAX_DATA_REQUESTED  1024
#define WMA_MAX_METADATA_LEN    1024     // Max length (in bytes) of any metadata field - note that metadata is WCHAR, so use even numbers
                                        // We will truncate incoming metadata to this length (and skip past the remaining data).
                                        // If you want to support max allowable size, set this to 65535 (0xFFFF).

#define NONSUPER_WRAPAROUND 1024
#define SINCOSTABLE_ENTRIES 65

#if defined(BUILD_INTEGER)
typedef tWMA_I32 MaskPowerType;
#define MASK_POWER_FRAC_BITS 28
#define MASK_POWER_SCALE (1<<MASK_POWER_FRAC_BITS)
#define MASK_POWER_FROM_FLOAT(flt) ((MaskPowerType)((flt)*MASK_POWER_SCALE))

typedef tWMA_I32 DBPowerType;
#define DBPOWER_FRAC_BITS QUANTSTEP_FRACT_BITS
#define DBPOWER_FROM_FLOAT(flt) ((DBPowerType)((flt)*(1<<DBPOWER_FRAC_BITS)))
#endif

#define MASK_MINUS_POWER_TABLE_SIZE 72
#  define MASK_PLUS_POWER_TABLE_SIZE 62



#define DBPOWER_TABLE_SIZE   128
#define DBPOWER_TABLE_SIZEV3 192
#define INTEGER_DBPOWER_TABLE_SIZEV3 (187)
#define DBPOWER_TABLE_OFFSET  18

#define INVQUADROOT_FRACTION_TABLE_LOG2_SIZE 8
#define INVQUADROOT_FRACTION_TABLE_SIZE (1<<INVQUADROOT_FRACTION_TABLE_LOG2_SIZE)

#define INVERSE_FRACTION_TABLE_LOG2_SIZE 8
#define INVERSE_FRACTION_TABLE_SIZE (1<<INVERSE_FRACTION_TABLE_LOG2_SIZE)

#define SQRT_FRACTION_TABLE_LOG2_SIZE 8
#define SQRT_FRACTION_TABLE_SIZE (1<<SQRT_FRACTION_TABLE_LOG2_SIZE)



#   define BITS_LP_SPEC_POWER 64
#   define FRACT_BITS_LP_SPEC_POWER 30
#   define QR_FRACTION_FRAC_BITS 24
#   define QR_EXPONENT_FRAC_BITS 29



#endif

