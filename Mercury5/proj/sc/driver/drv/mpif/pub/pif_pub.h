/*------------------------------------------------------------------------------
	Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    PROJECT:
        Hercules
    DESCRIPTION:
        PIF middle ware header

    HISTORY:
        2009.08.17    Vince Hsieh   initial version
        2010.05.05    Edgar Lu      second version for big3
-------------------------------------------------------------------------------*/
#ifndef __PIF_PUB_H__
#define __PIF_PUB_H__

/************************************************************************
 * Include File
 ************************************************************************/
#include "typedefs_pub.h"
#include "pif_reg_pub.h"
//#include "sys_sys.h"
//#include "driver_mpif.h"


//UINT32 _pif_dsr(void);
/************************************************************************
 * Constant
 ************************************************************************/

//#define HERCULES

#define MPIF_ID         MPIF2
#define MPIF_TRACE                  (_CUS2|LEVEL_17)
#ifdef __GPS_DUALSTAR_DRV__
#define SPIF_HAS_2_DAR
#endif
/*
 *  Defination for PIF API test and workaround
 */
#define PIF_API_TEST                    0       /* Set to 1 to do PIF API test */

#if PIF_API_TEST
#define PIF_API_TEST_4A                 1//PIF_DMA

#define PIF_API_TEST_ITERATION_TIMES    0x4000//0x20000
#define PIF_API_TEST_3A_LENGTH          18*1024//16   //64
#define PIF_API_TEST_4A_LENGTH          992 //1024  // Big2 bug, 992 is maximum write length of 4A

#endif

#define I_SW_PIF_TEST                    1       /* Set to 1 to support I-SW test */

#if I_SW_PIF_TEST
#define PIF_API_TEST_3A_LENGTH          18*1024//16   //64
#define PIF_API_TEST_4A_LENGTH          992 //1024  // Big2 bug, 992 is maximum write length of 4A

#endif

/*
* read / write parameter
*/
#define PIF_ACCESS_CHECKSUM         0
#define PIF_ACCESS_RETRX_LIMIT		0
#define PIF_ACCESS_POLL_DELAY		1	/* us */

/*
* block read / write parameter
*/
#define PIF_BLOCK_ACCESS_CHECKSUM		0
#define PIF_BLOCK_ACCESS_RETRX_LIMIT	1
#define PIF_BLOCK_ACCESS_POLL_DELAY     5	/* us */

/*
* polling config
*/
#define MPIF_ACCESS_POLL_COUNT      20480

/*
 * some general configuration
 */

#ifdef __GPS_DUALSTAR_DRV__
#define PIF_MPIF_BUS_CLOCK          SET_MPIF_BUS_CLOCK_11M
#else
#define PIF_MPIF_BUS_CLOCK          SET_MPIF_BUS_CLOCK_39M
#endif

#define PIF_DEFAULT_SID             3  // BT: 2, Carina:3, Hydra:3.
#define DUALSTAR_DEFAULT_SID        0  // Dualstar:0.
#define PIF_CONFIG_STREAM_MODE      1
#define PIF_PATH_WIDTH	            0   /* 0:1bit  1:2bit  2:4bit */
//#define PIF_INTERRUPT_SUPPORT	    0
#define PIF_1BIT_CMD_WIDTH          0
#define PIF_RESET_AFTER_EACH_ACTION 0
#define PIF_B_BANK_SUPPORT          1
#define PIF_3A3B_SUPPORT            0
#define PIF_4A_SUPPORT              1
#define PIF_SPIF_RIU_BASE           0x580

#define PIF_TURN_AROUND_CYCLE       1
#define PIF_WAIT_ACK_CYCLE          1

/* Flag */
#define PIF_F_READY	        (1 << 0)
#define PIF_F_LOCK	        (1 << 1)
#define PIF_F_DAR		    (1 << 2)
#define PIF_F_DOUBLE_WORD	(1 << 3)
#define PIF_F_STREAM_MODE	(1 << 4)
#define PIF_F_USE_B_BANK	(1 << 5)

/* Address mapping */
#define JAL_BASE_ADDR   0x40000000
#define HAB_BASE_ADDR   0x41000000

#ifdef HERCULES

#define BT_JAL_BASE     JAL_BASE_ADDR
#define BT_JAL_SIZE     0x10000
#define BT_HAB_BASE     HAB_BASE_ADDR
#define BT_HAB_SIZE     0x10000
#define BT_HW_JAL_BASE     0xD00
#define BT_HW_HAB_BASE     0x1280

#endif  //#ifdef HERCULES

/************************************************************************
 * Macros
 ************************************************************************/
#ifdef HERCULES

#define BT_IS_JAL_ADDR(a)      (((a) >= BT_JAL_BASE) && ((a) < (BT_JAL_BASE + BT_JAL_SIZE)))
#define BT_IS_HAB_ADDR(a)      (((a) >= BT_HAB_BASE) && ((a) < (BT_HAB_BASE + BT_HAB_SIZE)))
#define BT_HW_JAL_ADDR(a)       (BT_HW_JAL_BASE + (((a) - BT_JAL_BASE) >> 1))
#define BT_HW_HAB_ADDR(a)       (BT_HW_HAB_BASE + (((a) - BT_HAB_BASE) >> 1))

#endif  //#ifdef HERCULES

/************************************************************************
 * Data type
 ************************************************************************/

#ifndef BOOL
#define BOOL unsigned char
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U8
#define U8  unsigned char
#endif

#ifndef UINT8
#define UINT8  unsigned char
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif




/************************************************************************
 * Extern Global Variable
 ************************************************************************/

/************************************************************************
 * Extern Global Function
 ************************************************************************/

#if PIF_API_TEST
UINT32 pif_api_test(UINT8 testCase);
#endif


//For dualstar
/* 1A */
UINT8 dualstar_pif_init(UINT8 checksum);
UINT8 dualstar_pif_read_status(UINT32 u32Addr, UINT32 *pu32Val);
UINT8 dualstar_pif_write_status(UINT32 u32Addr, UINT32 u32Val);
//For dualstar



#endif /* #ifndef __PIF_PUB_H__ */

