#ifndef __VEN_FILE_H_
#define __VEN_FILE_H_
/**
 *
 * @file    ven_file.c
 * @brief   This file defines the file interface definition.
 *
 * @author  Owen.Lee
 * @version $Id: ven_file.h 26275 2009-03-20 09:55:07Z code.lin $
 *
 */
#include "ven_sdk.h"

/* Full path definition:
 *  1. Start from volume name,
 *      ex. in SD card, L"/CARD/my photo/1.jpg"
 *      ex. in NOR flash, L"/NOR0/my photo/1.jpg"
 *  2. in UCS2 format
 */
#define VEN_FILE_FAT_SPEC_FULLPATH_LEN      (262+1)  /**< FAT Spec Limitation of full path, 262 char + 1 NULL-terminate */
#define VEN_FILE_MAX_EXT_NAME_LEN           (3)    /**< Max u8 length of extension name */

#define VEN_FILE_MAX_PATH_BYTE_LEN         (VEN_FILE_FAT_SPEC_FULLPATH_LEN*2+8)     /**< Max u8 length of MStar full path, +8: buffer for internal use */
#define VEN_FILE_VOLUME_NAME_NOR    L"/NOR0"     /**< NOR flash volume name */
#define VEN_FILE_VOLUME_NAME_SD     L"/CARD"     /**< SD volume name */
#define VEN_FILE_VOLUME_NAME_NAND   L"/NAND"     /**< Nand flash volume name */
#define VEN_FILE_VOLUME_NAME_SD2    L"/SD_2"     /**< SD 2 volume name */
#define VEN_FILE_VOLUME_NAME_SD1    L"/SD_1"     /**< SD 1 volume name */
#define VEN_FILE_VOLUME_NAME_HIDDEN L"/HIDN"     /**<Hidden volume name */
#define VEN_FILE_PATH_SEPARATOR     L"/"

enum
{
    VEN_FILE_RET_SUCCESS             = 0, ///< operation completed successfully
    VEN_FILE_RET_FAILED              = 1, ///< WHAT? every code here is failed
    VEN_FILE_RET_NOT_SUPPORT         = 2, ///< not support
    VEN_FILE_RET_BAD_PARAM           = 3, ///< invalid input parameters
    VEN_FILE_RET_OUT_OF_MEMORY       = 4, ///< memory is not enough to complete the operation
};
typedef u32 ven_file_ret_t;

enum
{
    VEN_FILE_BROWSER_TYPE_IMAGE             = 0,
    VEN_FILE_BROWSER_TYPE_AUDIO             = 1,
    VEN_FILE_BROWSER_TYPE_VIDEO             = 2,
    VEN_FILE_BROWSER_TYPE_ALL,
};
typedef u8 ven_file_browser_type_t;

enum
{
	VEN_FILE_AVAIL_PATH_ALBUM = 0,		//capture images
	VEN_FILE_AVAIL_PATH_VOICEMEMO,		//record audio
	VEN_FILE_AVAIL_PATH_CAMCORDER,		//record video
};
typedef u8 ven_file_avail_path_t;

enum
{
    VEN_FILE_ASYNC_READ = 0,
    VEN_FILE_ASYNC_WRITE,
};
typedef u8 ven_file_async_operation_t;

typedef struct
{
    u16 *ptData;
    u16 dataLen;
    u8  nMarkedSize;
} ven_file_browse_rsp_t;

typedef struct
{
    u16 *ptData;
    u16 dataLen;
} ven_file_select_folder_rsp_t;

typedef struct
{
    s32 retCode;    ///< return code of write operation
    u32 progress;   ///< Write progress (0~100)
} ven_file_write_rsp_t;

typedef struct
{
    s32 retCode;    ///< return code of read operation
    u32 progress;   ///< Read progress (0~100)
} ven_file_read_rsp_t;

