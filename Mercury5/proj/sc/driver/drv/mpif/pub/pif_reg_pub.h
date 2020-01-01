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
-------------------------------------------------------------------------------*/
#ifndef __PIF_REG_PUB_H__
#define __PIF_REG_PUB_H__


/************************************************************************
 * Include File
 ************************************************************************/


/************************************************************************
 * Constant
 ************************************************************************/
/***************************************************************
*
*	master register file
*
***************************************************************/

/*----------- lc 1a control/data -----------*/
#define MPIF_R_LC1A_CONTROL	0x00

#define MPIF_R_LC1A_VALID_ADDR 0
#define MPIF_R_LC1A_VALID_OFFSET	0
#define MPIF_R_LC1A_VALID_LEN	1

#define MPIF_R_LC1A_RW_ADDR 0
#define MPIF_R_LC1A_RW_OFFSET	 1
#define MPIF_R_LC1A_RW_LEN   1

#define MPIF_R_LC1A_SID_ADDR 0
#define MPIF_R_LC1A_SID_OFFSET 2
#define MPIF_R_LC1A_SID_LEN  2

#define MPIF_R_LC1A_IDX_ADDR 0
#define MPIF_R_LC1A_IDX_OFFSET 4
#define MPIF_R_LC1A_IDX_LEN  3

#define MPIF_R_LC1A_DATA_ADDR 0
#define MPIF_R_LC1A_DATA_OFFSET 8
#define MPIF_R_LC1A_DATA_LEN   8

/*----------- lc 2a control -----------*/
#define MPIF_R_LC2A_CONTROL	0x01

#define MPIF_R_LC2A_VALID_ADDR 1
#define MPIF_R_LC2A_VALID_OFFSET  0
#define MPIF_R_LC2A_VALID_LEN    1

#define MPIF_R_LC2A_RW_ADDR 1
#define MPIF_R_LC2A_RW_OFFSET  1
#define MPIF_R_LC2A_RW_LEN   1

#define MPIF_R_LC2A_SID_ADDR 1
#define MPIF_R_LC2A_SID_OFFSET  2
#define MPIF_R_LC2A_SID_LEN   2

#define MPIF_R_LC2A_CHK_ADDR 1
#define MPIF_R_LC2A_CHK_OFFSET  4
#define MPIF_R_LC2A_CHK_LEN   1

#define MPIF_R_LC2A_RETRX_EN_ADDR 1
#define MPIF_R_LC2A_RETRX_EN_OFFSET 5
#define MPIF_R_LC2A_RETRX_EN_LEN   1

#define MPIF_R_LC2A_RETRX_LIMIT_ADDR 1
#define MPIF_R_LC2A_RETRX_LIMIT_OFFSET 6
#define MPIF_R_LC2A_RETRX_LIMIT_LEN  2

/*----------- lc 2a addr -----------*/
#define MPIF_R_LC2A_ADDR_ADDR  2
#define MPIF_R_LC2A_ADDR_OFFSET  0
#define MPIF_R_LC2A_ADDR_LEN   16

/*----------- lc 2a data -----------*/
#define MPIF_R_LC2A_DATA_ADDR  3
#define MPIF_R_LC2A_DATA_OFFSET  0
#define MPIF_R_LC2A_DATA_LEN   16

/*----------- lc 2b control -----------*/
#define MPIF_R_LC2B_CONTROL	0x04

#define MPIF_R_LC2B_VALID_ADDR 4
#define MPIF_R_LC2B_VALID_OFFSET  0
#define MPIF_R_LC2B_VALID_LEN    1

#define MPIF_R_LC2B_RW_ADDR 4
#define MPIF_R_LC2B_RW_OFFSET  1
#define MPIF_R_LC2B_RW_LEN   1

#define MPIF_R_LC2B_SID_ADDR 4
#define MPIF_R_LC2B_SID_OFFSET  2
#define MPIF_R_LC2B_SID_LEN   2

#define MPIF_R_LC2B_CHK_ADDR 4
#define MPIF_R_LC2B_CHK_OFFSET  4
#define MPIF_R_LC2B_CHK_LEN   1

#define MPIF_R_LC2B_RETRX_EN_ADDR 4
#define MPIF_R_LC2B_RETRX_EN_OFFSET 5
#define MPIF_R_LC2B_RETRX_EN_LEN   1

#define MPIF_R_LC2B_RETRX_LIMIT_ADDR 4
#define MPIF_R_LC2B_RETRX_LIMIT_OFFSET 6
#define MPIF_R_LC2B_RETRX_LIMIT_LEN  2

/*----------- lc 2b addr -----------*/
#define MPIF_R_LC2B_ADDR_ADDR  5
#define MPIF_R_LC2B_ADDR_OFFSET  0
#define MPIF_R_LC2B_ADDR_LEN   16

/*----------- lc 2b data -----------*/
#define MPIF_R_LC2B_DATA_ADDR  6
#define MPIF_R_LC2B_DATA_OFFSET  0
#define MPIF_R_LC2B_DATA_LEN   16

/*----------- lc 3a control -----------*/
#define MPIF_R_LC3A_CONTROL	0x07

#define MPIF_R_LC3A_VALID_ADDR 7
#define MPIF_R_LC3A_VALID_OFFSET 0
#define MPIF_R_LC3A_VALID_LEN   1

#define MPIF_R_LC3A_RW_ADDR 7
#define MPIF_R_LC3A_RW_OFFSET 1
#define MPIF_R_LC3A_RW_LEN   1

#define MPIF_R_LC3A_SID_ADDR 7
#define MPIF_R_LC3A_SID_OFFSET 2
#define MPIF_R_LC3A_SID_LEN   2

#define MPIF_R_LC3A_CHK_ADDR 7
#define MPIF_R_LC3A_CHK_OFFSET  4
#define MPIF_R_LC3A_CHK_LEN   1

#define MPIF_R_LC3A_RETRX_EN_ADDR 7
#define MPIF_R_LC3A_RETRX_EN_OFFSET 5
#define MPIF_R_LC3A_RETRX_EN_LEN   1

#define MPIF_R_LC3A_RETRX_LIMIT_ADDR 7
#define MPIF_R_LC3A_RETRX_LIMIT_OFFSET 6
#define MPIF_R_LC3A_RETRX_LIMIT_LEN  2

#define MPIF_R_LC3A_SRC_ADDR 7
#define MPIF_R_LC3A_SRC_OFFSET 8
#define MPIF_R_LC3A_SRC_LEN   1

#define MPIF_R_LC3A_MIUSEL_ADDR 7
#define MPIF_R_LC3A_MIUSEL_OFFSET 9
#define MPIF_R_LC3A_MIUSEL_LEN  1

#define MPIF_R_LC3A_FMODE_ADDR 7
#define MPIF_R_LC3A_FMODE_OFFSET 10
#define MPIF_R_LC3A_FMODE_LEN  1

/*----------- lc 3a length -----------*/
#define MPIF_R_LC3A_PKTLEN_ADDR  8
#define MPIF_R_LC3A_PKTLEN_OFFSET  0
#define MPIF_R_LC3A_PKTLEN_LEN  16

/*----------- lc 3a miu-based addr -----------*/
#define MPIF_R_LC3A_MADR_L_ADDR  0x11
#define MPIF_R_LC3A_MADR_L_OFFSET 0
#define MPIF_R_LC3A_MADR_L_LEN   16

