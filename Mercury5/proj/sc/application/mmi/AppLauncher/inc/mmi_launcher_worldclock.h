#ifndef __WCLOCK_H__
#define __WCLOCK_H__


#include "mmi_launcher_common.h"
#include "mmi_mae_clock_forward.h" //for MAE_TimeZone_Field_e

/// 1. ShortCut Srv,  APM_Mode = APM_LAUNCH_EMBEDDED, param = WORLDCLOCK_PARAM_t, Mode = WCLK_PICKUP_MODE
///                   APM_Mode = APM_LAUNCH_EMBEDDED, param = WORLDCLOCK_PARAM_t, Mode = WCLK_NORMAL_MODE

typedef enum
{
	WCLOCK_TIMEZONE_PRIMARY = 0,   // Primary timezone stored in config item
	WCLOCK_TIMEZONE_SECONDARY,     // Secondary timezone stored in config item
	WCLOCK_TIMEZONE_MAX = WCLOCK_TIMEZONE_SECONDARY,
    WCLOCK_TIMEZONE_NUM,
	WCLOCK_TIMEZONE_INVALID,
} WClock_TimeZone_Field_e;

/// URL Format: "WClock://SetTimeZone?APM_Mode=%d&TimeZone=%d"
/// No Response Data Callback
void  LaunchWorldClockAppToSetTimeZone
(
  AppLaunchMode_e eAppLaunchMode,
  WClock_TimeZone_Field_e eTimezoneField,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
typedef enum
{
    WCLK_NORMAL_MODE = 0, // Normal mode to view time of each timezone/city
    WCLK_PICKUP_MODE,     // Pickup time zone
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    WCLK_WIDGET_CLOCK1_MODE, // Pickup time zone for widget settings
    WCLK_WIDGET_CLOCK2_MODE,
    WCLK_WIDGET_CLOCK3_MODE,
    WCLK_WIDGET_CLOCK4_MODE,
#endif
} WorldClockAppMode_e;

typedef struct
{
    WorldClockAppMode_e     eMode;
    MAE_TimeZone_Field_e    ePickupTz;
	CmnAppLaunchRspCbInfo_t sCallerRspCBInfo;
} WorldClockAppParam_t;

typedef enum
{
    WCLOCK_TIMEZONE_WIDGET_CLOCK_START = 0,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_1,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_2,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_3,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_4,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_MAX = WCLOCK_TIMEZONE_WIDGET_CLOCK_4,
    WCLOCK_TIMEZONE_WIDGET_CLOCK_NUM,
	WCLOCK_TIMEZONE_WIDGET_CLOCK_INVALID,
} WClock_WidgetClock_Field_e;

void  LaunchWorldClockAppToSetWidgetTimeZone
(
  AppLaunchMode_e eAppLaunchMode,
  WClock_WidgetClock_Field_e eWidgetClockField,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif/* __WCLOCK_H__ */
