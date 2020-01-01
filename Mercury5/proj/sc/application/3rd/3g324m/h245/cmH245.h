/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef CMH245_H
#define CMH245_H

/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "rvlog.h"
#include "rvtimer.h"
#include "rvrandomgenerator.h"
#include "ema.h"
#include "pvaltree.h"
#include "cmH245GeneralDefs.h"
#include "cmControl.h"

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/
RV_DECLARE_HANDLE(HH245); /* H.245 Instance handle */


/* Ema types */
#define CHAN          (100)
#define H225CALL      (1001)
#define H223CALL      (1002)


/* Log declarations for API and callback functions */
typedef void (*h245iAPIEnterEvT)(IN HAPP hApp, IN const char*line, ...);
typedef void (*h245iAPIExitEvT)(IN HAPP hApp, IN const char*line, ...);
typedef void (*h245iCBEnterEvT)(IN HAPP hApp, IN const char*line, ...);
typedef void (*h245iCBExitEvT)(IN HAPP hApp, IN const char*line, ...);

/* Notify changes in the state of a control object of a call. This is called for connected
   states only (Connected/Conference) and when MultiplexEntrySend mechanism is over. */
typedef void (*h245iNotifyStateEvT)(IN HCALL hCall, IN H245ControlState state);

/* Send a message callback. Every H.245 message is sent by calling this function
   directly. The actual sending is done by the user of the H.245 module. The messageNodeId
   should not be deleted by this callback */
typedef RvStatus (*h245iSendMessageEvT)(IN HCALL hCall, IN RvPvtNodeId messageNodeId, OUT RvBool * sentOnDummy);
typedef RvStatus (*h245iSendChanMessageEvT)(IN HCALL hCall, IN HCHAN hChan, IN RvPvtNodeId messageNodeId, OUT RvBool * sentOnDummy);

/* Start a timer */
typedef RvTimer* (*h245iTimerStartEvT)(
    IN HCONTROL     hCtrl,
    IN RvTimerFunc  eventHandler,
    IN void*        context,
    IN RvInt32      millisec);

/* Cancel a timer */
typedef RvStatus (*h245iTimerCancelEvT)(
    IN    HCONTROL  hCtrl,
    INOUT RvTimer   **timer);

/* Clear a timer that has timed-out */
typedef RvStatus (*h245iTimerClearEvT)(
    IN    HCONTROL  hCtrl,
    INOUT RvTimer   **timer);

/* Open logical channel in the H.223 module. The actual opening is done by the upper
   layer. */
typedef RvStatus (*h245iH223LogicalChannelEvT)(IN HCALL hCall, IN HCHAN hChan, IN RvBool isChannelOpen);

/* insert the demux table entries from the multiplex entry send message */
typedef RvStatus (*h245iH223MEStoDEMUXEvT)(
    IN  HCALL           h3G324mCall,
    IN  HAPP            h3G324m,
    IN  RvPvtNodeId     descriptors,
    OUT RvUint16        *acceptedEntries,
    OUT RvBool          *tooComplex);

/* Set the Mux-Level and Optional Header in the Demux module */
typedef RvStatus (*h245iH223MultiplexReconfiguration)(
    IN  HCALL           h3G324mCall,
    IN  RvPstFieldId    fieldId,
    IN  RvBool          bIsH223ModeChange);

/* Set the max MUX - PDU size to the Muxer module */
typedef RvStatus (*h245iMaxH223MUXPDUsize)(
    IN  HCALL           h3G324mCall,
    IN  RvUint16        maxMuxPduSize);

typedef RvBool (RVCALLCONV *cmCallInAnsweringStateT)(IN HCALL hsCall);

/* Notify the application that the remote side requested to reset the call */
typedef RvStatus (*h245iReceivedResetRequestT)(IN HCALL hCall);

/*clear ACP ignore data timer*/
typedef RvStatus (*h245iResetH223ACPIgnoreDataEvT)(
				IN HCHAN hChan);
/*clear ACP channels on reject*/
typedef RvStatus (*h245iClearH223ACPChannelEvT)(
                IN HCHAN hChan, 
                IN RvBool isVideo);
/*set mux default table for ACP*/
typedef RvStatus (*h245iSetH223ACPDefaultMuxTblEvT)(IN HCALL hCall);

/* request for a random number from the application */
typedef void (*h245ipfnRandomNumberT)(
    IN HAPP               h3G324m,
    IN HCALL              h3G324mCall,
    IN RvRandomGenerator  *seed,
    OUT RvRandom          *value);