#define MPIF_R_LC3A_MADR_H_ADDR  0x12
#define MPIF_R_LC3A_MADR_H_OFFSET 0
#define MPIF_R_LC3A_MADR_H_LEN   8

/*----------- lc 3b control -----------*/
#define MPIF_R_LC3B_VALID_ADDR 0x13
#define MPIF_R_LC3B_VALID_OFFSET 0
#define MPIF_R_LC3B_VALID_LEN   1

#define MPIF_R_LC3B_RW_ADDR 0x13
#define MPIF_R_LC3B_RW_OFFSET 1
#define MPIF_R_LC3B_RW_LEN   1

#define MPIF_R_LC3B_SID_ADDR 0x13
#define MPIF_R_LC3B_SID_OFFSET 2
#define MPIF_R_LC3B_SID_LEN   2

#define MPIF_R_LC3B_CHK_ADDR 0x13
#define MPIF_R_LC3B_CHK_OFFSET  4
#define MPIF_R_LC3B_CHK_LEN   1

#define MPIF_R_LC3B_RETRX_EN_ADDR 0x13
#define MPIF_R_LC3B_RETRX_EN_OFFSET 5
#define MPIF_R_LC3B_RETRX_EN_LEN   1

#define MPIF_R_LC3B_RETRX_LIMIT_ADDR 0x13
#define MPIF_R_LC3B_RETRX_LIMIT_OFFSET 6
#define MPIF_R_LC3B_RETRX_LIMIT_LEN  2

#define MPIF_R_LC3B_SRC_ADDR 0x13
#define MPIF_R_LC3B_SRC_OFFSET 8
#define MPIF_R_LC3B_SRC_LEN   1

#define MPIF_R_LC3B_MIUSEL_ADDR 0x13
#define MPIF_R_LC3B_MIUSEL_OFFSET 9
#define MPIF_R_LC3B_MIUSEL_LEN  1

#define MPIF_R_LC3B_FMODE_ADDR 7
#define MPIF_R_LC3B_FMODE_OFFSET 10
#define MPIF_R_LC3B_FMODE_LEN  1

/*----------- lc 3b length -----------*/
#define MPIF_R_LC3B_PKTLEN_ADDR  0x14
#define MPIF_R_LC3B_PKTLEN_OFFSET  0
#define MPIF_R_LC3B_PKTLEN_LEN  16

/*----------- lc 3b miu-based addr -----------*/
#define MPIF_R_LC3B_MADR_L_ADDR  0x1d
#define MPIF_R_LC3B_MADR_L_OFFSET 0
#define MPIF_R_LC3B_MADR_L_LEN   16

#define MPIF_R_LC3B_MADR_H_ADDR  0x1e
#define MPIF_R_LC3B_MADR_H_OFFSET 0
#define MPIF_R_LC3B_MADR_H_LEN   9

/*----------- lc 4a control -----------*/
#define MPIF_R_LC4A_CONTROL_ADDR	0x1f

#define MPIF_R_LC4A_VALID_ADDR 0x1f
#define MPIF_R_LC4A_VALID_OFFSET 0
#define MPIF_R_LC4A_VALID_LEN   1

#define MPIF_R_LC4A_RW_ADDR 0x1f
#define MPIF_R_LC4A_RW_OFFSET 1
#define MPIF_R_LC4A_RW_LEN   1

#define MPIF_R_LC4A_SID_ADDR 0x1f
#define MPIF_R_LC4A_SID_OFFSET 2
#define MPIF_R_LC4A_SID_LEN   2

#define MPIF_R_LC4A_RETRX_EN_ADDR 0x1f
#define MPIF_R_LC4A_RETRX_EN_OFFSET 5
#define MPIF_R_LC4A_RETRX_EN_LEN   1

#define MPIF_R_LC4A_RETRX_LIMIT_ADDR 0x1f
#define MPIF_R_LC4A_RETRX_LIMIT_OFFSET  6
#define MPIF_R_LC4A_RETRX_LIMIT_LEN   2

#define MPIF_R_LC4A_MIUSEL_ADDR 0x1f
#define MPIF_R_LC4A_MIUSEL_OFFSET 9
#define MPIF_R_LC4A_MIUSEL_LEN   1

#define MPIF_R_LC4A_GRANULAR_ADDR 0x1f
#define MPIF_R_LC4A_GRANULAR_OFFSET 10
#define MPIF_R_LC4A_GRANULAR_LEN   1

#define MPIF_R_LC4A_WCNT_ADDR 0x1f
#define MPIF_R_LC4A_WCNT_OFFSET 12
#define MPIF_R_LC4A_WCNT_LEN   4

/*----------- lc 4a pkt len -----------*/
#define MPIF_R_LC4A_PKTLEN_ADDR	0x20
#define MPIF_R_LC4A_PKTLEN_OFFSET	0x00
#define MPIF_R_LC4A_PKTLEN_LEN	16

/*----------- lc 4a miu-based addr -----------*/
#define MPIF_R_LC4A_MADR_L_ADDR  0x21
#define MPIF_R_LC4A_MADR_L_OFFSET 0
#define MPIF_R_LC4A_MADR_L_LEN   16

#define MPIF_R_LC4A_MADR_H_ADDR  0x22
#define MPIF_R_LC4A_MADR_H_OFFSET 0
#define MPIF_R_LC4A_MADR_H_LEN   9

/*----------- 4-wire spi control -----------*/
#define MPIF_R_4WSPI_VALID_ADDR  0x23
#define MPIF_R_4WSPI_VALID_OFFSET  0
#define MPIF_R_4WSPI_VALID_LEN   1

#define MPIF_R_4WSPI_RW_ADDR  0x23
#define MPIF_R_4WSPI_RW_OFFSET 1
#define MPIF_R_4WSPI_RW_LEN   1

/*----------- 3-wire spi control -----------*/
#define MPIF_R_3WSPI_VALID_ADDR 0x24
#define MPIF_R_3WSPI_VALID_OFFSET 0
#define MPIF_R_3WSPI_VALID_LEN 1

#define MPIF_R_3WSPI_RW_ADDR  0x24
#define MPIF_R_3WSPI_RW_OFFSET 1
#define MPIF_R_3WSPI_RW_LEN   1

/*----------- channel busy status -----------*/
#define MPIF_R_4WSPI_BUSY_ADDR 0x2b
#define MPIF_R_4WSPI_BUSY_OFFSET 0
#define MPIF_R_4WSPI_BUSY_LEN   1

#define MPIF_R_3WSPI_BUSY_ADDR 0x2b
#define MPIF_R_3WSPI_BUSY_OFFSET 1
#define MPIF_R_3WSPI_BUSY_LEN   1

#define MPIF_R_LC1A_BUSY_ADDR 0x2b
#define MPIF_R_LC1A_BUSY_OFFSET 2
#define MPIF_R_LC1A_BUSY_LEN   1

#define MPIF_R_LC2A_BUSY_ADDR 0x2b
#define MPIF_R_LC2A_BUSY_OFFSET 3
#define MPIF_R_LC2A_BUSY_LEN   1

#define MPIF_R_LC2B_BUSY_ADDR 0x2b
#define MPIF_R_LC2B_BUSY_OFFSET 4
#define MPIF_R_LC2B_BUSY_LEN   1

