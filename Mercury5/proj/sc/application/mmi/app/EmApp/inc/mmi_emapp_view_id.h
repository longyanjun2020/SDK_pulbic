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
 * @file    mmi_emapp_view_id.h
 *
 @version $Id: mmi_em_view_id.h 27358 2009-04-02 08:00:09Z steve.lee $
 */

#ifndef __MMI_EMAPP_VIEW_ID_H__
#define __MMI_EMAPP_VIEW_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_view_id_range.h"
#include "mmi_wdg_scrollbar.h"
#include "mmi_wdg_handwriting.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
/* View ID start */
    VID_EM_LIST_VIEW = MMI_VIEW_ID_AP_BEGIN ,
    VID_EM_EDIT_VIEW,
    VID_EM_KEYPAD_VIEW,
    VID_EM_FM_RADIO_VIEW,
    VID_EM_TOUCH_PANEL_VIEW,
    VID_EM_ATV_VIEW,

    VID_EM_LAST
/* View ID end */
};

enum

{
/* Widget ID start */
    WID_EM_TITLEWIDGET  = 1,
    WID_EM_MENUWIDGET,
    WID_EM_PROPCONTAINER,
    WID_EM_SCROLLBARWIDGET,
    WID_EM_INPUTWIDGET,
    WID_EM_ABSCONTAINERWIDGET,
    WID_EM_MAINCONTAINER,
    WID_EM_VIEW_ONLY_INPUTWIDGET,
    WID_EM_TOUCH_PANEL_TEXTWIDGET,
    WID_EM_TOUCH_PANEL_HWWIDGET,
    WID_EM_ATV_OSDWIDGET,
    WID_EM_ATV_TF_TEXTWIDGET,
    WID_EM_ATV_TG_TEXTWIDGET,
    WID_EM_ATV_BIT2_TEXTWIDGET,
    WID_EM_ATV_CHANNEL_TEXTWIDGET,
    WID_EM_BUTTONWDG_PROPCONTAINER,
    WID_EM_SEND_KEY_BUTTONWIDGET,
    WID_EM_END_KEY_BUTTONWIDGET,

    WID_EM_LAST
/* Widget ID end */
};

#endif /* __MMI_EMAPP_VIEW_ID_H__ */
