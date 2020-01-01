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
* @file    drv_riu_sw_irq_pub_api.h
* @version
* @brief   Riu Software interrupt
*
* This interrupt is used for external tool (ex. dbtool) to issue an interrupt to
* trap the CPU. The CPU will keep in an infinite loop without accessing the AHB, so
* the external tool can check and modify the content on AHB. After that, another
* interrupt will release CPU and let it execute from original break position.
*/
#ifndef __DRV_RIU_SW_IRQ_PUB_API_H__
#define __DRV_RIU_SW_IRQ_PUB_API_H__

/*=============================================================*/
// Global function prototype
/*=============================================================*/

void DrvRiuSwInterruptInit(void);

#endif // __DRV_RIU_SW_IRQ_PUB_API_H__