#define MPIF_R_LC3A_BUSY_ADDR 0x2b
#define MPIF_R_LC3A_BUSY_OFFSET 5
#define MPIF_R_LC3A_BUSY_LEN   1

#define MPIF_R_LC3B_BUSY_ADDR 0x2b
#define MPIF_R_LC3B_BUSY_OFFSET 6
#define MPIF_R_LC3B_BUSY_LEN   1

#define MPIF_R_LC4A_BUSY_ADDR 0x2b
#define MPIF_R_LC4A_BUSY_OFFSET 7
#define MPIF_R_LC4A_BUSY_LEN   1

/*----------- interrupt event mask -----------*/
#define MPIF_R_INTR_EVENT_MASK_ADDR	0x2c

#define MPIF_R_INT_ENABLE_4WSPI_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_4WSPI_TRX_DONE_OFFSET 0
#define MPIF_R_INT_ENABLE_4WSPI_TRX_DONE_LEN   1

#define MPIF_R_INT_ENABLE_3WSPI_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_3WSPI_TRX_DONE_OFFSET 1
#define MPIF_R_INT_ENABLE_3WSPI_TRX_DONE_LEN   1

#define MPIF_R_INT_ENABLE_1A_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_1A_TRX_DONE_OFFSET 2
#define MPIF_R_INT_ENABLE_1A_TRX_DONE_LEN   1

#define MPIF_R_INT_ENABLE_2A_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_2A_TRX_DONE_OFFSET 3
#define MPIF_R_INT_ENABLE_2A_TRX_DONE_LEN 1

#define MPIF_R_INT_ENABLE_2B_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_2B_TRX_DONE_OFFSET 4
#define MPIF_R_INT_ENABLE_2B_TRX_DONE_LEN 1

#define MPIF_R_INT_ENABLE_3A_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_3A_TRX_DONE_OFFSET 5
#define MPIF_R_INT_ENABLE_3A_TRX_DONE_LEN 1

#define MPIF_R_INT_ENABLE_3B_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_3B_TRX_DONE_OFFSET 6
#define MPIF_R_INT_ENABLE_3B_TRX_DONE_LEN 1

#define MPIF_R_INT_ENABLE_4A_TRX_DONE_ADDR 0x2c
#define MPIF_R_INT_ENABLE_4A_TRX_DONE_OFFSET 7
#define MPIF_R_INT_ENABLE_4A_TRX_DONE_LEN 1

#define MPIF_R_INT_ENABLE_2A_TRX_ERROR_ADDR 0x2c
#define MPIF_R_INT_ENABLE_2A_TRX_ERROR_OFFSET 8
#define MPIF_R_INT_ENABLE_2A_TRX_ERROR_LEN 1

#define MPIF_R_INT_ENABLE_2B_TRX_ERROR_ADDR 0x2c
#define MPIF_R_INT_ENABLE_2B_TRX_ERROR_OFFSET 9
#define MPIF_R_INT_ENABLE_2B_TRX_ERROR_LEN 1

#define MPIF_R_INT_ENABLE_3A_TRX_ERROR_ADDR 0x2c
#define MPIF_R_INT_ENABLE_3A_TRX_ERROR_OFFSET 10
#define MPIF_R_INT_ENABLE_3A_TRX_ERROR_LEN 1

#define MPIF_R_INT_ENABLE_3B_TRX_ERROR_ADDR 0x2c
#define MPIF_R_INT_ENABLE_3B_TRX_ERROR_OFFSET 11
#define MPIF_R_INT_ENABLE_3B_TRX_ERROR_LEN 1

#define MPIF_R_INT_ENABLE_4A_TRX_ERROR_ADDR 0x2c
#define MPIF_R_INT_ENABLE_4A_TRX_ERROR_OFFSET 12
#define MPIF_R_INT_ENABLE_4A_TRX_ERROR_LEN 1

/*----------- interrupt event status -----------*/
#define MPIF_R_INT_EVENT_STATUE			0x2d

#define MPIF_R_INT_FLAG_4WSPI_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_4WSPI_TRX_DONE_OFFSET 0
#define MPIF_R_INT_FLAG_4WSPI_TRX_DONE_LEN   1

#define MPIF_R_INT_FLAG_3WSPI_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_3WSPI_TRX_DONE_OFFSET 1
#define MPIF_R_INT_FLAG_3WSPI_TRX_DONE_LEN   1

#define MPIF_R_INT_FLAG_1A_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_1A_TRX_DONE_OFFSET 2
#define MPIF_R_INT_FLAG_1A_TRX_DONE_LEN   1

#define MPIF_R_INT_FLAG_2A_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_2A_TRX_DONE_OFFSET 3
#define MPIF_R_INT_FLAG_2A_TRX_DONE_LEN 1

#define MPIF_R_INT_FLAG_2B_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_2B_TRX_DONE_OFFSET 4
#define MPIF_R_INT_FLAG_2B_TRX_DONE_LEN 1

#define MPIF_R_INT_FLAG_3A_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_3A_TRX_DONE_OFFSET 5
#define MPIF_R_INT_FLAG_3A_TRX_DONE_LEN 1

#define MPIF_R_INT_FLAG_3B_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_3B_TRX_DONE_OFFSET 6
#define MPIF_R_INT_FLAG_3B_TRX_DONE_LEN 1

#define MPIF_R_INT_FLAG_4A_TRX_DONE_ADDR 0x2d
#define MPIF_R_INT_FLAG_4A_TRX_DONE_OFFSET 7
#define MPIF_R_INT_FLAG_4A_TRX_DONE_LEN 1

#define MPIF_R_INT_FLAG_2A_TRX_ERROR_ADDR 0x2d
#define MPIF_R_INT_FLAG_2A_TRX_ERROR_OFFSET 8
#define MPIF_R_INT_FLAG_2A_TRX_ERROR_LEN 1

#define MPIF_R_INT_FLAG_2B_TRX_ERROR_ADDR 0x2d
#define MPIF_R_INT_FLAG_2B_TRX_ERROR_OFFSET 9
#define MPIF_R_INT_FLAG_2B_TRX_ERROR_LEN 1

#define MPIF_R_INT_FLAG_3A_TRX_ERROR_ADDR 0x2d
#define MPIF_R_INT_FLAG_3A_TRX_ERROR_OFFSET 10
#define MPIF_R_INT_FLAG_3A_TRX_ERROR_LEN 1

#define MPIF_R_INT_FLAG_3B_TRX_ERROR_ADDR 0x2d
#define MPIF_R_INT_FLAG_3B_TRX_ERROR_OFFSET 11
#define MPIF_R_INT_FLAG_3B_TRX_ERROR_LEN 1

#define MPIF_R_INT_FLAG_4A_TRX_ERROR_ADDR 0x2d
#define MPIF_R_INT_FLAG_4A_TRX_ERROR_OFFSET 12
#define MPIF_R_INT_FLAG_4A_TRX_ERROR_LEN 1

/*----------- misc -----------*/
#define MPIF_R_MISC	0x30

#define MPIF_R_SWRSTN_ADDR 0x30
#define MPIF_R_SWRSTN_OFFSET 0
#define MPIF_R_SWRSTN_LEN 1

#define MPIF_R_DYNAMIC_GATE_EN_ADDR 0x30
#define MPIF_R_DYNAMIC_GATE_EN_OFFSET 1
#define MPIF_R_DYNAMIC_GATE_EN_LEN 1

