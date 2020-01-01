///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   srcconvert.h
// @author MStar Semiconductor Inc. ( Created by Jerry Wu )
// @brief  source rate converte
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __AUD_SRC_H__
#define __AUD_SRC_H__

#include "vm_types.ht"

/*=============================================================================
                             Config Define
===============================================================================*/

//========== Plathform ==========
#define SRC_ON_MONTAGE

//============ Print ============
//#define SRC_PRINTF

/*=============================================================================
                             Data Type Define
===============================================================================*/

#if 0
#ifdef SRC_ON_MONTAGE

//#include "shellcfg.h"

#ifdef WIN32
typedef __int64           S64 ;
#else
//typedef long long         S64;
#endif

#else // else SRC_ON_MONTAGE

typedef char              S8;
typedef unsigned char     U8;
typedef short             S16;
typedef unsigned short    U16;
typedef int               S32;
typedef unsigned int      U32;
typedef int               BOOL;

#ifdef WIN32
typedef __int64           S64;
#else
typedef long long         S64;
#endif

#define TRUE  1
#define FALSE 0

#endif // end SRC_ON_MONTAGE

#else

#if 0
typedef char              S8;
typedef unsigned char     U8;
typedef short             S16;
typedef unsigned short    U16;
typedef int               S32;
typedef unsigned int      U32;
typedef bool               BOOL;

#ifdef WIN32
typedef __int64           S64;
#else
typedef long long         S64;
#endif

#define TRUE  1
#define FALSE 0
#else
#include "vm_types.ht"
#include "map_msmError.h"

#ifndef __WAV_BOOL_defined
#define  __WAV_BOOL_defined
typedef bool       BOOL;
#endif
#endif

#endif

/*=============================================================================
                                  SRC Define
===============================================================================*/

/*===================== print message ==================*/
#ifdef SRC_ON_MONTAGE
   #ifdef SRC_PRINTF
   #define SRC_DBG_MSG       diag_printf
   #else
   #define SRC_DBG_MSG(_format_, ...)
   #endif
#else
   #ifdef SRC_PRINTF
   #define SRC_DBG_MSG       printf
   #else
   #define SRC_DBG_MSG(_format_, ...)
   #endif
#endif


/*====================== attribute ====================*/
#if 0
#ifdef WIN32
#define SRC_ATTR_MIPS16
#define SRC_ATTR_MIPS32
#else
#define SRC_ATTR_MIPS16    __attribute__((mips16))
#define SRC_ATTR_MIPS32    __attribute__((nomips16))
#endif
#endif

#define SRC_ATTR_MIPS16
#define SRC_ATTR_MIPS32

/*============== SRC up/down mutliple flag ===============*/
typedef enum {
    SRC_UP_MULTIPLE_1     = 0,
    SRC_UP_MULTIPLE_2     = 1,
    SRC_UP_MULTIPLE_3     = 2,
    SRC_UP_MULTIPLE_4     = 3,
    SRC_UP_MULTIPLE_6     = 5,
    SRC_UP_MULTIPLE_3DIV2 = 6,
    SRC_UP_MULTIPLE_FAILD = 99,
} SRC_MUTLIPLE_FLAG;

typedef enum {
    SRC_MIN_SAMPLERATE     = 0,
    SRC_MAX_SAMPLERATE     = 1,
} SRC_SAMPLERATE_SELECTOR_FLAG;


#define MAX_OUT_SAMPLERATE_SIZE 12
#define MAX_SRC_CHANNEL_SIZE    2

/*================== SRC Interface Strc. =================*/
typedef struct
{
    // IP specific controls
    BOOL  bEn;
    S32   s32ValidOutSamplRateArray[MAX_OUT_SAMPLERATE_SIZE];
    S32   s32ValidOutSamplRateArraySize;
    SRC_SAMPLERATE_SELECTOR_FLAG SelectRule;
}M_SRC_SETTING_STRC;

/*====================== Main Strc. =====================*/

typedef struct
{
    // IP specific controls
    M_SRC_SETTING_STRC src_ctr;

    // IP public variable
    short *pFrmBuf;
    S32    s32ChumN;
    S32    s32In_FrmSz;
    S32    s32In_SmpFreq;

    // IP specific variables
    S32   s32Out_SmpFreq;
    SRC_MUTLIPLE_FLAG mutliple_flag;

    S16 last_14_sample[7 *MAX_SRC_CHANNEL_SIZE*2];
    S16 last_46_sample[23*MAX_SRC_CHANNEL_SIZE*2];
    S16 last_60_sample[30*MAX_SRC_CHANNEL_SIZE*2];
}M_SRC_STRUCTURE;


/*=============================================================================
                                 PEQ Function
===============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

// Setting Data , Interface
BOOL SRC_ATTR_MIPS16 AUD_SRCContInterface_SetPower(void * void_set_stc, BOOL bEn );
BOOL SRC_ATTR_MIPS16 AUD_SRCContInterface_SetSamplingRate(void * void_set_stc, S32 *s32ValidOutSamplRateArray, S32 s32ValidOutSamplRateArraySize);
BOOL SRC_ATTR_MIPS16 AUD_SRCContInterface_SetSelectRule(void * void_set_stc, SRC_SAMPLERATE_SELECTOR_FLAG Rule);

// Main IP
BOOL SRC_ATTR_MIPS16 AUD_SRCMainIP_GetOutputSamplingRate( void * void_src_ip , S32* s32SamplingRate);
BOOL SRC_ATTR_MIPS16 AUD_SRCMainIP_GetOutputSampleSize( void * void_src_ip , S32 proc_input_size_per_ch, S32* proc_out_size_per_ch);
BOOL SRC_ATTR_MIPS16 AUD_SRCMainIP_Init(void * void_src_ip, void * void_set_stc ,
                        S32  s32ChNum ,
                        S32  s32InSamplRate);
BOOL AUD_SRCMainIP_Proc(void * void_src_ip,
                          S16* ps16Insample_buffer , S32  proc_input_size_per_ch,
                          S16* ps16Tmpsample_buffer, S32  proc_tmp_size_per_ch,
                          S16* ps16Outsample_buffer, S32  proc_output_size_per_ch,
						  S32* real_output_size_per_ch);
BOOL AUD_SRCMainIP_CheckAndUpdate( void *void_src_ip , void * void_set_stc );
BOOL SRC_ATTR_MIPS16 AUD_SRCMainIP_Close(void * void_src_ip, void * void_set_stc );

#ifdef __cplusplus
}
#endif
#endif // AUD_SRC

