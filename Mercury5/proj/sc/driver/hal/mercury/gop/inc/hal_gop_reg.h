////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file     hal_gop_reg.h
 * @version
 * @Platform I3
 * @brief    This file defines the HAL SCL utility interface
 *
 */

#ifndef __HAL_GOP_REG_H__
#define __HAL_GOP_REG_H__

#define MIU_BUS_MERCURY5       0x4
#define MIU_BUS_ALIGN           MIU_BUS_MERCURY5

//-------------------------------------------------------------------------------------
#define GOP_BANK_DOUBLE_WR_G00      0x0400
#define GOP_BANK_DOUBLE_WR_G10      0x0403
#define GOP_BANK_DOUBLE_WR_G20      0x0406

#define GOP_BANK_DOUBLE_WR_MSK      0x0400
#define GOP_BANK_ALL_DOUBLE_WR_MSK      0x0100
#define GOP_BANK_SEL_MSK            0x000F

#define GOP_BANK_DOUBLE_WR_ALL_BANK          0x0100
#define GOP_BANK_FORCE_WR           0x0200

#define GOP_BANK_GOP0_WR_ACK_MSK    0x1000
#define GOP_BANK_GOP1_WR_ACK_MSK    0x2000
#define GOP_BANK_GOP2_WR_ACK_MSK    0x4000

//-------------------------------------------------------------------------------------
// REG_GOP_00
#define GOP_SOFT_RESET                    0x0001
#define GOP_VS_INV                        0x0002
#define GOP_HS_INV                        0x0004
#define GOP_DISPLAY_MODE                  0x0008 // 0:interlace, 1: progress
#define GOP_FIELD_INV                     0x0010
#define GOP_YUV_TRANSPARENT_COLOR_ENABLE  0x0020
#define GOP_TEST_PATTENR_MODE_ENABLE      0x0040
#define GOP_5541_EN                       0x0080 // RGB5541 alpha mask mode enable, only for RGB1555 Data type
#define GOP_REG_OUTPUT_READY              0x0100
#define GOP_G3D_FORMATE_NEW_MODE_ENABLE   0x0200
#define GOP_OUTPUT_FORMAT                 0x0400 // 0:RGB out, 1:YUV out
#define GOP_RGB_TRANSPARENT_COLOR_MASK    0x0800
#define GOP_DISP_HBACK_ENABLE             0x1000 // H Mirror enable; H pixel read out direction, 0:forward, 1:backward
#define GOP_DISP_VBACK_ENABLE             0x2000 // V Mirror enable; V line read out direction, 0:down, 1:up
#define GOP_HS_MASK                       0x4000
#define GOP_ALPHA_INV                     0x8000
// GOP Display Mode
#define GWIN_display_mode_progress        0x0008
#define GWIN_display_mode_interlace       0x0000
// GOP Output Color
#define GOP_YUVOUT                        0x0400
#define GOP_RGBOUT                        0x0000
// GOP RGB Transparent Color
#define GOP_RGB_TRANSPARENT_COLOR_ENABLE  0x0800
#define GOP_RGB_TRANSPARENT_COLOR_DISABLE 0x0000

#define GOP_PIXEL_ALPHA_EN                0x4000
#define GOP_CONSTANT_ALPHA_EN             0x0000
#define GOP_ALPHA_MASK                    0x4000

//-------------------------------------------------------------------------------------
// REG_GOP_01
// GOP Destination
#define GOP_DST_IP_MAIN                   0x0000
#define GOP_DST_IP_SUB                    0x0001
#define GOP_DST_OP                        0x0002
#define GOP_DST_MVOP                      0x0003
#define GOP_DST_SUB_MVOP                  0x0004
#define GOP_DST_FRC                       0x0006
// GOP interval settings
#define GOP_REGDMA_INTERVAL_START         0x0200 //infinity:0x0200; cedric:0x0300
#define GOP_REGDMA_INTERVAL_END           0x4000 //infinity:0x4000; cedirc:0x5000

//-------------------------------------------------------------------------------------
// REG_GOP_02
#define GOP_BLINK_DISABLE                 0x0000
#define GOP_BLINK_ENABLE                  0x8000
#define GOP_INPUT_VSYNC_INVERT                 0x0080
//-------------------------------------------------------------------------------------
// REG_GOP_05
#define GOP_PALETTE_TABLE_ADDRESS_MASK    0x00FF //palette index
#define GOP_PALETTE_WRITE_ENABLE_MASK     0x0100
#define GOP_PALETTE_READ_ENABLE_MASK      0x0200
#define GOP_PALETTE_SRAM_CTRL_MASK        0x3000 //0:RIU mode; 1:REGDMA mode; 2,3:for external gop
#define GOP_PALETTE_SRAM_CTRL_RIU         0x0000
#define GOP_PALETTE_SRAM_CTRL_REGDMA      0x1000

