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

#ifndef _RV_H223_MUXER_IFC_H
#define _RV_H223_MUXER_IFC_H

#include "rvh223defs.h"
#include "rvwatchdog.h"
#include "rvh223txalifc.h"
#include "rvh223ifc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

/* Informs the user that the data buffer is not in use any more.*/
typedef void (*RvH223ReleaseMuxSduEv) (IN void *,       /* Context.*/
                                       IN RvInt32,      /*Subcontext*/
                                       IN TRvMuxSdu *,  /* Pointer to a MUX-SDU.*/
                                       IN RvBool        /* RV_TRUE if the buffer got processed.*/
                                      );

typedef struct{
    EMuxLevel                     level; /* Mux level to use */
    void*                         callContext; /* The call contect */
}TH223MuxerConstructCfg;

typedef struct{
    RvUint16                lcn;                /* Logical channel number.*/
    RvBool                  segmentable;        /* Indicates if LC is segmentable, e.g.
                                                   if its MUX_SDU could be divided and
                                                   sent in multiple MUX-PDU-s.*/
    RvBool                  framed;             /* Indicates if LC is framed, e.g if
                                                   the PM flag should be set when its
                                                   MUX-SDU ends.*/
    RvUint8                 overhead;           /* Bytes of overhead the AL has on the data
                                                   in this channel */
    RvH223LCDataType        dataType;           /* See rvh223defs.h.*/
    RvH223ReleaseMuxSduEv   ReleaseMuxSduEv;    /* Callback for input MuxSdu release.*/
    RvH223IsClearEv         MuxerLCIsClearEv;   /* Ready for LC termination callback.*/
    void                    *releaseContext;    /* Context for ReleaseMuxSduEv.*/
    void                    *clearContext;      /* Context for MuxerLCIsClearEv.*/
    RvBool                  bIsMPCLC;            /*RV_TRUE if MPC LC*/
}TH223MuxerLCDescCfg;



/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223MuxerInit
 * ----------------------------------------------------------------------------
 * General: Initializes the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper objects' construction
 *                                             fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  numOfInstancesMax    - Number of concurrent conversations.
 *         numOfLCPerMuxer      - Number of LC per Muxer.
 *         numOfMuxSduPerMuxLC  - Depth of MuxSdu queue per LC descriptor.
 *         eventCfg             - Muxer callbacks for the construction of the muxer instance. 
 *                                messages.
 *         hLog                 - Handle to the log source.
 *         hLogErr              - Handle to the error log source.
 *         hLogMgr              - Handle to the log manager.
 *         hControlRpool        - RPOOL instance to use when needed for control
 *                                messages.
 *         hMediaRpool          - RPOOL instance to use for ALxM media frames.
 *         hWatchdog            - Handle to the resources watch dog.
 * Output: hMuxerModule         - handle to the muxer module.
 *****************************************************************************/
RvStatus RvH223MuxerInit (IN  RvUint16                      numOfInstancesMax,
                          IN  RvUint16                      numOfLCPerMuxer,
                          IN  RvUint16                      numOfMuxSduPerMuxLC,
                          IN  TH223InitCfgEvents            *eventCfg,
                          IN  RvLogSource                   hLog,
                          IN  RvLogSource                   hLogErr,
                          IN  RvLogMgr                      *hLogMgr,
                          IN  HRPOOL                        hControlRpool,
                          IN  HRPOOL                        hMediaRpool,
                          IN  RvWatchdog                    *hWatchdog,
                          OUT HMUXERMODULE                  *hMuxerModule);

/******************************************************************************
 * RvH223MuxerGetLCDescSizeOf
 * ----------------------------------------------------------------------------
 * General: Find the size of a multiplexer logical channel descriptor.
 *
 * Return Value: Size of the data required for allocation.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input: numOfMuxSduPerMuxLC - Number of MUX-SDUs per logical channel.
 *****************************************************************************/
RvSize_t RvH223MuxerGetLCDescSizeOf(
    IN RvUint16 numOfMuxSduPerMuxLC);

/******************************************************************************
 * RvH223MuxerEnd
 * ----------------------------------------------------------------------------
 * General: Terminates the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper objects' destruction
 *                                             fails.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input: hMuxerModule - handle to the muxer module.
 *****************************************************************************/
RvStatus RvH223MuxerEnd (HMUXERMODULE hMuxerModule);

