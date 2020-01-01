#ifndef _ICON_DEFINE_H_
#define _ICON_DEFINE_H_

#include "Customer_config.h"
#include "ahc_gui.h"
//#include "config_fw.h"

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Dummy;

#if (ENABLE_ADAS_LDWS)
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_LDWS_Right;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_LDWS_Left;
#define BMICON_LDWS_WARNING_RIGHT       bmIcon_LDWS_Right
#define BMICON_LDWS_WARNING_LEFT        bmIcon_LDWS_Left
#else
#define BMICON_LDWS_WARNING_RIGHT       bmIcon_Dummy
#define BMICON_LDWS_WARNING_LEFT        bmIcon_Dummy
#endif

/* Customer Specific Icons */

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
extern GUI_CONST_STORAGE GUI_BITMAP     bmTV_TimeLapseB;
#define BMICON_TV_TIMELAPSE_B           bmTV_TimeLapseB
#endif


#if (MENU_MOVIE_SIZE_EN==1 || OSD_SHOW_MOVIE_SIZE==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_720P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_720_60P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_1080P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_1080P_60;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_VGA_30P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_VGA_120P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_720_10P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_SHD_30P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_SHD_25P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_SHD_24P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_720_24P;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_1080_24P;
    #define BMICON_MOVIESIZE_720P        bmIcon_MovieSize_720P
    #define BMICON_MOVIESIZE_720_60P     bmIcon_MovieSize_720_60P
    #define BMICON_MOVIESIZE_1080P       bmIcon_MovieSize_1080P
    #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) || (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
    #define BMICON_MOVIESIZE_1080P_HDR   bmIcon_MovieSize_1080P
    #endif
    #define BMICON_MOVIESIZE_1080_60P    bmIcon_MovieSize_1080P_60
    #define BMICON_MOVIESIZE_VGA_30P     bmIcon_MovieSize_VGA_30P
    #define BMICON_MOVIESIZE_VGA_120P    bmIcon_MovieSize_VGA_120P
    #define BMICON_MOVIESIZE_1296P       bmIcon_MovieSize_SHD_30P
    #define BMICON_MOVIESIZE_1296_25P    bmIcon_MovieSize_SHD_25P
    #define BMICON_MOVIESIZE_1296_24P    bmIcon_MovieSize_SHD_24P
    #define BMICON_MOVIESIZE_720_24P     bmIcon_MovieSize_720_24P
    #define BMICON_MOVIESIZE_1080_24P    bmIcon_MovieSize_1080_24P
#endif

#if (MENU_STILL_SIZE_EN==1 || OSD_SHOW_IMAGE_SIZE==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_VGA;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_1_2M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_2M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_3M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_5M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_8M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_12M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_14M;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_30ML;
    #define BMICON_IMAGESIZE_VGA         bmIcon_ImageSize_VGA
    #define BMICON_IMAGESIZE_1_2M        bmIcon_ImageSize_1_2M
    #define BMICON_IMAGESIZE_2M          bmIcon_ImageSize_2M
    #define BMICON_IMAGESIZE_3M          bmIcon_ImageSize_3M
    #define BMICON_IMAGESIZE_5M          bmIcon_ImageSize_5M
    #define BMICON_IMAGESIZE_8M          bmIcon_ImageSize_8M
    #define BMICON_IMAGESIZE_12M         bmIcon_ImageSize_12M
    #define BMICON_IMAGESIZE_14M         bmIcon_ImageSize_14M
    #define BMICON_IMAGESIZE_30M         bmIcon_ImageSize_30ML

#endif

#if (MENU_STILL_FLASH_EN==1 || OSD_SHOW_FLASH_STATUS==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Flash_Auto;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Flash_OFF;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Flash_ON;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Flash_Slow_Sync;
#endif

#if (MENU_STILL_SELF_TIMER_EN==1 || OSD_SHOW_SELF_TIMER==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Selftimer_2S;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Selftimer_10S;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SelfTimer;
    #define BMICON_SELFTIMER_2S          bmIcon_Selftimer_2S
    #define BMICON_SELFTIMER_10S         bmIcon_Selftimer_10S
    #define BMICON_SELFTIMER_OFF         bmIcon_Dummy

#endif

#if (MENU_STILL_BURST_SHOT_EN==1 || OSD_SHOW_BURST_SHOT==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Burst_High;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Burst_Low;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Burst_Middle;
#endif

#if (MENU_STILL_STABILIZE_EN==1 || OSD_SHOW_IMAGE_STABLIZATION==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageStable_OFF;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageStable_ON;
#endif

#if (MENU_MANUAL_FOCUS_RANGE_EN==1 || OSD_SHOW_FOCAL_RANGE==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Focus_Infinity;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Focus_Marco;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Focus_Window;
#endif

#if (MENU_MANUAL_FOCUS_EN==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_FocusWindow;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_FocusWindow_CentrSpot;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_FocusWindow_Multi;
#endif

#if (MENU_MANUAL_METERING_EN==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Metering_CenterSpot;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Metering_Multi;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Metering_Weighted;
#endif

