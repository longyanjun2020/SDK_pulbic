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
* @file    drv_keypad_pub_types.h
* @version
* @brief   Keypad driver interface
*
*/

#ifndef __DRV_KEYPAD_PUB_TYPES_H__
#define __DRV_KEYPAD_PUB_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_keypad_pub_forward.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MAX_HK_KEY_NUM  (3)

#define NB_KBD_COLS 	(8)
#define NB_KBD_ROWS 	(8)

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern const u8 g_KeyCdcFastInit;
extern CusOfnSensitivityLevel_e OfnSensitivity;

/*=============================================================*/
// Data type definition
/*=============================================================*/
opaque_enum(DrvKeyPadErrCode_e_)
{
    KEYPAD_OK,                    /**< Function complete successfully */
    KEYPAD_FAIL,                  /**< Function common fail */
};

opaque_enum(CusOfnSensitivityLevel_e_)
{
    OfnLevel_default = 0, //low
    OfnLevel_2 = 1, //middle
    OfnLevel_3 = 2 //fast
};

struct Cust_KeyTbl_t_
{
  ascii keyName[30];
  u8 nKeyMap[NB_KBD_ROWS][NB_KBD_COLS];
};

/*=============================================================*/
// Global function definition
/*=============================================================*/
extern const Cust_KeyTbl_t g_MSKeyMap[];

#endif /* __DRV_KEYPAD_PUB_TYPES_H__ */




