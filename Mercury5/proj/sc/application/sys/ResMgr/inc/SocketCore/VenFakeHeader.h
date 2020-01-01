#ifndef __VEN_FAKE_HEADER_H__
#define __VEN_FAKE_HEADER_H__

#include "SockMgrPlatformDefines.h"

#define VEN_SETTING_MAX_LEN_PRFNAME    (10)
#define VEN_SETTING_IP_BYTESIZE        (10)
#define VEN_SETTING_MAX_LEN_SERVERURL  (10)
#define VEN_SETTING_MAX_LEN_GPRSAPN    (10)
#define VEN_SETTING_MAX_LEN_USERNAME   (10)
#define VEN_SETTING_MAX_LEN_PASSWORD   (10)

typedef unsigned int           SOCKET;

enum{
	VEN_SETTING_NETWORK_PROTOCOL_WAP=0,
	VEN_SETTING_NETWORK_PROTOCOL_HTTP,
};
typedef u8 ven_setting_network_protocol_t;

enum{
	VEN_SETTING_NETWORK_AUTH_NORMAL=0,
	VEN_SETTING_NETWORK_AUTH_SEC,
};
typedef u8 ven_setting_network_auth_t;

enum
{
    VEN_SETTING_NETWORK_CONNECTSET_WIFI_ONLY=0, 
    VEN_SETTING_NETWORK_CONNECTSET_GPRS_ONLY=1, 
    VEN_SETTING_NETWORK_CONNECTSET_WIFI_PREFERRED=2, 
    VEN_SETTING_NETWORK_CONNECTSET_GPRS_PREFERRED=3,     
};
typedef u8 ven_setting_network_connectset_t;

typedef struct{
	u16 PrfName[(VEN_SETTING_MAX_LEN_PRFNAME + 1)];  /* profile name (in UCS2) */
	u16 nProxyPort;
	ven_setting_network_protocol_t tProtocol;        /* type of WAP protocol: WAP/HTTP */
	ven_setting_network_auth_t Auth;                 /* Connect Bearer: GPRS Auth */
	u8 ServerUrl[VEN_SETTING_MAX_LEN_SERVERURL + 1]; /* Only for WAP and MMS Profile */
	u8 ProxyIp[VEN_SETTING_IP_BYTESIZE];

	u8 GprsApn[VEN_SETTING_MAX_LEN_GPRSAPN + 1];     /* Connect Bearer: GPRS APN  */
	u8 Username[VEN_SETTING_MAX_LEN_USERNAME + 1];   /* Connect Bearer: User Name */
	u8 Password[VEN_SETTING_MAX_LEN_PASSWORD + 1];   /* Connect Bearer: Password  */
	u8 DnsIp[VEN_SETTING_IP_BYTESIZE];               /* Connect Bearer: DNS IP    */
	ven_setting_network_connectset_t tConnSet;
}ven_setting_network_profile_t;

typedef enum
{
	VEN_BEARER_GPRS = 0,
#ifdef __WLAN_IP_SUPPORT__
	VEN_BEARER_WIFI,
#endif/* __WLAN_IP_SUPPORT__ */

	VEN_BEARER_NUM,
	VEN_BEARER_INVALID,
}ven_socket_bearer_t;

struct sockaddr
{
	unsigned short sa_family;              /* address family */
	char    sa_data[14];            /* up to 14 bytes of direct address */
};

struct sockproto
{
	unsigned short sp_family;              /* address family */
	unsigned short sp_protocol;            /* protocol */
};

typedef struct
{
	void *pCBFunc;
	u32 UserData;
} iVen_Callback_Info_t;

typedef struct
{
	u32 AP_ID;
	bool bSync;
	union{
		iVen_Callback_Info_t CbInfo;    ///< for async req
		u32  SemID;                     ///< for sync req
	}Resp;
} iVen_AsyncReq_BodyBase_t;

typedef struct
{
	u32 AP_ID;
	iVen_Callback_Info_t CbInfo;
} iVen_AsyncRsp_BodyBase_t;

typedef enum
{
	VEN_SOCKET_RET_SUCCESS		= 0, ///< operation completed successfully
	VEN_SOCKET_RET_BAD_PARAM	= 1, ///< invalid input parameters
	VEN_SOCKET_RET_FAILED		= 2, ///< WHAT? every code here is failed
	VEN_SOCKET_RET_OUT_OF_MEMORY	= 3, ///< memory is not enough to complete the operation
	VEN_SOCKET_RET_DATA_LINK_ALREADY_ACTIVATED = 4, ///< data link already activated
	VEN_SOCKET_RET_DATA_LINK_KO     = 5, ///< create data link failed 
	VEN_SOCKET_RET_COM_CLOSE_BY_PEER = 6, ///< com close by peer
	VEN_SOCKET_RET_CONTCP_NO_BUFFER_ERROR = 7, // con tcp no buffer error
}ven_socket_ret_t;

enum
{
	E_VEN_MASTER_SIM=0,
	E_VEN_SLAVE_SIM,
	E_VEN_NO_SIM_ACTIVE,
	E_VEN_SELECT_NONE,
};
typedef u8 ven_common_sim_id_t;

