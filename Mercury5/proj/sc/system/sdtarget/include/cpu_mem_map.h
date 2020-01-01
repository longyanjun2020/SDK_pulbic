#ifndef __CPU_MEM_MAP_H__
#define __CPU_MEM_MAP_H__

//======================================================================
// Definition of the number of slaves on AHB bus.
// This number does not include default slave.
//======================================================================

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


//======================================================================
// Definition of the HADDR bits used to generate the Chip Select signals
// of the different AHB slaves
//======================================================================
// HADDR[AHB_ADD_MSB:AHB_ADD_LSB] is used by the address decoder to
// generate the chip select
#define AHB_ADD_MSB     30
#define AHB_ADD_LSB     25


//MSB or LSB can range from 0 to 31 -> 5 bit are required to code IDX
#define XSB_IDX_WIDTH   5


//======================================================================
// Definition of the addresses ranges
// note that adresses out of range will select
// default slave.
//======================================================================

// COMMON space definition

#define COMMON_START_ADDRESS        0x00000000
#define COMMON_END_ADDRESS          0x03FFFFFF
#define COMMON_ADD_LSB              0x1A    //26 //64 Mbytes boundary

// On chip ROM space definition (through IMI)
#define IROM_START_ADDRESS          0x04000000
#define IROM_END_ADDRESS            0x07FFFFFF
#define IROM_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// On chip RAM space definition (through IMI)
#define IRAM_START_ADDRESS          0x08000000
#define IRAM_END_ADDRESS            0x0BFFFFFF
#define IRAM_ADD_LSB                0x1A    //26 //64 Mbytes boundary

/* +AKO and LSM - 29/08/05 */
#define IRAM_DSP_START_ADDRESS      0x20000
/* -AKO and LSM - 29/08/05 */

// Off chip MEM0 space definition (through EMI)
#define MEM0_START_ADDRESS          0x0C000000
#define MEM0_END_ADDRESS            0x0FFFFFFF
#define MEM0_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// Off chip MEM1 space definition (through EMI)
#define MEM1_START_ADDRESS          0x10000000
#define MEM1_END_ADDRESS            0x13FFFFFF
#define MEM1_ADD_LSB                0x1A    //26 //64 Mbytes boundary

//Off chip MEM2 space definition (through EMI)
#define MEM2_START_ADDRESS          0x14000000
#define MEM2_END_ADDRESS            0x17FFFFFF
#define MEM2_ADD_LSB                0x1A    //26 //64 Mbytes boundary

//Off chip MEM3 space definition (through EMI)
#define MEM3_START_ADDRESS          0x18000000
#define MEM3_END_ADDRESS            0x1BFFFFFF
#define MEM3_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// Off chip USR0 space definition (through EMI)
#define USR0_START_ADDRESS          0x1C000000
#define USR0_END_ADDRESS            0x1FFFFFFF
#define USR0_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// Off chip USR1 space definition (through EMI)
#define USR1_START_ADDRESS          0x20000000
#define USR1_END_ADDRESS            0x23FFFFFF
#define USR1_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// Off chip USR2 space definition (through EMI)
#define USR2_START_ADDRESS          0x24000000
#define USR2_END_ADDRESS            0x27FFFFFF
#define USR2_ADD_LSB                0x1A    //26 //64 Mbytes boundary

// On chip ETB RAM space definition (through ETB IF)
#define ETBRAM_START_ADDRESS        0x28000000
#define ETBRAM_END_ADDRESS          0x2BFFFFFF
#define ETBRAM_ADD_LSB              0x1A    //26 //64 Mbytes boundary

// On chip ITCM space definition (through IMI and dedicated CPU IF)
#define ITCMRAM_START_ADDRESS       0x2C000000
#define ITCMRAM_END_ADDRESS         0x2FFFFFFF
#define ITCMRAM_ADD_LSB             0x1A    //26 //64 Mbytes boundary

