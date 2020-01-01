/**
 * @file    http.h
  */
#ifndef __HTTP_H__
#define __HTTP_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "nccwhttp.h"
#include "http_pub.h"
#include "ven_socket.h"
#include "ven_setting.h"
#include "ven_wlan.h"
#include "GenEvtHdlrItf.h"
#include "mdl_avp_streaming_interface.h"
/*=============================================================*/
// types define
/*=============================================================*/
#define MAX_HTTP_CONNECT_COUNT 40
#define HTTP_GPRS_SEGMENT_SIZE 30 * 1024
#define HTTP_WIFI_SEGMENT_SIZE 240 * 1024

enum
{
    HTTP_DOWNLOAD_REQ__GROUP = 0x0000,
	HTTP_DOWNLOAD_REQ__OPEN_DATALINK = HTTP_DOWNLOAD_REQ__GROUP,
    HTTP_DOWNLOAD_REQ__CLOSE_DATALINK,
    HTTP_DOWNLOAD_REQ__OPEN_DL_HANDLE,
    HTTP_DOWNLOAD_REQ__CLOSE_DL_HANDLE,
    HTTP_DOWNLOAD_REQ__START,
    HTTP_DOWNLOAD_REQ__STOP,
	HTTP_DOWNLOAD_REQ__SUSPEND,
    HTTP_DOWNLOAD_REQ__RESUME,
    HTTP_DOWNLOAD_REQ__SEEK,
    HTTP_DOWNLOAD_REQ__DATA_CONSUMED,

    HTTP_DOWNLOAD_REQ__START_CONFIRMED,
    HTTP_DOWNLOAD_REQ__SEEK_CONFIRMED,
    HTTP_DOWNLOAD_REQ__GET_DATA,
    HTTP_DOWNLOAD_REQ__GET_NEXT_SEGMENT,

    HTTP_DOWNLOAD_RSP__GROUP = 0x0100,
	HTTP_DOWNLOAD_RSP__OPEN_DATALINK = HTTP_DOWNLOAD_RSP__GROUP,
    HTTP_DOWNLOAD_RSP__CLOSE_DATALINK,
    HTTP_DOWNLOAD_RSP__OPEN_DL_HANDLE,
    HTTP_DOWNLOAD_RSP__CLOSE_DL_HANDLE,
    HTTP_DOWNLOAD_RSP__START,
    HTTP_DOWNLOAD_RSP__STOP,
	HTTP_DOWNLOAD_RSP__SUSPEND,
    HTTP_DOWNLOAD_RSP__RESUME,
    HTTP_DOWNLOAD_RSP__SEEK,

    HTTP_DOWNLOAD_NOTIFY__GROUP = 0x0200,
	HTTP_DOWNLOAD_NOTIFY__OPEN_COMPLETE = HTTP_DOWNLOAD_NOTIFY__GROUP,
	HTTP_DOWNLOAD_NOTIFY__OPEN_ERROR,
    HTTP_DOWNLOAD_NOTIFY__START_COMPLETE,
    HTTP_DOWNLOAD_NOTIFY__START_ERROR,
    HTTP_DOWNLOAD_NOTIFY__SEEK_COMPLETE,
    HTTP_DOWNLOAD_NOTIFY__SEEK_ERROR,
    HTTP_DOWNLOAD_NOTIFY__DOWNLOAD_COMPLETE,
    HTTP_DOWNLOAD_NOTIFY__DOWNLOAD_ERROR,
    HTTP_DOWNLOAD_NOTIFY__DATALINK_ERROR,
};
typedef u32 HttpDownloadEvent_e;

enum
{
    HTTP_DOWNLOAD_STATE__IDLE = 0,
    HTTP_DOWNLOAD_STATE__CONNECT,
    HTTP_DOWNLOAD_STATE__DOWNLOAD,
    HTTP_DOWNLOAD_STATE__SUSPEND,
    HTTP_DOWNLOAD_STATE__DOWNLOAD_STOPPED
};
typedef u16 HttpDownloadState_e;

enum
{
    HTTP_LINK_STATE__IDLE = 0,
    HTTP_LINK_STATE__TO_DATALINK,  //Waiting for data link callback
    HTTP_LINK_STATE__DATALINK,     //Create data link success
};
typedef u8 HttpLinkState_e;

