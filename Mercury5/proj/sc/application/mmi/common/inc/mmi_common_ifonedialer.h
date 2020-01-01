////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (?°ÏMStar Confidential Information?°ß) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __UI_STYLE_MMI_IFONE__
#include "mmi_common_vtm.h"
typedef struct
{
    u32 nTabidx;
    IWidget *pTabWdg;
} DialerWndLaunchVoiceMailData_t;

typedef enum
{
    DIALER_TAB_WDGITEM = 0,
    DIALER_TAB_WDGITEM_BACK = DIALER_TAB_WDGITEM,
    DIALER_TAB_WDGITEM_CALLOG,
    DIALER_TAB_WDGITEM_PHB,
    DIALER_TAB_WDGITEM_DIALER,
    DIALER_TAB_WDGITEM_VOICEMAIL,
    DIALER_TAB_WDGITEM_NUM,
} eDialerTabWdgItem;

#define DIALER_TAB_WDG 100
#define DIALER_WND_VOICEMAIL 100

IWidget* DialerTabWdgCreateForWnd
(
    HWIN             hWin,
    Pos_t                  *pPos,
    WidgetSize_t            *pSize,
    void                        *pCusHandle,
    u32                     nFoucsItem
);

#endif