#define MPIF_R_TR_CYCLE_ADDR 0x30
#define MPIF_R_TR_CYCLE_OFFSET 2
#define MPIF_R_TR_CYCLE_LEN 2

#define MPIF_R_WAIT_CYCLE_ADDR 0x30
#define MPIF_R_WAIT_CYCLE_OFFSET 4
#define MPIF_R_WAIT_CYCLE_LEN 2

#define MPIF_R_SLV0_DW_ADDR	0x30
#define MPIF_R_SLV0_DW_OFFSET	6
#define MPIF_R_SLV0_DW_LEN	2

#define MPIF_R_SLV1_DW_ADDR	0x30
#define MPIF_R_SLV1_DW_OFFSET	8
#define MPIF_R_SLV1_DW_LEN	2

#define MPIF_R_SLV2_DW_ADDR	0x30
#define MPIF_R_SLV2_DW_OFFSET	10
#define MPIF_R_SLV2_DW_LEN	2

#define MPIF_R_SLV3_DW_ADDR	0x30
#define MPIF_R_SLV3_DW_OFFSET	12
#define MPIF_R_SLV3_DW_LEN	2

#define MPIF_R_CMD_DW_ADDR	0x30
#define MPIF_R_CMD_DW_OFFSET	14
#define MPIF_R_CMD_DW_LEN	2

/*----------- misc2 -----------*/
#define MPIF_R_CLK_INV_ADDR	0x30
#define MPIF_R_CLK_INV_OFFSET	4
#define MPIF_R_CLK_INV_LEN	1

/*
#ifdef __GPS_DUALSTAR_DRV__
typedef struct
{
    u32 REG_LC1A_SETTINGS;                      // h00
    u32 REG_LC2A_REG_CONTROL;                   // h01
    u32 REG_LC2A_REG_ADDRESS;                   // h02
    u32 REG_LC2A_REG_DATA;                      // h03
    u32 REG_LC2B_REG_CONTROL;                   // h04
    u32 REG_LC2B_REG_ADDRESS;                   // h05
    u32 REG_LC2B_REG_DATA;                      // h06
    u32 REG_LC3A_PACKET_CONTROL;                    // h07
    u32 REG_LC3A_PACKET_LENGTH;                 // h08
    u32 REG_LC3A_PACKET_DATA[8];                // h09-h10
    u32 REG_LC3A_PACKET_MIU_BASE_ADDRESS_L;     // h11
    u32 REG_LC3A_PACKET_MIU_BASE_ADDRESS_H;     // h12
    u32 REG_LC3B_PACKET_CONTROL;                // h13
    u32 REG_LC3B_PACKET_LENGTH;                 // h14
    u32 REG_LC3B_PACKET_DATA[8];                // h15-h1C
    u32 REG_LC3B_PACKET_MIU_BASE_ADDRESS_L;     // h1D
    u32 REG_LC3B_PACKET_MIU_BASE_ADDRESS_H;     // h1E
    u32 REG_LC4A_STREAM_CONTROL;                // h1F
    u32 REG_LC4A_STREAM_LENGTH;                 // h20
    u32 REG_LC4A_STREAM_MIU_BASE_ADDRESS_L;     // h21
    u32 REG_LC4A_STREAM_MIU_BASE_ADDRESS_H;     // h22
    u32 REG_4WIRE_SPI_CONTROL;                  // h23
    u32 REG_3WIRE_SPI_CONTROL;                  // h24
    u32 REG_SPI_CONTROL;                        // h25
    u32 REG_SPI_COMMAND_VALUE_L;                // h26
    u32 REG_SPI_COMMAND_VALUE_H;                // h27
    u32 REG_SPI_DATA_LENGTH;                    // h28
    u32 REG_SPI_MIU_BASE_ADDRESS_L;             // h29
    u32 REG_SPI_MIU_BASE_ADDRESS_H;             // h2A
    u32 REG_CHANNEL_BUSY_STATUS;                    // h2B
    u32 REG_INTERRUPT_EVENT_MASK;               // h2C
    u32 REG_INTERRUPT_EVENT_STATUS;             // h2D
    u32 REG_BUSY_TIMEOUT_COUNTER;               // h2E
    u32 REG_BUSY_TIMEOUT_TO;                        // h2F
    u32 REG_MISC1;                                  // h30
    u32 REG_MISC2;                              // h31
#ifdef BIG2
    u32 REG_MISC3;                              // h32
    u32 REG_SYNC_CONTROL;                       // h33
#endif
    u32 REG_SPI_UCPLT_LENGTH;                   // h34      // h32
#ifdef BIG2
    u32 REG_MIU_WRITE_PROTECTION[5];                // h35~h39
    u32 REG_DUMMY[6];                           // h3A~h3F
#endif
    u32 REG_DEBUG_SELECTION;                    // h40      // h33
    u32 REG_DEBUG_CHECKSUM_L;                   // h41      // h34
    u32 REG_DEBUG_CHECKSUM_H;                   // h42      // h35
    u32 REG_DEBUG_STS_IF_CTRL0;                 // h43      // h36
    u32 REG_DEBUG_STS_IF_CTRL1;                 // h44      // h37
    u32 REG_DEBUG_STS_PKT3A_CNT;                // h45      // h38
    u32 REG_DEBUG_STS_PKT3B_CNT;                // h46      // h39
    u32 REG_DEBUG_STS_STM0_CNT;                 // h47      // h3A
    u32 REG_DEBUG_STS_LC2X_CNT;                 // h48      // h3B
    u32 REG_DEBUG_STS_LC3X_CNT;                 // h49      // h3C
    u32 REG_DEBUG_STS_LC4X_CNT;                 // h4A      // h3D
#ifdef BIG2
    u32 REG_DEBUG_BITFAIL;                      // h4B
    u32 REG_DEBUG_RECORD;                       // h4C
#endif
} REG_MPIF_st, *PREG_MPIF_st;
#endif
*/
/***************************************************************
*
*	slave register file
*
***************************************************************/

/* manually added */
#define SPIF_R_LC1A_RESET_ADDR		0x0
#define SPIF_R_LC1A_RESET_LEN		1
#define SPIF_R_LC1A_RESET_OFFSET		7

/* manually added */
#define SPIF_R_LC1A_DSTSEL_ADDR		0x1
#define SPIF_R_LC1A_DSTSEL_LEN		1
#define SPIF_R_LC1A_DSTSEL_OFFSET		0

#define SPIF_R_LC1A_DSTSEL2_ADDR                        0x2
#define SPIF_R_LC1A_DSTSEL2_LEN                         1
#define SPIF_R_LC1A_DSTSEL2_OFFSET                      0

#define SPIF_R_LC1A_MIU_POLLING_ENABLE_ADDR     0x6
#define SPIF_R_LC1A_MIU_POLLING_ENABLE_LEN      2
#define SPIF_R_LC1A_MIU_POLLING_ENABLE_OFFSET   0
#define SPIF_R_LC1A_MIU_POLLING_ENABLE  0x1

#define SPIF_R_LC1A_MIU_WRITE_DONE_ADDR     0x7
#define SPIF_R_LC1A_MIU_WRITE_DONE_LEN      1
#define SPIF_R_LC1A_MIU_WRITE_DONE_OFFSET   0

