#ifndef __UNFD_B5_ROM_H__
#define __UNFD_B5_ROM_H__


#define UNFD_ST_PLAT             0x80000000 // error header for ROM code
#define IF_IP_VERIFY             0 // [CAUTION]: to verify IP and HAL code, defaut 0
#define FTL_FIRST_BLOCK          10 // [UNDO]: check if can be removed

// debug
#define FCIE3_DUMP_DEBUG_BUS     1

//#include <stdio.h>
//#include <string.h>
#include "datatype.h"
#include "hwreg.h"
#include "sys_ass.h"
#include "bootrom.h"
#include "hal.h"
#include "sysapi.h"
#include <string.h>
// [CAUTION]: remember to disable DCACHE in sample.c
//    #include <cyg/hal/hal_cache.h>
//    HAL_DCACHE_DISABLE(); // add atte beginning of cyg_user_start


#define NC_SEL_FCIE3         1
#if NC_SEL_FCIE3
#include "drvNAND_reg_v3.h"
#else
#error "Error! no FCIE registers selected."
#endif

#define drvNAND_SendMsg2BkgndTask(x)

#if IF_IP_VERIFY
// select a default NAND chip for IP_VERIFY or NAND_PROGRAMMER
//#define K9F1G08X0C             1
//#define H27UF081G2A            1
//#define K511F12ACA			 1
//#define TY8A0A111162KC40         1
#define K511F12ACAB075  1
//#define K522H1GACE               1
//#define TY890A111229KC40         1
//#define H8ACU0CE0DAR             1
//#define H9LA25G25HAMBR           1
//#define TY8A0A111178KC4          1
//#define TY9A0A111443KA          1
#define NAND_IF_WORD_MODE        1

#endif

#define IF_FCIE_SHARE_PINS       1 // 1: need to nand_pads_switch at HAL's functions.
#define IF_FCIE_SHARE_CLK        1 // 1: need to nand_clock_setting at HAL's functions.
#define IF_FCIE_SHARE_IP         1

#define ENABLE_NAND_INTERRUPT_MODE 0

// define for MIU_LAST_DONE
#define NC_REG_MIU_LAST_DONE_ST  NC_MIE_EVENT
#define NC_CLR_MIU_LAST_DONE()      REG_W1C_BITS_UINT16(NC_REG_MIU_LAST_DONE_ST, BIT_MIU_LAST_DONE)
#define NC_MASK_INT_MIU_LAST_DONE() REG_CLR_BITS_UINT16(NC_MIE_INT_EN, BIT_MIU_LAST_DONE)

#define REG50_ECC_CTRL_INIT_VALUE    (BIT_NC_SHARE_PAD_EN)
#define REG30_TEST_MODE_INIT_VALUE   0x5800

#define ECC_ALLOWED_MAX_BITS_CNT      2
#define DEBUG_ASSERT_PARTITION_TYPE   UNFD_PART_CUS

//#define NC_ECO_FIX                  NC_REG_57h
#define NC_DEFAULT_DELAY_CYCLE      BIT_NC_DAT_LATCH_0_5T
#define NC_MMA_PRI_REG_SET_W()       REG_SET_BITS_UINT16(NC_MMA_PRI_REG, BIT_NC_DMA_DIR_W|BIT_NC_MIU_BURST_16|BIT_NC_MIU_CTRL_SW|BIT_NC_MIU_CLK_EN_SW);
#define NC_MMA_PRI_REG_SET_R()       REG_CLR_BITS_UINT16(NC_MMA_PRI_REG, BIT_NC_DMA_DIR_W); REG_SET_BITS_UINT16(NC_MMA_PRI_REG, BIT_NC_MIU_CTRL_SW|BIT_NC_MIU_CLK_EN_SW); 

#define NC_HAL_POST_HANDLER()        {REG_CLR_BITS_UINT16(NC_MMA_PRI_REG, BIT_NC_MIU_CLK_EN_SW);}


#define NAND_DRIVER_ROM_VERSION    0 // to save code size
#define AUTO_FORMAT_FTL            1

#if defined(__WINTARGET__)
#define __VER_UNFD_FTL__           1
#endif
#if defined(BOOTLOADER)
#define NAND_BLD_LD_OS             1
#define BLD_LD_OS_RD               1
#endif

#if defined(__BOOTLOADER__)
#define ENABLE_CB_BEFORE_DMA              1
#endif

//=====================================================
// Nand Driver configs
//=====================================================
//#define NAND_BUF_USE_STACK       0 // temporary buffer in stack (1) or directly assigned address (0)
#define NAND_ENV_FPGA            1 //BD_FPGA
#define NAND_ENV_ASIC            2 //BD_ASIC
#if defined(__FPGA_MODE__)// && 0!=__FPGA_MODE__
#define NAND_DRIVER_ENV          NAND_ENV_FPGA
#else
#define NAND_DRIVER_ENV          NAND_ENV_ASIC
#endif

#if defined(__ASIC_SIM__)// && __ASIC_SIM__
#define NAND_DRIVER_FOR_ROM_SIM    1
#else
#define NAND_DRIVER_FOR_ROM_SIM    0
#endif


