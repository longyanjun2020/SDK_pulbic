/***********************************************************************
Copyright (c) 2005 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..
RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_3G324M_CALL_H223_GLUE_H_
#define _RV_3G324M_CALL_H223_GLUE_H_

/***********************************************************************
The API functions in this file can be used by the application only
if it has been compiled without the H.223 module embedded inside the
stack.
This happens when the application wishes to run the H.223 on a different
processor for load balancing or due to other reasons.

This API is specifically used to pass information to the 3G-324M
Call manager side from the H.223 module.

Rv3G324m.h should be included instead of including this header file
directly.
***********************************************************************/


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "Rv3G324mCallTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (RV_H223_USE_SPLIT == RV_YES)

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * Rv3G324mCallH223GlueChannelConstruct
 * ----------------------------------------------------------------------------
 * General: Callback function called when a channel is constructed.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppChannel    - The channel handle in the application. 
 *         All other IN parameters are channel-specific configuration parameters.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueChannelConstruct) (
    IN  HAPPCHAN                h3G324mAppChan,
    IN  cmH223ALLevel           adaptationLayerLevel,
    IN  RvBool                  bIsFramed,
    IN  RvBool                  bIsSegmentable,
    IN  RvBool                  bUseSequenceNumbering,
    IN  RvInt32                 controlFieldSize,
    IN  RvUint16                logicalChannelNumber,
    IN  RvUint16                reverseLogicalChannelNumber,
    IN  RvBool                  bIsDuplex,
    IN  RvBool                  bIsIncoming,
    IN  RvInt32                 channelType);

/******************************************************************************
 * Rv3G324mCallH223GlueChannelDestruct
 * ----------------------------------------------------------------------------
 * General: Callback function called when a channel is destructed.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppChannel    - The channel handle in the application.
 *         All other IN params are channel-specific configuration parameters.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueChannelDestruct) (
    IN  HAPPCHAN                h3G324mAppChan);

/******************************************************************************
 * Rv3G324mCallH223GlueDemuxSetMuxtableEntry
 * ----------------------------------------------------------------------------
 * General: Callback function called when a muxtable entry needs to be set in 
 * the demultiplexer.
 *          The application should implement this callback by calling
 *          Rv3G324mH223CallDemuxSetMuxtableEntry() on the H.223 application side.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall          - The call handle in the Stack.
 *         h3G324mAppCall       - The call handle in the application.
 *         muxEntry             - The multiplex entry number.
 *         patoms               - Array of atoms to be parsed into muxtable entry.
 *         arraySize            - atomArray size.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueDemuxSetMuxtableEntry) (
    IN  HCALL                   h3G324mCall,
    IN  HAPPCALL                h3G324mAppCall,
    IN  RvUint32                muxEntry,
    IN  void                    *patoms,
    IN  RvUint32                arraySize);


/******************************************************************************
 * Rv3G324mCallH223GlueSendControlEv
 * ----------------------------------------------------------------------------
 * General: Callback function called when an H.245 message needs to be sent on 
 * the H.223 control channel of a call. The application should implement 
 * this callback by calling Rv3G324mH223CallSendControl() on the H.223 
 * application side.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall          - The call handle in the Stack.
 *         h3G324mAppCall       - The call handle in the application.
 *         pBuffer              - Buffer holding the control messages.
 *         bufferSize           - Size of the buffer.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueSendControlEv) (
    IN  HCALL                   h3G324mCall,
    IN  HAPPCALL                h3G324mAppCall,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                bufferSize);

/******************************************************************************
 * Rv3G324mCallH223GlueClearMuxtableEv
 * ----------------------------------------------------------------------------
 * General:  Callback function called when a muxtable is cleared.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mAppCall       - The call handle in the application.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueClearMuxtableEv) (
    IN  HAPPCALL                h3G324mAppCall);


/******************************************************************************
 * Rv3G324mCallH223GlueGenerateMuxtableEv
 * ----------------------------------------------------------------------------
 * General:  Callback function called when a muxtable should be generated.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mAppCall      - The call handle in the application.
 *         audioType            - According to AMR codec (see RvH223defs.h).
 *         videoBitrate         - In bits.
 *         dataBitrate          - In bits.
 *         enhancedCapability   - Muxtable complexity level, according to H223.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueGenerateMuxtableEv) (
    IN  HAPPCALL           h3G324mAppCall,
    IN  RvInt32            audioType,
    IN  RvUint32           videoBitrate,
    IN  RvUint32           dataBitrate,
    IN  RvBool             enhancedCapability);
    
/******************************************************************************
 * Rv3G324mCallH223GlueMuxtableAddEntryEv
 * ----------------------------------------------------------------------------
 * General:  Callback function called when a muxtable should be generated.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   h3G324mAppCall       - The call handle in the application.
 *          audioSize   - Size of audio frame in bytes in this entry.
 *          video1Size  - Size of video1 to multiplex in this entry, 0 if none. 
 *                        For an entry with more than 1 segmentable entry, this 
 *                        should be small enough to serve as ratio.
 *          video2Size  - Size of video2 to multiplex in this entry, 0 if none. 
 *                        For an entry with more than 1 segmentable entry, this 
 *                        should be small enough to serve as ratio.
 *          dataSize    - Size of data to multiplex in this entry, 0 if none. 
 *                        For an entry with more than 1 segmentable entry, this 
 *                        should be small enough to serve as ratio.
 * Output: None.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV * Rv3G324mCallH223GlueMuxtableAddEntryEv) (
    IN  HAPPCALL    h3G324mAppCall,
    IN  RvUint32    audioSize,
    IN  RvUint32    video1Size,
    IN  RvUint32    video2Size,
    IN  RvUint32    dataSize);

/* Rv3G324mH223GlueEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the H.223 Glue callbacks.
 * This structure is used to set the application callbacks in the function 
 * Rv3G324mCallH223GlueSetEvHandlers(). They are only applicable when the 
 * H.223 Split add-on is used.
 */
