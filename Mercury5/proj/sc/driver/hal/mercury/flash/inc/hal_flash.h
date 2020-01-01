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
* @file    hal_flash.h
* @version
* @brief   Flash HAL function include file
*
*/

#ifndef __HAL_FLASH_H__
#define __HAL_FLASH_H__


/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
/**
  * @brief Loop timing value before erase suspend on WHAT2 for DrvFlashIntelErase
  */
#if 0
#define FLASH_ERASE_MAX_ITERATIONS_INTEL 350
/**
  * @brief Loop timing value before erase suspend on WHAT2 for DrvFlashAmdErase
  */
#define FLASH_ERASE_MAX_ITERATIONS_AMD 115
/**
  * @brief Loop timing value before erase suspend on WHAT2 for DrvFlashToshibaErase
  */
#define FLASH_ERASE_MAX_ITERATIONS_TOSHIBA 100

#define FLASH_OFFSET_TO_DEVICEID (0x01<<1)   ///< Offset to device ID in electronic signature
#define FLASH_OFFSET_TO_DEVICEID_2 (0x0E<<1)   ///< Offset to device 2nd ID in Spansion electronic signature
#define FLASH_OFFSET_TO_DEVICEID_3 (0x0F<<1)   ///< Offset to device 3rd ID in Spansion electronic signature
#define FLASH_OFFSET_TO_PROTECTFLAG (0x02<<1)   ///< Offset to block protection status in electronic signature
/**
  * @brief Offset to protection register (unique device number) in electronic signature
  */
#define FLASH_OFFSET_TO_ELECSIGNATURE (0x81<<1)

#define FLASH_CFI_OFFSET_TO_QUERYSTR_Q (0x10<<1)  ///< Offset to 'Q' in CFI query result
#define FLASH_CFI_OFFSET_TO_QUERYSTR_R (0x11<<1)  ///< Offset to 'R' in CFI query result
#define FLASH_CFI_OFFSET_TO_QUERYSTR_Y (0x12<<1)  ///< Offset to 'Y' in CFI query result
#define FLASH_CFI_OFFSET_TO_CMDSETID   (0x13<<1)  ///< Offset to command set code in CFI query result

#define FLASH_SAMSUNG_2883_PROTECT (0x02<<1)
#define FLASH_SAMSUNG_2883_UNPROTECT (0x42<<1)
#define FLASH_SAMSUNG_2883_PROTECT_CMD 0x60

#define FLASH_ADDOFF_555 (0x555L<<1)  ///< Special address 0x555 shifted because of 16-bit access
#define FLASH_ADDOFF_AAA (0x2AAL<<1)  ///< Special address 0xAAA shifted because of 16-bit access
#define FLASH_DATA_AA 0xAA         ///< Special value '0xAA'
#define FLASH_DATA_55 0x55         ///< Special value '0x55'

#define FLASH_ADDR_KEEPHIGH(_X_)  ((_X_) & ~0x3FFFFFFUL)
#define FLASH_UNEXPAND_BASE(_X_) (FLASH_ADDR_KEEPHIGH(_X_)>>26)
#define FLASH_EXPAND_BASE(_X_) ((_X_)<<26)
#define FLASH_ADDR_KEEPLOW(_X_)   (((unsigned int)(_X_)) & 0x3FFFFFFUL)

#define __USE_INTERRUPT_SUSPEND__
/*
    g_ptW5IrqControl->u32_Status0: 0x3400184C
    g_ptW5IrqControl->u32_Status1: 0x34001850
*/

#define FLASH_GET_INT_STATUS(x,y) \
    do{(x) = (*(volatile u32 *)(0x3400184C)); (y) = (*(volatile u32 *)(0x34001850));}while(0)
#endif
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/**
  * @brief Common query CFI command
  *
  * The offset is done for AMD command set flash devices
  * and Intel ones don't care
  *
  * @param _ADDR_ Address within the device to query
  */
#if 0
#define HalFlashCmdCfiQuery( _ADDR_ ) do{\
        *(volatile u8*)( FLASH_ADDR_KEEPHIGH(_ADDR_) | (0x55L<<1)) = 0x98;\
    }while(0)
