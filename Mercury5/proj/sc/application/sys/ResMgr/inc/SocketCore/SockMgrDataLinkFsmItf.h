#ifndef __SOCKMGR_DATALINKFSMITF_H__
#define __SOCKMGR_DATALINKFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	SOCKMGR_DATALINK_STATE__DISCONNECTED = 0,
	SOCKMGR_DATALINK_STATE__DISCONNECTING,
	SOCKMGR_DATALINK_STATE__CONNECTED,
	SOCKMGR_DATALINK_STATE__CONNECTING,
	SOCKMGR_DATALINK_STATE__NUM,
}SockMgr_DataLink_State_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


SockMgr_FSMHdl_t SockMgr_DataLinkFSMFactory_CreateDataLinkFSM
(
  void *pvCusData
);

void SockMgr_DataLinkFSMFactory_DestroyDataLinkFSM
(
  SockMgr_FSMHdl_t hFSM
);

u16 SockMgr_DataLinkFSM_HandleRsp
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

u16 SockMgr_DataLinkFSM_HandleReq
(
 SockMgr_FSMHdl_t hFSM, 
 void *pEvt
);

SockMgr_FSM_ErrCode_e SockMgr_DataLinkFSM_AcceptReq
(
  SockMgr_FSMHdl_t hFSM, 
  u16 uReq
);

#endif/* __SOCKMGR_DATALINKFSMITF_H__ */
