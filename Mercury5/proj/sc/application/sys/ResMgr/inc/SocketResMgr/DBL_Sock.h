#ifndef __DBL_SOCK_H__
#define __DBL_SOCK_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
#include "SocketCmdItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

s16 DBL_CreateConnection(SocketCmdHdl_t hSocketCmd);
s16 DBL_DestroyConnection(SocketCmdHdl_t hSocketCmd);
s16 DBL_DestroyAllConnections(SocketCmdHdl_t hSocketCmd);
s16 DBL_OpenSocket(SocketCmdHdl_t hSocketCmd);
s16 DBL_CloseSocket(SocketCmdHdl_t hSocketCmd);
s16 DBL_TerminateOpenSocket(SocketCmdHdl_t hSocketCmd);
s16 DBL_TerminateCreateConnection(SocketCmdHdl_t hSocketCmd);
void DBL_CreateConnectionUpdateCusData(SocketCmdHdl_t hSocketCmd, void *pvRspData);
void DBL_DestroyConnectionUpdateCusData(SocketCmdHdl_t hSocketCmd, void *pvRspData);
void DBL_SocketCmd2VmlCreateDataLinkMsg(SocketCmdHdl_t hSocketCmd ,void **ppvMsg);
void DBL_MakeFakeVmlCreateDataLinkRsp(u8 uClientID, u32 uLocalIPAddr, u32 uUserData, ProtocolResult_t uResult, void **ppvMsg);
void DBL_MakeFakeVmlCloseDataLinkRsp(u8 uClientID, u32 uUserData, ProtocolResult_t uResult, void **ppvMsg);
void DBL_MakeFakeVmlOpenSocketRsp(u8 uClientID, u8 uSocketIdx, u16 uClientPort, u32 uUserData, ProtocolResult_t uResult, void **ppvMsg);
void DBL_MakeFakeVmlCloseSocketRsp(u8 uClientID, u8 uSocketIdx, u32 uUserData, ProtocolResult_t uResult, void **ppvMsg);
void DBL_MakeFakeHasSharableDataLinkRsp(SockMgr_SharableDataLinkRspData_t *psSharableRspData ,void **ppvMsg);
void DBL_CreateConnectionInExecHandler(SocketCmdHdl_t hSocketCmd);
void DBL_DestroyConnectionInExecHandler(SocketCmdHdl_t hSocketCmd);
void DBL_DestroyAllConnectionsInExecHandler(SocketCmdHdl_t hSocketCmd);
void DBL_OpenSocketInExecHandler(SocketCmdHdl_t hSocketCmd);
void DBL_CloseSocketInExecHandler(SocketCmdHdl_t hSocketCmd);
void DBL_ReSetCreateConnectionSocketCmd(CmdMgrStgrHdl_t hCmdStgr,SocketCmdHdl_t hSocketCmd);
void DBL_ReSetDestroyAllConnectionSocketCmd(CmdMgrStgrHdl_t hCmdStgr,SocketCmdHdl_t hSocketCmd);
void DBL_CreateConnectionTerminateInfoApp(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd, ResMgr_RspHdl_t hRspCmd);
void DBL_OpenSocketTerminateInfoApp(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd, ResMgr_RspHdl_t hRspCmd);
bool DBL_CreateConnectionNeedRetry(SocketCmdHdl_t hSocketCmd);
bool DBL_DestroyAllConnectionNeedRetry(SocketCmdHdl_t hSocketCmd);
void DBL_CreateConnectionFakeInfoApp(SocketCmdHdl_t hSocketCmd);
void DBL_CreateConnectionTimeOutHandler(CmdMgrStgrHdl_t hCmdStgr,SocketCmdHdl_t hSocketCmd);

#endif/* __DBL_SOCK_H__ */
