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

#ifndef _RV_H223_CONTROL_IFC_H
#define _RV_H223_CONTROL_IFC_H

#ifdef __cplusplus
extern "C" {
#endif

/*maximum number of segments in a window*/
#define RV_H223_WNSRP_WINDOW_SIZE 10

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

typedef void (*RvH223ControlDataIndicationEv) (IN void *,   /* Context.*/
                                               IN RvUint8 *,/* Filled buffer.*/
                                               IN RvUint32, /* Filled size.*/
                                               IN EControlResult /* Error.*/
                                               );

/* Initialization parameters of Control LC.*/
typedef struct{
    RvUint32                       numOfInstancesMax; /* Number of Control LC instances.*/
    RvUint32                       bufferSize; /* Size of a control buffer (larger messages can be sent - using RPOOL) */
    RvUint32                       numOfBuffers; /* Number of control buffers to allocate */
    RvTimerQueue                   *pcontrolTimerQueue; /* Timer queue for timer creation in NSRP.*/
    RvH223ControlDataIndicationEv  ControlDataIndicationEv; /* Delivers data.*/
    RvH223IsClearEv                ControlIsClearEv;    /* Indicates safe disconnection.*/
    RvLogSource                    hLog;
    RvLogSource                    hLogErr;
    RvLogMgr                       *hLogMgr;
    RvWatchdog                     *hWatchdog;
}TH223ControlInitCfg;

typedef struct{
    HMUXER                      hmuxer; /* Handle of the associated muxer.*/
    HDEMUX                      hdemux; /* Handle of the associated demux.*/
    void                        *controlContext; /* Handle to use in the callbacks.*/
    EMuxLevel                   muxerLevel;/* Multiplex level of Muxer.*/
    RvBool                      useCCSRL;  /* Indicates the use of CCSRL.*/
    RvUint64                    nsrpTimerT401; /* Used for NSRP and WNSRP */
    RvUint64                    srpTimerT401;  /* Used for SRP */
    RvUint8                     nsrpCounterN400; /* Used for NSRP and SRP */
    RvUint8                     wnsrpCounterN402; /* Used for WNSRP */
    RvH223MuxDataIndicationEv   DemuxMuxDataIndicationEv; /* assembled NSRP frame indication */
}TH223ControlConstructCfg;

/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223ControlInit
 * ----------------------------------------------------------------------------
 * General: Initializes the Control class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_OUTOFRESOURCES - if the memory allocation fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : pcfg                - Initialization parameters.
 * Output : hH223ControlModule  - handle to the H.223 control module.
 *****************************************************************************/
RvStatus RvH223ControlInit (IN   TH223ControlInitCfg *pcfg,
                            OUT  HH223CONTROLMODULE  *hH223ControlModule);

/******************************************************************************
 * RvH223ControlEnd
 * ----------------------------------------------------------------------------
 * General: Destructs an instance of Control LC.
 *
 * Return Value: RV_OK.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hH223ControlModule - handle to the H.223 control module.
 *****************************************************************************/
RvStatus RvH223ControlEnd (IN HH223CONTROLMODULE hH223ControlModule);

/******************************************************************************
 * RvH223ControlGetRPOOL
 * ----------------------------------------------------------------------------
 * General: Get the RPOOL instance used by the control channels.
 *
 * Return Value: RV_OK.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hH223ControlModule - handle to the H.223 control module.
 *****************************************************************************/
HRPOOL RvH223ControlGetRPOOL(IN HH223CONTROLMODULE hH223ControlModule);

/******************************************************************************
 * RvH223ControlConstruct
 * ----------------------------------------------------------------------------
 * General: Constructs an instance of Control LC.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hH223ControlModule - Handle to the control module.
 *          pcfg               - Configuration parameters.
 *          phnd               - Pointer to be filled with logical channel handle.
 * Output : None
 *****************************************************************************/
RvStatus RvH223ControlConstruct(
    IN  HH223CONTROLMODULE          hH223ControlModule,
    IN  TH223ControlConstructCfg    *pcfg,
    IN  HH223CONTROL                phnd);

/******************************************************************************
 * RvH223ControlDestruct
 * ----------------------------------------------------------------------------
 * General: Destructs an instance of Control LC.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_BADPARAM - if the handle is invalid.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hcontrol - Control LC's handle.
 *****************************************************************************/
RvStatus RvH223ControlDestruct (IN HH223CONTROL hcontrol);

/******************************************************************************
 * RvH223ControlSendData
 * ----------------------------------------------------------------------------
 * General: This routine is not blocking and if the buffer is too large to
 *          transmit in a single chunk, puts the data on waiting list. Actual
 *          sending will be done from the timer callback. Buffer releasing is
 *          done in a callback routine.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_BADPARAM - if the handle is invalid.
 *               RV_ERROR_BUSY - if the previous sending operation has not been
 *                               completed yet.
 *               RV_ERROR_OUTOFRESOURCES - if the internal pools appear to be
 *                                         insufficient.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hcontrol  - Handle to the control LC instance.
 *          pbuffer   - Data buffer.
 *          size      - Data buffer size.
 *****************************************************************************/
RvStatus RvH223ControlSendData (IN   HH223CONTROL hcontrol,
                                IN   RvUint8  *pbuffer,
                                IN   RvUint32 size);

/******************************************************************************
 * RvH223ControlSetReportClear
 * ----------------------------------------------------------------------------
 * General: Sets/resets flag, which forces control LC to report when it is
 *          clear from any data.
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hcontrol  - Handle to the control LC instance.
 *          set       - RV_TRUE - report, RV_FALSE - not.
 *****************************************************************************/
RvStatus RvH223ControlSetReportClear (IN  HH223CONTROL hcontrol,
                                      IN  RvBool set);

/******************************************************************************
 * RvH223ControlSetMuxLevel
 * ----------------------------------------------------------------------------
 * General: Changes multiplex level.
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hcontrol  - Handle to the control LC instance.
 *          EMuxLevel - Multiplex level.
 *          bMuxer    - Defines whether the it is the muxer or demux muxLevel.
 *****************************************************************************/
RvStatus RvH223ControlSetMuxLevel (IN  HH223CONTROL hcontrol,
                                   IN  EMuxLevel    muxLevel,
                                   IN  RvBool       bMuxer);

/******************************************************************************
 * RvH223ControlSetWNSRP
 * ----------------------------------------------------------------------------
 * General: Instruct the instance of Control LC to use WNSRP mode.
 *          To be used only when constructing a control.
 *
 * Return Value: RV_OK  - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl     - Handle to the control module.
 *          bUseWnsrp    - RV_TRUE to use WNSRP, RV_FALSE otherwise.
 * Output : none.
 *****************************************************************************/
RvStatus RvH223ControlSetWNSRP (IN   HH223CONTROL       hControl,
                                IN   RvBool             bUseWnsrp);

/******************************************************************************
 * RvH223ControlGetWNSRP
 * ----------------------------------------------------------------------------
 * General: Get indication if the control instance used WNSRP mode.
 *
 * Return Value: RV_OK  - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl     - Handle to the control module.
 * Output : bUseWnsrp    - Indication whether the control used WNSRP mode.
 *****************************************************************************/
RvStatus RvH223ControlGetWNSRP (IN   HH223CONTROL       hControl,
                                OUT  RvBool             *bUseWnsrp);

/******************************************************************************
 * RvH223ControlSetRetransmitOnTimeoutDisabled
 * ----------------------------------------------------------------------------
 * General: set the retransmitOnTimeoutDisabled flag in the control instance to
 *          the given value..
 *
 * Return Value: RV_OK on success.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 *          value               - RV_TRUE - retransmission on timeout disabled,
 *                                RV_FALSE - retransmission on timeout enabled.
 * Output : None.
 *****************************************************************************/
RvStatus  RvH223ControlSetRetransmitOnTimeoutDisabled(
    IN   HH223CONTROL       hControl,
    IN   RvBool             value);

/******************************************************************************
 * RvH223ControlGetRetransmitOnTimeoutDisabled
 * ----------------------------------------------------------------------------
 * General: set the retransmitOnTimeoutDisabled flag in the control instance to
 *          the given value.
 *
 * Return Value: RV_OK on success.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 * Output : value.              - RV_TRUE - retransmission on timeout disabled,
 *                                RV_FALSE - retransmission on timeout enabled.
 *****************************************************************************/
RvStatus  RvH223ControlGetRetransmitOnTimeoutDisabled(
    IN   HH223CONTROL       hControl,
    IN   RvBool             *value);

/******************************************************************************
 * RvH223ControlStopRetransmissionOnIdle
 * ----------------------------------------------------------------------------
 * General: set the retransmitOnTimeoutDisabled flag in the control instance to
 *          RV_FALSE and cancel the nsrpT401Timer.
 *
 * Return Value: RV_OK on success.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 * Output : None
 *****************************************************************************/
RvStatus RvH223ControlStopRetransmissionOnIdle
		(IN     HH223CONTROL        hControl);

/******************************************************************************
 * RvH223ControlCancelNsrpTimer
 * ----------------------------------------------------------------------------
 * General: Cancel the nsrpT401Timer
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 * Output : None
 *****************************************************************************/
void RvH223ControlCancelNsrpTimer
        (IN     HH223CONTROL        hControl);

/******************************************************************************
 * RvH223ControlSetMaxCCSRLSegmentSize
 * ----------------------------------------------------------------------------
 * General: Set the maximum size for CCSRL segment.
 *
 * Return Value: RV_OK on success.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 *          maxCCSRLSegmentSize - Maximum size to allow a CCSRL segment.
 * Output : None.
 *****************************************************************************/
RvStatus RvH223ControlSetMaxCCSRLSegmentSize(
    IN   HH223CONTROL       hControl,
    IN   RvUint16           maxCCSRLSegmentSize);

/******************************************************************************
 * RvH223ControlGetMaxCCSRLSegmentSize
 * ----------------------------------------------------------------------------
 * General: Get the maximum size a CCSRL segment is allowed.
 *
 * Return Value: RV_OK on success.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl            - Handle to the control module.
 * Output : maxCCSRLSegmentSize - Maximum size a CCSRL segment is allowed.
 *****************************************************************************/
RvStatus RvH223ControlGetMaxCCSRLSegmentSize(
    IN   HH223CONTROL       hControl,
    IN   RvUint16           *maxCCSRLSegmentSize);


#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)
/******************************************************************************
 * RvH223ControlSave2Buffer
 * ----------------------------------------------------------------------------
 * General: save the control instance into a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl     - Handle to the control instance.
 *          buffLen       - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : pBuffer       - buffer to save to.
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223ControlSave2Buffer(IN    HH223CONTROL        hControl,
                              OUT   RvUint8             *pBuffer,
                              IN    RvSize_t            buffLen,
                              INOUT RvSize_t            *lenDone,
                              INOUT RvStatus            *pStatus);

/******************************************************************************
 * RvH223ControlGetFromBuffer
 * ----------------------------------------------------------------------------
 * General: restores the control instance from a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hControl     - Handle to the control instance.
 *          pBuffer      - buffer to restore data from.
 *          buffLen      - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : hControl     - h223control instance updated with restored
 *                         data from buffer.
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223ControlGetFromBuffer(INOUT    HH223CONTROL        hControl,
                                IN   RvUint8             *pBuffer,
                                IN    RvSize_t            buffLen,
                                INOUT RvSize_t            *lenDone,
                                INOUT RvStatus            *pStatus);
#endif /* (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES) */


/******************************************************************************
 * RvH223ControlDemuxDataIndication
 * ----------------------------------------------------------------------------
 * General: Callback for Demux module. Is called when Demux has filled the whole
 *          NSRP frame. Performs input NSRP procedures.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   context - Handle to the control LC instance.
 *          pbuf    - Pointer to a data.
 *          size    - Size of data.
 *          result  - Result of opening this control packet by the demux.
 * Output:  none.
 *****************************************************************************/
void RvH223ControlDemuxDataIndication(
    IN void             *context,
    IN RvUint8          *pbuf,
    IN RvUint32         size,
    IN EDemuxResult     result);

/******************************************************************************
 * RvH223ControlAssembleCCSRLSegment
 * ----------------------------------------------------------------------------
 * General: Copies necessary amount of data to user's buffer.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hControl    - Handle to the control LC instance.
 * Output:  none.
 *****************************************************************************/
void RvH223ControlAssembleCCSRLSegment(
    IN HH223CONTROL hControl);

#ifdef __cplusplus
}
#endif

#endif /*_RV_H223_CONTROL_IFC_H*/
