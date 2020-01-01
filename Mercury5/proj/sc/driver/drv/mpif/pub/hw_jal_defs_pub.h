#ifndef _PARTHUS_HW_JAL_DEFS_PUB_H_
#define _PARTHUS_HW_JAL_DEFS_PUB_H_


/******************************************************************************
 * MODULE:          hw_jal_defs.h
 * PROJECT:         BlueStream
 * MAINTAINER:      John Nelson, Ivan Griffin
 * CREATION NAME:   7.July.1999
 *
 * LICENSE:
 *     This source code is copyright (c) 2000-2004 Ceva Inc.
 *     All rights reserved.
 *
 * SOURCE CONTROL: $Id: hw_jal_defs.h,v 1.1.2.3 2006/10/05 05:48:53 artis.chiu Exp $
 *
 * COMMENTS:
 *
 *     There will be the requirement to present two definitions based on
 *     the register/memory addressing approach adopted.
 *     Currently a 32 bit approach is adopted. The associated HW module
 *     is generic of the approach, but will depend on correct constants.
 *
 * REVISION HISTORY:
 *     7 July 1999    Jalapeno Revision 1.0, 30 June 1999
 *    30 July 1999      Jalapeno Revision 2.4, 14 July 1999
 *    07 Oct  1999      Jalapeno Revision (jal006v2.2)
 *    15 Nov  1999      Restructured as a result of habanero introduction.
 *     3 Mar  2000      Added definitions to support register caching
 ******************************************************************************/

/*
 * the error directive had a hash include in it -- some customer
 * complain at this !!
 */
#ifndef JAL_BASE_ADDR
#error Must include "sys_config.h" for BASE_ADDR of Jalapeno/Habanero
#endif

#ifdef __HERCULES_AEON__
#define JAL_ADDR_CONVERT(addr)          ((((addr) - JAL_BASE_ADDR) << 1) + JAL_BASE_ADDR)
#else
#define JAL_ADDR_CONVERT(addr)          ((addr) + JAL_BASE_ADDR)
#endif

/****************************************************************
*
*  Define the addresses and bit positions for the Transmit Control
*  Registers. The Addresss assume a 32 bit address space.
*  The 16 bit address bus mappings are taken care of by the macros in
*  the HW_lbl.h.
*
*****************************x***********************************/
#ifdef __HERCULES_AEON__
#define JAL_BD_ADDR_ADDR     (0x00000000*2 + JAL_BASE_ADDR)
#define JAL_BD_ADDR_MASK     0xFFFFFFFF
#define JAL_BD_ADDR_SHFT     0

#define JAL_UAP_LAP_ADDR     (0x00000000*2 + JAL_BASE_ADDR)
#define JAL_NAP_ADDR         (0x00000004*2 + JAL_BASE_ADDR)

#define JAL_SYNC_ADDR        (0x00000008*2 + JAL_BASE_ADDR)
#define JAL_SYNC_MASK        0xFFFFFFFF
#define JAL_SYNC_SHFT        0

#define JAL_SYNC2_ADDR       (0x0000000C*2 + JAL_BASE_ADDR)
#define JAL_SYNC2_MASK       0xFFFFFFFF
#define JAL_SYNC2_SHFT       0

#define JAL_INTRASLOT_OFFSET_ADDR        (0x00000010*2 + JAL_BASE_ADDR)
#define JAL_INTRASLOT_OFFSET_MASK        0x000007FF
#define JAL_INTRASLOT_OFFSET_SHFT        0

#define JAL_BT_CLK_OFFSET_ADDR      (0x00000018*2 + JAL_BASE_ADDR)
#define JAL_BT_CLK_OFFSET_MASK      0x0FFFFFFF
#define JAL_BT_CLK_OFFSET_SHFT      0

#define JAL_NATIVE_CLK_ADDR  (0x0000001c*2 + JAL_BASE_ADDR)
#define JAL_NATIVE_CLK_MASK  0x0FFFFFFF
#define JAL_NATIVE_CLK_SHFT  0

#define JAL_AM_ADDR_ADDR     (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_AM_ADDR_MASK     0x00000007
#define JAL_AM_ADDR_SHFT     0

#define JAL_ENCRYPT_ADDR     (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_ENCRYPT_MASK     0x00000018
#define JAL_ENCRYPT_SHFT     3

#define JAL_USE_LF_ADDR      (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_USE_LF_MASK      0x00000020
#define JAL_USE_LF_SHFT      5

#define JAL_SLAVE_ADDR       (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SLAVE_MASK       0x00000040
#define JAL_SLAVE_SHFT       6

#define JAL_PAGE_ADDR        (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_PAGE_MASK        0x00000080
#define JAL_PAGE_SHFT        7

#define JAL_SCO_CFG_ADDR   (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SCO_CFG_MASK   0x000FFF00
#define JAL_SCO_CFG_SHFT   8

#define JAL_SCO_CFG0_ADDR   (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SCO_CFG0_MASK   0x00000F00
#define JAL_SCO_CFG0_SHFT   8

#define JAL_SCO_CFG1_ADDR   (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SCO_CFG1_MASK   0x0000F000
#define JAL_SCO_CFG1_SHFT   12

#define JAL_SCO_CFG2_ADDR   (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SCO_CFG2_MASK   0x000F0000
#define JAL_SCO_CFG2_SHFT   16

#define JAL_SCO_FIFO_ADDR    (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_SCO_FIFO_MASK    0x00300000
#define JAL_SCO_FIFO_SHFT    20

#define JAL_VCI_CLK_SEL_ADDR    (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_VCI_CLK_SEL_MASK    0x00c00000
#define JAL_VCI_CLK_SEL_SHFT    22

#define JAL_CRC_INIT_ADDR    (0x00000020*2 + JAL_BASE_ADDR)
#define JAL_CRC_INIT_MASK    0xff000000
#define JAL_CRC_INIT_SHFT    24

#define JAL_LOOP_ADDR        (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_LOOP_MASK        0x00000001
#define JAL_LOOP_SHFT        0

#define JAL_TEST_ECO_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_ECO_MASK    0x00000002
#define JAL_TEST_ECO_SHFT    1

#define JAL_ECO_ERR_ADDR     (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_ECO_ERR_MASK     0x0000003C
#define JAL_ECO_ERR_SHFT     2

#define JAL_TEST_CRC_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_CRC_MASK    0x00000040
#define JAL_TEST_CRC_SHFT    6

#define JAL_TEST_HEC_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_HEC_MASK    0x00000080
#define JAL_TEST_HEC_SHFT    7

#define JAL_TEST_RADIO_ADDR  (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_RADIO_MASK  0x00000100
#define JAL_TEST_RADIO_SHFT  8

#define JAL_VCI_CLK_SEL_MAP_ADDR     (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_VCI_CLK_SEL_MAP_MASK     0x00000200
#define JAL_VCI_CLK_SEL_MAP_SHFT     9

#define JAL_TEST_FORCE_NO_DDW_ADDR (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_FORCE_NO_DDW_MASK 0x00000400
#define JAL_TEST_FORCE_NO_DDW_SHFT 10

#define JAL_TEST_MSG_ADDR       (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_MSG_MASK       0x00000800
#define JAL_TEST_MSG_SHFT       11

#define JAL_TEST_TX_SHIFT_ADDR  (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_TEST_TX_SHIFT_MASK  0x00007000
#define JAL_TEST_TX_SHIFT_SHFT  12

#define JAL_USE_HAB_CTRL_ADDR   (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_USE_HAB_CTRL_MASK   0x00008000
#define JAL_USE_HAB_CTRL_SHFT   15

/*
 * Setup Full DWH register to allow fast clearance of all DWH registers
 */
#define JAL_DWH_ALL_REG_ADDR      (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_DWH_ALL_REG_MASK      0xFFBF0000
#define JAL_DWH_ALL_REG_SHFT      16

#define JAL_DWH_INIT_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_DWH_INIT_MASK    0x003f0000
#define JAL_DWH_INIT_SHFT    16

/*
 * RGB 22/08/01 - new bit added for switching between codec types
 */
#define JAL_CODEC_TYPE_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_CODEC_TYPE_MASK    0x00400000
#define JAL_CODEC_TYPE_SHFT    22

#define JAL_DWH_BY_BT_CLK_ADDR    (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_DWH_BY_BT_CLK_MASK    0x00800000
#define JAL_DWH_BY_BT_CLK_SHFT    23

#define JAL_DWH2_INIT_ADDR   (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_DWH2_INIT_MASK   0x3f000000
#define JAL_DWH2_INIT_SHFT   24

#define JAL_WHITEN_ADDR      (0x00000024*2 + JAL_BASE_ADDR)
#define JAL_WHITEN_MASK      0x80000000
#define JAL_WHITEN_SHFT      31

/*
 * Interrupt related
 */
#define JAL_TIM_INTR_MSK_ADDR        (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_MSK_MASK        0x0000000f
#define JAL_TIM_INTR_MSK_SHFT        0

#define JAL_TIM0_INTR_MSK_ADDR       (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_MSK_MASK       0x00000001
#define JAL_TIM0_INTR_MSK_SHFT       0

#define JAL_TIM1_INTR_MSK_ADDR       (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_MSK_MASK       0x00000002
#define JAL_TIM1_INTR_MSK_SHFT       1

#define JAL_TIM2_INTR_MSK_ADDR       (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_MSK_MASK       0x00000004
#define JAL_TIM2_INTR_MSK_SHFT       2

#define JAL_TIM3_INTR_MSK_ADDR       (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_MSK_MASK       0x00000008
#define JAL_TIM3_INTR_MSK_SHFT       3

#define JAL_PKD_INTR_MSK_ADDR        (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKD_INTR_MSK_MASK        0x00000010
#define JAL_PKD_INTR_MSK_SHFT        4

#define JAL_AUX_TIM_INTR_MSK_ADDR    (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_MSK_MASK    0x00000020
#define JAL_AUX_TIM_INTR_MSK_SHFT    5

#define JAL_PKA_INTR_MSK_ADDR        (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKA_INTR_MSK_MASK        0x00000040
#define JAL_PKA_INTR_MSK_SHFT        6

#define JAL_PKD_RX_HDR_INTR_MSK_ADDR (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_MSK_MASK 0x00000080
#define JAL_PKD_RX_HDR_INTR_MSK_SHFT 7

#define JAL_GIO_INTR_MSK0_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK0_MASK  0x00000300
#define JAL_GIO_INTR_MSK0_SHFT  8

#define JAL_GIO_INTR_MSK1_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK1_MASK  0x00000c00
#define JAL_GIO_INTR_MSK1_SHFT  10

#define JAL_GIO_INTR_MSK2_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK2_MASK  0x00001000 /* NO_PKD_INTR_MASK in this location CM(20Apr2000) 0x03000 */
#define JAL_GIO_INTR_MSK2_SHFT  12

#define JAL_GIO_INTR_MSK3_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK3_MASK  0x0000c000
#define JAL_GIO_INTR_MSK3_SHFT  14

#if(PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1)

#define JAL_TIM_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_CLR_MASK   0x000f0000
#define JAL_TIM_INTR_CLR_SHFT   16

#define JAL_TIM0_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_CLR_MASK   0x00010000
#define JAL_TIM0_INTR_CLR_SHFT   16

#define JAL_TIM1_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_CLR_MASK   0x00020000
#define JAL_TIM1_INTR_CLR_SHFT   17

#define JAL_TIM2_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_CLR_MASK   0x00040000
#define JAL_TIM2_INTR_CLR_SHFT   18

#define JAL_TIM3_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_CLR_MASK   0x00080000
#define JAL_TIM3_INTR_CLR_SHFT   19

#else   /* (PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1) */

#define JAL_TIM_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_CLR_MASK   0x00010000
#define JAL_TIM_INTR_CLR_SHFT   16

#define JAL_TIM0_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_CLR_MASK   0x00010000
#define JAL_TIM0_INTR_CLR_SHFT   16

#define JAL_TIM1_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_CLR_MASK   0x00010000
#define JAL_TIM1_INTR_CLR_SHFT   16

#define JAL_TIM2_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_CLR_MASK   0x00010000
#define JAL_TIM2_INTR_CLR_SHFT   16

#define JAL_TIM3_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_CLR_MASK   0x00010000
#define JAL_TIM3_INTR_CLR_SHFT   16

#endif  /* (PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1) */

#define JAL_PKD_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKD_INTR_CLR_MASK   0x00100000
#define JAL_PKD_INTR_CLR_SHFT   20

#define JAL_AUX_TIM_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_CLR_MASK   0x00200000
#define JAL_AUX_TIM_INTR_CLR_SHFT   21

#define JAL_PKA_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKA_INTR_CLR_MASK   0x00400000
#define JAL_PKA_INTR_CLR_SHFT   22

#define JAL_NO_PKT_RCVD_INTR_ADDR    (0x0000002C*2 + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_SHFT    13
#define JAL_NO_PKT_RCVD_INTR_MASK    0x00002000

#define JAL_SYNC_DET_INTR_ADDR    (0x0000002C*2 + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_SHFT    14
#define JAL_SYNC_DET_INTR_MASK    0x00004000

#define JAL_SLEEP_STATUS_ADDR    (0x0000002C*2 + JAL_BASE_ADDR)
#define JAL_SLEEP_STATUS_SHFT    15
#define JAL_SLEEP_STATUS_MASK    0x00008000

#define JAL_NO_PKT_RCVD_INTR_MSK_ADDR (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_MSK_SHFT 13
#define JAL_NO_PKT_RCVD_INTR_MSK_MASK 0x00002000

#define JAL_SYNC_DET_INTR_MSK_ADDR (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_MSK_SHFT 14
#define JAL_SYNC_DET_INTR_MSK_MASK 0x00004000

#define JAL_NO_PKT_RCVD_INTR_CLR_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_CLR_SHFT  29
#define JAL_NO_PKT_RCVD_INTR_CLR_MASK  0x20000000

#define JAL_SYNC_DET_INTR_CLR_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_CLR_SHFT  30
#define JAL_SYNC_DET_INTR_CLR_MASK  0x40000000

#define JAL_VCI_SYNC_DIR_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_VCI_SYNC_DIR_SHFT  31
#define JAL_VCI_SYNC_DIR_MASK  0x80000000

#define JAL_PKD_RX_HDR_INTR_CLR_ADDR   (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_CLR_MASK   0x00800000
#define JAL_PKD_RX_HDR_INTR_CLR_SHFT   23

#define JAL_GIO_INTR_CLR0_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR0_MASK  0x01000000
#define JAL_GIO_INTR_CLR0_SHFT  24

#define JAL_GIO_INTR_CLR1_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR1_MASK  0x04000000
#define JAL_GIO_INTR_CLR1_SHFT  26

#define JAL_GIO_INTR_CLR2_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR2_MASK  0x10000000
#define JAL_GIO_INTR_CLR2_SHFT  28

#define JAL_PG_TIMEOUT_INTR_CLR_ADDR (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_PG_TIMEOUT_INTR_CLR_SHFT 0x20000000
#define JAL_PG_TIMEOUT_INTR_CLR_MASK 29

#define JAL_GIO_INTR_CLR3_ADDR  (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR3_MASK  0x40000000
#define JAL_GIO_INTR_CLR3_SHFT  30

/****************************************************************
*  Define the bit positions for the Common Status Registers
****************************************************************/

#define JAL_TIM_INTR_ADDR         (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_MASK         0x0000000f
#define JAL_TIM_INTR_SHFT         0

#define JAL_TIM0_INTR_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_MASK        0x00000001
#define JAL_TIM0_INTR_SHFT        0

#define JAL_TIM1_INTR_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_MASK        0x00000002
#define JAL_TIM1_INTR_SHFT        1

#define JAL_TIM2_INTR_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_MASK        0x00000004
#define JAL_TIM2_INTR_SHFT        2

#define JAL_TIM3_INTR_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_MASK        0x00000008
#define JAL_TIM3_INTR_SHFT        3

#define JAL_PKD_INTR_ADDR         (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_PKD_INTR_MASK         0x00000010
#define JAL_PKD_INTR_SHFT         4

#define JAL_AUX_TIM_INTR_ADDR     (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_MASK     0x00000020
#define JAL_AUX_TIM_INTR_SHFT     5

#define JAL_PKA_INTR_ADDR         (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_PKA_INTR_MASK         0x00000040
#define JAL_PKA_INTR_SHFT         6

#define JAL_PKD_RX_HDR_INTR_ADDR  (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_MASK  0x00000080
#define JAL_PKD_RX_HDR_INTR_SHFT  7

#define JAL_GIO_INTR0_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR0_MASK        0x00000100
#define JAL_GIO_INTR0_SHFT        8

#define JAL_GIO_INTR1_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR1_MASK        0x00000400
#define JAL_GIO_INTR1_SHFT        10

#define JAL_GIO_INTR2_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR2_MASK        0x00001000
#define JAL_GIO_INTR2_SHFT        12

#define JAL_PG_TIMEOUT_INTR_ADDR  (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_PG_TIMEOUT_INTR_MASK  0x00002000
#define JAL_PG_TIMEOUT_INTR_SHFT  13

#define JAL_GIO_INTR3_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_GIO_INTR3_MASK        0x00004000
#define JAL_GIO_INTR3_SHFT        14

#define JAL_SLEEP_ADDR        (0x0000002c*2 + JAL_BASE_ADDR)
#define JAL_SLEEP_MASK        0x00008000
#define JAL_SLEEP_SHFT        15

/*************************************
 * TX Control Registers
 ************************************/
#define JAL_TX_LEN_ADDR      (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_LEN_MASK      0x000001ff
#define JAL_TX_LEN_SHFT      0

#define JAL_TX_TYPE_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_TYPE_MASK     0x00001e00
#define JAL_TX_TYPE_SHFT     9

#define JAL_TX_FLOW_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_FLOW_MASK     0x00002000
#define JAL_TX_FLOW_SHFT     13

#define JAL_TX_ARQN_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_ARQN_MASK     0x00004000
#define JAL_TX_ARQN_SHFT     14

#define JAL_TX_SEQN_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_SEQN_MASK     0x00008000
#define JAL_TX_SEQN_SHFT     15

#define JAL_TX_BUF_ADDR      (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_BUF_MASK      0x00010000
#define JAL_TX_BUF_SHFT      16

#define JAL_TX_MODE_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_MODE_MASK     0x00060000
#define JAL_TX_MODE_SHFT     17

#define JAL_TRANSMIT_ADDR    (0x00000030*2 + JAL_BASE_ADDR)  /* Obsolete */
#define JAL_TRANSMIT_MASK    0x00020000
#define JAL_TRANSMIT_SHFT    17

#define JAL_TX_HALF_ADDR     (0x00000030*2 + JAL_BASE_ADDR)  /* Obsolete */
#define JAL_TX_HALF_MASK     0x00040000
#define JAL_TX_HALF_SHFT     18

#define JAL_TX_L_CH_ADDR     (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_L_CH_MASK     0x00180000
#define JAL_TX_L_CH_SHFT     19

#define JAL_TX_P_FLOW_ADDR   (0x00000030*2 + JAL_BASE_ADDR)
#define JAL_TX_P_FLOW_MASK   0x00200000
#define JAL_TX_P_FLOW_SHFT   21

/*************************************
 * eSCO Control Registers
 ************************************/

#define JAL_ESCO_TX_LEN_ADDR   (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_ESCO_TX_LEN_MASK   0x000000FF
#define JAL_ESCO_TX_LEN_SHFT   0

#define JAL_ESCO_RX_LEN_ADDR   (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_ESCO_RX_LEN_MASK   0x0000FF00
#define JAL_ESCO_RX_LEN_SHFT   8

#define JAL_ESCO_LT_ADDR_ADDR   (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_ESCO_LT_ADDR_MASK   0x00070000
#define JAL_ESCO_LT_ADDR_SHFT   16

#define JAL_SCO_ROUTE_ADDR      (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_SCO_ROUTE_MASK      0x00080000
#define JAL_SCO_ROUTE_SHFT      19

