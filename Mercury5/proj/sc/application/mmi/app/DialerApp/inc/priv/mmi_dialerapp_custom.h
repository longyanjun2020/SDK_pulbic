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
* @file    mmi_dialerapp_custom.h
* @version
* @brief   DialerApp customization file
*
*/

#ifndef __MMI_DIALERAPP_CUSTOM_H__
#define __MMI_DIALERAPP_CUSTOM_H__

#define DIALERAPP_TS_LONGPRESS_TIME 1500
//#define __SMART_DIALER_STROKES_SUPPORT__  //PHB didn't support now.

#ifdef __DIALERAPP_WALLPAPER_MMC_CACHE__
//#define DIALERAPP_WALLPAPER_CACHE_PATH L"fs:/CARD/Wallpaper/"
//#define DIALERAPP_WALLPAPER_CACHE_FILEPATH L"fs:/CARD/Wallpaper/%S"
//#define DIALERAPP_WALLPAPER_CACHE_FORMAT L".bmp"
//#define DIALERAPP_WALLPAPER_CACHE_MAX_FILENAME_LENGTH 57//path(20) + MD5 Hash ID to Hex String (32) + file extension (4) + terminator (1)
//#define DIALERAPP_WALLPAPER_CACHE_CRITERIA_X 2000
//#define DIALERAPP_WALLPAPER_CACHE_CRITERIA_Y 2000
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __MMI_DIALERAPP_CUSTOM_H__ */
