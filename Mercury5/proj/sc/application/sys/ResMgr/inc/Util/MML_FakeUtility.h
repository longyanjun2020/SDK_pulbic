////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    MML_FakeUtility.h
* @version
* @brief   This file should sync. to MML_Utility.h for Resource manager UT usage
*
*/

#ifndef __MML_FAKEUTILITY_H__
#define __MML_FAKEUTILITY_H__


#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "PlatformDefines.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MML_RING_HEAD_SIGNATURE     0x1C2D3E4F
#define MML_RING_TAIL_SIGNATURE     0xB6C7D8E9
/*The following defines are copied from MML_Common.h*/
#define MML_DCACHE_ALIGN_SIZE               (32)
#define MML_DCACHE_ALIGN_MASK               (MML_DCACHE_ALIGN_SIZE - 1)
#define MML_DCACHE_ALIGN_CEIL(nSize)        (((u32)(nSize) + MML_DCACHE_ALIGN_MASK) & (~MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_FLOOR(nSize)       ((u32)(nSize) & (~MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_CEIL_D(nSize)      ((((u32)(nSize) + MML_DCACHE_ALIGN_MASK) & MML_DCACHE_ALIGN_MASK) ^ (MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_FLOOR_D(nSize)     ((u32)(nSize) & MML_DCACHE_ALIGN_MASK)
/*The following defines are faked for RM UT*/
#define MML_SEM_CONSUME(_X_)
#define MML_SEM_PRODUCE(_X_)
#define MML_MALLOC(Type_t, nSize)           ((Type_t *)GRM_MALLOC(nSize))
#define MML_MFREE(pMem)                     GRM_MFREE(pMem)
#define MML_TRACE                           GRM_TRACE
#define MML_TRC_NORM                        _GRM
/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerUtility
    @brief      Response results
*/
typedef enum
{
    RING_ERROR_SUCCESS = 0,
    RING_ERROR_WATERMARK_INVALIDE,
    RING_ERROR_PARAMETER_INVALID,
    RING_ERROR_ADDRESS_MISALIGNMENT,
    RING_ERROR_SIZE_MISALIGNMENT,
    RING_ERROR_BUFFER_INSUFFICIENT,
    RING_ERROR_HANDLE_INVALIDE,
    RING_ERROR_ADVANCESIZE_OVERRUN,
    RING_ERROR_CALLBACK_INVALID,
    RING_ERROR_OPERATION_UNSUPPORTED,
    RING_ERROR_MEMORY_FAILURE,
	RING_ERROR_REENTRY_NOTALLOWED,

    FILE_GET_FILENAME_BASE = 0x20,
    FILE_GET_FILENAME_SUCCESS = FILE_GET_FILENAME_BASE,
    FILE_GET_FILENAME_ERROR,
    FILE_GET_FILENAME_FORMAT_NOT_SUPPORT,
    FILE_GET_FILENAME_STRUCT_NULL,
    FILE_GET_FILENAME_MEMORY_ALLOC_FAIL,
    FILE_GET_FILENAME_STRUCT_INVALID,
} MmlUtilityResult_e;

/** @ingroup    MMLayerUtility
    @brief      Events
*/
typedef enum
{
    /* Ring buffer */
    RING_EVENT_OPEN = 0,
    RING_EVENT_OPEN_READY,
	RING_EVENT_RESET,
	RING_EVENT_RESET_READY,
    RING_EVENT_CLOSE,
    RING_EVENT_CLOSE_READY,
    RING_EVENT_REACH_HIGH_WATERMARK,
	RING_EVENT_REACH_LOW_WATERMARK,
} MmlUtilityEvent_e;

/** @ingroup    MMLayerUtility
    @brief      Ring buffer operating modes
*/
typedef  enum
{
    RING_OPERATINGMODE_CONSUMER = 0,
    RING_OPERATINGMODE_PRODUCER,
    RING_OPERATINGMODE_NUM
} MmlRingOperatingMode_e;

/** @ingroup    MMLayerUtility
    @brief      Ring buffer callback prototype
    @param      nContactID        Registrant's contact ID
    @param      nUserValue        Interface self-reference
*/
typedef void (*PfnMmlRingCallback)(u32 nContactID, u32 nUserValue);