// On chip DTCM space definition (through IMI and dedicated CPU IF)
#define DTCMRAM_START_ADDRESS       0x30000000
#define DTCMRAM_END_ADDRESS         0x33FFFFFF
#define DTCMRAM_ADD_LSB             0x1A    //26 //64 Mbytes boundary

// PERIPH space definition (through AHB to APB bridges)
#define PERIPH_START_ADDRESS        0x34000000
#define PERIPH_END_ADDRESS          0x37FFFFFF
#define PERIPH_ADD_LSB              0x19    //25 //32 Mbytes boundary

// GSS space definition (through AHB2AHB bridge)
#define GSS_START_ADDRESS           0x38000000
#define GSS_END_ADDRESS             0x3BFFFFFF
#define GSS_ADD_LSB                 0x1A    //26 //64 Mbytes boundary

// SDRAM CONFIG space definition
// (unfortunately must be defined as a primary space address
//  because there is only one AHB IF on SDRAM CTRL shared between config and data).
#define PORT0_CFG_START_ADDRESS     0x3C000000
#define PORT0_CFG_END_ADDRESS       0x3FFFFFFF
#define PORT0_CFG_ADD_LSB           0x1A    //26 //64 Mbytes boundary

// SDRAM space definition (through SDRAM controller)
#define SDRAM_START_ADDRESS         0x40000000
#define SDRAM_END_ADDRESS           0x47FFFFFF
#define SDRAM_ADD_LSB               0x1A    //27 //128 Mbytes boundary

// NAND_FLASH space definition (through NAND_FLASH controller)
#define NAND_FLASH_DPRAM_START_ADDRESS  0x48000000
#define NAND_FLASH_DPRAM_END_ADDRESS    0x4BFFFFFF
#define NAND_FLASH_DPRAM_ADD_LSB        0x1A    //26 //64 Mbytes boundary

// NAND_FLASH space definition (through NAND_FLASH controller)
#define RFDL_SHIFACE_DPRAM_START_ADDRESS    0x50000000
#define RFDL_SHIFACE_DPRAM_END_ADDRESS      0x53FFFFFF
#define RFDL_SHIFACE_DPRAM_ADD_LSB          0x1A    //26 //64 Mbytes boundary


//======================================================================
// Definition of the sub addresses
// for the bridges.
//======================================================================

// PERIPH space definition (through AHB to APB bridge 0)
#define PERIPH0_OFFSET_ADDRESS      0x00000000
#define PERIPH0_START_ADDRESS       (PERIPH_START_ADDRESS + PERIPH0_OFFSET_ADDRESS)

// PERIPH space definition (through AHB to APB bridge 1)
#define PERIPH1_OFFSET_ADDRESS      0x00004000
#define PERIPH1_START_ADDRESS       (PERIPH_START_ADDRESS + PERIPH1_OFFSET_ADDRESS)

// PERIPH space definition (through AHB to APB bridge 2)
#define PERIPH2_OFFSET_ADDRESS      0x00008000
#define PERIPH2_START_ADDRESS       (PERIPH_START_ADDRESS + PERIPH2_OFFSET_ADDRESS)

// PERIPH space definition (through AHB to APB bridge 3)
#define PERIPH3_OFFSET_ADDRESS      0x0000C000
#define PERIPH3_START_ADDRESS       (PERIPH_START_ADDRESS + PERIPH3_OFFSET_ADDRESS)

//======================================================================
// Definition of the sub addresses
// for periph directly connected to AHB.
//======================================================================

// DMA config space definition (directly on AHB)
#define DMAC_CFG_OFFSET_ADDRESS     0x00010000
#define DMAC_CFG_START_ADDRESS      (PERIPH_START_ADDRESS + DMAC_CFG_OFFSET_ADDRESS)

