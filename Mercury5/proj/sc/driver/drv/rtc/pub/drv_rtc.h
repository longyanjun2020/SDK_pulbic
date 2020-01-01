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
 * @file drv_rtc.h
 * @brief  API prototypes for RTC
*/

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_vm_rtc.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
//#if 1
//    #define RTC_TRACE _TRACE
//#else
//    #define RTC_TRACE(x)
//#endif

#define MSDRV_RTC_TRACE_LEVEL               (_IOB | LEVEL_22)

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    DRV_RTC_OK = 0,
    DRV_RTC_ERROR,
    DRV_RTC_WARNING,
    DRV_RTC_PENDING,
    DRV_RTC_INVALID_PARAM
}DrvRtcRetCode_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern bool gbRtcLostTime;

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** DrvRtcInit
 * @brief Initialize RTC
 *
 * @param None
 *
 * @return RTC_OK                       : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcInit(void);

/** DrvRtcSetTime
 * @brief Sets the Incense RTC time with the given argument
 *
 * @param RtcTime	                      : RTC time
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcSetTime (vm_rtcTimeFormat_t *RtcTime);

/**
 * @brief Gets the Incense RTC time in the given argument
 *
 * @param RtcTime	                      : RTC time
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcGetTime (vm_rtcTimeFormat_t *RtcTime);

/**
 * @brief Mask any alarm from RTC and reset alarm registers
 *
 * @param None
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcStopAlarm(void);

/**
 * @brief Program alarm register and enable alarm
 *
 * @param RtcTime	                      : RTC time
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcSetAlarm(vm_rtcTimeFormat_t * RtcAlarm);

/**
 * @brief Get present configured alarm
 *
 * @param RtcTime	                      : RTC time
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcGetAlarm(vm_rtcTimeFormat_t  *RtcAlarm);

/**
 * @brief Sets a calendar event. The caller will get a weekly, monthly of yearly IRQ
 *
 * @param event	                        : Calendar Event to set (there can be only one at the same time)
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcSetCalendarEvent(vm_rtcCalendarEvent_t event);

/**
 * @brief Gets the present calendar event.
 *
 * @param event	                        : Calendar Event to get (there can be only one at the same time)
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcGetCalendarEvent(vm_rtcCalendarEvent_t *event);

/**
 * @brief Stops the present calendar event.
 *
 * @param None
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcStopCalendarEvent(void);

/**
 * @brief Sets a Tick event. The caller will get a minute (1st second of every minute)
 *        or hour (1st second of every hour), or midnight or noon IRQ message.
 *
 * @param tick_type                     :Type of Tick Event to set (there can be only one at the same time)
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcSetTick(vm_rtcTickType_t tick_type);

/**
 * @brief Gets the present Tick event.
 *
 * @param tick_type                     : Tick Event to get (there can be only one at the same time)
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcGetTick(vm_rtcTickType_t *tick_type);

/**
 * @brief Stops the present calendar event.
 *
 * @param None
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcStopTick(void);

/**
 * @brief Called by Incense IRQ handler when a Incense IRQ is detected, to check whether
 *
 * @param None
 *
 * @return None
 */
DrvRtcRetCode_e DrvRtcCheckIrq(void);

/**
 * @brief Defines the mailbox that will receive alarm and tick messages
 *
 * @param mailbox                       :mailbox in which tick messages or alarms will be sent
 *
 * @return None
 */
DrvRtcRetCode_e DrvRtcSubscribe (u8 mailbox);


/**
 * @brief Clear pending Power Cut and RTC Lost Time IRQ
 *
 * @param None
 *
 * @return None
 */
DrvRtcRetCode_e DrvRtcClearIrq(void);

/**
 * @brief Check if a RTC alarm is the cause of the Wake-up
 *
 * @param None
 *
 * @return RTC_OK       				        : Function open request success
 * @return RTC_ERROR                    : Function open request fail
 */
DrvRtcRetCode_e DrvRtcGetStatus(s8 *pRet);

/**
 * @brief Controls the PWR_EN pin, typically used to shutdown the baseband with the PMU
 *
 * @param enable                        : Power on/off
 *
 * @return None
 */
DrvRtcRetCode_e DrvRtcPowerCtrl(bool enable);

/**
 * @brief Get RTC Counter
 *
 * @param None
 *
 * @return RTC Count value
 */
DrvRtcRetCode_e DrvRtcGetCount(u32 *pConfigValue);

/**
 * @brief Get RTC current time in second base
 *
 * @param None
 *
 * @return RTC Count value in second base
 */
DrvRtcRetCode_e DrvRtcGetSecondCount(u32 *pSecondCount);

/** DrvRtcCheckPowerOnCause
* @brief        Check poweron cause
* @retval       PowerOnCause_e error code
*
*/
DrvRtcRetCode_e DrvRtcCheckPowerOnAlarm(bool *pbAlarmPowerOn);

/** DrvRtcCheckReset
* @brief        Check RTC reset
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcCheckReset(void);

/** DrvRtcIsReset
* @brief        Check RTC reset
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcIsReset(bool *pbIsReset);

/** DrvRtcGetUTCSecondCount
* @brief        Get RTC current time in UTC second base
* @para         RTC Count value in UTC second base
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcGetUTCSecondCount(u32 *pSecondCount);

/** DrvRtcGetRange
* @brief        Get minimal and maximal RTC time
* @para         Minimal RTC time
* @para         Maximal RTC time
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcGetRange(vm_rtcTimeFormat_t *pMinRtcTime, vm_rtcTimeFormat_t *pMaxRtcTime);

/** DrvRtcBackupTime
* @brief        Backup RTC time
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcBackupTime(vm_rtcTimeFormat_t *tRtcTime);

/** DrvRtcResetBackupTime
* @brief        Reset backup RTC time
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcResetBackupTime(void);

/** DrvRtcEnableBackupTime
* @brief        Enable backup RTC time
* @retval       DrvRtcRetCode_e error code
*
*/
DrvRtcRetCode_e DrvRtcEnableBackupTime(void);


/**
 * \fn DrvRtcRetCode_e DrvRtcSetAbbrstFlag(void)
 * \brief Set Abbrst Flag
 * \return Success, DRV_RTC_OK; Other, Failed.
 */
DrvRtcRetCode_e DrvRtcSetAbbrstFlag(void);

/**
 * \fn bool DrvRtcAbbrstHappened(void)
 * \brief Check if Abbrst happened
 * \return Success, TRUE; Other, FALSE.
 */
bool DrvRtcAbbrstHappened(void);

#endif //__DRV_RTC_H__

