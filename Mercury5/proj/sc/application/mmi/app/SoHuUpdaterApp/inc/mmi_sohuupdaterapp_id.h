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
* @file    mmi_sohuupdaterapp_id.h
* @version
* @brief   SoHu Updater applet private header file
*
*/

#ifndef __MMI_SOHUUPDATERAPP_ID_H__
#define __MMI_SOHUUPDATERAPP_ID_H__

#include "mmi_sohuupdaterapp_cfg.h"

typedef enum
{
    SOHU_UPDATER_WND_MAIN = WND_ID_APP_BASE,
    SOHU_UPDATER_WND_SKIN_MANAGER, 
    SOHU_UPDATER_WND_SKIN_SELECTION, 
    SOHU_UPDATER_WND_SKIN_OPTION,
    SOHU_UPDATER_WND_SKIN_DOWNLOAD,
    SOHU_UPDATER_WND_SKIN_VIEW_IMAGE,
    SOHU_UPDATER_WND_CONNECT_REMIND,
    SOHU_UPDATER_WND_LIB_UPDATE,
    SOHU_UPDATER_WND_SETTINGS,     
    SOHU_UPDATER_WND_SYS_UPDATE_SETTING,
    SOHU_UPDATER_WND_AUTO_UPDATE_SETTING,  
    SOHU_UPDATER_WND_RADIO_MENU,
    SOHU_UPDATER_WND_RADIO_MENU_FREQ
} SoHuUpdaterWndId_e;

typedef enum
{
    SOHU_UPDATER_WDG_VIEW_IMAGE = APP_WDG_START,   
    SOHU_UPDATER_WDG_MFLCONTAINER,
    SOHU_UPDATER_WDG_FREQUENCY_DOUBLETEXTWIDGET,
    SOHU_UPDATER_WDG_TIME_TEXTTIMEWIDGET,
    SOHU_UPDATER_WDG_SCROLLBARWIDGET
} SoHuUpdaterWdgId_e;

typedef enum
{
    MNU_SOHU_SKIN_MANAGER = 0,
    MNU_SOHU_LIB_UPDATE,
    MNU_SOHU_UPDATE_SETTING,
    MNU_SOHU_SKIN_SELECTION,
    MNU_SOHU_MORE_SKIN,
    MNU_SOHU_SYSTEM_UPDATE_SETTING,
    MNU_SOHU_AUTO_UPDATE_SETTING,    
    MNU_SOHU_LIB_UPDATE_HINT,
    MNU_SOHU_CONNECT_PROMPT,
    MNU_SOHU_SIM_SELECTION,
    MNU_SOHU_DATA_ACCOUNTS,
    MNU_SOHU_LIB_UPDATE_FREQUENCY,
    MNU_SOHU_LIB_UPDATE_TIME,
    MNU_SOHU_VIEW, 
    MNU_SOHU_SET, 
    MNU_SOHU_DELETE, 
} SoHuUpdaterMenuId_e;

#endif //__MMI_SOHUUPDATERAPP_ID_H__