#if (MENU_MANUAL_SCENE_EN==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Auto;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Beach;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Fireworks;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Landscape;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Portrait;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Snow;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Sport;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Twilight;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Twilight_Portrait;
    #define BMICON_SCENE_AUTO            bmIcon_Scene_Auto
    #define BMICON_SCENE_BEACH           bmIcon_Scene_Beach
    #define BMICON_SCENE_FIREWORK        bmIcon_Scene_Fireworks
    #define BMICON_SCENE_LANDSCAPE       bmIcon_Scene_Landscape
    #define BMICON_SCENE_PORTRAIT        bmIcon_Scene_Portrait
    #define BMICON_SCENE_SNOW            bmIcon_Scene_Snow
    #define BMICON_SCENE_SPORT           bmIcon_Scene_Sport
    #define BMICON_SCENE_TWILIGHT        bmIcon_Scene_Twilight
    #define BMICON_SCENE_TWILIGHT_POR    bmIcon_Scene_Twilight_Portrait
#else
    #define BMICON_SCENE_AUTO            bmIcon_Dummy
    #define BMICON_SCENE_BEACH           bmIcon_Dummy
    #define BMICON_SCENE_FIREWORK        bmIcon_Dummy
    #define BMICON_SCENE_LANDSCAPE       bmIcon_Dummy
    #define BMICON_SCENE_PORTRAIT        bmIcon_Dummy
    #define BMICON_SCENE_SNOW            bmIcon_Dummy
    #define BMICON_SCENE_SPORT           bmIcon_Dummy
    #define BMICON_SCENE_TWILIGHT        bmIcon_Dummy
    #define BMICON_SCENE_TWILIGHT_POR    bmIcon_Dummy
#endif

#if (OSD_SHOW_SCENE_MODE==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Auto;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Beach;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Fireworks;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Landscape;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Portrait;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Snow;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Sport;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Twilight;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Scene_Twilight_Portrait;
    #define BMICON_UI_SCENE_AUTO         bmIcon_Scene_Auto
    #define BMICON_UI_SCENE_BEACH        bmIcon_Scene_Beach
    #define BMICON_UI_SCENE_FIREWORK     bmIcon_Scene_Fireworks
    #define BMICON_UI_SCENE_LANDSCAPE    bmIcon_Scene_Landscape
    #define BMICON_UI_SCENE_PORTRAIT     bmIcon_Scene_Portrait
    #define BMICON_UI_SCENE_SNOW         bmIcon_Scene_Snow
    #define BMICON_UI_SCENE_SPORT        bmIcon_Scene_Sport
    #define BMICON_UI_SCENE_TWILIGHT     bmIcon_Scene_Twilight
    #define BMICON_UI_SCENE_TWILIGHT_POR bmIcon_Scene_Twilight_Portrait
#else
    #define BMICON_UI_SCENE_AUTO         bmIcon_Dummy
    #define BMICON_UI_SCENE_BEACH        bmIcon_Dummy
    #define BMICON_UI_SCENE_FIREWORK     bmIcon_Dummy
    #define BMICON_UI_SCENE_LANDSCAPE    bmIcon_Dummy
    #define BMICON_UI_SCENE_PORTRAIT     bmIcon_Dummy
    #define BMICON_UI_SCENE_SNOW         bmIcon_Dummy
    #define BMICON_UI_SCENE_SPORT        bmIcon_Dummy
    #define BMICON_UI_SCENE_TWILIGHT     bmIcon_Dummy
    #define BMICON_UI_SCENE_TWILIGHT_POR bmIcon_Dummy
#endif

#if (MENU_MANUAL_WB_EN==1)
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Incandescent;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Cloudy;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Daylight;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent1;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent2;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent3;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Flash;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_One_Push;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_One_Push_Set;
    #define BMICON_WB_AUTO               bmIcon_Dummy
    #define BMICON_WB_INCANDESCENT       bmIcon_WB_Incandescent
    #define BMICON_WB_CLOUDY             bmIcon_WB_Cloudy
    #define BMICON_WB_DAYLIGHT           bmIcon_WB_Daylight
    #define BMICON_WB_FLUO1              bmIcon_WB_Fluorescent1
    #define BMICON_WB_FLUO2              bmIcon_WB_Fluorescent2
    #define BMICON_WB_FLUO3              bmIcon_WB_Fluorescent3
    #define BMICON_WB_FLASH              bmIcon_WB_Flash
    #define BMICON_WB_ONE_PUSH           bmIcon_WB_One_Push
    #define BMICON_WB_ONE_PUSH_SET       bmIcon_WB_One_Push_Set
#else
    #define BMICON_WB_AUTO               bmIcon_Dummy
    #define BMICON_WB_INCANDESCENT       bmIcon_Dummy
    #define BMICON_WB_CLOUDY             bmIcon_Dummy
    #define BMICON_WB_DAYLIGHT           bmIcon_Dummy
    #define BMICON_WB_FLUO1              bmIcon_Dummy
    #define BMICON_WB_FLUO2              bmIcon_Dummy
    #define BMICON_WB_FLUO3              bmIcon_Dummy
    #define BMICON_WB_FLASH              bmIcon_Dummy
    #define BMICON_WB_ONE_PUSH           bmIcon_Dummy
    #define BMICON_WB_ONE_PUSH_SET       bmIcon_Dummy
#endif

