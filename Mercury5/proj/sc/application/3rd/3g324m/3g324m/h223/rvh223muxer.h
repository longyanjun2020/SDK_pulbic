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

#ifndef _RV_H223_MUXER_H
#define _RV_H223_MUXER_H

#include "ra.h"
#include "rvh223muxerifc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                            MODULE VARIABLES                               */
/*---------------------------------------------------------------------------*/

/* The highest LCN number supported for an outgoing channel */
#define MAX_LC                  (5)

#define LC_IDX_CONTROL          (0)
#define LC_IDX_AUDIO            (1)
#define LC_IDX_VIDEO1           (2)
#define LC_IDX_VIDEO2           (3)
#define LC_IDX_DATA             (4)

#define AMR_COMFORT_NOISE_SIZE      6
#define AMR_NO_DATA_SIZE            1
#define G723_SID_SIZE               4
#define G723_LOW_BIT_RATE_SIZE      20
#define G723_HIGH_BIT_RATE_SIZE     24
/* AMR WIDEBAND */
#define G7222_COMFORT_NOISE_SIZE    6
#define G7222_NO_DATA_SIZE          1


#define AUDIO_AMR_IN_USE(audioType) \
    (((audioType) >= AMR_4750_TYPE) && ((audioType) <= AMR_1220_TYPE) ? RV_TRUE : RV_FALSE)
#define AUDIO_G7231_IN_USE(audioType) \
    (((audioType) >= G723_53_TYPE) && ((audioType) <= G723_63_TYPE) ? RV_TRUE : RV_FALSE)
/* AMR WIDEBAND */
#define AUDIO_G7222_IN_USE(audioType) \
    (((audioType) >= G7222_0660_TYPE) && ((audioType) <= G7222_2385_TYPE) ? RV_TRUE : RV_FALSE)

#define DEFAULT_VIDEO_2_DATA_RATIO  5
#define BYTES_MULTIPLYER            10

#define EXPECTED_SIZE_MAX(x)  ((((x) * 5) >> 2) + ((x) & 0x01))

#define CHECK_ALIGNMENT(x, s, i) \
                        {                                   \
                            if (8 == ++(i))                 \
                            {                               \
                                (x)++;                      \
                                (s)--;                      \
                                (i) = 0;                    \
                            }                               \
                        }

#define MAX_PAYLOAD_SIZE 260 /* Used for rpool elements */

#if (RV_3G324M_USE_MONA == RV_YES)
#define MAX_MONA_MSG_LEN            26
#define RAW_MONA_MSG_LEN            11
#define MONA_MAX_ACK_STATUS          2
#define MONA_MIN_NUMBER_OF_MESSAGES 10
#define MONA_MAX_NUMBER_OF_MESSAGES 300
#define MONA_MAX_NUMBER_OF_ACK_2     5 /* The maximum number of times mona PM with ack=0x10 will be sent */ 
/* MONA preference message params */
typedef struct  
{
    RvUint8     ver;            /* MONA version - value 3 is reserved*/
    RvUint8     monaAckStatus;  /* 0x00 - No preference message received. 
                                   0x01 - A preference message with ack field 0x00 received.
                                   0x10 - A preference message with ack field 0x01 received. */
    RvBool      bSupportSPC;    /* RV_TRUE If SPC supported - currently always RV_FALSE */
    RvBool      bPreferSPC;     /* RV_TRUE if SPC is preferred - currently always RV_FALSE */
    RvUint8     monaML;          /* The initial muxLevel of the call that will be inserted into
                                   the MONA-ML of the prefernce message */
    RvUint8     payloadLen;     /* length of payload of preference message */
    RvUint16    mpcRx;          /* Bitmask of receiving MPC channels/types */
    RvUint16    mpcTx;          /* Bitmask of transmitting MPC channels/types - currently always 0 */
    RvBool      maxAckMsgSent;  /* Indication that a prefernce message with ack 2 sent */
    RvBool      firstAckMsgSent; /* Indication that 1 PM with ack = 1 was sent */
    RvUint16    numMessagesSent; /* The number of preference messages sent until now */
    RvUint8     numMaxAckSent; /* RV_TRUE if first PM with Ack 0x10 sent */
}TH223MuxMonaPMParams;
#endif
/* StuffingParams
 * ----------------------------------------------------------------------------
 * The multiplexer's 0-bit insertion information. This is required when working
 * in mux level 0.
 */
typedef struct
{
    RvUint8   writeBitIndex; /* Index of the next free bit */
    RvUint8   onesCount; /* Number of consecutive bits with the value of 1 inserted/checked */
    RvUint8   stuffingRemainder;
    RvUint8   readBit; /* Mux-level 0 read bit when using software 0-bit insersion */
} StuffingParams;


/* OutBufParams
 * ----------------------------------------------------------------------------
 * Intermediate buffer information. This is required for the multiplexing
 * process.
 */