/* Internal callbacks between the H.245 module and the stack on top of it */
typedef struct
{
    /* API logger functions */
    h245iAPIEnterEvT                  pfnAPIEnterEv;
    h245iAPIExitEvT                   pfnAPIExitEv;
    h245iCBEnterEvT                   pfnCBEnterEv;
    h245iCBExitEvT                    pfnCBExitEv;

    /* Timer functions */
    h245iTimerStartEvT                pfnTimerStartEv;
    h245iTimerCancelEvT               pfnTimerCancelEv;
    h245iTimerClearEvT                pfnTimerClearEv;

    /* Misc */
    h245iNotifyStateEvT               pfnNotifyStateEv;
    h245iSendMessageEvT               sendMessageForH245;
    h245iSendChanMessageEvT           sendMessageForH245Chan;

    h245iH223LogicalChannelEvT        pfnH223LogicalChannelEv;
    h245iH223MEStoDEMUXEvT            pfnH223MEStoDEMUXEv;
    h245iH223MultiplexReconfiguration pfnH223MultiplexReconfigurationEv;
    h245iMaxH223MUXPDUsize            pfnMaxH223MUXPDUsize;
    h245iReceivedResetRequestT        pfnReceivedResetRequestEv;
	h245iResetH223ACPIgnoreDataEvT		pfnResetH223ACPIgnoreData;
    h245iClearH223ACPChannelEvT			pfnClearH223ACPChannel;
    h245iSetH223ACPDefaultMuxTblEvT		pfnSetH223ACPDefaultMuxTbl;
    h245ipfnRandomNumberT             pfnRandomNumberEv;
    cmCallInAnsweringStateT           cmCallInAnsweringState;
} H245EvHandlers;



typedef struct
{
    int                     maxCalls;
    int                     maxChannels;

    /* Control Offset */
    int                     h225CtrlOffset;
    int                     h223CtrlOffset;

    H245EvHandlers          evHandlers; /* General H.245 Callbacks to the stack above */

    /* parameters that are used in H.245 and outside H.245 */
    RvLogMgr*               logMgr; /* Log manager to use */

    HPVT                    hVal;
    RvBool                  bIsPropertyModeNotUsed;  /* Mode used for the property database of
                                                        the stack */
    HPST                    hSynProtH245;
    RvPvtNodeId             h245Conf; /* H.245 configuration node id */
    HPST                    synOLC;

#if (RV_H245_LEAN_H223 == RV_NO)
    HPST                    hAddrSynH245;
    HPST                    h245TransCap;
    HPST                    h245RedEnc;
#endif

    HPST                    h245DataType;
#if (RV_H245_SUPPORT_H225_PARAMS == RV_YES)
    MibEventT               mibEvent;       /* MIB Callbacks to call */
    HMibHandleT             mibHandle;      /* Handle of MIB to use */
#endif
    int                     encodeBufferSize;
    RvWatchdog*             watchdog; /* Watchdog to use for resources */
    RvBool                  bSupportEFC; /* indicates whether to allocate enough memory for EFC */
} H245Config;




/******************************************************************************
 * H245Init
 * ----------------------------------------------------------------------------
 * General: Initialize an H.245 module.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  pH245Cfg     - Configuration parameters for the H245 module.
 *         hApp         - Application handle to associate with this module.
 * Output: pH245        - H245 module handle created.
 *****************************************************************************/
RvStatus H245Init(
    IN  H245Config  *pH245Cfg,
    IN  HAPP        hApp,
    OUT HH245       *pH245);


/******************************************************************************
 * H245End
 * ----------------------------------------------------------------------------
 * General: Destruct an H.245 module.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245        - Handle to the H.245 module.
 *****************************************************************************/
void H245End(IN HH245 hH245);


/******************************************************************************
 * H245Start
 * ----------------------------------------------------------------------------
 * General: Start the execution of the H.245 module.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245        - Handle to the H.245 module.
 *****************************************************************************/
void H245Start(IN HH245 hH245);


/******************************************************************************
 * H245Stop
 * ----------------------------------------------------------------------------
 * General: Stop the execution of the H.245 module.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245        - Handle to the H.245 module.
 *****************************************************************************/
void H245Stop(IN HH245 hH245);



#if (RV_H245_USE_HIGH_AVAILABILITY == RV_YES)