#define UNFD_CACHE_LINE   0x20
//=====================================================
// tool-chain attributes
//=====================================================
#define UNFD_PACK0         
#define UNFD_PACK1         __attribute__((__packed__))
#define UNFD_ALIGN0        
#define UNFD_ALIGN1        __attribute__((aligned(UNFD_CACHE_LINE)))

//=====================================================
// debug option
//=====================================================
#define NAND_TEST_IN_DESIGN          0


#if defined(__FPGA_MODE__) || defined(__DEBUG_ON__)
#define NAND_DEBUG_MSG           1
#else
#define NAND_DEBUG_MSG           0
#endif

/* Define trace levels. */
#define UNFD_DEBUG_LEVEL_ERROR    (1)    /* Error condition debug messages. */
#define UNFD_DEBUG_LEVEL_WARNING  (2)    /* Warning condition debug messages. */
#define UNFD_DEBUG_LEVEL_HIGH     (3)    /* Debug messages (high debugging). */
#define UNFD_DEBUG_LEVEL_MEDIUM   (4)    /* Debug messages. */
#define UNFD_DEBUG_LEVEL_LOW      (5)    /* Debug messages (low debugging). */

/*
 * Higer debug level means more verbose
 */
#ifndef UNFD_DEBUG_LEVEL
#define UNFD_DEBUG_LEVEL         UNFD_DEBUG_LEVEL_WARNING
#endif

#if defined(NAND_DEBUG_MSG) && NAND_DEBUG_MSG
#define nand_printf    printf
#define nand_debug(dbg_lv, tag, str, ...)         \
	do {                                          \
		if (dbg_lv > UNFD_DEBUG_LEVEL)            \
			break;                                \
		else {								      \
		if (tag)                                  \
			nand_printf((const char *)"[ %s() ] ", __func__); \
                                                  \
		nand_printf((const char *)str, ##__VA_ARGS__);          \
		}									      \
	} while(0)

#else /* NAND_DEBUG_MSG */
#define nand_printf(...)
#define nand_debug(enable, tag, str, ...)      {}
#endif /* NAND_DEBUG_MSG */

extern void nand_reset_WatchDog(void);
extern void nand_set_WatchDog(U8 u8_IfEnable);

#define nand_die(msg) SYS_FAIL(""msg);

#define nand_stop() \
	while(1)  nand_reset_WatchDog();

//=====================================================
// HW Timer for Delay
//=====================================================

#define HW_TIMER_DELAY_1us	    1
#define HW_TIMER_DELAY_10us	    10
#define HW_TIMER_DELAY_100us	100
#define HW_TIMER_DELAY_1ms	    (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms	    (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms	    (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms	(100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms	(500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s	    (1000 * HW_TIMER_DELAY_1ms)

extern void delay_us( unsigned us );
extern U32  nand_hw_timer_delay(U32 u32usTick);

//=====================================================
// Pads Switch
//=====================================================
#define PADCRTL_ADDR   (0x74000000+(0x1980<<2))
#define PADCRTL        GET_REG_ADDR(PADCRTL_ADDR, 0x0B)

extern U32 nand_pads_switch(U32 u32EnableFCIE);

//=====================================================
// set FCIE clock
//=====================================================
#define MPLL_CLK_REG_BASE_ADDR   (0x74000000+(0x1F00<<2))
#define reg_mclk_fcie             GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x53)
#define reg_mdcg_live             GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x48)
#define reg_mdcg_dyn              GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x49)


#define NFIE_CLK_19_5M		  19500000
#define FCIE3_SW_DEFAULT_CLK  NFIE_CLK_19_5M
#define NAND_SEQ_ACC_TIME_TOL	10 //in unit of ns

extern U32  nand_clock_setting(U32 u32ClkParam);

//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS       3 // 8 bytes aligned, FCIE3 don't care

/* --------------------------------------------
 * Important:
 *  - The following buffers should be large enough
 *    for a whole NAND block.
 *  - And sould be software kernel safe.
 */
#if 0//IF_IP_VERIFY
#define DMA_W_ADDR       0x81C00000
#define DMA_R_ADDR       0x81D00000
#define DMA_W_SPARE_ADDR 0x81E00000
#define DMA_R_SPARE_ADDR 0x81E80000
#define DMA_BAD_BLK_BUF  0x81F00000
#else
#define DMA_W_ADDR       0xC200000 // common space, should be access after MMU
#define DMA_R_ADDR       0xC300000
#define DMA_W_SPARE_ADDR 0xC400000
#define DMA_R_SPARE_ADDR 0xC500000
#define DMA_BAD_BLK_BUF  0xC600000
#endif
//=====================================================
// misc
//=====================================================
//#define BIG_ENDIAN
#define LITTLE_ENDIAN


typedef struct NAND_DRIVER_PLATFORM_DEPENDENT
{
	U8 *pu8_PageSpareBuf;
	U8 *pu8_PageDataBuf;
	U32	u32_DMAAddrOffset;
	U32	u32_RAMBufferOffset;
	U32	u32_RAMBufferLen;

}NAND_DRIVER_PLAT_CTX, *P_NAND_DRIVER_PLAT;

#endif /* __UNFD_B5_ROM_H__ */
