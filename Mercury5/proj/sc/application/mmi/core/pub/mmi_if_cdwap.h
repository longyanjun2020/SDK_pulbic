/**
 * @file    mmi_if_cdwap.h
 * @brief   The file handles the cdwap event with wap task
 * @author  
 *
 * $Id:$
 */
#ifndef __MMI_IF_CDWAP_H__
#define __MMI_IF_CDWAP_H__

#ifdef __WAP_MMI_CDWAP__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
//#include "java_ams_itf.h"

#ifdef _MSIM_
//#define __JAVA_SIMULATE__
#endif




//void mmi_cdwap_msg_parser(IBase* pRecipient, vm_msg_t *pData);
//void mmi_cdwap_user_extend_rsp_if(IBase* pRecipient, vm_msg_t *pData);

void mmi_cdwap_msg_parser(IBase* pRecipient, vm_msg_t *pMsg);



#endif // __WAP_MMI_CDWAP__

#endif /* __MMI_IF_CDWAP_H__ */
