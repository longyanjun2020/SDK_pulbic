/****************************************************************************/
/*  File    : fs_error.h                                              		*/
/*--------------------------------------------------------------------------*/
/*  Scope   : file system error codes					           			*/
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __FS_ERROR_H__
#define __FS_ERROR_H__

/*_____ I N C L U D E S ____________________________________________________*/

#include "vm_types.ht" 

#define FS_NO_ERROR					1
#define FS_CLOSE_ERROR 				-1
#define FS_STEP_IN_ERROR 			-2
#define FS_MOUNT_ERROR				-3
#define FS_NO_FILE_ERROR			-4
#define FS_FRAGMENTATION_ERROR		-5
#define FS_MEMORY_FULL_ERROR		-6
#define FS_EMPTY_FILE_ERROR			-7
#define FS_EXISTING_DIR_ERROR		-8
#define FS_TOO_MUCH_FILES_ERROR		-9
#define FS_NOT_EXISTING_DIR			-10
#define FS_NOT_EXISTING_FILE		-11
#define FS_PHYSICAL_ERROR			-12
#define FS_PROTECTED_FILE			-13
#define FS_READ_ERROR				-14
#define FS_WRITE_ERROR				-15
#define FS_NOT_FORMATTED_ERROR		-16
#define FS_NOT_EMPTY_DIR_ERROR		-17
#define FS_INVALID_NAME_ERROR		-18
#define FS_BAD_PARAM_ERROR			-19
#define FS_NOT_EXISTING_VOL			-20
#define FS_UNMOUNTED_VOL			-21
#define FS_EOF						-22
#define FS_LIST_DIR_ERROR			-23
#define FS_MEMORY_ERROR				-24

#endif  /* __FS_ERROR_H__ */
