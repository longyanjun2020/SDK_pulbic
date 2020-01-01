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
* @file    UrlSrvServerMgr.h
* @brief   define the struct for url server manager
*          
*/

#ifndef __MMI_URL_SRV_SERVER_MGR_H__
#define __MMI_URL_SRV_SERVER_MGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvUtilListener.h"
#include "mmi_UrlSrvServerMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
	UrlSrvListenerHdl_t pListener;
}UrlSrvServerMgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* __MMI_URL_SRV_SERVER_MGR_H__ */
