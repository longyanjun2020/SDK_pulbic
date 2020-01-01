////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    : timepitch_stretch.h
* @version :
* @author  : Wendy.Lin(Creator), CA.Wang(Refine)
* @brief   : time and pitch stretch
*/

#ifndef __TIMEPITCH_STRETCH_H__
#define __TIMEPITCH_STRETCH_H__

/*============================================================================*/
// Include files
/*============================================================================*/
#include "app_datatype.h"

/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*------------------ Process Data Type ------------------*/
//#define POST_PROC_TIMEPITCHSTRETCH_32BITS_Q8_DATA

/*---------------- Print Message Switch -----------------*/
#define ENABLE_TIMESTRETCH_PARSER_PRINTF

/*--------------- Pitch Stretch Function ----------------*/
#if 1//defined(ENABLE_TIMEPITCH_STRETCH)
#define TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
#else
#undef  TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
#endif

/*------------------- Optimize Mode ---------------------*/
#define TIMEPITCHSTRETCH_OPT

/*-------------------- Quality Mode ---------------------*/
#define TIMEPITCHSTRETCH_HQSEARCH

#ifdef TIMEPITCHSTRETCH_HQSEARCH
#define TIMEPITCHSTRETCH_PMAX 1672  // for 48K
#else
#define TIMEPITCHSTRETCH_PMAX 1045  // for 48K
#endif
#define TIMEPITCHSTRETCH_PMIN 192   // for 48K

/*-------------------- Buffer Size ----------------------*/
// Time Stretch Process Buffer Size:
// ((2 * MaxPitch) + ProcSize) *  1 * Sizeof(Sample Type)
// HQ = ((2 * 278) + 160) * 1 * 2
//    = 1432 Bytes
// LQ = ((2 * 174) + 160) * 1 * 2
//    = 1016 Bytes
#define TIMEPITCHSTRETCH_PROCESS_SIZE 1152
#define TIMEPITCHSTRETCH_TIMESTRETCH_PROCBUFSIZE (((TIMEPITCHSTRETCH_PMAX * 2) + TIMEPITCHSTRETCH_PROCESS_SIZE))

#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
// Time Stretch Output Buffer Size:
// ((MaxPitch + (MaxPitch+ ProcSize)) * Max Rate * 1 * Sizeof(Sample Type)
// HQ = (278 + ((278 + 160) * 2)) * 1 * 2
//    = 2308 Bytes
// LQ = (174 + ((174 + 160) * 2)) * 1 * 2
//    = 1684 Bytes
#define TIMEPITCHSTRETCH_TIMESTRETCH_OUTBUFSIZE   (TIMEPITCHSTRETCH_PMAX + ((TIMEPITCHSTRETCH_PMAX + TIMEPITCHSTRETCH_PROCESS_SIZE) * 2))

// SRC FIR Output Buffer Size:
//   (Time Stretch Output Buffer Size) * 2
// HQ = 4616 Bytes
// LQ = 3368 Bytes
#define TIMEPITCHSTRETCH_SRCFIR_OUTBUFSIZE        ((TIMEPITCHSTRETCH_TIMESTRETCH_OUTBUFSIZE * 2))

// HQ : 1432 + 2308 + 4616 = 8356 Bytes 8520
// LQ : 1016 + 1684 + 3368 = 6068 Bytes

#define TIMESTRETCH_TOTAL_BUF_SZ 2*(TIMEPITCHSTRETCH_TIMESTRETCH_PROCBUFSIZE+TIMEPITCHSTRETCH_TIMESTRETCH_OUTBUFSIZE+TIMEPITCHSTRETCH_SRCFIR_OUTBUFSIZE+TIMEPITCHSTRETCH_UPSAMPLE_BACKUPSIZE+TIMEPITCHSTRETCH_DOWNSAMPLE_BACKUPSIZE)

/*---------------------- FIR Filter ---------------------*/

#define TIMEPITCHSTRETCH_UPSAMPLE_TAPS         (16)
// Up + Down Sample Backup Buffer Size : 64 Bytes
#define TIMEPITCHSTRETCH_UPSAMPLE_BACKUPSIZE   (TIMEPITCHSTRETCH_UPSAMPLE_TAPS * 2)

