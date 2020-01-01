//==============================================================================
//
//  File        : mmps_rtc.c
//  Description : RTC Functions.
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_rtc.c
 *  @brief The rtc control functions
 *  @author Ben Lu
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 
 
#include "mmp_lib.h"
#include "mmps_rtc.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPS_RTC_Initialize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Initialize RTC

 @return the status of the operation.
*/
MMP_ERR MMPS_RTC_Initialize(void)
{
    return MMPD_RTC_Initialize();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_RTC_SetTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set RTC

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[in] datetime : Date time information
 @return the status of the operation.
*/
MMP_ERR MMPS_RTC_SetTime(AUTL_DATETIME *datetime)
{
    return MMPD_RTC_SetTime(datetime);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_RTC_GetTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get RTC

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[out] datetime : Date time information
 @return the ssatus of the operation.
*/
MMP_ERR MMPS_RTC_GetTime(AUTL_DATETIME *datetime)
{
    return MMPD_RTC_GetTime(datetime);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_RTC_SetWakeUpEn
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set wake up counter of RTC unit

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[in] bEnable : Enable/Disable RTC wake up 
 @param[in] datetime : Date time information
 @param[in] cb : Callback function during alarming
 @return the status of the operation.
*/
MMP_ERR MMPS_RTC_SetWakeUpEn(MMP_BOOL bEnable, AUTL_DATETIME *datetime,
                             RtcAlarmCallBackFunc *cb)
{
	return MMPD_RTC_SetWakeUpEn(bEnable, datetime, cb);
}
