//==============================================================================
//
//  File        : mmpf_rtc_ctl.h
//  Description : INCLUDE File for the RTC Driver Function
//  Author      : Jerry Li
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_RTC_CTL_H_
#define _MMPF_RTC_CTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "mmp_rtc_inc.h"
#include "aitu_calendar.h"

/** @addtogroup MMPF_RTC
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define RTC_SEMAPHORE_TIMEOUT   (1000)
#define RTC_DBG_LEVEL           (3)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _RTC_WKALRM
{
    MMP_BOOL 	bEnable;			/* 0 = alarm disabled, 1 = alarm enabled */
    MMP_UBYTE 	ubPending;  		/* 0 = alarm not pending, 1 = alarm pending */
    struct _AUTL_DATETIME sTime;	/* Time the alarm is set to */
    RtcAlarmCallBackFunc *pRTCCB;	/* AIT specific function */
} RTC_WKALRM;

typedef struct _3RD_PARTY_RTC
{
    //0
    MMP_ERR (*fpMMPF_RTC_Open)(struct _3RD_PARTY_RTC *);
    MMP_ERR (*fpMMPF_RTC_Release)(struct _3RD_PARTY_RTC *);
    MMP_ERR (*fpMMPF_RTC_Ioctl)(struct _3RD_PARTY_RTC *, MMP_ULONG, MMP_U_LONG);
    MMP_ERR (*fpMMPF_RTC_Read_Time)(struct _3RD_PARTY_RTC *, AUTL_DATETIME *data);
    MMP_ERR (*fpMMPF_RTC_Read_ShadowTime)(struct _3RD_PARTY_RTC *, AUTL_DATETIME *data);
    //5
    MMP_ERR (*fpMMPF_RTC_Set_Time)(struct _3RD_PARTY_RTC *, AUTL_DATETIME *data);
    MMP_ERR (*fpMMPF_RTC_Read_Alarm)(struct _3RD_PARTY_RTC *, RTC_WKALRM *alrm);
    MMP_ERR (*fpMMPF_RTC_Set_Alarm)(struct _3RD_PARTY_RTC *, RTC_WKALRM *alrm);
    MMP_ERR (*fpMMPF_RTC_Set_Mmss)(struct _3RD_PARTY_RTC *, MMP_U_LONG secs);
    MMP_ERR (*fpMMPF_RTC_Read_Callback)(struct _3RD_PARTY_RTC *, MMP_LONG data);
    //10
    MMP_ERR (*fpMMPF_RTC_Alarm_Irq_Enable)(struct _3RD_PARTY_RTC *, MMP_ULONG enabled);
	MMP_ERR (*fpMMPF_RTC_Read_BaseTime)(struct _3RD_PARTY_RTC *, MMP_LONG *data);
} THIRD_PARTY_RTC;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_RTC_CTL_Open(void);
MMP_ERR	MMPF_RTC_CTL_Release(void);
MMP_ERR MMPF_RTC_CTL_Ioctl(MMP_ULONG cmd, MMP_U_LONG arg);
MMP_ERR MMPF_RTC_CTL_Read_Time(AUTL_DATETIME *pDate);
MMP_ERR MMPF_RTC_CTL_Read_ShadowTime(AUTL_DATETIME *pDate);
MMP_ERR MMPF_RTC_CTL_Set_Time(AUTL_DATETIME *pDate);
MMP_ERR MMPF_RTC_CTL_Read_Alarm(RTC_WKALRM *pAlarm);
MMP_ERR MMPF_RTC_CTL_Set_Alarm(RTC_WKALRM *pAlarm);
MMP_ERR MMPF_RTC_CTL_Set_Mmss(MMP_U_LONG secs);
MMP_ERR MMPF_RTC_CTL_Read_Callback(MMP_LONG data);
MMP_ERR MMPF_RTC_CTL_Alarm_Irq_Enable(MMP_ULONG enabled);
MMP_ERR MMPF_RTC_CTL_Read_BaseTime(MMP_ULONG *date);
void 	MMPF_RTC_CTL_Register(struct _3RD_PARTY_RTC *pdev_obj);
void 	MMPF_RTC_CTL_UnRegister(void);

#endif // _MMPF_RTC_CTL_H_