#define SPIF_R_LC1A_XIU_WRITE_DONE_ADDR     0x7
#define SPIF_R_LC1A_XIU_WRITE_DONE_LEN      1
#define SPIF_R_LC1A_XIU_WRITE_DONE_OFFSET   1

/************************************************
 *		 Logical Channel 1a (Setting/Status)
 ************************************************/

/*----- register reg0 -----*/
#define SPIF_R_REG0_ADDR	0x00

#define SPIF_R_SPIF_1A_IDX0_ADDR	0x00
#define SPIF_R_SPIF_1A_IDX0_LEN	8
#define SPIF_R_SPIF_1A_IDX0_OFFSET	0


/*----- register reg1 -----*/
#define SPIF_R_REG1_ADDR	0x01

#define SPIF_R_SPIF_1A_IDX1_ADDR	0x01
#define SPIF_R_SPIF_1A_IDX1_LEN	8
#define SPIF_R_SPIF_1A_IDX1_OFFSET	0


/*----- register reg2 -----*/
#define SPIF_R_REG2_ADDR	0x02

#define SPIF_R_SPIF_1A_IDX2_ADDR	0x02
#define SPIF_R_SPIF_1A_IDX2_LEN	8
#define SPIF_R_SPIF_1A_IDX2_OFFSET	0


/*----- register reg3 -----*/
#define SPIF_R_REG3_ADDR	0x03

#define SPIF_R_SPIF_1A_IDX3_ADDR	0x03
#define SPIF_R_SPIF_1A_IDX3_LEN	8
#define SPIF_R_SPIF_1A_IDX3_OFFSET	0


/*----- register reg4 -----*/
#define SPIF_R_REG4_ADDR	0x04

#define SPIF_R_SPIF_1A_IDX4_ADDR	0x04
#define SPIF_R_SPIF_1A_IDX4_LEN	8
#define SPIF_R_SPIF_1A_IDX4_OFFSET	0


/*----- register reg5 -----*/
#define SPIF_R_REG5_ADDR	0x05

#define SPIF_R_SPIF_1A_IDX5_ADDR	0x05
#define SPIF_R_SPIF_1A_IDX5_LEN	8
#define SPIF_R_SPIF_1A_IDX5_OFFSET	0


/*----- register reg6 -----*/
#define SPIF_R_REG6_ADDR	0x06

#define SPIF_R_SPIF_1A_IDX6_ADDR	0x06
#define SPIF_R_SPIF_1A_IDX6_LEN	8
#define SPIF_R_SPIF_1A_IDX6_OFFSET	0


/*----- register reg7 -----*/
#define SPIF_R_REG7_ADDR	0x07

#define SPIF_R_SPIF_1A_IDX7_ADDR	0x07
#define SPIF_R_SPIF_1A_IDX7_LEN	8
#define SPIF_R_SPIF_1A_IDX7_OFFSET	0


/*----- register reg8 -----*/
#define SPIF_R_REG8_ADDR	0x08

#define SPIF_R_SPIF_1A_IDX_ADDR	0x08
#define SPIF_R_SPIF_1A_IDX_LEN	3
#define SPIF_R_SPIF_1A_IDX_OFFSET	0

#define SPIF_R_SPIF_1A_RW_ADDR	0x08
#define SPIF_R_SPIF_1A_RW_LEN	1
#define SPIF_R_SPIF_1A_RW_OFFSET	4



/************************************************
 *		 Logical Channel 2a (register)
 ************************************************/

/*----- register reg16 -----*/
#define SPIF_R_REG16_ADDR	0x10

#define SPIF_R_SPIF_2A_MB0_ADDR	0x10
#define SPIF_R_SPIF_2A_MB0_LEN	16
#define SPIF_R_SPIF_2A_MB0_OFFSET	0


/*----- register reg17 -----*/
#define SPIF_R_REG17_ADDR	0x11

#define SPIF_R_SPIF_2A_MB1_ADDR	0x11
#define SPIF_R_SPIF_2A_MB1_LEN	16
#define SPIF_R_SPIF_2A_MB1_OFFSET	0


/*----- register reg18 -----*/
#define SPIF_R_REG18_ADDR	0x12

#define SPIF_R_SPIF_2A_MB2_ADDR	0x12
#define SPIF_R_SPIF_2A_MB2_LEN	16
#define SPIF_R_SPIF_2A_MB2_OFFSET	0


/*----- register reg19 -----*/
#define SPIF_R_REG19_ADDR	0x13

#define SPIF_R_SPIF_2A_MB3_ADDR	0x13
#define SPIF_R_SPIF_2A_MB3_LEN	16
#define SPIF_R_SPIF_2A_MB3_OFFSET	0


/*----- register reg20 -----*/
#define SPIF_R_REG20_ADDR	0x14

#define SPIF_R_SPIF_2A_MB4_ADDR	0x14
#define SPIF_R_SPIF_2A_MB4_LEN	16
#define SPIF_R_SPIF_2A_MB4_OFFSET	0


/*----- register reg21 -----*/
#define SPIF_R_REG21_ADDR	0x15

#define SPIF_R_SPIF_2A_MB5_ADDR	0x15
#define SPIF_R_SPIF_2A_MB5_LEN	16
#define SPIF_R_SPIF_2A_MB5_OFFSET	0


/*----- register reg22 -----*/
#define SPIF_R_REG22_ADDR	0x16

#define SPIF_R_SPIF_2A_MB6_ADDR	0x16
#define SPIF_R_SPIF_2A_MB6_LEN	16
#define SPIF_R_SPIF_2A_MB6_OFFSET	0


/*----- register reg23 -----*/
#define SPIF_R_REG23_ADDR	0x17

#define SPIF_R_SPIF_2A_MB7_ADDR	0x17
#define SPIF_R_SPIF_2A_MB7_LEN	16
#define SPIF_R_SPIF_2A_MB7_OFFSET	0


/*----- register reg24 -----*/
#define SPIF_R_REG24_ADDR	0x18

#define SPIF_R_SPIF_2A_ADDR_ADDR	0x18
#define SPIF_R_SPIF_2A_ADDR_LEN	16
#define SPIF_R_SPIF_2A_ADDR_OFFSET	0


/*----- register reg25 -----*/
#define SPIF_R_REG25_ADDR	0x19

#define SPIF_R_SPIF_2A_RW_ADDR	0x19
#define SPIF_R_SPIF_2A_RW_LEN	1
#define SPIF_R_SPIF_2A_RW_OFFSET	0



/************************************************
 *		 Logical Channel 2b (register)
 ************************************************/

/*----- register reg32 -----*/
#define SPIF_R_REG32_ADDR	0x20

#define SPIF_R_SPIF_2B_MB0_ADDR	0x20
#define SPIF_R_SPIF_2B_MB0_LEN	16
#define SPIF_R_SPIF_2B_MB0_OFFSET	0


/*----- register reg33 -----*/
#define SPIF_R_REG33_ADDR	0x21

#define SPIF_R_SPIF_2B_MB1_ADDR	0x21
#define SPIF_R_SPIF_2B_MB1_LEN	16
#define SPIF_R_SPIF_2B_MB1_OFFSET	0


/*----- register reg34 -----*/
#define SPIF_R_REG34_ADDR	0x22

#define SPIF_R_SPIF_2B_MB2_ADDR	0x22
#define SPIF_R_SPIF_2B_MB2_LEN	16
#define SPIF_R_SPIF_2B_MB2_OFFSET	0


