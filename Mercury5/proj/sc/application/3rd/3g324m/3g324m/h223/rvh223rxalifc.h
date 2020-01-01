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

#ifndef _RV_H223_RXAL_IFC_H
#define _RV_H223_RXAL_IFC_H

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

/* This routine delivers the data to a user. It serves as both AL-DATA.indication
and AL-ABORT.indication primitives of H223.*/
typedef void (*RvH223AlDataIndicationEv) (IN void *,    /* Context.*/
                                          IN RvInt32,   /*Sub Context*/
                                          IN TRvAlSdu *,/* Output structure.*/
                                          IN RvUint32,  /* Filled size.*/
                                          IN EExtractionResult  /* Error summary.*/
                                        );

/* This routine request from the application what to retransmit. The return
   value indicates from which SN to start the retransmissions. Setting it to -1
   indicates no retransmission is required. */
typedef RvInt32 (*RvH223AlRtxRequestEv) (
    IN  void      *context,         /* Context.*/
    IN  RvUint16  expectedSeqNum,   /* SN expected to arrive.*/
    IN  RvUint16  curSeqNum);       /* SN that actually arrived.*/

/* Common callbacks for all AL's.*/
typedef struct{
    RvH223GetBufEv           GetBufEv;         /* Callback for output AlSdu obtaining.*/
    RvH223AlDataIndicationEv DataIndicationEv; /* Data delivering callback.*/
    RvH223AlRtxRequestEv     RtxRequestEv;     /* Retransmission request callback*/
}TRxCallbacks;

/* Configuration parameters of AL instance.*/
typedef struct{
    RvBool  isFramed;
}TRxAl1Params;

typedef struct{
    RvBool  useSequenceNumbering;
}TRxAl2Params;

typedef struct{
    RvUint8             controlFieldSize;
    RvUint8             useRtx;
    HTXAL               correspondingChannel;
}TRxAl3Params;

#if (RV_H223_USE_MUX_LEVEL_3 == RV_YES)

/* AL1M, AL2M & AL3M related parameters */
typedef struct{
    RvBool          isFramed;
    RvBool          isUseGolay;
    ECrcLength      crcLength;
    RvBool          isInterleaving;
    RvBool          isALSDUSplitting;
    RvUint8         codeRate; /* can be RCPC(Annex C) or RS(Annex D) */
    EArqType        arqType;
    RvUint8         retransmissionsNum; /* 0-16, 255 for infinite */
    RvUint32        sendBufferSize;
    HTXAL           correspondingChannel;
}TRxAlxMParams;

#endif /*RV_H223_USE_MUX_LEVEL_3*/

typedef struct{
    EAL               layer;
    RvBool            isSegmentable;
    RvH223LCDataType  dataType;
    RvUint16          lcn;
    union{
        TRxAl1Params    rxal1;
        TRxAl2Params    rxal2;
        TRxAl3Params    rxal3;
#if (RV_H223_USE_MUX_LEVEL_3 == RV_YES)
        TRxAlxMParams   rxalxM;
#endif
    }rxalParams;
#define rxal1Params         rxalParams.rxal1
#define rxal2Params         rxalParams.rxal2
#define rxal3Params         rxalParams.rxal3
#define rxalxMParams        rxalParams.rxalxM

    void                *context;
    RvInt32             subContext;
    TRxCallbacks        rxalCallbacks;
    RvUint16            timeout; /* timer for the SREJ requests, in milliseconds */
#define AlGetBufEv              rxalCallbacks.GetBufEv
#define AlDataIndicationEv      rxalCallbacks.DataIndicationEv
#define AlRtxReqeuestEv         rxalCallbacks.RtxRequestEv
    RvH223MuxDataIndicationEv   demuxH223DataIndicationEv; /* for usage of an external function */
}TH223RxALCfg;


