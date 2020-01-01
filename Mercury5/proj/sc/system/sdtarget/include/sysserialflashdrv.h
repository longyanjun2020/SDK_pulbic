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

#ifndef __SYSSERIALFLASHDRV_H__
#define __SYSSERIALFLASHDRV_H__

#define SERIAL_FLASH_CMD_WREN           0x06    //Write Enable
#define SERIAL_FLASH_CMD_WRDI           0x04    //Write Disable
#define SERIAL_FLASH_CMD_RDID           0x9F    //JEDEC ID
#define SERIAL_FLASH_CMD_RDSR1          0x05    //Read Status Register1
#define SERIAL_FLASH_CMD_RDSR2          0x35    //Read Status Register2
#define SERIAL_FLASH_CMD_WRSR           0x01    //Write Status Register
#define SERIAL_FLASH_CMD_READ           0x03    //Data Read
#define SERIAL_FLASH_CMD_FAST_READ      0x0B    //Fast Read
#define SERIAL_FLASH_CMD_2READ          0xBB    //Fast Read Dual I/O
#define SERIAL_FLASH_CMD_SE             0x20    //(4kB)Sector Erase
#define SERIAL_FLASH_CMD_BE             0xD8    //(64kB)Block Erase
#define SERIAL_FLASH_CMD_BE32           0x52    //(64kB)Block Erase
#define SERIAL_FLASH_CMD_CE             0x60    //or C7h Chip Erase
#define SERIAL_FLASH_CMD_PP             0x02    //Page Program
#define SERIAL_FLASH_CMD_CP             0xAD
#define SERIAL_FLASH_CMD_PD             0xB9    //Power Down
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
#define SERIAL_FLASH_CMD_ERSU           0x75
#define SERIAL_FLASH_CMD_ERRE           0x7A
#define SERIAL_FLASH_CMD_QADDR          0xB7 //4 byte addr mode

typedef enum
{
	SPINOR_SECTOR4K = SERIAL_FLASH_CMD_SE,
	SPINOR_SECTOR32K = SERIAL_FLASH_CMD_BE32,
	SPINOR_SECTOR64K = SERIAL_FLASH_CMD_BE
} SPINORSector_e;


typedef enum
{
	SPIQSPICS0 = 0x0,
	SPIQSPICS1 = 0x1
} SPIQspiCS_e;

//***************************************************************************
// Serial Flash Drv
//***************************************************************************
void DrvSerialFlashOpen(void);
void DrvSerialFlashClose(void);
u32  DrvSerialFlashReadID(void);
void DrvSerialFlashRead(u32 nAddr, u8 *pData, u16 nSize);
void DrvSerialFlashPageProgram(u32 nAddr,u8 *pData, u16 nSize);
void DrvSerialFlashSectorErase(u32 nAddr);
void DrvSerialFlashWaitWriteDone(void);
u8   DrvSerialFlashGetStatus(void);
u8   DrvSerialFlashGetStatus2(void);
u8   DrvSerialFlashGetMXICSecStatus(void);
void DrvSerialFlashEraseSuspend(void);
void DrvSerialFlashEraseResume(void);
void DrvSerialFlashBlockErase(u32 nAddr, SPINORSector_e sector);
void DrvSerialFlashWriteStatus(u8 *pStatus, u8 nLength);
void DrvSerialFlashWriteEnable(void);

//***************************************************************************
// QSPI Drv
//***************************************************************************
void DrvQspiSetChipSelect(SPIQspiCS_e eQspiCS);
SPIQspiCS_e DrvQspiGetChipSelect(void);
void DrvQspiSetQuadAddr(void);


#endif /* __SYSSERIALFLASHDRV_H__ */
