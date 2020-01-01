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
* @file ABL_Gps.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of GPS.
*
*/

#ifndef __ABL_GPS_H__
#define __ABL_GPS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "srv_ResMgr_Gps.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_GpsParseExecRes(s16 sResult);
void ABL_GpsInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_GpsFreeCusData(void *pCusData);
void ABL_GpsGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
#endif //__ABL_GPS_H__
