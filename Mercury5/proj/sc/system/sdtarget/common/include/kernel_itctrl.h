/******************************************************************************/
/*  File    :   kernel_itctrl.h                                               */
/*----------------------------------------------------------------------------*/
/*  Scope   :   Interrupt controller related definitions                      */
/*                                                                            */
/******************************************************************************/
#ifndef __KERNEL_ITCTRL_H__
#define __KERNEL_ITCTRL_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/******************************************************************************/
/*        Interrupt Controller (ITCTRL) registers                             */
/******************************************************************************/
#define IRQCTRL_INT_ON_FIQ  0
#define IRQCTRL_INT_ON_IRQ  1


#define IRQCTRL_CLR_IRQ_ALL 0xFFFFFFFF
#define IRQCTRL_CLEARALL    0x00000100
#define IRQCTRL_AUTOACK     0x00000001


#define DMAC_IT_POS         30
#define AUDIO_IT_POS        24
#define RFDL_COL_IT_POS     23
#define TBU_SINTA_IT_POS    22
#define TBU_FINT_IT_POS     21
#define TBU_SINT3_IT_POS    20
#define TBU_SINT2_IT_POS    19
#define TBU_SINT1_IT_POS    18
#define TBU_SINT0_IT_POS    17
#define TIMEOUT_IT_POS      15
#define OSTICK_IT_POS       14
#define TIMSOFT_IT_POS      13
#define KEYBOARD_IT_POS     12
#define UART2_IT_POS        11
#define UART1_IT_POS        10
#define I2C_TRANSFER_IT_POS 9
#define MMP_IT_POS          6 // MultiMedia Processor (Montage)
#define SPI1_IT_POS         5
#define I2C_STATUS_IT_POS   4
#define EXT3_IT_POS         3
#define EXT2_IT_POS         2
#define EXT1_IT_POS         1
#define ABB_IT_POS          0

/******************************************************************************/
/*        External interrupt Controller registers                             */
/******************************************************************************/
/*u32_cfg0 register definitions */
#define EXT_INT_CFG0_POL_0_OS   0
#define EXT_INT_CFG0_POL_0_MSK  ((u32)1<< EXT_INT_CFG0_POL_0_OS)
#define EXT_INT_CFG0_MODE_0_OS  1
#define EXT_INT_CFG0_MODE_0_MSK ((u32)3<< EXT_INT_CFG0_MODE_0_OS)
#define EXT_INT_CFG0_DEB_0_OS   3
#define EXT_INT_CFG0_DEB_0_MSK  ((u32)7<< EXT_INT_CFG0_DEB_0_OS)
#define EXT_INT_CFG0_POL_1_OS   6
#define EXT_INT_CFG0_POL_1_MSK  ((u32)1<< EXT_INT_CFG0_POL_1_OS)
#define EXT_INT_CFG0_MODE_1_OS  7
#define EXT_INT_CFG0_MODE_1_MSK ((u32)3<< EXT_INT_CFG0_MODE_1_OS)
#define EXT_INT_CFG0_DEB_1_OS   9
#define EXT_INT_CFG0_DEB_1_MSK  ((u32)7<< EXT_INT_CFG0_DEB_1_OS)
#define EXT_INT_CFG0_POL_2_OS   12
#define EXT_INT_CFG0_POL_2_MSK  ((u32)1<< EXT_INT_CFG0_POL_2_OS)
#define EXT_INT_CFG0_MODE_2_OS  13
#define EXT_INT_CFG0_MODE_2_MSK ((u32)3<< EXT_INT_CFG0_MODE_2_OS)
#define EXT_INT_CFG0_DEB_2_OS   15
#define EXT_INT_CFG0_DEB_2_MSK  ((u32)7<< EXT_INT_CFG0_DEB_2_OS)
#define EXT_INT_CFG0_POL_3_OS   18
#define EXT_INT_CFG0_POL_3_MSK  ((u32)1<< EXT_INT_CFG0_POL_3_OS)
#define EXT_INT_CFG0_MODE_3_OS  19
#define EXT_INT_CFG0_MODE_3_MSK ((u32)3<< EXT_INT_CFG0_MODE_3_OS)
#define EXT_INT_CFG0_DEB_3_OS   21
#define EXT_INT_CFG0_DEB_3_MSK  ((u32)7<< EXT_INT_CFG0_DEB_3_OS)
#define EXT_INT_CFG0_POL_4_OS   24
#define EXT_INT_CFG0_POL_4_MSK  ((u32)1<< EXT_INT_CFG0_POL_4_OS)
#define EXT_INT_CFG0_MODE_4_OS  25
#define EXT_INT_CFG0_MODE_4_MSK ((u32)3<< EXT_INT_CFG0_MODE_4_OS)
#define EXT_INT_CFG0_DEB_4_OS   27
#define EXT_INT_CFG0_DEB_4_MSK  ((u32)7<< EXT_INT_CFG0_DEB_4_OS)

