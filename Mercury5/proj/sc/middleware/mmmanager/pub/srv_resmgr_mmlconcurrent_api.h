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
* @file    srv_resmgr_mmlconcurrent_api.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLCONCURRENT_API_H__
#define __SRV_RESMGR_MMLCONCURRENT_API_H__

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
#include "srv_resmgr_mmlconcurrent_types.h"

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

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Get the info of which chip type is used
*
*   @param[in]    pPlatformChipType       Pointer to a variable to store the chip type info
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
/*
MmlErrCode_e MmlPlatformChipTypeGet
(
    MmlPlatformChipType_e    *pPlatformChipType
);
*/

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Set the platform capabilities
*
*   @retval       MML_ERROR_SUCCESS    Succeed
*   @endcond
*/
MmlErrCode_e MmlPlatformCapabilitySet(void);

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLCONCURRENT_API_H__
