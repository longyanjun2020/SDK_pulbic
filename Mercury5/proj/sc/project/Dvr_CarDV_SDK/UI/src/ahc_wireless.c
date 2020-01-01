/** @file AHC_Wireless.c
 *
 */
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/
#include "MenuSetting.h"
#include "ahc_message.h"
#include "ahc_hdmi.h"
//#include "ahc_menu.h"
#include "ahc_wireless.h"
//#include "ahc_general.h"
#include "ahc_stream.h"
#include "ahc_sensor.h"
#include "ahc_uf.h" //switch UI mode
#include "ahc_utility.h"
#include "netapp.h"
#include "net_utility.h"
#include "amn_sysobjs.h"

#include "wlan.h"

#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "statevideofunc.h" //switch UI mode

#include "ledcontrol.h"
#include "aitu_ringbuf.h"
#include "ait_utility.h"

/*===========================================================================
 * Global variables
 *===========================================================================*/

#if 0
void ____CGI_Menu_Struct_____(){ruturn;} //dummy
#endif

/*  snippet:[CGI for CGI_MENU_UI_STATE]
    cgi-bin/Config.cgi?action=set&property=UIMode&value=[VIDEO|CAMERA|BURST|TIMELAPSE|SETTING|PLAYBACK|UPDATEFW]
    [CGI for CGI_MENU_UI_STATE]*/
/** @brief Available UI States for CGI
 *
 *  Need to sync with ahc_menu.h\n
 *  See the following initial values for this project.*/
CGI_MENU_MAP CGI_MENU_UI_STATE[] = {
    {"VIDEO",     UI_VIDEO_STATE},
    {"CAMERA",    UI_CAMERA_STATE},
    {"BROWSER",   UI_BROWSER_STATE},
    //{"BURST",   UI_CAMERA_BURST_STATE},
    //{"TIMELAPSE", UI_TIME_LAPSE_STATE},
    //{"SETTING",     UI_CAMERA_SETTINGS_STATE},
    {"PLAYBACK",  UI_NET_PLAYBACK_STATE},
    {"UPDATEFW",  UI_NET_FWUPDATE_STATE},
    {"SD_UPDATE", UI_SD_UPDATE_STATE},
    {NULL, 0}
};

/*  snippet:[CGI for CGI_MENU_VIDEO_RES]
    cgi-bin/Config.cgi?action=set&property=VideoRes&value=[4K15|2.7K30|1080P60|1080P50|720P120|720P100]
    [CGI for CGI_MENU_VIDEO_RES]*/
/** @brief Available Video Resolution for CGI
 *
 *  See the following initial values for this project.
 *  @deprecated "*fps", such as "720P30fps" is for APP backward-compatibility.
 *  Those are no longer needed if only latest version of APP is used.
 *  @showinitializer*/
CGI_MENU_MAP CGI_MENU_VIDEO_RES[] = {
#if defined(MENU_MOVIE_SIZE_4K_15P_EN) && (MENU_MOVIE_SIZE_4K_15P_EN)
    {"4K15",        MOVIE_SIZE_4K_15P},
#endif
#if defined(MENU_MOVIE_SIZE_4K_12d5P_EN) && (MENU_MOVIE_SIZE_4K_12d5P_EN)
    {"4K12.5",      MOVIE_SIZE_4K_12d5P},
#endif
#if defined(MENU_MOVIE_SIZE_2d7K_30P_EN) && (MENU_MOVIE_SIZE_2d7K_30P_EN)
    {"2.7K30",      MOVIE_SIZE_2d7K_30P},
#endif
#if defined(MENU_MOVIE_SIZE_2d7K_25P_EN) && (MENU_MOVIE_SIZE_2d7K_25P_EN)
    {"2.7K25",      MOVIE_SIZE_2d7K_25P},
#endif
#if (defined (MENU_MOVIE_SIZE_1080P_30_HDR_EN) && (MENU_MOVIE_SIZE_1080P_30_HDR_EN)) || \
    (defined (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN) && (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN))
    {"1080P30HDR", MOVIE_SIZE_1080_30P_HDR},
#endif
#if defined(MENU_MOVIE_SIZE_SHD_30P_EN) && (MENU_MOVIE_SIZE_SHD_30P_EN)
    {"1296P30",     MOVIE_SIZE_SHD_30P},
#endif
#if defined(MENU_MOVIE_SIZE_SHD_25P_EN) && (MENU_MOVIE_SIZE_SHD_25P_EN)
    {"1296P25",     MOVIE_SIZE_SHD_25P},
#endif
#if defined(MENU_MOVIE_SIZE_SHD_24P_EN) && (MENU_MOVIE_SIZE_SHD_24P_EN)
    {"1296P24",     MOVIE_SIZE_SHD_24P},
#endif
#if defined(MENU_MOVIE_SIZE_1080_60P_EN) && (MENU_MOVIE_SIZE_1080_60P_EN)
    {"1080P60",     MOVIE_SIZE_1080_60P},
#endif
#if defined(MENU_MOVIE_SIZE_1080_50P_EN) && (MENU_MOVIE_SIZE_1080_50P_EN)
    {"1080P50",     MOVIE_SIZE_1080_50P},
#endif
#if defined(MENU_MOVIE_SIZE_1080P_EN) && (MENU_MOVIE_SIZE_1080P_EN)
    {"1080P30",     MOVIE_SIZE_1080_30P},
    {"1080P30fps",  MOVIE_SIZE_1080_30P},   // compatible with 8427 CarDV CGI
#endif
#if defined(MENU_MOVIE_SIZE_1080_25P_EN) && (MENU_MOVIE_SIZE_1080_25P_EN)
    {"1080P25",     MOVIE_SIZE_1080_25P},
#endif
#if defined(MENU_MOVIE_SIZE_960P_30P_EN) && (MENU_MOVIE_SIZE_960P_30P_EN)
    {"960P30",  MOVIE_SIZE_960P_30P},
#endif
#if defined(MENU_MOVIE_SIZE_720_120P_EN) && (MENU_MOVIE_SIZE_720_120P_EN)
    {"720P120",     MOVIE_SIZE_720_120P},
#endif
#if defined(MENU_MOVIE_SIZE_720_100P_EN) && (MENU_MOVIE_SIZE_720_100P_EN)
    {"720P100",     MOVIE_SIZE_720_100P},
#endif
#if defined(MENU_MOVIE_SIZE_720_60P_EN) && (MENU_MOVIE_SIZE_720_60P_EN)
    {"720P60",      MOVIE_SIZE_720_60P},
    {"720P60fps",   MOVIE_SIZE_720_60P},    // compatible with 8427 CarDV CGI
#endif
#if defined(MENU_MOVIE_SIZE_720_50P_EN) && (MENU_MOVIE_SIZE_720_50P_EN)
    {"720P50",      MOVIE_SIZE_720_50P},
#endif
#if defined(MENU_MOVIE_SIZE_720P_EN) && (MENU_MOVIE_SIZE_720P_EN)
    {"720P30",      MOVIE_SIZE_720_30P},
    {"720P30fps",   MOVIE_SIZE_720_30P},    // compatible with 8427 CarDV CGI
#endif
#if defined(MENU_MOVIE_SIZE_VGA120P_EN) && (MENU_MOVIE_SIZE_VGA120P_EN)
    {"VGA120P",     MOVIE_SIZE_VGA_120P},
#endif
#if defined(MENU_MOVIE_SIZE_VGA30P_EN) && (MENU_MOVIE_SIZE_VGA30P_EN)
    {"VGA",         MOVIE_SIZE_VGA_30P},    // compatible with 8427 CarDV CGI
#endif
    {NULL, 0}
};

/*  snippet:[CGI for CGI_MENU_IMAGE_RES]
    property=Imageres&value=...
    [CGI for CGI_MENU_IMAGE_RES]*/
