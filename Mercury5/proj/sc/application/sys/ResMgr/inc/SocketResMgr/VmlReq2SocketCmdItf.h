#ifndef __VMLREQ_2_SOCKETCMD_ITF_H__
#define __VMLREQ_2_SOCKETCMD_ITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
#include "SocketCmdItf.h"
#include "CmdAdaptorCommon.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SocketCmdHdl_t VmlCreateDataLink2SocketCmd
(
  void *pvMsg, 
  ResMgr_AppId_e eApId,
  SockMgr_ConnHdl_t hConn,
  CmdAdaptor_Sim_e eSimID, 
  void *pvVenCb, 
  void *pvVenUserData, 
  CmdAdaptor_Version_e eVersion
);

SocketCmdHdl_t VmlCreateDataLink2SocketCmdEx
(
  void *pvMsg, 
  ResMgr_AppId_e eApId, 
  SockMgr_ConnHdl_t hConn,
  CmdAdaptor_Sim_e eSimID,
  void *pvVenCb, 
  void *pvVenUserData, 
  CmdAdaptor_Version_e eVersion
);


SocketCmdHdl_t VmlDestroyDataLink2SocketCmd
(
  void *pvMsg, 
  ResMgr_AppId_e eApId, 
  SockMgr_ConnHdl_t hConn, 
  void *pvVenCb, 
  void *pvVenUserData, 
  CmdAdaptor_Version_e eVersion
);

SocketCmdHdl_t VmlOpenSocket2SocketCmd
(
  void *pvMsg, 
  ResMgr_AppId_e eApId, 
  SockMgr_ConnHdl_t hConn, 
  SockMgr_SocketHdl_t hSocket
);

SocketCmdHdl_t VmlCloseSocket2SocketCmd
(
  void *pvMsg, 
  ResMgr_AppId_e eApId, 
  SockMgr_ConnHdl_t hConn, 
  SockMgr_SocketHdl_t hSocket
);

SocketCmdHdl_t VmlDestroyAllDataLinks2SocketCmd
(
  void *pvMsg,
  ResMgr_AppId_e eApId,
  SockMgr_Bearer_e eBearer,
  SockMgr_ConnHdl_t hConn,
  void *pvVenCb, 
  void *pvVenUserData, 
  CmdAdaptor_Version_e eVersion
);

#endif/* __VMLREQ_2_SOCKETCMD_ITF_H__ */
