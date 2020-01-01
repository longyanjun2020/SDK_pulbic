/// @ait_only
/**
 @file mmpd_sdhc.c
 @brief AIT SDHC driver (It ONLY works when MMP firmware is in active mode)
 @author Philip Lin
 @version 1.0
*/

#include "ait_config.h"
#include "mmp_lib.h"
#include "mmph_hif.h"
#include "mmpd_sdhc.h"
#include "mmpd_fs.h"

/** @addtogroup MMPD_SD
 *  @{
 */

#ifdef  SUPPORT_PRAGMA
#pragma O2
#endif

MMP_BYTE    mFilename[100];
MMP_ULONG   mFilenameLength;

#if 0
#if 0
void __sDEFINE_APOLLO_RETINAV1_DIAMOND_DV1_MELODY__(){ruturn;} //dummy for IDE tool
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_SDHC_InitialInterface
//------------------------------------------------------------------------------
MMP_ERR  MMPD_SDHC_InitialInterface(void)
{
    return  MMP_ERR_NONE;
} /* MMPD_SD_InitialInterface */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_EnableCardPWR
//------------------------------------------------------------------------------
MMP_ERR MMPD_SDHC_EnableCardPWR(MMP_BOOL bEnable)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMPD_FS_IOCTL_PARA Aux;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Control power for SD card
    Cmd = MMPS_FS_CMD_PWR_DISABLE;
    Aux.ulPara[0] = bEnable;

    status = MMPD_FS_IOCtl(mFilename, mFilenameLength, Cmd, &Aux, (void *) 0);
    if(status!=MMP_ERR_NONE) {
        return MMP_SD_ERR_COMMAND_FAILED;
    }
    return MMP_ERR_NONE;

} /* MMPD_SDHC_EnableCardPWR */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_CheckCardIn
//------------------------------------------------------------------------------
MMP_USHORT MMPD_SDHC_CheckCardIn(void)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Check card in
    Cmd = MMPD_FS_CMD_CARD_DETECT;
    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, 0, (void *)0);
    if (status) {
        //PRINTF("card detect\n");
        return 1;
    }
    else {
        //PRINTF("no card detect\n");
        return 0;
    }

} /* MMPD_SDHC_CheckCardIn */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_CheckCardWP
//------------------------------------------------------------------------------
MMP_USHORT MMPD_SDHC_CheckCardWP(void)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Check card write protect
    Cmd = MMPD_FS_CMD_WRITE_PROTECT;
    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, 0, (void *)0);
    if (status) {
        //PRINTF("write protect\n");
        return 1;
    }
    else {
        //PRINTF("no write protect\n");
        return 0;
    }

} /* MMPD_SDHC_CheckCardWP */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_CheckCardStatus
//------------------------------------------------------------------------------
MMP_ERR MMPD_SDHC_CheckCardStatus(void)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Check card status
    Cmd = MMPD_FS_CMD_GET_CARDSTATUS;
    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, 0, (void *)0);
    if(status != MMP_ERR_NONE) {
        return status;
    }
    return MMP_ERR_NONE;

} /* MMPD_SDHC_CheckCardStatus */

#if 0
void __eDEFINE_APOLLO_RETINAV1_DIAMOND_DV1_MELODY__(){ruturn;} //dummy for IDE tool
#endif
#endif  /* #if 0 */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_GetSize
//------------------------------------------------------------------------------
MMP_ERR MMPD_SDHC_GetSize(MMP_ULONG *ulSize)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // get card status
    Cmd = MMPD_FS_CMD_GET_DEVINFO;
    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, 0, (void *)ulSize);
    if(status != MMP_ERR_NONE) {
        return status;
    }
    return MMP_ERR_NONE;

} /* MMPD_SDHC_GetSize */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_Read
//------------------------------------------------------------------------------
MMP_ERR  MMPD_SDHC_Read(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMPD_FS_IOCTL_PARA Aux;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Read sector
    Cmd = MMPS_FS_CMD_READ_SECTOR;
    Aux.ulPara[0] = ulStartSector;
    Aux.ulPara[1] = ulSectorCnt;

    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, &Aux, (void *)pBuf);
    if (MMP_ERR_NONE != status) {
        //PRINTF("read sector fail\n");
        return MMP_SD_ERR_COMMAND_FAILED;
    }
    return MMP_ERR_NONE;

} /* MMPD_SDHC_Read */

//------------------------------------------------------------------------------
// FUNCTION : MMPD_SDHC_Write
//------------------------------------------------------------------------------
MMP_ERR  MMPD_SDHC_Write(MMP_ULONG ulStartSector, MMP_UBYTE* pBuf, MMP_ULONG ulSectorCnt)
{
    MMPD_FS_IOCTL_CMD Cmd;
    MMPD_FS_IOCTL_PARA Aux;
    MMP_ERR status;

    #if (FS_INPUT_ENCODE == UCS2)
    WSTRCPY(mFilename, "SD:\\");
    mFilenameLength = WSTRLEN((const short *)mFilename);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(mFilename, "SD:\\");
    mFilenameLength = STRLEN(mFilename);
    #endif

    // Write sector
    Cmd = MMPS_FS_CMD_WRITE_SECTOR;
    Aux.ulPara[0] = ulStartSector;
    Aux.ulPara[1] = ulSectorCnt;

    status = MMPD_FS_IOCtl(mFilename, mFilenameLength , Cmd, &Aux, (void *)pBuf);
    if ( MMP_ERR_NONE != status) {
        //PRINTF("write sector fail\n");
        return MMP_SD_ERR_COMMAND_FAILED;
    }
    return MMP_ERR_NONE;

} /* MMPD_SDHC_Write */

/// @}
/// @end_ait_only
