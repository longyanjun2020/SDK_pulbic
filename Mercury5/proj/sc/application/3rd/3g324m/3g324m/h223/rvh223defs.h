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

#ifndef _RV_H223_DEFS_H
#define _RV_H223_DEFS_H

#include "rpool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                                */
/*---------------------------------------------------------------------------*/

/* General configuration parameters.*/
#define RV_H223_NESTING_DEPTH_MAX   1   /* Maximal nesting depth of multiplex
                                           table entry.*/
#define RV_H223_ELEM_LIST_SIZE_MAX  2   /* Maximal number of elements at
                                           multiplex table entry.*/
#define RV_H223_SUB_ELEM_LIST_SIZE_MAX 2/* Maximal number of sub-elements at
                                           multiplex table entry.*/
/* The following number is tricky to get.It should be calculated as follows:
int size = 1;
while (RV_H223_NESTING_DEPTH_MAX-- >= 0)
{
  size += (RV_H223_SUB_ELEM_LIST_SIZE_MAX ^ RV_H223_NESTING_DEPTH_MAX) *
           RV_H223_ELEM_LIST_SIZE_MAX;
},
where ^ means power.
However this number can be enormous, so it is manually set here.*/
#define RV_H223_MUX_TABLE_ATOM_PER_ENTRY_MAX   7
/* End of general configuration parameters.*/

/* New handle types.*/
RV_DECLARE_HANDLE (HH223MODULE);
RV_DECLARE_HANDLE (HMUXERMODULE);
RV_DECLARE_HANDLE (HDEMUXMODULE);
RV_DECLARE_HANDLE (HH223CONTROLMODULE);
RV_DECLARE_HANDLE (HTXALMODULE);
RV_DECLARE_HANDLE (HRXALMODULE);

RV_DECLARE_HANDLE (HH223);
RV_DECLARE_HANDLE (HMUXER);
RV_DECLARE_HANDLE (HDEMUX);
RV_DECLARE_HANDLE (HH223CONTROL);
RV_DECLARE_HANDLE (HTXAL);
RV_DECLARE_HANDLE (HRXAL);
RV_DECLARE_HANDLE (HMUXLCDESC);

/* Some H223 specific error codes.*/
#define RV_ERROR_HELPER_OBJ_FAILURE -512  /* Infrastructure object failure.*/
#define RV_ERROR_CHANNEL_IS_CLOSING -514 /* Channel has ReportClear flag set.*/

/* Logical channel types for use during multiplex table related operations.*/
#define CHANNEL_TYPE_UNKNOWN 0L
#define CHANNEL_TYPE_CONTROL 0x00000010
#define CHANNEL_TYPE_AUDIO   0x00000008
#define CHANNEL_TYPE_DATA    0x00000001
#define CHANNEL_TYPE_VIDEO   0x00000002
#define CHANNEL_TYPE_VIDEO2  0x00000004

/* Payload types available for the muxer */
#define PAYLOAD_BUFFER      0   /* Regular buffer payload indication */
#define PAYLOAD_RPOOL       1   /* RPOOL element given as payload and is being process by the muxer */
#define PAYLOAD_RPOOL_DONE  2   /* RPOOL element that was already acknowledged and is not needed
                                   anymore by the muxer was given as payload */
#define PAYLOAD_RPOOL_SENT  3   /* RPOOL element that was already sent by the muxer but was not
                                   acknowledged and might get retransmitted in the future */

/* MUX-PDU delimiting flags.*/
#define MUX_LEVEL_0_FLAG     0x7e
#define MUX_LEVEL_0_INVERSE_FLAG   0x81
#define MUX_LEVEL_1_2_FLAG_OCTET_1 0xe1
#define MUX_LEVEL_1_2_FLAG_OCTET_2 0x4d
#define MUX_LEVEL_1_2_INVERSE_FLAG_OCTET_1 0x1e
#define MUX_LEVEL_1_2_INVERSE_FLAG_OCTET_2 0xb2
#define MUX_LEVEL_2_3_INVERSE_FLAG_OCTET 0xff
#define MUX_LEVEL_3_INVERSE_FLAG_OCTET 0xf0
#if (RV_3G324M_USE_MONA == RV_YES)
#define MUX_LEVEL_MONA_FLAG_OCTET_1 0xa3
#define MUX_LEVEL_MONA_FLAG_OCTET_2 0x35
#define MUX_LEVEL_MONA_FEA_BYTE     0xC5
#endif /* USE_MONA */

