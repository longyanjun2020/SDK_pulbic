/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/***************************************************************************
 * FILE: kjava_sys_fs_dev.h
 *
 * DESCRIPTION:
 *      The module is one of KJava interface modules. It is for device's protected 
 *      file system handling.
 *
 * UPDATED DATE:
 *      2006/01/28
 *
 * REVISION:
 *                 yih
 *
 ***************************************************************************/
 
 
#ifndef KJAVA_DRM_FS_HEADER
#define KJAVA_DRM_FS_HEADER

/**
 * @file kjava_sys_fs_dev.h
 * File System KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup file_system_ksi
 *  @{
 */
 
/*
 *  Interfaces listed in the group are used for JAD/JAR file IO of the
 *  #AJMS_APPLICATION_TYPE_3 application. In other words, if device's AMS
 *  does not support such Java application type. All the KSI should not be
 *  implemented. See 
 *  JBlendia document for the detail of #AJMS_APPLICATION_TYPE_3 application.
 */

/** 
 * @addtogroup kjava_dev_fs_io Device Protected File Access KSI
 * An interface for accessing device protected files.
 *
 * This interface needs to be implemented by the device manufacturer when supporting {@link #AJMS_APPLICATION_TYPE_3 Storage type 3} applications.
 * When not supporting, this interface need not exist in the native system.
 * 
 * Support of {@link #AJMS_APPLICATION_TYPE_3 Storage type 3} applications is a library option.
 * By default, the option is disabled.
 * To support the option, a library customization request needs to be submitted.
 *
 * This interface is called in the KVE thread.
 *
 * @par Include file 
 * \#include kjava_sys_fs_dev.h
 * @{
 */

/** KSI device protected file handle type */
typedef const void* KJavaDevFileHandle;

/**
 * @name Result Code
 * @{
 */
/** Error code: None */
#define KJAVA_DEVFILE_ERR_NONE          (0)

/** Error code: The file does not exists. */
#define KJAVA_DEVFILE_ERR_NOT_EXIST     (-2)

/** Error code: An I/O error occurred. */
#define KJAVA_DEVFILE_ERR_IO_ERR        (-3)

/** Error code: End of file reached */
#define KJAVA_DEVFILE_ERR_END_OF_FILE   (-6)
/** 
 * @} 
 */

/**
 * Opens a device protected file
 * @param fileName
 *        A pointer to the string containing the name of the file to be opened.
 * @param err
 *        A pointer to the buffer in which this function should store a result code.
 *        - #KJAVA_DEVFILE_ERR_NONE<br>
 *          if the function succeeds. The return value must not be #AJ_NULL.
 *        - #KJAVA_DEVFILE_ERR_NOT_EXIST<br>
 *          if the function fails because the file does not exist or is not accessible currently.
 *        . 
 * @retval "The file handle value" if the function succeeds; <br>
 * @retval #AJ_NULL if it fails.
 *
 * The file opened by this KSI is used for reading only. 
 * In order words, AJSC assumes that the file exists and is readable.
 */
KJavaDevFileHandle kjava_dfs_open(const char *fileName, int* err );

/**
 *        Closes a device-protected file.
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_dfs_open() is designated.
 * @retval #KJAVA_DEVFILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_DEVFILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_dfs_close(KJavaDevFileHandle hFile);

/** 
 *        Reads a file.
 * @param ptr
 *        A pointer to the buffer in which this function should store the data read.
 * @param offset
 *        The file position to start reading. 
 *        It is designated as the offset (in bytes) from the beginning of the file.
 * @param size
 *        The size (in bytes) to be read.
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_dfs_open() is designated.
 * @param read
 *        A pointer to the buffer in which this function should set the number of bytes (0 or more) actually read.
 * @retval #KJAVA_DEVFILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_DEVFILE_ERR_IO_ERR if the function fails due to an IO error.
 * @retval #KJAVA_DEVFILE_ERR_END_OF_FILE if the function fails because the end of file has been reached.
 * <p>
 * This function is called in the KVE thread to read the JAD or JAR file
 * when application installation is requested via ajms_ota_installEx() or when 
 * an application launch is requested via ajms_arc_runApp().
 *
 * If the size of read data is less than the requested size, AJSC retries reading the remaining data by this function.
 *
 * If the size of the data read is greater than the requested size, AJSC treats this result as an error.
 * If the read data exceeds the buffer size, the behavior of AJSC is not guaranteed.
 */
int kjava_dfs_read(void* ptr, 
                  signed long offset,
                  signed long size, 
                  signed long* read,
                  KJavaDevFileHandle hFile);

/**
 * Gets information about a file.
 * @param fileName
 *        A pointer to the string containing the file name.
 * @param size
 *        A pointer to the buffer in which this function should store the file size.
 *        AJSC assumes that the JAR/JAD size is no more than 0x7FFFFFFF bytes.
 * @retval #KJAVA_DEVFILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_DEVFILE_ERR_NOT_EXIST if the file <i>fileName</i> does not exist.
 * @retval #KJAVA_DEVFILE_ERR_IO_ERR if the function fails due to an IO error.
 * <p>
 * This function is used to query the file size as well as the file existence. 
 */
int kjava_dfs_stat2(const char *fileName, signed long* size );

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_FS_HEADER */
