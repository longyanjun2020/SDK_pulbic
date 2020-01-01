/**
* @file ResMgr_CmdMgrStgr.h
*
* This header file defines the data structure of command manager tStgr
*
*/

#ifndef __RESMGR_CMDMGRSTGR_H__
#define __RESMGR_CMDMGRSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdMgrStgr.h"
#include "ResMgr_DevMediator.h"
#include "ResMgr_EvtItf.h"
#include "ResMgr_CtrlItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_CmdMgrStgr_t_
{
    CmdMgrStgrExtItf_t const *pExtInterface;
    DevMediatorHdl pDevMedHdl;
    CmdMgrStgr_HandleEvt aEvtHandlers[RES_MGR_EVT__NUM];
    CmdMgrStgr_ExecCtrlReq aCtrlExecutors[RES_MGR_CTRL_TYPE__NUM];
} ResMgr_CmdMgrStgr_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
__SLDPM_FREE__ void CmdMgrStgr_InitStgr(CmdMgrStgrHdl_t pHandle, CmdMgrStgrExtItf_t const *pExtInterface, ResMgrCommItf_t *pCommItf);
__SLDPM_FREE__ void CmdMgrStgr_UninitStgr(CmdMgrStgrHdl_t pHandle);

#endif //__RESMGR_CMDMGRSTGR_H__

