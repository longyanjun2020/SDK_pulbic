/**
 * Copyright 2004-2007 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkFileConnectionFile.h
 *   FileConnection File JSI
 */
/**
 * @addtogroup Module_FileConnection_File_JSI
 * @{
 */

#ifndef ___JK_FILECONNECTION_FILE_H
#define ___JK_FILECONNECTION_FILE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "JkFileConnectionCommon.h"


/**
 * Gets the status of file system support in the target device.
 *
 * @return 
 *         Return a combination (logical sum) of the following constants.
 *         - #JK_FILECONNECTION_FILESYSTEM_SUPPORTED: <br>
 *            The target device supports a file system.
 *         - #JK_FILECONNECTION_FILESYSTEM_READ_ACCESSIBLE: <br>
 *            The target device supports read access to the file system.
 *         .
 *
 * Return the nature of file system support in the native system.
 */
JKSint32 JkFileConnectionIsFileSystemSupported(void);


/**
 * Gets the root names of available file systems.
 * 
 * @param array
 *        A pointer to the structure holding an array of pointers to root name strings.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 * 
 * Put in the structure indicated by the <i>array</i> parameter all the root names of file systems 
 * currently available to JBlend.
 * Call AmFileConnectionUtilsAddString() to put the root name strings in this structure.
 * 
 * See the "FileConnection Optional Package 1.0 Specification" on the root name string format.
 */
JKFileConnectionErr JkFileConnectionListRoots(JKFileConnectionStringArray* array);


/**
 * Starts watching for and notifying of file system root structure changes.
 * 
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded. 
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_GENERAL_ERR: <br>
 *            The function failed.
 *         .
 * 
 * This function is called by JBlend immediately after a <code>javax.microedition.io.file.FileSystemListener</code> 
 * instance is registered for the first time in the <code>javax.microedition.io.file.FileSystemRegistry</code> class.
 * 
 * When this function is called, in the native system start watching the available root structures as
 * returned by JkFileConnectionListRoots(), and notify JBlend of an event when a root structure change is detected.
 * 
 * It is possible even before this function is called to start watching for root structure changes and to
 * make event notification when a change occurs. While this will not cause problems with the behavior
 * of the JVM itself, queueing of an event may fail if no event queue has been created.
 * 
 * @see AmNotifyFileConnectionRootChangedEvent()
 * @see JkFileConnectionEndRootChangeNotification
 */
JKFileConnectionErr JkFileConnectionStartRootChangeNotification(void);


/**
 * 
 * Ends watching for and notifying of file system root structure changes.
 * 
 * @return
 * 	       Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded. 
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_GENERAL_ERR: <br>
 *            The function failed.
 *         .
 *
 * This function is called by JBlend at the time of VM termination.
 * It is called even if JkFileConnectionStartRootChangeNotification() has 
 * not been called.
 * If the watching operation for root structure changes has not yet
 * started, return #JK_FILECONNECTION_SUCCESS. 
 * @see JkFileConnectionStartRootChangeNotification()
 */
JKFileConnectionErr JkFileConnectionEndRootChangeNotification(void);


