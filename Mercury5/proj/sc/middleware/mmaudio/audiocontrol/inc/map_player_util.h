////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file   map_player_util.h
* @version
* @brief
*
*/

#ifndef __MAP_PLAYER_UTIL_H__
#define __MAP_PLAYER_UTIL_H__

#include <stdint.h>
#include "ms_io.h"

#if 1
#if defined(__I_SW__)
#  include "sys_sys_isw_uart.h"
#  define _CUSAUD                (_CUS2 | LEVEL_30)
#  define diag_printf             UartSendTrace
#elif defined(__RTK_OS__)
#  include "sys_vm_dbg.ho"
//#  define _CUSAUD                (_CUS2 | LEVEL_30)
//#  define diag_printf(fmt, ...)   vm_dbgTrace(_CUSAUD, fmt, ##__VA_ARGS__)
#elif defined(ECOS)
#  include <cyg/infra/diag.h>
#elif defined(AEONDEV)
#  include "utl.h"
#  define diag_printf             UTL_printf
#else
#  include <stdio.h>
#  define diag_printf             printf
#endif


MmlAudioFormat_e MAP_UTL_GetFileType(const ms_fnchar *pfilename);
MmlAudioFormat_e MAP_UTL_GetMemType(const u8 *pAudMem, const u32 nMemLen);
#endif
#endif
