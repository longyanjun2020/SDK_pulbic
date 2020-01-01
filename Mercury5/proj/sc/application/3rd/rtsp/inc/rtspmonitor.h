/**
 * @file    rtspmonitor.h
  */
#ifndef __RTSPMONITOR_H__
#define __RTSPMONITOR_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "ven_std.h"
#include "cus_msg.hc"
#include "ven_socket.h"
#include "net_itf.h"
#include "rtsp_struct.h"
#include "vm_types.ht"

/*=============================================================*/
// types define
/*=============================================================*/
#define __LOG_LOSTPACKET_SEQ__
#define MAX_MEMBERS_NUM         (4)
#define INTERLEAVING_HDR_LENGTH (4)
#define EOF_THRESHOLD           2000
#define WAITING_THRESHOLD       (10000) //10 sec
#define MAX_PAYLOAD_SIZE        (154)
#define MAX_CNAME_LEN           (100)
#define MAX_DROPOUT             (3000)
#define MAX_MISORDER            (100)
#define FIRST_PACKET_THRESHOLD  (10000)
#define MIN_SEQUENTIAL          (2)
#define RTP_VERSION             (2)
#define RTP_SEQ_MOD             (1<<16)
#define RTP_MAX_SDES            (255)      /* maximum text length for SDES */
#define _TRACE_RTSPMONITOR_     (VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_19)		// cus5_19
#define JITTER_INTEGER
/*
* Big-endian mask for version, padding bit and packet type pair
*/
#define RTCP_VALID_MASK (0xc000 | 0x2000 | 0xfe)
#define RTCP_VALID_VALUE ((RTP_VERSION << 14) | RTCP_SR)
#define SPLIT2BYTES(ptr, val) \
    *(ptr)   = ((val) >> 8) & 0xff; \
    *(ptr+1) = ((val) >> 0) & 0xff;

#define SPLIT3BYTES(ptr, val) \
    *(ptr)   = ((val) >> 16) & 0xff; \
    *(ptr+1) = ((val) >>  8) & 0xff; \
    *(ptr+2) = ((val) >>  0) & 0xff;

#define SPLIT4BYTES(ptr, val) \
    *(ptr)   = ((val) >> 24) & 0xff; \
    *(ptr+1) = ((val) >> 16) & 0xff; \
    *(ptr+2) = ((val) >>  8) & 0xff; \
    *(ptr+3) = ((val) >>  0) & 0xff;

/* The code from the spec assumes a type "time_tp"; make this a s64: */
typedef s64 time_tp;
/* The code from the spec assumes a type "packet"; make this a void*: */
typedef void* packet;
/* The code from the spec assumes a type "event"; make this a void*: */
typedef void* event;
/*=============================================================*/
// enumeration define
/*=============================================================*/
enum
{
    EVENT_UNKNOWN = 0,
    EVENT_REPORT  = 1,
    EVENT_BYE     = 2,
};
typedef u8 RtcpEventType_e;

enum
{
    PACKET_UNKNOWN_TYPE = 0,
    PACKET_RTP          = 1,
    PACKET_RTCP_REPORT  = 2,
    PACKET_BYE          = 3,
};
typedef u8 PacketType_e;

enum
{
    RTCP_SR   = 200,
    RTCP_RR   = 201,
    RTCP_SDES = 202,
    RTCP_BYE  = 203,
    RTCP_APP  = 204
};
typedef u8 RtcpType_e;

enum
{
    RTSP_STATUS_NORMAL = 0,
    RTSP_STATUS_EOS,
    RTSP_STATUS_WAITING_RTP,
    RTSP_STATUS_RECONNECT,
    RTSP_STATUS_RECV_BYE,    
};
typedef u8 RtspStreamStatus_e;

enum
{
    RTCP_SDES_END   = 0,
    RTCP_SDES_CNAME = 1,
    RTCP_SDES_NAME  = 2,
    RTCP_SDES_EMAIL = 3,
    RTCP_SDES_PHONE = 4,
    RTCP_SDES_LOC   = 5,
    RTCP_SDES_TOOL  = 6,
    RTCP_SDES_NOTE  = 7,
    RTCP_SDES_PRIV  = 8
};
typedef u8 RtcpSdesType_e;