#if (OSD_SHOW_WB_MODE==1) //For UI Preview
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Incandescent;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Cloudy;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Daylight;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent1;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent2;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Fluorescent3;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_Flash;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_One_Push;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WB_One_Push_Set;
    #define BMICON_UI_WB_AUTO            bmIcon_Dummy
    #define BMICON_UI_WB_INCANDESCENT    bmIcon_WB_Incandescent
    #define BMICON_UI_WB_CLOUDY          bmIcon_WB_Cloudy
    #define BMICON_UI_WB_DAYLIGHT        bmIcon_WB_Daylight
    #define BMICON_UI_WB_FLUO1           bmIcon_WB_Fluorescent1
    #define BMICON_UI_WB_FLUO2           bmIcon_WB_Fluorescent2
    #define BMICON_UI_WB_FLUO3           bmIcon_WB_Fluorescent3
    #define BMICON_UI_WB_FLASH           bmIcon_WB_Flash
    #define BMICON_UI_WB_ONE_PUSH        bmIcon_WB_One_Push
    #define BMICON_UI_WB_ONE_PUSH_SET    bmIcon_WB_One_Push_Set
#else
    #define BMICON_UI_WB_AUTO            bmIcon_Dummy
    #define BMICON_UI_WB_INCANDESCENT    bmIcon_Dummy
    #define BMICON_UI_WB_CLOUDY          bmIcon_Dummy
    #define BMICON_UI_WB_DAYLIGHT        bmIcon_Dummy
    #define BMICON_UI_WB_FLUO1           bmIcon_Dummy
    #define BMICON_UI_WB_FLUO2           bmIcon_Dummy
    #define BMICON_UI_WB_FLUO3           bmIcon_Dummy
    #define BMICON_UI_WB_FLASH           bmIcon_Dummy
    #define BMICON_UI_WB_ONE_PUSH        bmIcon_Dummy
    #define BMICON_UI_WB_ONE_PUSH_SET    bmIcon_Dummy
#endif

#if (MENU_PLAYBACK_ROTATE_EN==1)
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Rotate_Left;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Rotate_Right;
#endif

#if (OSD_SHOW_BATTERY_STATUS==1)

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Exhaust;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Empty;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Full;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Low;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Mid;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Battery_Normal;
    #define BMICON_BATTERY_EXHAUST       bmIcon_Battery_Exhaust
    #define BMICON_BATTERY_EMPTY         bmIcon_Battery_Empty
    #define BMICON_BATTERY_FULL          bmIcon_Battery_Full
    #define BMICON_BATTERY_LOW           bmIcon_Battery_Low
    #define BMICON_BATTERY_MID           bmIcon_Battery_Mid
    #define BMICON_BATTERY_NORMAL        bmIcon_Battery_Normal

#endif

#if (OSD_SHOW_MEDIA_TYPE==1)
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SD_Card;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SD_Card_No;
    #define BMICON_MEDIA_SD              bmIcon_SD_Card
    #define BMICON_MEDIA_NO_SD           bmIcon_SD_Card_No

    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SD_CardSlow;
    extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SDCard_Error;
    #define BMICON_MEDIA_SD_SLOW         bmIcon_SD_CardSlow
    #define BMICON_MEDIA_SD_ERROR        bmIcon_SDCard_Error
#else
    #define BMICON_MEDIA_SD              bmIcon_Dummy
    #define BMICON_MEDIA_NO_SD           bmIcon_Dummy
    #define BMICON_MEDIA_SD_SLOW         bmIcon_Dummy
    #define BMICON_MEDIA_SD_ERROR        bmIcon_Dummy
#endif

#define BMICON_UI_PARKING_MODE          bmIcon_Dummy

/* Menu Bar Icon */
#if defined(FONT_LARGE)
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_WhiteXLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_YellowXLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_WhiteLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_YellowLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_White_DefaultLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_Yellow_DefaultLarge;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_WhiteSmall;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_YellowSmall;
#define BMICON_MENUBAR_WHITE_XL         bmIcon_MenuBar_WhiteXLarge
#define BMICON_MENUBAR_YELLOW_XL        bmIcon_MenuBar_YellowXLarge
#define BMICON_MENUBAR_WHITE            bmIcon_MenuBar_WhiteLarge
#define BMICON_MENUBAR_YELLOW           bmIcon_MenuBar_YellowLarge
#define BMICON_MENUBAR_WHITE_DEFAULT    bmIcon_MenuBar_White_DefaultLarge
#define BMICON_MENUBAR_YELLOW_DEFAULT   bmIcon_MenuBar_Yellow_DefaultLarge
#define BMICON_SUBBAR_WHITE             bmIcon_MenuBar_WhiteLarge
#define BMICON_SUBBAR_YELLOW            bmIcon_MenuBar_YellowLarge
#define BMICON_SUBBAR_WHITE_DEFAULT     bmIcon_MenuBar_White_DefaultLarge
#define BMICON_SUBBAR_YELLOW_DEFAULT    bmIcon_MenuBar_Yellow_DefaultLarge
#define BMICON_SMALLBAR_WHITE           bmIcon_MenuBar_WhiteSmall
#define BMICON_SMALLBAR_YELLOW          bmIcon_MenuBar_YellowSmall
#else
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_White;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_Yellow;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_White_Default;
extern GUI_CONST_STORAGE GUI_BITMAP     bmIcon_MenuBar_Yellow_Default;
#define BMICON_MENUBAR_WHITE_XL         bmIcon_MenuBar_White
#define BMICON_MENUBAR_YELLOW_XL        bmIcon_MenuBar_Yellow
#define BMICON_MENUBAR_WHITE            bmIcon_MenuBar_White
#define BMICON_MENUBAR_YELLOW           bmIcon_MenuBar_Yellow
#define BMICON_MENUBAR_WHITE_DEFAULT    bmIcon_MenuBar_White_Default
#define BMICON_MENUBAR_YELLOW_DEFAULT   bmIcon_MenuBar_Yellow_Default
#define BMICON_SUBBAR_WHITE             bmIcon_SubMenuBar_White
#define BMICON_SUBBAR_YELLOW            bmIcon_SubMenuBar_Yellow
#define BMICON_SUBBAR_WHITE_DEFAULT     bmIcon_SubMenuBar_White_Default
#define BMICON_SUBBAR_YELLOW_DEFAULT    bmIcon_SubMenuBar_Yellow_Default

