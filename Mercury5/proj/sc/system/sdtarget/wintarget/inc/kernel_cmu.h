/***************************************************************************
 *  kernel_cmu.h
 *--------------------------------------------------------------------------
 *  Scope: CMU register description
 *
 ****************************************************************************/

#ifndef _45ae3b9bc7bf07eff33df26d1f3110fe_included_kernel_cmu_h
#define _45ae3b9bc7bf07eff33df26d1f3110fe_included_kernel_cmu_h

#include "stdcomp.h"
#include "cpu_mem_map.h"

typedef volatile struct KeCmu_s
{
#ifdef __B1__
    u32 fixPll;             // 0x00
    u32 cpuPll;             // 0x04
    u32 dspPll;             // 0x08
#else // __B1__
    u32 reserved1;          // 0x00
    u32 reserved2;          // 0x04
    u32 reserved3;          // 0x08
#endif // __B1__
    u32 auxSysCtrl;         // 0x0C
    u32 auxSysCfg;          // 0x10
    u32 fixSysCtrl;         // 0x14
    u32 fixSysCfg;          // 0x18
    u32 cpuSysCtrl;         // 0x1C
    //u32 cpuClkCfg;          // 0x20
    u32 cpuSysCfg;          // 0x20
    u32 dspSysCtrl;         // 0x24
    u32 dspSysCfg;          // 0x28
    u32 rtcSysCtrl;         // 0x2C
    //u32 cpuSysCfg;          // 0x30
    u32 gprCtrl0;           // 0x30
    u32 cpuPeriphCfg;       // 0x34
    u32 cpuPeriphPwd;       // 0x38
    u32 cpuPeriphRst;       // 0x3C
    u32 cpuPeriphSmWait;    // 0x40
    u32 reserved4;          // 0x44
    u32 reserved5;          // 0x48
    u32 reserved6;          // 0x4C
    u32 rfctrlPwd;          // 0x50
    u32 rfctrlRst;          // 0x54
    u32 rfctrlSmWait;       // 0x58
    u32 shifacePwd;         // 0x5C
    u32 shifaceRst;         // 0x60
    u32 shifaceSmWait;      // 0x64
    u32 reserved7;          // 0x68
    u32 reserved8;          // 0x6C
    u32 reserved9;          // 0x70
    u32 reserved10;         // 0x74
    u32 cmuRingOsc;         // 0x78
    u32 cmuRngCfg;       // 0x7C
    u32 cmuRngSeed;        // 0x80
    u32 cmuRngNb;    // 0x84
    u32 cmuPeriphClkCfg;    // 0x88
#ifndef __B1__
    u32 cmuMmpCfg;    // 0x8C
#endif // __B1__
} KeCmu_t;

// CPU SYS CFG register
#define BOOT_FREQ                   (0x0001<<0) // when 1, the external oscillator frequency is 26Mhz otherwise 113 Mhz

// CMU_PERIPH_CLK_CFG register
#define CMU_PERIPH1_CLKSEL_MSK                     	((u32)0x3<<0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK           		((u32)0x0<<0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<0)
#define CMU_PERIPH1_CLKEN_MSK                     	((u32)0x1<<3)
#define CMU_PERIPH2_CLKSEL_MSK                     	((u32)0x3<<4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK           		((u32)0x0<<4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<4)
#define CMU_PERIPH2_CLKEN_MSK                     	((u32)0x1<<7)
#define CMU_PERIPH3_CLKSEL_MSK                     	((u32)0x3<<8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK           		((u32)0x0<<8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<8)
#define CMU_PERIPH3_CLKEN_MSK                     	((u32)0x1<<11)

