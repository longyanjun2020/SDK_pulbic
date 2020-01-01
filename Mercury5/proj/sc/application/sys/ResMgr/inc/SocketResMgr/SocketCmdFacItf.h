#ifndef __SOCKET_CMD_FACITF_H__
#define __SOCKET_CMD_FACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_Cmd.h"
#if !defined(RES_MGR_STANDALONE_DEBUG)
#include "SocketCmdItf.h"
#else
typedef void* SocketCmdHdl_t ;
#endif
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
#if !defined(RES_MGR_STANDALONE_DEBUG)
SocketCmdHdl_t SocketCmd_CreateCmd
(
   ResMgr_AppId_e eApId,
   SocketCmd_Req_e eCmdReqType,
   SocketCmdCusParam_t *psSocketCmdCusParam,
   void *pvCusData
);
#endif
void SocketCmd_DestroyCmd
(
  SocketCmdHdl_t hSocketCmd
);

#endif/* __SOCKET_CMD_FACITF_H__ */