//-------------------------------------------------------------------------------------
// REG_GOP_06
#define GOP_REGDMA_END                    0x0034

//-------------------------------------------------------------------------------------
// REG_GOP_07
#define GOP_REGDMA_STR                    0x0000

//-------------------------------------------------------------------------------------
// REG_GOP_0F
#define GOP_HSYNC_PIPE_DLY_FOR_IP_SUB     0x0080
#define GOP_HSYNC_PIPE_DLY_FOR_SC1_OP     0x00A0
#define HSYNC_PIPE_DLY_FOR_SC0_2GOP       0x0044

// inifinity settings
#define INIFINITY_GOP_HSYNC_PIPE_DLY      0x0000
#define GOP_HSYNC_PIPE_DLY                INIFINITY_GOP_HSYNC_PIPE_DLY

#define GOP_HSYNC_PIPE_DLY_FOR_IP_SUB     0x0080

//-------------------------------------------------------------------------------------
// REG_GOP_19
#define GOP_BURST_LENGTH_MASK             0x1F00
#define GOP_BURST_LENGTH_MAX              0x1F00
#define GOP_BURST_LENGTH_AUTO             0x0000

//-------------------------------------------------------------------------------------
// REG_GOP_20
#define GOP_GWIN_HIGH_PRI_0               0x0000
#define GOP_GWIN_HIGH_PRI_1               0x0001
//-------------------------------------------------------------------------------------
// REG_GOP_32
#define GOP_STRETCH_HST                   0x0000

//-------------------------------------------------------------------------------------
// REG_GOP_34
#define GOP_STRETCH_VST                   0x0000

//-------------------------------------------------------------------------------------
// REG_GOP_35
#define GOP_STRETCH_HRATIO                0x1000
#define GOP_STRETCH_HRATIO_1X             0x1000
//-------------------------------------------------------------------------------------
// REG_GOP_36
#define GOP_STRETCH_VRATIO                0x1000
#define GOP_STRETCH_VRATIO_1X             0x1000
//-------------------------------------------------------------------------------------
// REG_GOP_38
#define GOP_STRETCH_HINI                  0x0000
//-------------------------------------------------------------------------------------
// REG_GOP_39
#define GOP_STRETCH_VINI                  0x0000

#define GOP_GWIN_ENABLE                   0x0001

//-------------------------------------------------------------------------------------
// REG BASE
//-------------------------------------------------------------------------------------

#define REG_GOP_00_BASE     0x123100    // SCL_GOP
#define REG_GOP_01_BASE     0x123200
#define REG_GOP_0_ST_BASE   0x123300
#define REG_GOP_10_BASE     0x123400    // DEC_GOP1
#define REG_GOP_11_BASE     0x123500
#define REG_GOP_1_ST_BASE   0x123600 
#define REG_GOP_20_BASE     0x123700    // DEC_GOP2
#define REG_GOP_21_BASE     0x123800
#define REG_GOP_2_ST_BASE   0x123900
#define REG_GOP_30_BASE     0x123A00    // DEC_GOP3
#define REG_GOP_31_BASE     0x123B00
#define REG_GOP_3_ST_BASE   0x123C00
#define REG_GOP_40_BASE     0x123D00    // DIP_GOP
#define REG_GOP_41_BASE     0x123E00
#define REG_GOP_4_ST_BASE   0x123F00

#define REG_SCL_TO_GOP_BASE         0x122D00
#define REG_SCL_EN_GOP_00           BK_REG(0x00)

#define REG_OSDB_GOP1_BASE          0x161400
#define REG_OSDB_EN_GOP_01          BK_REG(0x00)
#define OSDB_GOP1_LOC               0x0002
#define REG_OSDB_EN_GOP_02          BK_REG(0x40)
#define REG_OSDB_GOP3_BASE          0x161500
#define REG_OSDB_EN_GOP_03          BK_REG(0x00)

#define REG_DIP_TO_GOP4_OSDB_BASE   0x161700
#define REG_DIP_TO_GOP4_OSDB_EN     BK_REG(0x10) //bit0

#define REG_SCL_FCLK_BASE           0x103800

#define REG_GOP_PSRAM_CLK_BASE      0x113300

#define BK_REG(reg)               ((reg) * 2)