//AUX_SYS_CTRL
#define AUX_INT_CLK_ON							((u32)0x01<<0)
#define AUX_INT_CLK_SEL_POS                     1
#define AUX_INT_CLK_SEL_MASK                    (0x0003<<AUX_INT_CLK_SEL_POS)
#define AUX_INT_CLK_PLL21_DIV2_CLK              0
#define AUX_INT_CLK_PLL22_DIV2_CLK              1
#define AUX_INT_CLK_PLL1_DIV3_CLK               2
#define AUX_INT_CLK_PLL1_DIV2_CLK               3
#define AUX_INT_CLK_DIV_POS                     4
#define AUX_INT_CLK_DIV_MASK                    (0x0003<<AUX_INT_CLK_DIV_POS)
#define AUX_INT_CLK_DIV_1                       0
#define AUX_INT_CLK_DIV_2                       1
#define AUX_INT_CLK_DIV_4                       2
#define AUX_INT_CLK_DIV_8                       3

//AUX_SYS_CFG
#define UART1_CLK_DIV_POS					  	0
#define UART1_CLK_DIV_MASK					  	((u32)0x03<<0)
#define UART1_CKL_DIV_1_8432        			0
#define UART1_CKL_DIV_14_7456       			1
#define UART1_CKL_DIV_18_4320       			2
#define UART1_CKL_DIV_52_0000					3
#define UART2_CLK_DIV_POS					  	2
#define UART2_CLK_DIV_MASK						((u32)0x03<<UART2_CLK_DIV_POS)
#define UART2_CKL_DIV_1_8432        			0
#define UART2_CKL_DIV_14_7456       			1
#define UART2_CKL_DIV_18_4320       			2
#define UART2_CKL_DIV_52_0000					3

// FIX_SYS_CTRL register
#define FIX_INT_CLK_ON              (0x0001<<0)
#define FIX_INT_CLK_DIV_POS         1
#define FIX_INT_CLK_DIV_MASK        (0x0003<<FIX_INT_CLK_DIV_POS)

// CPU_SYS_CTRL register
#define CPU_INT_CLK_ON              			((u32)0x0001<<0)
#define CPU_INT_CLK_SEL_POS         			1
#define CPU_INT_CLK_SEL_MASK					(0x0003<<CPU_INT_CLK_SEL_POS)
#define CPU_INT_CLK_PLL21_DIV2_CLK				0
#define CPU_INT_CLK_PLL22_DIV2_CLK				1
#define CPU_INT_CLK_PLL1_DIV3_CLK				2
#define CPU_INT_CLK_PLL1_DIV2_CLK				3
#define CPU_INT_CLK_DIV_POS         			4
#define CPU_INT_CLK_DIV_MASK        			(0x0003<<CPU_INT_CLK_DIV_POS)
#define CPU_INT_CLK_DIV_1           			0
#define CPU_INT_CLK_DIV_2           			1
#define CPU_INT_CLK_DIV_4           			2
#define CPU_INT_CLK_DIV_8           			3
#define SYS_CLK_UPDATE              			(0x0001<<6)