/* hw conversion codec */
#define JAL_NEW_AULAW_TBL_ADDR         (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_NEW_AULAW_TBL_MASK         0x00100000
#define JAL_NEW_AULAW_TBL_SHFT         20

#define JAL_SCO_TX_ALIGN_MSB_ADDR      (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_SCO_TX_ALIGN_MSB_MASK      0x00200000
#define JAL_SCO_TX_ALIGN_MSB_SHFT      21

#define JAL_SCO_RX_ALIGN_MSB_ADDR      (0x00000034*2 + JAL_BASE_ADDR)
#define JAL_SCO_RX_ALIGN_MSB_MASK      0x00400000
#define JAL_SCO_RX_ALIGN_MSB_SHFT      22

/****************************************************************
*
*  Define the bit positions for the Transmit Status Registers
*
****************************************************************/
#define JAL_TX0_OVER_ADDR   (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX0_OVER_MASK   0x00000001
#define JAL_TX0_OVER_SHFT   0

#define JAL_TX0_UNDER_ADDR  (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX0_UNDER_MASK  0x00000002
#define JAL_TX0_UNDER_SHFT  1

#define JAL_TX1_OVER_ADDR   (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX1_OVER_MASK   0x00000004
#define JAL_TX1_OVER_SHFT   2


#define JAL_TX1_UNDER_ADDR  (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX1_UNDER_MASK  0x00000008
#define JAL_TX1_UNDER_SHFT  3

#define JAL_TX2_OVER_ADDR   (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX2_OVER_MASK   0x00000010
#define JAL_TX2_OVER_SHFT   4

#define JAL_TX2_UNDER_ADDR  (0x00000040*2 + JAL_BASE_ADDR)
#define JAL_TX2_UNDER_MASK  0x00000020
#define JAL_TX2_UNDER_SHFT  5



/****************************************************************
*
*  Define the bit positions for the Receive Control Rgeisters
*
****************************************************************/

#define JAL_RX_MODE_ADDR    (0x00000048*2 + JAL_BASE_ADDR)   /* Combination of RX_EN and FULL_WIN */
#define JAL_RX_MODE_MASK    0x00000003
#define JAL_RX_MODE_SHFT    0

#define JAL_RX_BUF_ADDR     (0x00000048*2 + JAL_BASE_ADDR)
#define JAL_RX_BUF_MASK     0x00000100
#define JAL_RX_BUF_SHFT     8

#define JAL_ERR_SEL_ADDR    (0x00000048*2 + JAL_BASE_ADDR)
#define JAL_ERR_SEL_MASK    0x00000e00
#define JAL_ERR_SEL_SHFT    9

#define JAL_WIN_EXT_ADDR    (0x00000048*2 + JAL_BASE_ADDR)
#define JAL_WIN_EXT_MASK    0x003ff000
#define JAL_WIN_EXT_SHFT    12

#define JAL_ABORT_ON_WRONG_AM_ADDR_ADDR (0x00000048*2 + JAL_BASE_ADDR)
#define JAL_ABORT_ON_WRONG_AM_ADDR_MASK 0x00800000
#define JAL_ABORT_ON_WRONG_AM_ADDR_SHFT 23

/****************************************************************
*
*  Define the bit positions for the Receive Status Rgeisters
*
****************************************************************/
#define JAL_RX_LEN_ADDR    (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_LEN_MASK    0x000001ff
#define JAL_RX_LEN_SHFT    0

#define JAL_RX_TYPE_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_TYPE_MASK   0x00001e00
#define JAL_RX_TYPE_SHFT   9

#define JAL_RX_FLOW_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_FLOW_MASK   0x00002000
#define JAL_RX_FLOW_SHFT   13

#define JAL_RX_ARQN_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_ARQN_MASK   0x00004000
#define JAL_RX_ARQN_SHFT   14

#define JAL_RX_SEQN_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_SEQN_MASK   0x00008000
#define JAL_RX_SEQN_SHFT   15

#define JAL_RX_AM_ADDR_ADDR (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_AM_ADDR_MASK 0x00070000
#define JAL_RX_AM_ADDR_SHFT 16

#define JAL_RX_L_CH_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_L_CH_MASK   0x00180000
#define JAL_RX_L_CH_SHFT   19

#define JAL_RX_P_FLOW_ADDR (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_P_FLOW_MASK 0x00200000
#define JAL_RX_P_FLOW_SHFT 21

#define JAL_RX_PKT_ADDR    (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_PKT_MASK    0x01000000
#define JAL_RX_PKT_SHFT    24

#define JAL_HEC_ERR_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_HEC_ERR_MASK   0x02000000
#define JAL_HEC_ERR_SHFT   25

#define JAL_CRC_ERR_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_CRC_ERR_MASK   0x04000000
#define JAL_CRC_ERR_SHFT   26

#define JAL_RX_HDR_ADDR    (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_HDR_MASK    0x08000000
#define JAL_RX_HDR_SHFT    27

//YC 20081112 Added
#define JAL_RX_EDR_SYNC_ERR_ADDR    (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_RX_EDR_SYNC_ERR_MASK    0x40000000
#define JAL_RX_EDR_SYNC_ERR_SHFT    30

#define JAL_RX0_OVER_ADDR  (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX0_OVER_MASK  0x00000001
#define JAL_RX0_OVER_SHFT  0

#define JAL_RX0_UNDER_ADDR (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX0_UNDER_MASK 0x00000002
#define JAL_RX0_UNDER_SHFT 1

#define JAL_RX1_OVER_ADDR  (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX1_OVER_MASK  0x00000004
#define JAL_RX1_OVER_SHFT  2

#define JAL_RX1_UNDER_ADDR (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX1_UNDER_MASK 0x00000008
#define JAL_RX1_UNDER_SHFT 3

#define JAL_RX2_OVER_ADDR  (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX2_OVER_MASK  0x00000010
#define JAL_RX2_OVER_SHFT  4

#define JAL_RX2_UNDER_ADDR (0x00000054*2 + JAL_BASE_ADDR)
#define JAL_RX2_UNDER_MASK 0x00000020
#define JAL_RX2_UNDER_SHFT 5

#define JAL_ERR_CNT_ADDR   (0x0000005C*2 + JAL_BASE_ADDR)
#define JAL_ERR_CNT_MASK   0x0000FFFF
#define JAL_ERR_CNT_SHFT   0

#define JAL_AM_ADDR_ABORT_ADDR   (0x00000050*2 + JAL_BASE_ADDR)
#define JAL_AM_ADDR_ABORT_MASK   0x20000000
#define JAL_AM_ADDR_ABORT_SHFT   29

/****************************************************************
*
*  Define the bit positions for the gio control registers
*
****************************************************************/
#define JAL_GIO_HIGH_ADDR   (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_GIO_HIGH_MASK   0x000007ff
#define JAL_GIO_HIGH_SHFT   0

#define JAL_GIO_LOW_ADDR    (0x00000070*2 + JAL_BASE_ADDR)
#define JAL_GIO_LOW_MASK    0x000007ff
#define JAL_GIO_LOW_SHFT    0

/***************************************************************
*
*   Define the bit positions for the gio combine registers
*
***************************************************************/
#define JAL_GIO0_ADDR   (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_GIO0_MASK   0x0000000F
#define JAL_GIO0_SHFT   0

#define JAL_GIO1_ADDR   (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_GIO1_MASK   0x000000F0
#define JAL_GIO1_SHFT   4

#define JAL_GIO2_ADDR   (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_GIO2_MASK   0x00000F00
#define JAL_GIO2_SHFT   8

#define JAL_GIO3_ADDR   (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_GIO3_MASK   0x0000F000
#define JAL_GIO3_SHFT   12

/****************************************************************
*
*    Define the bit positions for the gio status registers
*
*****************************************************************/
#define JAL_GIO_STATUS_ADDR (0x00000084*2 + JAL_BASE_ADDR)
#define JAL_GIO_STATUS_MASK 0x0000000F
#define JAL_GIO_STATUS_SHFT 0

/****************************************************************
*
*  Define the bit positions for the Parallel Interface Adaptor
*
****************************************************************/
#define JAL_P_DATA_0_ADDR      (0x000000A4*2 + JAL_BASE_ADDR)
#define JAL_P_DATA_0_MASK      0x000000FF
#define JAL_P_DATA_0_SHFT      0

#define JAL_P_DATA_1_ADDR      (0x000000A4*2 + JAL_BASE_ADDR)
#define JAL_P_DATA_1_MASK      0x0000FF00
#define JAL_P_DATA_1_SHFT      8

#define JAL_P_DATA_2_ADDR      (0x000000A4*2 + JAL_BASE_ADDR)
#define JAL_P_DATA_2_MASK      0x00FF0000
#define JAL_P_DATA_2_SHFT      16

#define JAL_P_DATA_3_ADDR      (0x000000A4*2 + JAL_BASE_ADDR)
#define JAL_P_DATA_3_MASK      0xFF000000
#define JAL_P_DATA_3_SHFT      24

#define JAL_P_SETUP_ADDR      (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_SETUP_MASK       0x000000FF
#define JAL_P_SETUP_SHFT       0

#define JAL_P_MASK_ADDR        (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_MASK_MASK        0x00000F00
#define JAL_P_MASK_SHFT        8

#define JAL_P_NOW_ADDR         (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_NOW_MASK         0x00001000
#define JAL_P_NOW_SHFT         12

#define JAL_P_SEQ_ADDR         (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_SEQ_MASK         0x00002000
#define JAL_P_SEQ_SHFT         13

#define JAL_P_DATA_DIR_ADDR    (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_DATA_DIR_MASK    0x00004000
#define JAL_P_DATA_DIR_SHFT    14

#define JAL_P_RDATA_ADDR       (0x000000A8*2 + JAL_BASE_ADDR)
#define JAL_P_RDATA_MASK       0x007F0000
#define JAL_P_RDATA_SHFT       16

/****************************************************************
*
*  Define the bit positions for the Serial Interface Registers
*
****************************************************************/
#define JAL_SER_CFG_ADDR        (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_CFG_MASK        0x7FFFFFFF
#define JAL_SER_CFG_SHFT        0

#if MBB
#define JAL_SER_WRITE_ADDR       (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_WRITE_MASK       0x20000000
#define JAL_SER_WRITE_SHFT       29

#define JAL_SER_PKT_LEN_H_ADDR       (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_PKT_LEN_H_MASK       0x10000000
#define JAL_SER_PKT_LEN_H_SHFT       28

#define JAL_SER_PKT_LEN_L_ADDR       (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_PKT_LEN_L_MASK       0x000003E0
#define JAL_SER_PKT_LEN_L_SHFT       5

#define JAL_SER_ADR_LEN_ADDR       (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_ADR_LEN_MASK       0x0000001F
#define JAL_SER_ADR_LEN_SHFT       0
#endif /* if MBB */

#define JAL_SER_BUSY_ADDR       (0x00000060*2 + JAL_BASE_ADDR)
#define JAL_SER_BUSY_MASK       0x80000000
#define JAL_SER_BUSY_SHFT       31

#define JAL_SER_TIME_ADDR       (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_TIME_MASK       0x000000FF
#define JAL_SER_TIME_SHFT       0

#define JAL_SER_COMBINE_ADDR    (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_COMBINE_MASK    0x00000700
#define JAL_SER_COMBINE_SHFT    8

#define JAL_SER_MASK_ADDR       (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_MASK_MASK       0x000F0000
#define JAL_SER_MASK_SHFT       16

#define JAL_SER_NOW_ADDR        (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_NOW_MASK        0x00100000
#define JAL_SER_NOW_SHFT        20

#define JAL_SER_SEQ_ADDR        (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_SEQ_MASK        0x00200000
#define JAL_SER_SEQ_SHFT        21

#define JAL_SER_MAP_SEL_ADDR        (0x00000064*2 + JAL_BASE_ADDR)
#define JAL_SER_MAP_SEL_MASK        0x00800000
#define JAL_SER_MAP_SEL_SHFT        23

#define JAL_SER_READ_DATA_ADDR  (0x0000006c*2 + JAL_BASE_ADDR)
#define JAL_SER_READ_DATA_MASK  0xFFFFFFFF
#define JAL_SER_READ_DATA_SHFT  0

#define JAL_SER_DATA0_ADDR      (0x00000070*2 + JAL_BASE_ADDR)
#define JAL_SER_DATA0_MASK      0xFFFFFFFF
#define JAL_SER_DATA0_SHFT      0

#define JAL_SER_DATA1_ADDR      (0x00000074*2 + JAL_BASE_ADDR)
#define JAL_SER_DATA1_MASK      0xFFFFFFFF
#define JAL_SER_DATA1_SHFT      0

#define JAL_SER_DATA2_ADDR      (0x00000078*2 + JAL_BASE_ADDR)
#define JAL_SER_DATA2_MASK      0xFFFFFFFF
#define JAL_SER_DATA2_SHFT      0

#define JAL_SER_DATA3_ADDR      (0x0000007C*2 + JAL_BASE_ADDR)
#define JAL_SER_DATA3_MASK      0xFFFFFFFF
#define JAL_SER_DATA3_SHFT      0

#define JAL_SER0_WRITE_CLR_ADDR       (0x00000028*2 + JAL_BASE_ADDR)
#define JAL_SER0_WRITE_CLR_MASK       0x08000000
#define JAL_SER0_WRITE_CLR_SHFT       27

/****************************************************************************
*
*  Define the bit positions for the Serial Transceiver Interface Registers
*
*****************************************************************************/
#define JAL_STB_CFG_ADDR        (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_STB_CFG_MASK        0x7FFFFFFF
#define JAL_STB_CFG_SHFT        0

#define JAL_STB_BUSY_ADDR       (0x00000080*2 + JAL_BASE_ADDR)
#define JAL_STB_BUSY_MASK       0x80000000
#define JAL_STB_BUSY_SHFT       31

#define JAL_STB_DATA0_ADDR      (0x00000084*2 + JAL_BASE_ADDR)
#define JAL_STB_DATA0_MASK      0xFFFFFFFF
#define JAL_STB_DATA0_SHFT      0

/* receive volume control */
/****************************************************************************
*
*  Define the bit positions for the Receive Volume control Registers
*
*****************************************************************************/
#define JAL_SCO_VOL_ATT_ADDR     (0x0000009C*2 + JAL_BASE_ADDR)
#define JAL_SCO_VOL_ATT_MASK     0x00000007
#define JAL_SCO_VOL_ATT_SHFT     0

#define JAL_PF3_BYPASS_ADDR      (0x0000009C*2 + JAL_BASE_ADDR)
#define JAL_PF3_BYPASS_MASK      0x00000080
#define JAL_PF3_BYPASS_SHFT      7

/*******************************************************************
 *
 *     Define the bit positions for the auxilliary timer
 *     registers
 *
 *******************************************************************/
#define JAL_AUX_TIMER_ADDR     (0x000000A0*2 + JAL_BASE_ADDR)
#define JAL_AUX_TIMER_MASK     0x00003FFF
#define JAL_AUX_TIMER_SHFT     0


/*******************************************************************
*
*      Define the bit positions for the rx_delay and tx_delay
*      control registers
*
*******************************************************************/
#define JAL_RX_DELAY_ADDR      (0x000000b0*2 + JAL_BASE_ADDR)
#define JAL_RX_DELAY_MASK      0x0000007f
#define JAL_RX_DELAY_SHFT      0

#define JAL_TX_DELAY_ADDR      (0x000000b0*2 + JAL_BASE_ADDR)
#define JAL_TX_DELAY_MASK      0x00000f00
#define JAL_TX_DELAY_SHFT      8

/*******************************************************************
*
*      Define the bit positions for the enc_key_len and enc_key
*      (16 bytes at C0-CF) control registers
*
*******************************************************************/
#define JAL_ENC_KEY_LEN_ADDR      (0x000000b8*2 + JAL_BASE_ADDR)
#define JAL_ENC_KEY_LEN_MASK      0x0000000f
#define JAL_ENC_KEY_LEN_SHFT      0

#define JAL_ENC_KEY_ADDR          (0x000000C0*2 + JAL_BASE_ADDR)

/*******************************************************************
 *
 *   Define the bit positions for the hop selection engine
 *
 *******************************************************************/
#define JAL_SYS_ADDR           (0x000000D0*2 + JAL_BASE_ADDR)
#define JAL_SYS_MASK           0x00000001
#define JAL_SYS_SHFT           0

#define JAL_H_PAGE_ADDR        (0x000000D0*2 + JAL_BASE_ADDR)
#define JAL_H_PAGE_MASK        0x00000002
#define JAL_H_PAGE_SHFT        1

#define JAL_H_SLAVE_ADDR       (0x000000D0*2 + JAL_BASE_ADDR)
#define JAL_H_SLAVE_MASK       0x00000004
#define JAL_H_SLAVE_SHFT       2

#define JAL_PAGE_OFFSET_ADDR   (0x000000D0 *2 + JAL_BASE_ADDR)
#define JAL_PAGE_OFFSET_MASK   0x00000008
#define JAL_PAGE_OFFSET_SHFT   3

#define JAL_INDEX_MAP_ADDR     (0x000000D0 *2 + JAL_BASE_ADDR)
#define JAL_INDEX_MAP_MASK     0x00000010
#define JAL_INDEX_MAP_SHFT     4

#define JAL_CLK_DELTA_ADDR     (0x000000D0 *2 + JAL_BASE_ADDR)
#define JAL_CLK_DELTA_MASK     0x000000E0
#define JAL_CLK_DELTA_SHFT     5

#define JAL_N_COUNT_ADDR       (0x000000D0 *2 + JAL_BASE_ADDR)
#define JAL_N_COUNT_MASK       0x00001F00
#define JAL_N_COUNT_SHFT       8

#define JAL_SEL_ADDR           (0x000000D0 *2 + JAL_BASE_ADDR)
#define JAL_SEL_MASK           0x00006000
#define JAL_SEL_SHFT           13

#define JAL_SUP_BT_CLK_ADDR    (0x000000D0*2 + JAL_BASE_ADDR)
#define JAL_SUP_BT_CLK_MASK    0xFFFF8000
#define JAL_SUP_BT_CLK_SHFT    15

#define JAL_HOP_ADDR           (0x000000D4*2 + JAL_BASE_ADDR)
#define JAL_HOP_MASK           0x0000007F
#define JAL_HOP_SHFT           0


/*******************************************************************
 *
 *   Define the bit positions for the BT Clock Controls(P6 only)
 *   (the clock gating signals are redundant)
 *******************************************************************/
#define JAL_ADD_BT_CLK_RELATIVE_ADDR     (0x000000F0*2 + JAL_BASE_ADDR)
#define JAL_ADD_BT_CLK_RELATIVE_MASK     0000000001
#define JAL_ADD_BT_CLK_RELATIVE_SHFT     0

#define JAL_WRITE_ABSOLUTE_BT_CLK_ADDR     (0x000000F0*2 + JAL_BASE_ADDR)
#define JAL_WRITE_ABSOLUTE_BT_CLK_MASK     0x00000002
#define JAL_WRITE_ABSOLUTE_BT_CLK_SHFT     1

#define JAL_DELAYED_BT_CLK_UPDATE_ADDR     (0x000000F0*2 + JAL_BASE_ADDR)
#define JAL_DELAYED_BT_CLK_UPDATE_MASK     0x00000004
#define JAL_DELAYED_BT_CLK_UPDATE_SHFT     2

#define JAL_FREEZE_BT_CLK_ADDR     (0x000000F0*2 + JAL_BASE_ADDR)
#define JAL_FREEZE_BT_CLK_MASK     0x00000008
#define JAL_FREEZE_BT_CLK_SHFT     3

/*******************************************************************
 *
 *   Define the bit positions for the LC Revision Code Register
 *
 *******************************************************************/