#define BMICON_SMALLBAR_WHITE           bmIcon_SubMenuBar_White
#define BMICON_SMALLBAR_YELLOW          bmIcon_SubMenuBar_Yellow
#endif

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SubMenuBar_White;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SubMenuBar_White_Default;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SubMenuBar_Yellow;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SubMenuBar_Yellow_Default;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MenuBar_White_Big;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MenuBar_Yellow_Big;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MenuBar_White_Default_Big;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MenuBar_Yellow_Default_Big;

/* Menu Mode Selection Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_PhotoBrowser;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_VideoBroswer;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MSDC;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_PCCAM;

/* Menu Misc Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Exit;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Cancel;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_OK;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Return;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_D_Down;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_D_Left;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_D_Right;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_D_Up;
#define BMICON_D_DOWN       bmIcon_D_Down
#define BMICON_D_LEFT       bmIcon_D_Left
#define BMICON_D_RIGHT      bmIcon_D_Right
#define BMICON_D_UP         bmIcon_D_Up

/* Main-Menu Icon */
#define BMICON_MENU_MOVIE            bmIcon_Button_Movie//bmIcon_Dummy
#define BMICON_MENU_REC_MODE         bmIcon_Dummy
#define BMICON_MENU_REC_QUALITY      bmIcon_Dummy
#define BMICON_MENU_CLIPTIME         bmIcon_Dummy
#define BMICON_MENU_OFFTIME          bmIcon_Dummy
#define BMICON_MENU_RECORD_SOUND     bmIcon_Dummy
#define BMICON_MENU_MIC              bmIcon_Dummy
#define BMICON_MENU_SCENE            bmIcon_Dummy
#define BMICON_MENU_EV               bmIcon_Dummy
#define BMICON_MENU_AWB              bmIcon_Dummy
#define BMICON_MENU_ISO              bmIcon_Dummy
#define BMICON_MENU_CAMERA           bmIcon_Button_Movie//bmIcon_Dummy
#define BMICON_MENU_IMG_SIZE         bmIcon_Dummy
#define BMICON_MENU_IMG_QUALITY      bmIcon_Dummy
#define BMICON_MENU_TIMELAPSE        bmIcon_Dummy
#define BMICON_MENU_COLOR            bmIcon_Dummy
#define BMICON_MENU_EFFECT           bmIcon_Dummy
#define BMICON_MENU_PLAYBACK         bmIcon_Button_Movie//bmIcon_Dummy
#define BMICON_MENU_VOLUME           bmIcon_Dummy
#define BMICON_MENU_DELETE           bmIcon_Dummy
#define BMICON_MENU_PROTECT          bmIcon_Dummy
#define BMICON_MENU_MEDIATOOL        bmIcon_Button_Movie//bmIcon_Dummy
#define BMICON_MENU_SD_FORMAT        bmIcon_Dummy
#define BMICON_MENU_SD_INFO          bmIcon_Dummy
#define BMICON_MENU_GEN_SETTING      bmIcon_Button_Movie//bmIcon_Dummy
#define BMICON_MENU_BEEP             bmIcon_Dummy
#define BMICON_MENU_AUTO_OFF         bmIcon_Dummy
#define BMICON_MENU_CLOCK            bmIcon_Dummy
#define BMICON_MENU_DRIVER_ID        bmIcon_Dummy
#define BMICON_MENU_DATE             bmIcon_Dummy
#define BMICON_MENU_LANG             bmIcon_Dummy
#define BMICON_MENU_TVOUT            bmIcon_Dummy
#define BMICON_MENU_HDMI             bmIcon_Dummy
#define BMICON_MENU_FLICK            bmIcon_Dummy
#define BMICON_MENU_USB              bmIcon_Dummy
#define BMICON_MENU_FLIP             bmIcon_Dummy
#define BMICON_MENU_LCDPOWER         bmIcon_Dummy
#define BMICON_MENU_BOOTMODE         bmIcon_Dummy
#define BMICON_MENU_RESET            bmIcon_Dummy
#define BMICON_MENU_FW_VER           bmIcon_Dummy
#define BMICON_MENU_GPS              bmIcon_Dummy
#define BMICON_MENU_GSNR_SENS        bmIcon_Dummy
#define BMICON_MENU_TIMEZONE         bmIcon_Dummy
#define BMICON_MENU_GSEN_POWER_ON    bmIcon_Dummy
#define BMICON_MENU_MTD              bmIcon_Dummy
#define BMICON_MENU_WIFI             bmIcon_Dummy
#define BMICON_MENU_EXIT             bmIcon_Dummy
#define BMICON_LDWS_CALI             bmIcon_Dummy
#define BMICON_MENU_CONTRAST         bmIcon_Dummy
#define BMICON_MENU_SATURATION       bmIcon_Dummy
#define BMICON_MENU_SHARPNESS        bmIcon_Dummy
#define BMICON_MENU_GAMMA            bmIcon_Dummy

