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
 * @file    mmi_calculatorplusapp_priv.h
 * @version
 * @brief   calculator plus app
 */

#ifndef __MMI_CALCULATORPLUSAPP_PRIV_H__
#define __MMI_CALCULATORPLUSAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_calculatorplusapp.h"
#include "mmi_wdg_headers.h"

#include "mmi_calculatorplusapp_id.h"
#include "calculatorplusapp_resource.h"


/*=============================================================*/
// Macro definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
	 WND_CALC_QWERTY = WND_ID_APP_BASE,
}CalcQwertyWndId_e;

typedef enum
{
	CALCQWERTY_WND_SHOW_TEXT_WDG = APP_WDG_START,
	CALCQWERTY_WND_RAD_DEG_TEXT_WDG,
	CALCQWERTY_WND_MEM_TEXT_WDG,
	CALCQWERTY_WND_IMAGE_WDG,
	CALCQWERTY_SCI_MINI_PAD_WDG,
	CALCQWERTY_WND_MISC_MENU_WDG,	
	CALCQWERTY_WND_NUM123_MENU_WDG,
	CALCQWERTY_WND_ZERO_MENU_WDG,
	CALCQWERTY_WND_POINT_MENU_WDG,
	CALCQWERTY_WND_EQUAL_MENU_WDG,
	CALCQWERTY_SCI_MINI_PAD2_WDG,
	CALCQWERTY_RAD_DEG_WND_MENU_WDG,
	CALCQWERTY_WND_SHOW_TEXT_MEM_POR_WDG,
	CALCQWERTY_WND_SHOW_TEXT_POR_WDG,
	CALCQWERTY_WND_IMAGE_POR_WDG,
	CALCQWERTY_WND_MISC_MENU_POR_WDG,	
	CALCQWERTY_WND_NUM123_MENU_POR_WDG,
	CALCQWERTY_WND_ZERO_MENU_POR_WDG,
	CALCQWERTY_WND_POINT_MENU_POR_WDG,
	CALCQWERTY_WND_EQUAL_MENU_POR_WDG,

	CALCQWERTY_WND_NULL_ID
} CalcQwertyWdgId_e;

typedef struct _CalcQetyWndData
{
	bool bStatus;
    bool bLandscapeMode;
	bool bkFlag ;
	u32 nT1,nT2;
	Point_t pointS,pointE;
} CalcQetyWndData;

typedef struct {
	APPLET_BASE_ELEMENTS;
} CalcQwertyAppData_t;

#endif /* __MMI_CALCULATORPLUSAPP_PRIV_H__ */