/*----- register reg35 -----*/
#define SPIF_R_REG35_ADDR	0x23

#define SPIF_R_SPIF_2B_MB3_ADDR	0x23
#define SPIF_R_SPIF_2B_MB3_LEN	16
#define SPIF_R_SPIF_2B_MB3_OFFSET	0


/*----- register reg36 -----*/
#define SPIF_R_REG36_ADDR	0x24

#define SPIF_R_SPIF_2B_MB4_ADDR	0x24
#define SPIF_R_SPIF_2B_MB4_LEN	16
#define SPIF_R_SPIF_2B_MB4_OFFSET	0


/*----- register reg37 -----*/
#define SPIF_R_REG37_ADDR	0x25

#define SPIF_R_SPIF_2B_MB5_ADDR	0x25
#define SPIF_R_SPIF_2B_MB5_LEN	16
#define SPIF_R_SPIF_2B_MB5_OFFSET	0


/*----- register reg38 -----*/
#define SPIF_R_REG38_ADDR	0x26

#define SPIF_R_SPIF_2B_MB6_ADDR	0x26
#define SPIF_R_SPIF_2B_MB6_LEN	16
#define SPIF_R_SPIF_2B_MB6_OFFSET	0


/*----- register reg39 -----*/
#define SPIF_R_REG39_ADDR	0x27

#define SPIF_R_SPIF_2B_MB7_ADDR	0x27
#define SPIF_R_SPIF_2B_MB7_LEN	16
#define SPIF_R_SPIF_2B_MB7_OFFSET	0


/*----- register reg40 -----*/
#define SPIF_R_REG40_ADDR	0x28

#define SPIF_R_SPIF_2B_ADDR_ADDR	0x28
#define SPIF_R_SPIF_2B_ADDR_LEN	16
#define SPIF_R_SPIF_2B_ADDR_OFFSET	0


/*----- register reg41 -----*/
#define SPIF_R_REG41_ADDR	0x29

#define SPIF_R_SPIF_2B_RW_ADDR	0x29
#define SPIF_R_SPIF_2B_RW_LEN	1
#define SPIF_R_SPIF_2B_RW_OFFSET	0



/************************************************
 *		 Logical Channel 3a (packet)
 ************************************************/

/*----- register reg48 -----*/
#define SPIF_R_REG48_ADDR	0x30

#define SPIF_R_SPIF_3A_RW_ADDR	0x30
#define SPIF_R_SPIF_3A_RW_LEN	1
#define SPIF_R_SPIF_3A_RW_OFFSET	0

#define SPIF_R_SPIF_3A_CHK_ADDR	0x30
#define SPIF_R_SPIF_3A_CHK_LEN	1
#define SPIF_R_SPIF_3A_CHK_OFFSET	1

#define SPIF_R_SPIF_3A_DSTSEL_ADDR	0x30
#define SPIF_R_SPIF_3A_DSTSEL_LEN	1
#define SPIF_R_SPIF_3A_DSTSEL_OFFSET	2

#define SPIF_R_SPIF_3A_MIU_PREFETCH_ADDR	0x30
#define SPIF_R_SPIF_3A_MIU_PREFETCH_LEN	1
#define SPIF_R_SPIF_3A_MIU_PREFETCH_OFFSET	3


/*----- register reg49 -----*/
#define SPIF_R_REG49_ADDR	0x31

#define SPIF_R_SPIF_3A_CHKSUM_ADDR	0x31
#define SPIF_R_SPIF_3A_CHKSUM_LEN	16
#define SPIF_R_SPIF_3A_CHKSUM_OFFSET	0


/*----- register reg50 -----*/
#define SPIF_R_REG50_ADDR	0x32

#define SPIF_R_SPIF_3A_PKTLEN_ADDR	0x32
#define SPIF_R_SPIF_3A_PKTLEN_LEN	16
#define SPIF_R_SPIF_3A_PKTLEN_OFFSET	0


/*----- register reg51 -----*/
#define SPIF_R_REG51_ADDR	0x33

#define SPIF_R_SPIF_3A_MADR_ADDR	0x33
#define SPIF_R_SPIF_3A_MADR_LEN	    25
#define SPIF_R_SPIF_3A_MADR_OFFSET	0



/************************************************
 *		 Logical Channel 3b (packet)
 ************************************************/

/*----- register reg64 -----*/
#define SPIF_R_REG64_ADDR	0x40

#define SPIF_R_SPIF_3B_RW_ADDR	0x40
#define SPIF_R_SPIF_3B_RW_LEN	1
#define SPIF_R_SPIF_3B_RW_OFFSET	0

#define SPIF_R_SPIF_3B_CHK_ADDR	0x40
#define SPIF_R_SPIF_3B_CHK_LEN	1
#define SPIF_R_SPIF_3B_CHK_OFFSET	1

#define SPIF_R_SPIF_3B_DSTSEL_ADDR	0x40
#define SPIF_R_SPIF_3B_DSTSEL_LEN	1
#define SPIF_R_SPIF_3B_DSTSEL_OFFSET	2

#define SPIF_R_SPIF_3B_MIU_PREFETCH_ADDR	0x40
#define SPIF_R_SPIF_3B_MIU_PREFETCH_LEN	1
#define SPIF_R_SPIF_3B_MIU_PREFETCH_OFFSET	3


/*----- register reg65 -----*/
#define SPIF_R_REG65_ADDR	0x41

#define SPIF_R_SPIF_3B_CHKSUM_ADDR	0x41
#define SPIF_R_SPIF_3B_CHKSUM_LEN	16
#define SPIF_R_SPIF_3B_CHKSUM_OFFSET	0


/*----- register reg66 -----*/
#define SPIF_R_REG66_ADDR	0x42

#define SPIF_R_SPIF_3B_PKTLEN_ADDR	0x42
#define SPIF_R_SPIF_3B_PKTLEN_LEN	16
#define SPIF_R_SPIF_3B_PKTLEN_OFFSET	0


/*----- register reg67 -----*/
#define SPIF_R_REG67_ADDR	0x43

#define SPIF_R_SPIF_3B_MADR_ADDR	0x43
#define SPIF_R_SPIF_3B_MADR_LEN	    25
#define SPIF_R_SPIF_3B_MADR_OFFSET	0



/************************************************
 *		 Logical Channel 4a (stream) control
 ************************************************/

/*----- register reg80 -----*/
#define SPIF_R_REG80_ADDR	0x50

#define SPIF_R_SPIF_4A_RW_ADDR	0x50
#define SPIF_R_SPIF_4A_RW_LEN	1
#define SPIF_R_SPIF_4A_RW_OFFSET	0

#define SPIF_R_SPIF_4A_GRANULAR_ADDR	0x50
#define SPIF_R_SPIF_4A_GRANULAR_LEN	2
#define SPIF_R_SPIF_4A_GRANULAR_OFFSET	1

#define SPIF_R_SPIF_4A_MIU_PREFETCH_ADDR	0x50
#define SPIF_R_SPIF_4A_MIU_PREFETCH_LEN	1
#define SPIF_R_SPIF_4A_MIU_PREFETCH_OFFSET	3

/* HANDLE MANUALLY: 52 51 16 SPIF_4A_CRC  */

/*----- register reg83 -----*/
#define SPIF_R_REG83_ADDR	0x53

