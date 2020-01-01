/**
* @file MediaCmdListenerItf.h
*
* This header file defines the interfaces of media proactive event
* 
*/

#ifndef __MEDIACMDLISTENERITF_H__
#define __MEDIACMDLISTENERITF_H__

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
typedef void* MediaProEvtsHdl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
__SLDPM_FREE__ void MediaCmdListener_RegProEvt(CmdMgrStgrHdl_t pStgrHdl, u16 uResInfo, ResMgr_CmdHdl_t pEvtOwnerCmd);
__SLDPM_FREE__ void MediaCmdListener_DeregProEvt(CmdMgrStgrHdl_t pStgrHdl, u16 uResInfo, ResMgr_CmdHdl_t pEvtOwnerCmd);
__SLDPM_FREE__ bool MediaCmdListener_CompareClient(void *pCurSettings, void *pRefSettings, void *pCusData);

#endif //__MEDIACMDLISTENERITF_H__

