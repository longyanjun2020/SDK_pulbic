/****************************************************************************/
/*  File    : fs_system.h                                              	*/
/*--------------------------------------------------------------------------*/
/*  Scope   : file and directory manipulation functions	           			*/
/*                                                                          */
/*                                                                          */
/****************************************************************************/
#ifndef __FS_SYSTEM_H__
#define __FS_SYSTEM_H__

#include "sys_fat.h"
#include "fs_browse.h"

u16 fs_get_start_cluster(u32 file_ref);
fs_file_info_s* fs_stat_open(u32 file_num);

#endif  /* __FS_SYSTEM_H__ */
