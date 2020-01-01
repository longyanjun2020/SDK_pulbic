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

#ifndef _RV_H223_DEMUX_IFC_H
#define _RV_H223_DEMUX_IFC_H


#include "rvh223defs.h"
#include "rvwatchdog.h"
#include "rvlog.h"
#include "rvtimer.h"
#include "rvh223rxalifc.h"
#include "rvh223ifc.h"





#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

typedef struct{
    RvUint16 lcn;
    RvBool segmentable;
    RvBool framed;
    void  *getBufContext;
    void  *dataIndicationContext;
    RvH223GetBufEv DemuxGetBufEv;
    RvH223MuxDataIndicationEv DemuxMuxDataIndicationEv;
	RvBool	bModeIsACP;
}TH223DemuxLCDescCfg;

/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223DemuxInit
 * ----------------------------------------------------------------------------
 * General: Initializes the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper objects' construction
 *                                             fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  numOfInstances               - Number of instances.
 *         numOfAlSduSaved              - Number of saved SDUs for AL3 retransmissions
 *         numOfLCDescs                 - Number of LC per instance.
 *         eventCfg                     - Demux callbacks for the construction of the demux instance. 
 *         ACPMaxVideoBuffers        - max number of buffers for buffering video AL-SDUs
 *                                        during ACP call setup.
 *         hLog                         - Handle to the log source.
 *         hLogErr                      - Handle to the errors log source.
 *         hLogMgr                      - Handle to the log manager.
 *         hWatchdog                    - Handle to the resources watch dog.
 * Output: pDemuxModule                 - Pointer to the demuxer module handle.
 *****************************************************************************/
RvStatus RvH223DemuxInit(
    IN  RvUint32                    numOfInstances,
    IN  RvUint32                    numOfAlSduSaved,
    IN  RvUint32                    numOfLCDescs,
    IN  TH223InitCfgEvents          *eventCfg,
    IN  RvUint8                     ACPMaxVideoBuffers,
    IN  RvLogSource                 hLog,
    IN  RvLogSource                 hLogErr,
    IN  RvLogMgr                    *hLogMgr,
    IN  RvWatchdog                  *hWatchdog,
    OUT HDEMUXMODULE                *pDemuxModule);

/******************************************************************************
 * RvH223DemuxEnd
 * ----------------------------------------------------------------------------
 * General: Terminates the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper objects' destruction
 *                                             fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input: hDemuxModule - handle to the Demux module.
 *****************************************************************************/
RvStatus RvH223DemuxEnd (IN   HDEMUXMODULE hDemuxModule);

/******************************************************************************
 * RvH223DemuxConstruct
 * ----------------------------------------------------------------------------
 * General: Creates an instance of the class and obtains a handle to it
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_NULLPTR - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemuxModule                - Handle of the demux module.
 *          muxLevelIndicationContext   - Context given to MuxLevelEv.
 *          synchLossBytes              - Number of bytes until out-of-synch
 *                                        is declared.
 *          pHnd                        - Pointer to be filled with
 *                                        instance's handle.
 * Output : None
 *****************************************************************************/
RvStatus RvH223DemuxConstruct(
    IN   HDEMUXMODULE               hDemuxModule,
    IN   void                       *muxLevelIndicationContext,
    IN   RvUint32                   synchLossBytes,
    IN   HDEMUX                     pHnd);

/******************************************************************************
 * RvH223DemuxDestruct
 * ----------------------------------------------------------------------------
 * General: Deletes an instance of the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hdemux    - Instance's handle.
 *****************************************************************************/
RvStatus RvH223DemuxDestruct (IN  HDEMUX hdemux);

/******************************************************************************
 * RvH223DemuxAddLCPlace
 * ----------------------------------------------------------------------------
 * General: Find and allocate a place for an LC to be muxed by a specified
 *          demux instance.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more LCDescs to
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hdemux      - Handle to a demux instance.
 *          lcn         - Logical channel number to use.
 * Output : phnd        - Pointer to be filled with LCDesc handle.
 *          sizeofDesc  - Calculated size of the descriptor. Required when
 *                        memory locality feature is used.
 *****************************************************************************/
