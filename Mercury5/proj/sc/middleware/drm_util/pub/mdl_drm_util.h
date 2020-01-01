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
* @file    mdl_drm_utiil.h
* @version
* @brief   This file defines drm utilities
*
*/

#ifndef __MDL_DRM_UTIL_H__
#define __MDL_DRM_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_drm_util_def.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

//DCF Parser
s32 MdlDrmUtilSyncRead_DCF(void *pStream, u32 nStreamSize, MDL_DRM_ContentField_DCF_t *pDCFData ,u32 *pReadLen);
void MdlDrmUtil_Free_DCF(MDL_DRM_ContentField_DCF_t *pDCFData);

//AES 128 codec(ECB/CBC)
void MdlDrmUtil_AES128Init(u8 *pKey, AES_HANDLE **ppAesHandle);
s32 MdlDrmUtil_AES128Encrypt(AES_HANDLE *pAesHandle, AES_ENCRYPT_PARAMS *pEncParams);
void MdlDrmUtil_AES128Close(AES_HANDLE *pAesHandle);

#endif /* __MDL_DRM_UTIL_PUB_H__ */


