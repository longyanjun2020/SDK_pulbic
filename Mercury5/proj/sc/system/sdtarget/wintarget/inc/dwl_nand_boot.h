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
* @file    dwl_nand_boot.h
* @version
* @brief   header file for booting from NAND after download
*
*/

#ifndef __DWL_NAND_BOOT_H__
#define __DWL_NAND_BOOT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#ifdef __DWL_NAND_BOOT_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

/*=============================================================*/
// Function prototype
/*=============================================================*/

INTERFACE bool dwl_BootFromNAND(void);


#undef INTERFACE

#endif

