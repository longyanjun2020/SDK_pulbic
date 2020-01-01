/******************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
*******************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
******************************************************************************/

#ifndef _RV_H223_CONTROL_H
#define _RV_H223_CONTROL_H

#include "rvh223controlifc.h"

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*/
/*                            MODULE VARIABLES                               */
/*---------------------------------------------------------------------------*/

#define CONTROL_INPUT_QUEUE_DEPTH_MAX 10

#define CCSRL_SDU_SIZE_MAX  RV_H223_MAX_H245_MESSAGE_SIZE
#define CCSRL_NSRP_PDU_SIZE_MAX  (CCSRL_SDU_SIZE_MAX + 1 /*CCSRL header*/ + 4 /*NSRP header+crc*/)
#define CCSRL_LAST_SEGMENT_HEADER       0xff
#define CCSRL_NOT_LAST_SEGMENT_HEADER   0x00
#define CCSRL_HEADER_SIZE               1

#define NSRP_COMMAND_FRAME_HEADER   0xf9
#define SRP_RESPONSE_FRAME_HEADER   0xfb
#define NSRP_RESPONSE_FRAME_HEADER  0xf7
#define WNSRP_COMMAND_FRAME_HEADER   0xf1
#define WNSRP_RESPONSE_FRAME_HEADER  0xf3

#define NSRP_HEADER_SIZE            2
#define SRP_HEADER_SIZE             1
#define NSRP_SEQUENCE_NUMBER_MAX    256

/* Default values for WNSRP */
#define WNSRP_WINDOW_SIZE               RV_H223_WNSRP_WINDOW_SIZE

typedef enum
{
    NSRP_ACK = 0,
    NSRP_DATA,
    WNSRP_ACK,
    WNSRP_DATA
}ENsrpReason;

typedef enum
{
    CONTROL_MODE_TYPE_SRP,
    CONTROL_MODE_TYPE_NSRP,
    CONTROL_MODE_TYPE_WNSRP,
    CONTROL_MODE_TYPE_NSRP_AND_WNSRP
}ControlModeType;

typedef struct
{
    RvUint8 *pbuf;
    RvUint16 size;
}TInputData;


typedef struct
{
    TRvMuxSdu muxSdu;
    RvUint8   bIsLastSegment;
}WnsrpDataUnit;

typedef struct{
    RvTimerQueue                   *pcontrolTimerQueue;/* Timer queue for timer creation in NSRP.*/
    HRPOOL                         hWindowRpool;      /* Handle for WNSRP Rpool window */
    TRvMuxSdu                      emptyMuxSdu;
    RvH223ControlDataIndicationEv  ControlDataIndicationEv; /* Delivers data.*/
    RvH223IsClearEv                ControlIsClearEv;    /* Reports readiness to termination.*/
    RvLogSource                    hLog;
    RvLogSource                    hLogErr;
    RvLogMgr                       *hLogMgr;
}H223ControlClass;


typedef struct{

    /* SRP, NSRP and WNSRP parameters */
    TRvMuxSdu       dataMuxSdu;
    TRvMuxSdu       ackMuxSdu[WNSRP_WINDOW_SIZE];
    RvUint8         ackCounter;
    RvInt8          nsrpInProcess;
    RvUint32        ackPayload[WNSRP_WINDOW_SIZE];
    RvUint8         nsrpSendNumber; /* Transmitting sequence number.*/
    RvInt16         nsrpRcvNumber;  /* Receiving sequence number. 0x7FFF if none received yet */
    RvUint8         nsrpN400Counter;/* Retransmission counter.*/
    RvTimer         nsrpT401Timer;  /* Timer descriptor for NSRP stack.*/
    RvUint8         timerIsActive;/* Boolean: there is an active timer in the system.*/
    RvUint64        nsrpTimerT401ExpirationValue;
    RvUint64        srpTimerT401ExpirationValue;
    RvUint8         srpSduWasSent; /* RV_TRUE if an SDU was sent and is waiting to be released/retransmitted */
    RvUint8         wnsrpExpectedRecvNumber; /* The next expected WNSRP sequence number. */
    RvUint8         wnsrpAckWaitingNumber; /* First WNSRP sequence number to be acked */
    WnsrpDataUnit   wnsrpSendWindow[WNSRP_WINDOW_SIZE];
    WnsrpDataUnit   wnsrpRecvWindow[WNSRP_WINDOW_SIZE];
    RvUint8         wnsrpFirstSendIndex;  /* First index in the send window */
    RvUint8         wnsrpLastSendIndex;   /* Last index in the send window */
    RvUint8         wnsrpFirstRecvIndex;  /* First index in the recv window */
    RvUint8         wnsrpLastRecvIndex;   /* Last index in the recv window */
    RvUint8         wnsrpSendSize;        /* The number of elements in the send window */
    RvUint8         wnsrpRecvSize;        /* The number of elements in the recv window */
    ControlModeType eControlModeType;   /* Used to indicate which control type is used */
    RvUint8         wnsrpN402Counter;  /* counter for WNSRP.*/
	RvUint8         nsrpCounterN400MaxValue; /* Maximum value of counter used for NSRP/SRP procedure */
    RvUint8         wnsrpCounterN402MaxValue; /* Maximum value of counter used for WNSRP procedure */

    /*retransmission on idle params*/
    RvUint8         retransmitOnTimeoutDisabled; /*RV_TRUE when retransmission on idle is active.*/
   
    /* CCSRL parameters */
    RvUint8         receiveBuffer[CCSRL_NSRP_PDU_SIZE_MAX];
    RvUint16        maxCCSRLSegmentSize; /* Maximum size of a CCSRL segment */
    EMuxLevel       muxerLevel;     /* Multiplex level of Muxer for CCSRL dividing.*/
    EMuxLevel       demuxLevel;     /* Multiplex level of Demux for CCSRL dividing.*/

    /* General parameters */
    RvUint8         reportClear;
    void            *userContext;    /* Handle to use in the callbacks.*/
    H223ControlClass *pControlClass;


    /* Handles */
    HMUXER          hmuxer;         /* Handle of the associated muxer.*/
    HDEMUX          hdemux;         /* Handle of the associated demux.*/
    HMUXLCDESC      hmuxerChannel;  /* Handle the associated muxer's channel.*/
    HMUXLCDESC      hdemuxChannel;  /* Handle the associated demux's channel.*/
    RvMutex         controlMutex;
}H223ControlInstance;


#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_CONTROL_H */

