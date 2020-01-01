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

#ifndef _HAL_IRQTBL_H_
#define _HAL_IRQTBL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define E_INT_RESERVED                  E_INT_IRQ_FIQ_NONE

#if defined(MSOS_TYPE_LINUX)
#ifdef CHIP_INT_SPI_MODE
#define CONFIG_IRQL_BASE_ADDRESS        0x00
#define CONFIG_IRQH_BASE_ADDRESS        0x10
#define CONFIG_IRQEXPL_BASE_ADDRESS     0x20
#define CONFIG_IRQEXPH_BASE_ADDRESS     0x30
#define CONFIG_FIQL_BASE_ADDRESS        0x40
#define CONFIG_FIQH_BASE_ADDRESS        0x50
#define CONFIG_FIQEXPL_BASE_ADDRESS     0x60
#define CONFIG_FIQEXPH_BASE_ADDRESS     0x70
#define CONFIG_IRQHYPL_BASE_ADDRESS     0x80
#define CONFIG_IRQHYPH_BASE_ADDRESS     0x90
#define CONFIG_IRQSUPL_BASE_ADDRESS     0xA0
#define CONFIG_IRQSUPH_BASE_ADDRESS     0xB0
#define CONFIG_FIQHYPL_BASE_ADDRESS     0xC0
#define CONFIG_FIQHYPH_BASE_ADDRESS     0xD0
#define CONFIG_FIQHYPL_BASE_ADDRESS     0xE0
#define CONFIG_FIQSUPL_BASE_ADDRESS     0xF0
#else
#define CONFIG_FIQL_BASE_ADDRESS        0x00
#define CONFIG_FIQH_BASE_ADDRESS        0x10
#define CONFIG_FIQEXPL_BASE_ADDRESS     0x20
#define CONFIG_FIQEXPH_BASE_ADDRESS     0x30
#define CONFIG_IRQL_BASE_ADDRESS        0x40
#define CONFIG_IRQH_BASE_ADDRESS        0x50
#define CONFIG_IRQEXPL_BASE_ADDRESS     0x60
#define CONFIG_IRQEXPH_BASE_ADDRESS     0x70
#define CONFIG_FIQHYPL_BASE_ADDRESS     0x80
#define CONFIG_FIQHYPH_BASE_ADDRESS     0x90
#define CONFIG_FIQSUPL_BASE_ADDRESS     0xA0
#define CONFIG_FIQSUPH_BASE_ADDRESS     0xB0
#define CONFIG_IRQHYPL_BASE_ADDRESS     0xC0
#define CONFIG_IRQHYPH_BASE_ADDRESS     0xD0
#define CONFIG_IRQSUPL_BASE_ADDRESS     0xE0
#define CONFIG_IRQSUPH_BASE_ADDRESS     0xF0
#endif

#elif defined(MSOS_TYPE_NOS) || defined(MSOS_TYPE_UCOS)
#define CONFIG_IRQL_BASE_ADDRESS        0x00
#define CONFIG_IRQH_BASE_ADDRESS        0x10
#define CONFIG_FIQL_BASE_ADDRESS        0x20
#define CONFIG_FIQH_BASE_ADDRESS        0x30
#define CONFIG_IRQEXPL_BASE_ADDRESS     0x40
#define CONFIG_IRQEXPH_BASE_ADDRESS     0x50
#define CONFIG_FIQEXPL_BASE_ADDRESS     0x60
#define CONFIG_FIQEXPH_BASE_ADDRESS     0x70
#define CONFIG_IRQHYPL_BASE_ADDRESS     0x80
#define CONFIG_IRQHYPH_BASE_ADDRESS     0x90
#define CONFIG_FIQHYPL_BASE_ADDRESS     0xA0
#define CONFIG_FIQHYPH_BASE_ADDRESS     0xB0
#define CONFIG_IRQSUPL_BASE_ADDRESS     0xC0
#define CONFIG_IRQSUPH_BASE_ADDRESS     0xD0
#define CONFIG_FIQSUPL_BASE_ADDRESS     0xE0
#define CONFIG_FIQSUPH_BASE_ADDRESS     0xF0

#elif defined(MSOS_TYPE_ECOS)
#define CONFIG_FIQL_BASE_ADDRESS        0x00
#define CONFIG_FIQH_BASE_ADDRESS        0x10
#define CONFIG_FIQEXPL_BASE_ADDRESS     0x20
#define CONFIG_FIQEXPH_BASE_ADDRESS     0x30
#define CONFIG_IRQL_BASE_ADDRESS        0x40
#define CONFIG_IRQH_BASE_ADDRESS        0x50
#define CONFIG_IRQEXPL_BASE_ADDRESS     0x60
#define CONFIG_IRQEXPH_BASE_ADDRESS     0x70
#define CONFIG_FIQHYPL_BASE_ADDRESS     0x80
#define CONFIG_FIQHYPH_BASE_ADDRESS     0x90
#define CONFIG_FIQSUPL_BASE_ADDRESS     0xA0
#define CONFIG_FIQSUPH_BASE_ADDRESS     0xB0
#define CONFIG_IRQHYPL_BASE_ADDRESS     0xC0
#define CONFIG_IRQHYPH_BASE_ADDRESS     0xD0
#define CONFIG_IRQSUPL_BASE_ADDRESS     0xE0
#define CONFIG_IRQSUPH_BASE_ADDRESS     0xF0


