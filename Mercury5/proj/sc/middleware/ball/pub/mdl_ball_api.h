/**
* @file    mdl_ball_api.h
* @version
* @brief   ball middleware interface.
*
*/

#ifndef __PUBLIC_MDL_BALL_H__
#define __PUBLIC_MDL_BALL_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/** MdlOfnParser
* @brief        Translate the Ball  to virtual key code and send to
*               subscribor
* @param[in]    Ball key message.
* @retval       MDL_OFN_OK,   key processed
*               MDL_OFN_FAIL, key is not processed
*/
MdlBallErrCode_e  MdlBallParser(void* pMessage);

/** MdlBallSubscribe
* @brief        Used to subscribe to the Ball middleware
* @param[in]    nMailbox       register mailbox ID.
* @param[out]   pnPreMailbox   to get the previous registered mailbox. 0xFF means no mailbox is registered.
*
* @retval       MDL_BALL_OK
*               MDL_BALL_FAIL
*/
MdlBallErrCode_e MdlBallSubscribe(u8 nMailbox, u8 *pnPreMailbox);
MdlBallErrCode_e MdlBallEnable(void);

#endif //__MDL_BALL_H__

