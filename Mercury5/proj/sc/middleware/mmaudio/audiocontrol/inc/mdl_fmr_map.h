////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
* @file    mdl_fmr_map.h
* @version
* @brief   This module defines the FM radio player controller header
*
*/

#ifndef MDL_FMR_MAP_H
#define MDL_FMR_MAP_H

#if defined(__FM_PEQ_ENABLE__) || defined(__ATV_PEQ_ENABLE__)
/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_msgof.hc"
#include "mdl_fmr_handle.h"

/*=============================================================*/
// Struct
/*=============================================================*/
typedef struct
{
    s32 FMAPP_Ch;
    s32 FMAPP_Samplesize;     //one channels sample unit
    s32 FMAPP_samplingrate;
    s32 FMAPP_DMAPlayerOverrun;
    s32 FMAPP_StartPlay;
    s32 FMAPP_AccumSize;    //accumulation for detect start play
    u8 *FMAPP_pIOBuffer;
    u8 *FMAPP_pDMAPcmBuffer;
    u8 *FMAPP_pDMAPlayerBuffer;
    MdlFmrErrCode_e errcode; //Use for debug Ram Dump state
    u8   FMAPP_StartRecord;
    MdlAudType_e FMAPP_AudioType;
    
}FMPlayerPara_t;

/*=============================================================*/
// function definition
/*=============================================================*/

extern MsTaskId_e nFMPlayerTaskId;
#define MDL_FMR_MAP_MBX nFMPlayerTaskId

void FMPlayerInit(void *taskdata);
void FMPlayerParseMsg(vm_msg_t *pMessage);
MdlFmrErrCode_e _MdlAudioPPTaskCreate(void);
MdlFmrErrCode_e _MdlAudioPPTaskDestory(void);
static MdlFmrErrCode_e _MdlStartAudioPP(void *pInst);

static void _MdlFMAudFullCb(void);
static void _MdlFMAudOverrunCb(void);
static void _MdlFMAudUnderrunCb(void);
static MdlFmrErrCode_e _fnFMPlayerBufGet(void *pInst);
static MdlFmrErrCode_e _fnFMPlayerProcessData(void *pInst);
static MdlFmrErrCode_e _fnFMPlayerFreeMemory(void *pInst);
static MdlFmrErrCode_e _fnFMPlayerStartDMA(void *pInst);
static MdlFmrErrCode_e _fnFMPlayerPushToDMA(void *pInst);
static MdlFmrErrCode_e _fnFMPlayerPushToRecRB(u8* u8PushData);

#endif
#endif
