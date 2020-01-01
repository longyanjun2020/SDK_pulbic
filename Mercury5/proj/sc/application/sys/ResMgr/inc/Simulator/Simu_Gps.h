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
* @file Simu_Gps.h
*
* This header file defines the interface of lower layer device simulation for gps
*
*/
#ifndef __SIMU_GPS_H__
#define __SIMU_GPS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Gps.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct
{
    u16 uTimerId;
    ABL_GpsCb GpsCb;
} Simu_GpsCbRemap_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/

void Simu_GpsOpenCb(void *pUserData);
void Simu_GpsCloseCb(void *pUserData);
void Simu_GpsStartCb(void *pUserData);
void Simu_GpsStopCb(void *pUserData);
void Simu_GpsReadDataCb(void *pUserData);
void Simu_GpsIoctlCb(void *pUserData);
void Simu_GpsChnagePSModeCb(void *pUserData);
#endif