RvStatus RvH223DemuxAddLCPlace(
    IN   HDEMUX     hdemux,
    IN   RvUint16   lcn,
    OUT  HMUXLCDESC *phnd,
    OUT  RvSize_t   *sizeofDesc);

/******************************************************************************
 * RvH223DemuxAddLC
 * ----------------------------------------------------------------------------
 * General: Adds a LC to receive data from the specified demux instance.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more LCDescs to
 *                                         allocate.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux      - Handle to a demux instance.
 *          pCfg        - Configuration parameters of the LC, which is being added.
 *          dataType    - data type of channel.
 * Output : pHnd        - Pointer to be filled with LCDesc handle.
 *****************************************************************************/
RvStatus RvH223DemuxAddLC (IN   HDEMUX hDemux,
                           IN   TH223DemuxLCDescCfg *pCfg,
                           IN   RvH223LCDataType    dataType,
                           OUT  HMUXLCDESC *pHnd);

/******************************************************************************
 * RvH223DemuxRemoveLC
 * ----------------------------------------------------------------------------
 * General: Removes the specified LC from the specified demux's list.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if any handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux    - Handle to a demux instance.
 *          hLcdesc   - Handle to a LCDesc instance.
 *****************************************************************************/
RvStatus RvH223DemuxRemoveLC (IN  HDEMUX hDemux,
                              IN  HMUXLCDESC hLcdesc);

/******************************************************************************
 * RvH223DemuxRemoveMonaMPCLC
 * ----------------------------------------------------------------------------
 * General: Removes the specified LC from the demux's phantomChannels list.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if any handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux    - Handle to a demux instance.
 *          hLcdesc   - Handle to a LCDesc instance.
 *****************************************************************************/
RvStatus RvH223DemuxRemoveMonaMPCLC (IN  HDEMUX hDemux,
                                IN  HMUXLCDESC hLcdesc);

/******************************************************************************
 * RvH223DemuxSetMonaMPCRTx
 * ----------------------------------------------------------------------------
 * General: For MPC - Set supported MPC types in the demux instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux          - Handle to a demux instance.
 *          mpcTypes        - bitMask of mpc types.
 *          isOutgoing      - if RV_TRUE - transmitting MPC types, else - receiving
 *                            MPC types.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxSetMonaMPCRTx(
     IN HDEMUX      hDemux,
     IN RvUint16    mpcTypes,
     IN RvBool      isOutgoing);
 
/******************************************************************************
 * RvH223DemuxRemoveMonaMPCChannel
 * ----------------------------------------------------------------------------
 * General: For MPC - Remove the MPC channel with the specified type.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux          - Handle to a demux instance.
 *          mpcChannelType   - MPC channel to remove.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxRemoveMonaMPCChannel(
        IN HDEMUX hDemux,
        IN RvH223MonaMPCChannelType mpcChannelType);

 /******************************************************************************
 * RvH223DemuxIsMPCChannelActive
 * ----------------------------------------------------------------------------
 * General: Checks if an MPC channel is active in the demux
 *
 * Return Value: RV_TRUE if MPC channel is active, RV_FALSE if not.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux          - Handle to a demux instance.
 *          mpcChannelType  - MPC channel type.
 * Output:  None.
 *****************************************************************************/
 RvBool RvH223DemuxIsMPCChannelActive(
        IN HDEMUX                   hDemux,
        IN RvH223MonaMPCChannelType mpcChannelType); 