enum
{
    VEN_FILE_DEVICE_TYPE_NOR        = 0,  ///< Use NOR flash file system
    VEN_FILE_DEVICE_TYPE_SD         = 1,  ///< Use SD file system
    VEN_FILE_DEVICE_TYPE_NAND       = 2,  ///< Use NAND flash file system
    VEN_FILE_DEVICE_TYPE_SD2		= 3,  ///< Use SD2 file system
    VEN_FILE_DEVICE_TYPE_SD1        = 4,  ///< Use SD1 file system
    VEN_FILE_DEVICE_TYPE_HIDN       = 5   ///< Use Hidden file system
};
typedef u8 ven_file_device_type_t;

// A handle points to an internal structure in MStar system. It uses as file handle.
typedef void* ven_file_handle_t;

// A handle points to an internal structure in MStar system. It uses as directory handle.
typedef void* ven_dir_handle_t;

// A handle points to an internal structure in MStar system. It uses as search handle. mk
typedef void* ven_file_search_handle_t;

// For the conversion from the u32 field (createdDate, updatedDate) of ven_file_info_t or ven_simple_file_info_t
#define VEN_FILE_HOURS(_time)   (u8)((_time&0x0000F800)>>11)
#define VEN_FILE_MINUTES(_time)     (u8)((_time&0x000007E0)>>5)
#define VEN_FILE_SECONDS(_time)     (u8)((_time&0x0000001F)<<1)
#define VEN_FILE_DAY(_date)         (u8)((_date&0x001F0000)>>16)
#define VEN_FILE_MONTH(_date)   (u8)((_date&0x01E00000)>>21)
#define VEN_FILE_YEAR(_date)    (u16)(((_date&0xFE000000)>>25)+1980)

// Use to contain the information of a file or directory
typedef struct ven_file_info_t_
{
    u16 longFileName[VEN_FILE_FAT_SPEC_FULLPATH_LEN + 1];     /**< Long file name in UCS2 string */
    s8  fileName[12];                                         /**< 8.3 file name in char string  */
    s8  fileExt[VEN_FILE_MAX_EXT_NAME_LEN + 1];               /**< 8.3 file name ext part        */
    u32 createdDate;                                          /**< Created time & date           */
    u32 updatedDate;                                          /**< Last modified time & date     */
    u32 size;                                                 /**< File size in bytes            */
    u8  attribute;                                            /**< Attributes bits               */
} ven_file_info_t;

// Attribute for file or folder
#define VEN_FILE_A_NORMAL       0x00    ///< Normal file - No read/write restrictions
#define VEN_FILE_A_RDONLY       0x01    ///< Read only file
#define VEN_FILE_A_HIDDEN       0x02    ///< Hidden file
#define VEN_FILE_A_SYSTEM       0x04    ///< System file
#define VEN_FILE_A_SUBDIR       0x10    ///< Subdirectory
#define VEN_FILE_A_ARCH         0x20    ///< Archive file

// Use to contain the information of a file
typedef struct ven_simple_file_info_t_
{
    u32 createdDate;                                        /**< Created time & date           */
    u32 updatedDate;                                        /**< Last modified time & date     */
    u32 size;                                               /**< File size in bytes            */
    u8  attribute;                                          /**< Attributes bits               */
} ven_simple_file_info_t;

// File seek whence definition
#define VEN_FILE_SEEK_SET               0           ///< Count the offset from the file beginning
#define VEN_FILE_SEEK_CUR               1           ///< Count the offset from current position
#define VEN_FILE_SEEK_END               2           ///< Count the offset from the file end

// For includeSubDirs field in ven_file_wgetFolderSize()
#define VEN_FILE_EXCLUDE_SUBDIR         0x00        ///< exclude subdirectories size
#define VEN_FILE_INCLUDE_SUBDIR         0x01        ///< include all subdirectories size

