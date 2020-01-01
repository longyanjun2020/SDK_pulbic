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
* @file    hal_flash_sst.h
* @version
* @brief   Flash SST HAL function include file
*
*/

#ifndef __HAL_FLASH_SST_H__
#define __HAL_FLASH_SST_H__


/**
  * @brief Issue a sector erase command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSST36VF16SectorErase( _ADDR_ ) do{     \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x80; \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)(_ADDR_) = 0x30;                      \
    }while(0)

/**
  * @brief Issue a sector erase command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSST36VF32SectorErase( _ADDR_ ) do{     \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x80; \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)(_ADDR_) = 0x50;                      \
    }while(0)


#define HalFlashCmdSST36VF16BlockErase(_X_) HalFlashCmdSST36VF32SectorErase(_X_)
#define HalFlashCmdSST36VF32BlockErase(_X_) HalFlashCmdSST36VF16SectorErase(_X_)

/**
  * @brief Enter in Query Sec ID mode
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSSTQuerySecID( _ADDR_ )   do{         \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                    \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x88; \
    }while(0)

#define FLASH_DEVICECODE_SST_SST36VF1601 0x734B
#define FLASH_DEVICECODE_SST_SST36VF1602 0x734A
#define FLASH_DEVICECODE_SST_SST36VF3203 0x7354
#define FLASH_DEVICECODE_SST_SST36VF3204 0x7353

#define FLASH_SECID_OFFSET_SST36VF1601 0
#define FLASH_SECID_OFFSET_SST36VF1602 0xC0000
#define FLASH_SECID_OFFSET_SST36VF3203 0x100000
#define FLASH_SECID_OFFSET_SST36VF3204 0

/**
  * @brief Issue a chip erase command
  *
  * @param _ADDR_ Targeted address (should be flash's base)
  */
#define HalFlashCmdSSTChipErase( _ADDR_ ) do{           \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                   \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x80; \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                   \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x10; \
    }while(0)

/**
  * @brief Common query CFI command
  *
  * This one sets a bank in CFI mode, whereas
  * the other one can still be read.
  *
  * @param _ADDR_ Address within the device to query
  */
#define HalFlashCmdSSTCfiQuery( _ADDR_ ) do{           \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                 \
        *(volatile u8*)( (_ADDR_) | (0x555L<<1)) = 0x98; \
    }while(0)


#endif //__HAL_FLASH_SST_H__