/*u32_cfg1 register definitions */
#define EXT_INT_CFG1_POL_5_OS   0
#define EXT_INT_CFG1_POL_5_MSK  ((u32)1<< EXT_INT_CFG1_POL_5_OS)
#define EXT_INT_CFG1_MODE_5_OS  1
#define EXT_INT_CFG1_MODE_5_MSK ((u32)3<< EXT_INT_CFG1_MODE_5_OS)
#define EXT_INT_CFG1_DEB_5_OS   3
#define EXT_INT_CFG1_DEB_5_MSK  ((u32)7<< EXT_INT_CFG1_DEB_5_OS)
#define EXT_INT_CFG1_POL_6_OS   6
#define EXT_INT_CFG1_POL_6_MSK  ((u32)1<< EXT_INT_CFG1_POL_6_OS)
#define EXT_INT_CFG1_MODE_6_OS  7
#define EXT_INT_CFG1_MODE_6_MSK ((u32)3<< EXT_INT_CFG1_MODE_6_OS)
#define EXT_INT_CFG1_DEB_6_OS   9
#define EXT_INT_CFG1_DEB_6_MSK  ((u32)7<< EXT_INT_CFG1_DEB_6_OS)
#define EXT_INT_CFG1_POL_7_OS   12
#define EXT_INT_CFG1_POL_7_MSK  ((u32)1<< EXT_INT_CFG1_POL_7_OS)
#define EXT_INT_CFG1_MODE_7_OS  13
#define EXT_INT_CFG1_MODE_7_MSK ((u32)3<< EXT_INT_CFG1_MODE_7_OS)
#define EXT_INT_CFG1_DEB_7_OS   15
#define EXT_INT_CFG1_DEB_7_MSK  ((u32)7<< EXT_INT_CFG1_DEB_7_OS)
#define EXT_INT_CFG1_POL_8_OS   18
#define EXT_INT_CFG1_POL_8_MSK  ((u32)1<< EXT_INT_CFG1_POL_8_OS)
#define EXT_INT_CFG1_MODE_8_OS  19
#define EXT_INT_CFG1_MODE_8_MSK ((u32)3<< EXT_INT_CFG1_MODE_8_OS)
#define EXT_INT_CFG1_DEB_8_OS   21
#define EXT_INT_CFG1_DEB_8_MSK  ((u32)7<< EXT_INT_CFG1_DEB_8_OS)
#define EXT_INT_CFG1_POL_9_OS   24
#define EXT_INT_CFG1_POL_9_MSK  ((u32)1<< EXT_INT_CFG1_POL_9_OS)
#define EXT_INT_CFG1_MODE_9_OS  25
#define EXT_INT_CFG1_MODE_9_MSK ((u32)3<< EXT_INT_CFG1_MODE_9_OS)
#define EXT_INT_CFG1_DEB_9_OS   27
#define EXT_INT_CFG1_DEB_9_MSK  ((u32)7<< EXT_INT_CFG1_DEB_9_OS)

/*u32_cfg2 register definitions */
#define EXT_INT_CFG2_POL_10_OS  0
#define EXT_INT_CFG2_POL_10_MSK ((u32)1<< EXT_INT_CFG2_POL_10_OS)
#define EXT_INT_CFG2_MODE_10_OS 1
#define EXT_INT_CFG2_MODE_10_MSK    ((u32)3<< EXT_INT_CFG2_MODE_10_OS)
#define EXT_INT_CFG2_DEB_10_OS  3
#define EXT_INT_CFG2_DEB_10_MSK ((u32)7<< EXT_INT_CFG2_DEB_10_OS)
#define EXT_INT_CFG2_POL_11_OS  6
#define EXT_INT_CFG2_POL_11_MSK ((u32)1<< EXT_INT_CFG2_POL_11_OS)
#define EXT_INT_CFG2_MODE_11_OS 7
#define EXT_INT_CFG2_MODE_11_MSK    ((u32)3<< EXT_INT_CFG2_MODE_11_OS)
#define EXT_INT_CFG2_DEB_11_OS  9
#define EXT_INT_CFG2_DEB_11_MSK ((u32)7<< EXT_INT_CFG2_DEB_11_OS)
#define EXT_INT_CFG2_POL_12_OS  12
#define EXT_INT_CFG2_POL_12_MSK ((u32)1<< EXT_INT_CFG2_POL_12_OS)
#define EXT_INT_CFG2_MODE_12_OS 13
#define EXT_INT_CFG2_MODE_12_MSK    ((u32)3<< EXT_INT_CFG2_MODE_12_OS)
#define EXT_INT_CFG2_DEB_12_OS  15
#define EXT_INT_CFG2_DEB_12_MSK ((u32)7<< EXT_INT_CFG2_DEB_12_OS)
#define EXT_INT_CFG2_POL_13_OS  18
#define EXT_INT_CFG2_POL_13_MSK ((u32)1<< EXT_INT_CFG2_POL_13_OS)
#define EXT_INT_CFG2_MODE_13_OS 19
#define EXT_INT_CFG2_MODE_13_MSK    ((u32)3<< EXT_INT_CFG2_MODE_13_OS)
#define EXT_INT_CFG2_DEB_13_OS  21
#define EXT_INT_CFG2_DEB_13_MSK ((u32)7<< EXT_INT_CFG2_DEB_13_OS)
#define EXT_INT_CFG2_POL_14_OS  24
#define EXT_INT_CFG2_POL_14_MSK ((u32)1<< EXT_INT_CFG2_POL_14_OS)
#define EXT_INT_CFG2_MODE_14_OS 25
#define EXT_INT_CFG2_MODE_14_MSK    ((u32)3<< EXT_INT_CFG2_MODE_14_OS)
#define EXT_INT_CFG2_DEB_14_OS  27
#define EXT_INT_CFG2_DEB_14_MSK ((u32)7<< EXT_INT_CFG2_DEB_14_OS)

