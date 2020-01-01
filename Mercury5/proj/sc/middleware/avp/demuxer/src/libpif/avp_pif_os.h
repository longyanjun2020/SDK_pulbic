/* Hercules+++ */
#ifndef __PIF_OS_H__
#define __PIF_OS_H__

#include "avp_hal_intr.h"
#include "avp_hal_if.h"
#include "avp_hal_io.h"

/***************************************************************
*
*	configuration
*
***************************************************************/

//#define LC1A_ECO

//#ifdef ECO_CONFIG
#if 0
  #define MPIF_ENABLE					CONFIG_MPIF_ENABLE

  /*
   * read / write parameter
   */
  #define PIF_ACCESS_CHECKSUM		CONFIG_PIF_ACCESS_CHECKSUM
  #define PIF_ACCESS_RETRX_LIMIT		CONFIG_PIF_ACCESS_RETRX_LIMIT
  #define PIF_ACCESS_POLL_DELAY		CONFIG_PIF_ACCESS_POLL_DELAY	/* us */

  /*
   * block read / write parameter
   */
  #define PIF_BLOCK_ACCESS_CHECKSUM			CONFIG_PIF_BLOCK_ACCESS_CHECKSUM
  #define PIF_BLOCK_ACCESS_RETRX_LIMIT		CONFIG_PIF_BLOCK_ACCESS_RETRX_LIMIT
  #define PIF_BLOCK_ACCESS_POLL_DELAY		CONFIG_PIF_BLOCK_ACCESS_POLL_DELAY	/* us */

  /*
   * register
   */
  #define MPIF_R_BASE					CONFIG_MPIF_R_BASE

  /*
   * polling config
   */
  #define MPIF_ACCESS_POLL_COUNT        CONFIG_PIF_MAX_POLL_COUNT

    /*
     * some general configuration
     */
  #define PIF_CONFIG_STREAM_MODE              CONFIG_PIF_STREAM_MODE
  #define PIF_PATH_WIDTH	CONFIG_PIF_PATH_WIDTH
  #define PIF_INTERRUPT_SUPPORT	CONFIG_PIF_INTRERRUPT
  #define PIF_DEFAULT_SID CONFIG_PIF_DEFAULT_SID

#else

  #define MPIF_ENABLE					1

  /*
   * read / write parameter
   */
  #define PIF_ACCESS_CHECKSUM		1
  #define PIF_ACCESS_RETRY          1
  #define PIF_ACCESS_RETRX_LIMIT	3
  #define PIF_ACCESS_POLL_DELAY		1	/* us */

  /*
   * block read / write parameter
   */
  #define PIF_BLOCK_ACCESS_CHECKSUM			1//0
  #define PIF_BLOCK_ACCESS_RETRY            0//1
  #define PIF_BLOCK_ACCESS_RETRX_LIMIT		0//3
  #define PIF_BLOCK_ACCESS_POLL_DELAY		1	/* us */

  /*
   * register
   */
  #define MPIF_R_BASE	0xbf82d000
  #define SPIF_R_BASE   0xbf82e000

  /*
   * polling config
   */
  #define MPIF_ACCESS_POLL_COUNT        20480 //20480

  /*
   * busy timeout count
   */
  #define MPIF_BUSY_TIMEOUT_COUNT       0x100 // PIF_CLK cycle unit


  /*
   * some general configuration
   */
  #define PIF_CONFIG_STREAM_MODE        1
  #define PIF_PATH_WIDTH	            2   /* 0:1bit  1:2bit  2:4bit */
  #define PIF_INTERRUPT_SUPPORT	        0
  #define PIF_DEFAULT_SID               3
  #define PIF_1BIT_CMD_WIDTH            1 // 0: means command width equal to data witdth
  #define PIF_RESET_AFTER_EACH_ACTION   0
  #define PIF_B_BANK_SUPPORT            0 //1
  #define PIF_3A3B_SUPPORT              1 //0
  #define PIF_4A_SUPPORT                0 //1
  #define PIF_SPIF_RIU_BASE             0x580
#endif /* #ifdef ECO_CONFIG */


/***************************************************************
*
*	internal options
*
***************************************************************/

#define PIF_SAFTY_READ  1


/***************************************************************
*
*	debug options, not open for user
*
***************************************************************/

#define PIF_DEBUG	0
#define PIF_DEBUG_BUF_SIZE	2048
#define PIF_DEBUG_MIU_TEST_UNIT 256
#define PIF_DEBUG_MIU_DATA_READY_TIME   15 /* ms */
#define PIF_DEBUG_RIU_TEST_ADDR 0x3a0
#define PIF_DEBUG_MIU_TEST  0


/***************************************************************
*
*	miu convert
*
***************************************************************/

#define PIF_OS_MIU_ADDR(addr)		(((pif_dma_addr_t)(addr) & 0xFFFFFFF8) >> 2)//(((pif_dma_addr_t)(addr) & 0xFFFFFFF0) >> 2)
#define PIF_OS_RIU_ADDR(addr) 		pif_os_addr_convert(addr)


/***************************************************************
*
*	types
*
***************************************************************/

typedef unsigned long pif_riu_t;
typedef unsigned long pif_intr_state_t;


/***************************************************************
*
*	interrupt
*
***************************************************************/

#define PIF_OS_DISABLE_INTR()		HAL_DISABLE_INTERRUPTS(pif_cb.intr_state)
#define PIF_OS_ENABLE_INTR()		HAL_RESTORE_INTERRUPTS(pif_cb.intr_state)


/***************************************************************
*
*	delay
*
***************************************************************/

#define PIF_OS_DELAY(us)                cyg_thread_delay(us)
#define PIF_OS_PAUSE(us) 				cyg_thread_delay(us)


/***************************************************************
*
*	cache
*
***************************************************************/

#define PIF_OS_UNCACHE_ADDR(addr)       ((addr) | 0xa0000000)


/***************************************************************
*
*	debug
*
***************************************************************/

#define PIF_OS_HW_UINT16_READ(a, r)         HAL_READ_UINT16((a), (r))
#define PIF_OS_HW_UINT16_WRITE(a, r)        HAL_WRITE_UINT16((a), (r))


/***************************************************************
*
*	log
*
***************************************************************/

//extern int diag_printf(const char *fmt, ...);
#define PIF_OS_DEBUG	diag_printf //cyg_thread_delay(1); Uart1_Printf
#define PIF_OS_PRINT	diag_printf //cyg_thread_delay(1); Uart1_Printf

#include <cyg/kernel/kapi.h>
#include <pkgconf/kernel.h>


/***************************************************************
*
*	func prototype
*
***************************************************************/

/*
 * os
 */
pif_err_t pif_os_init(void);
pif_addr_t pif_os_addr_convert(pif_addr_t addr);


#endif /* #ifndef __PIF_OS_H__ */

