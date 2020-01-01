#ifndef __UT_SOCKET_CMN_ITF_H__
#define __UT_SOCKET_CMN_ITF_H__

#include <windows.h>
#include "ResMgr_CmdMgrItf.h"

#include "SocketCmd.h"
#include "SockMgrPlatformDefines.h"

/// Common struct

typedef void (*_UT_Cmn_RspCb)(bool bSuccess, void *pvUserData, void *pvRspData);

typedef struct
{
	u8 uGprsDNS[SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uGprsIP [SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uGprsAPN[SOCKMGR_APN_MAX_LEN];
}_UT_GprsData_t;

typedef struct
{
	bool bStaticIp;
	u8 uWiFiIp[SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uWiFiDns1[SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uWiFiDns2[SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uWiFiSubnet[SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uWiFiGateway[SOCKMGR_IP_ADDRESS_MAX_LEN];
}_UT_WiFiData_t;

typedef struct
{
	SockMgr_Bearer_e eBearer;
	union
	{
        _UT_GprsData_t sGprsData;
        _UT_WiFiData_t sWiFiData;
	}uBearerSpecificData_t;
}_UT_BearerInfo_t;

typedef struct
{
	SockMgr_ApId_e eAppId;
	u8 uBearerNum;
    _UT_BearerInfo_t sBearerInfos[E_SOCKMGR_BEARER_NUM];
}_UT_CreateDataLinkReqCmd_InitData_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
}_UT_DestroyDataLinkReqCmd_InitData_t;

typedef struct
{
    SockMgr_ApId_e eAppId;
	SockMgr_ConnHdl_t hConn;
	SockMgr_Bearer_e eBearer;
}_UT_DestroyAllDataLinksReqCmd_InitData_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
	SockMgr_SocketHdl_t hSocket;
}_UT_OpenSocketReqCmd_InitData_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
	SockMgr_SocketHdl_t hSocket;
}_UT_CloseSocketReqCmd_InitData_t;

typedef struct
{
	bool bRspResult;
	void *pvUserData;
	_UT_Cmn_RspCb pfnRspCb;
	HANDLE hSem;
}_UT_CmnRspCbInfo_t;

typedef struct
{
	bool bRspResult;
	SockMgr_ConnHdl_t hConn;
}_UT_CreateConnectionRspData_t;

typedef struct
{
	bool bRspResult;
}_UT_CmnRspData_t;

//////////////////////////////////////////////////////////////////////////

SocketCmd_t* _UT_CreateSocketCmd
(
  void
);

_UT_CmnRspCbInfo_t* _UT_DupRspCbInfo
(
  _UT_CmnRspCbInfo_t *psRspCbInfo
);

void SocketCmd_CmnInformApp
(
  void *pCusData, 
  void *pRspData, 
  ResMgr_InformType_e eInformType
);

void SocketCmd_CmnFreeCusData
(
  void *pCusData
);

void SocketCmd_CmnInExecHandler
(
  SocketCmdHdl_t hSocketCmd
);

void SocketCmd_CmnTerminateInfoApp
(
  CmdMgrStgrHdl_t hCmdStgr, 
  SocketCmdHdl_t hSocketCmd, 
  ResMgr_RspHdl_t hRspCmd
);

CmdMgrHdl_t _UT_InitSocketCmdMgr
(
  void
);

void _UT_UnInitSocketCmdMgr
(
 CmdMgrHdl_t hCmdMgr
);

//////////////////////////////////////////////////////////////////////////

#endif/* __UT_SOCKET_CMN_ITF_H__ */