// ETB config space definition (directly on AHB)
#define ETB_CFG_OFFSET_ADDRESS      0x00014000
#define ETB_CFG_START_ADDRESS       (PERIPH_START_ADDRESS + ETB_CFG_OFFSET_ADDRESS)

// USB config space definition (directly on AHB)
#define USB_CFG_OFFSET_ADDRESS      0x00018000
#define USB_CFG_START_ADDRESS       (PERIPH_START_ADDRESS + USB_CFG_OFFSET_ADDRESS)

// SDMMC config and data space definition (directly on AHB)
#define SDMMC_CFG_OFFSET_ADDRESS    0x0001C000
#define SDMMC_CFG_START_ADDRESS     (PERIPH_START_ADDRESS + SDMMC_CFG_OFFSET_ADDRESS)

// SDRAM config space definition (directly on AHB)
#define SDRAM_CFG_OFFSET_ADDRESS    0x00000000
#define SDRAM_CFG_START_ADDRESS     (PORT0_CFG_START_ADDRESS + SDRAM_CFG_OFFSET_ADDRESS)


//======================================================================
// Definition of the sub addresses
// for shiface dpram and rfdl.
//======================================================================
#define RF_DL_OFFSET_ADDRESS            0x00000000
#define RF_DL_START_ADDRESS             (RFDL_SHIFACE_DPRAM_START_ADDRESS + RF_DL_OFFSET_ADDRESS)

#define SHIFACE_DPRAM_OFFSET_ADDRESS    0x00001000
#define SHIFACE_DPRAM_START_ADDRESS     (RFDL_SHIFACE_DPRAM_START_ADDRESS + SHIFACE_DPRAM_OFFSET_ADDRESS)


//======================================================================
// Definition of the sub addresses
// for the peripherals.
//======================================================================

// define DUMMY address for periph which do not
// have a mapping yet.
#define TO_BE_DEFINED               0xFFFFFFFF

// this values are repeated to be parsed by script
#define COMMON_BASE_ADD             COMMON_START_ADDRESS
#define IROM_BASE_ADD               IROM_START_ADDRESS
#define IRAM_BASE_ADD               IRAM_START_ADDRESS
#define IRAM_DSP_BASE_ADD           IRAM_DSP_START_ADDRESS
#define MEM0_BASE_ADD               MEM0_START_ADDRESS
#define MEM1_BASE_ADD               MEM1_START_ADDRESS
#define MEM2_BASE_ADD               MEM2_START_ADDRESS
#define MEM3_BASE_ADD               MEM3_START_ADDRESS
#define USR0_BASE_ADD               USR0_START_ADDRESS
#define USR1_BASE_ADD               USR1_START_ADDRESS
#define USR2_BASE_ADD               USR2_START_ADDRESS
#define ETBRAM_BASE_ADD             ETBRAM_START_ADDRESS
#define ITCMRAM_BASE_ADD            ITCMRAM_START_ADDRESS
#define DTCMRAM_BASE_ADD            DTCMRAM_START_ADDRESS
#define GSS_BASE_ADD                GSS_START_ADDRESS
#define SDRAM_BASE_ADD              SDRAM_START_ADDRESS
#define NAND_FLASH_DPRAM_BASE_ADD   NAND_FLASH_DPRAM_START_ADDRESS

#define DMAC_CFG_BASE_ADD           DMAC_CFG_START_ADDRESS
#define ETB_CFG_BASE_ADD            ETB_CFG_START_ADDRESS
#define USB_CFG_BASE_ADD            USB_CFG_START_ADDRESS
#define SDMMC_CFG_BASE_ADD          SDMMC_CFG_START_ADDRESS
#define SDRAM_CFG_BASE_ADD          SDRAM_CFG_START_ADDRESS
#define RF_DL_BASE_ADD              RF_DL_START_ADDRESS
#define SHIFACE_DPRAM_BASE_ADD      SHIFACE_DPRAM_START_ADDRESS


