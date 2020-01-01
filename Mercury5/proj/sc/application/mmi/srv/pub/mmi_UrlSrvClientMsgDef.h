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
* @file    UrlSrvClientMsgDef.h
* @brief   define the the message structs in Url Service Client
*          
*/

#ifndef __MMI_URL_SRV_CLIENT_MSG_DEF_H__
#define __MMI_URL_SRV_CLIENT_MSG_DEF_H__


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvClientHelper.h"

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/****************************************************************************/
/*  Message :       URL_SRV_HANDLE_URL_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Server To Url Service Client                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvHandleUrlReq_t                                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
	UrlSrvUrlHdl_t pUrl;
	UrlSrvUrlHandlerInfo_t sUrlHandlerInfo;
	UrlSrvUrlRspInfo_t sResponseInfo;
	boolean *pbContinue; /// used only when sUrlHandlerInfo.eHandlerType == SRV_URLHANDLER_TYPE_HOOK
}UrlSrvHandleUrlReq_t;


/****************************************************************************/
/*  Message :       URL_SRV_HANDLE_URL_RSP                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Client To Url Service Client                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvHandleUrlDataRsp_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    void *pvFreeWrapperData;
	void *pvRspExecData;
	void *pvRspData;
	MAE_Ret nRspCode;
	UrlSrvRspDataFreeCb pfnRspDataFreeCb;
	UrlSrvUrlRspInfo_t sResponseInfo;
}UrlSrvHandleUrlDataRsp_t;


/****************************************************************************/
/*  Message :       URL_SRV_HANDLE_URL_RSP                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Client To Url Service Client                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvHandleUrlLaunchRsp_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct  
{
    void *pvFreeWrapperData;
    void *pvRspExecData;
    MAE_Ret nRspCode;
	UrlSrvUrlRspInfo_t sResponseInfo;
}UrlSrvHandleUrlLaunchRsp_t;


/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* __MMI_URL_SRV_CLIENT_MSG_DEF_H__ */