/**
 * 
 * Opens a connection to a file or directory.
 * 
 * @param connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param onlyExisting
 * 	#JK_TRUE if connection is not to be made to a nonexistent file/directory,
 * 	else #JK_FALSE.
 * @param dir 
 *	A pointer to the memory area for putting whether or not the connection target is a directory.
 *	When the connection target exists, put #JK_TRUE if it is a directory, 
 *	else put #JK_FALSE.
 *	When the connection target does not exist, do NOT put any value.
 * @param id
 * 	A pointer to the buffer for putting the file ID.
 * 	This ID is solely for reference by the native system, and
 * 	is never used by the Java execution environment.
 * @return
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_INVALID_NAME_ERR: <br>
 *            The function failed because of an invalid path name.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because of an access mode violation.
 *         - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR:<br>
 *            The function failed because #JK_TRUE was passed to the 
 *            <i>onlyExisting</i> parameter, but the target does not exist. 
 * 	       - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 * 
 * Open a connection to the file or directory held in the structure indicated 
 * by the <i>connection</i> parameter. 
 * 
 * The structure indicated by the <i>connection</i> parameter is passed to 
 * identify the file connection for all file/directory operation functions 
 * defined in this interface and in the @ref Module_FileConnection_Stream_JSI. 
 * The native system must not modify the values held in this structure. 
 * 
 * If the native system uses a file ID as an identifier, a unique file ID 
 * value must be stored in the buffer indicated by <i>id</i>. 
 * When this function returns to its caller, the file ID value stored in the 
 * buffer indicated by <i>id</i> is set by JBlend in the <i>id</i> member of 
 * the structure indicated by <i>connection</i>.
 * JBlend then passes this structure as a parameter when calling other 
 * functions defined in this interface. 
 * 
 * If the connection indicated by the Java application represents a directory, 
 * JBlend sets #JK_TRUE to the <i>dir</i> member of the structure indicated by 
 * <i>connection</i>; if it represents a file, JBlend sets #JK_FALSE.
 * This value may not be correct for the file or directory that is existing currently
 * or that might be created afterwards.
 * 
 * If a connection is opened to a nonexistent file or directory, the 
 * file/directory must not be created.
 */
JKFileConnectionErr JkFileConnectionOpenConnection(JKFileConnectionConnectionInfo* connection,JKBool onlyExisting,JKBool* dir,JKSint32* id);


/**
 * Closes a connection to a file or directory.
 * 
 * @param connection 
 *        A pointer to the structure holding file/directory connection information.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 */
JKFileConnectionErr JkFileConnectionCloseConnection(JKFileConnectionConnectionInfo* connection);


/**
 * Determines whether a file or directory is readable or not.
 * 
 * @param connection 
 *        A pointer to the structure holding file/directory connection information.
 * @param readable 
 *        A pointer to the buffer for putting whether the file/directory is readable or not.
 *        Set #JK_TRUE if the file/directory is readable, or #JK_FALSE if not readable.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access 
 *            to the file/directory.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the 
              connection was opened for write access.
 *         .
 * 
 * 	When the file/directory does not exist or is not accessible, set #JK_FALSE
 * 	in the buffer indicated by the <i>readable</i> parameter and return #JK_FILECONNECTION_SUCCESS.
 */
JKFileConnectionErr JkFileConnectionIsReadable(JKFileConnectionConnectionInfo* connection,JKBool* readable);


/**
 * Determines whether a file or directory is writable or not.
 * 
 * @param connection
 *        A pointer to the structure holding file/directory connection information.
 * @param writable 
 *        A pointer to the buffer for putting whether the file/directory is writable or not.
 *        Set #JK_TRUE if the file/directory is writable, or #JK_FALSE if not writable.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access 
 *            to the file/directory.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *         .
 * 
 * 	When the file/directory does not exist or is not accessible, set #JK_FALSE
 * 	in the buffer indicated by the <i>writable</i> parameter and return #JK_FILECONNECTION_SUCCESS.
 */
JKFileConnectionErr JkFileConnectionIsWritable(JKFileConnectionConnectionInfo* connection,JKBool* writable);


/**
 * Determines whether a file or directory is visible or not.
 * 
 * @param connection
 *        A pointer to the structure holding file/directory connection information.
 * @param hidden
 *        A pointer to the buffer for putting whether the file/directory is invisible or not.
 *        Set #JK_TRUE if the file/directory is invisible, or #JK_FALSE if not invisible. 
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access 
 *            to the file/directory.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *         .
 * 
 * 	When the file/directory does not exist or is not accessible, set #JK_FALSE
 * 	in the buffer indicated by the <i>hidden</i> parameter and return #JK_FILECONNECTION_SUCCESS.
 */
JKFileConnectionErr JkFileConnectionIsHidden(JKFileConnectionConnectionInfo* connection,JKBool* hidden);


/**
 * Determines whether the connection is to a directory or not.
 * 
 * @param connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param dir
 *        A pointer to the buffer for putting whether the connection 
 *        target is a directory or not. Set #JK_TRUE if the connection 
 *        target is a directory, or #JK_FALSE if not a directory. 
 * @return
 *          Return one of the following error codes.
 *          - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *          - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *          - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because of an access mode violation.
 *          - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *          - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or 
 *            is not accessible.
 * 	        .
 * 
 */
