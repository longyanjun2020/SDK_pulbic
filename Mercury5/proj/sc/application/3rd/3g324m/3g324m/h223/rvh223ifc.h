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

#ifndef _RV_H223_IFC_H
#define _RV_H223_IFC_H

#include "rvh223defs.h"
#include "rvtimer.h"
#include "rvh223controlifc.h"
#include "rvh223txalifc.h"
#include "rvh223rxalifc.h"


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/
/* Structure of events for the initialization of the H.223 module */ 
typedef struct 
{
    RvH223ControlDataIndicationEv ControlDataIndicationEv; /*Informs the user that the new control message has arrived */
    RvH223IsClearEv               ControlIsClearEv; /*Informs the user that the module is empty
                                        and ready for termination.*/
    RvH223MuxLevelIndicationEv    MuxLevelIndicationEv; /* Callback for demux to be called */
    RvH223GetBufEv                DemuxACPGetBufEv;    /* Callback for demux to be called when a buffer for demuxing
                                                          needs to be allocated */
    RvH223ReleaseBufEv            DemuxACPReleaseBufEv; /*Callback for demux to be called when a buffer for demuxing
                                                          is no longer used and needs to be released*/
#if (RV_3G324M_USE_MONA == RV_YES)
    RvH223MONAUpdateAckStatusEv   MONAUpdateAckStatusEv;    /* Callback for demux to be called when the monaAckStatus
                                                            should be updated in the muxer */
    RvH223MONAPreferenceRcvEv     MONAPreferenceRcvEv;      /* Callback to notify the application that a MONA preference
                                                               message was received */
    RvH223MONAPreferenceSendEv    MONAPreferenceSendEv;      /* Callback to notify the application that a MONA preference message was sent*/                                                              

	RvH223MONAAckStatusChangedEv  MONAAckStatusChangedEv;	 /* Callback to notify the application that the mona ack status changed */	
#endif /* USE_MONA */
}TH223InitCfgEvents;
/* Input structure for H223 module initialization.*/
typedef struct
{
    RvUint16                      numOfInstances;/* Maximal number of concurrently running
                                                    conversations. This parameter implicitly
                                                    determines a number of muxers, demuxs and
                                                    ControlLC-s.*/
    RvUint16                      numOfTxAL;    /* Transmitting AL modules.*/
    RvUint16                      numOfRxAL;    /* Receiving AL modules.*/
    RvUint16                      numOfLCPerMux; /* Maximal number of logical channels per multiplexer*/
    RvUint16                      numOfLCPerDemux; /* Maximal number of logical channels per de-multiplexer*/
    RvUint8                       maxVideoBuffers;   /*Max media buffers per call for ACN*/
    RvUint16                      numOfMuxSduPerMuxLC;/* Input buffers queue depth.*/
    RvUint16                      numOfAlSduSaved;    /* Out of sequence AlSdu queue depth.*/
    RvUint16                      controlBufferSize; /* Size of a control buffer */
    RvUint16                      controlNumOfBuffers; /* Number of control buffers */
    RvUint16                      alxmBufferSize; /* Size of an ALxM buffer */
    RvUint16                      alxmNumOfBuffers; /* Number of ALxM buffers */
    RvUint16                      interleavingBufferSize; /* Size of an ALxM interleaving buffer */
    RvUint16                      interleavingNumOfBuffers; /* Number of ALxM interleaving buffers */
    TH223InitCfgEvents            h223InitEvents;
    RvTimerQueue                  *pcontrolTimerQueue;/* Timer queue for use in SRP/NSRP module.*/
    RvTimerQueue                  *prtxTimerQueue;    /* Timer queue for use in Rtx module.*/
    RvWatchdog                    *hWatchdog;  /* Handle to the resources Watchdog module */
    RvLogMgr                      *hLogMgr;    /* Handle to the log manager */
} TH223InitCfg;

/* Input structure for H223 instance creation(conversation establishing).*/
typedef struct
{
    EMuxLevel                   muxLevel;                   /* Mux level to use */
    void                        *muxLevelIndicationContext; /* upon MUX-LEVEL determination.*/
    void                        *controlContext;            /* Handle to use in callback routines of control
                                                               logical channel.*/
    RvUint64                    nsrpTimerT401;              /* Timer expiration value.*/
    RvUint64                    srpTimerT401;               /* Timer expiration value.*/
    RvUint8                     nsrpCounterN400;            /* Maximum value of the counter used in NSRP/SRP procedure. */
    RvUint8                     wnsrpCounterN402;           /* Maximum value of the counter used in WNSRP procedure. */
    RvUint32                    synchLossBytes;             /* Maximum out-of-synch tolerated */
} TH223ConstructCfg;


