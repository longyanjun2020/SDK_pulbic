//==============================================================================
//
//  File        : mmps_rtc.h
//  Description : INCLUDE File for the RTC
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_rtc.h
 *  @brief Header File for the RTC API.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPS_RTC_H_
#define _MMPS_RTC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 

#include "mmpd_rtc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPS_RTC_Initialize(void);
MMP_ERR MMPS_RTC_SetTime(AUTL_DATETIME *datetime);
MMP_ERR MMPS_RTC_GetTime(AUTL_DATETIME *datetime);
MMP_ERR MMPS_RTC_SetWakeUpEn(MMP_BOOL bEnable, AUTL_DATETIME *datetime,
                             RtcAlarmCallBackFunc *cb);

#endif // _MMPS_RTC_H_