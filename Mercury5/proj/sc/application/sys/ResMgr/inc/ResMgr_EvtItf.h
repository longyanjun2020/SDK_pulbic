/**
* @file ResMgr_EvtItf.h
*
* This header file defines the data structure of resource manager
* control request
*/

#ifndef __RESMGR_EVTITF_H__
#define __RESMGR_EVTITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_RspEvtItf.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ResMgr_EvtType_e_
{
    RES_MGR_EVT__DEVICE_STATUS_UPDATE,
    RES_MGR_EVT__REG_MEDIATOR,
    RES_MGR_EVT__DEREG_MEDIATOR,
    RES_MGR_EVT__REG_MAILBOX,
    RES_MGR_EVT__PROACTIVE_RSP,
    RES_MGR_EVT__RECEIVE_CMD,
    RES_MGR_EVT__GENERIC_RSP,
    RES_MGR_EVT__NUM
} ResMgr_EvtType_e;

typedef struct AppMbxEvtParms_t_
{
    ResMgr_TaskId_e eTaskId;
    u32 uAppMbx;
} AppMbxEvtParms_t;
/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_EVTITF_H__

