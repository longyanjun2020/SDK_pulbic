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
* @file    mcu2mmp_irq_ctrl_pub_forward.h
* @version
* @brief   System interrupt controller (INTC) header file
*
*/
#if defined (__UPGRADE_SHARE_MEMORY__)
#ifndef __MCU2MMP_IRQ_CTRL_PUB_FORWARD_H__
#define __MCU2MMP_IRQ_CTRL_PUB_FORWARD_H__

#include "vm_types.ht"

/** CSQ data type */
typedef struct AtCsqData_ AtCsqData;

/** CREG data type */
typedef struct AtCregData_ AtCregData;

/** CGREG data type */
typedef struct AtCgregData_ AtCgregData;

/** Command Type */
opaque_enum(CmdType_);
typedef enum CmdType_ CmdType;

/** AT data*/
typedef union UnionAtData_ UnionAtData;

/* Data and Type*/
typedef struct AtDataType_ AtDataType;

#endif // __MCU2MMP_IRQ_CTRL_PUB_FORWARD_H__

#endif /*__UPGRADE_SHARE_MEMORY__*/