//======================================================================
//======================================================================
//====================== PERIPH 0 peripherals ==========================
//======================================================================
//======================================================================

//----------------------------------------------------------------------
// CLKGEN
//----------------------------------------------------------------------
#define WHAT_CMU_OFFSET_BASE_ADD    0x00000000
#define WHAT_CMU_BASE_ADD           (PERIPH0_START_ADDRESS + WHAT_CMU_OFFSET_BASE_ADD)


#define WHAT_CMU_GPR_CTRL0_OFFSET_ADD	0x00000030
/*global register definitions */
#define WHAT_CMU_GPR_CTRL0_ADD	    (WHAT_CMU_BASE_ADD	+	WHAT_CMU_GPR_CTRL0_OFFSET_ADD)

//----------------------------------------------------------------------
// SYSREG
//----------------------------------------------------------------------
#define SYS_APB_REG_OFFSET_BASE_ADD 0x00000400
#define SYS_APB_REG_BASE_ADD        (PERIPH0_START_ADDRESS + SYS_APB_REG_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// KEYPAD
//----------------------------------------------------------------------
#define KEYBOARD_OFFSET_BASE_ADD    0x00000800
#define KEYBOARD_BASE_ADD           (PERIPH0_START_ADDRESS + KEYBOARD_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// PWM
//----------------------------------------------------------------------
#define PWM_OFFSET_BASE_ADD         0x00000C00
#define PWM_BASE_ADD                (PERIPH0_START_ADDRESS + PWM_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// GPIO
//----------------------------------------------------------------------
#define GPIO_OFFSET_BASE_ADD        0x00001000
#define GPIO_BASE_ADD               (PERIPH0_START_ADDRESS + GPIO_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// INT controler
//----------------------------------------------------------------------
#define IT_CTRL_OFFSET_BASE_ADD     0x00001800
#define IT_CTRL_BASE_ADD            (PERIPH0_START_ADDRESS + IT_CTRL_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// external IT
//----------------------------------------------------------------------
#define EXT_INT_OFFSET_BASE_ADD     0x00001C00
#define EXT_INT_BASE_ADD            (PERIPH0_START_ADDRESS + EXT_INT_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// EXICE
//----------------------------------------------------------------------
#define EX_ICE_OFFSET_BASE_ADD      0x00002000
#define EX_ICE_BASE_ADD             (PERIPH0_START_ADDRESS + EX_ICE_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// EMI_CONFIG
//----------------------------------------------------------------------
#define EMI_OFFSET_BASE_ADD         0x00002400
#define EMI_BASE_ADD                (PERIPH0_START_ADDRESS + EMI_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// DEBUG_MATRIX
//----------------------------------------------------------------------
#define DEBUG_MATRIX_OFFSET_BASE_ADD    0x00002800
#define DEBUG_MATRIX_BASE_ADD           (PERIPH0_START_ADDRESS + DEBUG_MATRIX_OFFSET_BASE_ADD)
#define PROBE_REG2SERIAL_BASE_ADD       DEBUG_MATRIX_BASE_ADD

//----------------------------------------------------------------------
// SYS_TIMER
//----------------------------------------------------------------------
#define SYS_TIMER_OFFSET_BASE_ADD   0x00002C00
#define SYS_TIMER_BASE_ADD          (PERIPH0_START_ADDRESS + SYS_TIMER_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// EMI_SMC (Static Memory Controler) CONFIG
//----------------------------------------------------------------------
#define EMI_SMC_OFFSET_BASE_ADD     0x00003800
#define EMI_SMC_BASE_ADD            (PERIPH0_START_ADDRESS + EMI_SMC_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// EMI_SMC (Dynamic Memory Controler) CONFIG
//----------------------------------------------------------------------
#define EMI_DMC_OFFSET_BASE_ADD     0x00003400
#define EMI_DMC_BASE_ADD            (PERIPH0_START_ADDRESS + EMI_DMC_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// EMI_MAIN CONFIG
//----------------------------------------------------------------------
#define EMI_MAIN_OFFSET_BASE_ADD    0x00003000
#define EMI_MAIN_BASE_ADD           (PERIPH0_START_ADDRESS + EMI_MAIN_OFFSET_BASE_ADD)

