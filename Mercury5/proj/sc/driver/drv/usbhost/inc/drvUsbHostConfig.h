//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#ifndef DRV_USBHOST_CONFIG_H
#define DRV_USBHOST_CONFIG_H

#include <drvUSB_rtk.h>

#define ECOS_USB_HOST_LOCAL_VER "20171212-rtos"

#define URB_TIMEOUT_BY_WAIT_EVENT

//#define USB_EHCI_TT

#define ECOS_XHC_COMPANION_SUPPORT

//#define ENABLE_LEGACY_CACHE_SETTING

#define ENABLE_DISCONNECT_FAST_RESPONSE

/* 20140630 quick response for file read/write root hub disconnected */
#define ENABLE_RW_DISCONNECTING

#define ENABLE_ROOTHUB_DISCONN_REINIT

/* 20140715 maximum hub top level to restric hub_probe */
#ifdef USB_NOT_SUPPORT_EX_HUB
#define MAX_HUB_TOPO_LEVEL 1
#else
#define MAX_HUB_TOPO_LEVEL 6
#endif

/* 20170504 ATA command pass through support */
#define ENABLE_ATA_COMMAND_PASS_THROUGH

/* 20170313 isochronous pipe */
#define ENABLE_EHCI_ISOC_PIPE

/* 20170313 isochronous pipe to do */
//#define ENABLE_DESC_INTF_ASSOC

/* 20171211 usb physical reset method */
#define ENABLE_PHYSICAL_RESET_LOGIC_MODE

/*** Definition by chip attribute ***/
#define MIPS_L1_CACHE_SIZE 32

#ifdef ENABLE_LEGACY_CACHE_SETTING
#define CPU_L1_CACHE_BOUND (15)
#else
#define CPU_L1_CACHE_BOUND (MIPS_L1_CACHE_SIZE-1)
#endif

#define BASE_USBBC_NULL     (0)

/* define UHC port enable */
/* two ports is default, else extra needs to be defined */

//------ Software patch enable switch ----------------------------------
//---- 1. Monkey Test software Patch
#define _USB_HS_CUR_DRIVE_DM_ALLWAYS_HIGH_PATCH    0

//---- 2. Clock phase adjustment software Patch
#define _USB_CLOCK_PHASE_ADJ_PATCH    0

//---- 3. enabe PVCI i_miwcplt wait for mi2uh_last_done_z
#define _USB_MIU_WRITE_WAIT_LAST_DONE_Z_PATCH    1

//---- 4. data structure (qtd ,...) must be 128-byte aligment
#define _USB_128_ALIGMENT 1

//---- 5. OBF application should enable BDMA function to move QH head

//---- 6. Embeded Host Electric Test software Patch
#define EHSTST_TEST_PACKET_UTMI10    0x0078

//-----------------------------------------
// U4_series_usb_init flag:
// Use low word as flag
#define EHCFLAG_NONE             0x0
#define EHCFLAG_DPDM_SWAP        0x1
#define EHCFLAG_TESTPKG          0x2
#define EHCFLAG_DOUBLE_DATARATE  0x4
#define EHCFLAG_USBBC_OFF        0x8
#define EHCFLAF_XHC_COMP         0x10
#define EHCFLAG_ENABLE_OTG       0x20
#define EHCFLAG_USBBC_ID_CUR     0x40

// Use high word as data
#define EHCFLAG_DDR_MASK     0xF0000000
#define EHCFLAG_DDR_x15      0x10000000 //480MHz x1.5
#define EHCFLAG_DDR_x18      0x20000000 //480MHz x1.8
//-----------------------------------------
/* USB port 0 UTMI flag */
#if USB_OTG_SWITCH_SUPPORT
#define _EHCFLAG_P0 (EHCFLAG_USBBC_OFF | EHCFLAG_ENABLE_OTG  | EHCFLAG_USBBC_ID_CUR)
#else
#define _EHCFLAG_P0 (EHCFLAG_USBBC_OFF | EHCFLAG_USBBC_ID_CUR)
#endif
#if _USB_UTMI_DPDM_SWAP_P0
#define EHCFLAG_P0_SOC (_EHCFLAG_P0 | EHCFLAG_DPDM_SWAP)
#else
#define EHCFLAG_P0_SOC _EHCFLAG_P0
#endif

/* USB port 1 UTMI flag */
#define _EHCFLAG_P1 (EHCFLAG_USBBC_OFF  | EHCFLAG_USBBC_ID_CUR)

#if _USB_UTMI_DPDM_SWAP_P1
#define EHCFLAG_P1_SOC (_EHCFLAG_P1 | EHCFLAG_DPDM_SWAP)
#else
#define EHCFLAG_P1_SOC _EHCFLAG_P1
#endif