/** @brief Available Image Resolution for CGI
 *
 *  See the following initial values for this project.
 *  @showinitializer*/
CGI_MENU_MAP CGI_MENU_IMAGE_RES[] = {
#if defined(MENU_STILL_SIZE_14M_EN) && (MENU_STILL_SIZE_14M_EN)
    {"14MP",  IMAGE_SIZE_14M},
#endif
#if defined(MENU_STILL_SIZE_12M_EN) && (MENU_STILL_SIZE_12M_EN)
    {"12MP",  IMAGE_SIZE_12M},
#endif
#if defined(MENU_STILL_SIZE_8M_EN) && (MENU_STILL_SIZE_8M_EN)
    {"8MP",  IMAGE_SIZE_8M},
#endif
#if defined(MENU_STILL_SIZE_6M_WIDE_EN) && (MENU_STILL_SIZE_6M_WIDE_EN)
    {"6MPW", IMAGE_SIZE_6M_WIDE},
#endif
#if defined(MENU_STILL_SIZE_6M_EN) && (MENU_STILL_SIZE_6M_EN)
    {"6MP",  IMAGE_SIZE_6M},
#endif
#if defined(MENU_STILL_SIZE_5M_EN) && (MENU_STILL_SIZE_5M_EN)
    {"5MP",  IMAGE_SIZE_5M},
#endif
#if defined(MENU_STILL_SIZE_3M_EN) && (MENU_STILL_SIZE_3M_EN)
    {"3MP",  IMAGE_SIZE_3M},
#endif
#if defined(MENU_STILL_SIZE_2M_WIDE_EN) && (MENU_STILL_SIZE_2M_WIDE_EN)
    {"2MP",  IMAGE_SIZE_2M},
#endif
#if defined(MENU_STILL_SIZE_1d2M_EN) && (MENU_STILL_SIZE_1d2M_EN)
    {"1.2MP",IMAGE_SIZE_1_2M},
#endif
#if defined(MENU_STILL_SIZE_VGA_EN) && (MENU_STILL_SIZE_VGA_EN)
    {"VGA",  IMAGE_SIZE_VGA},
#endif
    {NULL, 0}
};

//Gsensor Sensitivity
CGI_MENU_MAP CGI_MENU_GSENSOR[] = {
#if defined(MENU_GENERAL_GSENSOR_OFF_EN) && (MENU_GENERAL_GSENSOR_OFF_EN)
    {"OFF", GSENSOR_SENSITIVITY_OFF},
#endif

#if defined(MENU_GENERAL_GSENSOR_LEVEL0_EN) && (MENU_GENERAL_GSENSOR_LEVEL0_EN)
    {"LEVEL0", GSENSOR_SENSITIVITY_L0},
#endif

#if defined(MENU_GENERAL_GSENSOR_LEVEL1_EN) && (MENU_GENERAL_GSENSOR_LEVEL1_EN)
    {"LEVEL1", GSENSOR_SENSITIVITY_L1},
#endif
#if defined(MENU_GENERAL_GSENSOR_LEVEL2_EN) && (MENU_GENERAL_GSENSOR_LEVEL2_EN)
    {"LEVEL2", GSENSOR_SENSITIVITY_L2},
#endif
#if defined(MENU_GENERAL_GSENSOR_LEVEL3_EN) && (MENU_GENERAL_GSENSOR_LEVEL3_EN)
    {"LEVEL3", GSENSOR_SENSITIVITY_L3},
#endif
#if defined(MENU_GENERAL_GSENSOR_LEVEL4_EN) && (MENU_GENERAL_GSENSOR_LEVEL4_EN)
    {"LEVEL4", GSENSOR_SENSITIVITY_L4},
#endif

};

CGI_MENU_MAP_ENTRY example_front_cam_menu[] = {
    0, {"1080P60",  MOVIE_SIZE_1080_60P},
    1, {"1080P50",  MOVIE_SIZE_1080_50P},
    2, {"1080P30",  MOVIE_SIZE_1080_30P},       // Allow 2 CGI strings map to the same MENU_ID
    3, {"1080P30fps",   MOVIE_SIZE_1080_30P},   // compatible with 8427 CarDV CGI
    5, {"720P30",   MOVIE_SIZE_720_30P},    // <=== 5 is an error due to copy paste. It would be found by the function
    5, {"VGA",          MOVIE_SIZE_VGA_30P},    // compatible with 8427 CarDV CGI
    6, {NULL, 0}
};

CGI_MENU_MAP_ENTRY example_rear_cam_menu[] = {
    0, {"720P30",   MOVIE_SIZE_720_30P},
    1, {"VGA",      MOVIE_SIZE_VGA_30P},
    2, {NULL, 0}
};

#define STREAMING_SIZE_360P IMAGE_SIZE_DEFAULT
#define STREAMING_SIZE_720P IMAGE_SIZE_DEFAULT
CGI_MENU_MAP_ENTRY example_streaming_res[] = {
    0, {"720P", STREAMING_SIZE_720P},//TBD, maybe something like STREAMING_SIZE_720P
    1, {"360P", STREAMING_SIZE_360P},
    2, {NULL, 0}
};


NCAM_RES_MAP example_res_master_map[] = {
    {0, "front_cam_video", example_front_cam_menu},
    {1, "rear_cam_video", example_rear_cam_menu},
    {2, "streaming", example_streaming_res},
};

NCAM_RES_COMB_ENTRY example_combination[] = {
    {0, RES_NONE, RES_NONE}, //front FHD 60, rear CAM and stream is not allowed
    {1, 0, RES_NONE}, //only another 720P@30 is allowed
    {1, RES_NONE, 0}, //only another 720P@30 is allowed
    {1, 1, 1}, //while front FHD 50, rear allows only VGA and only 360P is allowed
    {2, 0, 0},
    {2, 0, 1},
    {2, 1, 0},
    {2, 1, 1},
    {3, 0, 0},
    {3, 0, 1},
    {3, 1, 0},
    {3, 1, 1}, //have to list all combinations
    {4, 0, 0},
    {4, 0, 1},
    {4, 1, 0},
    {4, 1, 1},
    {5, 0, 0},
    {5, 0, 1},
    {5, 1, 0},
    {5, 1, 1},
    {END_OF_INDEX, END_OF_INDEX, END_OF_INDEX} //end of this big table
};
//pros: The code is easier to be programmed and it runs faster.
//cons: while a new resolution entry is added, the whole table needs to be revised/reviewed.

NCAM_RES_COMB_MAP example_comb_map = {
    DIM_OF_COMBNATION,
    example_combination,
    example_res_master_map
};

NCAM_RES_COMB_ENTRY example_combination_2[] = {
    {MOVIE_SIZE_1080_60P, RES_NONE,           RES_NONE}, //front FHD 60, rear CAM and stream is not allowed
    {MOVIE_SIZE_1080_50P, MOVIE_SIZE_720_30P, RES_NONE}, //only another 720P@30 is allowed
    {MOVIE_SIZE_1080_50P, RES_NONE,           STREAMING_SIZE_720P}, //only another 720P@30 is allowed
    {MOVIE_SIZE_1080_50P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_360P}, //while front FHD 50, rear allows only VGA and only 360P is allowed
    {MOVIE_SIZE_1080_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_1080_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_360P},
    {MOVIE_SIZE_1080_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_1080_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_360P},
    //{3, 0, 0},
    //{3, 0, 1},
    //{3, 1, 0},
    //{3, 1, 1}, //could possibly remove duplicated entries
    {MOVIE_SIZE_720_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_720_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_360P},
    {MOVIE_SIZE_720_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_720_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_360P},
    {MOVIE_SIZE_VGA_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_VGA_30P, MOVIE_SIZE_720_30P, STREAMING_SIZE_360P},
    {MOVIE_SIZE_VGA_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_720P},
    {MOVIE_SIZE_VGA_30P, MOVIE_SIZE_VGA_30P, STREAMING_SIZE_360P},
    {END_OF_INDEX, END_OF_INDEX, END_OF_INDEX} //end of this big table
};
//pros: easier for human editing. No CGI_MENU_MAP_ENTRY::idx is needed
//      More portable from project to project. It remains fixed for our solution, mostly just add and delete entries.
//cons: The code is more complex and might run slower. It is even worse if we need to parse this many times



