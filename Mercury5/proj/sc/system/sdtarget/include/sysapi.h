/******************************************************************************/
/* File    : sysapi.h                                                         */
/*----------------------------------------------------------------------------*/
/* Scope   : System related APIs                                              */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSAPI_H__
#define __SYSAPI_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "hal.h"
#include "sys_ass.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#if defined(__FPGA_MODE__) || defined(__DEBUG_ON__)
int     diag_printf(const char *fmt, ...);
# define    printf      diag_printf
#else
# define    printf(...)
#endif

#ifdef  __ASIC_SIM__
# define    SYS_ASICSIM_STEP    sys_asicSimStep
#else
# define    SYS_ASICSIM_STEP(...)
#endif

#define SPEED_TEST_OPT(_val_)   _val_

#define CFG_DMC_FREQ        DMC_133MHZ


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef enum
{
    REMAP_NONE = 0,
    REMAP_IMI1,
    REMAP_MEM1,
    REMAP_MEM2,
    REMAP_MEM3,
    REMAP_IMI2,
    REMAP_ROM,
    REMAP_MEM0
} MemRemap_e;

typedef enum
{
    NAND_BOOT = 0,
    NOR_BOOT,
    SPI_BOOT,
    DWLD_BOOT
} BootMode_e;

typedef enum
{
    EXTMEM_NOR = 0,
    EXTMEM_NAND_8BITS,
    EXTMEM_NAND_16BITS,
    EXTMEM_SPI,
    EXTMEM_NAND_MANUAL,
    EXTMEM_EMBED_SPI
} ExtMem_e;

typedef enum
{
    BOOTSRC_ROM = 0,
    BOOTSRC_NOR,
    BOOTSRC_SPI,
    BOOTSRC_NONE
} BootSrc_e;

typedef enum {
    SPI_DBB = 0,
    SPI_BKDOOR
} SPI_BOND_e;

typedef enum {
    CTRL_OFF = 0,
    CTRL_ON
} SYSCTRL_OP_e;

/* Enumeration of Pad type */
typedef enum {
    PAD_SPI_DBB_MODE0 = 0,
    PAD_SPI_DBB_MODE1,
    PAD_SPI_DBB_MODE2,
    PAD_SPI_DBB_MODE3,
    PAD_SPI_BKDOOR,
    PAD_UART1_USE_MPIF,
    PAD_UART1_USE_BTIF,
    PAD_UART2,
    PAD_SDCARD,
    PAD_SDMODE
} PADCTRL_TYPE_e;

/* Enumeration of Peripheral type */
typedef enum {
    PERIPH_RSVD0 = 0,
    PERIPH_IMI,
    PERIPH_AHB_ML,
    PERIPH_AHB2APB1,
    PERIPH_AHB2APB2,
    PERIPH_AHB2APB3,
    PERIPH_DMA_PWD,
    PERIPH_ITCTRL,
    PERIPH_EXT_ITCTRL,
    PERIPH_FCS,
    PERIPH_GEA,
    PERIPH_GEA2,
    PERIPH_UART1,
    PERIPH_UART2,
    PERIPH_SPI1,
    PERIPH_SPI2,
    PERIPH_RSVD16 = 16,
    PERIPH_SIM1,
    PERIPH_RSVD18 = 18,
    PERIPH_PWM,
    PERIPH_KEYPAD,
    PERIPH_I2C,
    PERIPH_SYSTIMER,
    PERIPH_EMI,
    PERIPH_EMI_ARBITER,
    PERIPH_SDRAM,
    PERIPH_EBI,
    PERIPH_AUDIO,
    PERIPH_RTC,
    PERIPH_LAST_IN_CMU = PERIPH_RTC,
    PERIPH_NAND,
    PERIPH_SDCARD,
} PERIPH_TYPE_e;

/* Enumeration of PLL CRU unit */
typedef enum {
    CRU_BIST = 0,
    CRU_SDIO,
    CRU_NFIE,
    CRU_ICP,
    CRU_SCL,
    CRU_JPDE,
    CRU_MPIF,
    CRU_XIU,
    CRU_FMRX_312,
    CRU_FMRX,
    CRU_FMRX_I2S,
    CRU_MIU,
    CRU_EMI_32K,
    CRU_AUX,
    CRU_AUX_32K,
    CRU_AUX_16K,
    CRU_AUX_128,
    CRU_AUDIO_32K,
    CRU_AUDIO_128,
    CRU_SPI,
    CRU_AU_SRC,
    CRU_AU_MAC,
    CRU_RF_26M,
    CRU_GPS_32K,
    CRU_DB_BUS,
    CRU_UTMI_AS_214,
    CRU_UTMI_AS_192,
    CRU_UTMI_AS_120,
    CRU_SR_M,
    CRU_SR_P,
    CRU_ADC_DMA,
    CRU_RF_RX,
    CRU_DISP,
    CRU_PADOUT_26M,
    CRU_TIMER,
    CRU_GPS1_32K,
    CRU_PADOUT1_26M
} SYSPLL_TYPE_e;

