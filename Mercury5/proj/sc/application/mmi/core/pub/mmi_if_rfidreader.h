/**
 * @file    mmi_if_rfidreader.c
 *
 * @brief   This file implements the functions which are used parse the confirmations from rfidreader driver and send events to rfidreader AP.
 * @author	allan.hsu@mstarsemi.com
 *
 * @version $Id: mmi_if_rfidreader.h 11319 2008-06-04 03:32:12Z allan.hsu $
 */

#ifdef __RFID__

#ifndef __MMI_IF_RFIDREADER_H__
#define __MMI_IF_RFIDREADER_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "vm_types.ht"
#include "esl_rfid_itf.h"

void mmi_rfidreader_msg_parser(IBase* pRecipient, vm_msg_t *pData);


#if	!defined(__SUPPORT_ABL_INTERFACE__) && !defined(__PC_SIMULATOR__)
void mmi_rfidreader_drv_req(esl_RFID_driver_Req_t *pReq, esl_RFID_Cb_t *pRfidCb);

#ifdef __SUPPORT_JSR257__
void mmi_rfidreader_reg_listener_req(esl_RFID_Cb_t *pRfidCb);
#endif	//__SUPPORT_JSR257__

#endif	//__SUPPORT_ABL_INTERFACE__

#endif /* __MMI_IF_RFIDREADER_H__ */

#endif	//__RFID__