/******************************************************************************
 * H245encodeIntoBuffer
 * ----------------------------------------------------------------------------
 * General: Encodes a nodeID into the buffer, adding to it's length.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * input  : hVal      - pvt thingie
 *          nodeId    - nodeId to encode
 *          bufferLen - Size of the buffer
 *          length    - pointer to the length done so far
 *          ret       - current status
 * output : buffer    - The buffer with the encoded nodeId
 *          length    - updated length done
 *****************************************************************************/
void H245encodeIntoBuffer(
    IN    HPVT          hVal,
    IN    int           nodeId,
    OUT   RvUint8       *pBuffer,
    IN    RvSize_t      bufferLen,
    INOUT RvSize_t      *length,
    INOUT RvStatus      *status);


/******************************************************************************
 * H245decodeFromBuffer
 * ----------------------------------------------------------------------------
 * General: Decodes the buffer into a node Id.
 *
 * Return Value: RV_OK on success error code (negative values) on failure. 
 * ----------------------------------------------------------------------------
 * Arguments:
 * input  : hVal      - pvt thingie
 *          hSyn      - syntax tree.
 *          nodeId    - pointer to nodeId to decode to
 *          length    - Size of the buffer
 *          lenDone   - pointer to the length done so far
 *          buffer    - The buffer with the encoded nodeId
 * output : lenDone   - updated length done
 *****************************************************************************/
RvStatus H245decodeFromBuffer(
    IN    HPVT              hVal,
    IN    HPST              hSyn,
    IN    RvPvtNodeId       *nodeId,
    IN    RvUint8           *buffer,
    IN    RvSize_t          length,
    INOUT RvSize_t          *lenDone,
    INOUT RvStatus          *status);

#endif /* (RV_H245_USE_HIGH_AVAILABILITY == RV_YES) */


HCHAN cmH245GetChannelList(
              HCONTROL hControlChan);


void cmH245SetChannelList(
              HCONTROL hControlChan,HCHAN ch);


/* Cross Reference functions */

/************************************************************************
 * cmiGetH245Handle
 * purpose: Get the H245 handle.
 *          note that we are counting on the fact that the H.245 handle is declared
 *          first in the cmElem object.
 * input  : hApp    - Stack's application handle
 * output : none
 * return : HH245 handle.
 ************************************************************************/
HH245 cmiGetH245Handle(IN HAPP hApp);

/************************************************************************
 * cmiGetByControl
 * purpose: get the call handle from the control handle.
 * input  : ctrl         - the control handle.
 * output : none
 * return : The call handle.
 ************************************************************************/
HCALL cmiGetByControl(HCONTROL ctrl);

/************************************************************************
 * cmiGetControl
 * purpose: get the control handle from the call handle.
 * input  : call         - the call handle.
 * output : none
 * return : The control handle.
 ************************************************************************/
HCONTROL cmiGetControl(HCALL call);


/************************************************************************
 * cmiGetIsControl
 * purpose: Get the indication for H.245 control connection.
 * input  : hsCall - handle to the call.
 * output : none
 * return : RV_TRUE if the connection exists, otherwise RV_FALSE.
 ************************************************************************/
RvBool cmiGetIsControl(IN HCALL hsCall);

/************************************************************************
 * cmiSetIsControl
 * purpose: Set the indication for H.245 control connection.
 * input  : hsCall     - handle to the call.
 *          bIsControl - RV_TRUE if the H.245 connection exists, otherwise RV_FALSE.
 * output : none
 * return : none
 ************************************************************************/
void cmiSetIsControl(IN HCALL hsCall, RvBool bIsControl);

#if (RV_H245_SUPPORT_H225_PARAMS == 1)

/************************************************************************
 * cmiGetIsFastStartFinished
 * purpose: Get the indication that tells us whether the fast start process was finished.
 * input  : hsCall - handle to the call.
 * output : none
 * return : RV_TRUE if the fast start process was finished, otherwise RV_FALSE.
 ************************************************************************/
RvBool cmiGetIsFastStartFinished(IN HCALL hsCall);

/************************************************************************
 * cmiSetIsFastStartFinished
 * purpose: Set the indication that tells us whether the fast start process was finished.
 * input  : hsCall               - handle to the call.
 *          bIsFastStartFinished - RV_TRUE if the fast start process was finished, otherwise RV_FALSE.
 * output : none
 * return : none
 ************************************************************************/
