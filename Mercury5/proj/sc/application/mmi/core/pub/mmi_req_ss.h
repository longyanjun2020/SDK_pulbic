/**
 * @file    mmi_req_ss.h
 * @brief   The file handles all the SS request function to RIL
 * @author  lih.wang@mstarsemi.com
 * 
 * @version $Id: mmi_req_ss.h 12881 2008-07-29 08:32:05Z lih.wang $
 */

#ifndef __MMI_REQ_SS_H__
#define __MMI_REQ_SS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_sssrv_def.h"


void mmi_ss_call_divert_req(SSSRV_CallDivertReq_t *pReq, u8 DualID);
void mmi_ss_call_barring_req(SSSRV_CallBarringReq_t *pReq, u8 DualID);
void mmi_ss_change_barring_pwd_req(SSSRV_ChangeBarringPwdReq_t *pReq, u8 DualID);
void mmi_ss_call_waiting_req(SSSRV_CallWaitingReq_t *pReq, u8 DualID);
void mmi_ss_ussd_req(SSSRV_USSDReq_t *pReq, u8 DualID);


#ifdef __SS_TEST__
//void mmi_ss_call_divert_req(IBase *pRecipient, SSSRV_CallDivertReq_t *pReq, u8 DualID);
//void mmi_ss_call_barring_req(IBase *pRecipient, SSSRV_CallBarringReq_t *pReq, u8 DualID);
//void mmi_ss_change_barring_pwd_req(IBase *pRecipient, SSSRV_ChangeBarringPwdReq_t *pReq, u8 DualID);
//void mmi_ss_call_waiting_req(IBase *pRecipient, SSSRV_CallWaitingReq_t*pReq, u8 DualID);
//void mmi_ss_ussd_req(IBase *pRecipient, SSSRV_USSDReq_t *pReq, u8 DualID);
void mmi_ss_ussd_release_req(IBase *pRecipient, u8 DualID);
void mmi_ss_cug_req(IBase *pRecipient, SSSRV_UserGroupReq_t *pReq, u8 DualID);
void mmi_ss_cug_query(IBase *pRecipient, u8 DualID);
void mmi_ss_aoc_req(IBase *pRecipient, SSSRV_AOCReq_t *pReq, u8 DualID);
void mmi_ss_aoc_query(IBase *pRecipient, u8 DualID);
void mmi_ss_acm_req(IBase *pRecipient, SSSRV_ACMReq_t *pReq, u8 DualID);
void mmi_ss_amm_req(IBase *pRecipient, SSSRV_ACMMaxReq_t *pReq, u8 DualID);
void mmi_ss_puc_req(IBase *pRecipient, SSSRV_PUCReq_t *pReq, u8 DualID);
void mmi_ss_clx_req(IBase *pRecipient, MMI_SSSRV_CI_ReqType_e eCIType, u8 DualID);

#else

//void mmi_ss_call_divert_req(SSSRV_CallDivertReq_t *pReq, u8 DualID);
//void mmi_ss_call_barring_req(SSSRV_CallBarringReq_t *pReq, u8 DualID);
//void mmi_ss_change_barring_pwd_req(SSSRV_ChangeBarringPwdReq_t *pReq, u8 DualID);
//void mmi_ss_call_waiting_req(SSSRV_CallWaitingReq_t *pReq, u8 DualID);
//void mmi_ss_ussd_req(SSSRV_USSDReq_t *pReq, u8 DualID);
void mmi_ss_ussd_release_req(u8 DualID);
void mmi_ss_cug_req(SSSRV_UserGroupReq_t *pReq, u8 DualID);
void mmi_ss_cug_query(u8 DualID);
void mmi_ss_aoc_req(SSSRV_AOCReq_t *pReq, u8 DualID);
void mmi_ss_aoc_query(u8 DualID);
void mmi_ss_acm_req(SSSRV_ACMReq_t *pReq, u8 DualID);
void mmi_ss_amm_req(SSSRV_ACMMaxReq_t *pReq, u8 DualID);
void mmi_ss_puc_req(SSSRV_PUCReq_t *pReq, u8 DualID);
void mmi_ss_clx_req(MMI_SSSRV_CI_ReqType_e eCIType, u8 DualID);
    
#endif



#endif /* __MMI_REQ_SS_H__ */
