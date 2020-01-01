#ifndef __MS_SOCKET_MSG_DEF_H__
#define __MS_SOCKET_MSG_DEF_H__

#include "ven_setting.h"
#include "ven_comdef_priv.h"
#include "ms_socket_cmn.h"

/////////////////////////////////////////////////////////////////////////////////////
///                          IMPORTANT RULE                                       ///
/////////////////////////////////////////////////////////////////////////////////////
/// pre-condition                                                                 ///
///   when mserv task startup, we must check this condition                       ///
///                                                                               ///
///   1. iVen_AsyncReq_BodyBase_t == Mserv_AsyncReq_BodyBase_t                    ///
///   2. iVen_AsyncRsp_BodyBase_t == Mserv_AsyncRsp_BodyBase_t                    ///
///   3. ven_setting_network_profile_t == Mserv_setting_network_profile_t         ///
///   4. the first field of ven_socket_t must be MS_Socket_Info_t                 ///
///   5. sizeof(ven_socket_ret_t) == sizeof(u32)                                  ///


typedef iVen_AsyncReq_BodyBase_t Mserv_AsyncReq_BodyBase_t;
typedef iVen_AsyncRsp_BodyBase_t Mserv_AsyncRsp_BodyBase_t;
typedef ven_setting_network_profile_t Mserv_setting_network_profile_t;
typedef iVen_Callback_Info_t Mserv_Callback_Info_t;

/// query data-link request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u8 *pModId;
    bool *pAvailable;
    Mserv_setting_network_profile_t NetProf;
}Mserv_socket_query_datalink_req_t;

/// query dns request
#define MSERV_HOSTNAME_LEN 0XFF
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u8 pName[MSERV_HOSTNAME_LEN]; /// host name
    u8 nTi;
    struct hostent *ppHostent;    /// output: only useful if the ReqBase.bSync is TRUE
    void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_gethostbyname_req_t;

/// query dns response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    u8 nTi;
    struct hostent *pHostent;
    void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_gethostbyname_rsp_t;

/// create datalink request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
}Mservn_socket_createsocket_req_t;

/// create socket response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
}Mserv_socket_createsocket_rsp_t;


/// close socket request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_closesocket_req_t;


/// close socket response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
	u32 RetCode;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_closesocket_rsp_t;

/// socket connect request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    struct sockaddr name;
    s32 namelen;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_connect_req_t;

/// socket connect response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
	u32 RetCode;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_connect_rsp_t;

/// register receive callback request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 flags;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
	Mserv_Callback_Info_t CbInfo;
}Mserv_socket_regRecvCB_req_t;


typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
    s32 len;
    struct sockaddr *from;
    s32 fromlen;
    s32 flags;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
    u8  *buf;
    u8  *linkmsg; /// msg from VML to be link, and to be free in vendor sdk
}Mserv_socket_recv_notify_t;


/// register receive from callback
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 flags;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	u32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	Mserv_Callback_Info_t CbInfo;
}Mserv_socket_regRecvFromCB_req_t;

/// receive from notify
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
    s32 len;
    struct sockaddr from;
    s32 fromlen;
    s32 flags;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
    u8  *buf;
    u8  *linkmsg; /// msg from VML to be link, and to be free in vendor sdk
}Mserv_socket_recvfrom_notify_t;

/// socket send request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 len;
    s32 flags;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
    u8  *buf;
}Mserv_socket_send_req_t;

/// socket send response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
	u32 RetCode;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_send_rsp_t;

/// socket sendto request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 len;
    s32 flags;
    struct sockaddr to;
    s32 tolen;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
    u8  *buf;
}Mserv_socket_sendto_req_t;

/// send to response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    Mserv_socket_t *VenSock;
	u32 RetCode;
	void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_sendto_rsp_t;

/// create datalink request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u8 nModId;
    ven_setting_network_profile_t NetProf;
    u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
    MservSocketCreateDatalinkCB pCB;
}Mserv_socket_create_datalink_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketNetworkProfile_t sProfile;
    u32      *pRetCode;                 /// output: only useful if the ReqBase.bSync is TRUE
    void *pCB;                          /// only used when async call
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_create_datalink_ex_req_t;