// Video Clip Time//CarDV
CGI_MENU_MAP CGI_MENU_VIDEO_CLIP[] = {
#if defined(MENU_MOVIE_CLIP_TIME_OFF_EN) && (MENU_MOVIE_CLIP_TIME_OFF_EN == 1)
    {"OFF",   MOVIE_CLIP_TIME_OFF},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_6SEC_EN) && (MENU_MOVIE_CLIP_TIME_6SEC_EN == 1)
    {"6SEC",  MOVIE_CLIP_TIME_6SEC},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_1MIN_EN) && (MENU_MOVIE_CLIP_TIME_1MIN_EN == 1)
    {"1MIN",  MOVIE_CLIP_TIME_1MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_2MIN_EN) && (MENU_MOVIE_CLIP_TIME_2MIN_EN == 1)
    {"2MIN",  MOVIE_CLIP_TIME_2MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_3MIN_EN) && (MENU_MOVIE_CLIP_TIME_3MIN_EN == 1)
    {"3MIN",  MOVIE_CLIP_TIME_3MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_5MIN_EN) && (MENU_MOVIE_CLIP_TIME_5MIN_EN == 1)
    {"5MIN",  MOVIE_CLIP_TIME_5MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_10MIN_EN) && (MENU_MOVIE_CLIP_TIME_10MIN_EN == 1)
    {"10MIN", MOVIE_CLIP_TIME_10MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_25MIN_EN) && (MENU_MOVIE_CLIP_TIME_25MIN_EN == 1)
    {"25MIN", MOVIE_CLIP_TIME_25MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_30MIN_EN) && (MENU_MOVIE_CLIP_TIME_30MIN_EN == 1)
    {"30MIN", MOVIE_CLIP_TIME_30MIN},
#endif
    {NULL, 0}
};

// White Balance
CGI_MENU_MAP CGI_MENU_WB[] = {
#if defined(MENU_MANUAL_WB_AUTO_EN) && (MENU_MANUAL_WB_AUTO_EN)
    {"AUTO",         WB_AUTO},
#endif
#if defined(MENU_MANUAL_WB_DAYLIGHT_EN) && (MENU_MANUAL_WB_DAYLIGHT_EN)
    {"DAYLIGHT",     WB_DAYLIGHT},
#endif
#if defined(MENU_MANUAL_WB_CLOUDY_EN) && (MENU_MANUAL_WB_CLOUDY_EN)
    {"CLOUDY",       WB_CLOUDY},
#endif
#if defined(MENU_MANUAL_WB_FLUORESCENT1_EN) && (MENU_MANUAL_WB_FLUORESCENT1_EN)
    {"FLUORESCENT1", WB_FLUORESCENT1},
#endif
#if defined(MENU_MANUAL_WB_FLUORESCENT2_EN) && (MENU_MANUAL_WB_FLUORESCENT2_EN)
    {"FLUORESCENT2", WB_FLUORESCENT2},
#endif
#if defined(MENU_MANUAL_WB_FLUORESCENT3_EN) && (MENU_MANUAL_WB_FLUORESCENT3_EN)
    {"FLUORESCENT3", WB_FLUORESCENT3},
#endif
#if defined(MENU_MANUAL_WB_INCANDESCENT_EN) && (MENU_MANUAL_WB_INCANDESCENT_EN)
    {"INCANDESCENT", WB_INCANDESCENT},
#endif
    {NULL, 0}
};

// Exposure Time
CGI_MENU_MAP CGI_MENU_EXPO[] = {
#if defined(MENU_MANUAL_EV_N20_EN) && (MENU_MANUAL_EV_N20_EN)
    {"EVN200", EVVALUE_N20},
#endif
#if defined(MENU_MANUAL_EV_N17_EN) && (MENU_MANUAL_EV_N17_EN)
    {"EVN167", EVVALUE_N17},
#endif
#if defined(MENU_MANUAL_EV_N15_EN) && (MENU_MANUAL_EV_N15_EN)
    {"EVN150", EVVALUE_N15},
#endif
#if defined(MENU_MANUAL_EV_N13_EN) && (MENU_MANUAL_EV_N13_EN)
    {"EVN133", EVVALUE_N13},
#endif
#if defined(MENU_MANUAL_EV_N10_EN) && (MENU_MANUAL_EV_N10_EN)
    {"EVN100", EVVALUE_N10},
#endif
#if defined(MENU_MANUAL_EV_N07_EN) && (MENU_MANUAL_EV_N07_EN)
    {"EVN067", EVVALUE_N07},
#endif
#if defined(MENU_MANUAL_EV_N05_EN) && (MENU_MANUAL_EV_N05_EN)
    {"EVN050", EVVALUE_N05},
#endif
#if defined(MENU_MANUAL_EV_N03_EN) && (MENU_MANUAL_EV_N03_EN)
    {"EVN033", EVVALUE_N03},
#endif
    {"EV0",    EVVALUE_00},
#if defined(MENU_MANUAL_EV_P03_EN) && (MENU_MANUAL_EV_P03_EN)
    {"EVP033", EVVALUE_P03},
#endif
#if defined(MENU_MANUAL_EV_P05_EN) && (MENU_MANUAL_EV_P05_EN)
    {"EVP050", EVVALUE_P05},
#endif
#if defined(MENU_MANUAL_EV_P07_EN) && (MENU_MANUAL_EV_P07_EN)
    {"EVP067", EVVALUE_P07},
#endif
#if defined(MENU_MANUAL_EV_P10_EN) && (MENU_MANUAL_EV_P10_EN)
    {"EVP100", EVVALUE_P10},
#endif
#if defined(MENU_MANUAL_EV_P13_EN) && (MENU_MANUAL_EV_P13_EN)
    {"EVP133", EVVALUE_P13},
#endif
#if defined(MENU_MANUAL_EV_P15_EN ) && (MENU_MANUAL_EV_P15_EN)
    {"EVP150", EVVALUE_P15},
#endif
#if defined(MENU_MANUAL_EV_P17_EN) && (MENU_MANUAL_EV_P17_EN)
    {"EVP167", EVVALUE_P17},
#endif
#if defined(MENU_MANUAL_EV_P20_EN) && (MENU_MANUAL_EV_P20_EN)
    {"EVP200", EVVALUE_P20},
#endif
    {NULL, 0}
};

// Flicker
CGI_MENU_MAP CGI_MENU_FLICKER[] = {
#if defined(MENU_GENERAL_FLICKER_50HZ_EN) && (MENU_GENERAL_FLICKER_50HZ_EN)
    {"50Hz", FLICKER_50HZ},
#endif
#if defined(MENU_GENERAL_FLICKER_60HZ_EN) && (MENU_GENERAL_FLICKER_60HZ_EN)
    {"60Hz", FLICKER_60HZ},
#endif
    {NULL, 0}
};

