///////////////////////////////////////////////////////////////////////////////////////////////////
//   HEADER NAME:
//       storage.h
//
//   Written by Jeffrey.Chen@MSTAR Inc.
//---------------------------------------------------------------------
//
// Initial revision for ceramal 3
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "sys_MsWrapper_cus_os_type.h"

#ifndef STORAGE_H
#define STORAGE_H
///////////////////////////////////////////////////////////////////////////////////////////////////
// THIS HEADER IS FOR FCIE2 [CERAMAL3][BIGBLUE2] USE ONLY
///////////////////////////////////////////////////////////////////////////////////////////////////

/** \defgroup storage SD Card Driver
 * @ingroup Driver
 * @brief SD Card Driver and related functions
 * @details Provide SD Card driver initialization function, IO functions and related API for infomation acquire & debug.\n
            This driver support SDSC and SDHC up to 32GB uSD(t-flash).\n
            If uSD(s) are high speed switchable, driver will switch cards to high speed mode for gaining more performance.
 * @note
 **/

/**
 * @file    storage.h
 * @brief   SD driver related enum, structure, and API declaration
 */

/** \addtogroup storage
 *  @{
 * \file
 */

/**
 * @brief Slot Status Of Disk
 */
typedef enum
{
    E_SLOT_NONE        = 0x0000, ///< None card exist
    E_SLOT_NAND        = 0x0001, ///< NAND
    E_SLOT_SM          = 0x0002, ///< SM card
    E_SLOT_CF          = 0x0004, ///< CF
    E_SLOT_SDMMC       = 0x0008, ///< First SD Card
    E_SLOT_MSPRO       = 0x0010, ///< MS/PRO
    E_SLOT_XD          = 0x0020, ///< xD-Picture
    E_SLOT_SDIO        = 0x0040, ///< Second SD card if have
    E_SLOT_NAND_HIDDEN = 0x0080, ///< Hidden partition
    E_SLOT_CH          = 0x8000, ///< Any possible card change in disk
    E_SLOT_MASK        = 0x7FFF, ///< Slot mask
    //E_SLOT_NO_CH       = 0xFFFF,

} SLOT_STATUS;

/**
 * @brief Write Protect Enumeration For function MDrvIsDiskWriteProtect()
 */
typedef enum
{
    E_WP_OF = 0, ///< Not write protected SD card
    E_WP_ON = 1, ///< Write protected SD card

} WP_STATUS;

/**
 * @brief SD Card Read Write Access functions MDrvStorageR() MDrvStorageW() return enum
 */
typedef enum
{
    STS_SUCCESS              = 0x00, ///< Read write access complete with no error happen
    STS_CR_NOMEDIA           = 0x8D, ///< No SD card exist in designated disk index
    STS_CR_MEDIUM_FAILED     = 0x8E, ///< SD card initial fail
    STS_CR_WRITE_PROTECT     = 0x8F, ///< SD card at write portect stat
    STS_CR_SECTOR_ADDR_ERR   = 0x90, ///< Parameter u32StartSector & u32SectorCount combination out of range
    STS_CR_CARD_NOTREADY     = 0x92, ///< SD card is under initializing procedure
    STS_CR_IO_ERROR          = 0x93, ///< IO error happened while accessing
    STS_CR_CARD_INIT_FAIL    = 0x96, ///< SD driver internal use only
    STS_CR_CHG_NOT_HANDLE    = 0x99, ///< SD card just plug in or out, card detect monitor task is handling related job
    STS_CMP_FAIL_R_ONLY      = 0xF0, ///< SD driver in read only mode

} RW_STATUS;

/**
 * @brief SD Card bus state, return by function MDrvCheckSDBusStat()
 */
typedef enum
{
    SD_BUS_STAT_UNKNOW, ///< Unknown bus state
    SD_BUS_STAT_1_BIT,  ///< SD card run at only 1 bit mode
    SD_BUS_STAT_4_BITS, ///< SD card run at 4 bits mode

} SD_BUS_STAT;

/**
 * @brief Storage driver option. The parameter for function MDrvStorageInitial()
 */
typedef enum
{
    E_MODE_INTERPT = 0x00, ///< Interrutp mode
    E_MODE_POLLING = 0x01, ///< Polling mode

} STORAGE_MODE;

///@cond INTERNAL
/**
 * @brief For backtrace record SD driver reltaed information use
 */
typedef struct
{
    u32 StartTickR; ///< Last read  IO start  tick
    u32 FinisTickR; ///< Last read  IO finish tick
    u32 StartTickW; ///< Last write IO start  tick
    u32 FinisTickW; ///< Last write IO finish tick
    u16 DriverStat; ///< Stat record for debug use

} BACKTRACE_REC;
///@endcond

