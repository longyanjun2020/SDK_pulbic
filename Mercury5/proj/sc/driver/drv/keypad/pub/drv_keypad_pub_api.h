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
* @file    drv_keypad_pub_api.h
* @version
* @brief   Keypad driver interface
*
*/

#ifndef __DRV_KEYPAD_PUB_API_H__
#define __DRV_KEYPAD_PUB_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_keypad_pub_forward.h"
#include "vm_kbd.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** DrvKeypadISR
* @brief        Top level handler for keypad interrupt
*
* @retval       None.
*
*/
void DrvKeypadISR(void);

/** DrvKeypadInitBuffer
* @brief        Allows the customer to specify how many keys can be set into the keypad buffer
* @param[in]    nLowLimit         keypadd buffer low limit.
* @param[in]    nUpLimit          keypadd buffer up limit.
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadInitBuffer(u32 nLowLimit, u32 nUpLimit);

/** DrvKeypadProcessed
* @brief        Decrement the key counter after the key has been processed by the customer binary
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadProcessed(void);

/** DrvKeypadUnProcessed
* @brief        Decrement the key counter after the OFN key has been processed by the customer binary
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadUnProcessed(void);

/** DrvKeypadUnProcessed
* @brief        check the Keypad Buffer Up Limit to avoid sending msg to mmi
*
* @retval       TRUE         Msg Queue is Full.
* @retval       FALSE        Msg Queue is not Full.
*
*/
bool DrvKeypadIsMsgQueueFull(void);

/** DrvKeypadProduced
* @brief        Increase the key counter for the fake key produced from middleware.
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadProduced(void);

/** DrvKeypadIrqInit
* @brief        Initializes and enable the keypad IRQ
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadIrqInit(void);

/** DrvKeypadIrqInit
* @brief        Initializes and enable the keypad IRQ
* @param[in]    nMailbox    register mailbox.
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadSubscribe(u8 nMailbox);

/** DrvKeypadPowerOnOffKey
* @brief        Called by Athena IRQ handler when the On/Off key is pressed or released
* @param[in]    bPressed         Key pressed
*
* @retval       KEYPAD_OK        Success.
* @retval       Other            Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadPowerOnOffKey(bool bPressed);

/** DrvKeypadGetPowerKey
* @brief        This funciton is used to get the power key status. 0: release, 1: press.
* @param[out]   nPressed         Power key status.
*
* @retval       KEYPAD_OK        Success.
* @retval       Other            Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetPowerKey(u8 *nPressed);

#ifdef __DRV_HOT_KEY_FREQUENCY__
/** DrvKeypadSetHotKeyProcess
* @brief        This funciton is used to record the status of hot key exception process. 0: end, 1: start.
* @param[out]   nIsStart         Process status.
*
* @retval       KEYPAD_OK        Success.
* @retval       Other            Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadSetHotKeyProcess(u8 nIsStart);

/** DrvKeypadGetHotKeyProcess
* @brief        This funciton is used to get the status of hot key exception process. 0: end, 1: start.
* @param[out]   nProcess         Process status.
*
* @retval       KEYPAD_OK        Success.
* @retval       Other            Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetHotKeyProcess(u8 *nProcess);
#endif

/** DrvKeypadSetTbl
* @brief        This funciton is used to set keypad table.
* @param[in]    *pkeyTbl         keypad table name.
*
* @retval       KEYPAD_OK        Success.
* @retval       KEYPAD_FAIL      Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadSetTbl(char *pkeyTbl);

#ifdef __DRV_KEYPAD_TABLE_STACKABLE__
/** DrvKeypadFreeTbl
* @brief        This funciton is used to free keypad table.
* @param[in]    *pkeyMap         keypad map name.
*
* @retval       KEYPAD_OK        Success.
* @retval       KEYPAD_FAIL      Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadFreeTbl(char *pkeyTbl);
#endif

/** DrvKeypadGetTbl
* @brief        This funciton is used to get keypad table index.
*
* @retval       return table index.
*
*/
u8 DrvKeypadGetTbl(void);

/** DrvKeypadGetState
* @brief         This function returns the exact number of pressed key and their mapping for pressed keys
* @param[out]    ppPressedkeys    pointer on pressed keys array (don't need allocation or release)
* @param[out]    pnBpressed  :    number of pressed key.
*
* @retval       KEYPAD_OK         Success.
* @retval       Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetState(vm_kbdKey_t **ppPressedkeys, u8 *pnBpressed);

/** DrvKeypadGetState
* @brief
* @param[out]     ppPressedkeys     pointer on pressed keys array (don't need allocation or release)
* @param[in]      nRow0             number row0.
* @param[in]      nRow1             number row1.
* @param[out]     pnBpressed        number of pressed keys
*
* @retval         KEYPAD_OK         Success.
* @retval         Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetStateNew(vm_kbdKey_t **ppPressedkeys, u8 nRow0, u8 nRow1, u8 *pnBpressed);

/** DrvKeypadGetBufferNbKeys
* @brief          To get the number of pressed in keyad buffer.
* @param[out]     number of pressed keys
*
* @retval         KEYPAD_OK         Success.
* @retval         Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetBufferNbKeys(u32 *pnKeypadBufNum);

/** DrvKeypadGetStateAuto
* @brief          This function returns the exact number of pressed key and their mapping
* @param[out]     ppPressedkeys     pointer on pressed keys array (don't need allocation or release)
* @param[out]     pnBpressed        number of pressed keys
*
* @retval         KEYPAD_OK         Success.
* @retval         Other             Failed.
*
*/
DrvKeyPadErrCode_e DrvKeypadGetStateAuto(vm_kbdKey_t **ppPressedkeys, u8 *pnBpressed);

/** DrvKeypadMultiKey
* @brief          This function is used to enable the multi-keypad support.
* @param[in]      isEnable     TRUE: enable, FALSE: disable
*
* @retval         KEYPAD_OK         Success.
* @retval         Other             Failed.
*/
DrvKeyPadErrCode_e DrvKeypadMultiKey(bool isEnable);

#endif /* __DRV_KEYPAD_PUB_API_H__ */




