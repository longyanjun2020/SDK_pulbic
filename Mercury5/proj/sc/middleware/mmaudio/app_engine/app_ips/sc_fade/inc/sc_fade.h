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
* @file    : sc_fade.h
* @version :
* @author  : Wendy.Lin
* @brief   : Audio Fade in Fade Out
*/

#ifndef __SC_FADE_H__
#define __SC_FADE_H__

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
//#define POST_PROC_FADER_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_FADER_PARSER_PRINTF

/*-------------- Fading Method(Curve) --------------*/
#define FADER_COS_CURVE

/*--------------- Fading Time Bound ----------------*/
#define FADER_MIN_FADINGTIME 0     // ms
#define FADER_MAX_FADINGTIME 1000  // ms

/*============================================================================*/
// Data type definition
/*============================================================================*/
#ifdef POST_PROC_FADER_32BITS_Q8_DATA
typedef tS32 FADER_PROC_DATA_TYPE;
#else
typedef tS16 FADER_PROC_DATA_TYPE;
#endif

/*--------------------- Fade State ----------------------*/
typedef enum
{
    FADE_IN  = 0,
    FADE_OUT = 1
}FADE_DIR_e;

/*--------------------- Fade Coeff. ---------------------*/
typedef struct
{
    tS32 s32Gain;
    tS32 s32Delta;
}FADER_COEFF_s;

/*---------------------- Interface ----------------------*/
typedef struct
{
    tU8  bEn;
    tS32 s32FadeTimeMs;
    tU8  bInitFade;
}M_FADER_PAR_s;
#define SIZEOF_FADER_DATA (sizeof(tU8) + sizeof(tS32) + sizeof(tU8))

typedef struct
{
    M_FADER_PAR_s sFader_Ctr;

    tS32 s32ChumN ;
    tS32 s32SmpFreq;

    tU32 u32GainAccmu ;
    tU32 u32StepSize;

    tS32           bFadeDone;
    FADE_DIR_e    eFadeInOut;

    FADER_COEFF_s psCoeff[1];
}M_FADER_MAIN_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

// Parser
tS32 POSTPROCMGR_ATTR_16BITS AUD_FaderPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_FaderPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_FaderPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_GetPower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_SetFadeTimeMs(void* void_pSet, tS32 s32FadeTimeMs);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_GetFadeTimeMs(void* void_pSet, tS32* ps32FadeTimeMs);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_SetInitFade(void* void_pSet, tU8 bInitFade);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_FaderPar_GetInitFade(void* void_pSet, tU8* pbInitFade);

// Main
tBOOL AUD_FaderMain_UpdateIP(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_FaderMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_FaderMain_Proc(void* void_pIP, FADER_PROC_DATA_TYPE* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_FaderMain_Close(void* void_pIP, void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __SC_FADE_H__ */

