/**
* @file nccport_mail_fs.h
* NCC email fs porting Layer
*
* Service API exposed by the NCC email fs porting module
*/
#ifndef __NCCPORT_EMAIL_FS_H__
#define __NCCPORT_EMAIL_FS_H__

#include <ncc_types.h>

/*return value*/
#define EMAIL_FS_OK 0           ///Return code that indicates successful completion of an operation
#define EMAIL_FS_FAIL -1      ///Return code that indicates the current operation is failed
#define EMAIL_FS_NO_BUF -2         ///Return code indicates memory malloc fail 
#define EMAIL_FS_INVALID_PARAM -3   ///Return code indicates that param error 
#define EMAIL_FS_PATH_TOOLONG -4   ///Return code indicates path is too long
#define EMAIL_FS_EOF -5             ///Return code indicates file is empty
 
#define NCCPort_EMAIL_FS_ISREG 0    ///Return code indicates this object is file
#define NCCPort_EMAIL_FS_ISDIR 1    ///Return code indicates this object is dirtory

#define NCCPort_EMAIL_FS_OPEN_READ  1  ///indicates mode of read
#define NCCPort_EMAIL_FS_OPEN_WRITE 2   ///indicates mode of write

#define NCCPort_EMAIL_FS_MAX_FILEPATH_LEN   250   ///max file path length

