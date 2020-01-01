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
* @file    _mdl_keypad_private.h
* @version
* @brief   keypad middleware private interface.
*
*/

#ifndef __MDL_KEYPAD_PRIVATE_H__
#define __MDL_KEYPAD_PRIVATE_H__

typedef union{
    VKEYCODE         vcode;
    vm_kbdInd_t      scancode;
} Body_t;
#endif//__MDL_KEYPAD_PRIVATE_H__