#elif defined(MSOS_TYPE_NUTTX)
#define CONFIG_IRQL_BASE_ADDRESS        0x00
#define CONFIG_IRQH_BASE_ADDRESS        0x10
#define CONFIG_FIQL_BASE_ADDRESS        0x20
#define CONFIG_FIQH_BASE_ADDRESS        0x30
#define CONFIG_IRQEXPL_BASE_ADDRESS     0x40
#define CONFIG_IRQEXPH_BASE_ADDRESS     0x50
#define CONFIG_FIQEXPL_BASE_ADDRESS     0x60
#define CONFIG_FIQEXPH_BASE_ADDRESS     0x70
#define CONFIG_IRQHYPL_BASE_ADDRESS     0x80
#define CONFIG_IRQHYPH_BASE_ADDRESS     0x90
#define CONFIG_FIQHYPL_BASE_ADDRESS     0xA0
#define CONFIG_FIQHYPH_BASE_ADDRESS     0xB0
#define CONFIG_IRQSUPL_BASE_ADDRESS     0xC0
#define CONFIG_IRQSUPH_BASE_ADDRESS     0xD0
#define CONFIG_FIQSUPL_BASE_ADDRESS     0xE0
#define CONFIG_FIQSUPH_BASE_ADDRESS     0xF0
#else
#error "Unknown Platform Selection"
#endif