/* Menu Catalog Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Edit;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Edit_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_General_Settings;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_General_SettingsHL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Manul_Settings;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Manul_Settings_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Media;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Media_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Movie;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Movie_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Playback;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Playback_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Still;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Still_HL;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu_Video_HL;

#define BMICON_CATALOG_MOVIE_MENU_HL    bmIcon_Menu_Movie_HL
#define BMICON_CATALOG_CAMERA_MENU_HL   bmIcon_Menu_Still_HL
#define BMICON_CATALOG_PLAYBACK_MENU_HL bmIcon_Menu_Playback_HL
#define BMICON_CATALOG_MEDIA_MENU_HL    bmIcon_Menu_Media_HL
#define BMICON_CATALOG_GENERAL_MENU_HL  bmIcon_Menu_General_SettingsHL

#define BMICON_CATALOG_MOVIE_MENU    bmIcon_Menu_Movie
#define BMICON_CATALOG_CAMERA_MENU   bmIcon_Menu_Still
#define BMICON_CATALOG_PLAYBACK_MENU bmIcon_Menu_Playback
#define BMICON_CATALOG_MEDIA_MENU    bmIcon_Menu_Media
#define BMICON_CATALOG_GENERAL_MENU  bmIcon_Menu_General_Settings

/* Sub-Menu Icon */

// Movie Resolution
#define BMICON_MOVIE_RES_VGA30P      bmIcon_Dummy
#define BMICON_MOVIE_RES_HD30P       bmIcon_Dummy
#define BMICON_MOVIE_RES_HD60P       bmIcon_Dummy
#define BMICON_MOVIE_RES_FHD30P      bmIcon_Dummy
#define BMICON_MOVIE_RES_FHD60P      bmIcon_Dummy
#define BMICON_MOVIE_RES_SHD30P      bmIcon_Dummy
#define BMICON_MOVIE_RES_SHD25P      bmIcon_Dummy
#define BMICON_MOVIE_RES_SHD24P      bmIcon_Dummy
#define BMICON_MOVIE_RES_FHD24P      bmIcon_Dummy
#define BMICON_MOVIE_RES_HD24P       bmIcon_Dummy
#define BMICON_MOVIE_RES_FHD30PHDR   bmIcon_Dummy

// Image Resolution
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_VGA;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_1_2M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_2M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_3M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_5M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_8M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_12M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_14M;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ImageSize_30ML;
#define BMICON_IMAGE_RES_VGA         bmIcon_ImageSize_VGA
#define BMICON_IMAGE_RES_1_2M        bmIcon_ImageSize_1_2M
#define BMICON_IMAGE_RES_2M          bmIcon_ImageSize_2M
#define BMICON_IMAGE_RES_3M          bmIcon_ImageSize_3M
#define BMICON_IMAGE_RES_5M          bmIcon_ImageSize_5M
#define BMICON_IMAGE_RES_8M          bmIcon_ImageSize_8M
#define BMICON_IMAGE_RES_12M         bmIcon_ImageSize_12M
#define BMICON_IMAGE_RES_14M         bmIcon_ImageSize_14M
#define BMICON_IMAGE_RES_30M         bmIcon_ImageSize_30ML

// ISO Mode
#define BMICON_ISO_100               bmIcon_Dummy
#define BMICON_ISO_200               bmIcon_Dummy
#define BMICON_ISO_400               bmIcon_Dummy
#define BMICON_ISO_AUTO              bmIcon_Dummy

// EV
#define BMICON_EV_N2_0               bmIcon_Dummy
#define BMICON_EV_N1_7               bmIcon_Dummy
#define BMICON_EV_N1_3               bmIcon_Dummy
#define BMICON_EV_N1_0               bmIcon_Dummy
#define BMICON_EV_N0_7               bmIcon_Dummy
#define BMICON_EV_N0_3               bmIcon_Dummy
#define BMICON_EV_0                  bmIcon_Dummy
#define BMICON_EV_P0_3               bmIcon_Dummy
#define BMICON_EV_P0_7               bmIcon_Dummy
#define BMICON_EV_P1_0               bmIcon_Dummy
#define BMICON_EV_P1_3               bmIcon_Dummy
#define BMICON_EV_P1_7               bmIcon_Dummy
#define BMICON_EV_P2_0               bmIcon_Dummy

// Color
#define BMICON_COLOR_NATURAL         bmIcon_Dummy
#define BMICON_COLOR_VIVID           bmIcon_Dummy
#define BMICON_COLOR_PALE            bmIcon_Dummy

