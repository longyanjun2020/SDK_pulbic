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
* @file    hal_serial_flash.h
* @version
* @brief   Hal serial flash driver.
*
*/

#ifndef __HAL_SERIAL_FLASH_H__
#define __HAL_SERIAL_FLASH_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_serial_flash_pub.h"
#include "drv_serial_flash.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
//	typedef enum
//	{
//		SPINOR_SECTOR4K = SERIAL_FLASH_CMD_SE,
//		SPINOR_SECTOR32K = SERIAL_FLASH_CMD_BE32,
//		SPINOR_SECTOR64K = SERIAL_FLASH_CMD_BE
//	} SPINORSector_e;
#ifndef BIT0
#define BIT0    (1<<0)
#endif
//	#define INREG16(x)              ms_readw(x)
//	#define OUTREG16(x, y)          ms_writew((u16)(y), x)
//	#define SETREG16(x, y)          OUTREG16(x, INREG16(x)|(y))

#ifndef BIT
#define BIT(_bit_)                  (1 << (_bit_))
#endif
#define SF_SR_SRWD (BITS(7:7, 1))
#define BITS(_bits_, _val_) ((BIT(((1)?_bits_)+1)-BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
#define SETREG16(addr, a) ( (*(volatile u16 *)(addr)) |= a )
#define CLRREG16(addr, a) ( (*(volatile u16 *)(addr)) &= ~a )
#define OUTREG16(addr, a) ( (*(volatile u16 *)(addr)) = a )
#define INREG16(addr)       (*(volatile u16 *)(addr))


typedef enum
{
  HAL_FLASH_FUNC_NORMAL     = 0x0,
	HAL_FLASH_FUNC_CMD_BYPASS = 0x1,
  HAL_FLASH_FUNC_WRAP       = 0x2
} HalFlashFunc_e;

typedef enum
{
    E_SINGLE_MODE,
    E_FAST_MODE,
    E_DUAL_D_MODE,
    E_DUAL_AD_MODE,
    E_QUAD_MODE,
    E_RIUISP_MODE=0xFF
}SPI_READ_MODE;
/*=============================================================*/
// Variable definition
/*=============================================================*/
#if CONFIG_FSP_WRITE_BDMA == 1
#define HAL_FLASH_WRITE_BUFFER_LEN 256
#else
#define HAL_FLASH_WRITE_BUFFER_LEN 8
#endif
/*=============================================================*/
// Global function definition
/*=============================================================*/
//	#ifdef __SUPPORT_BUS_FSP_SPI__
/**
 * @brief Set Hal SPI NOR param address
 *
 * @param [in]  pSPINORParams
 * @return None
 */
void HalSerialFlashSetSPINORParams(void* pSPINORParams);

/**
 * @brief Set Hal SPI current Bus clock address
 *
 * @param [in]  pCurrentBusClock
 * @return None
 */
void HalSerialFlashSetSPICurrentBusClock(void* pCurrentBusClock);

/**
 * @brief Set serial flash bus clock
 *
 * @param [in]  eBusClock                SPINOR_48MHz/SPINOR_77MHz/SPINOR_89MHz/SPINOR_96MHz
 * @return None
 */
//	void HalSerialFlashSetBusClock(SPINORBusClock_e eBusClock);

/**
 * @brief set MXIC Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetMXICQuadBit(void);

/**
 * @brief set WINBOND Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetWINBONDQuadBit(void);

/**
 * @brief set GIGADEVICE Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetGIGADEVICEQuadBit(void);

/**
 * @brief set ESMT Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetESMTQuadBit(void);

/**
 * @brief set EONSI Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetEONSIQuadBit(void);

/**
 * @brief Set serial flash WINBOND QPI mode
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetWINBONDQpi(bool isQpiMode);

/**
 * @brief Set serial flash MXCI QPI mode
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetMXCIQpi(bool isQpiMode);

/**
 * @brief Set serial flash EON command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetEONQpi(bool isQpiMode);

/**
 * @brief Get serial flash QPI mode
 *
 * @return bool               TRUE: Qpi mode is enabled, FALSE: Spi mode is disabled.
 */