#define CYCLIC_INCREMENT32(counter, addition, limit)  ((counter) = (RvUint32)(((RvUint32)(counter) + (addition)) % (limit)))
#define CYCLIC_INCREMENT16(counter, addition, limit)  ((counter) = (RvUint16)(((RvUint16)(counter) + (addition)) % (limit)))
#define CYCLIC_INCREMENT8(counter, addition, limit)   ((counter) = (RvUint8)(((RvUint8)(counter) + (addition)) % (limit)))
#define CYCLIC_DIFFERENCE16(head, tail, limit)   (RvUint16)(((head) >= (tail)) ? ((head) - (tail)) : (((limit) - (tail)) + (head)))
#define CYCLIC_DECREMENT16(counter, addition, limit) \
    {                                                                                                           \
        if ((RvUint16)(counter) >= (RvUint16)(addition))                                                        \
        {                                                                                                       \
            (counter) = (RvUint16)((RvUint16)(counter) - (RvUint16)(addition));                                 \
        }                                                                                                       \
        else                                                                                                    \
        {                                                                                                       \
            (counter) = (RvUint16)((RvUint16)(limit) - (RvUint16)((RvUint16)(addition) - (RvUint16)(counter))); \
        }                                                                                                       \
    }

#define CYCLIC_DECREMENT8(counter, addition, limit) \
    {                                                                                                           \
        if ((RvUint8)(counter) >= (RvUint8)(addition))                                                          \
        {                                                                                                       \
            (counter) = (RvUint8)((RvUint8)(counter) - (RvUint8)(addition));                                    \
        }                                                                                                       \
        else                                                                                                    \
        {                                                                                                       \
            (counter) = (RvUint8)((RvUint8)(limit) - (RvUint8)((RvUint8)(addition) - (RvUint8)(counter)));      \
        }                                                                                                       \
    }

#define CONSECUTIVE_1_MAX     5
#define INSERT_0(x, i)        (*(x) &= ~(PATTERN_1 << (i)))
#define INSERT_1(x, i)        (*(x) |= (PATTERN_1 << (i)))

/* Muxtable related definitions.*/
#define REPEAT_COUNT_UCF 0 /* UCF - Until Closing Flag.*/
#define MUXTABLE_ATOM_TYPE_ATOM 1
#define MUXTABLE_ATOM_TYPE_LIST 2
#define CONTROL_LOGICAL_CHANNEL_NUMBER  0

/* Miscellaneous.*/
#define MUX_PDU_LEVEL_0_PAYLOAD_SIZE_MAX  254
#define MUX_PDU_LEVEL_1_PAYLOAD_SIZE_MAX  254
#define MUX_PDU_LEVEL_2_PAYLOAD_SIZE_MAX  254
#define PATTERN_1                         0x01
#define LEVEL_1_2_FLAG_SIZE               2
#define WNSRP_PAYLOAD_FLAG                0x8000 /* used as a mask for the payload size to determine if the mux-sdu is from WNDRP type */

/*MONA MPC defintions*/
#define RV_H223_MPC_AMR_SUPPORTED        0x0002
#define RV_H223_MPC_AMR_WB_SUPPORTED     0x0004
#define RV_H223_MPC_H264_SUPPORTED       0x0008
#define RV_H223_MPC_MPEG4_SUPPORTED      0x0010
#define RV_H223_MPC_H263_SUPPORTED       0x0020

#define MONA_FLAG_SIZE                   2

/*MPC max supported channels*/
#define RV_H223_MPC_MAX_SUPPORTED_CHANNELS   5




