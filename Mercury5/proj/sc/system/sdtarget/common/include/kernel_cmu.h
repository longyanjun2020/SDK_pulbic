/*******************************************************************************
 *  kernel_cmu.h
 *------------------------------------------------------------------------------
 *  Scope: CMU register description
 *
 ******************************************************************************/

#ifndef __KERNEL_CMU_H__
#define __KERNEL_CMU_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* System PLL configuration:
   PLL21 : 312MHz
   PLL22 : 624MHz
*/
#define PLL22_DIV2          0x00
#define PLL22_DIV5          0x01
#define PLL22_DIV3          0x02
#define PLL21               0x03

/* Common PLL setting defines */
#define INTCLK_ON_OFF(_type_)               _type_##_INTCLK_ON_OFF
#define INTCLK_ON_MSK(_type_)               (0x01 << INTCLK_ON_OFF(_type_))
#define INTCLK_SEL_OFF(_type_)              _type_##_INTCLK_SEL_OFF
#define INTCLK_SEL_MSK(_type_)              (0x03 << INTCLK_SEL_OFF(_type_))
#define INTCLK_SEL(_type_, _value_)         ((_value_) << INTCLK_SEL_OFF(_type_))
#define INTCLK_DIVBY_OFF(_type_)            _type_##_INTCLK_DIV_OFF
#define INTCLK_DIVBY_MSK(_type_)            (0x03 << INTCLK_DIVBY_OFF(_type_))
#define INTCLK_DIVBY_EXP(_type_, _value_)   ((_value_) << INTCLK_DIVBY_OFF(_type_))

/* CPU_SYS_CTRL register */
#define CPU_INTCLK_ON_OFF   0
#define CPU_INTCLK_SEL_OFF  1
#define CPU_INTCLK_DIV_OFF  4
#define CPU_SYSCLK_UPD_OFF  6
#define CPU_SYSCLK_UPD_MSK  (0x01 << CPU_SYSCLK_UPD_OFF)

/* CPU_SYS_CFG register */
#define CPUSYSCLK_DIVBY_OFF(_type_)         _type_##_CLK_DIV_OFF
#define CPUSYSCLK_DIVBY_MSK(_type_)         (0x0F << CPUSYSCLK_DIVBY_OFF(_type_))
#define CPUSYSCLK_DIVBY_VAL(_type_, _value_)    \
            (((_value_)-0x01) << CPUSYSCLK_DIVBY_OFF(_type_))
#define APB0_CLK_DIV_OFF    0x00
#define APB1_CLK_DIV_OFF    0x04
#define APB2_CLK_DIV_OFF    0x08
#define APB3_CLK_DIV_OFF    0x0C
#define AHB_CLK_DIV_OFF     0x10
#define FREQ26M_CLK_DIV_OFF 0x14
#define CPU_CLK_DIV_OFF     0x18

/* AUX_SYS_CTRL register */
#define AUX_INTCLK_ON_OFF   0
#define AUX_INTCLK_SEL_OFF  1
#define AUX_INTCLK_DIV_OFF  4

/* AUX_SYS_CFG register for A0_ROOT_AUX_CLK input as 52MHz */
#define AUX_UART1_FREQ_OFF  0
#define AUX_UART1_FREQ_MSK  (0x03 << AUX_UART1_FREQ_OFF)
#define AUX_UART1_FREQ_1M8  (0X00 << AUX_UART1_FREQ_OFF)
#define AUX_UART1_FREQ_14M7 (0X01 << AUX_UART1_FREQ_OFF)
#define AUX_UART1_FREQ_18M4 (0X02 << AUX_UART1_FREQ_OFF)
#define AUX_UART1_FREQ_52M  (0X03 << AUX_UART1_FREQ_OFF)
#define AUX_UART2_FREQ_OFF  2
#define AUX_UART2_FREQ_MSK  (0x03 << AUX_UART2_FREQ_OFF)
#define AUX_UART2_FREQ_1M8  (0X00 << AUX_UART2_FREQ_OFF)
#define AUX_UART2_FREQ_14M7 (0X01 << AUX_UART2_FREQ_OFF)
#define AUX_UART2_FREQ_18M4 (0X02 << AUX_UART2_FREQ_OFF)
#define AUX_UART2_FREQ_52M  (0X03 << AUX_UART2_FREQ_OFF)

