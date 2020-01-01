/**
 * @file    mmi_req_vtcc.h
 * @brief   The file handles all the vtcc request function to RIL
 * @author  
 * 
 * @version $Id: mmi_req_vtcc.h $
 */
#ifndef __MMI_REQ_VTCC_H__
#define __MMI_REQ_VTCC_H__

#ifdef __VT_3G324M__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_vtccsrv_def.h"

void mmi_vtcc_dialing_req(MMI_CLIR_INFO_e CLIRInfo, u8 *pCallNum, u8 DualID);
void mmi_vtcc_accept_req(u8 DualID);
void mmi_vtcc_hangup_req(u8 DualID);
void mmi_vtcc_fallback_req(u8 DualID);

#endif //__VT_3G324M__

#endif /* __MMI_REQ_VTCC_H__ */

