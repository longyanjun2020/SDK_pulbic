/**
 *
 * @file    vfs_fat_internal.h
 *
 * @brief
 *
 * @author  Xavier
 * @version $Id: vfs_fat_internal.h 15206 2008-10-16 06:52:18Z xavier.fan $
 *
 */
#ifndef __VFS_FAT_INTERNAL_H__
#define __VFS_FAT_INTERNAL_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_vfs_fat.ho"
#include "vm_msgof.hc"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __VFS_FAT_INTERNAL__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef enum
{
  VFS_SET_STATE,
  VFS_CLEAR_STATE,
} vfs_state_op_e;


typedef enum
{
  VFS_STATE_FS_FREE             = 0x0000,
  VFS_STATE_FILE_OPENED         = 0x0001,
  VFS_STATE_ASYNC_OP_PROCESSING = 0x0002,
  VFS_STATE_SYNC_OP_PROCESSING  = 0x0004,
} vfs_state_e;

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "vfs_fat_message_define__.hi"
} vfs_asyncOp_e;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/
DefExtern u32 * volume_Id_List
#ifdef __VFS_FAT_INTERNAL__
	= NULL
#endif
;



/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
s32   fat_N_get_device_by_volume(u32 volumeId);
s32   fat_N_scan_name_format(u16 * path);
s32   fat_N_get_device_by_path(u16 * path);
void  fat_N_print_path(const u16 * const pPath);
#if !defined(__SDK_SIMULATION__)
void fat_N_print_fileName_by_fh(u32 fh);
#endif
void fat_N_chkfileunclose(u32 file_ref, const char *stg_dev);


void  fat_N_setAsyncFlag(void);
void  fat_N_resetAsyncFlag(void);
bool  fat_N_getAsyncFlag(void);

#endif