/******************************************************************************
 * RvH223MuxerConstruct
 * ----------------------------------------------------------------------------
 * General: Initializes an instance of the class in a given memory region.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hMuxerModule    - Handle to the muxer module.
 *          pcfg            - Configuration parameters of Muxer.
 *          phnd            - Pointer to memory region to use.
 * Output : None
 *****************************************************************************/
RvStatus RvH223MuxerConstruct(
    IN   HMUXERMODULE           hMuxerModule,
    IN   TH223MuxerConstructCfg *pcfg,
    IN   HMUXER                 phnd);

/******************************************************************************
 * RvH223MuxerDestruct
 * ----------------------------------------------------------------------------
 * General: Deletes an instance of the class.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Instance's handle.
 *****************************************************************************/
RvStatus RvH223MuxerDestruct (IN  HMUXER hmuxer);

/******************************************************************************
 * RvH223MuxerSetOutputBuf
 * ----------------------------------------------------------------------------
 * General: Set the output buffer used by this muxer instance.
 *          This function must be called after RvH223MuxerConstruct() and
 *          before any actual work is done with this muxer.
 *          It is only useful to set the buffer if the muxer is to be used
 *          in an environment where the stuffing mode is done by the software
 *          and not through hardware (meaning that RvH223MuxerGetMuxedStream()
 *          is to be used.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more muxers to
 *                                         allocate.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer          - Handle to a muxer instance.
 *          pOutputBuf      - Output buffer to use for stuffing
 *          outputBufSize   - Size of the output buffer
 *****************************************************************************/
RvStatus RvH223MuxerSetOutputBuf (IN   HMUXER hmuxer,
                                  IN   RvUint8 *pOutputBuf,
                                  IN   RvUint32 outputBufSize);

/******************************************************************************
 * RvH223MuxerAddLCPlace
 * ----------------------------------------------------------------------------
 * General: Find and allocate a plalce for an LC to be muxed by a specified
 *          muxer instance.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more LCDescs to
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer      - Handle to a muxer instance.
 *          lcn         - Logical channel number to use.
 * Output : phnd        - Pointer to be filled with LCDesc handle.
 *          sizeofDesc  - Calculated size of the descriptor. Required when
 *                        memory locality feature is used.
 *****************************************************************************/
RvStatus RvH223MuxerAddLCPlace(
    IN   HMUXER     hmuxer,
    IN   RvUint16   lcn,
    OUT  HMUXLCDESC *phnd,
    OUT  RvSize_t   *sizeofDesc);

/******************************************************************************
 * RvH223MuxerAddLC
 * ----------------------------------------------------------------------------
 * General: Adds a LC to be muxed by a specified muxer instance.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_OUTOFRESOURCES - if there are no more LCDescs to
 *                                         allocate.
 *               RV_ERROR_BADPARAM - if a muxer handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer - Handle to a muxer instance.
 *          pcfg   - Configuration parameters of the LC, which is being added.
 * Output : phnd   - Pointer to be filled with LCDesc handle.
 *****************************************************************************/
RvStatus RvH223MuxerAddLC (IN   HMUXER hmuxer,
                           IN   TH223MuxerLCDescCfg *pcfg,
                           OUT  HMUXLCDESC *phnd);

/******************************************************************************
 * RvH223MuxerRemoveLC
 * ----------------------------------------------------------------------------
 * General: Removes the specified LC from the specified muxer's muxing list.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 *               RV_ERROR_BADPARAM - if any handle is invalid.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          hlcdesc   - Handle to a LCDesc instance.
 *****************************************************************************/
RvStatus RvH223MuxerRemoveLC (IN  HMUXER hmuxer,
                              IN  HMUXLCDESC hlcdesc);

/******************************************************************************
 * RvH223MuxerGetLC
 * ----------------------------------------------------------------------------
 * General: Get an LC that was already added to the muxer.
 *
 * Return Value: RV_OK  - if successful.
 *               RV_ERROR_NOT_FOUND - if no such LC was found.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer      - Handle to a muxer instance.
 *          dataType    - The data type of the channel.
 * Output : context     - The clear context passed to the specified channel.
 *****************************************************************************/
RvStatus RvH223MuxerGetLC(
    IN   HMUXER             hmuxer,
    IN   RvH223LCDataType   dataType,
    OUT  void               **context);

