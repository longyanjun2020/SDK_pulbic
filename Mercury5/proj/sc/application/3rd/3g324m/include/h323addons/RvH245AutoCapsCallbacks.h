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

#ifndef _RV_H245_AUTO_CAPS_CALLBACKS_H_
#define _RV_H245_AUTO_CAPS_CALLBACKS_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "RvH245AutoCapsTypes.h"
#include "RvH245AutoCapsValidation.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*                           FUNCTION HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * RvH245AutoCapsChannelStateChangeEv
 * ----------------------------------------------------------------------------
 * General: This function should be called from inside the implementation of the
 *          application of the cmEvCallControlStateChangedT() callback.
 *          The application must fill the information object with all the parameters
 *          at hand.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall     - The handle to the H.245 AutoCaps call object.
 *                             The application must set all the information
 *                             needed for the validation to this handle.
 *         hsChan            - The channel handle.
 *         state             - The state of the channel.
 *         stateMode         - The state mode of the channel.
 * Output: eChannelResponse  - The recommended channel response. If the recommended
 *                             response is Reject, then the reject reason can be found 
 *                             in the eRejectReason parameter.
 *                             It is the responsibility of the application to respond to the
 *                             channel.
 *         eRejectReason     - The reject reason of the channel. This parameter should be 
 *                             considered only if the eChannelResponse parameter recommends 
 *                             that the channel be rejected. Otherwise, this parameter 
 *                             should be ignored.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsChannelStateChangeEv(
    IN  HAUTOCAPSCALL                  hAutoCapsCall,
    IN  HCHAN                          hsChan,
    IN  cmChannelState_e               state,
    IN  cmChannelStateMode_e           stateMode,
    OUT RvH245AutoCapsChannelResponse  *eChannelResponse,
    OUT cmRejectLcnReason              *eRejectReason);


/******************************************************************************
 * RvH245AutoCapsChannelMasterSlaveConflictEv
 * ----------------------------------------------------------------------------
 * General: This function should be called from inside the implementation of the
 *          application of the cmEvChannelMasterSlaveConflictT() callback.
 *          The application must fill the information object with all the parameters
 *          at hand.
 *          Note that this module assumes that the application
 *          returns a negative value in the cmEvChannelMasterSlaveConflictT()
 *          callback.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall  - The handle to the H.245 AutoCaps call object.
 *                          The application must set all the information needed 
 *                          for the validation to this handle.
 *         hsChan         - Stack's handle for the channel.
 *         conflictType   - Type of conflict.
 *         confChans      - Array of handles of conflicting channels.
 *         numConfChans   - Number of channels in the array.
 *         message        - PVT node ID of the incoming OLC.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsChannelMasterSlaveConflictEv(
    IN      HAUTOCAPSCALL               hAutoCapsCall,
    IN      HCHAN                       hsChan,
    IN      cmH245ChannelConflictType   conflictType,
    IN      HCHAN                       *confChans,
    IN      int                         numConfChans,
    IN      RvPvtNodeId                 message);

/******************************************************************************
 * RvH245AutoCapsCallCapabilitiesExtEv
 * ----------------------------------------------------------------------------
 * General: This function should be called from inside the implementation of the
 *          application of the cmEvCallCapabilitiesExtT() callback.
 *          The application must fill the information object with all the parameters
 *          at hand.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall            - The handle to the H.245 AutoCaps call object.
 *                                    The application must set all the information 
 *                                    needed for the validation to this handle.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsCallCapabilitiesExtEv(
    IN  HAUTOCAPSCALL hAutoCapsCall);




#ifdef __cplusplus
}
#endif

#endif /* _RV_H245_AUTO_CAPS_CALLBACKS_H_ */
