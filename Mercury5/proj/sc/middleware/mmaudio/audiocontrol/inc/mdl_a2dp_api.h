////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
* @file   mdl_a2dp_api.h
* @version
* @brief
*
*/

#ifndef __MDL_A2DP_API_H__
#define __MDL_A2DP_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_MsWrapper_cus_os_sem.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MDL_A2DP_REENTRY_LOCK                   MsConsumeSem(A2DP_REENTRY_LOCK_SEM)
#define MDL_A2DP_REENTRY_UNLOCK                 MsProduceSem(A2DP_REENTRY_LOCK_SEM)
#define MDL_A2DP_SYNC_BLOCK                     MsConsumeSem(A2DP_SYNC_SEM)
#define MDL_A2DP_SYNC_UNBLOCK                   MsProduceSem(A2DP_SYNC_SEM)

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines the return code of the A2DP interface
 */
typedef enum
{
    MDL_A2DP_OK = 0,             /**< Function complete successfully */
    MDL_A2DP_FAIL,               /**< Function common fail */
    MDL_A2DP_PARAM_ERROR,        /**< The input parameter is wrong */
    MDL_A2DP_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
    MDL_A2DP_REJECT,             /**< Request rejected because of other function's confliction */
    MDL_A2DP_ABORT,              /**< Request aborted because of incorrect sequence */
    MDL_A2DP_TIMEOUT             /**< Request no response timeout, this error is returned by call back function */
} MdlA2dpErrCode_e;


/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
MdlA2dpErrCode_e MdlA2dpOpenReq(u32 nSampleRate, u32 nChannel);
MdlA2dpErrCode_e MdlA2dpPlayReq(void);
MdlA2dpErrCode_e MdlA2dpStopReq(void);
MdlA2dpErrCode_e MdlA2dpPlayEndReq(void);
MdlA2dpErrCode_e MdlA2dpPauseReq(void);
MdlA2dpErrCode_e MdlA2dpResumeReq(void);
MdlA2dpErrCode_e MdlA2dpSetPositionReq(void);
MdlA2dpErrCode_e MdlA2dpCloseReq(void);

s32 MdlA2dpPcmWriteReq(u8 *pBuffer, u32 u32Len, u32 timestamp);
void MdlA2dpPlayGetBufInfoReq(u32 *pnDataSize);
void MdlA2dpRecGetBufInfoReq(u32 *pnDataSize);
void MdlA2dpGetRingBufInfoReq(u32 *pnDataSize);
void MdlA2dpDmaResetReq(void);
void MdlA2dpGetRingSampleNumReq(u32 *pnDataSize);

#endif
