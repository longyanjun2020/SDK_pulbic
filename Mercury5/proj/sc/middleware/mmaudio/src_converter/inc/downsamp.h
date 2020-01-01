////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _AUD_DOWNSAMP_H_
#define _AUD_DOWNSAMP_H_


//#define __DOWN_MIPS4KE__
#define DOWNSAMPLE_ON_MONTAGE

#if 0
    typedef char              S8;
    typedef unsigned char     U8;
    typedef short             S16;
    typedef unsigned short    U16;
    typedef int               S32;
    typedef unsigned int      U32;
    //typedef int               BOOL;
    typedef long long         S64;

    #define TRUE  1
    #define FALSE 0
#else
#include "vm_types.ht"
//#include "msmComm.h"
#include "mdl_mmaudio_msmerror.h"
#include "sys_vm_dbg.ho"

#ifndef __WAV_BOOL_defined
#define  __WAV_BOOL_defined
typedef bool       BOOL;
#endif
#endif

#define DOWNSAMP_HBF_SHARP_HSTRY_LEN   34 //37 taps
#define DOWNSAMP_HBF_SHARP_COEF_LEN    10

#define DOWNSAMP_HBF_BLUNT_HSTRY_LEN   10 //11 taps
#define DOWNSAMP_HBF_BLUNT_COEF_LEN     4

#define DOWNSAMP_CH_NUM_MAX    2

#define DOWNSAMP_DOWN_NONE     1
#define DOWNSAMP_DOWN_2X       2
#define DOWNSAMP_DOWN_4X       4


typedef struct
{
   void *frmbuf;
   S32 nchans;
   S32 nfrmsz;
   S32 smpfreq;
   void * tmp_buf;
}AIP_COMMON_STRUCT;


typedef struct
{
    // common interface controls
    AIP_COMMON_STRUCT cs;

    // IP specific controls
    S32 mode;
    S32 out_nchans;
    S32 out_nfrmsz;
    S32 out_smpfreq;
    void  *out_frmbuf;

    // IP specific variables
    S16 hbf_blunt_hstry[DOWNSAMP_HBF_BLUNT_HSTRY_LEN * DOWNSAMP_CH_NUM_MAX];
    S16 hbf_sharp_hstry[DOWNSAMP_HBF_SHARP_HSTRY_LEN * DOWNSAMP_CH_NUM_MAX];
} MS_DOWNSAMPLE_STRUCT;

#ifdef __cplusplus
extern "C"
{
#endif

//int AUD_DownSampleInit( void* this_ip );

extern int AUD_DownSampleInit( void *this_ip, S32 channel, S32 framesize, S32 samplerate, void* tmpbuf , S32 mode);

//int AUD_DownSampleProc( void* this_ip );
extern int AUD_DownSampleProc( void *this_ip, void* inbuf, void* outbuf );

#ifdef __cplusplus
}
#endif

#endif
