#ifndef __UT_DATAMGR_UTIL_FS_H__
#define __UT_DATAMGR_UTIL_FS_H__

#include "mmi_mae_common_def.h" 
#include "mmi_mae_interface_def.h"

#include "mae_datamgr.h"

typedef struct
{
    s32 mem_free;            // total byte amount of immediately available memory
    s32 mem_contig;          // byte amount of immediately available CONTIGUOUS memory
    s32 mem_avail;           // byte amount of memory available after complete garbage collection
    s32 mem_limit;           // total storage byte space
                             // (may be used as a scale factor for the other mem_xxx infos)
    s32 objects_read;        // number of objects read since last reboot
    s32 objects_created;     // number of objects created since last reboot
    s32 objects_overwritten; // number of objects overwritten since last reboot
    s32 objects_deleted;     // number of objects deleted since last reboot

    s32 sectors_erased;      // number of FLASH sectors erased since last reboot
#ifdef __NAND__
    int continuousmem[16];   // dump continuous memory space of each sector.
#endif

}UT_mmi_raiStats_t; 

typedef u16 mmi_raiSize_t;
typedef u32 mmi_raiId_t;

typedef struct
{
	mmi_raiSize_t size;
}UT_mmi_raiInfo_t;

typedef struct
{
    u32 nRaiID;
    u32 nRaiSize;
    u8 bIsUsed;
    void *pData;
}UT_raiData_t;

typedef struct 
{
    u32 opaque[4];
} UT_mmi_adHandle_t;


void UT_mmi_fs_raiInit(IBase *pIAccessory);
s32 UT_mmi_fs_raiWrite(mmi_raiId_t ident, mmi_raiSize_t size, const void * data);
u32 UT_mmi_fs_raiDelete (mmi_raiId_t ident);
s32 UT_mmi_fs_raiRead (mmi_raiId_t ident, mmi_raiSize_t start, mmi_raiSize_t length, void * data);
boolean UT_mmi_fs_raiInfo(u32 ident, UT_mmi_raiInfo_t *info);
void UT_mmi_fs_raiDestory(void);
void UT_mmi_fs_SetRaiWriteStatus(u8 bStatus);
void UT_mmi_fs_SetRaiReadStatus(u8 bStatus);
void UT_mmi_fs_SetRaiDeleteStatus(u8 bStatus);
void UT_mmi_fs_SetRaiInfoStatus(u8 bStatus);
#endif//__MAE_UTIL_FS_H__
