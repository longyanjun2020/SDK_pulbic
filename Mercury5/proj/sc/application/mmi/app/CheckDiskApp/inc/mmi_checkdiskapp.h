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
* @file    mmi_checkdisk.h
* @version
* @brief   BMI header file
*
*/

#ifndef __MMI_CHECKDISKAPP_H__
#define __MMI_CHECKDISKAPP_H__ 

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** CheckDiskNew
* @brief        New function for create CheckDisk Applet
*
* @param[in]    nClsId                 CheckDisk class id
* @param[in]    ppObj               The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail
*
*/
MAE_Ret CheckDiskAppNew
(
    MAE_ClsId   nClsId, 
    void        **ppObj
);

/* This data structure is used for passing the type of embedded mode and the return value of Calendar application. */
typedef struct
{
    u32 nStartMode;
    u32 nStartType;
} CheckDiskModeInfo_t;

/** CheckDiskPreNew
* @brief        New function for create CheckDisk lanucher
*
*/
void CheckDiskAppPreNew(void);

#endif /* __MMI_CHECKDISKAPP_H__ */
