/***************************************************************************
 *  kernel_itctrl.h
 *--------------------------------------------------------------------------
 *  Scope: Interrupt controller related definitions
 *
 ****************************************************************************/
#ifndef __KERNEL_ITCTRL_H__
#define __KERNEL_ITCTRL_H__

#include "cpu_mem_map.hc"


typedef struct KeIrqControl_s
{
  u32 u32_Fiq_Force0;     //force 15~0
  u32 u32_Fiq_Force1;     //force 31~16
  u32 u32_Fiq_Force2;     //force 47~32
  u32 u32_Fiq_Force3;     //force 63~48
  u32 u32_Fiq_Mask0;      //mask 15~0
  u32 u32_Fiq_Mask1;      //mask 31~16
  u32 u32_Fiq_Mask2;      //mask 47~32
  u32 u32_Fiq_Mask3;      //mask 63~48
  u32 u32_Fiq_Polarity0;  //polarity 15~0
  u32 u32_Fiq_Polarity1;  //polarity 31~16
  u32 u32_Fiq_Polarity2;  //polarity 47~32
  u32 u32_Fiq_Polarity3;  //polarity 63~48
  u32 u32_Fiq_Status0;    //polarity 15~0
  u32 u32_Fiq_Status1;    //polarity 31~16
  u32 u32_Fiq_Status2;    //polarity 47~32
  u32 u32_Fiq_Status3;    //polarity 63~48
  u32 u32_Irq_Force0;     //force 15~0
  u32 u32_Irq_Force1;     //force 31~16
  u32 u32_Irq_Force2;     //force 47~32
  u32 u32_Irq_Force3;     //force 63~48
  u32 u32_Irq_Mask0;      //mask 15~0
  u32 u32_Irq_Mask1;      //mask 31~16
  u32 u32_Irq_Mask2;      //mask 47~32
  u32 u32_Irq_Mask3;      //mask 63~48
  u32 u32_Irq_Polarity0;  //polarity 15~0
  u32 u32_Irq_Polarity1;  //polarity 31~16
  u32 u32_Irq_Polarity2;  //polarity 47~32
  u32 u32_Irq_Polarity3;  //polarity 63~48
  u32 u32_Irq_Status0;    //polarity 15~0
  u32 u32_Irq_Status1;    //polarity 31~16
  u32 u32_Irq_Status2;    //polarity 47~32
  u32 u32_Irq_Status3;    //polarity 63~48
}KeIrqControl_t;

extern volatile KeIrqControl_t* const g_pKeIrqControl;

typedef struct KeIrqControl_1_s
{
  u32 u32_Fiq_Force0;     //force 15~0
  u32 u32_Fiq_Force1;     //force 31~16
  u32 u32_Fiq_Force2;     //force 47~32
  u32 u32_Fiq_Force3;     //force 63~48
  u32 u32_Fiq_Mask0;      //mask 15~0
  u32 u32_Fiq_Mask1;      //mask 31~16
  u32 u32_Fiq_Mask2;      //mask 47~32
  u32 u32_Fiq_Mask3;      //mask 63~48
  u32 u32_Fiq_Polarity0;  //polarity 15~0
  u32 u32_Fiq_Polarity1;  //polarity 31~16
  u32 u32_Fiq_Polarity2;  //polarity 47~32
  u32 u32_Fiq_Polarity3;  //polarity 63~48
  u32 u32_Fiq_Status0;    //polarity 15~0
  u32 u32_Fiq_Status1;    //polarity 31~16
  u32 u32_Fiq_Status2;    //polarity 47~32
  u32 u32_Fiq_Status3;    //polarity 63~48
  u32 u32_Irq_Force0;     //force 15~0
  u32 u32_Irq_Force1;     //force 31~16
  u32 u32_Irq_Force2;     //force 47~32
  u32 u32_Irq_Force3;     //force 63~48
  u32 u32_Irq_Mask0;      //mask 15~0
  u32 u32_Irq_Mask1;      //mask 31~16
  u32 u32_Irq_Mask2;      //mask 47~32
  u32 u32_Irq_Mask3;      //mask 63~48
  u32 u32_Irq_Polarity0;  //polarity 15~0
  u32 u32_Irq_Polarity1;  //polarity 31~16
  u32 u32_Irq_Polarity2;  //polarity 47~32
  u32 u32_Irq_Polarity3;  //polarity 63~48
  u32 u32_Irq_Status0;    //polarity 15~0
  u32 u32_Irq_Status1;    //polarity 31~16
  u32 u32_Irq_Status2;    //polarity 47~32
  u32 u32_Irq_Status3;    //polarity 63~48
}KeIrqControl_1_t;

extern volatile KeIrqControl_1_t* const g_pKeIrqControl_1;


