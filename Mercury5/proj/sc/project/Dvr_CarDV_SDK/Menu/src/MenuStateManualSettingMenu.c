/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_isp.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_capture.h"
#include "ahc_warningmsg.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "ahc_message.h"
#include "MenuCommon.h"
#include "MenuSetting.h"
#include "MenuTouchButton.h"
#include "MenuDrawingManualSettingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuStateMenu.h"
#include "MenuStateManualSettingMenu.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "snr_cfg.h"


/*===========================================================================
 * Local function
 *===========================================================================*/

UINT32   SubMenuEventHandler_EV(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   MenuGetDefault_ManualSetting(PSMENUSTRUCT pMenu);

AHC_BOOL MenuItemScenceSelect(PSMENUITEM pItem, AHC_BOOL bHover);
AHC_BOOL MenuItemFocusWindow(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFocusRange(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemExpoMetering(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemExpoAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemISO(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemWB(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemColor(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemColorTemp(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemEffect(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemContrastAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSaturationAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSharpnessAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemGammaAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global varible : Touch Menu
 *===========================================================================*/

/*===========================================================================
 * Global varible : Menu
 *===========================================================================*/

SMENUSTRUCT sMainMenuManual;

SMENUSTRUCT sSubScence;
SMENUSTRUCT sSubFocusWindow;
SMENUSTRUCT sSubFocusRange;
SMENUSTRUCT sSubExpoMetering;
SMENUSTRUCT sSubExpoAdjust;
SMENUSTRUCT sSubISO;
SMENUSTRUCT sSubWB;
SMENUSTRUCT sSubColor;
SMENUSTRUCT sSubColorTemp;
SMENUSTRUCT sSubEffect;
SMENUSTRUCT sSubSmileDetection;
SMENUSTRUCT sSubSmileSensitivity;
SMENUSTRUCT sSubContrastAdjust;
SMENUSTRUCT sSubSaturationAdjust;
SMENUSTRUCT sSubSharpnessAdjust;
SMENUSTRUCT sSubGammaAdjust;

/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/

// Scence
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
SMENUITEM sItemScence                   = { ITEMID_SCENE,           &BMICON_MENU_SCENE,     IDS_DS_SCENE_SELECTION, &sSubScence, 0,             0, AHC_TRUE, NULL };
#if (MENU_MANUAL_SCENE_AUTO_EN)
SMENUITEM sItemScence_Auto              = { ITEMID_SCENE_AUTO,      &BMICON_SCENE_AUTO,     IDS_DS_AUTO ,           NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_SPORT_EN)
SMENUITEM sItemScence_Sports            = { ITEMID_SCENE_SPORTS,    &BMICON_SCENE_SPORT,    IDS_DS_SCENE_SPORTS,    NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_PORTRAIT_EN)
SMENUITEM sItemScence_Portrait          = { ITEMID_SCENE_PORTRAIT,  &BMICON_SCENE_PORTRAIT, IDS_DS_SCENE_PORTRAIT,  NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
SMENUITEM sItemScence_Landscape         = { ITEMID_SCENE_LANDSCAPE, &BMICON_SCENE_LANDSCAPE,IDS_DS_SCENE_LANDSCAPE, NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
SMENUITEM sItemScence_TwilightPortrait  = { ITEMID_SCENE_TWILIGHT_PORTRAIT, &BMICON_SCENE_TWILIGHT_POR, IDS_DS_SCENE_TWILIGHTPORTRAIT,NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_EN)
SMENUITEM sItemScence_Twilight          = { ITEMID_SCENE_TWILIGHT,  &BMICON_SCENE_TWILIGHT, IDS_DS_SCENE_TWILIGHT,  NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_SNOW_EN)
SMENUITEM sItemScence_Snow              = { ITEMID_SCENE_SNOW,      &BMICON_SCENE_SNOW,     IDS_DS_SCENE_SNOW,      NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_BEACH_EN)
SMENUITEM sItemScence_Beach             = { ITEMID_SCENE_BEACH,     &BMICON_SCENE_BEACH,    IDS_DS_SCENE_BEACH,     NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_SCENE_FIREWORKS_EN)
SMENUITEM sItemScence_Fireworks         = { ITEMID_SCENE_FIREWORKS, &BMICON_SCENE_FIREWORK, IDS_DS_SCENE_FIREWORKS, NULL, MenuItemScenceSelect, 0, AHC_TRUE, NULL };
#endif
#endif

// Focus Window
#if (MENU_MANUAL_FOCUS_EN)
SMENUITEM sItemFocusWindow          = { ITEMID_FOCUSWINDOW, NULL, IDS_DS_FOCUS_WINDOW,  &sSubFocusWindow, 0, 0, AHC_TRUE, NULL };
#if (MENU_MANUAL_FOCUS_MULTI_EN)
SMENUITEM sItemFocusWindow_Multi    = { ITEMID_FOCUSWINDOW_MULTI,       &bmIcon_FocusWindow_Multi,      IDS_DS_MULTI ,      NULL, MenuItemFocusWindow, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_FOCUS_CENTERSPOT_EN)
SMENUITEM sItemFocusWindow_CSpot    = { ITEMID_FOCUSWINDOW_CENTER_SPOT, &bmIcon_FocusWindow_CentrSpot,  IDS_DS_CENTER_SPOT, NULL, MenuItemFocusWindow, 0, AHC_TRUE, NULL };
#endif
#endif

// Focus Range
#if (MENU_MANUAL_FOCUS_RANGE_EN)
SMENUITEM sItemFocusRange           = { ITEMID_FOCUSRANGE, NULL, IDS_DS_FOCUS_RANGE,    &sSubFocusRange, 0, 0, AHC_TRUE, NULL };
#if (MENU_MANUAL_FOCUS_RANGE_NORMAL_EN)
SMENUITEM sItemFocusRange_Normal    = { ITEMID_FOCUSRANGE_NORMAL, &bmIcon_Focus_Infinity, IDS_DS_NORMAL,            NULL, MenuItemFocusRange, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_FOCUS_RANGE_MACRO_EN)
SMENUITEM sItemFocusRange_Macro     = { ITEMID_FOCUSRANGE_MACRO,  &bmIcon_Focus_Marco,    IDS_DS_FOCUS_RANGE_MACRO, NULL, MenuItemFocusRange, 0, AHC_TRUE, NULL };
#endif
#endif

// Exposure Metering
#if (MENU_MANUAL_METERING_EN)
SMENUITEM sItemMetering             = { ITEMID_METERING, NULL, IDS_DS_METERING, &sSubExpoMetering, 0, 0, AHC_TRUE, NULL };
#if (MENU_MANUAL_METERING_MULTI_EN)
SMENUITEM sItemMetering_Multi       = { ITEMID_METERING_MULTI,           &bmIcon_Metering_Multi,        IDS_DS_MULTI,                   NULL, MenuItemExpoMetering, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_METERING_WEIGHTED_EN)
SMENUITEM sItemMetering_CWeighted   = { ITEMID_METERING_CENTER_WEIGHTED, &bmIcon_Metering_Weighted,     IDS_DS_METERING_CENTER_WEIGHTED,NULL, MenuItemExpoMetering, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_METERING_CENTER_SPOT_EN)
SMENUITEM sItemMetering_CenterSpot  = { ITEMID_METERING_CENTER_SPOT,     &bmIcon_Metering_CenterSpot,   IDS_DS_CENTER_SPOT,             NULL, MenuItemExpoMetering, 0, AHC_TRUE, NULL };
#endif
#endif

// Exposure Adjust
#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
SMENUITEM sItemEV                   = { ITEMID_EV,     &BMICON_MENU_EV, IDS_DS_EV,  &sSubExpoAdjust, 0,         0, AHC_TRUE, NULL };
#if (MENU_MANUAL_EV_P20_EN)
SMENUITEM sItemEV_P20               = { ITEMID_EV_P20, &BMICON_EV_P2_0, IDS_DS_EV_P20,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_P17_EN)
SMENUITEM sItemEV_P17               = { ITEMID_EV_P17, &BMICON_EV_P1_7, IDS_DS_EV_P17,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_P13_EN)
SMENUITEM sItemEV_P13               = { ITEMID_EV_P13, &BMICON_EV_P1_3, IDS_DS_EV_P13,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_P10_EN)
SMENUITEM sItemEV_P10               = { ITEMID_EV_P10, &BMICON_EV_P1_0, IDS_DS_EV_P10,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_P07_EN)
SMENUITEM sItemEV_P07               = { ITEMID_EV_P07, &BMICON_EV_P0_7, IDS_DS_EV_P07,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_P03_EN)
SMENUITEM sItemEV_P03               = { ITEMID_EV_P03, &BMICON_EV_P0_3, IDS_DS_EV_P03,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_00_EN)
SMENUITEM sItemEV_00                = { ITEMID_EV_00,  &BMICON_EV_0,    IDS_DS_EV_0,  NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N03_EN)
SMENUITEM sItemEV_N03               = { ITEMID_EV_N03, &BMICON_EV_N0_3, IDS_DS_EV_N03,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N07_EN)
SMENUITEM sItemEV_N07               = { ITEMID_EV_N07, &BMICON_EV_N0_7, IDS_DS_EV_N07,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N10_EN)
SMENUITEM sItemEV_N10               = { ITEMID_EV_N10, &BMICON_EV_N1_0, IDS_DS_EV_N10,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N13_EN)
SMENUITEM sItemEV_N13               = { ITEMID_EV_N13, &BMICON_EV_N1_3, IDS_DS_EV_N13,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N17_EN)
SMENUITEM sItemEV_N17               = { ITEMID_EV_N17, &BMICON_EV_N1_7, IDS_DS_EV_N17,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EV_N20_EN)
SMENUITEM sItemEV_N20               = { ITEMID_EV_N20, &BMICON_EV_N2_0, IDS_DS_EV_N20,NULL, MenuItemExpoAdjust, 0, AHC_TRUE, NULL };
#endif
#endif

// ISO Sensitivity
#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
SMENUITEM sItemISO                  = { ITEMID_ISO,      &BMICON_MENU_ISO,  IDS_DS_ISO,     &sSubISO, 0,        0, AHC_TRUE, NULL };
#if (MENU_MANUAL_ISO_AUTO_EN)
SMENUITEM sItemISO_Auto             = { ITEMID_ISO_AUTO, &BMICON_ISO_AUTO,  IDS_DS_AUTO,     NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_100_EN)
SMENUITEM sItemISO_100              = { ITEMID_ISO_100,  &BMICON_ISO_100,   IDS_DS_ISO_100,  NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_200_EN)
SMENUITEM sItemISO_200              = { ITEMID_ISO_200,  &BMICON_ISO_200,   IDS_DS_ISO_200,  NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_400_EN)
SMENUITEM sItemISO_400              = { ITEMID_ISO_400,  &BMICON_ISO_400,   IDS_DS_ISO_400,  NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_800_EN)
SMENUITEM sItemISO_800              = { ITEMID_ISO_800,  NULL,              IDS_DS_ISO_800,  NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_1600_EN)
SMENUITEM sItemISO_1600             = { ITEMID_ISO_1600, NULL,              IDS_DS_ISO_1600, NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_ISO_3200_EN)
SMENUITEM sItemISO_3200             = { ITEMID_ISO_3200, NULL,              IDS_DS_ISO_3200, NULL, MenuItemISO, 0, AHC_TRUE, NULL };
#endif
#endif

// White Balance
#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)

SMENUITEM sItemWB                   = { ITEMID_WB,              &BMICON_MENU_AWB,       IDS_DS_WB,              &sSubWB, 0,       0, AHC_TRUE, NULL };
#if (MENU_MANUAL_WB_AUTO_EN)
SMENUITEM sItemWB_Auto              = { ITEMID_WB_AUTO,         &BMICON_WB_AUTO,        IDS_DS_AUTO,            NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_DAYLIGHT_EN)
SMENUITEM sItemWB_Daylight          = { ITEMID_WB_DAYLIGHT,     &BMICON_WB_DAYLIGHT,    IDS_DS_WB_DAYLIGHT,     NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_CLOUDY_EN)
SMENUITEM sItemWB_Cloudy            = { ITEMID_WB_CLOUDY,       &BMICON_WB_CLOUDY,      IDS_DS_WB_CLOUDY,       NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT1_EN)
SMENUITEM sItemWB_Fluorescent1      = { ITEMID_WB_FLUORESCENT1, &BMICON_WB_FLUO1,       IDS_DS_WB_FLUORESCENT1, NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT2_EN)
SMENUITEM sItemWB_Fluorescent2      = { ITEMID_WB_FLUORESCENT2, &BMICON_WB_FLUO2,       IDS_DS_WB_FLUORESCENT2, NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT3_EN)
SMENUITEM sItemWB_Fluorescent3      = { ITEMID_WB_FLUORESCENT3, &BMICON_WB_FLUO3,       IDS_DS_WB_FLUORESCENT3, NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_INCANDESCENT_EN)
SMENUITEM sItemWB_Incandescent      = { ITEMID_WB_INCANDESCENT, &BMICON_WB_INCANDESCENT,IDS_DS_WB_INCANDESCENT, NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_FLASH_EN)
SMENUITEM sItemWB_Flash             = { ITEMID_WB_FLASH,        &BMICON_WB_FLASH,       IDS_DS_WB_FLASH,        NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_ONEPUSH_EN)
SMENUITEM sItemWB_Onepush           = { ITEMID_WB_ONEPUSH,      &BMICON_WB_ONE_PUSH,    IDS_DS_WB_ONEPUSH,      NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
SMENUITEM sItemWB_OnePush_Set       = { ITEMID_WB_ONE_PUSH_SET, &BMICON_WB_ONE_PUSH_SET,IDS_DS_WB_ONE_PUSH_SET, NULL, MenuItemWB, 0, AHC_TRUE, NULL };
#endif
#endif

// Color
#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
SMENUITEM sItemColor                = { ITEMID_COLOR,         &BMICON_MENU_COLOR,    IDS_DS_COLOR,  &sSubColor, 0,              0, AHC_TRUE, NULL };
#if (MENU_MANUAL_COLOR_NATURAL_EN)
SMENUITEM sItemColor_Natural        = { ITEMID_COLOR_NATURAL, &BMICON_COLOR_NATURAL, IDS_DS_COLOR_NATURAL, NULL, MenuItemColor, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_COLOR_VIVID_EN)
SMENUITEM sItemColor_Vivid          = { ITEMID_COLOR_VIVID,   &BMICON_COLOR_VIVID,   IDS_DS_COLOR_VIVID,   NULL, MenuItemColor, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_COLOR_PALE_EN)
SMENUITEM sItemColor_Pale           = { ITEMID_COLOR_PALE,    &BMICON_COLOR_PALE,    IDS_DS_COLOR_PALE,    NULL, MenuItemColor, 0, AHC_TRUE, NULL };
#endif
#endif

// Effect
#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
SMENUITEM sItemEffect               = { ITEMID_EFFECT,              &BMICON_MENU_EFFECT,    IDS_DS_EFFECT,              &sSubEffect, 0,       0, AHC_TRUE, NULL };
#if (MENU_MANUAL_EFFECT_NORMAL_EN)
SMENUITEM sItemEffect_Normal        = { ITEMID_EFFECT_NORMAL,       &BMICON_EFFECT_NORMAL,  IDS_DS_NORMAL,              NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_SEPIA_EN)
SMENUITEM sItemEffect_Sepia         = { ITEMID_EFFECT_SEPIA,        &BMICON_EFFECT_SEPIA,   IDS_DS_EFFECT_SEPIA,        NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_BLACK_WHITE_EN)
SMENUITEM sItemEffect_BlackWhite    = { ITEMID_EFFECT_BLACK_WHITE,  &BMICON_EFFECT_BW,      IDS_DS_EFFECT_BLACK_WHITE,  NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_EMBOSS_EN)
SMENUITEM sItemEffect_Emboss        = { ITEMID_EFFECT_EMBOSS,       &BMICON_EFFECT_EMBOSS,  IDS_DS_EFFECT_EMBOSS,       NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_NEGATIVE_EN)
SMENUITEM sItemEffect_Negative      = { ITEMID_EFFECT_NEGATIVE,     &BMICON_EFFECT_NAGATIVE, IDS_DS_EFFECT_NEGATIVE,    NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_SKETCH_EN)
SMENUITEM sItemEffect_Sketch        = { ITEMID_EFFECT_SKETCH,       &BMICON_EFFECT_SKETCH,  IDS_DS_EFFECT_SKETCH,       NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_OIL_EN)
SMENUITEM sItemEffect_Oil           = { ITEMID_EFFECT_OIL,          &BMICON_EFFECT_OIL,     IDS_DS_EFFECT_OIL,          NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_CRAYON_EN)
SMENUITEM sItemEffect_Crayon        = { ITEMID_EFFECT_CRAYON,       &BMICON_EFFECT_CRAYON,  IDS_DS_EFFECT_CRAYON,       NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#if (MENU_MANUAL_EFFECT_BEAUTY_EN)
SMENUITEM sItemEffect_Beauty        = { ITEMID_EFFECT_BEAUTY,       &BMICON_EFFECT_BEAUTY,  IDS_DS_EFFECT_BEAUTY,       NULL, MenuItemEffect, 0, AHC_TRUE, NULL };
#endif
#endif

// Contrast Adjust
#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
SMENUITEM sItemContrast             = { ITEMID_CONTRAST,        &BMICON_MENU_CONTRAST,  IDS_DS_CONTRAST,    &sSubContrastAdjust, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemContrastInc          = { ITEMID_CONTRAST_INC,    &BMICON_MENU_CONTRAST,  IDS_DS_CONTRAST,    NULL, MenuItemContrastAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemContrastDec          = { ITEMID_CONTRAST_DEC,    &BMICON_MENU_CONTRAST,  IDS_DS_CONTRAST,    NULL, MenuItemContrastAdjust, 0, AHC_TRUE, NULL };
#endif

// Saturation Adjust
#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
SMENUITEM sItemSaturation           = { ITEMID_SATURATION,      &BMICON_MENU_SATURATION,IDS_DS_SATURATION,  &sSubSaturationAdjust, 0,   0, AHC_TRUE, NULL };
SMENUITEM sItemSaturationInc        = { ITEMID_SATURATION_INC,  &BMICON_MENU_SATURATION,IDS_DS_SATURATION,  NULL, MenuItemSaturationAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemSaturationDec        = { ITEMID_SATURATION_DEC,  &BMICON_MENU_SATURATION,IDS_DS_SATURATION,  NULL, MenuItemSaturationAdjust, 0, AHC_TRUE, NULL };
#endif

// Sharpness Adjust
#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
SMENUITEM sItemSharpness            = { ITEMID_SHARPNESS,       &BMICON_MENU_SHARPNESS, IDS_DS_SHARPNESS,   &sSubSharpnessAdjust, 0,    0, AHC_TRUE, NULL };
SMENUITEM sItemSharpnessInc         = { ITEMID_SHARPNESS_INC,   &BMICON_MENU_SHARPNESS, IDS_DS_SHARPNESS,   NULL, MenuItemSharpnessAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemSharpnessDec         = { ITEMID_SHARPNESS_DEC,   &BMICON_MENU_SHARPNESS, IDS_DS_SHARPNESS,   NULL, MenuItemSharpnessAdjust, 0, AHC_TRUE, NULL };
#endif

// Gamma Adjust
#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
SMENUITEM sItemGamma                = { ITEMID_GAMMA,           &BMICON_MENU_GAMMA,     IDS_DS_GAMMA,       &sSubGammaAdjust, 0,    0, AHC_TRUE, NULL };
SMENUITEM sItemGammaInc             = { ITEMID_GAMMA_INC,       &BMICON_MENU_GAMMA,     IDS_DS_GAMMA,       NULL, MenuItemGammaAdjust, 0, AHC_TRUE, NULL };
SMENUITEM sItemGammaDec             = { ITEMID_GAMMA_DEC,       &BMICON_MENU_GAMMA,     IDS_DS_GAMMA,       NULL, MenuItemGammaAdjust, 0, AHC_TRUE, NULL };
#endif

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
PSMENUITEM   sMenuListScence[] =
{
#if (MENU_MANUAL_SCENE_AUTO_EN)
    &sItemScence_Auto,
#endif
#if (MENU_MANUAL_SCENE_SPORT_EN)
    &sItemScence_Sports,
#endif
#if (MENU_MANUAL_SCENE_PORTRAIT_EN)
    &sItemScence_Portrait,
#endif
#if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
    &sItemScence_Landscape,
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
    &sItemScence_TwilightPortrait,
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_EN)
    &sItemScence_Twilight,
#endif
#if (MENU_MANUAL_SCENE_SNOW_EN)
    &sItemScence_Snow,
#endif
#if (MENU_MANUAL_SCENE_BEACH_EN)
    &sItemScence_Beach,
#endif
#if (MENU_MANUAL_SCENE_FIREWORKS_EN)
    &sItemScence_Fireworks
#endif
};
#endif

#if (MENU_MANUAL_FOCUS_EN)
PSMENUITEM   sMenuListFocusWindow[] =
{
#if (MENU_MANUAL_FOCUS_MULTI_EN)
    &sItemFocusWindow_Multi,
#endif
#if (MENU_MANUAL_FOCUS_CENTERSPOT_EN)
    &sItemFocusWindow_CSpot
#endif
};
#endif

#if (MENU_MANUAL_FOCUS_RANGE_EN)
PSMENUITEM   sMenuListFocusRange[] =
{
#if (MENU_MANUAL_FOCUS_RANGE_NORMAL_EN)
    &sItemFocusRange_Normal,
#endif
#if (MENU_MANUAL_FOCUS_RANGE_MACRO_EN)
    &sItemFocusRange_Macro
#endif
};
#endif

#if (MENU_MANUAL_METERING_EN)
PSMENUITEM   sMenuListExpoMeterting[] =
{
#if (MENU_MANUAL_METERING_MULTI_EN)
    &sItemMetering_Multi,
#endif
#if (MENU_MANUAL_METERING_WEIGHTED_EN)
    &sItemMetering_CWeighted,
#endif
#if (MENU_MANUAL_METERING_CENTER_SPOT_EN)
    &sItemMetering_CenterSpot
#endif
};
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
PSMENUITEM   sMenuListEV[] =
{
#if (MENU_MANUAL_EV_N20_EN)
    &sItemEV_N20,
#endif
#if (MENU_MANUAL_EV_N17_EN)
    &sItemEV_N17,
#endif
#if (MENU_MANUAL_EV_N13_EN)
    &sItemEV_N13,
#endif
#if (MENU_MANUAL_EV_N10_EN)
    &sItemEV_N10,
#endif
#if (MENU_MANUAL_EV_N07_EN)
    &sItemEV_N07,
#endif
#if (MENU_MANUAL_EV_N03_EN)
    &sItemEV_N03,
#endif
#if (MENU_MANUAL_EV_00_EN)
    &sItemEV_00,
#endif
#if (MENU_MANUAL_EV_P03_EN)
    &sItemEV_P03,
#endif
#if (MENU_MANUAL_EV_P07_EN)
    &sItemEV_P07,
#endif
#if (MENU_MANUAL_EV_P10_EN)
    &sItemEV_P10,
#endif
#if (MENU_MANUAL_EV_P13_EN)
    &sItemEV_P13,
#endif
#if (MENU_MANUAL_EV_P17_EN)
    &sItemEV_P17,
#endif
#if (MENU_MANUAL_EV_P20_EN)
    &sItemEV_P20
#endif
};
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
PSMENUITEM   sMenuListISO[] =
{
#if (MENU_MANUAL_ISO_AUTO_EN)
    &sItemISO_Auto,
#endif
#if (MENU_MANUAL_ISO_100_EN)
    &sItemISO_100,
#endif
#if (MENU_MANUAL_ISO_200_EN)
    &sItemISO_200,
#endif
#if (MENU_MANUAL_ISO_400_EN)
    &sItemISO_400,
#endif
#if (MENU_MANUAL_ISO_800_EN)
    &sItemISO_800,
#endif
#if (MENU_MANUAL_ISO_1600_EN)
    &sItemISO_1600,
#endif
#if (MENU_MANUAL_ISO_3200_EN)
    &sItemISO_3200
#endif
};
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
PSMENUITEM   sMenuListWB[] =
{
#if (MENU_MANUAL_WB_AUTO_EN)
    &sItemWB_Auto,
#endif
#if (MENU_MANUAL_WB_DAYLIGHT_EN)
    &sItemWB_Daylight,
#endif
#if (MENU_MANUAL_WB_CLOUDY_EN)
    &sItemWB_Cloudy,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT1_EN)
    &sItemWB_Fluorescent1,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT2_EN)
    &sItemWB_Fluorescent2,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT3_EN)
    &sItemWB_Fluorescent3,
#endif
#if (MENU_MANUAL_WB_INCANDESCENT_EN)
    &sItemWB_Incandescent,
#endif
#if (MENU_MANUAL_WB_FLASH_EN)
    &sItemWB_Flash,
#endif
#if (MENU_MANUAL_WB_ONEPUSH_EN)
    &sItemWB_Onepush,
#endif
#if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
    &sItemWB_OnePush_Set
#endif
};
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN)
PSMENUITEM   sMenuListColor[] =
{
#if (MENU_MANUAL_COLOR_NATURAL_EN)
    &sItemColor_Natural,
#endif
#if (MENU_MANUAL_COLOR_VIVID_EN)
    &sItemColor_Vivid,
#endif
#if (MENU_MANUAL_COLOR_PALE_EN)
    &sItemColor_Pale
#endif
};
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
PSMENUITEM   sMenuListEffect[] =
{
#if (MENU_MANUAL_EFFECT_NORMAL_EN)
    &sItemEffect_Normal,
#endif
#if (MENU_MANUAL_EFFECT_SEPIA_EN)
    &sItemEffect_Sepia,
#endif
#if (MENU_MANUAL_EFFECT_BLACK_WHITE_EN)
    &sItemEffect_BlackWhite,
#endif
#if (MENU_MANUAL_EFFECT_EMBOSS_EN)
    &sItemEffect_Emboss,
#endif
#if (MENU_MANUAL_EFFECT_NEGATIVE_EN)
    &sItemEffect_Negative,
#endif
#if (MENU_MANUAL_EFFECT_SKETCH_EN)
    &sItemEffect_Sketch,
#endif
#if (MENU_MANUAL_EFFECT_OIL_EN)
    &sItemEffect_Oil,
#endif
#if (MENU_MANUAL_EFFECT_CRAYON_EN)
    &sItemEffect_Crayon,
#endif
#if (MENU_MANUAL_EFFECT_BEAUTY_EN)
    &sItemEffect_Beauty
#endif
};
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
PSMENUITEM   sMenuListContrast[] =
{
    &sItemContrastDec,
    &sItemContrastInc
};
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
PSMENUITEM   sMenuListSaturation[] =
{
    &sItemSaturationDec,
    &sItemSaturationInc
};
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
PSMENUITEM   sMenuListSharpness[] =
{
    &sItemSharpnessDec,
    &sItemSharpnessInc
};
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
PSMENUITEM   sMenuListGamma[] =
{
    &sItemGammaDec,
    &sItemGammaInc
};
#endif

/*===========================================================================
 * Global varible : Menu Structure
 *===========================================================================*/

//--------------SUB MENU-------------------

#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
SMENUSTRUCT sSubScence =
{
    MENUID_SUB_MENU_SCENCE,
    NULL,
    IDS_DS_SCENE_SELECTION,
    NULL,
    sizeof(sMenuListScence)/sizeof(PSMENUITEM),
    sMenuListScence,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_SCENE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_FOCUS_EN)
SMENUSTRUCT sSubFocusWindow =
{
    MENUID_SUB_MENU_FOCUSWINDOW,
    NULL,
    IDS_DS_FOCUS_WINDOW,
    NULL,
    sizeof(sMenuListFocusWindow)/sizeof(PSMENUITEM),
    sMenuListFocusWindow,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_FOCUS_WINDOW_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_FOCUS_RANGE_EN)
SMENUSTRUCT sSubFocusRange=
{
    MENUID_SUB_MENU_FOCUSRANGE,
    NULL,
    IDS_DS_FOCUS_RANGE,
    NULL,
    sizeof(sMenuListFocusRange)/sizeof(PSMENUITEM),
    sMenuListFocusRange,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_FOCUS_RANGE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_METERING_EN)
SMENUSTRUCT sSubExpoMetering =
{
    MENUID_SUB_MENU_METERING,
    NULL,
    IDS_DS_METERING,
    &sSubExpoMetering,
    sizeof(sMenuListExpoMeterting)/sizeof(PSMENUITEM),
    sMenuListExpoMeterting,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_METERING_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
SMENUSTRUCT sSubExpoAdjust =
{
    MENUID_SUB_MENU_EV,
    NULL,
    IDS_DS_EV,
    NULL,
    sizeof(sMenuListEV)/sizeof(PSMENUITEM),
    sMenuListEV,
    SubMenuEventHandler_EV,//SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_EV_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
SMENUSTRUCT sSubISO =
{
    MENUID_SUB_MENU_ISO,
    NULL,
    IDS_DS_ISO,
    NULL,
    sizeof(sMenuListISO)/sizeof(PSMENUITEM),
    sMenuListISO,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_ISO_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
SMENUSTRUCT sSubWB =
{
    MENUID_SUB_MENU_WB,
    NULL,
    IDS_DS_WB,
    NULL,
    sizeof(sMenuListWB)/sizeof(PSMENUITEM),
    sMenuListWB,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_WB_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN)
SMENUSTRUCT sSubColor =
{
    MENUID_SUB_MENU_COLOR,
    NULL,
    IDS_DS_COLOR,
    NULL,
    sizeof(sMenuListColor)/sizeof(PSMENUITEM),
    sMenuListColor,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_COLOR_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
SMENUSTRUCT sSubEffect =
{
    MENUID_SUB_MENU_EFFECT,
    NULL,
    IDS_DS_EFFECT,
    NULL,
    sizeof(sMenuListEffect)/sizeof(PSMENUITEM),
    sMenuListEffect,
    SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_EFFECT_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
SMENUSTRUCT sSubContrastAdjust =
{
    MENUID_SUB_MENU_CONTRAST,
    NULL,
    IDS_DS_CONTRAST,
    NULL,
    sizeof(sMenuListContrast)/sizeof(PSMENUITEM),
    sMenuListContrast,
    SubMenuEventHandler_Contrast,//SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_CONTRAST_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
SMENUSTRUCT sSubSaturationAdjust =
{
    MENUID_SUB_MENU_SATURATION,
    NULL,
    IDS_DS_SATURATION,
    NULL,
    sizeof(sMenuListSaturation)/sizeof(PSMENUITEM),
    sMenuListSaturation,
    SubMenuEventHandler_Saturation,//SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_SATURATION_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
SMENUSTRUCT sSubSharpnessAdjust =
{
    MENUID_SUB_MENU_SHARPNESS,
    NULL,
    IDS_DS_SHARPNESS,
    NULL,
    sizeof(sMenuListSharpness)/sizeof(PSMENUITEM),
    sMenuListSharpness,
    SubMenuEventHandler_Sharpness,//SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_SHARPNESS_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
SMENUSTRUCT sSubGammaAdjust =
{
    MENUID_SUB_MENU_GAMMA,
    NULL,
    IDS_DS_GAMMA,
    NULL,
    sizeof(sMenuListSaturation)/sizeof(PSMENUITEM),
    sMenuListGamma,
    SubMenuEventHandler_Gamma,//SubMenuEventHandler,
    MenuGetDefault_ManualSetting,
    0,
    IDS_DS_GAMMA_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
AHC_BOOL MenuItemScenceSelect(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiScene = pItem->iItemId - ITEMID_SCENE -1;
    Menu_SetSceneMode(MenuSettingConfig()->uiScene);

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

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_FOCUS_EN)
AHC_BOOL MenuItemFocusWindow(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiFocus = pItem->iItemId - ITEMID_FOCUSWINDOW-1;

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_FOCUS_RANGE_EN)
AHC_BOOL MenuItemFocusRange(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiFocusRange = pItem->iItemId - ITEMID_FOCUSRANGE-1;

    switch(pItem->iItemId)
    {
    #if (MENU_MANUAL_FOCUS_RANGE_NORMAL_EN)
        case ITEMID_FOCUSRANGE_NORMAL:      AHC_SetAfMode(AHC_AF_MODE_NORMAL);  break;
    #endif
    #if (MENU_MANUAL_FOCUS_RANGE_MACRO_EN)
        case ITEMID_FOCUSRANGE_MACRO:       AHC_SetAfMode(AHC_AF_MODE_MACRO);   break;
    #endif
        default:                            AHC_SetAfMode(AHC_AF_MODE_FULL);    break;
    }

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_METERING_EN)
AHC_BOOL MenuItemExpoMetering(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiMetering = pItem->iItemId - ITEMID_METERING-1;

    switch(pItem->iItemId)
    {
    #if (MENU_MANUAL_METERING_MULTI_EN)
        case ITEMID_METERING_MULTI:
            AHC_SetAeMeteringMode(0, AHC_AE_METERING_MATRIX);
            if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SetAeMeteringMode(1, AHC_AE_METERING_MATRIX);
        break;
    #endif
    #if (MENU_MANUAL_METERING_WEIGHTED_EN)
        case ITEMID_METERING_CENTER_WEIGHTED:
            AHC_SetAeMeteringMode(0, AHC_AE_METERING_CENTER);
            if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SetAeMeteringMode(1, AHC_AE_METERING_CENTER);
        break;
    #endif
    #if (MENU_MANUAL_METERING_CENTER_SPOT_EN)
        case ITEMID_METERING_CENTER_SPOT:
            AHC_SetAeMeteringMode(0, AHC_AE_METERING_SPOT);
            if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SetAeMeteringMode(1, AHC_AE_METERING_SPOT);
        break;
    #endif
        case ITEMID_METERING_TOUCH_SPOT:
            AHC_DBG_MSG(1, "Not supported now. \n");
        break;
        default:
            AHC_SetAeMeteringMode(0, AHC_AE_METERING_MATRIX);
            if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SetAeMeteringMode(1, AHC_AE_METERING_MATRIX);
        break;
    }

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
AHC_BOOL MenuItemExpoAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiEV = pItem->iItemId - ITEMID_EV-1;
    Menu_SetEV(0, MenuSettingConfig()->uiEV);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetEV(1, MenuSettingConfig()->uiEV);
    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
AHC_BOOL MenuItemISO(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiISO = pItem->iItemId - ITEMID_ISO-1;
    Menu_SetISO(0, MenuSettingConfig()->uiISO);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetISO(1, MenuSettingConfig()->uiISO);
    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
AHC_BOOL MenuItemWB(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set WB when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    MenuSettingConfig()->uiWB = pItem->iItemId - ITEMID_WB -1;
    Menu_SetAWB(0, MenuSettingConfig()->uiWB);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetAWB(1, MenuSettingConfig()->uiWB);
    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
AHC_BOOL MenuItemColor(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set Saturation when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    MenuSettingConfig()->uiColor = pItem->iItemId - ITEMID_COLOR-1;
    Menu_SetColor(0, MenuSettingConfig()->uiColor);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetColor(1, MenuSettingConfig()->uiColor);

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
AHC_BOOL MenuItemEffect(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
#if ( MENU_MANUAL_COLOR_EN)
    if (MenuSettingConfig()->uiColor != COLOR_NATURAL)    {

        MenuSettingConfig()->uiColor = COLOR_NATURAL;
        Menu_SetColor(0, COLOR_NATURAL);
        if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            Menu_SetColor(1, COLOR_NATURAL);
        AHC_DBG_MSG(1, "Try to set effect mode when menu_color != COLOR_NATURAL\r\n");
        AHC_DBG_MSG(1, "Set menu_color = COLOR_NATURAL first\r\n");
    }
#endif
    MenuSettingConfig()->uiEffect = pItem->iItemId - ITEMID_EFFECT-1;
    Menu_SetEffect(0, MenuSettingConfig()->uiEffect);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetEffect(1, MenuSettingConfig()->uiEffect);
    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
AHC_BOOL MenuItemContrastAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    INT32 s32Contrast = 0;
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set Contrast when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    pf_General_EnGet(COMMON_KEY_CONTRAST, &s32Contrast);

    if (ITEMID_CONTRAST_INC == pItem->iItemId){
        AHC_DBG_MSG(1, "ITEMID_CONTRAST_INC\r\n");
        if (s32Contrast >= MENU_MANUAL_CONTRAST_MAX)
            s32Contrast = MENU_MANUAL_CONTRAST_MAX;
        else
            s32Contrast += MENU_MANUAL_CONTRAST_STEP;
    }
    else if (ITEMID_CONTRAST_DEC == pItem->iItemId) {
        AHC_DBG_MSG(1, "ITEMID_CONTRAST_DEC\r\n");
        if (s32Contrast <= MENU_MANUAL_CONTRAST_MIN)
            s32Contrast = MENU_MANUAL_CONTRAST_MIN;
        else
            s32Contrast -= MENU_MANUAL_CONTRAST_STEP;
    }

    AHC_DBG_MSG(1, "New contrast = %d\r\n", s32Contrast);

    pf_General_EnSet(COMMON_KEY_CONTRAST, s32Contrast);
    Menu_SetContrast(0, s32Contrast);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetContrast(1, s32Contrast);

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
AHC_BOOL MenuItemSaturationAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    INT32 s32Saturation = 0;
#if ( MENU_MANUAL_COLOR_EN)

   if ( MenuSettingConfig()->uiColor != COLOR_NATURAL)
   {
       AHC_DBG_MSG(1, "Try to set Saturation when menu_color != COLOR_NATURAL\r\n");
       return AHC_FALSE;
   }
#endif
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set Saturation when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    pf_General_EnGet(COMMON_KEY_SATURATION, &s32Saturation);

    if (ITEMID_SATURATION_INC == pItem->iItemId){
        AHC_DBG_MSG(1, "ITEMID_SATURATION_INC\r\n");
        if ((INT32)s32Saturation >= MENU_MANUAL_SATURATION_MAX)
            s32Saturation = MENU_MANUAL_SATURATION_MAX;
        else
            s32Saturation += MENU_MANUAL_SATURATION_STEP;
    }
    else if (ITEMID_SATURATION_DEC == pItem->iItemId) {
        AHC_DBG_MSG(1, "ITEMID_SATURATION_DEC\r\n");
        if ((INT32)s32Saturation <= MENU_MANUAL_SATURATION_MIN)
            s32Saturation = MENU_MANUAL_SATURATION_MIN;
        else
            s32Saturation -= MENU_MANUAL_SATURATION_STEP;
    }

    pf_General_EnSet(COMMON_KEY_SATURATION, s32Saturation);
    Menu_SetSaturation(0, s32Saturation);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetSaturation(1, s32Saturation);

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
AHC_BOOL MenuItemSharpnessAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    INT32 s32Sharpness = 0;
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set Sharpness when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    pf_General_EnGet(COMMON_KEY_SHARPNESS, &s32Sharpness);

    if (ITEMID_SHARPNESS_INC == pItem->iItemId){
        AHC_DBG_MSG(1, "ITEMID_SHARPNESS_INC\r\n");
        if ((INT32)s32Sharpness >= MENU_MANUAL_SHARPNESS_MAX)
            s32Sharpness = MENU_MANUAL_SHARPNESS_MAX;
        else
            s32Sharpness += MENU_MANUAL_SHARPNESS_STEP;
    }
    else if (ITEMID_SHARPNESS_DEC == pItem->iItemId) {
        AHC_DBG_MSG(1, "ITEMID_SHARPNESS_DEC\r\n");
        if ((INT32)s32Sharpness <= MENU_MANUAL_SHARPNESS_MIN)
            s32Sharpness = MENU_MANUAL_SHARPNESS_MIN;
        else
            s32Sharpness -= MENU_MANUAL_SHARPNESS_STEP;
    }

    AHC_DBG_MSG(1, "New contrast = %d\r\n", s32Sharpness);

    pf_General_EnSet(COMMON_KEY_SHARPNESS, s32Sharpness);
    Menu_SetSharpness(0, s32Sharpness);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetSharpness(1, s32Sharpness);

    return AHC_TRUE;
}
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
AHC_BOOL MenuItemGammaAdjust(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    INT32 s32Gamma = 0;
#if ( MENU_MANUAL_EFFECT_EN)
   if ( MenuSettingConfig()->uiEffect != EFFECT_NORMAL)
   {
       AHC_DBG_MSG(1, "Try to set Gamma when menu_effect != EFFECT_NORMAL\r\n");
       return AHC_FALSE;
   }
#endif
    pf_General_EnGet(COMMON_KEY_GAMMA, &s32Gamma);

    if (ITEMID_GAMMA_INC == pItem->iItemId){
        AHC_DBG_MSG(1, "ITEMID_GAMMA_INC\r\n");
        if (s32Gamma >= MENU_MANUAL_GAMMA_MAX)
            s32Gamma = MENU_MANUAL_GAMMA_MAX;
        else
            s32Gamma += MENU_MANUAL_GAMMA_STEP;
    }
    else if (ITEMID_GAMMA_DEC == pItem->iItemId) {
        AHC_DBG_MSG(1, "ITEMID_GAMMA_DEC\r\n");
        if (s32Gamma <= MENU_MANUAL_GAMMA_MIN)
            s32Gamma = MENU_MANUAL_GAMMA_MIN;
        else
            s32Gamma -= MENU_MANUAL_GAMMA_STEP;
    }

    AHC_DBG_MSG(1, "New gamma = %d\r\n", s32Gamma);

    pf_General_EnSet(COMMON_KEY_GAMMA, s32Gamma);
    Menu_SetGamma(0, s32Gamma);
    if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        Menu_SetGamma(1, s32Gamma);

    return AHC_TRUE;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 MenuGetDefault_ManualSetting(PSMENUSTRUCT pMenu)
{
    UINT32  DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
        case MENUID_SUB_MENU_SCENCE:
            DefaultValue = MenuSettingConfig()->uiScene;
            break;
#endif
#if (MENU_MANUAL_FOCUS_EN)
        case MENUID_SUB_MENU_FOCUSWINDOW:
            DefaultValue = MenuSettingConfig()->uiFocus;
            break;
#endif
#if (MENU_MANUAL_FOCUS_RANGE_EN)
        case MENUID_SUB_MENU_FOCUSRANGE:
            DefaultValue = MenuSettingConfig()->uiFocusRange;
            break;
#endif
#if (MENU_MANUAL_METERING_EN)
        case MENUID_SUB_MENU_METERING:
            DefaultValue = MenuSettingConfig()->uiMetering;
            break;
#endif
#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
        case MENUID_SUB_MENU_EV:
            DefaultValue = MenuSettingConfig()->uiEV;
            break;
#endif
#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
        case MENUID_SUB_MENU_ISO:
            DefaultValue = MenuSettingConfig()->uiISO;
            break;
#endif
#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
        case MENUID_SUB_MENU_WB:
            DefaultValue = MenuSettingConfig()->uiWB ;
            break;
#endif
#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
        case MENUID_SUB_MENU_COLOR:
            DefaultValue = MenuSettingConfig()->uiColor;
            break;
#endif
#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
        case MENUID_SUB_MENU_EFFECT:
            DefaultValue = MenuSettingConfig()->uiEffect;
            break;
#endif
#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
        case MENUID_SUB_MENU_CONTRAST:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_CONTRAST, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
        case MENUID_SUB_MENU_SATURATION:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_SATURATION, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
        case MENUID_SUB_MENU_SHARPNESS:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_SHARPNESS, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
        case MENUID_SUB_MENU_GAMMA:
            {
                INT32 s32Setting = 0;

                pf_General_EnGet(COMMON_KEY_GAMMA, &s32Setting);
                DefaultValue = (UINT32) s32Setting;
            }
            break;
#endif
    }

    return DefaultValue;
}

////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)

UINT32 SubMenuEventHandler_EV(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
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
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_EV( pMenu );
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

        MenuItemExpoAdjust(sMenuListEV[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_EV( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
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

        MenuItemExpoAdjust(sMenuListEV[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_EV( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

        if( pCurrentItem ->pfItemSelect != NULL )
        {
            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
        }

        iPrevPos         = pMenu->iCurrentPos;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if(ulEvent==MENU_SET_ONE)
        {
            pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
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

            return SubMenuEventHandler_EV(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_EV( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
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

////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)

UINT32 SubMenuEventHandler_Contrast(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
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
        AHC_DBG_MSG(1, "%s - MENU_INIT\r\n", __func__);

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
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_Contrast( pMenu );
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

        MenuItemContrastAdjust(sMenuListContrast[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Contrast();
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

        AHC_DBG_MSG(1, "%s - MENU_RIGHT\r\n", __func__);

        iPrevPos = pMenu->iCurrentPos;

        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuItemContrastAdjust(sMenuListContrast[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Contrast();
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        AHC_DBG_MSG(1, "%s - MENU_OK\r\n", __func__);

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

//        if( pCurrentItem ->pfItemSelect != NULL )
//        {
//            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
//        }

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

////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)

UINT32 SubMenuEventHandler_Saturation(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
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
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_Saturation( pMenu );
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

        MenuItemSaturationAdjust(sMenuListSaturation[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Saturation();
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

        MenuItemSaturationAdjust(sMenuListSaturation[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Saturation();
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

//        if( pCurrentItem ->pfItemSelect != NULL )
//        {
//            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
//        }

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

            return SubMenuEventHandler_Saturation(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_Saturation();
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

////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)

UINT32 SubMenuEventHandler_Sharpness(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
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
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_Sharpness( pMenu );
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

        MenuItemSharpnessAdjust(sMenuListSharpness[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Sharpness();
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

        MenuItemSharpnessAdjust(sMenuListSharpness[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Sharpness();
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

//        if( pCurrentItem ->pfItemSelect != NULL )
//        {
//            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
//        }

        iPrevPos         = pMenu->iCurrentPos;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if(ulEvent==MENU_SET_ONE)
        {
            pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
        }

       // if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
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

            return SubMenuEventHandler_Sharpness(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_Sharpness();
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

////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)

UINT32 SubMenuEventHandler_Gamma(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;

#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent ){
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
        KeyParser_TouchItemRegister(&MenuEV_TouchButton[0], ITEMNUM(MenuEV_TouchButton));
        #endif

        MenuDrawSubPage_Gamma( pMenu );
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

        MenuItemGammaAdjust(sMenuListGamma[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Gamma();
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

        MenuItemGammaAdjust(sMenuListGamma[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Gamma();
    break;

    case MENU_OK            :
    case MENU_SET_ONE       :
    {
        PSMENUITEM pCurrentItem;

        pMenu->bSetOne  = 1;
        pCurrentItem    = pMenu->pItemsList[pMenu->iCurrentPos];

//        if( pCurrentItem ->pfItemSelect != NULL )
//        {
//            pCurrentItem ->pfItemSelect( pCurrentItem, AHC_TRUE );
//        }

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

            return SubMenuEventHandler_Gamma(pMenu, uiNextEvent, ulParam);
        }
    break;

    case MENU_TOUCH_RELEASE:
        if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
        {
            iPrevPos = pMenu->iSelected;
            pMenu->uiStatus = 0;
            MenuDrawChangeSubItem_Gamma();
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