void cmiSetIsFastStartFinished(IN HCALL hsCall, RvBool bIsFastStartFinished);

/******************************************************************************
 * cmiGetExtendedFastConectStatus
 * ----------------------------------------------------------------------------
 * General: Get the current status of the EFC.
 *
 * Return Value: The current status. If this is the calling side, the status
 * will be Undetermined until a response is received, at which time it will
 * change to Approved or No. If this is the receiving side, the status will be
 * No, Offered or Required, until the local support is set, in which time it
 * will change to Approved or No.
 * ----------------------------------------------------------------------------
 * Arguments:
 * input : hsCall  - handle to the call
 *         bOrigin - RV_TRUE if we are the origin of the call
 * Output: None.
 *****************************************************************************/
cmExtendedFastConnectState_e cmiGetExtendedFastConectStatus(IN HCALL  hsCall,
                                                            IN RvBool bOrigin);

/******************************************************************************
 * cmiSetExtendedFastConectStatus
 * ----------------------------------------------------------------------------
 * General: Set the current side's support of EFC.
 *
 * Return Value: Non-negative value on success, Negative value on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * input : hsCall      - Handle to the call
 *         newEFCState - the current side's support of EFC. must be either No,
 *                       Supported or Required.
 * Output: None.
 *****************************************************************************/
RvStatus cmiSetExtendedFastConectStatus(IN HCALL hsCall,
                                        IN cmExtendedFastConnectState_e newEFCState);

/******************************************************************************
 * cmiSetRemoteExtendedFastConectStatus
 * ----------------------------------------------------------------------------
 * General: Set the remote side's support of EFC.
 *
 * Return Value: Non-negative value on success, Negative value on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * input : hsCall      - Handle to the call
 *         remEFCState - the remote side's support of EFC. must be either No,
 *                       Supported or Required.
 * Output: None.
 *****************************************************************************/
RvStatus cmiSetRemoteExtendedFastConectStatus(IN HCALL hsCall,
                                              IN cmExtendedFastConnectState_e remEFCState);

#else

#define cmiGetIsFastStartFinished(hsCall) (RV_TRUE)
#define cmiSetIsFastStartFinished(hsCall,bIsFastStartFinished)
#define cmiGetExtendedFastConectStatus(hsCall,bOrigin) (cmExtendedFastConnectNo)
#define cmiSetExtendedFastConectStatus(hsCall,newEFCState) (RV_ERROR_NOTSUPPORTED)
#define cmiSetRemoteExtendedFastConectStatus(hsCall,remEFCState) (RV_ERROR_NOTSUPPORTED)

#endif

/************************************************************************
 * cmiGetFirstChannel
 * purpose: Get the first channel in the channel list.
 * input  : hsCall - handle to the call.
 * output : none
 * return : handle of the first channel.
 ************************************************************************/
HCHAN cmiGetFirstChannel(IN HCALL hsCall);

/************************************************************************
 * cmiGetNextChannel
 * purpose: Get the next channel in the channel list.
 * input  : hsChan - handle to the channel.
 * output : none
 * return : handle of the next channel.
 ************************************************************************/
HCHAN cmiGetNextChannel(IN HCHAN hsChan);

#if (RV_H245_SUPPORT_H223_PARAMS == 1)

/************************************************************************
 * cmiGetChannelDataType
 * purpose: Get the data type of the channel.
 * input  : hsChan - handle to the channel.
 * output : none
 * return : Data type.
 ************************************************************************/
cmChannelDataType cmiGetChannelDataType(IN HCHAN hsChan);

/************************************************************************
 * cmiGetControlReset
 * purpose: Get the indication for H.245 module that the user requested
 *          to perform a reset procedure.
 * input  : hsCall - handle to the call.
 * output : none
 * return : RV_TRUE if the user requested reset procedure, otherwise RV_FALSE.
 ************************************************************************/
RvBool cmiGetControlReset(IN HCALL hsCall);


/************************************************************************
 * cmiGetControlResetInitiator
 * purpose: Get the indication for H.245 module that the user is the initiator
 *          of the Reset procedure.
 * input  : hsCall - handle to the call.
 * output : none
 * return : RV_TRUE if the user is the initiator of the reset procedure, otherwise RV_FALSE.
 ************************************************************************/
RvBool cmiGetControlResetInitiator(IN HCALL hsCall);

