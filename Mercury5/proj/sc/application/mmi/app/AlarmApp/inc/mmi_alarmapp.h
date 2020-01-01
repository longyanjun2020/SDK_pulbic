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

#ifndef __MMI_ALARMAPP_H__
#define __MMI_ALARMAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_common_util.h"
#include "mmi_launcher_alarm.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/* Type of embedded mode for Alarm application. */
typedef enum
{
    ALARM_EMBEDDEDMODE_UNDEFINED,
    ALARM_EMBEDDEDMODE_VIEWALARM
} AlarmEmbeddedMode_e;

/* This data structure is used for passing the embedded mode info of Alarm application. */
typedef struct
{
    u32                 nAlarmUID;
    AlarmEmbeddedMode_e eEmbeddedMode;
} AlarmEmbedModeInfo_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

void AlarmPreNew(void);
MAE_Ret AlarmAppNew(MAE_ClsId id, void **ppObj);
void AlarmAppFreeStartData(IBase *pIssuer, u32 nParam);

#endif /* __MMI_ALARMAPP_H__ */
