/**
* @file ResMgr_AppStgr.h
*
* This header file defines the interface of resource manager 
* application strategier
*/

#ifndef __RESMGR_APPSTGR_H__
#define __RESMGR_APPSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_AsyncStgr.h"
#include "StateMachineItf.h"
#include "ListenerItf.h"
#include "ResMgr_AppListenerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_AppStgr_t_
{
    ResMgr_AsyncStgr_t tAsyncStgr;
    StateMachine_t tStateMachine;
    MediatorClient_t *pMediatorClient;
    AppMbxEvtParms_t *pAppMbx;
    ListenerHdl_t pAppListenerHdl;
    AppListenerItf_t *pListenerItf;
} ResMgr_AppStgr_t;

typedef enum AppStgrStates_e_
{
    APP_STGR_STATE__IDLE,
    APP_STGR_STATE__WAIT_RSP,
    APP_STGR_STATE__NUM
} AppStgrStates_e;

typedef enum AppStgrSmEvt_e_
{
    APP_STGR_SM_EVT__CMD,
    APP_STGR_SM_EVT__RSP,
    APP_STGR_SM_EVT__NUM
} AppStgrSmEvt_e;

typedef struct AppStgrEvtInfo_t_
{
    AppStgrSmEvt_e eEvt;
    void *pInfo;
} AppStgrEvtInfo_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
void ResMgrAppStgr_Init(CmdMgrStgrHdl_t pHandle, ResMgrCommItf_t *pCommItf);
void ResMgrAppStgr_Uninit(CmdMgrStgrHdl_t pHandle);
void ResMgrAppStgr_Send(CmdMgrStgrHdl_t pHandle, u32 uTypeMsg, void *pMsgBody);

#endif //__RESMGR_APPSTGR_H__

