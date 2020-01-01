/**
* @file ResMgr_AppListenerItf.h
*
* This header file defines the interface of Application Listener
*
*/

#ifndef __RESMGR_APPLISTENERITF_H__
#define __RESMGR_APPLISTENERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CtrlItf.h"
#include "ResMgr_CmdMgrStgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void (*ResMgr_ListenEvt)(u32 uCusData, void *pEvtInfo);

typedef enum AppListenerRegType_e_
{
    APP_LISTENER_REG_TYPE__EVT,
    APP_LISTENER_REG_TYPE__EVT_GROUP,
    APP_LISTENER_REG_TYPE__EVT_BY_MASK,
    APP_LISTENER_REG_TYPE__EVT_BY_ACT_GROUP, //Only used for Camera App currently.
    APP_LISTENER_REG_TYPE__NUM
} AppListenerRegType_e;

typedef u16 (*AppListener_GetEvtGroup)(u16 uEvt);
typedef bool (*AppListener_CheckEvtMask)(u16 uEvt, u16 uEvtParm, u32 uMask);
typedef u16 (*AppListener_GetActGroup)(u16 uAct);

typedef struct AppListenerItf_t_
{
    AppListener_GetEvtGroup GetEvtGroup;
    AppListener_CheckEvtMask CheckEvtMask;
    AppListener_GetActGroup GetActGroup;
} AppListenerItf_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
bool AppListener_CompareClient(void *pCurSettings, void *pRefSettings, void *pCusData);
bool AppListener_CompareClientEntirely(void *pCurSettings, void *pRefSettings, void *pCusData);

__SLDPM_FREE__ ResMgr_CtrlReqHandle_t AppListener_CreateRegReq
(
    ResMgr_AppId_e eAppId,
    AppListenerRegType_e eRegType,
    u16 uEvtParm,
    u32 uEvtMask,
    u16 uActGroup,
    ResMgr_ListenEvt ListenEvt,
    u32 uCusData
);

bool AppListener_HandleRegReq(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t AppListener_CreateDeregReq
(
    ResMgr_AppId_e eAppId,
    AppListenerRegType_e eRegType,
    u16 uEvtParm,
    u32 uEvtMask,
    u16 uActGroup,
    ResMgr_ListenEvt ListenEvt,
    u32 uCusData
);

bool AppListener_HandleDeregReq(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t AppListener_CreateConfigReq(ResMgr_ConfigListenerType_e eListenerType);
bool AppListener_HandleConfigReq(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);

#endif //__RESMGR_APPLISTENERITF_H__

