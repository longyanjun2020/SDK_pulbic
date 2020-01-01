#ifndef __SOCKMGR_CONNECTION_H__
#define __SOCKMGR_CONNECTION_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrDSPortItf.h"
#include "SockMgrConnectionItf.h"
#include "SockMgrFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct _SockMgr_Connection_t_
{
    ResMgr_AppId_e eApOwner;
    SockMgr_Bearer_e eBearer;
    SockMgr_DataLinkHdl_t hDataLink;
    SockMgr_ComMediaHdl_t hComMedia;
	SockMgr_FSMHdl_t hConnFsm;
    SockMgr_CtnrHdl_t hCtnr;     /// For Dns Query
#ifdef __WLAN_IP_SUPPORT__
	SockMgr_CtnrHdl_t hPingCtnr; /// For Ping Query
#endif/* __WLAN_IP_SUPPORT__ */
	void *pvVenCreateReq;
	void *pvVenDestroyReq;
	void *pfnCreateCb;
	void *pfnDestroyCb;
	u8 uAttribute;
}SockMgr_Connection_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_DataLinkHdl_t SockMgr_Connection_GetDataLink(SockMgr_ConnHdl_t hConn);
SockMgr_ComMediaHdl_t SockMgr_Connection_GetComMedia(SockMgr_ConnHdl_t hConn);
ResMgr_AppId_e SockMgr_Connection_GetOwner(SockMgr_ConnHdl_t hConn);


#endif/* __SOCKMGR_CONNECTION_H__ */
