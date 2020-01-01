/**
 * @file    rtsp_util.h
  */
#ifndef __RTSP_UTIL_H__
#define __RTSP_UTIL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "sys_rtk_vmrtkho.h"
#include "rtsp.h"

#define MAX_RTSP_TIMER_NUM      (10)
#define MAX_RTSP_INSTANCE_NUM      (3)

//#define RTSP_DUMP_DATA_BY_CHANNEL
#ifdef RTSP_DUMP_DATA_BY_CHANNEL
#define DUMP_RTP_RTCP_FILE_PATH   "/rtsptest"
#define DUMP_AUDIO_RTP_FILE_NAME  "RtpAudioFile.rtp"
#define DUMP_VIDEO_RTP_FILE_NAME  "RtpVideoFile.rtp"
#define DUMP_AUDIO_RTCP_FILE_NAME "RtcpAudioFile.rtcp"
#define DUMP_VIDEO_RTCP_FILE_NAME "RtcpVideoFile.rtcp"
#endif

//#define RTSP_DUMP_RTP
#ifdef RTSP_DUMP_RTP
#define DUMP_RTP_FILE_PATH "/rtsptest"
#define DUMP_RTP_FILE_NAME "RtpSample.rtp"
#endif

typedef void (*RtspTimeoutCb)(void *pUserData);

typedef struct RtspTimer_t_
{
    u16 nTimerId;
    void *pUserData;
    RtspTimeoutCb pfnTimeoutCb;
} RtspTimer_t;

static RtspTimer_t g_tRtspTimerTbl[MAX_RTSP_TIMER_NUM] = {0};


typedef struct RtspMsgHistory_t_
{
    u16 idx;
    RtspModule_t * pHandle;
    u16 msg;
} RtspMsgHistory_t;


typedef enum rtspDatalinkCnf_e_
{
    RTSP_DL_OK = 0,
    RTSP_DL_ERR_CONFIRM
}rtspDatalinkCnf_e;

typedef enum rtspDatalinkState_e_
{
    RTSP_DLS_INVALID = 0,
    RTSP_DLS_OPENING,
    RTSP_DLS_OPEN_ERROR,
    RTSP_DLS_OPEND,
    RTSP_DLS_CLOSING,
    RTSP_DLS_CLOSE_ERROR,
    RTSP_DLS_DISCNT_HANDLING,
    RTSP_DLS_DISCNT,
    RTSP_DLS_ERROR,
}rtspDatalinkState_e;

typedef struct
{
    RtspModule_t * pHandle;
    rtspDatalinkCnf_e eDlCnfState;
}rtspInst_t;

typedef struct rtspDnsQuery_t_
{
    u8 ti;
    struct hostent *phostent;
} rtspDnsQuery_t;

/*=============================================================*/
// types define
/*=============================================================*/
s64 RtspGet64BytesTimestamp(void);
u32 RtspGet32BytesTimestamp(void);
u32 RtspGetRandom32(void);
double RtspGetRandom48(void);
void RtspMsgHistory(RtspModule_t * pHandle, u32 nMsg);
s32 RtspCreateTimer(void *pUserData, u32 nMSecs, RtspTimeoutCb pfnTimeoutCb);
void RtspCancelTimer(void *pUserData, RtspTimeoutCb pfnTimeoutCb);
void RtspSendMsg(RtspModule_t *pRtspMd, u32 eEvtType, RTSP_Ret eRet);
void RtspDatalinkSendMsg(u32 eEvtType, RTSP_Ret eRet);
void RtspDatalinkErrorConfirm(RtspModule_t * pRtspMd);
void RtspSendDownloadData(RtspModule_t *pRtspMd, void *pData, u32 nDataSize);
RtspModule_t * RtspOpenHandle(void);
void RtspCloseHandle(RtspModule_t *pRtspMd);
void RtspHandleInit(RtspModule_t *pRtspMd);
RTSP_Ret RtspCreateDataLink(void *pDatalinkCtlHandle, avp_send_msg_to_avp_cb *pDatalinkCtlCb, u8 datalinkType);
RTSP_Ret RtspReleaseDataLink(void);
void RtspSetGuideEvt(RtspModule_t *pRtspMd, rtspEvt_t evt);
void RtspClearGuideEvt(RtspModule_t *pRtspMd);
void RtspEvtInit(rtspEvt_t *pEvt,  rtspEvtType_e eEvtId);
bool RtspEvtQueueIsEmpty(RtspModule_t *pRtspMd);
bool RtspEvtQueueIsFull(RtspModule_t *pRtspMd);
bool RtspEvtQueueGet(RtspModule_t *pRtspMd, rtspEvt_t *pEvt);
bool RtspEvtQueuePut(RtspModule_t *pRtspMd, rtspEvt_t evt);
bool RtspEvtQueueClear(RtspModule_t *pRtspMd);
void RtspSetBusyFlag(RtspModule_t *pRtspMd, bool bBusy);
bool RtspGetBusyFlag(RtspModule_t *pRtspMd);
rtspReqCmd_e RtspPendingReqPop(RtspModule_t *pRtspMd, u32 nSeqNo);
RTSP_Ret RtspPendingReqPush(RtspModule_t *pRtspMd, rtspReqCmd_e cmd, u32 nSeqNo);
RTSP_Ret RtspPendingReqClear(RtspModule_t *pRtspMd);
u32 RtspPendingReqGetNum(RtspModule_t *pRtspMd);
#ifdef RTSP_DUMP_RTP
void RtspDumpPacketToFile(RtspModule_t *pRtspMd, u8 *pPath, const u8 *pFile, void* DataBuf, s32 DataLen, bool bOverwrite);
#endif
#if defined(RTSP_DUMP_DATA_BY_CHANNEL)
void RtspDumpPacketByChannelToFile(RtspModule_t *pRtspMd, rtspItfType_e eType, u8 *pPath, const u8 *pFile, void* DataBuf, s32 DataLen, u32 nSeqNo);
#endif
NetItf_Ret RtspCreateBufObj(u32 nBufSize, NetItfBufferObj **ppBufObj);
void RtspDestroyBufObj(NetItfBufferObj *pBufObj);
void RtspDumpString(u8 *pStr);
RTSP_Ret RtspDnsQuery(RtspModule_t *pRtspMd, const u8  *name);
#endif //__RTSP_UTIL_H__