JKFileConnectionErr JkFileConnectionIsDirectory(JKFileConnectionConnectionInfo* connection,JKBool* dir);


/**
 * 
 * Gets the date and time that a file or directory was last modified.
 *
 * @param *connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param *date
 *	A pointer to the structure for putting the last modified date and time of the file or directory.
 *	Store as elapsed milliseconds from 0:00:00.000, January 1, 1970 (GMT).
 * @return
 *         Return one of the following error codes.
 *        - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *        - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *        - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read 
 *            access to the file/directory.
 *        - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *        - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or 
 *            is not accessible.
 *        - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because the feature (last modified date) is 
 *            not supported by the native system or because an I/O error occurred.
 * 	      .
 * 
 */
JKFileConnectionErr JkFileConnectionGetLastModifiedDate(JKFileConnectionConnectionInfo* connection,JKFileConnectionLong* date);


/**
 * Determines whether a file or directory exists or not.
 * 
 * @param connection
 *        A pointer to the structure holding file/directory connection information.
 * @param exists 
 *        A pointer to the buffer for putting whether the file/directory exists or not.
 *         Set #JK_TRUE if the file/directory exists, or #JK_FALSE if not exist.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access to the file/directory.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *         .
 */
JKFileConnectionErr JkFileConnectionExists(JKFileConnectionConnectionInfo* connection,JKBool* exists);


/**
 * 
 * Gets the size of a file.
 *
 * @param *connection
 * 	A pointer to the structure holding file connection information.
 * @param *size
 * 	A pointer to the structure for putting the file size. Set the size in bytes.  
 * @return
 * 	       Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access 
 *            to the file.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 *         - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is 
 *            not accessible.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 * 
 * If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionGetFileSize(JKFileConnectionConnectionInfo* connection,JKFileConnectionLong* size);


/**
 * Gets the size of a directory. 
 * 
 * @param taskId
 *        The task ID. 
 *        If the requested processing is performed asynchronously, pass this value in
 *        a parameter when calling AmNotifyFileConnectionAsyncFunctionEvent() in order to 
 *        notify JBlend of the processing result.
 * @param connection
 *        A pointer to the structure holding directory connection information.  
 * @param includeSubDirs
 *        #JK_TRUE if the size is to include subdirectories, else #JK_FALSE.  
 * @param size
 *        A pointer to the structure for putting the directory size. 
 *        Set the size in bytes.  
 * @return Return one of the following error codes.
 * 	       - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	       - #JK_FILECONNECTION_ASYNC_FUNCTION: <br>
 *            The processing of this function was started asynchronously.
 * 	       - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	       - #JK_FILECONNECTION_SECURITY_ERR:<br>
 *             The function failed because the application was denied read 
 *             access to the directory.
 * 	       - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed  because the connection was opened for write access.
 * 	       - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or 
 *            is not accessible.
 * 	       - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 * 
 * If #JK_FALSE is designated in <i>includeSubDirs</i>, return the size only of files 
 * in the designated directory itself, not including subdirectories. 
 * If #JK_TRUE is designated, return the size of all files in the directory and 
 * its subdirectories. 
 * 
 * If the connection is to a file, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR. 
 * 
 * When this function performs the requested processing synchronously, 
 * the pointer designated in the <i>size</i> parameter is valid only until this 
 * function returns; when performing it asynchronously, the pointer 
 * remains valid until the native system passes its result to JBlend as an event.
 * 
 * To perform the processing asynchronously, return #JK_FILECONNECTION_ASYNC_FUNCTION
 * from this function.
 * Then when the asynchronous processing is completed, call AmNotifyFileConnectionAsyncFunctionEvent()
 * in order to notify JBlend of the processing result by an event. The event format is as follows. 
 * <ul>
 * <li> event[0]: Task ID. 
 *           The value designated in the <i>taskId</i> parameter of this function. 
 * <li> event[1]: One of the following error codes.
 * 	<ul>
 * 	 <li> #JK_FILECONNECTION_SUCCESS: <br>
 *          The function succeeded. 
 * 	 <li> #JK_FILECONNECTION_MEMORY_ERR: <br>
 *          The function failed because of insufficient memory. 
 * 	 <li> #JK_FILECONNECTION_SECURITY_ERR: <br>
 *         The function failed because the 
 *          application was denied read access to the directory.
 * 	 <li> #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *          The function failed 
 *          because the connection was opened for write access.
 * 	 <li> #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *          The function failed because the file/directory does not exist 
 *          or is not accessible.
 * 	 <li> #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 * 	</ul>
 * </ul>
 */
