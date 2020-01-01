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
* @file    drv_io_chip_pub_forward.h
* @version
* @brief   Header for High level GPIO interface.
*
*/

#ifndef __DRV_IO_CHIP_PUB_FORWARD_H__
#define __DRV_IO_CHIP_PUB_FORWARD_H__

#ifndef __SDK_SIMULATION__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
opaque_enum(IoChipSignalIndex_e_);
typedef enum IoChipSignalIndex_e_ IoChipSignalIndex_e;

opaque_enum(IoChipPull_e_);
typedef enum IoChipPull_e_ IoChipPull_e;

opaque_enum(IoChipDrive_e_);
typedef enum IoChipDrive_e_ IoChipDrive_e;

opaque_enum(IoChipReleaseOption_e_);
typedef enum IoChipReleaseOption_e_ IoChipReleaseOption_e;

typedef struct IoChipPadInit_t_ IoChipPadInit_t;

typedef struct IoChipSignalMapping_t_ IoChipSignalMapping_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/


#endif // __SDK_SIMULATION__
#endif // __DRV_IO_CHIP_PUB_FORWARD_H__