/* Structure, which defines the atom of muxtable entry.*/
typedef struct{
    RvUint8 atomType;       /* TYPE_ATOM or TYPE_LIST.*/
    RvUint8 repeatCount;    /* Repeat count.*/
    union
    {
        RvUint16  firstAtom;  /* Index of the first TMuxTblAtom in the list if type == TYPE_LIST.*/
        RvUint16  lcn;        /* Logical channel number if type == TYPE_ATOM.*/
    } atomData;
    void  *plc;             /* Pointer to the associated logical channel descriptor.
                             to use by MUXER and DEMUXER only!*/
}TMuxTblAtom;


/* Structure for data exchange between user, LC and Muxer.*/
typedef struct{
    RvUint8       pheader[3];         /* OUT - is filled by LC according to its AL.*/
    RvUint8       headerSize;         /* OUT - is filled by LC according to its AL.*/
    union
    {
        HRPOOLELEM  pRpoolElement;          /* IN - RPOOL payload buffer element */
        RvUint8     *pBuffer;               /* IN - Payload buffer pointer */
    } ppayload;
    RvInt16       payloadSize;        /* IN  - a size of data, pointed to by ppayload. Negative value used for WNSRP at beginning of call */
    RvUint8       payloadType;        /* IN  - defines whether ppayload is rpool element or a buffer. 1 - rpoolElement, 0 - buffer */
    RvUint8       suffixSize;         /* OUT - is filled by LC according to its AL.*/
#if (RV_H223_USE_MUX_LEVEL_3 == RV_YES)
    RvUint8       psuffix[4];         /* OUT - is filled by LC according to its AL.*/
    RvUint8       retransmissionsNum; /* IN  - defines how many retransmissions allowed for this SN */        
#else
    RvUint8       psuffix[2];         /* OUT - is filled by LC according to its AL.*/
#endif
}TRvMuxSdu;

/* Structure for data exchange between user and LC.*/
typedef struct{
    RvUint8   *pbuffer;     /* IN  - a pointer to a data received from demux.*/
    RvUint8   *ppayload;    /* OUT - a pointer to an actual payload.*/
}TRvAlSdu;

/* Data type of LC - AUDIO, CONTROL, etc.*/
typedef RvUint32 RvH223LCDataType;

/* Helper structure for cyclic buffer management.*/
typedef struct{
    RvUint32  readIndex;
    RvUint32  writeIndex;
    RvUint32  usedSize;
}TCyclicParams;

/* Statistics gathering structure for muxer or demux*/
typedef struct 
{
    RvSize_t    entries[16]; /* Number of times each mux entry was used */
    RvSize_t    totalBytes; /* Number of bytes that were handled so far */
    RvSize_t    stuffingBytes; /* Number of bytes that were recognized as stuffing */
    RvSize_t    muxPduCount; /* Number of MUX-PDUs handled so far */
    RvSize_t    muxPduSize; /* Number of bytes in MUX-PDUs handled so far */
} TH223LegStatistics;

/* Statistics gathering structure for a call */
typedef struct 
{
    TH223LegStatistics      mux; /* Muxer statistics */
    TH223LegStatistics      demux; /* Demux statistics */
} TH223Statistics;

/* Definitions of AMR frame types.*/
typedef enum{
    UNKNOWN_AUDIO_TYPE  = -1,
    AMR_4750_TYPE  = 0,
    AMR_5150_TYPE  = 1,
    AMR_5900_TYPE  = 2,
    AMR_6700_TYPE  = 3,
    AMR_7400_TYPE  = 4,
    AMR_7950_TYPE  = 5,
    AMR_1020_TYPE  = 6,
    AMR_1220_TYPE  = 7,
    G723_53_TYPE  = 8,
    G723_63_TYPE  = 9,
    /* AMR WIDEBAND */
    G7222_0660_TYPE,
    G7222_0885_TYPE,
    G7222_1265_TYPE,
    G7222_1425_TYPE,
    G7222_1585_TYPE,
    G7222_1825_TYPE,
    G7222_1985_TYPE,
    G7222_2305_TYPE,
    G7222_2385_TYPE
} EAudioFrameType;