// Error code
#define VEN_FILE_ERR_NO_ERROR           (1)         ///< Operation success
#define VEN_FILE_ERR_INTERNAL_ERROR     (-1)        ///< Internal error
#define VEN_FILE_ERR_PATH_NOT_EXIST     (-2)        ///< If the path does not exits
#define VEN_FILE_ERR_NOT_EMPTY_DIR      (-3)        ///< If the path of directory is not empty
#define VEN_FILE_ERR_ALREADY_EXIST      (-4)        ///< If the path of file/directory already exists
#define VEN_FILE_ERR_BAD_PARAM          (-5)        ///< Parameter error
#define VEN_FILE_ERR_VOLUME_FULL        (-6)        ///< No space error
#define VEN_FILE_ERR_MOUNT_ERROR        (-7)        ///< Mount error
#define VEN_FILE_ERR_READ_ERROR         (-8)        ///< Read error
#define VEN_FILE_ERR_WRITE_ERROR        (-9)        ///< Write error


typedef struct
{
	u32 count;             /**< Number of extension should be compared                                      */
	u16 *pExtList;         /**< Extension list in Unicode, please separate with '|' in wide character, too  */
} ven_file_ExtensionFilter_t;

typedef struct _ven_file_browse_cfg_tag
{
    ven_file_ExtensionFilter_t tExtFilter;
    u16 *pwszBrowsingFolder;
    u16 nFolderStrLen;
}ven_file_browse_cfg_t;

bool ven_file_browse(u16 *ptTitle, u8 titleLen, ven_file_browser_type_t type,  u8 maxMarkSize, u16 **pptOutData, u16 *ptOutDataLen, u8 *ptOutMarkedSize, ven_req_data_t* ptVenReq);

bool ven_file_browse_with_filter(u16 *ptTitle, u8 titleLen, ven_file_browse_cfg_t *ptVen_file_browse_cfg, u8 maxMarkSize, u16 **pptOutData, u16 *ptOutDataLen, u8 *ptOutMarkedSize, ven_req_data_t* ptVenReq);

bool ven_file_selectFolder(u16 *ptTitle, u8 titleLen, u16 **pptOutData, u16 *ptOutDataLen, ven_req_data_t* ptVenReq);

/**
 *  ven_file_getAvailPath
 *
 *  @brief  This function will help to get available path for capture images/record audio/record video
 *
 *  @param  type       		[in] what kind default path you want
 *  @param  ppOutPath     	[out] the pointer of pointer to the path string
 *  @param  pOutPathLen	[out] the pointer to the path string length
 *  @param  ptVenReq        	[in]Request data.
 *
 *  @retval VEN_FILE_RET_SUCCESS if success
 *          VEN_FILE_RET_FAILED if failed
 *          VEN_FILE_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note  Only support sync mode and must free the path string after using this API.
 */
ven_file_ret_t ven_file_getAvailPath(ven_file_avail_path_t type, u16 **ppOutPath, u16* pOutPathLen, ven_req_data_t *ptVenReq);

/**
 *  ven_file_wfopen
 *
 *  @brief  Open file with specific mode.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  mode     [in] "r" indicates mode of read
 *                              1. Open the file for reading
 *                              2. The operation will fail if the file doesn't exist
 *                        "w" indicates mode of write
 *                              1. Open the file for writing from the beginning of the file (always create a new file)
 *                              2. If the file already existed, its old contents are discarded
 *                        "a" indicates mode of append
 *                              1. Open the file for appending data that is writing from the end of the file
 *                              2. When you open a file this way, all data always goes to the current end of file
 *                        "r+" indicates mode of read
 *                              1. To permit reading and writing anywhere in an existing file without discarding any data
 *                              2. The operation will fail if the file doesn't exist
 *                        "w+" indicates mode of write
 *                              1. To create a new file that permits reading and writing anywhere in it
 *                        "a+" indicates mode of append
 *                              1. To permit reading anywhere in an existing file, but writing only at the end
 *                              2. The file position after open is at the end of file
 *
 *  @retval File handle, if NULL, means error occurs
 */
ven_file_handle_t ven_file_wfopen(const u16 *path, const u8 *mode);

