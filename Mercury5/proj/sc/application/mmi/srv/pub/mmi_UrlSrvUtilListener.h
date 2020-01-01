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
* @file    UrlSrvUtilListener.h
* @brief   Define the inetrfaces for url service listener
*          
*          
*/

#ifndef __MMI_URL_SRV_UTIL_LISTENER_H__
#define __MMI_URL_SRV_UTIL_LISTENER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

typedef void* UrlSrvListenerHdl_t;

typedef enum
{
	SRV_LISTENER_TYPE_NOTIFY_FIRST,
	SRV_LISTENER_TYPE_NOTIFY_LAST,
	SRV_LISTENER_TYPE_NOTIFY_ALL,
	SRV_LISTENER_TYPE_NUM
}UrlSrvListenerType_e;

typedef enum
{
	SRV_REGISTER_TYPE_TO_HEAD,
	SRV_REGISTER_TYPE_TO_TAIL,
	SRV_REGISTER_TYPE_TO_NUM
}UrlSrvListenerRegTo_e;

typedef boolean (*UrlSrvListenerCmpCb)(void *pvCurClient, void *pvRefClient, void *pvCusData);
typedef boolean (*UrlSrvListenerCheckEvtCb)(u16 uEvt, void *pvEvtParm, void *pvOwner, void *pvCusData);
typedef boolean (*UrlSrvListenerNotifyCb) (u16 uEvt, void *pvEvtParm, void *pvOwner, void *pvCusData);
typedef void    (*UrlSrvListenerFreeClientCb)(void *pvClient);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvListenerCreate
* @brief      Create the handle to listener
*
* @param[in]  eType         Type for listener
* @param[in]  pfnCbCompare  Compare function for listener
* @param[in]  pvCusData     User data for listener
*
* @retval     Handle to listener
*
*/
UrlSrvListenerHdl_t UrlSrvListenerCreate
(
  UrlSrvListenerType_e eType,
  UrlSrvListenerCmpCb pfnCbCompare, 
  void *pvCusData
);

/** UrlSrvListenerDestroy
* @brief      Destroy the handle to listener
*
* @param[in]  pListener     Handle to the listener
*
* @retval     None
*
*/
void UrlSrvListenerDestroy
(
  UrlSrvListenerHdl_t pListener
);

/** UrlSrvListenerDestroyEx
* @brief      Destroy the handle to listener
*
* @param[in]  pListener       Handle to the listener
* @param[in]  pfnFreeClientCb Free all the registered client
*
* @retval     None
*
*/
void UrlSrvListenerDestroyEx
(
  UrlSrvListenerHdl_t pListener,
  UrlSrvListenerFreeClientCb pfnFreeClientCb
);

/** UrlSrvListenerRegister
* @brief      Register client
*
* @param[in]  pListener       Handle to the listener
* @param[in]  eInsertTo       Type for listener
* @param[in]  pvClient        The client you want to register  
* @param[in]  pfnCbCheckEvt   When event notifying, pfnCbCheckEvt will determine whether pfnCbNotify will be called
* @param[in]  pfnCbNotify     
*
* @retval     None
*
*/
void UrlSrvListenerRegister
(
  UrlSrvListenerHdl_t pListener,
  UrlSrvListenerRegTo_e eInsertTo,
  void *pvClient,
  UrlSrvListenerCheckEvtCb pfnCbCheckEvt,
  UrlSrvListenerNotifyCb pfnCbNotify
);

/// De-Register client
void *UrlSrvListenerDeregister
(
  UrlSrvListenerHdl_t pListener, 
  void *pvClient
);

/// Notifying client
boolean UrlSrvListnerNotify
(
  UrlSrvListenerHdl_t pListener, 
  u16 uEvt,
  void *pvEvtParm
);

void UrlSrvListenerDeRegisterAll
(
  UrlSrvListenerHdl_t pListener, 
  UrlSrvListenerFreeClientCb pfnFreeClientCb
);

/// Check whether the client registers or not
boolean UrlSrvListenerIsRegister
(
  UrlSrvListenerHdl_t pListener, 
  void *pvClient
);

#endif/* __MMI_URL_SRV_UTIL_LISTENER_H__ */