/* GPR_CTRL0 register */
/* when 1, the external oscillator frequency is 26Mhz otherwise 13 Mhz */
#define BOOT_FREQ           (0x0001 << 0)

/* CMU_PERIPH_CLK_CFG register */
#define CMU_PERIPH1_CLKSEL_MSK              (0x3 << 0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK         (0x0 << 0)
#define CMU_PERIPH1_CLKSEL_MAIN_CLK_DIV2    (0x1 << 0)
#define CMU_PERIPH1_CLKEN_MSK               (0x1 << 3)
#define CMU_PERIPH2_CLKSEL_MSK              (0x3 << 4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK         (0x0 << 4)
#define CMU_PERIPH2_CLKSEL_MAIN_CLK_DIV2    (0x1 << 4)
#define CMU_PERIPH2_CLKEN_MSK               (0x1 << 7)
#define CMU_PERIPH3_CLKSEL_MSK              (0x3 << 8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK         (0x0 << 8)
#define CMU_PERIPH3_CLKSEL_MAIN_CLK_DIV2    (0x1 << 8)
#define CMU_PERIPH3_CLKEN_MSK               (0x1 << 11)

/* RTC_SYS_CTRL register */
#define RTC_INT_CLK_ON_OFF      0
#define RTC_INT_CLK_ON_MSK      (0x1 << RTC_INT_CLK_ON_OFF)
#define RTC_INT_CLK_ON_32K      (0x0 << RTC_INT_CLK_ON_OFF)
#define RTC_INT_CLK_ON_PSEUDO   (0x1 << RTC_INT_CLK_ON_OFF)
#define RTC_INT_CLK_DIV_OFF     1
#define RTC_INT_CLK_DIV_MSK     (0x1 << RTC_INT_CLK_DIV_OFF)
#define RTC_INT_CLK_DIV_396     (0x0 << RTC_INT_CLK_DIV_OFF)
#define RTC_INT_CLK_DIV_792     (0x1 << RTC_INT_CLK_DIV_OFF)

/* MMP_CFG register */
#define MMP_RST_OFF             4
#define MMP_RST_MSK             (0x1 << MMP_RST_OFF)


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef volatile struct KeCmu_s
{
    u32 reserved1;          // 0x00
    u32 reserved2;          // 0x04
    u32 reserved3;          // 0x08
    u32 auxSysCtrl;         // 0x0C
    u32 auxSysCfg;          // 0x10
    u32 fixSysCtrl;         // 0x14
    u32 fixSysCfg;          // 0x18
    u32 cpuSysCtrl;         // 0x1C
    u32 cpuClkCfg;          // 0x20
    u32 dspSysCtrl;         // 0x24
    u32 dspSysCfg;          // 0x28
    u32 rtcSysCtrl;         // 0x2C
    u32 cpuSysCfg;          // 0x30
    u32 cpuPeriphCfg;       // 0x34
    u32 cpuPeriphPwd;       // 0x38
    u32 cpuPeriphRst;       // 0x3C
    u32 cpuPeriphSmWait;    // 0x40
    u32 gssPwd;             // 0x44
    u32 gssRst;             // 0x48
    u32 gssSmWait;          // 0x4C
    u32 rfctrlPwd;          // 0x50
    u32 rfctrlRst;          // 0x54
    u32 rfctrlSmWait;       // 0x58
    u32 shifacePwd;         // 0x5C
    u32 shifaceRst;         // 0x60
    u32 shifaceSmWait;      // 0x64
    u32 cmuIrqMask;         // 0x68
    u32 cmuIrqStatus;       // 0x6C
    u32 cmuIrqClear;        // 0x70
    u32 cmuIrqRawStatus;    // 0x74
    u32 cmuRingOsc;         // 0x78
    u32 cmuRngCfg;          // 0x7C
    u32 cmuRngSeed;         // 0x80
    u32 cmuRngNb;           // 0x84
    u32 cmuPeriphClkCfg;    // 0x88
    u32 cmuMmpCfg;          // 0x8C
    u32 cmuSpare;           // 0x90
    u32 cmuEfuse;           // 0x94
    u32 cmuTcmEtm;          // 0x98
    u32 cmuDetSimRange;     // 0x9C
    u32 cmuDisEtbSync;      // 0xA0
} KeCmu_t;

#endif  // __KERNEL_CMU_H__