// CPU_SYS_CFG
#define APB0_CLK_DIV_POS            			0
#define APB0_CLK_DIV_MASK           			(0x000F<<APB0_CLK_DIV_POS)
#define APB1_CLK_DIV_POS            			4
#define APB1_CLK_DIV_MASK           			(0x000F<<APB1_CLK_DIV_POS)
#define APB2_CLK_DIV_POS            			8
#define APB2_CLK_DIV_MASK           			(0x000F<<APB2_CLK_DIV_POS)
#define APB3_CLK_DIV_POS            			12
#define APB3_CLK_DIV_MASK           			(0x000F<<APB3_CLK_DIV_POS)
#define AHB_CLK_DIV_POS             			16
#define AHB_CLK_DIV_MASK            			(0x000F<<AHB_CLK_DIV_POS)
#define BUS_CLK_DIV_1               			0
#define BUS_CLK_DIV_2               			1
#define BUS_CLK_DIV_3               			2
#define BUS_CLK_DIV_4               			3
#define BUS_CLK_DIV_5               			4
#define BUS_CLK_DIV_6               			5
#define BUS_CLK_DIV_7               			6
#define BUS_CLK_DIV_8               			7
#define BUS_CLK_DIV_9               			8
#define BUS_CLK_DIV_10              			9
#define BUS_CLK_DIV_11             				10
#define BUS_CLK_DIV_12             				11
#define BUS_CLK_DIV_13             				12
#define BUS_CLK_DIV_14             				13
#define BUS_CLK_DIV_15             				14
#define BUS_CLK_DIV_16             				15
#define CLK_26M_DIV_POS             			20
#define CLK_26M_DIV_MASK            			(0x000F<<CLK_26M_DIV_POS)
#define CPU_CLK_DIV_POS             			24
#define CPU_CLK_DIV_MASK            			(0x001F<<CPU_CLK_DIV_POS)
#define CPU_CLK_DIV_1               			0
#define CPU_CLK_DIV_2               			1
#define CPU_CLK_DIV_3               			2
#define CPU_CLK_DIV_4               			3
#define CPU_CLK_DIV_5               			4
#define CPU_CLK_DIV_6               			5
#define CPU_CLK_DIV_7               			6
#define CPU_CLK_DIV_8               			7
#define CPU_CLK_DIV_9               			8
#define CPU_CLK_DIV_10              			9
#define CPU_CLK_DIV_11             				10
#define CPU_CLK_DIV_12             				11
#define CPU_CLK_DIV_13             				12
#define CPU_CLK_DIV_14             				13
#define CPU_CLK_DIV_15             				14
#define CPU_CLK_DIV_16             				15
#define CPU_CLK_DIV_17             				16
#define CPU_CLK_DIV_18             				17
#define CPU_CLK_DIV_19             				18
#define CPU_CLK_DIV_20             				19
#define CPU_CLK_DIV_21             				20
#define CPU_CLK_DIV_22             				21
#define CPU_CLK_DIV_23             				22
#define CPU_CLK_DIV_24             				23
#define CPU_CLK_DIV_25             				24
#define CPU_CLK_DIV_26             				25
#define CPU_CLK_DIV_27             				26
#define CPU_CLK_DIV_28             				27
#define CPU_CLK_DIV_29             				28
#define CPU_CLK_DIV_30             				29
#define CPU_CLK_DIV_31             				30
#define CPU_CLK_DIV_32             				31

// DSP_SYS_CTRL
#define DSP_INT_CLK_ON              			(0x0001<<0)
#define DSP_INT_CLK_SEL_POS         			1
#define DSP_INT_CLK_SEL_MASK        			(0x0003<<DSP_INT_CLK_SEL_POS)
#define DSP_INT_CLK_SEL_PLL21_DIV2     			0
#define DSP_INT_CLK_SEL_PLL22_DIV2     			1
#define DSP_INT_CLK_SEL_PLL1_DIV3      			2
#define DSP_INT_CLK_SEL_PLL1_DIV2     			3
#define DSP_INT_CLK_DIV_POS         			4
#define DSP_INT_CLK_DIV_MASK        			(0x0003<<DSP_INT_CLK_DIV_POS)
#define DSP_INT_CLK_DIV_1           			0
#define DSP_INT_CLK_DIV_2           			1
#define DSP_INT_CLK_DIV_4           			2
#define DSP_INT_CLK_DIV_8           			3
#define DSP_CLK_DIV_EN							(1<<7)

// DSP_SYS_CFG
#define EDGE_CLK_DIV_POS            			0
#define EDGE_CLK_DIV_MASK           			(0x0003<<EDGE_CLK_DIV_POS)

// RTC_SYS_CTRL
#define RTC_INT_CLK_ON_MSK						(0x0001<<0)
#define RTC_INT_CLK_ON_32K_EXT					(0x0000<<0)
#define RTC_INT_CLK_ON_32K_INT					(0x0001<<0)
#define RTC_INT_CLK_DIV             			(0x0001<<1)

