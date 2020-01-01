/**
* @file ResMgr_AppListener.h
*
* This header file defines the declaration of Application Listener.
*
*/

#ifndef __RESMGR_APPLISTENER_H__
#define __RESMGR_APPLISTENER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_AppListenerItf.h"
#include "ListenerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct AppListenerRegReq_t_
{
    ResMgr_AppId_e eAppId;
    AppListenerRegType_e eRegType;
    u16 uEvtParm;
    u32 uEvtMask;
    u16 uActGroup;
    ResMgr_ListenEvt ListenEvt;
    u32 uCusData;
} AppListenerRegReq_t;

typedef struct AppListenerDeregReq_t_
{
    ResMgr_AppId_e eAppId;
    AppListenerRegType_e eRegType;
    u16 uEvtParm;
    u32 uEvtMask;
    u16 uActGroup;
    ResMgr_ListenEvt ListenEvt;
    u32 uCusData;
} AppListenerDeregReq_t;

typedef struct AppListenerRegSettings_t_
{
    ResMgr_AppId_e eAppId;
    AppListenerRegType_e eRegType;
    u16 uEvtParm;
    u32 uEvtMask;
    u16 uActGroup;
    ResMgr_ListenEvt ListenEvt;
    u32 uCusData;
} AppListenerRegSettings_t;

typedef struct AppListenerConfigReq_t_
{
    ListenerType_e eType;
} AppListenerConfigReq_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__RESMGR_APPLISTENER_H__