#define REG_GOP_00                BK_REG(0x00)
#define REG_GOP_01                BK_REG(0x01)
#define REG_GOP_02                BK_REG(0x02)
#define REG_GOP_03                BK_REG(0x03)
#define REG_GOP_04                BK_REG(0x04)
#define REG_GOP_05                BK_REG(0x05)
#define REG_GOP_06                BK_REG(0x06)
#define REG_GOP_07                BK_REG(0x07)
#define REG_GOP_08                BK_REG(0x08)
#define REG_GOP_09                BK_REG(0x09)
#define REG_GOP_0A                BK_REG(0x0A)
#define REG_GOP_0B                BK_REG(0x0B)
#define REG_GOP_0C                BK_REG(0x0C)
#define REG_GOP_0D                BK_REG(0x0D)
#define REG_GOP_0E                BK_REG(0x0E)
#define REG_GOP_0F                BK_REG(0x0F)

#define REG_GOP_10                BK_REG(0x10)
#define REG_GOP_11                BK_REG(0x11)
#define REG_GOP_12                BK_REG(0x12)
#define REG_GOP_13                BK_REG(0x13)
#define REG_GOP_14                BK_REG(0x14)
#define REG_GOP_15                BK_REG(0x15)
#define REG_GOP_16                BK_REG(0x16)
#define REG_GOP_17                BK_REG(0x17)
#define REG_GOP_18                BK_REG(0x18)
#define REG_GOP_19                BK_REG(0x19)
#define REG_GOP_1A                BK_REG(0x1A)
#define REG_GOP_1B                BK_REG(0x1B)
#define REG_GOP_1C                BK_REG(0x1C)
#define REG_GOP_1D                BK_REG(0x1D)
#define REG_GOP_1E                BK_REG(0x1E)
#define REG_GOP_1F                BK_REG(0x1F)

#define REG_GOP_20                BK_REG(0x20)
#define REG_GOP_21                BK_REG(0x21)
#define REG_GOP_22                BK_REG(0x22)
#define REG_GOP_23                BK_REG(0x23)
#define REG_GOP_24                BK_REG(0x24)
#define REG_GOP_25                BK_REG(0x25)
#define REG_GOP_26                BK_REG(0x26)
#define REG_GOP_27                BK_REG(0x27)
#define REG_GOP_28                BK_REG(0x28)
#define REG_GOP_29                BK_REG(0x29)
#define REG_GOP_2A                BK_REG(0x2A)
#define REG_GOP_2B                BK_REG(0x2B)
#define REG_GOP_2C                BK_REG(0x2C)
#define REG_GOP_2D                BK_REG(0x2D)
#define REG_GOP_2E                BK_REG(0x2E)
#define REG_GOP_2F                BK_REG(0x2F)

#define REG_GOP_30                BK_REG(0x30)
#define REG_GOP_31                BK_REG(0x31)
#define REG_GOP_32                BK_REG(0x32)
#define REG_GOP_33                BK_REG(0x33)
#define REG_GOP_34                BK_REG(0x34)
#define REG_GOP_35                BK_REG(0x35)
#define REG_GOP_36                BK_REG(0x36)
#define REG_GOP_37                BK_REG(0x37)
#define REG_GOP_38                BK_REG(0x38)
#define REG_GOP_39                BK_REG(0x39)
#define REG_GOP_3A                BK_REG(0x3A)
#define REG_GOP_3B                BK_REG(0x3B)
#define REG_GOP_3C                BK_REG(0x3C)
#define REG_GOP_3D                BK_REG(0x3D)
#define REG_GOP_3E                BK_REG(0x3E)
#define REG_GOP_3F                BK_REG(0x3F)

#define REG_GOP_40                BK_REG(0x40)
#define REG_GOP_41                BK_REG(0x41)
#define REG_GOP_42                BK_REG(0x42)
#define REG_GOP_43                BK_REG(0x43)
#define REG_GOP_44                BK_REG(0x44)
#define REG_GOP_45                BK_REG(0x45)
#define REG_GOP_46                BK_REG(0x46)
#define REG_GOP_47                BK_REG(0x47)
#define REG_GOP_48                BK_REG(0x48)
#define REG_GOP_49                BK_REG(0x49)
#define REG_GOP_4A                BK_REG(0x4A)
#define REG_GOP_4B                BK_REG(0x4B)
#define REG_GOP_4C                BK_REG(0x4C)
#define REG_GOP_4D                BK_REG(0x4D)
#define REG_GOP_4E                BK_REG(0x4E)
#define REG_GOP_4F                BK_REG(0x4F)