/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223Init
 * ----------------------------------------------------------------------------
 * General: Initializes the module.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   pcfg        - H223 initialization parameters.
 * Output:  phH223Module - Pointer to be filled with H.223 module's handle.
 *****************************************************************************/
RvStatus RvH223Init (IN  TH223InitCfg *pcfg,
                     OUT HH223MODULE  *phH223Module);

/******************************************************************************
 * RvH223End
 * ----------------------------------------------------------------------------
 * General: Terminates the class.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments: hH223Module - handle to the H.223 module.
 *****************************************************************************/
RvStatus RvH223End (IN HH223MODULE  hH223Module);


#if (RV_H223_USE_SPLIT == RV_YES)
/******************************************************************************
 * RvH223GlueSetEvHandlers
 * ----------------------------------------------------------------------------
 * General: Set the callbacks for the H.223 Glue indications when H.223
 *          is split between processes.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH223Module      - handle to the H.223 module.
 *         pevents          - Callback functions to set 
 *         eventsSize       - size of events structure
 *****************************************************************************/
RvStatus RvH223GlueSetEvHandlers(
    IN  HH223MODULE           hH223Module,
    IN  RvH223GlueEvHandlers  *pevents,
    IN  RvSize_t              eventsSize);

/******************************************************************************
 * RvH223GlueMuxtableEntries
 * ----------------------------------------------------------------------------
 * General: Set the muxtable entries
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hh223            - Handle to the H.223 instance.
 *         muxEntriesSize   - the size of the muxtable.
 *         atomArray        - Table atoms for each muxtable entry
 *         arraySize        - The size of each table atom.
 *****************************************************************************/
RvStatus RvH223GlueMuxtableEntries(
    IN  HH223           hh223,
    IN  RvUint32        muxEntriesSize,
    IN  TMuxTblAtom     *atomArray,
    IN  RvUint32        *arraySize);

#endif

/******************************************************************************
 * RvH223Construct
 * ----------------------------------------------------------------------------
 * General: Creates an instance of conversation and provides user with the
 *          handles to Muxer, Demux and CLC.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more objects to
 *                                         allocate.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hH223Module - handle to the H.223 module.
 *          pcfg        - H223 instance configuration parameters.
 * Output : phh223      - Pointer to be filled with H223 instance's handle.
 *          phdemux     - Pointer to be filled with Demux's handle.
 *          phmuxer     - Pointer to be filled with Muxer's handle.
 *          phcontrol   - Pointer to be filled with ControlLC's handle.
 *****************************************************************************/
RvStatus RvH223Construct (IN  HH223MODULE           hH223Module,
                          IN  TH223ConstructCfg    *pcfg,
                          OUT HH223                *phh223,
                          OUT HMUXER               *phmuxer,
                          OUT HDEMUX               *phdemux,
                          OUT HH223CONTROL         *phcontrol);

/******************************************************************************
 * RvH223Destruct
 * ----------------------------------------------------------------------------
 * General: Deletes an instance of the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if any object's handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223     - H223 instance's handle.
 *****************************************************************************/
RvStatus RvH223Destruct (IN  HH223  hh223);

/******************************************************************************
 * RvH223SetLevelCfg
 * ----------------------------------------------------------------------------
 * General: Sets muxing level related options for muxer and control channel.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223   - Handle to the H.223 instance.
 *          pcfg    - New configuration.
 *****************************************************************************/
RvStatus RvH223SetLevelCfg (IN  HH223  hh223,
                            IN  TMuxLevelCfg *pcfg);

#if (RV_H223_USE_STATISTICS == RV_YES)
/******************************************************************************
 * RvH223GetStatistics
 * ----------------------------------------------------------------------------
 * General: Get the H.223 statistics.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223   - Handle to the H.223 instance.
 * Output:  pStats  - Statistics information.
 *****************************************************************************/
RvStatus RvH223GetStatistics(
    IN  HH223           hh223,
    OUT TH223Statistics *pStats);
#endif /* (RV_H223_USE_STATISTICS == RV_YES) */

/******************************************************************************
 * RvH223OpenTxLogicalChannel
 * ----------------------------------------------------------------------------
 * General: Opens non-retransmissional transmitting logical channel.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223       - handle to the H.223 instance.
 *          palCfg      - configuration parameters.
 * Output:  phal        - pointer to be filled with an AL handle.
 *****************************************************************************/