JKFileConnectionErr JkFileConnectionGetDirectorySize(JKSint32 taskId,JKFileConnectionConnectionInfo* connection,JKBool includeSubDirs,JKFileConnectionLong* size);



/**
 * 
 * Gets the size of the volume where the connected root is located.
 *
 * @param *connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param *size
 *	A pointer to the structure for putting the volume size information.
 *	Set values for all the structure members.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access to the root volume.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the volume does not exist or is not accessible.
 * .
 * 
 */
JKFileConnectionErr JkFileConnectionGetVolumeSize(JKFileConnectionConnectionInfo* connection,JKFileConnectionVolumeSize* size);


/**
 * 
 * Sets invisibility of a file or directory.
 *
 * @param connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param hidden
 *	#JK_TRUE is designated if "hidden" is set, else #JK_FALSE is designated.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file/directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 *
 * If the native system does not support invisible file/directory attribute,  
 * check the error conditions first, then return #JK_FILECONNECTION_SUCCESS if there is no error.
 * If an error is detected, it must be indicated by the return value.
 *
 */
JKFileConnectionErr JkFileConnectionSetHidden(JKFileConnectionConnectionInfo* connection,JKBool hidden);


/**
 * 
 * Sets readability of a file or directory.
 *
 * @param *connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param readable
 *	#JK_TRUE is designated if "readable" is set, else #JK_FALSE is designated.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file/directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 * 
 * If the native system does not support the file/directory readability attribute, 
 * check the error conditions first, then return #JK_FILECONNECTION_SUCCESS if there is no error.
 * If an error is detected, it must be indicated by the return value.
 *
 */
JKFileConnectionErr JkFileConnectionSetReadable(JKFileConnectionConnectionInfo* connection,JKBool readable);


/**
 * 
 * Sets writability of a file or directory.
 *
 * @param connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param writable
 *	#JK_TRUE is designated if "writable" is set, else #JK_FALSE is designated.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file/directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 * 
 * If the native system does not support the file/directory writability attribute, 
 * check the error conditions first, then return #JK_FILECONNECTION_SUCCESS if there is no error.
 * If an error is detected, it must be indicated by the return value.
 *
 */
JKFileConnectionErr JkFileConnectionSetWritable(JKFileConnectionConnectionInfo* connection,JKBool writable);


/**
 * 
 * Searches for files and directories by name.
 *
 * @param connection
 * 	A pointer to the structure holding directory connection information.
 * @param filter
 *	The filter string, which can contain a wildcard character "*".
 *	The string passed in the <code>filter</code> parameter of 
 *	the <code>FileConnection</code> class 
 *	<code>list(java.lang.String filter, boolean includeHidden)</code>
 *	method is passed in this parameter.
 *	When a Java application calls the <code>list()</code> method, "*" is passed.
 * @param includeHidden
 *	#JK_TRUE is designated if files and directories with the hidden attribute are to be included; else #JK_FALSE is designated.
 * @param array
 *	A pointer to the structure for putting file and directory name strings matching the search conditions.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_INVALID_NAME_ERR: <br>
 *            The function failed because of an invalid path name.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied read access to the directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for write access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 * .
 *
 * Search the connected directory for matches to the filter strings set in the 
 * structure indicated by the <i>filter</i> parameter, 
 * and put all matching file and directory name strings in the structure 
 * indicated by the <i>array</i> parameter. 
 * Only names are to be stored, not paths.
 * A "/" must be affixed at the end of directory names.
 * 
 * AmFileConnectionUtilsAddString() is called to put file and directory name 
 * strings in the structure indicated by <i>array</i>.
 * 
 * If the connection is to a file, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionListFiles(JKFileConnectionConnectionInfo* connection,JKFileConnectionString* filter,JKBool includeHidden,JKFileConnectionStringArray* array);


/**
 * 
 * Creates a file of size 0.
 * 
 * @param connection
 * 	A pointer to the structure holding file connection information.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the parent directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_TARGET_ALREADY_EXIST_ERR: <br>
 *            The function failed because the directory already exists.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 * 
 */
