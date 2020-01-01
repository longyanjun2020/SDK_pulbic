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
* @file    srv_resmgr_mmlutility_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLUTILITY_TYPES_H__
#define __SRV_RESMGR_MMLUTILITY_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerUtility
    @brief      Response results
*/
opaque_enum(MmlUtilityResult_e_)
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
	RING_ERROR_RING_LOCKED,

    FILE_GET_FILENAME_BASE = 0x20,
    FILE_GET_FILENAME_SUCCESS = FILE_GET_FILENAME_BASE,
    FILE_GET_FILENAME_ERROR,
    FILE_GET_FILENAME_FORMAT_NOT_SUPPORT,
    FILE_GET_FILENAME_STRUCT_NULL,
    FILE_GET_FILENAME_MEMORY_ALLOC_FAIL,
    FILE_GET_FILENAME_STRUCT_INVALID,

    MODULE_ERROR_PARAMETER_INVALID = 0x0100,
};

/** @ingroup    MMLayerUtility
    @brief      Events
*/
typedef enum
{
    /* Ring buffer */
    RING_EVENT_OPEN = MML_GET_UCGEVENT_BASE(MML_UCGID_UTILITY),
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
opaque_enum(MmlRingOperatingMode_e_)
{
    RING_OPERATINGMODE_CONSUMER = 0,
    RING_OPERATINGMODE_PRODUCER,
    RING_OPERATINGMODE_NUM
};

/** @ingroup    MMLayerUtility
    @brief      Ring buffer callback prototype
    @param      nContactID        Registrant's contact ID
    @param      nUserValue        Interface self-reference
*/
typedef void (*PfnMmlRingCallback)(u32 nContactID, u32 nUserValue);

/** @ingroup    MMLayerUtility
    @brief      Ring buffer callback registration structure
*/
#ifdef __GNUC__
struct __packed MmlRingCallback_t_
#else
__packed struct MmlRingCallback_t_
#endif
{
    u32                    nContactID;
    u32                    nUserValue;
    u32                    pfnRingCallback;
};

/** @ingroup    MMLayerUtility
    @brief      Ring buffer message data
*/
struct MmlRingMessage_t_
{
    MmlUtilityEvent_e     eEvent;
    u32                   nRingHandle;
    s16                   TypMsg; /* Temporary GMI wordaround */
};

/** @ingroup    MMLayerUtility
    @brief      Ring buffer handle
*/
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
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
	u16                  bLocked;
    u32                  nWriteSpaceAvailSize;
    u32                  nReadDataAvailSize;
    u32                  nSemaphore;
    MmlRingCallback_t    tConsumerCallback;
    MmlRingCallback_t    tProducerCallback;
    u8                   nAlignPadding[13];  /* Force to be cache line aligned (32-bytes) */
    u32                  nTailSignature;
} MmlRingHandle_t;

struct MmlRingOpen_t_
{
    u8      *pBuffer;
    u32     nBufferSize;
    u32     nHighWatermark;
    u32     nLowWatermark;
	u32     nSemaphore;
};

struct MmlFileNameInfo_t_
{
    u16 *pPrefix;
    u16 *pDatFilename;
    u16 *pPostfix;
    u16 *pFolderPath;
};

opaque_enum(MmlFileGetFileNameType_e_)
{
    MML_GET_FILE_NAME_CREATE = 0,
    MML_GET_FILE_NAME_SAVE = 1,
};

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLUTILITY_TYPES_H__
