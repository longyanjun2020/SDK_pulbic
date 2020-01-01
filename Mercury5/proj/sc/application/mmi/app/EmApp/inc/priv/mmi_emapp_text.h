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
* @file mmi_emapp_text.h
*
* @version $Id: mmi_em_text.h 27933 2009-04-09 11:49:07Z lena.lin $
*/
#ifndef __MMI_EMAPP_TEXT_H__
#define __MMI_EMAPP_TEXT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define  GET_EM_TXT_STR(_id)  EM_TXT_TABLE[((int)EM_TXT_LANG_NUM*(int)_id)+pThis->CurrentLang]

/*=============================================================*/
// Data type definition
/*=============================================================*/
//The order of enum is related with PRODUCTION_TEST_MENU_TITLE and EM_TXT_TABLE
typedef enum
{
    EM_TXT_LANG_EN = 0,
    EM_TXT_LANG_SC,
    EM_TXT_LANG_NUM
} EmAppTxtLang_e;

//The order of enum is related with EM_TXT_TABLE
typedef enum
{
    EM_TXT_NULL = 0
    ,EM_TXT_PRODUCTION_TEST

#ifdef __APP_MMI_FM_RADIO__
    ,EM_TXT_FMRADIO_RESULT
#ifdef __TOUCH_SCREEN_MMI__
    ,EM_TXT_FMRADIO_TS_RESULT
#endif
#endif

    ,EM_TXT_AUDIO_TEST_RESULT
    ,EM_TXT_BACKLIGHT_TEST_RESULT
    ,EM_TXT_SPEAKER_TEST_RESULT
    ,EM_TXT_VIBRATE_TEST_RESULT
    ,EM_TXT_PLEASE_INSERT_SD
    ,EM_TXT_RW_SD_HOTPLUG_OK
    ,EM_TXT_RW_SD_HOTPLUG_OK_1BIT
    ,EM_TXT_RW_SD_HOTPLUG_OK_4BITS
    ,EM_TXT_INSERT_SD_CONTINUING
    ,EM_TXT_RW_SD_OK_RESULT
    ,EM_TXT_RW_SD_OK_1BIT_RESULT
    ,EM_TXT_RW_SD_OK_4BITS_RESULT
    ,EM_TXT_RW_SD_FAIL_RESULT
    ,EM_TXT_RW_SD_FAIL_4BITS
    ,EM_TXT_PLEASE_INSERT_USB_CABLE
    ,EM_TXT_DETECT_USB_CABLE_PLUG_IN
    ,EM_TXT_PLEASE_INSERT_HEADSET
    ,EM_TXT_DETECT_HEADSET_RESULT

#ifdef __BLUETOOTH_MMI__
    ,EM_TXT_TRY_TO_TURN_ON_BT
    ,EM_TXT_START_INQUIRY
    ,EM_TXT_FAIL_TURN_ON_BT
    ,EM_TXT_FIND_BT_RESULT
    ,EM_TXT_BT_RECEIVE_FILE
#endif// __BLUETOOTH_MMI__

    ,EM_TXT_AUTO_TEST_SUMMARY
    ,EM_TXT_AUTO_TEST_RESULT_TITLE
    ,EM_TXT_AUTO_TEST_RESULT
    ,EM_TXT_AUTO_TEST_PROGRAM_RESULT
    ,EM_TXT_KEY_PAD_LIGHT_COLOR
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_GREEN
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_CYAN
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_BLUE
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_YELLOW
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_PURPLE
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_WHITE
    ,EM_TXT_KEY_PAD_LIGHT_COLOR_RED
    ,EM_TXT_NOT_FIND_BT_DEVICE
    ,EM_TXT_SPEAKER_TEST_FAIL
    ,EM_TXT_IDLE_TIME_TOO_LONG
    ,EM_TXT_SUCCESS
    ,EM_TXT_FAIL
    ,EM_TXT_SD_REMOVED
    ,EM_TXT_SN

#ifdef __BLUETOOTH_MMI__
    ,EM_TXT_BT_ADDRESS
#endif//__BLUETOOTH_MMI__

    ,EM_TXT_SW_VERSION

#ifdef __ATV_MMI__
    ,EM_TXT_ATV_TURN_ON_FAIL
    ,EM_TXT_ATV_SET_CONFIG_FAIL
    ,EM_TXT_ATV_PREVIEW_FAIL
    ,EM_TXT_ATV_SWITCH_CHANNEL_FAIL
    ,EM_TXT_ATV_TURN_OFF_FAIL
    ,EM_TXT_ATV_SWITCH_SHENZHEN
    ,EM_TXT_ATV_SWITCH_TAIWAN
    ,EM_TXT_ATV_SCAN_FAIL
    ,EM_TXT_ATV_SCAN_NO_CHANNEL
#endif // __ATV_MMI__

    ,EM_TXT_START_TEST

#ifdef __G_SENSOR_MMI__
    ,EM_TXT_GENSOR_NOTICE
#endif//__G_SENSOR_MMI__

#ifdef __BLUETOOTH_MMI__
    ,EM_TXT_PLEASE_OPEN_BT_DEVICE
#endif//__BLUETOOTH_MMI__

#if (defined(__TOUCH_SCREEN_MMI__) && defined(__HANDWRITING_MMI__))
    ,EM_TXT_TOUCH_PANEL_TEST_PROMPT
#endif

    ,EM_TXT_LEFT_CHANNEL
    ,EM_TXT_RIGHT_CHANNEL
    ,EM_TXT_MONO
    ,EM_TXT_PASS
    ,EM_TXT_NOT_TEST

#ifndef __EM_KEYPAD_TEST_FUN__
    ,EM_TXT_SEND_KEY
    ,EM_TXT_END_KEY
#endif//__EM_KEYPAD_TEST_FUN__

    //Add new text above
    ,EM_TXT_LAST
} EmAppTxtLabel_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
extern const MAE_WChar * const EM_TXT_TABLE[EM_TXT_LAST*EM_TXT_LANG_NUM];

//extern const MAE_WChar *PRODUCTION_TEST_MENU_TITLE[(EM_AUTO_TEST_ITEMS+1)*EM_TXT_LANG_NUM];
#endif//__MMI_EMAPP_TEXT_H__
