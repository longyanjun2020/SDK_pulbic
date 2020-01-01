/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/***************************************************************************
 * FILE: kjava_sys_fs.h
 *
 * DESCRIPTION:
 *      The module is one of KJava interface modules. It is for java protected
 *      file system handling.
 *
 * REVISION:
 *      2006/02/07,    yih,           seperate different level ksi
 *
 ***************************************************************************/

#ifndef KJAVA_ADV_FS_HEADER
#define KJAVA_ADV_FS_HEADER

/**
 * @file kjava_sys_fs_adv.h
 * File System KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup file_system_ksi
 *  @{
 */

#include <kjava_sys_fs.h>

/** 
 * @addtogroup kjava_sys_fs_advance Advanced File System KSI
 * An interface for performing JSR-75 file system operations.
 * This interface must be implemented by the device manufacturer only when supporting JSR-75 <code>FileConnection</code>.
 * When not supporting JSR-75 this interface need not not exist in the native system.
 *
 * Support of JSR-75 <code>FileConnection</code> is a library option. 
 * By default, the option is disabled. To support the option, a library customization request needs to be submitted. 
 * 
 * This interface is called in the KVE thread.
 *
 * @par Include file 
 * \#include kjava_sys_fs_adv.h
 * @{
 */

/** A constant indicating that a file system root has been added to the device. */
#define KJAVA_FILE_ROOT_ADDED        (0)
/** A constant indicating that a file system root has been removed from the device. */
#define KJAVA_FILE_ROOT_REMOVED      (1)

/** Data type for directory handle */
typedef const void* KJavaDirHandle;

/** 
 * Function type for root change notification 
 * @param root
 *        A pointer to the structure indicating the root for which this notification is made.
 * @param type
 *        The notification type.
 *        Pass either of the following:
 *         - #KJAVA_FILE_ROOT_ADDED when a new root is added.
 *         - #KJAVA_FILE_ROOT_REMOVED when an existing root is removed.
 *         .
 * @retval #KJAVA_FILE_ERR_NONE
 *         if the function succeeds in notifying AJSC of the event.
 * @retval #KJAVA_FILE_ERR_ROOT_FULL
 *         if the function fails due to insufficient space for storing path mapping data for root.
 *         This can be returned only for a #KJAVA_FILE_ROOT_ADDED notification.
 * @retval #KJAVA_FILE_ERR_ROOT_ALREADY_EXIST
 *         if the function fails because the path mapping data is already stored.
 *         That is, a root having the authority name indicated by <i>{@link KJavaPathMappingEntry#name root->name}</i> 
 *         has been already registered.
 * @retval #KJAVA_FILE_ERR_ROOT_TOO_LONG
 *         if the function fails because the authority name indicated by <i>{@link KJavaPathMappingEntry#name root->name}</i> 
 *         is too long.
 * @retval #KJAVA_FILE_ERR_ROOT_NOT_EXIST
 *         if the function fails because the root indicated by the the authority name 
 *         <i>{@link KJavaPathMappingEntry#name root->name}</i> has not been registered.
 *         This can be returned only for a #KJAVA_FILE_ROOT_REMOVED notification.
 * @retval #KJAVA_FILE_ERR_IO_ERR
 *         if the function fails for any other reason.
 * <p>
 *
 * The address of a callback function of this type is passed to kjava_fs_setRootChangeNotification().
 */
typedef int (*KJavaFsRootChange)(KJavaPathMappingEntry *root, int type );


/**
 * Flushes cached data of the opened file.
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_fs_open() is designated.
 * @param taskId
 *        Pass 0 in this parameter. This parameter is reserved for future use.
 *        <!--
 *        The task identifier to be passed to the asynchronous callback function passed to kjava_fs_init(). 
 *        The native system should not reference this parameter when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_fs_flush(KJavaFileHandle hFile, signed long taskId );

/** 
 * Sets the file attributes of a file system entry.
 * @param filename
 *        A pointer to the string containing the name of a file system entry. 
 *        The entry can be a file or directory.
 * @param attr
 *        The attribute to set. The value must be a combination of the following flags: 
 *        - #KJAVA_FILE_ATTR_READABLE
 *        - #KJAVA_FILE_ATTR_WRITABLE
 *        - #KJAVA_FILE_ATTR_HIDDEN
 *        .
 *        When the native system does not support some or all of these attributes, ignore bit(s) corresponding to them.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the file or directory <i>filename</i> does not exist.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 * <p>
 *
 * See @ref page_fileconnection for details.
 */ 
int kjava_fs_setAttr( const char* filename, unsigned int attr );

/**
 * Changes the size of a file indicated by file name
 * @param fileName
 *        A pointer to the string containing the file name.
 * @param size
 *        The new size in bytes of the truncated file. 
 *        Only a size smaller than the current file size is designated.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the file <i>fileName</i> does not exist.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails for any other reason.
 */
int kjava_fs_truncate2(const char *fileName, KJavaLongSize  *size );