typedef struct
{
	SOCKET socket;
	u32 handle;
	s32 af;
	s32 type ;
	s32 protocol;
	u8 bSuspend;
} ven_socket_t;

typedef void* ven_socket_datalink_t ;

typedef struct
{
	ven_common_sim_id_t simid;
	u8 uApn[VEN_SETTING_MAX_LEN_GPRSAPN + 1];
	u8 uDns[VEN_SETTING_IP_BYTESIZE];
	u8 uIp[VEN_SETTING_IP_BYTESIZE];
}ven_socket_gprs_profile_ex_t;

#ifdef __WLAN_IP_SUPPORT__
typedef struct
{
	bool bStaticIp;
	u8 uIp[VEN_SETTING_IP_BYTESIZE];
	u8 uIpSubnet[VEN_SETTING_IP_BYTESIZE];
	u8 uGateway[VEN_SETTING_IP_BYTESIZE];
	u8 uDns1[VEN_SETTING_IP_BYTESIZE];
	u8 uDns2[VEN_SETTING_IP_BYTESIZE];
}ven_socket_wifi_profile_ex_t;
#endif/* __WLAN_IP_SUPPORT__ */

typedef struct
{
	ven_socket_bearer_t bearer;
	union
	{
		ven_socket_gprs_profile_ex_t sGprs;
#ifdef __WLAN_IP_SUPPORT__
		ven_socket_wifi_profile_ex_t sWifi;
#endif/* __WLAN_IP_SUPPORT__ */
	}profile_u;
}ven_socket_network_profile_ex_t;

