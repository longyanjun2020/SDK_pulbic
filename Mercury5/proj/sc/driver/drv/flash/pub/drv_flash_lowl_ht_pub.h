////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    drv_flash_lowl_ht_pub.h
* @version
* @brief   Flash Memory Services - Type definitions
*
*/

#ifndef __DRV_FLASH_LOWL_HT_PUB_H__
#define __DRV_FLASH_LOWL_HT_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef s32 DrvFlashErrCode_n;

/* Write */
typedef DrvFlashErrCode_n(*PfnFlashProgramFunc)(u32, u32);

/* Erase */
typedef DrvFlashErrCode_n(*PfnFlashEraseFunc)(u32, u32);

/* SetProtect */
typedef DrvFlashErrCode_n(*PfnFlashSetProtectFunc)(u32, u32);

/* ExtendedCmd */
typedef DrvFlashErrCode_n(*PfnFlashExtendedCmdFunc)(u32, u32, void*);

/* Buffer Write */
typedef DrvFlashErrCode_n(*PfnFlashBufferProgramFunc)(u32, u16*,u32);

/* voidf */
typedef void (*PfnFlashVoidFunc)(void);


/*=============================================================*/
// Macro definition
/*=============================================================*/
//#define FMS_WRITE_DEBUG

#ifdef __GNUC__ /* Gnu C compiler */
#define FLASH_ZERO_SIZE_ARRAY 0
#elif defined(_MSC_VER) /* Visual C++, ...etc */
#define FLASH_ZERO_SIZE_ARRAY 1
#elif defined(__ARMCC_VERSION)  /* ARMCC */
/* Any version lower than 1.2 is rejected */
#if __ARMCC_VERSION < 120000
#error This version of ARM C Compiler is too old!
#endif
#define FLASH_ZERO_SIZE_ARRAY
#elif defined(S_SPLINT_S)
#define FLASH_ZERO_SIZE_ARRAY 1
#else
#error Unknown compiler
#endif /* Compilers */


/****************************************************************************/
/* ERROR CODE                                                               */
/****************************************************************************/
#define FLASH_OK             0
#define FLASH_DELAYED        0x1   /* Returned by fms_XXX_Erase when erasure is suspended */
#define FLASH_RETRY          0x2   /* Returned by fms_XXX_Erase when erasure needs retry */


#define FLASH_BAD            0xFFFFFFFF
#define FLASH_UNDEFINED      0xFFFFFFFF

#define FLASH_BAD_ARGS       0xFFFFFFFE
#define FLASH_BAD_FUNCTION   0xFFFFFFFD
#define FLASH_FORBIDDEN      0xFFFFFFFC
#define FLASH_HW_ERROR       0xFFFFFFFB
#define FLASH_SEQUENCE_ERROR 0xFFFFFFFA
#define FLASH_OVERFLOW       0xFFFFFFF9
#define FLASH_CMD_FAILED     0xFFFFFFF8
#define FLASH_TIMEOUT        0xFFFFFFF7
#define FLASH_REACHED_END    0xFFFFFFF6
#define FLASH_NOT_AVAILABLE  0xFFFFFFF5
#define FLASH_DAMAGED        0xFFFFFFF4
#define FALSH_CLEANING_REQD  0xFFFFFFF3
#define FLASH_CMD_FAILED2    0xFFFFFFF2
#define FLASH_NO_CHANGE      0xFFFFFFF1 // no change when trying to change an eeprom parameter


/****************************************************************************/
/* ERASURE AND PROTECTION MODES                                             */
/****************************************************************************/
#define FLASH_ERASE_NORMAL      1
#define FLASH_ERASE_NO_SUSPEND  2
#define FLASH_ERASE_RESUME      4
#define NOR_ERASE_SECTOR4K    0x10//<bit4>
#define NOR_ERASE_BLOCK32K    0x20//<bit5>

#define FLASH_PROGRAM_NORMAL      1
#define FLASH_PROGRAM_NO_SUSPEND  2
#define FLASH_PROGRAM_RESUME      4

#define FLASH_PROTECT_DEACTIVATE 1
#define FLASH_PROTECT_ACTIVATE   2
#define FLASH_PROTECT_LOCKDOWN   4
#define FLASH_PROTECT_RANGE      8