bool HalSerialFlashGetQpi(void);

/**
 * @brief Set serial flash WINBOND command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetWINBONDCmdByp(bool isEnable);

/**
 * @brief Set serial flash EON command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetEONCmdByp(bool isEnable);


/**
 * @brief Set serial flash WINBOND command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetMXCICmdByp(bool isEnable);

/**
 * @brief Set serial flash WINBOND wrap function
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetWINBONDWrap(void);

/**
 * @brief Set serial flash MXIC wrap function
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetMXICWrap(void);

/**
 * @brief Set serial flash EON wrap function
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetEONWrap(void);

/**
 * @brief Set serial flash MICRON QPI mode
 *
 * @param [in]  isQpiMode.
 * @return None
 */
void HalSerialFlashSetMICRONQpi(bool isQpiMode);

/**
 * @brief set MICRON Quad bit function
 *
 * @param  None
 * @return None
 */
void HalSerialFlashSetMICRONQuadBit(void);

/**
 * @brief Set serial flash MICRON command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetMICRONCmdByp(bool isEnable);

/**
 * @brief Set serial flash MICRON set dummy clock
 *
 * @param [in]  is6T.
 * @return None
 */
void HalSerialFlashSetMICRONDummy(bool is6T);

/**
 * @brief Set serial flash GD QPI mode
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetGDQpi(bool isQpiMode);

/**
 * @brief Get serial flash QPI mode
 *
 * @return bool               TRUE: Qpi mode is enabled, FALSE: Spi mode is disabled.
 */
bool HalSerialFlashGetQpi(void);

/**
 * @brief Set serial flash GIGA command bypass function
 *
 * @param [in]  isEnable                TRUE: enable, FALSE: disable.
 * @return None
 */
void HalSerialFlashSetGDCmdByp(bool isEnable);

/**
 * @brief Set serial flash GIGA wrap function
 *
 * @param [in]  None.
 * @return None
 */
void HalSerialFlashSetGDWrap(void);

/**
 * @brief Get serial flash function
 *
 * @param [in]  eFunc                Funciton selection.
 * @return bool                      TRUE: function is enabled, FALSE: funciton is disabled.
 */
bool HalSerialFlashGetFunc(HalFlashFunc_e eFunc);

/**
 * @brief flash buffer program function
 *
 * @return None
 */
void HalSerflashBufferProgram(u32 nAddr, u32 nSize, u8 *pData);

/**
 * @brief flash erase function
 *
 * @return None
 */
void HalSerflashBlockErase(u32 nAddr, SPINORSector_e eSector);
/**
 * @brief flash write Engine function
 *
 * @return None
 */
void HalFspWriteEngine(u32 nAddr, u32 nSize, u8 *pData);
/**
 * @brief flash word program function
 *
 * @return None
 */
void HalFspWrite(u32 nAddr, u32 nSize, u8 *pData);


/**
 * @brief flash word program function
 *
 * @return None
 */
 void HalSerflashWrite(u32 nAddr, u32 nSize, u8 *pData);
 void HalSerialFlashReset(void);
 u32 HalSerialFlashGetWriteBufferLen(void);
 u32 HalSerflashReadID(void);
 void HalSerflashWriteProtect(bool bEnable);
//	#endif //__SUPPORT_BUS_FSP_SPI__

/**
 * @brief Get write buffer length of flash program
 *
 * @param [in]  None.
 * @return u32  write buffer length
 */
u32 HalSerflashGetWriteBufferLen(void);

/**
 * @brief Flash reset
 *
 * @param [in]  None.
 * @return u32  write buffer length
 */
void HalSerflashFlashReset(void);

/**
 * @brief SPI reset procedure
 *
 * @param [in]  None.
 * @return None
 */
//	void HalSerialFlashResetProcedure(void);

void HalSerflashSetStatus(u8 *pStatus, u8 nLen, bool bIsNonVolatile);

u8 HalSerflashGetStatus(u8 nReg);
void HalFspEntry(void);
void HalFspExit(void);
#endif //__HAL_SERIAL_FLASH_H__

