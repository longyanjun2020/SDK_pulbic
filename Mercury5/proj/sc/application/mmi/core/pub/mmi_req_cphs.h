/**
 * @file    mmi_req_cphs.h
 * @brief   The file handles all the CPHS request function to RIL
 * @author  cosmo.sung@mstarsemi.com
 * 
 * @version $Id: 
 */
#ifndef __MMI_REQ_CPHS_H__
#define __MMI_REQ_CPHS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_cphssrv_def.h"

#ifdef __CPHS_SIMTEST__

void mmi_cphs_voice_mail_req(IBase *pRecipient, u8 DualID);
void mmi_cphs_query_line_req(IBase *pRecipient, u8 DualID);

#else

void mmi_cphs_voice_mail_req(u8 DualID);
void mmi_cphs_query_line_req(u8 DualID);

#endif

void mmi_cphs_query_mail_box_req(u8 DualID);
MAE_Ret mmi_cphs_set_mail_box_number_req(u8 DualID, MMI_CPHSSRV_Line_Service_e Line, MMI_CPHS_Type_e Type, u8 *pStrNumber, u8 nStrByteLen);
void mmi_cphs_set_request(u8 DualID, MMI_CPHS_Mode_e Mode, MMI_CPHS_FCTLD_e FctId);    
void mmi_cphs_read_functionality_req(u8 DualID);

#ifdef __3G_RIL_MMI__
void mmi_cphs_mnon_req(u8 DualID);
#endif // __3G_RIL_MMI__

#endif /* __MMI_REQ_CPHS_H__ */
