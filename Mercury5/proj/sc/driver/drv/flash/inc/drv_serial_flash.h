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
 * @file drv_serial_flash.h
 * @brief API prototypes for Serial Flash memory
 */

#ifndef __DRV_SERIAL_FLASH_H__
#define __DRV_SERIAL_FLASH_H__
//	#define __SUPPORT_BUS_FSP_SPI__
#include "vm_types.ht"
#include "drv_vm_spi.h"
#include "drv_serial_flash_pub.h"
#include "drv_bus_spi.h"

/****************************************************************************/
/*  Macro definition                                                        */
/****************************************************************************/
#define DRV_BUS_SPI_ERROR_LEVEL               (_DEV)
#define DRV_BUS_SPI_TRACE_LEVEL               (DRV_BUS_SPI_ERROR_LEVEL | LEVEL_6)

#define SERIAL_FLASH_CMD_WREN           0x06
#define SERIAL_FLASH_CMD_WRDI           0x04
#define SERIAL_FLASH_CMD_RDID           0x9F
#define SERIAL_FLASH_CMD_RDSR1          0x05
#define SERIAL_FLASH_CMD_WRSR           0x01
#define SERIAL_FLASH_CMD_READ           0x03
#define SERIAL_FLASH_CMD_FAST_READ      0x0B
#define SERIAL_FLASH_CMD_DUAL_READ      0xBB
#define SERIAL_FLASH_CMD_QUAD_READ      0xEB
#define SERIAL_FLASH_CMD_SE             0x20
#define SERIAL_FLASH_CMD_BE32           0x52
#define SERIAL_FLASH_CMD_BE             0xD8
#define SERIAL_FLASH_CMD_WREAR          0xC5
#define SERIAL_FLASH_CMD_RDEAR          0xC8

//	#define SPI_CMD_SE			(0x20)
//	#define SPI_CMD_32BE		(0x52)
//	#define SPI_CMD_64BE		(0xD8)
#define SERIAL_FLASH_CMD_CE             0x60  //0xC7
#define SERIAL_FLASH_CMD_PP             0x02
#define SERIAL_FLASH_CMD_CP             0xAD
#define SERIAL_FLASH_CMD_DP             0xB9
#define SERIAL_FLASH_CMD_RDP            0xAB
#define SERIAL_FLASH_CMD_RES            0xAB
#define SERIAL_FLASH_CMD_REMS           0x90
#define SERIAL_FLASH_CMD_REMS2          0xEF
#define SERIAL_FLASH_CMD_ENSO           0xB1
#define SERIAL_FLASH_CMD_EXSO           0xC1
#define SERIAL_FLASH_CMD_RDSCUR         0x2B
#define SERIAL_FLASH_CMD_WRSCUR         0x2F
#define SERIAL_FLASH_CMD_ESRY           0x70
#define SERIAL_FLASH_CMD_DSRY           0x80
#define SERIAL_FLASH_CMD_QADDR          0xB7
#define SERIAL_FLASH_CMD_RDCR           0x15

#define SPINOR_BUSY_BIT					0x01

#define WINBOND_QE_BIT					0x02
#define GIGADEVICE_QE_BIT				0x02
#define MACRONIX_QE_BIT					0x40

#define WINBOND_SUSPEND_BIT				0x80

#define GIGADEVICE_SUSPEND_BIT			0x80

#define MACRONIX_SUSPEND_BIT			0x08
#define MACRONIX_ERASE_ERROR_BIT		0x40

#define MICRON_SUSPEND_BIT				0x40
#define MICRON_BUSY_BIT					0x80
#define MICRON_ERASE_ERROR_BIT			0x20

#define EON_SUSPEND_BIT					0x04
#define EON_BUSY_BIT					0x80
#define EON_FAIL_BIT					0x20

#define ESMT_SUSPEND_BIT				0x01
#define ESMT_QE_BIT						0x40

typedef enum
{
	SPINOR_SECTOR4K = SERIAL_FLASH_CMD_SE,
	SPINOR_SECTOR32K = SERIAL_FLASH_CMD_BE32,
	SPINOR_SECTOR64K = SERIAL_FLASH_CMD_BE
} SPINORSector_e;

typedef enum
{
	NORMAL_1BIT 			= 0x0,	//SPI CMD:0x03
    FAST_1BIT 				= 0x1,	//SPI CMD:0x0B
    DUAL_ADDR1BIT_DATA2BIT 	= 0x2,	//SPI CMD:0x3B
    DUAL_ADDR2BIT_DATA2BIT 	= 0x3,	//SPI CMD:0xBB
    QUAD_ADDR1BIT_DATA4BIT 	= 0xA,	//SPI CMD:0x6B
    QUAD_ADDR4BIT_DATA4BIT 	= 0xB	//SPI CMD:0xEB
} SPIReadMode_e;