#if 1                                   ///not use
#define NCCPort_EMAIL_FS_FIND_FIRST     1 /**<Find the first file that locates at the appointed folder.*/
#define NCCPort_EMAIL_FS_FIND_NEXT      2 /**<Find the next file that locates at the appointed folder.*/
#define NCCPort_EMAIL_FS_FIND_CLOSE     3 /**<Close the handle.*/
#endif
#ifdef __cplusplus
extern "C" {
#endif
/**
   *startup   the FS module. This function need to be called when email system startup.
   * \return    #EMAIL_FS_OK if successful, otherwise #EMAIL_FS_FAILED
   */   
int32_t NCCPort_emailfs_startUp(void);

/**
   *shutdown  the FS module. This function need to be called when  email shutdown.
   */
void NCCPort_emailfs_shutDown(void);

/**
   *get file length with special filename
   *\param    *fileName [in]    Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   * \return    number of bytes of the file.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                        If the parameter is error, fileName == NULL
   *                                return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_getFileLength(const int8_t *fileName);

/**
   *create file  with special filename
   *\param    *fileName  Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   * \return   #EMAIL_FS_OK .
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                        If the parameter is error, fileName == NULL
   *                                return #EMAIL_FS_INVALID_PARAM directly
   */   
int32_t NCCPort_emailfs_createFile(const int8_t *fileName);

/**
   *Open file with specific mode.
   *\param *fileName [in] Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\param   mode      [in] NCCPort_EMAIL_FS_OPEN_READ indicates mode of read
   *                                1. Open the file for reading
   *                                2. The operation will fail if the file doesn't exist
   *                                   NCCPort_EMAIL_FS_OPEN_WRITE indicates mode of write
   *                                1. Open the file for writing from the beginning of the file (always create a new file)
   *                                2. If the file already existed, its old contents are discarded
   *                       NCCPort_EMAIL_FS_OPEN_READ|NCCPort_EMAIL_FS_OPEN_WRITE indicates mode of read
   *                                1. To permit reading and writing anywhere in an existing file without discarding any data
   *                                2. The operation will fail if the file doesn't exist
   * \return   handle 
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                                  If the parameter is error, fileName == NULL
   *                                           return #EMAIL_FS_INVALID_PARAM directly
   */ 
int32_t NCCPort_emailfs_openFile(const int8_t *fileName, int32_t mode);

/**
   *get file length with file handle .
   *\param     handle  [in]    File handle
   * \return    number of byes of the file.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   */
int32_t NCCPort_emailfs_getLength(int32_t handle);

/**
   *For file read operation.
   *\param    handle  [in]             File handle
   *\param    *buffer    [in/out]     Data buffer for file read
   *\param    bufLen   [in]             How many bytes to read
   * \return   Return number of byes read.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                                  If the parameter is error, (buffer == NULL)||(0 >= bufLen)
   *                                           return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_read(int32_t handle, int8_t *buffer, int32_t bufLen);

/**
   *For file write operation.
   *\param   handle     [in]             File handle
   *\param   *buffer     [in]            Data buffer for file write
   *\param    bufLen    [in]             How many bytes to write
   * \return   Return number of byes write.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                                  If the parameter is error, (fileName == NULL)||(0 >= bufLen)
   *                                           return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_write(int32_t handle, int8_t *buffer, int32_t bufLen);

/**
   * For file close operation.
   *\param   handle  [in]             File handle
   * \return #EMAIL_FS_OK if successful, otherwise #EMAIL_FS_FAILED
   */
int32_t NCCPort_emailfs_close(int32_t handle);

/**
   *For file read operation.
   *\param  *fileName  [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\param  *buffer      [in/out]     Data buffer for file read
   *\param   len      [in]             How many bytes to read
   *\return   Return number of byes read.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                                  If the parameter is error, (fileName == NULL)||(0 >= bufLen)||(NULL == buffer)
   *                                           return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_getFile(const int8_t *fileName, int8_t *buffer, int32_t len);

/**
   *For file write operation.
   *\param *fileName  [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\param *buffer       [in/out]     Data buffer for file read
   *\param  bufLen      [in]             How many bytes to read
   *\param  ifDelete     [in]             if  0  all data always goes to the current end of file 
   *                                                 else   Open the file for writing from the beginning of the file (always create a new file)
   *                                                          its old contents are discarded
   *\return   Return number of byes read.
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                                  If the parameter is error, (fileName == NULL)||(0 >= bufLen)||(NULL == buffer)
   *                                           return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_saveFile(const int8_t *fileName, int8_t *buffer, int32_t len, uint32_t ifDelete);

/**
   *For Delete an existed file or dir.
   *\param    *fileName  [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\return    #EMAIL_FS_OK
   *                                             If error occurs, it return #EMAIL_FS_FAILED
   *                                             If the parameter is error, fileName == NULL
   *                                             return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_deleteFile(const int8_t *fileName);

/**
   *For Rename a file or directory.
   *\param    *oldFile     [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\param    *newFile   [in]          [in] Should be absolute path. Ex. L"/Card/Picture/pic0002.jpg"
   *\return    #EMAIL_FS_OK
   *                                             If error occurs, it return #EMAIL_FS_FAILED
   *                                             If the parameter is error, fileName == NULL
   *                                             return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_renameFile(int8_t *oldFile, int8_t *newFile);

/**
   *For Check this object is file or directory.
   *\param    *fileName     [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\return    #NCCPort_EMAIL_FS_ISREG or #NCCPort_EMAIL_FS_ISDIR
   *                                             If error occurs, it return #EMAIL_FS_FAILED
   *                                             If the parameter is error, fileName == NULL
   *                                             return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_checkFile(const int8_t *fileName);

/**
   *Check the existence of file or directory
   *\param     *fileName     [in]          Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
   *\param      type            [in]           #NCCPort_EMAIL_FS_ISREG or #NCCPort_EMAIL_FS_ISDIR
   *\return      #EMAIL_FS_OK
   *                                             If error occurs, it return #EMAIL_FS_FAILED
   *                                             If the parameter is error, fileName == NULL
   *                                             return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_checkFileExt(const int8_t *fileName, int32_t type);

/**
   * Create a new directory
   *\param    *dir  Should be absolute path with volume name. Ex. L"/Card/Picture"
   * \return   #EMAIL_FS_OK .
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                        If the parameter is error,dir == NULL
   *                                return #EMAIL_FS_INVALID_PARAM directly
   */
int32_t NCCPort_emailfs_makeDir(const int8_t *dir);

/**
   * delete all file in the directory
   *\param    *dir  Should be absolute path with volume name. Ex. L"/Card/Picture/"
   * \return   #EMAIL_FS_OK .
   *                                  If error occurs, it return #EMAIL_FS_FAILED
   *                        If the parameter is error, dir == NULL
   *                                return #EMAIL_FS_INVALID_PARAM directly
   */

int32_t NCCPort_emailfs_deleteFileList(const int8_t *dir);


#ifdef __cplusplus
}
#endif

#endif /*__NCCPORT_EMAIL_FS_H__*/

