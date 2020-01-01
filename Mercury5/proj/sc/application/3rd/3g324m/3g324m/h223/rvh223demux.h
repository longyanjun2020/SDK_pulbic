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

#ifndef _RV_H223_DEMUX_H
#define _RV_H223_DEMUX_H

#include "rvh223demuxifc.h"
#include "rvh223structs.h"
#include "muxtable.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

#define MUX_FLAGS_SEQUENCE_LENGTH   8 /* 16 */
#define DEMUX_MAX_NUMBER_OF_ERRORS  2 /* the maximum error that the golay code allows */
#define INVERSE_FLAGS_SEQUENCE_LENGTH   16
#define INVERSE_FLAGS_INDICATION   255

#define MOVE_2_NEXT_BYTE {(*pbuf)++; (*bytesProcessed)++; (*size)--;}

#define FREE_NONSEGMENTABLE     {                                                                           \
                                if ((NULL != pdesc->cfg.DemuxMuxDataIndicationEv) &&                        \
                                    (pdesc->currentBuffer != NULL))                                         \
                                {                                                                           \
                                    pdesc->cfg.DemuxMuxDataIndicationEv(                                    \
                                        pdesc->cfg.dataIndicationContext,                                   \
                                        pdesc->currentBuffer,                                               \
                                        pinst->parseParams.bytesRedFromThisAtom,                            \
                                        pinst->params.read.eDemuxResult);                                   \
                                }                                                                           \
                                pdesc->currentBuffer = NULL;                                                \
                                pdesc->pcurWrite = NULL;                                                    \
                                pdesc->bytesRed = 0;                                                        \
                                }

#define FREE_NONSEGMENTABLE_L0  {                                           \
                                FREE_NONSEGMENTABLE;                        \
                                pinst->parseParams.writeBitIndex = 0;       \
                                }


#define DELIVER_BYTE_L1(ptr)     {  \
                            if (pdesc->bytesRed >= pdesc->maxSize)                  \
                            {                                                       \
                                pinst->eReadingState = DEMUX_SYNCHRONIZE;           \
                                stop = RV_TRUE;                                     \
                                nextIteration = RV_FALSE;                           \
                                break;                                              \
                            }       \
                            if (NULL != pdesc->pcurWrite)               \
                            {                                           \
                                *pdesc->pcurWrite++ = *(ptr);           \
                            }                                           \
                            pinst->parseParams.bytesRedFromThisAtom++;  \
                            pdesc->bytesRed++;                          \
                        }
#define FREE_READ_BUFFER_L1(ptr, size)  {                               \
                            for (i = 0; i < (size); i++)                \
                            {                                           \
                                DELIVER_BYTE_L1(&(ptr)[i]);             \
                            }                                           \
                        }

/* DemuxReadState
 * ----------------------------------------------------------------------------
 * This enumeration is used to remember the current type of information parsed
 * from the buffer
 */
typedef enum
{
    DEMUX_DETERMINE_MUX_LEVEL = 0,
    DEMUX_SYNCHRONIZE,
    DEMUX_FLAG,
    DEMUX_HEADER,
    DEMUX_DATA,
    DEMUX_MONA
} DemuxReadState;

/* DemuxSyncState
 * ----------------------------------------------------------------------------
 * This enumeration is used as a state machine for the synchronization procedure
 * from the buffer
 */
typedef enum
{
    DemuxSyncUnknown,
    DemuxSyncLevel0,
    DemuxSyncLevel1or2,
    DemuxSyncLevel1,
    DemuxSyncLevel2,
    DemuxSyncLevel2waitOpt,
    DemuxSyncLevel2opt,
    DemuxSyncLevel2wait0000,
    DemuxSyncLevel3,
    DemuxSyncLevel3waitOpt,
    DemuxSyncLevel3opt,
    DemuxSyncLevel3wait0F20
} DemuxSyncState;

/*A media buffer element for ACP*/
typedef  struct 
{
	RvUint8 *buff; 
	RvSize_t size;
} h223ACPBufferElem;