// Motion Detection (MTD)
CGI_MENU_MAP CGI_MENU_MTD[] = {
#if defined(MENU_GENERAL_MOTION_DTC_OFF_EN) && (MENU_GENERAL_MOTION_DTC_OFF_EN)
    {"OFF",    MOTION_DTC_SENSITIVITY_OFF},
#endif
#if defined(MENU_GENERAL_MOTION_DTC_LOW_EN) && (MENU_GENERAL_MOTION_DTC_LOW_EN)
    {"LOW",    MOTION_DTC_SENSITIVITY_LOW},
#endif
#if defined(MENU_GENERAL_MOTION_DTC_MID_EN) && (MENU_GENERAL_MOTION_DTC_MID_EN)
    {"MIDDLE", MOTION_DTC_SENSITIVITY_MID},
#endif
#if defined(MENU_GENERAL_MOTION_DTC_HIGH_EN) && (MENU_GENERAL_MOTION_DTC_HIGH_EN)
    {"HIGH",   MOTION_DTC_SENSITIVITY_HIGH},
#endif
    {NULL, 0}
};

// PowerOff delay
CGI_MENU_MAP CGI_MENU_OFF_DELAY[] = {
#if defined(MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN) && (MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN)
    {"OFF",   MOVIE_POWEROFF_TIME_0MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN) && (MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN)
    {"5SEC",  MOVIE_POWEROFF_TIME_5SEC},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN) && (MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN)
    {"10SEC", MOVIE_POWEROFF_TIME_10SEC},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN) && (MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN)
    {"15SEC", MOVIE_POWEROFF_TIME_15SEC},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN) && (MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN)
    {"30SEC", MOVIE_POWEROFF_TIME_30SEC},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN)
    {"60SEC", MOVIE_POWEROFF_TIME_60SEC},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_2MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_2MIN_EN)
    {"2MIN",  MOVIE_POWEROFF_TIME_2MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_3MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_3MIN_EN)
    {"3MIN",  MOVIE_POWEROFF_TIME_3MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_5MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_5MIN_EN)
    {"5MIN",  MOVIE_POWEROFF_TIME_5MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_15MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_15MIN_EN)
    {"15MIN", MOVIE_POWEROFF_TIME_15MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_30MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_30MIN_EN)
    {"30MIN", MOVIE_POWEROFF_TIME_30MIN},
#endif
#if defined(MENU_MOVIE_POWER_OFF_DELAY_60MIN_EN) && (MENU_MOVIE_POWER_OFF_DELAY_60MIN_EN)
    {"60MIN", MOVIE_POWEROFF_TIME_60MIN},
#endif
    {NULL, 0}
};

// Video/Image Quality
CGI_MENU_MAP CGI_MENU_QUALITY[] = {
#if defined(MENU_STILL_QUALITY_FINE_EN) && (MENU_STILL_QUALITY_FINE_EN)
    {"FINE",        QUALITY_FINE},
#endif
#if defined(MENU_STILL_QUALITY_SUPER_FINE_EN) && (MENU_STILL_QUALITY_SUPER_FINE_EN)
    {"SUPERFINE",   QUALITY_SUPER_FINE},
#endif
    {NULL, 0}
};

// Time format
CGI_MENU_MAP CGI_MENU_TIME_FMT[] = {
#if defined(MENU_GENERAL_DATE_FORMAT_NONE_EN) && (MENU_GENERAL_DATE_FORMAT_NONE_EN)
    {"OFF", DATETIME_SETUP_NONE},
#endif
#if defined(MENU_GENERAL_DATE_FORMAT_YMD_EN) && (MENU_GENERAL_DATE_FORMAT_YMD_EN)
    {"YMD", DATETIME_SETUP_YMD},
#endif
#if defined(MENU_GENERAL_DATE_FORMAT_MDY_EN) && (MENU_GENERAL_DATE_FORMAT_MDY_EN)
    {"MDY", DATETIME_SETUP_MDY},
#endif
#if defined(MENU_GENERAL_DATE_FORMAT_DMY_EN) && (MENU_GENERAL_DATE_FORMAT_DMY_EN)
    {"DMY", DATETIME_SETUP_DMY},
#endif
    {NULL, 0},
};

// TV System
CGI_MENU_MAP CGI_MENU_TV_SYSTEM[] = {
#if defined(MENU_GENERAL_TV_SYSTEM_NTSC_EN) && (MENU_GENERAL_TV_SYSTEM_NTSC_EN)
    {"NTSC", TV_SYSTEM_NTSC},
#endif
#if defined(MENU_GENERAL_TV_SYSTEM_PAL_EN) && (MENU_GENERAL_TV_SYSTEM_PAL_EN)
    {"PAL",  TV_SYSTEM_PAL},
#endif
    {NULL, 0}
};

// LCD Power save
CGI_MENU_MAP CGI_MENU_LCD_POWER_SAVE[] = {
#if defined(MENU_GENERAL_LCD_POWER_SAVE_OFF_EN) && (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
    {"OFF",   LCD_POWER_SAVE_OFF},
#endif
#if defined(MENU_GENERAL_LCD_POWER_SAVE_10SEC_EN) && (MENU_GENERAL_LCD_POWER_SAVE_10SEC_EN)
    {"10SEC", LCD_POWER_SAVE_10SEC},
#endif
#if defined(MENU_GENERAL_LCD_POWER_SAVE_30SEC_EN) && (MENU_GENERAL_LCD_POWER_SAVE_30SEC_EN)
    {"30SEC", LCD_POWER_SAVE_30SEC},
#endif
#if defined(MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN) && (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
    {"1MIN",  LCD_POWER_SAVE_1MIN},
#endif
#if defined(MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN) && (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
    {"3MIN",  LCD_POWER_SAVE_3MIN},
#endif
    {NULL, 0}
};

// Photo burst
CGI_MENU_MAP CGI_MENU_PHOTO_BURST[] = {
#if defined(MENU_STILL_BURST_SHOT_LO_EN) && (MENU_STILL_BURST_SHOT_LO_EN)
    {"3_1SEC",  BURST_SHOT_LO},
#endif
#if defined(MENU_STILL_BURST_SHOT_MID_EN) && (MENU_STILL_BURST_SHOT_MID_EN)
    {"5_1SEC",  BURST_SHOT_MID},
#endif
#if defined(MENU_STILL_BURST_SHOT_HI_EN) && (MENU_STILL_BURST_SHOT_HI_EN)
    {"10_1SEC", BURST_SHOT_HI},
#endif
    {NULL, 0}
};

// Timelapse
CGI_MENU_MAP CGI_MENU_TIMELAPSE[] = {
    //{"3SEC",   TIMELAPSE_INTERVAL_3_SEC},
    {"5SEC",   TIMELAPSE_INTERVAL_5_SEC},
    {"10SEC",  TIMELAPSE_INTERVAL_10_SEC},
    {"30SEC",  TIMELAPSE_INTERVAL_30_SEC},
    {"60SEC",  TIMELAPSE_INTERVAL_60_SEC},
    {NULL, 0}
};

// Upsidedown
CGI_MENU_MAP CGI_MENU_UPSIDE_DOWN[] = {
    {"Normal",       IMAGE_UPSIDE_DOWN_NORMAL},
    {"Upsidedown",   IMAGE_UPSIDE_DOWN_UPSIDE_DOWN},
    {"Mirror",       IMAGE_UPSIDE_DOWN_MIRROR},
    {"Colrow",       IMAGE_UPSIDE_DOWN_COLROW},
    {NULL, 0}
};

// Spot Meter
CGI_MENU_MAP CGI_MENU_SPOT_METER[] = {
    {"OFF",  METERING_CENTER},
    {"ON",   METERING_CENTER_SPOT},
    {NULL, 0}
};