// GPR_CTRL0
#define BOOT_FREQ                   (0x0001<<0) // when 1, the external oscillator frequency is 26Mhz otherwise 13 Mhz
#define VCXO_PWD                    (0x0001<<1) // when 1, the external 13/26 Mhz oscillator is switched off in sleep mode
#define WD_PERIPH_EN                (0x0001<<2) // watchdog out enabled
#define DSP_DBG_EN                  (0x0001<<3) // when 1, the DSP jtag is enabled
#define CPU_PERIPH_AUTO_PWD         (0x0001<<4)
#define GSS_AUTO_PWD                (0x0001<<5)
#define RF_AUTO_PWD                 (0x0001<<6)
#define SHIFACE_AUTO_PWD            (0x0001<<7)
#define DSP_PERIPH_AUTO_PWD         (0x0001<<8)
#define CPU_DBG_EN                  (0x0001<<9) // when 1, the CPU jtag is enabled
#define SM_WAIT_CPU_PWD             (0x0001<<11) // when 1, system clocks are only switched off in sleep mode if all selected devices are in power_down mode
#define ETM_TRACE_CLK_DEL_POS       12
#define ETM_TRACE_CLK_DEL_MASK      (0x0003<<ETM_TRACE_CLK_DEL_POS)
#define CHIP_DBG_EN                 (0x0001<<14) // when 1, the chip debug mode is enabled
#define CPU_DSP_RST                 (0x0001<<15) // when 1, a reset is applied on the DSP sub-system
#define CPU_DSP_PWD                 (0x0001<<16) // when 1, all DSP sub-system clocks are switched off
#define PLL_PWD						(0x0001<<21)

// CPU_PERIPH_PWD
#define IMI_PWD                     (0x0001<<1)
#define AHB_ML_PWD                  (0x0001<<2)
#define AHB2APB1_PWD                (0x0001<<3)
#define AHB2APB2_PWD                (0x0001<<4)
#define AHB2APB3_PWD                (0x0001<<5)
#define DMA_PWD                     (0x0001<<6)
#define ITCTRL_PWD                  (0x0001<<7)
#define EXT_ITCTRL_PWD              (0x0001<<8)
#define FCS_PWD                     (0x0001<<9)
#define GEA_PWD                     (0x0001<<10)
#define GEA2_PWD                    (0x0001<<11)
#define UART1_PWD                   (0x0001<<12)
#define UART2_PWD                   (0x0001<<13)
#define SPI1_PWD                    (0x0001<<14)
#ifdef __B1__
#define SPI2_PWD                    (0x0001<<15)
#endif //__B1__
#define SIM1_PWD                    (0x0001<<17)
#define SIM2_PWD                    (0x0001<<18)
#define PWM_PWD                     (0x0001<<19)
#define I2C_PWD                     (0x0001<<21)
#define SYSTIMER_PWD                (0x0001<<22)
#define EMI_PWD                     (0x0001<<23)
#define EMI_ARBITER_PWD             (0x0001<<24)
#define SDRAM_PWD                   (0x0001<<25)
#define EBI_PWD                     (0x0001<<26)
#define AUDIO_PWD                   (0x0001<<27)

// CPU_PERIPH_RST
#define DMA_RST                     (0x0001<<6)
#define ITCTRL_RST                  (0x0001<<7)
#define EXT_ITCTRL_RST              (0x0001<<8)
#define FCS_RST                     (0x0001<<9)
#define GEA_RST                     (0x0001<<10)
#define GEA2_RST                    (0x0001<<11)
#define UART1_RST                   (0x0001<<12)
#define UART2_RST                   (0x0001<<13)
#define SPI1_RST                    (0x0001<<14)
#define SIM1_RST                    (0x0001<<17)
#define SIM2_RST                    (0x0001<<18)
#define PWM_RST                     (0x0001<<19)
#define KEYPAD_RST                  (0x0001<<20)
#define I2C_RST                     (0x0001<<21)
#define SYSTIMER_RST                (0x0001<<22)
#define EBI_RST                     (0x0001<<26)
#define AUDIO_RST                   (0x0001<<27)

