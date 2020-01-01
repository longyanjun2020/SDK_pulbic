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
* @file    hal_rtc.h
* @version
* @brief   RTC HAL layer header file
*
*/

#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_vm_rtc.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/


/****************************************************************************/
/*        RTC  registers                                                    */
/****************************************************************************/

/*=============================================================*/
// Macro definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    HAL_RTC_OK = 0,
    HAL_RTC_FAIL,
    HAL_RTC_INVALID_PARAM
}HalRtcRetCode_e;

typedef enum
{
    HAL_RTC_DEFAULT = 0,
    HAL_RTC_DISABLE_ALRM_IRQ
}HalRtcPwrCtrlCode_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** HalRtcInit
* @brief        HAL interface to initialize RTC
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcInit(void);

/** HalRtcGetSecondCount
* @brief        HAL interface to get second count
* @param[out]    pConfigValue:       pointer to a u32 for second count
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetSecondCount(u32* pSecondCount);

/** HalRtcSetTimeDateAndYear
* @brief        HAL interface to set time date and year
* @param[in]    RtcTime:       vm_rtcTimeFormat_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetTimeDateAndYear(vm_rtcTimeFormat_t *RtcTime);

/** HalRtcGetTimeDateAndYear
* @brief        HAL interface to get time date and year
* @param[out]    RtcTime:       vm_rtcTimeFormat_tstructure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetTimeDateAndYear(vm_rtcTimeFormat_t *RtcTime);

/** HalRtcDStopAlarm
* @brief        HAL interface to stop alarm
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcDStopAlarm(void);

/** HalRtcSetAlarm
* @brief        HAL interface to set alarm
* @param[in]    RtcAlarm:       vm_rtcTimeFormat_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetAlarm(vm_rtcTimeFormat_t * RtcAlarm);

/** HalRtcGetAlarm
* @brief        HAL interface to get alarm
* @param[out]    RtcAlarm:       vm_rtcTimeFormat_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetAlarm(vm_rtcTimeFormat_t * RtcAlarm);

/** HalRtcSetCalendarEvent
* @brief        HAL interface to set calendar event
* @param[in]    event:       vm_rtcCalendarEvent_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetCalendarEvent(vm_rtcCalendarEvent_t event);

/** HalRtcGetCalendarEvent
* @brief        HAL interface to get calendar event
* @param[out]    event:       vm_rtcCalendarEvent_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetCalendarEvent(vm_rtcCalendarEvent_t *event);

/** HalRtcStopCalendarEvent
* @brief        HAL interface to stop calendar event
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcStopCalendarEvent(void);



/** HalRtcSetTick
* @brief        HAL interface to set tick
* @param[in]    tick_type:       vm_rtcTickType_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetTick(vm_rtcTickType_t tick_type);

/** HalRtcGetTick
* @brief        HAL interface to get tick
* @param[out]    tick_type:       vm_rtcTickType_t structure
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetTick(vm_rtcTickType_t *tick_type);

/** HalRtcStopTick
* @brief        HAL interface to stop tick
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcStopTick(void);

/** HalRtcGetCount
* @brief        HAL interface to get count
* @param[out]    pConfigValue:       pointer to a u32 for count
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetCount(u32* pConfigValue);

/** HalRtcPowerCtrlDown
* @brief        HAL interface to disable power hold with interface ready check
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcPowerCtrlDown(void);

/** HalRtcSetPasscode
* @brief        HAL interface to set passcode
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetPasscode(void);

/** HalRtcCheckIrqSrc
* @brief        HAL interface to check IRQ source
* @param[out]    pConfigValue:       pointer to a u16 for IRQ source return
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcCheckIrqSrc(u16* pIrqSource);

/** HalRtcClearIrqSrc
* @brief        HAL interface to clear RTC IRQ source
* @param[in]    pConfigValue:       pointer to a u16 for IRQ to clear
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcClearIrqSrc(u16* pIrqSource);

/** HalRtcDisableAllEvent
* @brief        HAL interface to clear all RTC event
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcDisableAllEvent(void);

/** HalRtcCheckPowerOnCause
* @brief        HAL interface to get power on cause
* @retval       PowerOnCause_e error code
*
*/
HalRtcRetCode_e HalRtcCheckPowerOnAlarm(bool *pbAlarmPowerOn);

/** HalRtcCheckIrq
* @brief        HAL interface to check RTC IRQ
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcCheckIrq(void);

/** HalRtcClearIrq
* @brief        HAL interface to clear RTC IRQ
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcClearIrq(void);

/** HalRtcReset
* @brief        HAL interface to reset RTC
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcReset(void);

/** HalRtcCheckCalendarGood
* @brief        HAL interface to check RTC calendar is reliable or not
* @param[in]    pLastValidTime:       pointer of valid time in E2P
* @retval       HalRtcRetCode_e error code
*
*/
bool HalRtcCheckCalendarGood(vm_rtcTimeFormat_t *pLastValidTime);

/** HalRtcSetCalendarGood
* @brief        HAL interface to check RTC calendar is reliable or not
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcSetCalendarGood(void);

/** HalRtcGetUTCSecondCount
* @brief        HAL interface to get UTC second count
* @param[out]   pConfigValue:       pointer to a u32 for UTC second count
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetUTCSecondCount(u32* pConfigValue);

/** HalRtcGetRange
* @brief        HAL interface to get minimal and maximal RTC time
* @param[out]   pMinRtcTime:        Minimal RTC time
* @param[out]   pMaxRtcTime:        Maximal RTC time
* @retval       HalRtcRetCode_e error code
*
*/
HalRtcRetCode_e HalRtcGetRange(vm_rtcTimeFormat_t *pMinRtcTime, vm_rtcTimeFormat_t *pMaxRtcTime);

/** HalRtcSetAbbrstFlag
* @brief        HAL interface to set abbrst flag (bit 12 in g_ptAsuraRtcReg->misc_ctrl_sts)
* @retval       HalRtcRetCode_e error code
*/
HalRtcRetCode_e HalRtcSetAbbrstFlag(void);

/** HalRtcAbbrstHappened
* @brief        HAL interface to check if abbrst happened
* @retval       TRUE if happened; FALSE if not
*/
bool HalRtcAbbrstHappened(void);


#endif //__HAL_RTC_H__

