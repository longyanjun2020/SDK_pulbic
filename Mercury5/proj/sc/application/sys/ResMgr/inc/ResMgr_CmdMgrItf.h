/**
* @file ResMgr_CmdMgrItf.h
*
* This header file defines the interface of resource command manager.
*
*/

#ifndef __RESMGR_CMDMGRITF_H__
#define __RESMGR_CMDMGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* CmdMgrHdl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void CmdMgr_HandleCmd(CmdMgrHdl_t pCmdMgrHdl, ResMgr_CmdHdl_t pCmdHdl);
void CmdMgr_HandleRsp(CmdMgrHdl_t pCmdMgrHdl, ResMgr_RspHdl_t pRspHdl);
__SLDPM_FREE__ void CmdMgr_HandleCtrl(CmdMgrHdl_t pCmdMgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);
void CmdMgr_HandleEvt(CmdMgrHdl_t pCmdMgrHdl, ResMgr_EvtHdl_t pEvtHdl);

#endif //__RESMGR_CMDMGRITF_H__

