#ifndef __SOCKET_RSP_FACITF_H__
#define __SOCKET_RSP_FACITF_H__


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SocketCmdItf.h"
#include "ResMgr_RspItf.h"
#include "SocketCmdRspItf.h"
#include "SockMgrPlatformCommon.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

ResMgr_RspHdl_t SocketCmd_CreateGenRsp
(
  u32 uRspId, 
  u16 uExecRes, 
  u32 uCusData, 
  void *pvRspData
);

ResMgr_RspHdl_t SocketCmd_CreateProRsp
(
  u32 uRspId, 
  u32 uCusData, 
  void *pvRspData
);

void SocketCmd_DestroyRsp
(
  ResMgr_RspHdl_t hRsp
);

#endif/* __SOCKET_RSP_FACITF_H__ */
