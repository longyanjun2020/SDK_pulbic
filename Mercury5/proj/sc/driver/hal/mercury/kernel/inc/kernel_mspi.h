/*
 * kernel_mspi.h
 *
 *  Created on: 2017/8/9
 *      Author: titan.huang
 */

#ifndef _KERNEL_MSPI_H_
#define _KERNEL_MSPI_H_


#define MSPI0_BANK_ADDR		0x111000
#define MSPI1_BANK_ADDR		0x111100
#define MSPI2_BANK_ADDR		0x111200
#define CLK_BANK_ADDR		0x103800
#define CHIPTOP_BANK_ADDR 	0x101E00

//-------------------------------------------------------------------------------------------------
//  Hardware Register Capability
//-------------------------------------------------------------------------------------------------
#define MSPI_WRITE_BUF_OFFSET          0x40
#define MSPI_READ_BUF_OFFSET           0x44
#define MSPI_WBF_SIZE_OFFSET           0x48
#define MSPI_RBF_SIZE_OFFSET           0x48
    // read/ write buffer size
    #define MSPI_RWSIZE_MASK               0xFF
    #define MSPI_RSIZE_BIT_OFFSET          0x8
    #define MAX_READ_BUF_SIZE              0x8
    #define MAX_WRITE_BUF_SIZE             0x8
// CLK config
#define MSPI_CTRL_OFFSET               0x49
#define MSPI_CLK_CLOCK_OFFSET          0x49
    #define MSPI_CLK_CLOCK_BIT_OFFSET      0x08
    #define MSPI_CLK_CLOCK_MASK            0xFF
    #define MSPI_CLK_PHASE_MASK            0x40
    #define MSPI_CLK_PHASE_BIT_OFFSET      0x06
    #define MSPI_CLK_POLARITY_MASK         0x80
	#define MSPI_CLK_POLARITY_BIT_OFFSET   0x07
    #define MSPI_CLK_PHASE_MAX             0x1
    #define MSPI_CLK_POLARITY_MAX          0x1
    #define MSPI_CLK_CLOCK_MAX             0x7
// DC config
#define MSPI_DC_MASK                   0xFF
#define MSPI_DC_BIT_OFFSET             0x08
#define MSPI_DC_TR_START_OFFSET        0x4A
    #define MSPI_DC_TRSTART_MAX            0xFF
#define MSPI_DC_TR_END_OFFSET          0x4A
    #define MSPI_DC_TREND_MAX              0xFF
#define MSPI_DC_TB_OFFSET              0x4B
    #define MSPI_DC_TB_MAX                 0xFF
#define MSPI_DC_TRW_OFFSET             0x4B
    #define MSPI_DC_TRW_MAX                0xFF
// Frame Config
#define MSPI_FRAME_WBIT_OFFSET         0x4C
#define MSPI_FRAME_RBIT_OFFSET         0x4E
    #define MSPI_FRAME_BIT_MAX             0x07
    #define MSPI_FRAME_BIT_MASK            0x07
    #define MSPI_FRAME_BIT_FIELD           0x03
#define MSPI_LSB_FIRST_OFFSET          0x50
#define MSPI_TRIGGER_OFFSET            0x5A
#define MSPI_DONE_OFFSET               0x5B
#define MSPI_DONE_CLEAR_OFFSET         0x5C
#define MSPI_CHIP_SELECT_OFFSET        0x5F

#define MSPI_FULL_DEPLUX_RD00 (0x78)
#define MSPI_FULL_DEPLUX_RD01 (0x78)
#define MSPI_FULL_DEPLUX_RD02 (0x79
#define MSPI_FULL_DEPLUX_RD03 (0x79)
#define MSPI_FULL_DEPLUX_RD04 (0x7a)
#define MSPI_FULL_DEPLUX_RD05 (0x7a)
#define MSPI_FULL_DEPLUX_RD06 (0x7b)
#define MSPI_FULL_DEPLUX_RD07 (0x7b)

#define MSPI_FULL_DEPLUX_RD08 (0x7c)
#define MSPI_FULL_DEPLUX_RD09 (0x7c)
#define MSPI_FULL_DEPLUX_RD10 (0x7d)
#define MSPI_FULL_DEPLUX_RD11 (0x7d)
#define MSPI_FULL_DEPLUX_RD12 (0x7e)
#define MSPI_FULL_DEPLUX_RD13 (0x7e)
#define MSPI_FULL_DEPLUX_RD14 (0x7f)
#define MSPI_FULL_DEPLUX_RD15 (0x7f)

//chip select bit map
    #define MSPI_CHIP_SELECT_MAX           0x07
// control bit
#define MSPI_DONE_FLAG                 0x01
#define MSPI_TRIGGER                   0x01
#define MSPI_CLEAR_DONE                0x01
#define MSPI_INT_ENABLE                0x04
#define MSPI_RESET                     0x02
#define MSPI_ENABLE                    0x01

// clk_mspi0
#define MSPI0_CLK_CFG       			0x33
	//bit 0
    #define  MSPI0_CLK_DISABLE      0x01
    #define  MSPI0_CLK_DIS_MASK     0x01
	//bit 2 ~bit 3
    #define  MSPI0_CLK_108M         0x00
    #define  MSPI0_CLK_54M          0x04
    #define  MSPI0_CLK_12M          0x08
    #define  MSPI0_CLK_MASK         0x0C
// clk_mspi1
#define MSPI1_CLK_CFG       			0x33
	//bit 8
    #define  MSPI1_CLK_DISABLE      0x0100
    #define  MSPI1_CLK_DIS_MASK     0x0100
	//bit 10 ~bit 11
    #define  MSPI1_CLK_108M         0x0000
    #define  MSPI1_CLK_54M          0x0400
    #define  MSPI1_CLK_12M          0x0800
    #define  MSPI1_CLK_MASK         0x0C00
// clk_mspi2
#define MSPI2_CLK_CFG                   0x3a
	//bit 0
    #define  MSPI2_CLK_DISABLE      0x01
    #define  MSPI2_CLK_DIS_MASK     0x01
	//bit 2 ~bit 3
    #define  MSPI2_CLK_108M         0x00
    #define  MSPI2_CLK_54M          0x04
    #define  MSPI2_CLK_12M          0x08
    #define  MSPI2_CLK_MASK         0x0C

//CHITOP 101E mspi mode select
#define MSPI0_MODE          0x0C //bit0~bit2
    #define MSPI0_MODE_MASK 0x07
#define MSPI1_MODE          0x0C //bit4~bit6
    #define MSPI1_MODE_MASK 0x70
#define MSPI2_MODE          0x14 //bit12~bit14
    #define MSPI2_MODE_MASK 0x7000
#define EJTAG_MODE          0xF
    #define EJTAG_MODE_MASK 0x07

#endif /* _KERNEL_MSPI_H_ */
