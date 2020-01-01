/// @ait_only
/**
 @file mmps_sdhc.c
 @brief AIT SDHC driver (It ONLY works when MMP firmware is in active mode)
 @author Philip Lin
 @version 1.0
*/

#include "ait_config.h"
#include "mmp_lib.h"
#include "mmph_hif.h"
#include "mmpd_sdhc.h"
#include "mmpd_fs.h"

/** @addtogroup MMPS_SD
 *  @{
 */

//------------------------------------------------------------------------------
//  Function    : MMPS_SDHC_InitialInterface
//------------------------------------------------------------------------------
MMP_ERR  MMPS_SDHC_InitialInterface(void)
{
    return  MMPD_SDHC_InitialInterface();
} /* MMPD_SD_InitialInterface */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_EnableCardPWR
//------------------------------------------------------------------------------
MMP_ERR MMPS_SDHC_EnableCardPWR(MMP_BOOL bEnable)
{
    return MMPD_SDHC_EnableCardPWR(bEnable);
} /* MMPS_SDHC_EnableCardPWR */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_CheckCardIn
//------------------------------------------------------------------------------
MMP_USHORT MMPS_SDHC_CheckCardIn(void)
{
    return MMPD_SDHC_CheckCardIn();
} /* MMPS_SDHC_CheckCardIn */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_CheckCardWP
//------------------------------------------------------------------------------
MMP_USHORT MMPS_SDHC_CheckCardWP(void)
{
    return MMPD_SDHC_CheckCardWP();
} /* MMPS_SDHC_CheckCardWP */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_CheckCardStatus
//------------------------------------------------------------------------------
MMP_ERR MMPS_SDHC_CheckCardStatus(void)
{
    return MMPD_SDHC_CheckCardStatus();
} /* MMPS_SDHC_CheckCardStatus */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_GetSize
//------------------------------------------------------------------------------
MMP_ERR MMPS_SDHC_GetSize(MMP_ULONG *ulSize)
{
    return  MMPD_SDHC_GetSize(ulSize);
} /* MMPS_SDHC_GetSize */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_Read
//------------------------------------------------------------------------------
MMP_ERR  MMPS_SDHC_Read(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt)
{
    return MMPD_SDHC_Read(ulStartSector, pBuf, ulSectorCnt);
} /* MMPS_SDHC_Read */

//------------------------------------------------------------------------------
// FUNCTION : MMPS_SDHC_Write
//------------------------------------------------------------------------------
MMP_ERR  MMPS_SDHC_Write(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt)
{
    return MMPD_SDHC_Write(ulStartSector, pBuf, ulSectorCnt);
} /* MMPS_SDHC_Write */

/// @}
/// @end_ait_only
