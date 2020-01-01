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
* @file mmi_vtmsrv_priv.h
*
* Class Id: CLSID_VTMSRV
*
* @version $Id:
*/
/*=============================================================*/
// Include Files
/*=============================================================*/
#ifdef __VT_3G324M__	

#ifndef __MMI_VTMSRV_PRIV_H__
#define __MMI_VTMSRV_PRIV_H__
#include "mmi_mae_common_def.h"
#include "mmi_vtmsrv.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Variable Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
static u32 _VtmSrvAddRef(IVTMSRV *pIVtmSrv);
static u32 _VtmSrvRelease(IVTMSRV *pIVtmSrv);
static MAE_Ret _VtmSrvQueryInterface(IVTMSRV *pIVtmSrv, MAE_IId nId, void **ppObj, IBase *pOwner);
static boolean _VtmSrvHandleEvent(IVTMSRV *pIVtmSrv, MAE_EventId nEventID, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Private Function Implementations
/*=============================================================*/
static void _VtmSrvConfigSetItem(VtmSrv_t *pVtmSrv, boolean bOsdOn);
static void _VtmSrvPackCnfCb(VtmSrv_t *pVtmSrv, u32 nSrvClientInstId, void *pfnClientCb, ABL_VtmCb pfnCb, ABL_VtmCb_t *pVtmCb);
static void _VtmSrvCmnCbExt(u32 nUserValue, VtmSrvErrCode_e nSrvErrCode);
static VtmSrvErrCode_e _VtmSrvRemapErrCode(ABL_VtmErrCode_e eAblErrCode);
static void _VtmSrvOpenCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvStartCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvStopCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvCloseCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvSetConfigCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvStartRecordCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvStopRecordCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvSaveRecordFileCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvDiscardRecordFileCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvAbortSavingFileCb(u16 senderID, u32 nUserValue, ABL_VtmErrCode_e eErrCode, ABL_VtmRspData_t *pVtmRspData);
static void _VtmSrvInterruptNotifyCb(u32 nCusData, void *pNotifyInfo);
static void _VtmSrvNotifyCb(u32 nCusData, void *pNotifyInfo);

#endif //__MMI_VTMSRV_PRIV_H__

#endif //#ifdef __VT_3G324M__