#define JAL_MINOR_REVISION_ADDR    (0x000000F8*2 + JAL_BASE_ADDR)
#define JAL_MINOR_REVISION_MASK    0x000000FF
#define JAL_MINOR_REVISION_SHFT    0

#define JAL_MAJOR_REVISION_ADDR    (0x000000F8*2 + JAL_BASE_ADDR)
#define JAL_MAJOR_REVISION_MASK    0x0000FF00
#define JAL_MAJOR_REVISION_SHFT    8

/*******************************************************************
*
*      Define the bit positions for the reset controls
*
********************************************************************/
#define JAL_RST_CODE_ADDR     (0x000000FC*2 + JAL_BASE_ADDR)
#define JAL_RST_CODE_MASK     0xFF000000
#define JAL_RST_CODE_SHFT     24


/*******************************************************************
*
*      Define the bit positions for the EDR control
*
********************************************************************/

/*
 * EDR Control Register                  Address 104H
 */
#define JAL_EDR_CTRL_REG_ADDR                      (JAL_BASE_ADDR+0x104*2)

#define JAL_EDR_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_MASK     0x00000001
#define JAL_EDR_SHFT     0

#define JAL_EDR_MODE_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_MODE_MASK     0x00000002
#define JAL_EDR_MODE_SHFT     1

#define JAL_EDR_ESCO_RX_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_ESCO_RX_MASK     0x00000010
#define JAL_EDR_ESCO_RX_SHFT     4

#define JAL_EDR_TX_LEN_H_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_TX_LEN_H_MASK     0x01000000
#define JAL_EDR_TX_LEN_H_SHFT     24

#define JAL_EDR_RX_LEN_H_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_RX_LEN_H_MASK     0x02000000
#define JAL_EDR_RX_LEN_H_SHFT     25

#define JAL_EDR_TX_LEN_ESCO_H_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_TX_LEN_ESCO_H_MASK     0x30000000
#define JAL_EDR_TX_LEN_ESCO_H_SHFT     28

#define JAL_EDR_RX_LEN_ESCO_H_ADDR     (0x00000104*2 + JAL_BASE_ADDR)
#define JAL_EDR_RX_LEN_ESCO_H_MASK     0xc0000000
#define JAL_EDR_RX_LEN_ESCO_H_SHFT     30

#define JAL_EDR_CTRL_REG_JAL_EDR_MASK   JAL_EDR_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_MODE_MASK   JAL_EDR_MODE_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_ESCO_RX_MASK   JAL_EDR_ESCO_RX_MASK

#define JAL_EDR_CTRL_REG_JAL_EDR_TX_LEN_H_MASK  JAL_EDR_TX_LEN_H_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_RX_LEN_H_MASK  JAL_EDR_RX_LEN_H_MASK

#define JAL_EDR_CTRL_REG_JAL_EDR_TX_LEN_ESCO_H_MASK JAL_EDR_TX_LEN_ESCO_H_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_RX_LEN_ESCO_H_MASK JAL_EDR_RX_LEN_ESCO_H_MASK


/*
 * EDR Config Register                  Address 10cH
 */
#define JAL_EDR_CTRL_EXT_REG_ADDR                      (JAL_BASE_ADDR+0x108*2)

#define JAL_EDR_MBB_EN_ADDR     (0x00000108*2 + JAL_BASE_ADDR)
#define JAL_EDR_MBB_EN_MASK     0x80000000
#define JAL_EDR_MBB_EN_SHFT     31

#define JAL_EDR_CTRL_EXT_REG_JAL_EDR_MBB_EN_MASK  JAL_EDR_MBB_EN_MASK

/*
 * EDR Config Register                  Address 10cH
 */
#define JAL_EDR_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x10c*2)

#define JAL_EDR_2M_GTIME_ADDR     (0x0000010c*2 + JAL_BASE_ADDR)
#define JAL_EDR_2M_GTIME_MASK     0x00003F00
#define JAL_EDR_2M_GTIME_SHFT     8

#define JAL_EDR_3M_GTIME_ADDR     (0x0000010c*2 + JAL_BASE_ADDR)
#define JAL_EDR_3M_GTIME_MASK     0x003F0000
#define JAL_EDR_3M_GTIME_SHFT     16

#define JAL_EDR_CONFIG_REG_JAL_EDR_2M_GTIME_MASK   JAL_EDR_2M_GTIME_MASK
#define JAL_EDR_CONFIG_REG_JAL_EDR_3M_GTIME_MASK    JAL_EDR_3M_GTIME_MASK

/* sco/esco plc */
/*
 * PLC Config Register                  Address 11cH
 */
#define JAL_PLC_CONFIG_REG_ADDR         (JAL_BASE_ADDR+0x11c*2)

#define JAL_PLC_RX_START_ADDR           (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_RX_START_MASK           0x00000001
#define JAL_PLC_RX_START_SHFT           0

#define JAL_PLC_TX_START_ADDR           (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_START_MASK           0x00000002
#define JAL_PLC_TX_START_SHFT           1

#define JAL_PLC_TX_DATA_BLOCKED_ADDR    (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_DATA_BLOCKED_MASK    0x00000004
#define JAL_PLC_TX_DATA_BLOCKED_SHFT    2

#define JAL_PLC_RX_DATA_BLOCKED_ADDR    (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_RX_DATA_BLOCKED_MASK    0x00000008
#define JAL_PLC_RX_DATA_BLOCKED_SHFT    3

#define JAL_PLC_TX_BUFFER_RDY_ADDR      (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_BUFFER_RDY_MASK      0x00000010
#define JAL_PLC_TX_BUFFER_RDY_SHFT      4

#define JAL_PLC_TX_FINISH_ADDR          (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_FINISH_MASK          0x00000040
#define JAL_PLC_TX_FINISH_SHFT          6

#define JAL_PLC_RX_FINISH_ADDR          (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_RX_FINISH_MASK          0x00000080
#define JAL_PLC_RX_FINISH_SHFT          7

#define JAL_PLC_RX_LENGTH_ADDR          (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_RX_LENGTH_MASK          0x0000FF00
#define JAL_PLC_RX_LENGTH_SHFT          8

#define JAL_PLC_TX_THRESHOLD_ADDR       (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_THRESHOLD_MASK       0x00FF0000
#define JAL_PLC_TX_THRESHOLD_SHFT       16

#define JAL_PLC_TX_LENGTH_ADDR          (0x0000011c*2 + JAL_BASE_ADDR)
#define JAL_PLC_TX_LENGTH_MASK          0xFF000000
#define JAL_PLC_TX_LENGTH_SHFT          24

#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_START_MASK           JAL_PLC_RX_START_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_START_MASK           JAL_PLC_TX_START_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_DATA_BLOCKED_MASK    JAL_PLC_TX_DATA_BLOCKED_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_DATA_BLOCKED_MASK    JAL_PLC_RX_DATA_BLOCKED_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_BUFFER_RDY_MASK      JAL_PLC_TX_BUFFER_RDY_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_FINISH_MASK          JAL_PLC_TX_FINISH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_FINISH_MASK          JAL_PLC_RX_FINISH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_LENGTH_MASK          JAL_PLC_RX_LENGTH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_THRESHOLD_MASK       JAL_PLC_TX_THRESHOLD_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_LENGTH_MASK          JAL_PLC_TX_LENGTH_MASK

/*******************************************************************
*
*      Define the bit positions for the DMA control
*
********************************************************************/

/*
 * DMA config register                  Address 120H
 */
#define JAL_DMA_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x120*2)

#define JAL_DMA_TX_MODE_ADDR     (0x00000120*2 + JAL_BASE_ADDR)
#define JAL_DMA_TX_MODE_MASK     0x00000003
#define JAL_DMA_TX_MODE_SHFT     0

#define JAL_DMA_TEST_EN_ADDR     (0x00000120*2 + JAL_BASE_ADDR)
#define JAL_DMA_TEST_EN_MASK     0x00000010
#define JAL_DMA_TEST_EN_SHFT     4

#define JAL_DMA_RX_MODE_ADDR     (0x00000120*2 + JAL_BASE_ADDR)
#define JAL_DMA_RX_MODE_MASK     0x00000300
#define JAL_DMA_RX_MODE_SHFT     8

#define JAL_DMA_CONFIG_REG_JAL_DMA_TX_MODE_MASK JAL_DMA_TX_MODE_MASK
#define JAL_DMA_CONFIG_REG_JAL_DMA_TEST_EN_MASK JAL_DMA_TEST_EN_MASK
#define JAL_DMA_CONFIG_REG_JAL_DMA_RX_MODE_MASK JAL_DMA_RX_MODE_MASK

#define DMA_MODE_CPU    0
#define DMA_MODE_DMA    1
#define DMA_MODE_PIF    2

/*******************************************************************
*
*      Define the bit positions for the pre-preamble control
*
********************************************************************/

/*
 * Pre-preamble config register                  Address 128H
 */
#define JAL_PPREAMBLE_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x128*2)

#define JAL_PPREAMBLE_CNT_ADDR     (0x00000128*2 + JAL_BASE_ADDR)
#define JAL_PPREAMBLE_CNT_MASK     0x0000001f
#define JAL_PPREAMBLE_CNT_SHFT     0

#define JAL_PPREAMBLE_PWR_RAMPUP_ADDR     (0x00000128*2 + JAL_BASE_ADDR)
#define JAL_PPREAMBLE_PWR_RAMPUP_MASK     0x00000100
#define JAL_PPREAMBLE_PWR_RAMPUP_SHFT     8

#define JAL_PPREAMBLE_TOGGLE_ADDR     (0x00000128*2 + JAL_BASE_ADDR)
#define JAL_PPREAMBLE_TOGGLE_MASK     0x00000200
#define JAL_PPREAMBLE_TOGGLE_SHFT     9

#define JAL_PPREAMBLE_DATA_ADDR     (0x00000128*2 + JAL_BASE_ADDR)
#define JAL_PPREAMBLE_DATA_MASK     0x00000400
#define JAL_PPREAMBLE_DATA_SHFT     10

#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_CNT_MASK     JAL_PPREAMBLE_CNT_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_PWR_RAMPUP_MASK     JAL_PPREAMBLE_PWR_RAMPUP_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_TOGGLE_MASK     JAL_PPREAMBLE_TOGGLE_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_DATA_MASK     JAL_PPREAMBLE_DATA_MASK

/* pcm configuration */
/****************************************************************************
*
*  Define the bit positions for the PCM Registers
*
*****************************************************************************/
#define JAL_PCM_CONFIG_REG_ADDR         (JAL_BASE_ADDR+0x12c*2)

#define JAL_PCM_CLKINV_ADDR             (0x0000012c*2 + JAL_BASE_ADDR)
#define JAL_PCM_CLKINV_MASK             0x00000001
#define JAL_PCM_CLKINV_SHFT             0

#define JAL_PCM_DATAMODE_ADDR           (0x0000012c*2 + JAL_BASE_ADDR)
#define JAL_PCM_DATAMODE_MASK           0x00000002
#define JAL_PCM_DATAMODE_SHFT           1

#define JAL_PCM_SYNCLEN_ADDR            (0x0000012c*2 + JAL_BASE_ADDR)
#define JAL_PCM_SYNCLEN_MASK            0x00007F00
#define JAL_PCM_SYNCLEN_SHFT            8

#define JAL_PCM_CONFIG_REG_JAL_PCM_CLKINV_MASK      JAL_PCM_CLKINV_MASK
#define JAL_PCM_CONFIG_REG_JAL_PCM_DATAMODE_MASK    JAL_PCM_DATAMODE_MASK
#define JAL_PCM_CONFIG_REG_JAL_PCM_SYNCLEN_MASK     JAL_PCM_SYNCLEN_MASK


/*******************************************************************
*
*      debug probe
*
********************************************************************/

/*
 * debug probe register                  Address 130H
 */
#define JAL_DBG_PROBE_REG_ADDR                      (JAL_BASE_ADDR+0x130*2)

//YC 20090512 Timing_Modification
#define JAL_DBG_PROBE_16BITS_ADDR             (0x00000130*2 + JAL_BASE_ADDR)
#define JAL_DBG_PROBE_16BITS_MASK             0x0000ffff
#define JAL_DBG_PROBE_16BITS_SHFT             0

#define JAL_DBG_PROBE_SEL_ADDR             (0x00000130*2 + JAL_BASE_ADDR)
#define JAL_DBG_PROBE_SEL_MASK             0xff000000
#define JAL_DBG_PROBE_SEL_SHFT             24

//YC 20090512 Timing_Modification
#define JAL_DBG_PROBE_REG_JAL_DBG_PROBE_16BITS_MASK             JAL_DBG_PROBE_16BITS_MASK
#define JAL_DBG_PROBE_REG_JAL_DBG_PROBE_SEL_MASK             JAL_DBG_PROBE_SEL_MASK


/*******************************************************************
*
*      EDR config extension
*
********************************************************************/

/*
 * edr config extension register                  Address 148H
 */
#define JAL_EDR_CONFIG_EX_REG_ADDR                      (JAL_BASE_ADDR+0x148*2)

#define JAL_TSM_FINISH_CNT_ADDR     (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_TSM_FINISH_CNT_MASK     0x0000001f
#define JAL_TSM_FINISH_CNT_SHFT     0

/* manual cvsd */
#define JAL_CVSD_RETXRX_ON_ADDR     (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_ON_MASK     0x00000100
#define JAL_CVSD_RETXRX_ON_SHFT     8

#define JAL_CVSD_RETXRX_COMMIT_TX_ADDR      (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_COMMIT_TX_MASK      0x00000200
#define JAL_CVSD_RETXRX_COMMIT_TX_SHFT      9

#define JAL_CVSD_RETXRX_RESET_ADDR          (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_RESET_MASK          0x00000400
#define JAL_CVSD_RETXRX_RESET_SHFT          10

#define JAL_CVSD_RETXRX_COMMIT_RX_ADDR      (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_COMMIT_RX_MASK      0x00000800
#define JAL_CVSD_RETXRX_COMMIT_RX_SHFT      11

#define JAL_TSM_GUARDTIME_GFSK_OFF_ADDR     (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_TSM_GUARDTIME_GFSK_OFF_MASK     0x00001000
#define JAL_TSM_GUARDTIME_GFSK_OFF_SHFT     12

#define JAL_CVSD_TX_GAIN_ADDR               (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_TX_GAIN_MASK               0x00004000
#define JAL_CVSD_TX_GAIN_SHFT               14

#define JAL_CVSD_RX_GAIN_ADDR               (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_CVSD_RX_GAIN_MASK               0x00008000
#define JAL_CVSD_RX_GAIN_SHFT               15

#define JAL_GFSK_PADDING_CNT_ADDR     (0x00000148*2 + JAL_BASE_ADDR)
#define JAL_GFSK_PADDING_CNT_MASK     0x001f0000
#define JAL_GFSK_PADDING_CNT_SHFT     16

#define JAL_EDR_CONFIG_EX_REG_JAL_TSM_FINISH_CNT_MASK             JAL_TSM_FINISH_CNT_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_ON_MASK             JAL_CVSD_RETXRX_ON_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_COMMIT_TX_MASK      JAL_CVSD_RETXRX_COMMIT_TX_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_RESET_MASK          JAL_CVSD_RETXRX_RESET_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_COMMIT_RX_MASK      JAL_CVSD_RETXRX_COMMIT_RX_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_TSM_GUARDTIME_GFSK_OFF_MASK     JAL_TSM_GUARDTIME_GFSK_OFF_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_TX_GAIN_MASK               JAL_CVSD_TX_GAIN_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RX_GAIN_MASK               JAL_CVSD_RX_GAIN_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_GFSK_PADDING_CNT_MASK           JAL_GFSK_PADDING_CNT_MASK


/****************************************************************
*
*  Define the Transmit and Receive Registers
*
****************************************************************/
#define JAL_TX_ACL_BUF_ADDR   (0x0000200*2 + JAL_BASE_ADDR)
#define JAL_RX_ACL_BUF_ADDR   (0x0000700*2 + JAL_BASE_ADDR)
#define JAL_ACL_BUF_LEN   1024 /* ethan. extend acl buffer size from 360 to 1024 */

#define JAL_TX_ACL_BUF_END JAL_TX_ACL_BUF_ADDR + JAL_ACL_BUF_LEN
#define JAL_RX_ACL_BUF_END JAL_RX_ACL_BUF_ADDR + JAL_ACL_BUF_LEN

/****************************************************************
 *  Define additional constants for hardware
 ****************************************************************/
#define  JAL_MAX_POSITION_ERROR     10
#define  JAL_MAX_PACKET_LENGTH      341
#define  JAL_HW_REGISTER_LENGTH     (RX_ACL_BUF_ADDR+ACL_BUF_LEN)

/****************************************************************
*
*  Define the addresses of the main registers and associated
*  fields to allow local caching of registers and checking of
*  field assignments to take place
*  To use a local copy of a register
*  1. Give it a unique meaningful name REGISTER_XXX.
*  2. #define REGISTER_XXX_FIELD FIELD for each FIELD that will be
*     used with this register
*  3
*
****************************************************************/
/*
 * BD_ADDR Register        Low/High Address 00H/04H
 */
#define JAL_COM_CTRL_BD_ADDR_LO_REG_ADDR             (JAL_BASE_ADDR+2*0x00)
#define JAL_COM_CTRL_BD_ADDR_HI_REG_ADDR             (JAL_BASE_ADDR+2*0x04)

/*
 * Clock Registers         BT_CLK[_OFFSET]  18H/ NATIVE_CLK 1CH
 */
#define JAL_COM_CTRL_BT_CLK_READ_REG_ADDR           (JAL_BASE_ADDR+2*0x18)
#define JAL_COM_CTRL_BT_CLK_OFFSET_WRITE_REG_ADDR   (JAL_BASE_ADDR+2*0x18)
#define JAL_COM_CTRL_NATIVE_CLK_REG_ADDR            (JAL_BASE_ADDR+2*0x1C)

/*
 * Common Control Syncword Low/High Address 08H/12H
 */
#define JAL_COM_CTRL_SYNC_LO_REG_ADDR             (JAL_BASE_ADDR+2*0x08)
#define JAL_COM_CTRL_SYNC_HI_REG_ADDR             (JAL_BASE_ADDR+2*0x0C)

/*
 * Common Control General Purpose Register 1  Address 20H
 */
#define JAL_COM_CTRL_GP1_REG_ADDR                 (JAL_BASE_ADDR+2*0x20)

#define JAL_COM_CTRL_GP1_REG_JAL_PAGE_MASK        JAL_PAGE_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SLAVE_MASK       JAL_SLAVE_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_USE_LF_MASK      JAL_USE_LF_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_ENCRYPT_MASK     JAL_ENCRYPT_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_AM_ADDR_MASK     JAL_AM_ADDR_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG_MASK    JAL_SCO_CFG_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG0_MASK   JAL_SCO_CFG0_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG1_MASK   JAL_SCO_CFG1_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG2_MASK   JAL_SCO_CFG2_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_SCO_FIFO_MASK   JAL_SCO_FIFO_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_VCI_CLK_SEL_MASK   JAL_VCI_CLK_SEL_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_CRC_INIT_MASK    JAL_CRC_INIT_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_CLK1M_DIR_MASK JAL_CLK1M_DIR_MASK

/*
 * Common Control General Purpose Register 2  Address 24H
 */
#define JAL_COM_CTRL_GP2_REG_ADDR                      (JAL_BASE_ADDR+2*0x24)

/*
 * All whitening registers grouped in one u_int32 control word
 */
#define JAL_COM_CTRL_GP2_REG_JAL_WHITEN_MASK          JAL_WHITEN_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_INIT_MASK        JAL_DWH_INIT_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH2_INIT_MASK       JAL_DWH2_INIT_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_BY_BT_CLK_MASK   JAL_DWH_BY_BT_CLK_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_ALL_REG_MASK     JAL_DWH_ALL_REG_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_VCI_CLK_SEL_MAP_MASK JAL_VCI_CLK_SEL_MAP_MASK

