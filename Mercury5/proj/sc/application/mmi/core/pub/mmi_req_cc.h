/**
 * @file    mmi_req_cc.h
 * @brief   The file handles all the cc request function to RIL
 * @author  collin.chiang@mstarsemi.com
 * 
 * @version $Id: mmi_req_cc.h 25955 2009-03-17 11:53:23Z collin.chiang $
 */
#ifndef __MMI_REQ_CC_H__
#define __MMI_REQ_CC_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_ccsrv_def.h"

void mmi_cc_dialing_req(MMI_CLIR_INFO_e CLIRInfo, u8 *pCallNum, u8 DualID);
void mmi_cc_accept_req(u8 DualID);
void mmi_cc_chld_req(MMI_Call_Chld_Type_e ChldFlag, u8 u8CallID, u8 DualID);
void mmi_cc_call_oper_req(MMI_Call_Chld_Type_e ChldFlag, u8 DualID);
void mmi_cc_hangup_req(u8 DualID);
void mmi_cc_hangup_outgoingcall_req(u8 DualID);
void mmi_cc_dtmf_req(u8 keycode, MMI_CCSRV_DTMF_OP_e oper, u8 duration, u8 DualID);
void mmi_cc_abort_dtmf_req(u8 DualID);
void mmi_cc_clcc_req(u8 DualID);
#ifdef __MMI_CALL_FIREWALL__
void mmi_cc_call_cause_req(u8 cause, u8 DualID);
#endif /* __MMI_CALL_FIREWALL__ */
#endif /* __MMI_REQ_CC_H__ */