// Effect
#define BMICON_EFFECT_NORMAL         bmIcon_Dummy
#define BMICON_EFFECT_BEAUTY         bmIcon_Dummy
#define BMICON_EFFECT_BW             bmIcon_Dummy
#define BMICON_EFFECT_CRAYON         bmIcon_Dummy
#define BMICON_EFFECT_EMBOSS         bmIcon_Dummy
#define BMICON_EFFECT_NAGATIVE       bmIcon_Dummy
#define BMICON_EFFECT_OIL            bmIcon_Dummy
#define BMICON_EFFECT_SEPIA          bmIcon_Dummy
#define BMICON_EFFECT_SKETCH         bmIcon_Dummy

// Volume
#define BMICON_VOL_0                 bmIcon_Dummy
#define BMICON_VOL_1                 bmIcon_Dummy
#define BMICON_VOL_2                 bmIcon_Dummy
#define BMICON_VOL_3                 bmIcon_Dummy
#define BMICON_VOL_4                 bmIcon_Dummy
#define BMICON_VOL_5                 bmIcon_Dummy
#define BMICON_VOL_6                 bmIcon_Dummy
#define BMICON_VOL_7                 bmIcon_Dummy
#define BMICON_VOL_8                 bmIcon_Dummy
#define BMICON_VOL_9                 bmIcon_Dummy
#define BMICON_VOL_10                bmIcon_Dummy

// Edit File
#define BMICON_DEL_ALL               bmIcon_Dummy
#define BMICON_DEL_ONE               bmIcon_Dummy
#define BMICON_LOCK_ALL              bmIcon_Dummy
#define BMICON_LOCK_ONE              bmIcon_Dummy
#define BMICON_UNLOCK_ALL            bmIcon_Dummy
#define BMICON_UNLOCK_ONE            bmIcon_Dummy

// Media Tool
#define BMICON_FORMAT_YES            bmIcon_Dummy
#define BMICON_FORMAT_NO             bmIcon_Dummy

// Movie Power-Off Delay Time
#define BMICON_OFFTIME_0MIN          bmIcon_Dummy
#define BMICON_OFFTIME_1MIN          bmIcon_Dummy
#define BMICON_OFFTIME_2MIN          bmIcon_Dummy
#define BMICON_OFFTIME_3MIN          bmIcon_Dummy
#define BMICON_OFFTIME_5SEC          bmIcon_Dummy
#define BMICON_OFFTIME_10SEC         bmIcon_Dummy
#define BMICON_OFFTIME_30SEC         bmIcon_Dummy
#define BMICON_OFFTIME_60SEC         bmIcon_Dummy

// Movie Clip Time
#define BMICON_CLIPTIME_1MIN         bmIcon_Dummy
#define BMICON_CLIPTIME_3MIN         bmIcon_Dummy
#define BMICON_CLIPTIME_5MIN         bmIcon_Dummy
#define BMICON_CLIPTIME_10MIN        bmIcon_Dummy

// Movie/Image Quality
#define BMICON_QUALITY_HQ            bmIcon_Dummy
#define BMICON_QUALITY_SHQ           bmIcon_Dummy

// Mic Sensitivity
#define BMICON_MIC_SENS_H            bmIcon_Dummy
#define BMICON_MIC_SENS_L            bmIcon_Dummy

// Date Format
#define BMICON_DATE1_ENGLISH         bmIcon_Dummy
#define BMICON_DATE2_ENGLISH         bmIcon_Dummy
#define BMICON_DATE3_ENGLISH         bmIcon_Dummy

// TV-out Type
#define BMICON_TV_PAL                bmIcon_Dummy
#define BMICON_TV_NTSC               bmIcon_Dummy

// HDMI Resolution
#define BMICON_HDMI_1080P            bmIcon_Dummy
#define BMICON_HDMI_1080I            bmIcon_Dummy
#define BMICON_HDMI_720P             bmIcon_Dummy
#define BMICON_HDMI_480P             bmIcon_Dummy

// USB Function
#define BMICON_USB_MSDC              bmIcon_Dummy
#define BMICON_USB_PCAM              bmIcon_Dummy

// Flicker Hz
#define BMICON_FLICKER_50HZ          bmIcon_Dummy
#define BMICON_FLICKER_60HZ          bmIcon_Dummy

// Language
#define BMICON_LANG_PORTUGAL         bmIcon_Dummy
#define BMICON_LANG_TCHINESE         bmIcon_Dummy
#define BMICON_LANG_SCHINESE         bmIcon_Dummy
#define BMICON_LANG_ENGLISH          bmIcon_Dummy
#define BMICON_LANG_RUSSIA           bmIcon_Dummy
#define BMICON_LANG_SPAIN            bmIcon_Dummy
#define BMICON_LANG_POLISH           bmIcon_Dummy

// Gsensor Sensitivity
#define BMICON_GSNR_LV0              bmIcon_Dummy
#define BMICON_GSNR_LV1              bmIcon_Dummy
#define BMICON_GSNR_LV2              bmIcon_Dummy
#define BMICON_GSNR_LV3              bmIcon_Dummy
#define BMICON_GSNR_LV4              bmIcon_Dummy
#define BMICON_GSNR_LV_H             bmIcon_Dummy
#define BMICON_GSNR_LV_M             bmIcon_Dummy
#define BMICON_GSNR_LV_L             bmIcon_Dummy
#define BMICON_GSNR_POWERON_LV_H     bmIcon_Dummy
#define BMICON_GSNR_POWERON_LV_M     bmIcon_Dummy
#define BMICON_GSNR_POWERON_LV_L     bmIcon_Dummy