/* Definitions of multiplex level.*/
typedef enum{
    MUX_LEVEL_0 = 0,
    MUX_LEVEL_1,
    MUX_LEVEL_2,
    MUX_LEVEL_3,
    MUX_LEVEL_UNKNOWN
}EMuxLevel;

typedef struct{
    EMuxLevel   muxLevel;
    union{
        RvBool      useOptHdr;              /* Used in level 2 MUX-PDU header.*/
        RvBool      useDoubleFlag;          /* Used in level 1 MUX-PDU framing.*/
    }uoption;
    RvUint32    muxPduPayloadSizeMax;
}TMuxLevelCfg;

/* Definitions of Adaptation layer.*/
typedef enum{
    AL_1_TX = 1,
    AL_1_RX,
    AL_2_TX,
    AL_2_RX,
    AL_3_TX,
    AL_3_RX,
    AL_1M_TX,
    AL_1M_RX,
    AL_2M_TX,
    AL_2M_RX,
    AL_3M_TX,
    AL_3M_RX
}EAL;


/* Definitions of CRC Length*/
typedef enum{
    CRC_NOT_USED = 0,
    CRC_4_BIT = 4,
    CRC_8_BIT = 8,
    CRC_12_BIT = 12,
    CRC_16_BIT = 16,
    CRC_20_BIT = 20,
    CRC_28_BIT = 28,
    CRC_32_BIT = 32
}ECrcLength;

/* Definitions of ARQ type for retransmition*/
typedef enum{
    FEC_ONLY = 0,
    ARQ_I_TYPE,
    ARQ_II_TYPE
}EArqType;

/* Definitions of codes to rx Retransmissions number list*/
typedef enum{
    RTX_NUM_SN_UPDATE = 0,
    RTX_NUM_SN_DELETE,
    RTX_NUM_SN_CHECK
}ERtxNumSnCode;


/* Definitions of AL-PDU extraction results.*/
typedef enum{
    DATA_EXTRACTION_SUCCESS                         = 0x00000000,
    DATA_EXTRACTION_CRC_INVALID                     = 0x00010000,
    DATA_EXTRACTION_SEQUENCE_NUMBER_INVALID         = 0x00020000,
    DATA_EXTRACTION_ERROR_DEMUX                     = 0x00040000,
    DATA_EXTRACTION_USED_FOR_SPDU                   = 0x00080000,
    DATA_EXTRACTION_ERROR_ALPDU_LOST                = 0x00100000,
    DATA_EXTRACTION_ERROR_ALPDU_EMPTY               = 0x00200000,
    DATA_EXTRACTION_ERROR_BUFFER_NOT_RELEASED       = 0x00400000,
    DATA_EXTRACTION_ERROR_UNKNOWN                   = 0x00800000,
	DATA_EXTRACTION_SEBCH_GOLAY_INVALID_CODE		= 0x01000000,
	DATA_EXTRACTION_SPLITTING_IGNORE				= 0x02000000,
	DATA_EXTRACTION_ALSDU_LENGTH_INVALID			= 0x04000000,
	DATA_EXTRACTION_OUT_OF_RESOURCES				= 0x08000000
}EExtractionResult;

#define EXTRACTION_RESULT_IS_SUCCESS(_eResult) (((RvUint32)(_eResult) & 0xffff0000) == 0)

/* Get the sequence number of the demux result */
#define EXTRACTION_RESULT_SEQUENCE_NUMBER(_eResult) ((RvUint16)((RvUint32)(_eResult) & 0x0000ffff))

/* Definition of demux operation results.*/
typedef enum{
    DEMUX_SUCCESS                   = 0x00,
    DEMUX_GOLAY_INVALID             = 0x01,
    DEMUX_NO_USER_BUFFER            = 0x02,
    DEMUX_USER_BUFFER_INSUFFICIENT  = 0x04,
    DEMUX_BUFFER_NOT_RELEASED       = 0x08,
    DEMUX_ERROR_UNKNOWN             = 0x10
}EDemuxResult;

