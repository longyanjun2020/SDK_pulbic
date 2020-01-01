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
* @file    UrlSrvServer.h
* @brief   define the message id
*          
*/

#ifndef __MMI_URL_SRV_SERVER_H__
#define __MMI_URL_SRV_SERVER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvServerMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/


/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvServerInit
* @brief      Init url service info for server task
*
* @param      None
*
* @retval     None
*
*/
void UrlSrvServerInit(void);

/** UrlSrvServerUnInit
* @brief      Uninit url service info for server task
*
* @param      None
*
* @retval     None
*
*/
void UrlSrvServerUnInit(void);

/** UrlSrvServerMsgParser
* @brief      Parser for url service server
*
* @param[in]  pvMsg  Message to be parsed
*
* @retval     None
*
*/
MAE_Ret UrlSrvServerMsgParser(void *pvMsg);

/** UrlSrvServerInit
* @brief      Get the handle to server manager
*
* @param      None
*
* @retval     None
*
*/
UrlSrvServerMgrHdl_t UrlSrvServerGetMgr(void);

#endif/* __MMI_URL_SRV_SERVER_H__ */
