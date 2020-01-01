/**
* @file TaskStgrEvtHandlerItf.h
*
* This header file defines the interfaces of Resource Manager Control  
* Indicator Handler
*/

#ifndef __TASKSTGREVTHANDLERITF_H__
#define __TASKSTGREVTHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_Evt.h"
#include "ResMgr_CmdMgrStgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void CmdMgrStgr_InitEvtHandler(CmdMgrStgrHdl_t pHandle, CmdMgrStgr_HandleEvt EvtHandler);
void CmdMgrStgr_RegEvtHandler(CmdMgrStgrHdl_t pHandle, ResMgr_EvtType_e eEvtType, CmdMgrStgr_HandleEvt HandleEvt);
void CmdMgrStgr_DeregEvtHandler(CmdMgrStgrHdl_t pHandle, ResMgr_EvtType_e eEvtType);
void CmdMgrStgr_HandleTaskEvt(CmdMgrStgrHdl_t pHandle, ResMgr_EvtHdl_t pEvtHdl);

#endif //__TASKSTGREVTHANDLERITF_H__

