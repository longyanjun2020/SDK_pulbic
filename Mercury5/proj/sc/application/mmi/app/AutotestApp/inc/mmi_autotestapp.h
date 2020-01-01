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
* @file    mmi_calibrationapp.h
* @version
* @brief   Calibration applet header file
*
*/

#ifndef __MMI_AUTOTESTAPP_H__
#define __MMI_AUTOTESTAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#ifdef __FT_AUTO_TEST__
#include "mmi_mae_applet.h"
#include "mmi_srv_header.h"

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
// Global function definition
/*=============================================================*/

MAE_Ret AutotestAppNew(MAE_ClsId id, void **ppObj);
void AutotestAppPreNew(void);

#endif //__FT_AUTO_TEST__
#endif /* __MMI_AUTOTESTAPP_H__ */
