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
* @file srv_ResMgr_RFID.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	applications and MML
*  This header file defines the declaration of operations of RFID.
*
*/

#ifndef __SRV_RESMGR_RFID_H__
#define __SRV_RESMGR_RFID_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "srv_resmgr_mmlrfid_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
MmlErrCode_e ABL_RFID_DriverAPI(MmlRfidUCParam_t *pReq);
MmlErrCode_e ABL_RFID_ListenerRegReq(MmlRfidNotifyCallback_t *pRfidCb);
MmlErrCode_e ABL_RFID_ListenerDeRegReq(MmlRfidNotifyCallback_t *pRfidCb);
#endif //__SRV_RESMGR_AUD_H__

