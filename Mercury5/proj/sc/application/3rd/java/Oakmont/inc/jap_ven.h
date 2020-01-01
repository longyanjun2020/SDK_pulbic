#ifndef __JAP_VEN_DEFINE_H__
#define __JAP_VEN_DEFINE_H__
/**
*
* @file    java_ven.c
* @brief   This file .
*
* @author  Owen.Lee
* @version $Id: jap_ven.h 28349 2009-04-15 02:10:31Z code.lin $
*
*/


/* Aplix header - begin */
/* Aplix header - end */

/* Mstar header - begin */
#include "jap_head.h"
/* Mstar header - end */


/**
 *  jap_ven_init
 *
 *  @brief  Init SDK vendor state control environment.
 *
 *  @param  none
 *
 *  @retval none
 */
void jap_ven_init(void);

void jt_vm_msg_handler(AJ_S32 eventType);


void jap_subscribe_ts_kpd(void);
void jap_unsubscribe_ts_kpd(void);


#endif /* __JAP_VEN_DEFINE_H__ */