/*This structure that holds all the media buffer elements for the primary video channel for ACP*/
typedef  struct 
{
	h223ACPBufferElem   *buffers;         /*the media buffers*/
	h223ACPBufferElem	nextBuffer2save;
    RvUint8	            currentNumVideoBuffers;     /*the number of currently used buffers*/
    RvInt8              currentReplayIndex;         /*the index of the replayed buffer. -1 if no buffer is replayed.*/ 
    RvInt64             noMediaBufferingTimeStamp;  /*An indication that a video channel reject was sent 
                                           and video media should not be buffered for a while*/
	RvBool				bCheckIgnoreData;	/* RV_FALSE if noMediaBufferingTimeStamp == 0 */
    RvBool              replayVideoBuffers; /*Indication for the demux to replay saved videoBuffers*/
} h223VideoBuffers;


/* DemuxListDesc
 * ----------------------------------------------------------------------------
 * This structure is used to help in the parsing process of a MUX-PDU.
 */
typedef struct
{
    TMuxTblAtom     *pactive;  /* active list */
    RvUint16        runningCount; /* the repeat count of the list */
} DemuxListDesc;


/* DemuxParseParams
 * ----------------------------------------------------------------------------
 * This structure is used to remember in which situation we left the parsing
 * process when we switched buffers
 */
typedef struct
{
    DemuxListDesc listDesc[RV_H223_NESTING_DEPTH_MAX + 1]; /* list that holds the atoms from list type */
    RvUint32      listBalance; /* The index in the listDesc */
    TMuxTblAtom   *patom;  /* the atom array of the multiplexEntry */
    RvUint32      bytesRedFromThisAtom;
    RvBool        resumeAtom;
    RvUint8       onesCount;
    RvUint8       writeBitIndex; /* Used in level 0 only */
    RvUint8       readBitIndex; /* Used in level 0 only */
    RvUint8       storedByte; /* Used in level 0 only */
    RvBool        active;
} DemuxParseParams;


/* DemuxSyncParams
 * ----------------------------------------------------------------------------
 * This structure is used to remember synchronization related parameters.
 * These parameters are used only from DetermineMuxLevel().
 */
typedef struct
{
    RvUint32        bytesRead; /* Number of bytes read for the current sync component */
    RvUint32        readingBuffer; /* Accumulated buffer information */
    DemuxSyncState  state; /* Synchronization state we're in */
    RvUint8         bitShift; /* Current bit shifting we're looking for */
    RvBool          bIsOpt; /* RV_TRUE for synchronization on an optional header in mux levels 2 and 3 */
} DemuxSyncParams;


/* DemuxReadParams
 * ----------------------------------------------------------------------------
 * This structure is used to remember in which situation we left the validate
 * process when we switched buffers.
 */
typedef struct
{
    RvUint32        bytesReadUntilNowFromThisTypeOfInformation; /* number of bytes read from the current type of information */
    RvUint8         readingBuffer[5]; /* the buffer that accumulates the bytes from the current type of information */
    EDemuxResult    eDemuxResult;   /* the demux result that should be given to the AL layer */
    RvUint8         mc;             /* Multiplex Code - the number of the entry inside the muxTable */
    RvUint8         mpl;            /* the length of the information field */
    RvBool          parseClosingFlag; /* defines whether the closing flag was actually an opening flag */
    RvBool          bLastWasntFlag; /* RV_TRUE if the last state we were at was trying to search for a flag,
                                       but we couldn't find any when we get a header. This is needed for
                                       mux-level 2, where 0xFFFFFF is a valid header - it causes some
                                       aggravation... */
    RvUint16        inverseFlagsCount; /* Defines the number of inverse flags */
    RvUint8         inverseFlagsCharsCount; /* Defines the number of characters processed from
                                               a specific inverse flag */
    RvBool          bInverseFlagsFound;
    /* MONA */
    RvBool          bPrevWasMonaFEA;    /* RV_TRUE if the previously read byte was 0xC5
                                           in a MONA preference message */
    /* PMT */
    RvUint32        consecutiveFlags;      /* Count consecutive flags for muxLevel switching in PMT */
} DemuxReadParams;


/* TH223DemuxLCDesc
 * ----------------------------------------------------------------------------
 * The H.223 de-multiplexer logical channel descriptor.
 * This is used for parsing incoming MUX-SDUs on the stream for a given frame of
 * a logical channel. It might span several buffers as well as several MUX-PDUs.
 */
