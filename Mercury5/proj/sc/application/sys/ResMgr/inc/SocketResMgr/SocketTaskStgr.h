#ifndef __SOCKET_TASKSTGR_H__
#define __SOCKET_TASKSTGR_H__


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_TaskStgr.h"
#include "ResMgr_CmdMgrStgrItf.h"
#include "SocketTaskStgrItf.h"
#include "SockMgrBearerMgrItf.h"
#include "SockMgrComMediaMgrItf.h"
#include "SockMgrConflictMgrItf.h"
#include "SocketCmdItf.h"
#include "ListenerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

extern SockMgr_ComMediaHdl_t ghComMediaMserv;

typedef struct
{
	ResMgr_TaskStgr_t sTaskStgr;
	SockMgr_BearerMgrHdl_t hBearerMgr;
	SockMgr_ComMediaMgrHdl_t hComMediaMgr;
	SockMgr_ConflictMgrHdlt_t hConflictMgr;
    ListenerHdl_t hListener;
	SocketCmdHdl_t hTmpCurSocketCmd;  /// used when find high priority cmd
}Socket_TaskStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void SocketCmdMgrStgr_HandleCmd
(
  CmdMgrStgrHdl_t hCmdMgrStgr, 
  ResMgr_CmdHdl_t hReqCmd
);

void SocketCmdMgrStgr_HandleRsp
( 
  CmdMgrStgrHdl_t hCmdMgrStgr, 
  ResMgr_CmdHdl_t hRspCmd
);

bool SocketCmdMgrStgr_HandleCtrl
(
  CmdMgrStgrHdl_t hCmdMgrStgr, 
  ResMgr_CtrlHdl_t hCtrlCmd
);


#endif/* __SOCKET_TASKSTGR_H__ */
