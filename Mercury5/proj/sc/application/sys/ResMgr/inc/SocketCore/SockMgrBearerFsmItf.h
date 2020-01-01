#ifndef __SOCKMGR_BEARERFSMITF_H__
#define __SOCKMGR_BEARERFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrFsmItf.h"
#include "SockMgrPlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_FSMHdl_t SockMgr_BearerFSMFactory_CreateBearerFSM
(
  SockMgr_Bearer_e eBearer, 
  void *pvCusData
);

void SockMgr_BearerFSMFactory_DestroyBearerFSM
(
  SockMgr_FSMHdl_t hFSM
);

u16 SockMgr_BearerFSM_HandleReq
(
 SockMgr_FSMHdl_t hFSM, 
 void *pEvt
);

u16 SockMgr_BearerFSM_HandleRsp
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

SockMgr_FSM_ErrCode_e SockMgr_BearerFSM_AcceptReq
(
  SockMgr_FSMHdl_t hFSM, 
  u16 uReq
);

#endif/* __SOCKMGR_BEARERFSMITF_H__ */
