/******************************************************************************/
/*  File    :   kernel_timer.h                                                */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System timer related definitions                              */
/*                                                                            */
/******************************************************************************/

#ifndef __KERNEL_TIMER_H__
#define __KERNEL_TIMER_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* SYS_TIMER_TIMSOFT_CFG */
#define TIMSOFT_COUNTER_OFF         0
#define TIMSOFT_COUNTER_MSK         (0x07FF << TIMSOFT_COUNTER_OFF)
#define TIMSOFT_LENGTH_OFF          16
#define TIMSOFT_LENGTH_MSK          (0x07FF << TIMSOFT_LENGTH_OFF)
#define TIMSOFT_ENABLE_OFF          28
#define TIMSOFT_ENABLE_MSK          (0x01 << TIMSOFT_ENABLE_OFF)

/* SYS_TIMER_OSTICK_CFG */
#define OSTICK_LENGTH_OFF           0
#define OSTICK_LENGTH_MSK           (0x00FFFFFF << OSTICK_LENGTH_OFF)
#define OSTICK_ENABLE_OFF           28
#define OSTICK_ENABLE_MSK           (0x01 << OSTICK_ENABLE_OFF)

/* SYS_TIMER_OSTICK_COUNTER */
#define OSTICK_COUNTER_OFF          0
#define OSTICK_COUNTER_MSK          (0x00FFFFFF << OSTICK_COUNTER_OFF)

/* SYS_TIMER_WATCHDOG [0:1] */
#define WATCHDOG_LENGTH_OFF         0
#define WATCHDOG_LENGTH_MSK         (0x0FFF << WATCHDOG_LENGTH_OFF)
#define WATCHDOG_ENABLE_OFF         12
#define WATCHDOG_ENABLE_MSK         (0x01 << WATCHDOG_ENABLE_OFF)
#define WATCHDOG_NO_RESET_OFF       13
#define WATCHDOG_NO_RESET_MSK       (0x01 << WATCHDOG_NO_RESET_OFF)
#define WATCHDOG_ACK_OFF            16
#define WATCHDOG_ACK_MSK            (0x01 << WATCHDOG_ACK_OFF)
#define WATCHDOG_TIMEOUT_FLAG_OFF   20
#define WATCHDOG_TIMEOUT_FLAG_MSK   (0x01 << WATCHDOG_TIMEOUT_FLAG_OFF)

/* SYS_TIMER_TIMEOUT [0:3] */
#define TIMEOUT_COUNTER_OFF         0
#define TIMEOUT_COUNTER_MSK         (0xFF << TIMEOUT_COUNTER_OFF)
#define TIMEOUT_LENGTH_OFF          8
#define TIMEOUT_LENGTH_MSK          (0xFF << TIMEOUT_LENGTH_OFF)
#define TIMEOUT_CH_ID_OFF           16
#define TIMEOUT_CH_ID_MSK           (0x0F << TIMEOUT_CH_ID_OFF)
#define TIMEOUT_ENABLE_OFF          20
#define TIMEOUT_ENABLE_MSK          (0x01 << TIMEOUT_ENABLE_OFF)
#define TIMEOUT_STEP_OFF            24
#define TIMEOUT_STEP_MSK            (0x01 << TIMEOUT_STEP_OFF)
#define TIMEOUT_START_OFF           28
#define TIMEOUT_START_MSK           (0x01 << TIMEOUT_START_OFF)

/* SYS_TIMER_SOFT_ACK */
#define SOFT_ACK_OFF                0
#define SOFT_ACK_MSK                (0x01 << SOFT_ACK_OFF)

/* SYS_TIMER_INT_RAW_STATUS */
#define TIMEOUT_RAW_STATUS_OFF      0
#define TIMEOUT_RAW_STATUS_MSK      (0x0F << TIMEOUT_RAW_STATUS_OFF)
#define TIMSOFT_RAW_STATUS_OFF      4
#define TIMSOFT_RAW_STATUS_MSK      (0x01 << TIMSOFT_RAW_STATUS_OFF)
#define OSTICK_RAW_STATUS_OFF       5
#define OSTICK_RAW_STATUS_MSK       (0x01 << OSTICK_RAW_STATUS_OFF)
#define WATCHDOG_RAW_STATUS_OFF     6
#define WATCHDOG_RAW_STATUS_MSK     (0x01 << WATCHDOG_RAW_STATUS_OFF)
#define OSTICK2_RAW_STATUS_OFF      7
#define OSTICK2_RAW_STATUS_MSK      (0x01 << OSTICK2_RAW_STATUS_OFF)

