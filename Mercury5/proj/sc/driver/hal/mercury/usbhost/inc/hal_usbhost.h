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

#ifndef _HAL_USBHOST_H
#define _HAL_USBHOST_H

#define CHIP_MV5
#define CPU_TYPE_ARM_RTK
#define KERNEL_OS_RTK

#define CHIPID_MV5         0xD9
#define USB_LIB_CHIPID     CHIPID_MV5
#define USB_LIB_CHIPNAME   "Mercury5"
#define NUM_OF_ROOT_HUB    2

/* SOC USB IP register base address */
#define OS_BASE_ADDR        0x1f200000
#define _MSTAR_PM_BASE      0x1f000000

#define BASE_UPLL0_SOC      (_MSTAR_PM_BASE+(0x2100*2))
#define BASE_UTMI0_SOC      (_MSTAR_PM_BASE+(0x2200*2))
#define BASE_UHC0_SOC       (_MSTAR_PM_BASE+(0x2500*2))
#define BASE_USBC0_SOC      (_MSTAR_PM_BASE+(0x2400*2))
#define BASE_USBBC0_SOC     (OS_BASE_ADDR+(0x2300*2))
#define E_IRQ_UHC_SOC       (14)
#define E_IRQ_USBC_SOC      (13)
#define _USB_UTMI_DPDM_SWAP_P0	1

#define BASE_UTMI1_SOC      (OS_BASE_ADDR+(0x42900*2))
#define BASE_UHC1_SOC       (OS_BASE_ADDR+(0x43200*2))
#define BASE_USBC1_SOC      (OS_BASE_ADDR+(0x43180*2))
#define BASE_USBBC1_SOC     (OS_BASE_ADDR+(0x43000*2))
#define E_IRQ_UHC1_SOC      (55)
#define E_IRQ_USBC1_SOC     (54)
#define _USB_UTMI_DPDM_SWAP_P1	1


//------ Hardware ECO enable switch ----------------------------------
//---- 1. fix pv2mi bridge mis-behavior, list chip before Kris
//#define ENABLE_PV2MI_BRIDGE_ECO

//---- 2. Reduce EOF1 to 16us for performance imporvement
/* Enlarge EOF1 from 12us to 16us for babble prvention under hub case.
 * However, we keep the "old config name". 20130121
 */
#define ENABLE_16US_EOF1

//---- 3. Enable UTMI 240 as 120 phase
#define ENABLE_UTMI_240_AS_120_PHASE_ECO

//---- 4. Change to 55 interface
#define ENABLE_UTMI_55_INTERFACE

//---- 5. tx/rx reset clock gating cause XIU timeout
#define ENABLE_TX_RX_RESET_CLK_GATING_ECO

//---- 6. Setting PV2MI bridge read/write burst size to minimum
#define _USB_MINI_PV2MI_BURST_SIZE 1

//---- 7. HS connection fail problem (Gate into VFALL state)
#define ENABLE_HS_CONNECTION_FAIL_INTO_VFALL_ECO

//---- 8. Enable UHC Preamble ECO function
#define ENABLE_UHC_PREAMBLE_ECO

//---- 9. Enable HS ISO IN Camera Cornor case ECO function
#define ENABLE_HS_ISO_IN_CORNER_ECO

//---- 10. Don't close RUN bit when device disconnect, default enable after KIWI
//#define ENABLE_UHC_RUN_BIT_ALWAYS_ON_ECO

//---- 11. Port is disabled when device is dosconnected
#if 0 // no chip must apply it, it can't work with RUN_BIT_ALWAYS_ON_ECO
	#define ENABLE_DISCONNECT_PE_CLR_ECO
#endif

//---- 12.
//#define ENABLE_HS_DISCONNECTION_DEBOUNCE_ECO

//---- 13. UHC speed type report should be reset by device disconnection
#define ENABLE_DISCONNECT_SPEED_REPORT_RESET_ECO

//---- 14. Port Change Detect (PCD) is triggered by babble. Pulse trigger will not hang this condition.
/* 1'b0: level trigger
 * 1'b1: one-pulse trigger
 */
#define ENABLE_BABBLE_PCD_ONE_PULSE_TRIGGER_ECO

//---- 15. generation of hhc_reset_u
/* 1'b0: hhc_reset is_u double sync of hhc_reset
 * 1'b1: hhc_reset_u is one-pulse of hhc_reset
 */
#define ENABLE_HC_RESET_FAIL_ECO

//---- 16. Do SRAM clock gating automatically to save power */
//#define ENABLE_SRAM_CLK_GATING_ECO

#endif