#define REG_GOP_50                BK_REG(0x50)
#define REG_GOP_51                BK_REG(0x51)
#define REG_GOP_52                BK_REG(0x52)
#define REG_GOP_53                BK_REG(0x53)
#define REG_GOP_54                BK_REG(0x54)
#define REG_GOP_55                BK_REG(0x55)
#define REG_GOP_56                BK_REG(0x56)
#define REG_GOP_57                BK_REG(0x57)
#define REG_GOP_58                BK_REG(0x58)
#define REG_GOP_59                BK_REG(0x59)
#define REG_GOP_5A                BK_REG(0x5A)
#define REG_GOP_5B                BK_REG(0x5B)
#define REG_GOP_5C                BK_REG(0x5C)
#define REG_GOP_5D                BK_REG(0x5D)
#define REG_GOP_5E                BK_REG(0x5E)
#define REG_GOP_5F                BK_REG(0x5F)

#define REG_GOP_60                BK_REG(0x60)
#define REG_GOP_61                BK_REG(0x61)
#define REG_GOP_62                BK_REG(0x62)
#define REG_GOP_63                BK_REG(0x63)
#define REG_GOP_64                BK_REG(0x64)
#define REG_GOP_65                BK_REG(0x65)
#define REG_GOP_66                BK_REG(0x66)
#define REG_GOP_67                BK_REG(0x67)
#define REG_GOP_68                BK_REG(0x68)
#define REG_GOP_69                BK_REG(0x69)
#define REG_GOP_6A                BK_REG(0x6A)
#define REG_GOP_6B                BK_REG(0x6B)
#define REG_GOP_6C                BK_REG(0x6C)
#define REG_GOP_6D                BK_REG(0x6D)
#define REG_GOP_6E                BK_REG(0x6E)
#define REG_GOP_6F                BK_REG(0x6F)

#define REG_GOP_70                BK_REG(0x70)
#define REG_GOP_71                BK_REG(0x71)
#define REG_GOP_72                BK_REG(0x72)
#define REG_GOP_73                BK_REG(0x73)
#define REG_GOP_74                BK_REG(0x74)
#define REG_GOP_75                BK_REG(0x75)
#define REG_GOP_76                BK_REG(0x76)
#define REG_GOP_77                BK_REG(0x77)
#define REG_GOP_78                BK_REG(0x78)
#define REG_GOP_79                BK_REG(0x79)
#define REG_GOP_7A                BK_REG(0x7A)
#define REG_GOP_7B                BK_REG(0x7B)
#define REG_GOP_7C                BK_REG(0x7C)
#define REG_GOP_7D                BK_REG(0x7D)
#define REG_GOP_7E                BK_REG(0x7E)
#define REG_GOP_7F                BK_REG(0x7F)

#define GWIN_OFFSET               BK_REG(0x20)

#define REG_GW_GOP_00(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x00))
#define REG_GW_GOP_01(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x01))
#define REG_GW_GOP_02(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x02))
#define REG_GW_GOP_03(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x03))
#define REG_GW_GOP_04(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x04))
#define REG_GW_GOP_05(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x05))
#define REG_GW_GOP_06(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x06))
#define REG_GW_GOP_07(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x07))
#define REG_GW_GOP_08(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x08))
#define REG_GW_GOP_09(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x09))
#define REG_GW_GOP_0A(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0A))
#define REG_GW_GOP_0B(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0B))
#define REG_GW_GOP_0C(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0C))
#define REG_GW_GOP_0D(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0D))
#define REG_GW_GOP_0E(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0E))
#define REG_GW_GOP_0F(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x0F))

#define REG_GW_GOP_10(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x10))
#define REG_GW_GOP_11(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x11))
#define REG_GW_GOP_12(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x12))
#define REG_GW_GOP_13(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x13))
#define REG_GW_GOP_14(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x14))
#define REG_GW_GOP_15(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x15))
#define REG_GW_GOP_16(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x16))
#define REG_GW_GOP_17(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x17))
#define REG_GW_GOP_18(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x18))
#define REG_GW_GOP_19(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x19))
#define REG_GW_GOP_1A(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1A))
#define REG_GW_GOP_1B(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1B))
#define REG_GW_GOP_1C(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1C))
#define REG_GW_GOP_1D(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1D))
#define REG_GW_GOP_1E(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1E))
#define REG_GW_GOP_1F(GWIN)     (GWIN_OFFSET*GWIN +BK_REG(0x1F))

#endif /* __HAL_GOP_REG_H__ */