/****************************************************************************/
/* EXTENDED COMMANDS                                                        */
/****************************************************************************/
#define FLASH_CMD_READ_SERIALNUMBER      1 /* Returns the device S/N                                          */
#define FLASH_CMD_GET_FLASH_NAME         2 /* Returns the device part name                                    */
#define FLASH_CMD_GET_DEVICE_SIZE        3 /* Returns the size of the device                                  */
#define FLASH_CMD_DWL_SUSPENDERASE       4 /* Suspends an erase process                                       */
#define FLASH_CMD_DWL_RESUMEERASE        5 /* Resumes a suspended erasure                                     */
#define FLASH_CMD_GET_DEVICE_ID          6 /* Returns the manufacturer+device code                            */
#define FLASH_CMD_PERMANENT_LOCK_STATUS  7 /* Returns FMS_OK if the permanent locking feature can be disabled */
#define FLASH_CMD_PREVENT_PERMANENT_LOCK 8 /* Deactivates the permanent locking feature                       */
#define FLASH_CMD_ACTIVATE_SYNCHRONOUS   9 /* Set the device in synchronous mode                              */
#define FLASH_CMD_DEACTIVATE_SYNCHRONOUS 10 /* Exit the device from synchronous mode                          */
#define FLASH_CMD_GET_SMALL_BLOCK_START_ADDR 11 /*Returns the small block Start addr*/

/****************************************************************************/
/* FEATURES OF THE FLASH MEMORY DEVICE                                      */
/****************************************************************************/
#define FLASH_FEATURE_SECTOR_PROTECTION       (1<<0)
#define FLASH_FEATURE_MULTILEVELCELL          (1<<1)
#define FLASH_FEATURE_PERMANENT_BLOCK_LOCKING (1<<2)
#define FLASH_FEATURE_SYNCHRONOUS_MODE        (1<<3)


/****************************************************************************/
/* GEOMETRY-RELATED TYPES                                                   */
/****************************************************************************/

typedef struct
{
    u16 nShiftedSize; /* Block size = 2 ^ u16_ShiftedSize  */
    u16 nNumber;
} FlashDeviceSectorRegion_t;

typedef struct
{
    u16 nDeviceSize; /* Device size = u16_DeviceSize * 64 KiB */
    u8 nPad;
    u8 nRegionNumber;
    FlashDeviceSectorRegion_t nAsRegions[FLASH_ZERO_SIZE_ARRAY];
} FlashDeviceGeometry_t;


/****************************************************************************/
/* BANKS                                                                    */
/****************************************************************************/

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[FLASH_ZERO_SIZE_ARRAY];
} FlashBanksDescriptor_t;


/****************************************************************************/
/* CHIP DESCRIPTOR                                                          */
/****************************************************************************/

#define FLASH_NUMBER_OF_FUNC_IN_DEVDESCRIPTOR (5)

typedef struct
{
    /* Joined manufacturer code and device code */
    u32 nDeviceFullId;

    /* Supported features */
    u32 nFeatures;

    /* Device geometry */
    FlashDeviceGeometry_t *ptGeometry;
    FlashBanksDescriptor_t *ptBanks;

    /* RAM based low-level functions */
    PfnFlashProgramFunc pfnFlashProgram;
    PfnFlashEraseFunc pfnFlashErase;
    PfnFlashSetProtectFunc pfnFlashSetProtect;
    PfnFlashExtendedCmdFunc pfnFlashExtendedCmd;
    PfnFlashBufferProgramFunc pfnFlashBufferProgram;
} FlashDeviceDescriptor_t;


/****************************************************************************/
/* CHIP DIRECTORY                                                           */
/****************************************************************************/

typedef struct
{
    u32   nPresentUserDevices;
    u16   nUserDevicesNumber;
    FlashDeviceDescriptor_t *ptDevices;
} FlashChipDirStruct_t;


/****************************************************************************/
/* DEVICE IDENTIFICATION RELATED                                            */
/****************************************************************************/



#if defined(__DEVICE_INFO__)

typedef struct
{
    u32 nDeviceFullId;
    char *pszFlashName;
    u32 nProdId;
} FlashIdentifier_t;

#else

typedef struct
{
    u32 nDeviceFullId;
#ifdef __DOWNLOADER__
    char *pszFlashName;
#else
    u32 nProdId;
#endif //__DOWNLOADER__
} FlashIdentifier_t;

