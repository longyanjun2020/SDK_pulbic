/****************************************************************************/
/* File    : plfcfg.h                                                      */
/*--------------------------------------------------------------------------*/
/* Scope   : Platform Configurations                                        */
/*                                                                          */
/****************************************************************************/
#ifndef __PLFCFG_H__
#define __PLFCFG_H__


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SYSNUM_TEMP_BUFFER_SIZE     0x1000
#if defined(__MSW8522__) || defined(__MSW8556__)
#define SYSNUM_USBVEND_BUFFER_SIZE  (16 * 1024)
#define SYSNUM_EMI_USBVEND_BUFFER_SIZE  (64 * 1024)	/* for recieve wintarget in bootstrap */
#else
#define SYSNUM_USBVEND_BUFFER_SIZE  (64 * 1024)
#endif
#define SYSNUM_USBDATA_BUFFER_SIZE  (8 * 1024)

#if defined(__MSW8522__) || defined(__MSW8556__)
#define SYSNUM_MMU_PAGETBL_ADDR 0x08000000
#define SYSNUM_MMU_PAGETBL_SIZE 0x4000
#define SYSNUM_MMU_PAGETBLLV2_ADDR 0x1C006000
#define SYSNUM_MMU_PAGETBLLV2_SIZE 0x1000
#else
#define SYSNUM_MMU_PAGETBL_ADDR 0x08003000
#define SYSNUM_MMU_PAGETBL_SIZE 0x5000
#endif

#define SYSHAL_ICACHE_LINE_SIZE 32
#define SYSHAL_DCACHE_LINE_SIZE 32

#if defined(__MSW8522__) || defined(__MSW8556__)
#define SYSNUM_KEY_ROW_COUNT    5
#define SYSNUM_KEY_COL_COUNT    5
#else
#define SYSNUM_KEY_ROW_COUNT    6
#define SYSNUM_KEY_COL_COUNT    7
#endif
#define SYSNUM_DWLD_KEY_PERIOD  2000    /* in mSec */

#define SYSNUM_HAL_ISR_MIN      0
#define SYSNUM_HAL_ISR_MAX      63
#define SYSNUM_HAL_ISR_COUNT    (SYSNUM_HAL_ISR_MAX + 1)

#define SYSNUM_HAL_RTC_PERIOD   4000

#define SYSNUM_CRU_SLOWCLK_FREQ 26000000
#define SYSNUM_OSTICK_CLK_FREQ  (32768/152)
#define SYSNUM_STDA_CLK_FREQ    (13000000/12)
#if defined(__MSW8522__) || defined(__MSW8556__)
#ifdef __FPGA_MODE__
#define SYSNUM_UART_CLK_FREQ    24000000 //for 12MHz XTAL
//#define SYSNUM_UART_CLK_FREQ    16000000  //for 8MHz XTAL
#else
#define SYSNUM_UART_CLK_FREQ    14745600
#endif
#else
#define SYSNUM_UART_CLK_FREQ    14745600
#endif

#endif /* __PLFCFG_H__ */
