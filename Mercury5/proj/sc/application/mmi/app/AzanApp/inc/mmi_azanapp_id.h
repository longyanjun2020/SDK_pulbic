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
* @file    mmi_id.h
* @version
* @brief   Azan applet ID header file
*
*/
#ifndef __MMIAPP_ID_H__
#define __MMIAPP_ID_H__



/*=============================================================*/
// Include files
/*=============================================================*/
typedef enum
{
	AZAN_WND_ALARTIME = WND_ID_APP_BASE,
    AZAN_WND_MAIN,
    AZAN_WND_SET_COUNTRY_LOCATION,
    AZAN_WND_EDIT_LOCATION,
    AZAN_WND_SET_STATE_LOCATION,
    AZAN_WND_SET_CITY_LOCATION,
    AZAN_WND_EDIT_LOCATION_TITLE,
    AZAN_WND_EDIT_TITLE_OPTION,
    AZAN_WND_TIME_ZONE,
	AZAN_WND_OPTION,
	AZAN_WND_QIBLAT_DIRECTION,
    AZAN_WND_PLAY_SOUND,
    AZAN_WND_SETCALMETHOD,
}AZANWNDId_e;

typedef enum
{
    AZAN_WDG_FAJR_TEXT = APP_WDG_START,
    AZAN_WDG_SYURUK_TEXT,
    AZAN_WDG_ZUHR_TEXT,
    AZAN_WDG_ASR_TEXT,
    AZAN_WDG_MAGHRIB_TEXT,
    AZAN_WDG_ISHA_TEXT,
    AZAN_WDG_FAJR_TIME_TEXT,
    AZAN_WDG_SYURUK_TIME_TEXT,
    AZAN_WDG_ZUHR_TIME_TEXT,
    AZAN_WDG_ASR_TIME_TEXT,
    AZAN_WDG_MAGHRIB_TIME_TEXT,
    AZAN_WDG_ISHA_TIME_TEXT,
    AZAN_WDG_LOCATION_TEXT,
    AZAN_WDG_MFL_LOCATION, 
    AZAN_WDG_MFL_NAME,
    AZAN_WDG_MFL_TIME,
}AZANMainMenuWdgId_e;

typedef enum
{    
   
    AZAN_MNU_EGYPTION = 0,
    AZAN_MNU_UNIVERSITY,
    AZAN_MNU_SCIENCE,
    AZAN_MNU_UMM_AI_QURA,
    AZAN_MNU_ISNA_NORTH_AMERICA,
} AZANCalMethodMenuId_e;

typedef enum
{
    AZAN_OPTION_VIEW_MFLCONTAINER = APP_WDG_START,
    AZAN_OPTION_VIEW_SCROLLBARWIDGET,
    AZAN_SET_LOCATION_DOUBLETEXTWIDGET,
    AZAN_SET_STATUS_TEXTPICKWIDGET,
    AZAN_QIBLAT_DIRECTION_DOUBLETEXTWIDGET,
    AZAN_PLAY_SOUND_DOUBLETEXTWIDGET,
    AZAN_SET_CAL_METHOD_DOUBLETEXTWIDGET,
    AZAN_SET_DST_TEXTPICKWIDGET,
}AZANOptionView_e;

typedef enum
{
    AZAN_EDIT_LOCATION_VIEW_MFLCONTAINER = APP_WDG_START,
    AZAN_EDIT_LOCATION_VIEW_SCROLLBARWIDGET,
    AZAN_EDIT_LOCATION_TITLE_DOUBLETEXTWIDGET,
    AZAN_EDIT_LOCATION_LATITUDE_DOUBLETEXTWIDGET,
    AZAN_EDIT_LOCATION_LONGITUDE_DOUBLETEXTWIDGET,
    AZAN_EDIT_LOCATION_TIME_ZONE_DOUBLETEXTWIDGET, 
}AZANEditLocationView_e;
 
#endif /* __MMIAPP_ID_H__ */

