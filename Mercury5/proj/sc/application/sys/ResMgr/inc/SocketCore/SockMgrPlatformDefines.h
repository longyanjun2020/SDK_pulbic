#ifndef _SOCKMGR_PLATFORM_DEFINES_H_
#define _SOCKMGR_PLATFORM_DEFINES_H_

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "ResMgr_Common.h"
#include "VmlAdaptor.h"
#ifdef _RESMGR_STANDLONE_
#include "VMLFakeHeader.h"
#else
#ifdef __3G_RIL_MMI__
#include "ip_prim.hc"/* IP layer definition */
#include "ip_msg.hi"
#include "vm_ip.h"
#else //__3G_RIL_MMI__
#include "vm_vml_socket.h"
#endif //__3G_RIL_MMI__
#endif/*_RESMGR_STANDLONE_ */

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

#define SOCKMGR_INVALID_HANDLE		NULL 
#define SOCKMGR_IP_ADDRESS_STR_MAX_LEN  16      ///different from SOCKMGR_IP_ADDRESS_MAX_LEN, this is for the form of "xxx.xxx.xxx.xxx"

#define SOCKMGR_INVALID_TIMER_ID (~0)

typedef void* SockMgr_BearerHdl_t ;
typedef void* SockMgr_DataLinkHdl_t ;
typedef void* SockMgr_ComMediaHdl_t ;
typedef void* SockMgr_SocketHdl_t;
typedef void* SockMgr_ConnHdl_t;
typedef MsTimerId_e SockMgr_TimeId_t;
typedef MsMailbox_e SockMgr_MailBox_t;
typedef MsTaskId_e SockMgr_TaskId_t;

typedef enum
{
	E_SOCKMGR_BEARER_GPRS1 = 0, // GPRS1 for sim1
	E_SOCKMGR_BEARER_GPRS2,     // GPRS2 for sim2
#ifdef __WLAN_IP_SUPPORT__
	E_SOCKMGR_BEARER_WIFI,
#endif/* #ifdef __WLAN_IP_SUPPORT__ */
	E_SOCKMGR_BEARER_NUM,
	E_SOCKMGR_BEARER_INVALID,
}SockMgr_Bearer_e;

#define SOCKMGR_APP_ID_DONT_CARE 0XEE

typedef struct
{
	u8 uGprsUserName[SOCKMGR_USER_NAME_MAX_LEN];
	u8 uGprsPassWd[SOCKMGR_PASSWD_MAX_LEN];
    u8 uGprsDNS[SOCKMGR_IP_ADDRESS_MAX_LEN];
    u8 uGprsIP [SOCKMGR_IP_ADDRESS_MAX_LEN];
	u8 uGprsAPN[SOCKMGR_APN_MAX_LEN];
}SockMgr_GPRSSpecificShareData_t;

typedef struct
{
    bool bStaticIp;
    u8 uWiFiIp[SOCKMGR_IP_ADDRESS_MAX_LEN];
    u8 uWiFiDns1[SOCKMGR_IP_ADDRESS_MAX_LEN];
    u8 uWiFiDns2[SOCKMGR_IP_ADDRESS_MAX_LEN];
    u8 uWiFiSubnet[SOCKMGR_IP_ADDRESS_MAX_LEN];
    u8 uWiFiGateway[SOCKMGR_IP_ADDRESS_MAX_LEN];
}SockMgr_WiFiSpecificShareData_t;


typedef struct
{
    SockMgr_Bearer_e eBearer;
    union
    {
        SockMgr_GPRSSpecificShareData_t sGPRSShareData;
        SockMgr_WiFiSpecificShareData_t sWiFiShareData;
    }SpecificData_u;
}SockMgr_BearerInfo_t;

typedef struct
{
    ResMgr_AppId_e eAp;
    SockMgr_ConnHdl_t hConn;
    SockMgr_Bearer_e eBearer;
    union
    {
        SockMgr_GPRSSpecificShareData_t sGPRSShareData;
        SockMgr_WiFiSpecificShareData_t sWiFiShareData;
    }SpecificData_u;
}SockMgr_DataLinkShareResInfo_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
	SockMgr_SocketHdl_t hSocket;
}SockMgr_SocketResCheckInfo_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
}SockMgr_DataLinkDestroyResInfo_t;

typedef struct
{
	SockMgr_ConnHdl_t hConn;
	SockMgr_SocketHdl_t hSocket;
}SockMgr_SocketCloseResInfo_t;

typedef struct
{
	void *pvReqUserData;
	void *pvCbUserData;
    SockMgr_ConnHdl_t hConn;
    SockMgr_Bearer_e eBearer;
}SockMgr_DataLinkDestroyAllResInfo_t;

typedef union
{
	SockMgr_DataLinkShareResInfo_t sDataLinkResShareInfo;
    SockMgr_DataLinkDestroyResInfo_t sDataLinkDestroyResInfo;
    SockMgr_DataLinkDestroyAllResInfo_t sDataLinkDestroyAllResInfo;
	SockMgr_SocketResCheckInfo_t sSocketResInfo;
	SockMgr_SocketCloseResInfo_t sSocketCloseInfo;
}SockMgr_ResCheckInfo_t;


/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* _SOCKMGR_PLATFORM_DEFINES_H_ */
