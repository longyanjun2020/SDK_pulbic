#ifndef __VML_MAKEMSG_COMMON_H__
#define __VML_MAKEMSG_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
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

void* VmlMakeMsgCommon(s16 sMsgType, s16 sBodyLen);
void* VmlMakeCloseDataLinkReq(u8 uClientID, u8 uTi, u32 uUserData);
void* VmlMakeCloseSocketReq(u8 uClientID, u8 uSocketId, u32 uUserData);
void* VmlMakeCloseSocketRsp(u8 uClientID, u32 uUserData, ProtocolResult_t  Result);
void* VmlMakeCreateSocketRsp(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);
void* VmlMakeCloseDataLinkRsp(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);
void* VmlMakeCreateDataLinkRsp(u8 uClientID, u8 uTi, u32 uUserData, ProtocolResult_t  Result);

#endif/* __VML_MAKEMSG_COMMON_H__ */
