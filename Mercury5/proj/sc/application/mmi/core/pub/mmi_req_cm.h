/**
 * @file    mmi_req_cm.h
 * @brief   The file handles all the cm request function to RIL
 * @author  
 * 
 * @version $Id: mmi_req_cm.h $
 */
#ifndef __MMI_REQ_CM_H__
#define __MMI_REQ_CM_H__

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

void mmi_cm_get_channel_number_req(u32 index);
void mmi_cm_disconnect_req(u32 channelNumber);


#endif //__VT_3G324M__

#endif /* __MMI_REQ_CM_H__ */

