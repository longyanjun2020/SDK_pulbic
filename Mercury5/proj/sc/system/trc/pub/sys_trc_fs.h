/**
 * \file trc_fs.h
 * \brief Management of Backtraces with File System in NAND
 *
 */

#ifndef __SYS_TRC_FS_H__
#define __SYS_TRC_FS_H__

#include "vm_types.ht"
#include "fms_trace.hi"

extern s32 trc_FsInit(void);
extern s32 trc_FsAddEntry(u32 i__u32_Ident, u32 i__u32_Size);
extern s32 trc_FsWriteEntry(const void *i__p_Buffer, u32 i__u32_Size);
extern s32 trc_FsFinalizeEntry(void);
extern s32 trc_FsFindInit(u32 i__u32_Ident);
extern s32 trc_FsFindNextEntry(fms_TrcHandle_t*o__ps_Handle);
extern s32 trc_FsQueryEntry(fms_TrcHandle_t *i__ps_Handle, fms_TrcInfo_t *o__ps_Info);
extern s32 trc_FsFindClose(fms_TrcHandle_t *i__ps_Handle);
extern s32 trc_FsStats(u32 *o__ps_Stats);
extern void trc_FsEraseAll(void);

#endif /* __SYS_TRC_FS_H__ */