/**
 *  ven_file_wfopenWithSize
 *
 *  @brief  Open file with specific mode with given file size. Only support "w", "r+". "w+" now.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  mode     [in] "r" indicates mode of read
 *                              1. Open the file for reading
 *                              2. The operation will fail if the file doesn't exist
 *                        "w" indicates mode of write
 *                              1. Open the file for writing from the beginning of the file (always create a new file)
 *                              2. If the file already existed, its old contents are discarded
  *                       "r+" indicates mode of read
 *                              1. To permit reading and writing anywhere in an existing file without discarding any data
 *                              2. The operation will fail if the file doesn't exist
 *                        "w+" indicates mode of write
 *                              1. To create a new file that permits reading and writing anywhere in it
 *
 *  @retval File handle, if NULL, means error occurs
 */
ven_file_handle_t ven_file_wfopenWithSize(const u16 *path, const u8 *mode, u32 size);

ven_file_handle_t ven_file_wfopenWithBuffer(const u16 *path, const u8 *mode,u8 * pBuffer, u32 bufferSize);

ven_file_handle_t ven_file_fopenWithBuffer(const u8 *path, const u8 *mode,u8 * pBuffer, u32 bufferSize);

/**
 *  ven_file_wfread
 *
 *  @brief  For file read operation.
 *
 *  @param  ptr             [in/out] Data buffer for file read
 *  @param  size            [in] How many bytes to read
 *  @param  file_handle     [in] File handle
 *
 *  @retval Return number of byes read.
 *                          If the value does not equal to the request size or VEN_FILE_ERR_INTERNAL_ERROR,
 *                              either an error occured or the End Of File was reached.
 *                              We can get the last error code by ven_file_wferror().
 *                              or we can check if End Of File by ven_file_wfeof().
 *                          If the parameter is error, (ptr == NULL) || (size < 0)
 *                              return VEN_FILE_ERR_BAD_PARAM directly
 */
s32 ven_file_wfread(void * ptr, s32 size, ven_file_handle_t file_handle);

/**
*  ven_file_wfreadEx
*
*  @brief  For advanced file read operation.
*          Note: This function supports both synchronous and asynchronous
*
*  @param  ptr             [in/out] Data buffer for file read
*  @param  size            [in] How many bytes to read
*  @param  file_handle     [in] File handle
*  @param  ptVenReq        [in] Request data.
*
*  @retval Return number of byes read if synchronous.
*          VEN_FILE_ERR_NO_ERROR / VEN_FILE_ERR_INTERNAL_ERROR if asynchronous
*
*                           If the value does not equal to the request size or VEN_FILE_ERR_INTERNAL_ERROR,
*                               either an error occured or the End Of File was reached.
*                               We can get the last error code by ven_file_wferror().
*                               or we can check if End Of File by ven_file_wfeof().
*                           If the parameter is error, (ptr == NULL) || (size < 0)
*                               return VEN_FILE_ERR_BAD_PARAM directly
* Response structure:
*   ven_file_read_rsp_t readRsp;   [out]The result of asynchronous read
*/
s32 ven_file_wfreadEx(void * ptr, s32 size, ven_file_handle_t file_handle, ven_req_data_t *ptVenReq);


/**
 *  ven_file_wfwrite
 *
 *  @brief  For file write operation.
 *
 *  @param  ptr             [in] Data buffer for file write
 *  @param  size            [in] How many bytes to write
 *  @param  file_handle     [in] File handle
 *
 *  @retval Return number of byes written.
 *                          If error occurs, it return VEN_FILE_ERR_INTERNAL_ERROR, then
 *                              we can get the last error code by ven_file_wferror().
 *                          If the parameter is error, (ptr == NULL) || (size < 0)
 *                              return VEN_FILE_ERR_BAD_PARAM directly
 */
s32 ven_file_wfwrite(void * ptr, s32 size, ven_file_handle_t file_handle);