JKFileConnectionErr JkFileConnectionCreateFile(JKFileConnectionConnectionInfo* connection);


/**
 * 
 * Creates a new directory.
 *
 * @param *connection
 * 	A pointer to the structure holding directory connection information.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the parent directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_TARGET_ALREADY_EXIST_ERR: <br>
 *            The function failed because the directory already exists.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 * .
 * 
 */
JKFileConnectionErr JkFileConnectionCreateDirectory(JKFileConnectionConnectionInfo* connection);


/**
 * 
 * Truncates a file.
 *
 * @param connection
 * 	A pointer to the structure holding file connection information.
 * @param offset
 *	The offset value (in bytes) starting from which data is to be discarded.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 *
 * Truncate the file by discarding data from the position designated in 
 * <i>offset</i> to the end of the file.
 * If the value designated by <i>offset</i> is larger than the file size, 
 * return #JK_FILECONNECTION_SUCCESS without truncating the file.
 * 
 *  If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionTruncateFile(JKFileConnectionConnectionInfo* connection,JKFileConnectionLong* offset);


/**
 * 
 * Deletes a directory.
 *
 * @param connection
 * 	A pointer to the structure holding directory connection information.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_DIRECTORY_NOT_EMPTY_ERR: <br>
 *            The function failed because the directory is not empty.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 * 
 * If the connection is to a file, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionDeleteDirectory(JKFileConnectionConnectionInfo* connection);


/**
 * 
 * Deletes a file.
 *
 * @param connection
 * 	A pointer to the structure holding file connection information.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 * 
 * If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionDeleteFile(JKFileConnectionConnectionInfo* connection);


/**
 * 
 * Renames a file or directory.
 *
 * @param connection
 * 	A pointer to the structure holding file/directory connection information.
 * @param newConnection
 *	A pointer to the structure holding file/directory connection information after the renaming.
 * @return
 * 	Return one of the following error codes.
 * 	- #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 * 	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 * 	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file/directory.
 * 	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 * 	- #JK_FILECONNECTION_INVALID_NAME_ERR: <br>
 *            The function failed because the path name contains a character invalid.
 * 	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file/directory does not exist or is not accessible.
 * 	- #JK_FILECONNECTION_TARGET_ALREADY_EXIST_ERR: <br>
 *            The function failed because the file/directory already exists.
 * 	- #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 * .
 * 
 * The only difference between members of the <i>connection</i> structure and 
 * <i>newConnection</i> structure is the <i>path</i> member setting.
 * The <i>id</i> member of the <i>newConnection</i> structure and the <i>id</i> 
 * member of the <i>connection</i> structure retain the same value. 
 *
 */
JKFileConnectionErr JkFileConnectionRename(JKFileConnectionConnectionInfo* connection,JKFileConnectionConnectionInfo* newConnection);

/**
 *         Frees a memory area holding the root name.
 *  @param name
 *         A pointer to the structure holding the root name.
 *         The value passed in the <i>rootName</i> parameter 
 *         to the AmNotifyFileConnectionRootChangedEvent() function is passed here.
 *
 *  Free the memory area occupied by the structure <i>*name</i> and the string held by the structure. 
 *  
 *  This function is called the same number of times AmNotifyFileConnectionRootChangedEvent() called by the native system succeeds. 
 * @see AmNotifyFileConnectionRootChangedEvent()
 */
void JkFileConnectionFreeName(JKFileConnectionString *name);


#ifdef __cplusplus
}
#endif

#endif /* ___JK_FILECONNECTION_FILE_H */

/**
 * @} end of group
 */