/******************************************************************************
 * RvH223DemuxSetContextLC
 * ----------------------------------------------------------------------------
 * General: Set the data indication context for a specific LC in the demux's
 *          list. We do that to remove the context when we want to shut down
 *          incoming channels.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if any handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux                  - Handle to a demux instance.
 *          hLcdesc                 - Handle to a LCDesc instance.
 *          dataIndicationContext   - Context to set
 *          getBufContext           - Context to set
 *****************************************************************************/
RvStatus RvH223DemuxSetContextLC (IN  HDEMUX hDemux,
                                  IN  HMUXLCDESC hLcdesc,
                                  IN  void *dataIndicationContext,
                                  IN  void *getBufContext);

/******************************************************************************
 * RvH223DemuxSetMuxtableEntry
 * ----------------------------------------------------------------------------
 * General: Sets the multiplex table entry to the demux.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_OUTOFRANGE - if the the multiplex entry is too big.
 *               RV_ERROR_NULLPTR - if the handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux    - Handle to a muxer instance.
 *          muxEntry  - the multiplex entry number.
 *          atomArray - Array of atoms to be parsed into muxtable entry.
 *          arraySize - atomArray size
 * Output:
 *****************************************************************************/
RvStatus RvH223DemuxSetMuxtableEntry (IN  HDEMUX      hDemux,
                                      IN  RvUint32    muxEntry,
                                      IN  TMuxTblAtom *atomArray,
                                      IN  RvUint32    arraySize);

/******************************************************************************
 * RvH223DemuxSetLevelCfg
 * ----------------------------------------------------------------------------
 * General: Changes demux multiplex level.
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hdemux      - Handle to a demux instance.
 *          pcfg        - New configuration.
 *          inSession   - Determines whether the dynamic change of option is
 *                        taking place.
 *****************************************************************************/
RvStatus RvH223DemuxSetLevelCfg (IN  HDEMUX hdemux,
                                 IN  TMuxLevelCfg *pcfg,
                                 IN  RvBool inSession);

 /******************************************************************************
 * RvH223DemuxSetACPAudioEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets ACPAudioEntry in the demux instance
 *                       and creates the audio UCF entry in the demux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to the demux instance.
 *          value   - The value of the demux table entry number.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxSetACPAudioEntry(
        IN  HDEMUX      hDemux, 
        IN  RvUint16    value);

 /******************************************************************************
 * RvH223DemuxGetACPAudioEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Gets ACPAudioEntry from the demux instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux      - Handle to the demux instance.      
 * Output:  value      - The value of the audio entry for ACP in the demux.
 *****************************************************************************/
 RvStatus RvH223DemuxGetACPAudioEntry(
        IN  HDEMUX      hDemux, 
        OUT RvUint32   *value);

 /******************************************************************************
 * RvH223DemuxSetACPVideoEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets ACPVideoEntry in the demux instance.
 *                       and creates the video UCF entry in the demux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to the demux instance.
 *          value   - The value to set.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxSetACPVideoEntry(
        IN  HDEMUX      hDemux, 
        IN  RvUint16    value);

 /******************************************************************************
 * RvH223DemuxGetACPVideoEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Gets ACPVideoEntry from the demux instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux      - Handle to the demux instance.      
 * Output:  value      - The value of the video entry for ACP in the demux.
 *****************************************************************************/
 RvStatus RvH223DemuxGetACPVideoEntry(
        IN  HDEMUX      hDemux, 
        OUT RvUint32   *value);

