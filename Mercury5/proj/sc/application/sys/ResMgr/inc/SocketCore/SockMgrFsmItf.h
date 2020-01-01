#ifndef __SOCKMGR_FSMITF_H__
#define __SOCKMGR_FSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformDefines.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SockMgr_FSMHdl_t;

typedef enum
{
	SOCKMGR_FSM_ERRCODE__ACCEPT = 0,
	SOCKMGR_FSM_ERRCODE__ACCEPT_BUSY,
	SOCKMGR_FSM_ERRCODE__UNACCPET,
	SOCKMGR_FSM_ERRCODE__NUM,
}SockMgr_FSM_ErrCode_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_FSMHdl_t SockMgr_FSMFactory_CreateFSM
(
  void *pvCusData, 
  u16 uStateNum, 
  const GenericState_t *psStates, 
  u16 uDefaultState
);

void SockMgr_FSMFactory_DestroyFSM
(
  SockMgr_FSMHdl_t hFSM
);

u16 SockMgr_FSM_HandleRsp
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

u16 SockMgr_FSM_HandleReq
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

u16 SockMgr_FSM_GetCurState
(
  SockMgr_FSMHdl_t hFSM
);


SockMgr_FSM_ErrCode_e SockMgr_FSM_AcceptReq
(
  SockMgr_FSMHdl_t hFSM, 
  u16 uReq
);

#endif/* __SOCKMGR_FSMITF_H__ */
