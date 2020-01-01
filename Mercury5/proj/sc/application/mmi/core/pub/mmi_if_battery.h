/**
 * @file    mmi_if_battery.h
 * @brief   The file handles the vm battery event and forward to IBATTERY service
 * @author  christoph.kuo@mstarsemi.com
 * 
 * @version $Id: mmi_if_battery.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_BATTERY_H__
#define __MMI_IF_BATTERY_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

 
void mmi_battery_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_BATTERY_H__ */