typedef void (*ven_socket_recv_cbfunc_t) (ven_socket_t *s, u8 *buf, s32 len);
typedef void (*ven_socket_recvfrom_cbfunc_t) (ven_socket_t *s, u8 *buf, s32 len, struct sockaddr *from, s32 fromlen);
typedef void (*ven_socket_connect_cbfunc_t) (ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_gethostbyname_cbfunc_t) (u8 ti, struct hostent *host);
typedef void (*ven_socket_send_cbfunc_t) (ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_sendto_cbfunc_t) (ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_closesocket_cbfunc_t) (ven_socket_t *s, ven_socket_ret_t result);
typedef void (*ven_socket_create_datalink_cbfunc_t) (ven_socket_ret_t result);
typedef void (*ven_socket_close_datalink_cbfunc_t) (ven_socket_ret_t result);
typedef void (*ven_socket_status_cbfunc_t) (ven_socket_ret_t result);
typedef void (*ven_socket_create_datalink_ex_cbfunc_t)(ven_socket_datalink_t datalink, void* pvUserData, ven_socket_ret_t result);
typedef void (*ven_socket_close_datalink_ex_cbfunc_t)(ven_socket_datalink_t datalink, void* pvUserData, ven_socket_ret_t result);


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETHOSTBYNAME_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : gethostbyname                                               */
/*                                                                          */
/*  Structure : iVen_socket_gethostbyname_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
#define VEN_HOSTNAME_LEN 0xff
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	u8 pName[VEN_HOSTNAME_LEN]; // host name
	u8 nTi;
	struct hostent *ppHostent; //output: only useful if the ReqBase.bSync is TRUE
	ven_socket_gethostbyname_cbfunc_t pCB;
}iVen_socket_gethostbyname_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETHOSTBYNAME_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : gethostbyname                                               */
/*                                                                          */
/*  Structure : iVen_socket_gethostbyname_rsp_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	u8 nTi;
	struct hostent *pHostent;
	ven_socket_gethostbyname_cbfunc_t pCB;
}iVen_socket_gethostbyname_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATESOCKET_REQ                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_createsocket_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_createsocket_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATESOCKET_RSP                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_createsocket_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
}iVen_socket_createsocket_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSESOCKET_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_closesocket_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	ven_socket_closesocket_cbfunc_t pCB;
}iVen_socket_closesocket_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSESOCKET_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_close_socket_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 RetCode;
	ven_socket_closesocket_cbfunc_t pCB;
}iVen_socket_closesocket_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CONNECT_REQ                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_connect_req_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	struct sockaddr name;
	s32 namelen;
	ven_socket_connect_cbfunc_t pCB;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_connect_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CONNECT_RSP                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_connect_rsp_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 RetCode;
	ven_socket_connect_cbfunc_t pCB;
}iVen_socket_connect_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REGRECVCB_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regRecvCB_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 flags;
	ven_socket_recv_cbfunc_t pCB;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_regRecvCB_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECV_NOTIFY                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recv_notify_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 len;
	struct sockaddr *from;
	s32 fromlen;
	s32 flags;
	ven_socket_recv_cbfunc_t pCB;
	u8  *buf;
	u8  *linkmsg; // msg from VML to be link, and to be free in vendor sdk
}iVen_socket_recv_notify_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REGRECVFROMCB_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regRecvFromCB_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 flags;
	ven_socket_recvfrom_cbfunc_t pCB;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_regRecvFromCB_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECVFROM_NOTIFY                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recvfrom_notify_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 len;
	struct sockaddr from;
	s32 fromlen;
	s32 flags;
	ven_socket_recvfrom_cbfunc_t pCB;
	u8  *buf;
	u8  *linkmsg; // msg from VML to be link, and to be free in vendor sdk
}iVen_socket_recvfrom_notify_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SEND_REQ                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_send_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 len;
	s32 flags;
	ven_socket_send_cbfunc_t pCB;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	u8  *buf;
}iVen_socket_send_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SEND_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_send_rsp_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 RetCode;
	ven_socket_send_cbfunc_t pCB;
}iVen_socket_send_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SENDTO_REQ                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_sendto_req_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 len;
	s32 flags;
	struct sockaddr to;
	s32 tolen;
	ven_socket_sendto_cbfunc_t pCB;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	u8  *buf;
}iVen_socket_sendto_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SENDTO_RSP                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_sendto_rsp_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_t *VenSock;
	s32 RetCode;
	ven_socket_sendto_cbfunc_t pCB;
}iVen_socket_sendto_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATE_DATALINK_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : create_datalink                                             */
/*                                                                          */
/*  Structure : iVen_socket_create_datalink_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	u8 nModId;
	ven_setting_network_profile_t NetProf;
	ven_socket_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	ven_socket_create_datalink_cbfunc_t pCB;
}iVen_socket_create_datalink_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u8 nProfileNum;
    ven_socket_network_profile_ex_t sProfile[VEN_BEARER_NUM];
    ven_socket_ret_t      *pRetCode;             /// output: only useful if the ReqBase.bSync is TRUE
    union
    {
        ven_socket_datalink_t *pdatalink;        /// output: only useful if the ReqBase.bSync is TRUE
        ven_socket_datalink_t datalink;          /// output: only useful if the ReqBase.bSync is FALSE
    }uDataLink;
    void *pvUserData;                            /// only used when async call
    ven_socket_create_datalink_ex_cbfunc_t pCB;  /// only used when async call
}iVen_socket_create_datalink_ex_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATE_DATALINK_RSP                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : create_datalink                                             */
/*                                                                          */
/*  Structure : iVen_socket_create_datalink_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_ret_t RetCode;
	ven_socket_create_datalink_cbfunc_t pCB;
}iVen_socket_create_datalink_rsp_t;

typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_ret_t RetCode;
	ven_socket_datalink_t datalink;
	void *pvUserData;
	ven_socket_create_datalink_ex_cbfunc_t pCB;
}iVen_socket_create_datalink_ex_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSE_DATALINK_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : close_datalink                                              */
/*                                                                          */
/*  Structure : iVen_socket_close_datalink_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	ven_socket_close_datalink_cbfunc_t pCB;
}iVen_socket_close_datalink_req_t;

typedef struct
{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_ret_t *pRetCode;                // output: only useful if the ReqBase.bSync is TRUE
	ven_socket_datalink_t datalink;
	void *pvUserData;                          // used only when ReqBase.bSync is FALSE
	ven_socket_close_datalink_ex_cbfunc_t pCB; // used only when ReqBase.bSync is FALSE
}iVen_socket_close_datalink_ex_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSE_DATALINK_RSP                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : close_datalink                                              */
/*                                                                          */
/*  Structure : iVen_socket_close_datalink_rsp_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_ret_t RetCode;
	ven_socket_close_datalink_cbfunc_t pCB;
}iVen_socket_close_datalink_rsp_t;

typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_ret_t RetCode;
	ven_socket_datalink_t datalink;
	void *pvUserData;
	ven_socket_close_datalink_ex_cbfunc_t pCB;
}iVen_socket_close_datalink_ex_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECEIVE_READY_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_receiveReady_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	ven_socket_t *VenSock;
}iVen_socket_receiveReady_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECV_REQ                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recv_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 len;
	s32 flags;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	u8  *buf;
}iVen_socket_recv_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECVFROM_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recvfrom_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 len;
	s32 flags;
	struct sockaddr *from;
	s32 *pfromlen;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	u8  *buf;
}iVen_socket_recvfrom_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SETSOCKOPT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_setsockopt_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 level;
	s32 optname;
	s8 *optval;
	s32 optlen;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_setsockopt_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETSOCKOPT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_getsockopt_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 level;
	s32 optname;
	s8 *optval;
	s32 *optlen;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_getsockopt_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SHUTDOWN_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_shutdown_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
	s32 how;
	s32 *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
}iVen_socket_shutdown_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REG_STATUS_CB_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regStatusCB_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
	ven_socket_status_cbfunc_t pCB;
}iVen_socket_regStatusCB_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_STATUS_INDICATION                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_status_indication_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_socket_ret_t RetCode;
	ven_socket_status_cbfunc_t pCB;
}iVen_socket_status_indication_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_DEQUE                                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to Vendor                                       */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_deque_req_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct{
	iVen_AsyncReq_BodyBase_t ReqBase;
	ven_socket_t *VenSock;
}iVen_socket_deque_req_t;


#endif/* __VEN_FAKE_HEADER_H__ */