/******************************************************************************
 * RvH223MuxerHasMuxTable
 * ----------------------------------------------------------------------------
 * General: Checks if there is an updated muxtable currently set.
 *          The muxtable is automatically invalidated when channels are added
 *          to the muxer.
 *
 * Return Value: RV_TRUE if the muxtable is updated properly.
 *               RV_FALSE if the muxtable requires an update.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer              - Handle to a muxer instance
 *****************************************************************************/
RvBool RvH223MuxerHasMuxTable(
    IN  HMUXER hmuxer);

/******************************************************************************
 * RvH223MuxerClearMuxtable
 * ----------------------------------------------------------------------------
 * General: Clear up the muxtable.
 *
 * Return Value: RV_OK - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance
 *****************************************************************************/
RvStatus RvH223MuxerClearMuxtable(
    IN HMUXER       hmuxer);

/******************************************************************************
 * RvH223MuxerMuxtableAddEntry
 * ----------------------------------------------------------------------------
 * General: Add an entry to the muxtable used.
 *
 * Return Value: RV_OK - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer      - Handle to a muxer instance.
 *          ACPEntryNumber   - The mux table entry index if using ACP.
 *                                 ignored if 0 or bUseACP in the muxer is not RV_TRUE.
 *          audioSize   - Size of audio frame in bytes in this entry. This size
 *                        should not include the adaptation layer overhead (this
 *                        may include header and CRC information and is
 *                        automatically added by this function).
 *          video1Size  - Size of video1 to multiplex in this entry, 0 if none.
 *                        For an entry with more than 1 segmentable entry, this
 *                        should be small enough to serve as ratio.
 *          video2Size  - Size of video2 to multiplex in this entry, 0 if none.
 *                        For an entry with more than 1 segmentable entry, this
 *                        should be small enough to serve as ratio.
 *          dataSize    - Size of data to multiplex in this entry, 0 if none.
 *                        For an entry with more than 1 segmentable entry, this
 *                        should be small enough to serve as ratio.
 *****************************************************************************/
RvStatus RvH223MuxerMuxtableAddEntry(
    IN  HMUXER      hmuxer,
    IN  RvUint16    ACPEntryNumber,
    IN  RvUint32    audioSize,
    IN  RvUint32    video1Size,
    IN  RvUint32    video2Size,
    IN  RvUint32    dataSize);

/******************************************************************************
 * RvH223MuxerGenerateMuxtable
 * ----------------------------------------------------------------------------
 * General: Generates muxtabel according to the added LC-s.
 *
 * Return Value: RV_OK - if successful.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer              - Handle to a muxer instance
 *          audioType           - According to AMR codec (see RvH223defs.h).
 *          videoBitrate        - In bits.
 *          dataBitrate         - In bits.
 *          enhancedCapability  - Muxtable complexity level, according to H223.
 *****************************************************************************/
RvStatus RvH223MuxerGenerateMuxtable (IN  HMUXER hmuxer,
                                      IN  EAudioFrameType audioType,
                                      IN  RvUint32 videoBitrate,
                                      IN  RvUint32 dataBitrate,
                                      IN  RvBool enhancedCapability);

/******************************************************************************
 * RvH223MuxerGetMuxtableEntry
 * ----------------------------------------------------------------------------
 * General: Parses szInit string into muxtable entry. It doesn't return entry0!
 *
 * Return Value: RV_OK                  - if successful.
 *               RV_ERROR_BADPARAM      - if the handle is invalid or the
 *                                        specified muxtable entry doesn't exist.
 *               RV_ERROR_DESTRUCTED    - for an entry with a channel that got
 *                                        closed by now.
 *               RV_ERROR_UNINITIALIZED - when the table itself is not valid
 *                                        at all and should not be sent out.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to a muxer instance.
 *          entrynumber - Number of muxtable entry to get.
 * Output:  pentry  - Pointer to a buffer to be filled with muxtable entry.
 *          psize - Size of the buffer (number of atoms).
 *****************************************************************************/
RvStatus RvH223MuxerGetMuxtableEntry(
    IN    HMUXER        hmuxer,
    IN    RvUint32      entrynumber,
    OUT   TMuxTblAtom   *pentry,
    OUT   RvUint32      *psize);

/******************************************************************************
 * RvH223MuxerMuxDataRequest
 * ----------------------------------------------------------------------------
 * General: Adds MuxSdu to the specified LCDesc's queue.
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          hlcdesc   - Handle to a LCDesc instance.
 *          pmuxsdu   - Pointer to an input buffer descriptor.
 *****************************************************************************/