/*
 * Common Control Interrupt Register          Address 28H
 */
#define JAL_COM_CTRL_IRQ_REG_ADDR                     (JAL_BASE_ADDR+2*0x28)

#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_RX_HDR_INTR_MSK_MASK   JAL_PKD_RX_HDR_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_INTR_MSK_MASK          JAL_PKD_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKA_INTR_MSK_MASK          JAL_PKA_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM_INTR_MSK_MASK          JAL_TIM_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM0_INTR_MSK_MASK         JAL_TIM0_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM1_INTR_MSK_MASK         JAL_TIM1_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM2_INTR_MSK_MASK         JAL_TIM2_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM3_INTR_MSK_MASK         JAL_TIM3_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_NO_PKT_RCVD_INTR_MSK_MASK  JAL_NO_PKT_RCVD_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SYNC_DET_INTR_MSK_MASK     JAL_SYNC_DET_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_AUX_TIM_INTR_MSK_MASK       JAL_AUX_TIM_INTR_MSK_MASK

#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_RX_HDR_INTR_CLR_MASK    JAL_PKD_RX_HDR_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_INTR_CLR_MASK           JAL_PKD_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKA_INTR_CLR_MASK           JAL_PKA_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM0_INTR_CLR_MASK          JAL_TIM0_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM1_INTR_CLR_MASK          JAL_TIM1_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM2_INTR_CLR_MASK          JAL_TIM2_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM3_INTR_CLR_MASK          JAL_TIM3_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_NO_PKT_RCVD_INTR_CLR_MASK   JAL_NO_PKT_RCVD_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SYNC_DET_INTR_CLR_MASK      JAL_SYNC_DET_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_AUX_TIM_INTR_CLR_MASK       JAL_AUX_TIM_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SER0_WRITE_CLR_MASK         JAL_SER0_WRITE_CLR_MASK

/*
 * Common Control Interrupt Register          Address 2CH
 */
#define JAL_COM_STAT_IRQ_REG_ADDR                     (JAL_BASE_ADDR+2*0x2C)

#define JAL_COM_STAT_IRQ_REG_JAL_PKD_RX_HDR_INTR_MASK      JAL_PKD_RX_HDR_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_PKD_INTR_MASK             JAL_PKD_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_PKA_INTR_MASK             JAL_PKA_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM0_INTR_MASK            JAL_TIM0_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM1_INTR_MASK            JAL_TIM1_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM2_INTR_MASK            JAL_TIM2_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM3_INTR_MASK            JAL_TIM3_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_NO_PKT_RCVD_INTR_MASK     JAL_NO_PKT_RCVD_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_SYNC_DET_INTR_MASK        JAL_SYNC_DET_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_SLEEP_STATUS_MASK         JAL_SLEEP_STATUS_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_AUX_TIM_INTR_MASK         JAL_AUX_TIM_INTR_MASK


/*
 * Transmit Control Register                  Address 30H
 */
#define JAL_TX_CTRL_REG_ADDR                      (JAL_BASE_ADDR+2*0x30)

#define JAL_TX_CTRL_REG_JAL_TX_LEN_MASK            JAL_TX_LEN_MASK
#define JAL_TX_CTRL_REG_JAL_TX_TYPE_MASK           JAL_TX_TYPE_MASK

#define JAL_TX_CTRL_REG_JAL_TX_FLOW_MASK           JAL_TX_FLOW_MASK
#define JAL_TX_CTRL_REG_JAL_TX_ARQN_MASK           JAL_TX_ARQN_MASK
#define JAL_TX_CTRL_REG_JAL_TX_SEQN_MASK           JAL_TX_SEQN_MASK

#define JAL_TX_CTRL_REG_JAL_TX_BUF_MASK            JAL_TX_BUF_MASK

#define JAL_TX_CTRL_REG_JAL_TX_MODE_MASK           JAL_TX_MODE_MASK
#define JAL_TX_CTRL_REG_JAL_TX_L_CH_MASK           JAL_TX_L_CH_MASK
#define JAL_TX_CTRL_REG_JAL_TX_P_FLOW_MASK         JAL_TX_P_FLOW_MASK

/*
 * eSCO Control Register                    Address 34H
 */

#define JAL_ESCO_CTRL_REG_ADDR       (JAL_BASE_ADDR+2*0x34)

#define JAL_ESCO_CTRL_REG_JAL_ESCO_TX_LEN_MASK      JAL_ESCO_TX_LEN_MASK
#define JAL_ESCO_CTRL_REG_JAL_ESCO_RX_LEN_MASK      JAL_ESCO_RX_LEN_MASK
#define JAL_ESCO_CTRL_REG_JAL_ESCO_LT_ADDR_MASK      JAL_ESCO_LT_ADDR_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_ROUTE_MASK     JAL_SCO_ROUTE_MASK
/* hw conversion codec */
#define JAL_ESCO_CTRL_REG_JAL_NEW_AULAW_TBL_MASK     JAL_NEW_AULAW_TBL_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_TX_ALIGN_MSB_MASK  JAL_SCO_TX_ALIGN_MSB_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_RX_ALIGN_MSB_MASK  JAL_SCO_RX_ALIGN_MSB_MASK

/*
 * Transmit Status Register                   Address 40H
 */
#define JAL_TX_STATUS_REG_ADDR                    (JAL_BASE_ADDR+2*0x40)

/*
 * Receive Control Register                   Address 48H
 */
#define JAL_RX_CTRL_REG_ADDR                      (JAL_BASE_ADDR+2*0x48)

#define JAL_RX_CTRL_REG_JAL_RX_MODE_MASK         JAL_RX_MODE_MASK
#define JAL_RX_CTRL_REG_JAL_SYNC_ERR_MASK        JAL_SYNC_ERR_MASK
#define JAL_RX_CTRL_REG_JAL_ABORT_ON_WRONG_AM_ADDR_MASK     JAL_ABORT_ON_WRONG_AM_ADDR_MASK
#define JAL_RX_CTRL_REG_JAL_RX_BUF_MASK          JAL_RX_BUF_MASK
#define JAL_RX_CTRL_REG_JAL_ERR_SEL_MASK         JAL_ERR_SEL_MASK
#define JAL_RX_CTRL_REG_JAL_WIN_EXT_MASK         JAL_WIN_EXT_MASK

/*
 * Receive Status General Purpose Register    Address 50H
 */
#define JAL_RX_STATUS_GP_REG_ADDR                 (JAL_BASE_ADDR+2*0x50)

#define JAL_RX_STATUS_GP_REG_JAL_RX_LEN_MASK      JAL_RX_LEN_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_TYPE_MASK     JAL_RX_TYPE_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_FLOW_MASK     JAL_RX_FLOW_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_ARQN_MASK     JAL_RX_ARQN_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_SEQN_MASK     JAL_RX_SEQN_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_AM_ADDR_MASK  JAL_RX_AM_ADDR_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_L_CH_MASK     JAL_RX_L_CH_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_P_FLOW_MASK   JAL_RX_P_FLOW_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_PKT_MASK      JAL_RX_PKT_MASK
#define JAL_RX_STATUS_GP_REG_JAL_HEC_ERR_MASK     JAL_HEC_ERR_MASK
#define JAL_RX_STATUS_GP_REG_JAL_CRC_ERR_MASK     JAL_CRC_ERR_MASK
//YC 20081201 Added
#define JAL_RX_STATUS_GP_REG_JAL_RX_EDR_SYNC_ERR_MASK     JAL_RX_EDR_SYNC_ERR_MASK

#define JAL_RX_STATUS_GP_REG_JAL_AM_ADDR_ABORT_MASK     JAL_AM_ADDR_ABORT_MASK


/*
 * Receive Status SCO Register                Address 54H
 */
#define JAL_RX_STATUS_SCO_REG_ADDR                (JAL_BASE_ADDR+2*0x54)

/*
 * Encryption Key Length Register             Address B8H
 */
#define JAL_ENC_KEY_LENGTH_REG_ADDR               (JAL_BASE_ADDR+2*0xB8)

/*
 * Parallel Interface Adapter Register        Address A4H
 */
#define JAL_PIA_DATA_REG_ADDR                     (JAL_BASE_ADDR+2*0xA4)

#define JAL_PIA_DATA_REG_JAL_P_DATA_0_MASK     JAL_P_DATA_0_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_1_MASK     JAL_P_DATA_1_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_2_MASK     JAL_P_DATA_2_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_3_MASK     JAL_P_DATA_3_MASK


/*
 * Serial Interface Adapter Register          Address 60H
 */
#define JAL_SER_CFG_REG_ADDR                     (JAL_BASE_ADDR+2*0x60)

#define JAL_SER_CFG_REG_JAL_SER_CFG_MASK         JAL_SER_CFG_MASK
#define JAL_SER_CFG_REG_JAL_SER_BUSY_MASK        JAL_SER_BUSY_MASK

#if MBB
#define JAL_SER_CFG_REG_JAL_SER_WRITE_MASK        JAL_SER_WRITE_MASK
#define JAL_SER_CFG_REG_JAL_SER_PKT_LEN_H_MASK        JAL_SER_PKT_LEN_H_MASK
#define JAL_SER_CFG_REG_JAL_SER_PKT_LEN_L_MASK        JAL_SER_PKT_LEN_L_MASK
#define JAL_SER_CFG_REG_JAL_SER_ADR_LEN_MASK        JAL_SER_ADR_LEN_MASK
#endif /* #if MBB */

#define JAL_SER_CTRL_REG_ADDR                    (JAL_BASE_ADDR+2*0x64)

#define JAL_SER_CTRL_REG_JAL_SER_TIME_MASK       JAL_SER_TIME_MASK
#define JAL_SER_CTRL_REG_JAL_SER_COMBINE_MASK    JAL_SER_COMBINE_MASK
#define JAL_SER_CTRL_REG_JAL_SER_MASK_MASK       JAL_SER_MASK_MASK
#define JAL_SER_CTRL_REG_JAL_SER_NOW_MASK        JAL_SER_NOW_MASK
#define JAL_SER_CTRL_REG_JAL_SER_SEQ_MASK        JAL_SER_SEQ_MASK
#define JAL_SER_CTRL_REG_JAL_SER_MAP_SEL_MASK        JAL_SER_MAP_SEL_MASK


#define JAL_SER_DATA0_REG_ADDR                  (JAL_BASE_ADDR+2*0x70)
#define JAL_SER_DATA1_REG_ADDR                  (JAL_BASE_ADDR+2*0x74)
#define JAL_SER_DATA2_REG_ADDR                  (JAL_BASE_ADDR+2*0x78)
#define JAL_SER_DATA3_REG_ADDR                  (JAL_BASE_ADDR+2*0x7C)


/*
 * Definitions for the Enhanced SER block
 */
#define JAL_SER_ESER_CTRL_REG_ADDR                    (JAL_BASE_ADDR+2*0x64)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_COMBINE_MASK    (0x00070000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MASK_MASK       (0x0000FFFF)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_NOW_MASK        (0x00100000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_SEQ_MASK        (0x00200000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_DOUBLE_MASK     (0x00400000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_SEL_MASK    (0x00800000)

#define JAL_SER_ESER_CTRL_REG_JAL_SER_COMBINE_BIT_OFFSET    16
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MASK_BIT_OFFSET        0
#define JAL_SER_ESER_CTRL_REG_JAL_SER_NOW_BIT_OFFSET        20
#define JAL_SER_ESER_CTRL_REG_JAL_SER_SEQ_BIT_OFFSET        21
#define JAL_SER_ESER_CTRL_REG_JAL_SER_DOUBLE_BIT_OFFSET     22
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_SEL_BIT_OFFSET    23
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_BUSY_BIT_OFFSET   31



#define JAL_SER_ESER_TIME_REG_ADDR         (JAL_BASE_ADDR+2*0x68)

#define JAL_SER_ESER_TIME_0_BIT_OFFSET     0
#define JAL_SER_ESER_TIME_1_BIT_OFFSET     4
#define JAL_SER_ESER_TIME_2_BIT_OFFSET     8
#define JAL_SER_ESER_TIME_3_BIT_OFFSET     12

#define JAL_SER_ESER_TIME_0_ADDR     JAL_ADDR_CONVERT(JAL_BASE_ADDR + 0x68)
#define JAL_SER_ESER_TIME_0_MASK     0x000000ff
#define JAL_SER_ESER_TIME_0_SHFT     0

#define JAL_SER_ESER_TIME_1_ADDR     JAL_ADDR_CONVERT(JAL_BASE_ADDR + 0x68)
#define JAL_SER_ESER_TIME_1_MASK     0x0000ff00
#define JAL_SER_ESER_TIME_1_SHFT     8

#define JAL_SER_ESER_TIME_2_ADDR     JAL_ADDR_CONVERT(JAL_BASE_ADDR + 0x68)
#define JAL_SER_ESER_TIME_2_MASK     0x00ff0000
#define JAL_SER_ESER_TIME_2_SHFT     16

#define JAL_SER_ESER_TIME_3_ADDR     JAL_ADDR_CONVERT(JAL_BASE_ADDR + 0x68)
#define JAL_SER_ESER_TIME_3_MASK     0xff000000
#define JAL_SER_ESER_TIME_3_SHFT     24

#define JAL_SER_ESER_TIME_REG_JAL_SER_ESER_TIME_0_MASK  JAL_SER_ESER_TIME_0_MASK
#define JAL_SER_ESER_TIME_REG_JAL_SER_ESER_TIME_1_MASK  JAL_SER_ESER_TIME_1_MASK
#define JAL_SER_ESER_TIME_REG_JAL_SER_ESER_TIME_2_MASK  JAL_SER_ESER_TIME_2_MASK
#define JAL_SER_ESER_TIME_REG_JAL_SER_ESER_TIME_3_MASK  JAL_SER_ESER_TIME_3_MASK

/* receive volume control */
/*
 * Receive Volume control Register    Address 9CH
 */
#define JAL_RECV_VOLUME_CTRL_REG_ADDR                   (JAL_BASE_ADDR+2*0x9C)

#define JAL_RECV_VOLUME_CTRL_REG_JAL_SCO_VOL_ATT_MASK   JAL_SCO_VOL_ATT_MASK
#define JAL_RECV_VOLUME_CTRL_REG_JAL_PF3_BYPASS_MASK    JAL_PF3_BYPASS_MASK

#define JAL_SER_ESER_DATA_ADDR                   (JAL_BASE_ADDR+0x600)
#define JAL_SER_ESER_DATA_0_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR)
#define JAL_SER_ESER_DATA_1_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*1)
#define JAL_SER_ESER_DATA_2_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*2)
#define JAL_SER_ESER_DATA_3_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*3)
#define JAL_SER_ESER_DATA_4_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*4)
#define JAL_SER_ESER_DATA_5_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*5)
#define JAL_SER_ESER_DATA_6_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*6)
#define JAL_SER_ESER_DATA_7_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*7)
#define JAL_SER_ESER_DATA_8_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*8)
#define JAL_SER_ESER_DATA_9_ADDR                 JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*9)
#define JAL_SER_ESER_DATA_10_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*10)
#define JAL_SER_ESER_DATA_11_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*11)
#define JAL_SER_ESER_DATA_12_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*12)
#define JAL_SER_ESER_DATA_13_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*13)
#define JAL_SER_ESER_DATA_14_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*14)
#define JAL_SER_ESER_DATA_15_ADDR                JAL_ADDR_CONVERT(JAL_SER_ESER_DATA_ADDR+4*15)




/*
 * Parallel Interface Adapter Register        Address A8H
 */
#define JAL_PIA_CTRL_REG_ADDR                   (JAL_BASE_ADDR+2*0xA8)

#define JAL_PIA_CTRL_REG_JAL_P_SETUP_MASK       JAL_P_SETUP_MASK
#define JAL_PIA_CTRL_REG_JAL_P_MASK_MASK        JAL_P_MASK_MASK
#define JAL_PIA_CTRL_REG_JAL_P_NOW_MASK         JAL_P_NOW_MASK
#define JAL_PIA_CTRL_REG_JAL_P_SEQ_MASK         JAL_P_SEQ_MASK
#define JAL_PIA_CTRL_REG_JAL_P_DATA_DIR_MASK    JAL_P_DATA_DIR_MASK
#define JAL_PIA_CTRL_REG_JAL_P_RDATA_MASK       JAL_P_RDATA_MASK


/*
 * Hop Selection Control Register             Address D0H (temp 9CH)
 *                                            see register definitions
 */
#define JAL_HSE_CONTROL_REG_ADDR                 (JAL_BASE_ADDR+2*0xD0)

#define JAL_HSE_CONTROL_REG_JAL_SYS_MASK          JAL_SYS_MASK
#define JAL_HSE_CONTROL_REG_JAL_H_PAGE_MASK       JAL_H_PAGE_MASK
#define JAL_HSE_CONTROL_REG_JAL_H_SLAVE_MASK      JAL_H_SLAVE_MASK
#define JAL_HSE_CONTROL_REG_JAL_PAGE_OFFSET_MASK  JAL_PAGE_OFFSET_MASK
#define JAL_HSE_CONTROL_REG_JAL_INDEX_MAP_MASK    JAL_INDEX_MAP_MASK
#define JAL_HSE_CONTROL_REG_JAL_CLK_DELTA_MASK    JAL_CLK_DELTA_MASK
#define JAL_HSE_CONTROL_REG_JAL_N_COUNT_MASK      JAL_N_COUNT_MASK
#define JAL_HSE_CONTROL_REG_JAL_SEL_MASK          JAL_SEL_MASK
#define JAL_HSE_CONTROL_REG_JAL_SUP_BT_CLK_MASK   JAL_SUP_BT_CLK_MASK

/*
 * Hop Selection Control Register             Address D4H
 */
#define JAL_HSE_HOP_REG_ADDR                      (JAL_BASE_ADDR+2*0xD4)
#define JAL_HSE_HOP_REG_JAL_HOP_MASK              JAL_HOP_MASK

#if MBB
/*
 * MBB
 */
#define JAL_MBB_ENABLE_REG_ADDR             (JAL_BASE_ADDR+2*0x108)
#endif /* #if MBB */
/*
 * Hop Selection Registers V1.2               Address D0-DC
 * No fields, since there is only a single one in each register.
 *  Addr       b7     b6     b5     b4     b3     b2     b1     b0
 *  CONTROL +------+------+------+------+------+------+------+------+
 *  D0      |    HSE_BT_CLK[27:0]                                   |
 *          +------+------+------+------+------+------+------+------+
 *  D4      |    HSE_UAP_LAP[23:0]                                  |
 *          +------+------+------+------+------+------+------+------+
 *  D8      |    HSE_SUM[23:0]                                      |
 *          +------+------+------+------+------+------+------+------+
 *  DC      |    HSE_RF_CHAN_INDEX[6:0]                             |
 *          +------+------+------+------+------+------+------+------+
 */
#define JAL_HSE_BT_CLK_REG_ADDR                   (JAL_BASE_ADDR+2*0xD0)
#define JAL_HSE_UAP_LAP_REG_ADDR                  (JAL_BASE_ADDR+2*0xD4)
#define JAL_HSE_SUM_REG_ADDR                      (JAL_BASE_ADDR+2*0xD8)
#define JAL_HSE_RF_CHAN_INDEX_REG_ADDR            (JAL_BASE_ADDR+2*0xDC)

#if (PRH_BS_CFG_SYS_SCO_REPEATER_SUPPORTED==1)
/*******************************************************************
 *
 *   Define the bit positions for the SCO Repeater Controls(Tama only)
 *   (NT clock phase offset is also adjustable when hit by RX packet)
 *******************************************************************/
#define JAL_SCO_REPEATER_BIT_ADDR     (0x000000F0*2 + JAL_BASE_ADDR)
#define JAL_SCO_REPEATER_BIT_MASK     0x000000010
#define JAL_SCO_REPEATER_BIT_SHFT     4
#endif // (PRH_BS_CFG_SYS_SCO_REPEATER_SUPPORTED==1)

