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
* @file    UrlSrvClientInternal.h
* @brief   Define the Internal APIs for Url Service Client 
*          
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_INTERNAL_H__
#define __MMI_URL_SRV_CLIENT_INTERNAL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvCommon.h"
#include "mmi_UrlSrvCommonCommItf.h"

#include "mmi_srv_client_commondefine.h"


/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*UrlSrvGetRspExecDataCb)(void **ppvExecData);
typedef void (*UrlSrvRspPreExecCb)(void *pvExecData);
typedef void (*UrlSrvRspPostExecCb)(void *pvExecData);
typedef void (*UrlSrvRspProcessDataCb)(void *pvAppObj, void *pvWrapperData, UrlSrvUrlHdl_t pUrlObj);
typedef bool (*UrlSrvRspCheckExec)(void *pvWrapperData);

typedef struct
{
    UrlSrvGetRspExecDataCb pfnGetRspExecDataCb;
    UrlSrvRspProcessDataCb pfnProcessDataCb;
    UrlSrvRspCheckExec     pfnRspCheckExecCb;
    UrlSrvRspPreExecCb     pfnRspPreExecCb;
    UrlSrvRspPostExecCb    pfnRspPostExecCb;
}UrlSrvClientRspExecInfo_t;

typedef struct
{
	UrlSrvUrlHandlerInfo_t sUrlHandlerInfo; /// trick: put SRV_UrlHandlerInfo_t in the first field, 
	                                        ///        it's used in _SRV_Task_Srv_IsAddUrlHandlerReqEqual
	u16 uSrcMbx;
	u16 uDstMbk;
}UrlSrvClientUrlHandlerWrapper_t;

typedef struct
{
	UrlSrvUrlRspInfo_t sUrlResponseInfo;
	u16 uSrcMbx;
	u16 uDstMbk;
	void *pvRspExecData;
    boolean bLaunchOk;
    void *pvAppObj;
}UrlSrvClientUrlRspCbWrapper_t;

typedef struct
{
	u8 uMsTaskId;                           /// rtk's task id
	UrlSrvTaskCommItf_t sCommItf;           /// task's communication interface
	UrlSrvClientRspExecInfo_t sRspExecInfo; /// task's response callback pre/post exec hook
}UrlSrvClientInfo_t;

extern UrlSrvClientInfo_t gUrlSrvClientTaskInfo[SRV_CLIENT_TASK_ID__NUM];

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/// Internal Function ( Protected )
/// Share by UrlSrvClient.h & UrlSrvHelper.h

/** _UrlSrvClientGetCurTaskId
* @brief      Get current task's Srv_TaskId_e
*
* @param      None
*
* @retval     Task id
*
*/
__SLDPM_FREE__ Srv_TaskId_e _UrlSrvClientGetCurTaskId(void); 

/** _UrlSrvClientUrlRspCbWrapper
* @brief      Handler for url handler wrapper
*
* @param[in]  pUrl             Request url object
* @param[in]  pvUserData       User data
* @param[in]  psResponseInfo   Response information
*
* @retval     None
*
*/
boolean _UrlSrvClientUrlHandlerCbWrapper(UrlSrvUrlHdl_t pUrl, void *pvUserData, void **ppvLaunchObj, UrlSrvUrlRspInfo_t *psResponseInfo);

/** _UrlSrvClientUrlDataRspCbWrapper
* @brief      Handler for url response callback wrapper
*
* @param[in]  pvUserData          User data in response callback information
* @param[in]  nRspCode            result code
* @param[in]  pvRspData           response data
* @param[in]  pfnRspDataFreeCb    free function for response data
*
* @retval     None
*
*/
void _UrlSrvClientUrlDataRspCbWrapper(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, UrlSrvRspDataFreeCb pfnRspDataFreeCb);


/** _UrlSrvClientUrlLaunchCbWrapper
* @brief      Handler for url response callback wrapper
*
* @param[in]  pvUserData          User data in response callback information
* @param[in]  nRspCode            result code
* @param[in]  pvRspData           response data
* @param[in]  pfnRspDataFreeCb    free function for response data
*
* @retval     None
*
*/
void _UrlSrvClientUrlLaunchCbWrapper(void *pvUserData, MAE_Ret nRspCode);


/** _UrlSrvClientSendMsg
* @brief      Send message to server task
*
* @param[in]  pvMsg Message you want to send
*
* @retval     None
*
*/
void _UrlSrvClientSendMsg(void *pvMsg);

/** _UrlSrvClientGetCurTaskMbx
* @brief      Get current task's mailbox
*
* @param      None
*
* @retval     Mailbox for current task
*
*/
__SLDPM_FREE__ u16 _UrlSrvClientGetCurTaskMbx(void);

/** _UrlSrvClientGetTaskMbx
* @brief      Get task's mail box
*
* @param[in]  eTaskId Task's Id
*
* @retval     Mailbox for this task
*
*/
__SLDPM_FREE__ u16 _UrlSrvClientGetTaskMbx(Srv_TaskId_e eTaskId);

void _UrlSrvClientWrapperMemAddRef(void *pvWrapperData);

void _UrlSrvClientFreeWrapperData(void *pvWrapperData);

#endif/* __MMI_URL_SRV_CLIENT_INTERNAL_H__ */