typedef enum{
    CONTROL_RESULT_OK = 0,
    CONTROL_RTX_FAILURE,
    CONTROL_DATA_INVALID
}EControlResult;

typedef enum{
    SPDU_CODE_SREJ = 0x00,
    SPDU_CODE_DRTX = 0xff
}ESpduCode;

typedef enum{
    ALXM_SPDU_CODE_DRTX,        /* S-PDU for ALxM */
    ALXM_SPDU_CODE_SREJ
}EALxMSpduCode;

typedef enum{
    RELEASE_NOT_NEEDED, /* Buffer wasn't actually sent, but got released */
    RELEASE_SENT_AND_NEEDED, /* Buffer was sent, but might be needed for retransmissions */
    RELEASE_SENT_NOT_NEEDED /* Buffer was sent and is no longer needed */
}EReleaseIndicationType;

typedef enum{
    DEMUX_ACP_STATUS_NOT_USED,
    DEMUX_ACP_STATUS_NOT_INITIALIZED,
    DEMUX_ACP_STATUS_AUDIO_LC_INITIALIZED,
    DEMUX_ACP_STATUS_VIDEO_LC_INITIALIZED
}DemuxACPStatus;

/*MPC media types*/
typedef enum
{
    RvH223MonaMPCChannelTypeUNKNOWN = 0,
    RvH223MonaMPCChannelTypeAMR,
    RvH223MonaMPCChannelTypeAMR_WB,
    RvH223MonaMPCChannelTypeH264,
    RvH223MonaMPCChannelTypeMPEG4,
    RvH223MonaMPCChannelTypeH263,
    RvH223MonaMPCChannelTypeLAST
} RvH223MonaMPCChannelType;

/* Callback prototypes.*/
/* Informs the user that the module is empty and ready for termination.*/
typedef void (*RvH223IsClearEv) (IN void *   /* Context.*/
                                 );

/* Informs the user that the data buffer is not in use any more.*/
typedef void (*RvH223ReleaseBufEv) (IN void *,                  /* Context. */
                                    IN RvInt32,                 /*Sub context*/
                                    IN RvUint8 *,               /* Pointer to a buffer. */
                                    IN RvUint32,                /* Size of the buffer. */
                                    IN EReleaseIndicationType /* Type of release indication for the buffer. */
                                    );

/* Gets a free buffer to be filled with incoming data.*/
typedef void (*RvH223GetBufEv) (IN   void *,    /* Context.*/
                                OUT  RvUint8 **,/* Address of a buffer.*/
                                OUT  RvUint32 * /* Maximal size of a buffer.*/
                               );

/* This routine delivers the data to a user. It uses as both MUX-DATA.indication
and MUX-ABORT.indication primitives of H223.*/
typedef void (*RvH223MuxDataIndicationEv) (IN void *,   /* Context.*/
                                           IN RvUint8 *,/* Filled buffer.*/
                                           IN RvUint32, /* Filled size.*/
                                           IN EDemuxResult /* Error.*/
                                          );

/* This routine indicates that we got synchronized on a specific level/parameters
   or that we lost synchronization for some time */
typedef void (*RvH223MuxLevelIndicationEv) (IN void *,          /* Context.*/
                                            IN RvUint8,         /* Bit shift. */
                                            IN TMuxLevelCfg *   /* MUX-LEVEL parameters.*/);

typedef void (*RvH223MONAUpdateAckStatusEv) (IN void *,  /* Context */
                                             IN RvUint8 /* Ack status */);

typedef void (* RvH223MONAPreferenceRcvEv) (
    IN  void *,                /* context */
    IN  RvUint16,              /* mpcRx */
    IN  RvUint16,              /* mpcTx */
    IN  RvUint8 *,             /* *pMsg */
    IN  RvSize_t,              /* msgSize */ 
    IN  RvBool                 /* bAnyError */);

typedef void (* RvH223MONAPreferenceSendEv) (
    IN  void *,                 /* context */
    IN  RvBool                  /* lastMessage */);

