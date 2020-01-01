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
* @file    mdl_keypad.h
* @version
* @brief   keypad middleware interface.
*
*/

#ifndef __MDL_KEYPAD_H__
#define __MDL_KEYPAD_H__
#if 1
#include "mdl_keypad_pub.h"
#else
/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "vm_kbd.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define DEV_KEY_OFFSET          1


/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines the return code of the keypad middle interface
 */
typedef enum
{
    MDL_KEYPAD_OK,                 /**< Function complete successfully */
    MDL_KEYPAD_FAIL,               /**< Function common fail */
} MdlKeypadErrCode_e;

/*
typedef enum {
    KEY_0 = (u8)0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SEND,      //10
    KEY_END,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_SELECT,
    KEY_HASH,      // #
    KEY_STAR,      // *
    KEY_LMENU,
    KEY_RMENU,     //20
    KEY_VOLUP,
    KEY_VOLDOWN,
    KEY_CLR,
    KEY_FUNC,
    KEY_SK1,
    KEY_SK2,
    KEY_POWER,
    KEY_HEADSET,
    KEY_CAMERA,
    MVVK_MAX,
    KEY_NONE = (u8)(0xFF)
};
*/

enum MS_VKeyCode
{
  KEY_OK = DEV_KEY_OFFSET ,
  KEY_MEN    ,
  KEY_LEFT   ,
  KEY_PHB    ,
  KEY_RIGHT  ,
  KEY_ONOFF  ,
  KEY_CLR    ,
  KEY_PLUS   ,
  KEY_SEND   ,
  KEY_SEND2  ,
  KEY_END    ,
  KEY_MINUS  ,
  KEY_1      ,
  KEY_2      ,
  KEY_3      ,
  KEY_4      ,
  KEY_5      ,
  KEY_6      ,
  KEY_7      ,
  KEY_8      ,
  KEY_9      ,
  KEY_STAR   ,
  KEY_0      ,
  KEY_HASH   ,
  KEY_MSG    ,
  KEY_MAIL   ,
  KEY_FSTDL1 ,
  KEY_FSTDL2 ,
  KEY_FSTDL3 ,
  KEY_FSTDL4 ,
  KEY_REDIAL ,
  KEY_HOOKOFF_DUMMY, /* add this dummy id in order to sync with MMI platform */
  KEY_HOOK   ,
  KEY_UP     ,
  KEY_DOWN   ,
  KEY_FLAPON ,
  KEY_FLAPOFF,
  KEY_SIDE_UP,
  KEY_SIDE_DN,
  KEY_SKLEFT ,
  KEY_SKRIGHT,
  KEY_HEADSET,
  KEY_CLEAR  ,
  KEY_ACTION ,
	KEY_CAMERA ,
	KEY_MP3    ,
  KEY_ATV    ,
  KEY_FM     ,
	KEY_POWERMODE,
	     
	KEY_Q, 
	KEY_A,
	KEY_Alt,
	KEY_SHIFTLEFT, 
	KEY_ENTER,
	KEY_W , 
	KEY_S, 
	KEY_Z,
	KEY_E, 
	KEY_D,
	KEY_X, 
	KEY_SPACE, 
	KEY_R,
	KEY_F, 
	KEY_C, 
	KEY_SYM,
	KEY_T, 
	KEY_G, 
	KEY_V ,
	KEY_SHIFTRIGHT,
	KEY_Y, 
	KEY_H, 
	KEY_B,
	KEY_DOLLAR,
	KEY_U, 
	KEY_J,
	KEY_N,
	KEY_O, 
	KEY_L,
	KEY_I, 
	KEY_K, 
	KEY_M,
	KEY_P, 
	KEY_DEL,
	KEY_NEXT,
	KEY_DOT,
	KEY_SHIFT,
  KEY_CTRL,
  KEY_LOCK,
 
	KEY_COMMA,
	KEY_AT,
	KEY_EXCLAM,
	KEY_APOSTROPHE,

  KEY_FASTFORWARD,
  KEY_REWIND,
 
  KEY_MENU,
  KEY_QUESTION,

