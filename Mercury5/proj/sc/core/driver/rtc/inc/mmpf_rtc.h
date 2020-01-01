//==============================================================================
//
//  File        : mmpf_rtc.h
//  Description : INCLUDE File for RTC Control Interface
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_RTC_H_
#define _MMPF_RTC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "aitu_calendar.h"
#include "mmp_rtc_inc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_RTC_Initialize(void);
MMP_BOOL MMPF_RTC_IsValid(void);
MMP_BOOL MMPF_RTC_SecondsToDate(MMP_ULONG ulSeconds, AUTL_DATETIME *pTime);
MMP_ERR	MMPF_RTC_SetTime(AUTL_DATETIME *pTime);
MMP_ERR MMPF_RTC_GetTime(AUTL_DATETIME *pTime);
MMP_ERR MMPF_RTC_GetShadowTime(AUTL_DATETIME *pTime);
MMP_ULONG MMPF_RTC_GetTime_InSeconds(void);
MMP_ERR MMPF_RTC_SetAlarmEnable(MMP_BOOL bEnable, AUTL_DATETIME *pTime,
                                RtcAlarmCallBackFunc *cb);

#endif //_MMPF_RTC_H_