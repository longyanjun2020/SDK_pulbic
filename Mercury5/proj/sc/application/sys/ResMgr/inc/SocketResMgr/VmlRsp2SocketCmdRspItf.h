#ifndef __VMLRSP_2_SOCKETCMDRSPITF_H__
#define __VMLRSP_2_SOCKETCMDRSPITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
#include "SocketCmdRspFacItf.h"
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

ResMgr_RspHdl_t VmlRsp2SocketRspCmd_OpenSocket(const void *cpvMsg);
ResMgr_RspHdl_t VmlRsp2SocketRspCmd_CloseSokcet(const void *cpvMsg);
ResMgr_RspHdl_t VmlRsp2SocketRspCmd_CreateDataLink(const void *cpvMsg);
ResMgr_RspHdl_t VmlRsp2SocketRspCmd_DestroyDataLink(const void *cpvMsg);
SockMgr_ConnHdl_t VmlRspDestroyDataLink_RetrieveConnection(const void *cpvMsg);
void* VmlRspCloseSocketError(u8 uClientID, u32 uUserData, ProtocolResult_t  Result);
void* VmlRspCreateSocketError(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);
void* VmlRspCloseDataLinkError(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);
void* VmlRspCreateDataLinkError(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);

#endif/* __VMLRSP_2_SOCKETCMDRSP_H__ */