#if 0
/****************************************************************************/
/*        Interrupt Controller (ITCTRL) registers                           */
/****************************************************************************/
typedef struct W5IrqControl_s
{
  u32 u32_Priority12;   // 0x1800: INT0  to INT7 (0 highest, 7 lowest)
  u32 u32_Priority34;   // 0x1804: INT8  to INT15
  u32 u32_Priority56;   // 0x1808: INT16 to INT23
  u32 u32_Priority78;   // 0x180C: INT24 to INT31
  u32 u32_Priority910;  // 0x1810: INT32 to INT39
  u32 u32_Mapping0;     // 0x1814: INT0  to INT31 / 0=IRQ0n, 1=IRQ1n
  u32 u32_Mapping1;     // 0x1818: INT31 to INT63 / 0=IRQ0n, 1=IRQ1n
  u32 u32_Mask0;        // 0x181C: INT0  to INT31 / 0=masked, 1=not masked
  u32 u32_Mask1;        // 0x1820: INT31 to INT63 / 0=masked, 1=not masked
  u32 u32_Sensitivity0; // 0x1824: INT0  to INT31 / 0=edge, 1=level
  u32 u32_Sensitivity1; // 0x1828: INT31 to INT63 / 0=edge, 1=level
  u32 u32_Polarity0;    // 0x182C: INT0  to INT31 / 0=low,neg, 1=high,pos
  u32 u32_Polarity1;    // 0x1830: INT31 to INT63 / 0=low,neg, 1=high,pos
  u32 u32_Reentrant0;   // 0x1834: INT0  to INT31 / 0=not reentrant, 1=reentrant
  u32 u32_Reentrant1;   // 0x1838: INT31 to INT63 / 0=not reentrant, 1=reentrant
  u32 u32_Pending0;     // 0x183C: IRQ0n
  u32 u32_Pending1;     // 0x1840: IRQ1n
  u32 u32_RawStatus0;   // 0x1844: INT0  to INT31 / 0=not pending, 1=pending (before mask)
  u32 u32_RawStatus1;   // 0x1848: INT31 to INT63 / 0=not pending, 1=pending (before mask)
  u32 u32_Status0;      // 0x184C: INT0  to INT31 / 0=not pending, 1=pending
  u32 u32_Status1;      // 0x1850: INT31 to INT63 / 0=not pending, 1=pending
  u32 u32_Clear0;       // 0x1854: INT0  to INT31 / 0=no effect, 1=clear interrupt (EOI for an it)
  u32 u32_Clear1;       // 0x1858: INT31 to INT63 / 0=no effect, 1=clear interrupt (EOI for an it)
  u32 u32_Ack0;         // 0x185C: INT0  to INT31 / 0=no effect, 1=acknowledge interrupt
  u32 u32_Ack1;         // 0x1860: INT31 to INT63 / 0=no effect, 1=acknowledge interrupt
  u32 u32_Service0;     // 0x1864: INT0  to INT31 / 0=not in service, 1=ack but not cleared
  u32 u32_Service1;     // 0x1868: INT31 to INT63 / 0=not in service, 1=ack but not cleared
  u32 au32_Pad1[4];
  u32 u32_WakeUpMask0;  // 0x187C: INT0  to INT31 / 0=masked, 1=not masked
  u32 u32_WakeUpMask1;  // 0x1880: INT31 to INT63 / 0=masked, 1=not masked
  u32 u32_Config;       // 0x1884: clear all pending it (EOI) or autoack config
  u32 au32_Pad2[2];
  u32 u32_Priority1112; // 0x1890: INT40 to INT47 (0 highest, 7 lowest)
  u32 u32_Priority1314; // 0x1894: INT48 to INT55
  u32 u32_Priority1516; // 0x1898: INT56 to INT63
} W5IrqControl_t;

/****************************************************************************/
/*        External interrupt Controller registers                           */
/****************************************************************************/
typedef struct W5ExtInt_s
{
    u32 u32_clk_deb_cfg;    // 0x1C00
    u32 u32_cfg0;           // 0x1C04
    u32 u32_cfg1;           // 0x1C08
    u32 u32_cfg2;           // 0x1C0C
    u32 u32_cfg3;           // 0x1C10
    u32 u32_int_raw_status; // 0x1C14
    u32 u32_int_clear;      // 0x1C18
    u32 u32_int_mask1;      // 0x1C1C
    u32 u32_int_status1;    // 0x1C20
    u32 u32_int_mask2;      // 0x1C24
    u32 u32_int_status2;    // 0x1C28
    u32 u32_int_mask3;      // 0x1C2C
    u32 u32_int_status3;    // 0x1C30
    u32 u32_int_mask4;      // 0x1C34
    u32 u32_int_status4;    // 0x1C38
    u32 u32_int_mask5;      // 0x1C3C
    u32 u32_int_status5;    // 0x1C40
    u32 u32_int_mask6;      // 0x1C44
    u32 u32_int_status6;    // 0x1C48
    u32 u32_int_mask7;      // 0x1C4C
    u32 u32_int_status7;    // 0x1C50
    u32 u32_int_mask8;      // 0x1C54
    u32 u32_int_status8;    // 0x1C58
    u32 u32_spare;          // 0x1C5C
} W5ExtInt_t;

extern volatile W5IrqControl_t* const g_ptW5IrqControl;
extern volatile W5ExtInt_t* const g_ptW5ExtInt;
#endif
#endif // __KERNEL_ITCTRL_H__

