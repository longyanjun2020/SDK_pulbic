/**
 * @file    mmi_if_autotest.h
 * @brief   The file handles the RIL SIM/SEC event and forward to SIM/SEC service
 * @author  christine.tai@mstarsemi.com
 * 
 */
#if defined(__FT_AUTO_TEST__)
#ifndef __MMI_IF_AUTOTEST_H__ 
#define __MMI_IF_AUTOTEST_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

typedef struct
{
  u32  	nStatus;
  s8 strTestCase[64+1];
}MMI_AutoTest_Status_Ind_t;

void mmi_autotest_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_auto_test_status_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_auto_test_send_mms_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_AUTOTEST_H__ */
#endif