RvStatus RvH223MuxerMuxDataRequest (IN  HMUXER hmuxer,
                                    IN  HMUXLCDESC hlcdesc,
                                    IN  TRvMuxSdu *pmuxsdu);

/******************************************************************************
 * RvH223MuxerClearDescriptorData
 * ----------------------------------------------------------------------------
 * General: Clear a specific descriptor's data (MuxSdu's not sent yet).
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          hlcdesc   - Handle to a LCDesc instance.
 *****************************************************************************/
RvStatus RvH223MuxerClearDescriptorData(
    IN  HMUXER      hmuxer,
    IN  HMUXLCDESC  hlcdesc);


/******************************************************************************
 * RvH223MuxerSetLevelCfg
 * ----------------------------------------------------------------------------
 * General: Determines if muxer shall use optional header at multiplex level 2.
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          pcfg      - New configuration.
 *****************************************************************************/
RvStatus RvH223MuxerSetLevelCfg (IN  HMUXER        hmuxer,
                                 IN  TMuxLevelCfg *pcfg);

/******************************************************************************
 * RvH223MuxerGetLevelCfg
 * ----------------------------------------------------------------------------
 * General: Gets the current mux level of the muxer.
 * Return Value: mux level configuration.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *****************************************************************************/
TMuxLevelCfg *RvH223MuxerGetLevelCfg (IN  HMUXER        hmuxer);

/******************************************************************************
 * RvH223MuxerSetMaxMuxPduSize
 * ----------------------------------------------------------------------------
 * General: Sets the maximum MUX - PDU size.
 *
 * Return Value: RV_OK - if successful.
 *               RV_ERROR_HELPER_OBJ_FAILURE - if helper object malfunctions.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer          - Handle to a muxer instance.
 *          maxMuxPduSize   - The max MUX - PDU size.
 *****************************************************************************/
RvStatus RvH223MuxerSetMaxMuxPduSize (IN  HMUXER   hmuxer,
                                      IN  RvUint16 maxMuxPduSize);

/******************************************************************************
 * RvH223MuxerGetMuxPdu
 * ----------------------------------------------------------------------------
 * General: Finds the appropriate MuxTableEntry, creates MuxPdu and releases
 *          transmitted MuxSdus.
 *
 * Return Value: RV_OK  - if successful.
 *               error code - if helper objects fail.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          poutbuf   - Buffer to be filled with data.
 * Input/Output:  psize - Buffer size(input), Size of written data(output).
 *****************************************************************************/
RvStatus RvH223MuxerGetMuxPdu (IN   HMUXER hmuxer,
                               IN   RvUint8 *poutbuf,
                               INOUT  RvUint32 *psize);

/******************************************************************************
 * RvH223MuxerGetMuxedStream
 * ----------------------------------------------------------------------------
 * General: Fills the provided buffer with a specified amount of data. If there
 *          is no actual data, uses mux level dependent stuffing data.
 *
 * Return Value: RV_OK  - if successful.
 *               error code - if helper objects fail.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *          poutbuf   - Buffer to be filled with data.
 *          size      - Requested size.
 *          invertFlags - Indicates whether to send he regular or reversed stuff.
 *******************************************************************************/
RvStatus RvH223MuxerGetMuxedStream (IN  HMUXER hmuxer,
                                    IN  RvUint8 *poutbuf,
                                    IN  RvUint32 size,
                                    IN  RvBool invertFlags);
#if 0
/******************************************************************************
 * RvH223MuxerGetSizeOfStuff
 * ----------------------------------------------------------------------------
 * General: Fills the provided buffer with a specified amount of data. If there
 *          is no actual data, uses mux level dependent stuffing data.
 *
 * Return Value: Number of stuffing bytes.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer    - Handle to a muxer instance.
 *****************************************************************************/
RvUint32 RvH223MuxerGetSizeOfStuff (IN   HMUXER hmuxer);
#endif

/******************************************************************************
 * RvH223MuxerSetRetransmissionOnIdle
 * ----------------------------------------------------------------------------
 * General: sets the retransmission on idle flag.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer      - Handle to the muxer instance.
 *          value       - value to set (RV_TRUE/RV_FALSE).
 * Output : None.
 *****************************************************************************/
void RvH223MuxerSetRetransmissionOnIdle(IN    HMUXER      hmuxer,
                                        IN    RvBool      value);