typedef struct H223DemuxLCDesc TH223DemuxLCDesc;
struct H223DemuxLCDesc
{
    TH223DemuxLCDescCfg cfg;
    RvUint8            *currentBuffer;
    RvUint8            *pcurWrite;
    RvUint32            bytesRed;
    RvUint32            maxSize;
#if (RV_H223_USE_MEMORY_LOCALITY == RV_NO)
    TH223DemuxLCDesc   *pPrev;
    TH223DemuxLCDesc   *pNext;
#else
    RvUint32            pPrev;
    RvUint32            pNext;
#endif
};


/* TH223DemuxClass
 * ----------------------------------------------------------------------------
 * The H.223 de-multiplexer class
 */
typedef struct
{
    RvH223MuxLevelIndicationEv      MuxLevelIndicationEv;
#if (RV_H223_USE_MEMORY_LOCALITY == RV_NO)
    HRA                             chnlDesc; /* RA of channel descriptors */
#else
    RvUint16                        numOfLCPerDemux; /* Number of logical channels allows per de-multiplexer */
    RvUint16                        numOfAlSduSaved; /* Number of retransmission packets */
#endif
    RvLogSource                     hLog;
    RvLogSource                     hLogErr;
    RvLogMgr                        *hLogMgr;
     /*ACP*/
    RvH223GetBufEv                  DemuxACPGetBufEv; /*get buffer event for ACP*/
    RvH223ReleaseBufEv              DemuxACPReleaseBufEv;/*release buffer event for ACP*/
    RvUint8	                        maxVideoBuffers; /*max buffers to use for video buffering per call*/
    /* MONA */
    RvH223MONAUpdateAckStatusEv     MonaUpdateAckStatusEv;
    RvH223MONAPreferenceRcvEv       MonaPreferenceRcvEv;
} TH223DemuxClass;


/*MPC channel element*/
typedef struct{
    TH223DemuxLCDesc    *pmpcChannel;
    void                *alRxContext; /*MPC channel AL object*/
}TH223MPCDemuxChannel;


/* TH223DemuxInstance
 * ----------------------------------------------------------------------------
 * The H.223 de-multiplexer part of a call
 */
typedef struct
{
    RvBool              parseDamaged;
    RvUint8             pDamagedPdu[MUX_PDU_LEVEL_2_PAYLOAD_SIZE_MAX]; /* A buffer for generic use.
                                                                       currently used for damaged pdus and
                                                                       MONA preference message */
    RvUint8            *pwriteDamaged;
    RvUint32            damagedPduSize;
    void               *muxLevelIndicationContext;
    RvUint32            stuffingCounter;
    RvUint32            maxOutOfSync; /* Maximum bytes that we tolerate until we declare out-of-synch */
    RvUint32            outOfSyncCounter; /* Number of bytes that got out-of-synch */
#if (RV_H223_USE_MEMORY_LOCALITY == RV_NO)
    TH223DemuxLCDesc   *firstChannel;
    TH223DemuxLCDesc   *lastChannel;
#else
    RvUint32            firstChannel;
    RvUint32            lastChannel;
#endif
    TMuxTbl             muxerTable;

    /* ACP related parameters */
    RvUint16            ACPAudioEntry;
    RvUint16            ACPVideoEntry;
    TH223DemuxLCDesc   *ACPAudioChan; 
    TH223DemuxLCDesc   *ACPVideoChan;
    DemuxACPStatus      ACPStatus; 
    h223VideoBuffers    videoBuffers; /*the buffers for media buffering*/
#if (RV_3G324M_USE_MONA == RV_YES)
    /*MPC related parameters*/
    RvBool               bUseMONA;     /*RV_TRUE if MPC used on the call*/
    TH223MPCDemuxChannel MonaMPCChannels[RV_H223_MPC_MAX_SUPPORTED_CHANNELS];
    RvBool               callMonaPreferenceMsgRcvEv; /* RV_TRUE if the event should be raised to the application */
    RvBool               callMonaPreferenceMsgMuxlevelIndEv; /* RV_TRUE if MuxLevelIndicationEv should be called while handling 
                                                             the received preference message */
    RvUint8              pMonaPMBuffer[MUX_PDU_LEVEL_2_PAYLOAD_SIZE_MAX];
    RvUint32             monaPMBufferSize; 
    RvUint16             mpcTxTypes; /* Bitmask of supported transmitting MPC types */
    RvUint16             mpcRxTypes; /* Bitmask of supported receiving MPC types */
#endif /* USE_MONA */
#if (RV_H223_USE_MUX_LEVEL_2 == RV_YES)
    RvUint8             PMFlag;
	RvBool				bFirstTime;
#endif
    RvUint8             inSession;
    TMuxLevelCfg        levelCfg;
    TMuxLevelCfg        tmpLevelCfg;
    TH223DemuxClass    *pDemuxModule;
    DemuxReadState      eReadingState; /* the state of the parsing: OpeningFlag, Header, Data or ClosingFlag */
    DemuxReadState      eSavedReadingState; /* Saved reading state for after MONA */
    RvBool              incrementBuffer; /* Used in MONA only RV_TRUE if buffer should not be read from the
                                            beginning after synchronization */
    DemuxParseParams    parseParams; /* parse params that remember the situation when changing buffers */
    DemuxParseParams    tmpParseParams;
    union
    {
        DemuxReadParams     read;  /* read params that remember the situation when changing buffers */
        DemuxSyncParams     sync; /* sync params that remember the situation when changing buffers */
    } params;
    RvMutex             instanceMutex;
} TH223DemuxInstance;


