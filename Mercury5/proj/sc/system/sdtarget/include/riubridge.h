/******************************************************************************/
/* File     : riubridge.h                                                     */
/*----------------------------------------------------------------------------*/
/* Scope    : RIU bridge definitions                                          */
/*                                                                            */
/******************************************************************************/

#ifndef __RIUBRIDGE_H__
#define __RIUBRIDGE_H__

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define HAL_RIU_BRIDGE_BASE     0x74000000
#define RIU_OFF_SHIFT           2

//-----------------------------------------------------------------------
// EMI_MAIN CONFIG
//-----------------------------------------------------------------------
#define HAL_RIU_EMI_MAIN_BASE   (HAL_RIU_BRIDGE_BASE + (0x0800 << RIU_OFF_SHIFT))
//-----------------------------------------------------------------------
// EMI_SMC (Dynamic Memory Controler) CONFIG
//-----------------------------------------------------------------------
#define HAL_RIU_EMI_DMC_BASE    (HAL_RIU_BRIDGE_BASE + (0x0900 << RIU_OFF_SHIFT))
//-----------------------------------------------------------------------
// EMI_SMC (Static Memory Controler) CONFIG
//-----------------------------------------------------------------------
#define HAL_RIU_EMI_SMC_BASE    (HAL_RIU_BRIDGE_BASE + (0x0A00 << RIU_OFF_SHIFT))
//-----------------------------------------------------------------------
// EMI_SC (Static Memory Controler) CONFIG
//-----------------------------------------------------------------------
#define HAL_RIU_EMI_SC_BASE     (HAL_RIU_BRIDGE_BASE + (0x0B00 << RIU_OFF_SHIFT))

#define HAL_RIU_PLLTOP_BASE     (HAL_RIU_BRIDGE_BASE + (0x1900 << RIU_OFF_SHIFT))
#define HAL_RIU_PADCTRL_BASE    (HAL_RIU_BRIDGE_BASE + (0x1980 << RIU_OFF_SHIFT))
#if defined(__BRAVO__) ||  defined(__MSW8522__) || defined(__MSW8556__)
#define HAL_RIU_PSPI_BASE       (HAL_RIU_BRIDGE_BASE + (0x1400 << RIU_OFF_SHIFT))
#else
#define HAL_RIU_PSPI_BASE       (HAL_RIU_BRIDGE_BASE + (0x1B00 << RIU_OFF_SHIFT))
#endif // __BRAVO__
#define HAL_RIU_PMU_BASE        (HAL_RIU_BRIDGE_BASE + (0x1B80 << RIU_OFF_SHIFT))
#define HAL_RIU_GPIOCTRL0_BASE  (HAL_RIU_BRIDGE_BASE + (0x1D00 << RIU_OFF_SHIFT))
#define HAL_RIU_GPIOCTRL1_BASE  (HAL_RIU_BRIDGE_BASE + (0x1D80 << RIU_OFF_SHIFT))
#define HAL_RIU_GPIOCTRL2_BASE  (HAL_RIU_BRIDGE_BASE + (0x1E00 << RIU_OFF_SHIFT))
#define HAL_RIU_BBTOP0_BASE     (HAL_RIU_BRIDGE_BASE + (0x1F00 << RIU_OFF_SHIFT))

#endif  // __RIUBRIDGE_H__
