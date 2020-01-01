////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file    mmi_settingapp_view_id.h
 *
 @version $Id: mmi_settingapp_view_id.h 37118 2009-08-04 09:24:07Z lena.lin $
 */

#ifndef __MMI_SETTINGAPPVIEW_ID_H__
#define __MMI_SETTINGAPPVIEW_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_view_id_range.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
// use SrvClockGetTimeRange to get max & min year
//#define TEXT_DATE_WIDGET_MAX_YEAR   2039
//#define TEXT_DATE_WIDGET_MIN_YEAR   2008

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    SET_MenuList    ,
    SET_OptionList  ,
    SET_SOption     ,
    SET_LaunchAP    ,
    SET_Info        ,
    SET_LaunchFileMgrAP ,

}SET_NEXT_FORM_TYPE_e;

enum
{
/* View ID start */
    VID_SETTING_INVALID_VIEW = MMI_VIEW_ID_AP_BEGIN ,
    VID_SETTING_NOT_CREATE_VIEW         ,

    VID_SETTING_TABLIST_MAIN_LIST_VIEW  , // TabView
    VID_SETTING_MAIN_LIST_VIEW          ,

    VID_SETTING_PHONE_SETTING_VIEW      ,
    VID_SETTING_DISPLAY_LANGUAGE_VIEW   ,
    VID_SETTING_INPUT_METHOD_VIEW       ,
    VID_SETTING_DATETIME_VIEW           ,
    VID_SETTING_TIME_ZONE_VIEW          ,
    VID_SETTING_AUTOMATIC_UPDATE_VIEW   ,
    VID_SETTING_TIME_FORMAT_VIEW            ,
    VID_SETTING_DATE_FORMAT_VIEW        ,
    VID_SETTING_POWER_ON_OFF_VIEW           ,
    VID_SETTING_AUTO_ON_OFF_VIEW        ,
    VID_SETTING_INFORMATION_VIEW        ,
    VID_SETTING_DATE_VIEW               ,
    VID_SETTING_TIME_VIEW               ,

    VID_SETTING_DISPLAY_SETTING_VIEW    ,
    VID_SETTING_IDLE_SCREEN_VIEW        ,
    VID_SETTING_SUB_PANEL_VIEW          ,
    VID_SETTING_BACLLIGHT_VIEW          ,
    VID_SETTING_BACKLIGHT_LEVEL_VIEW    ,
    VID_SETTING_BACLLIGHT_DURATION_VIEW ,
    VID_SETTING_POWER_SAVING_VIEW       ,
    VID_SETTING_SCREENSAVER_VIEW        ,
    VID_SETTING_SCREENSAVER_STYLE_VIEW  ,
    VID_SETTING_SCREENSAVER_TIMEOUT_VIEW,
    VID_SETTING_POWER_ON_VIEW           ,
    VID_SETTING_POWER_OFF_VIEW          ,
    VID_SETTING_OPERATOR_NAME_VIEW      ,
    VID_SETTING_MENU_LAYOUT_VIEW        ,
    VID_SETTING_MAIN_LAYOUT_VIEW        ,
    VID_SETTING_SUB_PANEL_LAYOUT_VIEW   ,
    VID_SETTING_LUNAR_CALENDAR_VIEW     ,
    VID_SETTING_TRANSITION_VIEW         ,

