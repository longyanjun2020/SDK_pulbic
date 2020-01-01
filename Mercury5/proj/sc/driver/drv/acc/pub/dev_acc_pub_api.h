#ifndef __DEV_ACC_PUB_API_H__
#define __DEV_ACC_PUB_API_H__

#include "vm_types.ht"
#include "dev_acc_pub_forward.h"

#if defined (__CHECK_VBATT_BY_CUS_AT_POWER_ON__)
u16 dev_cus_set_power_on_voltage(void);
#endif
u16 dev_cus_get_power_on_voltage_if_charger_on(void);        
u8 dev_accLCDSwitch (u8 on);
u8 dev_accGetLCDStatus (void);
u8 dev_chkSysSleepReady(void);
void dev_appSleepMode(u8 enable);

#endif /* __DEV_ACC_PUB_API_H__ */