/** @ingroup    MMLayerUtility
    @brief      Ring buffer callback registration structure
*/
typedef __packed struct
{
    u32                    nContactID;
    u32                    nUserValue;
    u32                    pfnRingCallback;
} MmlRingCallback_t;

/** @ingroup    MMLayerUtility
    @brief      Ring buffer message data
*/
typedef struct
{
    MmlUtilityEvent_e     eEvent;
    u32                   nRingHandle;
    s16                   TypMsg; /* Temporary GMI wordaround */
} MmlRingMessage_t;

/** @ingroup    MMLayerUtility
    @brief      Ring buffer handle
*/
typedef __packed struct
{
    u32                  nHeadSignature;
    u16                  nAlignOffset;
    u32                  pBuffer;
    u32 	             nBufferSize;
    u32                  nReadDataSize;
    u32                  nWriteOffset;
    u32                  nReadOffset;
    u32                  nWriteCount;
    u32                  nReadCount;
    u32                  nHighWatermark;
    u32                  nLowWatermark;
    u16                  bHighWatermarkLock;
    u16                  bLowWatermarkLock;
    u16                  bBufferFull;
    u16                  bBufferEmpty;
	u16                  bReentry;
    u16                  bDataEnd;
    u32                  nWriteSpaceAvailSize;
    u32                  nReadDataAvailSize;
    u32                  nSemaphore;
    MmlRingCallback_t    tConsumerCallback;
    MmlRingCallback_t    tProducerCallback;
    u8                   nAlignPadding[15];  /* Force to be cache line aligned (32-bytes) */
    u32                  nTailSignature;
} MmlRingHandle_t;

typedef struct
{
    u8      *pBuffer;
    u32     nBufferSize;
    u32     nHighWatermark;
    u32     nLowWatermark;
	u32     nSemaphore;
} MmlRingOpen_t;

typedef struct
{
    u16 *pPrefix;
    u16 *pDatFilename;
    u16 *pPostfix;
    u16 *pFolderPath;
} MmlFileNameInfo_t;

typedef enum
{
    MML_GET_FILE_NAME_CREATE = 0,
    MML_GET_FILE_NAME_DELETE = 1,
} MmlFileGetFileNameType_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MmlUtilityResult_e MmlRingOpen
(
    MmlRingOpen_t     tOpen,
    u32               *pHandle
);

MmlUtilityResult_e MmlRingClose
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingWriteSpaceSizeGet
(
    u32     nHandle,
    u32     *pWriteSpaceSize
);

MmlUtilityResult_e MmlRingReadDataSizeGet
(
    u32     nHandle,
    u32     *pReadDataSize
);

MmlUtilityResult_e MmlRingWriteInfoGet
(
    u32     nHandle,
    u32     *pWritePoint,
    u32     *pWriteSpaceAvailSize
);

MmlUtilityResult_e MmlRingReadInfoGet
(
    u32     nHandle,
    u32     *pReadPoint,
    u32     *pReadDataAvailSize
);

MmlUtilityResult_e MmlRingWriteAdvance
(
    u32     nHandle,
    u32     nWriteSize
);

MmlUtilityResult_e MmlRingReadAdvance
(
    u32     nHandle,
    u32     nReadSize
);

MmlUtilityResult_e MmlRingReset
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingCallbackAttach
(
    u32                         nHandle,
    MmlRingOperatingMode_e      eOperatingMode,
    MmlRingCallback_t           tCallback
);

MmlUtilityResult_e MmlRingPrint
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingWatermarkNotifyDisable
(
    u32                        nHandle,
    MmlRingOperatingMode_e     eOperatingMode
);

MmlUtilityResult_e MmlRingWatermarkNotifyEnable
(
    u32                        nHandle,
    MmlRingOperatingMode_e     eOperatingMode
);

MmlUtilityResult_e MmlRingDataEndFlagSet
(
    u32     nHandle,
    bool    bDataEndFlag
);

MmlUtilityResult_e MmlRingDataEndFlagGet
(
    u32     nHandle,
    bool    *bDataEnd
);

#endif //__MML_UTILITY_H__
