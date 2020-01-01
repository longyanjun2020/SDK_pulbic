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
* @file    : time_stretch.h
* @version :
* @author  : Wendy.Lin(Creator), CA.Wang(Refine)
* @brief   : time stretch
*/

#ifndef __TIME_STRETCH_H__
#define __TIME_STRETCH_H__

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
//#define POST_PROC_TIMESTRETCH_32BITS_Q8_DATA

/*---------------- Print Message Switch -----------------*/
#define ENABLE_TIMESTRETCH_PARSER_PRINTF

/*------------------- Optimize Mode ---------------------*/
#define TIMESTRETCH_OPT

/*-------------------- Quality Mode ---------------------*/
#define TIMESTRETCH_HQSEARCH

#ifdef TIMESTRETCH_HQSEARCH
#define TIMESTRETCH_PMAX 1672  // for 48K
#else
#define TIMESTRETCH_PMAX 1045  // for 48K
#endif
#define TIMESTRETCH_PMIN 192   // for 48K

/*-------------------- Buffer Size ----------------------*/
// Time Stretch Process Buffer Size:
// ((2 * MaxPitch) + ProcSize) *  1 * Sizeof(Sample Type)
// HQ = ((2 * 278) + 160) * 1 * 2
//    = 1432 Bytes
// LQ = ((2 * 174) + 160) * 1 * 2
//    = 1016 Bytes
#define TIMESTRETCH_PRROCESS_SIZE  2048//1152
#define TIMESTRETCH_TIMESTRETCH_PROCBUFSIZE (((TIMESTRETCH_PMAX * 2) + TIMESTRETCH_PRROCESS_SIZE))

/*------------------ Stretch Rate Info. -----------------*/
#define TIMESTRETCH_MIN_RATEIDX (0)
#define TIMESTRETCH_MAX_RATEIDX (12)
#define TIMESTRETCH_RATEIDX_NUM (TIMESTRETCH_MAX_RATEIDX - TIMESTRETCH_MIN_RATEIDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/

/*---------------------- Interface ----------------------*/
typedef struct
{
    tU8 bEn;
    tU8 u8ExpRate;
}M_TIME_STRETCH_PAR_s;
#define SIZEOF_TIME_STRETCH_DATA      (sizeof(tU8) + sizeof(tU8))

typedef struct
{
    M_TIME_STRETCH_PAR_s sTimeStretch_Ctr;

    tU8   bFirstFrm;
    tU8   bUpdateFlag;

    tS32  s32SmpFreq;
    tS32  s32ChumN;

    tS16  s16PMax;
    tS16  s16PMin;
    tS16  s16JumpP;
    tS16  s16InLeftsz;

    // Time Stretch Process Buffer
    //tS16 ps16ProcTmpBuf[TIMESTRETCH_TIMESTRETCH_PROCBUFSIZE];

    tS16* ps16ProcTmpBuf;
}M_TIME_STRETCH_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_GetPower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_SetRate(void* void_pSet, tU8 u8Rate);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimeStretchPar_GetRate(void* void_pSet, tU8* pu8Rate);

// Mem
tBOOL POSTPROCMGR_ATTR_16BITS AUD_TimeStretchMem_Distribute(void* void_pIP, tU8* MemAddr, tS32 s32Size);

// Main
tBOOL AUD_TimeStretchMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_TimeStretchMain_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_TimeStretchMain_Update( void* void_pIP, void* void_pSet);
tBOOL AUD_TimeStretchMain_Proc(void* void_pIP, tS16* ps16ProcBuf_In, tS32* ps32ProcSizePerCh);
tBOOL AUD_TimeStretchMain_Close(void* void_pIP, void * void_pSet);

#ifdef __cplusplus
}
#endif

#endif // __TIMEP_STRETCH_H__

