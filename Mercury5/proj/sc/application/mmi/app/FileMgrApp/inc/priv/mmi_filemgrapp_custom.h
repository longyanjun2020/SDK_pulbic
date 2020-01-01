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
* @file    mmi_filemgrapp_custom.h
* @version
* @brief   Calibration applet header file
*
*/

#ifndef __MMI_FILEMGRAPP_CUSTOM_H__
#define __MMI_FILEMGRAPP_CUSTOM_H__

/*-------------------------------------------------------------------------*/
/*   Compile Option                                                        */
/*-------------------------------------------------------------------------*/
#if defined(__GAME_ENGINE_EMU_MMI__)
#define __FEATURE_CPMV_EMU_ALLOWED__
#endif
//#define __FEATURE_UNSUPPORTED_FILE_CPMV__

/*-------------------------------------------------------------------------*/
/*    Definition                                                           */
/*-------------------------------------------------------------------------*/
#define FILEMGRAPP_CPMV_PROGBAR_TOTAL       100
#define FILEMGRAPP_FOLDERLEVEL_MAX          128
#define FILEMGRAPP_GET_NEXT_THUMBNAIL_TIMER 1
#ifdef __FILEMGRAPP_ID3V2_IMG__
#define FILEMGRAPP_GET_NEXT_ID3_IMG_TIMER   5
#endif
/*-------------------------------------------------------------------------*/
#endif /* __MMI_FILEMGRAPP_CUSTOM_H__ */