// Looping video//CarDV
CGI_MENU_MAP CGI_MENU_LOOPING_VIDEO[] = {
#if defined(MENU_MOVIE_CLIP_TIME_OFF_EN) && (MENU_MOVIE_CLIP_TIME_OFF_EN == 1)
    {"OFF",   MOVIE_CLIP_TIME_OFF},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_6SEC_EN) && (MENU_MOVIE_CLIP_TIME_6SEC_EN == 1)
    {"6SEC",  MOVIE_CLIP_TIME_6SEC},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_1MIN_EN) && (MENU_MOVIE_CLIP_TIME_1MIN_EN == 1)
    {"1MIN",  MOVIE_CLIP_TIME_1MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_2MIN_EN) && (MENU_MOVIE_CLIP_TIME_2MIN_EN == 1)
    {"2MIN",  MOVIE_CLIP_TIME_2MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_3MIN_EN) && (MENU_MOVIE_CLIP_TIME_3MIN_EN == 1)
    {"3MIN",  MOVIE_CLIP_TIME_3MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_5MIN_EN) && (MENU_MOVIE_CLIP_TIME_5MIN_EN == 1)
    {"5MIN",  MOVIE_CLIP_TIME_5MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_10MIN_EN) && (MENU_MOVIE_CLIP_TIME_10MIN_EN == 1)
    {"10MIN", MOVIE_CLIP_TIME_10MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_25MIN_EN) && (MENU_MOVIE_CLIP_TIME_25MIN_EN == 1)
    {"25MIN", MOVIE_CLIP_TIME_25MIN},
#endif
#if defined(MENU_MOVIE_CLIP_TIME_30MIN_EN) && (MENU_MOVIE_CLIP_TIME_30MIN_EN == 1)
    {"30MIN", MOVIE_CLIP_TIME_30MIN},
#endif
    {NULL, 0}
};

// HDR
CGI_MENU_MAP CGI_MENU_HDR[] = {
    {"OFF",  WDR_OFF},
    {"ON",   WDR_ON},
    {NULL, 0}
};

// Q-SHOT
CGI_MENU_MAP CGI_MENU_Q_SHOT[] = {
    {"OFF",  AUTO_REC_OFF},
    {"ON",   AUTO_REC_ON},
    {NULL, 0}
};

// Status lights
CGI_MENU_MAP CGI_MENU_STATUS_LIGHTS[] = {
    {"OFF",  STATUS_LIGHT_OFF},
    {"ON",   STATUS_LIGHT_ON},
    {NULL, 0}
};

// Sound Indicator
CGI_MENU_MAP CGI_MENU_SOUND_INDICATOR[] = {
#if defined(MENU_GENERAL_BEEP_OFF_EN) && (MENU_GENERAL_BEEP_OFF_EN)
    {"OFF",  BEEP_OFF},
#endif
#if defined(MENU_GENERAL_BEEP_ON_EN) && (MENU_GENERAL_BEEP_ON_EN)
    {"ON",   BEEP_ON},
#endif
    {NULL, 0}
};

// Power saving
CGI_MENU_MAP CGI_MENU_POWER_SAVING[] = {
#if defined(MENU_GENERAL_AUTO_POWEROFF_NEVER_EN) && (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
    {"OFF",  AUTO_POWER_OFF_NEVER},
#endif
#if defined(MENU_GENERAL_AUTO_POWEROFF_1MIN_EN) && (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
    {"1MIN", AUTO_POWER_OFF_1MIN},
#endif
#if defined(MENU_GENERAL_AUTO_POWEROFF_2MIN_EN) && (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
    {"2MIN", AUTO_POWER_OFF_2MINS},
#endif
#if defined(MENU_GENERAL_AUTO_POWEROFF_5MIN_EN) && (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
    {"5MIN", AUTO_POWER_OFF_5MINS},
#endif
    {NULL, 0}
};

// SD0 Card
CGI_MENU_MAP CGI_MENU_SD0[] = {
    {"format", 1},
    {NULL, 0}
};

#if SUPPORT_DLQ
#define MAX_DLQ_NUM (10)

static DFILEINFO        gFileQueueBuf[MAX_DLQ_NUM] = {0};
static AUTL_RINGBUF     gFileQueue = {0};
static AHC_BOOL         gDLQInit = AHC_FALSE;

void DLQ_InitQueue(void);
int DLQ_PopQueue(PDFILEINFO fi);
int DLQ_GetQueueSize(UINT32* uiQueueSize);
int DLQ_GetQueueItemNum(UINT32* uiQueueItemNum);
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/
#define UI_GLOBAL_WIFI_EVENT_DEMO (1)
#if UI_GLOBAL_WIFI_EVENT_DEMO
/** @brief Process Wifi Events for UI state machine

@note This is more like a global event which is independent or universal to UI state.\n
      If the handling varies too much among states, then it might be better to
      handle WIFI event in each state.

@ref UI_GLOBAL_EVENT_HANDLER for type definition
@return Return if the state machine processing can be continue. That is, the
        message is not consumed here.
*/
AHC_BOOL uiStateProcessGlobalWifiEventDemo( UINT32 ulMsgId, UINT32* pulEvent , UINT32* pulParam )
{
    AHC_BOOL    bMsgContinue = AHC_FALSE;

    switch(ulMsgId)
    {
    case AHLM_WIRELESS_CONNECT:
        switch( *pulEvent )
        {
        case WIRELESS_CONNECT_FAIL:
            //Example: Play sound, beep or change LED state
            printc(FG_YELLOW("WIRELESS_CONNECT_FAIL")"\r\n");
            AHC_PlaySoundEffectEx(AHC_SOUNDEFFECT_WIFIFAIL, AHC_MSOUND_NULL, AHC_SOUND_IMPORTANCE_MAYBELOST);
            bMsgContinue = AHC_TRUE;
            break;
        case WIRELESS_CONNECT_SUCCESS:
            //Example: Play sound, beep or change LED state
            printc(FG_YELLOW("WIRELESS_CONNECT_SUCCESS")"\r\n");
            break;
        case WIRELESS_NETWORK_READY:
            //simply consume this event and does nothing to prevent handling in each UI_STATE_ID
            break;
        default:
            bMsgContinue = AHC_TRUE;//other handler to keep processing this
            break;
        }
        break;
    default:
        bMsgContinue = AHC_TRUE;//other handler to keep processing this
        break;
    }

    return bMsgContinue;
}
#endif

AHC_BOOL uiQueryStatusInfo(QUERY_STATUS_TYPE ulCmd, void* InPara1, void* InPara2, void* OutPara)
{
    switch (ulCmd) {
    // Query if it can start wifi stream.
    case QUERY_TYPE_WIFI_STREAMABLE:
        {
            UINT8 ubCurUIState = 0;
            UI_STATE_ID ubParentUIState = 0;

            ubCurUIState = uiGetCurrentState();
            StateModeGetParent(ubCurUIState, &ubParentUIState);

            #if 0
            if(ubParentUIState != UI_STATE_UNSUPPORTED)
                ubCurUIState = ubParentUIState;
            #endif

            if (*(UINT32*)InPara1 == 0/*liveRTSP*/){

                if(ubParentUIState != UI_STATE_UNSUPPORTED){

                    return (StateModeFindState(ubCurUIState, UI_VIDEO_STATE)  ||
                            StateModeFindState(ubCurUIState, UI_CAMERA_BURST_STATE) ||
                            StateModeFindState(ubCurUIState, UI_TIME_LAPSE_STATE) ||
                            StateModeFindState(ubCurUIState, UI_CAMERA_STATE) )
                            ?  1 : 0;
                }
                else{
                    return (ubCurUIState == UI_VIDEO_STATE  ||
                            ubCurUIState == UI_CAMERA_BURST_STATE ||
                            ubCurUIState == UI_TIME_LAPSE_STATE ||
                            ubCurUIState == UI_CAMERA_STATE)
                            ?  1 : 0;
                }
            }
            else{   /*txRTSP work under PLAYBACK or SETTING UI state */

                if(ubParentUIState != UI_STATE_UNSUPPORTED){
                    return (StateModeFindState(ubCurUIState, UI_NET_PLAYBACK_STATE)  ||
                            StateModeFindState(ubCurUIState, UI_BROWSER_STATE) ||
                            StateModeFindState(ubCurUIState, UI_CAMERA_SETTINGS_STATE)) ?  1 : 0;
                }
                else{
                    return (ubCurUIState == UI_NET_PLAYBACK_STATE ||
                            ubCurUIState == UI_BROWSER_STATE      ||
                            ubCurUIState == UI_CAMERA_SETTINGS_STATE)? 1 : 0;
                }
            }
        }
        break;
    default:
        printc("\r\nNot support this command for QueryStatus");
        return AHC_FALSE;
    } // end of switch

    return AHC_TRUE;
}

