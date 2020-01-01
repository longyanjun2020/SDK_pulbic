/**
 * @file    mmi_sys_cfg.h
 *
 * @brief   This file is auto generate by XRG tool. Do not modify file directly
 *
 * @version $Id:$
 *
 * @time
 */

#ifndef __MMI_SYS_CFG__H__
#define __MMI_SYS_CFG__H__


#define ONOFFAPP_MAX_ONOFF_RECORD_SIZE (20)
#define ONOFFAPP_MAX_SYS_DBG_STK_SIZE (210)
#define SYS_HIGH_SPEEF_TASK_DBG_RAI_ARRAY_SIZE (20)
#define SYS_HIGH_SPEEF_TASK_DBG_CLIENT_ARRAY_SIZE (3)
#define SYS_SMS_CRASH_NUMBER (20)
enum
{
    SYS_TZ_GMTminus1100=0,
    SYS_TZ_GMTminus1000=1,
    SYS_TZ_GMTminus0900=2,
    SYS_TZ_GMTminus0900_1=3,
    SYS_TZ_GMTminus0800=4,
    SYS_TZ_GMTminus0700=5,
    SYS_TZ_GMTminus0600=6,
    SYS_TZ_GMTminus0600_1=7,
    SYS_TZ_GMTminus0500=8,
    SYS_TZ_GMTminus0430=9,
    SYS_TZ_GMTminus0400=10,
    SYS_TZ_GMTminus0330=11,
    SYS_TZ_GMTminus0330_1=12,
    SYS_TZ_GMTminus0300=13,
    SYS_TZ_GMTminus0200=14,
    SYS_TZ_GMTminus0100=15,
    SYS_TZ_GMTminus0100_1=16,
    SYS_TZ_GMTminus0000=17,
    SYS_TZ_GMTminus0000_1=18,
    SYS_TZ_GMTplus0100=19,
    SYS_TZ_GMTplus0100_1=20,
    SYS_TZ_GMTplus0200=21,
    SYS_TZ_GMTplus0200_1=22,
    SYS_TZ_GMTplus0300=23,
    SYS_TZ_GMTplus0300_1=24,
    SYS_TZ_GMTplus0330=25,
    SYS_TZ_GMTplus0330_1=26,
    SYS_TZ_GMTplus0400=27,
    SYS_TZ_GMTplus0430=28,
    SYS_TZ_GMTplus0500=29,
    SYS_TZ_GMTplus0530=30,
    SYS_TZ_GMTplus0545=31,
    SYS_TZ_GMTplus0600=32,
    SYS_TZ_GMTplus0700=33,
    SYS_TZ_GMTplus0800=34,
    SYS_TZ_GMTplus0900=35,
    SYS_TZ_GMTplus0930=36,
    SYS_TZ_GMTplus1000=37,
    SYS_TZ_GMTplus1000_1=38,
    SYS_TZ_GMTplus1100=39,
    SYS_TZ_GMTplus1200=40,
    SYS_TZ_GMTminus0300_1=41,
    SYS_TZ_GMTminus0700_1=42,
    SYS_TZ_GMTminus0800_1=43,
    SYS_TZ_GMTplus1200_1=44,
    SYS_TZ_GMTminus1200=45,
    SYS_TZ_GMTminus0930=46,
    SYS_TZ_GMTminus0230=47,
    SYS_TZ_GMTplus0630=48,
    SYS_TZ_GMTplus0845=49,
    SYS_TZ_GMTplus1030=50,
    SYS_TZ_GMTplus1130=51,
    SYS_TZ_GMTplus1245=52,
    SYS_TZ_GMTplus1300=53,
    SYS_TZ_GMTplus1345=54,
    SYS_TZ_GMTplus1400=55,
};
typedef u32 SysTimeZoneType_e;
enum
{
    SYS_DEBUG_OFF=0,
    SYS_DEBUG_ON=1
};
typedef u8 SYS_DEBUG_FLAG_e;
enum
{
    ONOFF_Type_None=0,
    ONOFF_Type_On=1,
    ONOFF_Type_Off=2
};
typedef u8 ONOFF_Type_e;
enum
{
    ONOFF_Cause_Unknow=0,
    ONOFF_Cause_Normal=1,
    ONOFF_Cause_Auto=2,
    ONOFF_Cause_Alarm=3,
    ONOFF_Cause_Charging=4,
    ONOFF_Cause_Powercut=5,
    ONOFF_Cause_ATCommand=6,
    ONOFF_Cause_STKRefresh=7,
    ONOFF_Cause_Reset=8,
    ONOFF_Cause_TimeEvt=9,
    ONOFF_Cause_SWReset=10,
    ONOFF_Cause_NormalKeyRelease=11,
    ONOFF_Cause_Others=12,
    ONOFF_Cause_Lowbattery=13,
    ONOFF_Cause_Last=14
};
typedef u8 ONOFF_Cause_e;
enum
{
    SYS_SMS_CRASH_LOG_DISABLE,
    SYS_SMS_CRASH_LOG_ENABLE
};
typedef u8 SYS_SMS_CRASH_LOG_FLAG_e;
enum
{
    SYS_USB_MENU_ENABLE=0,
    SYS_USB_MENU_DISABLE
};
typedef u8 SYS_USB_MENU_FLAG_e;
enum
{
    SYS_SMS_RESEND_DISABLE=1,
    SYS_SMS_RESEND_ENABLE=0
};
typedef u8 SYS_SMS_RESEND_FLAG_e;
typedef struct SysFactoryDefaultTime_TAG
{
    u16 nYear;
    u8 nMonth;
    u8 nDay;
} SysFactoryDefaultTime_t;
typedef struct _ONOFF_Record_Data_t
{
    ONOFF_Type_e eType;
    ONOFF_Cause_e eCause;
    u16 nVoltage;
    u32 nDateTime;
} ONOFF_Record_Data_t;
typedef struct _ONOFF_Record_List_t
{
    ONOFF_Record_Data_t astRecord[ONOFFAPP_MAX_ONOFF_RECORD_SIZE];
} ONOFF_Record_List_t;

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
typedef struct _High_CPU_Task_Record_Data_t
{
    boolean bFirstBoot;
    u32 eClient[4];
    u32 nDateTime;
} High_CPU_Task_Record_Data_t;

typedef struct _High_CPU_Task_List_t
{
    u8 nCount;
    High_CPU_Task_Record_Data_t astRecord[SYS_HIGH_SPEEF_TASK_DBG_RAI_ARRAY_SIZE];
} High_CPU_Task_List_t;
#endif

typedef struct
{
	u8					Id;
    char				TaskName[8];
	u32					Type;
	void*				TopOfStack;
 	u16					StackSize;
	u32					MaxUsage;
} CFG_SysTaskStkInfo_t;

typedef struct
{
    u32                     nMax;
    u32                     nTotalQueried;
    CFG_SysTaskStkInfo_t    Info[ONOFFAPP_MAX_SYS_DBG_STK_SIZE];
} CFG_SysTaskStkDebug_t;

#endif /* __MMI_SYS_CFG__H__ */