// CPU_PERIPH_SM_WAIT
#define SM_WAIT_EXICE_PWD           (0x0001<<0)
#define SM_WAIT_IMI_PWD             (0x0001<<1)
#define SM_WAIT_AHB_ML_PWD          (0x0001<<2)
#define SM_WAIT_AHB2APB1_PWD        (0x0001<<3)
#define SM_WAIT_AHB2APB2_PWD        (0x0001<<4)
#define SM_WAIT_AHB2APB3_PWD        (0x0001<<5)
#define SM_WAIT_DMA_PWD             (0x0001<<6)
#define SM_WAIT_ITCTRL_PWD          (0x0001<<7)
#define SM_WAIT_EXT_ITCTRL_PWD      (0x0001<<8)
#define SM_WAIT_FCS_PWD             (0x0001<<9)
#define SM_WAIT_GEA_PWD             (0x0001<<10)
#define SM_WAIT_GEA2_PWD            (0x0001<<11)
#define SM_WAIT_UART1_PWD           (0x0001<<12)
#define SM_WAIT_UART2_PWD           (0x0001<<13)
#define SM_WAIT_SPI1_PWD            (0x0001<<14)
#define SM_WAIT_SPI2_PWD            (0x0001<<15)
//#define SM_WAIT_SPI3_PWD            (0x0001<<16)
#define SM_WAIT_SIM1_PWD            (0x0001<<17)
#define SM_WAIT_SIM2_PWD            (0x0001<<18)
#define SM_WAIT_PWM_PWD             (0x0001<<19)
#define SM_WAIT_I2C_PWD             (0x0001<<21)
#define SM_WAIT_SYSTIMER_PWD        (0x0001<<22)
#define SM_WAIT_EMI_PWD             (0x0001<<23)
#define SM_WAIT_EMI_ARBITRER_PWD    (0x0001<<24)
#define SM_WAIT_SDRAM_PWD           (0x0001<<25)
#define SM_WAIT_NANDFLASH_PWD       (0x0001<<26)
#define SM_WAIT_AUDIO_PWD           (0x0001<<27)
//#define SM_WAIT_RTC_PWD             (0x0001<<28) // only for the cpu I/F clocks of the RTC
//#define SM_WAIT_SDMMC_PWD           (0x0001<<29)
//#define SM_WAIT_USB_PWD             (0x0001<<30)

// RFCTRL_PWD
#define TBU_PWD                     (0x0001<<0)
#define RXPORT_PWD                  (0x0001<<1)
#define TXPORT_PWD                  (0x0001<<2)
#define AGC_PWD                     (0x0001<<3)
#define RFDL_PWD                    (0x0001<<4)
#define RFDL_P2S0_PWD               (0x0001<<5)
#define RFDL_P2S1_PWD               (0x0001<<6)

// RFCTRL_RST
#define TBU_RST                     (0x0001<<0)
#define RXPORT_RST                  (0x0001<<1)
#define TXPORT_RST                  (0x0001<<2)
#define AGC_RST                     (0x0001<<3)
#define RFDL_RST                    (0x0001<<4)
#define RFDL_P2S0_RST               (0x0001<<5)
#define RFDL_P2S1_RST               (0x0001<<6)

// RFCTRL_SM_WAIT
#define SM_WAIT_TBU_PWD            (0x0001<<0)
#define SM_WAIT_RXPORT_PWD         (0x0001<<1)
#define SM_WAIT_TXPORT_PWD         (0x0001<<2)
#define SM_WAIT_AGC_PWD            (0x0001<<3)
#define SM_WAIT_RFDL_PWD           (0x0001<<4)
#define SM_WAIT_RFDL_P2S0_PWD      (0x0001<<5)
#define SM_WAIT_RFDL_P2S1_PWD      (0x0001<<6)

