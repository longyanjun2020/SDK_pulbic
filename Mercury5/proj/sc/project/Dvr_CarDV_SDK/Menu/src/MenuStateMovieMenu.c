/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_display.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_common.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_video.h"
#include "ahc_warningmsg.h"
#include "ahc_parameter.h"
#include "ahc_general_cardv.h"
#include "ahc_general.h"
#include "MenuCommon.h"
#include "MenuStateMovieMenu.h"
#include "MenuStateModeSelectMenu.h"
#include "MenuSetting.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "ahc_usb.h"
#include "ahc_fs.h"
#if WIFI_PORT
#include "netapp.h"
#endif
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "ledcontrol.h"
#if (SD_UPDATE_FW_EN)
#include "SD_Updater.h"
#endif
#include "snr_cfg.h"
#include "ait_utility.h"

/*===========================================================================
 * External function
 *===========================================================================*/
AHC_BOOL IsAdapter_Connect(void);
AHC_BOOL VideoFunc_GetRecordStatus(void);
AHC_BOOL SwitchUIDrawSetVideoRecordMode(void);
AHC_BOOL StateVideoRecModeInitHDMI(void* pData);
UINT32 KeyParser_ClockSettingEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
void InitOSD(void);

/*===========================================================================
 * Local function
 *===========================================================================*/