typedef enum
{
  SPINOR_SPI 		= 0x0,
  SPINOR_QPI		= 0x1
} SPINOROpMode_e;

typedef enum
{
	SPINOR_CS0 = 0x0,
	SPINOR_CS1 = 0x1
} SPINORCS_e;

#define SPINOR_FUNC_NORMAL     0
#define SPINOR_FUNC_CMD_BYPASS (1<<0)
#define SPINOR_FUNC_WRAP       (1<<1)

typedef struct
{
    u32 nFlashID;
    SPINOROpMode_e   eOpMode;
    u8               eFunc;
    SPINORBusClock_e eBusClock;
    void (* pSPIInit)(void);
    void (* pSPICmdByp)(bool isEnable);
    u8 nCMDStatus2;
    u8 nCMDSuspend;
    u8 nCMDResume;
    u8 nSuspendBit;
    u16 R_CSZ;
    u16 W_CSZ;
    u16 nDummyClk;
    u16 nDeviceSize;
	u32 nDeviceFullId;
} spi_norConfig_t;

#define CONFIG_FSP_WRITE_BDMA (1)
/****************************************************************************/
/*  BUS functions                                                           */
/****************************************************************************/

void DrvSerialFlashOpen(s32 *pHandle, VmSpiBloc_e eSpiBloc);
void DrvSerialFlashClose(s32 nHandle);
void DrvSerialFlashReadID(s32 nHandle, u8 *pFlashID);
void DrvSerialFlashRead(s32 nHandle, u32 nAddr, u32 nSize, u8 *pData);
void DrvSerialFlashPageProgram(s32 nHandle, u32 nAddr, u32 nSize, u8 *pData);
void DrvSerialFlashSectorErase(s32 nHandle, u32 nAddr);

#ifdef __SUPPORT_BUS_FSP_SPI__
void DrvSetSPIFastBit(void);
void DrvSetSPIDualBit(void);

void DrvSetSPIQUADBit(void);
void DrvFSPSetWINBONDQuadBit(void);
void DrvFSPSetWINBONDCmdByp(bool isEnable);
void DrvFSPSetMXICQuadBit(void);
void DrvFSPSetMXCICmdByp(bool isEnable);
void DrvFSPSetEONCmdByp(bool isEnable);
void DrvFSPSetEONSIQuadBit(void);
void DrvFSPSetMICRONQuadBit(void);
void DrvFSPSetMICRONCmdByp(bool isEnable);
void DrvFSPSetGIGADEVICEQuadBit(void);
void DrvFSPSetGDCmdByp(bool isEnable);
void DrvFSPSetESMTQuadBit(void);
void DrvSetSPIParameters(u32 nID);
void DrvSetSPICSZ_R(void);
void DrvSetSPICSZ_W(void);
u32 DrvSerflashReadID(void);
void DrvSerflashWriteProtect(bool bEnable);
void DrvSerflashWrite(u32 nAddr, u32 nSize, u8 *pData);
SPINORBusClock_e DrvGetSPINORBusClock(void);
SPINORBusClock_e DrvSetSPINORBusClock(SPINORBusClock_e eBusClock);
//	void DrvFSPWordProgram(u32 nAddr, u32 nSize, u8 *pData, bool bAutoCheck);
void DrvSerflashBufferProgram(u32 nAddr, u32 nSize, u8 *pData);
void DrvSerflashBlockErase(u32 nAddr, SPINORSector_e eSector);
u8   DrvFSPGetStatus(u8 nReg);
void DrvFSPEraseSuspend(void);
void DrvFSPEraseResume(void);
void DrvSetSPIBitMode(SPIReadMode_e mode);
void DrvEXTEND(void);
SPIReadMode_e DrvGetSPIBitMode(void);
u8 DrvFSPProtectMXIC(u32 nAddr, bool bProtect);
void DrvFSPSetStatus(u8 *pStatus, u8 nLen, bool bIsNonVolatile);
void DrvFSPSetHP(bool bIsOn);
void DrvFSPReset(void);
bool DrvFSPSuspendCheck(void);
void DrvSetSPIDriving(SPINORDriving_e eDriving);
SPINORCS_e DrvGetSPIChipSelect(void);
void DrvSetSPIChipSelect(SPINORCS_e eSpiCS);
bool DrvSPIBootSrcIsSPI(void);
void DrvSERFLASH_WriteProtect(bool bEnable);
#endif

#ifdef __I_SW__
void DrvDMASerialFlashRead(s32 nHandle, u32 nAddr, u32 nSize, u8 *pData);
void DrvDMASerialFlashPageProgram(s32 nHandle, u32 nAddr, u32 nSize, u8 *pData);
void DrvFlashMacronixEraseStress(u32 nAddress, u32 *suspend, u32 *resume);
void DrvFlashWinbondEraseStress(u32 nAddress, u32 *suspend, u32 *resume);
#endif

#endif /* __DRV_SERIAL_FLASH_H__*/