#endif
#if 0 //infinity no need
/**
  * @brief Issue a "reset" to return in Read Array mode
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdIntelReset(_ADDR_)       do { *(volatile u8*)(_ADDR_) = 0xFF; } while(0)

/**
  * @brief Get the status register
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdIntelReadStatus(_ADDR_) ( *(volatile u8*)(_ADDR_) )

/**
  * @brief Clear the status register's errors
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdIntelClearStatus(_ADDR_) do { *(volatile u8*)(_ADDR_) = 0x50; } while(0)

/**
  * @brief Enter in electronic signature mode
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdIntelAutoSelect( _ADDR_ ) do{\
        *(volatile u8*)(_ADDR_) = 0x90;\
    }while(0)


/* Unlock write cycles for AMD command set flashs */
/**
  * @brief Flash operation prolog
  *
  * Common flash operations prolog for AMD command set flash devices
  * @param _ADDR_ Address within the flash device
  */
#define HalFlashInitWriteCmdSeq( _ADDR_ ) do{                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555 ) = FLASH_DATA_AA; \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_AAA ) = FLASH_DATA_55; \
    }while(0)

/**
  * @brief Enter in electronic signature mode
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdAutoSelect( _ADDR_ ) do{           \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( (_ADDR_) & (~0x7FFUL) ) | FLASH_ADDOFF_555) = 0x90; \
    }while(0)

/**
  * @brief Return in read array mode
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdReset( _ADDR_ ) do{ *(volatile u8*)(_ADDR_) = 0xF0; }while(0)

/**
  * @brief Issue a word program command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdWordProg( _ADDR_, _DATA_) do{      \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0xA0; \
        *(volatile u16*)(_ADDR_) = (u16)(_DATA_);          \
    }while(0)

/**
  * @brief Issue a block erase command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdBlockErase( _ADDR_ ) do{           \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x80; \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)(_ADDR_) = 0x30;                    \
    }while(0)

/**
  * @brief Issue an erase suspend command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdEraseSuspend( _ADDR_ ) do{ *(volatile u8*)(_ADDR_) = 0xB0; }while(0)

/**
  * @brief Issue an erase resume command
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdEraseResume( _ADDR_ )  do{ *(volatile u8*)(_ADDR_) = 0x30; }while(0)

// FIXME (not only for Toshiba)
/**
  * @brief Enter in security block mode (Toshiba)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdEnterSecSi( _ADDR_ )   do{         \
        HalFlashInitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FLASH_ADDR_KEEPHIGH(_ADDR_) ) | FLASH_ADDOFF_555) = 0x88; \
    }while(0)

/**
  * @brief Exit the security block mode (Toshiba)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdAmdExitSecSi( _ADDR_ )   do{ \
        HalFlashCmdAmdAutoSelect( (_ADDR_) );          \
        *(volatile u8*)(_ADDR_) = 0x00;           \
    }while(0)

/**
  * @brief Volatie sector protection Entry (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSpansionDybEntey( _ADDR_ )   do{ \
        HalFlashInitWriteCmdSeq((_ADDR_));\
        *(volatile u8*)( (_ADDR_ ) | FLASH_ADDOFF_555) = 0xE0; \
    }while(0)

/**
  * @brief Volatie sector protection Exit (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSpansionDybExit( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0x90;\
        *(volatile u8*)(_ADDR_) = 0x00;\
    }while(0)



/**
  * @brief Volatie sector protection set (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSpansionDybSet( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0xA0;\
        *(volatile u8*)(_ADDR_ ) = 0x00;\
    }while(0)


/**
  * @brief Volatie sector protection Clear (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSpansionDybClear( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0xA0;\
        *(volatile u8*)(_ADDR_ ) = 0x01;\
    }while(0)


/**
  * @brief Samsung_2833_protect
  *
  * @param _ADDR_ Targeted address
  */
#define HalFlashCmdSamsung2833Protect( _ADDR_ )   do{ \
        *(volatile u8*)( (_ADDR_ ) ) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) ) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) | FLASH_SAMSUNG_2883_PROTECT) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
    }while(0)
/**
  * @brief Samsung_2833_unprotect
  *
  * @param _ADDR_ Targeted address
  */

#define HalFlashCmdSamsung2833Unprotect( _ADDR_ )   do{ \
        *(volatile u8*)( (_ADDR_ ) ) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) ) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) | FLASH_SAMSUNG_2883_UNPROTECT) = FLASH_SAMSUNG_2883_PROTECT_CMD; \
    }while(0)
#endif
#endif //__HAL_FLASH_H__
