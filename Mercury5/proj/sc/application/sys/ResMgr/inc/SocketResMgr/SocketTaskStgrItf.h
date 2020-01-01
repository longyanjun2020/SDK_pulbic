#ifndef __SOCKET_TASKSTGRITF_H__
#define __SOCKET_TASKSTGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_CmdMgrStgrItf.h"
#if !defined(RES_MGR_STANDALONE_DEBUG)
#include "SocketCmdItf.h"
#endif
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SocketCmdMgrStgrHdl_t;

typedef enum
{
	SOCKET_TASKSTGR_CONFLICT_RESOLVE__OK = 0,
	SOCKET_TASKSTGR_CONFLICT_RESOLVE__OK_BUSY,
	SOCKET_TASKSTGR_CONFLICT_RESOLVE__FAIL,
}SocketTaskStgr_ResolveConflict_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

CmdMgrStgrHdl_t SocketTaskStgr_Init
(
  ResMgrCommItf_t *pCommItf
);

void SocketTaskStgr_UnInit
(
  CmdMgrStgrHdl_t pHandle
);
#if !defined(RES_MGR_STANDALONE_DEBUG)
bool SocketCmdMgrStgr_IsValidPlayParam
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

bool SocketCmdMgrStgr_IsValidStopParam
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

SockMgr_ResolveConflict_e SocketTaskStgr_AcceptStopCmd
( 
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
 );

SockMgr_ResolveConflict_e SocketTaskStgr_AcceptPlayCmd
( 
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

void SocketCmdMgrStgr_ProRspInfo
(
  CmdMgrStgrHdl_t hCmdMgrStgr, 
  ResMgr_CmdHdl_t hRspCmd
);

bool SocketTaskStgr_PlayCmdIsWaitRsp
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

SockMgr_ResolveConflict_e SocketTaskStgr_PlayCmdCanResolveConflict
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

bool SocketTaskStgr_PlayCmdHasConflict
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

SockMgr_ResolveConflict_e SocketTaskStgr_PlayCmdResolveConflict
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
);

bool SocketTaskStgr_HasConnectionConflict
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
 );

bool SocketTaskStgr_HasSocketConflict
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
);

SocketTaskStgr_ResolveConflict_e SocketTaskStgr_CanResolveConnectionConflict
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);


SocketTaskStgr_ResolveConflict_e SocketTaskStgr_CanResolveSocketConflict
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);

u16 SocketTaskStgr_FindHighPriorityConflictCmd
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
 );

#ifdef __SOCKMGR_FEATURE_PREEMPTION__

SocketTaskStgr_ResolveConflict_e SocketTaskStgr_ResolveConnectionConflict
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
);

SocketTaskStgr_ResolveConflict_e SocketTaskStgr_ResolveSocketConflict
(
 SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
 SocketCmdHdl_t hSocketCmd
);

#endif/* __SOCKMGR_FEATURE_PREEMPTION__ */

bool SocketTaskStgr_RePackPlayCmd
(
  SocketCmdMgrStgrHdl_t hSocketCmdStgr, 
  SocketCmdHdl_t hSocketCmd
);
#endif/* RES_MGR_STANDALONE_DEBUG */
#endif/* __SOCKET_TASKSTGRITF_H__ */
