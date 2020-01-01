///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   dwl_fms.h
// @author MStar Semiconductor Inc.
// @brief  Montage Wintarget Flash memory service header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DWL_FMS_H
#define _DWL_FMS_H

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "dwl_medium.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define FMS_MAX_FILENAME_LEN        (256 * 2)
#define FMS_FAT16_FORMAT            0x00
#define FMS_FAT32_FORMAT            0x01
#define FMS_FAT12_FORMAT            0x02
#define FMS_CUS_FILENAME            "CUSF"
#define FMS_RAI_FILENAME            "RAI"
#define FMS_BTRACE_FILENAME         "BTRACE"
/* RAI files folder */
#define RAI_FOLDER                  "__RAI__"

#define FMS_FAT_DISK1_IDX           0x00
#define FMS_FAT_DISK2_IDX           0x01

#define FMS_RO_E2P_PARTNUM          0x00
#define FMS_RW_E2P_PARTNUM          0x01
#define FMS_E2P_PARTCNT             0x02

#define FMS_DISK_CUS                0x00
#define FMS_DISK_E2P                0x01
#define FMS_DISK_BTRACE             0x02
#define FMS_DISK_RAI                0x03
#define FMS_DISK_FATU               0x04
#define FMS_DISK_NULL               0x05


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
typedef enum
{
    FMS_STORAGE_NOT_RDY = 0,
    FMS_STORAGE_INIT_DONE,
    FMS_STORAGE_INIT_ERR,
    FMS_STORAGE_NOT_SUPPORT,
    FMS_STORAGE_BAD_PARTTBL,
    FMS_STORAGE_NO_PARTTBL,
    FMS_STORAGE_MOUNT_ERR
} FMS_STAT_e;


//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
s32     MDrv_FS_FATFmt(u8 FATType, u32 TotalCapa);
u32     fms_calChkSum(void const *ptrorg, u32 u32size, u32 u32inputVal);
u32     fms_disk_capacity(u8 disktype);
void    fms_unicodePath(u8 *fileName);
u32     fms_getHighWater(dwl_handle_t phandle);
u32     fms_getTotLen(dwl_handle_t phandle);
u8 const    *fms_getFileName(dwl_handle_t phandle);
bool    fms_init(void);
bool    fms_init_phase2(void);
void    fms_uninit(void);
bool    fms_mkdir(u8 const *dirName);
bool    fms_rmdir(u8 const *dirName);
bool    fms_open(dwl_handle_t *pphandle, u32 u32type, u8 const *fileName);
void    fms_close(dwl_handle_t phandle);
s32     fms_read(dwl_handle_t phandle, void *pdata, u32 u32len);
s32     fms_allocate(dwl_handle_t *pphandle, u32 u32type,
                     u32 u32len, u8 const *fileName);
s32     fms_write(dwl_handle_t phandle, void *pdata, u32 u32len);
s32     fms_finalize(dwl_handle_t phandle, u32 u32chksum);
bool    fms_fatFormat(u8 u8diskNum, u8 u8fatType);
void    fms_hexval2str(char *buf, u32 value);
FMS_STAT_e  fms_getCurrStat(void);
void fms_setCurrStat(FMS_STAT_e state);

#endif  // _DWL_FMS_H
