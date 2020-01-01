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
* @file    mmi_fmradioapp.h
* @version
* @brief   Fm radio applet header file
*
*/

#ifndef __MMI_FMRADIOAPP_H__
#define __MMI_FMRADIOAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mediasrv_common.h"
#include "mmi_launcher_fmradio.h"
#include "mmi_srv_scheduler.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define FMR_FREQ_IND__START           MMI_FMRADIOSRV_FREQ_MIN/10
#define FMR_FREQ_IND__END             MMI_FMRADIOSRV_FREQ_MAX/10
#define FMR_FREQ_IND__POS             MMI_FMRADIOSRV_FREQ_MIN/10

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    FmRadioLaunchMode_e eMode;
    u32 nSchId;
} FmRadioLaunchData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret FmRadioAppNew(MAE_ClsId nClsId, void **ppObj);
void FmRadioPreNew(void);

#endif /* __MMI_FMRADIOAPP_H__ */
