#ifndef __MMS_FS_NCCPort_H__
#define __MMS_FS_NCCPort_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NCCPort_MMS_FS_ISREG 0
#define NCCPort_MMS_FS_ISDIR 1

#define NCCPort_MMS_FS_OPEN_READ 1
#define NCCPort_MMS_FS_OPEN_WRITE 2

#define NCCPort_MMS_FS_RETRY_TIME 3

#define NCCPort_MMS_FS_FIND_FIRST                                                             1 /**<Find the first file that locates at the appointed folder.*/
#define NCCPort_MMS_FS_FIND_NEXT                                                             2 /**<Find the next file that locates at the appointed folder.*/
#define NCCPort_MMS_FS_FIND_CLOSE                                                             3/**<Close the handle.*/

int32_t NCCPort_mmsfs_startUp(void);
void NCCPort_mmsfs_shutDown(void);
int32_t NCCPort_mmsfs_getFileLength(int8_t *fileName);
int32_t NCCPort_mmsfs_openFile(int8_t *fileName, int32_t mode);
int32_t NCCPort_mmsfs_getLength(int32_t handle);
int32_t NCCPort_mmsfs_read(int32_t handle, uint8_t *buffer, int32_t bufLen);
int32_t NCCPort_mmsfs_write(int32_t handle, uint8_t *buffer, int32_t bufLen);
int32_t NCCPort_mmsfs_close(int32_t handle);
int32_t NCCPort_mmsfs_getFile(int8_t* fileName, uint8_t *buffer, int32_t len);
int32_t NCCPort_mmsfs_saveFile(int8_t *fileName, uint8_t  *buffer, int32_t len, int32_t ifDelete);
int32_t NCCPort_mmsfs_deleteFile(int8_t *fileName);
int32_t NCCPort_mmsfs_renameFile(int8_t *oldFile, int8_t *newFile);
int32_t NCCPort_mmsfs_checkFile(int8_t *fileName);
int32_t NCCPort_mmsfs_checkFileExt(int8_t *fileName, int32_t type);
int32_t NCCPort_mmsfs_makeDir(int8_t *dir);
int32_t NCCPort_mmsfs_deleteFileList(int8_t *dir);
int32_t NCCPort_mmsfs_getFileName(int8_t *path, int32_t type, int32_t *handle, int8_t *filename);
void NCCPort_mmsfs_getElapsedSeconds(uint32_t *timeValue);

#ifdef __cplusplus
}
#endif

#endif /*__MMS_FS_NCCPort_H__*/

