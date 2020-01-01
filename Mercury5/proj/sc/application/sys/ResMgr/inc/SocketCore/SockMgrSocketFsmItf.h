#ifndef __SOCKMGR_SOCKET_FSM_ITF_H__
#define __SOCKMGR_SOCKET_FSM_ITF_H__

#include "SockMgrFsmItf.h"

u16 SockMgr_SocketFSM_HandleRsp
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

u16 SockMgr_SocketFSM_HandleReq
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

SockMgr_FSM_ErrCode_e SockMgr_SocketFSM_AcceptReq
(
  SockMgr_FSMHdl_t hFSM, 
  u16 uReq
);

bool SockMgr_SocketFSM_IsWaitRsp
(
  SockMgr_FSMHdl_t hFSM
);

void SockMgr_SocketFSM_SetWaitRsp
(
   SockMgr_FSMHdl_t hFSM
);

void SockMgr_SocketFSM_ReSetWaitRsp
(
   SockMgr_FSMHdl_t hFSM
);

bool SockMgr_SocketFSM_IsClosing
(
   SockMgr_FSMHdl_t hFSM
);

#endif/* __SOCKMGR_SOCKET_FSM_ITF_H__ */
