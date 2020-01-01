////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef _SYS_SLEEP_H_
#define _SYS_SLEEP_H_


/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/*
 * Public System Sleep Interface. Please Don't change prototype!!!
 */
void sys_GotoSleep(void);
void sys_GotoLightSleep(void);

#endif /* _SYS_SLEEP_H_ */
