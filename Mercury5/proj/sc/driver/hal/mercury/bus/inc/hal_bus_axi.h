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
 * @file    hal_bus_axi.h
 * @version
 * @brief   HAL header for AXI bus
 *
 */

#ifndef __HAL_BUS_AXI_H__
#define __HAL_BUS_AXI_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "kernel_axi.h"


//#include "kernel.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define HAL_FLUSH_MIU_PIPE() \
    do \
    { \
        g_ptKeInfinityAxi->reg_flush_op_on_fire = 0x0; \
        g_ptKeInfinityAxi->reg_flush_op_on_fire = 0x1; \
    } while(0)

#define HAL_GET_MIU_PIPE_STATUS() (g_ptKeInfinityAxi->reg_dummy50_ro & L3_FLUSH_STATUS)

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
void HalAxiChipFlushMiuPipe(void);


#endif //__HAL_BUS_AXI_H__