    VID_SETTING_RINGTONE_SETTING_VIEW   ,
    VID_SETTING_VOICE_CALL_VIEW         ,
    VID_SETTING_MESSAGING_VIEW          ,
    VID_SETTING_CALENDAR_VIEW           ,
    VID_SETTING_ALARM_VIEW              ,
    VID_SETTING_KEYPAD_TONE_VIEW        ,
    VID_SETTING_RING_TYPE_VIEW          ,
    VID_SETTING_VIBRATE_TYPE_VIEW       ,
    VID_SETTING_VOLUME_VIEW             ,
    VID_SETTING_AIR_PLANE_MODE_VIEW     ,
    VID_SETTING_INPUT_METHOD_RADIO_VIEW ,
    VID_SETTING_ON_OFF_VIEW             ,
    VID_SETTING_ON_OFF_BEEP_VIEW        ,
    VID_SETTING_TOUCH_DATA_TIME_VIEW    ,
    VID_SETTING_IDLE_SCREEN_SELECT_WALLPAPER_VIEW,
    VID_SETTING_TOUCH_TIME_VIEW,
    VID_SETTING_TOUCH_DATE_VIEW,
    VID_SETTING_DEFAULT_SIM_VIEW,
    VID_SETTING_STYLE_VIEW,
    VID_SETTING_GENERAL_SETTING_VIEW,
    VID_SETTING_PERSONALIZATION_SETTING_VIEW,
    VID_SETTING_LANGUAGE_SETTING_VIEW,
    VID_SETTING_WRITING_LANGUAGE_VIEW,
    VID_SETTING_CHINESE_INPUT_METHOD_VIEW,
#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__
    VID_SETTING_MAIN_MENU_ANIMATION_SETTING_VIEW,
#endif //#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__

/* View ID end */
};

enum

{
/* Widget ID start */
    WID_SETTING_TITLEWIDGET = 1,
    WID_SETTING_MENUWIDGET,
    WID_SETTING_MAIN_CONTAINER,
    WID_SETTING_MFLCONTAINER,
    WID_SETTING_PROGRESS_PROGRESSWIDGET,
    WID_SETTING_BACKLLIGHT_IMG,
    WID_SETTING_BACKLLIGHT_LEVEL_IMG,
    WID_SETTING_BOTTON_SPACE,
    WID_SETTING_TEXT_DATE_WIDGET,
    WID_SETTING_TEXT_TIME_WIDGET,
    WID_SETTING_AUTO_POWER_ON_TEXT_TIME_WIDGET,
    WID_SETTING_AUTO_POWER_OFF_TEXT_TIME_WIDGET,
    WID_SETTING_SPACE,
    WID_SETTING_VOLUME_ICON,
    WID_SETTING_VOLUME_TEXT,
    WID_SETTING_INPUT_LANGUAGE,
    WID_SETTING_DEFAULT_CHINESE_INPUT_MODE,
    WID_SETTING_SMARTINPUT_ON_OFF,
    WID_SETTING_DEFAULT_INPUT_MODE,
    WID_SETTING_MFLSCROLLBAR,
    WID_SETTING_INPUT_METHOD_RADIOVIEW_TITLEWDG,
    WID_SETTING_INPUT_METHOD_RADIOVIEW_MENUWDG,
    WID_SETTING_SOFT_KEYBOARD,
    WID_SETTING_TOUCH_DATA_TIME_MAINCONTAINER,
    WID_SETTING_TOUCH_DATA_TIME_BG_IMAGE_WIDGET,
    WID_SETTING_TOUCH_DATA_TIME_GRIDWIDGET,
    WID_SETTING_TOUCH_DATA_TIME_BUTTONWIDGET,
    WID_SETTING_TOUCH_DATA_TIME_TEXT_WIDGET,
    WID_SETTING_TOUCH_DATA_TIME__DATE_WIDGET,
    WID_SETTING_TOUCH_DATA_TIME__TIME_WIDGET,
    WID_SETTING_VOLUME_WIDGET,
    WID_SETTING_BACKLLIGHT_LEVEL_DECREASE_BUTTON_WIDGET,
    WID_SETTING_BACKLLIGHT_LEVEL_INCREASE_BUTTON_WIDGET,
    WID_SETTING_FCTIME_WIDGET,
    WID_SETTING_FCDATE_WIDGET,
    WID_SETTING_TITLE2TXT,
    WID_SETTING_BACKLIGHT_CONTAINER,

    // for Tab View
    WID_SETTING_TABWIDGET,
    WID_SETTING_PHONE_MENUWIDGET,
    WID_SETTING_CONNECT_MENUWIDGET,
/* Widget ID end */
};

#endif /* __MMI_SETTINGAPPVIEW_ID_H__ */