/// create datalink response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    u32 RetCode;
    void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_create_datalink_rsp_t;

typedef Mserv_socket_create_datalink_rsp_t Mserv_socket_create_datalink_ex_rsp_t;

/// close datalink request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;                  /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;                      /// used only when ReqBase.bSync is FALSE
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_close_datalink_req_t;

typedef Mserv_socket_close_datalink_req_t Mserv_socket_close_datalink_ex_req_t;

/// close datalink response
typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    u32 RetCode;
    void *pCB;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
}Mserv_socket_close_datalink_rsp_t;

typedef Mserv_socket_close_datalink_rsp_t Mserv_socket_close_datalink_ex_rsp_t;

typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    u32 RetCode;
    MservSocketBearer_e bearer;
	void *pvUserData;               /// used only when ReqBase.bSync is FALSE
	void *pCB;
}Mserv_socket_close_all_datalinks_ex_rsp_t;

/// receive ready request
typedef struct
{
    Mserv_socket_t *VenSock;
}Mserv_socket_receiveReady_ind_t;

/// socket receive request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 len;
    s32 flags;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
    u8  *buf;
}Mserv_socket_recv_req_t;


/// socket receive from request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 len;
    s32 flags;
    struct sockaddr *from;
    s32 *pfromlen;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
    u8  *buf;
}Mserv_socket_recvfrom_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 level;
    s32 optname;
    s8 *optval;
    s32 optlen;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_setsockopt_req_t;

/// socket get option request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 level;
    s32 optname;
    s8 *optval;
    s32 *optlen;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_getsockopt_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketQueryBearerStatusInfo_t *psBearerStatusInfo;
    u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_query_bearer_status_req;

/// shutdow request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    s32 how;
	u32 *pRetCode; /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_shutdown_req_t;

/// register status callback
//    for network
typedef struct
{
	Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;
	void *pvUserData;
	Mserv_Callback_Info_t CbInfo;
}Mserv_socket_regNetworkStatusCB_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;
}Mserv_socket_deregNetworkStatusCB_req_t;

typedef struct
{
	Mserv_AsyncRsp_BodyBase_t RspBase;
	u32 RetCode;
	void *pCB;
    void *pvUserData;
}Mserv_socket_network_status_indication_t;

/// for bearer
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;
	void *pvUserData;
	Mserv_Callback_Info_t CbInfo;
}Mserv_socket_regBearerStatusCB_req_t;

typedef struct
{
	Mserv_AsyncReq_BodyBase_t ReqBase;
	u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
	void *pCB;
}Mserv_socket_deregBearerStatusCB_req_t;

typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
	Mserv_socket_status_rsp_info_t info;
	void *pCB;
    void *pvUserData;
}Mserv_socket_bearer_status_indication_t;


/// close all datalinks
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketBearer_e bearer;
	u32 *pRetCode;                                  /// used only when ReqBase.bSync is TRUE
    void *pvUserData;                               /// used only when ReqBase.bSync is FALSE
	void *pCB;                                      /// used only when ReqBase.bSync is FALSE
}Mserv_socket_close_all_datalinks_ex_req_t;

typedef struct
{
    u8 uModuleId; /// 0      --> Master
                  /// 1      --> Slave
                  /// others --> invalid
}Mserv_bearer_gprs_t;

typedef struct
{
    u8 uDummy;
}Mserv_bearer_wifi_t;

typedef union
{
    Mserv_bearer_gprs_t sGprs;
    Mserv_bearer_wifi_t sWiFi;
}Mserv_bearer_info_u;

/// bearer status change
typedef struct
{
    MservSocketBearer_e eBearer;
    Mserv_bearer_info_u uBearerInfo;
	u32 uStatus; /// 0 --> Disconnect
	             /// 1 --> Connect
}Mserv_socket_bearer_status_ind_t;

/// ping request
typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u8 ti;
    u32 *pRetCode;
    void* pCB;
    void *pvUserData;
}Mserv_socket_ping_req_t;
/// ping response
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u8 ti;
    u32 RetCode;
    void *pvUserData;
    MservSocketPingCB pCB;
}Mserv_socket_ping_rsp_t;