#if 0
/******************************************************************************
 * RvH223DemuxACPSetDefaultDemuxTbl
 * ----------------------------------------------------------------------------
 * General: For ACP - adds audio and video channel entries to the demux and
 *                    adds the ACP entries for audio and video to the demux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxACPSetDefaultDemuxTbl(IN  HDEMUX   hDemux);
#endif
 /******************************************************************************
 * RvH223DemuxACPClearDefaultDemuxTbl
 * ----------------------------------------------------------------------------
 * General: For ACP - cleans the entries for audio and video in the default demux
 *                    table and cleans the ACP entries for audio and video.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxACPClearDefaultDemuxTbl(IN  HDEMUX   hDemux);

 /******************************************************************************
 * RvH223DemuxResetIgnoreData
 * ----------------------------------------------------------------------------
 * General: For ACP - Resets the noMediaBufferingTimeStamp and the 
 *                       bCheckIgnoreData flag in the demux object, 
 *                       to avoid the check if a received data should be ignored.
 *                       This function is called when an OLC is received for a
 *                       ACP video channel that was previously rejected or when 
 *                       at least 2 seconds had passed since the rejection.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 * Output:  RV_OK on success RV_ERROR_XXX on failure.
 *****************************************************************************/
 RvStatus RvH223DemuxResetIgnoreData(IN HDEMUX   hDemux);

 /******************************************************************************
 * RvH223DemuxACPClearVideoLC
 * ----------------------------------------------------------------------------
 * General: For ACP -    Resets the the descriptor of the video LC, clears all
 *                          the buffers and sets the noMediaBufferingTimeStamp, and
 *                          the LC descriptor is reconfigured.
 *                          Important - the LC descriptor is not removed from the 
 *                          demux channel list.
 *
 * Return Value: RV_OK on success RV_ERROR_XXX on failure..
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 * Output:  None
 *****************************************************************************/
RvStatus RvH223DemuxACPClearVideoLC(IN HDEMUX   hDemux);

/******************************************************************************
 * RvH223DemuxACPClearVideoLC
 * ----------------------------------------------------------------------------
 * General: For ACP -    Resets the the descriptor of the audio LC.
 *                          Important - the LC descriptor is not removed from the 
 *                          the demux channel list, only 'reconfigured'.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 * Output:  None..
 *****************************************************************************/
RvStatus RvH223DemuxACPClearAudioLC(IN HDEMUX   hDemux);

/******************************************************************************
 * RvH223DemuxACPIgnoreData
 * ----------------------------------------------------------------------------
 * General: For ACP - Checks if data should be ignored (after a rejection) 
 *                       by checking the current time against the time stamp 
 *                       of the video buffers. This is done only if the 
 *                       bCheckIgnoreData flag in the demux is on.
 *
 * Return Value: RV_TRUE  - data should be ignored..
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 *          bCheckNumBuffers    - Indication to check number of buffers.
 * Output:  None.
 *****************************************************************************/
RvBool RvH223DemuxACPIgnoreData(IN HDEMUX   hDemux, 
                                IN RvBool   bCheckNumBuffers);

/******************************************************************************
 * RvH223DemuxACPGetMaxVideoBuffers
 * ----------------------------------------------------------------------------
 * General: For ACP -    Returns the maximum video buffers available for ACP video
 *                          buffering.
 *
 * Return Value: RV_OK  - on success RV_ERROR_UNKNOWN else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux      - Handle to a demux instance.
 * Output:  maxBuffers  - The maximum video buffers allowed.
 *****************************************************************************/
RvStatus RvH223DemuxACPGetMaxVideoBuffers(IN  HDEMUX   hDemux,
                                             OUT RvUint8  *maxBuffers);

/******************************************************************************
 * RvH223DemuxACPReleaseChannelBuffer
 * ----------------------------------------------------------------------------
 * General: For ACP - Releases buffers that should be ignored.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_XXXX  - if failed.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux      - Handle to a demux instance.
 *          buffer      - The buffer to release.
 *          size        - The buffer size.
 * Output:  None.
 *****************************************************************************/
RvStatus RvH223DemuxACPReleaseChannelBuffer(
    IN HDEMUX   hDemux,
    IN RvUint8  *buffer,
    IN  RvUint32 size);

/******************************************************************************
 * RvH223DemuxAnnounceData
 * ----------------------------------------------------------------------------
 * General: Parses the incoming bitstream.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_NULLPTR - if the handle is invalid.
 *               RV_ERROR_NOTSUPPORTED - The demux level is unsupported.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux  - Handle to a demux instance.
 *          pBuffer - Data buffer.
 *          size    - Size of data.
 *****************************************************************************/