AHC_BOOL MenuItemMovieMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieQuality(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieStable(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemAutoSlowShutter(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMICSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMoviePreRecord(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieClipTime(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieNightMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMoviePowerOffTime(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieSoundRecord(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieVMDRecTime(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieAutoRec(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieTimelapse(PSMENUITEM pItem, AHC_BOOL bIsHover);   // VIDEO_REC_TIMELAPSE_EN
AHC_BOOL MenuItemMovieParkingMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieLDWSMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieFCWSMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieSAGMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieHDRMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieSlowMotionMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemMovieWNRMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemRearCamType(PSMENUITEM pItem,AHC_BOOL bIsHover);

UINT32   MenuGetDefault_Movie(PSMENUSTRUCT pMenu);

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern SMENUITEM    sItemScence;
extern SMENUITEM    sItemEV;
extern SMENUITEM    sItemWB;
extern SMENUITEM    sItemISO;
extern SMENUITEM    sItemColor;
extern SMENUITEM    sItemEffect;
#if defined (CFG_LIST_STILL_IMAGE_SIZE) /*may be defined in config_xxx.h*/ && (MENU_STILL_SIZE_EN)
extern SMENUITEM    sItemStillImageSize;
#endif
extern SMENUSTRUCT  sSubClockSettings;

extern AHC_BOOL     Deleting_InBrowser;
extern AHC_BOOL     Protecting_InBrowser;
//extern AHC_BOOL   bForceSwitchBrowser;
#ifdef CFG_MENU_MOVIE_EXIT_TO_PREV
extern AHC_BOOL     bForceSwitchCameraMode;
#endif
extern AHC_BOOL     m_ubAtMenuTab;
extern SMENUITEM    sItemContrast;
extern SMENUITEM    sItemSaturation;
extern SMENUITEM    sItemSharpness;
extern SMENUITEM    sItemGamma;

extern MMP_UBYTE    gubWpFileNum;
extern AHC_BOOL     gbAhcDbgBrk;
#if (HDMI_ENABLE)
//extern AHC_BOOL       bHaveInitOsdHdmi;
#endif
#define IDS_DS_PARKING_MODE IDS_DS_POWERON_GSENSOR_SENSITIVETY

/*===========================================================================
 * Global varible : Menu
 *===========================================================================*/

SMENUSTRUCT sMainMenuVideo;

SMENUSTRUCT sSubMovieMode;
SMENUSTRUCT sSubMovieQuality;
SMENUSTRUCT sSubMovieStable;
SMENUSTRUCT sSubAutoSlowShutter;
SMENUSTRUCT sSubMICSensitivity;
SMENUSTRUCT sSubMoviePreRecord;
SMENUSTRUCT sSubMovieClipTime;
SMENUSTRUCT sSubMovieNightMode;
SMENUSTRUCT sSubMoviePowerOffTime;
SMENUSTRUCT sSubMovieSoundRecord;
SMENUSTRUCT sSubMovieVMDRecTime;
SMENUSTRUCT sSubMovieAutoRec;
SMENUSTRUCT sSubMovieTimelapse;     // VIDEO_REC_TIMELAPSE_EN
SMENUSTRUCT sSubMovieParkingMode;
SMENUSTRUCT sSubMovieLDWSMode;
SMENUSTRUCT sSubMovieFCWSMode;
SMENUSTRUCT sSubMovieSAGMode;
SMENUSTRUCT sSubMovieHDRMode;
SMENUSTRUCT sSubMovieSlowMotionMode;
SMENUSTRUCT sSubMovieWNRMode;
SMENUSTRUCT sSubRearCamType;


/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/

// Movie Mode
#if (MENU_MOVIE_SIZE_EN)
SMENUITEM sItemMovieMode                = { ITEMID_MOVIE_MODE,          &BMICON_MENU_REC_MODE,      IDS_DS_MOVIE_MODE,          &sSubMovieMode, 0,       0, AHC_TRUE, NULL };
#if (MENU_MOVIE_SIZE_4K_24P_EN)
SMENUITEM sItemMovieMode_4K_24P         = { ITEMID_MOVIE_MODE_4K_24P,   &BMICON_MOVIE_RES_SHD30P,   IDS_DS_MOVIE_MODE_SHD,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_1440_30P_EN)
SMENUITEM sItemMovieMode_1440_30P       = { ITEMID_MOVIE_MODE_1440_30P, &BMICON_MOVIE_RES_SHD30P,   IDS_DS_MOVIE_MODE_SHD,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_SHD_30P_EN)
SMENUITEM sItemMovieMode_SHD            = { ITEMID_MOVIE_MODE_SHD,      &BMICON_MOVIE_RES_SHD30P,   IDS_DS_MOVIE_MODE_SHD,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_SHD_25P_EN)
SMENUITEM sItemMovieMode_SHD_25P        = { ITEMID_MOVIE_MODE_SHD_25P,  &BMICON_MOVIE_RES_SHD25P,   IDS_DS_MOVIE_MODE_SHD_25P,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_SHD_24P_EN)
SMENUITEM sItemMovieMode_SHD_24P        = { ITEMID_MOVIE_MODE_SHD_24P,  &BMICON_MOVIE_RES_SHD24P,   IDS_DS_MOVIE_MODE_SHD_24P,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_1080_60P_EN)
SMENUITEM sItemMovieMode_FHD_60P        = { ITEMID_MOVIE_MODE_FHD_60P,  &BMICON_MOVIE_RES_FHD60P,   IDS_DS_MOVIE_MODE_FHD_60P,  NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_1080P_EN)
SMENUITEM sItemMovieMode_FHD            = { ITEMID_MOVIE_MODE_FHD,      &BMICON_MOVIE_RES_FHD30P,   IDS_DS_MOVIE_MODE_FHD,      NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif

#if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) || (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
SMENUITEM sItemMovieMode_FHD_HDR        = { ITEMID_MOVIE_MODE_FHD_HDR,  &BMICON_MOVIE_RES_FHD30PHDR, IDS_DS_MOVIE_MODE_FHD_HDR,     NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif

#if (MENU_MOVIE_SIZE_1080_24P_EN)
SMENUITEM sItemMovieMode_FHD_24P        = { ITEMID_MOVIE_MODE_FHD_24P,  &BMICON_MOVIE_RES_FHD24P,   IDS_DS_MOVIE_MODE_FHD_24P,  NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_720P_EN)
SMENUITEM sItemMovieMode_HD             = { ITEMID_MOVIE_MODE_HD,       &BMICON_MOVIE_RES_HD30P,    IDS_DS_MOVIE_MODE_HD,       NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_720_60P_EN)
SMENUITEM sItemMovieMode_HD_60P         = { ITEMID_MOVIE_MODE_HD_60P,   &BMICON_MOVIE_RES_HD60P,    IDS_DS_MOVIE_MODE_HD_60P,   NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_720_24P_EN)
SMENUITEM sItemMovieMode_HD_24P         = { ITEMID_MOVIE_MODE_HD_24P,   &BMICON_MOVIE_RES_HD24P,    IDS_DS_MOVIE_MODE_HD_24P,   NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_VGA30P_EN)
SMENUITEM sItemMovieMode_VGA_30P        = { ITEMID_MOVIE_MODE_VGA_30P,  &BMICON_MOVIE_RES_VGA30P,   IDS_DS_MOVIE_MODE_VGA_30P,  NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SIZE_VGA120P_EN)
SMENUITEM sItemMovieMode_VGA_120P       = { ITEMID_MOVIE_MODE_VGA_120P, &BMICON_MOVIE_RES_VGA30P,   IDS_DS_MOVIE_MODE_VGA_30P,  NULL, MenuItemMovieMode, 0, AHC_TRUE, NULL };
#endif

#endif

// Movie Quality
#if (MENU_MOVIE_QUALITY_EN)
SMENUITEM sItemMovieQuality             = { ITEMID_MOVIE_QUALITY,       &BMICON_MENU_REC_QUALITY, IDS_DS_MOVIE_QUALITY, &sSubMovieQuality, 0,       0, AHC_TRUE, NULL };
#if (MENU_MOVIE_QUALITY_SUPER_FINE_EN)
SMENUITEM sItemMovieQuality_Super_Fine  = { ITEMID_MQUALITY_SUPERFINE,  &BMICON_QUALITY_SHQ, IDS_DS_QUALITY_SUPERFINE,  NULL, MenuItemMovieQuality, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_QUALITY_FINE_EN)
SMENUITEM sItemMovieQuality_Fine        = { ITEMID_MQUALITY_FINE,       &BMICON_QUALITY_HQ,  IDS_DS_QUALITY_FINE,       NULL, MenuItemMovieQuality, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie Stabilization
#if (MENU_MOVIE_STABILIZE_EN)
SMENUITEM sItemMovieStabilization       = { ITEMID_MOVIE_STABLEILIZATION, NULL, IDS_DS_MOVIE_STABLEILIZATION,   &sSubMovieStable, 0, 0, AHC_TRUE, NULL };
#if (MENU_MOVIE_STABILIZE_ON_EN)
SMENUITEM sItemMovieStabilization_On    = { ITEMID_MOVIE_STABLE_ON,  &bmIcon_ImageStable_ON,  IDS_DS_ON,    NULL, MenuItemMovieStable, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_STABILIZE_OFF_EN)
SMENUITEM sItemMovieStabilization_Off   = { ITEMID_MOVIE_STABLE_OFF, &bmIcon_ImageStable_OFF, IDS_DS_OFF,   NULL, MenuItemMovieStable, 0, AHC_TRUE, NULL };
#endif
#endif

// Auto Slow Shutter
#if (MENU_MOVIE_SLOW_SHUTTER_EN)
SMENUITEM sItemAutoSlowShutter          = { ITEMID_AUTO_SLOW_SHUTTER,  NULL, IDS_DS_AUTO_SLOW_SHUTTER,  &sSubAutoSlowShutter, 0, 0, AHC_TRUE, NULL };
#if (MENU_MOVIE_SLOW_SHUTTER_ON_EN)
SMENUITEM sItemAutoSlowShutter_On       = { ITEMID_AUTO_SLOW_SHUT_ON,  NULL, IDS_DS_ON, NULL, MenuItemAutoSlowShutter, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SLOW_SHUTTER_OFF_EN)
SMENUITEM sItemAutoSlowShutter_Off      = { ITEMID_AUTO_SLOW_SHUT_OFF, NULL, IDS_DS_OFF,NULL, MenuItemAutoSlowShutter, 0, AHC_TRUE, NULL };
#endif
#endif

// MIC Sensitivity
#if (MENU_MOVIE_MIC_SEN_EN)
SMENUITEM sItemMICSensitivity           = { ITEMID_MIC_SENSITIVITY,      &BMICON_MENU_MIC,   IDS_DS_MIC_SENSITIVITY, &sSubMICSensitivity, 0,  0, AHC_TRUE, NULL };
#if (MENU_MOVIE_MIC_SEN_STANDARD_EN)
SMENUITEM sItemMICSensitivity_Standard  = { ITEMID_MIC_SENSITI_STANDARD, &BMICON_MIC_SENS_H, IDS_DS_STANDARD,   NULL, MenuItemMICSensitivity, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_MIC_SEN_LOW_EN)
SMENUITEM sItemMICSensitivity_Low       = { ITEMID_MIC_SENSITI_LOW,      &BMICON_MIC_SENS_L, IDS_DS_LOW,        NULL, MenuItemMICSensitivity, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie PreRecord
#if (MENU_MOVIE_PRE_RECORD_EN)
SMENUITEM sItemMoviePreRecord          = { ITEMID_MOVIE_PRE_RECORD, NULL, IDS_DS_MOVIE_PRE_RECORD,  &sSubMoviePreRecord, 0, 0, AHC_TRUE, NULL };
#if (MENU_MOVIE_PRE_RECORD_ON_EN)
SMENUITEM sItemMoviePreRecord_On       = { ITEMID_MOVIE_PRE_RECORD_ON,  NULL, IDS_DS_ON, NULL, MenuItemMoviePreRecord, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_PRE_RECORD_OFF_EN)
SMENUITEM sItemMoviePreRecord_Off      = { ITEMID_MOVIE_PRE_RECORD_OFF, NULL, IDS_DS_OFF,NULL, MenuItemMoviePreRecord, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie Clip Time
#if (MENU_MOVIE_CLIP_TIME_EN)
SMENUITEM sItemMovieClipTime            = { ITEMID_MOVIE_CLIPTIME,          &BMICON_MENU_CLIPTIME,  IDS_MOVIE_CLIPTIME,     &sSubMovieClipTime,     0,   0, AHC_TRUE, NULL };
#if (MENU_MOVIE_CLIP_TIME_OFF_EN)
SMENUITEM sItemMovieClipTime_off        = { ITEMID_MOVIE_CLIPTIME_OFF,      &BMICON_OPTION_CLOSE,   IDS_DS_OFF,             NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_6SEC_EN)
SMENUITEM sItemMovieClipTime_6sec       = { ITEMID_MOVIE_CLIPTIME_6SEC,     &BMICON_CLIPTIME_1MIN,  IDS_TIME_1MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_1MIN_EN)
SMENUITEM sItemMovieClipTime_1min       = { ITEMID_MOVIE_CLIPTIME_1MIN,     &BMICON_CLIPTIME_1MIN,  IDS_TIME_1MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_2MIN_EN)
SMENUITEM sItemMovieClipTime_2min       = { ITEMID_MOVIE_CLIPTIME_2MIN,     &BMICON_CLIPTIME_1MIN,  IDS_TIME_2MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_3MIN_EN)
SMENUITEM sItemMovieClipTime_3min       = { ITEMID_MOVIE_CLIPTIME_3MIN,     &BMICON_CLIPTIME_3MIN,  IDS_TIME_3MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_5MIN_EN)
SMENUITEM sItemMovieClipTime_5min       = { ITEMID_MOVIE_CLIPTIME_5MIN,     &BMICON_CLIPTIME_5MIN,  IDS_TIME_5MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_10MIN_EN)
SMENUITEM sItemMovieClipTime_10min      = { ITEMID_MOVIE_CLIPTIME_10MIN,    &BMICON_CLIPTIME_10MIN, IDS_TIME_10MIN,         NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_25MIN_EN)
SMENUITEM sItemMovieClipTime_25min      = { ITEMID_MOVIE_CLIPTIME_25MIN,    NULL,                   IDS_TIME_25MIN,         NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_CLIP_TIME_30MIN_EN)
SMENUITEM sItemMovieClipTime_30min      = { ITEMID_MOVIE_CLIPTIME_30MIN,    &BMICON_CLIPTIME_1MIN,  IDS_TIME_1MIN,          NULL, MenuItemMovieClipTime, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie Night mode
#if (MENU_MOVIE_NIGHT_MODE_EN)
SMENUITEM sItemMovieNightMode          = { ITEMID_MOVIE_NIGHT_MODE, NULL, IDS_DS_NIGHT_MODE,    &sSubMovieNightMode, 0, 0, AHC_TRUE, NULL };
#if (MENU_MOVIE_NIGHT_MODE_ON_EN)
SMENUITEM sItemMovieNightMode_On       = { ITEMID_MOVIE_NIGHT_MODE_ON,  NULL, IDS_DS_ON, NULL, MenuItemMovieNightMode, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_NIGHT_MODE_OFF_EN)
SMENUITEM sItemMovieNightMode_Off      = { ITEMID_MOVIE_NIGHT_MODE_OFF, NULL, IDS_DS_OFF,NULL, MenuItemMovieNightMode, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie PowerOff Time
#ifndef CFG_POWER_OFF_STR_ID //may be defined in config_xxx.h
    #define CFG_POWER_OFF_STR_ID IDS_MOVIE_POWEROFF_TIME
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
SMENUITEM sItemMoviePowerOffTime        = { ITEMID_MOVIE_POWEROFF_TIME,       &BMICON_MENU_OFFTIME,     CFG_POWER_OFF_STR_ID,   &sSubMoviePowerOffTime, 0,  0, AHC_TRUE, NULL };
#if (MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN)
SMENUITEM sItemMoviePowerOffTime_0min   = { ITEMID_MOVIE_POWEROFF_TIME_0MIN,  &BMICON_OFFTIME_0MIN,     IDS_TIME_0MIN,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN)
SMENUITEM sItemMoviePowerOffTime_5sec   = { ITEMID_MOVIE_POWEROFF_TIME_5SEC,  &BMICON_OFFTIME_5SEC,     IDS_TIME_5SEC,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN)
SMENUITEM sItemMoviePowerOffTime_10sec  = { ITEMID_MOVIE_POWEROFF_TIME_10SEC, &BMICON_OFFTIME_10SEC,    IDS_TIME_10SEC, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN)
SMENUITEM sItemMoviePowerOffTime_15sec  = { ITEMID_MOVIE_POWEROFF_TIME_15SEC, NULL,                     IDS_TIME_15SEC, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN)
SMENUITEM sItemMoviePowerOffTime_30sec  = { ITEMID_MOVIE_POWEROFF_TIME_30SEC, &BMICON_OFFTIME_30SEC,    IDS_TIME_30SEC, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN)
SMENUITEM sItemMoviePowerOffTime_1min   = { ITEMID_MOVIE_POWEROFF_TIME_1MIN,  &BMICON_OFFTIME_1MIN,     IDS_TIME_1MIN,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_2MIN_EN)
SMENUITEM sItemMoviePowerOffTime_2min   = { ITEMID_MOVIE_POWEROFF_TIME_2MIN,  &BMICON_OFFTIME_2MIN,     IDS_TIME_2MIN,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_3MIN_EN)
SMENUITEM sItemMoviePowerOffTime_3min   = { ITEMID_MOVIE_POWEROFF_TIME_3MIN,  &BMICON_OFFTIME_3MIN,     IDS_TIME_3MIN,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_5MIN_EN)
SMENUITEM sItemMoviePowerOffTime_5min   = { ITEMID_MOVIE_POWEROFF_TIME_5MIN,  NULL,                     IDS_TIME_5MIN,  NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_10MIN_EN)
SMENUITEM sItemMoviePowerOffTime_10min  = { ITEMID_MOVIE_POWEROFF_TIME_10MIN, NULL,                     IDS_TIME_10MIN, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_15MIN_EN)
SMENUITEM sItemMoviePowerOffTime_15min  = { ITEMID_MOVIE_POWEROFF_TIME_15MIN, NULL,                     IDS_TIME_15MIN, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_30MIN_EN)
SMENUITEM sItemMoviePowerOffTime_30min  = { ITEMID_MOVIE_POWEROFF_TIME_30MIN, NULL,                     IDS_TIME_30MIN, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_60MIN_EN)
SMENUITEM sItemMoviePowerOffTime_60min  = { ITEMID_MOVIE_POWEROFF_TIME_60MIN, NULL,                     IDS_TIME_60MIN, NULL, MenuItemMoviePowerOffTime, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie Sound Record
#if (MENU_MOVIE_SOUND_RECORD_EN)
SMENUITEM sItemMovieSoundRecord         = { ITEMID_MOVIE_SOUND_RECORD,      &BMICON_MENU_RECORD_SOUND,  IDS_MOVIE_SOUND_RECORD, &sSubMovieSoundRecord,  0,  0, AHC_TRUE, NULL };
#if (MENU_MOVIE_SOUND_RECORD_ON_EN)
SMENUITEM sItemMovieSoundRecord_On      = { ITEMID_MOVIE_SOUND_RECORD_ON,   &BMICON_OPTION_OPEN,        IDS_DS_ON,      NULL, MenuItemMovieSoundRecord, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_SOUND_RECORD_OFF_EN)
SMENUITEM sItemMovieSoundRecord_Off     = { ITEMID_MOVIE_SOUND_RECORD_OFF,  &BMICON_OPTION_CLOSE,       IDS_DS_OFF,     NULL, MenuItemMovieSoundRecord, 0, AHC_TRUE, NULL };
#endif
#endif

// Motion Record Time
#if (MENU_MOVIE_VMD_REC_TIME_EN)
SMENUITEM sItemMovieVMDRecTime          = { ITEMID_MOVIE_VMD_REC_TIME,       &BMICON_MENU_MTD,  IDS_VMD_REC_TIME,   &sSubMovieVMDRecTime,           0,         0, AHC_TRUE, NULL };
#if (MENU_MOVIE_VMD_REC_TIME_5SEC_EN)
SMENUITEM sItemMovieVMDRecTime_5sec     = { ITEMID_MOVIE_VMD_REC_TIME_5SEC,  &BMICON_OFFTIME_5SEC,  IDS_TIME_5SEC,  NULL, MenuItemMovieVMDRecTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_VMD_REC_TIME_10SEC_EN)
SMENUITEM sItemMovieVMDRecTime_10sec    = { ITEMID_MOVIE_VMD_REC_TIME_10SEC, &BMICON_OFFTIME_10SEC, IDS_TIME_10SEC, NULL, MenuItemMovieVMDRecTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_VMD_REC_TIME_30SEC_EN)
SMENUITEM sItemMovieVMDRecTime_30sec    = { ITEMID_MOVIE_VMD_REC_TIME_30SEC, &BMICON_OFFTIME_30SEC, IDS_TIME_30SEC, NULL, MenuItemMovieVMDRecTime, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MOVIE_VMD_REC_TIME_1MIN_EN)
SMENUITEM sItemMovieVMDRecTime_1min     = { ITEMID_MOVIE_VMD_REC_TIME_1MIN,  &BMICON_OFFTIME_60SEC, IDS_TIME_1MIN,  NULL, MenuItemMovieVMDRecTime, 0, AHC_TRUE, NULL };
#endif
#endif

// Movie Auto Rec
#if (MENU_MOVIE_AUTO_REC_EN)
SMENUITEM sItemMovieAutoRec             = { ITEMID_MOVIE_AUTO_REC,          NULL, IDS_AUTO_REC,     &sSubMovieAutoRec, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieAutoRec_On          = { ITEMID_MOVIE_AUTO_REC_ON,       NULL, IDS_DS_ON,        NULL,    MenuItemMovieAutoRec, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieAutoRec_Off         = { ITEMID_MOVIE_AUTO_REC_OFF,      NULL, IDS_DS_OFF,       NULL,    MenuItemMovieAutoRec, 0,AHC_TRUE, NULL };
#endif

#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
SMENUITEM sItemMovieTimelapse           = { ITEMID_MOVIE_TIMELAPSE,     NULL, IDS_DS_VIDEO_TIMELAPSE,       &sSubMovieTimelapse, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_Off       = { ITEMID_MOVIE_TIMELAPSE_OFF, NULL, IDS_DS_OFF,           NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_1Sec      = { ITEMID_MOVIE_TIMELAPSE_1SEC,    NULL, IDS_TIME_1SEC,        NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_5Sec      = { ITEMID_MOVIE_TIMELAPSE_5SEC,    NULL, IDS_TIME_5SEC,        NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_10Sec     = { ITEMID_MOVIE_TIMELAPSE_10SEC,   NULL, IDS_TIME_10SEC,           NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_30Sec     = { ITEMID_MOVIE_TIMELAPSE_30SEC,   NULL, IDS_TIME_30SEC,           NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieTimelapse_60Sec     = { ITEMID_MOVIE_TIMELAPSE_60SEC,   NULL, IDS_TIME_60SEC,           NULL,       MenuItemMovieTimelapse, 0,AHC_TRUE, NULL };
#endif

#if (MENU_MOVIE_PARKING_MODE_EN)
SMENUITEM sItemMovieParkingMode         = { ITEMID_MOVIE_PARKING_MODE,      NULL, IDS_DS_PARKING_MODE,  &sSubMovieParkingMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieParkingMode_On      = { ITEMID_MOVIE_PARKING_MODE_ON,   NULL, IDS_DS_ON,            NULL,       MenuItemMovieParkingMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieParkingMode_Off     = { ITEMID_MOVIE_PARKING_MODE_OFF,  NULL, IDS_DS_OFF,           NULL,       MenuItemMovieParkingMode, 0,AHC_TRUE, NULL };
#endif

// LDWS On/Off
#if (MENU_MOVIE_LDWS_MODE_EN)
SMENUITEM sItemMovieLDWSMode            = { ITEMID_MOVIE_LDWS_MODE,         NULL, IDS_DS_LDWS,          &sSubMovieLDWSMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieLDWSMode_On         = { ITEMID_MOVIE_LDWS_MODE_ON,      NULL, IDS_DS_ON,            NULL,       MenuItemMovieLDWSMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieLDWSMode_Off        = { ITEMID_MOVIE_LDWS_MODE_OFF,     NULL, IDS_DS_OFF,           NULL,       MenuItemMovieLDWSMode, 0,AHC_TRUE, NULL };
#endif

// FCWS On/Off
#if (MENU_MOVIE_FCWS_MODE_EN)
SMENUITEM sItemMovieFCWSMode            = { ITEMID_MOVIE_FCWS_MODE,         NULL, IDS_DS_FCWS,          &sSubMovieFCWSMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieFCWSMode_On         = { ITEMID_MOVIE_FCWS_MODE_ON,      NULL, IDS_DS_ON,            NULL,       MenuItemMovieFCWSMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieFCWSMode_Off        = { ITEMID_MOVIE_FCWS_MODE_OFF,     NULL, IDS_DS_OFF,           NULL,       MenuItemMovieFCWSMode, 0,AHC_TRUE, NULL };
#endif

// SAG On/Off
#if (MENU_MOVIE_SAG_MODE_EN)
SMENUITEM sItemMovieSAGMode            = { ITEMID_MOVIE_SAG_MODE,         NULL, IDS_DS_SAG,             &sSubMovieSAGMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieSAGMode_On         = { ITEMID_MOVIE_SAG_MODE_ON,      NULL, IDS_DS_ON,              NULL,       MenuItemMovieSAGMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieSAGMode_Off        = { ITEMID_MOVIE_SAG_MODE_OFF,     NULL, IDS_DS_OFF,             NULL,       MenuItemMovieSAGMode, 0,AHC_TRUE, NULL };
#endif

// HDR On/Off
#if (MENU_MOVIE_HDR_MODE_EN)
SMENUITEM sItemMovieHDRMode            = { ITEMID_MOVIE_HDR_MODE,           NULL, IDS_DS_HDR,           &sSubMovieHDRMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieHDRMode_On         = { ITEMID_MOVIE_HDR_MODE_ON,        NULL, IDS_DS_ON,            NULL,       MenuItemMovieHDRMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieHDRMode_Off        = { ITEMID_MOVIE_HDR_MODE_OFF,       NULL, IDS_DS_OFF,           NULL,       MenuItemMovieHDRMode, 0,AHC_TRUE, NULL };
#endif

// SLOWMOTION
#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
SMENUITEM sItemMovieSlowMotionMode           = { ITEMID_MOVIE_SLOWMOTION_MODE,           NULL, IDS_DS_SLOWMOTION,           &sSubMovieSlowMotionMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieSlowMotionMode_X1        = { ITEMID_MOVIE_SLOWMOTION_MODE_X1,        NULL, IDS_DS_SLOWMOTION_X1,        NULL,       MenuItemMovieSlowMotionMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieSlowMotionMode_X2        = { ITEMID_MOVIE_SLOWMOTION_MODE_X2,        NULL, IDS_DS_SLOWMOTION_X2,        NULL,       MenuItemMovieSlowMotionMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieSlowMotionMode_X4        = { ITEMID_MOVIE_SLOWMOTION_MODE_X4,        NULL, IDS_DS_SLOWMOTION_X4,        NULL,       MenuItemMovieSlowMotionMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieSlowMotionMode_X8        = { ITEMID_MOVIE_SLOWMOTION_MODE_X8,        NULL, IDS_DS_SLOWMOTION_X8,        NULL,       MenuItemMovieSlowMotionMode, 0,AHC_TRUE, NULL };
#endif

// WNR On/Off
#if (MENU_MOVIE_WNR_MODE_EN)
SMENUITEM sItemMovieWNRMode            = { ITEMID_MOVIE_WNR_MODE,           NULL, IDS_DS_WNR,           &sSubMovieWNRMode, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMovieWNRMode_On         = { ITEMID_MOVIE_WNR_MODE_ON,        NULL, IDS_DS_ON,            NULL,       MenuItemMovieWNRMode, 0,AHC_TRUE, NULL };
SMENUITEM sItemMovieWNRMode_Off        = { ITEMID_MOVIE_WNR_MODE_OFF,       NULL, IDS_DS_OFF,           NULL,       MenuItemMovieWNRMode, 0,AHC_TRUE, NULL };
#endif


//RearCam type
#if(MENU_REARCAM_TYPE_EN)
SMENUITEM sItemRearCamType                          ={ITEMID_REARCAM_TYPE,                  NULL, IDS_DS_REARCAMTYPE,           &sSubRearCamType, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_None                     ={ITEMID_REARCAM_TYPE_NONE,                 NULL, IDS_DS_NONE,                              NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_AIT                      ={ITEMID_REARCAM_TYPE_AIT,              NULL, IDS_DS_AIT,                   NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_SONIX_MJPEG2H264         ={ITEMID_REARCAM_TYPE_SONIX_MJPEG2H264, NULL, IDS_DS_SONIXMJPEG2H264,       NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_SONIX_MJPEG              ={ITEMID_REARCAM_TYPE_SONIX_MJPEG,      NULL, IDS_DS_SONIXMJPEG,            NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_TV_DECODER               ={ITEMID_REARCAM_TYPE_TV_DECODER,       NULL, IDS_DS_TVDECODER,         NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_BAYER_SENSOR             ={ITEMID_REARCAM_TYPE_BAYER_SENSOR,         NULL, IDS_DS_BAYERSENSOR,           NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
SMENUITEM sItemRearCamType_YUV_SENSOR               ={ITEMID_REARCAM_TYPE_YUV_SENSOR,       NULL, IDS_DS_YUVSENSOR,         NULL,               MenuItemRearCamType,0, AHC_TRUE, NULL };
#endif
/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

#if (MENU_MOVIE_SIZE_EN)
PSMENUITEM   sMenuListMovieMode[] =
{
#if (MENU_MOVIE_SIZE_4K_24P_EN)
    &sItemMovieMode_4K_24P,
#endif
#if (MENU_MOVIE_SIZE_1440_30P_EN)
    &sItemMovieMode_1440_30P,
#endif
#if (MENU_MOVIE_SIZE_SHD_30P_EN)
    &sItemMovieMode_SHD,
#endif
#if (MENU_MOVIE_SIZE_SHD_25P_EN)
    &sItemMovieMode_SHD_25P,
#endif
#if (MENU_MOVIE_SIZE_SHD_24P_EN)
    &sItemMovieMode_SHD_24P,
#endif
#if (MENU_MOVIE_SIZE_1080_60P_EN)
    &sItemMovieMode_FHD_60P,
#endif

#if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) ||(MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
    &sItemMovieMode_FHD_HDR,
#endif

#if (MENU_MOVIE_SIZE_1080P_EN)
    &sItemMovieMode_FHD,
#endif
#ifdef  MOVIE_SIZE_MENU_ORDER_1
#if (MENU_MOVIE_SIZE_720_60P_EN)
    &sItemMovieMode_HD_60P,
#endif
#if (MENU_MOVIE_SIZE_720P_EN)
    &sItemMovieMode_HD,
#endif
#else
#if (MENU_MOVIE_SIZE_720P_EN)
    &sItemMovieMode_HD,
#endif
#if (MENU_MOVIE_SIZE_720_60P_EN)
    &sItemMovieMode_HD_60P,
#endif
#if (MENU_MOVIE_SIZE_1080_24P_EN)
    &sItemMovieMode_FHD_24P,
#endif
#if (MENU_MOVIE_SIZE_720_24P_EN)
    &sItemMovieMode_HD_24P,
#endif
#endif
#if (MENU_MOVIE_SIZE_VGA30P_EN)
    &sItemMovieMode_VGA_30P,
#endif
#if (MENU_MOVIE_SIZE_VGA120P_EN)
    &sItemMovieMode_VGA_120P
#endif
};
#endif

#if (MENU_MOVIE_QUALITY_EN)
PSMENUITEM   sMenuListMovieQuality[] =
{
#if (MENU_MOVIE_QUALITY_SUPER_FINE_EN)
    &sItemMovieQuality_Super_Fine,
#endif
#if (MENU_MOVIE_QUALITY_FINE_EN)
    &sItemMovieQuality_Fine
#endif
};
#endif

#if (MENU_MOVIE_STABILIZE_EN)
PSMENUITEM   sMenuListMovieStable[] =
{
#if (MENU_MOVIE_STABILIZE_ON_EN)
    &sItemMovieStabilization_On,
#endif
#if (MENU_MOVIE_STABILIZE_OFF_EN)
    &sItemMovieStabilization_Off
#endif
};
#endif

#if (MENU_MOVIE_SLOW_SHUTTER_EN)
PSMENUITEM   sMenuListAutoSlowShutter[] =
{
#if (MENU_MOVIE_SLOW_SHUTTER_ON_EN)
    &sItemAutoSlowShutter_On,
#endif
#if (MENU_MOVIE_SLOW_SHUTTER_OFF_EN)
    &sItemAutoSlowShutter_Off
#endif
};
#endif

#if (MENU_MOVIE_MIC_SEN_EN)
PSMENUITEM   sMenuListMICSensitivity[] =
{
#if (MENU_MOVIE_MIC_SEN_STANDARD_EN)
    &sItemMICSensitivity_Standard,
#endif
#if (MENU_MOVIE_MIC_SEN_LOW_EN)
    &sItemMICSensitivity_Low
#endif
};
#endif

#if (MENU_MOVIE_PRE_RECORD_EN)
PSMENUITEM   sMenuListMoviePreRecord[] =
{
#if (MENU_MOVIE_PRE_RECORD_ON_EN)
    &sItemMoviePreRecord_On,
#endif
#if (MENU_MOVIE_PRE_RECORD_OFF_EN)
    &sItemMoviePreRecord_Off
#endif
};
#endif

#if (MENU_MOVIE_CLIP_TIME_EN)
PSMENUITEM   sMenuListMovieClipTime[] =
{
#if (MENU_MOVIE_CLIP_TIME_OFF_EN)
    &sItemMovieClipTime_off,
#endif
#if (MENU_MOVIE_CLIP_TIME_6SEC_EN)
    &sItemMovieClipTime_6sec,
#endif
#if (MENU_MOVIE_CLIP_TIME_1MIN_EN)
    &sItemMovieClipTime_1min,
#endif
#if (MENU_MOVIE_CLIP_TIME_2MIN_EN)
    &sItemMovieClipTime_2min,
#endif
#if (MENU_MOVIE_CLIP_TIME_3MIN_EN)
    &sItemMovieClipTime_3min,
#endif
#if (MENU_MOVIE_CLIP_TIME_5MIN_EN)
    &sItemMovieClipTime_5min,
#endif
#if (MENU_MOVIE_CLIP_TIME_10MIN_EN)
    &sItemMovieClipTime_10min,
#endif
#if (MENU_MOVIE_CLIP_TIME_25MIN_EN)
    &sItemMovieClipTime_25min,
#endif
#if (MENU_MOVIE_CLIP_TIME_30MIN_EN)
    &sItemMovieClipTime_30min,
#endif
};
#endif

#if (MENU_MOVIE_NIGHT_MODE_EN)
PSMENUITEM   sMenuListMovieNightMode[] =
{
#if (MENU_MOVIE_NIGHT_MODE_ON_EN)
    &sItemMovieNightMode_On,
#endif
#if (MENU_MOVIE_NIGHT_MODE_OFF_EN)
    &sItemMovieNightMode_Off
#endif
};
#endif

#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
PSMENUITEM   sMenuListMoviePowerOffTime[] =
{
#if (MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN)
    &sItemMoviePowerOffTime_0min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN)
    &sItemMoviePowerOffTime_5sec,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN)
    &sItemMoviePowerOffTime_10sec,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN)
    &sItemMoviePowerOffTime_15sec,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN)
    &sItemMoviePowerOffTime_30sec,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN)
    &sItemMoviePowerOffTime_1min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_2MIN_EN)
    &sItemMoviePowerOffTime_2min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_3MIN_EN)
    &sItemMoviePowerOffTime_3min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_5MIN_EN)
    &sItemMoviePowerOffTime_5min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_10MIN_EN)
    &sItemMoviePowerOffTime_10min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_15MIN_EN)
    &sItemMoviePowerOffTime_15min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_30MIN_EN)
    &sItemMoviePowerOffTime_30min,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_60MIN_EN)
    &sItemMoviePowerOffTime_60min
#endif
};
#endif

#if (MENU_MOVIE_SOUND_RECORD_EN)
PSMENUITEM  sMenuListMovieSoundRecord[] =
{
#if (MENU_MOVIE_SOUND_RECORD_ON_EN)
    &sItemMovieSoundRecord_On,
#endif
#if (MENU_MOVIE_SOUND_RECORD_OFF_EN)
    &sItemMovieSoundRecord_Off,
#endif
};
#endif

#if (MENU_MOVIE_VMD_REC_TIME_EN)
PSMENUITEM   sMenuListMovieVMDRecTime[] =
{
#if (MENU_MOVIE_VMD_REC_TIME_5SEC_EN)
    &sItemMovieVMDRecTime_5sec,
#endif
#if (MENU_MOVIE_VMD_REC_TIME_10SEC_EN)
    &sItemMovieVMDRecTime_10sec,
#endif
#if (MENU_MOVIE_VMD_REC_TIME_30SEC_EN)
    &sItemMovieVMDRecTime_30sec,
#endif
#if (MENU_MOVIE_VMD_REC_TIME_1MIN_EN)
    &sItemMovieVMDRecTime_1min,
#endif
};
#endif

#if (MENU_MOVIE_AUTO_REC_EN)
PSMENUITEM   sMenuMovieAutoRec[] =
{
    &sItemMovieAutoRec_On,
    &sItemMovieAutoRec_Off
};
#endif

#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
PSMENUITEM   sMenuMovieTimelapse[] =
{
    &sItemMovieTimelapse_Off,
    &sItemMovieTimelapse_1Sec,
    &sItemMovieTimelapse_5Sec,
    &sItemMovieTimelapse_10Sec,
    &sItemMovieTimelapse_30Sec,
    &sItemMovieTimelapse_60Sec,
};
#endif

#if (MENU_MOVIE_PARKING_MODE_EN)
PSMENUITEM   sMenuMovieParkingMode[] =
{
    &sItemMovieParkingMode_On,
    &sItemMovieParkingMode_Off,
};
#endif

#if (MENU_MOVIE_LDWS_MODE_EN)
PSMENUITEM   sMenuMovieLDWSMode[] =
{
    &sItemMovieLDWSMode_On,
    &sItemMovieLDWSMode_Off,
};
#endif

#if (MENU_MOVIE_FCWS_MODE_EN)
PSMENUITEM   sMenuMovieFCWSMode[] =
{
    &sItemMovieFCWSMode_On,
    &sItemMovieFCWSMode_Off,
};
#endif

#if (MENU_MOVIE_SAG_MODE_EN)
PSMENUITEM   sMenuMovieSAGMode[] =
{
    &sItemMovieSAGMode_On,
    &sItemMovieSAGMode_Off,
};
#endif

#if (MENU_MOVIE_HDR_MODE_EN)
PSMENUITEM   sMenuMovieHDRMode[] =
{
    &sItemMovieHDRMode_On,
    &sItemMovieHDRMode_Off,
};
#endif

#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
PSMENUITEM   sMenuMovieSlowMotionMode[] =
{
    &sItemMovieSlowMotionMode_X1,
    &sItemMovieSlowMotionMode_X2,
    &sItemMovieSlowMotionMode_X4,
    &sItemMovieSlowMotionMode_X8,
};
#endif

#if (MENU_MOVIE_WNR_MODE_EN)
PSMENUITEM   sMenuMovieWNRMode[] =
{
    &sItemMovieWNRMode_Off,
    &sItemMovieWNRMode_On,

};
#endif

#if(MENU_REARCAM_TYPE_EN)
PSMENUITEM   sMenuRearCamType[] =
{
    &sItemRearCamType_None,
    &sItemRearCamType_AIT,
    &sItemRearCamType_SONIX_MJPEG,
    &sItemRearCamType_SONIX_MJPEG2H264,
    &sItemRearCamType_TV_DECODER,
    &sItemRearCamType_BAYER_SENSOR,
    &sItemRearCamType_YUV_SENSOR,
};

#endif

PSMENUITEM   sMenuListMainVideo[] =
{
#if (MENU_MOVIE_SIZE_EN)
    &sItemMovieMode,
#endif

#if defined (CFG_LIST_STILL_IMAGE_SIZE) /*may be defined in config_xxx.h*/ && (MENU_STILL_SIZE_EN)
    &sItemStillImageSize,
#endif

#if (MENU_MOVIE_QUALITY_EN)
    &sItemMovieQuality,
#endif
#if (MENU_MOVIE_CLIP_TIME_EN)
    &sItemMovieClipTime,
#endif
#if (MENU_MOVIE_NIGHT_MODE_EN)
    &sItemMovieNightMode,
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
    &sItemMoviePowerOffTime,
#endif
#if (MENU_MOVIE_VMD_REC_TIME_EN)
    &sItemMovieVMDRecTime,
#endif
#if (MENU_MOVIE_AUTO_REC_EN)
    &sItemMovieAutoRec,
#endif
#if (MENU_MOVIE_SOUND_RECORD_EN)
    &sItemMovieSoundRecord,
#endif
#if (MENU_MOVIE_PRE_RECORD_EN)
    &sItemMoviePreRecord,
#endif
#if (MENU_MOVIE_MIC_SEN_EN)
    &sItemMICSensitivity,
#endif
#if (MENU_MOVIE_SCENE_EN)
    &sItemScence,
#endif
#if (MENU_MOVIE_EV_EN)
    &sItemEV,
#endif
#if (MENU_MOVIE_WB_EN)
    &sItemWB,
#endif
#if (MENU_MOVIE_ISO_EN)
    &sItemISO,
#endif
#if (MENU_MOVIE_COLOR_EN)
    &sItemColor,
#endif
#if (MENU_MOVIE_EFFECT_EN)
    &sItemEffect,
#endif
#if (MENU_MOVIE_PARKING_MODE_EN)
    &sItemMovieParkingMode,
#endif
#if (MENU_MOVIE_LDWS_MODE_EN)
    &sItemMovieLDWSMode,
#endif
#if (MENU_MOVIE_FCWS_MODE_EN)
    &sItemMovieFCWSMode,
#endif
#if (MENU_MOVIE_SAG_MODE_EN)
    &sItemMovieSAGMode,
#endif
#if (MENU_MOVIE_HDR_MODE_EN)
    &sItemMovieHDRMode,
#endif
#if (MENU_MOVIE_CONTRAST_EN)
    &sItemContrast,
#endif
#if (MENU_MOVIE_SATURATION_EN)
    &sItemSaturation,
#endif
#if (MENU_MOVIE_SHARPNESS_EN)
    &sItemSharpness,
#endif
#if (MENU_MOVIE_GAMMA_EN)
    &sItemGamma,
#endif
#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
    &sItemMovieTimelapse,
#endif
#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
    &sItemMovieSlowMotionMode,
#endif
#if (MENU_MOVIE_WNR_MODE_EN)
    &sItemMovieWNRMode,
#endif
#if (MENU_REARCAM_TYPE_EN)
    &sItemRearCamType,
#endif
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuVideo =
{
    MENUID_MAIN_MENU_VIDEO,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuListMainVideo)/sizeof(PSMENUITEM),
    sMenuListMainVideo,
    MainMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};

//--------------SUB MENU-------------------

#if (MENU_MOVIE_SIZE_EN)
SMENUSTRUCT sSubMovieMode =
{
    MENUID_SUB_MENU_MOVIE_MODE,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuListMovieMode)/sizeof(PSMENUITEM),
    sMenuListMovieMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_QUALITY_EN)
SMENUSTRUCT sSubMovieQuality =
{
    MENUID_SUB_MENU_MOVIE_QUALITY,
    NULL,
    IDS_DS_MOVIE_QUALITY,
    NULL,
    sizeof(sMenuListMovieQuality)/sizeof(PSMENUITEM),
    sMenuListMovieQuality,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_MOVIE_QUALITY_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_STABILIZE_EN)
SMENUSTRUCT sSubMovieStable =
{
    MENUID_SUB_MENU_MOVIE_STABLEILIZATION,
    NULL,
    IDS_DS_MOVIE_STABLEILIZATION,
    NULL,
    sizeof(sMenuListMovieStable)/sizeof(PSMENUITEM),
    sMenuListMovieStable,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_MOVIE_STABLE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_SLOW_SHUTTER_EN)
SMENUSTRUCT sSubAutoSlowShutter =
{
    MENUID_SUB_MENU_AUTO_SLOW_SHUTTER,
    NULL,
    IDS_DS_AUTO_SLOW_SHUTTER,
    NULL,
    sizeof(sMenuListAutoSlowShutter)/sizeof(PSMENUITEM),
    sMenuListAutoSlowShutter,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_ASSHUTTER_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_MIC_SEN_EN)
SMENUSTRUCT sSubMICSensitivity =
{
    MENUID_SUB_MENU_MIC_SENSITIVITY,
    NULL,
    IDS_DS_MIC_SENSITIVITY,
    NULL,
    sizeof(sMenuListMICSensitivity)/sizeof(PSMENUITEM),
    sMenuListMICSensitivity,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_MIC_SENSITIVITY_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_PRE_RECORD_EN)
SMENUSTRUCT sSubMoviePreRecord =
{
    MENUID_SUB_MENU_MOVIE_PRERECORD,
    NULL,
    IDS_DS_MOVIE_PRE_RECORD,
    NULL,
    sizeof(sMenuListMoviePreRecord)/sizeof(PSMENUITEM),
    sMenuListMoviePreRecord,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_MOVIE_PRE_RECORD_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_CLIP_TIME_EN)
SMENUSTRUCT sSubMovieClipTime =
{
    MENUID_SUB_MENU_MOVIE_CLIPTIME,
    NULL,
    IDS_MOVIE_CLIPTIME,
    NULL,
    sizeof(sMenuListMovieClipTime)/sizeof(PSMENUITEM),
    sMenuListMovieClipTime,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_MOVIE_CLIPTIME,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_NIGHT_MODE_EN)
SMENUSTRUCT sSubMovieNightMode =
{
    MENUID_SUB_MENU_MOVIE_NIGHT_MODE,
    NULL,
    IDS_DS_NIGHT_MODE,
    NULL,
    sizeof(sMenuListMovieNightMode)/sizeof(PSMENUITEM),
    sMenuListMovieNightMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_NIGHT_MODE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
SMENUSTRUCT sSubMoviePowerOffTime =
{
    MENUID_SUB_MENU_MOVIE_POWER_OFF_TIME,
    NULL,
    CFG_POWER_OFF_STR_ID,
    NULL,
    sizeof(sMenuListMoviePowerOffTime)/sizeof(PSMENUITEM),
    sMenuListMoviePowerOffTime,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    CFG_POWER_OFF_STR_ID,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_SOUND_RECORD_EN)
SMENUSTRUCT sSubMovieSoundRecord =
{
    MENUID_SUB_MENU_MOVIE_SOUND_RECORD,
    NULL,
    IDS_MOVIE_SOUND_RECORD,
    NULL,
    sizeof(sMenuListMovieSoundRecord)/sizeof(PSMENUITEM),
    sMenuListMovieSoundRecord,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_MOVIE_SOUND_RECORD,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_VMD_REC_TIME_EN)
SMENUSTRUCT sSubMovieVMDRecTime =
{
    MENUID_SUB_MENU_MOVIE_VMD_REC_TIME,
    NULL,
    IDS_VMD_REC_TIME,
    NULL,
    sizeof(sMenuListMovieVMDRecTime)/sizeof(PSMENUITEM),
    sMenuListMovieVMDRecTime,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_VMD_REC_TIME,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_AUTO_REC_EN)
SMENUSTRUCT sSubMovieAutoRec =
{
    MENUID_SUB_MENU_MOVIE_AUTO_REC,
    NULL,
    IDS_AUTO_REC,
    NULL,
    sizeof(sMenuMovieAutoRec)/sizeof(PSMENUITEM),
    sMenuMovieAutoRec,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_AUTO_REC,
    AHC_FALSE,
    0
};
#endif

#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
SMENUSTRUCT sSubMovieTimelapse =
{
    MENUID_SUB_MENU_VIDEO_TIMELAPSE,
    NULL,
    IDS_DS_TIMELAPSE,
    NULL,
    sizeof(sMenuMovieTimelapse)/sizeof(PSMENUITEM),
    sMenuMovieTimelapse,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_TIMELAPSE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_PARKING_MODE_EN)
SMENUSTRUCT sSubMovieParkingMode =
{
    MENUID_SUB_MENU_MOVIE_PARKING_MODE,
    NULL,
    IDS_DS_PARKING_MODE,
    NULL,
    sizeof(sMenuMovieParkingMode)/sizeof(PSMENUITEM),
    sMenuMovieParkingMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_PARKING_MODE,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_LDWS_MODE_EN)
SMENUSTRUCT sSubMovieLDWSMode =
{
    MENUID_SUB_MENU_MOVIE_LDWS_MODE,
    NULL,
    IDS_DS_LDWS,
    NULL,
    sizeof(sMenuMovieLDWSMode)/sizeof(PSMENUITEM),
    sMenuMovieLDWSMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_LDWS,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_FCWS_MODE_EN)
SMENUSTRUCT sSubMovieFCWSMode =
{
    MENUID_SUB_MENU_MOVIE_FCWS_MODE,
    NULL,
    IDS_DS_FCWS,
    NULL,
    sizeof(sMenuMovieFCWSMode)/sizeof(PSMENUITEM),
    sMenuMovieFCWSMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_FCWS,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_SAG_MODE_EN)
SMENUSTRUCT sSubMovieSAGMode =
{
    MENUID_SUB_MENU_MOVIE_SAG_MODE,
    NULL,
    IDS_DS_SAG,
    NULL,
    sizeof(sMenuMovieSAGMode)/sizeof(PSMENUITEM),
    sMenuMovieSAGMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_SAG,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_HDR_MODE_EN)
SMENUSTRUCT sSubMovieHDRMode =
{
    MENUID_SUB_MENU_MOVIE_HDR_MODE,
    NULL,
    IDS_DS_HDR,
    NULL,
    sizeof(sMenuMovieHDRMode)/sizeof(PSMENUITEM),
    sMenuMovieHDRMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_HDR,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
SMENUSTRUCT sSubMovieSlowMotionMode =
{
    MENUID_SUB_MENU_MOVIE_SLOWMOTION_MODE,
    NULL,
    IDS_DS_SLOWMOTION,
    NULL,
    sizeof(sMenuMovieSlowMotionMode)/sizeof(PSMENUITEM),
    sMenuMovieSlowMotionMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_SLOWMOTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MOVIE_WNR_MODE_EN)
SMENUSTRUCT sSubMovieWNRMode =
{
    MENUID_SUB_MENU_MOVIE_WNR_MODE,
    NULL,
    IDS_DS_WNR,
    NULL,
    sizeof(sMenuMovieWNRMode)/sizeof(PSMENUITEM),
    sMenuMovieWNRMode,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_WNR,
    AHC_FALSE,
    0
};
#endif

#if(MENU_REARCAM_TYPE_EN)
SMENUSTRUCT sSubRearCamType =
{
    MENUID_SUB_MENU_REAR_TYPE,
    NULL,
    IDS_DS_NONE,
    NULL,
    sizeof(sMenuRearCamType)/sizeof(PSMENUITEM),
    sMenuRearCamType,
    SubMenuEventHandler,
    MenuGetDefault_Movie,
    0,
    IDS_DS_WNR,
    AHC_FALSE,
    0
};
#endif
/*===========================================================================
 * Main body
 *===========================================================================*/

#if (MENU_MOVIE_SIZE_EN)
AHC_BOOL MenuItemMovieMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMOVSize= pItem->iItemId - ITEMID_MOVIE_MODE -1;
    Menu_SetMovieMode(MenuSettingConfig()->uiMOVSize);
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_QUALITY_EN)
AHC_BOOL MenuItemMovieQuality(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMOVQuality = pItem->iItemId - ITEMID_MOVIE_QUALITY -1;
    Menu_SetMovieQuality(MenuSettingConfig()->uiMOVQuality);
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_STABILIZE_EN)
AHC_BOOL MenuItemMovieStable(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMOVStabilize = pItem->iItemId - ITEMID_MOVIE_STABLEILIZATION -1;
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_SLOW_SHUTTER_EN)
AHC_BOOL MenuItemAutoSlowShutter(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSlowShutter = pItem->iItemId - ITEMID_AUTO_SLOW_SHUTTER -1;
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_MIC_SEN_EN)
AHC_BOOL MenuItemMICSensitivity(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMicSensitivity = pItem->iItemId - ITEMID_MIC_SENSITIVITY -1;
    Menu_SetMICSensitivity(MenuSettingConfig()->uiMicSensitivity);
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_PRE_RECORD_EN)
AHC_BOOL MenuItemMoviePreRecord(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    #if (VR_PREENCODE_EN)
    extern AHC_BOOL     m_ubPreEncodeEn;
    #endif

    if (ITEMID_MOVIE_PRE_RECORD_ON == pItem->iItemId)
        MenuSettingConfig()->uiMOVPreRecord = MOVIE_PRE_RECORD_ON;
    else
        MenuSettingConfig()->uiMOVPreRecord = MOVIE_PRE_RECORD_OFF;

    #if (VR_PREENCODE_EN)
    m_ubPreEncodeEn = (MenuSettingConfig()->uiMOVPreRecord == MOVIE_PRE_RECORD_ON)?(AHC_TRUE):(AHC_FALSE);
    #endif

    if(MenuSettingConfig()->uiMOVPreRecord == MOVIE_PRE_RECORD_ON)
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_PRERECORD_STATUS, 1);
    else
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_PRERECORD_STATUS, 0);
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_CLIP_TIME_EN)
AHC_BOOL MenuItemMovieClipTime(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMOVClipTime = pItem->iItemId - ITEMID_MOVIE_CLIPTIME -1;
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_NIGHT_MODE_EN)
AHC_BOOL MenuItemMovieNightMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    if (ITEMID_MOVIE_NIGHT_MODE_ON == pItem->iItemId) {
        printc("MenuItemMovieNightMode: NIGHT_MODE ON\r\n");
        pf_NightMode_EnSet(COMMON_NIGHT_MODE_EN_ON);
    }
    else {
        printc("MenuItemMovieNightMode: NIGHT_MODE OFF\r\n");
        pf_NightMode_EnSet(COMMON_NIGHT_MODE_EN_OFF);
    }
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
AHC_BOOL MenuItemMoviePowerOffTime(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMOVPowerOffTime = pItem->iItemId - ITEMID_MOVIE_POWEROFF_TIME -1;
    VideoPowerOffCounterReset();
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_SOUND_RECORD_EN)
AHC_BOOL MenuItemMovieSoundRecord(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    extern AHC_BOOL bMuteRecord;

    MenuSettingConfig()->uiMOVSoundRecord = pItem->iItemId - ITEMID_MOVIE_SOUND_RECORD -1;
    bMuteRecord = (MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON)?(AHC_FALSE):(AHC_TRUE);
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_VMD_REC_TIME_EN)
AHC_BOOL MenuItemMovieVMDRecTime(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiVMDRecTime = pItem->iItemId - ITEMID_MOVIE_VMD_REC_TIME -1;
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_AUTO_REC_EN)
AHC_BOOL MenuItemMovieAutoRec(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiAutoRec = pItem->iItemId - ITEMID_MOVIE_AUTO_REC -1;
    return AHC_TRUE;
}
#endif

#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
AHC_BOOL MenuItemMovieTimelapse(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    pf_General_EnSet(COMMON_KEY_VR_TIMELAPSE, pItem->iItemId - ITEMID_MOVIE_TIMELAPSE -1);

    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_PARKING_MODE_EN)
AHC_BOOL MenuItemMovieParkingMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    AHC_BOOL bParkingModeEn;

    bParkingModeEn = (pItem->iItemId - ITEMID_MOVIE_PARKING_MODE -1)? AHC_FALSE : AHC_TRUE;
    printc("MenuItemMovieParkingMode = %d\n", bParkingModeEn);

    #if(SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
    uiSetParkingModeEnable( bParkingModeEn );
    #endif
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_LDWS_MODE_EN)
AHC_BOOL MenuItemMovieLDWSMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    if (ITEMID_MOVIE_LDWS_MODE_ON == pItem->iItemId) {
        pf_LDWS_EnSet(LDWS_EN_ON);

        #if ((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) && MOTION_DETECTION_EN) // TBD
        // Turn-Off VMD
        MenuSettingConfig()->uiMotionDtcSensitivity = MOTION_DTC_SENSITIVITY_OFF;
        Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
        #endif
    }
    else {
        pf_LDWS_EnSet(LDWS_EN_OFF);

    }

    printc("%s = %d\n", __func__, pf_LDWS_EnGet());

    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_FCWS_MODE_EN)
AHC_BOOL MenuItemMovieFCWSMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    if (ITEMID_MOVIE_FCWS_MODE_ON == pItem->iItemId) {

        pf_FCWS_EnSet(FCWS_EN_ON);

        #if ((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) && MOTION_DETECTION_EN) // TBD
        // Turn-Off VMD
        MenuSettingConfig()->uiMotionDtcSensitivity = MOTION_DTC_SENSITIVITY_OFF;
        Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
        #endif
    }
    else {
        pf_FCWS_EnSet(FCWS_EN_OFF);
    }
    printc("%s = %d\n", __func__, pf_FCWS_EnGet());

    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_SAG_MODE_EN)
AHC_BOOL MenuItemMovieSAGMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    if (ITEMID_MOVIE_SAG_MODE_ON == pItem->iItemId) {
        //pf_LDWS_EnSet(LDWS_EN_ON);
        //pf_FCWS_EnSet(FCWS_EN_ON);
        pf_SAG_EnSet(SAG_EN_ON);

        #if ((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) && MOTION_DETECTION_EN) // TBD
        // Turn-Off VMD
        MenuSettingConfig()->uiMotionDtcSensitivity = MOTION_DTC_SENSITIVITY_OFF;
        Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
        #endif
    }
    else {
        pf_SAG_EnSet(SAG_EN_OFF);
    }

    printc("%s = %d\n", __func__, pf_SAG_EnGet());
    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_HDR_MODE_EN)
AHC_BOOL MenuItemMovieHDRMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if SNR_CLK_POWER_SAVING_SETTING
    pf_HDR_EnSet(COMMON_HDR_EN_OFF);
#else
    if (ITEMID_MOVIE_HDR_MODE_ON == pItem->iItemId)
        pf_HDR_EnSet(COMMON_HDR_EN_ON);
    else
        pf_HDR_EnSet(COMMON_HDR_EN_OFF);

    printc("%s = %d\n", __func__, pf_HDR_EnGet());
#endif

    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
UINT8 setVal;
AHC_BOOL MenuItemMovieSlowMotionMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    setVal = pItem->iItemId - ITEMID_MOVIE_SLOWMOTION_MODE -1;
    printc(FG_RED("***** setVal = %d \r\n"),setVal);
    pf_SLOWMOTION_EnSet(setVal);

    return AHC_TRUE;
}
#endif

#if (MENU_MOVIE_WNR_MODE_EN)
AHC_BOOL MenuItemMovieWNRMode(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if SNR_CLK_POWER_SAVING_SETTING
    pf_WNR_EnSet(COMMON_WNR_EN_OFF);
#else
    if (ITEMID_MOVIE_WNR_MODE_ON == pItem->iItemId)
        pf_WNR_EnSet(COMMON_WNR_EN_ON);
    else
        pf_WNR_EnSet(COMMON_WNR_EN_OFF);

    printc("%s = %d\n", __func__, pf_WNR_EnGet());
#endif

    return AHC_TRUE;
}
#endif

#if(MENU_REARCAM_TYPE_EN)
AHC_BOOL MenuItemRearCamType(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    int id;

    switch(pItem->iItemId)
    {
        case ITEMID_REARCAM_TYPE_NONE:
            id = SCD_CAM_NONE;
            break;
        case ITEMID_REARCAM_TYPE_AIT:
            id = USB_CAM_AIT;
            break;
        case ITEMID_REARCAM_TYPE_SONIX_MJPEG:
            id = USB_CAM_SONIX_MJPEG;
            break;
        case ITEMID_REARCAM_TYPE_SONIX_MJPEG2H264:
            id = USB_CAM_SONIX_MJPEG2H264;
            break;
        case ITEMID_REARCAM_TYPE_TV_DECODER:
            id = USB_CAM_SONIX_MJPEG2H264 + SCD_CAM_ANA_DECODER;
            break;
        case ITEMID_REARCAM_TYPE_BAYER_SENSOR:
            id = USB_CAM_SONIX_MJPEG2H264 + SCD_CAM_BAYER_SENSOR;
            break;
        case ITEMID_REARCAM_TYPE_YUV_SENSOR:
            id = USB_CAM_SONIX_MJPEG2H264 + SCD_CAM_YUV_SENSOR;
            break;
        default:
            id = SCD_CAM_NONE;
            break;
    }

    printc("%s : RearCam ID= %d\n", __func__, id);

    pf_RearCamType_EnSet(id);

    if (pItem->iItemId == ITEMID_REARCAM_TYPE_NONE) {
        MMP_SetScdCamType(SCD_CAM_NONE);
        MMP_SetUSBCamType(USB_CAM_NONE);
    }
    else if (id == USB_CAM_AIT ||
             id == USB_CAM_SONIX_MJPEG ||
             id == USB_CAM_SONIX_MJPEG2H264) {
        MMP_SetScdCamType(SCD_CAM_NONE);
        MMP_SetUSBCamType(id);
    }
    else if (id == SCD_CAM_ANA_DECODER ||
             id == SCD_CAM_BAYER_SENSOR ||
             id == SCD_CAM_YUV_SENSOR) {
        MMP_SetScdCamType(id);
        MMP_SetUSBCamType(USB_CAM_NONE);
    }

    MMPC_3gpRecd_InitConfig();
    MMPC_3gpPlay_InitConfig();
    MMPC_Audio_InitConfig();

    #if (SUPPORT_USB_HOST_FUNC)
    MMP_InitUSBHConfig(CAM_GET_USB);
    #endif

    printc( "MenuChangeRearCamType(%d)\r\n", id);
    StateSwitchMode(UI_VIDEO_STATE);
    return AHC_TRUE;
}
#endif

UINT32 MenuGetDefault_Movie(PSMENUSTRUCT pMenu)
{
    UINT32  DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_MOVIE_SIZE_EN)
        case MENUID_SUB_MENU_MOVIE_MODE:
            DefaultValue = MenuSettingConfig()->uiMOVSize ;
            break;
#endif
#if (MENU_MOVIE_QUALITY_EN)
        case MENUID_SUB_MENU_MOVIE_QUALITY:
            DefaultValue = MenuSettingConfig()->uiMOVQuality ;
            break;
#endif
#if (MENU_MOVIE_STABILIZE_EN)
        case MENUID_SUB_MENU_MOVIE_STABLEILIZATION:
            DefaultValue = MenuSettingConfig()->uiMOVStabilize;
            break;
#endif
#if (MENU_MOVIE_SLOW_SHUTTER_EN)
        case MENUID_SUB_MENU_AUTO_SLOW_SHUTTER:
            DefaultValue = MenuSettingConfig()->uiSlowShutter;
            break;
#endif
#if (MENU_MOVIE_MIC_SEN_EN)
        case MENUID_SUB_MENU_MIC_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiMicSensitivity;
            break;
#endif
#if (MENU_MOVIE_PRE_RECORD_EN)
        case MENUID_SUB_MENU_MOVIE_PRERECORD:
            DefaultValue = MenuSettingConfig()->uiMOVPreRecord;
            break;
#endif
#if (MENU_MOVIE_CLIP_TIME_EN)
        case MENUID_SUB_MENU_MOVIE_CLIPTIME:
            DefaultValue = MenuSettingConfig()->uiMOVClipTime;
            break;
#endif
#if (MENU_MOVIE_POWER_OFF_DELAY_EN)
        case MENUID_SUB_MENU_MOVIE_POWER_OFF_TIME:
            DefaultValue = MenuSettingConfig()->uiMOVPowerOffTime;
            break;
#endif
#if (MENU_MOVIE_SOUND_RECORD_EN)
        case MENUID_SUB_MENU_MOVIE_SOUND_RECORD:
            DefaultValue = MenuSettingConfig()->uiMOVSoundRecord;
            break;
#endif
#if (MENU_MOVIE_VMD_REC_TIME_EN)
        case MENUID_SUB_MENU_MOVIE_VMD_REC_TIME:
            DefaultValue = MenuSettingConfig()->uiVMDRecTime;
            break;
#endif
#if (MENU_MOVIE_AUTO_REC_EN)
        case MENUID_SUB_MENU_MOVIE_AUTO_REC:
            DefaultValue = MenuSettingConfig()->uiAutoRec;
            break;
#endif
#if (MENU_VIDEO_TIMELAPSE_MODE_EN)  // VIDEO_REC_TIMELAPSE_EN
        case MENUID_SUB_MENU_VIDEO_TIMELAPSE:
            pf_General_EnGet(COMMON_KEY_VR_TIMELAPSE, (INT32 *) &DefaultValue);
            break;
#endif
#if (MENU_MOVIE_PARKING_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_PARKING_MODE:
            DefaultValue = ( uiGetParkingModeEnable() == AHC_TRUE )? 0 : 1;
            break;
#endif
#if (MENU_MOVIE_LDWS_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_LDWS_MODE:
            DefaultValue = (pf_LDWS_EnGet() == LDWS_EN_ON) ? (ITEMID_MOVIE_LDWS_MODE_ON - ITEMID_MOVIE_LDWS_MODE - 1) : (ITEMID_MOVIE_LDWS_MODE_OFF - ITEMID_MOVIE_LDWS_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_FCWS_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_FCWS_MODE:
            DefaultValue = (pf_FCWS_EnGet() == FCWS_EN_ON) ? (ITEMID_MOVIE_FCWS_MODE_ON - ITEMID_MOVIE_FCWS_MODE - 1) : (ITEMID_MOVIE_FCWS_MODE_OFF - ITEMID_MOVIE_FCWS_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_SAG_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_SAG_MODE:
            DefaultValue = (pf_SAG_EnGet() == SAG_EN_ON) ? (ITEMID_MOVIE_SAG_MODE_ON - ITEMID_MOVIE_SAG_MODE - 1) : (ITEMID_MOVIE_SAG_MODE_OFF - ITEMID_MOVIE_SAG_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_HDR_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_HDR_MODE:
            DefaultValue = (pf_HDR_EnGet() == HDR_EN_ON) ? (ITEMID_MOVIE_HDR_MODE_ON - ITEMID_MOVIE_HDR_MODE - 1) : (ITEMID_MOVIE_HDR_MODE_OFF - ITEMID_MOVIE_HDR_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_SLOWMOTION_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_SLOWMOTION_MODE:
            DefaultValue = pf_SLOWMOTION_EnGet();
            break;
#endif
#if (MENU_MOVIE_WNR_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_WNR_MODE:
            DefaultValue = (pf_WNR_EnGet() == WNR_EN_ON) ? (ITEMID_MOVIE_WNR_MODE_ON - ITEMID_MOVIE_WNR_MODE - 1) : (ITEMID_MOVIE_WNR_MODE_OFF - ITEMID_MOVIE_WNR_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_NIGHT_MODE_EN)
        case MENUID_SUB_MENU_MOVIE_NIGHT_MODE:
            DefaultValue = (pf_NightMode_EnGet() == COMMON_NIGHT_MODE_EN_ON) ? (ITEMID_MOVIE_NIGHT_MODE_ON - ITEMID_MOVIE_NIGHT_MODE - 1) : (ITEMID_MOVIE_NIGHT_MODE_OFF - ITEMID_MOVIE_NIGHT_MODE - 1);
            break;
#endif
#if (MENU_MOVIE_CONTRAST_EN)
        case MENUID_SUB_MENU_CONTRAST:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_CONTRAST, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MOVIE_SATURATION_EN)
        case MENUID_SUB_MENU_SATURATION:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_SATURATION, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MOVIE_SHARPNESS_EN)
        case MENUID_SUB_MENU_SHARPNESS:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_SHARPNESS, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MOVIE_GAMMA_EN)
        case MENUID_SUB_MENU_GAMMA:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_GAMMA, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_REARCAM_TYPE_EN)
        case MENUID_SUB_MENU_REAR_TYPE:
            {
                INT32 s32Setting = 0;
                pf_General_EnGet(COMMON_KEY_REARCAM_TYPE, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
#endif
    }

    return DefaultValue;
}

#if 0
 UINT32 MenuStateVideoMode( UINT32 ulEvent, UINT32 ulPosition )
{
    //UINT32       ulOperation;
    UINT32       ulResult;
    PSMENUSTRUCT pCurrMenu = NULL;

#if 0
    if( BUTTON_VIRTUAL_RESET == ulEvent )
    {
#if (TOP_MENU_PAGE_EN)
        SetCurrentMenu(&sTopMenu);
#else
        SetCurrentMenu(&sMainMenuVideo);
#endif
    }
#endif

#if 0
    MenuModePreCheck(ulEvent);

    ulOperation = MenuButtonToMenuOp( ulEvent ,ulPosition);

    if(ulOperation == MENU_NONE)
        return;

#ifdef NET_SYNC_PLAYBACK_MODE
    if(EVENT_NET_ENTER_PLAYBACK == ulOperation)
    {
        ResetCurrentMenu();
        Menu_ImportSetting();
        bForceSwitchBrowser = AHC_FALSE;
        StateSwitchMode(UI_NET_PLAYBACK_STATE);
        CGI_SET_STATUS(ulOperation, 0 /* SUCCESSFULLY */)
        return;
    }
#endif
#endif
    pCurrMenu = GetCurrentMenu();

    if(pCurrMenu == NULL)
        return;

    //MainMenuEventHandler
    ulResult = pCurrMenu->pfEventHandler( pCurrMenu, ulEvent, ulPosition );

    if( ulResult == MENU_ERR_EXIT ){
#ifdef SLIDE_MENU
        if(IsSlidingMenu())
            StopSlideMenu();
#endif

        ResetCurrentMenu();
        Menu_ImportSetting();
    }

    return ulResult;
}
#endif

#if 0
void MenuStateClockSettingsMode( UINT32 ulEvent, UINT32 ulPosition )
{
    UINT32       ulOperation;
    UINT32       ulResult;
    PSMENUSTRUCT pCurrMenu = NULL;

    if( BUTTON_VIRTUAL_RESET == ulEvent )
    {
        SetCurrentMenu(&sSubClockSettings);
    }

    MenuModePreCheck(ulEvent);

    ulOperation = MenuButtonToMenuOp( ulEvent ,ulPosition);

    if(ulOperation == MENU_NONE)
        return;

    pCurrMenu = GetCurrentMenu();

    if( pCurrMenu == NULL )
        return;

    //SubMenuEventHandler
    ulResult = pCurrMenu->pfEventHandler( pCurrMenu, ulOperation, ulPosition );

    if( ulResult == MENU_ERR_EXIT )
    {
        ResetCurrentMenu();

        StateSwitchMode(UI_VIDEO_STATE);
    }
}
#endif

#if (SD_UPDATE_FW_EN)
void MenuStateSDUpdateMode( UINT32 ulEvent, UINT32 ulPosition )
{
    SD_UPDATER_ERR eError;

    printc("\r\n MenuStateSDUpdateMode \r\n");

    AHC_SetMode(AHC_MODE_IDLE);

    eError = SDUpdateCheckFileExisted(SD_FW_UPDATER_BIN_NAME);
    if(eError != SD_UPDATER_ERR_FILE) {
        printc(FG_YELLOW("Update SD:\\SD_CarDV.bin success!\r\n"));
    }
    else {
        eError = SDUpdateCheckWPExisted(SD_WP_FAT_BIN_NAME);
        if (eError != SD_UPDATER_ERR_FILE) {
            if (AHC_FS_FileRemove(SD_WP_FAT_BIN_NAME,  STRLEN(SD_WP_FAT_BIN_NAME)) ) {
                printc(FG_YELLOW("Update SD:\\SD_WpFat.bin success!\r\n"));
            }
        }
    }

    {
        UINT32 i;
        MMP_BYTE Index[2];
        MMP_BYTE SDfilename[64] = {0};

        for (i = 0; i<gubWpFileNum; i++) {
            MEMSET0(SDfilename);
            STRCPY(SDfilename, SD_WP_BASENAME);
            sprintf(Index,"%d",i);
            STRCAT(SDfilename,Index);
            STRCAT(SDfilename, SD_WP_EXTNAME);

            if (SDUpdateCheckWpFsExisted(SDfilename) != SD_UPDATER_ERR_FILE) {
                MEMSET0(SDfilename);
                STRCPY(SDfilename, SD_WP_BASENAME);
                sprintf(Index,"%d",i);
                STRCAT(SDfilename,Index);
                STRCAT(SDfilename, SD_WP_EXTNAME);
                if (AHC_FS_FileRemove(SDfilename,  STRLEN(SDfilename))) {
                    printc(FG_YELLOW("Update %s success!\r\n"), SDfilename);
                }
            }
        }
    }

    #if(EDOG_ENABLE)
    eError = SDUpdateCheckDBExisted(SD_DB_UPDATER_BIN_NAME);
    if(eError != SD_UPDATER_ERR_FILE)
    {
        printc("Update SD:\\SpeedCam_Data.bin success!\r\n");
    }
    #endif

    if(eError != SD_UPDATER_ERR_FILE)
    {
        if (eError == SD_UPDATER_ERR_FAIL)
            AHC_OS_Sleep(3000);

        // Update Success
        uiPowerOffPicture();
        AHC_PMU_PowerOff();
    }
}
#endif


AHC_BOOL MenuStateVideoModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;

    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);
#if (TOP_MENU_PAGE_EN)
    SetCurrentMenu(&sTopMenu);
#else
    SetCurrentMenu(&sMainMenuVideo);
#endif
    ulResult = MenuStateExecutionCommon(ulEvent, 0);//ulResult = MenuStateVideoMode(ulEvent, 0);

#if 0
    ahcRet = AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet);}
#endif

    return ahcRet;
}

AHC_BOOL MenuStateVideoModeShutDown(void* pData)
{
#if (1)
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_MENU_EXIT, 0);
#endif

    return AHC_TRUE;
}

DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_ENTER_NET_PLAYBACK)
{
    StateSwitchMode(UI_NET_PLAYBACK_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_USB_REMOVED_LCD)
{
   /* In Video state, the event should always be USB adapter out,
     * the real USB plug-out event should be received in MSDC state.
     *
     * The function AHC_USB_GetLastStatus() may return wrong status,
     * when USB plug-in/out then adapter plug-in.
     *
     */
    if (AHC_IsDcCableConnect() == AHC_TRUE)
        return;//break;

    //AHC_SetMode(AHC_MODE_IDLE);
    //bForce_PowerOff = AHC_TRUE;
    //AHC_PowerOff_NormalPath();

    #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
    AHC_SetShutdownByChargerOut(AHC_TRUE);
    #endif
}

DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_USB_DETECT_LCD)
{
    if(IsAdapter_Connect())
    {
        if (VideoFunc_GetRecordStatus()) {
            // Video Recording to ignore USB Charger
            return;//break;
        }
        else {
            //Power Off
        }
    }
    else
    {
        if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
            StateSwitchMode(UI_USBSELECT_MENU_STATE);
        }
        else
        {
            StateSwitchMode(UI_VIDEO_STATE);
        }
    }
}

DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_USB_B_DEVICE_DETECT)
{
    /////////////////////////////////////////////////////// Description ////////////////////////////////////////////////////
    // EVENT_USB_B_DEVICE_DETECT: Got when Rear Cam streaming was detected
    // EVENT_USB_B_DEVICE_REMOVED: Got when Rear Cam streaming was disconnected
    // Note: When some UVC error happened (ex: AHC_HostUVCVideoSetEp0TimeoutCB() / AHC_HostUVCVideoSetFrmRxTimeout2CB() was called),
    //       EVENT_USB_B_DEVICE_REMOVED will be sent. Below sample code will stop current recording and start next recording with only Front Cam.
    //       Once AHC_USBDetectHandler() detected Rear Cam streaming was recovered, EVENT_USB_B_DEVICE_DETECT will be sent.
    //       Below sample code will stop current recording and start next recording with Front & Rear Cam.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AHC_USB_PauseDetection(0);
    if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
        (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else{
        AHC_DBG_MSG(1, "KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted \r\n");
    }
}

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_TV_DETECT)
{
    StateSwitchMode(UI_CLOCK_SETTING_STATE);
    //StateSwitchMode(UI_VIDEO_STATE);
}
#endif

#if (HDMI_ENABLE)
DECL_AHC_EV_HANDLER(STATE_CLOCK_SETTING_MODE_EVENT_HDMI_DETECT)
{
    StateSwitchMode(UI_VIDEO_STATE);
}
#endif

UINT32 MenuStateClockSettingsModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    UINT32 ulResult = 0;
    //MenuStateClockSettingsMode(ulEvent, ulParam);

    ulResult = MenuStateHandlerCommon(ulMsgId, ulEvent, ulParam);
    if(MENU_ERR_EXIT == ulResult){
        UI_STATE_ID sParentState;
        StateModeGetParent(uiGetWorkingState(), &sParentState);
        StateSwitchMode(UI_VIDEO_STATE);
        //Pass event to Video UI state, no parent
        if(sParentState == UI_STATE_UNSUPPORTED){
            if(ulEvent == BUTTON_MENU_REL)
                ulEvent = EVENT_MENU_EXIT;
            StateVideoRecModeHandler(ulMsgId, ulEvent, ulParam);
        }
    }
    else{
        ulEvent = KeyParser_ClockSettingEvent(ulMsgId, ulEvent, ulParam);
        StateModeDoHandlerEvent(ulMsgId, ulEvent, ulParam);
    }
    return 0;
}

#if 0
AHC_BOOL MenuStateClockSettingsModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    //SwitchUIDrawSet(UI_VIDEO_STATE);
    SwitchUIDrawSetVideoRecordMode();

    StateLCDCheckStatus(UI_CLOCK_SETTING_STATE);
    MenuStateClockSettingsMode(BUTTON_VIRTUAL_RESET, 0);
    return ahcRet;
}
#endif

AHC_BOOL MenuStateClockSettingsModeInitCommon(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;

    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);
    SetCurrentMenu(&sSubClockSettings);

    ulResult = MenuStateExecutionCommon(ulEvent, 0);

    return ahcRet;
}

AHC_BOOL MenuStateClockSettingsModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevLCD();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    ahcRet = MenuStateClockSettingsModeInitCommon();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}

#if (TVOUT_ENABLE)
AHC_BOOL MenuStateClockSettingsModeInitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevTVout();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    ahcRet = MenuStateClockSettingsModeInitCommon();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}
#endif

#if (HDMI_ENABLE)
AHC_BOOL MenuStateClockSettingsModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    ahcRet = MenuStateClockSettingsModeInitCommon();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}
#endif

AHC_BOOL MenuStateClockSettingsModeShutDown(void* pData)
{
    AHC_SetMode(AHC_MODE_IDLE);

    return AHC_TRUE;
}

AHC_BOOL MenuStateEditConfirmModeShutDown(void* pData)
{
    return AHC_TRUE;
}

#if (SD_UPDATE_FW_EN)
UINT32 MenuStateSDUpdateModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    AHC_SDUpdateMode();
    return 0;
}

AHC_BOOL MenuStateSDUpdateModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    /* At this monunt, The StateLCDCheckStatus will set LCD Direction,
    * and it will cause system crash when booting from TV
    */
    if ((AHC_FALSE == AHC_IsTVConnectEx()) && (AHC_FALSE == AHC_IsHdmiConnect()))
        StateLCDCheckStatus(UI_SD_UPDATE_STATE);

    MenuStateSDUpdateMode(BUTTON_VIRTUAL_RESET, 0);

    return ahcRet;
}

AHC_BOOL MenuStateSDUpdateModeShutDown(void* pData)
{
    return AHC_TRUE;
}

AHC_BOOL StateSelectFuncClockSettingMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,           STATE_CLOCK_SETTING_MODE_EVENT_ENTER_NET_PLAYBACK);
#endif

    RegisterEventCb(EVENT_USB_DETECT,                   STATE_CLOCK_SETTING_MODE_EVENT_USB_DETECT_LCD);
    RegisterEventCb(EVENT_USB_REMOVED,                  STATE_CLOCK_SETTING_MODE_EVENT_USB_REMOVED_LCD);

#if (UVC_HOST_VIDEO_ENABLE)
    RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,          STATE_CLOCK_SETTING_MODE_EVENT_USB_B_DEVICE_DETECT);
    RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,         STATE_CLOCK_SETTING_MODE_EVENT_USB_B_DEVICE_DETECT);
#endif

#if (TVOUT_ENABLE)
    RegisterEventCb(EVENT_TV_DETECT,                    STATE_CLOCK_SETTING_MODE_EVENT_TV_DETECT);
    RegisterEventCb(EVENT_TV_REMOVED,                   STATE_CLOCK_SETTING_MODE_EVENT_TV_DETECT);
#endif
#if (HDMI_ENABLE)
    RegisterEventCb(EVENT_HDMI_DETECT,                  STATE_CLOCK_SETTING_MODE_EVENT_HDMI_DETECT);
    RegisterEventCb(EVENT_HDMI_REMOVED,                 STATE_CLOCK_SETTING_MODE_EVENT_HDMI_DETECT);
#endif

#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){
        ahcRet = StateModeSetOperation(UI_CLOCK_SETTING_STATE, MenuStateClockSettingsModeInitHDMI, MenuStateClockSettingsModeShutDown, MenuStateClockSettingsModeHandler);
    }else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){
        ahcRet = StateModeSetOperation(UI_CLOCK_SETTING_STATE, MenuStateClockSettingsModeInitTV, MenuStateClockSettingsModeShutDown, MenuStateClockSettingsModeHandler);
    }else
#endif
    {
        ahcRet = StateModeSetOperation(UI_CLOCK_SETTING_STATE, MenuStateClockSettingsModeInitLCD, MenuStateClockSettingsModeShutDown, MenuStateClockSettingsModeHandler);
    }

    return ahcRet;
}
#endif