/**
 * @brief For function MDrvStorageGetSdCID() parameter 2 use
 */
typedef struct
{
    u8 Valid;   ///< Valid status flag, zero means the CID array not valid.
    u8 CID[16]; ///< Card IDentification register array

} STG_CARD_IDENT_INFO;

/**
 * @brief For function MDrvStorageBurstModeSet() and MDrvStorageBurstModeGet() parameter use
 */
typedef enum
{
    BURST_MODE_DIS = 0, ///< Disable burst mode
    BURST_MODE_EN,      ///< Enable burst mode

} BURST_MODE_SW;

#ifndef STG_DRIVER

/**
 * \fn u8 MDrvStorageInitial(STORAGE_MODE InitMode)
 * \brief Initialize hardware engine and related storage driver.
    If card (t-flash) exist while reference this function, initial the t-flash by the way.
 * \param[in] InitMode Init with interrupt mode in normal case and init with polling mode in exception handler.
 * \return None
 */
extern void MDrvStorageInitial(STORAGE_MODE InitMode);

///@cond INTERNAL
/**
 * \fn void MDrvStorageRegCapture(void)
 * \brief Store the storage driver related IP register in a static RAM buffer for ramdump.
    When exception happen. System need to re-initialize sd driver in polling mode for ramdump.
    So we need to save the storage related tregister for debugging SD driver
 * \return None
 */
extern void MDrvStorageRegCapture(void);
///@endcond

/**
 * \fn SLOT_STATUS MDrvCheckDiskStatus(u8 u8Disk, u8 u8Monitor)
 * \brief Check if a disk exist or not.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \param[in] u8Monitor  Storage monitor middleware use only, always call this api with u8Monitor equal to 0.
 * \retval E_SLOT_NONE  Means No SD card exist in this disk index
 * \retval E_SLOT_SDMMC Means SD card 1 exist in this disk index
 * \retval E_SLOT_SDIO  Means SD card 2 exist in this disk index
 */
extern SLOT_STATUS MDrvCheckDiskStatus(u8 u8Disk, u8 u8Monitor);

/**
 * \fn u8 MDrvInitialDisk(u8 u8Disk)
 * \brief Initialize a disk.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \retval 0 If disk initial success
 * \retval 1 When disk initial fail
 */
extern u8 MDrvInitialDisk(u8 u8Disk);

/**
 * \fn u32 MDrvGetDiskCapacity(u8 u8Disk)
 * \brief Get the disk capacity if disk exist.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \return If disk is ready, return the sector numbers of this disk.
    Multiple this value with 512(0x200) to get value in bytes.
 */
extern u32 MDrvGetDiskCapacity(u8 u8Disk);

/**
 * \fn WP_STATUS MDrvIsDiskWriteProtect(u8 u8Disk)
 * \brief Get the write protect (read only) status of a disk.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \retval E_WP_OF Means disk is readable and writable
 * \retval E_WP_ON Means disk is only readable.
 */
extern WP_STATUS MDrvIsDiskWriteProtect(u8 u8Disk);

/**
 * \fn RW_STATUS MDrvStorageR(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MemAddr)
 * \brief Provide the disk read function to read data from disk (memory card) to a memeory buffer.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \param[in] u32StartSector  Zero base sector index, this value must between 0 to value get from MDrvGetDiskCapacity()-1.
 * \param[in] u32SectorCount  To define the quantity of sector(s) want to read.
 * \param[in] u32MemAddr  Give the memeory address of the buffer ready to store the data read out.
 * \retval STS_SUCCESS  If read IO operation complete with no error
 * \retval OTHERS       Check enum RW_STATUS to get more error codes definition
 */
extern RW_STATUS MDrvStorageR(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MemAddr);

/**
 * \fn RW_STATUS MDrvStorageW(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MemAddr)
 * \brief Provide the disk write function to write data from a memory buffer to disk (memory card).
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \param[in] u32StartSector  Zero base sector index, this value must between 0 to value get from MDrvGetDiskCapacity()-1.
 * \param[in] u32SectorCount  To define the quantity of sector(s) want to write.
 * \param[in] u32MemAddr  Give the memeory address of the buffer prepared, write function will transfer this data to a disk (memory card).
 * \retval STS_SUCCESS  If write IO operation complete with no error
 * \retval OTHERS       Check enum RW_STATUS to get more error codes definition
 */
extern RW_STATUS MDrvStorageW(u8 u8Disk, u32 u32StartSector, u32 u32SectorCount, u32 u32MemAddr);