RvStatus RvH223DemuxAnnounceData (IN  HDEMUX   hDemux,
                                  IN  RvUint8  *pBuffer,
                                  IN  RvUint32 size);

/******************************************************************************
 * RvH223DemuxAnnounceFrame
 * ----------------------------------------------------------------------------
 * General: Parses an incoming frame.
 *          This function should be used when the stuffing and framing is done
 *          by the hardware.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_NULLPTR - if the handle is invalid.
 *               RV_ERROR_NOTSUPPORTED - The demux level is unsupported.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hDemux                       - Handle to a demux instance.
 *         pBuffer                      - Data buffer holding a full frame.
 *         size                         - Size of data.
 *         bSegmentableChannelClosure   - RV_TRUE if the received MUX-PDU frame
 *                                        closes a segmentable channel.
 *                                        This parameter has to be set to RV_FALSE
 *                                        for mux-level 0 and mux-level 1 at
 *                                        all times since this information
 *                                        resides within the header of the
 *                                        MUX-PDU itself.
 *****************************************************************************/
RvStatus RvH223DemuxAnnounceFrame(
    IN  HDEMUX      hDemux,
    IN  RvUint8     *pBuffer,
    IN  RvUint32    size,
    IN  RvBool      bSegmentableChannelClosure);


#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)
/******************************************************************************
 * RvH223DemuxSave2Buffer
 * ----------------------------------------------------------------------------
 * General: save the demux instance into a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : HDEMUX       - hdemux       - Handle to the demux instance.
 *          buffLen      - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : pBuffer      - buffer to save to.
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223DemuxSave2Buffer(IN      HDEMUX       hdemux,
                            OUT     RvUint8     *pBuffer,
                            IN      RvSize_t    buffLen,
                            INOUT   RvSize_t    *lenDone,
                            INOUT   RvStatus    *pStatus);

/******************************************************************************
 * RvH223DemuxGetFromBuffer
 * ----------------------------------------------------------------------------
 * General: restores the demux instance from a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hdemux       - Handle to the demux instance.
 *          pBuffer      - buffer to restore data from.
 *          buffLen      - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : hdemux       - Handle to hdemux instance updated with saved
 *                         data from buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223DemuxGetFromBuffer(INOUT  HDEMUX      hdemux,
                              IN     RvUint8     *pBuffer,
                              IN     RvSize_t    buffLen,
                              INOUT  RvSize_t    *lenDone,
                              INOUT  RvStatus    *pStatus);
#endif /* (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES) */


/******************************************************************************
 * RvH223DemuxUpdateMuxerTablePLC
 * ----------------------------------------------------------------------------
 * General: Updates the plc fields in the atom fields of the muxerTable
 *          entry in the demux.  .
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hdemux       - Handle to the demux instance.
 * Output :None
 *****************************************************************************/
void RvH223DemuxUpdateMuxerTablePLC(INOUT  HDEMUX      hdemux);

/******************************************************************************
 * Synchronize
 * ----------------------------------------------------------------------------
 * General: Finds the next opening/closing uoption.
 *          This function is used internally by the demux object or externally
 *          as an API by the silent monitor add-on.
 *
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer.
 ******************************************************************************/
