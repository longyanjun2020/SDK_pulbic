#ifndef  __MMI_NTP_H__
#define __MMI_NTP_H__
#include "mmi_mae_common_def.h"
#include "mmi_srv_socket.h"
#include "winsocket.h"


#define NTP_PORT 	                        123                     //NTP server port number

#define NTP_SEND_REQ_RETRY_PERIOD           1200                    // 1.2 secs
#define NTP_SEND_REQ_RETRY_TIMES            20                      // 15 times for retry (note: 1200 X 15 should smaller than monitor period)
#define NTP_MONITOR_REQ_PERIOD              30000                   // 30 secs
#define NTP_TIME_FORMAT_STRING_LEN          20                      // %d-%d-%d %d:%d (YYYY-MM-DD HH:MM)

typedef struct NtpPacketDataTag
{
    s8 head[4];
    s8 root_delay[4];
    s8 root_dispersion[4];
    s8 reference_identifier[4];
    s8 reference_timestamp[8];
    s8 originate_timestamp[8];
    s8 receive_timestamp[8];
    s8 transmit_timestamp[8];
} NtpPacketData_t;


typedef struct NtpTmtag
{
    s32 nSec;     /* seconds after the minute - [0,59] */
    s32 nMin;     /* minutes after the hour - [0,59] */
    s32 nHour;    /* hours since midnight - [0,23] */
    s32 nMday;    /* day of the month - [1,31] */
    s32 nMonth;   /* months since January - [0,11] */
    s32 nYear;    /* years since 1900 */
    s32 nWday;    /* days since Sunday - [0,6] */
    s32 nYday;    /* days since January 1 - [0,365] */
    s32 nIsdst;   /* daylight savings time flag */
}NtpTm_t;

typedef struct NtpNetworkDatatag
{
    SrvSocketHdl_t sock;
    struct sockaddr_in sockDest;
    bool bIsUninit; 
    NtpPacketData_t tPacketData;
    NtpTm_t tTimeData;
    SrvSocketNetworkProfile_t tProfileData;
}NtpNetworkData_t;


/*=============================================================*/
// function definition
/*=============================================================*/
MAE_Ret _NtpAppCreateDataLink(void *pApplet, SrvSocketCreateDatalinkCB pFnCb);
MAE_Ret _NtpAppDestroyDataLink(void);

void _NtpAppCreateDataLinkCB(IBase *piCaller, void *pUserData, MAE_Ret nResult);
static void _NtpAppCloseDataLinkCB(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
static void _NtpAppSendToCB(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
static void _NtpAppRecvFromCB(IBase *piCaller, SrvSocketHdl_t hSocket, u8 *buf, s32 len, struct sockaddr *from, s32 fromlen, void *pvUserData);



void _NtpAppGetTime(void* pOwner);
void _NtpAppSendGetTimePacket(void *pOwner);
void _NtpAppMonitorSyncTime(void *pOwner);
void _NtpAppLocaltime(int time, NtpTm_t *pTmTime);
void _NtpAppUnInitNetwork(void *pApplet);

#endif //__MMI_NTP_H__