/**
 * Opens a directory.
 * @param dirName
 *        A pointer to the directory name string.
 * @param err
 *        A pointer to the buffer for putting an error code representing the result.
 *        One of the following values should be set.
 *        - #KJAVA_FILE_ERR_NONE<br>
 *          if the function succeeds. The return value must not be #AJ_NULL.
 *        - #KJAVA_FILE_ERR_NOT_EXIST<br>
 *          if the directory indicated by <i>dirName</i> does not exist.
 *        - #KJAVA_FILE_ERR_IO_ERR<br>
 *          if the function fails for an I/O error. 
 *        .
 * @retval "The directory handle value" if the operation succeeds.
 * @retval #AJ_NULL if it fails.
 *
 * When this function succeeds, a value indicating the position 
 * of current directory entry must index the first directory entry. 
 * This value is called as "directory entry index" in this specification.
 */
KJavaDirHandle kjava_fs_opendir( const char* dirName, int *err );

/**
 * Reads a directory entry.
 * @param hDir
 *        The directory handle.
 *        The value returned by kjava_fs_opendir() is designated.
 * @param filter
 *        The filter string, which can contain a wild card character "*". 
 *        The string passed in the filter parameter of the <code>FileConnection</code> class 
 *        <code>list(java.lang.String filter, boolean includeHidden)</code> method is passed 
 *        in this parameter. When a Java application calls the <code>list()</code> method, 
 *        "*" is passed.
 * @param showHidden 
 *        1 is designated if files and directories with the hidden attribute are to be included; 
 *        else 0 is designated. 
 * @param err
 *        A pointer to the buffer for putting an error code representing the processing result.
 *        One of the following values should be set. 
 *        - #KJAVA_FILE_ERR_NONE<br>
 *          if the function succeeds. The return value must not be #AJ_NULL.
 *        - #KJAVA_FILE_ERR_END_OF_DIRECTORY<br>
 *          if the end of directory has been reached. The return value must be #AJ_NULL.
 *        - #KJAVA_FILE_ERR_IO_ERR<br>
 *          if the function fails for any other reason. The return value must be #AJ_NULL.
 *        .
 * @return 
 *        A pointer to an ASCII string containing the name of 
 *        the directory entry that corresponds to the current directory entry index.
 *
 * Return the directory entry information that corresponds to the current 
 * directory entry index and proceed the index by 1.
 * If the index has already reached the end of directory, set #KJAVA_FILE_ERR_END_OF_DIRECTORY in <i>*err</i> and return #AJ_NULL.
 *
 * If the function succeeds, the return value must remain valid until 
 * next time this function is called or the directory is closed by 
 * kjava_fs_closedir().
 *
 * When the native sytstem does not support the hidden attribute, ignore the <i>showHidden</i> parameter.
 *
 * See @ref page_fileconnection for details.
 */
const char* kjava_fs_readdir(KJavaDirHandle hDir, const char* filter, int showHidden, int *err);

/**
 * Closes a directory
 * @param hDir
 *        The directory handle of the open directory.
 *        The value returned by kjava_fs_opendir() is designated.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_fs_closedir(KJavaDirHandle hDir);

/**
 * Creates a new directory
 * @param dirName
 *        A pointer to the string holding the name of the directory to be created.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 * @retval #KJAVA_FILE_ERR_ALREADY_EXIST if the directory <i>dirName</i> already exists.
 */
int kjava_fs_mkdir(const char* dirName);

/**
 * Removes an existing directory
 * @param dirName
 *        A pointer to the string holding the name of the directory to be removed.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the directory <i>dirName</i> does not exist.
 * @retval #KJAVA_FILE_ERR_DIRECTORY_NOT_EMPTY if the directory <i>dirName</i> is not empty.
 */
int kjava_fs_rmdir(const char* dirName);

/**
 * Calculates the total size of a directory
 * @param dirName
 *        A pointer to the string holding the name of the directory to be calculated.
 * @param includeSubDirs
 *        0 for not to include subdirectories size, 1 for include all subdirectories size.
 * @param size
 *        A pointer to the buffer for putting the total directory size in bytes.
 * @param taskId
 *        Pass 0 in this parameter. This parameter is reserved for future use.
 *        <!--
 *        The task identifier to be passed to the asynchronous callback function passed to kjava_fs_init(). 
 *        The native system should not reference this parameter when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the directory <i>dirName</i> does not exist.
 */
 int kjava_fs_sizedir( const char*     dirName, 
                       int             includeSubDirs,
                       KJavaLongSize  *size,
                       signed long     taskId );

/**
 * Sets or cancels the callback function for notifying the JVM of root path changes.
 * @param rootCallback
 *        The address of the root-notification callback function.
 * @retval KJAVA_FILE_ERR_NONE
 *         if the function succeeds.
 * @retval KJAVA_FILE_ERR_IO_ERR
 *         if the function fails.
 *
 * <p>
 * When <i>rootCallback</i> is a non-#AJ_NULL function address, the native system 
 * should invoke that function every time a change occurs in root directories, 
 * to notify the JVM of the change.
 *
 * When <i>rootCallback</i> is #AJ_NULL, the native system should cancel the 
 * previous root-notification function address and stop
 * monitoring the changes in root directories.
 */
int kjava_fs_setRootChangeNotification( KJavaFsRootChange rootCallback );

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_ADV_FS_HEADER */
