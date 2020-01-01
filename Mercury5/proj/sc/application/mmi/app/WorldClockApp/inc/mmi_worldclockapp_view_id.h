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

#ifndef __MMI_WORLDCLOCKAPP_VIEW_ID_H__
#define __MMI_WORLDCLOCKAPP_VIEW_ID_H__

#include "mmi_layout.h"
#include "mmi_view_id_range.h"
#include "mmi_common_thmid.h"

enum
{
    /* View ID start */
    IDV_WORLDCLOCKAPP_MAP_VIEW = MMI_VIEW_ID_AP_BEGIN,
    /* View ID end */
};

enum
{
    /* Widget ID start */
    IDW_WORLDCLOCKAPP_MAIN_CONTAINER = 1,
    IDW_WORLDCLOCKAPP_TITLEWIDGET,
    IDW_WORLDCLOCKAPP_MAP_BG_IMAGEWIDGET,
    IDW_WORLDCLOCKAPP_LINE_IMAGEWIDGET,
    IDW_WORLDCLOCKAPP_CITY_IMAGEWIDGET,
    IDW_WORLDCLOCKAPP_CITY_TITLE_TEXTWIDGET,
    IDW_WORLDCLOCKAPP_TZ_TEXTWIDGET,
    IDW_WORLDCLOCKAPP_TIME_TEXTWIDGET,
    /* Widget ID end */
};

enum
{
    /* Model ID start */
    IDM_WORLDCLOCKAPP_MAP_OPTION_MENUMODEL_L1 = 1,
    IDM_WORLDCLOCKAPP_MAP_OPTION_MENUMODEL_L2,
    IDM_WORLDCLOCKAPP_TIMEZONE_VECTOR_MODEL,
    IDM_WORLDCLOCKAPP_CITY_VECTOR_MODEL,
    /* Model ID end */
};

#endif //__MMI_WORLDCLOCKAPP_VIEW_ID_H__
