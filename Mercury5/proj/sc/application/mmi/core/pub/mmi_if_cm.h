/**
 * @file    mmi_if_cm.h
 * @brief   The file handles the CM event and forward to VTCC service
 * @author  
 * 
 * @version $Id: mmi_if_cm.h $
 */
#ifndef __MMI_IF_CM_H__
#define __MMI_IF_CM_H__

#ifdef __VT_3G324M__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_vtccsrv_def.h"

#include "sys_rtk_vmrtkho.h"
#include "sys_vm_dbg.ho"
#include "vm_osdef.hc"
#include "sys_MsWrapper_cus_os_type.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"

#include "api_cm_itf.h"
#include "cmmmi_sig.h"

void mmi_cm_msg_parser(IBase* pRecipient, struct vm_msg *pData);

///MMI_CM_GET_CHANNEL_NUMBER_CNF
void mmi_cm_get_channel_number_cnf_if(IBase* pRecipient, struct vm_msg *pData);
///MMI_CM_DISCONNECT_CNF
void mmi_cm_get_disconnect_cnf_if(IBase* pRecipient, struct vm_msg *pData);
///MMI_CM_DISCONNECT_IND
void mmi_cm_get_disconnect_ind_if(IBase* pRecipient, struct vm_msg *pData);

#endif //__VT_3G324M__
#endif /* __MMI_IF_CM_H__ */