int osalEv_Download(void* eventData, void* userData)
{
    struct osal_ev_download_parm *param = (struct osal_ev_download_parm*) eventData;
    //Since there is no callback or semaphore to make sure that this message is processed.
    //Furthermore, this message should only need a short processing time, thus use HP message queue.
    //for video state, STATE_VIDEO_REC_MODE_EVENT_DOWNLOAD would process this message.
    if (AHC_TRUE == AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_NET_DOWNLOAD, (UINT32)param->filename)) {
        return 0;
    }
    return -1;
}

struct ncgi_ret ncgi_send_ui_net_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg)
{
    struct ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    // Speed up WiFi event!
    // Send the WiFi message into High Priority Queue,
    // If send to normal queue by AHC_SendAHLMessage,
    // it will wait for normal messages finished like as
    // AHLM_UI_NOTIFICATION/BUTTON_UPDATE_MESSAGE, when system is busy!!
    AHC_SendAHLMessage_HP(AHLM_NET, msg, param1);

    if (pfn_wait) {
        // Wait, webwait_uiproc()
        ret.cgi = pfn_wait((void*)msg, arg);
        printc("--> COMMAND FINISH %d\n", ret.cgi);
        if (ret.cgi < 0) {
            ret.netapp = NETAPP_FAIL;
        }
    }
    return ret;
}

int osalEv_TxReport(void* eventData, void* userData)
{
    struct osal_ev_tx_rpt *rpt = (struct osal_ev_tx_rpt*) eventData;
#if 1
#define WAIT_RESULT (0)
    if (rpt && rpt->reset > OSAL_TXF_RESET) {
        if (ncam_enable_ui_streaming_mode(AHC_STREAM_NONE) < 0) {
            return -1;
        }
    }

#if WAIT_RESULT
    ncgi_op_callback(webwait_uisignal);
    if (NETAPP_DONE ==
        ncgi_send_ui_net_msg(WIRELESS_TX_REPORT,
                        (UINT32) rpt,
                        webwait_uiproc,
                        (void*)6000).netapp)
#else
    if (NETAPP_DONE ==
        ncgi_send_ui_net_msg(WIRELESS_TX_REPORT,
                        (UINT32) rpt, NULL, NULL).netapp)
#endif
    {
    #if DBG_UI_NET_EVENT
        printc(FG_GREEN(__func__ " OK")"\r\n");
    #endif
        return 0;
    }
    else{
       // printc(FG_RED(__func__ " failed")"\r\n");
    }
#else
    if (AHC_TRUE == AHC_SendAHLMessage(AHLM_NET, WIRELESS_TX_REPORT, (UINT32)rpt)) {
    #if DBG_UI_NET_EVENT
        printc("EVENT_NET_TX_REPORT(%X) is sent\r\n", WIRELESS_TX_REPORT);
    #endif
        return 0;
    }
#endif
    return -1;
}

NS_EV_RET uiBroadcastPrologue(void* eventData, void* userData)
{
    struct NS_ON_CGI_BUF_PARAM *param = (struct NS_ON_CGI_BUF_PARAM*) eventData;
    if (eventData == NULL)
        return NSE_PARAM;

    *(param->curLen) += snprintf(param->listBuf + (*(param->curLen)), param->maxlen - (*(param->curLen)),
            "BAK=bak\n");
    *(param->curLen) += snprintf(param->listBuf + (*(param->curLen)), param->maxlen - (*(param->curLen)),
            "PAK=pak\n");
    *(param->curLen) += snprintf(param->listBuf + (*(param->curLen)), param->maxlen - (*(param->curLen)),
            "TAG=tag\n");
    return NSE_OK;
}

/* @brief This function demonstrates inserting a customized list in front of standard broadcast messages.
 * @warning This function is most likely to be called from Network Task (53). Be a ware of UI Task thread-safe issue.
 */
NS_EV_RET uiBroadcastPrologueNewFiles(void* eventData, void* userData)
{
    const int MAX_FILE_LEN = 80;
    const int MAX_FILE_CNT = 30;
    struct NS_ON_CGI_BUF_PARAM *param = (struct NS_ON_CGI_BUF_PARAM*) eventData;
    int rlen;
    int rc;
    PFFINST hinst = NULL;
    FFFILTER_FN     filter;
    char sz[MAX_FILE_LEN];

    if (eventData == NULL)
        return NSE_PARAM;

    filter.arg.cam = FF_CAM_FRONT;//front cam
    filter.arg.new_file = FF_ATTR_NEW;//list only new files
    filter.arg.format = ALL_TYPE;
    filter.ffn = NULL;
#if defined(DCFDT_DB2_COMMON_FOLDER_PATH) && ( DCF_DB_COUNT >= 3)
    filter.arg.db = DCF_DB_TYPE_DB2_EVENT; //"event" folder/DCF DB. It's typically for emergency files.
#else
    filter.arg.db = DCF_DB_TYPE_DB0_NORMAL;
#endif
    AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *)"MP4,MOV,JPG,AVI");
    if ((hinst = FindFirstFile(sz, MAX_FILE_LEN, &rlen, &filter)) == NULL) {
        return NSE_OK;
    }

    rc = 1;
    do {
        *(param->curLen) += snprintf(param->listBuf + (*(param->curLen)), param->maxlen - (*(param->curLen)),
                "emerFn%d=%s\r\n", rc, sz);
        rc++;
    } while ((rc <= MAX_FILE_CNT) && FindNextFile(hinst, sz, MAX_FILE_LEN, &rlen, &filter) != 0);

    return NSE_OK;
}

/* Example Rule: Allows to dig thumbnail but forbid to rebuild a new one while recording.
 *
 * param[in] eventData as enum NS_MEDIA_TYPE. \n
 *           When input is NS_MEDIA_CMASK, it is querying if the thumbnail getting(dig embedded one) process is allowed.
 *           When input is other specified type, it is querying if the thumbnail rebuilding for the specified type
 *           is allowed.
 * retval NSE_OK If it is allowed to CREATE thumbnail.
 * retval NSE_ERR if it is forbidden to CREATE thumbnail.
 */
NS_EV_RET uiQueryThumbPermit(void* eventData, void* userData)
{
    //might consider calling uiQueryStatusInfo() if many others need it
    UINT8 ubCurUIState;
    enum NS_MEDIA_TYPE type = (enum NS_MEDIA_TYPE) (int)eventData;
    const int debug = 0;

    //query if thumbnail digging is allowed.
    if (type == NS_MEDIA_CMASK) {
        return NSE_OK; //allows to dig thumbnail while recording or any condition.
    }

    //query if thumbnail rebuilding is allowed.
    ubCurUIState = ncgi_get_ui_state_id();
    if (debug) {
        printc("Try to create thumbnail for type :%X in state %d.\r\n", type, ubCurUIState);
    }
    if (UI_NET_PLAYBACK_STATE == ubCurUIState) {
        return NSE_OK;//only allowed while UI_NET_PALYBACK_STATE
    }

    return NSE_ERR;
}

static UINT32 lastCgiTick = 0;

void uiRefreshLastCgiTick(void)
{
    AHC_OS_GetTime(&lastCgiTick);
}