// SHIFACE_PWD
#define SHIFACE_SHARE_REG_PWD      (0x0001<<0)
#define SHIFACE_DSMA_PWD           (0x0001<<1)
#define SHIFACE_FRAME_CNT_PWD      (0x0001<<2)
#define SHIFACE_DSP_PWD            (0x0001<<4)

// SHIFACE_RST
#define SHIFACE_SHARE_REG_RST      (0x0001<<0)
#define SHIFACE_DSMA_RST           (0x0001<<1)
#define SHIFACE_FRAME_CNT_RST      (0x0001<<2)
#define SHIFACE_DSP_RST            (0x0001<<4)

// SHIFACE_SM_WAIT
#define SM_WAIT_SHARE_REG_PWD      (0x0001<<0)
#define SM_WAIT_DSMA_PWD           (0x0001<<1)
#define SM_WAIT_FRAME_CNT_PWD      (0x0001<<2)
#define SM_WAIT_DSP_PWD            (0x0001<<4)

// CMU_PERIPH_CLK_CFG register
#define CMU_PERIPH1_CLKSEL_MSK                     	((u32)0x3<<0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK           		((u32)0x0<<0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<0)
#define CMU_PERIPH1_CLKEN_MSK                     	((u32)0x1<<3)
#define CMU_PERIPH2_CLKSEL_MSK                     	((u32)0x3<<4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK           		((u32)0x0<<4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<4)
#define CMU_PERIPH2_CLKEN_MSK                     	((u32)0x1<<7)
#define CMU_PERIPH3_CLKSEL_MSK                     	((u32)0x3<<8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK           		((u32)0x0<<8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK_DIV2           	((u32)0x1<<8)
#define CMU_PERIPH3_CLKEN_MSK                     	((u32)0x1<<11)

// CMU_MMP_CFG register
#define CMU_MMP_CLKSEL_POS  0   // MMP_CLKSEL: clock selection for on-chip multimedia processor
#define CMU_MMP_CLKSEL_MSK  ((u32)0x3<<CMU_MMP_CLKSEL_POS)
/*
00: MMP_CLK = MAIN_CLK (13 or 26 MHz)
01: MMP_CLK = MAIN_CLK/2 (6.5 or 13 MHz)
10: MMP_CLK = 26 MHz derived from C0_ROOT_CPU_CLK
11: MMP_CLK = 13 MHz derived from C0_ROOT_CPU_CLK
*/

#define CMU_MMP_CLKEN  ((u32)0x1<<3)  // MMP_CLKEN: MMP_CLK enable (glitch free)
/*
0: MMP_CLK is disabled
1: MMP_CLK is enabled
*/
#define CMU_MMP_RST  ((u32)0x1<<4)   // MMP_RST: Multimedia processor reset

/*
0: reset disabled
1: reset enabled
*/
#define CMU_MMP_WD_EN  ((u32)0x1<<5)   // MMP_WD_EN: Multimedia processor watchdog enable for MMP_RST

/*
0: Watchdog disabled
1: Watchdog enabled
*/
#define CMU_MMP_VDD_PWD  ((u32)0x1<<6)   // MMP_VDD_PWD: Multimedia processor "LCD bypass logic" isolation. When 1, the interface signals of the 'LCD bypass logic" are isolated (except the EBI/HIF and LCD I/F) and the corresponding power supply can be switched off in the ABB.

/*
0: Power-up, i.e. isolation disabled
1: Power-down, i.e. isolation enabled
*/
#define CMU_MMP_VDD1_PWD  ((u32)0x1<<7)   // MMP_VDD1_PWD: Multimedia processor core isolation. When 1, the MMP core signals are isolated (except the EBI/HIF and LCD I/F) and the corresponding power supply can be switched off in the ABB.

/*
0: Power-up, i.e. isolation disabled
1: Power-down, i.e. isolation enabled
*/


extern volatile KeCmu_t* const KeCmu;

#endif /* ! _45ae3b9bc7bf07eff33df26d1f3110fe_included_kernel_cmu_h */

