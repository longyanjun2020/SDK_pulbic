#ifndef __MDIC_DELTA_FILE_DEFINE_H_
#define __MDIC_DELTA_FILE_DEFINE_H_

#include "mdl_vfs_fat.ho"
#include "ven_file.h"

typedef enum
{
    FS_DEVICE_NOR,
    FS_DEVICE_NAND,
    FS_DEVICE_SD
} FS_DEVICE_TYPE_t;

typedef enum
{
    FS_DIR_RETURN_FAIL,
	FS_DIR_RETURN_OK
} FS_DIR_RETURN_TYPE_t;

typedef enum
{
    FS_MOUNT_RETURN_OK,
    FS_MOUNT_RETURN_FAIL
} FS_MOUNT_RETURN_TYPE_t;

// the __whence field in FILEP_fseek()
#define FILE_SEEK_CUR    1
#define FILE_SEEK_END    2
#define FILE_SEEK_SET    0

#define FILE_RET_SUCCESS 1
#define FILE_RET_FAIL    -1

typedef void FILEP;

#ifdef __cplusplus
extern "C" {
#endif

// device
extern FS_MOUNT_RETURN_TYPE_t    FILEP_mount(FS_DEVICE_TYPE_t device);
extern u32    FILEP_getFreeSpace(void);
extern u32    FILEP_getTotalSpace(void);
// directory operations
extern FS_DIR_RETURN_TYPE_t   FILEP_makeDir(const u8 * __path);
extern FS_DIR_RETURN_TYPE_t   FILEP_removeDir(const u8 * __path);
extern FS_DIR_RETURN_TYPE_t   FILEP_removeDirAll(const u8 *__path);
extern FS_DIR_RETURN_TYPE_t   FILEP_changeDir(const u8 * __path);
extern s32   FILEP_GetFileCountInDir(const u8 * __path);

extern FS_DIR_RETURN_TYPE_t   FILEP_GetFileInfoInDir(const u8 * __path, u32 index, File_Info_t* output_Info);
extern s8    FILEP_IsDirectory(VFS_File_Info_t* input_Info);

// file operations
extern s32   FILEP_fclose(FILEP * __stream);



extern FILEP    *FILEP_fopen(const u8 * __path, const u8 * __mode);
extern s32   FILEP_fread(void * __ptr, s32 __size, s32 __n, FILEP * __stream);          /*@@~~ return number of byte*/
extern s32   FILEP_fwrite(const void * __ptr, s32 __size, s32 __n,FILEP * __stream);    /*@@~~ return number of byte*/
extern s32   FILEP_fseek(FILEP * __stream, s32 __offset, s32 __whence);                /*@@~~ return operation result FILE_RET_XXX */
extern s32   FILEP_ftell(FILEP * __stream);                                              /*@@~~ return operation result FILE_RET_FILE_RET_FAIL or Pos */
extern s32   FILEP_unlink(const u8 * __path);                                          /*@@~~ return operation result FILE_RET_XXX */
extern s32   FILEP_exists(const u8 * __path);                                          /*@@~~ return 1, 0: exist or not*/
extern s32   FILEP_rename(const u8 * oldname,const u8 * newname);                    /*@@~~ return operation result FILE_RET_XXX */

#ifdef  __cplusplus
}
#endif


#endif