#define TIMEPITCHSTRETCH_DOWNSAMPLE_TAPS       (20)
// Down Sample Backup Buffer Size : 80  Bytes
#define TIMEPITCHSTRETCH_DOWNSAMPLE_BACKUPSIZE (TIMEPITCHSTRETCH_DOWNSAMPLE_TAPS * 2)
#endif

/*------------------ Stretch Rate Info. -----------------*/
#define TIMEPITCHSTRETCH_MIN_RATEIDX (0)
#define TIMEPITCHSTRETCH_MAX_RATEIDX (12)
#define TIMEPITCHSTRETCH_RATEIDX_NUM (TIMEPITCHSTRETCH_MAX_RATEIDX - TIMEPITCHSTRETCH_MIN_RATEIDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/

/*---------------------- Interface ----------------------*/
typedef struct
{
    tU8 bEn;
    tU8 u8ExpRate;
#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
    tU8 u8TypeIdx;
#endif
}M_TIMEPITCH_STRETCH_PAR_s;
#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
#define SIZEOF_TIMEPITCH_STRETCH_DATA (sizeof(tU8) + sizeof(tU8) + sizeof(tU8))
#endif

typedef struct
{
    M_TIMEPITCH_STRETCH_PAR_s sTimePitchStretch_Ctr;

    tU8   bFirstFrm;
    tU8   bUpdateFlag;

    tS32  s32SmpFreq;
    tS32  s32ChumN;

    tS16  s16PMax;
    tS16  s16PMin;
    tS16  s16JumpP;
    tS16  s16InLeftsz;

#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
    tS16  s16SRCPreSamp;
    tS16  s32SRCIntpIdx;
#endif

#if 0
    // Time Stretch Process Buffer
    tS16 ps16ProcTmpBuf[TIMEPITCHSTRETCH_TIMESTRETCH_PROCBUFSIZE];

#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
    // Time Stretch Output Buffer
    tS16 ps16OutTmpBuf[TIMEPITCHSTRETCH_TIMESTRETCH_OUTBUFSIZE];

    // SRC FIR Output Buffer
    tS16 ps16FIROutTmpBuf[TIMEPITCHSTRETCH_SRCFIR_OUTBUFSIZE];

    // SRC UpSample FIR Backup Buffer
    tS16 ps16UpSampleBuf[TIMEPITCHSTRETCH_UPSAMPLE_BACKUPSIZE];

    // SRC DownSample FIR Backup Buffer
    tS16 ps16DownSampleBuf[TIMEPITCHSTRETCH_DOWNSAMPLE_BACKUPSIZE];
#endif
#endif

#if 1
    tS16* ps16ProcTmpBuf;
// Time Stretch Output Buffer
    tS16* ps16OutTmpBuf;

    // SRC FIR Output Buffer
    tS16* ps16FIROutTmpBuf;

    // SRC UpSample FIR Backup Buffer
    tS16* ps16UpSampleBuf;
    //tS16* ps16UpSampleBuf;

    // SRC DownSample FIR Backup Buffer
    tS16* ps16DownSampleBuf;
#endif
}M_TIMEPITCH_STRETCH_MAIN_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

// Parser
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_GetPower(void* void_pSet, tU8* pbEn);
#ifdef TIMEPITCHSTRETCH_APPLY_PITCHSTRETCH
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_SetType(void* void_pSet, tU8 u8TypeIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_GetType(void* void_pSet, tU8* pu8TypeIdx);
#endif
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_SetRate(void* void_pSet, tU8 u8Rate);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchPar_GetRate(void* void_pSet, tU8* pu8Rate);

// Mem
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimePitchStretchMem_Distribute(void* void_pIP, tU8* MemAddr, tS32 s32Size);

// Main
tBOOL AUD_TimePitchStretchMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_TimePitchStretchMain_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_TimePitchStretchMain_Update( void* void_pIP, void* void_pSet);
tBOOL AUD_TimePitchStretchMain_Proc(void* void_pIP, tS16* ps16ProcBuf_In, tS32* ps32ProcSizePerCh);
tBOOL AUD_TimePitchStretchMain_Close(void* void_pIP, void * void_pSet);

#ifdef __cplusplus
}
#endif

#endif // __TIMEPITCH_STRETCH_H__