/* Enumeration of PMU LDO */
typedef enum {
    VMEM = 0,
    VLCM,
    VIO1,
    VIO2,
    VSIM1,
    VSIM2
} PMULDO_TYPE_e;

/* Enumeration of LDO mode */
typedef enum {
    MODE_ACT = 0,
    MODE_STDB
} PMULDO_MODE_e;

/* Enumeration of simulation stage */
typedef enum {
    SIM_START = 0xFF,
    SIM_CACHE = 0,
    SIM_PLL,
    SIM_PORT,
    SIM_IRQ,
    SIM_BOOTMODE,
    SIM_NORMALBOOT,
    SIM_CHKKEYPAD,
    SIM_DWLDBOOT,
    SIM_PRESSDWLDKEY,
    SIM_BOOTSTRAP,
} ASIC_SIM_e;

/* Chip revision */
typedef enum {
    BIG3_U01 = 0x8001,
    BIG3_U02 = 0x8002,
    BIG3_U03 = 0x8003,
} CHIP_REV_e;

/* Chip freq. */
typedef enum
{
    DMC_STOP   = 0,
    DMC_104MHZ = 104,
    DMC_130MHZ = 130,
    DMC_133MHZ = 133,
    DMC_153MHZ = 153,
    DMC_156MHZ = 156,
    DMC_166MHZ = 166,
    DMC_200MHZ = 200,
} DMC_FREQ_e;


//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/* sys_misc.c */
ExtMem_e    sys_get_extMemType(void);
BootMode_e  sys_get_bootMode(void);
BootSrc_e   sys_get_bootSrc(void);
void    *sys_get_tmpBuf(u16 u16size);
bool    sys_checkMem0Image(void);
bool    sys_isDwldKeyPressed(void);
void    sys_vddioPwrCtrl2V8(void);
void    sys_asicSimStep(ASIC_SIM_e estep);
u32     sys_touch_miscdata(void);
bool    sys_emiDMC_memInit(DMC_FREQ_e efreq);
DMC_FREQ_e  sys_emiDMC_getFreq(void);
bool    sys_emiDMC_phaseMargin(bool bdebug);
bool    sys_emiSMC_memInit(void);
void    sys_set_dwlComplete(void);

/* utility.c */
void    sys_cal_period(u32 *time, u32 control);

/* sys_periph.c */
SPI_BOND_e  sys_get_SPIBond(void);
u32     sys_pllCtrl(SYSPLL_TYPE_e etype, u32 u32freq);
void    sys_padCtrl(SYSCTRL_OP_e eop, PADCTRL_TYPE_e etype);
bool    sys_periphPwrCtrl(SYSCTRL_OP_e eop, PERIPH_TYPE_e etype);
void    sys_periphRstCtrl(SYSCTRL_OP_e eop, PERIPH_TYPE_e etype);
bool    sys_pmuLDOCtrl(PMULDO_TYPE_e etype, PMULDO_MODE_e emode, u8 u8val);

/* sys_cfg.c */
u32     sys_PHY2MIUAddr(u32 phyaddr);
u32     sys_MIU2PHYAddr(u32 miuaddr);
void    sys_kickoff_mem_remap(MemRemap_e etype);
u16     sys_get_productID(void);
u16     sys_get_chipRev(void);
u16     sys_dsp_rom_revision(void);


/* Asura PMU APIs */
bool    sys_AsuraInit(void);
void    sys_AsuraClose(void);
bool    sys_AsuraRead(u16 u16addr, u16 *ptrdata);
bool    sys_AsuraWrite(u16 u16addr, u16 u16data);

/* ARM speed test API */
u16     sys_get_ArmSpeedTestOpt(u8 u8opt);
void    sys_trap_ArmSpeedTest(void);
void    sys_do_ArmSpeedTest(void);

#endif  // __SYSAPI_H__
