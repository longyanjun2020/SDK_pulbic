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
* @file    mdl_touchscreen_msg_pub.h
* @version
* @brief   MDL header file of ouch screen; message data type
*
*/

#ifndef __MDL_TOUCH_SCREEN_MSG_PUB_H__
#define __MDL_TOUCH_SCREEN_MSG_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
//#include "cus_msg.hc"
#include "vm_msgof.hc"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define TSCR_FUNC_NONE        0
#define TSCR_FUNC_CALIBRATION 1
#define TSCR_FUNC_ZOOM_IN     2
#define TSCR_FUNC_ZOOM_OUT    3
#define MAX_FINGER_NUM        6
#define MAX_FUNCTION_NUM      4
#define MAX_TOUCH_FINGER      2

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MDL_TOUCH_SCREEN_FW_UPDATE_SUCCESS,                                       ///< Firmware update successfully
    MDL_TOUCH_SCREEN_FW_UPDATE_FAIL,                                              ///< Firmware update fail
    MDL_TOUCH_SCREEN_FW_UPDATE_START,                                           ///< Firmware update start
    MDL_TOUCH_SCREEN_FW_UPDATE_DATA,                                            ///< Firmware update data 
    MDL_TOUCH_SCREEN_FW_UPDATE_END,                                              ///< Firmware update end
    MDL_TOUCH_SCREEN_FW_UPDATE_ERASE_FAIL,                                 ///< Firmware erase fail
    MDL_TOUCH_SCREEN_FW_UPDATE_WRITE_FAIL,                                 ///< Firmware write fail
    MDL_TOUCH_SCREEN_FW_UPDATE_VERIFY_FAIL,                                ///< Firmware verify fail
    MDL_TOUCH_SCREEN_FW_UPDATE_INVALID_FIRMWARE,                    ///< Firmware incorrect firmware
    MDL_TOUCH_SCREEN_FW_UPDATE_INVALID_FIRMWARE_VERSION,    ///< Firmware invalid firmware version
}MdlTsFwUpdate_e;

/**
 *  @brief The structure defines data of touch screen firmware update.
 */
typedef struct
{
    u8 *data;                           ///< Firmware update data
	u16 size;                            ///< Firmware update data size
	u16 firmwareID;                ///< Firmware id
	MdlTsFwUpdate_e fwmsg;    ///< Firmware update massage
}MdlTouchScreenFwUpdate_t;

/**
 *  @brief The structure defines data of touch screen for MMI used.
 */
typedef struct
{
    u16     x;                   ///< Touch screen x axis
    u16     y;                   ///< Touch screen y axis
    u16     pressure;      ///< Touch screen pressure
    u16     mode;           ///< Touch screen mode

} MdlTouchScreenData_t;

/**
 *  @brief The structure defines touch point of touch screen driver.
 */
typedef struct
{
    u16 Row;                     ///< Touch point row data
    u16 Col;                      ///< Touch point column data
    u8  index;                  ///< Touch point index
	u16 coordiff;              ///< Touch point coordinater difference
	u8  Pressed;              ///< Touch point pressed or not
} vm_TouchPoint_t;

/**
 *  @brief The structure defines data of touch screen driver.
 */
typedef struct
{
    u8 nFunction;                                                    ///< Touch screen calibration mode
    u8 nKeyMode;                                                    ///< Touch screen press or not
    u8 nFingerNum;                                                ///< Touch screen finger number
	u8 nUpdateIndex;                                             ///< Touch screen update index
    vm_TouchPoint_t atPoint[MAX_TOUCH_FINGER];  ///< Touch screen point data
} MdlTouchScreenInfo_t;

/**
 *  @brief The structure defines test information of touch screen driver (not used).
 */
typedef struct
{
   u32 nTotalIntCount;
   u32 nKeyReleaseCount;
   u32 nKeyPressCount;
   u32 Function[MAX_FUNCTION_NUM];
   u32 FingerNumCount[MAX_FINGER_NUM];
} DrvTsTestInfo_t;


/*=============================================================*/
// Messages identifiers
/*=============================================================*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "mdl_touchscreen_message_define__.hi"
};


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif  /* __MDL_TOUCH_SCREEN_MSG_PUB_H__ */
