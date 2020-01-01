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
* @file    mmi_stopwatchapp_view_id.h
* @version
* @brief    ID values for Stopwatch
*
*/

#ifndef __MMI_STOPWATCHAPP_VIEW_ID_H__
#define __MMI_STOPWATCHAPP_VIEW_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_view_id_range.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

enum
{
    VID_STOPWATCH_VIEW = MMI_VIEW_ID_AP_BEGIN
};

enum
{
    WID_STOPWATCH_MAINCONTAINER = 1,
    WID_STOPWATCH_TIMERCONTAINER,
    WID_STOPWATCH_TITLEWIDGET,
    //WID_STOPWATCH_MENUWIDGET,
    WID_STOPWATCH_ITEM_HEADWIDGET,
    WID_STOPWATCH_TIMERWIDGET,
    WID_STOPWATCH_COUNT_TEXTWIDGET,
    WID_STOPWATCH_SCROLLBARWIDGET,
    WID_STOPWATCH_LISTWIDGET,
    WID_STOPWATCH_ITEMWIDGET,
    WID_STOPWATCH_ITEM_TEXTWIDGET,
    WID_STOPWATCH_ITEM_TIMERWIDGET,


};

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif
