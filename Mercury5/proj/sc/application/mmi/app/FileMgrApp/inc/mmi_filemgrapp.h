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
* @file    mmi_filemgrapp.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_H__
#define __MMI_FILEMGRAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_arraymodel.h"
#include "mmi_common_filemgr_type.h"
#ifdef __BLUETOOTH_MMI__
#include "mmi_btsrv_def.h"
#endif //__BLUETOOTH_MMI__

// TODO: need to turn this on if SrvFileMgr has been implemented

#define __FEATURE_FOLDERBASED_M3U__

#ifdef __MMI_ID3_SUPPORT__
#define __FILEMGRAPP_ID3V2_IMG__
#endif



/**
 * Functions
 */

MAE_Ret FILEMGRAPP_New(MAE_ClsId id, void **ppObj);
void FileMgrAppPreNew(void);
#if defined(__LIVE_WALLPAPER__)
void FileMgrAppPredefinedFileOpRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
void FileMgrAppUserFileOpRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#endif
void FileMgrAppFileOpRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#ifdef __BLUETOOTH_MMI__
void FileMgrAppBtRecvFileCb(void *pUserData, BTSRV_TRANS_RESULT_e eResult);
#endif //__BLUETOOTH_MMI__

#endif /* __MMI_FILEMGRAPP_H__ */
