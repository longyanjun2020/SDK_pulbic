/*!
 * \file  sys_sys_power_mngt.h
 * \brief Power Management for sleep mode
 *
 *  This file defines the interface that are offered to different drivers (SPI, I2C, UART...) to allow sleep mode or not.
 *
 *  The interface allows to :
 *   \li allow or forbid "sleep mode"
 *   \li enable HWL to know if sleep mode is allowed or not.
 *
 */

#ifndef __SYS_SYS_POWER_MNGT_H__
#define __SYS_SYS_POWER_MNGT_H__

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"

typedef enum
{
    SYS_POWER_DOWN_USIM=0,
    SYS_POWER_DOWN_SPI,
    SYS_POWER_DOWN_I2C,
    SYS_POWER_DOWN_UART,
    SYS_POWER_DOWN_PWM,
    SYS_POWER_DOWN_GPIO,
    SYS_POWER_DOWN_RTC,
    SYS_POWER_DOWN_I2S,
    SYS_POWER_DOWN_EXT, ///< Application request
    SYS_POWER_DOWN_ATHENA,
    SYS_POWER_DOWN_LAST
}  sys_PowerDownModule_e;


typedef enum
{
    SYS_POWER_DOWN_MODE_ACTIVE = 0,     ///< No sleep and no 26 MHz clock cut
    SYS_POWER_DOWN_MODE_SLEEP_WITH_CLK, ///< sleep allowed but no 26 MHz clock cut
    SYS_POWER_DOWN_MODE_FULL_SLEEP      ///< sleep allowed and 26 MHz clock cut
}  sys_PowerDownMode_e;

void                sys_PowerDownModeInit( void );
void                sys_EnterNoPowerDownModeRegion(vm_sysPowerDownRegion_t Mode, sys_PowerDownModule_e Module );
void                sys_LeaveNoPowerDownModeRegion(vm_sysPowerDownRegion_t Mode, sys_PowerDownModule_e Module );
sys_PowerDownMode_e sys_GetAllowedPowerDownMode( void );
void                sys_PowerDownCustomerEnable32k( bool i_b_Enable );

#endif //__SYS_SYS_POWER_MNGT_H__