#else // __HERCULES_AEON__
#define JAL_BD_ADDR_ADDR     (0x00000000 + JAL_BASE_ADDR)
#define JAL_BD_ADDR_MASK     0xFFFFFFFF
#define JAL_BD_ADDR_SHFT     0

#define JAL_UAP_LAP_ADDR     (0x00000000 + JAL_BASE_ADDR)
#define JAL_NAP_ADDR         (0x00000004 + JAL_BASE_ADDR)

#define JAL_SYNC_ADDR        (0x00000008 + JAL_BASE_ADDR)
#define JAL_SYNC_MASK        0xFFFFFFFF
#define JAL_SYNC_SHFT        0

#define JAL_SYNC2_ADDR       (0x0000000C + JAL_BASE_ADDR)
#define JAL_SYNC2_MASK       0xFFFFFFFF
#define JAL_SYNC2_SHFT       0

#define JAL_INTRASLOT_OFFSET_ADDR        (0x00000010 + JAL_BASE_ADDR)
#define JAL_INTRASLOT_OFFSET_MASK        0x000007FF
#define JAL_INTRASLOT_OFFSET_SHFT        0

#define JAL_BT_CLK_OFFSET_ADDR      (0x00000018 + JAL_BASE_ADDR)
#define JAL_BT_CLK_OFFSET_MASK      0x0FFFFFFF
#define JAL_BT_CLK_OFFSET_SHFT      0

#define JAL_NATIVE_CLK_ADDR  (0x0000001c + JAL_BASE_ADDR)
#define JAL_NATIVE_CLK_MASK  0x0FFFFFFF
#define JAL_NATIVE_CLK_SHFT  0

#define JAL_AM_ADDR_ADDR     (0x00000020 + JAL_BASE_ADDR)
#define JAL_AM_ADDR_MASK     0x00000007
#define JAL_AM_ADDR_SHFT     0

#define JAL_ENCRYPT_ADDR     (0x00000020 + JAL_BASE_ADDR)
#define JAL_ENCRYPT_MASK     0x00000018
#define JAL_ENCRYPT_SHFT     3

#define JAL_USE_LF_ADDR      (0x00000020 + JAL_BASE_ADDR)
#define JAL_USE_LF_MASK      0x00000020
#define JAL_USE_LF_SHFT      5

#define JAL_SLAVE_ADDR       (0x00000020 + JAL_BASE_ADDR)
#define JAL_SLAVE_MASK       0x00000040
#define JAL_SLAVE_SHFT       6

#define JAL_PAGE_ADDR        (0x00000020 + JAL_BASE_ADDR)
#define JAL_PAGE_MASK        0x00000080
#define JAL_PAGE_SHFT        7

#define JAL_SCO_CFG_ADDR   (0x00000020 + JAL_BASE_ADDR)
#define JAL_SCO_CFG_MASK   0x000FFF00
#define JAL_SCO_CFG_SHFT   8

#define JAL_SCO_CFG0_ADDR   (0x00000020 + JAL_BASE_ADDR)
#define JAL_SCO_CFG0_MASK   0x00000F00
#define JAL_SCO_CFG0_SHFT   8

#define JAL_SCO_CFG1_ADDR   (0x00000020 + JAL_BASE_ADDR)
#define JAL_SCO_CFG1_MASK   0x0000F000
#define JAL_SCO_CFG1_SHFT   12

#define JAL_SCO_CFG2_ADDR   (0x00000020 + JAL_BASE_ADDR)
#define JAL_SCO_CFG2_MASK   0x000F0000
#define JAL_SCO_CFG2_SHFT   16

#define JAL_SCO_FIFO_ADDR    (0x00000020 + JAL_BASE_ADDR)
#define JAL_SCO_FIFO_MASK    0x00300000
#define JAL_SCO_FIFO_SHFT    20

#define JAL_VCI_CLK_SEL_ADDR    (0x00000020 + JAL_BASE_ADDR)
#define JAL_VCI_CLK_SEL_MASK    0x00c00000
#define JAL_VCI_CLK_SEL_SHFT    22

#define JAL_CRC_INIT_ADDR    (0x00000020 + JAL_BASE_ADDR)
#define JAL_CRC_INIT_MASK    0xff000000
#define JAL_CRC_INIT_SHFT    24

#define JAL_LOOP_ADDR        (0x00000024 + JAL_BASE_ADDR)
#define JAL_LOOP_MASK        0x00000001
#define JAL_LOOP_SHFT        0

#define JAL_TEST_ECO_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_ECO_MASK    0x00000002
#define JAL_TEST_ECO_SHFT    1

#define JAL_ECO_ERR_ADDR     (0x00000024 + JAL_BASE_ADDR)
#define JAL_ECO_ERR_MASK     0x0000003C
#define JAL_ECO_ERR_SHFT     2

#define JAL_TEST_CRC_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_CRC_MASK    0x00000040
#define JAL_TEST_CRC_SHFT    6

#define JAL_TEST_HEC_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_HEC_MASK    0x00000080
#define JAL_TEST_HEC_SHFT    7

#define JAL_TEST_RADIO_ADDR  (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_RADIO_MASK  0x00000100
#define JAL_TEST_RADIO_SHFT  8

#define JAL_VCI_CLK_SEL_MAP_ADDR     (0x00000024 + JAL_BASE_ADDR)
#define JAL_VCI_CLK_SEL_MAP_MASK     0x00000200
#define JAL_VCI_CLK_SEL_MAP_SHFT     9

#define JAL_TEST_FORCE_NO_DDW_ADDR (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_FORCE_NO_DDW_MASK 0x00000400
#define JAL_TEST_FORCE_NO_DDW_SHFT 10

#define JAL_TEST_MSG_ADDR       (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_MSG_MASK       0x00000800
#define JAL_TEST_MSG_SHFT       11

#define JAL_TEST_TX_SHIFT_ADDR  (0x00000024 + JAL_BASE_ADDR)
#define JAL_TEST_TX_SHIFT_MASK  0x00007000
#define JAL_TEST_TX_SHIFT_SHFT  12

#define JAL_USE_HAB_CTRL_ADDR   (0x00000024 + JAL_BASE_ADDR)
#define JAL_USE_HAB_CTRL_MASK   0x00008000
#define JAL_USE_HAB_CTRL_SHFT   15

/*
 * Setup Full DWH register to allow fast clearance of all DWH registers
 */
#define JAL_DWH_ALL_REG_ADDR      (0x00000024 + JAL_BASE_ADDR)
#define JAL_DWH_ALL_REG_MASK      0xFFBF0000
#define JAL_DWH_ALL_REG_SHFT      16

#define JAL_DWH_INIT_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_DWH_INIT_MASK    0x003f0000
#define JAL_DWH_INIT_SHFT    16

/*
 * RGB 22/08/01 - new bit added for switching between codec types
 */
#define JAL_CODEC_TYPE_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_CODEC_TYPE_MASK    0x00400000
#define JAL_CODEC_TYPE_SHFT    22

#define JAL_DWH_BY_BT_CLK_ADDR    (0x00000024 + JAL_BASE_ADDR)
#define JAL_DWH_BY_BT_CLK_MASK    0x00800000
#define JAL_DWH_BY_BT_CLK_SHFT    23

#define JAL_DWH2_INIT_ADDR   (0x00000024 + JAL_BASE_ADDR)
#define JAL_DWH2_INIT_MASK   0x3f000000
#define JAL_DWH2_INIT_SHFT   24

#define JAL_WHITEN_ADDR      (0x00000024 + JAL_BASE_ADDR)
#define JAL_WHITEN_MASK      0x80000000
#define JAL_WHITEN_SHFT      31

/*
 * Interrupt related
 */
#define JAL_TIM_INTR_MSK_ADDR        (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_MSK_MASK        0x0000000f
#define JAL_TIM_INTR_MSK_SHFT        0

#define JAL_TIM0_INTR_MSK_ADDR       (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_MSK_MASK       0x00000001
#define JAL_TIM0_INTR_MSK_SHFT       0

#define JAL_TIM1_INTR_MSK_ADDR       (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_MSK_MASK       0x00000002
#define JAL_TIM1_INTR_MSK_SHFT       1

#define JAL_TIM2_INTR_MSK_ADDR       (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_MSK_MASK       0x00000004
#define JAL_TIM2_INTR_MSK_SHFT       2

#define JAL_TIM3_INTR_MSK_ADDR       (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_MSK_MASK       0x00000008
#define JAL_TIM3_INTR_MSK_SHFT       3

#define JAL_PKD_INTR_MSK_ADDR        (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKD_INTR_MSK_MASK        0x00000010
#define JAL_PKD_INTR_MSK_SHFT        4

#define JAL_AUX_TIM_INTR_MSK_ADDR    (0x00000028 + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_MSK_MASK    0x00000020
#define JAL_AUX_TIM_INTR_MSK_SHFT    5

#define JAL_PKA_INTR_MSK_ADDR        (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKA_INTR_MSK_MASK        0x00000040
#define JAL_PKA_INTR_MSK_SHFT        6

#define JAL_PKD_RX_HDR_INTR_MSK_ADDR (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_MSK_MASK 0x00000080
#define JAL_PKD_RX_HDR_INTR_MSK_SHFT 7

#define JAL_GIO_INTR_MSK0_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK0_MASK  0x00000300
#define JAL_GIO_INTR_MSK0_SHFT  8

#define JAL_GIO_INTR_MSK1_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK1_MASK  0x00000c00
#define JAL_GIO_INTR_MSK1_SHFT  10

#define JAL_GIO_INTR_MSK2_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK2_MASK  0x00001000 /* NO_PKD_INTR_MASK in this location CM(20Apr2000) 0x03000 */
#define JAL_GIO_INTR_MSK2_SHFT  12

#define JAL_GIO_INTR_MSK3_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_MSK3_MASK  0x0000c000
#define JAL_GIO_INTR_MSK3_SHFT  14

#if(PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1)

#define JAL_TIM_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_CLR_MASK   0x000f0000
#define JAL_TIM_INTR_CLR_SHFT   16

#define JAL_TIM0_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_CLR_MASK   0x00010000
#define JAL_TIM0_INTR_CLR_SHFT   16

#define JAL_TIM1_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_CLR_MASK   0x00020000
#define JAL_TIM1_INTR_CLR_SHFT   17

#define JAL_TIM2_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_CLR_MASK   0x00040000
#define JAL_TIM2_INTR_CLR_SHFT   18

#define JAL_TIM3_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_CLR_MASK   0x00080000
#define JAL_TIM3_INTR_CLR_SHFT   19

#else   /* (PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1) */

#define JAL_TIM_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM_INTR_CLR_MASK   0x00010000
#define JAL_TIM_INTR_CLR_SHFT   16

#define JAL_TIM0_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_CLR_MASK   0x00010000
#define JAL_TIM0_INTR_CLR_SHFT   16

#define JAL_TIM1_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_CLR_MASK   0x00010000
#define JAL_TIM1_INTR_CLR_SHFT   16

#define JAL_TIM2_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_CLR_MASK   0x00010000
#define JAL_TIM2_INTR_CLR_SHFT   16

#define JAL_TIM3_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_CLR_MASK   0x00010000
#define JAL_TIM3_INTR_CLR_SHFT   16

#endif  /* (PRH_BS_CFG_SYS_HW_INDIVIDUAL_TIM_INTR_CLR==1) */

#define JAL_PKD_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKD_INTR_CLR_MASK   0x00100000
#define JAL_PKD_INTR_CLR_SHFT   20

#define JAL_AUX_TIM_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_CLR_MASK   0x00200000
#define JAL_AUX_TIM_INTR_CLR_SHFT   21

#define JAL_PKA_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKA_INTR_CLR_MASK   0x00400000
#define JAL_PKA_INTR_CLR_SHFT   22

#define JAL_NO_PKT_RCVD_INTR_ADDR    (0x0000002C + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_SHFT    13
#define JAL_NO_PKT_RCVD_INTR_MASK    0x00002000

#define JAL_SYNC_DET_INTR_ADDR    (0x0000002C + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_SHFT    14
#define JAL_SYNC_DET_INTR_MASK    0x00004000

#define JAL_SLEEP_STATUS_ADDR    (0x0000002C + JAL_BASE_ADDR)
#define JAL_SLEEP_STATUS_SHFT    15
#define JAL_SLEEP_STATUS_MASK    0x00008000

#define JAL_NO_PKT_RCVD_INTR_MSK_ADDR (0x00000028 + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_MSK_SHFT 13
#define JAL_NO_PKT_RCVD_INTR_MSK_MASK 0x00002000

#define JAL_SYNC_DET_INTR_MSK_ADDR (0x00000028 + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_MSK_SHFT 14
#define JAL_SYNC_DET_INTR_MSK_MASK 0x00004000

#define JAL_NO_PKT_RCVD_INTR_CLR_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_NO_PKT_RCVD_INTR_CLR_SHFT  29
#define JAL_NO_PKT_RCVD_INTR_CLR_MASK  0x20000000

#define JAL_SYNC_DET_INTR_CLR_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_SYNC_DET_INTR_CLR_SHFT  30
#define JAL_SYNC_DET_INTR_CLR_MASK  0x40000000

#define JAL_VCI_SYNC_DIR_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_VCI_SYNC_DIR_SHFT  31
#define JAL_VCI_SYNC_DIR_MASK  0x80000000

#define JAL_PKD_RX_HDR_INTR_CLR_ADDR   (0x00000028 + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_CLR_MASK   0x00800000
#define JAL_PKD_RX_HDR_INTR_CLR_SHFT   23

#define JAL_GIO_INTR_CLR0_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR0_MASK  0x01000000
#define JAL_GIO_INTR_CLR0_SHFT  24

#define JAL_GIO_INTR_CLR1_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR1_MASK  0x04000000
#define JAL_GIO_INTR_CLR1_SHFT  26

#define JAL_GIO_INTR_CLR2_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR2_MASK  0x10000000
#define JAL_GIO_INTR_CLR2_SHFT  28

#define JAL_PG_TIMEOUT_INTR_CLR_ADDR (0x00000028 + JAL_BASE_ADDR)
#define JAL_PG_TIMEOUT_INTR_CLR_SHFT 0x20000000
#define JAL_PG_TIMEOUT_INTR_CLR_MASK 29

#define JAL_GIO_INTR_CLR3_ADDR  (0x00000028 + JAL_BASE_ADDR)
#define JAL_GIO_INTR_CLR3_MASK  0x40000000
#define JAL_GIO_INTR_CLR3_SHFT  30

/****************************************************************
*  Define the bit positions for the Common Status Registers
****************************************************************/

#define JAL_TIM_INTR_ADDR         (0x0000002c + JAL_BASE_ADDR)
#define JAL_TIM_INTR_MASK         0x0000000f
#define JAL_TIM_INTR_SHFT         0

#define JAL_TIM0_INTR_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_TIM0_INTR_MASK        0x00000001
#define JAL_TIM0_INTR_SHFT        0

#define JAL_TIM1_INTR_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_TIM1_INTR_MASK        0x00000002
#define JAL_TIM1_INTR_SHFT        1

#define JAL_TIM2_INTR_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_TIM2_INTR_MASK        0x00000004
#define JAL_TIM2_INTR_SHFT        2

#define JAL_TIM3_INTR_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_TIM3_INTR_MASK        0x00000008
#define JAL_TIM3_INTR_SHFT        3

#define JAL_PKD_INTR_ADDR         (0x0000002c + JAL_BASE_ADDR)
#define JAL_PKD_INTR_MASK         0x00000010
#define JAL_PKD_INTR_SHFT         4

#define JAL_AUX_TIM_INTR_ADDR     (0x0000002c + JAL_BASE_ADDR)
#define JAL_AUX_TIM_INTR_MASK     0x00000020
#define JAL_AUX_TIM_INTR_SHFT     5

#define JAL_PKA_INTR_ADDR         (0x0000002c + JAL_BASE_ADDR)
#define JAL_PKA_INTR_MASK         0x00000040
#define JAL_PKA_INTR_SHFT         6

#define JAL_PKD_RX_HDR_INTR_ADDR  (0x0000002c + JAL_BASE_ADDR)
#define JAL_PKD_RX_HDR_INTR_MASK  0x00000080
#define JAL_PKD_RX_HDR_INTR_SHFT  7

#define JAL_GIO_INTR0_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_GIO_INTR0_MASK        0x00000100
#define JAL_GIO_INTR0_SHFT        8

#define JAL_GIO_INTR1_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_GIO_INTR1_MASK        0x00000400
#define JAL_GIO_INTR1_SHFT        10

#define JAL_GIO_INTR2_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_GIO_INTR2_MASK        0x00001000
#define JAL_GIO_INTR2_SHFT        12

#define JAL_PG_TIMEOUT_INTR_ADDR  (0x0000002c + JAL_BASE_ADDR)
#define JAL_PG_TIMEOUT_INTR_MASK  0x00002000
#define JAL_PG_TIMEOUT_INTR_SHFT  13

#define JAL_GIO_INTR3_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_GIO_INTR3_MASK        0x00004000
#define JAL_GIO_INTR3_SHFT        14

#define JAL_SLEEP_ADDR        (0x0000002c + JAL_BASE_ADDR)
#define JAL_SLEEP_MASK        0x00008000
#define JAL_SLEEP_SHFT        15

/*************************************
 * TX Control Registers
 ************************************/
#define JAL_TX_LEN_ADDR      (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_LEN_MASK      0x000001ff
#define JAL_TX_LEN_SHFT      0

#define JAL_TX_TYPE_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_TYPE_MASK     0x00001e00
#define JAL_TX_TYPE_SHFT     9

#define JAL_TX_FLOW_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_FLOW_MASK     0x00002000
#define JAL_TX_FLOW_SHFT     13

#define JAL_TX_ARQN_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_ARQN_MASK     0x00004000
#define JAL_TX_ARQN_SHFT     14

#define JAL_TX_SEQN_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_SEQN_MASK     0x00008000
#define JAL_TX_SEQN_SHFT     15

#define JAL_TX_BUF_ADDR      (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_BUF_MASK      0x00010000
#define JAL_TX_BUF_SHFT      16

#define JAL_TX_MODE_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_MODE_MASK     0x00060000
#define JAL_TX_MODE_SHFT     17

#define JAL_TRANSMIT_ADDR    (0x00000030 + JAL_BASE_ADDR)  /* Obsolete */
#define JAL_TRANSMIT_MASK    0x00020000
#define JAL_TRANSMIT_SHFT    17

#define JAL_TX_HALF_ADDR     (0x00000030 + JAL_BASE_ADDR)  /* Obsolete */
#define JAL_TX_HALF_MASK     0x00040000
#define JAL_TX_HALF_SHFT     18

#define JAL_TX_L_CH_ADDR     (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_L_CH_MASK     0x00180000
#define JAL_TX_L_CH_SHFT     19

#define JAL_TX_P_FLOW_ADDR   (0x00000030 + JAL_BASE_ADDR)
#define JAL_TX_P_FLOW_MASK   0x00200000
#define JAL_TX_P_FLOW_SHFT   21

/*************************************
 * eSCO Control Registers
 ************************************/

#define JAL_ESCO_TX_LEN_ADDR   (0x00000034 + JAL_BASE_ADDR)
#define JAL_ESCO_TX_LEN_MASK   0x000000FF
#define JAL_ESCO_TX_LEN_SHFT   0

#define JAL_ESCO_RX_LEN_ADDR   (0x00000034 + JAL_BASE_ADDR)
#define JAL_ESCO_RX_LEN_MASK   0x0000FF00
#define JAL_ESCO_RX_LEN_SHFT   8

#define JAL_ESCO_LT_ADDR_ADDR   (0x00000034 + JAL_BASE_ADDR)
#define JAL_ESCO_LT_ADDR_MASK   0x00070000
#define JAL_ESCO_LT_ADDR_SHFT   16