// Time-Zone
#define BMICON_TIMEZONE_00           bmIcon_Dummy
#define BMICON_TIMEZONE_N01          bmIcon_Dummy
#define BMICON_TIMEZONE_N02          bmIcon_Dummy
#define BMICON_TIMEZONE_N03          bmIcon_Dummy
#define BMICON_TIMEZONE_N0330        bmIcon_Dummy
#define BMICON_TIMEZONE_N04          bmIcon_Dummy
#define BMICON_TIMEZONE_N05          bmIcon_Dummy
#define BMICON_TIMEZONE_N06          bmIcon_Dummy
#define BMICON_TIMEZONE_N07          bmIcon_Dummy
#define BMICON_TIMEZONE_N08          bmIcon_Dummy
#define BMICON_TIMEZONE_N09          bmIcon_Dummy
#define BMICON_TIMEZONE_N10          bmIcon_Dummy
#define BMICON_TIMEZONE_N11          bmIcon_Dummy
#define BMICON_TIMEZONE_N12          bmIcon_Dummy
#define BMICON_TIMEZONE_P01          bmIcon_Dummy
#define BMICON_TIMEZONE_P02          bmIcon_Dummy
#define BMICON_TIMEZONE_P03          bmIcon_Dummy
#define BMICON_TIMEZONE_P0330        bmIcon_Dummy
#define BMICON_TIMEZONE_P04          bmIcon_Dummy
#define BMICON_TIMEZONE_P0430        bmIcon_Dummy
#define BMICON_TIMEZONE_P05          bmIcon_Dummy
#define BMICON_TIMEZONE_P0530        bmIcon_Dummy
#define BMICON_TIMEZONE_P0545        bmIcon_Dummy
#define BMICON_TIMEZONE_P06          bmIcon_Dummy
#define BMICON_TIMEZONE_P0630        bmIcon_Dummy
#define BMICON_TIMEZONE_P07          bmIcon_Dummy
#define BMICON_TIMEZONE_P08          bmIcon_Dummy
#define BMICON_TIMEZONE_P09          bmIcon_Dummy
#define BMICON_TIMEZONE_P0930        bmIcon_Dummy
#define BMICON_TIMEZONE_P10          bmIcon_Dummy
#define BMICON_TIMEZONE_P11          bmIcon_Dummy
#define BMICON_TIMEZONE_P12          bmIcon_Dummy
#define BMICON_TIMEZONE_P13          bmIcon_Dummy

// BootUp Mode
#define BMICON_BOOTUP_VIDEO          bmIcon_Dummy
#define BMICON_BOOTUP_DSC            bmIcon_Dummy
#define BMICON_BOOTUP_BURST          bmIcon_Dummy
#define BMICON_BOOTUP_TIMELAPSE      bmIcon_Dummy

// Confirm Option
#define BMICON_OPTION_OPEN           bmIcon_Dummy
#define BMICON_OPTION_CLOSE          bmIcon_Dummy
#define BMICON_OPTION_YES            bmIcon_Dummy
#define BMICON_OPTION_NO             bmIcon_Dummy

/* HDMI/TVout Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiStillPlay;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlayPause;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlayStop;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_FF;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_FB;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_PFF;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_PFB;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_Play;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_Pause;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiVideoPlay_Stop;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_HdmiSlideShow;

#define BMICOM_VIDEOPLAY_FF     bmIcon_HdmiVideoPlay_FF
#define BMICOM_VIDEOPLAY_FB     bmIcon_HdmiVideoPlay_FB
#define BMICOM_VIDEOPLAY_PFF    bmIcon_HdmiVideoPlay_PFF
#define BMICOM_VIDEOPLAY_PFB    bmIcon_HdmiVideoPlay_PFB
#define BMICOM_VIDEOPLAY_PLAY   bmIcon_HdmiVideoPlay_Play
#define BMICOM_VIDEOPLAY_PAUSE  bmIcon_HdmiVideoPlay_Pause
#define BMICOM_VIDEOPLAY_STOP   bmIcon_HdmiVideoPlay_Stop

/* Warning/Wait Message Icon */
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_WMSG;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Wait0;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Wait1;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Wait2;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Wait3;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Wait4;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Info;

#define BM_ICON_WMSG                bmIcon_WMSG

/* Video Record Icon */
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_VRPause;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_ProtectKey;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_ProtectKey_90;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_ProtectKeyRed;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_mutemic;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_mutemicW;
extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_Motion_Detection;

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
#define BMICOM_FILE_PROTECTKEY      bmIcon_ProtectKey
#define BMICOM_FILE_G_PROTECTKEY    bmIcon_ProtectKey
#define BMICOM_FILE_M_PROTECTKEY    bmIcon_ProtectKey
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
#define BMICOM_FILE_PROTECTKEY      bmIcon_ProtectKey
#define BMICOM_FILE_G_PROTECTKEY    bmIcon_ProtectKey
#define BMICOM_FILE_M_PROTECTKEY    bmIcon_ProtectKey//bmIcon_ProtectKey_90
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
//TBD. Need 270 deg ICON.
#define BMICOM_FILE_PROTECTKEY      bmIcon_ProtectKey
#define BMICOM_FILE_G_PROTECTKEY    bmIcon_ProtectKey
#define BMICOM_FILE_M_PROTECTKEY    bmIcon_ProtectKey
#endif