typedef enum
{
    E_IRQL_START                = CONFIG_IRQL_BASE_ADDRESS,
    E_IRQ_00                    = E_IRQL_START + 0,
    E_IRQ_01                    = E_IRQL_START + 1,
    E_IRQ_02                    = E_IRQL_START + 2,
    E_IRQ_03                    = E_IRQL_START + 3,
    E_IRQ_04                    = E_IRQL_START + 4,
    E_IRQ_05                    = E_IRQL_START + 5,
    E_IRQ_06                    = E_IRQL_START + 6,
    E_IRQ_07                    = E_IRQL_START + 7,
    E_IRQ_08                    = E_IRQL_START + 8,
    E_IRQ_09                    = E_IRQL_START + 9,
    E_IRQ_10                    = E_IRQL_START + 10,
    E_IRQ_11                    = E_IRQL_START + 11,
    E_IRQ_12                    = E_IRQL_START + 12,
    E_IRQ_13                    = E_IRQL_START + 13,
    E_IRQ_14                    = E_IRQL_START + 14,
    E_IRQ_15                    = E_IRQL_START + 15,
    E_IRQL_END                  = E_IRQL_START + 15,

    E_IRQH_START                = CONFIG_IRQH_BASE_ADDRESS,
    E_IRQ_16                    = E_IRQH_START + 0,
    E_IRQ_17                    = E_IRQH_START + 1,
    E_IRQ_18                    = E_IRQH_START + 2,
    E_IRQ_19                    = E_IRQH_START + 3,
    E_IRQ_20                    = E_IRQH_START + 4,
    E_IRQ_21                    = E_IRQH_START + 5,
    E_IRQ_22                    = E_IRQH_START + 6,
    E_IRQ_23                    = E_IRQH_START + 7,
    E_IRQ_24                    = E_IRQH_START + 8,
    E_IRQ_25                    = E_IRQH_START + 9,
    E_IRQ_26                    = E_IRQH_START + 10,
    E_IRQ_27                    = E_IRQH_START + 11,
    E_IRQ_28                    = E_IRQH_START + 12,
    E_IRQ_29                    = E_IRQH_START + 13,
    E_IRQ_30                    = E_IRQH_START + 14,
    E_IRQ_31                    = E_IRQH_START + 15,
    E_IRQH_END                  = E_IRQH_START + 15,

    E_FIQL_START                = CONFIG_FIQL_BASE_ADDRESS,
    E_FIQ_00                    = E_FIQL_START + 0,
    E_FIQ_01                    = E_FIQL_START + 1,
    E_FIQ_02                    = E_FIQL_START + 2,
    E_FIQ_03                    = E_FIQL_START + 3,
    E_FIQ_04                    = E_FIQL_START + 4,
    E_FIQ_05                    = E_FIQL_START + 5,
    E_FIQ_06                    = E_FIQL_START + 6,
    E_FIQ_07                    = E_FIQL_START + 7,
    E_FIQ_08                    = E_FIQL_START + 8,
    E_FIQ_09                    = E_FIQL_START + 9,
    E_FIQ_10                    = E_FIQL_START + 10,
    E_FIQ_11                    = E_FIQL_START + 11,
    E_FIQ_12                    = E_FIQL_START + 12,
    E_FIQ_13                    = E_FIQL_START + 13,
    E_FIQ_14                    = E_FIQL_START + 14,
    E_FIQ_15                    = E_FIQL_START + 15,
    E_FIQL_END                  = E_FIQL_START + 15,

    E_FIQH_START                = CONFIG_FIQH_BASE_ADDRESS,
    E_FIQ_16                    = E_FIQH_START + 0,
    E_FIQ_17                    = E_FIQH_START + 1,
    E_FIQ_18                    = E_FIQH_START + 2,
    E_FIQ_19                    = E_FIQH_START + 3,
    E_FIQ_20                    = E_FIQH_START + 4,
    E_FIQ_21                    = E_FIQH_START + 5,
    E_FIQ_22                    = E_FIQH_START + 6,
    E_FIQ_23                    = E_FIQH_START + 7,
    E_FIQ_24                    = E_FIQH_START + 8,
    E_FIQ_25                    = E_FIQH_START + 9,
    E_FIQ_26                    = E_FIQH_START + 10,
    E_FIQ_27                    = E_FIQH_START + 11,
    E_FIQ_28                    = E_FIQH_START + 12,
    E_FIQ_29                    = E_FIQH_START + 13,
    E_FIQ_30                    = E_FIQH_START + 14,
    E_FIQ_31                    = E_FIQH_START + 15,
    E_FIQH_END                  = E_FIQH_START + 15,

    E_IRQEXPL_START             = CONFIG_IRQEXPL_BASE_ADDRESS,
    E_IRQ_32                    = E_IRQEXPL_START + 0,
    E_IRQ_33                    = E_IRQEXPL_START + 1,
    E_IRQ_34                    = E_IRQEXPL_START + 2,
    E_IRQ_35                    = E_IRQEXPL_START + 3,
    E_IRQ_36                    = E_IRQEXPL_START + 4,
    E_IRQ_37                    = E_IRQEXPL_START + 5,
    E_IRQ_38                    = E_IRQEXPL_START + 6,
    E_IRQ_39                    = E_IRQEXPL_START + 7,
    E_IRQ_40                    = E_IRQEXPL_START + 8,
    E_IRQ_41                    = E_IRQEXPL_START + 9,
    E_IRQ_42                    = E_IRQEXPL_START + 10,
    E_IRQ_43                    = E_IRQEXPL_START + 11,
    E_IRQ_44                    = E_IRQEXPL_START + 12,
    E_IRQ_45                    = E_IRQEXPL_START + 13,
    E_IRQ_46                    = E_IRQEXPL_START + 14,
    E_IRQ_47                    = E_IRQEXPL_START + 15,
    E_IRQEXPL_END               = E_IRQEXPL_START + 15,

    E_IRQEXPH_START             = CONFIG_IRQEXPH_BASE_ADDRESS,
    E_IRQ_48                    = E_IRQEXPH_START + 0,
    E_IRQ_49                    = E_IRQEXPH_START + 1,
    E_IRQ_50                    = E_IRQEXPH_START + 2,
    E_IRQ_51                    = E_IRQEXPH_START + 3,
    E_IRQ_52                    = E_IRQEXPH_START + 4,
    E_IRQ_53                    = E_IRQEXPH_START + 5,
    E_IRQ_54                    = E_IRQEXPH_START + 6,
    E_IRQ_55                    = E_IRQEXPH_START + 7,
    E_IRQ_56                    = E_IRQEXPH_START + 8,
    E_IRQ_57                    = E_IRQEXPH_START + 9,
    E_IRQ_58                    = E_IRQEXPH_START + 10,
    E_IRQ_59                    = E_IRQEXPH_START + 11,
    E_IRQ_60                    = E_IRQEXPH_START + 12,
    E_IRQ_61                    = E_IRQEXPH_START + 13,
    E_IRQ_62                    = E_IRQEXPH_START + 14,
    E_IRQ_63                    = E_IRQEXPH_START + 15,
    E_IRQEXPH_END               = E_IRQEXPH_START + 15,

    E_FIQEXPL_START             = CONFIG_FIQEXPL_BASE_ADDRESS,
    E_FIQ_32                    = E_FIQEXPL_START + 0,
    E_FIQ_33                    = E_FIQEXPL_START + 1,
    E_FIQ_34                    = E_FIQEXPL_START + 2,
    E_FIQ_35                    = E_FIQEXPL_START + 3,
    E_FIQ_36                    = E_FIQEXPL_START + 4,
    E_FIQ_37                    = E_FIQEXPL_START + 5,
    E_FIQ_38                    = E_FIQEXPL_START + 6,
    E_FIQ_39                    = E_FIQEXPL_START + 7,
    E_FIQ_40                    = E_FIQEXPL_START + 8,
    E_FIQ_41                    = E_FIQEXPL_START + 9,
    E_FIQ_42                    = E_FIQEXPL_START + 10,
    E_FIQ_43                    = E_FIQEXPL_START + 11,
    E_FIQ_44                    = E_FIQEXPL_START + 12,
    E_FIQ_45                    = E_FIQEXPL_START + 13,
    E_FIQ_46                    = E_FIQEXPL_START + 14,
    E_FIQ_47                    = E_FIQEXPL_START + 15,
    E_FIQEXPL_END               = E_FIQEXPL_START + 15,

    E_FIQEXPH_START             = CONFIG_FIQEXPH_BASE_ADDRESS,
    E_FIQ_48                    = E_FIQEXPH_START + 0,
    E_FIQ_49                    = E_FIQEXPH_START + 1,
    E_FIQ_50                    = E_FIQEXPH_START + 2,
    E_FIQ_51                    = E_FIQEXPH_START + 3,
    E_FIQ_52                    = E_FIQEXPH_START + 4,
    E_FIQ_53                    = E_FIQEXPH_START + 5,
    E_FIQ_54                    = E_FIQEXPH_START + 6,
    E_FIQ_55                    = E_FIQEXPH_START + 7,
    E_FIQ_56                    = E_FIQEXPH_START + 8,
    E_FIQ_57                    = E_FIQEXPH_START + 9,
    E_FIQ_58                    = E_FIQEXPH_START + 10,
    E_FIQ_59                    = E_FIQEXPH_START + 11,
    E_FIQ_60                    = E_FIQEXPH_START + 12,
    E_FIQ_61                    = E_FIQEXPH_START + 13,
    E_FIQ_62                    = E_FIQEXPH_START + 14,
    E_FIQ_63                    = E_FIQEXPH_START + 15,
    E_FIQEXPH_END               = E_FIQEXPH_START + 15,

	E_IRQHYPL_START             = CONFIG_IRQHYPL_BASE_ADDRESS,
    E_IRQ_64                    = E_IRQHYPL_START + 0,
    E_IRQ_65                    = E_IRQHYPL_START + 1,
    E_IRQ_66                    = E_IRQHYPL_START + 2,
    E_IRQ_67                    = E_IRQHYPL_START + 3,
    E_IRQ_68                    = E_IRQHYPL_START + 4,
    E_IRQ_69                    = E_IRQHYPL_START + 5,
    E_IRQ_70                    = E_IRQHYPL_START + 6,
    E_IRQ_71                    = E_IRQHYPL_START + 7,
    E_IRQ_72                    = E_IRQHYPL_START + 8,
    E_IRQ_73                    = E_IRQHYPL_START + 9,
    E_IRQ_74                    = E_IRQHYPL_START + 10,
    E_IRQ_75                    = E_IRQHYPL_START + 11,
    E_IRQ_76                    = E_IRQHYPL_START + 12,
    E_IRQ_77                    = E_IRQHYPL_START + 13,
    E_IRQ_78                    = E_IRQHYPL_START + 14,
    E_IRQ_79                    = E_IRQHYPL_START + 15,
    E_IRQHYPL_END               = E_IRQHYPL_START + 15,

	E_IRQHYPH_START             = CONFIG_IRQHYPH_BASE_ADDRESS,
    E_IRQ_80                    = E_IRQHYPH_START + 0,
    E_IRQ_81                    = E_IRQHYPH_START + 1,
    E_IRQ_82                    = E_IRQHYPH_START + 2,
    E_IRQ_83                    = E_IRQHYPH_START + 3,
    E_IRQ_84                    = E_IRQHYPH_START + 4,
    E_IRQ_85                    = E_IRQHYPH_START + 5,
    E_IRQ_86                    = E_IRQHYPH_START + 6,
    E_IRQ_87                    = E_IRQHYPH_START + 7,
    E_IRQ_88                    = E_IRQHYPH_START + 8,
    E_IRQ_89                    = E_IRQHYPH_START + 9,
    E_IRQ_90                    = E_IRQHYPH_START + 10,
    E_IRQ_91                    = E_IRQHYPH_START + 11,
    E_IRQ_92                    = E_IRQHYPH_START + 12,
    E_IRQ_93                    = E_IRQHYPH_START + 13,
    E_IRQ_94                    = E_IRQHYPH_START + 14,
    E_IRQ_95                    = E_IRQHYPH_START + 15,
    E_IRQHYPH_END               = E_IRQHYPH_START + 15,


	E_FIQHYPL_START             = CONFIG_FIQHYPL_BASE_ADDRESS,
    E_FIQ_64                    = E_FIQHYPL_START + 0,
    E_FIQ_65                    = E_FIQHYPL_START + 1,
    E_FIQ_66                    = E_FIQHYPL_START + 2,
    E_FIQ_67                    = E_FIQHYPL_START + 3,
    E_FIQ_68                    = E_FIQHYPL_START + 4,
    E_FIQ_69                    = E_FIQHYPL_START + 5,
    E_FIQ_70                    = E_FIQHYPL_START + 6,
    E_FIQ_71                    = E_FIQHYPL_START + 7,
    E_FIQ_72                    = E_FIQHYPL_START + 8,
    E_FIQ_73                    = E_FIQHYPL_START + 9,
    E_FIQ_74                    = E_FIQHYPL_START + 10,
    E_FIQ_75                    = E_FIQHYPL_START + 11,
    E_FIQ_76                    = E_FIQHYPL_START + 12,
    E_FIQ_77                    = E_FIQHYPL_START + 13,
    E_FIQ_78                    = E_FIQHYPL_START + 14,
    E_FIQ_79                    = E_FIQHYPL_START + 15,
    E_FIQHYPL_END               = E_FIQHYPL_START + 15,

	E_FIQHYPH_START             = CONFIG_FIQHYPH_BASE_ADDRESS,
    E_FIQ_80                    = E_FIQHYPH_START + 0,
    E_FIQ_81                    = E_FIQHYPH_START + 1,
    E_FIQ_82                    = E_FIQHYPH_START + 2,
    E_FIQ_83                    = E_FIQHYPH_START + 3,
    E_FIQ_84                    = E_FIQHYPH_START + 4,
    E_FIQ_85                    = E_FIQHYPH_START + 5,
    E_FIQ_86                    = E_FIQHYPH_START + 6,
    E_FIQ_87                    = E_FIQHYPH_START + 7,
    E_FIQ_88                    = E_FIQHYPH_START + 8,
    E_FIQ_89                    = E_FIQHYPH_START + 9,
    E_FIQ_90                    = E_FIQHYPH_START + 10,
    E_FIQ_91                    = E_FIQHYPH_START + 11,
    E_FIQ_92                    = E_FIQHYPH_START + 12,
    E_FIQ_93                    = E_FIQHYPH_START + 13,
    E_FIQ_94                    = E_FIQHYPH_START + 14,
    E_FIQ_95                    = E_FIQHYPH_START + 15,
    E_FIQHYPH_END               = E_FIQHYPH_START + 15,

    E_IRQ_FIQ_NONE              = 0xFE,
    E_IRQ_FIQ_ALL               = 0xFF

} IRQFIQNum;

