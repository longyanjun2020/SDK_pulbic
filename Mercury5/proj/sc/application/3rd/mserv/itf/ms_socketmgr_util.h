#ifndef __MS_SOCKMGR_UTIL_H__
#define __MS_SOCKMGR_UTIL_H__

#include "sic_net.h"
#include "ms_socket_cmn.h"
#include "SockMgrBearerItf.h"
#include "VmlReq2SocketCmdItf.h"
#include "VmlRsp2SocketCmdRspItf.h"
#include "SockMgrConnectionFsmItf.h"

#define E_VEN_MMS                    (E_VEN_FAKE_VENDOR)

typedef enum
{
	MSER_MIC_NET_DATALINK_DISCONNECTED = 0,
	MSER_MIC_NET_DATALINK_CONNECTING,
	MSER_MIC_NET_DATALINK_CONNECTED,
	MSER_MIC_NET_DATALINK_DISCONNECTING,
	MSER_MIC_NET_DATALINK_STATE_NUM,
	MSER_MIC_NET_DATALINK_INVALID,
}MServ_DataLink_State_e;

typedef void (*Mserv_Adaptor_TimerCb)(u16 uTimerId, u32 uUserData);
typedef void (*Mserv_Adaptor_TraverseDatalinkCb)(void *pvDatalink, void *pvUserData);

// Assumption
//   GPRS1 & GPRS2 can't exist simultaneously
MServ_DataLink_State_e Mserv_Adaptor_GetCurUseGPRSDataLinkState
(
  void
);

/// Check whether there's any connected datalink on gprs1/gprs2
bool Mserv_Adaptor_IsAnyConnectedGprsDataLink
(
  void
);

bool Mserv_Adaptor_IsBearerUsing
(
  SockMgr_Bearer_e eBearer
);

bool Mserv_Adaptor_HasEnoughDataLink
(
  SockMgr_Bearer_e eBearer
);

u8 Mserv_Adaptor_GetConnectionTi
(
  SockMgr_ConnHdl_t hConn
);

/// Check whether there's any sharable datalink on the bearer
bool Mserv_Adaptor_IsAnyUsableDataLink
(
  SockMgr_Bearer_e eBearer,
  SockMgr_ResCheckInfo_t *psResCheckInfo
);

/// Check whether there's any preemptable datalink on the bearer
bool Mserv_Adaptor_CanPreepmtUsingDataLink
(
  SockMgr_Bearer_e eBearer,
  SockMgr_ResCheckInfo_t *psResCheckInfo
);

/// Get a specific connection's state
MServ_DataLink_State_e MServ_Adaptor_GetSpecificDataLinkState
(
  SockMgr_ConnHdl_t hConn
);

/// Check whether the datalink(connection) is valid or not
bool Mserv_Adaptor_IsValidConnection
(
  SockMgr_ConnHdl_t hConn
);

// Adaptor for Mserv & Socket manager 
// These adaptors are used for convert 
// Mserv variable to Socket manager variable

// Assumption
//   if Mserv_Mic_DefMdl == VM_MBX_MDL1, then current sim == sim1
//   if Mserv_Mic_DefMdl == VM_MBX_MDL2, then current sim == sim2
CmdAdaptor_Sim_e Mserv_Adaptor_GetCurUseGPRSSimID
(
  void
);

// Assumption
//   convert vendor ap id to sockmgr ap id
ResMgr_AppId_e Mserv_Adaptor_Ven2SockApId
(
  u32 uVendorApId
);

// Assumption
//   each ven request message must have vendor ap id
u32 Mser_Adaptor_RetrieveVendorApIdFromVenReq
(
  void *pvMsg
);

SockMgr_Bearer_e Mserv_Adaptor_GetCurBearer
(
  u8 bearerid /// ven_socket_bearer_t 
);

Mserv_Mic_Net_DataLinkType_t Mserv_Adaptor_VenBearer2MicDataLinkType
(
  u8 bearerid /// ven_socket_bearer_t
);

__SLDPM_FREE__ bool Mserv_Adaptor_IsVMLOneUsed
(
  void
);

__SLDPM_FREE__ bool Mserv_Adaptor_IsVMLTwoUsed
(
  void
);

bool Mserv_Adaptor_IsVMLWiFiUsed
(
  void
);

MServ_DataLink_State_e Mserv_Adaptor_GetDataLinkStateByMsg
(
  const void *pvMsg
);

CmdAdaptor_Bearer_e Mserv_Adaptor_Ven2CmdAdaptorBearer
(
  u8 uBearerID
);

CmdAdaptor_Sim_e Mserv_Adaptor_VenSim2CmdAdaptorSim
(
  u8 uSimID
);

void* Mserv_Adaptor_GetVenCb
(
 u32 uVmlRspMsgType,
 const void *pvVmlRspMsg,
 bool bCloseAllDataLink
 );

void* Mserv_Adaptor_GetVenUserData
(
 u32 uVmlRspMsgType,
 const void *pvVmlRspMsg,
 bool bCloseAllDataLink
);

SockMgr_ConnHdl_t Mserv_Adaptor_RetriveConnection
(
 const void *cpvMsg
);

bool Mserv_Adaptor_IsValidRsp
(
 const void *cpvMsg
);

void Mserv_Adaptor_SendMsg
(
 SockMgr_ConnHdl_t hConn, 
 void *pvMsg
);

u32 Mserv_Adaptor_GetVenIdMMS
(
  void
);

void Mserv_Adpator_CmdTimeOutStart
(
  u32 uCmd
);

void Mserv_Adaptor_CmdTimeOutStop
(
  u32 uCmd
);

bool Mserv_Adaptor_IsDataLinkAvailable
(
  SockMgr_Bearer_e eBearer
);

bool Mserv_Adaptor_IsAnySocketConnect
(
  SockMgr_Bearer_e eBearer
);

SockMgr_Bearer_e Mserv_Adaptor_BearerInfo2SockMgrBearer
(
  MservSocketBearerInfo_t *psBearerInfo
);

void Mserv_Adaptor_SetTxTraffic
(
  SockMgr_SocketHdl_t hSocket
);

void Mserv_Adaptor_SetRxTraffic
(
  SockMgr_SocketHdl_t hSocket
);

void Mserv_Adaptor_CreateDataTrafficMonitorTimer
(
  void
);

void Mserv_Adaptor_StopDataTrafficMonotirTimer
(
  void
);

u32 Mserv_Adaptor_GetTaskId
(
  void
);

void Mserv_Adaptor_TraverseAllDatalink
(
    void *pvUserData,
    Mserv_Adaptor_TraverseDatalinkCb pfnTraverseDatalinkCb
);

bool Mserv_Adaptor_IsAnyDisconnectingDatalink
(
    SockMgr_Bearer_e eBearer,
    SockMgr_DataLinkHdl_t *phDataLink
);

#endif/* __MS_SOCKMGR_UTIL_H__ */