#define SPIF_R_SPIF_4A_STMLEN_ADDR	0x53
#define SPIF_R_SPIF_4A_STMLEN_LEN	16
#define SPIF_R_SPIF_4A_STMLEN_OFFSET	0

/* HANDLE MANUALLY: 55 54 16 SPIF_4A_MADR  */

/*----- register reg84 -----*/
#define SPIF_R_REG84_ADDR	0x54

#define SPIF_R_SPIF_4A_MADR_ADDR	0x54
#define SPIF_R_SPIF_4A_MADR_LEN	25
#define SPIF_R_SPIF_4A_MADR_OFFSET	0


/************************************************
 *		 Interrupt status/mask/clear
 ************************************************/

/*----- register reg96 -----*/
#define SPIF_R_REG96_ADDR	0x60

#define SPIF_R_SPIF_INT_MSK_ADDR	0x60
#define SPIF_R_SPIF_INT_MSK_LEN	16
#define SPIF_R_SPIF_INT_MSK_OFFSET	0


/*----- register reg97 -----*/
#define SPIF_R_REG97_ADDR	0x61

#define SPIF_R_SPIF_INT_CLR_ADDR	0x61
#define SPIF_R_SPIF_INT_CLR_LEN	16
#define SPIF_R_SPIF_INT_CLR_OFFSET	0


/*----- register reg98 -----*/
#define SPIF_R_REG98_ADDR	0x62

#define SPIF_R_SPIF_INT_FRC_ADDR	0x62
#define SPIF_R_SPIF_INT_FRC_LEN	16
#define SPIF_R_SPIF_INT_FRC_OFFSET	0


/*----- register reg99 -----*/
#define SPIF_R_REG99_ADDR	0x63

#define SPIF_R_SPIF_INT_RAW_STS_ADDR	0x63
#define SPIF_R_SPIF_INT_RAW_STS_LEN	16
#define SPIF_R_SPIF_INT_RAW_STS_OFFSET	0


/*----- register reg100 -----*/
#define SPIF_R_REG100_ADDR	0x64

#define SPIF_R_SPIF_INT_FINAL_STS_ADDR	0x64
#define SPIF_R_SPIF_INT_FINAL_STS_LEN	16
#define SPIF_R_SPIF_INT_FINAL_STS_OFFSET	0


/*----- register reg101 -----*/
#define SPIF_R_REG101_ADDR	0x65

#define SPIF_R_SPIF_LA_BUSY_ADDR	0x65
#define SPIF_R_SPIF_LA_BUSY_LEN	1
#define SPIF_R_SPIF_LA_BUSY_OFFSET	0

#define SPIF_R_SPIF_2A_BUSY_ADDR	0x65
#define SPIF_R_SPIF_2A_BUSY_LEN	1
#define SPIF_R_SPIF_2A_BUSY_OFFSET	1

#define SPIF_R_SPIF_2B_BUSY_ADDR	0x65
#define SPIF_R_SPIF_2B_BUSY_LEN	1
#define SPIF_R_SPIF_2B_BUSY_OFFSET	2

#define SPIF_R_SPIF_3A_BUSY_ADDR	0x65
#define SPIF_R_SPIF_3A_BUSY_LEN	1
#define SPIF_R_SPIF_3A_BUSY_OFFSET	3

#define SPIF_R_SPIF_3B_BUSY_ADDR	0x65
#define SPIF_R_SPIF_3B_BUSY_LEN	1
#define SPIF_R_SPIF_3B_BUSY_OFFSET	4

#define SPIF_R_SPIF_4A_BUSY_ADDR	0x65
#define SPIF_R_SPIF_4A_BUSY_LEN	1
#define SPIF_R_SPIF_4A_BUSY_OFFSET	5



/************************************************
 *		 Misc
 ************************************************/

/*----- register reg112 -----*/
#define SPIF_R_REG112_ADDR	0x70

#define SPIF_R_SPIF_SWRSTN_ADDR	0x70
#define SPIF_R_SPIF_SWRSTN_LEN	1
#define SPIF_R_SPIF_SWRSTN_OFFSET	0

#define SPIF_R_SPIF_DYNAMIC_GATE_EN_ADDR	0x70
#define SPIF_R_SPIF_DYNAMIC_GATE_EN_LEN	1
#define SPIF_R_SPIF_DYNAMIC_GATE_EN_OFFSET	1


/*----- register reg113 -----*/
#define SPIF_R_REG113_ADDR	0x71

#define SPIF_R_SPIF_ID_ADDR	0x71
#define SPIF_R_SPIF_ID_LEN	2
#define SPIF_R_SPIF_ID_OFFSET	0

#define SPIF_R_SPIF_CW_ADDR	0x71
#define SPIF_R_SPIF_CW_LEN	2
#define SPIF_R_SPIF_CW_OFFSET	4

#define SPIF_R_SPIF_DW_ADDR	0x71
#define SPIF_R_SPIF_DW_LEN	2
#define SPIF_R_SPIF_DW_OFFSET	6

#define SPIF_R_SPIF_TR_CNT_ADDR	0x71
#define SPIF_R_SPIF_TR_CNT_LEN	2
#define SPIF_R_SPIF_TR_CNT_OFFSET	8

#define SPIF_R_SPIF_WT_CNT_ADDR	0x71
#define SPIF_R_SPIF_WT_CNT_LEN	2
#define SPIF_R_SPIF_WT_CNT_OFFSET	10


/*----- register reg114 -----*/
#define SPIF_R_REG114_ADDR	0x72

#define SPIF_R_PIF_CLK_DLY_ADDR	0x72
#define SPIF_R_PIF_CLK_DLY_LEN	4
#define SPIF_R_PIF_CLK_DLY_OFFSET	0

#define SPIF_R_PIF_CLK_INV_ADDR	0x72
#define SPIF_R_PIF_CLK_INV_LEN	1
#define SPIF_R_PIF_CLK_INV_OFFSET	4

#define SPIF_R_PIF_CLK_INV_DLY_ADDR	0x72
#define SPIF_R_PIF_CLK_INV_DLY_LEN	4
#define SPIF_R_PIF_CLK_INV_DLY_OFFSET	8

#define SPIF_R_PIF_CLK_INV_INV_ADDR	0x72
#define SPIF_R_PIF_CLK_INV_INV_LEN	1
#define SPIF_R_PIF_CLK_INV_INV_OFFSET	12


/*----- register reg115 -----*/
#define SPIF_R_REG115_ADDR	0x73

#define SPIF_R_TX_FIFO_OCC_ADDR	0x73
#define SPIF_R_TX_FIFO_OCC_LEN	5
#define SPIF_R_TX_FIFO_OCC_OFFSET	0

#define SPIF_R_TX_FIFO_VAC_ADDR	0x73
#define SPIF_R_TX_FIFO_VAC_LEN	5
#define SPIF_R_TX_FIFO_VAC_OFFSET	8


/*----- register reg116 -----*/
#define SPIF_R_REG116_ADDR	0x74

#define SPIF_R_RX_FIFO_OCC_ADDR	0x74
#define SPIF_R_RX_FIFO_OCC_LEN	5
#define SPIF_R_RX_FIFO_OCC_OFFSET	0

#define SPIF_R_RX_FIFO_VAC_ADDR	0x74
#define SPIF_R_RX_FIFO_VAC_LEN	5
#define SPIF_R_RX_FIFO_VAC_OFFSET	8


