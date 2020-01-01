#ifndef __SOCKETTASKSTGR_LISTENER_ITF_H__
#define __SOCKETTASKSTGR_LISTENER_ITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_Common.h"
#include "ResMgr_CtrlItf.h"
#include "ResMgr_CmdMgrStgrItf.h"
#include "ListenerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*SockMgr_ListenEvt)(u16 uEvt, void *pEvtParm, u32 uCusData);
typedef void (*SockMgr_FreeCusDataCb)(u32 uCusData);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

bool SockMgrListener_CompareClient(void *pvCurSetting, void *pvRefSetting, void *pvCusData);

ResMgr_CtrlReqHandle_t SockMgrListener_CreateRegReq
(
 ResMgr_AppId_e eAppId,
 bool *pbResult,
 SockMgr_ListenEvt ListenEvt,
 u32 uCusData
);

bool SockMgrListener_HandleRegReq
(
 CmdMgrStgrHdl_t pStgrHdl, 
 ResMgr_CtrlHdl_t pCtrlHdl
);

ResMgr_CtrlReqHandle_t SockMgrListener_CreateDeregReq
(
 ResMgr_AppId_e eAppId,
 bool *pbResult,
 SockMgr_FreeCusDataCb pfnFreeCusData
);

bool SockMgrListener_HandleDeregReq
(
 CmdMgrStgrHdl_t pStgrHdl, 
 ResMgr_CtrlHdl_t pCtrlHdl
);

bool SockMgrListener_IsRegister
(
 CmdMgrStgrHdl_t pStgrHdl, 
 ResMgr_AppId_e eApId
);

#endif/* __SOCKETTASKSTGR_LISTENER_ITF_H__ */