#define BMICON_MOTION_DETECTION     bmIcon_Motion_Detection

#define BMICON_MUTEMIC              bmIcon_mutemic
#define BMICON_MUTEMICW             bmIcon_mutemicW

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
/* WiFi Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi;   // connected
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi01;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi02;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi03;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_ERR;   // error
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_FAIL;  // init WIFI failed

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_IDLE;  // disconnect
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_On;    // connected
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_Streaming_On;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_Streaming_Off;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFi_Disconnect;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_WiFiNoIP;

#define BMICON_WIFI_IDLE             bmIcon_WiFi_IDLE
#define BMICON_WIFI_ON               bmIcon_WiFi_On
#define BMICON_WIFI_CONNECTED        bmIcon_WiFi
#define BMICON_WIFI_DISCONNECT       bmIcon_WiFi_Disconnect
#define BMICON_WIFI_STREAMING_1      bmIcon_WiFi01
#define BMICON_WIFI_STREAMING_2      bmIcon_WiFi02
#define BMICON_WIFI_STREAMING_3      bmIcon_WiFi03
#define BMICON_WIFI_ERROR            bmIcon_WiFi_ERR
#define BMICON_WIFI_FAIL             bmIcon_WiFi_FAIL
#define BMICON_WIFI_NO_IP            bmIcon_WiFiNoIP

#define BMICON_WIFI_STREAMING_ON     bmIcon_WiFi_Streaming_On
#define BMICON_WIFI_STREAMING_OFF    bmIcon_WiFi_Streaming_Off
#endif

/* UI Mode Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Movie;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Movie_Playback;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Still;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Still_Playback;
#define BMICON_BUTTON_MOVIE          bmIcon_Button_Movie
#define BMICON_BUTTON_MOVIE_PLAYBACK bmIcon_Button_Movie_Playback
#define BMICON_BUTTON_STILL          bmIcon_Button_Still
#define BMICON_BUTTON_STILL_PLAYBACK bmIcon_Button_Still_Playback

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Movie;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Movie_Playback;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Still;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Still_Playback;
#define BMICON_MOVIE            bmIcon_Movie
#define BMICON_MOVIE_PLAYBACK   bmIcon_Movie_Playback
#define BMICON_STILL            bmIcon_Still
#define BMICON_STILL_PLAYBACK   bmIcon_Still_Playback

/* UI Select Mode Icon */
#define BMICON_MODE_SEL_PLAYBACK     bmIcon_Dummy
#define BMICON_MODE_SEL_MENU         bmIcon_Dummy

/* Other Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Volume_Decrease;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Volume_Increase;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_USB_Connect;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_USB_Connect_2;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_GPSSigs;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Music;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_REC;

/* Digit Icon */
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_0;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_1;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_2;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_3;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_4;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_5;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_6;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_7;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_8;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Num_9;

#if (SUPPORT_TOUCH_PANEL)//Un-Used
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Zoom_In;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Zoom_In_Touch;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Zoom_Out;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Zoom_Out_Touch;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Zoom_In;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Zoom_Out;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ZoomBar;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_InternalMem;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_InternalMem_Error;
#define BMICON_INTERNALMEM           bmIcon_InternalMem
#define BMICON_INTERNALMEM_ERROR     bmIcon_InternalMem_Error

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ProtectKeyG;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ProtectKeyM;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_ProtectKeyD;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_VR_Volume_On;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_VR_Volume_Off;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Record;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Record_Touch;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Capture;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Capture_Touch;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SlideShow;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SlideShow_Next;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_SlideShow_Previous;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Right;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Menu;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Previous;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Next;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Pause;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Play;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Play_Pause;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Play_Play;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Button_Cut;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Cut;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Delete;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Protect;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Movie_Fast_Forward;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Movie_Fast_Reverse;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_VGA_60P;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_MovieSize_VGA_120P;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_QuickMenuBar_White;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_QuickMenuBar_Yellow;

extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Thumbnail;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_W_Stabilization;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_Warning;
#else
#define BMICON_INTERNALMEM           bmIcon_Dummy
#define BMICON_INTERNALMEM_ERROR     bmIcon_Dummy

#endif

#define BMICON_MTD_H                 bmIcon_Dummy
#define BMICON_MTD_M                 bmIcon_Dummy
#define BMICON_MTD_L                 bmIcon_Dummy

#if defined(OSD_SHOW_GPS_STATUS_ICON) && OSD_SHOW_GPS_STATUS_ICON
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_GPS_Active;
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_GPS_Deactive;

#define BMICON_GPS_ACTIVE            bmIcon_GPS_Active
#define BMICON_GPS_DEACTIVE          bmIcon_GPS_Deactive
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmDamageVideoFile;
#define BMICOM_FILE_DAMAGE          bmDamageVideoFile

extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_HDR;
#define BMICOM_HDR_ON               bmIcon_HDR
//extern GUI_CONST_STORAGE GUI_BITMAP bmIcon_HDR_OFF;
//#define BMICOM_HDR_OFF              bmIcon_HDR_OFF

/*carback Icon*/
extern GUI_CONST_STORAGE GUI_BITMAP bmreverse_line;
#define BMPICON_Reverse_LINE        bmreverse_line;

#endif//_ICON_DEFINE_H_
