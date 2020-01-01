#ifndef __SOCKETCMD_CTRLHANDLER_ITF_H__
#define __SOCKETCMD_CTRLHANDLER_ITF_H__


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_CtrlItf.h"
#include "ResMgr_CtrlHandlerItf.h"
#include "SocketCmdRspItf.h"
#include "SocketTaskStgrItf.h"
#include "SockMgrPlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	SOCKMGR_CTRL_ID__BEARER_CONNECTED = 0,
	SOCKMGR_CTRL_ID__BEARER_DISCONNECTED,
}SockMgr_Bearer_StatusChange_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

ResMgr_CtrlReqHandle_t SockMgr_CreateUpdateBearerStatusReq(SockMgr_Bearer_e eBearerType, SockMgr_Bearer_StatusChange_e eStatusChange);
bool SockMgr_HandleUpdateBearerStatus(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);

#endif/* __SOCKETCMD_CTRLHANDLER_ITF_H__ */