#endif

/*=============================================================*/
// Global function definition
/*=============================================================*/
u32 DrvFlashGetFlashTypeExt(void);
void DrvFlashSetFlashTypeExt(u32 nFlashType);

DrvFlashErrCode_n DrvFlashProgram(u32 nAddress, u32 nData);
DrvFlashErrCode_n DrvFlashBufferProgram(u32 nAddress, u16 *pData);
DrvFlashErrCode_n DrvFlashErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashSetProtect(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashRead(u32 nAddress, u32 nData, u32 nSize);
#if 0
DrvFlashErrCode_n DrvFlashWinbondErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashWinbondSetProtect(u32 i__u32_Address, u32 i__u32_Mode);
DrvFlashErrCode_n DrvFlashWinbondExtendedCmd(u32 i__u32_Function, u32 i__u32_Address, void *io__p_Buffer);


DrvFlashErrCode_n DrvFlashMacronixErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashMacronixSetProtect(u32 i__u32_Address, u32 i__u32_Mode);
DrvFlashErrCode_n DrvFlashMacronixExtendedCmd(u32 i__u32_Function, u32 i__u32_Address, void *io__p_Buffer);

DrvFlashErrCode_n DrvFlashEONSIProgram(u32 nAddress, u32 nData);
DrvFlashErrCode_n DrvFlashEONSIBufferProgram(u32 nAddress, u16 *pData);
DrvFlashErrCode_n DrvFlashEONSIErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashMicronErase(u32 nAddress, u32 nMode);

DrvFlashErrCode_n DrvFlashGDProgram(u32 nAddress, u32 nData);
DrvFlashErrCode_n DrvFlashGDBufferProgram(u32 nAddress, u16 *pData);
DrvFlashErrCode_n DrvFlashGDErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashGDSetProtect(u32 i__u32_Address, u32 i__u32_Mode);
DrvFlashErrCode_n DrvFlashGDExtendedCmd(u32 i__u32_Function, u32 i__u32_Address, void *io__p_Buffer);

DrvFlashErrCode_n DrvFlashESMTErase(u32 nAddress, u32 nMode);
DrvFlashErrCode_n DrvFlashESMTSetProtect(u32 i__u32_Address, u32 i__u32_Mode);


/** DrvFlashAmdProgram
* @brief        FLASH PROGRAM OPERATION FOR AMD COMMAND SET DEVICE
*
* @param[in]    nAddress             Program start address.
* @param[in]    nData                Program data.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashAmdProgram(u32 nAddress, u32 nData);

/** DrvFlashAmdProgram
* @brief        FLASH PROGRAM OPERATION FOR AMD COMMAND SET DEVICE
*
* @param[in]    nAddress             Program start address.
* @param[in]    nData                Program data.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
//DrvFlashErrCode_n DrvFlashAmdProgram(u32 nAddress, u32 nData);
#ifdef FMS_WRITE_DEBUG
DrvFlashErrCode_n DrvFlashAmdProgramtest1(u32 nAddress, u32 nData);
#endif

/** DrvFlashAmdNoProtectProgram
* @brief        FLASH PROGRAM OPERATION FOR TOSHIBA (AMD COMMAND SET DEVICE)
* @brief        Whitout protection features available
* @brief        Data toggle bits check does not work properly with Toshiba Flashs.
*
* @param[in]    nAddress            Protect start address.
* @param[in]    nMode               Protect option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashAmdNoProtectProgram(u32 nAddress, u32 nData);

/** DrvFlashAmdErase
* @brief        FLASH ERASE OPERATION FOR AMD COMMAND SET DEVICE
*
* @param[in]    nAddress            Erase start address.
* @param[in]    nMode               Erase option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashAmdErase(u32 nAddress, u32 nMode);

/** DrvFlashAmdSetProtect
* @brief        FLASH SECTOR PROTECTION MANAGEMENT FOR AMD
*
* @param[in]    nAddress            Protect start address.
* @param[in]    nMode               Protect option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashAmdSetProtect(u32 nAddress, u32 nMode);

/** DrvFlashToshibaErase
* @brief        FLASH ERASE OPERATION FOR TOSHIBA
* @brief        Whitout protection features available
* @brief        Data toggle bits checking does not work properly with Toshiba Flashs.
*
* @param[in]    nAddress            Erase start address.
* @param[in]    nMode               Erase option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashToshibaErase(u32 nAddress, u32 nMode);

/** DrvFlashToshibaExtendedCmd
* @brief        OTHER FLASH OPERATIONS FOR TOSHIBA
*
* @param[in]    nFunction            Extended command function.
* @param[in]    nAddress             Operation start address.
* @param[in]    *pBuffer             Operation buffer pointer.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashToshibaExtendedCmd(u32 nFunction, u32 nAddress, void *pBuffer);

/** DrvFlashSpansionSetProtect
* @brief        FLASH SECTOR PROTECTION MANAGEMENT FOR SPANSION
*
* @param[in]    nAddress            Protect start address.
* @param[in]    nMode               Protect option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashSpansionSetProtect(u32 nAddress, u32 nMode);

/** DrvFlashSamsung2833SetProtect
* @brief        FLASH SECTOR PROTECTION MANAGEMENT FOR Samsung
*
* @param[in]    nAddress            Protect start address.
* @param[in]    nMode               Protect option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashSamsung2833SetProtect(u32 nAddress, u32 nMode);

/** DrvFlashSpansionExtendedCmd
* @brief        OTHER FLASH OPERATIONS FOR SPANSION
*
* @param[in]    nFunction            Extended command function.
* @param[in]    nAddress             Operation start address.
* @param[in]    *pBuffer             Operation buffer pointer.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashSpansionExtendedCmd(u32 nFunction, u32 nAddress, void *pBuffer);

/** DrvFlashToshibaErase2
* @brief        FLASH ERASE OPERATION FOR TOSHIBA
* @brief        Whitout protection features available
* @brief        Data toggle bits checking does not work properly with Toshiba Flashs.
*
* @param[in]    nAddress            Erase start address.
* @param[in]    nMode               Erase option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashToshibaErase2(u32 nAddress, u32 nMode);

/** DrvFlashToshibaSetProtect
 * @brief        FLASH SECTOR PROTECTION MANAGEMENT FOR TOSHIBA
 *
 * @param[in]    nAddress            Protect start address.
 * @param[in]    nMode               Protect option mode.
 *
 * @retval       FLASH_OK            Success.
 * @retval       Other               Failed.
 */
s32 DrvFlashToshibaSetProtect(u32 nAddress, u32 nMode);

/** DrvFlashIntelProgram
* @brief        FLASH PROGRAM OPERATION FOR INTEL
*
* @param[in]    nAddress             Program start address.
* @param[in]    nData                Program data.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashIntelProgram(u32 nAddress, u32 nData);

/** DrvFlashIntelBufferProgram
* @brief        FLASH BUFFER PROGRAM OPERATION FOR INTEL (32 16bits words)
*
* @param[in]    nAddress             Buffer program start address.
* @param[in]    *pData               Buffer program data pointer.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashIntelBufferProgram(u32 nAddress, u16 *pData , u32 nMode);

/** DrvFlashIntelErase
* @brief        FLASH ERASE OPERATION FOR INTEL
*
* @param[in]    nAddress            Erase start address.
* @param[in]    nMode               Erase option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashIntelErase(u32 nAddress, u32 nMode);

/** DrvFlashIntelSetProtect
* @brief        FLASH SECTOR PROTECTION MANAGEMENT FOR INTEL
*
* @param[in]    nAddress            Protect start address.
* @param[in]    nMode               Protect option mode.
*
* @retval       FLASH_OK            Success.
* @retval       Other               Failed.
*
*/
DrvFlashErrCode_n DrvFlashIntelSetProtect(u32 nAddress, u32 nMode);

/** DrvFlashIntelExtendedCmd
* @brief        OTHER FLASH OPERATIONS FOR INTEL
*
* @param[in]    nFunction            Extended command function.
* @param[in]    nAddress             Operation start address.
* @param[in]    *pBuffer             Operation buffer pointer.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashIntelExtendedCmd(u32 nFunction, u32 nAddress, void *pBuffer);

/** DrvFlashStIntelExtendedCmd
* @brief        OTHER FLASH OPERATIONS FOR ST INTEL
*
* @param[in]    nFunction            Extended command function.
* @param[in]    nAddress             Operation start address.
* @param[in]    *pBuffer             Operation buffer pointer.
*
* @retval       FLASH_OK             Success.
* @retval       Other                Failed.
*
*/
DrvFlashErrCode_n DrvFlashStIntelExtendedCmd(u32 nFunction, u32 nAddress, void *pBuffer);

/** DrvFlashProbe
* @brief        The probe function issues the "Read Electronic Signature" commands
* @brief        for both INTEL and AMD command sets.
* @brief        If there is no response to both Intel and AMD commands, 0 is returned.
* @brief        The BaseAddress parameter is the address where the flash device is
* @brief        supposed to be.
*
* @param[in]    nBaseAddress        Base address of probe.
*
* @retval       nIdentifier         Flash Identifier.
* @retval       NULL                Failed.
*
*/
#endif
u32 DrvFlashProbe(u32 nBaseAddress);

/** DrvFlashSetRaiStressTestFlag
* @brief        Set rai stress test flag
*
* @param[in]    nFlag             stress test flag.
*
* @retval       FLASH_OK          set success.
* @retval       DRV_FLASH_FIAL    set failed.
*
*/
DrvFlashErrCode_n DrvFlashSetRaiStressTestFlag(u32 nFlag);

/** DrvFlashGetRaiStressTestFlag
* @brief        Get rai stress test flag
*
* @param[in]    nFlag             stress test flag.
*
* @retval       FLASH_OK          get success.
* @retval       DRV_FLASH_FIAL    get failed.
*
*/
DrvFlashErrCode_n DrvFlashGetRaiStressTestFlag(u32 *pnFlag);

/** DrvFlashSetEraseCnt
* @brief        Set flash erase counter
*
* @param[in]    void
*
* @retval       FLASH_OK          set success.
* @retval       DRV_FLASH_FIAL    set failed.
*
*/
DrvFlashErrCode_n DrvFlashSetEraseCnt(void);

/** DrvFlashGetEraseCnt
* @brief        Get flash erase counter
*
* @param[in]    pnCnt             erase counter.
*
* @retval       FLASH_OK          get success.
* @retval       DRV_FLASH_FIAL    get failed.
*
*/
DrvFlashErrCode_n DrvFlashGetEraseCnt(u32 *pnCnt);

/** DrvFlashSetSuspendCnt
* @brief        Set flash suspend counter
*
* @param[in]    void
*
* @retval       FLASH_OK          set success.
* @retval       DRV_FLASH_FIAL    set failed.
*
*/
DrvFlashErrCode_n DrvFlashSetSuspendCnt(void);

/** DrvFlashGetSuspendCnt
* @brief        Get flash suspend counter
*
* @param[in]    pnCnt             suspend counter.
*
* @retval       FLASH_OK          get success.
* @retval       DRV_FLASH_FIAL    get failed.
*
*/
DrvFlashErrCode_n DrvFlashGetSuspendCnt(u32 *pnCnt);

/** DrvFlashSetResumeCnt
* @brief        Set flash resume counter
*
* @param[in]    void
*
* @retval       FLASH_OK          set success.
* @retval       DRV_FLASH_FIAL    set failed.
*
*/
DrvFlashErrCode_n DrvFlashSetResumeCnt(void);

/** DrvFlashGetResumeCnt
* @brief        Get flash resume counter
*
* @param[in]    pnCnt             resume counter.
*
* @retval       FLASH_OK          get success.
* @retval       DRV_FLASH_FIAL    get failed.
*
*/
DrvFlashErrCode_n DrvFlashGetResumeCnt(u32 *pnCnt);

//MSZ Sersen
/** DrvFlashGetManufacturerID
* @brief        Get flash manufactur id
* @param[in]
* @retval       manufactur id
*/
u32 DrvFlashGetManufacturerID(void);

/** DrvFlashGetWriteBufferLen
* @brief        Get length of SPI flash write buffer
* @param[in]    void
* @return       length of write buffer
*/
u32 DrvFlashGetWriteBufferLen(void);

/** DrvFlashResetProcedure
* @brief        SPI Flash Reset Procedure
* @param[in]    void
* @return       None
*/
void DrvFlashResetProcedure(void);
#endif // __DRV_FLASH_LOWL_HT_PUB_H__