/*u32_cfg3 register definitions */
#define EXT_INT_CFG3_POL_15_OS  0
#define EXT_INT_CFG3_POL_15_MSK ((u32)1<< EXT_INT_CFG3_POL_15_OS)
#define EXT_INT_CFG3_MODE_15_OS 1
#define EXT_INT_CFG3_MODE_15_MSK    ((u32)3<< EXT_INT_CFG3_MODE_15_OS)
#define EXT_INT_CFG3_DEB_15_OS  3
#define EXT_INT_CFG3_DEB_15_MSK ((u32)7<< EXT_INT_CFG3_DEB_15_OS)

/* u16_Pending_[0:1] register definitions */
#define PENDING_INT_ID_OFF      2
#define PENDING_INT_ID_MSK      (0x3F << PENDING_INT_ID_OFF)
#define PENDING_INT_FLAG_OFF    8
#define PENDING_INT_FLAG_MSK    (0x01 << PENDING_INT_FLAG_OFF)


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef struct W5IrqControl_s
{
  u32 u32_Priority12;   // INT0  to INT7 (0 highest, 7 lowest)
  u32 u32_Priority34;   // INT8  to INT15
  u32 u32_Priority56;   // INT16 to INT23
  u32 u32_Priority78;   // INT24 to INT31
  u32 u32_Priority910;  // INT32 to INT39
  u32 u32_Mapping0;     // INT0  to INT31 / 0=IRQ0n 1=IRQ1n
  u32 u32_Mapping1;     // INT32 to INT39 / 0=IRQ0n 1=IRQ1n
  u32 u32_Mask0;        // INT0  to INT31 / 0=masked 1=not masked
  u32 u32_Mask1;        // INT32 to INT39 / 0=masked 1=not masked
  u32 u32_Sensitivity0; // 0=edge  1=level
  u32 u32_Sensitivity1; // 0=edge  1=level
  u32 u32_Polarity0;    // 0=low,neg   1=high,pos
  u32 u32_Polarity1;    // 0=low,neg 1=high,pos
  u32 u32_Reentrant0;   // 0=not reentrant 1=reentrant
  u32 u32_Reentrant1;   // 0=not reentrant  1=reentrant
  u16 u16_Pending_0;    // IRQ0n
  u16 u16_Level_0;      // IRQ0n
  u16 u16_Pending_1;    // IRQ1n
  u16 u16_Level_1;      // IRQ1n
  u32 u32_RawStatus0;   // 0=not pending 1=pending (before mask)
  u32 u32_RawStatus1;   // 0=not pending 1=pending (before mask)
  u32 u32_Status0;      // 0=not pending 1=pending
  u32 u32_Status1;      // 0=not pending 1=pending
  u32 u32_Clear0;       // 0=no effect 1=clear interrupt (EOI for an it)
  u32 u32_Clear1;       // 0=no effect 1=clear interrupt (EOI for an it)
  u32 u32_Ack0;         // 0=no effect 1=acknowledge interrupt
  u32 u32_Ack1;         // 0=no effect 1=acknowledge interrupt
  u32 u32_Service0;     // 0=not in service 1=ack but not cleared
  u32 u32_Service1;     // 0=not in service 1=ack but not cleared
  u32 au32_Pad[4];
  u32 u32_WakeUpMask0;  // 0=masked 1=not masked
  u32 u32_WakeUpMask1;  // 0=masked 1=not masked
  u32 u32_Config;       // clear all pending it (EOI) or autoack config
} W5IrqControl_t;

typedef struct W5ExtInt_s
{
    u32 u32_clk_deb_cfg ;
    u32 u32_cfg0 ;
    u32 u32_cfg1 ;
    u32 u32_cfg2 ;
    u32 u32_cfg3 ;
    u32 u32_int_raw_status ;
    u32 u32_int_clear ;
    u32 u32_int_mask1 ;
    u32 u32_int_status1 ;
    u32 u32_int_mask2 ;
    u32 u32_int_status2 ;
    u32 u32_int_mask3 ;
    u32 u32_int_status3 ;
    u32 u32_spare ;
} W5ExtInt_t;

#endif // __KERNEL_ITCTRL_H__
