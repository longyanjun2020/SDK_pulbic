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
* @file GpsFsmItf.h
*
* This header file defines the interfaces of FmRadio States
*
*/

#ifndef __GPSFSMITF_H__
#define __GPSFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum GpsStates_e_
{
    GPS_STATE__IDLE,
    GPS_STATE__INIT,
    GPS_STATE__OPEN,
    GPS_STATE__START,
    GPS_STATE__NUM
} GpsStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t GpsFSM_Init(void *pCusData);
void GpsFSM_Uninit(StateMachineHandle_t pHandle);
bool Gps_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__GPSFSMITF_H__

