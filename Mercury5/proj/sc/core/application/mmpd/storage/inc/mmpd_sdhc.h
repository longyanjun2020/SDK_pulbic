/// @ait_only
#ifndef _MMPD_SDHC_H_
#define _MMPD_SDHC_H_

#include "mmp_err.h"
#include "ait_config.h"
#include "mmp_lib.h"
#include "mmpd_fs.h"

/**
 @file mmpd_sdhc.h
 @brief AIT SDHC driver (It ONLY works when MMP firmware is in active mode)
 @author Philip Lin
 @version 1.0
 <p>
 <b>Control Flow:</b><br>
 <pre>
 Step 1: Initial SD interface by calling MMPD_SDHC_InitialInterface().
 Step 2: Enable power switch for SD card, if need.
         (Only apply when AIT control power switch of SD card)
         (No used when Baseband control power switch of SD card)
 Step 3: Mount storage, to process reset sequence for SD memory card, by calling MMPS_FS_MountVolume().
 Step 4: Access SD card
   a. Check card in status by calling MMPD_SDHC_CheckCardIn().
   b. Check card write protect status by calling MMPD_SDHC_CheckCardWP().
   c. Check card status by calling MMPF_SDHC_CheckCardStatus().
   d. Get card size by calling MMPD_SDHC_GetSize(), if needed. Returns in Bytes.
   e. Read sector by calling MMPD_SDHC_Read(ulStartSector, *pBuf, ulSectorCnt).
   f. Read sector by calling MMPD_SDHC_Write(ulStartSector, *pBuf, ulSectorCnt).
 Step 5: Unmount storage, to sync AIT FS state machine for SD memory card, by calling MMPD_FS_UnmountVolume().
 Step 6: Disable power switch for SD card, if need.
         (Only apply when AIT control power switch of SD card)
         (No used when Baseband control power switch of SD card)
 </pre>
 </p>
*/

/** @addtogroup MMPD_SD
 *  @{
 */

/**
    @brief Initial SD interface
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_SDHC_InitialInterface(void);
/**
    @brief Enable power switch for SD card. Only works when AIT needs to control power of SD card.
    @param[in] bEnable Enable power switch for SD card. 1 means turn-on, 0 means turn-off.
    @return MMP_ERR_NONE
*/
MMP_ERR MMPD_SDHC_EnableCardPWR(MMP_BOOL bEnable);
/**
    @brief Check card-plug-in status
    @retval 0 No card exist
    @retval 1 Card exist
*/
MMP_USHORT MMPD_SDHC_CheckCardIn(void);

/**
    @brief Check write protect for SD card
    @retval 0 No write protect
    @retval 1 Write protect
*/
MMP_USHORT MMPD_SDHC_CheckCardWP(void);
/**
    @brief Get card status
    @retval MMP_ERR_NONE No error
    @retval MMP_SD_ERR_COMMAND_FAILED If any error
*/
MMP_ERR MMPD_SDHC_CheckCardStatus(void);
/**
    @brief Get SD card size. Returns in bytes.
    @param[out] ulSize Card size in Bytes.
    @retval MMP_ERR_NONE
    @retval MMP_SD_ERR_COMMAND_FAILED If any error
*/
MMP_ERR MMPD_SDHC_GetSize(MMP_ULONG *ulSize);
/**
    @brief Read data from specific SD Sector
    @param[in] ulStartSector Start sector number
    @param[in] pBuf Pointer of buffer to contain read data
    @param[in] ulSectorCnt Count of sector to read. For example, if you want to read 4 sector, please input 4. If you want to read 1024 byte, please input 1024/512=2.
    @retval MMP_ERR_NONE
    @retval MMP_SD_ERR_COMMAND_FAILED If any error
*/
MMP_ERR MMPD_SDHC_Read(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt);
/**
    @brief Write data into SD Sector
    @param[in] ulStartSector Start sector number
    @param[in] pBuf Pointer of buffer to contain read data
    @param[in] ulSectorCnt Count of sector to write. For example, if you want to write 2 sector, please input 2. If you want to read 4096 byte, please input 4096/512=8.
    @retval MMP_ERR_NONE
    @retval MMP_SD_ERR_COMMAND_FAILED If any error
*/
MMP_ERR MMPD_SDHC_Write(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt);

/// @}
#endif
/// @end_ait_only

