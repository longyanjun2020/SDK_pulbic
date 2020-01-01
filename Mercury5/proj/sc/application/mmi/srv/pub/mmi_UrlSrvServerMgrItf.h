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
* @file    UrlSrvServerMgrItf.h
* @brief   define the interfaces for url server manager
*          
*/

#ifndef __MMI_URL_SRV_SERVER_MGR_ITF_H__
#define __MMI_URL_SRV_SERVER_MGR_ITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvUtilListener.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* UrlSrvServerMgrHdl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvServerMgrCreate
* @brief      Create the instance to the server manager
*
* @param      None
*
* @retval     None
*
*/
UrlSrvServerMgrHdl_t UrlSrvServerMgrCreate(void);

/** UrlSrvServerMgrDestroy
* @brief      Destroy the instance to the server manager
*
* @param[in]  pSrvMgr    Handle to the server manager
*
* @retval     None
*
*/
void UrlSrvServerMgrDestroy(UrlSrvServerMgrHdl_t pSrvMgr);

/** UrlSrvServerMgrGetListener
* @brief      Get the listener handle to the service manager
*
* @param[in]  pSrvMgr    Handle to the server manager
*
* @retval     None
*
*/
UrlSrvListenerHdl_t UrlSrvServerMgrGetListener(UrlSrvServerMgrHdl_t pSrvMgr);

#endif/* __MMI_URL_SRV_SERVER_MGR_ITF_H__ */
