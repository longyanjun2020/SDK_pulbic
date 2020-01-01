////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
 * @file drv_emi_pub.h
 * @brief SRAM/NOR driver public interface
 */

#ifndef __DRV_EMI_PUB_H__
#define __DRV_EMI_PUB_H__

#include "vm_types.ht"

/**
 * @brief Error Code for emi procedures
 */
typedef enum
{
    RET_EMI_SUCCESS = 0,            ///< Process is done, nothing wrong
    RET_EMI_INVALID_PARAMETER,      ///< Pass invalid paramater
    RET_EMI_SPEED_NOT_SUPPORTED,    ///< clock speed is not supported
} EmiErrorCode_e;

/**
 * @brief This function configures EMI
 */
EmiErrorCode_e DrvEmiInitEmi(void);
EmiErrorCode_e DrvEmi_EnableDMC_CLKGating(u8 u8Enable);

#endif // __DRV_EMI_PUB_H__
