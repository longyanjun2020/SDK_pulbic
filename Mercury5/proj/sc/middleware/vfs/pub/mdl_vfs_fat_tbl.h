/****************************************************************************/
/*  $Workfile::   mdl_vfs_fat_tbl.c                                              $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : management file system table                            */
/*                                                                          */
/*  Author: MStar Match                                                                        */
/* ****************************************************************************/
#ifndef __MDL_VFS_FAT_TBL_H__
#define __MDL_VFS_FAT_TBL_H__

enum
{
  API_VFS_MOUNT ,
  API_VFS_MOUNT_DEV,
  API_VFS_UNMOUNT ,
  API_VFS_UNMOUNT_DEV,
  API_VFS_FORMAT,
  API_VFS_FORCE_FORMAT,
  API_VFS_GET_VOL_NAME,
  API_VFS_CHECK_VOLUME,

  API_VFS_OPEN,
  API_VFS_OPEN_WITH_SIZE,
  API_VFS_OPEN_WITH_BUFFER,
  API_VFS_CLOSE,
  API_VFS_READ,
  API_VFS_WRITE,
  API_VFS_EOF,
  API_VFS_SEEK,
  API_VFS_SEEK_64,
  API_VFS_TELL,
  API_VFS_TELL_64,
  API_VFS_GET_OPEN_FILEINFO,
  API_VFS_TRUNCATE,

  API_VFS_REMOVE_DIR,
  API_VFS_DELETE,
  API_VFS_DELETEALL,
  API_VFS_MAKE_DIR,
  API_VFS_RENAME,
  API_VFS_EXITS,
  API_VFS_TRUNCATE_NAME,
  API_VFS_GET_FOLDER_SIZE,

  API_VFS_CHANGE_DIR,
  API_VFS_GET_PATH_NBFILE,
  API_VFS_GET_NBFILE,
  API_VFS_GET_FILEINFO,
  API_VFS_FREE_LIST,
  API_VFS_GET_NAME_FILEINFO,
  API_VFS_GET_NAME_FULLINFO,
  API_VFS_SET_ATTR,
  API_VFS_GET_ATTR,

  API_VFS_GET_VOLUMESIZE,

  API_VFS_GET_RENAME_LENGTH,

  API_VFS_SET_NOTIFY,
  API_VFS_CLEAR_NOTIFY,

  API_VFS_GET_DIR_CHKSUM,

  API_VFS_GET_CHKSUM_REQ,
  API_VFS_ABORT_CHKSUM,

  API_VFS_GET_FILE_NUM_REQ,
  API_VFS_ABORT_GET_FILE_NUM,
  API_VFS_ID_TO_INFO,
  API_VFS_PARTIAL_LIST,

  API_VFS_DELETE_REQ,
  API_VFS_ABORT_DELETE,

  API_VFS_CHKDSK_REQ,
  API_VFS_ABORT_CHKDSK,

  API_VFS_GET_VOLUME_INFO,
  API_VFS_COMBILE_FILE,
  API_VFS_RECOUNT,

  API_VFS_VOL_TO_DEV,

  API_VFS_GET_SERIAL,

  APE_VFS_COMMAND_MAX
};

#endif /* __MDL_VFS_FAT_TBL_H__ */

