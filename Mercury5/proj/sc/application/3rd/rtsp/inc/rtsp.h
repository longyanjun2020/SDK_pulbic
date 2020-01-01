/**
 * @file    rtsp.h
  */
#ifndef __RTSP_H__
#define __RTSP_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "ven_std.h"
#include "cus_msg.hc"
#include "rtsp_struct.h"
#include "rtspmonitor.h"
#include "ven_socket.h"
#include "mdl_avp_streaming_interface.h"
/*=============================================================*/
// types define
/*=============================================================*/
#define RTSP_SLOWDOWN_ENABLE    1

#define _TRACE_RTSP           (VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_19)		// cus5_19

#define RTSP_RSP_TIMEOUT_TIMER (60*1000)
#define RTSP_ALIVE_RSP_TIMEOUT_TIMER (500)
#define RTSP_SEND_ALIVE_TIMER_PLAY (60*1000)
#define RTSP_SEND_ALIVE_TIMER_PAUSE (60*1000)
#define RTSP_AUTO_SEND_RTP_TIMER (1*1000)
#define RTSP_CHECK_RTP_COMEBACK_TIMER (300)
#define RTSP_AUTO_SEND_RTP_PKT_TIMER (1*1000)
#define RTSP_MAX_PENDING_REQ_NUM (5)
#define RTSP_EVT_QUEUE_SIZE (7)
#define RTSP_PORTNUM (554)
#define RTSP_MAX_STRLEN_RANGE (20)
#define RTSP_MAX_STRLEN_SESSION (50)
#define RTSP_MAX_TRACKNAME_LEN (20)
#define parseBufferSize (100)
#define RTSP_bzero(addr,len)   ven_std_memset((addr),0,(len))
#define REQUEST_MSG_SIZE    (512)
#define RTSP_DATATAG_SDP "SDP1"
#define RTSP_DATATAG_RTP "RTP1"
#define RTSP_CONSUME_NUM_NORMAL (3)
#define RTSP_CONSUME_NUM_LEVEL_1 (4)
#define RTSP_CONSUME_NUM_LEVEL_2 (5)
#define RTSP_CACHE_SIZE    (1500)
#define RTCP_CACHE_SIZE    (256)
#define RTP_VIDEO_CACHE_SIZE   (1500)
#define RTP_AUDIO_CACHE_SIZE   (512)
#define RTSP_INERLEAVE_CACHE_SIZE (RTP_VIDEO_CACHE_SIZE)
#define RTSP_BITRATE_LIMIT      (500)

typedef enum rtspNetState_e_
{
    RTSP_NET_INVALID = 0,
    RTSP_NET_OPENING,
    RTSP_NET_OK,
    RTSP_NET_FAIL
} rtspNetState_e;

typedef enum rtspItfType_e_
{
    RTSP_ITF_RTP = 0,
    RTSP_ITF_RTCP,
    RTSP_ITF_MAX
}rtspItfType_e;

typedef enum rtspTrackType_e_
{
    RTSP_TRACK_VIDEO = 0,
    RTSP_TRACK_AUDIO,
    RTSP_TRACK_RESERVED,
    RTSP_TRACK_NUM
}rtspTrackType_e;

typedef struct rtspTrackInfo_t_
{
    RtcpInstance_t   *pRtcp_inst;
    NetItfIndex tTrackItfIdx[RTSP_ITF_MAX]; // One is for RTP and the other is for RTCP
    rtspNetState_e eNetState[RTSP_ITF_MAX];
    NetItfConnectObj *pConnectObj[RTSP_ITF_MAX];
    NetItfBufferObj *pCacheBufObj[RTSP_ITF_MAX];
    u8  name[RTSP_MAX_TRACKNAME_LEN];
    bool bIsEnable;
    u32 svr_port;
    u32 bandwidth;
    u32 timestamp_freq;
    u16 clientport;
    u32 nRtpSeqNum;
    u32 nRtpTime;
    u32 nChannelNum;
    bool bIsReceiveRtp;
} rtspTrackInfo_t;

typedef enum rtspReqCmd_e_
{
    RTSP_REQ_INVALID = 0,
    RTSP_REQ_DESCRIBE,
    RTSP_REQ_SETUP,
    RTSP_REQ_PLAY,
    RTSP_REQ_TEARDOWN,
    RTSP_REQ_PAUSE,
    RTSP_REQ_OPTIONS,
    RTSP_REQ_ANNOUNCE,
    RTSP_REQ_GET_PARAMETER,
    RTSP_REQ_SET_PARAMETER,
    RTSP_REQ_RECORD,
    RTSP_REQ_REDIRECT
} rtspReqCmd_e;

typedef struct rtspPendingReq_t_
{
    rtspReqCmd_e eReqCmd;
    u32 nSeqNo;
    void *pRtspMd;
}rtspPendingReq_t;

