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
* @file    drv_clkgen_cmu_forward.h
* @version
* @brief   Clock Management Unit driver
*
*/

#ifndef __DRV_CLKGEN_CMU_FORWARD_H__
#define __DRV_CLKGEN_CMU_FORWARD_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Data type definition
/*=============================================================*/

opaque_enum(ClkgenResult_e_);
typedef enum ClkgenResult_e_ ClkgenResult_e;
opaque_enum(ClkgenModule_e_);
typedef enum ClkgenModule_e_ ClkgenModule_e;
opaque_enum(ClkgenClkReq_e_);
typedef enum ClkgenClkReq_e_ ClkgenClkReq_e;
opaque_enum(ClkgenClkSpeed_e_);
typedef enum ClkgenClkSpeed_e_ ClkgenClkSpeed_e;
opaque_enum(PeriphType_e_);
typedef enum PeriphType_e_ PeriphType_e;

#endif //__DRV_CLKGEN_CMU_FORWARD_H__

