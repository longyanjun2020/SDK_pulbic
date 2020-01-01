/*
 * hal_bus_mspi.h
 *
 *  Created on: 2017/8/9
 *      Author: titan.huang
 */

#ifndef __HAL_BUS_MSPI_H__
#define __HAL_BUS_MSPI_H__

void HAL_MSPI_Initial(void);
void HAL_MSPI_SetDCTiming(MSpiChannel_e eChannel, MSpi_DCConfig *ptDCConfig);
void HAL_MSPI_SetTransferBits(MSpiChannel_e eChannel, MSpi_BufferConfig *ptFrameConfig);
void HAL_MSPI_SetLSB(MSpiChannel_e eChannel, bool enable);
void HAL_MSPI_InitChannel(MSpiChannel_e eChannel,MSpiPad_e ePad);
s32	HAL_MSPI_SetMode(MSpiMode_e eChannel, MSpiMode_e eMode);
u32 HAL_MSPI_SetCLKRate(MSpiChannel_e eChannel,u32 u32MspiClk);
void HAL_MSPI_SetChipSelect(MSpiChannel_e eChannel, bool Enable, u8 u8CS);
void HAL_MSPI_ClkEnable(MSpiChannel_e eChannel,bool bEnable);
void HAL_MSPI_IntEnable(MSpiChannel_e eChannel,bool bEnable);
bool HAL_MSPI_Write(MSpiRWMethod_e eRWMode, MSpiChannel_e eChannel, u8 *pData, u16 u16Size);
bool HAL_MSPI_Read(MSpiRWMethod_e eRWMode, MSpiChannel_e eChannel, u8 *pData, u16 u16Size);

#endif /* HAL_BUS_MSPI_H */
