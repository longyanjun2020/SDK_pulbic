#ifndef __SOCKMGR_CONNECTIONFSMITF_H__
#define __SOCKMGR_CONNECTIONFSMITF_H__

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
	SOCKMGR_CONNECTION_STATE__CONNECTED = 0X00,
	SOCKMGR_CONNECTION_STATE__DISCONNECTED,
	SOCKMGR_CONNECTION_STATE__CONNECTING,
	SOCKMGR_CONNECTION_STATE__DISCONNECTING,
	SOCKMGR_CONNECTION_STATE__NUM,
}SockMgrConnectionState_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


SockMgr_FSMHdl_t SockMgr_ConnectionFSMFactory_CreateConnectionFSM
(
  void *pvCusData
);

void SockMgr_ConnectionFSMFactory_DestroyConnectionFSM
(
  SockMgr_FSMHdl_t hFSM
);

u16 SockMgr_ConnectionFSM_HandleRsp
(
  SockMgr_FSMHdl_t hFSM, 
  void *pEvt
);

u16 SockMgr_ConnectionFSM_HandleReq
(
 SockMgr_FSMHdl_t hFSM, 
 void *pEvt
);

#endif/* __SOCKMGR_CONNECTIONFSMITF_H__ */
