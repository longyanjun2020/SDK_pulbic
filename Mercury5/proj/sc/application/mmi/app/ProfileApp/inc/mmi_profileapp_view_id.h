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
 * @file    mmi_profileappview_id.h
 *
 @version $Id: mmi_profileappview_id.h 32623 2009-06-04 14:32:32Z jason.su $
 */
#ifndef __MMI_PROFILEAPPVIEW_ID_H__
#define __MMI_PROFILEAPPVIEW_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "Mmi_common_menu.h"
#include "mmi_common_cfg.h"
#include "mmi_settingapp_view_id.h"
#include "mmi_view_id_range.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/

enum
{
/* View ID start */
    VID_PROFILE_MAIN_LIST_VIEW = MMI_VIEW_ID_AP_BEGIN,
    VID_PROFILE_OPTION_VIEW,
    VID_PROFILE_EDIT_LIST_VIEW,
    VID_PROFILE_VIBRATE_TYPE_VIEW,
    VID_PROFILE_GENERIC_TONE_VIEW,
    VID_PROFILE_KEYPAD_TONE_VIEW,
    //VID_PROFILE_VOLUME_VIEW,
    //VID_PROFILE_VOICECALLS_VIEW,
    MID_PROFILE_OPTIONMENU_MENUMODEL_L1,
    MID_PROFILE_NORMAL_SILENT_MENUMODEL,
    MID_PROFILE_HEADSET_SILENT_MENUMODEL
/* View ID end */
};

enum
{
/* Widget ID start */
    WID_PROFILE_TITLEWIDGET = 1,
    WID_PROFILE_MENUWIDGET,
    WID_PROFILE_MAIN_CONTAINER
/* Widget ID end */
};

#endif /* __MMI_PROFILEAPPVIEW_ID_H__ */