/******************************************************************************
 * RvH223MuxerGetPendingMuxSdus
 * ----------------------------------------------------------------------------
 * General: Get the number of MUX_SDUs in use..
 *
 * Return Value: RV_OK on success or nagative value otherwise.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer          - Handle to the muxer instance.
 * Output : pendingMuxSdus  - The number of MUX_SDUs that were allocated and
 *                            not released.      
 *****************************************************************************/
RvStatus RvH223MuxerGetPendingMuxSdus(IN    HMUXER      hmuxer,
                                      OUT   RvUint32    *pendingMuxSdus);

#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)
/******************************************************************************
 * RvH223MuxerSave2Buffer
 * ----------------------------------------------------------------------------
 * General: save the muxer instance into a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer       - Handle to the muxer instance.
 *          buffLen      - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : pBuffer      - buffer to save to.
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223MuxerSave2Buffer(IN      HMUXER      hmuxer,
                            OUT     RvUint8     *pBuffer,
                            IN      RvSize_t    buffLen,
                            INOUT   RvSize_t    *lenDone,
                            INOUT   RvStatus    *pStatus);

/******************************************************************************
 * RvH223MuxerGetFromBuffer
 * ----------------------------------------------------------------------------
 * General: restores the muxer instance from a buffer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : hmuxer       - Handle to the muxer instance.
 *          hControl     - Handle of control instance.
 *          pBuffer      - buffer to restore data from.
 *          buffLen      - size of buffer
 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 * Output : hmuxer       - Handle to muxer instance updated with saved
 *                         data from buffer

 *          lenDone      - size of buffer already used.
 *          pStatus      - status of copy process.
 *****************************************************************************/
void RvH223MuxerGetFromBuffer(INOUT  HMUXER      hmuxer,
                              IN     RvUint8     *pBuffer,
                              IN     RvSize_t    buffLen,
                              INOUT  RvSize_t    *lenDone,
                              INOUT  RvStatus    *pStatus);
#endif /* (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES) */

/******************************************************************************
 * RvH223MuxerACPSetDefaultMuxTbl
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets default mux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerACPSetDefaultMuxTbl(IN  HMUXER   hmuxer);

 /******************************************************************************
 * RvH223MuxerSetACPInUse
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets bACPinUse in the muxer instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 *          value   - The value to set.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerSetACPInUse(
        IN  HMUXER   hmuxer, 
        IN  RvBool   value);

 /******************************************************************************
 * RvH223MuxerSetACPAudioEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets ACPAudioEntry in the muxer instance.
 *                        and creates the audio UCF entry in the mux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 *          value   - The mux table entry number.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerSetACPAudioEntry(
        IN  HMUXER      hmuxer, 
        IN  RvUint8    value);

 /******************************************************************************
 * RvH223MuxerGetACPAudioEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Gets ACPAudioEntry from the muxer instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 * Output:  value   - The value of the audio entry in the muxer.
 *****************************************************************************/
 RvStatus RvH223MuxerGetACPAudioEntry(
        IN      HMUXER      hmuxer, 
        OUT     RvUint32   *value);

 /******************************************************************************
 * RvH223MuxerSetACPVideoEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Sets ACPVideoEntry in the muxer instance.
 *                       and creates the video UCF entry in the mux table.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 *          value   - The mux table entry number.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerSetACPVideoEntry(
        IN  HMUXER      hmuxer, 
        IN  RvUint8     value);

 /******************************************************************************
 * RvH223MuxerGetACPVideoEntry
 * ----------------------------------------------------------------------------
 * General: For ACP - Gets ACPVideoEntry from the muxer instance.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 * Output:  value   - The value of the video entry in the muxer.
 *****************************************************************************/
 RvStatus RvH223MuxerGetACPVideoEntry(
        IN      HMUXER      hmuxer, 
        OUT     RvUint32   *value);
 
#if (RV_3G324M_USE_MONA == RV_YES)
  /******************************************************************************
 * RvH223MuxerSetMONA
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets the bMONAInUse flag in the muxer.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer			- Handle to the muxer instance.
 *          value           - Value to be set in the bMONAInUse flag.
 *****************************************************************************/
 RvStatus RvH223MuxerSetMONA(
     IN		HMUXER          hmuxer,
     IN     RvBool          value);

 /******************************************************************************
 * RvH223MuxerSetMonaMPCRTx
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets the mpcRx or mpcTx bitmask in the preference message 
 *					  parameters.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer			- Handle to the muxer instance.
 *          mpcRTx			- The bitmask of mpcRx or mpcTx to set.
 *		    isOutgoing		- If .RV_TRUE set the mpcTx, else - set the mpcRx
 *****************************************************************************/
 RvStatus RvH223MuxerSetMonaMPCRTx(
	 IN		HMUXER          hmuxer,
	 IN		RvUint16		mpcRTx,
	 IN		RvBool			isOutgoing);

 /******************************************************************************
 * RvH223SetMONAAckStatus
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets the ack status in the preference message 
 *					  parameters.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer			- Handle to the muxer instance.
 *          monaPMAckReceivedStatus	- The ack status in the last received 
 *									. preference message.
 *****************************************************************************/
 RvStatus RvH223SetMONAAckStatus(
	 IN		HMUXER      hmuxer,
	 IN		RvUint8		monaPMAckReceivedStatus);