//-----------------------------------------------------------------------
// RF LOG
//-----------------------------------------------------------------------
#define RF_LOG_OFFSET_BASE_ADD      0x00003A00
#define RF_LOG_BASE_ADD             (PERIPH0_START_ADDRESS + RF_LOG_OFFSET_BASE_ADD)


//======================================================================
//======================================================================
//====================== PERIPH 1 peripherals ==========================
//======================================================================
//======================================================================

//----------------------------------------------------------------------
// I2C interface
//----------------------------------------------------------------------
#define I2C_OFFSET_BASE_ADD         0x00000000
#define I2C_BASE_ADD                (PERIPH1_START_ADDRESS + I2C_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// SPI1
//----------------------------------------------------------------------
#define FS_SPI1_OFFSET_BASE_ADD     0x00000400
#define FS_SPI1_BASE_ADD	        (PERIPH1_START_ADDRESS + FS_SPI1_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// FS_SPI2
//----------------------------------------------------------------------
#define FS_SPI2_OFFSET_BASE_ADD     0x00000800
#define FS_SPI2_BASE_ADD	        (PERIPH1_START_ADDRESS + FS_SPI2_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// UART1
//----------------------------------------------------------------------
#define UART1_OFFSET_BASE_ADD       0x00001000
#define UART1_BASE_ADD              (PERIPH1_START_ADDRESS + UART1_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// UART2
//----------------------------------------------------------------------
#define UART2_OFFSET_BASE_ADD       0x00001400
#define UART2_BASE_ADD              (PERIPH1_START_ADDRESS + UART2_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// IRDA1  register  definitions
//----------------------------------------------------------------------
#define IRDA1_OFFSET_BASE_ADD       0x00001800
#define IRDA1_BASE_ADD              (PERIPH1_START_ADDRESS + IRDA1_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// IRDA2  register  definitions
//----------------------------------------------------------------------
#define IRDA2_OFFSET_BASE_ADD       0x00001C00
#define IRDA2_BASE_ADD              (PERIPH1_START_ADDRESS + IRDA2_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// SIM 1
//----------------------------------------------------------------------
#define SIM1_OFFSET_BASE_ADD        0x00002000
#define SIM1_BASE_ADD               (PERIPH1_START_ADDRESS + SIM1_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// SIM 2
//----------------------------------------------------------------------
#define SIM2_OFFSET_BASE_ADD        0x00002400
#define SIM2_BASE_ADD               (PERIPH1_START_ADDRESS + SIM2_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// NOT_USED
//----------------------------------------------------------------------
#define NOT_USED_OFFSET_BASE_ADD    0x00002800
#define NOT_USED_BASE_ADD           (PERIPH1_START_ADDRESS + NOT_USED_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// GEA coprocessor
//----------------------------------------------------------------------
#define GEA_OFFSET_BASE_ADD         0x00002C00
#define GEA_BASE_ADD                (PERIPH1_START_ADDRESS + GEA_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// FCS coprocessor
//----------------------------------------------------------------------
#define FCS_OFFSET_BASE_ADD         0x00003000
#define FCS_BASE_ADD                (PERIPH1_START_ADDRESS + FCS_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// GEA2 coprocessor
//----------------------------------------------------------------------
#define GEA2_OFFSET_BASE_ADD        0x00003400
#define GEA2_BASE_ADD               (PERIPH1_START_ADDRESS + GEA2_OFFSET_BASE_ADD)


//======================================================================
//======================================================================
//====================== PERIPH 2 peripherals ==========================
//======================================================================
//======================================================================

