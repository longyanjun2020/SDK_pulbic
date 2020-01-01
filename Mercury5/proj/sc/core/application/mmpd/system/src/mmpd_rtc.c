//==============================================================================
//
//  File        : mmpd_rtc.c
//  Description : RTC Functions.
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmpd_rtc.c
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
#include "mmpd_rtc.h"
#include "mmpf_rtc.h"
#include "mmpf_rtc_ctl.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPD_RTC_Initialize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Initialize RTC

 @param: none
 @return the status of the operation.
*/
MMP_ERR MMPD_RTC_Initialize(void)
{
    return MMPF_RTC_CTL_Open();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_RTC_SetTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set RTC

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[in] datetime : Date time information
 @return the status of the operation.
*/
MMP_ERR MMPD_RTC_SetTime(AUTL_DATETIME *pDatetime)
{
    return MMPF_RTC_CTL_Set_Time(pDatetime);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_RTC_GetTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get RTC

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[out] datetime : Date time information
 @return the status of the operation.
*/
MMP_ERR MMPD_RTC_GetTime(AUTL_DATETIME *pDatetime)
{
    return MMPF_RTC_CTL_Read_Time(pDatetime);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_RTC_SetWakeUpEn
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
MMP_ERR MMPD_RTC_SetWakeUpEn(MMP_BOOL bEnable, AUTL_DATETIME *pDatetime,
                             RtcAlarmCallBackFunc *cb)
{
    RTC_WKALRM sRTC_Alarm;
    
    sRTC_Alarm.bEnable 		= bEnable;
    sRTC_Alarm.ubPending 	= 0;
    sRTC_Alarm.sTime 		= *pDatetime;
    sRTC_Alarm.pRTCCB 		= cb;    
    
    return MMPF_RTC_CTL_Set_Alarm(&sRTC_Alarm);
}
