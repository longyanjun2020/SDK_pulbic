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
 * @file cust_backlight.h
 * @brief
 */
#ifndef __CUST_BACKLIGHT_H__
#define __CUST_BACKLIGHT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_backlight_types.h"
#include "cust_gpio_sddl.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define BACKLIGHT_CONFIG_CONST __attribute__((section("cust_backlight_functable"))) const
#define SUBBACKLIGHT_CONFIG_CONST __attribute__((section("cust_subbacklight_functable"))) const
#define BREATHLIGHT_CONFIG_CONST __attribute__((section("cust_breathlight_functable"))) const

#define WLED_LEVEL_COUNT 64

#define _TRACE(...)

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    DrvBacklightErrCode_e  (*init)(void);
    DrvBacklightErrCode_e  (*probe)(void);	
    DrvBacklightErrCode_e  (*SetBacklightlLevel)(u16 nLevel, u16 nCurLevel);
    DrvBacklightErrCode_e  (*BacklightSingleStep)(void);
    u16                    (*BacklightGetStrInfo)(u8 id, char *pStr, u16 maxLen);
   	u32                    backlightLevelCount;
}CusBacklightInterfaceTable_s;

typedef struct
{
    DrvBacklightErrCode_e  (*init)(void);
    DrvBacklightErrCode_e  (*probe)(void);	
    DrvBacklightErrCode_e  (*SetBacklightlLevel)(u16 nLevel, u16 nCurLevel);
    DrvBacklightErrCode_e  (*BacklightSingleStep)(void);
    u16                    (*BacklightGetStrInfo)(u8 id, char *pStr, u16 maxLen);
   	u32                    backlightLevelCount;
}CusSubBacklightInterfaceTable_s;

typedef struct
{
    DrvBacklightErrCode_e  (*init)(void);
    DrvBacklightErrCode_e  (*probe)(void);	
    DrvBacklightErrCode_e  (*SetBreathlightlLevel)(u16 nLevel);
    DrvBacklightErrCode_e  (*SetBreathlightlExtendLevel)(u32 nLevel, u32 nLevel2);
    DrvBacklightErrCode_e  (*BreathlightSingleStep)(void);
    u16                    (*BreathlightGetStrInfo)(u8 id, char *pStr, u16 maxLen);
   	u32                    BreathlightLevelCount;
}CusBreathlightInterfaceTable_s;
#endif // __CUST_BACKLIGHT_H__

