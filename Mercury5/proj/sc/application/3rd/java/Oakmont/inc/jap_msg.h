#ifndef __JAP_MSG_DEFINE_H__
#define __JAP_MSG_DEFINE_H__
/**
*
* @file    jap_msg.h
* @brief   This file .
*
* @author  Owen.Lee
* @version $Id: jap_msg.h 28349 2009-04-15 02:10:31Z code.lin $
*
*/


/* Aplix header - begin */
/* Aplix header - end */

/* Mstar header - begin */
#include "jap_head.h"
/* Mstar header - end */


/**
 *  jap_msg_create
 *
 *  @brief  Create one message for send to KVE task.
 *
 *  @param  msgType             [in]Use specified device
 *  @param  ppData              [out]The address point to the message body for return
 *
 *  @retval the message for jap_msg_send()
 *          NULL if failed
 */
void* jap_msg_create(JAP_MsgId_t msgType, void **ppData);


/**
 *  jap_msg_send
 *
 *  @brief  Send the message created by jap_msg_create() to KVE task.
 *
 *  @param  pMsg                [in]Message to send
 *
 *  @retval none
 */
void jap_msg_send(void* pMsg);





#endif /* __JAP_MSG_DEFINE_H__ */