enum
{
    HTTP_LINK_TYPE__WIFI = 0,
    HTTP_LINK_TYPE__GPRS_SIM1,
    HTTP_LINK_TYPE__GPRS_SIM2,
};
typedef u8 HttpLinkType_e;

typedef void *HttpDownloadHdl_t;

typedef struct
{
    void *pfnLinkStatusCb;
    HttpLinkType_e eDatalinkType;
} HttpOpenDatalinkParam_t;

typedef struct
{
    u32 nUser;
    u32 nNotifyThreshold;
    void *pfnDownloadStatusCb;
} HttpDownloadOpenHdlParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
} HttpDownloadCloseHdlParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
    u16 *pDownloadUrl;
    s32 sStartBytes;
	s32 sEndBytes;
} HttpDownloadStartParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
} HttpDownloadStopParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
} HttpDownloadSuspendParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
} HttpDownloadResumeParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
    s32 sSeekByte;
} HttpDownloadSeekParam_t;

typedef struct
{
    HttpDownloadHdl_t pDownloadHdl;
    void *pData;
    u32 nDataSize;
} HttpDownloadDataConsumedParam_t;

typedef struct
{
    HttpDownloadEvent_e eRequestType;
    union
    {
        HttpOpenDatalinkParam_t tOpenDatalinkParam;
        HttpDownloadOpenHdlParam_t tOpenHdlParam;
        HttpDownloadCloseHdlParam_t tCloseHdlParam;
        HttpDownloadStartParam_t tStartParam;
        HttpDownloadStopParam_t tStopParam;
        HttpDownloadSuspendParam_t tSuspendParam;
        HttpDownloadResumeParam_t tResumeParam;
        HttpDownloadSeekParam_t tSeekParam;
        HttpDownloadDataConsumedParam_t tDataConsumeParam;
    } uParam;
} HttpDownloadRequest_t;

typedef struct
{
    u32 nUser;
    void *pfnUserCallback;
} HttpUserInfo_t;

typedef struct
{
    s32 sGetDataPeriod;
    u32 nDefBufferSize;
    s32 sSegmentSize;
} HttpDataCtrlParam_t;

typedef struct
{
    HttpUserInfo_t tDownloadUser;

    /*Download parameters*/
    u8 *pDownloadUrl;
    s32 sStartBytes;
    s32 sEndBytes;

    /*Buffer information*/
    u8 *pDataBuffer;
    u32 nBufferSize;
    u32 nWaterMark;
    u32 nUnconfirmedSize;
    u32 nNotifyThreshold;

    /*Content information*/
    HTTPCTXT *pHttpContext;
    s32 sCurrByte;
    s32 sTotalByte;

    /*State information*/
    u8 nConnectCount;
    GenEvtHdlrHdl_t pEvtHdlrHdl;
}HttpDownloadInfo_t;

typedef struct
{
    u32 nVenHandle;
    HttpLinkState_e eLinkState;
    HttpDataCtrlParam_t *pDataCtrlParam;

    HttpUserInfo_t tLinkUser;
    HttpDownloadInfo_t *pDownloadInfo;
} HttpLinkStatus_t;

/*For Unittest only*/
void _HttpProcessOpenDatalinkReq(HttpOpenDatalinkParam_t *pReqParam);
void _HttpProcessCloseDatalinkReq(void);
void _HttpProcessDownloadOpenHdlReq(HttpDownloadOpenHdlParam_t *pReqParam);
void _HttpProcessDownloadCloseHdlReq(HttpDownloadCloseHdlParam_t *pReqParam);
void _HttpProcessDownloadStartReq(HttpDownloadStartParam_t *pReqParam);
void _HttpProcessDownloadStopReq(HttpDownloadStopParam_t *pReqParam);
void _HttpProcessDownloadSuspendReq(HttpDownloadSuspendParam_t *pReqParam);
void _HttpProcessDownloadResumeReq(HttpDownloadResumeParam_t *pReqParam);
void _HttpProcessDownloadSeekReq(HttpDownloadSeekParam_t *pReqParam);
void _HttpProcessDownloadDataConsumedReq(HttpDownloadDataConsumedParam_t *pReqParam);
void _HttpCreateDataLinkCb(ven_socket_ret_t eRet);
void _HttpSocketStatusCheckCb(ven_socket_ret_t eRet);
void _HttpTimerCb(u16 nTimerId);

HttpLinkStatus_t* HttpTestGetLinkStatus(void);

#endif //__HTTP_H__
