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
* @file    mmi_mainmenuapp_priv.h
* @version
* @brief   MainMenu applet private header file
*
*/
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
#ifndef __MMI_MAINMENUAPP_PRIV_H__
#define __MMI_MAINMENUAPP_PRIV_H__


/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_common_menu.h"
#include "mmi_common_wdgvar.h"
#include "mmi_srv_header.h"
#include "mmi_android_mainmenuapp.h"
#include "mmi_wdg_headers.h"
#include "mmi_android_mainmenuapp_id.h"
#include "AndroidMainmenu_resource.h"
#include "mae_animation.h"
#include "mmi_android_menuitem.h"
#include "mmi_common_color_def.h"
/*-------------------------------------------------------------------------*/

typedef struct CellItemInfo_TAG
{
    Rect_t  tPos;
    u32 u32ImageId;
    u32 u32TextId;
}CellItemInfo_t;
typedef struct {
    s32                 nViewPortOffset;
	IWidget             *pViewPortWdg;
    IWidget             *pMainContainer;
    IWidget             *pHighlightWidget;
    IWidget             *pImgBGWdg;
    IWidget             *pImgWdg;
    IWidget             *pTextWdg;
    VectorClass_t       *pIVM_Cell;
    VectorClass_t       *pIVM_TextWidget;
    VectorClass_t       *pIVM_ItemImgWidget;
    AndroidMenuItemData_t      *pMenuData;
    CellItemInfo_t      pCellItemInfo[MAIN_MENU_AP_LIST_TOTAL];
    WidgetHandler_t     tCellViewPortHandler;
    WidgetHandler_t     tCellMainHandler;
    HistoryInfo_t       stHistory;
    u32 nLastTouchIndex;
}CellWndData_t;

/**
 * Application structure
 */
typedef struct MMI_MAINMENUAPP_TAG {
	APPLET_BASE_ELEMENTS;
	u32		nEntryTransId[1];
	u32		nExitTransId[1];
#ifdef  __GADGETS_MMI__
	MainMenuStartType_e MenuAppStart;
#endif

} MMI_ANDROIDMAINMENUAPP;

#endif //__MMI_MAINMENUAPP_PRIV_H__

#endif /* __UI_STYLE_MMI_ANDROID_MAIN_MENU__ */

