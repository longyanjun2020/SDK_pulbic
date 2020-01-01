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
* @file    MML_Concurrent.h
* @version
* @brief
*
*/

#ifndef __MML_CONCURRENT_H__
#define __MML_CONCURRENT_H__

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
#include "srv_resmgr_mmlconcurrent_api.h" // Lib release stage1's workaround

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern u16 _g_bConcurrentConflict[][(u32)CONCURRENT_SECTION_NUM];

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** @ingroup      MMLayerManager
*   @brief        Get a copy of the platform capability from the multimedia manager
*
*   @param[in]    pPlatformCapability     Pointer to the buffer to store the platform capability
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlPlatformCapabilityGet
(
    MmlPlatformCapability_t    *pPlatformCapability
);

#ifdef __cplusplus
}
#endif

#endif //__MML_CONCURRENT_H__