typedef enum rtspState_e_
{
    RTSP_STATE_IDLE = 0,
    RTSP_STATE_INIT,
    RTSP_STATE_UNINIT,
    RTSP_STATE_READY,
    RTSP_STATE_PLAYING,
    RTSP_STATE_STOPING,
    RTSP_STATE_SLOWDOWN,
    RTSP_STATE_ERROR
} rtspState_e;

#define RTSP_GET_EVT_GROUP(_EVT_) ((_EVT_) & 0xFF00)
typedef enum rtspEvtType_e_
{
    RTSP_EVT_INVALID = 0x0000,

    RTSP_EVT_GROUP_REQ = 0x0100,
    RTSP_EVT_PLAY_REQ = RTSP_EVT_GROUP_REQ,
    RTSP_EVT_STOP_REQ,
    RTSP_EVT_PAUSE_REQ,
    RTSP_EVT_RESUME_REQ,
    RTSP_EVT_SEEK_REQ,

    RTSP_EVT_GROUP_INT_REQ = 0x0200,
    RTSP_EVT_SELF_PAUSE_REQ = RTSP_EVT_GROUP_INT_REQ,
    RTSP_EVT_SELF_PLAY_REQ,
    RTSP_EVT_REDIRECT_REQ,
    RTSP_EVT_KEEPALIVE_REQ,

    RTSP_EVT_GROUP_2IDLE_REQ = 0x0300,
    RTSP_EVT_BACK2IDLE_EOS_REQ = RTSP_EVT_GROUP_2IDLE_REQ,
    RTSP_EVT_BACK2IDLE_PLAY_ERR_REQ,
    RTSP_EVT_BACK2IDLE_STOP_ERR_REQ,

    RTSP_EVT_GROUP_RSP = 0x0400,
    RTSP_EVT_DESCRIBE_RSP = RTSP_EVT_GROUP_RSP,
    RTSP_EVT_SETUP_RSP,
    RTSP_EVT_PLAY_RSP,
    RTSP_EVT_TEARDOWN_RSP,
    RTSP_EVT_PAUSE_RSP,
    RTSP_EVT_OPTION_RSP,
    RTSP_EVT_ANNOUNCE_RSP,
    RTSP_EVT_GET_PARAMETER_RSP,
    RTSP_EVT_SET_PARAMETER_RSP,
    RTSP_EVT_RECORD_RSP,
    RTSP_EVT_REDIRECT_RSP,
    RTSP_EVT_CONNECT_RSP,
    RTSP_EVT_DNS_RSP,

    RTSP_EVT_GROUP_NTF = 0x0500,
    RTSP_EVT_NET_ERR_NTF = RTSP_EVT_GROUP_NTF,
    RTSP_EVT_TCP_DISCONNECT_NTF,
    RTSP_EVT_TIMEOUT_NTF,
    RTSP_EVT_SEND_FAIL_NTF,
    RTSP_EVT_RECONNECT_NTF,
    RTSP_EVT_DL_FINISH_NTF,
    RTSP_EVT_RTCP_BYE_NTF
} rtspEvtType_e;

typedef struct rtspEvt_t_
{
    rtspEvtType_e eEvtId;

    /* for request */
    bool bRangeSpecified;
    u32 nStartTime;
    u32 nEndTime;

    /* for responce */
    u8 *pMsg;
    s32 nMsgLen;
    u32 nErrCode;
    u32 nSeqNo;

    bool bNetError;
} rtspEvt_t;

typedef enum rtspSpeedMode_e_
{
    RTSP_SPEED_NORMAL = 0,
    RTSP_SPEED_SLOW_RTCP,
    RTSP_SPEED_SLOW_PAUSE,

    RTSP_SPEED_NUM
} rtspSpeedMode_e;


typedef enum rtspParserState_e_
{
    RTSP_PARSE_INITIAL = 0,
    RTSP_PARSE_RTSP_DATA= RTSP_PARSE_INITIAL,
    RTSP_PARSE_CH_NUM,
    RTSP_PARSE_BIN_LEN,
    RTSP_PARSE_BIN_DATA,

    RTSP_PARSE_NUM
}rtspParserState_e;

typedef enum rtspInformType_e_
{
    /* RTSP --> monitor */
    RTSP_INF_INIT_MONITOR = 0,
    RTSP_INF_RTCP_SERVER_PORT,
    RTSP_INF_RTCP_SERVER_IP,
    RTSP_INF_SET_DURATION,
    RTSP_INF_START_STREAM,
    RTSP_INF_PAUSE_STREAM,
    RTSP_INF_RESUME_STREAM,
    RTSP_INF_STOP_STREAM,
    RTSP_INF_SPEED_NORMAL,
    RTSP_INF_SPEED_SLOW,
    RTSP_INF_CONNECTION_TYPE,
    RTSP_INF_CHANNEL_NUM,
    RTSP_INF_SET_RTP_SEQ,
    /* monitor --> RTSP */
    RTSP_INF_STREAM_END,
    RTSP_INF_RTCP_BYE,
    RTSP_INF_RTCP_RECONNECT
}rtspInformType_e;