RvStatus RvH223OpenTxLogicalChannel (IN  HH223            hh223,
                                     IN  TH223TxALCfg    *palCfg,
                                     OUT HTXAL           *phal);

/******************************************************************************
 * RvH223OpenRxLogicalChannel
 * ----------------------------------------------------------------------------
 * General: Opens non-retransmissional receiving logical channel.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223       - handle to the H.223 instance.
 *          palCfg      - configuration parameters.
 * Output:  phal        - pointer to be filled with an AL handle.
 *****************************************************************************/
RvStatus RvH223OpenRxLogicalChannel (IN  HH223            hh223,
                                     IN  TH223RxALCfg    *palCfg,
                                     OUT HRXAL           *phal);

/******************************************************************************
 * RvH223CloseTxLogicalChannel
 * ----------------------------------------------------------------------------
 * General: Closes non-retransmissional transmitting logical channel.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223      - handle to the H.223 instance.
 *          hal        - pointer to the AL.
 *****************************************************************************/
RvStatus RvH223CloseTxLogicalChannel (IN  HH223       hh223,
                                      IN  HTXAL       hal);

/******************************************************************************
 * RvH223CloseRxLogicalChannel
 * ----------------------------------------------------------------------------
 * General: Closes non-retransmissional receiving logical channel.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223      - handle to the H.223 instance.
 *          hal        - pointer to the AL.
 *****************************************************************************/
RvStatus RvH223CloseRxLogicalChannel (IN  HH223       hh223,
                                      IN  HRXAL       hal);

/******************************************************************************
 * RvH223CloseRtxLogicalChannel
 * ----------------------------------------------------------------------------
 * General: Closes retransmissional logical channels.
 *
 * Return Value: RV_OK  - if successful.
 *               otherwise - other modules' error codes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223      - handle to the H.223 instance.
 *          htxal      - handle to the transmitting AL.
 *          hrxal      - handle to the receiving AL.
 *****************************************************************************/
RvStatus RvH223CloseRtxLogicalChannel (IN  HH223       hh223,
                                       IN  HTXAL       htxal,
                                       IN  HRXAL       hrxal);

/******************************************************************************
 * RvH223GenerateMuxtable
 * ----------------------------------------------------------------------------
 * General: Generates muxtable according to the added LC-s.
 *
 * Return Value: RV_OK - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hh223      - handle to the H.223 instance.
 *          audioType - According to AMR codec (see RvH223defs.h).
 *          videoBitrate - In bits.
 *          dataBitrate  - In bits.
 *          enhancedCapability - Muxtable complexity level, according to H223.
 *****************************************************************************/
RvStatus RvH223GenerateMuxtable (IN  HH223              hh223,
                                 IN  EAudioFrameType    audioType,
                                 IN  RvUint32           videoBitrate,
                                 IN  RvUint32           dataBitrate,
                                 IN  RvBool             enhancedCapability);


#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)
/******************************************************************************
 * RvH223Save2Buffer
 * ----------------------------------------------------------------------------
 * General: save all the h223 related instances of a call into a buffer
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	hH223       - handle to mux instance.
 *          buffLen     - the buffer length.
 *          lenDone     - the used size of the buffer.
 *          pStatus     - The status before saving.
 * Output:  pBuffer     - the buffer.
 *          lenDone     - The used/reqired size of the buffer.
 *          pStatus     - The status after saving.
 *****************************************************************************/
void RvH223Save2Buffer(
      IN    HH223       hH223,
      OUT   RvUint8     *pBuffer,
      IN    RvSize_t    buffLen,
      INOUT RvSize_t    *lenDone,
      INOUT RvStatus    *pStatus);

/******************************************************************************
 * RvH223GetFromBuffer(

 * ----------------------------------------------------------------------------
 * General: rebuild and set all h.223 elements in the call
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	bufLen          -   size of buffer.
 *          lenDone         -   size of buffer already used.
 * Output:  pBuffer         -   the buffer.
 *          lenDone         -   size of buffer already used.
 *          phH223          -   pointer to handle of h.223 instance.
 *          phH223Control   -   pointer to handle of h.223 control instance.
 *          phMuxer         -   pointer to handle of h.223 mux instance.
 *          phDemux         -   pointer to handle of h.223 demux instance.
 *****************************************************************************/
void RvH223GetFromBuffer(
           OUT      HH223          phH223,
           OUT      RvUint8        *pBuffer,
           IN       RvSize_t       buffLen,
           INOUT    RvSize_t       *lenDone,
           INOUT    RvStatus       *pStatus);

#endif /* (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif /*_RV_H223_IFC_H*/
