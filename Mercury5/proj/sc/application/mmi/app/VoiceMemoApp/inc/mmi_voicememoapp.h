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
* @file    mmi_voicememoapp.h
* @version
* @brief   voicememo applet header file
*
*/

#ifndef __MMI_VOICEMEMOAPP_H__
#define __MMI_VOICEMEMOAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_launcher_voicememo.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    u32 nClient;
    CmnLaunchAppFileOpRspCb pfnRspCb;
} VoiceMemoAppParams_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret VoiceMemoAppNew(MAE_ClsId nClsId, void **ppObj);
void VoiceMemoPreNew(void);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_VOICEMEMOAPP_H__ */
