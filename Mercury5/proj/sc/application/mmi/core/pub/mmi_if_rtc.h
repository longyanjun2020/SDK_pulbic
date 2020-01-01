/**
 * @file    mmi_if_test.c
 *
 * @brief   This file defines the interface to parse singals of test group.
 * @author	kenny.wu@mstarsemi.com
 *
 * @version $Id: mmi_if_rtc.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */


#ifndef __MMI_IF_RTC_H__
#define __MMI_IF_RTC_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_rtc_alarm_ind(IBase *pRecipient, struct vm_msg*);

#endif /* __MMI_IF_RTC_H__ */
