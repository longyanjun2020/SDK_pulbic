#ifndef __MS_SOCKET_CMN_H__
#define __MS_SOCKET_CMN_H__

/**
* @file ms_socket_cmn.h
*
* This header file defines the common struct for socket clients
*
*/
#include "vm_types.ht"
#include "winsocket.h"

#if defined(__NETWORK_COUNTER_MMI__)
#define __NETWORK_FLOW_STATISTIC__
#endif /// __NETWORK_COUNTER_MMI__

#define SOCKET_ERROR            (-1)
#define SOCKET_OK               (0)

#ifdef __SDK_SIMULATION__
#ifndef ASSERT
#define ASSERT(x)  {assert(x);}
#endif/* ASSERT */
#else
#ifndef ASSERT
#define ASSERT(x)       {if(!(x)){\
    extern void ker_assert_func(u8 *str, u8 *file, u32 line);\
    ker_assert_func((u8*)#x, (u8*)__FILE__, __LINE__);}}
#endif/* ASSERT */
#endif/* __PC_SIMULATOR__ */

#define MSERV_BEARER_USERNAME_LEN (31+1)
#define MSERV_BEARER_PASSWD_LEN   (31+1)
#define MSERV_BEARER_APN_LEN      (50+1)
#define MSERV_BEARER_IP_LEN       (4)

/// pre-condition: 
///   it shouldn't define the same value with those in ven_socket_ret_t
#define MSERV_NETWORK_STATUS_DATALINK_CLOSE_BY_PEER (0x06)
#define MSERV_NETWORK_STATUS_INVALID                (0xFF)

#define MSERV_SET_U32_AS_IP(x,y)    ((x)[0]=(u8)((y)>>24),(x)[1]=(u8)((y)>>16),(x)[2]=(u8)((y)>>8),(x)[3]=(u8)(y))
#define MSERV_DEFAULT_THRESHOLD (90)

/// for backward compatible
#define E_VEN_MASTER_SIM    SIM_ONE
#define E_VEN_SLAVE_SIM     SIM_TWO
#define E_VEN_NO_SIM_ACTIVE NO_SIM_ACTIVE
#define E_VEN_SELECT_NONE   NO_SIM_SELECT

enum
{
    SIM_ONE = 0x00,
    SIM_TWO,
    NO_SIM_ACTIVE,
    NO_SIM_SELECT,
};

enum
{
    MSERV_SOL_SOCKET = 0xffffU,
    MSERV_SOL_IP = 0,
    MSERV_SOL_TCP = 6,
    MSERV_SOL_UDP = 17,
};

enum
{
    MSERV_SO_KEEPALIVE = 0x0008,
    MSERV_SO_LINGER = 0x0080,
    MSERV_SO_SNDBUF = 0x1001,
    MSERV_SO_RCVBUF = 0x1002,
    MSERV_TCP_NODELAY = 0x0001,
    MSERV_SO_RCVMODE   = 0x0002,
};

enum
{
    MSERV_SD_RECV = 0,
    MSERV_SD_SEND,
    MSERV_SD_BOTH
};

typedef enum
{
    MSERV_IPV4 = 0X00,
}MservSocketIPFormat_e;

typedef enum
{
    MSERV_CAPABILITY_SUPPORT_GPRS_MULTIDATALINK_E = 0,
    MSERV_CAPABILITY_SUPPORT_WIFI_E,
    MSERV_CAPABILITY_SUPPORT_UDP_FLOW_CONTROL_E,
    MSERV_CAPABILITY_SUPPORT_NUM_E,
}MservCapability_e;

///NOTE: warnings may be produced because of casting from enum to u8
typedef u8 MservSocketSim_e;
typedef void* MservSocketTrafficStatus_t;

typedef struct
{
    s32 l_onoff;
    s32 l_linger;
}Mserv_socket_linger_t;

typedef enum
{
    BEARER_GPRS = 0x00,
    BEARER_WIFI = 0x01,
    BEARER_NUM  = 0x02,
    BEARER_INVALID,
}MservSocketBearer_e;

typedef enum
{
    BEARER_DATALINK_AVAILABLE = 0x00,
    BEARER_NO_CONNECTED_SOCKET,
    BEARER_STATUS_NUM,
}Mserv_socket_bearer_status_e;

typedef struct
{
    MservSocketBearer_e bearer;     /// indicate the status of specific bearer
    bool bStatus;                   /// indicate whether the status is true
}Mserv_socket_datalink_status_rsp_info_t;

typedef struct
{
    MservSocketBearer_e bearer;     /// indicate the status of specific bearer
    bool bStatus;                   /// indicate whether the status is true
    MservSocketSim_e simid;         /// indicate the sim id, only for gprs
}Mserv_socket_bearer_status_rsp_info_t;

typedef struct
{
    Mserv_socket_bearer_status_e status;
    union
    {
        Mserv_socket_bearer_status_rsp_info_t sBearerInfo;
        Mserv_socket_datalink_status_rsp_info_t sDataLinkInfo;
    } rsp_data_u;
}Mserv_socket_status_rsp_info_t;

typedef struct
{
    MservSocketSim_e eSimId;
}MservSocketGprsDataTrafficStatus_t;

typedef struct
{
    u8 uDummy;
}MservSocketWiFiDataTrafficStatus_t;

typedef struct
{
    MservSocketBearer_e eBeaerer;
    union
    {
        MservSocketGprsDataTrafficStatus_t sGprsDataTrafficStatus;
        MservSocketWiFiDataTrafficStatus_t sWiFiDataTrafficStatus;
    }uBearerDataTrafficStatus_t;
}MservSocketBearerInfo_t;

typedef struct
{
    bool bDataLinkAvailable;
    bool bHasConnectedSocket;
}MservSocketQueryBearerStatusInfo_t;

typedef struct
{
    MservSocketSim_e simid;
    u8 uUserName[MSERV_BEARER_USERNAME_LEN];
    u8 uPassWd[MSERV_BEARER_PASSWD_LEN];
    u8 uApn[MSERV_BEARER_APN_LEN];
    u8 uDns[MSERV_BEARER_IP_LEN];
    u8 uIp[MSERV_BEARER_IP_LEN];
}MservBearerGprsProfile_t;

typedef struct
{
    bool bStaticIp;
    u8 uIp[MSERV_BEARER_IP_LEN];
    u8 uIpSubnet[MSERV_BEARER_IP_LEN];
    u8 uGateway[MSERV_BEARER_IP_LEN];
    u8 uDns1[MSERV_BEARER_IP_LEN];
    u8 uDns2[MSERV_BEARER_IP_LEN];
}MservBearerWiFiProfile_t;

typedef struct
{
    MservSocketBearer_e bearer;
    union
    {
        MservBearerGprsProfile_t sGprs;
        MservBearerWiFiProfile_t sWifi;
    }profile_u;
}MservSocketNetworkProfile_t;

typedef struct
{
    bool bNoSimActive;
}MservSocketGprsInfo_t;

typedef struct
{
    bool bAvailable;
    union
    {
        MservSocketGprsInfo_t sGprsExtraInfo;
    }uBearerExtraInfo;
}MservSocketQueryDatalink_t;

typedef struct
{
    SOCKET socket; /// SOCKET is equal Ms_Socket_Info_t
    u32 handle ;
    s32 af ;
    s32 type ;
    s32 protocol ;
    u8 bSuspend;
}Mserv_socket_t;

typedef struct
{
    SOCKET socket; /// SOCKET is equal Ms_Socket_Info_t
    u32 handle ;
    s32 af ;
    s32 type ;
    s32 protocol ;
    u8 bSuspend;
    void *pvRecvValidationData;
    void *pvRecvFromValidationData;
}Mserv_socket_ex_t;

typedef struct
{
    MservSocketIPFormat_e eFormat;
    u8   nIPNum;
    u32 *pnIPAddr;
}MservSocketIPInfo_t;

/// define callbacks
typedef void (*MservSocketRecvCB)(SOCKET s, u8 *buf, s32 len);
typedef void (*MservSocketRecvFromCB)(SOCKET s, u8 *buf, s32 len, struct sockaddr *from, s32 fromlen);
typedef void (*MservSocketConnectCB)(SOCKET s, u32 result);
typedef void (*MservSocketGetHostByNameCB)(u8 ti, struct hostent *host);
typedef void (*MservSocketSendCB)(SOCKET s, u32 result);
typedef void (*MservSocketSendToCB)(SOCKET s, u32 result);
typedef void (*MservSocketCloseSocketCB)(SOCKET s, u32 result);
typedef void (*MservSocketCreateDatalinkCB) (u32 result);
typedef void (*MservSocketCloseDatalinkCB)(u32 result);
typedef void (*MservSocketStatusCB)(u32 result);
typedef void (*MservSocketStatusExCB)(void *pvUserData, Mserv_socket_status_rsp_info_t *pinfo);
typedef void (*MservSocketCloseAllDatalinkCB)(MservSocketBearer_e bearer, void* pvUserData, u32 result);
typedef void (*MservSocketPingCB)(u8 ti, u32 result);
typedef void (*MservSocketStatisticQueryCB)(u8 ti, u32 bytes, void *pvUserData, u32 result);
typedef void (*MservSocketStatisticResetCB)(u8 ti, void *pvUserData, u32 result);

SOCKET MservCreateSocket(u32 uResMgrAppId, u8 uSocketType, Mserv_socket_t *psWrapperSocket, bool bUseExtApi);

bool MservMayOverWhelmTask(u16 uTaskNo);
bool MservIsSupportBind(Mserv_socket_t *psWrapperSocket);
bool MservIsValidSocket(Mserv_socket_t *psWrapperSocket);
bool MservCanBindDatalink(Mserv_socket_t *psWrapperSocket);
bool MservIsValidBearerInfo(MservSocketBearerInfo_t *psBearerInfo);

void MservSocketCmnHdlr(void *pvMsg);
void MservSockettHasTraffic(MservSocketTrafficStatus_t pStatus, bool *pbHas);
void MservSocketFreeIPInfo(const MservSocketIPInfo_t *cpsIpInfo);

const MservSocketIPInfo_t* MservSocketAllocIPInfo(void);

bool MservQueryCapability(MservCapability_e eCapability);
void MservInitCapability(MservCapability_e eCapability, bool bSupport);

u32  MservVenId2SocketId(u32 uVenId);
void MservPrintAsciiString(u8 *u8String);
#endif/* __MS_SOCKET_CMN_H__ */