typedef struct
{
    /* MDL info */
    avp_send_msg_to_stm_cb *pStreamCtlCb;
    void *pStreamCtlHandle;

    /* rtsp state*/
    rtspState_e eRtspState;
    bool bGetDescription;
    bool bQueryDns;
    rtspParserState_e eParseState;
    rtspEvt_t guidEvt;

    /* SM & event queue*/
    rtspEvt_t tEvtQueue[RTSP_EVT_QUEUE_SIZE];
    u32 nQueueHead;
    u32 nQueueTail;
    bool bIsSMBusy;
    bool bIsHandlingEvt;
    rtspEvt_t tPendingEvt;

    /* user setting parameter*/
    u8 *pUrlPath;
    u16 nPathLen;
    s8 serverIp[MAX_IP_LENGTH];
    u32 serverPort;
    u32 nThreshold;
    bool bVideoEnable;
    bool bAudioEnable;

    /* track information*/
    u32 nTrackNum;
    u32 nActiveTrack;
    rtspTrackInfo_t  trackInfo[RTSP_TRACK_NUM];
    u8 *pSdpData;
    u32 nSdpDataSize;
    u8 aStreamRangeStart[RTSP_MAX_STRLEN_RANGE];
    u8 aStreamRangeEnd[RTSP_MAX_STRLEN_RANGE];
    u8 aPlayRangeStart[RTSP_MAX_STRLEN_RANGE];
    u8 aPlayRangeEnd[RTSP_MAX_STRLEN_RANGE];

    /* connection*/
    bool bChangeConnectType;
    rtspCntMode_e eConnectType;
    rtspSpeedMode_e eSpeedMode;
    NetItfIndex tRtspNetItf;
    rtspNetState_e eRtspNetState;
    NetItfBufferObj *pRtspBufObj;
    NetItfConnectObj *pRtspConnectObj;
    NetItfBufferObj *pRtpBufObj;
    NetItfBufferObj *pRtcpBufObj;

    /* other */
    u8 session[RTSP_MAX_STRLEN_SESSION];
    u32 nSeqNo;
    rtspPendingReq_t tPendingReqTbl[RTSP_MAX_PENDING_REQ_NUM];
    u32 nUnconfirmedSize;
    u32 nUnconfirmedNum;
    bool bIsRunKeepAlive;
    rtspEvt_t eDsc404Rsp;
    u8 nDscRspDelayCount;
    bool bWaitForCloseCmp;
    u8 ti;

    /* TCP-interleaving*/
    NetItfBufferObj *pRtspCacheBufObj;
    NetItfBufferObj *pInterleavingBufObj;
    u32 nChannelNum;
    u32 nBinaryDataLen;
    u32 nRtspDataLen;
}RtspModule_t;

enum
{
    RTSP_RSP_OK = 200,
    RTSP_RSP_MOVED_PERMANENTLY = 301,
    RTSP_RSP_MOVED_TEMPORARILY = 302,
    RTSP_RSP_BAD_REQUEST       = 400,
    RTSP_RSP_UNAUTHORIZED      = 401,
    RTSP_RSP_PAYMENT_REQUIRED  = 402,
    RTSP_RSP_FORBIDDEN         = 403,
    RTSP_RSP_NOT_FOUND         = 404,
};

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
RTSP_Ret RtspPlay(RtspModule_t *pRtspMd,u32 nStartTime, u32 nEndTime);
RTSP_Ret RtspStop(RtspModule_t *pRtspMd);
RTSP_Ret RtspPause(RtspModule_t *pRtspMd,u32 nStartTime);
RTSP_Ret RtspResume(RtspModule_t *pRtspMd,u32 nStartTime, u32 nEndTime);
RTSP_Ret RtspSeek(RtspModule_t *pRtspMd, u32 nStartTime);
RTSP_Ret RtspSlowdownStart(RtspModule_t *pRtspMd);
RTSP_Ret RtspSlowdownStop(RtspModule_t *pRtspMd);
RTSP_Ret RtspKeepAlive(RtspModule_t *pRtspMd);
void RtspNetStatusCb(RtspModule_t *pRtspMd, ven_socket_ret_t eRet);
void RtspCheckSpeedNormal(RtspModule_t *pRtspMd, u32 nDataSize);
void RtspAutoSendRtpCb(void *pUserData);
void RtspRspTimeoutCb(void *pUserData);
void RtspDnsQueryCb (RtspModule_t *pRtspMd);
#endif //__RTSP_H__
