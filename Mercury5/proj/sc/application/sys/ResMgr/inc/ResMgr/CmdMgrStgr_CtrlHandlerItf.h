/**
* @file CmdMgrStgrCtrlHandlerItf.h
*
* This header file defines the interfaces of Resource Manager Control  
* Indicator Handler
*/

#ifndef __TASKSTGRCTRLHANDLERITF_H__
#define __TASKSTGRCTRLHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
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
void CmdMgrStgr_InitCtrlHandler(CmdMgrStgrHdl_t pHandle, CmdMgrStgr_ExecCtrlReq CtrlHandler);
void CmdMgrStgr_RegCtrlHandler(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlType_e eCtrlType, CmdMgrStgr_ExecCtrlReq ExecCtrl);
void CmdMgrStgr_DeregCtrlHandler(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlType_e eCtrlType);
__SLDPM_FREE__ bool CmdMgrStgr_HandleTaskCtrl(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

#endif //__TASKSTGRCTRLHANDLERITF_H__