/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223RxALInit
 * ----------------------------------------------------------------------------
 * General: Initializes the module.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   numOfInstances  - Maximal number of concurrent instances.
 *          alSduQueueDepth - Maximal number of out of sequence saved AlSdu.
 *          hRpool          - handle to the rpool
 *          hLog            - handle to the log source.
 *          hLogErr         - handle to the error log source.
 *          hLogMgr         - handle to the log manager.
 *          hWatchdog       - handle to the watchdog.
 *          prtxTimerQueue  - timer queue for use in retransmission channels.
 * Output:  hAlModule       - handle to the receiving AL module.
 *****************************************************************************/
RvStatus RvH223RxALInit (IN RvUint16      numOfInstances,
                         IN RvUint16      alSduQueueDepth,
                         IN HRPOOL        hRpool,
                         IN RvLogSource   hLog,
                         IN RvLogSource   hLogErr,
                         IN RvLogMgr     *hLogMgr,
                         IN RvWatchdog   *hWatchdog,
                         IN RvTimerQueue *prtxTimerQueue,
                         OUT HRXALMODULE *hAlModule);

/******************************************************************************
 * RvH223RxALGetLCDescSizeOf
 * ----------------------------------------------------------------------------
 * General: Find the size of a multiplexer AL.
 *
 * Return Value: Size of the data required for allocation.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input: demuxSduQueueDepth    - Number of MUX-SDUs that can be pending on
 *                                retransmissions.
 *****************************************************************************/
RvSize_t RvH223RxALGetLCDescSizeOf(
    IN RvUint16 demuxSduQueueDepth);

/******************************************************************************
 * RvH223RxALEnd
 * ----------------------------------------------------------------------------
 * General: Terminates the class.
 *
 * Return Value: RV_OK  if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input: hAlModule - handle to the receiving AL module.
 *****************************************************************************/
RvStatus RvH223RxALEnd (HRXALMODULE hAlModule);

/******************************************************************************
 * RvH223RxALConstruct
 * ----------------------------------------------------------------------------
 * General: Constructs an instance of AL.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more free instances.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hAlModule - handle to the AL module.
 *          pCfg      - Configuration parameters.
 *          handle  - Handle to Muxer or Demux depending on pcfg.
 * Output : phnd      - Pointer to be filled with logical channel handle.
 *****************************************************************************/
RvStatus RvH223RxALConstruct (IN   HRXALMODULE  hAlModule,
                              IN   TH223RxALCfg *pcfg,
                              IN   HDEMUX        handle,
                              OUT  HRXAL        *phnd);

/******************************************************************************
 * RvH223RxALDestruct
 * ----------------------------------------------------------------------------
 * General: Destructs an instance of AL.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_BADPARAM - if the handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hal - Logical channel's handle.
 *****************************************************************************/
RvStatus RvH223RxALDestruct (IN HRXAL hal);

/******************************************************************************
 * RvH223RxALMonaMPCDestruct
 * ----------------------------------------------------------------------------
 * General: Destructs an instance of AL of a MPC channel .
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_BADPARAM - if the handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hal - AL's handle.
 *****************************************************************************/
RvStatus RvH223RxALMonaMPCDestruct (IN HRXAL hal);

/******************************************************************************
 * RvH223RxAlSetTransmitAL
 * ----------------------------------------------------------------------------
 * General: Set the transmission adaptation layer instance associated with a
 *          receive adaptation layer. This is used for bidirectional channels
 *          for handling retransmission requests.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_BADPARAM - if the handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : phrxal - Receive logical channel's handle.
 *          phtxal - Transmit logical channel's handle.
 *****************************************************************************/
RvStatus RvH223RxAlSetTransmitAL(
    IN  HRXAL           phrxal,
    IN  HTXAL           phtxal);

/******************************************************************************
 * RvH223AlDemuxDataIndication
 * ----------------------------------------------------------------------------
 * General: Callback for Demux module. Is called when Demux has filled the whole
 *          MUX-SDU.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   context - Handle to the AL instance.
 *          pbuf    - Pointer to a data.
 *          size    - Size of data.
 *          result  - Result of opening this control packet by the demux.
 * Output:  none.
 *****************************************************************************/
void RvH223AlDemuxDataIndication(
    IN void             *context,
    IN RvUint8          *pbuf,
    IN RvUint32         size,
    IN EDemuxResult     result);

#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_RXAL_IFC_H */
