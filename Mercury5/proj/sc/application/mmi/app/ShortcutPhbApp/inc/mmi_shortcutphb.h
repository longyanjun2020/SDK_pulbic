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
* @file    mmi_shortcutphp.h
* @version $Id: mmi_shortcutphp.h  $
* @brief   shortcut Phonebook applet header file
*
*/

#ifndef __MMI_SHORTCUTPHB_H__
#define __MMI_SHORTCUTPHB_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__)
/*-------------------------------------------------------------------------*/
/*
Include
*/
#include "mmi_phbsrv.h"
#include "mmi_filemgrapp.h"
#include "mmi_launcher_phb.h"

/*
    Definitions
*/
 
#define SHORTCUT_PHB_ITEM_MAX_NUM                       (12)
#define SHORTCUT_PHB_MAX_DECODE_ITEM_NUM                (8)
#define SHORTCUT_PHB_ITEM_LOWER_TEXT_COLOR              (0xFF6C6E70) 
#define SHORTCUT_PHB_ENTER_ANIMATION_TOTAL_FRAME        (20)
#define SHORTCUT_PHB_ANIMATION_START_FRAME              (SHORTCUT_PHB_ENTER_ANIMATION_TOTAL_FRAME)
#define SHORTCUT_PHB_PAGE_ANIMATION_FRAME               (12)
#define SHORTCUT_PHB_ANIMATION_END_FRAME                (164)
#define SHORTCUT_PHB_SPIN_END_FRAME                     (214)
#define SHORTCUT_PHB_SPIN_START_FRAME                   (SHORTCUT_PHB_ANIMATION_END_FRAME + 2)
#define SHORTCUT_PHB_SPIN_DOWN_FRAME                    (6)
#define SHORTCUT_PHB_SPIN_SINGLE_STEP                   (4)
#define SHORTCUT_PHB_SPIN_UP_FRAME                      (2)
#define SHORTCUT_PHB_TOUCH_STEP_THRESHOLD               (40) //MAIN_LCD_HEIGHT / SHORTCUT_PHB_ITEM_MAX_NUM
#define SHORTCUT_PHB_DEFAULT_TIMER_VALUE                (10)
#define SHORTCUT_PHB_NO_PRESSED_BTN_INDEX               (-1)
#define SHORTCUT_PHB_BTNNAME_PREFIX                     "Item"

#define SHORTCUT_PHB_FULL_ALPHA                         (1.0f)
#define SHORTCUT_PHB_80_PERCENT_ALPHA                   (0.8f)
#define SHORTCUT_PHB_60_PERCENT_ALPHA                   (0.6f)
#define SHORTCUT_PHB_40_PERCENT_ALPHA                   (0.4f)
#define SHORTCUT_PHB_TRANSPARENT_ALPHA                  (0.0f)

/*
    Structure
*/

typedef struct
{
	MmiPhbNumber_t	atNumber[SHORTCUT_PHB_ITEM_MAX_NUM];
} MmiShortcutPhbData_t;


/**
 * Functions
 */
MAE_Ret ShortcutPhbNew(MAE_ClsId nClsId, void **ppObj);

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#endif //__3D_UI_IDLE_MULTIPAGE__
#endif /* __MMI_PHBAPP_H__ */
