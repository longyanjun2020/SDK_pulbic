/**
* @file ResMgr_CmdMgrFacItf.h
*
* This header file defines the interface of command manager factory
*
*/

#ifndef __RESMGR_CMDMGRFACITF_H__
#define __RESMGR_CMDMGRFACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CommItf.h"
#include "ResMgr_CmdMgrItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
CmdMgrHdl_t CmdMgrFactory_InitMgr(ResMgr_StgrType_e eStrategier, ResMgrCommItf_t *pCommItf);
void CmdMgrFactory_UninitMgr(CmdMgrHdl_t pCmdMgrHdl);

CmdMgrHdl_t CmdMgrFactory_InitMgrEx(ResMgr_StgrType_e eStrategier, bool (*pbInitCategorys)[RES_MGR_RES_CATEGORY__NUM], ResMgrCommItf_t *pCommItf);
void CmdMgrFactory_UninitMgrEx(CmdMgrHdl_t pCmdMgrHdl);

#endif //__RESMGR_CMDMGRFACITF_H__