/************************************************************************
 * cmiSetControlResetInitiator
 * purpose: Get the indication from H.245 module that the user is the initiator
 *          of the Reset procedure.
 * input  : hsCall     - handle to the call.
 *          bReset - RV_TRUE if to reset the call, otherwise RV_FALSE.
 * output : none
 * return : none
 ************************************************************************/
void cmiSetControlResetInitiator(IN HCALL hsCall, RvBool bResetInitiator);

/******************************************************************************
 * cmiGetSaveCallIndication
 * ----------------------------------------------------------------------------
 * General: return the value of bSaveCallIndication flag from the control.
 *
 * Return Value: bSaveCallIndication value
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hsCall          -   The call handle.
 *  
 * Output:  None..
 *****************************************************************************/
RvBool cmiGetSaveCallIndication(IN HCALL hsCall);

/******************************************************************************
 * cmiStartChannelTimer
 * ----------------------------------------------------------------------------
 * General: start the channel timer.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hVal          -   The h245 value tree
 *          hsChan        -   The channel handle
 * Output:  ppTimer       -   The channel's timer
 *****************************************************************************/
void cmiStartChannelTimer(IN  HPVT      hVal, 
                          IN  HCHAN     hsChan, 
                          OUT RvTimer   **ppTimer);



#if (RV_H245_USE_HIGH_AVAILABILITY == RV_YES)

/******************************************************************************
 * cmiCtrlSaveToBuffer
 * ----------------------------------------------------------------------------
 * General: save the control object, channels and capabilities into a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hVal         - The value tree.
 *         ctrl         - The control object.
 *         chanList     - The call channel list.
 *         buffLen      - The size of the buffer.
 *         lenDone      - The used size before saving.
 *         pStatus      - status before saving.
 *         
 * Output: pBuffer      - The buffer.
 *         lenDone      - The used/required size after saving.
 *         pStatus      - status after saving.
 *****************************************************************************/
void cmiCtrlSaveToBuffer(IN     HPVT            hVal,
                         IN     H245Control*    ctrl,
                         IN     H245Channel *   chanList,
                         OUT    RvUint8*        pBuffer,
                         IN     RvSize_t        buffLen,
                         INOUT  RvSize_t        *lenDone,
                         INOUT  RvStatus        *pStatus);

/******************************************************************************
 * cmiCtrlClean
 * ----------------------------------------------------------------------------
 * General: clean the control object, channels and capabilities of a call before
 *          update for HighAvailability.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hVal         - The value tree.
 *         ctrl         - The control object.
 *         chanList     - The call channel list.
 * Output: None.
 *****************************************************************************/
void cmiCtrlClean(IN HPVT           hVal,
                  IN H245Control    *ctrl,
                  IN H245Channel    *chanList);

/******************************************************************************
 * cmiCtrlGetFromBuffer
 * ----------------------------------------------------------------------------
 * General: restore a control object, including channels and capabilities
 *          from buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hVal         - The value tree.
 *         hSynProtH245 - H245 message syntax.
 *         h245DataType - Channel DataType syntax tree.
 *         newControl   - The new control object
 *         buffLen      - The size of the buffer.
 *         lenDone      - The used size before saving.
 *         pStatus      - status before saving.
 *         
 * Output:
 *         pBuffer      - The buffer.
 *         lenDone      - The used/required size after saving.
 *         pStatus      - status after saving.
 *****************************************************************************/
void cmiCtrlGetFromBuffer(
    IN    HPVT            hVal,
    IN    HPST            hSynProtH245,
    IN    HPST            h245DataType,
    OUT   H245Control     *newControl,
    IN    RvUint8         *pBuffer,
    IN    RvSize_t        bufLen, 
    INOUT RvSize_t        *lenDone,
    INOUT RvStatus        *pStatus);

/******************************************************************************
 * cmiCtrlActivateH223Channel
 * ----------------------------------------------------------------------------
 * General: Calls the H324mH223LogicalChannelEv for each channel to open the h223
 *          objects of the channel.
 *
 * Return Value: RV_OK on success, negative values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan           - The channel handle in the stack.
 * Output:None.
 *****************************************************************************/
RvStatus cmiCtrlActivateH223Channel(IN HCHAN    hsChan);

#endif /* (RV_H245_USE_HIGH_AVAILABILITY == RV_YES) */