/**
*  ven_file_wfwriteEx
*
*  @brief  For advanced file write operation.
*          Note: This function supports both synchronous and asynchronous
*
*  @param  ptr             [in] Data buffer for file write
*  @param  size            [in] How many bytes to write
*  @param  file_handle     [in] File handle
*  @param  ptVenReq        [in] Request data.
*
*  @retval Return number of byes written  if synchronous.
*          VEN_FILE_ERR_NO_ERROR / VEN_FILE_ERR_INTERNAL_ERROR if asynchronous
*
*                           If error occurs, it return VEN_FILE_ERR_INTERNAL_ERROR, then
*                               we can get the last error code by ven_file_wferror().
*                           If the parameter is error, (ptr == NULL) || (size < 0)
*                               return VEN_FILE_ERR_BAD_PARAM directly
* Response structure:
*   ven_file_write_rsp_t readRsp;   [out]The result of asynchronous write
*/
s32 ven_file_wfwriteEx(void * ptr, s32 size, ven_file_handle_t file_handle, ven_req_data_t *ptVenReq);

/**
 *  ven_file_wfeof
 *
 *  @brief  Check if End Of File
 *
 *  @param  file_handle     [in] File handle
 *
 *  @retval TRUE if End Of File was reached, FALSE if not
 *          If the return value is smaller than zero, it means error occurs,
 *          For example, if the parameter is error, return VEN_FILE_ERR_BAD_PARAM directly
 */
s32 ven_file_wfeof(ven_file_handle_t file_handle);


/**
 *  ven_file_wferror
 *
 *  @brief  Get the last error code for ven_file_wfread() or ven_file_wfwrite()
 *          The last error code will update in each of the following condition
 *              1. Next time ven_file_wfread() or  ven_file_wfwrite() is called
 *              2. ven_file_wfclearerr() is called, the last error code will reset to VEN_FILE_ERR_NO_ERROR
 *
 *  @param  file_handle     [in] File handle
 *
 *  @retval Error code for the last operation
 */
s32 ven_file_wferror(ven_file_handle_t file_handle);


/**
 *  ven_file_wfclearerr
 *
 *  @brief  Clear the last error code for ven_file_wfread() or ven_file_wfwrite()
 *          When ven_file_wfclearerr() is called, the last error code will reset to VEN_FILE_ERR_NO_ERROR
 *
 *  @param  file_handle     [in] File handle
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfclearerr(ven_file_handle_t file_handle);


/**
 *  ven_file_wfseek
 *
 *  @brief  For file seek operation.
 *
 *  @param  file_handle     [in] File handle
 *  @param  offset          [in] The distance which you want to offset
 *  @param  whence          [in] VEN_FILE_SEEK_SET is to count the offset from file beginning.
 *                               VEN_FILE_SEEK_CUR is to count the offset from current position.
 *                               VEN_FILE_SEEK_END is to count the offset from file end.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfseek(ven_file_handle_t file_handle, s32 offset, s32 whence);


/**
 *  ven_file_wftell
 *
 *  @brief  For file tell operation.
 *
 *  @param  file_handle     [in] File handle
 *
 *  @retval Return current position of the opened file. If error occurs, it return VEN_FILE_ERR_INTERNAL_ERROR
 */
s32 ven_file_wftell(ven_file_handle_t file_handle);


/**
 *  ven_file_wtruncate
 *
 *  @brief  For file truncate operation by file handle.
 *
 *  @param  file_handle     [in] File handle
 *  @param  size            [in] The new size in bytes of the truncated file.
 *                                  Only a size smaller than the current file size is designated.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wtruncate(ven_file_handle_t file_handle, s32 size);


/**
 *  ven_file_wfclose
 *
 *  @brief  For file close operation.
 *
 *  @param  file_handle     [in] File handle
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfclose(ven_file_handle_t file_handle);


/**
 *  ven_file_wtruncateByPath
 *
 *  @brief  For file truncate operation by full path.
 *
 *  @param  path            [in] Should be absolute path with volume name. Ex. L"/Card/Picture/data.bin"
 *  @param  size            [in] The new size in bytes of the truncated file.
 *                                  Only a size smaller than the current file size is designated.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wtruncateByPath(const u16 *path, s32 size);


/**
 *  ven_file_wmakeDir
 *
 *  @brief  Create a new directory.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture"
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 *          VEN_FILE_ERR_ALREADY_EXIST if the path of directory already exists
 */
s32 ven_file_wmakeDir(const u16 *path);