typedef struct
{
    Rv3G324mCallH223GlueSendControlEv           pfnSendControlEv;
    Rv3G324mCallH223GlueDemuxSetMuxtableEntry   pfnDemuxSetMuxtableEntryEv;
    Rv3G324mCallH223GlueChannelConstruct        pfnChannelConstructEv;
    Rv3G324mCallH223GlueChannelDestruct         pfnChannelDestructEv;
    Rv3G324mCallH223GlueMuxtableAddEntryEv      pfnMuxtableAddEntryEv;
    Rv3G324mCallH223GlueGenerateMuxtableEv      pfnGenerateMuxtableEv;
    Rv3G324mCallH223GlueClearMuxtableEv         pfnClearMuxtableEv;
} Rv3G324mH223GlueEvHandlers;



/*-----------------------------------------------------------------------*/
/*                           FUNCTION HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * Rv3G324mCallH223GlueSetEvHandlers
 * ----------------------------------------------------------------------------
 * General: Sets the callbacks for the H.223 Glue indications when H.223 is 
 * split between processes.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324m          - Stack instance to use.
 *         glueEvent        - Callback functions to set.
 *         size             - Set this parameter to sizeof(Rv3G324mH223GlueEvHandlers).
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallH223GlueSetEvHandlers(
    IN  HAPP                        h3G324m,
    IN  Rv3G324mH223GlueEvHandlers  *glueEvent,
    IN  RvSize_t                    size);


/******************************************************************************
 * Rv3G324mCallH223GlueMuxLevelIndication
 * ----------------------------------------------------------------------------
 * General: This function should be called when Rv3G324mH223CallMuxLevelIndicationEv() 
 * is received in the H.223 application (through the use of opcode 
 * Rv3G324mH223SerializeOpcodeCallMuxLevelIndication).
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to use.
 *         muxLevel         - Mux level for which to indicate synchronization.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallH223GlueMuxLevelIndication(
    IN  HCALL                       h3G324mCall,
    IN  Rv3G324mCallMuxLevel        muxLevel);


/******************************************************************************
 * Rv3G324mCallH223GlueIsClear
 * ----------------------------------------------------------------------------
 * General: This function should be called when Rv3G324mH223CallIsClearEv() 
 * is received in the H.223 application (through the use of opcode 
 * Rv3G324mH223SerializeOpcodeCallIsClear).
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to use.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallH223GlueIsClear(
    IN  HCALL           h3G324mCall);


/******************************************************************************
 * Rv3G324mCallH223GlueReceiveControl
 * ----------------------------------------------------------------------------
 * General: This function should be called when Rv3G324mH223CallReceiveControlEv() 
 * is received in the H.223 application (through the use of opcode 
 * Rv3G324mH223SerializeOpcodeCallReceiveControl).
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to use.
 *         pBuffer          - Buffer holding the control messages.
 *         bufferSize       - Size of the buffer.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallH223GlueReceiveControl(
    IN  HCALL           h3G324mCall,
    IN  RvUint8         *pBuffer,
    IN  RvSize_t        bufferSize);


/******************************************************************************
 * Rv3G324mCallH223GlueMuxtableEntries
 * ----------------------------------------------------------------------------
 * General: This function should be called when muxtable entries are received 
 * from the split side.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to use.
 *         muxEntriesSize   - Size of the muxtable.
 *         atomArray        - Table atoms for each muxtable entry.
 *         arraySize        - The size of each table atom.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallH223GlueMuxtableEntries(
    IN  HCALL           h3G324mCall,
    IN  RvUint32        muxEntriesSize,
    IN  void            *atomArray,
    IN  RvUint32        *arraySize);



#endif /* (RV_H223_USE_SPLIT == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif /* _RV_3G324M_CALL_H223_GLUE_H_ */
