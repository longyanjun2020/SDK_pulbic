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
* @file mmi_gpssrv_priv.h
*
* Class Id: CLSID_GPSSRV
*
* @version $Id:
*/
/*=============================================================*/
// Include Files
/*=============================================================*/
//#ifdef __GPS_MMI__
#ifndef __MMI_GPSSRV_PRIV_H__
#define __MMI_GPSSRV_PRIV_H__
#include "mmi_mae_common_def.h"
#include "mmi_gpssrv.h"
#include "mmi_coresrv.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct GPSSrv_t_
{
    DECLARE_FUNCTBL(IGPSSRV);
    u32 nRefCnt;
    ICORESRV    *pICoreSrv;
    GPSSrvCusInfo_t *pGPSStatus;
    GPSSrvCusInfo_t *pGPSData;
} GPSSrv_t;
/*=============================================================*/
// Variable Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
static u32 _GPSSrvAddRef(IGPSSRV *pIGPSSrv);
static u32 _GPSSrvRelease(IGPSSRV *pIGPSSrv);
static MAE_Ret _GPSSrvQueryInterface(IGPSSRV *pIGPSSrv, MAE_IId nId, void **ppObj, IBase *pOwner);
static boolean _GPSSrvHandleEvent(IGPSSRV *pIGPSSrv, MAE_EventId nEventID, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Private Function Implementations
/*=============================================================*/

static void _GPSSrvPackCnfCb(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, void *pfnClientCb, ABL_GpsCb pfnCb, ABL_GpsCb_t *pGpsCb);
static ABL_GpsFreq_e _GPSSrvRemapFreq(GPSSrvFreq_e eFreq);
static void _GPSSrvCmnCbExt(u32 nUserValue, GPSSrvErrCode_e nSrvErrCode);
static void _GPSSrvOpenCb(u16 senderID, u32 nUserValue, ABL_GpsErrCode_e eErrCode, ABL_GpsInfo_t *pGpsInfo);
static GPSSrvErrCode_e _GPSSrvRemapErrCode(ABL_GpsErrCode_e eAblErrCode);

#endif //__MMI_GPSSRV_PRIV_H__
//#endif //__GPS_MMI__