AHC_BOOL uiIsAppTimeOut(void)
{
    UINT32 tick;
    int timeOut, result;
    result = ncfg_get(NCFG_APP_TIMEOUT, &timeOut);
    if (result >= 0 && timeOut > 0) {
        //timeOut = 0; //not available seconds default value for APP CGI time out
        AHC_OS_GetTime(&tick);
        if ((tick - lastCgiTick) > timeOut) {
            return AHC_TRUE;
        }
    }
    return AHC_FALSE;
}

//List and remove entries from DCF
static NS_EV_RET uiListEmerFiles(struct NS_ON_CGI_BUF_PARAM *cgi_buf)
{
    const int MAX_FILE_LEN = 80;
    const int MAX_FILE_CNT = 30;
    int rlen;
    int rc;
    PFFINST hinst = NULL;
    FFFILTER_FN     filter;
    char sz[MAX_FILE_LEN];

    filter.arg.cam = FF_CAM_FRONT;//front cam
    filter.arg.new_file = FF_ATTR_NEW;//list only new files
    //filter.arg.new_file = FF_ATTR_ANY;//list every files
    filter.arg.format = ALL_TYPE;
    filter.ffn = NULL;
#if defined(DCFDT_DB2_COMMON_FOLDER_PATH) && ( DCF_DB_COUNT >= 3)
    filter.arg.db = DCF_DB_TYPE_DB2_EVENT; //"event" folder/DCF DB. It's typically for emergency files.
#else
    filter.arg.db = DCF_DB_TYPE_DB0_NORMAL;
#endif
    AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *)"MP4,MOV,JPG,AVI");
    if ((hinst = FindFirstFile(sz, MAX_FILE_LEN, &rlen, &filter)) == NULL) {
        return NSE_ERR;
    }

    rc = 1;
    do {
        *(cgi_buf->curLen) += snprintf(cgi_buf->listBuf + (*(cgi_buf->curLen)), cgi_buf->maxlen - (*(cgi_buf->curLen)),
                "emerFn%d=%s\r\n", rc, sz);
        //clear new file bit
        {
            char szDirName[48] = {0};
            char szFileName[48] = {0};

            if (GetPathDirStr(szDirName, sizeof(szDirName), sz) &&
                GetPathFileNameStr(szFileName, sizeof(szFileName), sz))
            {
                //printd("clear:%s / %s \r\n", szDirName, szFileName);
                AHC_UF_FileOperation((UINT8*)szDirName, (UINT8*)szFileName, DCF_FILE_NONDOWNLOAD, NULL, NULL);
            }
        }
        rc++;
    } while ((rc <= MAX_FILE_CNT) && FindNextFile(hinst, sz, MAX_FILE_LEN, &rlen, &filter) != 0);
    return NSE_OK;
}

#if SUPPORT_DLQ
//List and remove entries from the queue
static NS_EV_RET uiListDLQ(struct NS_ON_CGI_BUF_PARAM *cgi_buf)
{
    UINT32 uiQueueSize = 0;
    DFILEINFO fi = {0};
    char szDirName[32] = {0};
    char szFileName[32] = {0};
    int rc;

    if (DLQ_GetQueueItemNum(&uiQueueSize) == 0 && uiQueueSize)
    {
        rc = 1;
        while (uiQueueSize--)
        {
            DLQ_PopQueue(&fi);
            *(cgi_buf->curLen) += snprintf(cgi_buf->listBuf + (*(cgi_buf->curLen)),
                    cgi_buf->maxlen - (*(cgi_buf->curLen)), "dlFn%d=%s\r\n", rc, fi.szFilePath);
            if (GetPathDirStr(szDirName, sizeof(szDirName), fi.szFilePath) &&
                GetPathFileNameStr(szFileName, sizeof(szFileName), fi.szFilePath))
            {
                printd("clear queue:%s / %s \r\n", szDirName, szFileName);
                AHC_UF_FileOperation((UINT8*)szDirName, (UINT8*)szFileName, DCF_FILE_NONDOWNLOAD, NULL, NULL);
            }
            rc++;
        }
        return NSE_OK;
    }
    return NSE_ERR;
}
#else
#define uiListDLQ(cgi_buf) (NSE_OK)
#endif

/* @brief This function is a call back of Get status CGI.
 * This CGI is designed for heart beat and CGI feature
 * @warning This function is most likely to be called from Network Task (53). Be a ware of UI Task thread-safe issue.
 */
NS_EV_RET uiQueryStatus(void* eventData, void* userData)
{
#if SUPPORT_DLQ == 0
    struct NS_ON_CGI_BUF_PARAM *param = (struct NS_ON_CGI_BUF_PARAM*) eventData;
#endif

    //Update CGI time
    AHC_OS_GetTime(&lastCgiTick);

    if (eventData == NULL)
        return NSE_PARAM;

#if SUPPORT_DLQ == 0
    (void)uiListEmerFiles(param); //ignores the return and always goes the next
    (void)uiListDLQ(param);
#endif
    return NSE_OK;
}

/* @brief This function is a call back of Get status CGI.
 * It demonstrates how CGI response string is appended.
 * This CGI is designed for heart beat and CGI feature
 * @warning This function is most likely to be called from Network Task (53). Be a ware of UI Task thread-safe issue.
 */
NS_EV_RET uiQueryStatusSimpleDemo(void* eventData, void* userData)
{
    struct NS_ON_CGI_BUF_PARAM *cb = (struct NS_ON_CGI_BUF_PARAM *) eventData;

    *cb->curLen += snprintf(cb->listBuf + *cb->curLen, cb->maxlen, "%s\n%s", "I have a pen.", "I have an apple.\n");
    printd(BG_GREEN("uiQueryStatus")"\r\n");
    return NSE_OK;
}

NS_EV_RET uiBroadcastList(void* eventData, void* userData)
{
    struct NS_ON_CGI_BUF_PARAM cgi;
    const int BROADCAST_BUFFER_CHUNK = 64*1024;
    int len = 0;
    notify_reason_t* notify;

    cgi.listBuf = osal_malloc(BROADCAST_BUFFER_CHUNK);
    if (cgi.listBuf == NULL) {
        return NSE_ERR;
    }

    cgi.curLen = &len;
    cgi.maxlen = BROADCAST_BUFFER_CHUNK;

    (void)uiListEmerFiles(&cgi); //ignores the return and always goes the next
    (void)uiListDLQ(&cgi);

    notify = ncgi_notify_uiroll(NOTIFY_CUSTOMIZE, cgi.listBuf);
    if (notify == NULL) {
        osal_free(cgi.listBuf);
        return NSE_ERR;
    }
    ncgi_notify_set_len(notify, len);
    if (ncgi_notify_uichange(notify) != 0) {
        return NSE_ERR;
    }
    return 0;
}


AHC_BOOL uiRegisterNetworkCallback(void)
{
    osal_set_ev_handler(OSAL_EV_DOWNLOAD, osalEv_Download, NULL);
    osal_set_ev_handler(OSAL_EV_TX_REPORT, osalEv_TxReport, NULL);
    ns_set_ev_handler(NS_EVENT_BROADCAST_PROLOGUE, uiBroadcastPrologueNewFiles, NULL);
    ns_set_ev_handler(NS_EVENT_QUERY_THUMB_STATE, uiQueryThumbPermit, NULL);
    ns_set_ev_handler(NS_EVENT_GET_STATUS, uiQueryStatus, NULL);
    ns_set_ev_handler(NS_EVENT_BROADCAST, uiBroadcastList, NULL);
#if UI_GLOBAL_WIFI_EVENT_DEMO
    uiStateRegisterGlobalNetEventHandler(uiStateProcessGlobalWifiEventDemo);
#endif

#if SUPPORT_DLQ
    DLQ_InitQueue();
#endif
    return AHC_TRUE;
}