  KEY_OFN_LEFT,  
  KEY_OFN_RIGHT,  
  KEY_OFN_UP,  
  KEY_OFN_DOWN,
  KEY_HOME, 

	KEY_SAME = 0xFE,
  KEY_DUMMY   = 0xFF
};

/*
** ---------------------------------------------------------------
**    Primitive structure between KBD driver and MMI
** ---------------------------------------------------------------
*/
typedef struct st_vkey_message_
{
    u8              keymode;
    u8              vkey;
} VKEYCODE, *PVKEYCODE;


//#define KEY_PRESSED             (u8) 1
//#define KEY_RELEASED            (u8) 2
//#define KEY_PRESSED_ON_OFF      (u8) 3
//#define KEY_RELEASED_ON_OFF	    (u8) 4

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef _VIRTUAL_KEY_CODE_BODY_

/** MdlVkeyParser
* @brief        Translate the key matrix to virtual key code and send to
*               subscribor
* @param[in]    key message.
* @retval       MDL_KEYPAD_OK,   key processed
*               MDL_KEYPAD_FAIL, key is not processed
*/
MdlKeypadErrCode_e  MdlVkeyParser(void* pMessage);

/** MdlKeypadSubscribe
* @brief        Used to subscribe to the Keypad service
* @param[in]    nMailbox       register mailbox ID.
* @param[out]   pnPreMailbox   to get the previous registered mailbox. 0xFF means no mailbox is registered.
*
* @retval       MDL_KEYPAD_OK
*               MDL_KEYPAD_FAIL
*/
MdlKeypadErrCode_e MdlKeypadSubscribe(u8 nMailbox, u8 *pnPreMailbox);


MdlKeypadErrCode_e MdlKeypadSubscribe_ex(u8 nMailbox, u8 *pnPreMailbox);

/** MdlVkeySendFakeKey
* @brief       Send fake virtual key code to subscribor
* @param       None
* @retval      MDL_KEYPAD_OK,   key processed
*              MDL_KEYPAD_FAIL, key is not processed
*/
MdlKeypadErrCode_e MdlVkeySendFakeKey(void);
#else //_VIRTUAL_KEY_CODE_BODY_

/** MdlVkeyParser
* @brief        Translate the key matrix to virtual key code and send to
*               subscribor
* @param[in]    key message.
* @retval       MDL_KEYPAD_OK,   key processed
*               MDL_KEYPAD_FAIL, key is not processed
*/
extern MdlKeypadErrCode_e  MdlVkeyParser(void* pMessage);

/** MdlKeypadSubscribe
* @brief        Used to subscribe to the Keypad service
* @param[in]    nMailbox       register mailbox ID.
* @param[out]   pnPreMailbox   to get the previous registered mailbox. 0xFF means no mailbox is registered.
*
* @retval       MDL_KEYPAD_OK
*               MDL_KEYPAD_FAIL
*/
extern MdlKeypadErrCode_e MdlKeypadSubscribe(u8 nMailbox, u8 *pnPreMailbox);


extern MdlKeypadErrCode_e MdlKeypadSubscribe_ex(u8 nMailbox, u8 *pnPreMailbox);

/** MdlKeypadHookKey
* @brief        Hook key process.
* @param[in]    nPress   Hook key is press or release.
* @retval       MDL_KEYPAD_OK
*               MDL_KEYPAD_FAIL
*/
extern MdlKeypadErrCode_e MdlKeypadHookKey(u8 nPress);

/** MdlVkeySendFakeKey
* @brief       Send fake virtual key code to subscribor
* @param       None
* @retval      MDL_KEYPAD_OK,   key processed
*              MDL_KEYPAD_FAIL, key is not processed
*/
extern MdlKeypadErrCode_e MdlVkeySendFakeKey(void);

/** MdlKeypadMailbox
* @brief        Used to get subscribe mailbox of task.
* @param[out]    pnMailbox      subscribe mail box of task.
*
* @retval       MDL_KEYPAD_OK
*               MDL_KEYPAD_FAIL
*/
extern MdlKeypadErrCode_e MdlKeypadMailbox(u8 *pnMailbox);

#endif//_VIRTUAL_KEY_CODE_BODY_
#endif
#endif//__MDL_KEYPAD_H__


