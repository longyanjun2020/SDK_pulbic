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
* @file    sys_sleep_g1.h
* @version
* @brief   This module defines the Scaler driver hal layer
*
*/

#ifndef SYS_SYS_SLEEP_G1
#define SYS_SYS_SLEEP_G1

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
#define REG_TIMER0_CAP_LOW  0x2A000C10
#define REG_TIMER0_CAP_HIGH 0x2A000C14

#define REG_ICP_SW_RESET 0x2A000804

#define REG_PRE_ARBI_MASK  0x2A00250C

#define REG_WFI_CONFIG    0x2A007E70

#define REG_AHB2MIU_EMI_TYPE    0x2a002004

#define REG_MMP_EMI_TYPE    0x2a007ec4

#define REG_MMP_EMI_2_TYPE   0x2a007ec8

#define REG_MMPASIC_EMI_TYPE   0x2a001c04

#define REG_MMPASIC_EMI_2_TYPE   0x2a001c08


#define REG_POST_RQ_EMI_TYPE   0x2a002534

#define REG_POST_CL_NUM_       0x2a002504


#define REG_POST_CL_HIGH_MASK   0x2a002510

#define REG_POST_CONFIG   0x2a002500



/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    SYS_SLEEP_POWER_ON = 0,
    SYS_SLEEP_POWER_DOWN,
} SYS_SLEEP_MODE_e;

typedef enum
{
    SYS_SLEEP_DISABLE = 0,
    SYS_SLEEP_ENABLE_POWER_ON,
    SYS_SLEEP_ENABLE_POWER_DOWN,
} SYS_SLEEP_ENABLE_e;


typedef struct sys_profile_s {
	u16     etmi_type;                 /* etmi type*/
	u16     etmi_data;                 /* etmi data*/
	u32     wake_up_time;              /* total wake time(process time),ms */
	u32     sleep_time;              /* sleep time when current interrupt occurred,ms */
} sys_profile_t, *sys_profile_ptr;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 *
 *  MMP System sleep check enable function
 *
 * @return None
 *
 */
bool sys_sleepIsEnable(void);


/**
 *
 *  MMP System set sleep function
 *
 * @return None
 *
 */
void sys_sleepActive(SYS_SLEEP_ENABLE_e action);


/**
 *
 *  MMP System get current active config function
 *
 * @return None
 *
 */
SYS_SLEEP_ENABLE_e sys_sleepGetActive(void);

/**
 * @brief  This function is used to print the G1 system sleep related debug information
 *         kept in baseband driver.
 *
 * @retVal NONE
 */
void sys_sleepDebugInfo(void);


#endif // SYS_SYS_SLEEP_G1