/*=============================================================*/
// Data Structure define
/*=============================================================*/
typedef struct
{
    u16 nMaxSeq;              /* highest seq. number seen */
    u32 nCycles;              /* shifted count of seq. number cycles */
    u32 nBaseSeq;             /* base seq number */
    u32 nBadSeq;              /* last 'bad' seq number + 1 */
    u8  nProbation;           /* sequ. packets till source is valid */
    u32 nReceived;            /* packets received */
    u32 nExpectedPrior;       /* packet expected at last interval */
    u32 nReceivedPrior;       /* packet received at last interval */
    u32 nTransit;             /* relative trans time for prev pkt */
    u32 nJitter;              /* estimated jitter */
}RtpSourceInfo_t;

typedef struct
{
    u32 nExtendSeqNo;
    u32 nSsrc;
    u32 nTimebase;
    u32 nPlaytime;
}RtpInfo_t;

typedef struct
{
    s32 s32Bandwidth;  // Kbps
    s32 s32TimestampFreq;
}SdpInfo_t;

typedef struct
{
    bool                bFirstRtpReady;
    RtpSourceInfo_t     tSrc;
    // for SR
    u32                 nSr_Ssrc;
    u32                 nLast_NTPmsw;
    u32                 nLast_NTPlsw;
    s64                 s64LastArrivalTime;
    u32                 nReceivedPacketSize;
#if defined(__LOG_LOSTPACKET_SEQ__)
    u32                 nTotalRecv;
    u32                 nTotalLoss;
    u32                 nStartRecvSeq;
    u32                 nLastRecvSeq;
#endif
    // for RR
    u32                 nRr_Ssrc;
    u8                  CNAME[MAX_CNAME_LEN];
    time_tp             tp;
    time_tp             tn;
    s32                 s32Senders;
    s32                 s32PreMembers;
    s32                 s32CurMembers;
    bool                bWeSent;
    double              fRtcpBw;
    u8                  nInitial;
    double              fAvgRtcpSize;
    PacketType_e        ePacketType;
    RtcpEventType_e     eEventType;
    RtspStreamStatus_e  eCurStatus;
    SdpInfo_t           tReceivedSdp;
    RtpInfo_t           tLastReceivedRtp;
    s32                 s32MemberList[MAX_MEMBERS_NUM];
    u8                  nPayload[MAX_PAYLOAD_SIZE];
    u8                  nPayloadSize;
    NetItfIndex         tRtcpItfIdx;
    bool                bReceiveBye;
    bool                bSendBye;
    bool                bRtspPause;
    time_tp             nPlayStartTime;
    time_tp             nWiatingStartTime;
    u32                 nDuration;
    rtspCntMode_e       eConnectType;    
    u8                  nChannelNum;
    u32                 nSvrPort;
    u8                  *pServerIp;
}RtcpInstance_t;

/*=============================================================*/
// Public functions
/*=============================================================*/
/*=============================================================*/
// functions
/*=============================================================*/

bool RtspMonitorInitializeRtcp(RtcpInstance_t *pCtx, s32 nBandwidthKbps, s32 nTimestampFreq, NetItfIndex tItfIdx, u32 nSvrPort);
void RtspMonitorStartRtcp(RtcpInstance_t *pCtx);
void RtspMonitorSetDurationInfo(RtcpInstance_t *pCtx, u32 nTmpDuration);
void RtspMonitorSetRtpSeqNumber(RtcpInstance_t *pCtx, u32 nSeqNum, u32 nTimeBae);
bool RtspMonitorParseRtpHeader(RtcpInstance_t *pCtx, u8 *pData, u32 nLen);
bool RtspMonitorParseRtcpHeader(RtcpInstance_t *pCtx, u8 *pData, u32 nLen);
RtspStreamStatus_e RtspMonitorGetStreamStatus(RtcpInstance_t *pCtx);
void RtspMonitorSetPauseStream(RtcpInstance_t *pCtx);
void RtspMonitorSetResumeStream(RtcpInstance_t *pCtx);
void RtspMonitorSetStopStream(RtcpInstance_t *pCtx);
#endif //__RTSPMONITOR_H__
