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

#ifndef _H245_AUTO_CAPS_TYPES_INTERNAL_H_
#define _H245_AUTO_CAPS_TYPES_INTERNAL_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "rvtypes.h"
#if (RV_H245_SUPPORT_H223_PARAMS == 1)
#include "Rv3G324m.h"
#else
#include "cm.h"
#endif /* (RV_H245_SUPPORT_H223_PARAMS == 1) */
#include "RvH245AutoCapsTypes.h"
#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/

#define MAX_CHANNEL_REJECTIONS 2 /* Number of times that we allow the remote terminal
                                    reject a channel before the local terminal stop
                                    opening the channel. */
    
/* ACP */

/* RvH245AutoCapsMONAStatus
 * ------------------------------------------------------------------------
 * This enumeration Defines the MONA status of the call's autoCaps.*/
typedef enum
{
    RvH245AutoCapsACPStatusOff,
    RvH245AutoCapsACPStatusOn
}RvH245AutoCapsACPStatus;

/* RvH245AutoCaps
 * ------------------------------------------------------------------------
 * This structure defines the information needed for the H.245 AutoCaps
 * module. This structure is used by all H.245 AutoCaps instances.
 */
typedef struct
{
    HPST                            hPstDataType;                  /* The DataType PST handle */
    RvLogSource                     hLog;                          /* Log manager for log printing. */
    RvH245AutoCapsValidateFunctions *validateFunctionsArray;       /* The validation function provided by the application to match caps and get
                                                                      GCD of caps which are not supported in this add-on */
    RvUint32                        numberOfValidationFunctions;   /* Maximum number of validation functions allocated */
} RvH245AutoCaps;


/* RvH245AutoCapsCall
 * ------------------------------------------------------------------------
 * This structure defines the information that the application should pass
 * to in each API call.
 */
