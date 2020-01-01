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
* @file    srv_hopper_data_type.h
* @version
* @brief
*
*/

#ifndef __SRV_HOPPER_DATA_TYPES_H__
#define __SRV_HOPPER_DATA_TYPES_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define HOPPER_GENERATE_KEY_INTERVAL	     	   	(400)
#define HOPPER_WRITE_BUFFER_SIZE					(32)
#define HOPPER_READ_BUFFER_SIZE						(4)

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct 
{
	u32 tLog;
	/*
	MSB
	31~31: 1 bit  TouchPress
	20~30:11 bits PosX 
	9~20 :11 bits PosY
	8~8  : 1 bit  KeyPress
	0~7  : 8 bits KeyID
	*/
	u32 nSeconds;
} LogInputEvt;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__SRV_HOPPER_DATA_TYPES_H__
