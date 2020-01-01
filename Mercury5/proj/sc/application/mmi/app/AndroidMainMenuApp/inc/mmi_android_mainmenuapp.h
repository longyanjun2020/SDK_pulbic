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
* @file    mmi_android_mainmenuapp.h
* @version
* @brief   MainMenu header file
*
*/
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__

#ifndef __MMI_ANDROID_MAINMENUAPP_H__
#define __MMI_ANDROID_MAINMENUAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_android_mainmenuapp_id.h"

typedef struct CellLongPS_TAG
{
    Pos_t tPos;
    u32 eMenuID;
}CellLongPS_t;

MAE_Ret MAINMENUANDROID_New(MAE_ClsId id, void **ppObj);

#endif // __UI_STYLE_MMI_ANDROID_MAIN_MENU__
#endif /* __MMI_ANDROID_MAINMENUAPP_H__ */