typedef struct
{
    RvH245AutoCaps                              *autoCaps;   /* The H.245 AutoCaps object */
    HCALL                                       hCall;       /* The handle of the call. */
    HCHAN                                       hAudioChan;  /* The handle of the outgoing audio channel. */
    HCHAN                                       hVideoChan;  /* The handle of the outgoing video channel. */
    HCHAN                                       hVideo2Chan; /* The handle of the second outgoing video channel - not
                                                                in use currently. */
    HPVT                                        hPvt;        /* The PVT handle used for PVT manipulations. */
    void                                        *context;    /* The context handle provided by application
                                                                that can then be used in validation functions
                                                                and in callbacks. */
    RvH245AutoCapsGetNewChannelEv               pfnGetNewChannelEv; /* Event handler of application when new channel
                                                                       handle is needed by the add-on. */
    RvH245AutoCapsUpdateCapabilityInformationEv pfnUpdateCapabilityInformationEv; /* Event handler of application that is
                                                                                     used when the application wants to update parameters
                                                                                     to a dataType of an OLC just before the opening. */
    RvBool                                      bOpenNewAudioChannel;    /* Defines an indication where an an audio channel gets closed
                                                                            and a new channel should be opened instead. */
    RvBool                                      bOpenNewVideoChannel;    /* Defines an indication where an an video channel gets closed
                                                                            and a new channel should be opened instead. */
    RvBool                                      bEmptyTCS;   /* Defines whether the stack received an empty TCS message. */
    RvBool                                      bLocalEmptyTCS;   /* Defines whether the stack sent an empty TCS message. */
    RvPvtNodeId                                 incomingAudioDataType;   /* Defines the dataType of the incoming audio channel. We keep it
                                                                            for the reopening of our channel after our previous channel was rejected. */
    RvPvtNodeId                                 incomingVideoDataType;   /* Defines the dataType of the incoming video channel. We keep it
                                                                            for the reopening of our channel after our previous channel was rejected. */
    RvBool                                      bMimicAudioChannel;    /* Defines an indication where an audio channel gets rejected from unknown
                                                                          and a new channel should be opened instead. */
    RvBool                                      bMimicVideoChannel;    /* Defines an indication where a video channel gets rejected from unknown
                                                                          and a new channel should be opened instead. */
    RvBool                                      bMimicVideoReverseChannel;    /* Defines an indication where a bi-directional video channel gets rejected
                                                                                 due to unsuitableReverseParameters reason and a new channel should be
                                                                                 opened instead. */
    RvUint8                                     audioReject;            /* Defines the number of rejections for the audio outgoing channel. */
    RvUint8                                     videoReject;            /* Defines the number of rejections for the video outgoing channel. */

    RvBool                                      bAudioCapFound;         /* Check if no simultaneous audio and video capabilities were found but only audio */
    RvBool                                      bVideoCapFound;         /* Check if no simultaneous audio and video capabilities were found but only video */

    /* ACP */
    RvH245AutoCapsACPStatus                     ACPStatus;              /*The status of the autoCaps regarding the ACP*/
    RvBool                                      bVideoAL3Only;          /* Defines whether only AL3 video channel is supported by both sides */
    RvBool                                      bOpenNullData;          /* Defines whether Null data channel should be opened */

	/* Non standard channels */
	RvPvtNodeId									nonStandardNodeId;      /* The node id to be used in outgoing channel in case that
																		   the remote side acted in a non standard way */
    RvInt32  									nonStandardCapEntryNum; /* The capability entry number in cap set of the non standard channel */
    
    /* Do not change the following parameters */
    RvBool                                      bSessionResetCapPresent;  /* Defines whether SessionReset is supported by both sides. */
    RvUint16                                    maximumAl2SDUSize;   /* Holds the incoming maximumAl2SDUSize parameter value. */
    RvUint16                                    maximumAl3SDUSize;   /* Holds the incoming maximumAl3SDUSize parameter value. */
    RvUint16                                    maximumDelayJitter;  /* Holds the incoming maximumDelayJitter parameter value. */
} RvH245AutoCapsCall;


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * H245AutoCapsValidateNewCaps
 * ----------------------------------------------------------------------------
 * General: Validate the capabilities with the new received capabilities.
 *          If the already opened channels do not fit anymore, they will be
 *          closed and reopened with new capabilities.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall            - The handle to the H.245 AutoCaps call object.
 *                                    The application must set to this handle
 *                                    all the information needed for the
 *                                    validation.
 * Output: None.
 *****************************************************************************/
RvStatus RVCALLCONV H245AutoCapsValidateNewCaps(
    IN     HAUTOCAPSCALL              hAutoCapsCall);

/******************************************************************************
 * H245AutoCapsValidateIncomingChannel
 * ----------------------------------------------------------------------------
 * General: Validate that the capability of the incoming channel is under
 *          the constraints of capabilities from both sides. If it is valid
 *          and the outgoing channel hasn't been opened yet then the outgoing
 *          channel will use the capability of the incoming channel.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall            - The handle to the H.245 AutoCaps call object.
 *                                    The application must set to this handle
 *                                    all the information needed for the
 *                                    validation.
 *         hChan                    - The handle of the incoming channel.
 * Output: eChannelResponse         - The recommended channel response. If the recommended
 *									  response is Reject, then the reject reason can be found in
 *									  eRejectReason parameter.
 *         eRejectReason            - The reject reason of the channel. This parameter should be considered
 *									  only if eChannelResponse parameter recommends to reject the channel.
 *									  Otherwise, this parameter should be ignored.
 *****************************************************************************/
RvStatus RVCALLCONV H245AutoCapsValidateIncomingChannel(
    IN     HAUTOCAPSCALL				  hAutoCapsCall,
    IN     HCHAN						  hChan,
	OUT    RvH245AutoCapsChannelResponse  *eChannelResponse,
	OUT	   cmRejectLcnReason			  *eRejectReason);

#ifdef __cplusplus
}
#endif

#endif /* _H245_AUTO_CAPS_TYPES_INTERNAL_H_ */
