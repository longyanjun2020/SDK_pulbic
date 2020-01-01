/**
 * @file    mmi_if_timer.h
 * @brief   The document describes all the time out action of the timer used in MMI
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id: mmi_if_timer.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_TIMER_H__
#define __MMI_IF_TIMER_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

 
void mmi_timer_expired_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_TIMER_H__ */
