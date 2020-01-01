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
* @file    srv_hopper_priv.h
* @version
* @brief
*
*/

#ifndef __SRV_HOPPER_PRIV_H__
#define __SRV_HOPPER_PRIV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_types.ht"
#include "mdl_keypad_pub.h"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "mdl_touch_screen_pub.h"
#include "srv_hopper_data_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#undef MALLOC
#undef FREE
#undef FREEIF
#define MALLOC(size)    MsAllocateCusMem(size)
#define FREE(p)         MsReleaseCusMemoryGlobal(p)
#define FREEIF(p)       if(p != 0) {MsReleaseCusMemoryGlobal((void*)p); p = 0;}


/*=============================================================*/
// Type Declarations
/*=============================================================*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "srv_hopper_message_define__.hi"
} HopperMsg_e;

typedef struct
{
	u8 nMode;
	u16 nRow;
	u16 nCol;
} HopperTouchScreenCoord_t;

typedef struct
{
	const FileMgr_WChar *pStrURL;
	void *pIShell;
} Hopper_NotifyReplay_Req_t;

typedef union
{
	Hopper_NotifyReplay_Req_t Replay;
	VKEYCODE nVCode;
	HopperTouchScreenCoord_t TouchScreenInfo;
	vm_osTimerMsgBody_t HopperTimerMsg;
} vm_msgBody_t;

typedef struct
{
	u16 nTimes; //don't use float for speed
	u8 nKey;
} HopperKeyProbability;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// Variable Declarations
/*=============================================================*/

#endif //__SRV_HOPPER_PRIV_H__
