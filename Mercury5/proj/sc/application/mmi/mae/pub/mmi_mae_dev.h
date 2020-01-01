/**
* @file    mmi_mae_dev.h
* @brief   
* @author  
* @version $Id$
*/

#ifndef __MMI_MAE_DEV_H__
#define __MMI_MAE_DEV_H__
#include "mmi_mae_common_def.h"

void MAE_Dev_LCDPowerOn(MAE_DispId_t id, boolean isOn);
boolean MAE_Dev_IsLCDPowerOn(MAE_DispId_t id);
void MAE_Dev_SetAppSleepMode(boolean isAllowed);
boolean MAE_Dev_IsG3DPowerOn(void);

#endif /* __MMI_MAE_DEV_H__ */