typedef struct
{
    u32 uCmd;
	u32 uTimerId;
}Mserv_socket_cmd_timeout_ind_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    Mserv_socket_t *VenSock;
    void* pCB;
    struct sockaddr name;
    s32 namelen;
    u32 *pRetCode;                     /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_bind_req_t;

typedef enum
{
    MS_SOCKET_STATISTIC_TOTAL_RX = 0,
    MS_SOCKET_STATISTIC_TOTAL_TX,
    MS_SOCKET_STATISTIC_LAST_RX,
    MS_SOCKET_STATISTIC_LAST_TX,
    MS_SOCKET_STATISTIC_INVALID,
}Mserv_socket_statistic_query_e;

enum
{
    MS_SD_RECV = 0,
    MS_SD_SEND,
    MS_SD_BOTH
};

enum
{
    MS_SOL_SOCKET = 0xffffU,
    MS_SOL_IP = 0,
    MS_SOL_TCP = 6,
    MS_SOL_UDP = 17,
};
enum
{
    MS_SO_KEEPALIVE = 0x0008,
    MS_SO_LINGER = 0x0080,
    MS_SO_SNDBUF = 0x1001,
    MS_SO_RCVBUF = 0x1002,
    MS_TCP_NODELAY = 0x0001,
};

typedef struct
{
    s32 l_onoff;
    s32 l_linger;
} ms_socket_linger_t;

/// re-define struct
#define MS_BEARER_GPRS    (BEARER_GPRS)
#define MS_BEARER_WIFI    (BEARER_WIFI)
#define MS_BEARER_NUM     (BEARER_NUM)
#define MS_BEARER_INVALID (BEARER_INVALID)

/// re-define struct
#define MS_SOCKET_BEARER_DATALINK_AVAILABLE  (BEARER_DATALINK_AVAILABLE)
#define MS_SOCKET_BEARER_NO_CONNECTED_SOCKET (BEARER_NO_CONNECTED_SOCKET)
#define MS_SOCKET_STATUS_NUM                 (BEARER_STATUS_NUM)


typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketTrafficStatus_t sStatus;
    void *pCB;
    void *pvUserData;
}Mserv_socket_data_traffic_status_ind_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
    void *pCB;
    void *pvUserData;
    Mserv_Callback_Info_t CbInfo;
}Mserv_socket_regDataTrafficStatusCB_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketTrafficStatus_t *psStatus;
    /// output: only useful if the operation is successfully
    u32 *pRetCode;                                            /// output: only useful if the ReqBase.bSync is TRUE
}Mserv_socket_queryDataTrafficStatus_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;      /// output: only useful if the ReqBase.bSync is TRUE
    void *pCB;
}Mserv_socket_deregDataTrafficStatusCB_req_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketBearerInfo_t sBearerInfo;
    Mserv_socket_statistic_query_e eQueryType;
    void* pCB;
    void *pvUserData;
    u8 ti;
}Mserv_socket_statistic_query_req_t;

typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketStatisticQueryCB pCB;
    void *pvUserData;
    u32 RetCode;
    u32 Bytes;
    Mserv_socket_statistic_query_e eQueryType;
    u8 ti;
}Mserv_socket_statistic_query_rsp_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    MservSocketBearerInfo_t sBearerInfo;
    void* pCB;
    void *pvUserData;
    u8 ti;
}Mserv_socket_statistic_reset_all_req_t;

typedef struct
{
    Mserv_AsyncRsp_BodyBase_t RspBase;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketStatisticResetCB pCB;
    void *pvUserData;
    u32 RetCode;
    u8 ti;
}Mserv_socket_statistic_reset_all_rsp_t;

typedef struct
{
    Mserv_AsyncReq_BodyBase_t ReqBase;
    u32 *pRetCode;
    MservSocketBearerInfo_t sBearerInfo;
    MservSocketIPInfo_t *psIPInfo;
}Mserv_socket_getIPInfo_req;

#endif/* __MS_SOCKET_MSG_DEF_H__ */
