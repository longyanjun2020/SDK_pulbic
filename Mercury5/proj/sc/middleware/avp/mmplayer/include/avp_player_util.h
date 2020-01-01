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


#ifndef PLAYER_UTIL_H
#define PLAYER_UTIL_H

#include <stdint.h>
#include "avp_ms_io.h"

struct cb_io_s;

#define STRINGIFY(x)            #x
#define NAME(x,y)               x ## y
#define NAME_MUX(x,y)           STRINGIFY(x##y)
#define THREAD_NAME(x,y)        NAME_MUX(x,y)
#define ATOM_ID(a,b,c,d)        (((a)<<24)|((b)<<16)|((c)<<8)|(d))
#define CODEC_TYPE_4CC          ATOM_ID

#if defined(__I_SW__)
#  include "sys_sys_isw_uart.h"
#  define _CUSAVP                 (_CUS2 | LEVEL_30)
#  define diag_printf             UartSendTrace
#elif defined(__RTK_OS__)
#  include "sys_vm_dbg.ho"
#  define _CUSAVP                 (_CUS2 | LEVEL_30)
#  define diag_printf(fmt, ...)   vm_dbgTrace(_CUSAVP, fmt, ##__VA_ARGS__)
#elif defined(ECOS)
#  include <cyg/infra/diag.h>
#elif defined(AEONDEV)
#  include "utl.h"
#  define diag_printf             UTL_printf
#else
#  include <stdio.h>
#  define diag_printf             printf
#endif

int MMP_UTL_GetTypeHint(const ms_fnchar *filename);
int MMP_UTL_GetFileType(struct cb_io_s *cbio);

#endif
