#ifndef __CMD_ADAPTOR_COMMON_H__
#define __CMD_ADAPTOR_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
#include "PlatformDefines.h"
#include "SocketCmdRspItf.h"
#include "SockMgrPlatformCommon.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	CMDADAPTOR_BEARER__GPRS = 0,
#ifdef __WLAN_IP_SUPPORT__
	CMDADAPTOR_BEARER__WIFI,
#endif/* __WLAN_IP_SUPPORT__ */
	CMDADAPTOR_BEARER__NUM,
}CmdAdaptor_Bearer_e;

typedef enum
{
	CMDADAPTOR_SIM__ONE = 0,
	CMDADAPTOR_SIM__TWO,
	CMDADAPTOR_SIM__NOSIM,
	CMDADAPTOR_SIM__NUM,
}CmdAdaptor_Sim_e;

typedef enum
{
	CMDADAPTOR_VERSION__FOR_VEN_SDK_EX = 0XAB,
	CMDADAPTOR_VERSION__FOR_VEN_SDK,
	CMDADAPTOR_VERSION__NUM,
	CMDADAPTOR_VERSION__INVALID,
}CmdAdaptor_Version_e; 

// Adaptor for ven socket & vml
typedef enum
{
	CMDADAPTOR_SOCKET_OK = 0,
	CMDADAPTOR_SOCKET_BAD_PARAM,
	CMDADAPTOR_SOCKET_FAIL,
	CMDADAPTOR_SOCKET_OUT_OF_MEMORY, 
	CMDADAPTOR_SOCKET_DATA_LINK_ALREADY_ACTIVATED,
	CMDADAPTOR_SOCKET_DATA_LINK_KO, 
	CMDADAPTOR_SOCKET_DATA_LINK_CLOSE_BY_PEER, 
	CMDADAPTOR_SOCKET_RESULT_DEFAULT,
	CMDADAPTOR_SOCKET_NB_MAX_CTXT_REACHED,
	CMDADAPTOR_SOCKET_IP_ERROR,
	CMDADAPTOR_SOCKET_NO_MORE_SOCKET,
	CMDADAPTOR_SOCKET_BAD_SOCKET_ID,
	CMDADAPTOR_SOCKET_CONTCP_CLOSE,
	CMDADAPTOR_SOCKET_DNS_ERROR,
	CMDADAPTOR_SOCKET_GPRS_NOT_PRESENT,
	CMDADAPTOR_SOCKET_KO_WRONG_STATE,
	CMDADAPTOR_SOCKET_KO_NO_MSL_CONTEXT_FOUND,
	CMDADAPTOR_SOCKET_SET_SOCKET_OPTION_ERROR,
	CMDADAPTOR_SOCKET_GET_SOCKET_OPTION_ERROR,
	CMDADAPTOR_SOCKET_SHUTDOWN_SOCKET_ERROR,
	CMDADAPTOR_SOCKET_CONTCP_SYN_TIMEOUT,
	CMDADAPTOR_SOCKET_RESULT_CONTCP_AGAIN,
}CmdAdaptor_ErrCode_e;

typedef struct _CmdAdaptor_CreateGPRSSpecificData_t_
{
	u8 uUserName[CMDADAPTOR_USER_NAME_MAX_LEN];
	u8 uPassWord[CMDADAPTOR_PASSWD_MAX_LEN];
	u8 uAPN[CMDADAPTOR_APN_MAX_LEN];
	u8 uClientIpAddress[CMDADAPTOR_IP_ADDRESS_MAX_LEN];
}CmdAdaptor_CreateGPRSSpecificData_t;

typedef struct _CmdAdaptor_CreateWiFiSpecificData_t_
{
	u8 uUserName[CMDADAPTOR_USER_NAME_MAX_LEN];
	u8 uPassWord[CMDADAPTOR_PASSWD_MAX_LEN];
	u8 uClientIpAddress[CMDADAPTOR_IP_ADDRESS_MAX_LEN];
}CmdAdaptor_CreateWiFiSpecificData_t;

