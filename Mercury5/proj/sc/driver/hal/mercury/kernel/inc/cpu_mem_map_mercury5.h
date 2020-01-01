/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright MSTAR SAS (c) 2007
*/
/////////////////////////////////////////////////////////////////////////
//                                                                     //
// Asic          : Mercury5                                            //
// File name     : cpu_mem_map_mercury5.h                              //
// Author        :                                                     //
// Purpose       :                                                     //
// hierarchy     :                                                     //
//                                                                     //
// Notes         :                                                     //
// Synthetisable : yes                                                 //
//                                                                     //
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Notes:                                                              //
//                                                                     //
//    This file is the definition of the cpu memory map. All base      //
//    addresses of AHB slaves and peripherals (through the bridge) are //
//    defined here.                                                    //
//                                                                     //
/////////////////////////////////////////////////////////////////////////
#ifndef __CPU_MEM_MAP_MERCURY5_H__
#define __CPU_MEM_MAP_MERCURY5_H__

//=======================================================================
// Definition of the number of slaves on AHB bus.
// This number does not include default slave.
//=======================================================================

// there is 13 slaves defined :
// - On Chip ROM
// - On Chip RAM
// - MEM0
// - MEM1
// - MEM2
// - MEM3
// - USR0
// - USR1
// - USR2
// - PERIPH
// - PERIPH 32 BITS
// - DPRAM_DSP
// - SHIFACE

#define NB_AHB_SLAVES   17
#define MAIN_OFFSET     0x00000000

//=======================================================================
// Definition of the HADDR bits used to generate the Chip Select signals
// of the different AHB slaves
//=======================================================================
// HADDR[AHB_ADD_MSB:AHB_ADD_LSB] is used by the address decoder to
// generate the chip select
#define AHB_ADD_MSB     30
#define AHB_ADD_LSB     25

//MSB or LSB can range from 0 to 31 -> 5 bit are required to code IDX
#define XSB_IDX_WIDTH   5

//=======================================================================
// Definition of the addresses ranges
// note that adresses out of range will select
// default slave.
//=======================================================================

// COMMON space definition
#define COMMON_START_ADDRESS       0x00000000
#define COMMON_END_ADDRESS         0x03FFFFFF
#define COMMON_ADD_LSB             0x1A //26 //64 Mbytes boundary

#define SPI_START_ADDRESS          0x14000000
#define SPI_END_ADDRESS            0x15FFFFFF

#define GIC_START_ADDRESS          0x16000000
#define GIC_END_ADDRESS            0x16003FFF

#define IO_START_ADDRESS           0x1F000000
#define IO_END_ADDRESS             0x1F03FFFF

#define IMI_START_ADDRESS          0xA0000000
#define IMI_END_ADDRESS            0xA0015FFF //I1 88k
//#define IMI_END_ADDRESS            0xA0013FFF //I3 128k

// Off chip MEM1 space definition (through EMI)

#define MEM1_START_ADDRESS         0x20000000
#define MEM1_END_ADDRESS           (0x20000000 + SYS_PHY_RAM_SIZE_SETTING)//0x28000000 //default 128MB
#define MEM1_ADD_LSB               0x1A //26 //64 Mbytes boundary

//Off chip MEM3 space definition (through EMI Serial Flash)
#define MEM3_START_ADDRESS         0x14000000
#define MEM3_END_ADDRESS           0x1BFFFFFF
#define MEM3_ADD_LSB               0x1A //26 //64 Mbytes boundary

#define IMI2_START_ADDRESS          0xA0000000
#define IMI2_END_ADDRESS            0xA0015FFF //I1 88k
//#define IMI2_END_ADDRESS            0xA0013FFF //I3 128k

//======================================================================
//====================== MIU address domain ============================
//======================================================================

#define MIU_BASE_PHYADDR                    MEM1_START_ADDRESS
#define MIU_ADDR_MASK                       0x3FFFFFFF
#define MIU_MAX_PHYADDR                     MEM1_END_ADDRESS

// define DUMMY address for periph which do not
// have a mapping yet.
#define TO_BE_DEFINED                       0xFFFFFFFF

// Register macros
#define REG(Reg_Addr)                       (*(volatile U16*)(Reg_Addr))
#define GET_REG_ADDR(x, y)                  ((x) + ((y) << 2))
#define GET_BASE_ADDR_BY_BANK(x, y)         ((x) + ((y) << 1))

#define MS_BASE_INTERRUPT_CONTROLLER_PA     (0x16001000)
#define MS_INTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET 0x1000