typedef struct
{
  RvUint8   *pbuf;            /* Buffer to use by RvH223MuxerGetMuxedStream.*/
  RvUint32   maxSize;         /* Size of the above buffer.*/
  RvUint8   *pread;           /* Current read pointer.*/
  RvUint32   readSize;        /* Remaining size of the data.*/
  RvUint8   *pstuffPtr;       /* Pointer to a next byte of stuffing sequence.*/
  RvUint8    remainStuffSize; /* Size of the remaining stuffing sequence.*/
} OutBufParams;


/* TH223MuxEntry
 * ----------------------------------------------------------------------------
 * A multiplexer entry information. This one is quite condensed to work well
 * with our smart multiplexing technique.
 */
typedef struct
{
	RvUint8	dataTypes; /* Data types needed for this entry */
	RvUint8	segSizes; /* Size of segmentable channels that are used. 4 bits each */
} TH223MuxEntry;


typedef struct{
    TMuxLevelCfg    levelCfg;
    RvUint32        entry;
    RvUint32        numDataTypes; /* Number of data types we're trying to mux with the entry */
    TH223MuxEntry   muxEntry; /* Multiplex entry to use */
    RvUint8        *poutbuf;
}MuxTemp;

typedef struct{
    TMuxLevelCfg    levelCfg;
    RvUint32        freeSize;
    RvBool          invertFlags;
    RvUint8        *poutbuf;
}StuffTemp;


/* TMuxSduInWork
 * ----------------------------------------------------------------------------
 * The current MUX-SDU being sent by the multiplexer on a given logical channel
 */
typedef struct
{
    TRvMuxSdu               *pmuxSduPtr;
    RvUint32                byteIndex;
    RvInt32                 overallSize; /* Negative value indicates WNSRP frame during call setup */
    HRPOOL                  hRpool; /* RPOOL handle to use when applicable for the given MUX-SDU */
    RvH223ReleaseMuxSduEv   ReleaseMuxSduEv; /* Callback for input MuxSdu release.*/
    void                    *releaseContext; /* Context for ReleaseMuxSduEv */
    RvInt32                 releaseSubContext;
} TMuxSduInWork;


/* TH223MuxerLCDesc
 * ----------------------------------------------------------------------------
 * The H.223 multiplexer logical channel descriptor data
 */
typedef struct
{
    RvUint16          lcn;              /* Logical channel number.*/
    RvBool            segmentable;      /* Used in MUX-PDU creation.*/
    RvBool            framed;           /* Used in MUX-PDU creation.*/
    RvH223LCDataType  dataType;         /* Used in muxtable entries choice.*/
    RvH223IsClearEv   MuxerLCIsClearEv; /* Ready for LC termination callback.*/
    void             *clearContext;     /* Context for MuxerLCIsClearEv.*/
    TRvMuxSdu       **ppmuxSduRequest;  /* Pointers to input MuxSdu-s.*/
    TCyclicParams     requestList;      /* Management parameters of ppmuxSduRequest list.*/
} TH223MuxerLCDesc;


/*MPC channel element*/
typedef struct{
    TH223MuxerLCDesc    *pmpcChannel;
    void                *alTxContext; /*phantom channel AL object*/
}TH223MPCMuxerChannel;


/* TH223MuxerClass
 * ----------------------------------------------------------------------------
 * The H.223 multiplexer class
 */
typedef struct
{
    RvUint16    numOfLCPerMuxer; /* Number of logical channels we might have */
    RvUint16    numOfMuxSduPerMuxLC; /* Number of MUX-SDUs per channel (queue length) */
#if (RV_H223_USE_MEMORY_LOCALITY == RV_NO)
    HRA         lcdescArray;    /* Channel descriptors per multiplexer */
#endif
    HRPOOL      hControlMsgs; /* Handle to rpool to be used for payloads that are saved in rpool elements */
    HRPOOL      hMediaFrames; /* Handle to rpool to be used for ALxM media frames */
    RvLogSource hLog;            /* used for log printing */
    RvLogSource hLogErr;         /* used for error log printing */
    RvLogMgr    *hLogMgr;
    RvH223MONAPreferenceSendEv       MonaPreferenceSendEv;
	RvH223MONAAckStatusChangedEv	 MonaAckStatusChangedEv;
} TH223MuxerClass;


/* TH223MuxerInstance
 * ----------------------------------------------------------------------------
 * The H.223 multiplexer part of a call
 */
