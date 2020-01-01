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
* @file    mmi_calllogapp.h
* @version
* @brief   call log header file
*
*/

#ifndef __MMI_CALLLOGAPP_H__
#define __MMI_CALLLOGAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_calllog.h"
#include "mmi_common_calllog_type.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CallLogAppNew(MAE_ClsId id, void **ppObj);
void CallLogAppPreNew(void);
void CallLogAppFreeStartData(IBase *pOwner, u32 nParam);

#endif /* __MMI_CALLLOGAPP_H__ */