/**
 * \fn u8 MDrvSlot2Disk(SLOT_STATUS Status)
 * \brief Transfer the slot infomation to a zero base disk index number.
 * \param[in] Status  A slot status E_SLOT_SDMMC means the disk connect to FCIE IP and E_SLOT_SDIO means connect to SDIO IP.
 * \retval 0    Means "Sd card 1"
 * \retval 1    Means "Sd card 2".
 */
extern u8 MDrvSlot2Disk(SLOT_STATUS Status);

/**
 * \fn u16 MDrvDisk2Slot(u8 u8Disk)
 * \brief Transfer the disk index to the slot infomation.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \retval E_SLOT_SDMMC Means this disk connect to FCIE IP
 * \retval E_SLOT_SDIO  Means this disk connect to SDIO IP
 */
extern u16 MDrvDisk2Slot(u8 u8Disk);

///@cond INTERNAL
/**
 * \fn void MDrvSDProtect(void)
 * \brief Secrect function, check with jeffrey.chen to get more detail.
 * \return None
 */
extern void MDrvSDProtect(void);
///@endcond

/**
 * \fn SD_BUS_STAT MDrvCheckSDBusStat(u8 u8Disk)
 * \brief To know a SD card (t-flash) bus run at 1 bit mode or 4 bits mode
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \retval SD_BUS_STAT_UNKNOW   Means unknow status
 * \retval SD_BUS_STAT_1_BIT    Means 1 bit
 * \retval SD_BUS_STAT_4_BITS   Means 4 bits.
 */
extern SD_BUS_STAT MDrvCheckSDBusStat(u8 u8Disk);

///@cond INTERNAL
/**
 * \fn void MDrvGetSdBackTrace(BACKTRACE_REC * pBt4TF1, BACKTRACE_REC * pBt4TF2)
 * \brief Get the SD card related debug information for store in backtrace while system hang up.
 * \param[out] *pBt4TF1  The "sd card 1" related information
 * \param[out] *pBt4TF2  The "sd card 2" related information
 * \return None
 */
extern void MDrvGetSdBackTrace(BACKTRACE_REC * pBt4TF1, BACKTRACE_REC * pBt4TF2);
///@endcond

///@cond INTERNAL
/**
 * \fn void MdrvStorageSuspendWhenNobodyUse(void)
 * \brief Check the last access time and suspend when the last access time from the present 30 seconds
 * \return None
 */
extern void MdrvStorageSuspendWhenNobodyUse(void);
///@endcond

/**
 * \fn void MDrvStorageSuspend(u8 u8Force)
 * \brief Suspend all the disk(s) and cut related power and pad.
 * \param[in] u8Force  Force to do the suspend procedure again, normally call this api with u8Force = 0.
 * \return None
 */
extern void MDrvStorageSuspend(u8 u8Force);

/**
 * \fn void MDrvStorageResume(void)
 * \brief Resume all the disk(s).
 * \return None
 */
extern void MDrvStorageResume(void);

/**
 * \fn void MDrvStorageGetSdCID(u8 u8Disk, STG_CARD_IDENT_INFO * pCID)
 * \brief To get a SD card (t-flash) serial number in CID.
 * \param[in] u8Disk  Zero base disk index, normally 0 means "sd card 1" and 1 means "sd card 2".
 * \param[out] *pCID  A 16 bytes serial number in sd card.
 * \return None
 */
extern void MDrvStorageGetSdCID(u8 u8Disk, STG_CARD_IDENT_INFO * pCID);

///@cond INTERNAL

/**
 * \fn void DrvStgRestoreFcie(void)
 * \brief Fast resume function, use this only when resume after MMP off.
 * \return None
 */
extern void DrvStgRestoreFcie(void);

/**
 * \fn U8 DrvStgIsFcieActive(void)
 * \brief Check if storage driver still working.
 * \retval 1 If driver still working
 * \retval 0 For other cases.
 */
extern U8 DrvStgIsFcieActive(void);

/**
 * \fn void MDrvStorageBurstModeSet(BURST_MODE_SW BurstModeSwitch)
 * \brief SD burst mode control API. To Set burst mode status.
 * \return None
 */
extern void MDrvStorageBurstModeSet(BURST_MODE_SW BurstModeSwitch);

/**
 * \fn BURST_MODE_SW MDrvStorageBurstModeGet(void)
 * \brief SD burst mode control API. To get current status of burst mode.
 * \return None
 */
extern BURST_MODE_SW MDrvStorageBurstModeGet(void);

///@endcond

/** @}*/

#endif

#endif // #ifndef STORAGE_H

