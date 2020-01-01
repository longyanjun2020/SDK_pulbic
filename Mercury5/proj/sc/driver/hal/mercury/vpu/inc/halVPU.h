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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#ifndef _HAL_VPU_H_
#define _HAL_VPU_H_


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#if defined(REDLION_LINUX_KERNEL_ENVI)
#define ENABLE_VPU_MUTEX_PROTECTION     0
#define VPU_DEFAULT_MUTEX_TIMEOUT       0xFFFFFFFFUL
#else
#define ENABLE_VPU_MUTEX_PROTECTION     1
#define VPU_DEFAULT_MUTEX_TIMEOUT       MSOS_WAIT_FOREVER
#endif

#define VPU_CLOCK_240MHZ                BITS(11:10,0)
#define VPU_CLOCK_216MHZ                BITS(11:10,1)
#define VPU_CLOCK_160MHZ                BITS(11:10,2)
#define VPU_CLOCK_144MHZ                BITS(11:10,3)
//#define VPU_CLOCK_MCU                   BITS(6:2,8)
//#define VPU_CLOCK_MIU                   BITS(6:2,16)
//#define VPU_CLOCK_XTALI                 BITS(6:2,24)

#define VPU_HI_MBOX0        0
#define VPU_HI_MBOX1        1
#define VPU_RISC_MBOX0      2
#define VPU_RISC_MBOX1      3


#define VPU_Timer_delay_ms(x)            \
    do {                                                            \
        volatile MS_U32 ticks=0;                                         \
        while( ticks < ( ((MS_U32)(x)) <<13) )      \
        {                                                               \
            ticks++;                                                \
        }                                                               \
    } while(0)
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_VPU_DECODER_NONE = 0,
    E_VPU_DECODER_MVD,
    E_VPU_DECODER_HVD,
    E_VPU_DECODER_MJPEG,
    E_VPU_DECODER_RVD,
} VPU_DecoderType;

typedef enum
{
    E_VPU_CLOCK_240MHZ   = VPU_CLOCK_240MHZ,
    E_VPU_CLOCK_216MHZ   = VPU_CLOCK_216MHZ,
    E_VPU_CLOCK_160MHZ   = VPU_CLOCK_160MHZ,
    E_VPU_CLOCK_144MHZ   = VPU_CLOCK_144MHZ,
} VPU_Clock_Speed;

/// vpu clock speed
typedef enum
{
    E_HAL_VPU_CLOCK_SPEED_NONE = 0,
    E_HAL_VPU_CLOCK_SPEED_HIGHEST,
    E_HAL_VPU_CLOCK_SPEED_HIGH,
    E_HAL_VPU_CLOCK_SPEED_MEDIUM,
    E_HAL_VPU_CLOCK_SPEED_LOW,
    E_HAL_VPU_CLOCK_SPEED_LOWEST,
    E_HAL_VPU_CLOCK_SPEED_DEFAULT,
} HAL_VPU_ClockSpeedType;

typedef struct
{
    VPU_Clock_Speed eClockSpeed;
    MS_BOOL  bClockInv;
    MS_S32  s32VPUMutexID;
    MS_U32  u32VPUMutexTimeout;
    MS_BOOL bInMIU1;
} VPU_Init_Params;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void HAL_VPU_InitRegBase(MS_U32 u32RegBase);
MS_BOOL HAL_VPU_IsNeedReload(VPU_DecoderType eDecoder);
void HAL_VPU_SetFWDecoder(VPU_DecoderType eDecoder);
VPU_DecoderType HAL_VPU_GetFWDecoder(void);

MS_BOOL HAL_VPU_Init(VPU_Init_Params* InitParams);
MS_BOOL HAL_VPU_DeInit(void);
void HAL_VPU_PowerCtrl(MS_BOOL bEnable);
void HAL_VPU_ClockSpeed(MS_U32 u32type);
void HAL_VPU_ClockInv(MS_BOOL bEnable);
void HAL_VPU_MIU_RW_Protect(MS_BOOL bEnable);
MS_BOOL HAL_VPU_CPUSetting(MS_U32 u32StAddr);
MS_BOOL HAL_VPU_SwRst(void);
void HAL_VPU_SwRstRelse(void);
void HAL_VPU_SwRelseMAU(void);
MS_U32 HAL_VPU_MemRead(MS_U32 u32Address);
MS_BOOL HAL_VPU_MemWrite(MS_U32 u32Address, MS_U32 u32Value);
MS_BOOL HAL_VPU_MBoxRdy(MS_U32 u32type);
MS_BOOL HAL_VPU_MBoxRead(MS_U32 u32type, MS_U32 *u32Msg);
void HAL_VPU_MBoxClear(MS_U32 u32type);
MS_BOOL HAL_VPU_MBoxSend(MS_U32 u32type, MS_U32 u32Msg);
MS_U32 HAL_VPU_GetProgCnt(void);
MS_BOOL HAL_VPU_MAU_IDLE(void);

VPU_Clock_Speed HAL_VPU_GetClockSpeed(void);
MS_U32 HAL_VPU_GetClock(void);
MS_BOOL HAL_VPU_SetClockSpeedType(HAL_VPU_ClockSpeedType eClockSpeed);

#endif // _HAL_VPU_H_

