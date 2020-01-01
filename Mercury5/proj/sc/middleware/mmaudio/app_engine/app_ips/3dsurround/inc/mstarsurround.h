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
* @file    : mstarsurround.h
* @version :
* @author  : Stephen.Chen
* @brief   : Basic Surround
*/

#ifndef __MSTAR_SURROUND_H__
#define __MSTAR_SURROUND_H__

/*============================================================================*/
// Include Files
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
//#define POST_PROC_MSTARSURROUND_32BITS_Q8_DATA

/*---------------- Print Message Switch -----------------*/
#define ENABLE_MSTARSURROUND_PARSER_PRINTF

/*-------------------------------------------------------*/
//#define DEF_MONO_BUF

/*-------------------- channel size ---------------------*/
#define MSTARSURROUND_MAX_CH_NUM         (2)
#define MSTARSURROUND_SURROUND_BUFSIZE   (576*2) // in bytes

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_MSTARSURROUND_32BITS_Q8_DATA
typedef tS32 MSTARSURROUND_PROC_DATA_TYPE;
#else
typedef tS16 MSTARSURROUND_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8 bEn;                     // TRUE/FALSE  (1 Bit)   *(2 CHannel) = 2 Bits
}M_MSTARSURROUND_PAR_s;
#define SIZEOF_SURROUND_DATA (sizeof(tU8))


typedef struct
{
    // IP control interface
    M_MSTARSURROUND_PAR_s         sMStarSurround_Ctr;

    // IP public variable
    MSTARSURROUND_PROC_DATA_TYPE* pFrmBuf;
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;
    tU8	 bUpdateFlag;

    // IP private variable
    //tS16  ps16TmpBuf[MSTARSURROUND_SURROUND_BUFSIZE];
    tS16*  ps16TmpBuf;
    tS32  s32writeidx;
    tS32  s32readidx;
    tS32  s32mono_delay;
    tS32  s32stereo_delay;
}M_MSTARSURROUND_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundPar_SetPower(void* void_pSet, tU8 bEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundPar_GetPower(void* void_pSet, tU8* pbEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundMem_Distribute(void* void_pIP, tU8* MemAddr, tS32 s32Size);

// Main
tBOOL                         AUD_MStarSurroundMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundMain_Check(void* void_pIP, void* void_pSet, tU8* bUpdateFlag);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundMain_Update(void* void_pIP, void* void_pSet);
tBOOL                         AUD_MStarSurroundMain_Proc(void* void_pIP, MSTARSURROUND_PROC_DATA_TYPE* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_MStarSurroundMain_Close(void* void_pIP, void* void_pSet );

#ifdef __cplusplus
}
#endif

#endif /* __MSTAR_SURROUND_H__ */

