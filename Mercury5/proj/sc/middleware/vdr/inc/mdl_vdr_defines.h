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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_defines.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_DEFINES_H__
#define __MDL_VDR_DEFINES_H__
#include "mdl_vdr_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------
#define VDR_MALLOC(Type_t, nSize)                       ((Type_t *)vdr_DynamicAlloc(nSize))
#define VDR_MFREE(pMem)                                     vdr_DynamicFree((void **)&pMem)
#define VDR_MEMSET(pMem, nVal, nSize)               memset(pMem, nVal, nSize)
#define VDR_MEMCPY(pDst, pSrc, nSize)                   memcpy(pDst, pSrc, nSize)
#define VDR_MEMCMP(pMem1, pMem2, nSize)         memcmp(pMem1, pMem2, nSize)

#define VDR_SENDMSG(eMailbox, pMsg)                 MsSend(eMailbox, pMsg)

/*
 * File <big2m3-flashBoot.ecc>
 */
#define CYGHWR_HAL_MIPS_MSTAR_SDRAM_ENABLE          1
#define CYGHWR_BIG2_TYPE_A                          0
#define VIDEO_REC_D1_EN                             0


/*
 * File <pkgconf/app_shell.h>
 *
 * This file is generated automatically by the configuration
 * system. It should not be edited. Any changes to this file
 * may be overwritten.
 */

#define SManager_Shared_Data_Memory 1
#define H263_DRIVER 1
#define MP4_RECORDER 1
#define MP4REC_PLUGIN_EN 1


/*
 * File <pkgconf/system.h>
 *
 * This file is generated automatically by the configuration
 * system. It should not be edited. Any changes to this file
 * may be overwritten.
 */

#define CYGHWR_HAL_MIPS_MSTAR_SDRAM_ENABLE 1


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------


#endif // __MDL_VDR_DEFINES_H__

