////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file    mmi_ussdapp.h
 * @version
 * @brief   ussd app
 */

#ifndef __MMI_USSDAPP_H__
#define __MMI_USSDAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_ussd.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define USSDAPP_EVT_Exit                        (CLSID_USSDAPP << 16 | 1)
#define USSDAPP_EVT_ShowProcesScreen            (CLSID_USSDAPP << 16 | 2)
#define USSDAPP_EVT_DisplayUSSD                 (CLSID_USSDAPP << 16 | 3)
#define USSDAPP_EVT_SelectDualSIM               (CLSID_USSDAPP << 16 | 4)
#define USSDAPP_EVT_ShowSSProcessScreen         (CLSID_USSDAPP << 16 | 5)


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret UssdAppNew(MAE_ClsId id, void **ppObj);
void UssdAppPreNew(void);
boolean UssdAppUrlHandlerUssdReq(UrlSrvUrlHdl_t pUrl, void *pvUserData, UrlSrvUrlRspInfo_t *psResponseInfo);

#endif /* __MMI_USSDAPP_H__ */
