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

#ifndef __MMI_URL_SRV_SERVER_MSG_DEF_H__
#define __MMI_URL_SRV_SERVER_MSG_DEF_H__


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_srv_client_commondefine.h"
#include "mmi_UrlSrvClientHelper.h"
#include "mmi_UrlSrvCommonSchemeTbl.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/****************************************************************************/
/*  Message :       URL_SRV_ADD_URL_HANDLER_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Client To Url Service Server                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvAddUrlHandlerReq_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
#define SRV_MAX_SCHEME_LEN SRV_MAX_URL_SCHEME_LEN

typedef struct
{
    MAE_WChar strScheme[SRV_MAX_SCHEME_LEN];
    UrlSrvUrlHandlerInfo_t sUrlHandlerInfo;
    UrlSrvRegHdlrRspInfo_t sAddUrlHdlrCbInfo;
}UrlSrvAddUrlHandlerReq_t;


/****************************************************************************/
/*  Message :       URL_SRV_OVERRIDE_URL_HANDLER_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Client To Url Service Server                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvAddUrlHandlerReq_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
    boolean bOverride;
    MAE_WChar strScheme[SRV_MAX_SCHEME_LEN];
    UrlSrvUrlHandlerInfo_t sUrlOldHdlrInfo;
    UrlSrvUrlHandlerInfo_t sUrlNewHdlrInfo;
    UrlSrvRegHdlrRspInfo_t sOverrideUrlHdlrCbInfo;
}UrlSrvOverrideUrlHandlerReq_t;

/****************************************************************************/
/*  Message :       URL_SRV_DISPATCH_URL_OBJ_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Url Service Client To Url Service Server                    */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : UrlSrvDispatchUrlObjReq_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
	UrlSrvUrlHdl_t pUrl;
	UrlSrvUrlRspInfo_t sUrlResponseInfo;
}UrlSrvDispatchUrlObjReq_t;


/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* __MMI_URL_SRV_SERVER_MSG_DEF_H__ */