#define HUB_STACK_SIZE  0x2000

#ifndef MSTAR_USB_DEBUG
#define MSTAR_USB_DEBUG                  0
#endif

/* Debug level print definition */
//#define DBG_MSG
//#define DBG_WARN
//#define DBG_FUNC
//#define DBG_DEBUG
#define DBG_ERR

#undef  ms_debug_msg
#undef  ms_debug_warn
#undef  ms_debug_err
#undef  ms_debug_func
#undef  ms_debug_debug

#ifdef DBG_MSG
#define ms_debug_msg(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_debug_msg(fmt, arg...) do {} while (0)
#endif

#ifdef DBG_DEBUG
#define ms_debug_debug(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_debug_debug(fmt, arg...) do {} while (0)
#endif

#ifdef DBG_WARN
#define ms_debug_warn(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_debug_warn(fmt, arg...) do {} while (0)
#endif

#ifdef DBG_ERR
#define ms_debug_err(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_debug_err(fmt, arg...) do {} while (0)
#endif

#ifdef DBG_FUNC
#define ms_debug_func(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_debug_func(fmt, arg...) do {} while (0)
#endif

#define ms_usbhost_msg ms_debug_msg
#define ms_usbhost_warn ms_debug_warn
#define ms_usbhost_debug ms_debug_debug
#define ms_usbhost_dbg ms_debug_debug
#define ms_usbhost_err ms_debug_err
#define ms_debug_dbg ms_debug_debug

//------ UTMI:FL_XCVR_TEST  
//0x0022_14[3] FL_XCVR_TEST  1b0:HV, 1b1:LV
#define UTMI_DISCON_LEVEL_28	(0x08)

//------ UTMI disconnect level parameters ---------------------------------
// 0x00: 550mv, 0x20: 575, 0x40: 600, 0x60: 625
// squelch: bit[3:0] 4'b0010 => 100mv
#define UTMI_DISCON_LEVEL_2A	(0x60 | 0x02)

//------ UTMI eye diagram parameters ---------------------------------
/* Eye pattern setting */
#define ENABLE_EYE_PATTERN_SETTING 1

#if defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 7)
	// for 40nm after Agate, use 55nm setting7
	#define UTMI_EYE_SETTING_2C     (0x90)
	#define UTMI_EYE_SETTING_2D     (0x03)
	#define UTMI_EYE_SETTING_2E     (0x30)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 6)
	// for 40nm after Agate, use 55nm setting6
	#define UTMI_EYE_SETTING_2C     (0x10)
	#define UTMI_EYE_SETTING_2D     (0x03)
	#define UTMI_EYE_SETTING_2E     (0x30)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 5)
	// for 40nm after Agate, use 55nm setting5
	#define UTMI_EYE_SETTING_2C     (0x90)
	#define UTMI_EYE_SETTING_2D     (0x02)
	#define UTMI_EYE_SETTING_2E     (0x30)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 4)
	// for 40nm after Agate, use 55nm setting4
	#define UTMI_EYE_SETTING_2C     (0x90)
	#define UTMI_EYE_SETTING_2D     (0x03)
	#define UTMI_EYE_SETTING_2E     (0x00)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 3)
	// for 40nm after Agate, use 55nm setting3
	#define UTMI_EYE_SETTING_2C     (0x10)
	#define UTMI_EYE_SETTING_2D     (0x03)
	#define UTMI_EYE_SETTING_2E     (0x00)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 2)
	// for 40nm after Agate, use 55nm setting2
	#define UTMI_EYE_SETTING_2C     (0x90)
	#define UTMI_EYE_SETTING_2D     (0x02)
	#define UTMI_EYE_SETTING_2E     (0x00)
	#define UTMI_EYE_SETTING_2F     (0x81)
#elif defined(ENABLE_EYE_PATTERN_SETTING) && (ENABLE_EYE_PATTERN_SETTING == 1)
	// for 40nm after Agate, use 55nm setting1, the default
	#define UTMI_EYE_SETTING_2C     (0x10)
	#define UTMI_EYE_SETTING_2D     (0x02)
	#define UTMI_EYE_SETTING_2E     (0x00)
	#define UTMI_EYE_SETTING_2F     (0x81)
#else
	// for 40nm
	#define UTMI_EYE_SETTING_2C     (0x98)
	#define UTMI_EYE_SETTING_2D     (0x02)
	#define UTMI_EYE_SETTING_2E     (0x10)
	#define UTMI_EYE_SETTING_2F     (0x01)
#endif

#endif
