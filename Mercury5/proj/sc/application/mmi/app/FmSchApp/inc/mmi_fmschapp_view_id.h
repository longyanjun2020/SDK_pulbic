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

#ifndef _MMI_FMSCHAPP_VIEW_ID_H_
#define _MMI_FMSCHAPP_VIEW_ID_H_

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_layout.h"
#include "mmi_view_id_range.h"
#include "mae_menulabel.h"
#include "mmi_mae_menumodel.h"
//#include "mae_menuwidget.h"
//#include "mae_listwidget.h"
//#include "mae_textwidget.h"
//#include "mae_scrollbarwidget.h"
//#include "mae_imagetextwidget.h"
#include "mmi_common_thmid.h"
#include "mmi_common_transition.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
/* View ID start */
    IDV_ALARMAPP_ALARMLIST_VIEW = MMI_VIEW_ID_AP_BEGIN,
    IDV_ALARMAPP_SETALARM_VIEW,
    IDV_ALARMAPP_SETTITLE_VIEW,
    IDV_ALARMAPP_SETSTATUS_VIEW,
    IDV_ALARMAPP_SETFREQUENCY_VIEW,
    IDV_ALARMAPP_VIEWALARM_VIEW,
/* View ID end */
};

enum
{
/* Widget ID start */
    IDW_ALARMAPP_ALARMLIST_TITLEWIDGET = 1,
    IDW_ALARMAPP_ALARMLIST_MENUWIDGET,
    IDW_ALARMAPP_SETALARM_TITLEWIDGET,
    IDW_ALARMAPP_SETALARM_SCROLLBARWIDGET,
    IDW_ALARMAPP_SETALARM_MFLCONTAINER,
    IDW_ALARMAPP_SETALARM_TITLE_DOUBLETEXTWIDGET,
    IDW_ALARMAPP_SETALARM_TIME_TEXTTIMEWIDGET,
    IDW_ALARMAPP_SETALARM_STATUS_TEXTPICKWIDGET,
    IDW_ALARMAPP_SETALARM_FREQUENCY_DOUBLETEXTWIDGET,
    IDW_ALARMAPP_SETALARM_RINGTONE_DOUBLETEXTWIDGET,
    IDW_ALARMAPP_SETTITLE_TITLEWIDGET,
    IDW_ALARMAPP_SETTITLE_SCROLLBARWIDGET,
    IDW_ALARMAPP_SETTITLE_INPUTWIDGET,
    IDW_ALARMAPP_SETSTATUS_TITLEWIDGET,
    IDW_ALARMAPP_SETSTATUS_MENUWIDGET,
    IDW_ALARMAPP_SETFREQUENCY_ABSCONTAINER,
    IDW_ALARMAPP_SETFREQUENCY_TITLEWIDGET,
    IDW_ALARMAPP_SETFREQUENCY_MENUWIDGET,
    IDM_ALARMAPP_SETTITLE_L1_MENUMODEL,
    IDW_ALARMAPP_VIEWALARM_TITLEWIDGET,
    IDW_ALARMAPP_VIEWALARM_SCROLLBARWIDGET,
    IDW_ALARMAPP_VIEWALARM_VIEWPORTWIDGET,
    IDW_ALARMAPP_VIEWALARM_PROPCONTAINER,
    IDW_ALARMAPP_VIEWALARM_TITLE_TEXTWIDGET,
    IDW_ALARMAPP_VIEWALARM_TIME_TEXTWIDGET,
    IDW_ALARMAPP_VIEWALARM_STATUS_TEXTWIDGET,
    IDW_ALARMAPP_VIEWALARM_FREQUENCY_TEXTWIDGET,
    IDW_ALARMAPP_VIEWALARM_RINGTONE_TEXTWIDGET,
/* Widget ID end */
};

#endif /* _MMI_FMSCHAPP_VIEW_ID_H_ */
