/*
 * wpa_supplicant/hostapd - Default include files
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 *
 * This header file is included into all C files so that commonly used header
 * files can be selected with OS specific ifdef blocks in one place instead of
 * having to have OS/C library specific selection in many files.
 */

#ifndef INCLUDES_H
#define INCLUDES_H

//include OS related header files
#ifdef __MIP_ECOS__
/* Include possible build time configuration before including anything else */
#include "../../platform/M3_ECOS/osl_funTable.h"
#include "../../platform/M3_ECOS/sdk_heap.h"
//#include "comm_funTable.h"
#endif

#include "build_config.h"

#ifdef __ARM_RDK__
#include "kernel.h"
#include "kernel_emi.h"
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#include "hal_io_chip.h"
//#include "hal_mpif.h"
#include "sys_sys.h"
#include "sys_sys_tools.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_flag.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_sys_arm.h"
#include "Osdefs.hc"
#include "srv_filemgr_data_types.h" // for FILEMGR_MAX_FILEPATH_SIZE
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if !defined(__MIP_ECOS__) && !defined(__ARM_RDK__)
#ifndef _WIN32_WCE
#ifndef CONFIG_TI_COMPILER
#include <signal.h>
#include <sys/types.h>
#endif /* CONFIG_TI_COMPILER */
#include <errno.h>
#endif /* _WIN32_WCE */
#include <ctype.h>
#include <time.h>

#ifndef CONFIG_TI_COMPILER
#ifndef _MSC_VER
#include <unistd.h>
#endif /* _MSC_VER */
#endif /* CONFIG_TI_COMPILER */

#ifndef CONFIG_NATIVE_WINDOWS
#ifndef CONFIG_TI_COMPILER
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifndef __vxworks
#ifndef __SYMBIAN32__
#include <sys/uio.h>
#endif /* __SYMBIAN32__ */
#include <sys/time.h>
#endif /* __vxworks */
#endif /* CONFIG_TI_COMPILER */
#endif /* CONFIG_NATIVE_WINDOWS */
#endif

#endif /* INCLUDES_H */
