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
* @file    hal_bus_qspi.h
* @version
* @brief   This file contains the bus QSPI hardware layer headers.
*
*/

#ifndef __HAL_BUS_QSPI_H__
#define __HAL_BUS_QSPI_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "drv_vm_spi.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	HAL_QSPI_NORMAL_1BIT 			              = 0x0, //SPI CMD:0x03
  HAL_QSPI_FAST_1BIT 				              = 0x1, //SPI CMD:0x0B
  HAL_QSPI_DUAL_CMD1BIT_ADDR1BIT_DATA2BIT = 0x2, //SPI CMD:0x3B
  HAL_QSPI_DUAL_CMD1BIT_ADDR2BIT_DATA2BIT	= 0x3, //SPI CMD:0xBB
	  HAL_QSPI_QUAD_CMD1BIT_ADDR1BIT_DATA4BIT	= 0xA, //SPI CMD:0x6B
//	  HAL_QSPI_QUAD_CMD1BIT_ADDR4BIT_DATA4BIT	= 0xB, //SPI CMD:0xEB
//	  HAL_QSPI_QUAD_CMD4BIT_ADDR4BIT_DATA4BIT	= 0xD  //QPI CMD:0xEB
} HalQspiBitMode_e;

typedef enum
{
	HAL_QSPI_SPI_MODE = 0x0,
  HAL_QSPI_QPI_MODE = 0x4
} HalQspiOpMode_e;

typedef enum
{
  HAL_QSPI_FUNC_NORMAL     = 0x0,
	HAL_QSPI_FUNC_CMD_BYPASS = 0x1,
  HAL_QSPI_FUNC_WRAP       = 0x2
} HalQspiFunc_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

void HalQspiSetCszHigh(u16 nRCsz, u16 eBusClk, bool bIsSetFspCsz);
void HalQspiSetBitMode(HalQspiBitMode_e eMode);
HalQspiBitMode_e HalQspiGetBitMode(void);


/**
 * @brief Set Operation Mode
 *
 * @param [in]  isQpiMode               1: Qpi mode, 0: Spi mode
 * @return None
 */
void HalQspiSetQpiMode(bool isQpiMode);

/**
 * @brief Get Operation Mode
 *
 * @return isQpiMode               1: Qpi mode, 0: Spi mode
 */
bool HalQspiGetQpiMode(void);

/**
 * @brief Set Function Mode
 *
 * @param [in]  eFunc                Funciton selection.
 * @param [in]  isFunc               1: Set Function, 0: Disable Funciton
 * @return None
 */
void HalQspiSetFunc(HalQspiFunc_e eFunc, bool isFunc);

/**
 * @brief Get Function Mode
 *
 * @param [in]  eFunc                Funciton selection.
 * @return bool                      1: Funciton Enable, 0: Function Disable.
 */
bool HalQspiGetFunc(HalQspiFunc_e eFunc);

/**
 * @brief Replace QPI read Cmd=0xEB to 0x0C
 *
 * @param[in]  None
 * @return     None
 */
void HalQspiReplaceCmd(void);

/**
 * @brief Set QSPI dummy cycle of read cmd
 *
 * @param[in]  None
 * @return     None
 */
void HalQspiSetDummyCycle(u8 nDummyCycle);

/**
 * @brief Set QSPI Chip select
 *
 * @param[in]  eQspiCS
 * @return     None
 */
void HalQspiSetChipSelect(u8 eQspiCS);

/**
 * @brief Get QSPI Chip select
 *
 * @param[in]  None
 * @return     HALQspiCS_e
 */
u8 HalQspiGetChipSelect(void);

/**
 * @brief Enable QSPI CSZ timeout counter
 *
 * @param[in]  None
 * @return     None
 */
void HalQspiEnableCszTimeoutCnt(void);


#ifdef __QBYTE_ADDR_SPI_FLASH__
/**
 * @brief Set QSPI 4Byte Addr mode
 *
 * @param[in]  None
 * @return     None
 */

void HalQspiSetQbyteAddrMode(void);
#endif //__QBYTE_ADDR_SPI_FLASH__

#endif //__HAL_BUS_QSPI_H__