//----------------------------------------------------------------------
// DSMA
//----------------------------------------------------------------------
#define DSMA_CPU_OFFSET_BASE_ADD    0x00000000
#define DSMA_CPU_BASE_ADD           (PERIPH2_START_ADDRESS + DSMA_CPU_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// Audio
//----------------------------------------------------------------------
#define AUDIO_REG_OFFSET_BASE_ADD   0x00000400
#define AUDIO_REG_BASE_ADD          (PERIPH2_START_ADDRESS + AUDIO_REG_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// DSP timer
//----------------------------------------------------------------------
#define DSP_TIMER_OFFSET_BASE_ADD   0x00000800
#define DSP_TIMER_BASE_ADD          (PERIPH2_START_ADDRESS + DSP_TIMER_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// FRAME COUNTER
//----------------------------------------------------------------------
#define FRAMECNT_CPU_OFFSET_BASE_ADD    0x00000C00
#define FRAMECNT_CPU_BASE_ADD           (PERIPH2_START_ADDRESS + FRAMECNT_CPU_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// Shared interface
//----------------------------------------------------------------------
#define SHIFACE_CPU_OFFSET_BASE_ADD     0x00001000
#define SHIFACE_CPU_BASE_ADD            (PERIPH2_START_ADDRESS + SHIFACE_CPU_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// DSP INT controler
//----------------------------------------------------------------------
#define DSP_ITCTRL_OFFSET_BASE_ADD      0x00001400
#define DSP_ITCTRL_BASE_ADD             (PERIPH2_START_ADDRESS + DSP_ITCTRL_OFFSET_BASE_ADD)
#define TEAKITCTRL_BASE_ADD             DSP_ITCTRL_BASE_ADD

//----------------------------------------------------------------------
// I2S
//----------------------------------------------------------------------
#define I2S_OFFSET_BASE_ADD         0x00001800
#define I2S_BASE_ADD                (PERIPH2_START_ADDRESS + I2S_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// AGC
//----------------------------------------------------------------------
#define AGC_OFFSET_BASE_ADD         0x00001800
#define AGC_BASE_ADD                (PERIPH3_START_ADDRESS + AGC_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// RFDL
//----------------------------------------------------------------------
#define RFDOWNLOADER_OFFSET_BASE_ADD    0x00001C00
#define RFDOWNLOADER_BASE_ADD           (PERIPH3_START_ADDRESS + RFDOWNLOADER_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// RXFIR
//----------------------------------------------------------------------
#define RXFIR_OFFSET_BASE_ADD       0x00002000
#define RXFIR_BASE_ADD              (PERIPH3_START_ADDRESS + RXFIR_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// TXPORT
//----------------------------------------------------------------------
#define TXPORT_OFFSET_BASE_ADD      0x00002400
#define TXPORT_BASE_ADD             (PERIPH3_START_ADDRESS + TXPORT_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// DIGRF
//----------------------------------------------------------------------
#define RXDIGRF_OFFSET_BASE_ADD     0x00002800
#define RXDIGRF_BASE_ADD            (PERIPH3_START_ADDRESS + RXDIGRF_OFFSET_BASE_ADD)

//----------------------------------------------------------------------
// TBU
//----------------------------------------------------------------------
#define TBU_OFFSET_BASE_ADD         0x00002C00
#define TBU_BASE_ADD                (PERIPH3_START_ADDRESS + TBU_OFFSET_BASE_ADD)


//======================================================================
//======================================================================
//====================== PERIPH 3 peripherals ==========================
//======================================================================
//======================================================================

//----------------------------------------------------------------------
// ABB (Analog BaseBand)
//----------------------------------------------------------------------
#define ABB_OFFSET_BASE_ADD         0x00000000
#define ABB_BASE_ADD                (PERIPH3_START_ADDRESS + ABB_OFFSET_BASE_ADD)