#define MS_BASE_REG_RIU_PA                  (0x1F000000)
#define MS_BASE_REG_IMI_PA                  (0xA0000000)
#define MS_BASE_REG_FUART_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x110200)
#define MS_BASE_REG_URDMA_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x110300)
#define MS_BASE_REG_UART0_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x110800)
#define MS_BASE_REG_UART1_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x110900)
#define MS_BASE_REG_UART2_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x110400)
#define MS_BASE_REG_WDT_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x003000)
#define MS_BASE_REG_TIMER0_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x003020)
#define MS_BASE_REG_CHIPTOP_PA              GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x101E00)
#define MS_BASE_REG_INTRCTL_PA              GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x100900)
#define MS_BASE_REG_INTRCTL_1_PA            GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x100B00)
#define MS_BASE_REG_FSP_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x0016C0) // CHECK
#define MS_BASE_REG_QSPI_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x001780) // CHECK
#define MS_BASE_REG_PWM_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x001A00)
#define MS_BASE_REG_PWM2_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x001B00)
#define MS_BASE_REG_CLKGEN_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x103800)
#define MS_BASE_REG_IIC0_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x111800)
#define MS_BASE_REG_IIC1_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x111900)
#define MS_BASE_REG_IIC2_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x111500)
#define MS_BASE_REG_IIC3_PA                 GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x111600)
#define MS_BASE_REG_DPHY_CSI_ANA_PA         GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120200)
#define MS_BASE_REG_DPHY_CSI_DIG_PA         GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120300)
#define MS_BASE_REG_CSI_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120400)
#define MS_BASE_REG_DPHY_CSI_ANA_4LANE_PA   GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120500)
#define MS_BASE_REG_DPHY_CSI_DIG_4LANE_PA   GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120600)
#define MS_BASE_REG_CSI_4LANE_PA            GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x120700)
#define MS_BASE_REG_VIF_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x131200)
#define MS_BASE_REG_DEC_GP_CTL_PA           GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x111370)
#define MS_BASE_REG_SC_GP_CTRL_PA           GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x113300)
#define MS_BASE_REG_PM_SLEEP_CKG_PA         GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x000E00)
#define MS_BASE_REG_MIU_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x101200)
#define MS_BASE_REG_DMAGEN_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x153000)
#define MS_BASE_REG_AESDMA_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x112200)
#define MS_BASE_REG_L3_BRIDGE_PA            GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x102200)
#define MS_BASE_REG_BDMA0_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x100200)
#define MS_BASE_REG_BDMA1_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x100220) // CHECK
#define MS_BASE_REG_RTC_PA                  GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x001200)
#define MS_BASE_REG_RTC_PWC_PA              GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x003400)
#define MS_BASE_REG_DIP_HVSP_PA             GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x161600)
#define MS_BASE_REG_DIP_TOP_PA              GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x161700)
#define MS_BASE_REG_DIP_PDW_PA              GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x161800)
#define MS_BASE_REG_SARADC_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x001400)
#define MS_BASE_REG_BACH0_PA                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x150200)
#define MS_BASE_REG_ARMPLL_PA               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, 0x103200)


#define BASE_REG_TIMER                      MS_BASE_REG_TIMER0_PA
#define TIMER0_BASE_REG                     GET_REG_ADDR(BASE_REG_TIMER, 0x00)
#define TIMER1_BASE_REG                     GET_REG_ADDR(BASE_REG_TIMER, 0x10)
#define TIMER2_BASE_REG                     GET_REG_ADDR(BASE_REG_TIMER, 0x20)

#define BASE_REG_INTRCTL                    MS_BASE_REG_INTRCTL_PA
#define HST0_BASE_REG                       GET_REG_ADDR(BASE_REG_INTRCTL, 0x00)
#define HST1_BASE_REG                       GET_REG_ADDR(BASE_REG_INTRCTL, 0x20)
#define HST2_BASE_REG                       GET_REG_ADDR(BASE_REG_INTRCTL, 0x40)
#define HST3_BASE_REG                       GET_REG_ADDR(BASE_REG_INTRCTL, 0x60)

#define BASE_REG_INTRCTL_1                  MS_BASE_REG_INTRCTL_1_PA
#define HST0_1_BASE_REG                     GET_REG_ADDR(BASE_REG_INTRCTL_1, 0x00)
#define HST1_1_BASE_REG                     GET_REG_ADDR(BASE_REG_INTRCTL_1, 0x20)
#define HST2_1_BASE_REG                     GET_REG_ADDR(BASE_REG_INTRCTL_1, 0x40)
#define HST3_1_BASE_REG                     GET_REG_ADDR(BASE_REG_INTRCTL_1, 0x60)

#define BASE_REG_BACH_0                     MS_BASE_REG_BACH0_PA
#define BACH0_DMA_TEST_CTRL5_REG            GET_REG_ADDR(BASE_REG_BACH_0, 0x75)

//======================================================================
//====================== vmalloc address ===============================
//======================================================================

#define VMALLOC_START_ADDRESS               0xDE000000
#define VMALLOC_ADDR_LEN                    0x02000000
#define VMALLOC_END_ADDRESS                 (VMALLOC_START_ADDRESS+VMALLOC_ADDR_LEN-1)

#endif //__CPU_MEM_MAP_MERCURY5_H__
