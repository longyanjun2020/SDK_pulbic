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
* @file mmi_btapp.h
*
* Class Id: CLSID_BTAPP
*
* @version $Id$
*/
#ifndef __MMI_BTAPP_H__
#define __MMI_BTAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_filemgr.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_bt.h"
#include "mmi_launcher_sendvia.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    BTAPP_NONE,
    BTAPP_SEARCH_DEVICES,
    BTAPP_PAIRED_DEVICES_LIST,
    BTAPP_SEND_FILE
} MMI_BTAPP_ENTRY_MODE_e;

typedef struct
{
    MMI_BTAPP_ENTRY_MODE_e Type;

    MAE_WChar             *pwURL; // Full file path for vCal, vCard or vToDo file.
    u16                   u16CurrentSendFile;

    MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE];

    u32 nFileNumber;
    u32 nHandleId;

    /* PR#60331: SendViaApp to trigger BTAPP by URLs, but not Content-IDs */
    VectorClass_t          *pURLList; // List of URL for files, such as Image, Music, Video, etc.
    /* end PR#60331 */
    boolean               bIsNeedDeleteFile;
} MmiBtappRequest_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
void _BtAppCleanFuncFoBtApp(IBase *pIssuer, u32 Param);
void BtPreNew(void);
MAE_Ret BtAppNew(MAE_ClsId id, void **ppObj);
void BtAppFreeStartData(IBase *pOwner, u32 nParam);
void BtAppFreeModelData(void *pItemData, void *pUseData);

#endif /* __MMI_BTAPP_H__ */
