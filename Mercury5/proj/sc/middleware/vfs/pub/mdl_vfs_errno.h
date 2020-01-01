/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/
/****************************************************************************/
/*  File    : mdl_vfs_errno.h                                           		*/
/*--------------------------------------------------------------------------*/
/*  Scope   : stdio error numbers						                	*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 04.23.02 |   NRO  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/

#ifndef __MDL_VFS_ERRNO_H__
#define __MDL_VFS_ERRNO_H__

#include "vm_types.ht"

#define EINVAL 1

/* @ 2007.07.05 David Chang */
#define FAT_NO_ERROR              (  1)
#define FAT_CLOSE_ERROR           ( -1)
#define FAT_STEP_IN_ERROR         ( -2)
#define FAT_MOUNT_ERROR           ( -3)
#define FAT_NO_FILE_ERROR         ( -4)
#define FAT_FRAGMENTATION_ERROR   ( -5)
#define FAT_MEMORY_FULL_ERROR     ( -6) /* be replaced by FAT_VOLUME_FULL */
#define FAT_EMPTY_FILE_ERROR      ( -7)
#define FAT_EXISTING_DIR_ERROR    ( -8)
#define FAT_TOO_MUCH_FILES_ERROR  ( -9)
#define FAT_NOT_EXISTING_DIR      (-10)
#define FAT_NOT_EXISTING_FILE     (-11)
#define FAT_PHYSICAL_ERROR        (-12)
#define FAT_PROTECTED_FILE        (-13)
#define FAT_READ_ERROR            (-14)
#define FAT_WRITE_ERROR           (-15)
#define FAT_NOT_FORMATTED_ERROR   (-16)
#define FAT_NOT_EMPTY_DIR_ERROR   (-17)
#define FAT_INVALID_NAME_ERROR    (-18)
#define FAT_BAD_PARAM_ERROR       (-19)
#define FAT_NOT_EXISTING_VOL      (-20)
#define FAT_NOT_MOUNTED_ERROR     (-21)
#define FAT_EOF                   (-22)
#define FAT_LIST_DIR_ERROR        (-23)
#define FAT_MEMORY_ERROR          (-24) /* be replaced by FAT_OUT_OF_MEMORY */
#define FAT_NOT_PRESENT_ERROR     (-25)
#define FAT_OPEN_ERROR            (-26)
#define FAT_UNMOUNT_ERROR         (-27)
#define FAT_INIT_ERROR            (-28)
#define FAT_ASYNC_ABORT           (-29)
#define FAT_ASYNC_COMPLETED       (-30)
#define FAT_VOLUME_FULL           (-31) /* be replaced by FAT_VOLUME_FULL */
#define FAT_RESOURCE_BUSY         (-32)
#define FAT_REJECT                (-33)
#define FAT_TIMEOUT               (-34)
#define FAT_NOT_DIR               (-35)
#define FAT_NOT_FILE              (-36)
#define FAT_EXISTING_FILE         (-37)
#define FAT_NO_FILE_HANDLE        (-38)
#define FAT_ERROR_FILE_HANDLE     (-39)
#define FAT_FILE_CORRUPTED        (-40)
#define FAT_INVALID_NAME_LEN      (-41)
#define FAT_ALLOCATE_BUFFER_FAIL  (-42) /* be replaced by FAT_OUT_OF_MEMORY */
#define FAT_OUT_OF_MEMORY         (-42) /* replace FAT_ALLOCATE_BUFFER_FAIL and FAT_MEMORY_ERROR */
#define FAT_FUNCTION_NOT_SUPPORT  (-43)
#define FAT_NO_DEVICE             (-44) /* the error code is used for mount API */
#define FAT_LIST_END              (-45)
#define FAT_DISK_DIRTY            (-46)
#define FAT_TBL_NOTSAME           (-47)
#define FAT_CHECKDISK_ABORT       (-48)
#define FAT_ROOT_FULL             (-49) 
#define FAT_DISK_LOCK             (-50)
#define FAT_NO_PARPATH            (-51)
#define FAT_NULL_SESSION          (-52)
#define FAT_DIR_CORRUPTED         (-53)
#define FAT_PERMIT_DENY           (-54)
#define FAT_FILE_INCONSITANT_FAT  (-55)

/* @ David Chang */
#endif 	/* __MDL_VFS_ERRNO_H__ */

