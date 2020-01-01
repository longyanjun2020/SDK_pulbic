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
* @file mmi_idleapp.h
* @version
* @brief   Idle applet file 
*
*/

#ifndef __MMI_IDLEAPP_H__
#define __MMI_IDLEAPP_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"

/*-------------------------------------------------------------------------*/
#define IDLEAPP_EVENTWIDGET_COLOR COLOR_GREY_1
#define IDLEAPP_EVENTWIDGET_OUTLINE_COLOR COLOR_WHITE
#define IDLEAPP_DIALINGVIEW_COLOR MAKE_RGB(2, 187, 240)
//Put Network Widget Font Size and Type here due to when setting SPN name, the width has to be calculated at run time
#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_SIMPLE__)
#define IDLEAPP_NETWORKWIDGET_FONT_CAT FONT_CAT_SUPERSMALL
#else
#define IDLEAPP_NETWORKWIDGET_FONT_CAT FONT_CAT_NORMAL
#endif
#define IDLEAPP_NETWORKWIDGET_FONT_TYPE FONT_TYPE_OUTLINE
#define IDLEAPP_MAX_INPUT_BYTE 160 //Maximum allowable input bytes (80 characters)
//For Idle Media Name (MP3 name)
#define IDLEAPP_MEDIANAMEWIDGET_FONT_TYPE FONT_TYPE_OUTLINE
#ifdef __SMALL_ROM__
#define IDLEAPP_MEDIANAMEWIDGET_FONT_SIZE FONT_CAT_NORMAL
#else
#define IDLEAPP_MEDIANAMEWIDGET_FONT_SIZE FONT_CAT_SUPERSMALL
#endif
#define IDLEAPP_MEDIANAMEWIDGET_COLOR COLOR_GREY_5
#define IDLEAPP_MEDIANAMEWIDGET_OUTLINE_COLOR COLOR_BLACK
#define IDLEAPP_BGIMAGECOLOR COLOR_BLACK
#define WARNING_STRING_TIMEOUT 3000
/*-------------------------------------------------------------------------*/

/**
 * External Events
 */
#define IDLEAPP_EVT_RELEASE_DESKTOP_WIDGET				(CLSID_IDLEAPP << 16 | 1)



/**
 * Functions
 */

MAE_Ret IDLEAPP_New(MAE_ClsId id, void **ppObj);

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#endif /* __MMI_IDLEAPP_H__ */
