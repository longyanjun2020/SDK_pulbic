#ifndef _SOCKMGR_DATALINK_ITF_H_
#define _SOCKMGR_DATALINK_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "VmlAdaptor.h"
#include "SockMgrPlatformCommon.h"
#include "SockMgrResItf.h"
#include "SockMgrSocketItf.h"
#include "SockMgrBearerItf.h"
#include "SockMgrDataLinkFsmItf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	E_SOCKMGR_DATALINK_GPRS = 0,
	E_SOCKMGR_DATALINK_WIFI,
	E_SOCKMGR_DATALINK_CSD,
	E_SOCKMGR_DATALINK_NUM,
}SockMgr_DataLink_e;

typedef struct
{
	SockMgr_Res_e  eResType  ;
	u16 uOwnerNum;
	SockMgr_BearerHdl_t hParentBearer; 
	SockMgr_Bearer_e eParentBearer;
	u16 uMaxSocket;
	SockMgr_ResCheckInfo_t sResShareInfo;
	ResMgr_AppId_e eAp;
}SockMgr_DataLinkCreateData_t;

typedef struct
{
    u8 u8GPRS_APN[SOCKMGR_APN_MAX_LEN];
    u8 u8ProxyIP[SOCKMGR_IP_ADDRESS_STR_MAX_LEN];
}SockMgr_APNProxyMap;

typedef ProtocolCreateDatalinkRspMsg_t SockMgr_SharableDataLinkRspData_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_DataLinkHdl_t SockMgr_DataLinkFactory_CreateDataLink(SockMgr_DataLinkCreateData_t *psCreateDataLinkData) ;
void SockMgr_DataLinkFactory_DestroyDataLink(SockMgr_DataLinkHdl_t hDataLink, ResMgr_AppId_e eAp) ;
SockMgr_BearerHdl_t SockMgr_DataLink_GetBearer(SockMgr_DataLinkHdl_t hDataLink) ;
void SockMgr_DataLink_SetBearer(SockMgr_DataLinkHdl_t hDataLink, SockMgr_BearerHdl_t hBearer) ;
bool SockMgr_DataLink_OccupySocket (SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
bool SockMgr_DataLink_ReleaseSocket(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
void SockMgr_DataLink_ReleaseAllSocketToExpirePool(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_GetMaxSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_GetRemainSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_GetUsedSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
bool SockMgr_DataLink_CheckSharable(SockMgr_DataLinkHdl_t hDataLink, void *pvVerifyData) ;
bool SockMgr_DataLink_IsDataLinkExpired(SockMgr_DataLinkHdl_t hDataLink) ;
SockMgr_FSMHdl_t SockMgr_DataLink_GetDataLinkFSM(SockMgr_DataLinkHdl_t hDataLink);
void SockMgr_DataLink_GetSharableRspData(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SharableDataLinkRspData_t *psSharableRspData);
void SockMgr_DataLink_SetSharableRspData(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SharableDataLinkRspData_t *psSharableRspData);
void SockMgr_DataLink_ReSetSharableRspData(SockMgr_DataLinkHdl_t hDataLink);
SockMgr_Bearer_e SockMgr_DataLink_GetParentBearerID(SockMgr_DataLinkHdl_t hDataLink);
bool SockMgr_DataLink_IsValidDataLink(SockMgr_DataLinkHdl_t hDataLink);
u32 SockMgr_DataLink_GetIpAddr(SockMgr_DataLinkHdl_t hDataLink);
u8 SockMgr_DataLink_GetTi(SockMgr_DataLinkHdl_t hDataLink);
void SockMgr_DataLink_SetTi(SockMgr_DataLinkHdl_t hDataLink, u8 uTi);
u8* SockMgr_DataLink_GetProxy(SockMgr_DataLinkHdl_t hDataLink);


#endif/* _SOCKMGR_DATALINK_ITF_H_ */
