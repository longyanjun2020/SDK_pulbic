/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION RADVISION Ltd.. No part of this document may be reproduced
in any form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV3G324M_HA_H_
#define _RV3G324M_HA_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "Rv3G324mCallTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/

 /******************************************************************************
 * Rv3G324mCallHaActivateCallEv
 * ----------------------------------------------------------------------------
 * General: Application function type. Called from Rv3G324mCallHaActivateSingleCall() 
 *          each time a stored call is activated.
 *
 * Return Value: RV_OK if successful. Other on failure. 
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mAppCall  -   The call handle in the application.
 *          h3G324mCall     -   The call handle in the Stack.
 *          state           -   The call state.
 *          stateMode       -   The call state mode.
 * Output:  None.          
 *****************************************************************************/
typedef RvStatus (*Rv3G324mCallHaActivateCallEv)(
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallState       state,
    IN  Rv3G324mCallStateMode   stateMode);

/******************************************************************************
 * Rv3G324mCallHaActivateChannelEv
 * ----------------------------------------------------------------------------
 * General: Application function type. Called from Rv3G324mCallHaActivateSingleCall() 
 *          each time a channel is activated.
 *
 * Return Value: RV_OK if successful. Other on failure. 
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mAppCall  -   The call handle in the application.
 *          h3G324mCall     -   The call handle in the Stack.
 *          hsChan          -   The channel handle in the Stack.
 *          channelDataType -   The channel's logical dataType.
 * Output:  haChan          -   The channel handle in the application.
 *****************************************************************************/
typedef RvStatus (*Rv3G324mCallHaActivateChannelEv)(
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HCHAN                   hsChan,
    IN  cmChannelDataType       channelDataType,
    OUT HAPPCHAN                *haChan);




/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/

#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)

/******************************************************************************
 * Rv3G324mCallHaGetBuffer
 * ----------------------------------------------------------------------------
 * General: Saves a call in a buffer. This function saves the call object, 
 *          the h223, mux instance, demux instance, h223 control, h245 control 
 *          instance and channels. Also encoded in the buffer are the value 
 *          trees of capabilities and channel dataType. This function should 
 *          be called by the application each time the saveCallIndication flag 
 *          in the call is set. The saved call buffer is then used by the 
 *          stand-by machine to store the call using Rv3G324mCallHaAdd().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mCall     -   The call handle.
 *          pLength         -   The size of the buffer provided by the application.
 * Output:  pBuffer         -   The buffer provided by the application, 
 *                              which is filled up by this function.
 *          pLength         -   The required buffer size if the size provided by the
 *                              application was too small..
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallHaGetBuffer(
    IN      HCALL       h3G324mCall,
    OUT     RvUint8     *pBuffer,
    INOUT   RvSize_t    *pLength);

/******************************************************************************
 * Rv3G324mCallHaAdd
 * ----------------------------------------------------------------------------
 * General: Stores a saved call from a buffer created by 
 *          Rv3G324mCallHaGetBuffer() in a stored call object.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324m         -   The Stack handle.
 *          h3G324mAppCall  -   The call handle in the application.
 *          h3G324mCall     -   The call handle. Can be NULL for new calls to be stored.
 *          pBuffer         -   The buffer provided by the application.
 *          pLength         -   The size of the buffer provided by the application
 * Output:  none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallHaAdd(
    IN     HAPP        h3G324m,
    IN     HAPPCALL    h3G324mAppCall,
    IN     HCALL       h3G324mCall,
    IN     RvUint8     *pBuffer,
    IN     RvSize_t    *pLength);

/******************************************************************************
 * Rv3G324mCallHaDelete
 * ----------------------------------------------------------------------------
 * General: Deletes a stored call object.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mCall     -   The call handle.
 * Output:  None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallHaDelete(
    IN     HCALL       h3G324mCall);

/******************************************************************************
 * Rv3G324mCallHaActivateSingleCall
 * ----------------------------------------------------------------------------
 * General: Activates a single stored call object. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mCall         -   The call handle in the Stack.
 *          activateCallCB      -   The callback supplied by the application, 
 *                                  which is called each time a call is activated.
 *          activateChannelCB   -   The callback supplied by the application, 
 *                                  called each time a channel is activated.
 * Output:  None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallHaActivateSingleCall(
    IN      HCALL                           h3G324mCall,
    IN      Rv3G324mCallHaActivateCallEv    activateCallCB,
    IN      Rv3G324mCallHaActivateChannelEv activateChannelCB);

/******************************************************************************
 * Rv3G324mCallHaActivateCalls
 * ----------------------------------------------------------------------------
 * General: Activates all stored calls.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   H3G324m             -   The Stack handle.
 *          activateCallCB      -   The callback supplied by the application, 
 *                                  which is called each time a call is activated.
 *          activateChannelCB   -   The callback supplied by the application, 
 *                                  which is called each time a channel is activated.
 * Output:  None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallHaActivateCalls(
    IN      HAPP                            H3G324m,
    IN      Rv3G324mCallHaActivateCallEv    activateCallCB,
    IN      Rv3G324mCallHaActivateChannelEv activateChannelCB);


#else
#define Rv3G324mCallHaGetBuffer(_call, _buf, _len) RV_ERROR_NOTSUPPORTED
#define Rv3G324mCallHaAdd(_stack, _appcall, _call, _buf, len) RV_ERROR_NOTSUPPORTED
#define Rv3G324mCallHaDelete(_call) RV_ERROR_NOTSUPPORTED
#define Rv3G324mCallHaActivateSingleCall(_call, _callCb, _chanCb) RV_ERROR_NOTSUPPORTED
#define Rv3G324mCallHaActivateCalls(_inst, _callCb, _chanCb) RV_ERROR_NOTSUPPORTED

#endif /* (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif /* _RV3G324M_HA_H_*/