static MS_U32 IntEnum2HWIdx[E_INT_IRQ_MAX];
static MS_U32 HWIdx2IntEnum[E_IRQ_FIQ_ALL];

static void HAL_UpdateIrqTable(MS_U32 byHardwareIndex, MS_U32 bySoftwareIndex)
{
    if(bySoftwareIndex == E_INT_RESERVED)
    {
        IntEnum2HWIdx[bySoftwareIndex] = E_IRQ_FIQ_NONE;
        HWIdx2IntEnum[byHardwareIndex] = E_INT_IRQ_FIQ_NONE;
    }
    else
    {
        IntEnum2HWIdx[bySoftwareIndex] = byHardwareIndex;
        HWIdx2IntEnum[byHardwareIndex] = bySoftwareIndex;
    }
}

static void HAL_InitIrqTable(void)
{
    unsigned int    dwDataCounter = 0;

    for(dwDataCounter = 0; dwDataCounter < E_IRQ_FIQ_ALL; dwDataCounter ++)
    {
        IntEnum2HWIdx[dwDataCounter] = E_IRQ_FIQ_NONE;
        HWIdx2IntEnum[dwDataCounter] = E_INT_IRQ_FIQ_NONE;
    }

    for(dwDataCounter = E_IRQ_FIQ_ALL; dwDataCounter < E_INT_IRQ_MAX; dwDataCounter++)
    {
        IntEnum2HWIdx[dwDataCounter] = E_IRQ_FIQ_NONE;
    }

    HAL_UpdateIrqTable(E_IRQ_00, E_INT_IRQ_UART0);                  //int_uart0
    HAL_UpdateIrqTable(E_IRQ_01, E_INT_IRQ_MIIC_INT1);              //miic1_int
    HAL_UpdateIrqTable(E_IRQ_02, E_INT_IRQ_MVD2MIPS);               //mvd2mips_int
    HAL_UpdateIrqTable(E_IRQ_03, E_INT_IRQ_MVD);                    //mvd_int
    HAL_UpdateIrqTable(E_IRQ_04, E_INT_IRQ_FIQ_NONE);               //~reg_top_gpio_in[2]
    HAL_UpdateIrqTable(E_IRQ_05, E_INT_IRQ_CA_NSK_INT);             //ca_nsk_int
    HAL_UpdateIrqTable(E_IRQ_06, E_INT_IRQ_USB);                    //usb_int
    HAL_UpdateIrqTable(E_IRQ_07, E_INT_IRQ_UHC);                    //uhc_int
    HAL_UpdateIrqTable(E_IRQ_08, E_INT_IRQ_ZDEC);                   //zdec_irq
    HAL_UpdateIrqTable(E_IRQ_09, E_INT_IRQ_GMAC);                   //gmac_int
    HAL_UpdateIrqTable(E_IRQ_10, E_INT_IRQ_DISP);                   //disp_int
    HAL_UpdateIrqTable(E_IRQ_11, E_INT_IRQ_DHC);                    //dhc_int
    HAL_UpdateIrqTable(E_IRQ_12, E_INT_IRQ_MSPI0);                  //mspi_int
    HAL_UpdateIrqTable(E_IRQ_13, E_INT_IRQ_EVD);                    //evd_int
    HAL_UpdateIrqTable(E_IRQ_14, E_INT_IRQ_EVD_LITE);               //evd_lite_int
    HAL_UpdateIrqTable(E_IRQ_15, E_INT_IRQ_FIQ_NONE);               //Reserved.

    HAL_UpdateIrqTable(E_IRQ_16, E_INT_IRQ_TSP2HK);                 //tsp2hk_int
    HAL_UpdateIrqTable(E_IRQ_17, E_INT_IRQ_VE);                     //ve_int
    HAL_UpdateIrqTable(E_IRQ_18, E_INT_IRQ_AEON2HI);                //irq_aeon2hi
    HAL_UpdateIrqTable(E_IRQ_19, E_INT_IRQ_DC);                     //dc_int
    HAL_UpdateIrqTable(E_IRQ_20, E_INT_IRQ_GOP);                    //gop_int
    HAL_UpdateIrqTable(E_IRQ_21, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_22, E_INT_IRQ_MIIC_INT0);              //miic0_int
    HAL_UpdateIrqTable(E_IRQ_23, E_INT_IRQ_RTC);                    //rtc0_int
    HAL_UpdateIrqTable(E_IRQ_24, E_INT_IRQ_KEYPAD);                 //keypad_int
    HAL_UpdateIrqTable(E_IRQ_25, E_INT_IRQ_PM);                     //pm_int
    HAL_UpdateIrqTable(E_IRQ_26, E_INT_IRQ_MFE);                    //mfe_int
    HAL_UpdateIrqTable(E_IRQ_27, E_INT_FIQ_UP_IRQ_EMM_ECM);         //up_irq_emm_ecm
    HAL_UpdateIrqTable(E_IRQ_28, E_INT_IRQ_UP_IRQ_UART_CA);         //up_irq_uart_ca
    HAL_UpdateIrqTable(E_IRQ_29, E_INT_IRQ_RTC1);                   //rtc1_int
    HAL_UpdateIrqTable(E_IRQ_30, E_INT_IRQ_CA_IP_INT);              //ca_ip_int
    HAL_UpdateIrqTable(E_IRQ_31, E_INT_IRQ_ADCDVI2RIU);             //adcdvi2riu_int

    HAL_UpdateIrqTable(E_IRQ_32, E_INT_IRQ_TSP_TSO0);               //tsp_tso0_int
    HAL_UpdateIrqTable(E_IRQ_33, E_INT_IRQ_USB1);                   //usb_int1
    HAL_UpdateIrqTable(E_IRQ_34, E_INT_IRQ_UHC1);                   //uhc_int1
    HAL_UpdateIrqTable(E_IRQ_35, E_INT_IRQ_MIU);                    //miu_int
    HAL_UpdateIrqTable(E_IRQ_36, E_INT_IRQ_ERROR_RESP);             //error_resp_int
    HAL_UpdateIrqTable(E_IRQ_37, E_INT_IRQ_OTG);                    //otg_int
    HAL_UpdateIrqTable(E_IRQ_38, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_39, E_INT_IRQ_UART1);                  //int_uart1
    HAL_UpdateIrqTable(E_IRQ_40, E_INT_IRQ_SVD_HVD);                //hvd_int
    HAL_UpdateIrqTable(E_IRQ_41, E_INT_IRQ_FIQ_NONE);               //reg_top_gpio_in[4]
    HAL_UpdateIrqTable(E_IRQ_42, E_INT_IRQ_FIQ_NONE);               //~reg_top_gpio_in[4]
    HAL_UpdateIrqTable(E_IRQ_43, E_INT_IRQ_EMMC_OSP_INT);           //emmc_osp_int
    HAL_UpdateIrqTable(E_IRQ_44, E_INT_IRQ_CA_RSA_INT0);            //ca_crypto_dma_int
    HAL_UpdateIrqTable(E_IRQ_45, E_INT_IRQ_JPD);                    //jpd_int
    HAL_UpdateIrqTable(E_IRQ_46, E_INT_IRQ_DISP1);                  //disp1_int
    HAL_UpdateIrqTable(E_IRQ_47, E_INT_IRQ_AKL_INT);                //akl_intrrupt

    HAL_UpdateIrqTable(E_IRQ_48, E_INT_IRQ_BDMA0);                  //int_bdma[0]
    HAL_UpdateIrqTable(E_IRQ_49, E_INT_IRQ_BDMA1);                  //int_bdma[1]
    HAL_UpdateIrqTable(E_IRQ_50, E_INT_IRQ_UART2MCU);               //uart2mcu_intr
    HAL_UpdateIrqTable(E_IRQ_51, E_INT_IRQ_URDMA2MCU);              //urdma2mcu_intr
    HAL_UpdateIrqTable(E_IRQ_52, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_53, E_INT_IRQ_CEC);                    //cec_irq_out
    HAL_UpdateIrqTable(E_IRQ_54, E_INT_IRQ_HDMI_LEVEL);             //HDMITX_IRQ_LEVEL
    HAL_UpdateIrqTable(E_IRQ_55, E_INT_IRQ_FCIE2RIU);               //fcie_int
    HAL_UpdateIrqTable(E_IRQ_56, E_INT_IRQ_HDCP_X74);               //hdcp_x74_int
    HAL_UpdateIrqTable(E_IRQ_57, E_INT_IRQ_GPD);                    //gpd_int
    HAL_UpdateIrqTable(E_IRQ_58, E_INT_IRQ_SAR1);                   //SAR1_int
    HAL_UpdateIrqTable(E_IRQ_59, E_INT_IRQ_IDAC_PLUG_DET);          //irq_dac_plug_det
    HAL_UpdateIrqTable(E_IRQ_60, E_INT_IRQ_FIQ_NONE);               //reg_top_gpio_in[2]
    HAL_UpdateIrqTable(E_IRQ_61, E_INT_IRQ_RASP);                   //rasp0_int
    HAL_UpdateIrqTable(E_IRQ_62, E_INT_IRQ_TSP_FI_QUEUE_INT);       //fi_queue_int
    HAL_UpdateIrqTable(E_IRQ_63, E_INT_IRQ_FRM_PM);                 //irq_frm_pm
    HAL_UpdateIrqTable(E_IRQ_64, E_INT_IRQ_MIIC_INT2);              //miic2_int
    HAL_UpdateIrqTable(E_IRQ_65, E_INT_IRQ_MIIC_INT3);              //miic3_int
    HAL_UpdateIrqTable(E_IRQ_66, E_INT_IRQ_MIIC_INT4);              //miic4_int
    HAL_UpdateIrqTable(E_IRQ_67, E_INT_IRQ_MIIC_INT5);              //miic5_int
    HAL_UpdateIrqTable(E_IRQ_68, E_INT_IRQ_HDMITX);                 //hdmitx_phy_int
    HAL_UpdateIrqTable(E_IRQ_69, E_INT_IRQ_GE);                     //ge_int
    HAL_UpdateIrqTable(E_IRQ_70, E_INT_IRQ_MIU_SECURE);             //miu_security_int
    HAL_UpdateIrqTable(E_IRQ_71, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_72, E_INT_IRQ_G3D2MCU);                //g3d2mcu_irq_dft
    HAL_UpdateIrqTable(E_IRQ_73, E_INT_FIQEXPH_CMDQ);               //cmdq_int
    HAL_UpdateIrqTable(E_IRQ_74, E_INT_IRQ_AUDMA_V2_INT);           //AUDMA_V2_INTR
    HAL_UpdateIrqTable(E_IRQ_75, E_INT_IRQ_SCDC_PM_INT);            //scdc_int_pm
    HAL_UpdateIrqTable(E_IRQ_76, E_FRCINT_IRQ_MSPI2);               //mspi2_int
    HAL_UpdateIrqTable(E_IRQ_77, E_INT_IRQ_SMART);                  //smart_int0
    HAL_UpdateIrqTable(E_IRQ_78, E_INT_IRQ_FIQ_NONE);               //Reserved..
    HAL_UpdateIrqTable(E_IRQ_79, E_INT_IRQ_DCSUB);                  //dc_sub_int
    HAL_UpdateIrqTable(E_IRQ_80, E_INT_IRQ_SDIO);                   //sdio_int
    HAL_UpdateIrqTable(E_IRQ_81, E_INT_IRQ_EMAC);                   //emac
    HAL_UpdateIrqTable(E_IRQ_82, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_83, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_84, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_85, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_IRQ_86, E_INT_IRQ_USB2);                   //ubb_int_p2
    HAL_UpdateIrqTable(E_IRQ_87, E_INT_IRQ_UHC2);                   //uhc_int_p2
    HAL_UpdateIrqTable(E_IRQ_88, E_INT_IRQ_FIQ_NONE);               //miu_ns_int
    HAL_UpdateIrqTable(E_IRQ_89, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_IRQ_90, E_INT_IRQ_VIVALDI_V9_MIU_AL);      //INT_v9_mui_al
    HAL_UpdateIrqTable(E_IRQ_91, E_INT_IRQ_SDIO_OSP_INT);           //sdio_osp_int
    HAL_UpdateIrqTable(E_IRQ_92, E_INT_IRQ_MIU_TLB_INT);            //miu_tlb_int
    HAL_UpdateIrqTable(E_IRQ_93, E_INT_IRQ_DIPW);                   //dipw_INT
    HAL_UpdateIrqTable(E_IRQ_94, E_INT_IRQ_FIQ_NONE);               //diamond_reg_rxiu_timeout_nodefine_int
    HAL_UpdateIrqTable(E_IRQ_95, E_INT_IRQ_PAS_PTS_COMBINE_INT);    //PAS_PTS_INTRL_COMBINE

    HAL_UpdateIrqTable(E_FIQ_00, E_INT_FIQ_EXTIMER0);               //int_timer0
    HAL_UpdateIrqTable(E_FIQ_01, E_INT_FIQ_EXTIMER1);               //int_timer1
    HAL_UpdateIrqTable(E_FIQ_02, E_INT_FIQ_WDT);                    //int_wdt
    HAL_UpdateIrqTable(E_FIQ_03, E_INT_FIQ_SEC_TIMER0);             //int_sec_timer0
    HAL_UpdateIrqTable(E_FIQ_04, E_INT_FIQ_SEC_TIMER1);             //int_sec_timer1
    HAL_UpdateIrqTable(E_FIQ_05, E_INT_FIQ_R2TOMCU_INT0);           //MB_auR2to_MCU_INT[0]
    HAL_UpdateIrqTable(E_FIQ_06, E_INT_FIQ_DSPTOMCU_INT0);          //MB_DSP2toMCU_INT[0]
    HAL_UpdateIrqTable(E_FIQ_07, E_INT_FIQ_DSPTOMCU_INT1);          //MB_DSP2toMCU_INT[1]
    HAL_UpdateIrqTable(E_FIQ_08, E_INT_FIQ_R2TOMCU_INT1);           //MB_auR2to_MCU_INT[1]
    HAL_UpdateIrqTable(E_FIQ_09, E_INT_FIQ_UP_IRQ_UART_CA);         //up_irq_uart_ca
    HAL_UpdateIrqTable(E_FIQ_10, E_INT_FIQ_R2TOMCU_INT2);           //MB_auR2to_MCU_INT[2]
    HAL_UpdateIrqTable(E_FIQ_11, E_INT_FIQ_HDMI_NON_PCM);           //HDMI_NON_PCM_MODE_INT_OUT
    HAL_UpdateIrqTable(E_FIQ_12, E_INT_FIQ_SPDIF_IN_NON_PCM);       //SPDIF_IN_NON_PCM_INT_OUT
    HAL_UpdateIrqTable(E_FIQ_13, E_INT_FIQ_LAN_ESD_INT);            //lan_esd_int
    HAL_UpdateIrqTable(E_FIQ_14, E_INT_FIQ_SE_DSP2UP);              //SE_DSP2UP_intr
    HAL_UpdateIrqTable(E_FIQ_15, E_INT_FIQ_TSP2AEON);               //tsp2aeon_int

    HAL_UpdateIrqTable(E_FIQ_16, E_INT_FIQ_VIVALDI_STR);            //vivaldi_str_intr
    HAL_UpdateIrqTable(E_FIQ_17, E_INT_FIQ_VIVALDI_PTS);            //vivaldi_pts_intr
    HAL_UpdateIrqTable(E_FIQ_18, E_INT_FIQ_DSP_MIU_PROT);           //DSP_MIU_PROT_intr
    HAL_UpdateIrqTable(E_FIQ_19, E_INT_FIQ_XIU_TIMEOUT);            //xiu_timeout_int
    HAL_UpdateIrqTable(E_FIQ_20, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_21, E_INT_FIQ_VSYNC_VE4VBI);           //ve_vbi_f0_int
    HAL_UpdateIrqTable(E_FIQ_22, E_INT_FIQ_FIELD_VE4VBI);           //ve_vbi_f1_int
    HAL_UpdateIrqTable(E_FIQ_23, E_INT_FIQ_R2TOMCU_INT3);           //MB_auR2to_MCU_INT[3]
    HAL_UpdateIrqTable(E_FIQ_24, E_INT_FIQ_VE_DONE_TT);             //ve_done_TT_irq
    HAL_UpdateIrqTable(E_FIQ_25, E_INT_FIQ_INT_CCFL);               //INT_CCFL
    HAL_UpdateIrqTable(E_FIQ_26, E_INT_IRQ_FIQ_NONE);               //int_in
    HAL_UpdateIrqTable(E_FIQ_27, E_INT_FIQ_IR);                     //ir_int
    HAL_UpdateIrqTable(E_FIQ_28, E_INT_FIQ_AU_SPDIF_TX_CS0);        //AU_SPDIF_TX_CS_INT[0]
    HAL_UpdateIrqTable(E_FIQ_29, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_30, E_INT_FIQ_AU_SPDIF_TX_CS1);        //AU_SPDIF_TX_CS_INT[1]
    HAL_UpdateIrqTable(E_FIQ_31, E_INT_FIQ_DEC_DSP2MIPS);           //DSP2MIPS_INT

    HAL_UpdateIrqTable(E_FIQ_32, E_INT_FIQ_IR_INT_RC);              //ir_int_rc
    HAL_UpdateIrqTable(E_FIQ_33, E_INT_FIQ_AU_DMA_BUF_INT);         //AU_DMA_BUFFER_INT_EDGE
    HAL_UpdateIrqTable(E_FIQ_34, E_INT_FIQ_VE_SW_WR2BUF);           //ve_sw_wr2buf_int
    HAL_UpdateIrqTable(E_FIQ_35, E_INT_IRQ_UP_IRQ_EMM_ECM);         //up_irq_emm_ecm
    HAL_UpdateIrqTable(E_FIQ_36, E_INT_IRQ_FIQ_NONE);               //reg_hst0to3_int   # HOST 0 - PM 8051
    HAL_UpdateIrqTable(E_FIQ_37, E_INT_FIQ_8051_TO_BEON);           //reg_hst0to2_int   # HOST 1 - Secure R2
    HAL_UpdateIrqTable(E_FIQ_38, E_INT_FIQ_8051_TO_SECURER2);       //reg_hst0to1_int   # HOST 2 - ACPU Core0 (BEON)
    HAL_UpdateIrqTable(E_FIQ_39, E_INT_IRQ_FIQ_NONE);               //Reserved           # HOST 3 - Secure 8051/ACPU Core1 (No used)
    HAL_UpdateIrqTable(E_FIQ_40, E_INT_IRQ_FIQ_NONE);               //reg_hst1to3_int
    HAL_UpdateIrqTable(E_FIQ_41, E_INT_FIQ_SECURER2_TO_BEON);       //reg_hst1to2_int
    HAL_UpdateIrqTable(E_FIQ_42, E_INT_FIQ_SECURER2_TO_8051);       //reg_hst1to0_int
    HAL_UpdateIrqTable(E_FIQ_43, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_44, E_INT_IRQ_FIQ_NONE);               //reg_hst2to3_int
    HAL_UpdateIrqTable(E_FIQ_45, E_INT_FIQ_BEON_TO_SECURER2);       //reg_hst2to1_int
    HAL_UpdateIrqTable(E_FIQ_46, E_INT_FIQ_BEON_TO_8051);           //reg_hst2to0_int
    HAL_UpdateIrqTable(E_FIQ_47, E_INT_IRQ_FIQ_NONE);               //Reserved.

    HAL_UpdateIrqTable(E_FIQ_48, E_INT_IRQ_FIQ_NONE);               //reg_hst3to2_int
    HAL_UpdateIrqTable(E_FIQ_49, E_INT_IRQ_FIQ_NONE);               //reg_hst3to1_int
    HAL_UpdateIrqTable(E_FIQ_50, E_INT_IRQ_FIQ_NONE);               //reg_hst3to0_int
    HAL_UpdateIrqTable(E_FIQ_51, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_52, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_53, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_54, E_INT_FIQ_HDMITX_IRQ_EDGE);        //HDMITX_IRQ_EDGE
    HAL_UpdateIrqTable(E_FIQ_55, E_INT_IRQ_FIQ_NONE);               //Reserved.
    HAL_UpdateIrqTable(E_FIQ_56, E_INT_FIQ_CA_CRYPTO_DMA);          //crypto_dma_int
    HAL_UpdateIrqTable(E_FIQ_57, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_58, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_59, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_60, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_61, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_62, E_INT_IRQ_FIQ_NONE);               //Reserved
    HAL_UpdateIrqTable(E_FIQ_63, E_INT_FIQ_FRM_PM);                 //fiq_frm_pm

    HAL_UpdateIrqTable(E_FIQ_64, E_INT_FIQ_SEC_GUARD_INT);          //sec_guard_int
    HAL_UpdateIrqTable(E_FIQ_65, E_INT_FIQ_PM_SD_CDZ0);             //SD_CDZ_IN

}

#ifdef __cplusplus
}
#endif

#endif // _HAL_IRQTBL_H_