typedef struct
{
    TH223MuxerClass     *pMuxerClass;       /* pointer to the muxer class */
    TMuxLevelCfg        levelCfg;           /* Mux level and level specific flags.*/
#if (RV_H223_USE_MEMORY_LOCALITY == RV_NO)
    TH223MuxerLCDesc    *pChannel[MAX_LC];  /* Pointers to the channels used (0-control,1-audio,2-video1,3-video2,4-data) */
#else
    RvUint32            channelOffset[MAX_LC];  /* Offset to the channels used (0-control,1-audio,2-video1,3-video2,4-data) */
#endif

    /* Information needed for the choice of mux entry when muxing */
    RvUint8             entryLookup[RV_H223_MAX_AUDIO_FRAME_SIZE+1];    /* Lookup table for smaller mux table */
    RvUint8             table[8][RV_H223_MAX_AUDIO_SIZES+1]; /* Compact "mux-table" used */
    RvUint32            requestDataTypes;   /* Bitmask of the data types we have pending for muxing */
    RvUint8             pendingAudioSize;   /* Size of audio we have pending */
    RvUint16            maxPduSize;         /* Maximum size of a PDU. This is pre-calculated from levelCfg */
    TH223MuxEntry       entry[15];          /* Mux entries information */
    RvUint8             PMflag;
    RvUint8             firstTime;
    RvUint8             muxTableIsUpdated;  /* RV_TRUE if the mux table is updated properly */
    RvUint8             audioOverhead;      /* Bytes of overhead we have for the audio channel */
#if (RV_3G324M_USE_MONA == RV_YES)
    /* MONA */
    RvBool                  bMONAInUse;                 /* RV_TRUE if MONA call setup procedures are in use */
    void                    *callContext;
    TH223MuxMonaPMParams    monaPreferenceMsgParams; /* Current parameters of MONA preference message */
	RvUint8					monaPreferenceMsg[RAW_MONA_MSG_LEN]; /* the buffer containing the raw preference message after CRC and before FEA */
	RvUint8					monaPreferenceMsg2Send[MAX_MONA_MSG_LEN]; /* the buffer containing the preference message after FEA and CRC */
    RvUint32                monaPreferenceMsg2SendSize;   /* size of preference message after Frame Emulation Avoidance 
															and CRC */
    RvUint32                monaPreferenceMsg2SendSizeLeft; /* The number of bytes left to be set in the stream of the currently
															added prefernce message */
    RvUint32                monaRemainStuffing;             /* How many sync flag sequences should be added */ 
    RvBool                  addFlagBeforeData;              /* If RV_TRUE - flag is added before data */
    RvBool                  lastFlagOctetNeeded;            /* Second octet of muxLevel flag needed before data */
#endif /* USE_MONA */
    RvBool                  bUseMonaStuffing;               /* MONA stuffing (MONA flag + preference message + MONA flag + 20 sync flags) */                

    /* ACP */
    RvBool                  bACPInUse;          /*RV_TRUE if ACP is used in this call for fast connection*/ 
    RvUint8                 ACPAudioEntry;       /* Audio UCF mux table entry when using ACP */
    RvUint8                 ACPVideoEntry;       /* Video1 UCF mux table entry when using ACP */

    /*MPC related parameters*/
    RvUint16                activeMPCChannels;   /*bitmask of active mpc channel (1 audio & 1 video*/
    TH223MPCMuxerChannel    MonaMPCChannels[RV_H223_MPC_MAX_SUPPORTED_CHANNELS]; /*MPC channels*/
    TH223MuxEntry           mpcEntry[RV_H223_MPC_MAX_SUPPORTED_CHANNELS]; /*mux table for MPC*/
    TMuxSduInWork           mpcMuxSdu[MAX_LC];   /* MuxSdu processing parameters. */
    /*TODO: RvBool                  bLastWasControl;*/

    /*retransmission on idle*/
    RvUint32            pendingMuxSdus;     /*Number of mux_sdus that are currently in use*/
    RvBool              retransmissionOnIdle; /* RV_TRUE if retransmission on idle mode is on */
    RvUint32            additionalRemainStuff; /* To ensure a minimum of stuffing between retransmissions on idle */

#if (RV_H223_USE_MUX_LEVEL_2 == RV_YES)
    RvUint8             optionalHeader;     /* Optional header. Used in level 2 only.*/
#endif /* (RV_H223_USE_MUX_LEVEL_2 == RV_YES) */
#if (RV_H223_USE_MUX_LEVEL_0 == RV_YES)
    StuffingParams      stuffParams;        /* HDLC stuffing parameters. Used in level 0 only.*/
#endif /* (RV_H223_USE_MUX_LEVEL_0 == RV_YES) */
    OutBufParams        muxOutput;          /* Intermediate buffer's management parameters.*/
    RvUint32            overallStuffSize;   /* Keeps track of the number of stuffing bytes.*/
    RvMutex             instanceMutex;      /* Locks instance data modifying.*/

    /* Information needed for the Multiplex() function. This is never locked. */
    TMuxSduInWork       muxSdu[MAX_LC];   /* MuxSdu processing parameters. */
    RvUint32            processDataTypes;   /* Bitmask of the data types we have pending in muxSdu field */

} TH223MuxerInstance;


#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_MUXER_H */