/******************************************************************************
 * RvH223MuxerSetMonaMPCCall
 * ----------------------------------------------------------------------------
 * General: For MPC - Sets bUseMONA in the muxer instance, creates phantom channels 
 *                   according to the supportedChannels bitmask and creates 
 *                   the default MPC mux table according to the same bitmask 
 *                   Note: If supportedChaannels = 0 - the mux table, phantim
 *                   channels will be removed.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 *          hH223   - Handle to the H223 module.
 *          palCfg  - Array of adaptation layer transmitting configurations 
 *                    for all  supported MPC media codecs.
 *          supportedChannels   - The bitmask of required phantom channels
 *                                 and mux table entries.
 * Output:  activeMPCChannels   -   The bitmask of created MPC channels.
 *****************************************************************************/
 RvStatus RvH223MuxerSetMonaMPCCall(
        IN   HMUXER          hmuxer, 
        IN   HH223            hH223,
        IN   TH223TxALCfg    *palCfg, 
        IN   RvUint16         supportedChannels,
        OUT  RvUint16        *activeMPCChannels);

/******************************************************************************
 * RvH223MuxerRemoveMonaMPCChannel
 * ----------------------------------------------------------------------------
 * General: For MPC - Remove the phantom channel with the specified type.
 *
 * Return Value: RV_OK  - if successful, other RV_ERRORs else.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer  - Handle to the muxer instance.
 *          supportedChannels   - The bitmask of required phantom channels
 *                                 and mux table entries.
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerRemoveMonaMPCChannel(
        IN  HMUXER   hmuxer, 
        IN RvH223MonaMPCChannelType mpcChannelType);

 /******************************************************************************
 * RvH223MuxerGetMonaMPCChannelALContext
 * ----------------------------------------------------------------------------
 * General: Get Adaptation Layer handle for a MPC channel.   
 *
 * Return RV_OK on success, RV_ERROR_HELPER_OBJ_FAILURE on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer          - Handle to the muxer instance.
 *          mpcChannelType   - The type of MPC channel.
 * Output:  alContext       - The handle for the AL of the MPC channel.
 *****************************************************************************/
 RvStatus RvH223MuxerGetMonaMPCChannelALContext(
     IN     HMUXER              hmuxer,
     IN     RvH223MonaMPCChannelType mpcChannelType,
     OUT    void**              alContext);

  /******************************************************************************
 * RvH223MuxerMonaStopSendPreferenceMsg
 * ----------------------------------------------------------------------------
 * General: Stop sending MONA preference messages.   
 *
 * Return RV_OK on success, negative values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer              - Handle to the muxer instance.
 *
 * Output:  None.
 *****************************************************************************/
 RvStatus RvH223MuxerMonaStopSendPreferenceMsg(IN	HMUXER	hmuxer);

/******************************************************************************
 * RvH223MuxerGetMonaMPCActiveChannels
 * ----------------------------------------------------------------------------
 * General: Get a bitmask of currently active outgoing mpc channels.   
 *
 * Return RV_OK on success, RV_ERROR_HELPER_OBJ_FAILURE on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   hmuxer              - Handle to the muxer instance.
 * Output:  audioEntry          - Entry number of mpc audio channel 
 *                                (0 if no mpc audio channel).
 *          videoEntry          - Entry number of mpc video channel 
 *                                (0 if no mpc audio channel).
 *****************************************************************************/
 RvStatus RvH223MuxerGetMonaMPCActiveChannels(
     IN     HMUXER                  hmuxer,
     OUT    RvH223MonaMPCChannelType    *audioEntry,
     OUT    RvH223MonaMPCChannelType    *videoEntry); 
#endif /* USE_MONA */

#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_MUXER_IFC_H */