/**
 *  ven_file_wremoveDir
 *
 *  @brief  Delete an existed empty directory.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture"
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 *          VEN_FILE_ERR_PATH_NOT_EXIST if the path does not exits
 *          VEN_FILE_ERR_NOT_EMPTY_DIR if the path of directory is not empty
 */
s32 ven_file_wremoveDir(const u16 *path);


/**
 *  ven_file_wremoveDirAll
 *
 *  @brief  Delete a directory and all it's content will also be deleted.
 *          In the folder to be deleted, if there is a file opened, the delete would be failed.
 *          Current limitation:
 *          In NOR and MSIM: If the (path) contains sub-folder, the sub-folder should be empty.
 *                              Or it will return VEN_FILE_ERR_NOT_EMPTY_DIR.
 *          In SD: no this limitation.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture"
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 *          VEN_FILE_ERR_PATH_NOT_EXIST if the path does not exits
 *          VEN_FILE_ERR_NOT_EMPTY_DIR if the path of directory is not empty
 */
s32 ven_file_wremoveDirAll(const u16 *path);


/**
 *  ven_file_wunlink
 *
 *  @brief  Delete an existed file.
 *
 *  @param  path     [in] Should be absolute path with volume name. Ex. L"/Card/Picture"
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 *          VEN_FILE_ERR_PATH_NOT_EXIST if the path does not exits
 */
s32 ven_file_wunlink(const u16 *path);


/**
 *  ven_file_wexists
 *
 *  @brief  Check the existence of file or directory.
 *
 *  @param  path     [in] Should be absolute path with volume name.
 *                        Ex. File: L"/Card/Picture/pic0001.jpg"
 *                        Ex. Folder: L"/Card/Picture"
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ven_file_wexists(const u16 *path);


/**
 *  ven_file_wrename
 *
 *  @brief  Rename a file or directory.
 *
 *  @param  path_old     [in] Should be absolute path. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  path_new     [in] Should be absolute path. Ex. L"/Card/Picture/pic0002.jpg"
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wrename(const u16 *path_old, const u16 *path_new);


/**
 *  ven_file_wfstat
 *
 *  @brief  Get information by full path.
 *
 *  @param  path            [in] Should be absolute path. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  output_info     [out] The query result for a file or directory
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfstat(const u16 *path, ven_simple_file_info_t * output_info);


/**
 *  ven_file_wfsetAttr
 *
 *  @brief  Set attribute to the file or folder.
 *
 *  @param  path        [in] Should be absolute path. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  attr        [in] Attribute bitwised by VEN_FILE_A_RDONLY, ...
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfsetAttr(const u16 *path, u32 attr);


/**
 *  ven_file_wfgetAttr
 *
 *  @brief  Get attribute from the file or folder.
 *
 *  @param  path        [in] Should be absolute path. Ex. L"/Card/Picture/pic0001.jpg"
 *  @param  attr        [out] The query result for attribute
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wfgetAttr(const u16 *path, u32 *attr);


/**
 *  ven_file_wgetVolumeSpaceInfo
 *
 *  @brief  Get the space information by device type
 *
 *  @param  device     [in] Should be VEN_FILE_DEVICE_TYPE_NOR or VEN_FILE_DEVICE_TYPE_SD
 *  @param  totalSize  [out] The query result for total space is in KBytes on the device
 *  @param  freeSize   [out] The query result for free space is in KBytes on the device
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wgetVolumeSpaceInfo(ven_file_device_type_t device, u32 * totalSize, u32 * freeSize);


/**
 *  ven_file_wgetFolderSize
 *
 *  @brief  Calculates the total size of a directory.
 *
 *  @param  path                [in] Should be absolute path with volume name. Ex. L"/Card/Picture"
 *  @param  includeSubDirs      [in] VEN_FILE_EXCLUDE_SUBDIR for not to include subdirectories size,
 *                                   VEN_FILE_INCLUDE_SUBDIR for include all subdirectories size.
 *  @param  pSize               [out] The query result for foder size.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wgetFolderSize(const u16 *path, s8 includeSubDirs, s32 *pSize);


/**
 *  ven_file_wopendir
 *
 *  @brief  Open a directory. The directory handle contains the file/folder list in this directory
 *
 *  @param  path            [in] Should be absolute path. Ex. L"/Card/Picture"
 *
 *  @retval Directory handle, if NULL, means error occurs
 */
