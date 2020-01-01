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
* @file    drv_serial_flash_pub.h
* @version
* @brief   This file contains the common definition of serial flash driver.
*
*/

#ifndef __DRV_SERIAL_FLASH_PUB_H__
#define __DRV_SERIAL_FLASH_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	SPINOR_26MHz 		= 26,
    SPINOR_48MHz 		= 48,
    SPINOR_54MHz		= 54,
	SPINOR_55MHz		= 55,
	SPINOR_64MHz		= 64,
    SPINOR_77MHz        = 77,
    SPINOR_78MHz 		= 78,
    SPINOR_89MHz 		= 89,
    SPINOR_96MHz		= 96,
    SPINOR_104MHz		= 104,
    SPINOR_128MHz       = 128
} SPINORBusClock_e;

typedef enum
{
	SPINOR_DRIVING00 	= 0,
    SPINOR_DRIVING01 	= 1,
    SPINOR_DRIVING10 	= 2,
    SPINOR_DRIVING11 	= 3
} SPINORDriving_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/


#endif //__DRV_SERIAL_FLASH_PUB_H__

