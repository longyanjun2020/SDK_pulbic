#ifndef __SOCKETTASKSTGR_LISTENER_H__
#define __SOCKETTASKSTGR_LISTENER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "SocketTaskStgrListenerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
    ResMgr_AppId_e eAppId;
    SockMgr_ListenEvt ListenEvt;
    bool *pbResult;
    u32 uCusData;
}SockMgrListenerRegReq_t;

typedef struct
{
    ResMgr_AppId_e eAppId;
    bool *pbResult;
    SockMgr_FreeCusDataCb pfnFreeCusCb;
}SockMgrListenerDeRegReq_t;

typedef struct
{
    ResMgr_AppId_e eAppId;
    SockMgr_ListenEvt ListenEvt;
    u32 uCusData;
}SockMgrListenerRegSettings_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* __SOCKETTASKSTGR_LISTENER_H__ */
