////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    hal_bus_fsp_spi.h
* @version
* @brief   This file contains the bus FSP SPI hardware layer headers.
*
*/

#ifndef __HAL_BUS_FSP_SPI_H__
#define __HAL_BUS_FSP_SPI_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "stdcomp.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct KeFspSpi_s
{
    //0x0[rw]
    u32 reg_fsp_wd0                 :8;
    u32 reg_fsp_wd1                 :8;
    u32                             :16;
    //0x1[rw]
    u32 reg_fsp_wd2                 :8;
    u32 reg_fsp_wd3                 :8;
    u32                             :16;
    //0x2[rw]
    u32 reg_fsp_wd4                 :8;
    u32 reg_fsp_wd5                 :8;
    u32                             :16;
    //0x3[rw]
    u32 reg_fsp_wd6                 :8;
    u32 reg_fsp_wd7                 :8;
    u32                             :16;
    //0x4[rw]
    u32 reg_fsp_wd8                 :8;
    u32 reg_fsp_wd9                 :8;
    u32                             :16;
    //0x5[rw]
    u32 reg_fsp_rd0                 :8;
    u32 reg_fsp_rd1                 :8;
    u32                             :16;
    //0x6[rw]
    u32 reg_fsp_rd2                 :8;
    u32 reg_fsp_rd3                 :8;
    u32                             :16;
    //0x7[rw]
    u32 reg_fsp_rd4                 :8;
    u32 reg_fsp_rd5                 :8;
    u32                             :16;
    //0x8[rw]
    u32 reg_fsp_rd6                 :8;
    u32 reg_fsp_rd7                 :8;
    u32                             :16;
    //0x9[rw]
    u32 reg_fsp_rd8                 :8;
    u32 reg_fsp_rd9                 :8;
    u32                             :16;
    //0xa[rw] how many bytes will be transmitted in nth command
    u32 reg_fsp_wbf_size0           :4;     //first command 1~10 bytes
    u32 reg_fsp_wbf_size1           :4;     //second command 1~9 bytes
    u32 reg_fsp_wbf_size2           :4;     //third command 1~8 bytes
    u32                             :20;
    //0xb[rw] how many bytes will be received in nth command
    u32 reg_fsp_rbf_size0           :4;     //first command 0~10 bytes
    u32 reg_fsp_rbf_size1           :4;     //second command 0~10 bytes
    u32 reg_fsp_rbf_size2           :4;     //third command 0~10 bytes
    u32                             :20;
    //0xc[rw]
    u32 reg_fsp_en                  :1;     //Enable FSP [0]:Disable [1]:Enable
    u32 reg_fsp_reset               :1;     //Enable reset [0]:Reset [1]: Not Reset
    u32 reg_fsp_interrupt           :1;     //Enable FSP interrupt [0]:Disable [1]:Enable
    u32 reg_fsp_auto_chk_err_flg    :1;     //Enable auto check error flag
    u32                             :4;
    u32 reg_fsp_flash_rdy_bit       :3;     //Which bit is flash ready bit
    u32 reg_fsp_rdsr_cmd            :2;     //Which command is RDSR
    u32 reg_fsp_auto_check_en       :1;     //Enable auto check flash status
    u32 reg_fsp_third_cmd_en        :1;
    u32 reg_fsp_second_cmd_en       :1;
    u32                             :16;
    //0xd[w]
    u32 reg_fsp_trigger             :1;
    u32                             :31;
    //0xe[r]
    u32 reg_fsp_done_flg            :1;
    u32 reg_fsp_auto_chk_err        :1;
    u32                             :30;
    //0xf[w]
    u32 reg_fsp_done_flg_clear      :1;
    u32                             :31;
} KeFspSpi_t;

/**
 * @brief FSP SPI access description structure
 */
typedef enum
{
    FSP_USE_ONE_CMD     = 0x0,
    FSP_USE_TWO_CMD     = 0x1,
    FSP_USE_THREE_CMD   = 0x2,
} FspCmdUse_e;


typedef enum
{
    FSP_CHK_BIT0 = 0x0,
    FSP_CHK_BIT1 = 0x1,
    FSP_CHK_BIT2 = 0x2,
    FSP_CHK_BIT3 = 0x3,
    FSP_CHK_BIT4 = 0x4,
    FSP_CHK_BIT5 = 0x5,
    FSP_CHK_BIT6 = 0x6,
    FSP_CHK_BIT7 = 0x7
} FspAutoCheckBit_e;

typedef enum
{
    FSP_FST_CMD   = 0x0,
    FSP_SND_CMD   = 0x1,
    FSP_TRD_CMD   = 0x2
} FspCmdList_e;

typedef struct {
    bool                bAutoCheck;
    FspAutoCheckBit_e   eAutoCheckBit;
    FspCmdList_e        eCmdRDSR;
    FspCmdUse_e         eCmdUse;
    u8                  nFSTCmdWLen;
    u8                  nSNDCmdWLen;
    u8                  nTRDCmdWLen;
    u8                  nFSTCmdRLen;
    u8                  nSNDCmdRLen;
    u8                  nTRDCmdRLen;
    u8                  nWBuffer[10];
    u8                  nRBuffer[10];
} FspSpiParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

void HalFspSpiWriteAndRead(FspSpiParam_t *pFspParam);


#endif //__HAL_BUS_FSP_SPI_H__
