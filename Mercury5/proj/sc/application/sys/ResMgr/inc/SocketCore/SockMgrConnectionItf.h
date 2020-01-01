#ifndef __SOCKMGR_CONNECTIONITF_H__
#define __SOCKMGR_CONNECTIONITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrFsmItf.h"
#include "SockMgrDSPortItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

#define SOCKMGR_CONNECTION_ATTR__NONE             (0X00)
#define SOCKMGR_CONNECTION_ATTR__INTERRUPTED      (0X01)
#define SOCKMGR_CONNECTION_ATTR__DESTROY_DIRECTLY (0X02)
#define SOCKMGR_CONNECTION_ATTR__DESTROY_MERGED   (0X04)

#define SOCKMGR_CONNECTION_QUERY__NONE          (0X00)
#define SOCKMGR_CONNECTION_QUERY__CONNECTED     (0X01)
#define SOCKMGR_CONNECTION_QUERY__CONNECTING    (0X02)
#define SOCKMGR_CONNECTION_QUERY__DISCONNECTING (0X04)
#define SOCKMGR_CONNECTION_QUERY__DISCONNECTED  (0X08)

typedef void (*SockMgr_Connection_VisitDnsDataCb)(void *pvDnsData, void *pvUserData);

#ifdef __WLAN_IP_SUPPORT__
typedef void (*SockMgr_Connection_VisitPingDataCb)(void *pvPingData, void *pvUserData);
#endif/* __WLAN_IP_SUPPORT__ */

/*=============================================================*/
// Function Declarations
/*=============================================================*/

u16 SockMgr_Connection_GetCurState
(
 SockMgr_ConnHdl_t hConn
);

u32 SockMgr_Connection_GetIpAddress
(
 SockMgr_ConnHdl_t hConn
);

s32 SockMgr_Connection_PostMessage
(
 SockMgr_ConnHdl_t hConn,
 void *pvMsg
);


void SockMgr_Connection_GetSocketsWithSameConnection
(
 SockMgr_ConnHdl_t hConn,
 SockMgr_CtnrHdl_t hCtnr
);

bool SockMgr_Connection_IsValid
(
 SockMgr_ConnHdl_t hConn
);

void SockMgr_Connection_OccupyResource
(
 SockMgr_ConnHdl_t hConn,
 SockMgr_DataLinkHdl_t hDataLink, 
 SockMgr_ComMediaHdl_t hComMedia, 
 ResMgr_AppId_e eApOwner
);

void SockMgr_Connection_ReleaseResource
(
 SockMgr_ConnHdl_t hConn
);

/// the api can use to query connection which match the following states:
///   uQueryConnState = SOCKMGR_CONNECTION_QUERY__CONNECTED
///   uQueryConnState = SOCKMGR_CONNECTION_QUERY__CONNECTTING
///   uQueryConnState = SOCKMGR_CONNECTION_QUERY__CONNECTTING | SOCKMGR_CONNECTION_QUERY__CONNECTED
///
/// the query result will only one connection
/// in other hands, the query result may connected connection or connecting connection.
/// an app never has connected and connecting connection at the same time
SockMgr_ConnHdl_t SockMgr_Connection_QueryConnection
(
 ResMgr_AppId_e eApOwner, 
 SockMgr_Bearer_e eBearer,
 u8 uQueryConnState
);

/// the api can use to query connections which match following states:
/// the query result may may connections
void SockMgr_Connection_QueryConnections
(
 SockMgr_Bearer_e eBearer, 
 u8 uQueryConnState,
 SockMgr_CtnrHdl_t hCtnr
);


void SockMgr_Connection_SetAttr
(
 SockMgr_ConnHdl_t hConn,
 u8 uAttr
);

bool SockMgr_Connection_CheckAttr
(
 SockMgr_ConnHdl_t hConn,
 u8 uAttr
);

void SockMgr_Connection_ReSetAttr
(
 SockMgr_ConnHdl_t hConn,
 u8 uAttr
);

SockMgr_Bearer_e SockMgr_Connection_GetBearerType
( 
 SockMgr_ConnHdl_t hConn
);

u8 SockMgr_Connection_GetClientId
(
 SockMgr_ConnHdl_t hConn
);

void SockMgr_Connection_AddDnsData
(
  SockMgr_ConnHdl_t hConn, 
  void *pvDnsData
);

void SockMgr_Connection_RemoveDnsData
(
 SockMgr_ConnHdl_t hConn, 
 void *pvDnsData
);

void SockMgr_Connection_VisitAllDnsData
(
  SockMgr_ConnHdl_t hConn, 
  void *pvUserData, 
  SockMgr_Connection_VisitDnsDataCb pfnCb
);

u8 SockMgr_Connection_GetTi
(
  SockMgr_ConnHdl_t hConn
);

SockMgr_FSMHdl_t SockMgr_Connection_GetConnectionFSM
(
  SockMgr_ConnHdl_t hConn
);

#ifdef __WLAN_IP_SUPPORT__

void SockMgr_Connection_AddPingData
(
  SockMgr_ConnHdl_t hConn, 
  void *pvPingData
);

void SockMgr_Connection_RemovePingData
(
  SockMgr_ConnHdl_t hConn, 
  void *pvPingData
);

void SockMgr_Connection_VisitAllPingData
(
  SockMgr_ConnHdl_t hConn, 
  void *pvUserData, 
  SockMgr_Connection_VisitPingDataCb pfnCb
);

#endif/* __WLAN_IP_SUPPORT__*/

#endif/* __SOCKMGR_CONNECTIONITF_H__ */
