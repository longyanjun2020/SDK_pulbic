////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    hal_int_irq_pub.h
* @version
* @brief   HAL header for interrupt
*
*/

#ifndef __HAL_INT_IRQ_PUB_H__
#define __HAL_INT_IRQ_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/* [GIC]
        ID   0 -  15 : SGI
        ID  16 -  31 : PPI
        ID  32 -  63 : ARM_INTERNAL
        ID  64 - 127 : MS_IRQ (GIC_HWIRQ_MS_START)
        ID 128 - 159 : MS_FIQ
   [PMSLEEP]
        ID   0 -  31 : MS_PM_IRQ
*/
#if 1//defined(__MV5_FPGA__)
#define INTC_ID_TOTAL           (160 + 32 + 32) //(160) //__MV5_FPGA__

#define GIC_SGI_NR                 16
#define GIC_PPI_NR                 16

#define GIC_SPI_ARM_INTERNAL_NR    32
#define GIC_SPI_MS_IRQ_NR          96 //64 //__MV5_FPGA__
#define GIC_SPI_MS_FIQ_NR          64 //32 //__MV5_FPGA__
#else //#if defined(__MV5_FPGA__)
#define INTC_ID_TOTAL           (160)

#define GIC_SGI_NR                 16
#define GIC_PPI_NR                 16
#define GIC_SPI_ARM_INTERNAL_NR    32
#define GIC_SPI_MS_IRQ_NR          64
#define GIC_SPI_MS_FIQ_NR          32
#endif //#if defined(__MV5_FPGA__)

#define GIC_HWIRQ_MS_START        (GIC_SGI_NR + GIC_PPI_NR + GIC_SPI_ARM_INTERNAL_NR)

#define GIC_SPI_MS_IRQ_START       GIC_HWIRQ_MS_START
#define GIC_SPI_MS_IRQ_END        (GIC_SPI_MS_IRQ_START + GIC_SPI_MS_IRQ_NR)
#define GIC_SPI_MS_FIQ_START       GIC_SPI_MS_IRQ_END
#define GIC_SPI_MS_FIQ_END        (GIC_SPI_MS_FIQ_START + GIC_SPI_MS_FIQ_NR)



//NOTE(Spade): We count from GIC_SPI_ARM_INTERNAL because interrupt delcaration in dts is from SPI 0
/* MS_NON_PM_IRQ 32-95 */
#define GIC_SPI_MS_IRQ_START       GIC_HWIRQ_MS_START


/**
 * Number of interruption lines
 */
#define IT_MAX_NUMBER   INTC_ID_TOTAL//64

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * The interrupt line can be mapped on IRQ or FIQ
 */
typedef enum
{
    INTC_MAP_FIQ=0,
    INTC_MAP_IRQ,
    INTC_MAP_MAX
} IntcMap_e;

/**
 * Sensitivity type
 */
typedef enum
{
    INTC_SENSITIVITY_EDGE=0, /// edge detect
    INTC_SENSITIVITY_LEVEL,  /// level detect
    INTC_SENSITIVITY_MAX
} IntcSensitivity_e;

/**
 * Polarity of the interrupt line
 */
typedef enum
{
    INTC_POLARITY_LOW=0,
    INTC_POLARITY_HIGH,
    INTC_POLARITY_MAX
} IntcPolarity_e;

/**
 * Priority of the interrupt line
 */
typedef u8	IntcPriority_e;

#define    INTC_PRIORITY_0		0
#define    INTC_PRIORITY_1		1
#define    INTC_PRIORITY_2		2
#define    INTC_PRIORITY_3		3
#define    INTC_PRIORITY_4		4
#define    INTC_PRIORITY_5		5
#define    INTC_PRIORITY_6		6
#define    INTC_PRIORITY_7		7
#define    INTC_PRIORITY_8		8
#define    INTC_PRIORITY_9		9
#define    INTC_PRIORITY_10		10
#define    INTC_PRIORITY_11		11
#define    INTC_PRIORITY_12		12
#define    INTC_PRIORITY_13		13
#define    INTC_PRIORITY_14		14
#define    INTC_PRIORITY_15		15
#define    INTC_PRIORITY_MAX    16


/**
 * Clear type
 */
typedef enum
{
    INTC_CLEAR_PRE=0,  /// auto-clear before isr invocation
    INTC_CLEAR_POST,   /// auto-clear after isr invocation
    INTC_CLEAR_MANUAL, /// manual clear
    INTC_CLEAR_MAX
} IntcClear_e;

/**
 * Interrupt Service Routine type
 */
typedef void (*PfnIntcISR)(void);

/*typedef struct
{
    IntcMap_e         eMap;         /// IRQ or FIQ
    IntcSensitivity_e eSensitivity; /// EDGE or LEVEL
    IntcPolarity_e    ePolarity;    ///
    IntcPriority_e    ePriority;    ///
    IntcClear_e       eClear;       ///
    bool              bReEntrant;   /// is reentrance allowed for this interruption
    bool              bWakeUp;      /// is waikup allowed for this interruption
    bool              bAutoMask;    /// mask interrupt after IRQ is served
    PfnIntcISR        pfnIsr;
} IntcParam_t;*/


typedef struct
{
    IntcMap_e         eMap;         /// IRQ or FIQ
    IntcPriority_e    ePriority;    ///
    PfnIntcISR        pfnIsr;
} IntcParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

#endif //__HAL_INT_IRQ_PUB_H__

