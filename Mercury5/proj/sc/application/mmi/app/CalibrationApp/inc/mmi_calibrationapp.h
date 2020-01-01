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

#ifndef __MMI_CALIBRATIONAPP_H__
#define __MMI_CALIBRATIONAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_applet.h"
#ifndef __PC_SIMULATOR__
#include "touchscreen.h"
#endif
#include "mmi_srv_header.h"
#include "mmi_launcher_calibration.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define MMI_CALIBRATIONAPP_MAX_DOTS_NUM 3

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
   MMI_CALIBRATIONAPP_START_NORMAL = 0,
   MMI_CALIBRATIONAPP_START_ENGINEER_MODE
} MMI_CALIBRATIONAPP_START_MODE_e;

/* 3 dots: top-left corner / down-right corner / center */
typedef enum
{
   MMI_CALIBRATIONAPP_CORNER_TOP_LEFT = 0,
   MMI_CALIBRATIONAPP_CORNER_BOTTOM_RIGHT,
   MMI_CALIBRATIONAPP_CENTER
} MMI_CALIBRATIONAPP_LOC_e;

typedef struct
{
   s32 NValues;
   s32 XSum;
   s32 YSum;
   Point_t tPoints[MMI_CALIBRATIONAPP_MAX_DOTS_NUM];
#ifdef __MULTI_TOUCH_SLIM__
   Point_t tResistance[MMI_CALIBRATIONAPP_MAX_DOTS_NUM];   
#endif
} Mmi_CalibrationApp_InputPoints_t;

typedef struct
{
   MMI_CALIBRATIONAPP_START_MODE_e eStartMode;
} Mmi_CalibrationApp_StartData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CalibrationAppNew(MAE_ClsId id, void **ppObj);
void CalibrationAppPreNew(void);

#endif /* __MMI_CALIBRATIONAPP_H__ */