RvUint32 Synchronize(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * ParseFlag
 * ----------------------------------------------------------------------------
 * General: Parse only the closing uoption.
 *          This function is used internally by the demux object or externally
 *          as an API by the silent monitor add-on.
 *
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer.
 * Output : none
 *****************************************************************************/
RvUint32 ParseFlag(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * ParseData
 * ----------------------------------------------------------------------------
 * General: Parse only the information field of the MUX-PDU.
 *          This function is used internally by the demux object or externally
 *          as an API by the silent monitor add-on.
 *
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer.
 * Output : none
 *****************************************************************************/
RvUint32 ParseData(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * ParseHeader
 * ----------------------------------------------------------------------------
 * General: Parse only the header of the MUX-PDU. if we managed to find a header,
 *          we validate the header according to the header type.
 *          This function is used internally by the demux object or externally
 *          as an API by the silent monitor add-on.
 *
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer. Should be more then
 *                   4 (including optional header).
 * Output : none
 *****************************************************************************/
RvUint32 ParseHeader(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * DetermineMuxLevel
 * ----------------------------------------------------------------------------
 * General: Synchronizes on stuffing sequence of either muxLevel.
 *          This function is used internally by the demux object or externally
 *          as an API by the silent monitor add-on.
 *
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - Size of data chunk.
 ******************************************************************************/
RvUint32 DetermineMuxLevel(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * GetBufMaxSize
 * ----------------------------------------------------------------------------
 * General: Get buffer max size
 *
 * Return Value: Buffer max size.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  :  pdesc  - The logical channel descriptor.
 ******************************************************************************/
RvUint32 GetBufMaxSize(IN  HMUXLCDESC hLcdesc);

/******************************************************************************
 * RvH223ACPDemuxReplayVideoBuffers
 * ----------------------------------------------------------------------------
 * General: Replays saved video buffers to the application.         
 *
 * Return Value: RV_OK  - if successful.
 *        .      RV_ERROR_NULLPTR - if demux instance is NULL.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if lock/unlock of the demux fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - The demux instance.
 ******************************************************************************/
RvStatus RvH223ACPDemuxReplayVideoBuffers(IN HDEMUX hDemux);

/******************************************************************************
 * RvH223ACPDemuxGetCurrentBuffer2Release
 * ----------------------------------------------------------------------------
 * General: Sets buffer to release in pBuffer2Release if replaying media buffers 
 *          is currently on.
 *          Important - This function is called from the dataIndicationEv 
 *                      and the demux instance is already locked - DO NOT ADD
 *                      LOCK.
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux          - The demux instance.
 * Output : pBuffer2Release -   The buffer to release.
 ******************************************************************************/
void RvH223ACPDemuxGetCurrentBuffer2Release(IN HDEMUX hDemux,
                                               OUT RvUint8 **pBuffer2Release);

#if (RV_3G324M_USE_MONA == RV_YES)
/******************************************************************************
 * ParseMONAMsg
 * ----------------------------------------------------------------------------
 * General: Parse the MONA preference message. 
 * Return Value: Number of bytes processed from the incoming buffer.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hDemux - Handle to a demux instance.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer. 
 * Output : none
 *****************************************************************************/
RvUint32 ParseMONAMsg(
    IN HDEMUX               hDemux,
    IN RvUint8              *pbuf,
    IN RvUint32             size);

/******************************************************************************
 * RvH223DemuxSetMONA
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets bUseMONA in the demux instance
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux              - The demux instance.
 *          value               - The value to set.
 * Output:  None.
 *****************************************************************************/
RvStatus RvH223DemuxSetMONA(
     IN  HDEMUX          hDemux,
     IN  RvBool          value);
/******************************************************************************
 * RvH223DemuxSetMonaMPCCall
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets bUseMONA in the demux instance, creates mpc channels 
 *                   and the default MPC mux table for all supported MPC media codecs.   
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hDemux              - The demux instance.
 *          palCfg              - an array of alCfg's for the demux phantom channels.
 *          rxSupportedChannels - Supported receiving MPC types.  
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223DemuxSetMonaMPCCall(
     IN  HDEMUX          hDemux,
     IN  HH223           hH223,
     IN  TH223RxALCfg   *palCfg, 
     IN  RvUint16        rxSupportedChannels);
#endif /* (RV_3G324M_USE_MONA == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_MUXER_IFC_H */
