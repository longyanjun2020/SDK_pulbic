/**
 * @file    mmi_if_sys.h
 * @brief   The file handles the system messages
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id $
 */
 
#ifndef __MMI_IF_SYS_H__
#define __MMI_IF_SYS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

__SLDPM_FREE__ void mmi_sys_ema_notify_if(IBase* pRecipient, vm_msg_t *pData);

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
void mmi_sys_find_high_speed_task_notify_if(IBase* pRecipient, vm_msg_t *pData);
#endif

#endif /* __MMI_IF_SYS_H__ */
