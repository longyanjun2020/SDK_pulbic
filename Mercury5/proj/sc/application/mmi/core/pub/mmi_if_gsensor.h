/**
* @file    mmi_if_gsensor.h
* @brief   
* @author  mark.yang@mstarsemi.com
* 
* @version $Id: mmi_if_gsensor.h 15893 2008-11-04 14:51:24Z mark.yang $
*/
#ifndef __MMI_IF_GSENSOR_H__
#define __MMI_IF_GSENSOR_H__

#include "mmi_mae_interface_def.h"
#include "mmi_gsensor_msgdef.h"

void mmi_gsensor_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_gsensor_op_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_gsensor_regnotify_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_gsensor_ind_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_GSENSOR_H__ */
