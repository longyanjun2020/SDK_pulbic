/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_utility.h"
#include "ahc_browser.h"
#include "ahc_display.h"
#include "ahc_general.h"
#include "ahc_gui.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_parameter.h"
#include "ahc_warningmsg.h"
#include "ahc_common.h"
#include "ahc_general_cardv.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "statecamerafunc.h"
#include "statebrowserfunc.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawingCameraFunc.h"
#include "MenuStateCameraMenu.h"
#include "MenuSetting.h"
#include "MenuStateMenu.h"

/*===========================================================================
 * Local function
 *===========================================================================*/

UINT32   SubMenuEventHandler_FlashLevel(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   MenuGetDefault_Camera(PSMENUSTRUCT pMenu);

AHC_BOOL MenuItemStillImageSize(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemStillQuality(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemStillStable(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFlash(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFlashLevel(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemRedEyeReduc(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSelfTimer(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemBurstCapture(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemVMDShotNum(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemTimeLapseInterval(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern SMENUITEM 	sItemScence;
extern SMENUITEM 	sItemEV;
extern SMENUITEM 	sItemWB;
extern SMENUITEM 	sItemISO;
extern SMENUITEM 	sItemColor;
extern SMENUITEM 	sItemEffect;
extern SMENUITEM 	sItemContrast;
extern SMENUITEM 	sItemSaturation;
extern SMENUITEM 	sItemSharpness;
extern SMENUITEM 	sItemGamma;

extern AHC_BOOL 	Deleting_InBrowser;
extern AHC_BOOL 	Protecting_InBrowser;
//extern AHC_BOOL 	bForceSwitchBrowser;
extern AHC_BOOL		bForceSwitchVideoMode;
extern AHC_BOOL 	m_ubAtMenuTab;

/*===========================================================================
 * Global variable : Menu
 *===========================================================================*/

SMENUSTRUCT	sMainMenuStill;

SMENUSTRUCT sSubStillImageSize;
SMENUSTRUCT sSubStillQuality;
SMENUSTRUCT sSubStillStable;
SMENUSTRUCT sSubFlash;
SMENUSTRUCT sSubFlashLevel;
SMENUSTRUCT sSubRedEyeReduc;
SMENUSTRUCT sSubSelfTimer;
SMENUSTRUCT sSubBurstCapture;
SMENUSTRUCT sSubVMDShotNum;
SMENUSTRUCT sSubTimeLapseInterval;

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/

// Still Image Size
#if (MENU_STILL_SIZE_EN)
SMENUITEM sItemStillImageSize          = { ITEMID_STILL_IMAGE_SIZE, &BMICON_MENU_IMG_SIZE, 	IDS_DS_STILL_IMAGE_SIZE,	&sSubStillImageSize, 0,   0, AHC_TRUE, NULL };
#if (MENU_STILL_SIZE_30M_EN)
SMENUITEM sItemStillImageSize_30M      = { ITEMID_IMAGE_SIZE_30M,  &BMICON_IMAGE_RES_30M, 	IDS_DS_IMAGE_SIZE_30M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_14M_EN)
SMENUITEM sItemStillImageSize_14M      = { ITEMID_IMAGE_SIZE_14M,  &BMICON_IMAGE_RES_14M, 	IDS_DS_IMAGE_SIZE_14M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_12M_EN)
SMENUITEM sItemStillImageSize_12M      = { ITEMID_IMAGE_SIZE_12M,  &BMICON_IMAGE_RES_12M, 	IDS_DS_IMAGE_SIZE_12M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_8M_EN)
SMENUITEM sItemStillImageSize_8M       = { ITEMID_IMAGE_SIZE_8M,   &BMICON_IMAGE_RES_8M,  	IDS_DS_IMAGE_SIZE_8M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_5M_EN)
SMENUITEM sItemStillImageSize_5M       = { ITEMID_IMAGE_SIZE_5M,   &BMICON_IMAGE_RES_5M,  	IDS_DS_IMAGE_SIZE_5M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_3M_EN)
SMENUITEM sItemStillImageSize_3M       = { ITEMID_IMAGE_SIZE_3M,   &BMICON_IMAGE_RES_3M,  	IDS_DS_IMAGE_SIZE_3M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_2M_WIDE_EN)
SMENUITEM sItemStillImageSize_2M_Wide  = { ITEMID_IMAGE_SIZE_2M,   &BMICON_IMAGE_RES_2M,   	IDS_DS_IMAGE_SIZE_2M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_1d2M_EN)
SMENUITEM sItemStillImageSize_1_2M     = { ITEMID_IMAGE_SIZE_1_2M, &BMICON_IMAGE_RES_1_2M, 	IDS_DS_IMAGE_SIZE_1_2M,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SIZE_VGA_EN)
SMENUITEM sItemStillImageSize_VGA      = { ITEMID_IMAGE_SIZE_VGA,  &BMICON_IMAGE_RES_VGA, 	IDS_DS_IMAGE_SIZE_VGA,	NULL, MenuItemStillImageSize, 0, AHC_TRUE, NULL };
#endif
#endif

// Still Quality
#if (MENU_STILL_QUALITY_EN)
SMENUITEM sItemStillQuality            = { ITEMID_STILL_QUALITY, 	  &BMICON_MENU_IMG_QUALITY, IDS_DS_STILL_QUALITY,	&sSubStillQuality, 0, 		0, AHC_TRUE, NULL };
#if (MENU_STILL_QUALITY_SUPER_FINE_EN)
SMENUITEM sItemStillQuality_Super_Fine = { ITEMID_SQUALITY_SUPERFINE, &BMICON_QUALITY_SHQ, IDS_DS_QUALITY_SUPERFINE,	NULL, MenuItemStillQuality, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_QUALITY_FINE_EN)
SMENUITEM sItemStillQuality_Fine       = { ITEMID_SQUALITY_FINE, 	  &BMICON_QUALITY_HQ,  IDS_DS_QUALITY_FINE, 		NULL, MenuItemStillQuality, 0, AHC_TRUE, NULL };
#endif
#endif

// Still Stabilization
#if (MENU_STILL_STABILIZE_EN)
SMENUITEM sItemStillStabilization      = { ITEMID_STILL_STABLEILIZATION, NULL, 				 IDS_DS_STILL_STABLEILIZATION,	&sSubStillStable, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_STABILIZE_ON_EN)
SMENUITEM sItemStillStabilization_On   = { ITEMID_STILL_STABLE_ON,  &bmIcon_ImageStable_ON,  IDS_DS_ON,	 NULL, MenuItemStillStable, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_STABILIZE_OFF_EN)
SMENUITEM sItemStillStabilization_Off  = { ITEMID_STILL_STABLE_OFF, &bmIcon_ImageStable_OFF, IDS_DS_OFF, NULL, MenuItemStillStable, 0, AHC_TRUE, NULL };
#endif
#endif

// Flash
#if (MENU_STILL_FLASH_EN)
SMENUITEM sItemFlash          		   = { ITEMID_FLASH, 			NULL, 					 IDS_DS_FLASH,	&sSubFlash, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_FLASH_AUTO_EN)
SMENUITEM sItemFlash_Auto      		   = { ITEMID_FLASH_AUTO,  		&bmIcon_Flash_Auto, 	 IDS_DS_AUTO,			NULL, MenuItemFlash, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_FLASH_SLOW_SYNC_EN)
SMENUITEM sItemFlash_Slow_Sync     	   = { ITEMID_FLASH_SLOW_SYNC,  &bmIcon_Flash_Slow_Sync, IDS_DS_FLASH_SLOW_SYNC,NULL, MenuItemFlash, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_FLASH_ON_EN)
SMENUITEM sItemFlash_On  			   = { ITEMID_FLASH_ON,  		&bmIcon_Flash_ON, 		 IDS_DS_ON,				NULL, MenuItemFlash, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_FLASH_OFF_EN)
SMENUITEM sItemFlash_Off  			   = { ITEMID_FLASH_OFF, 		&bmIcon_Flash_OFF, 		 IDS_DS_OFF,			NULL, MenuItemFlash, 0, AHC_TRUE, NULL };
#endif
#endif

// Flash Level
#if (MENU_STILL_FLASH_LEVEL_EN)
SMENUITEM sItemFlashLevel         	   = { ITEMID_FLASH_LEVEL, 		  NULL, IDS_DS_FLASH_LEVEL,	&sSubFlashLevel, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_FLASH_LEVEL_HIGH_EN)
SMENUITEM sItemFlashLevel_High         = { ITEMID_FLASH_LEVEL_HIGH,   NULL, IDS_DS_HIGH,   NULL, MenuItemFlashLevel, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_FLASH_LEVEL_NORMAL_EN)
SMENUITEM sItemFlashLevel_Normal       = { ITEMID_FLASH_LEVEL_NORMAL, NULL, IDS_DS_NORMAL, NULL, MenuItemFlashLevel, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_FLASH_LEVEL_LOW_EN)
SMENUITEM sItemFlashLevel_Low          = { ITEMID_FLASH_LEVEL_LOW,    NULL, IDS_DS_LOW,    NULL, MenuItemFlashLevel, 0, AHC_TRUE, NULL };
#endif
#endif

// Red Eye Reduction
#if (MENU_STILL_REDEYE_REDUCE_EN)
SMENUITEM sItemRedEyeReduction         = { ITEMID_REDEYE_REDUCTION, NULL, IDS_DS_REDEYE_REDUCTION,	&sSubRedEyeReduc, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_REDEYE_REDUCE_ON_EN)
SMENUITEM sItemRedEyeReduction_On      = { ITEMID_REDEYE_REDUC_ON,  NULL, IDS_DS_ON, NULL, MenuItemRedEyeReduc, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_REDEYE_REDUCE_OFF_EN)
SMENUITEM sItemRedEyeReduction_Off     = { ITEMID_REDEYE_REDUC_OFF, NULL, IDS_DS_OFF,NULL, MenuItemRedEyeReduc, 0, AHC_TRUE, NULL };
#endif
#endif

// Self Timer
#if (MENU_STILL_SELF_TIMER_EN)
SMENUITEM sItemSelfTimer         	   = { ITEMID_SELFTIMER, 	 NULL, 					IDS_DS_SELFTIMER,	&sSubSelfTimer, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_SELF_TIMER_OFF_EN)
SMENUITEM sItemSelfTimer_Off           = { ITEMID_SELFTIMER_OFF, &BMICON_SELFTIMER_OFF, IDS_DS_OFF,			NULL, MenuItemSelfTimer, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SELF_TIMER_2S_EN)
SMENUITEM sItemSelfTimer_2Seconds      = { ITEMID_SELFTIMER_2S,  &BMICON_SELFTIMER_2S, 	IDS_TIME_2SEC, 		NULL, MenuItemSelfTimer, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_SELF_TIMER_10S_EN)
SMENUITEM sItemSelfTimer_10Seconds     = { ITEMID_SELFTIMER_10S, &BMICON_SELFTIMER_10S, IDS_TIME_10SEC,		NULL, MenuItemSelfTimer, 0, AHC_TRUE, NULL };
#endif
#endif

// Burst Capture
#if (MENU_STILL_BURST_SHOT_EN)
SMENUITEM sItemBurstCapture           = { ITEMID_BURST_CAPTURE,  NULL, 					IDS_DS_BURST_CAPTURE, &sSubBurstCapture, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_BURST_SHOT_OFF_EN)
SMENUITEM sItemBurstCapture_Off       = { ITEMID_BURST_OFF, 	 NULL, 					IDS_DS_OFF,				NULL, MenuItemBurstCapture, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_BURST_SHOT_LO_EN)
SMENUITEM sItemBurstCapture_Lo        = { ITEMID_BURST_SHOT_LO,  &bmIcon_Burst_Low, 	IDS_DS_BURST_SHOT_LO, 	NULL, MenuItemBurstCapture, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_BURST_SHOT_MID_EN)
SMENUITEM sItemBurstCapture_Mid       = { ITEMID_BURST_SHOT_MID, &bmIcon_Burst_Middle, 	IDS_DS_BURST_SHOT_MID,	NULL, MenuItemBurstCapture, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_BURST_SHOT_HI_EN)
SMENUITEM sItemBurstCapture_Hi        = { ITEMID_BURST_SHOT_HI,  &bmIcon_Burst_High, 	IDS_DS_BURST_SHOT_HI,	NULL, MenuItemBurstCapture, 0, AHC_TRUE, NULL };
#endif
#endif

// Motion Shot Num
#if (MENU_STILL_VMD_SHOT_NUM_EN)
SMENUITEM sItemVMDShotNum           = { ITEMID_VMD_SHOT_NUM,     NULL, 	IDS_VMD_SHOT_NUM, 		&sSubVMDShotNum, 0, 0, AHC_TRUE, NULL };
#if (MENU_STILL_VMD_SHOT_NUM_1P_EN)
SMENUITEM sItemVMDShotNum_1P        = { ITEMID_VMD_SHOT_NUM_1P,  NULL, 	IDS_DS_P,				NULL, MenuItemVMDShotNum, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_VMD_SHOT_NUM_2P_EN)
SMENUITEM sItemVMDShotNum_2P        = { ITEMID_VMD_SHOT_NUM_2P,  NULL, 	IDS_DS_P, 				NULL, MenuItemVMDShotNum, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_VMD_SHOT_NUM_3P_EN)
SMENUITEM sItemVMDShotNum_3P        = { ITEMID_VMD_SHOT_NUM_3P,  NULL, 	IDS_DS_P,				NULL, MenuItemVMDShotNum, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_VMD_SHOT_NUM_5P_EN)
SMENUITEM sItemVMDShotNum_5P        = { ITEMID_VMD_SHOT_NUM_5P,  NULL, 	IDS_DS_P,				NULL, MenuItemVMDShotNum, 0, AHC_TRUE, NULL };
#endif
#endif

// Time Lapse Interval
#if (MENU_STILL_TIMELAPSE_TIME_EN)
SMENUITEM sItemTimeLapseTime       = { ITEMID_TIME_LAPSE,        &BMICON_MENU_TIMELAPSE, 	IDS_DS_TIMELAPSE, 		&sSubTimeLapseInterval, 0,       0, AHC_TRUE, NULL };
#if (MENU_STILL_TIMELAPSE_TIME1_EN)
SMENUITEM sItemTimeLapse_Time1     = { ITEMID_TIME_LAPSE_TIME1,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME2_EN)
SMENUITEM sItemTimeLapse_Time2     = { ITEMID_TIME_LAPSE_TIME2,  NULL, 	IDS_DS_SEC, 			NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME3_EN)
SMENUITEM sItemTimeLapse_Time3     = { ITEMID_TIME_LAPSE_TIME3,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME4_EN)
SMENUITEM sItemTimeLapse_Time4     = { ITEMID_TIME_LAPSE_TIME4,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME5_EN)
SMENUITEM sItemTimeLapse_Time5     = { ITEMID_TIME_LAPSE_TIME5,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME6_EN)
SMENUITEM sItemTimeLapse_Time6     = { ITEMID_TIME_LAPSE_TIME6,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#if (MENU_STILL_TIMELAPSE_TIME7_EN)
SMENUITEM sItemTimeLapse_Time7     = { ITEMID_TIME_LAPSE_TIME7,  NULL, 	IDS_DS_SEC,				NULL, MenuItemTimeLapseInterval, 0, AHC_TRUE, NULL };
#endif
#endif

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

#if (MENU_STILL_SIZE_EN)
PSMENUITEM   sMenuListStillImageSize[] =
{
#if (MENU_STILL_SIZE_30M_EN)
    &sItemStillImageSize_30M,
#endif
#if (MENU_STILL_SIZE_14M_EN)
    &sItemStillImageSize_14M,
#endif
#if (MENU_STILL_SIZE_12M_EN)
    &sItemStillImageSize_12M,
#endif
#if (MENU_STILL_SIZE_8M_EN)
    &sItemStillImageSize_8M,
#endif
#if (MENU_STILL_SIZE_5M_EN)
    &sItemStillImageSize_5M,
#endif
#if (MENU_STILL_SIZE_3M_EN)
    &sItemStillImageSize_3M,
#endif
#if (MENU_STILL_SIZE_2M_WIDE_EN)
    &sItemStillImageSize_2M_Wide,
#endif
#if (MENU_STILL_SIZE_1d2M_EN)
    &sItemStillImageSize_1_2M,
#endif
#if (MENU_STILL_SIZE_VGA_EN)
    &sItemStillImageSize_VGA
#endif
};
#endif

#if (MENU_STILL_QUALITY_EN)
PSMENUITEM   sMenuListStillQuality[] =
{
#if (MENU_STILL_QUALITY_SUPER_FINE_EN)
    &sItemStillQuality_Super_Fine,
#endif
#if (MENU_STILL_QUALITY_FINE_EN)
    &sItemStillQuality_Fine
#endif
};
#endif

#if (MENU_STILL_STABILIZE_EN)
PSMENUITEM   sMenuListStillStable[] =
{
#if (MENU_STILL_STABILIZE_ON_EN)
    &sItemStillStabilization_On,
#endif
#if (MENU_STILL_STABILIZE_OFF_EN)
    &sItemStillStabilization_Off
#endif
};
#endif

#if (MENU_STILL_FLASH_EN)
PSMENUITEM   sMenuListFlash[] =
{
#if (MENU_STILL_FLASH_AUTO_EN)
    &sItemFlash_Auto,
#endif
#if (MENU_STILL_FLASH_SLOW_SYNC_EN)
    &sItemFlash_Slow_Sync,
#endif
#if (MENU_STILL_FLASH_ON_EN)
    &sItemFlash_On,
#endif
#if (MENU_STILL_FLASH_OFF_EN)
    &sItemFlash_Off
#endif
};
#endif

#if (MENU_STILL_FLASH_LEVEL_EN)
PSMENUITEM   sMenuListFlashLevel[] =
{
#if (MENU_STILL_FLASH_LEVEL_HIGH_EN)
    &sItemFlashLevel_High,
#endif
#if (MENU_STILL_FLASH_LEVEL_NORMAL_EN)
    &sItemFlashLevel_Normal,
#endif
#if (MENU_STILL_FLASH_LEVEL_LOW_EN)
    &sItemFlashLevel_Low
#endif
};
#endif

#if (MENU_STILL_REDEYE_REDUCE_EN)
PSMENUITEM   sMenuListRedEyeReduc[] =
{
#if (MENU_STILL_REDEYE_REDUCE_ON_EN)
    &sItemRedEyeReduction_On,
#endif
#if (MENU_STILL_REDEYE_REDUCE_OFF_EN)
    &sItemRedEyeReduction_Off
#endif
};
#endif

#if (MENU_STILL_SELF_TIMER_EN)
PSMENUITEM   sMenuListSelfTimer[] =
{
#if (MENU_STILL_SELF_TIMER_OFF_EN)
    &sItemSelfTimer_Off,
#endif
#if (MENU_STILL_SELF_TIMER_2S_EN)
    &sItemSelfTimer_2Seconds,
#endif
#if (MENU_STILL_SELF_TIMER_10S_EN)
    &sItemSelfTimer_10Seconds
#endif
};
#endif

#if (MENU_STILL_BURST_SHOT_EN)
PSMENUITEM   sMenuListBurstCapture[] =
{
#if (MENU_STILL_BURST_SHOT_OFF_EN)
    &sItemBurstCapture_Off,
#endif
#if (MENU_STILL_BURST_SHOT_LO_EN)
    &sItemBurstCapture_Lo,
#endif
#if (MENU_STILL_BURST_SHOT_MID_EN)
    &sItemBurstCapture_Mid,
#endif
#if (MENU_STILL_BURST_SHOT_HI_EN)
    &sItemBurstCapture_Hi
#endif
};
#endif

#if (MENU_STILL_VMD_SHOT_NUM_EN)
PSMENUITEM   sMenuListVMDShotNum[] =
{
#if (MENU_STILL_VMD_SHOT_NUM_1P_EN)
    &sItemVMDShotNum_1P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_2P_EN)
    &sItemVMDShotNum_2P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_3P_EN)
    &sItemVMDShotNum_3P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_5P_EN)
    &sItemVMDShotNum_5P
#endif
};
#endif

#if (MENU_STILL_TIMELAPSE_TIME_EN)
PSMENUITEM   sMenuListTimeLapseInterval[] =
{
#if (MENU_STILL_TIMELAPSE_TIME1_EN)
    &sItemTimeLapse_Time1,
#endif
#if (MENU_STILL_TIMELAPSE_TIME2_EN)
    &sItemTimeLapse_Time2,
#endif
#if (MENU_STILL_TIMELAPSE_TIME3_EN)
    &sItemTimeLapse_Time3,
#endif
#if (MENU_STILL_TIMELAPSE_TIME4_EN)
    &sItemTimeLapse_Time4,
#endif
#if (MENU_STILL_TIMELAPSE_TIME5_EN)
    &sItemTimeLapse_Time5,
#endif
#if (MENU_STILL_TIMELAPSE_TIME6_EN)
    &sItemTimeLapse_Time6,
#endif
#if (MENU_STILL_TIMELAPSE_TIME7_EN)
    &sItemTimeLapse_Time7,
#endif
};
#endif

PSMENUITEM   sMenuListMainStill[] =
{
#if (MENU_STILL_SIZE_EN)
    &sItemStillImageSize,
#endif
#if (MENU_STILL_QUALITY_EN)
    &sItemStillQuality,
#endif
#if (MENU_STILL_SELF_TIMER_EN)
	&sItemSelfTimer,
#endif
#if (MENU_STILL_BURST_SHOT_EN)
	&sItemBurstCapture,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_EN)
	&sItemVMDShotNum,
#endif
#if (MENU_STILL_TIMELAPSE_TIME_EN)
	&sItemTimeLapseTime,
#endif
#if (MENU_STILL_SCENE_EN)
	&sItemScence,
#endif
#if (MENU_STILL_EV_EN)
	&sItemEV,
#endif
#if (MENU_STILL_WB_EN)
	&sItemWB,
#endif
#if (MENU_STILL_ISO_EN)
	&sItemISO,
#endif
#if (MENU_STILL_COLOR_EN)
	&sItemColor,
#endif
#if (MENU_STILL_EFFECT_EN)
	&sItemEffect,
#endif
#if (MENU_STILL_CONTRAST_EN)
	&sItemContrast,
#endif
#if (MENU_STILL_SATURATION_EN)
	&sItemSaturation,
#endif
#if (MENU_STILL_SHARPNESS_EN)
	&sItemSharpness,
#endif
#if (MENU_STILL_GAMMA_EN)
	&sItemGamma,
#endif
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuStill =
{
    MENUID_MAIN_MENU_STILL,
    NULL,
    IDS_DS_STILL_CAPTURE,
    NULL,
    sizeof(sMenuListMainStill)/sizeof(PSMENUITEM),
    sMenuListMainStill,
    MainMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};

//--------------SUB MENU-------------------

#if (MENU_STILL_SIZE_EN)
SMENUSTRUCT sSubStillImageSize =
{
    MENUID_SUB_MENU_STILL_IMAGE_SIZE,
    NULL,
    IDS_DS_STILL_IMAGE_SIZE,
    NULL,
    sizeof(sMenuListStillImageSize)/sizeof(PSMENUITEM),
    sMenuListStillImageSize,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_IMAGE_SIZE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_QUALITY_EN)
SMENUSTRUCT sSubStillQuality =
{
    MENUID_SUB_MENU_STILL_QUALITY,
    NULL,
    IDS_DS_STILL_QUALITY,
    NULL,
    sizeof(sMenuListStillQuality)/sizeof(PSMENUITEM),
    sMenuListStillQuality,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_STILL_QUALITY_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_STABILIZE_EN)
SMENUSTRUCT sSubStillStable =
{
    MENUID_SUB_MENU_STILL_STABLEILIZATION,
    NULL,
    IDS_DS_STILL_STABLEILIZATION,
    NULL,
    sizeof(sMenuListStillStable)/sizeof(PSMENUITEM),
    sMenuListStillStable,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_STILL_STABLE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_FLASH_EN)
SMENUSTRUCT sSubFlash =
{
    MENUID_SUB_MENU_FLASH,
    NULL,
    IDS_DS_FLASH,
    NULL,
    sizeof(sMenuListFlash)/sizeof(PSMENUITEM),
    sMenuListFlash,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_FLASH_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_FLASH_LEVEL_EN)
SMENUSTRUCT sSubFlashLevel =
{
    MENUID_SUB_MENU_FLASH_LEVEL,
    NULL,
    IDS_DS_FLASH_LEVEL,
    NULL,
    sizeof(sMenuListFlashLevel)/sizeof(PSMENUITEM),
    sMenuListFlashLevel,
    SubMenuEventHandler_FlashLevel,
    MenuGetDefault_Camera,
    0,
    IDS_DS_FLASH_LEVEL_DESCRIPTION,
    AHC_TRUE,
    0
};
#endif

#if (MENU_STILL_REDEYE_REDUCE_EN)
SMENUSTRUCT sSubRedEyeReduc =
{
    MENUID_SUB_MENU_REDEYE_REDUCTION,
    NULL,
    IDS_DS_REDEYE_REDUCTION,
    NULL,
    sizeof(sMenuListRedEyeReduc)/sizeof(PSMENUITEM),
    sMenuListRedEyeReduc,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_REDEYE_REDUCTION_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_SELF_TIMER_EN)
SMENUSTRUCT sSubSelfTimer =
{
    MENUID_SUB_MENU_SELFTIMER,
    NULL,
    IDS_DS_SELFTIMER,
    NULL,
    sizeof(sMenuListSelfTimer)/sizeof(PSMENUITEM),
    sMenuListSelfTimer,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_SELFTIMER_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_BURST_SHOT_EN)
SMENUSTRUCT sSubBurstCapture =
{
    MENUID_SUB_MENU_BURST_CAPTURE,
    NULL,
    IDS_DS_BURST_CAPTURE,
    NULL,
    sizeof(sMenuListBurstCapture)/sizeof(PSMENUITEM),
    sMenuListBurstCapture,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_BURST_CAPTURE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_VMD_SHOT_NUM_EN)
SMENUSTRUCT sSubVMDShotNum =
{
    MENUID_SUB_MENU_VMD_SHOT_NUM,
    NULL,
    IDS_VMD_SHOT_NUM,
    NULL,
    sizeof(sMenuListVMDShotNum)/sizeof(PSMENUITEM),
    sMenuListVMDShotNum,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_VMD_SHOT_NUM,
    AHC_FALSE,
    0
};
#endif

#if (MENU_STILL_TIMELAPSE_TIME_EN)
SMENUSTRUCT sSubTimeLapseInterval =
{
    MENUID_SUB_MENU_TIMELAPSE_TIME,
    NULL,
    IDS_DS_TIMELAPSE,
    NULL,
    sizeof(sMenuListTimeLapseInterval)/sizeof(PSMENUITEM),
    sMenuListTimeLapseInterval,
    SubMenuEventHandler,
    MenuGetDefault_Camera,
    0,
    IDS_DS_TIMELAPSE,
    AHC_FALSE,
    0
};
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

UINT16 m_ulVMDShotNum[] 	= //Unit:Shots
{
#if (MENU_STILL_VMD_SHOT_NUM_1P_EN)
	1,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_2P_EN)
	2,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_3P_EN)
	3,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_5P_EN)
	5
#endif
};

UINT16 m_ulTimeLapseTime[] 	= //Unit:Second
{
#if (MENU_STILL_TIMELAPSE_TIME1_EN)
	0,
#endif
#if (MENU_STILL_TIMELAPSE_TIME2_EN)
	1,
#endif
#if (MENU_STILL_TIMELAPSE_TIME3_EN)
	2,
#endif
#if (MENU_STILL_TIMELAPSE_TIME4_EN)
	5,
#endif
#if (MENU_STILL_TIMELAPSE_TIME5_EN)
	10,
#endif
#if (MENU_STILL_TIMELAPSE_TIME6_EN)
	30,
#endif
#if (MENU_STILL_TIMELAPSE_TIME7_EN)
	60
#endif
};

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (MENU_STILL_SIZE_EN)
AHC_BOOL MenuItemStillImageSize(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiIMGSize = pItem->iItemId - ITEMID_STILL_IMAGE_SIZE -1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_QUALITY_EN)
AHC_BOOL MenuItemStillQuality(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiIMGQuality = pItem->iItemId - ITEMID_STILL_QUALITY-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_STABILIZE_EN)
AHC_BOOL MenuItemStillStable(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiIMGStabilize = pItem->iItemId - ITEMID_STILL_STABLEILIZATION-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_FLASH_EN)
AHC_BOOL MenuItemFlash(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiFlashMode = pItem->iItemId - ITEMID_FLASH-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_FLASH_LEVEL_EN)
AHC_BOOL MenuItemFlashLevel(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiFlashLevel = pItem->iItemId - ITEMID_FLASH_LEVEL-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_REDEYE_REDUCE_EN)
AHC_BOOL MenuItemRedEyeReduc(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiRedEyeReduce = pItem->iItemId - ITEMID_REDEYE_REDUCTION-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_SELF_TIMER_EN)
AHC_BOOL MenuItemSelfTimer(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSelfTimer = pItem->iItemId - ITEMID_SELFTIMER-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_BURST_SHOT_EN)
AHC_BOOL MenuItemBurstCapture(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiBurstShot = pItem->iItemId - ITEMID_BURST_CAPTURE-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_VMD_SHOT_NUM_EN)
AHC_BOOL MenuItemVMDShotNum(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiVMDShotNum = pItem->iItemId - ITEMID_VMD_SHOT_NUM-1;
    return AHC_TRUE;
}
#endif

#if (MENU_STILL_TIMELAPSE_TIME_EN)
AHC_BOOL MenuItemTimeLapseInterval(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiTimeLapseTime = pItem->iItemId - ITEMID_TIME_LAPSE-1;
    return AHC_TRUE;
}
#endif

UINT32 MenuGetDefault_Camera(PSMENUSTRUCT pMenu)
{
    UINT32       DefaultValue;

    switch( pMenu->iMenuId )
    {
#if (MENU_STILL_SIZE_EN)
        case MENUID_SUB_MENU_STILL_IMAGE_SIZE:
            DefaultValue = MenuSettingConfig()->uiIMGSize;
            break;
#endif
#if (MENU_STILL_QUALITY_EN)
        case MENUID_SUB_MENU_STILL_QUALITY:
            DefaultValue = MenuSettingConfig()->uiIMGQuality;
            break;
#endif
#if (MENU_STILL_STABILIZE_EN)
        case MENUID_SUB_MENU_STILL_STABLEILIZATION:
            DefaultValue = MenuSettingConfig()->uiIMGStabilize;
            break;
#endif
#if (MENU_STILL_FLASH_EN)
        case MENUID_SUB_MENU_FLASH:
            DefaultValue = MenuSettingConfig()->uiFlashMode;
            break;
#endif
#if (MENU_STILL_FLASH_LEVEL_EN)
        case MENUID_SUB_MENU_FLASH_LEVEL:
            DefaultValue = MenuSettingConfig()->uiFlashLevel;
            break;
#endif
#if (MENU_STILL_REDEYE_REDUCE_EN)
        case MENUID_SUB_MENU_REDEYE_REDUCTION:
            DefaultValue = MenuSettingConfig()->uiRedEyeReduce;
            break;
#endif
#if (MENU_STILL_SELF_TIMER_EN)
        case MENUID_SUB_MENU_SELFTIMER:
            DefaultValue = MenuSettingConfig()->uiSelfTimer;
            break;
#endif
#if (MENU_STILL_BURST_SHOT_EN)
        case MENUID_SUB_MENU_BURST_CAPTURE:
            DefaultValue = MenuSettingConfig()->uiBurstShot;
            break;
#endif
#if (MENU_STILL_VMD_SHOT_NUM_EN)
        case MENUID_SUB_MENU_VMD_SHOT_NUM:
            DefaultValue = MenuSettingConfig()->uiVMDShotNum;
            break;
#endif
#if (MENU_STILL_TIMELAPSE_TIME_EN)
        case MENUID_SUB_MENU_TIMELAPSE_TIME:
            DefaultValue = MenuSettingConfig()->uiTimeLapseTime;
            break;
#endif
    }

	return DefaultValue;
}

#if (MENU_STILL_FLASH_LEVEL_EN)
UINT32 SubMenuEventHandler_FlashLevel(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32 	iPrevPos;

	switch(ulEvent)
	{
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
        pMenu->iCurrentPos 	= pMenu->iSelected;
		pMenu->bSetOne   	= 0;

	    MenuDrawSubPage_FlashLevel( pMenu );
		break;

	case MENU_UP            :

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );

        MenuDrawChangeSubItem_FlashLevel( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;

	case MENU_DOWN          :

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuDrawChangeSubItem_FlashLevel( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;

	case MENU_OK            :
    {
        PSMENUITEM pCurrentItem;

		pMenu->bSetOne   = 1;
        pCurrentItem 	 = pMenu->pItemsList[pMenu->iCurrentPos];

        if( pCurrentItem ->pfItemSelect != NULL )
        {
            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
        }

        iPrevPos      	 = pMenu->iCurrentPos;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
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
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
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

AHC_BOOL MenuStateCameraModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;
    
    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);

#if (TOP_MENU_PAGE_EN)
    SetCurrentMenu(&sTopMenu);
#else
    SetCurrentMenu(&sMainMenuStill);
#endif

    ulResult = MenuStateExecutionCommon(ulEvent, 0);//ulResult = MenuStateVideoMode(ulEvent, 0);
    //MenuStateCameraMode(BUTTON_VIRTUAL_RESET, 0);
    return ahcRet;
}


AHC_BOOL MenuStateCameraModeShutDown(void* pData)
{
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_MENU_EXIT, 0);
    return AHC_TRUE;
}


