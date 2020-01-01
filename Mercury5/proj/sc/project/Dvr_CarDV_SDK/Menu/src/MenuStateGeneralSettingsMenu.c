/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_common.h"
#include "ahc_gui.h"
#include "ahc_gsensor.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_display.h"
#include "ahc_browser.h"
#include "ahc_video.h"
#include "ahc_warningmsg.h"
#include "ahc_capture.h"
#include "ahc_sensor.h"
#include "ahc_message.h"
#include "ahc_os.h"
#include "ahc_version.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuSetting.h"
#include "MenuTouchButton.h"
#include "MenuStateGeneralSettingsMenu.h"
#include "MenuDrawingGeneralSettingsFunc.h"
#include "MenuStateManualSettingMenu.h"
#include "MenuDrawCommon.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "ShowOSDFunc.h"
#include "statebrowserfunc.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "ledcontrol.h"
#if (SUPPORT_GSENSOR)
#include "GSensor_ctrl.h"
#endif
#if (GPS_CONNECT_ENABLE)
#include "gps_ctl.h"
#endif
#ifdef _OEM_MENU_
#include "Oem_Menu.h"
#endif

/*===========================================================================
 * Local function
 *===========================================================================*/

UINT32   SubMenuEventHandler_ClockSetting(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   SubMenuEventHandler_ResetSetup(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   SubMenuEventHandler_FwVersionInfo(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   SubMenuEventHandler_GPSInfoChart(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   MenuGetDefault_GeneralSetting(PSMENUSTRUCT pMenu );
#if (VIRTUAL_KEY_BOARD)
UINT32  SubMenuEventHandler_Keyboard(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam );
#endif

AHC_BOOL MenuItemBeep(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemLCDBrightness(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemAutoPowerOff(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemClockSettings(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemDateTimeFormat(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemDateLogoStamp(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemGPSStamp(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSpeedStamp(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemLanguage(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemTVSystem(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemHDMIOutput(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemResetSetup(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFwVersion(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemGPSInfo(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFlickerHz(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemUSBSelect(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemLCDRotate(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemLCDPowerSave(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemLEDFlash(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemGsensorSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemGsensorPowerOnSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMotionDtcSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemTimeZone(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemBootUpMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemNightModeSelect(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemWiFiMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
#if (VIRTUAL_KEY_BOARD)
AHC_BOOL MenuItemKeyboard(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif

void MenuItemDateTimeFormatToAhcTimeStampSetting(void);

#if (MENU_RD_LDWS_CALIBRATION_EN)
AHC_BOOL MenuItemLdwsCalibration(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
AHC_BOOL MenuItemUserLdwsCalibration(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN || MENU_GENERAL_PQ_BRIGHTNESS_EN || MENU_GENERAL_PQ_SATURATION_EN)
AHC_BOOL MenuItemPQAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
AHC_BOOL MenuItemPQColorTemp(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif

/*===========================================================================
 * Global variable : Touch Menu
 *===========================================================================*/

/*===========================================================================
 * Extern variable : Item
 *===========================================================================*/

#if (TOP_MENU_PAGE_EN)
extern SMENUITEM sItemFormatCard;
extern SMENUITEM sItemSDCardINFO;
#endif

extern int Setpf_GSNR_THR(int value);
extern int Getpf_GSNR_THR(void);
/*===========================================================================
 * Global variable : Menu
 *===========================================================================*/

SMENUSTRUCT sMainMenuGeneral;

SMENUSTRUCT sSubBeep;
SMENUSTRUCT sSubLCDBrightness;
SMENUSTRUCT sSubAutoPowerOff;
SMENUSTRUCT sSubClockSettings;
SMENUSTRUCT sSubDateTimeFormat;
SMENUSTRUCT sSubDateLogoStamp;
SMENUSTRUCT sSubGPSStamp;
SMENUSTRUCT sSubSpeedStamp;
SMENUSTRUCT sSubLanguage;
SMENUSTRUCT sSubTVSystem;
SMENUSTRUCT sSubHDMIOutput;
SMENUSTRUCT sSubResetSetup;
SMENUSTRUCT sSubFwVersionInfo;
SMENUSTRUCT sSubGPSInfo;
SMENUSTRUCT sSubFlickerHz;
SMENUSTRUCT sSubUSBSelect;
SMENUSTRUCT sSubLCDRotate;
SMENUSTRUCT sSubLCDPowerSave;
SMENUSTRUCT sSubLEDFlash;
SMENUSTRUCT sSubGsensorSensitivity;
SMENUSTRUCT sSubPowerOnGsensorSensitivity;
SMENUSTRUCT sSubMotionDtcSensitivity;
SMENUSTRUCT sSubTimeZone;
SMENUSTRUCT sSubBootUpMode;
SMENUSTRUCT sSubNightMode;
SMENUSTRUCT sSubWiFiMode;
#if (VIRTUAL_KEY_BOARD)
SMENUSTRUCT sSubVirtualKeyboard;
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
SMENUSTRUCT sSubLdwsCalibration;
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
SMENUSTRUCT sSubUserLdwsCalibration;
#endif
#if (MENU_GENERAL_PQ_CONTRAST_EN)
SMENUSTRUCT sSubPQContrast;
#endif
#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
SMENUSTRUCT sSubPQBrightness;
#endif
#if (MENU_GENERAL_PQ_SATURATION_EN)
SMENUSTRUCT sSubPQSaturation;
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
SMENUSTRUCT sSubPQColorTemp;
#endif
/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/

// Beep
#if (MENU_GENERAL_BEEP_EN)
SMENUITEM sItemBeep                 = { ITEMID_BEEP,     &BMICON_MENU_BEEP,    IDS_DS_BEEP, &sSubBeep, 0,     0, AHC_TRUE, NULL };
#if (MENU_GENERAL_BEEP_ON_EN)
SMENUITEM sItemBeep_On              = { ITEMID_BEEP_ON,  &BMICON_OPTION_OPEN,  IDS_DS_ON, NULL, MenuItemBeep, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_BEEP_OFF_EN)
SMENUITEM sItemBeep_Off             = { ITEMID_BEEP_OFF, &BMICON_OPTION_CLOSE, IDS_DS_OFF,NULL, MenuItemBeep, 0, AHC_TRUE, NULL };
#endif
#endif

// LCD Brightness
#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
SMENUITEM sItemLCDBrightness        = { ITEMID_LCD_BRIGHTNESS,    NULL, IDS_DS_LCD_BRIGHTNESS,  &sSubLCDBrightness, 0,  0, AHC_TRUE, NULL };
#if (MENU_GENERAL_LCD_BRIGHTNESS_NORMAL_EN)
SMENUITEM sItemLCDBrightness_Normal = { ITEMID_LCD_BRIGHT_NORMAL, NULL, IDS_DS_NORMAL,  NULL, MenuItemLCDBrightness,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LCD_BRIGHTNESS_BRIGHTNESS_EN)
SMENUITEM sItemLCDBrightness_Bright = { ITEMID_LCD_BRIGHT_BRIGHT, NULL, IDS_DS_BRIGHT,  NULL, MenuItemLCDBrightness,    0, AHC_TRUE, NULL };
#endif
#endif

// Power Save
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
SMENUITEM sItemAutoPowerOff          = { ITEMID_AUTO_POWER_OFF,       &BMICON_MENU_AUTO_OFF, IDS_DS_POWER_OFF,  &sSubAutoPowerOff, 0, 0, AHC_TRUE, NULL };
#if (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
SMENUITEM sItemAutoPowerOff_Never    = { ITEMID_AUTO_POWER_OFF_NEVER, &BMICON_OPTION_CLOSE,  IDS_DS_POWER_OFF_NEVER,    NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
SMENUITEM sItemAutoPowerOff_15Second = { ITEMID_AUTO_POWER_OFF_15SEC, &BMICON_CLIPTIME_1MIN, IDS_DS_POWER_OFF_15SEC,    NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
SMENUITEM sItemAutoPowerOff_30Second = { ITEMID_AUTO_POWER_OFF_30SEC, &BMICON_CLIPTIME_1MIN, IDS_TIME_30SEC,    NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
SMENUITEM sItemAutoPowerOff_1Minutes = { ITEMID_AUTO_POWER_OFF_1MIN,  &BMICON_CLIPTIME_1MIN, IDS_TIME_1MIN,     NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
SMENUITEM sItemAutoPowerOff_2Minutes = { ITEMID_AUTO_POWER_OFF_2MIN,  &BMICON_CLIPTIME_1MIN, IDS_TIME_2MIN,     NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
SMENUITEM sItemAutoPowerOff_3Minutes = { ITEMID_AUTO_POWER_OFF_3MIN,  &BMICON_CLIPTIME_1MIN, IDS_TIME_3MIN,     NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
SMENUITEM sItemAutoPowerOff_5Minutes = { ITEMID_AUTO_POWER_OFF_5MIN,  &BMICON_CLIPTIME_5MIN, IDS_TIME_5MIN,     NULL,   MenuItemAutoPowerOff, 0, AHC_TRUE, NULL };
#endif
#endif

// Clock Settings
#if (MENU_GENERAL_CLOCK_SETTING_EN)
SMENUITEM sItemClockSettings        = { ITEMID_CLOCK_SETTINGS, &BMICON_MENU_CLOCK, IDS_DS_CLOCK_SETTINGS,   &sSubClockSettings, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Year   = { ITEMID_DATETIME_YEAR,   NULL, IDS_DS_DATETIME_Y,    NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Month  = { ITEMID_DATETIME_MONTH,  NULL, IDS_DS_DATETIME_M,    NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Day    = { ITEMID_DATETIME_DAY,    NULL, IDS_DS_DATETIME_D,    NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Hour   = { ITEMID_DATETIME_HOUR,   NULL, IDS_DS_DATETIME_H,    NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Minute = { ITEMID_DATETIME_MINUTE, NULL, IDS_DS_DATETIME_MM,   NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Sec    = { ITEMID_DATETIME_SEC,    NULL, IDS_DS_DATETIME_S,    NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_OK     = { ITEMID_DATETIME_OK,     NULL, IDS_DS_OK,            NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
SMENUITEM sItemClockSettings_Cancel = { ITEMID_DATETIME_CANCEL, NULL, IDS_DS_CANCEL,        NULL, MenuItemClockSettings, 0, AHC_TRUE, NULL };
#endif

// Date/Time Format
#if (MENU_GENERAL_DATE_FORMAT_EN)
SMENUITEM sItemDateTimeFormat       = { ITEMID_DATETIME_FORMAT, &BMICON_MENU_DATE, IDS_DS_DATETIME_FORMAT, &sSubDateTimeFormat, 0, 0, AHC_TRUE, NULL };
#if (MENU_GENERAL_DATE_FORMAT_NONE_EN)
SMENUITEM sItemDateTime_None        = { ITEMID_DATETIME_NONE, &BMICON_OPTION_CLOSE,  IDS_DS_NONE,        NULL, MenuItemDateTimeFormat, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_FORMAT_YMD_EN)
SMENUITEM sItemDateTime_YMD         = { ITEMID_DATETIME_YMD,  &BMICON_DATE1_ENGLISH, IDS_DS_DATETIME_YMD,NULL, MenuItemDateTimeFormat, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_FORMAT_MDY_EN)
SMENUITEM sItemDateTime_MDY         = { ITEMID_DATETIME_MDY,  &BMICON_DATE2_ENGLISH, IDS_DS_DATETIME_MDY,NULL, MenuItemDateTimeFormat, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_FORMAT_DMY_EN)
SMENUITEM sItemDateTime_DMY         = { ITEMID_DATETIME_DMY,  &BMICON_DATE3_ENGLISH, IDS_DS_DATETIME_DMY,NULL, MenuItemDateTimeFormat, 0, AHC_TRUE, NULL };
#endif
#endif

// Time/Logo Stamp
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
SMENUITEM sItemDateLogoStamp        = { ITEMID_DATE_LOGO_STAMP, NULL, IDS_DS_STAMP, &sSubDateLogoStamp, 0, 0, AHC_TRUE, NULL };
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN)
SMENUITEM sItemStampDateLogo        = { ITEMID_STAMP_DATELOGO,  NULL, IDS_DS_STAMP_DATELOGO,    NULL, MenuItemDateLogoStamp, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN)
SMENUITEM sItemStampDate            = { ITEMID_STAMP_DATE,      NULL, IDS_DS_STAMP_DATE,        NULL, MenuItemDateLogoStamp, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN)
SMENUITEM sItemStampLogo            = { ITEMID_STAMP_LOGO,      NULL, IDS_DS_STAMP_LOGO,        NULL, MenuItemDateLogoStamp, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN)
SMENUITEM sItemStampOFF             = { ITEMID_STAMP_OFF,       NULL, IDS_DS_OFF,       NULL, MenuItemDateLogoStamp, 0, AHC_TRUE, NULL };
#endif
#endif

// GPS Stamp
#if (MENU_GENERAL_GPS_STAMP_EN)
SMENUITEM sItemGPSStamp         = { ITEMID_GPS_STAMP,           NULL,       IDS_DS_STAMP,   &sSubGPSStamp, 0,   0, AHC_TRUE, NULL };
#if (MENU_GENERAL_GPS_STAMP_ON_EN)
SMENUITEM sItemGPSStampOn       = { ITEMID_GPS_STAMP_ON,        &BMICON_OPTION_OPEN,    IDS_DS_ON,  NULL, MenuItemGPSStamp, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GPS_STAMP_OFF_EN)
SMENUITEM sItemGPSStampOff      = { ITEMID_GPS_STAMP_OFF,       &BMICON_OPTION_CLOSE,   IDS_DS_OFF, NULL, MenuItemGPSStamp, 0, AHC_TRUE, NULL };
#endif
#endif

// Speed Stamp
#if (MENU_GENERAL_SPEED_STAMP_EN)
SMENUITEM sItemSpeedStamp       = { ITEMID_SPEED_STAMP,         NULL, IDS_DS_STAMP,     &sSubSpeedStamp, 0,       0, AHC_TRUE, NULL };
#if (MENU_GENERAL_SPEED_STAMP_ON_EN)
SMENUITEM sItemSpeedStampOn     = { ITEMID_SPEED_STAMP_ON,      &BMICON_OPTION_OPEN,    IDS_DS_ON,  NULL, MenuItemSpeedStamp, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_SPEED_STAMP_OFF_EN)
SMENUITEM sItemSpeedStampOff    = { ITEMID_SPEED_STAMP_OFF,     &BMICON_OPTION_CLOSE,   IDS_DS_OFF, NULL, MenuItemSpeedStamp, 0, AHC_TRUE, NULL };
#endif
#endif

// Language
#if (MENU_GENERAL_LANGUAGE_EN)
SMENUITEM sItemLanguage             = { ITEMID_LANGUAGE,                &BMICON_MENU_LANG,      IDS_DS_LANGUAGE,                &sSubLanguage, 0,       0, AHC_TRUE, NULL };
#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
SMENUITEM sItemLanguage_English     = { ITEMID_LANGUAGES_ENGLISH,       &BMICON_LANG_ENGLISH,   IDS_DS_LANGUAGES_ENGLISH,       NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
SMENUITEM sItemLanguage_Spanish     = { ITEMID_LANGUAGES_SPANISH,       &BMICON_LANG_SPAIN,     IDS_DS_LANGUAGES_SPANISH,       NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
SMENUITEM sItemLanguage_Portuguese  = { ITEMID_LANGUAGES_PORTUGUESE,    &BMICON_LANG_PORTUGAL,  IDS_DS_LANGUAGES_PORTUGUESE,    NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
SMENUITEM sItemLanguage_Russian     = { ITEMID_LANGUAGES_RUSSIAN,       &BMICON_LANG_RUSSIA,    IDS_DS_LANGUAGES_RUSSIAN,       NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
SMENUITEM sItemLanguage_SChinese    = { ITEMID_LANGUAGES_SCHINESE,      &BMICON_LANG_SCHINESE,  IDS_DS_LANGUAGES_SCHINESE,      NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
SMENUITEM sItemLanguage_TChinese    = { ITEMID_LANGUAGES_TCHINESE,      &BMICON_LANG_TCHINESE,  IDS_DS_LANGUAGES_TCHINESE,      NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
SMENUITEM sItemLanguage_German     = { ITEMID_LANGUAGES_GERMAN,         NULL,                   IDS_DS_LANGUAGES_GERMAN,        NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
SMENUITEM sItemLanguage_Italian    = { ITEMID_LANGUAGES_ITALIAN,        NULL,                   IDS_DS_LANGUAGES_ITALIAN,       NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
SMENUITEM sItemLanguage_Latvian     = { ITEMID_LANGUAGES_LATVIAN,       NULL,                   IDS_DS_LANGUAGES_LATVIAN,       NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
SMENUITEM sItemLanguage_Polish      = { ITEMID_LANGUAGES_POLISH,        &BMICON_LANG_POLISH,    IDS_DS_LANGUAGES_POLISH,        NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
SMENUITEM sItemLanguage_Romanian    = { ITEMID_LANGUAGES_ROMANIAN,      NULL,                   IDS_DS_LANGUAGES_ROMANIAN,      NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
SMENUITEM sItemLanguage_Slovak      = { ITEMID_LANGUAGES_SLOVAK,        NULL,                   IDS_DS_LANGUAGES_SLOVAK,        NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
SMENUITEM sItemLanguage_Ukraninian  = { ITEMID_LANGUAGES_UKRANINIAN,    NULL,                   IDS_DS_LANGUAGES_UKRANINIAN,    NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
SMENUITEM sItemLanguage_French      = { ITEMID_LANGUAGES_FRENCH,        NULL,                   IDS_DS_LANGUAGES_FRENCH,        NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
SMENUITEM sItemLanguage_Japanese    = { ITEMID_LANGUAGES_JAPANESE,      NULL,                   IDS_DS_LANGUAGES_JAPANESE,      NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
SMENUITEM sItemLanguage_Korean      = { ITEMID_LANGUAGES_KOREAN,        NULL,                   IDS_DS_LANGUAGES_KOREAN,        NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
SMENUITEM sItemLanguage_Czech       = { ITEMID_LANGUAGES_CZECH,         NULL,                   IDS_DS_LANGUAGES_CZECH,         NULL, MenuItemLanguage, 0, AHC_TRUE, NULL };
#endif
#endif

// TV System
#if (MENU_GENERAL_TV_SYSTEM_EN)
SMENUITEM sItemTVSystem             = { ITEMID_TV_SYSTEM, &BMICON_MENU_TVOUT,   IDS_DS_TV_SYSTEM,   &sSubTVSystem, 0,   0, AHC_TRUE, NULL };
#if (MENU_GENERAL_TV_SYSTEM_NTSC_EN)
SMENUITEM sItemTVSystem_NTSC        = { ITEMID_TV_NTSC,   &BMICON_TV_NTSC,      IDS_DS_TV_NTSC, NULL, MenuItemTVSystem, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_TV_SYSTEM_PAL_EN)
SMENUITEM sItemTVSystem_PAL         = { ITEMID_TV_PAL,    &BMICON_TV_PAL,       IDS_DS_TV_PAL,  NULL, MenuItemTVSystem, 0, AHC_TRUE, NULL };
#endif
#endif

// HDMI Output
#if (MENU_GENERAL_HDMI_OUTPUT_EN)
SMENUITEM sItemHDMIOutput           = { ITEMID_HDMI_OUTPUT,       &BMICON_MENU_HDMI,  IDS_DS_HDMI_OUTPUT,       &sSubHDMIOutput, 0,       0, AHC_TRUE, NULL };
#if (MENU_GENERAL_HDMI_OUTPUT_1080P_EN)
SMENUITEM sItemHDMIOutput_1080P     = { ITEMID_HDMI_OUTPUT_1080P, &BMICON_HDMI_1080P, IDS_DS_HDMI_OUTPUT_1080P, NULL, MenuItemHDMIOutput, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_1080I_EN)
SMENUITEM sItemHDMIOutput_1080i     = { ITEMID_HDMI_OUTPUT_1080I, &BMICON_HDMI_1080I, IDS_DS_HDMI_OUTPUT_1080I, NULL, MenuItemHDMIOutput, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_720P_EN)
SMENUITEM sItemHDMIOutput_720P      = { ITEMID_HDMI_OUTPUT_720P,  &BMICON_HDMI_720P,  IDS_DS_HDMI_OUTPUT_720P,  NULL, MenuItemHDMIOutput, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_480P_EN)
SMENUITEM sItemHDMIOutput_480P      = { ITEMID_HDMI_OUTPUT_480P,  &BMICON_HDMI_480P,  IDS_DS_HDMI_OUTPUT_480P,  NULL, MenuItemHDMIOutput, 0, AHC_TRUE, NULL };
#endif
#endif

// Reset Setup
#if (MENU_GENERAL_RESET_SETUP_EN)
SMENUITEM sItemResetSetup           = { ITEMID_RESET_SETUP, &BMICON_MENU_RESET, IDS_DS_RESET_SETUP, &sSubResetSetup, 0, 0, AHC_TRUE, NULL };
#if (MENU_GENERAL_RESET_SETUP_YES_EN)
SMENUITEM sItemResetSetup_Yes       = { ITEMID_RESET_YES,   &BMICON_OPTION_YES, IDS_DS_YES, NULL, MenuItemResetSetup, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_RESET_SETUP_NO_EN)
SMENUITEM sItemResetSetup_No        = { ITEMID_RESET_NO,    &BMICON_OPTION_NO,  IDS_DS_NO,  NULL, MenuItemResetSetup, 0, AHC_TRUE, NULL };
#endif
#endif

// FW Version Info
#if (MENU_GENERAL_FW_VERSION_EN)
SMENUITEM sItemFWVersionInfo        = { ITEMID_FW_VERSION_INFO, &BMICON_MENU_FW_VER, IDS_DS_FW_VERSION_INFO, &sSubFwVersionInfo, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemFWVersion            = { ITEMID_FW_VERSION, NULL, IDS_DS_FW_VERSION, NULL, MenuItemFwVersion, 0, AHC_TRUE, NULL };
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
SMENUITEM sItemLdwsCalibration      = { ITEMID_LDWS_CALIBRATION, &BMICON_LDWS_CALI, IDS_DS_LDWS_CALI, &sSubLdwsCalibration, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemLdwscab              = { ITEMID_SUB_LDWS_CALIBRATION, NULL, IDS_DS_LDWS_CALI, NULL, MenuItemLdwsCalibration, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
SMENUITEM sItemUserLdwsCalibration  = { ITEMID_USER_LDWS_CALIBRATION, &BMICON_LDWS_CALI, IDS_DS_LDWS_CALI, &sSubUserLdwsCalibration, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemUserLdwscab          = { ITEMID_SUB_USER_LDWS_CALIBRATION, NULL, IDS_DS_LDWS_CALI, NULL, MenuItemUserLdwsCalibration, 0, AHC_TRUE, NULL };
#endif

// GPS Status
#if (MENU_GENERAL_GPSINFO_EN)
SMENUITEM sItemGPSInfoChart         = { ITEMID_GPS_INFO_CHART, &BMICON_MENU_GPS, IDS_DS_GPS_INFO_STATUS, &sSubGPSInfo, 0,       0, AHC_TRUE, NULL };
SMENUITEM sItemGPSInfo              = { ITEMID_GPS_INFO,        NULL,            IDS_DS_GPS_INFO_STATUS, NULL, MenuItemGPSInfo, 0, AHC_TRUE, NULL };
#endif

// Flicker Hz
#if (MENU_GENERAL_FLICKER_EN)
SMENUITEM sItemFlickerHz            = { ITEMID_FLICKER,         &BMICON_MENU_FLICK,   IDS_DS_FLICKER,   &sSubFlickerHz,         0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_FLICKER_50HZ_EN)
SMENUITEM sItemFlicker50Hz          = { ITEMID_FLICKER_50HZ,    &BMICON_FLICKER_50HZ, IDS_FLICKER_50HZ,     NULL, MenuItemFlickerHz,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_FLICKER_60HZ_EN)
SMENUITEM sItemFlicker60Hz          = { ITEMID_FLICKER_60HZ,    &BMICON_FLICKER_60HZ, IDS_FLICKER_60HZ,     NULL, MenuItemFlickerHz,    0, AHC_TRUE, NULL };
#endif
#endif

// USB Function Selection
#if (MENU_GENERAL_USB_FUNCTION_EN)
SMENUITEM sItemUSBFunction          = { ITEMID_USB_FUNCTION,    &BMICON_MENU_USB, IDS_USB_FUNCTION, &sSubUSBSelect,     0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_USB_FUNCTION_MSDC_EN)
SMENUITEM sItemUSBFunction_MSDC     = { ITEMID_USB_MSDC,        &BMICON_USB_MSDC, IDS_MSDC_MODE,    NULL, MenuItemUSBSelect,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_USB_FUNCTION_PCAM_EN)
SMENUITEM sItemUSBFunction_PCam     = { ITEMID_USB_PCAM,        &BMICON_USB_PCAM, IDS_PCAM_MODE,    NULL, MenuItemUSBSelect,    0, AHC_TRUE, NULL };
#endif
#endif

// LCD Rotate
#if (MENU_GENERAL_LCD_ROTATE_EN)
SMENUITEM sItemLCDRotate            = { ITEMID_LCD_ROTATE,      &BMICON_MENU_FLIP,    IDS_DS_LCD_ROTATE,    &sSubLCDRotate,     0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_LCD_ROTATE_ON_EN)
SMENUITEM sItemLCDRotate_On         = { ITEMID_LCD_ROTATE_ON,   &BMICON_OPTION_OPEN,  IDS_DS_ON,    NULL, MenuItemLCDRotate,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LCD_ROTATE_OFF_EN)
SMENUITEM sItemLCDRotate_Off        = { ITEMID_LCD_ROTATE_OFF,  &BMICON_OPTION_CLOSE, IDS_DS_OFF,   NULL, MenuItemLCDRotate,    0, AHC_TRUE, NULL };
#endif
#endif

// LCD Power Save
#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
SMENUITEM sItemLCDPowerSave         = { ITEMID_LCD_POWER_SAVE,      &BMICON_MENU_LCDPOWER, IDS_DS_LCD_POWER_SAVE,   &sSubLCDPowerSave,      0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
SMENUITEM sItemLCDPowerSave_Off     = { ITEMID_LCD_POWER_SAVE_OFF,  &BMICON_OPTION_CLOSE,  IDS_DS_OFF,      NULL, MenuItemLCDPowerSave,     0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
SMENUITEM sItemLCDPowerSave_1min    = { ITEMID_LCD_POWER_SAVE_1MIN, &BMICON_CLIPTIME_1MIN, IDS_TIME_1MIN,   NULL, MenuItemLCDPowerSave,     0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
SMENUITEM sItemLCDPowerSave_3min    = { ITEMID_LCD_POWER_SAVE_3MIN, &BMICON_CLIPTIME_3MIN, IDS_TIME_3MIN,   NULL, MenuItemLCDPowerSave,     0, AHC_TRUE, NULL };
#endif
#endif

// LED Flash
#if (MENU_GENERAL_FLASH_LED_EN)
SMENUITEM sItemLEDFlash             = { ITEMID_LED_FLASH,       NULL, IDS_DS_LED_LIGHT,     &sSubLEDFlash,  0,          0, AHC_TRUE, NULL };
#if (MENU_GENERAL_FLASH_LED_ON_EN)
SMENUITEM sItemLEDFlash_On          = { ITEMID_LED_FLASH_ON,    &BMICON_OPTION_OPEN,  IDS_DS_ON,    NULL, MenuItemLEDFlash,     0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_FLASH_LED_OFF_EN)
SMENUITEM sItemLEDFlash_Off         = { ITEMID_LED_FLASH_OFF,   &BMICON_OPTION_CLOSE, IDS_DS_OFF,   NULL, MenuItemLEDFlash,     0, AHC_TRUE, NULL };
#endif
#endif

// G-sensor Sensitivity, 5 - level
#if (MENU_GENERAL_GSENSOR_EN==GSENSOR_5_LEVEL)

SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY,     &BMICON_MENU_GSNR_SENS, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0,      0, AHC_TRUE, NULL };

#if (MENU_GENERAL_GSENSOR_OFF_EN)
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF, &BMICON_OPTION_CLOSE, IDS_DS_OFF,                       NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0,  &BMICON_GSNR_LV0, IDS_DS_GSENSOR_SENSITIVETY_LEVEL0,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
SMENUITEM sItemGsensorSensitivity_L1    = { ITEMID_GSENSOR_SENSITIVITY_L1,  &BMICON_GSNR_LV1, IDS_DS_GSENSOR_SENSITIVETY_LEVEL1,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2,  &BMICON_GSNR_LV2, IDS_DS_GSENSOR_SENSITIVETY_LEVEL2,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
SMENUITEM sItemGsensorSensitivity_L3    = { ITEMID_GSENSOR_SENSITIVITY_L3,  &BMICON_GSNR_LV3, IDS_DS_GSENSOR_SENSITIVETY_LEVEL3,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4,  &BMICON_GSNR_LV4, IDS_DS_GSENSOR_SENSITIVETY_LEVEL4,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
#endif
#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_4_LEVEL)
// G-sensor Sensitivity, 4 - level
SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY,     &BMICON_MENU_GSNR_SENS, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0,      0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF, &BMICON_OPTION_CLOSE,   IDS_DS_OFF,     NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0,  &BMICON_GSNR_LV0,       IDS_DS_HIGH,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L1    = { ITEMID_GSENSOR_SENSITIVITY_L1,  &BMICON_GSNR_LV1,       IDS_DS_MIDDLE,  NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2,  &BMICON_GSNR_LV2,       IDS_DS_LOW,     NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4,  &BMICON_GSNR_LV4,       IDS_DS_STANDARD,  NULL, MenuItemGsensorSensitivity,     0, AHC_TRUE, NULL };
#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_3_LEVEL)
// G-sensor Sensitivity, 3 - level
SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY,     &BMICON_MENU_GSNR_SENS, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0,      0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF, &BMICON_OPTION_CLOSE,   IDS_DS_OFF,     NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0,  &BMICON_GSNR_LV_H,      IDS_DS_HIGH,    NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2,  &BMICON_GSNR_LV_M,      IDS_DS_MIDDLE,  NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4,  &BMICON_GSNR_LV_L,      IDS_DS_LOW,     NULL, MenuItemGsensorSensitivity,   0, AHC_TRUE, NULL };

#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
SMENUITEM sItemPowerOnGsensorSensitivity    = { ITEMID_GSENSOR_POWERON_SENSITIVITY,     &BMICON_MENU_GSEN_POWER_ON, IDS_DS_POWERON_GSENSOR_SENSITIVETY,         &sSubPowerOnGsensorSensitivity,     0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_Off    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_OFF,  &BMICON_OPTION_CLOSE, IDS_DS_OFF,      NULL, MenuItemGsensorPowerOnSensitivity,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L0    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L0,  &BMICON_GSNR_POWERON_LV_H, IDS_DS_HIGH,      NULL, MenuItemGsensorPowerOnSensitivity,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L1    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L1,  &BMICON_GSNR_POWERON_LV_M, IDS_DS_MIDDLE,    NULL, MenuItemGsensorPowerOnSensitivity,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L2    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L2,  &BMICON_GSNR_POWERON_LV_L, IDS_DS_LOW,   NULL, MenuItemGsensorPowerOnSensitivity,    0, AHC_TRUE, NULL };
#endif
#endif
// Motion Detection Sensitivity
#if (MENU_GENERAL_MOTION_DTC_EN)
SMENUITEM sItemMotionDtcSensitivity     = { ITEMID_MOTION_DETECT,       &BMICON_MENU_MTD, IDS_DS_MOTION_DETECTION,  &sSubMotionDtcSensitivity,  0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_MOTION_DTC_OFF_EN)
SMENUITEM sItemMotionDtcSensitivity_Off = { ITEMID_MOTION_DETECT_OFF,   &BMICON_OPTION_CLOSE, IDS_DS_OFF,   NULL, MenuItemMotionDtcSensitivity,     0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_MOTION_DTC_LOW_EN)
SMENUITEM sItemMotionDtcSensitivity_Low = { ITEMID_MOTION_DETECT_LOW,   &BMICON_MTD_L, IDS_DS_LOW,      NULL, MenuItemMotionDtcSensitivity,     0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_MOTION_DTC_MID_EN)
SMENUITEM sItemMotionDtcSensitivity_Mid = { ITEMID_MOTION_DETECT_MID,   &BMICON_MTD_M, IDS_DS_MIDDLE,NULL, MenuItemMotionDtcSensitivity,    0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
SMENUITEM sItemMotionDtcSensitivity_High= { ITEMID_MOTION_DETECT_HIGH,  &BMICON_MTD_H, IDS_DS_HIGH,  NULL, MenuItemMotionDtcSensitivity,    0, AHC_TRUE, NULL };
#endif
#endif

// Time Zone
#if (MENU_GENERAL_TIME_ZONE_EN)
SMENUITEM sItemTimeZone            = { ITEMID_TIME_ZONE,             &BMICON_MENU_TIMEZONE,     IDS_DS_TIME_ZONE,   &sSubTimeZone,  0,      0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_12       = { ITEMID_TIME_ZONE_GMT_M_12,    &BMICON_TIMEZONE_N12,      IDS_DS_TIME_ZONE_GMT_M_12,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_11       = { ITEMID_TIME_ZONE_GMT_M_11,    &BMICON_TIMEZONE_N11,      IDS_DS_TIME_ZONE_GMT_M_11,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_10       = { ITEMID_TIME_ZONE_GMT_M_10,    &BMICON_TIMEZONE_N10,      IDS_DS_TIME_ZONE_GMT_M_10,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_9        = { ITEMID_TIME_ZONE_GMT_M_9 ,    &BMICON_TIMEZONE_N09,      IDS_DS_TIME_ZONE_GMT_M_9,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_8        = { ITEMID_TIME_ZONE_GMT_M_8 ,    &BMICON_TIMEZONE_N08,      IDS_DS_TIME_ZONE_GMT_M_8,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_7        = { ITEMID_TIME_ZONE_GMT_M_7 ,    &BMICON_TIMEZONE_N07,      IDS_DS_TIME_ZONE_GMT_M_7,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_6        = { ITEMID_TIME_ZONE_GMT_M_6 ,    &BMICON_TIMEZONE_N06,      IDS_DS_TIME_ZONE_GMT_M_6,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_5        = { ITEMID_TIME_ZONE_GMT_M_5 ,    &BMICON_TIMEZONE_N05,      IDS_DS_TIME_ZONE_GMT_M_5,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_4        = { ITEMID_TIME_ZONE_GMT_M_4 ,    &BMICON_TIMEZONE_N04,      IDS_DS_TIME_ZONE_GMT_M_4,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_3_30     = { ITEMID_TIME_ZONE_GMT_M_3_30 , &BMICON_TIMEZONE_N0330,    IDS_DS_TIME_ZONE_GMT_M_3_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_3        = { ITEMID_TIME_ZONE_GMT_M_3 ,    &BMICON_TIMEZONE_N03,      IDS_DS_TIME_ZONE_GMT_M_3,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_2        = { ITEMID_TIME_ZONE_GMT_M_2 ,    &BMICON_TIMEZONE_N02,      IDS_DS_TIME_ZONE_GMT_M_2,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_M_1        = { ITEMID_TIME_ZONE_GMT_M_1 ,    &BMICON_TIMEZONE_N01,      IDS_DS_TIME_ZONE_GMT_M_1,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_GMT        = { ITEMID_TIME_ZONE_GMT     ,    &BMICON_TIMEZONE_00,       IDS_DS_TIME_ZONE_GMT,        NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_1        = { ITEMID_TIME_ZONE_GMT_P_1 ,    &BMICON_TIMEZONE_P01,      IDS_DS_TIME_ZONE_GMT_P_1,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_2        = { ITEMID_TIME_ZONE_GMT_P_2 ,    &BMICON_TIMEZONE_P02,      IDS_DS_TIME_ZONE_GMT_P_2,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_3        = { ITEMID_TIME_ZONE_GMT_P_3 ,    &BMICON_TIMEZONE_P03,      IDS_DS_TIME_ZONE_GMT_P_3,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_3_30     = { ITEMID_TIME_ZONE_GMT_P_3_30 , &BMICON_TIMEZONE_P0330,    IDS_DS_TIME_ZONE_GMT_P_3_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_4        = { ITEMID_TIME_ZONE_GMT_P_4 ,    &BMICON_TIMEZONE_P04,      IDS_DS_TIME_ZONE_GMT_P_4,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_4_30     = { ITEMID_TIME_ZONE_GMT_P_4_30 , &BMICON_TIMEZONE_P0430,    IDS_DS_TIME_ZONE_GMT_P_4_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_5        = { ITEMID_TIME_ZONE_GMT_P_5 ,    &BMICON_TIMEZONE_P05,      IDS_DS_TIME_ZONE_GMT_P_5,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_5_30     = { ITEMID_TIME_ZONE_GMT_P_5_30 , &BMICON_TIMEZONE_P0530,    IDS_DS_TIME_ZONE_GMT_P_5_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_5_45     = { ITEMID_TIME_ZONE_GMT_P_5_45 , &BMICON_TIMEZONE_P0545,    IDS_DS_TIME_ZONE_GMT_P_5_45, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_6        = { ITEMID_TIME_ZONE_GMT_P_6 ,    &BMICON_TIMEZONE_P06,      IDS_DS_TIME_ZONE_GMT_P_6,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_6_30     = { ITEMID_TIME_ZONE_GMT_P_6_30 , &BMICON_TIMEZONE_P0630,    IDS_DS_TIME_ZONE_GMT_P_6_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_7        = { ITEMID_TIME_ZONE_GMT_P_7 ,    &BMICON_TIMEZONE_P07,      IDS_DS_TIME_ZONE_GMT_P_7,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_8        = { ITEMID_TIME_ZONE_GMT_P_8 ,    &BMICON_TIMEZONE_P08,      IDS_DS_TIME_ZONE_GMT_P_8,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_9        = { ITEMID_TIME_ZONE_GMT_P_9 ,    &BMICON_TIMEZONE_P09,      IDS_DS_TIME_ZONE_GMT_P_9,    NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_9_30     = { ITEMID_TIME_ZONE_GMT_P_9_30 , &BMICON_TIMEZONE_P0930,    IDS_DS_TIME_ZONE_GMT_P_9_30, NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_10       = { ITEMID_TIME_ZONE_GMT_P_10 ,   &BMICON_TIMEZONE_P10,      IDS_DS_TIME_ZONE_GMT_P_10,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_11       = { ITEMID_TIME_ZONE_GMT_P_11 ,   &BMICON_TIMEZONE_P11,      IDS_DS_TIME_ZONE_GMT_P_11,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_12       = { ITEMID_TIME_ZONE_GMT_P_12 ,   &BMICON_TIMEZONE_P12,      IDS_DS_TIME_ZONE_GMT_P_12,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
SMENUITEM sItemTimeZone_P_13       = { ITEMID_TIME_ZONE_GMT_P_13 ,   &BMICON_TIMEZONE_P13,      IDS_DS_TIME_ZONE_GMT_P_13,   NULL, MenuItemTimeZone, 0, AHC_TRUE, NULL };
#endif

// Boot Up Mode Selection
#if (MENU_GENERAL_BOOT_UP_MODE_EN)
SMENUITEM sItemBootUpMode           = { ITEMID_BOOTUP_MODE,             &BMICON_MENU_BOOTMODE,      IDS_DS_BOOTUP_MODE, &sSubBootUpMode,    0,              0, AHC_TRUE, NULL };
#if (MENU_GENERAL_BOOT_UP_VR_MODE_EN)
SMENUITEM sItemBootUpMode_VR        = { ITEMID_BOOTUP_MODE_VR,          &BMICON_BOOTUP_VIDEO,       IDS_DS_RECORD_EX,       NULL, MenuItemBootUpMode,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_BOOT_UP_DSC_MODE_EN)
SMENUITEM sItemBootUpMode_DSC       = { ITEMID_BOOTUP_MODE_DSC,         &BMICON_BOOTUP_DSC,         IDS_DSC_MODE_EX,        NULL, MenuItemBootUpMode,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_BOOT_UP_BURST_MODE_EN)
SMENUITEM sItemBootUpMode_Burst     = { ITEMID_BOOTUP_MODE_BURST,       &BMICON_BOOTUP_BURST,       IDS_DS_BURST_CAPTURE_EX,NULL, MenuItemBootUpMode,   0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_BOOT_UP_TIMELAPSE_MODE_EN)
SMENUITEM sItemBootUpMode_TimeLapse = { ITEMID_BOOTUP_MODE_TIMELAPSE,   &BMICON_BOOTUP_TIMELAPSE,   IDS_DS_TIMELAPSE_EX,    NULL, MenuItemBootUpMode,   0, AHC_TRUE, NULL };
#endif
#endif

// Night Mode
#if (MENU_GENERAL_NIGHT_MODE_EN)
SMENUITEM sItemNightMode            = { ITEMID_SCENE,           &BMICON_MENU_SCENE, IDS_DS_NIGHT_MODE,  &sSubNightMode, 0,     0, AHC_TRUE, NULL };
SMENUITEM sItemNightMode_NO         = { ITEMID_SCENE_AUTO,      NULL,               IDS_DS_OFF, NULL, MenuItemNightModeSelect, 0, AHC_TRUE, NULL };
SMENUITEM sItemNightMode_YES        = { ITEMID_SCENE_TWILIGHT,  NULL,               IDS_DS_ON,  NULL, MenuItemNightModeSelect, 0, AHC_TRUE, NULL };
#endif

#if (MENU_GENERAL_WIFI_EN)
SMENUITEM sItemWiFiMode             = { ITEMID_WIFI_MODE,           &BMICON_MENU_WIFI, IDS_DS_WIFI, &sSubWiFiMode, 0,      0, AHC_TRUE, NULL };
#if (MENU_GENERAL_WIFI_OFF_EN)
SMENUITEM sItemWiFiMode_NO          = { ITEMID_WIFI_MODE_OFF,       &BMICON_OPTION_CLOSE,               IDS_DS_OFF, NULL, MenuItemWiFiMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_GENERAL_WIFI_ON_EN)
SMENUITEM sItemWiFiMode_YES         = { ITEMID_WIFI_MODE_ON,    &BMICON_OPTION_OPEN,                IDS_DS_ON,  NULL, MenuItemWiFiMode, 0, AHC_TRUE, NULL };
#endif
#endif

#if (VIRTUAL_KEY_BOARD)
SMENUITEM sItemVirualKeyboard       = { ITEMID_VIRUAL_KEYBOARD,     &BMICON_MENU_SCENE, IDS_AUTO_REC,           &sSubVirtualKeyboard, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemKeyboard             = { ITEMID_KEYBOARD,            &BMICON_MENU_SCENE, IDS_DS_FW_VERSION,      NULL, MenuItemKeyboard, 0, AHC_TRUE, NULL };
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
SMENUITEM sItemPQContrast       = { ITMEID_PQ_CONTRAST, &BMICON_MENU_CONTRAST, IDS_DS_CONTRAST, &sSubPQContrast, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQContrastDec    = { ITMEID_PQ_CONTRAST_DEC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQContrastInc    = { ITMEID_PQ_CONTRAST_INC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
SMENUITEM sItemPQBrightness     = { ITEMID_PQ_BRIGHTNESS, &BMICON_MENU_SHARPNESS, IDS_DS_LCD_BRIGHTNESS, &sSubPQBrightness, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQBrightnessDec  = { ITEMID_PQ_BRIGHTNESS_DEC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQBrightnessInc  = { ITEMID_PQ_BRIGHTNESS_INC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
SMENUITEM sItemPQSaturation     = { ITEMID_PQ_SATURATION, &BMICON_MENU_SATURATION, IDS_DS_SATURATION, &sSubPQSaturation, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQSaturationDec  = { ITEMID_PQ_SATURATION_DEC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQSaturationInc  = { ITEMID_PQ_SATURATION_INC, NULL, IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust, 0, AHC_TRUE, NULL };
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
SMENUITEM sItemPQColorTemp      = { ITEMID_PQ_COLORTEMP, &BMICON_MENU_COLOR, IDS_DS_COLORTEMP, &sSubPQColorTemp, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQColorTemp_Off  = { ITEMID_PQ_COLORTEMP_OFF, NULL, IDS_DS_OFF, NULL, MenuItemPQColorTemp, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQColorTemp_MODE1    = { ITEMID_PQ_COLORTEMP_MODE1, NULL, IDS_DS_COLORTEMP_WARMCOLOR, NULL, MenuItemPQColorTemp, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQColorTemp_MODE2    = { ITEMID_PQ_COLORTEMP_MODE2, NULL, IDS_DS_COLORTEMP_COOLCOLOR, NULL, MenuItemPQColorTemp, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQColorTemp_MODE3    = { ITEMID_PQ_COLORTEMP_MODE3, NULL, IDS_DS_COLORTEMP_WARMCOLOR, NULL, MenuItemPQColorTemp, 0, AHC_TRUE, NULL };
SMENUITEM sItemPQColorTemp_MODE4    = { ITEMID_PQ_COLORTEMP_MODE4, NULL, IDS_DS_COLORTEMP_COOLCOLOR, NULL, MenuItemPQColorTemp, 0, AHC_TRUE, NULL };
#endif

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

#if (MENU_GENERAL_BEEP_EN)
PSMENUITEM   sMenuListBeep[] =
{
#if (MENU_GENERAL_BEEP_ON_EN)
    &sItemBeep_On,
#endif
#if (MENU_GENERAL_BEEP_OFF_EN)
    &sItemBeep_Off
#endif
};
#endif

#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
PSMENUITEM   sMenuListLCDBrightness[] =
{
#if (MENU_GENERAL_LCD_BRIGHTNESS_NORMAL_EN)
    &sItemLCDBrightness_Normal,
#endif
#if (MENU_GENERAL_LCD_BRIGHTNESS_BRIGHTNESS_EN)
    &sItemLCDBrightness_Bright
#endif
};
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
PSMENUITEM   sMenuListAutoPowerOff[] =
{
#if (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
    &sItemAutoPowerOff_Never,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
    &sItemAutoPowerOff_15Second,
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
    &sItemAutoPowerOff_30Second,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
    &sItemAutoPowerOff_1Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
    &sItemAutoPowerOff_2Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
    &sItemAutoPowerOff_3Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
    &sItemAutoPowerOff_5Minutes
#endif
};
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
PSMENUITEM   sMenuListClockSettings[] =
{
    &sItemClockSettings_Year,
    &sItemClockSettings_Month,
    &sItemClockSettings_Day,
    &sItemClockSettings_Hour,
    &sItemClockSettings_Minute,
    &sItemClockSettings_Sec,
    &sItemClockSettings_OK
};
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
PSMENUITEM   sMenuListDateTimeFormat[] =
{
#if (MENU_GENERAL_DATE_FORMAT_NONE_EN)
    &sItemDateTime_None,
#endif
#if (MENU_GENERAL_DATE_FORMAT_YMD_EN)
    &sItemDateTime_YMD,
#endif
#if (MENU_GENERAL_DATE_FORMAT_MDY_EN)
    &sItemDateTime_MDY,
#endif
#if (MENU_GENERAL_DATE_FORMAT_DMY_EN)
    &sItemDateTime_DMY
#endif
};
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
PSMENUITEM   sMenuListDateLogoStamp[] =
{
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN)
    &sItemStampDateLogo,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN)
    &sItemStampDate,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN)
    &sItemStampLogo,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN)
    &sItemStampOFF
#endif
};
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
PSMENUITEM   sMenuListGPSStamp[] =
{
#if (MENU_GENERAL_GPS_STAMP_ON_EN)
    &sItemGPSStampOn,
#endif
#if (MENU_GENERAL_GPS_STAMP_OFF_EN)
    &sItemGPSStampOff,
#endif
};
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
PSMENUITEM   sMenuListSpeedStamp[] =
{
#if (MENU_GENERAL_SPEED_STAMP_ON_EN)
    &sItemSpeedStampOn,
#endif
#if (MENU_GENERAL_SPEED_STAMP_OFF_EN)
    &sItemSpeedStampOff,
#endif
};
#endif

#if (MENU_GENERAL_LANGUAGE_EN)

PSMENUITEM   sMenuListLanguage[] =
{
#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
    &sItemLanguage_English,
#endif
#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
    &sItemLanguage_Spanish,
#endif
#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
    &sItemLanguage_Portuguese,
#endif
#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
    &sItemLanguage_Russian,
#endif
#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
    &sItemLanguage_SChinese,
#endif
#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
    &sItemLanguage_TChinese,
#endif
#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
    &sItemLanguage_German,
#endif
#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
    &sItemLanguage_Italian,
#endif
#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
    &sItemLanguage_Latvian,
#endif
#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
    &sItemLanguage_Polish,
#endif
#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
    &sItemLanguage_Romanian,
#endif
#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
    &sItemLanguage_Slovak,
#endif
#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
    &sItemLanguage_Ukraninian,
#endif
#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
    &sItemLanguage_French,
#endif
#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
    &sItemLanguage_Japanese,
#endif
#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
    &sItemLanguage_Korean,
#endif
#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
    &sItemLanguage_Czech,
#endif
};

#endif

#if (MENU_GENERAL_TV_SYSTEM_EN)
PSMENUITEM   sMenuListTVSystem[] =
{
#if (MENU_GENERAL_TV_SYSTEM_NTSC_EN)
    &sItemTVSystem_NTSC,
#endif
#if (MENU_GENERAL_TV_SYSTEM_PAL_EN)
    &sItemTVSystem_PAL
#endif
};
#endif

#if (MENU_GENERAL_HDMI_OUTPUT_EN)
PSMENUITEM   sMenuListHDMIOutput[] =
{
#if (MENU_GENERAL_HDMI_OUTPUT_1080P_EN)
    &sItemHDMIOutput_1080P,
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_1080I_EN)
    &sItemHDMIOutput_1080i,
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_720P_EN)
    &sItemHDMIOutput_720P,
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_480P_EN)
    &sItemHDMIOutput_480P
#endif
};
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
PSMENUITEM   sMenuListResetSetup[] =
{
#if (MENU_GENERAL_RESET_SETUP_YES_EN)
    &sItemResetSetup_Yes,
#endif
#if (MENU_GENERAL_RESET_SETUP_NO_EN)
    &sItemResetSetup_No
#endif
};
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
PSMENUITEM   sMenuListFWVersionInfo[] =
{
    &sItemFWVersion
};
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
PSMENUITEM   sMenuListLdwsCalibration[] =
{
    &sItemLdwscab
};
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
PSMENUITEM   sMenuListUserLdwsCalibration[] =
{
    &sItemUserLdwscab
};
#endif

#if (MENU_GENERAL_GPSINFO_EN)
PSMENUITEM   sMenuListGPSInfo[] =
{
    &sItemGPSInfo
};
#endif

#if (VIRTUAL_KEY_BOARD)
PSMENUITEM sMenuListVirtualKeyboard[] =
{
    &sItemKeyboard
};
#endif

#if (MENU_GENERAL_FLICKER_EN)
PSMENUITEM   sMenuListFlickerHz[] =
{
#if (MENU_GENERAL_FLICKER_50HZ_EN)
    &sItemFlicker50Hz,
#endif
#if (MENU_GENERAL_FLICKER_60HZ_EN)
    &sItemFlicker60Hz
#endif
};
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
PSMENUITEM   sMenuListUSBFunction[] =
{
#if (MENU_GENERAL_USB_FUNCTION_MSDC_EN)
    &sItemUSBFunction_MSDC,
#endif
#if (MENU_GENERAL_USB_FUNCTION_PCAM_EN)
    &sItemUSBFunction_PCam
#endif
};
#endif

#if (MENU_GENERAL_LCD_ROTATE_EN)
PSMENUITEM   sMenuListLCDRotate[] =
{
#if (MENU_GENERAL_LCD_ROTATE_ON_EN)
    &sItemLCDRotate_On,
#endif
#if (MENU_GENERAL_LCD_ROTATE_OFF_EN)
    &sItemLCDRotate_Off
#endif
};
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
PSMENUITEM   sMenuListLCDPowerSave[] =
{
#if (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
    &sItemLCDPowerSave_Off,
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
    &sItemLCDPowerSave_1min,
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
    &sItemLCDPowerSave_3min
#endif
};
#endif

#if (MENU_GENERAL_FLASH_LED_EN)
PSMENUITEM   sMenuListLEDFlash[] =
{
#if (MENU_GENERAL_FLASH_LED_ON_EN)
    &sItemLEDFlash_On,
#endif
#if (MENU_GENERAL_FLASH_LED_OFF_EN)
    &sItemLEDFlash_Off
#endif
};
#endif

#if (MENU_GENERAL_GSENSOR_EN==GSENSOR_5_LEVEL)
PSMENUITEM   sMenuListGsensorSensitivity[] =
{
#if (MENU_GENERAL_GSENSOR_OFF_EN)
    &sItemGsensorSensitivity_Off,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
    &sItemGsensorSensitivity_L0,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
    &sItemGsensorSensitivity_L1,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
    &sItemGsensorSensitivity_L2,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
    &sItemGsensorSensitivity_L3,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
    &sItemGsensorSensitivity_L4
#endif
};

#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_4_LEVEL)

PSMENUITEM   sMenuListGsensorSensitivity[] =
{
    &sItemGsensorSensitivity_Off,
    &sItemGsensorSensitivity_L0,    // High
    &sItemGsensorSensitivity_L2,    // Middle
    &sItemGsensorSensitivity_L3,    // Low
    &sItemGsensorSensitivity_L4     // Standard
};

#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_3_LEVEL)

PSMENUITEM   sMenuListGsensorSensitivity[] =
{
    &sItemGsensorSensitivity_Off,
    &sItemGsensorSensitivity_L0,
    &sItemGsensorSensitivity_L2,
    &sItemGsensorSensitivity_L4
};
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
PSMENUITEM   sMenuListPowerOnGsensorSensitivity[] =
{
#if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
    &sItemPowerOnGsensorSensitivity_Off,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
    &sItemPowerOnGsensorSensitivity_L0,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
    &sItemPowerOnGsensorSensitivity_L1,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
    &sItemPowerOnGsensorSensitivity_L2
#endif
};
#endif



#if (MENU_GENERAL_MOTION_DTC_EN)
PSMENUITEM   sMenuListMotionDtcSensitivity[] =
{
#if (MENU_GENERAL_MOTION_DTC_OFF_EN)
    &sItemMotionDtcSensitivity_Off,
#endif
#if (MENU_GENERAL_MOTION_DTC_LOW_EN)
    &sItemMotionDtcSensitivity_Low,
#endif
#if (MENU_GENERAL_MOTION_DTC_MID_EN)
    &sItemMotionDtcSensitivity_Mid,
#endif
#if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
    &sItemMotionDtcSensitivity_High,
#endif
};
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
PSMENUITEM   sMenuListTimeZone[] =
{
    &sItemTimeZone_M_12,
    &sItemTimeZone_M_11,
    &sItemTimeZone_M_10,
    &sItemTimeZone_M_9,
    &sItemTimeZone_M_8,
    &sItemTimeZone_M_7,
    &sItemTimeZone_M_6,
    &sItemTimeZone_M_5,
    &sItemTimeZone_M_4,
    &sItemTimeZone_M_3_30,
    &sItemTimeZone_M_3,
    &sItemTimeZone_M_2,
    &sItemTimeZone_M_1,
    &sItemTimeZone_GMT,
    &sItemTimeZone_P_1,
    &sItemTimeZone_P_2,
    &sItemTimeZone_P_3,
    &sItemTimeZone_P_3_30,
    &sItemTimeZone_P_4,
    &sItemTimeZone_P_4_30,
    &sItemTimeZone_P_5,
    &sItemTimeZone_P_5_30,
    &sItemTimeZone_P_5_45,
    &sItemTimeZone_P_6,
    &sItemTimeZone_P_6_30,
    &sItemTimeZone_P_7,
    &sItemTimeZone_P_8,
    &sItemTimeZone_P_9,
    &sItemTimeZone_P_9_30,
    &sItemTimeZone_P_10,
    &sItemTimeZone_P_11,
    &sItemTimeZone_P_12,
    &sItemTimeZone_P_13
};
#endif

#if (MENU_GENERAL_BOOT_UP_MODE_EN)
PSMENUITEM   sMenuListBootUpMode[] =
{
#if (MENU_GENERAL_BOOT_UP_VR_MODE_EN)
    &sItemBootUpMode_VR,
#endif
#if (MENU_GENERAL_BOOT_UP_DSC_MODE_EN)
    &sItemBootUpMode_DSC,
#endif
#if (MENU_GENERAL_BOOT_UP_BURST_MODE_EN)
    &sItemBootUpMode_Burst,
#endif
#if (MENU_GENERAL_BOOT_UP_TIMELAPSE_MODE_EN)
    &sItemBootUpMode_TimeLapse,
#endif
};
#endif

#if (MENU_GENERAL_NIGHT_MODE_EN)
PSMENUITEM   sMenuListNightMode[] =
{
    &sItemNightMode_NO,
    &sItemNightMode_YES
};
#endif

#if (MENU_GENERAL_WIFI_EN)
PSMENUITEM   sMenuListWiFiMode[] =
{
#if (MENU_GENERAL_WIFI_ON_EN)
    &sItemWiFiMode_YES,
#endif
#if (MENU_GENERAL_WIFI_OFF_EN)
    &sItemWiFiMode_NO
#endif
};
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
PSMENUITEM   sMenuListPQContrast[] =
{
    &sItemPQContrastDec,
    &sItemPQContrastInc
};
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
PSMENUITEM   sMenuListPQBrightness[] =
{
    &sItemPQBrightnessDec,
    &sItemPQBrightnessInc
};
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
PSMENUITEM   sMenuListPQSaturation[] =
{
    &sItemPQSaturationDec,
    &sItemPQSaturationInc
};
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
PSMENUITEM   sMenuListPQColorTemp[] =
{
#if (MENU_GENERAL_PQ_COLORTEMP_OFF_EN)
    &sItemPQColorTemp_Off,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE1_EN)
    &sItemPQColorTemp_MODE1,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE2_EN)
    &sItemPQColorTemp_MODE2,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE3_EN)
    &sItemPQColorTemp_MODE3,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE4_EN)
    &sItemPQColorTemp_MODE4
#endif
};
#endif

PSMENUITEM   sMenuListMainGeneral[]=
{
#if (MENU_GENERAL_BEEP_EN)
    &sItemBeep,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
    &sItemAutoPowerOff,
#endif
#if (MENU_GENERAL_CLOCK_SETTING_EN)
    &sItemClockSettings,
#endif
#if (MENU_GENERAL_DRIVER_ID_SETTING_EN)
    &sItemDriverIdSettings,
#endif
#if (MENU_GENERAL_DATE_FORMAT_EN)
    &sItemDateTimeFormat,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
    &sItemDateLogoStamp,
#endif
#if (MENU_GENERAL_GPS_STAMP_EN)
    &sItemGPSStamp,
#endif
#if (MENU_GENERAL_SPEED_STAMP_EN)
    &sItemSpeedStamp,
#endif
#if (MENU_GENERAL_LANGUAGE_EN)
    &sItemLanguage,
#endif
#if (MENU_GENERAL_TV_SYSTEM_EN)
    &sItemTVSystem,
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_EN)
    &sItemHDMIOutput,
#endif
#if (MENU_GENERAL_FLICKER_EN)
    &sItemFlickerHz,
#endif
#if (MENU_GENERAL_USB_FUNCTION_EN) && defined(SUPPORT_UVC_FUNC)
    &sItemUSBFunction,
#endif
#if (MENU_GENERAL_LCD_ROTATE_EN)
    &sItemLCDRotate,
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
    &sItemLCDPowerSave,
#endif
#if (LED_FLASH_CTRL!=LED_BY_NONE && LED_FLASH_CTRL!=LED_BY_KEY)
    &sItemLEDFlash,
#endif
#if (MENU_GENERAL_GSENSOR_EN)
    &sItemGsensorSensitivity,
#endif
#if (MENU_GENERAL_POWERON_GSENSOR_EN)
    &sItemPowerOnGsensorSensitivity,
#endif
#if (MENU_GENERAL_MOTION_DTC_EN)
    &sItemMotionDtcSensitivity,
#endif
#if (MENU_GENERAL_GPSINFO_EN)
    &sItemGPSInfoChart,
#endif
#if (MENU_GENERAL_TIME_ZONE_EN)
    &sItemTimeZone,
#endif
#if (MENU_GENERAL_BOOT_UP_MODE_EN)
    &sItemBootUpMode,
#endif
#if (MENU_GENERAL_RESET_SETUP_EN)
    &sItemResetSetup,
#endif
#if (MENU_GENERAL_NIGHT_MODE_EN)
    &sItemNightMode,
#endif
#if (MENU_GENERAL_WIFI_EN)
    &sItemWiFiMode,
#endif

#ifdef CFG_MENU_TOP_PAGE_SD //may be defined in config_xxx.h
#if (MENU_MEDIA_FORMAT_SD_EN)
    &sItemFormatCard,
#endif
#if (MENU_MEDIA_SHOW_SD_INFO)
    &sItemSDCardINFO,
#endif
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
    &sItemLdwsCalibration,
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
    &sItemUserLdwsCalibration,
#endif

#if (VIRTUAL_KEY_BOARD)
    &sItemVirualKeyboard,
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
    &sItemFWVersionInfo,
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
    &sItemPQContrast,
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
    &sItemPQBrightness,
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
    &sItemPQSaturation,
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
    &sItemPQColorTemp,
#endif
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuGeneral =
{
    MENUID_MAIN_MENU_GENERAL,
    NULL,
    IDS_DS_GENERAL_SETTINGS,
    NULL,
    sizeof(sMenuListMainGeneral)/sizeof(PSMENUITEM),
    sMenuListMainGeneral,
    MainMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};

//--------------SUB MENU-------------------

#if (MENU_GENERAL_BEEP_EN)
SMENUSTRUCT sSubBeep =
{
    MENUID_SUB_MENU_BEEP,
    NULL,
    IDS_DS_BEEP,
    NULL,
    sizeof(sMenuListBeep)/sizeof(PSMENUITEM),
    sMenuListBeep,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_BEEP_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
SMENUSTRUCT sSubLCDBrightness =
{
    MENUID_SUB_MENU_LCD_BRIGHTNESS,
    NULL,
    IDS_DS_LCD_BRIGHTNESS,
    NULL,
    sizeof(sMenuListLCDBrightness)/sizeof(PSMENUITEM),
    sMenuListLCDBrightness,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LCD_BRIGHTNESS_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
SMENUSTRUCT sSubAutoPowerOff =
{
    MENUID_SUB_MENU_AUTO_POWER_OFF,
    NULL,
    IDS_DS_POWER_OFF,
    NULL,
    sizeof(sMenuListAutoPowerOff)/sizeof(PSMENUITEM),
    sMenuListAutoPowerOff,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_POWER_OFF_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
SMENUSTRUCT sSubClockSettings =
{
    MENUID_SUB_MENU_CLOCK_SETTINGS,
    NULL,
    IDS_DS_CLOCK_SETTINGS,
    NULL,
    sizeof(sMenuListClockSettings)/sizeof(PSMENUITEM),
    sMenuListClockSettings,
    SubMenuEventHandler_ClockSetting, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
SMENUSTRUCT sSubDateTimeFormat =
{
    MENUID_SUB_MENU_DATETIME_FORMAT,
    NULL,
    IDS_DS_DATETIME_FORMAT,
    NULL,
    sizeof(sMenuListDateTimeFormat)/sizeof(PSMENUITEM),
    sMenuListDateTimeFormat,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_DATETIME_FORMAT_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
SMENUSTRUCT sSubDateLogoStamp =
{
    MENUID_SUB_MENU_DATELOGO_STAMP,
    NULL,
    IDS_DS_STAMP,
    NULL,
    sizeof(sMenuListDateLogoStamp)/sizeof(PSMENUITEM),
    sMenuListDateLogoStamp,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_STAMP_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
SMENUSTRUCT sSubGPSStamp =
{
    MENUID_SUB_MENU_GPS_STAMP,
    NULL,
    IDS_DS_STAMP,
    NULL,
    sizeof(sMenuListGPSStamp)/sizeof(PSMENUITEM),
    sMenuListGPSStamp,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_STAMP_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
SMENUSTRUCT sSubSpeedStamp =
{
    MENUID_SUB_MENU_SPEED_STAMP,
    NULL,
    IDS_DS_STAMP,
    NULL,
    sizeof(sMenuListSpeedStamp)/sizeof(PSMENUITEM),
    sMenuListSpeedStamp,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_STAMP_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_LANGUAGE_EN)
SMENUSTRUCT sSubLanguage =
{
    MENUID_SUB_MENU_LANGUAGE,
    NULL,
    IDS_DS_LANGUAGE,
    NULL,
    sizeof(sMenuListLanguage)/sizeof(PSMENUITEM),
    sMenuListLanguage,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LANGUAGE_DESCRIPTION,
    AHC_FALSE,
    0
};

SMENUSTRUCT sMainLanguage =
{
    MENUID_MAIN_LANGUAGE_SET,
    NULL,
    IDS_DS_LANGUAGE,
    NULL,
    sizeof(sMenuListLanguage)/sizeof(PSMENUITEM),
    sMenuListLanguage,
    MainMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LANGUAGE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_TV_SYSTEM_EN)
SMENUSTRUCT sSubTVSystem =
{
    MENUID_SUB_MENU_TV_SYSTEM,
    NULL,
    IDS_DS_TV_SYSTEM,
    NULL,
    sizeof(sMenuListTVSystem)/sizeof(PSMENUITEM),
    sMenuListTVSystem,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_TV_SYSTEM_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_HDMI_OUTPUT_EN)
SMENUSTRUCT sSubHDMIOutput =
{
    MENUID_SUB_MENU_HDMI_OUTPUT,
    NULL,
    IDS_DS_HDMI_OUTPUT,
    NULL,
    sizeof(sMenuListHDMIOutput)/sizeof(PSMENUITEM),
    sMenuListHDMIOutput,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_HDMI_OUTPUT_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
SMENUSTRUCT sSubResetSetup =
{
    MENUID_SUB_MENU_RESET_SETUP,
    NULL,
    IDS_DS_RESET_SETUP,
    NULL,
    sizeof(sMenuListResetSetup)/sizeof(PSMENUITEM),
    sMenuListResetSetup,
    SubMenuEventHandler_ResetSetup, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
SMENUSTRUCT sSubFwVersionInfo =
{
    MENUID_SUB_MENU_FW_VERSION_INFO,
    NULL,
    IDS_DS_FW_VERSION_INFO,
    NULL,
    sizeof(sMenuListFWVersionInfo)/sizeof(PSMENUITEM),
    sMenuListFWVersionInfo,
    SubMenuEventHandler_FwVersionInfo, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
SMENUSTRUCT sSubLdwsCalibration =
{
    MENUID_SUB_MENU_LDWS_CALIBRATION,
    NULL,
    IDS_DS_LDWS_CALI,
    NULL,
    sizeof(sMenuListLdwsCalibration)/sizeof(PSMENUITEM),
    sMenuListLdwsCalibration,
    SubMenuEventHandler_LdwsCalibration,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
SMENUSTRUCT sSubUserLdwsCalibration =
{
    MENUID_SUB_MENU_USER_LDWS_CALIBRATION,
    NULL,
    IDS_DS_LDWS_CALI,
    NULL,
    sizeof(sMenuListUserLdwsCalibration)/sizeof(PSMENUITEM),
    sMenuListUserLdwsCalibration,
    SubMenuEventHandler_UserLdwsCalibration,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_GPSINFO_EN)
SMENUSTRUCT sSubGPSInfo =
{
    MENUID_SUB_MENU_GPS_INFO,
    NULL,
    IDS_DS_GPS_INFO_STATUS,
    NULL,
    sizeof(sMenuListGPSInfo)/sizeof(PSMENUITEM),
    sMenuListGPSInfo,
    SubMenuEventHandler_GPSInfoChart,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_FLICKER_EN)
SMENUSTRUCT sSubFlickerHz =
{
    MENUID_SUB_MENU_FLICKER_FREQUENCY,
    NULL,
    IDS_DS_FLICKER,
    NULL,
    sizeof(sMenuListFlickerHz)/sizeof(PSMENUITEM),
    sMenuListFlickerHz,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_FLICKER,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
SMENUSTRUCT sSubUSBSelect =
{
    MENUID_SUB_MENU_USB_FUNCTION,
    NULL,
    IDS_USB_FUNCTION,
    NULL,
    sizeof(sMenuListUSBFunction)/sizeof(PSMENUITEM),
    sMenuListUSBFunction,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_USB_FUNCTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_LCD_ROTATE_EN)
SMENUSTRUCT sSubLCDRotate =
{
    MENUID_SUB_MENU_LCD_ROTATE,
    NULL,
    IDS_DS_LCD_ROTATE,
    NULL,
    sizeof(sMenuListLCDRotate)/sizeof(PSMENUITEM),
    sMenuListLCDRotate,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LCD_ROTATE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
SMENUSTRUCT sSubLCDPowerSave =
{
    MENUID_SUB_MENU_LCD_POWER_SAVE,
    NULL,
    IDS_DS_LCD_POWER_SAVE,
    NULL,
    sizeof(sMenuListLCDPowerSave)/sizeof(PSMENUITEM),
    sMenuListLCDPowerSave,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LCD_POWER_SAVE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_FLASH_LED_EN)
SMENUSTRUCT sSubLEDFlash =
{
    MENUID_SUB_MENU_LED_FLASH,
    NULL,
    IDS_DS_LED_LIGHT,
    NULL,
    sizeof(sMenuListLEDFlash)/sizeof(PSMENUITEM),
    sMenuListLEDFlash,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_LED_LIGHT,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_GSENSOR_EN)
SMENUSTRUCT sSubGsensorSensitivity =
{
    MENUID_SUB_MENU_GSENSOR_SENSITIVITY,
    NULL,
    IDS_DS_GSENSOR_SENSITIVETY,
    NULL,
    sizeof(sMenuListGsensorSensitivity)/sizeof(PSMENUITEM),
    sMenuListGsensorSensitivity,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_GSENSOR_SENSITIVETY_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
SMENUSTRUCT sSubPowerOnGsensorSensitivity =
{
    MENUID_SUB_MENU_GSENSOR_POWERON_SENSITIVITY,
    NULL,
    IDS_DS_POWERON_GSENSOR_SENSITIVETY,
    NULL,
    sizeof(sMenuListPowerOnGsensorSensitivity)/sizeof(PSMENUITEM),
    sMenuListPowerOnGsensorSensitivity,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_POWERON_GSENSOR_SENSITIVETY,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_MOTION_DTC_EN)
SMENUSTRUCT sSubMotionDtcSensitivity =
{
    MENUID_SUB_MENU_MOTION_DTC_SENSITIVITY,
    NULL,
    IDS_DS_MOTION_DETECTION,
    NULL,
    sizeof(sMenuListMotionDtcSensitivity)/sizeof(PSMENUITEM),
    sMenuListMotionDtcSensitivity,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_MOTION_DETECTION_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
SMENUSTRUCT sSubTimeZone =
{
    MENUID_SUB_MENU_TIME_ZONE,
    NULL,
    IDS_DS_TIME_ZONE,
    NULL,
    sizeof(sMenuListTimeZone)/sizeof(PSMENUITEM),
    sMenuListTimeZone,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_TIME_ZONE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_BOOT_UP_MODE_EN)
SMENUSTRUCT sSubBootUpMode =
{
    MENUID_SUB_MENU_BOOT_UP_MODE,
    NULL,
    IDS_DS_BOOTUP_MODE,
    NULL,
    sizeof(sMenuListBootUpMode)/sizeof(PSMENUITEM),
    sMenuListBootUpMode,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_BOOTUP_MODE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_NIGHT_MODE_EN)
SMENUSTRUCT sSubNightMode =
{
    MENUID_SUB_MENU_NIGHT_MODE,
    NULL,
    IDS_DS_NIGHT_MODE,
    NULL,
    sizeof(sMenuListNightMode)/sizeof(PSMENUITEM),
    sMenuListNightMode,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_NIGHT_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_GENERAL_WIFI_EN)
SMENUSTRUCT sSubWiFiMode =
{
    MENUID_SUB_MENU_WIFI_MODE,
    NULL,
    IDS_DS_WIFI,
    NULL,
    sizeof(sMenuListWiFiMode)/sizeof(PSMENUITEM),
    sMenuListWiFiMode,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    IDS_DS_WIFI,
    AHC_FALSE,
    0
};
#endif

#if (VIRTUAL_KEY_BOARD)
SMENUSTRUCT sSubVirtualKeyboard=
{
    MENUID_SUB_MENU_VURTUAL_KEYBOARD,
    NULL,
    IDS_DS_FW_VERSION_INFO,
    NULL,
    sizeof(sMenuListVirtualKeyboard)/sizeof(PSMENUITEM),
    sMenuListVirtualKeyboard,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
SMENUSTRUCT sSubPQContrast =
{
    MENUID_SUB_MENU_PQ_CONTRAST,
    NULL,
    IDS_DS_CONTRAST,
    NULL,
    sizeof(sMenuListPQContrast)/sizeof(PSMENUITEM),
    sMenuListPQContrast,
    SubMenuEventHandler_PQAdjust,
    MenuGetDefault_GeneralSetting,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
SMENUSTRUCT sSubPQBrightness =
{
    MENUID_SUB_MENU_PQ_BRIGHTNESS,
    NULL,
    IDS_DS_FW_VERSION_INFO,
    NULL,
    sizeof(sMenuListPQBrightness)/sizeof(PSMENUITEM),
    sMenuListPQBrightness,
    SubMenuEventHandler_PQAdjust,
    MenuGetDefault_GeneralSetting,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
SMENUSTRUCT sSubPQSaturation =
{
    MENUID_SUB_MENU_PQ_SATURATION,
    NULL,
    IDS_DS_SATURATION,
    NULL,
    sizeof(sMenuListPQSaturation)/sizeof(PSMENUITEM),
    sMenuListPQSaturation,
    SubMenuEventHandler_PQAdjust,
    MenuGetDefault_GeneralSetting,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
SMENUSTRUCT sSubPQColorTemp =
{
    MENUID_SUB_MENU_PQ_COLORTEMP,
    NULL,
    IDS_DS_COLORTEMP,
    NULL,
    sizeof(sMenuListPQColorTemp)/sizeof(PSMENUITEM),
    sMenuListPQColorTemp,
    SubMenuEventHandler,
    MenuGetDefault_GeneralSetting,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif
/*===========================================================================
 * Global varible
 *===========================================================================*/

AHC_BOOL initDatetime = AHC_TRUE;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern int Datetime[6];

/*===========================================================================
 * Main body
 *===========================================================================*/

AHC_BOOL MenuInitDateTime(void)
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
    UINT8 ubAmOrPm, b_12FormatEn;
    AHC_RTC_TIME    uRTCTime;

    AHC_SetParam(PARAM_ID_USE_RTC,1);

    AHC_RTC_GetTime(&uRTCTime);

    uwYear  = uRTCTime.uwYear;
    uwMonth     = uRTCTime.uwMonth;
    uwDay       = uRTCTime.uwDay;
    uwHour  = uRTCTime.uwHour;
    uwMinute    = uRTCTime.uwMinute;
    uwSecond    = uRTCTime.uwSecond;

    uwDayInWeek = uRTCTime.uwDayInWeek;
    ubAmOrPm = uRTCTime.ubAmOrPm;
    b_12FormatEn = uRTCTime.b_12FormatEn;

    if (uwYear < RTC_DEFAULT_YEAR)
    {
        AHC_RestoreDefaultTime(&uwYear, &uwMonth, &uwDay, &uwDayInWeek, &uwHour, &uwMinute, &uwSecond, &ubAmOrPm, &b_12FormatEn);
    }

    Datetime[0] = uwYear;
    Datetime[1] = uwMonth;
    Datetime[2] = uwDay;
    Datetime[3] = uwHour;
    Datetime[4] = uwMinute;
    Datetime[5] = uwSecond;

    initDatetime = AHC_FALSE;
    return AHC_TRUE;
}

#if (MENU_GENERAL_BEEP_EN)
AHC_BOOL MenuItemBeep(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiBeep = pItem->iItemId - ITEMID_BEEP-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
AHC_BOOL MenuItemLCDBrightness(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiLCDBrightness = pItem->iItemId - ITEMID_LCD_BRIGHTNESS-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
AHC_BOOL MenuItemAutoPowerOff(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiAutoPowerOff = pItem->iItemId - ITEMID_AUTO_POWER_OFF-1;
    AutoPowerOffCounterReset();
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
AHC_BOOL MenuItemClockSettings(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
AHC_BOOL MenuItemDateTimeFormat(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiDateTimeFormat = pItem->iItemId - ITEMID_DATETIME_FORMAT-1;
    MenuItemDateTimeFormatToAhcTimeStampSetting();

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
AHC_BOOL MenuItemDateLogoStamp(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiDateLogoStamp = pItem->iItemId - ITEMID_DATE_LOGO_STAMP-1;
    MenuItemDateTimeFormatToAhcTimeStampSetting();

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
AHC_BOOL MenuItemGPSStamp(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiGPSStamp = pItem->iItemId - ITEMID_GPS_STAMP-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
AHC_BOOL MenuItemSpeedStamp(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSpeedStamp = pItem->iItemId - ITEMID_SPEED_STAMP-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_LANGUAGE_EN)
AHC_BOOL MenuItemLanguage(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiLanguage = pItem->iItemId - ITEMID_LANGUAGE-1;
    ShowOSD_SetLanguage(0xff /* for dummy */);
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_TV_SYSTEM_EN)
AHC_BOOL MenuItemTVSystem(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiTVSystem = pItem->iItemId - ITEMID_TV_SYSTEM-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_HDMI_OUTPUT_EN)
AHC_BOOL MenuItemHDMIOutput(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    switch (pItem->iItemId)
    {
    #if (MENU_GENERAL_HDMI_OUTPUT_1080P_EN)
    case ITEMID_HDMI_OUTPUT_1080P:
        MenuSettingConfig()->uiHDMIOutput = HDMI_OUTPUT_1080P;
        printc("HDMI is 1080P@30\r\n");
        break;
    #endif
    #if (MENU_GENERAL_HDMI_OUTPUT_1080I_EN)
    case ITEMID_HDMI_OUTPUT_1080I:
        MenuSettingConfig()->uiHDMIOutput = HDMI_OUTPUT_1080I;
        printc("HDMI is 1080I@60\r\n");
        break;
    #endif
    #if (MENU_GENERAL_HDMI_OUTPUT_720P_EN)
    case ITEMID_HDMI_OUTPUT_720P:
        MenuSettingConfig()->uiHDMIOutput = HDMI_OUTPUT_720P;
        printc("HDMI is 720P@30\r\n");
        break;
    #endif
    #if (MENU_GENERAL_HDMI_OUTPUT_480P_EN)
    case ITEMID_HDMI_OUTPUT_480P:
        MenuSettingConfig()->uiHDMIOutput = HDMI_OUTPUT_480P;
        printc("HDMI is 480P@30\r\n");
        break;
    #endif
    default:
        MenuSettingConfig()->uiHDMIOutput = HDMI_OUTPUT_1080I;
        printc("default HDMI is 1080I@60\r\n");
        break;
    }

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
AHC_BOOL MenuItemResetSetup(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiResetSetting = pItem->iItemId - ITEMID_RESET_SETUP -1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
AHC_BOOL MenuItemFwVersion(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)
AHC_BOOL MenuItemLdwsCalibration(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
AHC_BOOL MenuItemUserLdwsCalibration(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_GPSINFO_EN)
AHC_BOOL MenuItemGPSInfo(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (VIRTUAL_KEY_BOARD)
AHC_BOOL MenuItemKeyboard(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_FLICKER_EN)
AHC_BOOL MenuItemFlickerHz(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiFlickerHz = pItem->iItemId - ITEMID_FLICKER -1;
    Menu_SetFlickerHz(MenuSettingConfig()->uiFlickerHz);
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
AHC_BOOL MenuItemUSBSelect(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiUSBFunction = pItem->iItemId - ITEMID_USB_FUNCTION -1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_LCD_ROTATE_EN)
AHC_BOOL MenuItemLCDRotate(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT8   BackUpSetting = MenuSettingConfig()->uiLCDRotate;

    MenuSettingConfig()->uiLCDRotate = pItem->iItemId - ITEMID_LCD_ROTATE-1;
    Menu_SetLCDDirectionEx(MenuSettingConfig()->uiLCDRotate, BackUpSetting);

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
AHC_BOOL MenuItemLCDPowerSave(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiLCDPowerSave = pItem->iItemId - ITEMID_LCD_POWER_SAVE-1;
    LCDPowerSaveCounterReset();
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_FLASH_LED_EN)
AHC_BOOL MenuItemLEDFlash(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiLEDFlash = pItem->iItemId - ITEMID_LED_FLASH-1;

#if (LED_FLASH_CTRL==LED_BY_MENU                || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_LINK   || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_NOT_LINK)

    AHC_SetMenuFlashLEDStatus(MenuSettingConfig()->uiLEDFlash);
    Menu_SetFlashLEDMode(MenuSettingConfig()->uiLEDFlash);

#elif (LED_FLASH_CTRL==LED_BY_KEY_WITH_MENU_CONFIRMED)

    if(MenuSettingConfig()->uiLEDFlash==LED_FALSH_OFF)
    {
        MenuSettingConfig()->uiFlashMode = FLASH_OFF;
        FlashLED_Timer_Stop();
        LedCtrl_FlashLed(AHC_FALSE);
    }
    else if (MenuSettingConfig()->uiLEDFlash==LED_FALSH_ON)
    {
        MenuSettingConfig()->uiFlashMode = FLASH_ON;
        FlashLED_Timer_Stop();
        LedCtrl_FlashLed(AHC_TRUE);
    }
#endif

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_GSENSOR_EN)
AHC_BOOL MenuItemGsensorSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiGsensorSensitivity = pItem->iItemId - ITEMID_GSENSOR_SENSITIVITY-1;
    AHC_Gsensor_UI_SetIntThreshold();
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
AHC_BOOL MenuItemGsensorPowerOnSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    Setpf_GSNR_THR(pItem->iItemId - ITEMID_GSENSOR_POWERON_SENSITIVITY - 1);
    //Menu_SetGsensorPowerOnSensitivity(pItem->iItemId - ITEMID_GSENSOR_POWERON_SENSITIVITY - 1);
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_MOTION_DTC_EN)
AHC_BOOL MenuItemMotionDtcSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMotionDtcSensitivity = pItem->iItemId - ITEMID_MOTION_DETECT-1;
    Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
    #if defined(CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY) && (MOTION_DETECTION_EN) && (VMD_ACTION != VMD_ACTION_NONE)
    if(MenuSettingConfig()->uiMotionDtcSensitivity != MOTION_DTC_SENSITIVITY_OFF)
        uiSetParkingModeEnable(AHC_TRUE);
    else
        uiSetParkingModeEnable(AHC_FALSE);
    #endif
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
AHC_BOOL MenuItemTimeZone(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if (GPS_CONNECT_ENABLE)
    const signed char* pTimeZoneTable = GetTimeZoneTable();
    signed char CurTimeZone = *(pTimeZoneTable+(pItem->iItemId - ITEMID_TIME_ZONE - 1));
    ST_GPS_INFO *pInfo = (ST_GPS_INFO *) GPS_Information();
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEATIME *pGMTtime = (NMEATIME *)GPS_GetGMTBackupTime();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARTIME *pGMTtime = (GPSRADARTIME *)GPSRadar_GetGMTBackupTime();
    #endif

    MenuSettingConfig()->uiTimeZone = pItem->iItemId - ITEMID_TIME_ZONE-1;

    if (GPSCtrl_GPS_IsValidValue()) {
        GPSCtrl_AttributeAddressForAviChuck()->byGMTOffset = CurTimeZone;
        GPSCtrl_GMT2LocalTime(pGMTtime, &(pInfo->sUTC),CurTimeZone);
        GPSCtrl_LinkGPSTime2RTC(&(pInfo->sUTC));
    }
#endif
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_BOOT_UP_MODE_EN)
AHC_BOOL MenuItemBootUpMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiBootUpMode = pItem->iItemId - ITEMID_BOOTUP_MODE-1;
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_NIGHT_MODE_EN)
AHC_BOOL MenuItemNightModeSelect(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    //Restore other setting
    Menu_SetEV(0, MenuSettingConfig()->uiEV);
    Menu_SetISO(0, MenuSettingConfig()->uiISO);
    Menu_SetAWB(0, MenuSettingConfig()->uiWB);
    Menu_SetColor(0, MenuSettingConfig()->uiColor);
    Menu_SetEffect(0, MenuSettingConfig()->uiEffect);
	if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
		Menu_SetEV(1, MenuSettingConfig()->uiEV);
    	Menu_SetISO(1, MenuSettingConfig()->uiISO);
    	Menu_SetAWB(1, MenuSettingConfig()->uiWB);
        Menu_SetColor(1, MenuSettingConfig()->uiColor);
        Menu_SetEffect(1, MenuSettingConfig()->uiEffect);
	}
    
    MenuSettingConfig()->uiScene = pItem->iItemId - ITEMID_SCENE -1;
    Menu_SetSceneMode(MenuSettingConfig()->uiScene);

    return AHC_TRUE;
}
#endif

#if(MENU_GENERAL_WIFI_EN)
AHC_BOOL MenuItemWiFiMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    Setpf_WiFi(pItem->iItemId - ITEMID_WIFI_MODE - 1);
    //Menu_SetWiFiMode(pItem->iItemId - ITEMID_WIFI_MODE - 1);
    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN || MENU_GENERAL_PQ_BRIGHTNESS_EN || MENU_GENERAL_PQ_SATURATION_EN)
AHC_BOOL MenuItemPQAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT8   ubPQCurValue = 50, ubPQMinValue = 0, ubPQMaxValue = 0, ubPQStep = 0;

    switch(pItem->iItemId)
    {
        case ITMEID_PQ_CONTRAST_DEC:
        case ITMEID_PQ_CONTRAST_INC:
            ubPQCurValue = Getpf_PQContrast();
            ubPQMinValue = PQCONTRAST_MIN;
            ubPQMaxValue = PQCONTRAST_MAX;
            ubPQStep = PQCONTRAST_STEP;
            break;
        case ITEMID_PQ_BRIGHTNESS_DEC:
        case ITEMID_PQ_BRIGHTNESS_INC:
            ubPQCurValue = Getpf_PQBrightness();
            ubPQMinValue = PQBRIGHTNESS_MIN;
            ubPQMaxValue = PQBRIGHTNESS_MAX;
            ubPQStep = PQBRIGHTNESS_STEP;
            break;
        case ITEMID_PQ_SATURATION_DEC:
        case ITEMID_PQ_SATURATION_INC:
            ubPQCurValue = Getpf_PQSaturation();
            ubPQMinValue = PQSATURATION_MIN;
            ubPQMaxValue = PQSATURATION_MAX;
            ubPQStep = PQSATURATION_STEP;
            break;
    }

    switch(pItem->iItemId)
    {
        case ITMEID_PQ_CONTRAST_DEC:
        case ITEMID_PQ_BRIGHTNESS_DEC:
        case ITEMID_PQ_SATURATION_DEC:
            if(ubPQCurValue <= ubPQStep)
                ubPQCurValue = ubPQMinValue;
            else
                ubPQCurValue = ((ubPQCurValue+1-ubPQStep)/10)*10;
            break;
        case ITMEID_PQ_CONTRAST_INC:
        case ITEMID_PQ_BRIGHTNESS_INC:
        case ITEMID_PQ_SATURATION_INC:
            ubPQCurValue += ubPQStep;
            if (ubPQCurValue >= ubPQMaxValue)
                ubPQCurValue = ubPQMaxValue;
            break;
    }

    switch(pItem->iItemId)
    {
        case ITMEID_PQ_CONTRAST_DEC:
        case ITMEID_PQ_CONTRAST_INC:
            Setpf_PQContrast(ubPQCurValue);
            AHC_Display_AdjustContrast( ubPQCurValue);
            break;
        case ITEMID_PQ_BRIGHTNESS_DEC:
        case ITEMID_PQ_BRIGHTNESS_INC:
            Setpf_PQBrightness(ubPQCurValue);
            AHC_Display_AdjustBrightness( ubPQCurValue);
            break;
        case ITEMID_PQ_SATURATION_DEC:
        case ITEMID_PQ_SATURATION_INC:
            Setpf_PQSaturation(ubPQCurValue);
            AHC_Display_AdjustSaturation( ubPQCurValue);
            break;
    }

    return AHC_TRUE;
}
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
AHC_BOOL MenuItemPQColorTemp(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    u16  u16TabIdx=0;

    Setpf_PQColorTemp(pItem->iItemId - ITEMID_PQ_COLORTEMP - 1);

    u16TabIdx = Getpf_PQColorTemp();

    AHC_Display_AdjustColorTemp(u16TabIdx);

    return AHC_TRUE;
}
#endif

UINT32 MenuGetDefault_GeneralSetting(PSMENUSTRUCT pMenu)
{
    UINT32       DefaultValue;

    switch( pMenu->iMenuId )
    {
#if (MENU_GENERAL_BEEP_EN)
        case MENUID_SUB_MENU_BEEP:
            DefaultValue = MenuSettingConfig()->uiBeep;
            break;
#endif
#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
        case MENUID_SUB_MENU_LCD_BRIGHTNESS:
            DefaultValue = MenuSettingConfig()->uiLCDBrightness;
            break;
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
        case MENUID_SUB_MENU_AUTO_POWER_OFF:
            DefaultValue = MenuSettingConfig()->uiAutoPowerOff;
            break;
#endif
#if (MENU_GENERAL_DATE_FORMAT_EN)
        case MENUID_SUB_MENU_DATETIME_FORMAT:
            DefaultValue = MenuSettingConfig()->uiDateTimeFormat;
            break;
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
        case MENUID_SUB_MENU_DATELOGO_STAMP:
            DefaultValue = MenuSettingConfig()->uiDateLogoStamp;
            break;
#endif
#if (MENU_GENERAL_GPS_STAMP_EN)
        case MENUID_SUB_MENU_GPS_STAMP:
            DefaultValue = MenuSettingConfig()->uiGPSStamp;
            break;
#endif
#if (MENU_GENERAL_SPEED_STAMP_EN)
        case MENUID_SUB_MENU_SPEED_STAMP:
            DefaultValue = MenuSettingConfig()->uiSpeedStamp;
            break;
#endif
#if (MENU_GENERAL_LANGUAGE_EN)
        case MENUID_MAIN_LANGUAGE_SET:
        case MENUID_SUB_MENU_LANGUAGE:
            DefaultValue = MenuSettingConfig()->uiLanguage;
            break;
#endif
#if (MENU_GENERAL_TV_SYSTEM_EN)
        case MENUID_SUB_MENU_TV_SYSTEM:
            DefaultValue = MenuSettingConfig()->uiTVSystem;
            break;
#endif
#if (MENU_GENERAL_HDMI_OUTPUT_EN)
        case MENUID_SUB_MENU_HDMI_OUTPUT:
            switch (MenuSettingConfig()->uiHDMIOutput)
            {
            #if (MENU_GENERAL_HDMI_OUTPUT_1080P_EN)
            case HDMI_OUTPUT_1080P:
                DefaultValue = ITEMID_HDMI_OUTPUT_1080P - ITEMID_HDMI_OUTPUT - 1;
                break;
            #endif
            #if (MENU_GENERAL_HDMI_OUTPUT_1080I_EN)
            case HDMI_OUTPUT_1080I:
                DefaultValue = ITEMID_HDMI_OUTPUT_1080I - ITEMID_HDMI_OUTPUT - 1;
                break;
            #endif
            #if (MENU_GENERAL_HDMI_OUTPUT_720P_EN)
            case HDMI_OUTPUT_720P:
                DefaultValue = ITEMID_HDMI_OUTPUT_720P - ITEMID_HDMI_OUTPUT - 1;
                break;
            #endif
            #if (MENU_GENERAL_HDMI_OUTPUT_480P_EN)
            case HDMI_OUTPUT_480P:
                DefaultValue = ITEMID_HDMI_OUTPUT_480P - ITEMID_HDMI_OUTPUT - 1;
                break;
            #endif
            default:
                DefaultValue = 0;
                break;
            }
            break;
#endif
#if (MENU_GENERAL_FLICKER_EN)
        case MENUID_SUB_MENU_FLICKER_FREQUENCY:
            DefaultValue = MenuSettingConfig()->uiFlickerHz;
            break;
#endif
#if (MENU_GENERAL_USB_FUNCTION_EN)
        case MENUID_SUB_MENU_USB_FUNCTION:
            DefaultValue = MenuSettingConfig()->uiUSBFunction;
            break;
#endif
#if (MENU_GENERAL_LCD_ROTATE_EN)
        case MENUID_SUB_MENU_LCD_ROTATE:
            DefaultValue = MenuSettingConfig()->uiLCDRotate;
            break;
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
        case MENUID_SUB_MENU_LCD_POWER_SAVE:
            DefaultValue = MenuSettingConfig()->uiLCDPowerSave;
            break;
#endif
#if (MENU_GENERAL_FLASH_LED_EN)
        case MENUID_SUB_MENU_LED_FLASH:
            DefaultValue = MenuSettingConfig()->uiLEDFlash;
            break;
#endif
#if (MENU_GENERAL_GSENSOR_EN)
        case MENUID_SUB_MENU_GSENSOR_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiGsensorSensitivity;
            break;
#endif
#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
        case MENUID_SUB_MENU_GSENSOR_POWERON_SENSITIVITY:
            DefaultValue = Getpf_GSNR_THR();
            break;
#endif
#if (MENU_GENERAL_MOTION_DTC_EN)
        case MENUID_SUB_MENU_MOTION_DTC_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiMotionDtcSensitivity;
            break;
#endif
#if (MENU_GENERAL_TIME_ZONE_EN)
         case MENUID_SUB_MENU_TIME_ZONE:
            DefaultValue = MenuSettingConfig()->uiTimeZone;
            break;
#endif
#if (MENU_GENERAL_BOOT_UP_MODE_EN)
        case MENUID_SUB_MENU_BOOT_UP_MODE:
            DefaultValue = MenuSettingConfig()->uiBootUpMode;
            break;
#endif
#if (MENU_GENERAL_NIGHT_MODE_EN)
        case MENUID_SUB_MENU_NIGHT_MODE:
            DefaultValue = (MenuSettingConfig()->uiScene == SCENE_TWILIGHT)?(1):(0);
            break;
#endif
#if (MENU_GENERAL_WIFI_EN)
        case MENUID_SUB_MENU_WIFI_MODE:
            DefaultValue = Getpf_WiFi();
            break;
#endif
#if (MENU_GENERAL_PQ_CONTRAST_EN)
        case MENUID_SUB_MENU_PQ_CONTRAST:
            DefaultValue = (UINT32)Getpf_PQContrast();
        break;
#endif
#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
        case MENUID_SUB_MENU_PQ_BRIGHTNESS:
            DefaultValue = (UINT32)Getpf_PQBrightness();
        break;
#endif
#if (MENU_GENERAL_PQ_SATURATION_EN)
        case MENUID_SUB_MENU_PQ_SATURATION:
            DefaultValue = (UINT32)Getpf_PQSaturation();
        break;
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
        case MENUID_SUB_MENU_PQ_COLORTEMP:
            DefaultValue = Getpf_PQColorTemp();;
        break;
#endif
    }

    return DefaultValue;
}

#if (MENU_GENERAL_CLOCK_SETTING_EN)

UINT32 SubMenuEventHandler_ClockSetting(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;
#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    if(initDatetime == AHC_TRUE)
        MenuInitDateTime();

    switch(ulEvent)
    {
    case MENU_EXIT:
        return MENU_ERR_EXIT;
    break;

    case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;
        pMenu->bSetOne  = 0;

        if( pMenu->pfMenuGetDefaultVal )
        {
            pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
        }
        else
        {
            pMenu->iSelected = 0 ;
        }
        pMenu->iCurrentPos = pMenu->iSelected;

        #if (SUPPORT_TOUCH_PANEL)
        KeyParser_TouchItemRegister(&MenuClockSetting_TouchButton[0], ITEMNUM(MenuClockSetting_TouchButton));
        #endif

        MenuDrawSubPage_ClockSetting( pMenu );
        break;

    #ifdef CFG_SUB_MENU_REVERSE_V_KEYS //may be defined in config_xxx.h
    case MENU_DOWN:
    #else
    case MENU_UP:
    #endif
        MenuDrawChangeSubItem_ClockSettingUD(pMenu, 1);
    break;

    #ifdef CFG_SUB_MENU_REVERSE_V_KEYS //may be defined in config_xxx.h
    case MENU_UP:
    #else
    case MENU_DOWN:
    #endif
        MenuDrawChangeSubItem_ClockSettingUD(pMenu, -1);
    break;

    #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_RIGHT         :
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );
        MenuDrawChangeSubItem_ClockSetting( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;
    #else
    case MENU_LEFT          :
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );
        MenuDrawChangeSubItem_ClockSetting( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_RIGHT         :
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );
        MenuDrawChangeSubItem_ClockSetting( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;
    #endif

    case MENU_OK            :
    case MENU_SET_ONE       :

        pMenu->bSetOne   = 1;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        if( pMenu->pItemsList[iPrevPos]->uiStringId == IDS_DS_OK &&
            pMenu->pItemsList[pMenu->iCurrentPos]->uiStringId == IDS_DS_OK )

        {
            PSMENUSTRUCT    pParentMenu;

            // OK -> Exit menu
            pParentMenu        = pMenu->pParentMenu;
            pMenu->pParentMenu = NULL;
            initDatetime       = AHC_TRUE;

            //Validate Clock Setting
            //if(AHC_Validate_ClockSetting(Datetime, CHECK_ALL, AHC_TRUE)!=CHECK_PASS)
            //{
                //AHC_WMSG_Draw(AHC_TRUE, WMSG_INVALID_OPERATION, 3);
            //}

            //Set time to RTC
            AHC_SetParam(PARAM_ID_USE_RTC,AHC_TRUE);

            AHC_SetClock(GetSubItemClockSetting_DateTime(0),  GetSubItemClockSetting_DateTime(1),  GetSubItemClockSetting_DateTime(2), 0,
                         GetSubItemClockSetting_DateTime(3),  GetSubItemClockSetting_DateTime(4),  GetSubItemClockSetting_DateTime(5), 0, 0);

            #if (GPS_CONNECT_ENABLE)
            GPSCtrl_EnableTimeSync(MMP_TRUE);
            #endif

            if( pParentMenu == NULL )
            {
                return MENU_ERR_EXIT;
            }

            SetCurrentMenu(pParentMenu);
            pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
            MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_MAIN, MMP_TRUE, 0);
        }
        else
        {
            MenuDrawChangeSubItem_ClockSetting( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
        }
    break;

    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;
        pMenu->bSetOne     = 0;
        initDatetime       = AHC_TRUE;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
        MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_MAIN, MMP_TRUE, 0);
    }
    break;

#if 0
    case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
    break;
#endif

    default:
    break;
    }

    return MENU_ERR_OK;
}
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
UINT32 SubMenuEventHandler_ResetSetup(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;
#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
    case MENU_EXIT:
        return MENU_ERR_EXIT;
    break;

    case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;
        pMenu->bSetOne  = 0;

        if( pMenu->pfMenuGetDefaultVal )
        {
            pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
        }
        else
        {
            pMenu->iSelected = 0 ;
        }
        pMenu->iCurrentPos = pMenu->iSelected;


        #if (SUPPORT_TOUCH_PANEL)
        KeyParser_TouchItemRegister(&MenuConfirm_TouchButton[0], ITEMNUM(MenuConfirm_TouchButton));
        #endif

        MenuDrawSubPage_ConfirmPage( pMenu );
    break;

    #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_UP:
    #else
    case MENU_LEFT:
    #endif
        #ifdef SLIDE_MENU
        if(IsSlidingMenu())
            break;
        #endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_DOWN:
    #else
    case MENU_RIGHT:
    #endif
        #ifdef SLIDE_MENU
        if(IsSlidingMenu())
            break;
        #endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :

        if(ulEvent==MENU_SET_ONE)
        {
            pMenu->iCurrentPos = ulParam;
            pMenu->iSelected   = ulParam;
            pMenu->bSetOne   = 1;
            pMenu->uiStatus |= MENU_STATUS_PRESSED;
            pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
        }
        else
        {
            pMenu->bSetOne   = 1;
            pMenu->iSelected = pMenu->iCurrentPos;
            pMenu->uiStatus |= MENU_STATUS_PRESSED;
        }

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {

            PSMENUSTRUCT pParentMenu;

            pParentMenu        = pMenu->pParentMenu;
            pMenu->pParentMenu = NULL;

            if( pParentMenu == NULL )
            {
                return MENU_ERR_EXIT;
            }

            if(MenuSettingConfig()->uiResetSetting == 0)  //Only change settings while press OK.
            {
                RestoreFromDefaultSetting();
                Menu_RenewMenuSetting(AHC_TRUE);
            }

            SetCurrentMenu(pParentMenu);
            pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );


            return MENU_ERR_OK;
        }
    break;

    case MENU_MENU          :
    {

        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        if(MenuSettingConfig()->uiResetSetting == 0 && pMenu->bSetOne==1)  //Only change settings while press OK.
        {
            RestoreFromDefaultSetting();
            Menu_RenewMenuSetting(AHC_TRUE);
        }

        pMenu->bSetOne     = 0;

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );

    }
    break;

#if (SUPPORT_TOUCH_PANEL)
    case MENU_TOUCH         :
       {
            UINT32  TouchEvent;
            UINT32  uiNextEvent = MENU_NONE;

            TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

            switch( TouchEvent )
            {
                case MENU_RETURN_PRESS :
                    uiNextEvent = MENU_MENU;
                break;
                case MENU_YES_PRESS :
                    ulParam = 0;
                    uiNextEvent = MENU_SET_ONE;
                break;
                case MENU_NO_PRESS :
                    ulParam = 1;
                    uiNextEvent = MENU_SET_ONE;
                break;
                default:
                    uiNextEvent = MENU_NONE;
                break;
            }

            return SubMenuEventHandler_ResetSetup(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
        }
    break;
#endif

#if 0
    case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
    break;
#endif

    default:
    break;
    }

    return MENU_ERR_OK;
}
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
UINT32 SubMenuEventHandler_FwVersionInfo(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
#if(SUPPORT_TOUCH_PANEL)
    POINT  TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
    case MENU_EXIT:
        return MENU_ERR_EXIT;
    break;

    case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;

        if( pMenu->pfMenuGetDefaultVal )
        {
            pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
        }
        else
        {
            pMenu->iSelected = 0 ;
        }

        pMenu->iCurrentPos = pMenu->iSelected;

        #if (SUPPORT_TOUCH_PANEL)
        KeyParser_TouchItemRegister(&MenuInfo_TouchButton[0], ITEMNUM(MenuInfo_TouchButton));
        #endif

        MenuDrawSubPage_FwVersionInfo( pMenu );
    break;

    case MENU_OK            :
    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
    }
    break;

#if (SUPPORT_TOUCH_PANEL)
    case MENU_TOUCH         :
    {
        UINT32  TouchEvent;
        UINT32  uiNextEvent = MENU_NONE;

        TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

        switch( TouchEvent )
        {
            case MENU_RETURN_PRESS :
                uiNextEvent = MENU_MENU;
            break;
            default:
                uiNextEvent = MENU_NONE;
            break;
        }
        return SubMenuEventHandler_FwVersionInfo(pMenu, uiNextEvent, ulParam);
    }
    break;
#endif

#if 0
    case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
    break;
#endif

    default:
    break;
    }

    return MENU_ERR_OK;
}
#endif

#if (MENU_GENERAL_GPSINFO_EN)
UINT32 SubMenuEventHandler_GPSInfoChart(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
#if(SUPPORT_TOUCH_PANEL)
    POINT  TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
    case MENU_EXIT:
        return MENU_ERR_EXIT;
    break;

    case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;

        if( pMenu->pfMenuGetDefaultVal )
        {
            pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
        }
        else
        {
            pMenu->iSelected = 0 ;
        }

        pMenu->iCurrentPos = pMenu->iSelected;

        #if (SUPPORT_TOUCH_PANEL)
        KeyParser_TouchItemRegister(&MenuInfo_TouchButton[0], ITEMNUM(MenuInfo_TouchButton));
        #endif

        MenuDrawSubPage_GPSInfo( pMenu );
    break;

    case MENU_OK            :
    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
    }
    break;

    case MENU_UPDATE_MESSAGE:
        MenuDrawSubPage_GPSInfo( pMenu );
        break;

#if (SUPPORT_TOUCH_PANEL)
    case MENU_TOUCH         :
    {
        UINT32  TouchEvent;
        UINT32  uiNextEvent = MENU_NONE;

        TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

        switch( TouchEvent )
        {
            case MENU_RETURN_PRESS :
                uiNextEvent = MENU_MENU;
            break;
            default:
                uiNextEvent = MENU_NONE;
            break;
        }
        return SubMenuEventHandler_GPSInfoChart(pMenu, uiNextEvent, ulParam);
    }
    break;
#endif

#if 0
    case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
    break;
#endif

    default:
    break;
    }

    return MENU_ERR_OK;
}
#endif

#if (VIRTUAL_KEY_BOARD)
void OSD_ShowStringPool_Keyboard(UINT16 uwDisplayID, PSKEY psKey, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign)
{
    GUI_RECT guiRect;
    INT8 chTempString[8];

    AHC_OSDSetColor(uwDisplayID, uiBkColor);

    if( uiBkColor != OSD_COLOR_TRANSPARENT)
        AHC_OSDDrawFillRoundedRect( uwDisplayID,
                                    StrRECT.uiLeft,
                                    StrRECT.uiTop,
                                    StrRECT.uiLeft+StrRECT.uiWidth,
                                    StrRECT.uiTop+StrRECT.uiHeight,
                                    RECT_ROUND_RADIUS);

    AHC_OSDSetColor(uwDisplayID, uiForeColor);
    AHC_OSDSetBkColor(uwDisplayID, uiBkColor);

    guiRect.x0 = StrRECT.uiLeft;
    guiRect.y0 = StrRECT.uiTop;
    guiRect.x1 = StrRECT.uiLeft+StrRECT.uiWidth;
    guiRect.y1 = StrRECT.uiTop+StrRECT.uiHeight;
    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    memset(chTempString, 0, 8);
    switch(psKey->uiASCIICode){
    case KEYBOARD_KEY_CTR:
        strcpy(chTempString, "CTR");
        break;
    case KEYBOARD_KEY_DEL:
        memcpy(chTempString, "DEL", 3);
        break;
    case KEYBOARD_KEY_CHG:
        memcpy(chTempString, "CHG", 3);
        break;
    case KEYBOARD_KEY_ENT:
        memcpy(chTempString, "ENTER", 5);
        break;
    case ' ':
        memcpy(chTempString, "SPACE", 5);
        break;
    default:
        chTempString[0] = psKey->uiASCIICode;
        break;
    }
    AHC_OSDDrawTextInRect(uwDisplayID, (UINT8*)&chTempString, &guiRect, wTextAlign);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);
}
void DrawSubItem_Keyboard(  UINT16 uwDisplayID,
                            PSKEY psKey,
                            const GUI_BITMAP* IconID,
                            GUI_COLOR colorFont,
                            GUI_BITMAP barID,
                            GUI_COLOR ColorBack,
                            GUI_COLOR colorSelect )
{
    RECT tmpRECT;

    if( colorSelect != 0 )
    {
        AHC_OSDSetColor(uwDisplayID, colorSelect);
        AHC_OSDDrawFillRoundedRect( uwDisplayID,
                                    psKey->rcUIRegion.uiLeft,
                                    psKey->rcUIRegion.uiTop,
                                    psKey->rcUIRegion.uiLeft + psKey->rcUIRegion.uiWidth,
                                    psKey->rcUIRegion.uiTop + psKey->rcUIRegion.uiHeight, RECT_ROUND_RADIUS );
    }

    tmpRECT.uiLeft   = psKey->rcUIRegion.uiLeft + 2;
    tmpRECT.uiTop    = psKey->rcUIRegion.uiTop + 4;
    tmpRECT.uiWidth  = psKey->rcUIRegion.uiWidth - 5;
    tmpRECT.uiHeight = psKey->rcUIRegion.uiHeight - 3;

    OSD_ShowStringPool_Keyboard(uwDisplayID, psKey, tmpRECT, colorFont, ColorBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

void MenuDrawBlinkSubItem_Keyboard(PSMENUSTRUCT pMenu,  PSKEY psKey, PSKEY psPrevKey )
{
    UINT8     bID0 = 0;
    UINT8     bID1 = 0;

    OSDDraw_EnterMenuDrawing( &bID0, &bID1 );

    {

    GUI_RECT pRect = {10, 20, 310, 50};

    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRoundedRect( bID0,
                                10,
                                20,
                                310,
                                50, RECT_ROUND_RADIUS );

    AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_WHITE);

    AHC_OSDDrawTextInRect(bID0, (UINT8*)KEYBOARD_GetWord(), &pRect, GUI_TA_HCENTER|GUI_TA_VCENTER);

    }

    if( pMenu->uiStatus == ( MENU_STATUS_PRESSED  | MENU_STATUS_ITEM_TOUCHED ))
    {
        DrawSubItem_Keyboard( bID0, psKey, NULL,  OSD_COLOR_BLACK, bmIcon_SubMenuBar_Yellow, OSD_COLOR_TRANSPARENT, OSD_COLOR_YELLOW );
    }
    else
    {
        DrawSubItem_Keyboard( bID0, psKey, NULL,  OSD_COLOR_BLACK, bmIcon_SubMenuBar_Yellow, OSD_COLOR_TRANSPARENT, OSD_COLOR_WHITE );
    }

    OSDDraw_ExitMenuDrawing( &bID0, &bID1 );

}

void MenuDrawSubPage_Keyboard(PSMENUSTRUCT pMenu, PSKEY psKey)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    PSKEY  psTempKey;

    psTempKey = psKey;

    OSDDraw_EnterMenuDrawing( &bID0, &bID1 );
    OSDDraw_ClearOvlDrawBuffer(bID0);

    {
        UINT16 uiWidth;
        UINT16 uiHeight;
        UINT16 uiColorFormat;
        UINT32 ulBufferAddr;

        AHC_OSDGetBufferAttr(bID0, &uiWidth, &uiHeight, &uiColorFormat, &ulBufferAddr);
        AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
        AHC_OSDDrawFillRect( bID0, 0, 0  , uiWidth, uiHeight  );
    }

    {
        GUI_RECT pRect = {10, 20, 310, 50};

        AHC_OSDSetColor(bID0,OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(bID0, OSD_COLOR_WHITE);
        AHC_OSDDrawFillRoundedRect( bID0,10,20,310,50, RECT_ROUND_RADIUS );

        AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
        AHC_OSDSetBkColor(bID0, OSD_COLOR_WHITE);

        AHC_OSDDrawTextInRect(bID0, (UINT8*)KEYBOARD_GetWord(), &pRect, GUI_TA_HCENTER|GUI_TA_VCENTER);
    }

    while(psTempKey!= NULL)
    {
        GUI_COLOR colorBackground = OSD_COLOR_TRANSPARENT;
        GUI_COLOR colorSelected   = OSD_COLOR_WHITE;

        GUI_BITMAP barID = bmIcon_SubMenuBar_White;

#if VIRTUAL_KEY_BOARD_BY_KEY
        if(psTempKey == (PSKEY)(KEYBOARD_GetKeyHead() + pMenu->iCurrentPos))
        {
            DrawSubItem_Keyboard( bID0, psTempKey, NULL,  OSD_COLOR_BLACK, barID, colorBackground, OSD_COLOR_YELLOW);
        }
        else
#endif
        {
            DrawSubItem_Keyboard( bID0, psTempKey, NULL,  OSD_COLOR_BLACK, barID, colorBackground, colorSelected );
        }
        psTempKey = psTempKey->psNextKey;
    }

    OSDDraw_ExitMenuDrawing( &bID0, &bID1 );
}

UINT32  SubMenuEventHandler_Keyboard(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam )
{
#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;
#endif

//    UINT32    CurMode;
    int     iPrevPos;

#ifdef SLIDE_STRING
    StopSlideString();
#endif

#if(SUPPORT_TOUCH_PANEL)
    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE  == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY =  (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
        case MENU_UP:
        case MENU_DOWN:
        case MENU_LEFT:
        case MENU_RIGHT:
        case MENU_CIRCLE        :
        case MENU_SET_ONE:
        case MENU_MENU:
        case MENU_OK:
            AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
        break;

        case MENU_SDMMC_IN:
        case MENU_SDMMC_OUT:
            MenuDraw_SD_Status();
        break;

   }

    switch(ulEvent)
    {
        case MENU_INIT          :

            KEYBOARD_INIT();

            pMenu->uiStatus = MENU_STATUS_NONE;

            if( pMenu->pfMenuGetDefaultVal )
            {
                pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
            }
            else
            {
                pMenu->iSelected = 0 ;
            }
            pMenu->iCurrentPos = pMenu->iSelected;

            MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
            break;

        case MENU_UP            :
            #if VIRTUAL_KEY_BOARD_BY_KEY
                pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, KEYBOARD_GetKeyMount()-1, -1, AHC_TRUE );
                MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
            #endif
            break;

        case MENU_DOWN          :
            #if VIRTUAL_KEY_BOARD_BY_KEY
                pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, KEYBOARD_GetKeyMount()-1, 1, AHC_TRUE );
                MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
            #endif
            break;

        case MENU_LEFT          :

            break;

        case MENU_RIGHT         :

            break;

#if (MENU_DIR_KEY_NUM == 1)
        case MENU_CIRCLE        :
            break;
#endif
#if 0
        case MENU_POWER_OFF     :
            AHC_PowerOff_NormalPath();
            break;
#endif
        case MENU_TOUCH_MOVE    :
            break;

        case MENU_TOUCH         :
           {
                UINT32  uiNextEvent = MENU_NONE;
                PSKEY psKey = (PSKEY)KEYBOARD_GetKeyHead();

                if(KEYBOARD_CheckTouchButton(&psKey, &TouchPoint) == AHC_TRUE)
                {
                    ulParam = (UINT32)psKey;
                    uiNextEvent = MENU_SET_ONE;
                }
                else
                {
                    uiNextEvent = MENU_NONE;
                }

                return SubMenuEventHandler_Keyboard(pMenu, uiNextEvent, ulParam);

            }
            break;

        case MENU_TOUCH_RELEASE:
            if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
            {
                iPrevPos = pMenu->iSelected;
                pMenu->uiStatus = 0;//pMenu->uiStatus  & ~MENU_STATUS_ITEM_TOUCHED;
                //MenuDrawBlinkSubItem_Keyboard( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
            }
            break;

        case MENU_OK            :
        #if VIRTUAL_KEY_BOARD_BY_KEY
        {
            UINT32 uiEvent;
            PSKEY psKey = (PSKEY)KEYBOARD_GetKeyHead();

            psKey = psKey +  pMenu->iCurrentPos;

            ulParam = (UINT32)psKey;
            uiEvent = KEYBOARD_EventHandler((PSKEY)ulParam);
            switch(uiEvent)
            {
                case KEYBOARD_EVENT_ENTER:
                {
                    PSMENUSTRUCT pParentMenu;

                    pParentMenu        = pMenu->pParentMenu;
                    pMenu->pParentMenu = NULL;

                    if( pParentMenu == NULL )
                    {
                        return MENU_ERR_EXIT;
                    }
                #if VIRTUAL_KEY_BOARD_FOR_CAR_ID
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_GENERAL)&&(pMenu->iMenuId == MENUID_SUB_MENU_DRIVER_ID_SETTINGS))
                    {
                        KEYBOARD_CarNo();
                    }
                #endif
                #if VIRTUAL_KEY_BOARD_FOR_WIFI
#if MENU_WIFI_AP_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_AP_SSID))
                    {
                        KEYBOARD_WifiAPSSID();
                    }
                #endif
#if MENU_WIFI_AP_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_AP_PSWD))
                    {
                        KEYBOARD_WifiAPPSWD();
                    }
#endif
#if MENU_WIFI_STATION2_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION2_SSID))
                    {
                        KEYBOARD_WifiSTA2SSID();
                    }
#endif
#if MENU_WIFI_STATION2_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION2_PSWD))
                    {
                        KEYBOARD_WifiSTA2PSWD();
                    }
#endif
#if MENU_WIFI_STATION3_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION3_SSID))
                    {
                        KEYBOARD_WifiSTA3SSID();
                    }
#endif
#if MENU_WIFI_STATION3_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION3_PSWD))
                    {
                        KEYBOARD_WifiSTA3PSWD();
                    }
#endif
#if MENU_WIFI_STATION4_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION4_SSID))
                    {
                        KEYBOARD_WifiSTA4SSID();
                    }
#endif
#if MENU_WIFI_STATION4_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION4_PSWD))
                    {
                        KEYBOARD_WifiSTA4PSWD();
                    }
#endif
#if MENU_WIFI_STATION5_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION5_SSID))
                    {
                        KEYBOARD_WifiSTA5SSID();
                    }
#endif
#if MENU_WIFI_STATION5_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION5_PSWD))
                    {
                        KEYBOARD_WifiSTA5PSWD();
                    }
#endif
#if MENU_WIFI_STATION6_SSID_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION6_SSID))
                    {
                        KEYBOARD_WifiSTA6SSID();
                    }
#endif
#if MENU_WIFI_STATION6_PSWD_EN
                    if((pParentMenu->iMenuId == MENUID_MAIN_MENU_WIFI)&&(pMenu->iMenuId == MENUID_SUB_MENU_WIFI_STATION6_PSWD))
                    {
                        KEYBOARD_WifiSTA6PSWD();
                    }
#endif
                #endif
                    SetCurrentMenu(pParentMenu);
                    pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );

                }
                break;

                case KEYBOARD_EVENT_CHG:
                case KEYBOARD_EVENT_CTR:
                default:
                    MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
                    break;
            }
        }
        #endif
            break;

        case MENU_MENU          :
            {
                PSMENUSTRUCT pParentMenu;

                pParentMenu        = pMenu->pParentMenu;
                pMenu->pParentMenu = NULL;

                if( pParentMenu == NULL )
                {
                    return MENU_ERR_EXIT;
                }

                SetCurrentMenu(pParentMenu);
                pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );

            }
            break;
        case MENU_MENU_RELEASE  :
            break;

        case MENU_SET_ONE       :
            {
                //UINT32 uiPrevSelected = pMenu->iSelected;
                UINT32 uiEvent;
                iPrevPos      = pMenu->iCurrentPos;

                pMenu->iCurrentPos = ulParam;///< the position of button.
                pMenu->iSelected   = ulParam;
                pMenu->bSetOne   = 1;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
                pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;

                //MenuDrawBlinkSubItem_Keyboard( pMenu, ulParam, uiPrevSelected );

                uiEvent = KEYBOARD_EventHandler((PSKEY)ulParam);
                switch(uiEvent)
                {
                    case KEYBOARD_EVENT_CHG:
                        MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
                        break;

                    case KEYBOARD_EVENT_CTR:
                        MenuDrawSubPage_Keyboard( pMenu , KEYBOARD_GetKeyHead());
                        break;

                    case KEYBOARD_EVENT_ENTER:
                    {
                        PSMENUSTRUCT pParentMenu;

                        pParentMenu        = pMenu->pParentMenu;
                        pMenu->pParentMenu = NULL;

                        if( pParentMenu == NULL )
                        {
                            return MENU_ERR_EXIT;
                        }

                        SetCurrentMenu(pParentMenu);
                        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );

                    }
                    break;

                    default:
                    break;
                }

            }

        default:
            break;
    }

    return MENU_ERR_OK;
}
#endif

#if (MENU_GENERAL_GSENSOR_EN)

int RemoveMenu_GsensorSensitivity(void)
{
    return RemoveMenuItem(&sMainMenuGeneral, &sItemGsensorSensitivity);
}
#endif

void MenuItemDateTimeFormatToAhcTimeStampSetting(void)
{
    UINT32 m_TimeStampConfig;

    AHC_Capture_GetConfig(ACC_DATE_STAMP, &m_TimeStampConfig);

    // Clean then Set
    m_TimeStampConfig &= ~(AHC_ACC_TIMESTAMP_ENABLE_MASK |
                           AHC_ACC_TIMESTAMP_DATE_MASK   |
                           AHC_ACC_TIMESTAMP_FORMAT_MASK);

    switch(MenuSettingConfig()->uiDateTimeFormat)
    {
    case DATETIME_SETUP_NONE:
        m_TimeStampConfig = (AHC_ACC_TIMESTAMP_DISABLE | AHC_ACC_TIMESTAMP_DATE_ONLY | AHC_ACC_TIMESTAMP_BOTTOM_RIGHT | AHC_ACC_TIMESTAMP_FORMAT_1);
    break;
    case DATETIME_SETUP_YMD:
        m_TimeStampConfig = (AHC_ACC_TIMESTAMP_ENABLE | AHC_ACC_TIMESTAMP_DATE_AND_TIME | AHC_ACC_TIMESTAMP_BOTTOM_RIGHT | AHC_ACC_TIMESTAMP_FORMAT_2);
    break;
    case DATETIME_SETUP_MDY:
        m_TimeStampConfig = (AHC_ACC_TIMESTAMP_ENABLE | AHC_ACC_TIMESTAMP_DATE_AND_TIME | AHC_ACC_TIMESTAMP_BOTTOM_RIGHT | AHC_ACC_TIMESTAMP_FORMAT_4);
    break;
    case DATETIME_SETUP_DMY:
        m_TimeStampConfig = (AHC_ACC_TIMESTAMP_ENABLE | AHC_ACC_TIMESTAMP_DATE_AND_TIME | AHC_ACC_TIMESTAMP_BOTTOM_RIGHT | AHC_ACC_TIMESTAMP_FORMAT_3);
    break;
    default:
        m_TimeStampConfig = (AHC_ACC_TIMESTAMP_DISABLE | AHC_ACC_TIMESTAMP_DATE_ONLY | AHC_ACC_TIMESTAMP_BOTTOM_RIGHT | AHC_ACC_TIMESTAMP_FORMAT_1);
    break;
    }

    m_TimeStampConfig &= ~(AHC_ACC_TIMESTAMP_LOGOEX_MASK |
                           AHC_ACC_TIMESTAMP_DATEEX_MASK);
    switch (MenuSettingConfig()->uiDateLogoStamp)
    {
    #if MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN
    case DATELOGO_STAMP:
        m_TimeStampConfig |= (AHC_ACC_TIMESTAMP_LOGOEX | AHC_ACC_TIMESTAMP_DATEEX);
        break;
    #endif
    #if MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN
    case DATE_STAMP:
        m_TimeStampConfig |= (AHC_ACC_TIMESTAMP_DATEEX);
        break;
    #endif
    #if MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN
    case LOGO_STAMP:
        m_TimeStampConfig |= (AHC_ACC_TIMESTAMP_LOGOEX);
        break;
    #endif
    #if MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN
    case OFF_STAMP:
    #endif
    default:
        m_TimeStampConfig &= ~AHC_ACC_TIMESTAMP_ENABLE_MASK;
        break;
    }

    AHC_Capture_SetConfig(ACC_DATE_STAMP, m_TimeStampConfig);
}

#if (MENU_GENERAL_PQ_CONTRAST_EN || MENU_GENERAL_PQ_BRIGHTNESS_EN || MENU_GENERAL_PQ_SATURATION_EN)
UINT32 SubMenuEventHandler_PQAdjust(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;
#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
    case MENU_EXIT:
        return MENU_ERR_EXIT;
    break;

    case MENU_INIT          :
        printc("%s - MENU_INIT\r\n", __func__);

        pMenu->uiStatus = MENU_STATUS_NONE;
        pMenu->bSetOne  = 0;

        #if (SUPPORT_TOUCH_PANEL)
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_PQAdjust( pMenu );
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_DOWN          :
#else
    case MENU_LEFT:
#endif  // DIR_KEY_TYPE
        #ifdef SLIDE_MENU
        if(IsSlidingMenu())
            break;
        #endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );
        MenuItemPQAdjust(pMenu->pItemsList[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_PQAdjust(pMenu);
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_UP            :
#else
    case MENU_RIGHT         :
#endif  // DIR_KEY_TYPE
        #ifdef SLIDE_MENU
        if(IsSlidingMenu())
            break;
        #endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );
        MenuItemPQAdjust(pMenu->pItemsList[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_PQAdjust(pMenu);
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        printc("%s - MENU_OK\r\n", __func__);

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

        iPrevPos         = pMenu->iCurrentPos;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if(ulEvent==MENU_SET_ONE)
        {
            pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
        }

        //if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {

            PSMENUSTRUCT pParentMenu;

            pParentMenu        = pMenu->pParentMenu;
            pMenu->pParentMenu = NULL;

            if( pParentMenu == NULL )
            {
                return MENU_ERR_EXIT;
            }
            SetCurrentMenu(pParentMenu);
            pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);

            return MENU_ERR_OK;
        }
    }
    break;

    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;
        pMenu->bSetOne     = 0;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);

    }
    break;

#if (SUPPORT_TOUCH_PANEL)
    case MENU_TOUCH         :
       {
            UINT32  TouchEvent;
            UINT32  uiNextEvent = MENU_NONE;

            TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

            switch( TouchEvent )
            {
                case MENU_EXIT_PRESS :
                    uiNextEvent = MENU_MENU;
                break;
                case MENU_INCREASE_PRESS:
                    #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
                    uiNextEvent = MENU_UP;
                    #else
                    uiNextEvent = MENU_RIGHT;
                    #endif
                break;
                case MENU_DECREASE_PRESS:
                    #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
                    uiNextEvent = MENU_DOWN;
                    #else
                    uiNextEvent = MENU_LEFT;
                    #endif
                break;
                case MENU_OK_PRESS :
                    uiNextEvent = MENU_SET_ONE;
                break;
                default:
                    uiNextEvent = MENU_NONE;
                break;
            }

            return SubMenuEventHandler_Contrast(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_Contrast();
        }
    break;
#endif

#if 0
    case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
    break;
#endif

    default:
    break;
    }

    return MENU_ERR_OK;
}
#endif




