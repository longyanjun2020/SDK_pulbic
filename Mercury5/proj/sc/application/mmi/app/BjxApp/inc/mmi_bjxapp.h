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
* @file mmi_bjxapp.h
*
* Class Id: CLSID_BJXAPP
*
* @version $Id$
*/
#ifndef __MMI_BJXAPP_H__
#define __MMI_BJXAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_bjx.h"
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    MmiPhbBookType_e         s32Booktype;    // book type you want to search
    MmiPhbGroup_e             s32PhbGroup;    // group type you want to search
    BjxAppFindContactIdCbInfo_t *pResponseInfo;
} BjxAppStartData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

void BjxPreNew(void);
MAE_Ret BjxAppNew(MAE_ClsId id, void **ppObj);
void BjxAppFreeStartData(IBase *pData, u32 nParam);
#endif /* __MMI_BJXAPP_H__ */
