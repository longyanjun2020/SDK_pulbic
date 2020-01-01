/****************************************************************************/
/*  File    : sys_fat.h                                              		*/
/*--------------------------------------------------------------------------*/
/* PURPOSE:																	*/
/* This file opens public interfaces for NOR FAT operations.				*/
/*																			*/
/* NOTES:																	*/
/*																			*/
/*                                                                          */
/****************************************************************************/
#ifndef __SYS_FAT_H__
#define __SYS_FAT_H__

/*_____ I N C L U D E S ____________________________________________________*/

#include "vm_types.ht"
#include "fs_error.h"
#include "mdl_vfs_fat.ho"

#ifndef O_RDONLY
#define O_RDONLY              (0)
#endif
#ifndef O_WRONLY
#define O_WRONLY              (1)
#endif
#ifndef O_RDWR
#define O_RDWR                (2)
#endif
#ifndef O_CREAT
#define O_CREAT               (0x200)
#endif
#ifndef O_TRUNC
#define O_TRUNC               (0x400)
#endif
#ifndef O_APPEND
#define O_APPEND              (0x800)
#endif

#define FS_SEEK_SET        0       /* set file offset to offset */
#define FS_SEEK_CUR        1       /* set file offset to current plus offset */
#define FS_SEEK_END        2       /* set file offset to EOF plus offset */

s32 fs_check_dev_support(void);
s32 fs_init(u8 nb_files);

s32 fs_mount (void);
s32 fs_mount_dev (VFS_DevType_e devId);
s32 fs_unmount (void);
s32 fs_unmount_dev (void);
s32 fs_format (void);
s32 fs_get_volume_name (u16 name[32]);

s32 fs_open(u16 *name, s32 mode);
s32 fs_close(u32 file_ref);
s32 fs_read(u32 file_ref, u8*,u32);
s32 fs_write(u32 file_ref, u8 *buffer, u32 nb_data);
s32 fs_eof(u32 file_ref);
s32 fs_seek(u32 file_ref, s32 offset, s32 position);
s32 fs_tell(u32 file_ref);
s32 fs_get_open_file_info(u32 file_ref, VFS_File_Info_t* file_info);
s32 fs_truncate(u32 file_ref, u32 size);

s32	fs_remove_dir (u16 *dirName, u32 flag);
s32	fs_remove_dir_force (u16 *dirName);
s32 fs_delete(u16 *fileName);
s32 fs_delete_all(u16 *dirName, u32 listLen, u8 * listBuf);
s32 fs_mkdir (u16 *dirName);
s32 fs_rename (u16* old_url, u16 *new_name);
s32 fs_exists (u16 *url);
s32 fs_truncate_name (u16 *url, u32 size);
s32 fs_get_folder_size (u16 *url, u32 flag);

s32 fs_change_dir (u16 *pathName, u32 * listLen, u8 ** listBuf);
s32 fs_get_path_nb_files (u16 *pathName);
s32 fs_get_nb_files (u32 listLen, u8 * listBuf);
s32 fs_get_file_info (u32 file_num, VFS_File_Info_t* file_info, u32 listLen, u8 * listBuf);
s32 fs_free_list(u8 * listBuf);
s32 fs_get_name_file_info (u16 * name, File_Simple_Info_t* vfs_file_info_ptr);
s32 fs_set_file_attr(u16 * name, u32 attr);
s32 fs_get_file_attr(u16 * name, u32 * attr);

s32 fs_get_curr_volume_space(u32 * total, u32 * free);
s32 fs_get_rename_length(u16 * name, u32 * length);

s32 fs_get_curr_path(u16* path);
s32 fs_get_curr_free_space(void);
s32 fs_goto_curr_rootdir(void);
s32 fs_goto_curr_subdir(u32 file_num);
s32 fs_goto_curr_parentdir(void);

// partial list related interface
s32 fs_filter_get_file_num(u16 * pathName, VFS_PartialListFilter_t * pFilter, u32 startFileNum, u32 * pStartFileNum, VFS_PartialListFileInfo_t * pFileInfoArray);
s32 fs_abort_filter_get_file_num(u32 refId);
s32 fs_filter_convert_id_to_info(u16 * pathName, u32 numFileId, VFS_FileID_t * pFileIdArray, VFS_PartialListFileInfo_t * pFileInfoArray);
s32 fs_filter_partial_list(u16 * pathName, VFS_PartialListFilter_t * pFilter, u32 offset, u32 requestNumEntry, u32 * pResultNumEntry, VFS_PartialListFileInfo_t * pFileInfoArray);
s32 fs_filter_get_full_info(u16 * fileName, VFS_PartialListFileInfo_t *pFileInfo);
s32 fs_filter_remove_dir(u16 * pathName, VFS_PartialListFilter_t * pFilter, u32 isRercusive, u32 isForce);
s32 fs_abort_filter_remove_dir(u32 refId);

s32 fs_vol_to_dev(VFS_VOL_TYPE vol);
s32 fs_dev_to_vol(VFS_DevType_e dev);

#endif  /* __SYS_FAT_H__ */