//======================================================================
//====================== Internal Memory IRAM ==========================
//======================================================================

// IRAM on CPU side
#define IRAM_BANK_LENGTH    0x8000  // the size of one IRAM bank is 32kb
#define IRAM_BANK1_ADD      IRAM_BASE_ADD
#define IRAM_BANK2_ADD      (IRAM_BANK1_ADD + IRAM_BANK_LENGTH)
#define IRAM_BANK3_ADD      (IRAM_BANK2_ADD + IRAM_BANK_LENGTH)
#define IRAM_BANK4_ADD      (IRAM_BANK3_ADD + IRAM_BANK_LENGTH)
#define IRAM_BANK5_ADD      (IRAM_BANK4_ADD + IRAM_BANK_LENGTH)
#define IRAM_BANK6_ADD      (IRAM_BANK5_ADD + IRAM_BANK_LENGTH)
#define IRAM_BANK7_ADD      (IRAM_BANK6_ADD + IRAM_BANK_LENGTH)

// IRAM on DSP side
#define IRAM_DSP_BANK_LENGTH    0x4000
#define IRAM_DSP_BANK5_ADD      IRAM_DSP_BASE_ADD
#define IRAM_DSP_BANK6_ADD      (IRAM_DSP_BANK5_ADD + IRAM_DSP_BANK_LENGTH)

#define EBI_CFG_BASE_ADD    0x34002000

#define EBI_CS0_BASE_ADD    0x48000000
#define EBI_CS1_BASE_ADD    0x48010000
#define EBI_CS2_BASE_ADD    0x48020000

#define BA_CMU      WHAT_CMU_BASE_ADD
#define BA_SYSREG   SYS_APB_REG_BASE_ADD
#define BA_GPIO     GPIO_BASE_ADD
#define BA_IT_CTRL  IT_CTRL_BASE_ADD
#define BA_EXT_INT  EXT_INT_BASE_ADD
#define BA_UART1    UART1_BASE_ADD
#define BA_UART2    UART2_BASE_ADD
#define BA_INT_RAM  IRAM_START_ADDRESS
#define BA_TIMER    SYS_TIMER_BASE_ADD
#define BA_SPI1     FS_SPI1_BASE_ADD
#define BA_EBI      EBI_CFG_BASE_ADD
#define BA_EBI_CS0  EBI_CS0_BASE_ADD
#define BA_EBI_CS1  EBI_CS1_BASE_ADD
#define BA_EBI_CS2  EBI_CS2_BASE_ADD


//======================================================================
//====================== MIU address domain ============================
//======================================================================

#define MIU_BASE_PHYADDR    MEM0_START_ADDRESS
#define MIU_ADDR_MASK       0x1FFFFFFF
#define MIU_MAX_PHYADDR     (MIU_BASE_PHYADDR + MIU_ADDR_MASK)
#define MIU_BANK_SIZE       0x04000000

#ifdef __MSW8556__
// PERIPH space definition (through AHB to RIU bridges)
#define RIUBRIDGE_START_ADDRESS    0x74000000
#define RIUBRIDGE_END_ADDRESS      0x74007FFF
#define RIUBRIDGE_ADD_LSB          0x1A //26 //64 Mbytes boundary

// PERIPH space definition (through AHB to RIU bridge)
#define RIUBRIDGE0_OFFSET_ADDRESS   0x00000000
#define RIUBRIDGE0_START_ADDRESS    (RIUBRIDGE_START_ADDRESS + RIUBRIDGE0_OFFSET_ADDRESS)

//-----------------------------------------------------------------------
// QSPI
//-----------------------------------------------------------------------

#define QSPI_OFFSET_BASE_ADD        0x00006D00
#define QSPI_BASE_ADD               ( RIUBRIDGE0_START_ADDRESS + QSPI_OFFSET_BASE_ADD )
#endif //__MSW8556__

#endif //__CPU_MEM_MAP_H__