#define JAL_SCO_ROUTE_ADDR      (0x00000034 + JAL_BASE_ADDR)
#define JAL_SCO_ROUTE_MASK      0x00080000
#define JAL_SCO_ROUTE_SHFT      19

/* hw conversion codec */
#define JAL_NEW_AULAW_TBL_ADDR         (0x00000034 + JAL_BASE_ADDR)
#define JAL_NEW_AULAW_TBL_MASK         0x00100000
#define JAL_NEW_AULAW_TBL_SHFT         20

#define JAL_SCO_TX_ALIGN_MSB_ADDR      (0x00000034 + JAL_BASE_ADDR)
#define JAL_SCO_TX_ALIGN_MSB_MASK      0x00200000
#define JAL_SCO_TX_ALIGN_MSB_SHFT      21

#define JAL_SCO_RX_ALIGN_MSB_ADDR      (0x00000034 + JAL_BASE_ADDR)
#define JAL_SCO_RX_ALIGN_MSB_MASK      0x00400000
#define JAL_SCO_RX_ALIGN_MSB_SHFT      22

/****************************************************************
*
*  Define the bit positions for the Transmit Status Registers
*
****************************************************************/
#define JAL_TX0_OVER_ADDR   (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX0_OVER_MASK   0x00000001
#define JAL_TX0_OVER_SHFT   0

#define JAL_TX0_UNDER_ADDR  (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX0_UNDER_MASK  0x00000002
#define JAL_TX0_UNDER_SHFT  1

#define JAL_TX1_OVER_ADDR   (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX1_OVER_MASK   0x00000004
#define JAL_TX1_OVER_SHFT   2


#define JAL_TX1_UNDER_ADDR  (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX1_UNDER_MASK  0x00000008
#define JAL_TX1_UNDER_SHFT  3

#define JAL_TX2_OVER_ADDR   (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX2_OVER_MASK   0x00000010
#define JAL_TX2_OVER_SHFT   4

#define JAL_TX2_UNDER_ADDR  (0x00000040 + JAL_BASE_ADDR)
#define JAL_TX2_UNDER_MASK  0x00000020
#define JAL_TX2_UNDER_SHFT  5



/****************************************************************
*
*  Define the bit positions for the Receive Control Rgeisters
*
****************************************************************/

#define JAL_RX_MODE_ADDR    (0x00000048 + JAL_BASE_ADDR)   /* Combination of RX_EN and FULL_WIN */
#define JAL_RX_MODE_MASK    0x00000003
#define JAL_RX_MODE_SHFT    0

#define JAL_RX_BUF_ADDR     (0x00000048 + JAL_BASE_ADDR)
#define JAL_RX_BUF_MASK     0x00000100
#define JAL_RX_BUF_SHFT     8

#define JAL_ERR_SEL_ADDR    (0x00000048 + JAL_BASE_ADDR)
#define JAL_ERR_SEL_MASK    0x00000e00
#define JAL_ERR_SEL_SHFT    9

#define JAL_WIN_EXT_ADDR    (0x00000048 + JAL_BASE_ADDR)
#define JAL_WIN_EXT_MASK    0x003ff000
#define JAL_WIN_EXT_SHFT    12

#define JAL_ABORT_ON_WRONG_AM_ADDR_ADDR (0x00000048 + JAL_BASE_ADDR)
#define JAL_ABORT_ON_WRONG_AM_ADDR_MASK 0x00800000
#define JAL_ABORT_ON_WRONG_AM_ADDR_SHFT 23

/****************************************************************
*
*  Define the bit positions for the Receive Status Rgeisters
*
****************************************************************/
#define JAL_RX_LEN_ADDR    (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_LEN_MASK    0x000001ff
#define JAL_RX_LEN_SHFT    0

#define JAL_RX_TYPE_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_TYPE_MASK   0x00001e00
#define JAL_RX_TYPE_SHFT   9

#define JAL_RX_FLOW_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_FLOW_MASK   0x00002000
#define JAL_RX_FLOW_SHFT   13

#define JAL_RX_ARQN_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_ARQN_MASK   0x00004000
#define JAL_RX_ARQN_SHFT   14

#define JAL_RX_SEQN_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_SEQN_MASK   0x00008000
#define JAL_RX_SEQN_SHFT   15

#define JAL_RX_AM_ADDR_ADDR (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_AM_ADDR_MASK 0x00070000
#define JAL_RX_AM_ADDR_SHFT 16

#define JAL_RX_L_CH_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_L_CH_MASK   0x00180000
#define JAL_RX_L_CH_SHFT   19

#define JAL_RX_P_FLOW_ADDR (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_P_FLOW_MASK 0x00200000
#define JAL_RX_P_FLOW_SHFT 21

#define JAL_RX_PKT_ADDR    (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_PKT_MASK    0x01000000
#define JAL_RX_PKT_SHFT    24

#define JAL_HEC_ERR_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_HEC_ERR_MASK   0x02000000
#define JAL_HEC_ERR_SHFT   25

#define JAL_CRC_ERR_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_CRC_ERR_MASK   0x04000000
#define JAL_CRC_ERR_SHFT   26

#define JAL_RX_HDR_ADDR    (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_HDR_MASK    0x08000000
#define JAL_RX_HDR_SHFT    27

//YC 20081112 Added
#define JAL_RX_EDR_SYNC_ERR_ADDR    (0x00000050 + JAL_BASE_ADDR)
#define JAL_RX_EDR_SYNC_ERR_MASK    0x40000000
#define JAL_RX_EDR_SYNC_ERR_SHFT    30

#define JAL_RX0_OVER_ADDR  (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX0_OVER_MASK  0x00000001
#define JAL_RX0_OVER_SHFT  0

#define JAL_RX0_UNDER_ADDR (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX0_UNDER_MASK 0x00000002
#define JAL_RX0_UNDER_SHFT 1

#define JAL_RX1_OVER_ADDR  (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX1_OVER_MASK  0x00000004
#define JAL_RX1_OVER_SHFT  2

#define JAL_RX1_UNDER_ADDR (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX1_UNDER_MASK 0x00000008
#define JAL_RX1_UNDER_SHFT 3

#define JAL_RX2_OVER_ADDR  (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX2_OVER_MASK  0x00000010
#define JAL_RX2_OVER_SHFT  4

#define JAL_RX2_UNDER_ADDR (0x00000054 + JAL_BASE_ADDR)
#define JAL_RX2_UNDER_MASK 0x00000020
#define JAL_RX2_UNDER_SHFT 5

#define JAL_ERR_CNT_ADDR   (0x0000005C + JAL_BASE_ADDR)
#define JAL_ERR_CNT_MASK   0x0000FFFF
#define JAL_ERR_CNT_SHFT   0

#define JAL_AM_ADDR_ABORT_ADDR   (0x00000050 + JAL_BASE_ADDR)
#define JAL_AM_ADDR_ABORT_MASK   0x20000000
#define JAL_AM_ADDR_ABORT_SHFT   29

/****************************************************************
*
*  Define the bit positions for the gio control registers
*
****************************************************************/
#define JAL_GIO_HIGH_ADDR   (0x00000060 + JAL_BASE_ADDR)
#define JAL_GIO_HIGH_MASK   0x000007ff
#define JAL_GIO_HIGH_SHFT   0

#define JAL_GIO_LOW_ADDR    (0x00000070 + JAL_BASE_ADDR)
#define JAL_GIO_LOW_MASK    0x000007ff
#define JAL_GIO_LOW_SHFT    0

/***************************************************************
*
*   Define the bit positions for the gio combine registers
*
***************************************************************/
#define JAL_GIO0_ADDR   (0x00000080 + JAL_BASE_ADDR)
#define JAL_GIO0_MASK   0x0000000F
#define JAL_GIO0_SHFT   0

#define JAL_GIO1_ADDR   (0x00000080 + JAL_BASE_ADDR)
#define JAL_GIO1_MASK   0x000000F0
#define JAL_GIO1_SHFT   4

#define JAL_GIO2_ADDR   (0x00000080 + JAL_BASE_ADDR)
#define JAL_GIO2_MASK   0x00000F00
#define JAL_GIO2_SHFT   8

#define JAL_GIO3_ADDR   (0x00000080 + JAL_BASE_ADDR)
#define JAL_GIO3_MASK   0x0000F000
#define JAL_GIO3_SHFT   12

/****************************************************************
*
*    Define the bit positions for the gio status registers
*
*****************************************************************/
#define JAL_GIO_STATUS_ADDR (0x00000084 + JAL_BASE_ADDR)
#define JAL_GIO_STATUS_MASK 0x0000000F
#define JAL_GIO_STATUS_SHFT 0

/****************************************************************
*
*  Define the bit positions for the Parallel Interface Adaptor
*
****************************************************************/
#define JAL_P_DATA_0_ADDR      (0x000000A4 + JAL_BASE_ADDR)
#define JAL_P_DATA_0_MASK      0x000000FF
#define JAL_P_DATA_0_SHFT      0

#define JAL_P_DATA_1_ADDR      (0x000000A4 + JAL_BASE_ADDR)
#define JAL_P_DATA_1_MASK      0x0000FF00
#define JAL_P_DATA_1_SHFT      8

#define JAL_P_DATA_2_ADDR      (0x000000A4 + JAL_BASE_ADDR)
#define JAL_P_DATA_2_MASK      0x00FF0000
#define JAL_P_DATA_2_SHFT      16

#define JAL_P_DATA_3_ADDR      (0x000000A4 + JAL_BASE_ADDR)
#define JAL_P_DATA_3_MASK      0xFF000000
#define JAL_P_DATA_3_SHFT      24

#define JAL_P_SETUP_ADDR      (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_SETUP_MASK       0x000000FF
#define JAL_P_SETUP_SHFT       0

#define JAL_P_MASK_ADDR        (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_MASK_MASK        0x00000F00
#define JAL_P_MASK_SHFT        8

#define JAL_P_NOW_ADDR         (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_NOW_MASK         0x00001000
#define JAL_P_NOW_SHFT         12

#define JAL_P_SEQ_ADDR         (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_SEQ_MASK         0x00002000
#define JAL_P_SEQ_SHFT         13

#define JAL_P_DATA_DIR_ADDR    (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_DATA_DIR_MASK    0x00004000
#define JAL_P_DATA_DIR_SHFT    14

#define JAL_P_RDATA_ADDR       (0x000000A8 + JAL_BASE_ADDR)
#define JAL_P_RDATA_MASK       0x007F0000
#define JAL_P_RDATA_SHFT       16

/****************************************************************
*
*  Define the bit positions for the Serial Interface Registers
*
****************************************************************/
#define JAL_SER_CFG_ADDR        (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_CFG_MASK        0x7FFFFFFF
#define JAL_SER_CFG_SHFT        0

#define JAL_SER_WRITE_ADDR       (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_WRITE_MASK       0x20000000
#define JAL_SER_WRITE_SHFT       29

#define JAL_SER_PKT_LEN_H_ADDR       (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_PKT_LEN_H_MASK       0x10000000
#define JAL_SER_PKT_LEN_H_SHFT       28

#define JAL_SER_PKT_LEN_L_ADDR       (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_PKT_LEN_L_MASK       0x000003E0
#define JAL_SER_PKT_LEN_L_SHFT       5

#define JAL_SER_ADR_LEN_ADDR       (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_ADR_LEN_MASK       0x0000001F
#define JAL_SER_ADR_LEN_SHFT       0

#define JAL_SER_BUSY_ADDR       (0x00000060 + JAL_BASE_ADDR)
#define JAL_SER_BUSY_MASK       0x80000000
#define JAL_SER_BUSY_SHFT       31

#define JAL_SER_TIME_ADDR       (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_TIME_MASK       0x000000FF
#define JAL_SER_TIME_SHFT       0

#define JAL_SER_COMBINE_ADDR    (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_COMBINE_MASK    0x00000700
#define JAL_SER_COMBINE_SHFT    8

#define JAL_SER_MASK_ADDR       (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_MASK_MASK       0x000F0000
#define JAL_SER_MASK_SHFT       16

#define JAL_SER_NOW_ADDR        (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_NOW_MASK        0x00100000
#define JAL_SER_NOW_SHFT        20

#define JAL_SER_SEQ_ADDR        (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_SEQ_MASK        0x00200000
#define JAL_SER_SEQ_SHFT        21

#define JAL_SER_MAP_SEL_ADDR        (0x00000064 + JAL_BASE_ADDR)
#define JAL_SER_MAP_SEL_MASK        0x00800000
#define JAL_SER_MAP_SEL_SHFT        23

#define JAL_SER_READ_DATA_ADDR  (0x0000006c + JAL_BASE_ADDR)
#define JAL_SER_READ_DATA_MASK  0xFFFFFFFF
#define JAL_SER_READ_DATA_SHFT  0

#define JAL_SER_DATA0_ADDR      (0x00000070 + JAL_BASE_ADDR)
#define JAL_SER_DATA0_MASK      0xFFFFFFFF
#define JAL_SER_DATA0_SHFT      0

#define JAL_SER_DATA1_ADDR      (0x00000074 + JAL_BASE_ADDR)
#define JAL_SER_DATA1_MASK      0xFFFFFFFF
#define JAL_SER_DATA1_SHFT      0

#define JAL_SER_DATA2_ADDR      (0x00000078 + JAL_BASE_ADDR)
#define JAL_SER_DATA2_MASK      0xFFFFFFFF
#define JAL_SER_DATA2_SHFT      0

#define JAL_SER_DATA3_ADDR      (0x0000007C + JAL_BASE_ADDR)
#define JAL_SER_DATA3_MASK      0xFFFFFFFF
#define JAL_SER_DATA3_SHFT      0

#define JAL_SER0_WRITE_CLR_ADDR       (0x00000028 + JAL_BASE_ADDR)
#define JAL_SER0_WRITE_CLR_MASK       0x08000000
#define JAL_SER0_WRITE_CLR_SHFT       27

/****************************************************************************
*
*  Define the bit positions for the Serial Transceiver Interface Registers
*
*****************************************************************************/
#define JAL_STB_CFG_ADDR        (0x00000080 + JAL_BASE_ADDR)
#define JAL_STB_CFG_MASK        0x7FFFFFFF
#define JAL_STB_CFG_SHFT        0

#define JAL_STB_BUSY_ADDR       (0x00000080 + JAL_BASE_ADDR)
#define JAL_STB_BUSY_MASK       0x80000000
#define JAL_STB_BUSY_SHFT       31

#define JAL_STB_DATA0_ADDR      (0x00000084 + JAL_BASE_ADDR)
#define JAL_STB_DATA0_MASK      0xFFFFFFFF
#define JAL_STB_DATA0_SHFT      0

/* receive volume control */
/****************************************************************************
*
*  Define the bit positions for the Receive Volume control Registers
*
*****************************************************************************/
#define JAL_SCO_VOL_ATT_ADDR     (0x0000009C + JAL_BASE_ADDR)
#define JAL_SCO_VOL_ATT_MASK     0x00000007
#define JAL_SCO_VOL_ATT_SHFT     0

#define JAL_PF3_BYPASS_ADDR      (0x0000009C + JAL_BASE_ADDR)
#define JAL_PF3_BYPASS_MASK      0x00000080
#define JAL_PF3_BYPASS_SHFT      7

/*******************************************************************
 *
 *     Define the bit positions for the auxilliary timer
 *     registers
 *
 *******************************************************************/
#define JAL_AUX_TIMER_ADDR     (0x000000A0 + JAL_BASE_ADDR)
#define JAL_AUX_TIMER_MASK     0x00003FFF
#define JAL_AUX_TIMER_SHFT     0


/*******************************************************************
*
*      Define the bit positions for the rx_delay and tx_delay
*      control registers
*
*******************************************************************/
#define JAL_RX_DELAY_ADDR      (0x000000b0 + JAL_BASE_ADDR)
#define JAL_RX_DELAY_MASK      0x0000007f
#define JAL_RX_DELAY_SHFT      0

#define JAL_TX_DELAY_ADDR      (0x000000b0 + JAL_BASE_ADDR)
#define JAL_TX_DELAY_MASK      0x00000f00
#define JAL_TX_DELAY_SHFT      8

/*******************************************************************
*
*      Define the bit positions for the enc_key_len and enc_key
*      (16 bytes at C0-CF) control registers
*
*******************************************************************/
#define JAL_ENC_KEY_LEN_ADDR      (0x000000b8 + JAL_BASE_ADDR)
#define JAL_ENC_KEY_LEN_MASK      0x0000000f
#define JAL_ENC_KEY_LEN_SHFT      0

#define JAL_ENC_KEY_ADDR          (0x000000C0 + JAL_BASE_ADDR)

/*******************************************************************
 *
 *   Define the bit positions for the hop selection engine
 *
 *******************************************************************/
#define JAL_SYS_ADDR           (0x000000D0 + JAL_BASE_ADDR)
#define JAL_SYS_MASK           0x00000001
#define JAL_SYS_SHFT           0

#define JAL_H_PAGE_ADDR        (0x000000D0 + JAL_BASE_ADDR)
#define JAL_H_PAGE_MASK        0x00000002
#define JAL_H_PAGE_SHFT        1

#define JAL_H_SLAVE_ADDR       (0x000000D0 + JAL_BASE_ADDR)
#define JAL_H_SLAVE_MASK       0x00000004
#define JAL_H_SLAVE_SHFT       2

#define JAL_PAGE_OFFSET_ADDR   (0x000000D0  + JAL_BASE_ADDR)
#define JAL_PAGE_OFFSET_MASK   0x00000008
#define JAL_PAGE_OFFSET_SHFT   3

#define JAL_INDEX_MAP_ADDR     (0x000000D0  + JAL_BASE_ADDR)
#define JAL_INDEX_MAP_MASK     0x00000010
#define JAL_INDEX_MAP_SHFT     4

#define JAL_CLK_DELTA_ADDR     (0x000000D0  + JAL_BASE_ADDR)
#define JAL_CLK_DELTA_MASK     0x000000E0
#define JAL_CLK_DELTA_SHFT     5

#define JAL_N_COUNT_ADDR       (0x000000D0  + JAL_BASE_ADDR)
#define JAL_N_COUNT_MASK       0x00001F00
#define JAL_N_COUNT_SHFT       8

#define JAL_SEL_ADDR           (0x000000D0  + JAL_BASE_ADDR)
#define JAL_SEL_MASK           0x00006000
#define JAL_SEL_SHFT           13

#define JAL_SUP_BT_CLK_ADDR    (0x000000D0 + JAL_BASE_ADDR)
#define JAL_SUP_BT_CLK_MASK    0xFFFF8000
#define JAL_SUP_BT_CLK_SHFT    15

#define JAL_HOP_ADDR           (0x000000D4 + JAL_BASE_ADDR)
#define JAL_HOP_MASK           0x0000007F
#define JAL_HOP_SHFT           0


/*******************************************************************
 *
 *   Define the bit positions for the BT Clock Controls(P6 only)
 *   (the clock gating signals are redundant)
 *******************************************************************/
#define JAL_ADD_BT_CLK_RELATIVE_ADDR     (0x000000F0 + JAL_BASE_ADDR)
#define JAL_ADD_BT_CLK_RELATIVE_MASK     0000000001
#define JAL_ADD_BT_CLK_RELATIVE_SHFT     0

#define JAL_WRITE_ABSOLUTE_BT_CLK_ADDR     (0x000000F0 + JAL_BASE_ADDR)
#define JAL_WRITE_ABSOLUTE_BT_CLK_MASK     0x00000002
#define JAL_WRITE_ABSOLUTE_BT_CLK_SHFT     1

#define JAL_DELAYED_BT_CLK_UPDATE_ADDR     (0x000000F0 + JAL_BASE_ADDR)
#define JAL_DELAYED_BT_CLK_UPDATE_MASK     0x00000004
#define JAL_DELAYED_BT_CLK_UPDATE_SHFT     2

#define JAL_FREEZE_BT_CLK_ADDR     (0x000000F0 + JAL_BASE_ADDR)
#define JAL_FREEZE_BT_CLK_MASK     0x00000008
#define JAL_FREEZE_BT_CLK_SHFT     3