typedef struct
{

/******************************************************************************
 * parseFlag
 * ----------------------------------------------------------------------------
 * General: Parse only the closing uoption.
 * Return Value: RvUint32 - The size of the data that was processed.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : pinst  - The demux instance object.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer.
 * Output : none
 *****************************************************************************/
RvUint32 (*parseFlag)(
                      IN   TH223DemuxInstance  *pinst,
                      IN   RvUint8             *pbuf,
                      IN   RvUint32            size);


/******************************************************************************
 * parseHeader
 * ----------------------------------------------------------------------------
 * General: Parse only the header of the MUX-PDU. if we managed to find a header,
 *          we validate the header according to the header type.
 * Return Value: RvUint32 - The size of the data that was processed.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : pinst  - The demux instance object.
 *          pbuf   - The incoming buffer.
 *          size   - The size of information in the buffer. Should be more then
 *                   4 (including optional header).
 * Output : none
 *****************************************************************************/
RvUint32 (*parseHeader)(
                        IN   TH223DemuxInstance  *pinst,
                        IN   RvUint8             *pbuf,
                        IN   RvUint32            size);


/******************************************************************************
 * ParseData
 * ----------------------------------------------------------------------------
 * General: Parse only the information field of the MUX-PDU.
 * Return Value: RvUint32 - The size of the data that was processed.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input  : pinst          - The demux instance object.
 *          pdesc          - The logical channel descriptor.
 *          pbuf           - The incoming buffer.
 *          size           - The size of information in the buffer.
 *          stopping       - Defines whether there is no more data to read.
 *          bytesProcessed - The size of the data that was processed.
 * Output : none
 *****************************************************************************/
RvUint32 (*parseData)(
                      IN    TH223DemuxInstance  *pinst,
                      IN    TH223DemuxLCDesc    *pdesc,
                      INOUT RvUint8             **pbuf,
                      INOUT RvUint32            *size,
                      INOUT RvBool              *stopping,
                      INOUT RvUint32            *bytesProcessed);


/******************************************************************************
* synchronize
* ----------------------------------------------------------------------------
* General: Finds the next opening/closing flag.
* Return Value: Processed size.
* ----------------------------------------------------------------------------
* Arguments:
* Input  : pinst          - The demux instance object.
*          pbuf           - The incoming buffer.
*          size           - The size of information in the buffer.
*          bytesProcessed - Number of bytes processed
******************************************************************************/
RvUint32 (*synchronize) (
                          IN TH223DemuxInstance  *pinst,
                          INOUT RvUint8          **pbuf,
                          INOUT RvUint32         *size,
                          INOUT RvUint32         *bytesProcessed);



}DemuxParseFunctions;

#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_DEMUXER_H */
