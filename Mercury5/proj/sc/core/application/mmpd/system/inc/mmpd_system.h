/// @ait_only
//==============================================================================
//
//  File        : mmpd_system.h
//  Description : INCLUDE File for the Host System Control Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_system.h
 *  @brief The header File for the Host System Control Driver
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPD_SYSTEM_H_
#define _MMPD_SYSTEM_H_

/** @addtogroup MMPD_System
 *  @{
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "ait_config.h"
#include "config_fw.h"
#include "mmp_gpio_inc.h"
#include "mmp_display_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPD_SYSTEM_PS_MODE
{
    MMPD_SYSTEM_ENTER_PS = 0,
    MMPD_SYSTEM_EXIT_PS
} MMPD_SYSTEM_PS_MODE;

typedef enum _MMPD_SYSTEM_WAKEUP_EVNET
{
    MMPD_SYSTEM_WAKEUP_NONE = 0x0,
    MMPD_SYSTEM_WAKEUP_GPIO,
    MMPD_SYSTEM_WAKEUP_TVPLUG_IN,
    MMPD_SYSTEM_WAKEUP_USB_RESUME,
    MMPD_SYSTEM_WAKEUP_HDMI_HPD,
    MMPD_SYSTEM_WAKEUP_RTC_CNT_VALID,
    MMPD_SYSTEM_WAKEUP_RTC_VALID,
    MMPD_SYSTEM_WAKEUP_RTC_INT,
    MMPD_SYSTEM_WAKEUP_MAX
} MMPD_SYSTEM_WAKEUP_EVNET;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_System_TVInitialize(MMP_BOOL bInit);
MMP_ERR MMPD_System_TVColorBar(MMP_TV_TYPE tvType, MMP_BOOL turnOn, MMP_UBYTE colorBarType);

MMP_ERR MMPD_System_SetPSMode(MMPD_SYSTEM_PS_MODE psmode);
MMP_ERR MMPD_System_ResetSystem(void);
MMP_ERR MMPD_System_SetWakeUpEvent(MMP_BOOL bEnable, MMPD_SYSTEM_WAKEUP_EVNET event, MMP_GPIO_PIN piopin, MMP_UBYTE polarity);
MMP_UBYTE MMPD_System_ReadCoreID(void);
MMP_ERR MMPD_System_SetSelfSleepMode(void);

#if (EN_AUTO_TEST_LOG == 1)
MMP_ERR MMPD_System_ClrAutoTestLog(void);
MMP_ERR MMPD_System_DumpAutoTestLog(void);
MMP_ERR MMPD_System_SetUserDefCmdNum(MMP_LONG ulUserDefNum);
MMP_UBYTE MMPD_System_IsAutoTestCmdLFull(MMP_ULONG ulAhcSysMode);
#endif

/// @}

#endif // _MMPD_SYSTEM_H_

/// @end_ait_only