/*******************************************************************
 *
 *   Define the bit positions for the LC Revision Code Register
 *
 *******************************************************************/
#define JAL_MINOR_REVISION_ADDR    (0x000000F8 + JAL_BASE_ADDR)
#define JAL_MINOR_REVISION_MASK    0x000000FF
#define JAL_MINOR_REVISION_SHFT    0

#define JAL_MAJOR_REVISION_ADDR    (0x000000F8 + JAL_BASE_ADDR)
#define JAL_MAJOR_REVISION_MASK    0x0000FF00
#define JAL_MAJOR_REVISION_SHFT    8

/*******************************************************************
*
*      Define the bit positions for the reset controls
*
********************************************************************/
#define JAL_RST_CODE_ADDR     (0x000000FC + JAL_BASE_ADDR)
#define JAL_RST_CODE_MASK     0xFF000000
#define JAL_RST_CODE_SHFT     24

#if EDR
/*******************************************************************
*
*      Define the bit positions for the EDR control
*
********************************************************************/

/*
 * EDR Control Register                  Address 104H
 */
#define JAL_EDR_CTRL_REG_ADDR                      (JAL_BASE_ADDR+0x104)

#define JAL_EDR_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_MASK     0x00000001
#define JAL_EDR_SHFT     0

#define JAL_EDR_MODE_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_MODE_MASK     0x00000002
#define JAL_EDR_MODE_SHFT     1

#define JAL_EDR_ESCO_RX_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_ESCO_RX_MASK     0x00000010
#define JAL_EDR_ESCO_RX_SHFT     4

#define JAL_EDR_TX_LEN_H_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_TX_LEN_H_MASK     0x01000000
#define JAL_EDR_TX_LEN_H_SHFT     24

#define JAL_EDR_RX_LEN_H_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_RX_LEN_H_MASK     0x02000000
#define JAL_EDR_RX_LEN_H_SHFT     25

#define JAL_EDR_TX_LEN_ESCO_H_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_TX_LEN_ESCO_H_MASK     0x30000000
#define JAL_EDR_TX_LEN_ESCO_H_SHFT     28

#define JAL_EDR_RX_LEN_ESCO_H_ADDR     (0x00000104 + JAL_BASE_ADDR)
#define JAL_EDR_RX_LEN_ESCO_H_MASK     0xc0000000
#define JAL_EDR_RX_LEN_ESCO_H_SHFT     30
#endif /* #if EDR */

#define JAL_EDR_CTRL_REG_JAL_EDR_MASK   JAL_EDR_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_MODE_MASK   JAL_EDR_MODE_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_ESCO_RX_MASK   JAL_EDR_ESCO_RX_MASK

#define JAL_EDR_CTRL_REG_JAL_EDR_TX_LEN_H_MASK  JAL_EDR_TX_LEN_H_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_RX_LEN_H_MASK  JAL_EDR_RX_LEN_H_MASK

#define JAL_EDR_CTRL_REG_JAL_EDR_TX_LEN_ESCO_H_MASK JAL_EDR_TX_LEN_ESCO_H_MASK
#define JAL_EDR_CTRL_REG_JAL_EDR_RX_LEN_ESCO_H_MASK JAL_EDR_RX_LEN_ESCO_H_MASK


/*
 * EDR Config Register                  Address 10cH
 */
#define JAL_EDR_CTRL_EXT_REG_ADDR                      (JAL_BASE_ADDR+0x108)

#define JAL_EDR_MBB_EN_ADDR     (0x00000108 + JAL_BASE_ADDR)
#define JAL_EDR_MBB_EN_MASK     0x80000000
#define JAL_EDR_MBB_EN_SHFT     31

#define JAL_EDR_CTRL_EXT_REG_JAL_EDR_MBB_EN_MASK  JAL_EDR_MBB_EN_MASK

/*
 * EDR Config Register                  Address 10cH
 */
#define JAL_EDR_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x10c)

#define JAL_EDR_2M_GTIME_ADDR     (0x0000010c + JAL_BASE_ADDR)
#define JAL_EDR_2M_GTIME_MASK     0x00003F00
#define JAL_EDR_2M_GTIME_SHFT     8

#define JAL_EDR_3M_GTIME_ADDR     (0x0000010c + JAL_BASE_ADDR)
#define JAL_EDR_3M_GTIME_MASK     0x003F0000
#define JAL_EDR_3M_GTIME_SHFT     16

#define JAL_EDR_CONFIG_REG_JAL_EDR_2M_GTIME_MASK   JAL_EDR_2M_GTIME_MASK
#define JAL_EDR_CONFIG_REG_JAL_EDR_3M_GTIME_MASK    JAL_EDR_3M_GTIME_MASK

/* sco/esco plc */
/*
 * PLC Config Register                  Address 11cH
 */
#define JAL_PLC_CONFIG_REG_ADDR         (JAL_BASE_ADDR+0x11c)

#define JAL_PLC_RX_START_ADDR           (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_RX_START_MASK           0x00000001
#define JAL_PLC_RX_START_SHFT           0

#define JAL_PLC_TX_START_ADDR           (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_START_MASK           0x00000002
#define JAL_PLC_TX_START_SHFT           1

#define JAL_PLC_TX_DATA_BLOCKED_ADDR    (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_DATA_BLOCKED_MASK    0x00000004
#define JAL_PLC_TX_DATA_BLOCKED_SHFT    2

#define JAL_PLC_RX_DATA_BLOCKED_ADDR    (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_RX_DATA_BLOCKED_MASK    0x00000008
#define JAL_PLC_RX_DATA_BLOCKED_SHFT    3

#define JAL_PLC_TX_BUFFER_RDY_ADDR      (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_BUFFER_RDY_MASK      0x00000010
#define JAL_PLC_TX_BUFFER_RDY_SHFT      4

#define JAL_PLC_TX_FINISH_ADDR          (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_FINISH_MASK          0x00000040
#define JAL_PLC_TX_FINISH_SHFT          6

#define JAL_PLC_RX_FINISH_ADDR          (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_RX_FINISH_MASK          0x00000080
#define JAL_PLC_RX_FINISH_SHFT          7

#define JAL_PLC_RX_LENGTH_ADDR          (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_RX_LENGTH_MASK          0x0000FF00
#define JAL_PLC_RX_LENGTH_SHFT          8

#define JAL_PLC_TX_THRESHOLD_ADDR       (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_THRESHOLD_MASK       0x00FF0000
#define JAL_PLC_TX_THRESHOLD_SHFT       16

#define JAL_PLC_TX_LENGTH_ADDR          (0x0000011c + JAL_BASE_ADDR)
#define JAL_PLC_TX_LENGTH_MASK          0xFF000000
#define JAL_PLC_TX_LENGTH_SHFT          24

#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_START_MASK           JAL_PLC_RX_START_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_START_MASK           JAL_PLC_TX_START_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_DATA_BLOCKED_MASK    JAL_PLC_TX_DATA_BLOCKED_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_DATA_BLOCKED_MASK    JAL_PLC_RX_DATA_BLOCKED_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_BUFFER_RDY_MASK      JAL_PLC_TX_BUFFER_RDY_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_FINISH_MASK          JAL_PLC_TX_FINISH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_FINISH_MASK          JAL_PLC_RX_FINISH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_RX_LENGTH_MASK          JAL_PLC_RX_LENGTH_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_THRESHOLD_MASK       JAL_PLC_TX_THRESHOLD_MASK
#define JAL_PLC_CONFIG_REG_JAL_PLC_TX_LENGTH_MASK          JAL_PLC_TX_LENGTH_MASK

/*******************************************************************
*
*      Define the bit positions for the DMA control
*
********************************************************************/

/*
 * DMA config register                  Address 120H
 */
#define JAL_DMA_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x120)

#define JAL_DMA_TX_MODE_ADDR     (0x00000120 + JAL_BASE_ADDR)
#define JAL_DMA_TX_MODE_MASK     0x00000003
#define JAL_DMA_TX_MODE_SHFT     0

#define JAL_DMA_TEST_EN_ADDR     (0x00000120 + JAL_BASE_ADDR)
#define JAL_DMA_TEST_EN_MASK     0x00000010
#define JAL_DMA_TEST_EN_SHFT     4

#define JAL_DMA_RX_MODE_ADDR     (0x00000120 + JAL_BASE_ADDR)
#define JAL_DMA_RX_MODE_MASK     0x00000300
#define JAL_DMA_RX_MODE_SHFT     8

#define JAL_DMA_CONFIG_REG_JAL_DMA_TX_MODE_MASK JAL_DMA_TX_MODE_MASK
#define JAL_DMA_CONFIG_REG_JAL_DMA_TEST_EN_MASK JAL_DMA_TEST_EN_MASK
#define JAL_DMA_CONFIG_REG_JAL_DMA_RX_MODE_MASK JAL_DMA_RX_MODE_MASK

#define DMA_MODE_CPU    0
#define DMA_MODE_DMA    1
#define DMA_MODE_PIF    2

/*******************************************************************
*
*      Define the bit positions for the pre-preamble control
*
********************************************************************/

/*
 * Pre-preamble config register                  Address 128H
 */
#define JAL_PPREAMBLE_CONFIG_REG_ADDR                      (JAL_BASE_ADDR+0x128)

#define JAL_PPREAMBLE_CNT_ADDR     JAL_PPREAMBLE_CONFIG_REG_ADDR
#define JAL_PPREAMBLE_CNT_MASK     0x0000001f
#define JAL_PPREAMBLE_CNT_SHFT     0

#define JAL_PPREAMBLE_PWR_RAMPUP_ADDR     JAL_PPREAMBLE_CONFIG_REG_ADDR
#define JAL_PPREAMBLE_PWR_RAMPUP_MASK     0x00000100
#define JAL_PPREAMBLE_PWR_RAMPUP_SHFT     8

#define JAL_PPREAMBLE_TOGGLE_ADDR     JAL_PPREAMBLE_CONFIG_REG_ADDR
#define JAL_PPREAMBLE_TOGGLE_MASK     0x00000200
#define JAL_PPREAMBLE_TOGGLE_SHFT     9

#define JAL_PPREAMBLE_DATA_ADDR     JAL_PPREAMBLE_CONFIG_REG_ADDR
#define JAL_PPREAMBLE_DATA_MASK     0x00000400
#define JAL_PPREAMBLE_DATA_SHFT     10

#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_CNT_MASK     JAL_PPREAMBLE_CNT_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_PWR_RAMPUP_MASK     JAL_PPREAMBLE_PWR_RAMPUP_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_TOGGLE_MASK     JAL_PPREAMBLE_TOGGLE_MASK
#define JAL_PPREAMBLE_CONFIG_REG_JAL_PPREAMBLE_DATA_MASK     JAL_PPREAMBLE_DATA_MASK

/* pcm configuration */
/****************************************************************************
*
*  Define the bit positions for the PCM Registers
*
*****************************************************************************/
#define JAL_PCM_CONFIG_REG_ADDR         (JAL_BASE_ADDR+0x12c)

#define JAL_PCM_CLKINV_ADDR             (0x0000012c + JAL_BASE_ADDR)
#define JAL_PCM_CLKINV_MASK             0x00000001
#define JAL_PCM_CLKINV_SHFT             0

#define JAL_PCM_DATAMODE_ADDR           (0x0000012c + JAL_BASE_ADDR)
#define JAL_PCM_DATAMODE_MASK           0x00000002
#define JAL_PCM_DATAMODE_SHFT           1

#define JAL_PCM_SYNCLEN_ADDR            (0x0000012c + JAL_BASE_ADDR)
#define JAL_PCM_SYNCLEN_MASK            0x00007F00
#define JAL_PCM_SYNCLEN_SHFT            8

#define JAL_PCM_CONFIG_REG_JAL_PCM_CLKINV_MASK      JAL_PCM_CLKINV_MASK
#define JAL_PCM_CONFIG_REG_JAL_PCM_DATAMODE_MASK    JAL_PCM_DATAMODE_MASK
#define JAL_PCM_CONFIG_REG_JAL_PCM_SYNCLEN_MASK     JAL_PCM_SYNCLEN_MASK


/*******************************************************************
*
*      debug probe
*
********************************************************************/

/*
 * debug probe register                  Address 130H
 */
#define JAL_DBG_PROBE_REG_ADDR                      (JAL_BASE_ADDR+0x130)

//YC 20090512 Timing_Modification
#define JAL_DBG_PROBE_16BITS_ADDR             (0x00000130 + JAL_BASE_ADDR)
#define JAL_DBG_PROBE_16BITS_MASK             0x0000ffff
#define JAL_DBG_PROBE_16BITS_SHFT             0

#define JAL_DBG_PROBE_SEL_ADDR             (0x00000130 + JAL_BASE_ADDR)
#define JAL_DBG_PROBE_SEL_MASK             0xff000000
#define JAL_DBG_PROBE_SEL_SHFT             24

//YC 20090512 Timing_Modification
#define JAL_DBG_PROBE_REG_JAL_DBG_PROBE_16BITS_MASK             JAL_DBG_PROBE_16BITS_MASK
#define JAL_DBG_PROBE_REG_JAL_DBG_PROBE_SEL_MASK             JAL_DBG_PROBE_SEL_MASK


/*******************************************************************
*
*      EDR config extension
*
********************************************************************/

/*
 * edr config extension register                  Address 148H
 */
#define JAL_EDR_CONFIG_EX_REG_ADDR                      (JAL_BASE_ADDR+0x148)

#define JAL_TSM_FINISH_CNT_ADDR             (0x00000148 + JAL_BASE_ADDR)
#define JAL_TSM_FINISH_CNT_MASK             0x0000001f
#define JAL_TSM_FINISH_CNT_SHFT             0

/* manual cvsd */
#define JAL_CVSD_RETXRX_ON_ADDR             (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_ON_MASK             0x00000100
#define JAL_CVSD_RETXRX_ON_SHFT             8

#define JAL_CVSD_RETXRX_COMMIT_TX_ADDR      (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_COMMIT_TX_MASK      0x00000200
#define JAL_CVSD_RETXRX_COMMIT_TX_SHFT      9

#define JAL_CVSD_RETXRX_RESET_ADDR          (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_RESET_MASK          0x00000400
#define JAL_CVSD_RETXRX_RESET_SHFT          10

#define JAL_CVSD_RETXRX_COMMIT_RX_ADDR      (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_RETXRX_COMMIT_RX_MASK      0x00000800
#define JAL_CVSD_RETXRX_COMMIT_RX_SHFT      11

#define JAL_TSM_GUARDTIME_GFSK_OFF_ADDR     (0x00000148 + JAL_BASE_ADDR)
#define JAL_TSM_GUARDTIME_GFSK_OFF_MASK     0x00001000
#define JAL_TSM_GUARDTIME_GFSK_OFF_SHFT     12

#define JAL_CVSD_TX_GAIN_ADDR               (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_TX_GAIN_MASK               0x00004000
#define JAL_CVSD_TX_GAIN_SHFT               14

#define JAL_CVSD_RX_GAIN_ADDR               (0x00000148 + JAL_BASE_ADDR)
#define JAL_CVSD_RX_GAIN_MASK               0x00008000
#define JAL_CVSD_RX_GAIN_SHFT               15

#define JAL_GFSK_PADDING_CNT_ADDR           (0x00000148 + JAL_BASE_ADDR)
#define JAL_GFSK_PADDING_CNT_MASK           0x001f0000
#define JAL_GFSK_PADDING_CNT_SHFT           16

#define JAL_EDR_CONFIG_EX_REG_JAL_TSM_FINISH_CNT_MASK             JAL_TSM_FINISH_CNT_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_ON_MASK             JAL_CVSD_RETXRX_ON_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_COMMIT_TX_MASK      JAL_CVSD_RETXRX_COMMIT_TX_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_RESET_MASK          JAL_CVSD_RETXRX_RESET_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RETXRX_COMMIT_RX_MASK      JAL_CVSD_RETXRX_COMMIT_RX_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_TSM_GUARDTIME_GFSK_OFF_MASK     JAL_TSM_GUARDTIME_GFSK_OFF_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_TX_GAIN_MASK               JAL_CVSD_TX_GAIN_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_CVSD_RX_GAIN_MASK               JAL_CVSD_RX_GAIN_MASK
#define JAL_EDR_CONFIG_EX_REG_JAL_GFSK_PADDING_CNT_MASK           JAL_GFSK_PADDING_CNT_MASK


/****************************************************************
*
*  Define the Transmit and Receive Registers
*
****************************************************************/
#define JAL_TX_ACL_BUF_OFFSET   0x0000200
#define JAL_RX_ACL_BUF_OFFSET   0x0000700
#define JAL_ACL_BUF_LEN   1024 /* ethan. extend acl buffer size from 360 to 1024 */

/****************************************************************
 *  Define additional constants for hardware
 ****************************************************************/
#define  JAL_MAX_POSITION_ERROR     10
#define  JAL_MAX_PACKET_LENGTH      341
#define  JAL_HW_REGISTER_LENGTH     (RX_ACL_BUF_ADDR+ACL_BUF_LEN)

/****************************************************************
*
*  Define the addresses of the main registers and associated
*  fields to allow local caching of registers and checking of
*  field assignments to take place
*  To use a local copy of a register
*  1. Give it a unique meaningful name REGISTER_XXX.
*  2. #define REGISTER_XXX_FIELD FIELD for each FIELD that will be
*     used with this register
*  3
*
****************************************************************/
/*
 * BD_ADDR Register        Low/High Address 00H/04H
 */
#define JAL_COM_CTRL_BD_ADDR_LO_REG_ADDR             (JAL_BASE_ADDR+0x00)
#define JAL_COM_CTRL_BD_ADDR_HI_REG_ADDR             (JAL_BASE_ADDR+0x04)

/*
 * Clock Registers         BT_CLK[_OFFSET]  18H/ NATIVE_CLK 1CH
 */
#define JAL_COM_CTRL_BT_CLK_READ_REG_ADDR           (JAL_BASE_ADDR+0x18)
#define JAL_COM_CTRL_BT_CLK_OFFSET_WRITE_REG_ADDR   (JAL_BASE_ADDR+0x18)
#define JAL_COM_CTRL_NATIVE_CLK_REG_ADDR            (JAL_BASE_ADDR+0x1C)

/*
 * Common Control Syncword Low/High Address 08H/12H
 */
#define JAL_COM_CTRL_SYNC_LO_REG_ADDR             (JAL_BASE_ADDR+0x08)
#define JAL_COM_CTRL_SYNC_HI_REG_ADDR             (JAL_BASE_ADDR+0x0C)

/*
 * Common Control General Purpose Register 1  Address 20H
 */
#define JAL_COM_CTRL_GP1_REG_ADDR                 (JAL_BASE_ADDR+0x20)

#define JAL_COM_CTRL_GP1_REG_JAL_PAGE_MASK        JAL_PAGE_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SLAVE_MASK       JAL_SLAVE_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_USE_LF_MASK      JAL_USE_LF_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_ENCRYPT_MASK     JAL_ENCRYPT_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_AM_ADDR_MASK     JAL_AM_ADDR_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG_MASK    JAL_SCO_CFG_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG0_MASK   JAL_SCO_CFG0_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG1_MASK   JAL_SCO_CFG1_MASK
#define JAL_COM_CTRL_GP1_REG_JAL_SCO_CFG2_MASK   JAL_SCO_CFG2_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_SCO_FIFO_MASK   JAL_SCO_FIFO_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_VCI_CLK_SEL_MASK   JAL_VCI_CLK_SEL_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_CRC_INIT_MASK    JAL_CRC_INIT_MASK

#define JAL_COM_CTRL_GP1_REG_JAL_CLK1M_DIR_MASK JAL_CLK1M_DIR_MASK

/*
 * Common Control General Purpose Register 2  Address 24H
 */
#define JAL_COM_CTRL_GP2_REG_ADDR                      (JAL_BASE_ADDR+0x24)

