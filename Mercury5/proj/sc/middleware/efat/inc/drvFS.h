#ifndef _DRVFS_H
#define _DRVFS_H
#include <pkgconf_system.h>
#include <pkgconf_hal.h>

#define FMS_FAT16_FORMAT            0x00
#define FMS_FAT32_FORMAT            0x01
#define FMS_FAT12_FORMAT            0x02


s32 MDrv_FS_FmtCardToFAT(U8 FATType,U8 * DevName,U32 TotalCapa);
void MdrvFS_FMTSetPauseState(U8 pause_on);
void MdrvFS_FMTSetAbortState(U8 abort_on);

#endif //_DRVFS_H

