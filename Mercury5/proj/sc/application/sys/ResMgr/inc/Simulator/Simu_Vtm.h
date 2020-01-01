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
* @file Simu_Vtm.h
*
* This header file defines the interface of lower layer device simulation for video telephony
*
*/
#ifndef __SIMU_VTM_H__
#define __SIMU_VTM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Vtm.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_VtmOpenCb(void *pUserData);
void Simu_VtmCloseCb(void *pUserData);
void Simu_VtmStartCb(void *pUserData);
void Simu_VtmStopCb(void *pUserData);
void Simu_VtmSetConfigCb(void *pUserData);
void Simu_VtmStartRecordCb(void *pUserData);
void Simu_VtmStopRecordCb(void *pUserData);
void Simu_VtmSaveRecordFileCb(void *pUserData);
void Simu_VtmDiscardRecordFileCb(void *pUserData);
void Simu_VtmAbortSavingFileCb(void *pUserData);
#endif