void WLAN_STA_CalculateChannel(UINT8* pubChannelList)
{
    void* pScanMemPtr;
    UINT32 uiScanBufLength = WLAN_SCAN_BUF_SIZE;
    WLAN_SCAN_RESULT *list;
    WLAN_BSS_INFO *bi;
    UINT32 uiChannel, i;
    uiChannel = 0;

    if(WLAN_SYS_IsStart() == AHC_FALSE)
        return;

    pScanMemPtr = mem_malloc(uiScanBufLength);

    if(pScanMemPtr == NULL){
        printc("alloc scan buffer fail\n");
    }

    list = (WLAN_SCAN_RESULT*)pScanMemPtr;

    if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
        printc("wlan_scan_netwrok: failed\n");

    if (list->count > 0) {

        bi = list->bss_info;

        //Calculate interfered channels
        printd("Scan Channels: [ch,RSSI]\r\n");
        for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {

            UINT32 uiDelta,Weight;
            UINT32 j;

            Weight = 1;
            uiChannel = WLAN_CHSPEC_CHANNEL(bi->chanspec);
            //printc("Current Channel : %d RSSI %d\n", WLAN_CHSPEC_CHANNEL(bi->chanspec),bi->RSSI);
            printd(" [%2d,%4d] ", WLAN_CHSPEC_CHANNEL(bi->chanspec),bi->RSSI);
            if ((i & 3) == 3) {
                printd("\r\n");
            }

            //If RSSI of the channel <= -65, we ignore it!
            if(bi->RSSI <= -65)
                continue;
            //If RSSI of the channel is great than -50,we increase the Weight !
            else if(bi->RSSI > -50)
                Weight ++;

            //previous 2 channels
            uiDelta = uiChannel - WLAN_CHANNEL_1;
            uiDelta = (uiDelta > 2) ? 2 : uiDelta;

            for(j = 1; j <= uiDelta; j++){
                pubChannelList[uiChannel - j] += (Weight * 2 / j);
                //printc("Previous Channel : %d : %d \n", uiChannel - j, uiDelta);
            }

            //behind 2 channels and current
            uiDelta = WLAN_CHANNEL_13 - uiChannel;
            uiDelta = (uiDelta > 2) ? 2 : uiDelta;

            for(j = uiChannel; j < (uiChannel + uiDelta + 1); j++){
                pubChannelList[j] += (Weight * 4 / (j - uiChannel + 1));
                //printc("Behind Channel : %d : %d \n", j, uiDelta);
            }
        }
        printd("\r\n");

        //To avoid using channel 11,because the EVM of channel 11 is always not good!
        pubChannelList[WLAN_CHANNEL_11]+=4;
        pubChannelList[WLAN_CHANNEL_12]+=8;
        pubChannelList[WLAN_CHANNEL_13]+=4;

    }

    mem_free(pScanMemPtr);

}

void WLAN_STA_AutoSelectChannel(UINT32* puiChannel)
{
    UINT32 i;
    UINT8  ubChannelList[WLAN_CHANNEL_13 + 1];
    UINT32 uiMaxSum = 0xFFFFFFFF;
    UINT32 uiChannelIndex = 0;

    if(WLAN_SYS_IsStart() == AHC_FALSE)
        return;

    for(i = WLAN_CHANNEL_1; i < (WLAN_CHANNEL_13+1); i++){
        ubChannelList[i] = 0;
    }

    WLAN_STA_CalculateChannel(ubChannelList);

    #if 1
    printc("Channel Sum:");
    for(i = WLAN_CHANNEL_1; i < (WLAN_CHANNEL_13+1); i++){
        if (i % 5 == WLAN_CHANNEL_1) {
            printd("\r\n%2d: ", i);
        }
        printd(" %2d ", ubChannelList[i]);
        //printc("Channel[%d] Sum : %d \n", i,ubChannelList[i]);
    }
    printc("\r\n");
    #endif

    #if(1)
    for(i = WLAN_CHANNEL_1; i < (WLAN_CHANNEL_11 + 1); i++){

        if(ubChannelList[i] < uiMaxSum){
            uiChannelIndex = i;
            uiMaxSum = ubChannelList[i];
        }

    }
    #else
    for(i = WLAN_CHANNEL_1; i < (WLAN_CHANNEL_9 + 1); i++){
        UINT32 uiSum = 0;
        uiSum  += (ubChannelList[i] + ubChannelList[i+1] +
                  ubChannelList[i+2] + ubChannelList[i+3] + ubChannelList[i+4]);

        if(uiSum <= uiMaxSum){
            uiChannelIndex = i + 2;
            uiMaxSum = uiSum;
        }
    }
    #endif

    if((uiChannelIndex >= WLAN_CHANNEL_1) && (uiChannelIndex <= WLAN_CHANNEL_13))
        *puiChannel = uiChannelIndex;
    else{
        *puiChannel = WLAN_CHANNEL_11;
    }
}


#if SUPPORT_DLQ
#define GetCurReadPtr(ring)     ring.ptr.rd
#define GetCurWritePtr(ring)    ring.ptr.wr

void DLQ_InitQueue(void)
{
    if (gDLQInit == AHC_FALSE)
    {
        AUTL_RingBuf_Init(&gFileQueue, &gFileQueueBuf[0], MAX_DLQ_NUM);
        gDLQInit = AHC_TRUE;
    }
}

int DLQ_PushQueue(PDFILEINFO fi)
{
    /* Discard last one if queue full. */

    PDFILEINFO  fw = NULL;

    if (fi == NULL || gDLQInit == AHC_FALSE)
        return (-1);

    fw = &gFileQueueBuf[GetCurWritePtr(gFileQueue)];

    MEMCPY(fw, fi, sizeof(DFILEINFO));

    AUTL_RingBuf_CommitWrite(&gFileQueue, 1);

    if (AUTL_RingBuf_Full(&gFileQueue))
    {
        AUTL_RingBuf_CommitRead(&gFileQueue, 1);
        return (1);
    }
    else
    {
        return (0);
    }
}

int DLQ_PopQueue(PDFILEINFO fi)
{
    DFILEINFO * fr = NULL;

    if (fi == NULL || gDLQInit == AHC_FALSE)
        return (-1);

    fr = &gFileQueueBuf[GetCurReadPtr(gFileQueue)];

    if (AUTL_RingBuf_Empty(&gFileQueue))
    {
        return (1);
    }
    else
    {
        AUTL_RingBuf_CommitRead(&gFileQueue, 1);
        MEMCPY(fi, fr, sizeof(DFILEINFO));
        return (0);
    }
}

int DLQ_GetQueueSize(UINT32* uiQueueSize)
{
    if (gDLQInit == AHC_FALSE)
        return (-1);

    *uiQueueSize = gFileQueue.size;
    return (0);
}

int DLQ_GetQueueItemNum(UINT32* uiQueueItemNum)
{
    if (gDLQInit == AHC_FALSE)
        return (-1);

    if (AUTL_RingBuf_DataAvailable(&gFileQueue, uiQueueItemNum) != RINGBUF_SUCCESS)
        return (-1);

    return (0);
}

int DLQ_FindQueueItem(PDFILEINFO fi)
{
    AUTL_RINGBUF tempQueue = {0};
    PDFILEINFO fc = NULL;

    if (fi == NULL || gDLQInit == AHC_FALSE)
        return (-1);

    AUTL_RingBuf_Fork(&gFileQueue, &tempQueue);

    while (AUTL_RingBuf_Empty(&tempQueue) == MMP_FALSE)
    {
        fc = &gFileQueueBuf[GetCurReadPtr(tempQueue)];
        if (MEMCMP(fc, fi, sizeof(DFILEINFO)) == 0)
        {
            return (0);
        }
        AUTL_RingBuf_CommitRead(&tempQueue, 1);
    }
    return (1);
}
#endif

/// @}
#endif