typedef struct _CmdAdaptor_CreateConnection_Param_t_
{
	ResMgr_AppId_e eAp;
	CmdAdaptor_Bearer_e eBearers[CMDADAPTOR_BEARER__NUM];
	CmdAdaptor_Sim_e eSim;
	u8 uDnsIP[CMDADAPTOR_IP_ADDRESS_MAX_LEN];
	u8 uBearerNum;
	CmdAdaptor_CreateGPRSSpecificData_t sGPRSSpecificData;
	CmdAdaptor_CreateWiFiSpecificData_t sWiFiSpecificData;
}CmdAdaptor_CreateConnection_Param_t;

/* define param for destroying connection */
typedef struct _CmdAdaptor_DestroyConnection_Param_t_
{
	SockMgr_ConnHdl_t hConn ; 
}CmdAdaptor_DestroyConnection_Param_t;

/* define param for opening socket */
typedef struct _CmdAdaptor_OpenSocket_Param_t_
{
	SockMgr_ConnHdl_t hConn ;
	SockMgr_SocketHdl_t hSocket ; // socket type can be obtained from socket handle. Ex: sAF, sType, sProtocol 
}CmdAdaptor_OpenSocket_Param_t;

/* define param for closing socket */
typedef struct _CmdAdaptor_CloseSocket_Param_t_
{
	SockMgr_ConnHdl_t hConn ;
	SockMgr_SocketHdl_t hSocket ; // socket type can be obtained from socket handle. Ex: sAF, sType, sProtocol 
}CmdAdaptor_CloseSocket_Param_t;

typedef struct _CmdAdaptor_CreateDataLink_Info_t_
{
	u32 uLocalIPAddr;
	SockMgr_ConnHdl_t hConn ; /* connection = data link + comMedia */
}CmdAdaptor_CreateDataLink_Info_t;

typedef struct _CmdAdaptor_DestroyDataLink_Info_t_
{
	// No Data
	u8 uDummy;
}CmdAdaptor_DestroyDataLink_Info_t;

typedef struct _CmdAdaptor_OpenSocket_Info_t_
{
	u8 uSocketIndex;
	u16 uClientPort;
}CmdAdaptor_OpenSocket_Info_t;

typedef struct _CmdAdaptor_CloseSocket_Info_t_
{
	u8 uSocketIndex ;
}CmdAdaptor_CloseSocket_Info_t;

typedef union
{
	CmdAdaptor_CreateDataLink_Info_t sCreateDataLinkInfo;
	CmdAdaptor_DestroyDataLink_Info_t sDestroyDataLinkInfo;
	CmdAdaptor_OpenSocket_Info_t sOpenSocketInfo;
	CmdAdaptor_CloseSocket_Info_t sCloseSocketInfo;
	const void *pvVmlRspMsg;
}CmdAdpator_RspInfoData_t;

typedef struct _CmdAdaptor_SocketRspInfo_t_
{
	CmdAdaptor_ErrCode_e eCmdAdaptorErrCode;
	CmdAdpator_RspInfoData_t uRspInfoData;
	CmdAdaptor_Version_e eVersion;
}CmdAdaptor_RspInfo_t;

typedef void (*CmdAdaptor_Cb)(u16 uSenderId, u32 uUserValue, CmdAdaptor_ErrCode_e eErrCode, CmdAdpator_RspInfoData_t *psRspInfoData) ;

typedef struct _CmdAdaptor_CbInfo_t_
{
	u16 uSenderId;
	u32 uUserValue;
	CmdAdaptor_Cb pfnCb;
}CmdAdaptor_CbInfo_t;

typedef struct _CmdAdaptor_Param_t_
{
	CmdAdaptor_CbInfo_t sCbInfo;
	void *pvVmlReqMsg;
	CmdAdaptor_Version_e eVersion;
}CmdAdaptor_Param_t;

typedef struct _CmdAdaptor_ProRspData_t_
{
	union
	{
		SocketCmdProRspInfo_t sProRspInfo;
	}uProRspData;
    void *pvVmlIndMsg;
	CmdAdaptor_Version_e eVersion;
}CmdAdaptor_ProRspData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __CMD_ADAPTOR_COMMON_H__ */