/*
 * All whitening registers grouped in one u_int32 control word
 */
#define JAL_COM_CTRL_GP2_REG_JAL_WHITEN_MASK          JAL_WHITEN_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_INIT_MASK        JAL_DWH_INIT_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH2_INIT_MASK       JAL_DWH2_INIT_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_BY_BT_CLK_MASK   JAL_DWH_BY_BT_CLK_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_DWH_ALL_REG_MASK     JAL_DWH_ALL_REG_MASK
#define JAL_COM_CTRL_GP2_REG_JAL_VCI_CLK_SEL_MAP_MASK JAL_VCI_CLK_SEL_MAP_MASK

/*
 * Common Control Interrupt Register          Address 28H
 */
#define JAL_COM_CTRL_IRQ_REG_ADDR                     (JAL_BASE_ADDR+0x28)

#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_RX_HDR_INTR_MSK_MASK   JAL_PKD_RX_HDR_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_INTR_MSK_MASK          JAL_PKD_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKA_INTR_MSK_MASK          JAL_PKA_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM_INTR_MSK_MASK          JAL_TIM_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM0_INTR_MSK_MASK         JAL_TIM0_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM1_INTR_MSK_MASK         JAL_TIM1_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM2_INTR_MSK_MASK         JAL_TIM2_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM3_INTR_MSK_MASK         JAL_TIM3_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_NO_PKT_RCVD_INTR_MSK_MASK  JAL_NO_PKT_RCVD_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SYNC_DET_INTR_MSK_MASK     JAL_SYNC_DET_INTR_MSK_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_AUX_TIM_INTR_MSK_MASK       JAL_AUX_TIM_INTR_MSK_MASK

#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_RX_HDR_INTR_CLR_MASK    JAL_PKD_RX_HDR_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKD_INTR_CLR_MASK           JAL_PKD_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_PKA_INTR_CLR_MASK           JAL_PKA_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM0_INTR_CLR_MASK          JAL_TIM0_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM1_INTR_CLR_MASK          JAL_TIM1_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM2_INTR_CLR_MASK          JAL_TIM2_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_TIM3_INTR_CLR_MASK          JAL_TIM3_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_NO_PKT_RCVD_INTR_CLR_MASK   JAL_NO_PKT_RCVD_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SYNC_DET_INTR_CLR_MASK      JAL_SYNC_DET_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_AUX_TIM_INTR_CLR_MASK       JAL_AUX_TIM_INTR_CLR_MASK
#define JAL_COM_CTRL_IRQ_REG_JAL_SER0_WRITE_CLR_MASK         JAL_SER0_WRITE_CLR_MASK

/*
 * Common Control Interrupt Register          Address 2CH
 */
#define JAL_COM_STAT_IRQ_REG_ADDR                     (JAL_BASE_ADDR+0x2C)

#define JAL_COM_STAT_IRQ_REG_JAL_PKD_RX_HDR_INTR_MASK      JAL_PKD_RX_HDR_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_PKD_INTR_MASK             JAL_PKD_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_PKA_INTR_MASK             JAL_PKA_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM0_INTR_MASK            JAL_TIM0_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM1_INTR_MASK            JAL_TIM1_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM2_INTR_MASK            JAL_TIM2_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_TIM3_INTR_MASK            JAL_TIM3_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_NO_PKT_RCVD_INTR_MASK     JAL_NO_PKT_RCVD_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_SYNC_DET_INTR_MASK        JAL_SYNC_DET_INTR_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_SLEEP_STATUS_MASK         JAL_SLEEP_STATUS_MASK
#define JAL_COM_STAT_IRQ_REG_JAL_AUX_TIM_INTR_MASK         JAL_AUX_TIM_INTR_MASK


/*
 * Transmit Control Register                  Address 30H
 */
#define JAL_TX_CTRL_REG_ADDR                      (JAL_BASE_ADDR+0x30)

#define JAL_TX_CTRL_REG_JAL_TX_LEN_MASK            JAL_TX_LEN_MASK
#define JAL_TX_CTRL_REG_JAL_TX_TYPE_MASK           JAL_TX_TYPE_MASK

#define JAL_TX_CTRL_REG_JAL_TX_FLOW_MASK           JAL_TX_FLOW_MASK
#define JAL_TX_CTRL_REG_JAL_TX_ARQN_MASK           JAL_TX_ARQN_MASK
#define JAL_TX_CTRL_REG_JAL_TX_SEQN_MASK           JAL_TX_SEQN_MASK

#define JAL_TX_CTRL_REG_JAL_TX_BUF_MASK            JAL_TX_BUF_MASK

#define JAL_TX_CTRL_REG_JAL_TX_MODE_MASK           JAL_TX_MODE_MASK
#define JAL_TX_CTRL_REG_JAL_TX_L_CH_MASK           JAL_TX_L_CH_MASK
#define JAL_TX_CTRL_REG_JAL_TX_P_FLOW_MASK         JAL_TX_P_FLOW_MASK

/*
 * eSCO Control Register                    Address 34H
 */

#define JAL_ESCO_CTRL_REG_ADDR       (JAL_BASE_ADDR+0x34)

#define JAL_ESCO_CTRL_REG_JAL_ESCO_TX_LEN_MASK      JAL_ESCO_TX_LEN_MASK
#define JAL_ESCO_CTRL_REG_JAL_ESCO_RX_LEN_MASK      JAL_ESCO_RX_LEN_MASK
#define JAL_ESCO_CTRL_REG_JAL_ESCO_LT_ADDR_MASK      JAL_ESCO_LT_ADDR_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_ROUTE_MASK     JAL_SCO_ROUTE_MASK
/* hw conversion codec */
#define JAL_ESCO_CTRL_REG_JAL_NEW_AULAW_TBL_MASK     JAL_NEW_AULAW_TBL_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_TX_ALIGN_MSB_MASK  JAL_SCO_TX_ALIGN_MSB_MASK
#define JAL_ESCO_CTRL_REG_JAL_SCO_RX_ALIGN_MSB_MASK  JAL_SCO_RX_ALIGN_MSB_MASK

/*
 * Transmit Status Register                   Address 40H
 */
#define JAL_TX_STATUS_REG_ADDR                    (JAL_BASE_ADDR+0x40)

/*
 * Receive Control Register                   Address 48H
 */
#define JAL_RX_CTRL_REG_ADDR                      (JAL_BASE_ADDR+0x48)

#define JAL_RX_CTRL_REG_JAL_RX_MODE_MASK         JAL_RX_MODE_MASK
#define JAL_RX_CTRL_REG_JAL_SYNC_ERR_MASK        JAL_SYNC_ERR_MASK
#define JAL_RX_CTRL_REG_JAL_ABORT_ON_WRONG_AM_ADDR_MASK     JAL_ABORT_ON_WRONG_AM_ADDR_MASK
#define JAL_RX_CTRL_REG_JAL_RX_BUF_MASK          JAL_RX_BUF_MASK
#define JAL_RX_CTRL_REG_JAL_ERR_SEL_MASK         JAL_ERR_SEL_MASK
#define JAL_RX_CTRL_REG_JAL_WIN_EXT_MASK         JAL_WIN_EXT_MASK

/*
 * Receive Status General Purpose Register    Address 50H
 */
#define JAL_RX_STATUS_GP_REG_ADDR                 (JAL_BASE_ADDR+0x50)

#define JAL_RX_STATUS_GP_REG_JAL_RX_LEN_MASK      JAL_RX_LEN_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_TYPE_MASK     JAL_RX_TYPE_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_FLOW_MASK     JAL_RX_FLOW_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_ARQN_MASK     JAL_RX_ARQN_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_SEQN_MASK     JAL_RX_SEQN_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_AM_ADDR_MASK  JAL_RX_AM_ADDR_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_L_CH_MASK     JAL_RX_L_CH_MASK
#define JAL_RX_STATUS_GP_REG_JAL_RX_P_FLOW_MASK   JAL_RX_P_FLOW_MASK

#define JAL_RX_STATUS_GP_REG_JAL_RX_PKT_MASK      JAL_RX_PKT_MASK
#define JAL_RX_STATUS_GP_REG_JAL_HEC_ERR_MASK     JAL_HEC_ERR_MASK
#define JAL_RX_STATUS_GP_REG_JAL_CRC_ERR_MASK     JAL_CRC_ERR_MASK
//YC 20081201 Added
#define JAL_RX_STATUS_GP_REG_JAL_RX_EDR_SYNC_ERR_MASK     JAL_RX_EDR_SYNC_ERR_MASK

#define JAL_RX_STATUS_GP_REG_JAL_AM_ADDR_ABORT_MASK     JAL_AM_ADDR_ABORT_MASK


/*
 * Receive Status SCO Register                Address 54H
 */
#define JAL_RX_STATUS_SCO_REG_ADDR                (JAL_BASE_ADDR+0x54)

/*
 * Encryption Key Length Register             Address B8H
 */
#define JAL_ENC_KEY_LENGTH_REG_ADDR               (JAL_BASE_ADDR+0xB8)

/*
 * Parallel Interface Adapter Register        Address A4H
 */
#define JAL_PIA_DATA_REG_ADDR                     (JAL_BASE_ADDR+0xA4)

#define JAL_PIA_DATA_REG_JAL_P_DATA_0_MASK     JAL_P_DATA_0_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_1_MASK     JAL_P_DATA_1_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_2_MASK     JAL_P_DATA_2_MASK
#define JAL_PIA_DATA_REG_JAL_P_DATA_3_MASK     JAL_P_DATA_3_MASK


/*
 * Serial Interface Adapter Register          Address 60H
 */
#define JAL_SER_CFG_REG_ADDR                     (JAL_BASE_ADDR+0x60)

#define JAL_SER_CFG_REG_JAL_SER_CFG_MASK         JAL_SER_CFG_MASK
#define JAL_SER_CFG_REG_JAL_SER_BUSY_MASK        JAL_SER_BUSY_MASK
#define JAL_SER_CFG_REG_JAL_SER_WRITE_MASK        JAL_SER_WRITE_MASK
#define JAL_SER_CFG_REG_JAL_SER_PKT_LEN_H_MASK        JAL_SER_PKT_LEN_H_MASK
#define JAL_SER_CFG_REG_JAL_SER_PKT_LEN_L_MASK        JAL_SER_PKT_LEN_L_MASK
#define JAL_SER_CFG_REG_JAL_SER_ADR_LEN_MASK        JAL_SER_ADR_LEN_MASK

#define JAL_SER_CTRL_REG_ADDR                    (JAL_BASE_ADDR+0x64)

#define JAL_SER_CTRL_REG_JAL_SER_TIME_MASK       JAL_SER_TIME_MASK
#define JAL_SER_CTRL_REG_JAL_SER_COMBINE_MASK    JAL_SER_COMBINE_MASK
#define JAL_SER_CTRL_REG_JAL_SER_MASK_MASK       JAL_SER_MASK_MASK
#define JAL_SER_CTRL_REG_JAL_SER_NOW_MASK        JAL_SER_NOW_MASK
#define JAL_SER_CTRL_REG_JAL_SER_SEQ_MASK        JAL_SER_SEQ_MASK
#define JAL_SER_CTRL_REG_JAL_SER_MAP_SEL_MASK        JAL_SER_MAP_SEL_MASK


#define JAL_SER_DATA0_REG_ADDR                  (JAL_BASE_ADDR+0x70)
#define JAL_SER_DATA1_REG_ADDR                  (JAL_BASE_ADDR+0x74)
#define JAL_SER_DATA2_REG_ADDR                  (JAL_BASE_ADDR+0x78)
#define JAL_SER_DATA3_REG_ADDR                  (JAL_BASE_ADDR+0x7C)


/*
 * Definitions for the Enhanced SER block
 */
#define JAL_SER_ESER_CTRL_REG_ADDR                    (JAL_BASE_ADDR+0x64)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_COMBINE_MASK    (0x00070000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MASK_MASK       (0x0000FFFF)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_NOW_MASK        (0x00100000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_SEQ_MASK        (0x00200000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_DOUBLE_MASK     (0x00400000)
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_SEL_MASK    (0x00800000)

#define JAL_SER_ESER_CTRL_REG_JAL_SER_COMBINE_BIT_OFFSET    16
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MASK_BIT_OFFSET        0
#define JAL_SER_ESER_CTRL_REG_JAL_SER_NOW_BIT_OFFSET        20
#define JAL_SER_ESER_CTRL_REG_JAL_SER_SEQ_BIT_OFFSET        21
#define JAL_SER_ESER_CTRL_REG_JAL_SER_DOUBLE_BIT_OFFSET     22
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_SEL_BIT_OFFSET    23
#define JAL_SER_ESER_CTRL_REG_JAL_SER_MAP_BUSY_BIT_OFFSET   31



#define JAL_SER_ESER_TIME_REG_ADDR         (JAL_BASE_ADDR+0x68)
#define JAL_SER_ESER_TIME_0_MASK           (0x000F)
#define JAL_SER_ESER_TIME_1_MASK           (0x00F0)
#define JAL_SER_ESER_TIME_2_MASK           (0x0F00)
#define JAL_SER_ESER_TIME_3_MASK           (0xF000)

#define JAL_SER_ESER_TIME_0_BIT_OFFSET     0
#define JAL_SER_ESER_TIME_1_BIT_OFFSET     4
#define JAL_SER_ESER_TIME_2_BIT_OFFSET     8
#define JAL_SER_ESER_TIME_3_BIT_OFFSET     12

/* receive volume control */
/*
 * Receive Volume control Register    Address 9CH
 */
#define JAL_RECV_VOLUME_CTRL_REG_ADDR                   (JAL_BASE_ADDR+0x9C)

#define JAL_RECV_VOLUME_CTRL_REG_JAL_SCO_VOL_ATT_MASK   JAL_SCO_VOL_ATT_MASK
#define JAL_RECV_VOLUME_CTRL_REG_JAL_PF3_BYPASS_MASK    JAL_PF3_BYPASS_MASK

#define JAL_SER_ESER_DATA_ADDR                   (JAL_BASE_ADDR+0x600)
#define JAL_SER_ESER_DATA_0_ADDR                 (JAL_SER_ESER_DATA_ADDR)
#define JAL_SER_ESER_DATA_1_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*1)
#define JAL_SER_ESER_DATA_2_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*2)
#define JAL_SER_ESER_DATA_3_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*3)
#define JAL_SER_ESER_DATA_4_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*4)
#define JAL_SER_ESER_DATA_5_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*5)
#define JAL_SER_ESER_DATA_6_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*6)
#define JAL_SER_ESER_DATA_7_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*7)
#define JAL_SER_ESER_DATA_8_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*8)
#define JAL_SER_ESER_DATA_9_ADDR                 (JAL_SER_ESER_DATA_ADDR+4*9)
#define JAL_SER_ESER_DATA_10_ADDR                (JAL_SER_ESER_DATA_ADDR+4*10)
#define JAL_SER_ESER_DATA_11_ADDR                (JAL_SER_ESER_DATA_ADDR+4*11)
#define JAL_SER_ESER_DATA_12_ADDR                (JAL_SER_ESER_DATA_ADDR+4*12)
#define JAL_SER_ESER_DATA_13_ADDR                (JAL_SER_ESER_DATA_ADDR+4*13)
#define JAL_SER_ESER_DATA_14_ADDR                (JAL_SER_ESER_DATA_ADDR+4*14)
#define JAL_SER_ESER_DATA_15_ADDR                (JAL_SER_ESER_DATA_ADDR+4*15)




/*
 * Parallel Interface Adapter Register        Address A8H
 */
#define JAL_PIA_CTRL_REG_ADDR                   (JAL_BASE_ADDR+0xA8)

#define JAL_PIA_CTRL_REG_JAL_P_SETUP_MASK       JAL_P_SETUP_MASK
#define JAL_PIA_CTRL_REG_JAL_P_MASK_MASK        JAL_P_MASK_MASK
#define JAL_PIA_CTRL_REG_JAL_P_NOW_MASK         JAL_P_NOW_MASK
#define JAL_PIA_CTRL_REG_JAL_P_SEQ_MASK         JAL_P_SEQ_MASK
#define JAL_PIA_CTRL_REG_JAL_P_DATA_DIR_MASK    JAL_P_DATA_DIR_MASK
#define JAL_PIA_CTRL_REG_JAL_P_RDATA_MASK       JAL_P_RDATA_MASK


/*
 * Hop Selection Control Register             Address D0H (temp 9CH)
 *                                            see register definitions
 */
#define JAL_HSE_CONTROL_REG_ADDR                 (JAL_BASE_ADDR+0xD0)

#define JAL_HSE_CONTROL_REG_JAL_SYS_MASK          JAL_SYS_MASK
#define JAL_HSE_CONTROL_REG_JAL_H_PAGE_MASK       JAL_H_PAGE_MASK
#define JAL_HSE_CONTROL_REG_JAL_H_SLAVE_MASK      JAL_H_SLAVE_MASK
#define JAL_HSE_CONTROL_REG_JAL_PAGE_OFFSET_MASK  JAL_PAGE_OFFSET_MASK
#define JAL_HSE_CONTROL_REG_JAL_INDEX_MAP_MASK    JAL_INDEX_MAP_MASK
#define JAL_HSE_CONTROL_REG_JAL_CLK_DELTA_MASK    JAL_CLK_DELTA_MASK
#define JAL_HSE_CONTROL_REG_JAL_N_COUNT_MASK      JAL_N_COUNT_MASK
#define JAL_HSE_CONTROL_REG_JAL_SEL_MASK          JAL_SEL_MASK
#define JAL_HSE_CONTROL_REG_JAL_SUP_BT_CLK_MASK   JAL_SUP_BT_CLK_MASK

/*
 * Hop Selection Control Register             Address D4H
 */
#define JAL_HSE_HOP_REG_ADDR                      (JAL_BASE_ADDR+0xD4)
#define JAL_HSE_HOP_REG_JAL_HOP_MASK              JAL_HOP_MASK

/*
 * Hop Selection Registers V1.2               Address D0-DC
 * No fields, since there is only a single one in each register.
 *  Addr       b7     b6     b5     b4     b3     b2     b1     b0
 *  CONTROL +------+------+------+------+------+------+------+------+
 *  D0      |    HSE_BT_CLK[27:0]                                   |
 *          +------+------+------+------+------+------+------+------+
 *  D4      |    HSE_UAP_LAP[23:0]                                  |
 *          +------+------+------+------+------+------+------+------+
 *  D8      |    HSE_SUM[23:0]                                      |
 *          +------+------+------+------+------+------+------+------+
 *  DC      |    HSE_RF_CHAN_INDEX[6:0]                             |
 *          +------+------+------+------+------+------+------+------+
 */
#define JAL_HSE_BT_CLK_REG_ADDR                   (JAL_BASE_ADDR+0xD0)
#define JAL_HSE_UAP_LAP_REG_ADDR                  (JAL_BASE_ADDR+0xD4)
#define JAL_HSE_SUM_REG_ADDR                      (JAL_BASE_ADDR+0xD8)
#define JAL_HSE_RF_CHAN_INDEX_REG_ADDR            (JAL_BASE_ADDR+0xDC)

#if (PRH_BS_CFG_SYS_SCO_REPEATER_SUPPORTED==1)
/*******************************************************************
 *
 *   Define the bit positions for the SCO Repeater Controls(Tama only)
 *   (NT clock phase offset is also adjustable when hit by RX packet)
 *******************************************************************/
#define JAL_SCO_REPEATER_BIT_ADDR     (0x000000F0 + JAL_BASE_ADDR)
#define JAL_SCO_REPEATER_BIT_MASK     0x000000010
#define JAL_SCO_REPEATER_BIT_SHFT     4
#endif // (PRH_BS_CFG_SYS_SCO_REPEATER_SUPPORTED==1)

#endif // __HERCULES_AEON__

#endif // _PARTHUS_HW_JAL_DEFS_PUB_H_

