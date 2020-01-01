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
* @file    sim_bt_task_priv.h
* @version
* @brief
*
*/

#if defined (__BLUETOOTH__) && defined (__SDK_SIMULATION__)

#ifndef __SIM_BT_TASK_PRIV_H__
#define __SIM_BT_TASK_PRIV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*
The timer IDs for Simulated BT Task
*/
typedef enum
{
    SIMBT_TIMER_INQUIRY_STOP = 0
    ,SIMBT_TIMER_INQUIRY_DEVICE
    ,SIMBT_TIMER_INQUIRY_NUM
    ,SIMBT_TIMER_SEND_FILE
    ,SIMBT_TIMER_RECV_FILE
} SIMBT_TimerID_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


/* Customize the behaviour of simulated BT task*/
void SimBTSetInquiryParams(u32 nInquiryTimer, bool bNoDevice);
void SimBTInit();
void SimBTParser(void *pReceivedMsg);


/*=============================================================*/
// Variable Declarations
/*=============================================================*/

#endif //__SIM_BT_TASK_PRIV_H__

#endif //__SDK_SIMULATION__ && __BLUETOOTH__