typedef void (* RvH223MONAAckStatusChangedEv) (
    IN  void *,                 /* context */
    IN  RvUint8,	            /* prevStatus */
	IN  RvUint8					/* newStatus */);

#if (RV_H223_USE_SPLIT == RV_YES)

/*  Callback function for the H.223 glue.
    This implementation invokes the application's callback that should
    send the H.245 buffer to the H.223 split application.   */
typedef RvStatus (*RvH223GlueSendControlEv) (IN  void *,        /* context */
                                             IN  RvUint8 *,    /* pBuffer */
                                             IN  RvUint32       /* bufferSize */ );

 /* Callback function called when an demux muxtable entry needs to be set.*/
typedef RvStatus (* RvH223GlueDemuxSetMuxtableEntryEv) (IN void * , /* context */
                                                        IN RvUint32, /* muxEntry */
                                                        IN void *, /*atomArray*/
                                                        IN RvUint32    /* arraySize */);

 /* Callback function called when a channel is opened */
typedef RvStatus (* RvH223GlueChannelConstructEv) (
                                                 IN  void *,        /* call context */
                                                 IN  void *,        /* channel context */
                                                 IN  EAL,           /* adaptationLayerLevel */
                                                 IN  RvBool,        /* bIsFramed */
                                                 IN  RvBool,        /* bIsSegmentable */
                                                 IN  RvBool,        /* bUseSequenceNumbering */
                                                 IN  RvInt32,       /* controlFieldSize */
                                                 IN  RvUint16,      /* logicalChannelNumber */
                                                 IN  RvUint16,      /* reverseLogicalChannelNumber */
                                                 IN  RvBool,        /* bIsDuplex */
                                                 IN  RvBool,        /* bIsIncoming */  
                                                 IN  RvH223LCDataType); /* channel data type */
                                                 
 /* Callback function called when a channel is closed */
typedef RvStatus (* RvH223GlueChannelDestructEv) (
                                                 IN  void *,        /* call context */
                                                 IN  void *);        /* channel context */
                                                 
 /* Callback function called when a muxtable should be generated */
typedef RvStatus (* RvH223GlueGenerateMuxtableEv) (
                                                 IN  void *,            /* call context */
                                                 IN  EAudioFrameType,   /* audioType */
                                                 IN  RvUint32,          /* videoBitrate */
                                                 IN  RvUint32,          /* dataBitrate */
                                                 IN  RvBool);           /* enhancedCapability */

 /* Callback function called when a muxtable is clear*/
typedef RvStatus (* RvH223GlueClearMuxtableEv) (
                                                 IN  void *);           /* call context */

 /* Callback function called when a muxtable entry should be added */
typedef RvStatus (* RvH223GlueMuxtableAddEntryEv) (
                                                 IN  void *,            /* call context */
                                                 IN  RvUint32,          /* audioSize */
                                                 IN  RvUint32,          /* video1Size */
                                                 IN  RvUint32,          /* video2Size */
                                                 IN  RvUint32);         /* dataSize */
                                                                        
/* RvH223GlueEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the H.223 Glue callbacks.
 * This structure is used to set the application callbacks in the function
 * RvH223GlueSetEvHandler().
 * They are only applicable when H.223 Split add-on is used.
 */
typedef struct
{
    RvH223GlueSendControlEv            pfnSendControlEv;
    RvH223GlueDemuxSetMuxtableEntryEv  pfnDemuxSetMuxtableEntryEv;
    RvH223GlueChannelConstructEv       pfnChannelConstructEv;
    RvH223GlueChannelDestructEv        pfnChannelDestructEv;
    RvH223GlueMuxtableAddEntryEv       pfnMuxtableAddEntryEv;
    RvH223GlueClearMuxtableEv          pfnClearMuxtableEv;
    RvH223GlueGenerateMuxtableEv       pfnGenerateMuxtableEv;
} RvH223GlueEvHandlers;

#endif /* (RV_H223_USE_SPLIT == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_DEFS_H */