/* SYS_TIMER_INT_MASK */
#define TIMEOUT_MASK_OFF            0
#define TIMEOUT_MASK_MSK            (0x0F << TIMEOUT_MASK_OFF)
#define TIMSOFT_MASK_OFF            4
#define TIMSOFT_MASK_MSK            (0x01 << TIMSOFT_MASK_OFF)
#define OSTICK_MASK_OFF             5
#define OSTICK_MASK_MSK             (0x01 << OSTICK_MASK_OFF)
#define WATCHDOG_MASK_OFF           6
#define WATCHDOG_MASK_MSK           (0x01 << WATCHDOG_MASK_OFF)
#define OSTICK2_MASK_OFF            7
#define OSTICK2_MASK_MSK            (0x01 << OSTICK2_MASK_OFF)

/* SYS_TIMER_INT_STATUS */
#define TIMEOUT_STATUS_OFF          0
#define TIMEOUT_STATUS_MSK          (0x0F << TIMEOUT_STATUS_OFF)
#define TIMSOFT_STATUS_OFF          4
#define TIMSOFT_STATUS_MSK          (0x01 << TIMSOFT_STATUS_OFF)
#define OSTICK_STATUS_OFF           5
#define OSTICK_STATUS_MSK           (0x01 << OSTICK_STATUS_OFF)
#define WATCHDOG_STATUS_OFF         6
#define WATCHDOG_STATUS_MSK         (0x01 << WATCHDOG_STATUS_OFF)
#define OSTICK2_STATUS_OFF          7
#define OSTICK2_STATUS_MSK          (0x01 << OSTICK2_STATUS_OFF)

/* SYS_TIMER_INT_CLEAR */
#define TIMEOUT_CLEAR_OFF           0
#define TIMEOUT_CLEAR_MSK           (0x0F << TIMEOUT_CLEAR_OFF)
#define TIMSOFT_CLEAR_OFF           4
#define TIMSOFT_CLEAR_MSK           (0x01 << TIMSOFT_CLEAR_OFF)
#define OSTICK_CLEAR_OFF            5
#define OSTICK_CLEAR_MSK            (0x01 << OSTICK_CLEAR_OFF)
#define WATCHDOG_CLEAR_OFF          6
#define WATCHDOG_CLEAR_MSK          (0x01 << WATCHDOG_CLEAR_OFF)
#define OSTICK2_CLEAR_OFF           7
#define OSTICK2_CLEAR_MSK           (0x01 << OSTICK2_CLEAR_OFF)

/* SYS_TIMER_STDA_CFG */
#define STDA_ENABLE_OFF             0
#define STDA_ENABLE_MSK             (0x01 << STDA_ENABLE_OFF)

/* SYS_TIMER_STDA_COUNTER */
#define STDA_COUNTER_OFF            0
#define STDA_COUNTER_MSK            (0xFFFFFFFF << STDA_COUNTER_OFF)

/* SYS_TIMER_SPARE */
#define OSTICK_HOLD_OFF             0
#define OSTICK_HOLD_MSK             (0x01 << OSTICK_HOLD_OFF)
#define OSTICK2_HOLD_OFF             1
#define OSTICK2_HOLD_MSK             (0x01 << OSTICK2_HOLD_OFF)

//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/************************************************/
/* system timer registers definition            */
/************************************************/
typedef struct W5TimerReg_s
{
    u32 u32_timsoftcfg;     // 0x00
    u32 u32_ostickcfg;      // 0x04
    u32 u32_ostickcnt;      // 0x08
    u32 u32_wdog0;          // 0x0C
    u32 u32_wdog1;          // 0x10
    u32 u32_timeout0;       // 0x14
    u32 u32_timeout1;       // 0x18
    u32 u32_timeout2;       // 0x1C
    u32 u32_timeout3;       // 0x20
    u32 u32_timsoftack;     // 0x24
    u32 u32_intrawstat;     // 0x28
    u32 u32_intmask;        // 0x2C
    u32 u32_intstat;        // 0x30
    u32 u32_intclr;         // 0x34
    u32 u32_rsvd0;          // 0x38
    u32 u32_rsvd1;          // 0x3C
    u32 u32_stdacfg;        // 0x40
    u32 u32_stdacnt;        // 0x44
    u32 u32_ostickhold;     // 0x48
    u32 u32_rsvd2;          // 0x4C
    u32 u32_rsvd3;          // 0x50
    u32 u32_ostick2cfg;     // 0x54
    u32 u32_ostick2cnt;     // 0x58
} W5TimerReg_t;

#endif // __KERNEL_TIMER_H__