/******************************************************************************
 * cmiResetH223ACPIgnoreDataTimer
 * ----------------------------------------------------------------------------
 * General: Calls the H324mResetH223ACPIgnoreDataEv. Called every time an
 *          incoming OLC is received and channel is not rejected, to avoid checking
 *          if a received data on an ACP channel should be ignored.
 *
 * Return Value: RV_OK on success, negative values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan           - The channel handle in the stack.
 * Output:None.
 *****************************************************************************/
RvStatus cmiResetH223ACPIgnoreDataTimer(IN HCHAN    hsChan);

/******************************************************************************
 * cmiClearH223ACPChannel
 * ----------------------------------------------------------------------------
 * General: Calls the H324mClearH223ACPChannelEv. Called every time an
 *          incoming channel is rejected or droped.         
 *
 * Return Value: RV_OK on success, negative values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan           - The channel handle in the stack.
 *         isVideo          - RV_TRUE if channel is a video channel - RV_FALSE
 *                            if it's an audio channel.
 * Output:None.
 *****************************************************************************/
RvStatus cmiClearH223ACPChannel(IN HCHAN    hsChan, 
                                IN RvBool   isVideo);

/******************************************************************************
 * cmiSetH223ACPDefaultMuxTbl
 * ----------------------------------------------------------------------------
 * General: Sets default mux table for ACP .         
 *
 * Return Value: RV_OK on success, negative values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall      - The call handle in the stack.
 * Output:None.
 *****************************************************************************/
RvStatus cmiSetH223ACPDefaultMuxTbl(IN HCALL    hsCall);

/******************************************************************************
 * cmiSetCtrlACP
 * ----------------------------------------------------------------------------
 * General: Sets the bACP boolean in the control object .         
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall      - The call handle in the stack.
 *         value       - The value to set.
 * Output:None.
 *****************************************************************************/
void cmiSetCtrlACP(IN HCALL    hsCall, RvBool value);

/*****************************************************************************
 * cmiSetCtrlMPC
 * ----------------------------------------------------------------------------
 * General: Sets the bMPCinUse boolean in the control object .         
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall      - The call handle in the stack.
 *         value       - The value to set.
 * Output:None.
 *****************************************************************************/
void cmiSetCtrlMPC(IN HCALL    hsCall, RvBool value);

/************************************************************************
 * cmiGettAcceptChannelUpgrades
 * purpose: Set the bAcceptChannelStatus in the H245 call control.
 * input  : hsCall	- he call handle in the stack.
 * output : value	- The current value of bAcceptChannelUpgrades in the H245 control.
 * return : none
 ************************************************************************/
void cmiGetAcceptChannelUpgrades(
		 IN HCALL		hsCall, 
         IN RvBool      *value);

#endif

#if (RV_H245_SUPPORT_H225_PARAMS == 1)

typedef int
    (RVCALLCONV * cmH245EvCallFastStartSetupT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        OUT IN  cmFastStartMessage  *fsMessage);

typedef int
    (RVCALLCONV*cmH245EvCallFastStartT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall);

typedef int
    (RVCALLCONV*cmH245EvExtFastConnectProposalCanceledT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvInt32             sessionId,
        IN      RvPvtNodeId         proposalNode);

typedef  struct
{
    cmH245EvCallFastStartSetupT                 cmEvCallFastStartSetup;
    cmH245EvCallFastStartT                      cmEvCallFastStart;
    cmH245EvExtFastConnectProposalCanceledT     cmH245EvExtFastConnectProposalCanceled;
} H245SupportH225CallEvent;


RvStatus H245SetH225CallEventHandler(
    IN HH245                        hH245,
    IN H245SupportH225CallEvent*    callEvents,
    IN RvSize_t                     size);

/************************************************************************
 * cmiStopControlTimers
 * purpose: Stop the control timers after tunneling was rejected.
 * input  : hsCall     - handle to the call.
 * output : none
 * return : none
 ************************************************************************/
RvStatus cmiStopControlTimers(IN HCALL hsCall);

/************************************************************************
 * cmiStartControlTimers
 * purpose: Restart the control timers after a real H.245 connection was 
 *          established.
 * input  : hsCall     - handle to the call.
 * output : none
 * return : none
 ************************************************************************/
RvStatus cmiStartControlTimers(IN HCALL hsCall);

/* Util functions */
int cmVtToTA_H245(HPVT hVal,int nodeId, cmTransportAddress* ta);

int cmTAToVt_H245(HPVT hVal,int nodeId, cmTransportAddress* ta);

#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */




#ifdef __cplusplus
}
#endif


#endif  /* CMH245_H */