/*----- register reg117 -----*/
#define SPIF_R_REG117_ADDR	0x75

#define SPIF_R_TX_FIFO_FULL_ADDR	0x75
#define SPIF_R_TX_FIFO_FULL_LEN	1
#define SPIF_R_TX_FIFO_FULL_OFFSET	0

#define SPIF_R_TX_FIFO_EMPTY_ADDR	0x75
#define SPIF_R_TX_FIFO_EMPTY_LEN	1
#define SPIF_R_TX_FIFO_EMPTY_OFFSET	1

#define SPIF_R_RX_FIFO_FULL_ADDR	0x75
#define SPIF_R_RX_FIFO_FULL_LEN	1
#define SPIF_R_RX_FIFO_FULL_OFFSET	2

#define SPIF_R_RX_FIFO_EMPTY_ADDR	0x75
#define SPIF_R_RX_FIFO_EMPTY_LEN	1
#define SPIF_R_RX_FIFO_EMPTY_OFFSET	3


/*----- register reg118 -----*/
#define SPIF_R_REG118_ADDR	0x76

#define SPIF_R_TEST_NAK_ADDR	0x76
#define SPIF_R_TEST_NAK_LEN	1
#define SPIF_R_TEST_NAK_OFFSET	0

#define SPIF_R_TEST_ZERO_CHKSUM_ADDR	0x76
#define SPIF_R_TEST_ZERO_CHKSUM_LEN	1
#define SPIF_R_TEST_ZERO_CHKSUM_OFFSET	1

#define SPIF_R_TEST_ZERO_CRC_ADDR	0x76
#define SPIF_R_TEST_ZERO_CRC_LEN	1
#define SPIF_R_TEST_ZERO_CRC_OFFSET	2

#define SPIF_R_RX_FIFO_PREFULL_THLD_ADDR	0x76
#define SPIF_R_RX_FIFO_PREFULL_THLD_LEN	5
#define SPIF_R_RX_FIFO_PREFULL_THLD_OFFSET	8

/* HANDLE MANUALLY: 78 77 24 DBG_SPIF  */

/*----- register reg121 -----*/
#define SPIF_R_REG121_ADDR	0x79

#define SPIF_R_LC3A_W_PKTLEN_DWNCNT_ADDR	0x79
#define SPIF_R_LC3A_W_PKTLEN_DWNCNT_LEN	16
#define SPIF_R_LC3A_W_PKTLEN_DWNCNT_OFFSET	0


/*----- register reg122 -----*/
#define SPIF_R_REG122_ADDR	0x7a

#define SPIF_R_LC3A_R_PKTLEN_DWNCNT_ADDR	0x7a
#define SPIF_R_LC3A_R_PKTLEN_DWNCNT_LEN	16
#define SPIF_R_LC3A_R_PKTLEN_DWNCNT_OFFSET	0


/*----- register reg123 -----*/
#define SPIF_R_REG123_ADDR	0x7b

#define SPIF_R_LC3B_W_PKTLEN_DWNCNT_ADDR	0x7b
#define SPIF_R_LC3B_W_PKTLEN_DWNCNT_LEN	16
#define SPIF_R_LC3B_W_PKTLEN_DWNCNT_OFFSET	0


/*----- register reg124 -----*/
#define SPIF_R_REG124_ADDR	0x7c

#define SPIF_R_LC3B_R_PKTLEN_DWNCNT_ADDR	0x7c
#define SPIF_R_LC3B_R_PKTLEN_DWNCNT_LEN	16
#define SPIF_R_LC3B_R_PKTLEN_DWNCNT_OFFSET	0


/*----- register reg125 -----*/
#define SPIF_R_REG125_ADDR	0x7d

#define SPIF_R_LC4A_W_STMLEN_DWNCNT_ADDR	0x7d
#define SPIF_R_LC4A_W_STMLEN_DWNCNT_LEN	16
#define SPIF_R_LC4A_W_STMLEN_DWNCNT_OFFSET	0


/*----- register reg126 -----*/
#define SPIF_R_REG126_ADDR	0x7e

#define SPIF_R_LC4A_R_STMLEN_DWNCNT_ADDR	0x7e
#define SPIF_R_LC4A_R_STMLEN_DWNCNT_LEN	16
#define SPIF_R_LC4A_R_STMLEN_DWNCNT_OFFSET	0


/*----- register reg127 -----*/
#define SPIF_R_REG127_ADDR	0x7f

#define SPIF_R_SPIF_PREBSY_BITNUM_ADDR	0x7f
#define SPIF_R_SPIF_PREBSY_BITNUM_LEN	3
#define SPIF_R_SPIF_PREBSY_BITNUM_OFFSET	0

#define SPIF_R_SPIF_PREBSY_BYTENUM_ADDR	0x7f
#define SPIF_R_SPIF_PREBSY_BYTENUM_LEN	3
#define SPIF_R_SPIF_PREBSY_BYTENUM_OFFSET	4

#define SPIF_R_SPIF_CMD_PREBSY_EN_ADDR	0x7f
#define SPIF_R_SPIF_CMD_PREBSY_EN_LEN	1
#define SPIF_R_SPIF_CMD_PREBSY_EN_OFFSET	7

#define SPIF_R_SPIF_WWTR_CNT_ADDR	0x7f
#define SPIF_R_SPIF_WWTR_CNT_LEN	2
#define SPIF_R_SPIF_WWTR_CNT_OFFSET	8

#define SPIF_R_SPIF_CMD_PREBSY_BITNUM_ADDR	0x7f
#define SPIF_R_SPIF_CMD_PREBSY_BITNUM_LEN	2
#define SPIF_R_SPIF_CMD_PREBSY_BITNUM_OFFSET	10

#define SPIF_R_SPIF_PREBSY_WAIT_CNT_ADDR	0x7f
#define SPIF_R_SPIF_PREBSY_WAIT_CNT_LEN	3
#define SPIF_R_SPIF_PREBSY_WAIT_CNT_OFFSET	12

#define SPIF_R_SPIF_PREBSY_EN_ADDR	0x7f
#define SPIF_R_SPIF_PREBSY_EN_LEN	1
#define SPIF_R_SPIF_PREBSY_EN_OFFSET	15


/************************************************************************
 * Macros
 ************************************************************************/
/* Cache manipulation */
#define SPIF_R_MASK(reg)	((UINT32)(((1 << SPIF_R_##reg##_LEN) - 1) << (SPIF_R_##reg##_OFFSET)))

#define SPIF_R_INIT_CACHE(cache)	(cache = 0)

#define SPIF_R_READ_CACHE(cache, reg, val)	do { \
								val = (U32) ((cache & SPIF_R_MASK(reg)) >> SPIF_R_##reg##_OFFSET); \
							} while (0)

#define SPIF_R_WRITE_CACHE(cache, reg, val)	do { \
									cache &= ~SPIF_R_MASK(reg); \
									cache |= (((UINT32)val <<  SPIF_R_##reg##_OFFSET) & SPIF_R_MASK(reg)); \
								} while(0)


/************************************************************************
 * Data type
 ************************************************************************/


/************************************************************************
 * Extern Global Variable
 ************************************************************************/


/************************************************************************
 * Extern Global Function
 ************************************************************************/


#endif /* #ifndef __PIF_REG_PUB_H__ */