ven_dir_handle_t ven_file_wopendir(const u16 *path);


/**
 *  ven_file_wclosedir
 *
 *  @brief  Close a directory handle if no longer use.
 *
 *  @param  dir_handle     [in] Dir handle
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wclosedir(ven_dir_handle_t dir_handle);


/**
 *  ven_file_wdir_get_nb_files
 *
 *  @brief  Get total number of files/folders in the directory handle.
 *
 *  @param  dir_handle     [in] Dir handle
 *  @param  nb_files       [out] Total number of files/folders
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wdir_get_nb_files(ven_dir_handle_t dir_handle, s32 *nb_files);


/**
 *  ven_file_wdir_get_info
 *
 *  @brief  Get file/folder information by index in the directory handle.
 *
 *  @param  dir_handle     [in] Dir handle
 *  @param  index           [in] The index of what you want to get.
 *  @param  output_info     [out] The query result for file or folder information.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wdir_get_info(ven_dir_handle_t dir_handle, s32 index, ven_file_info_t * output_info);


/**
 *  ven_file_syncFolder
 *
 *  @brief  Sync a given folder path to MMI's DB.
 *
 *  @param  u16             [in] Folder path
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
bool ven_file_syncFolder(u16 *pFolderPath, ven_req_data_t* ptVenReq);

/**
 *  ven_file_wget_open_file_info
 *
 *  @brief  Get file information by file handle.
 *
 *  @param  file_handle     [in] file handle
 *  @param  output_info     [out] The query result for file information.
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR if failed
 */
s32 ven_file_wget_open_file_info(ven_file_handle_t file_handle,  ven_file_info_t * output_info);

/**
 *  ven_file_mount
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_mount(ven_file_device_type_t device_type);

/**
 *  ven_file_fopen
 *
 *  Fade out function, no longer use !!
 */
ven_file_handle_t ven_file_fopen(const u8 *path, const u8 *mode);


/**
 *  ven_file_fread
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_fread(void * ptr, s32 size, ven_file_handle_t file_handle);

/**
 *  ven_file_fwrite
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_fwrite(void * ptr, s32 size, ven_file_handle_t file_handle);

/**
 *  ven_file_fclose
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_fclose(ven_file_handle_t file_handle);

/**
 *  ven_file_fseek
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_fseek(ven_file_handle_t file_handle, s32 offset, s32 whence);

/**
 *  ven_file_ftell
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_ftell(ven_file_handle_t file_handle);

/**
 *  ven_file_changeDir
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_changeDir(const u8 *path);

/**
 *  ven_file_makeDir
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_makeDir(const u8 *path);


/**
 *  ven_file_removeDir
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_removeDir(const u8 *path);


/**
 *  ven_file_removeDirAll
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_removeDirAll(const u8 *path);


/**
 *  ven_file_unlink
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_unlink(const u8 *path);


/**
 *  ven_file_exists
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_exists(const u8 *path);


/**
 *  ven_file_rename
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_rename(const u8 *path_old, const u8 *path_new);

/**
 *  ven_file_getTotalSpace
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_getTotalSpace(void);

/**
 *  ven_file_getTotalSpace
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_getFreeSpace(void);

/**
 *  ven_file_getFileCountInDir
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_getFileCountInDir(const u8 *path);

/**
 *  ven_file_getFileInfoInDir
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_getFileInfoInDir(const u8 *path, s32 index, ven_file_info_t * output_info);

/**
 *  ven_file_isDirectory
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_isDirectory(ven_file_info_t * info);

/**
 *  ven_file_fstat
 *
 *  Fade out function, no longer use !!
 */
s32 ven_file_fstat(const u8 *name, ven_simple_file_info_t * output_info);


#endif //__VEN_FILE_H_
