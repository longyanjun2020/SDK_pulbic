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
 * UPDATED DATE:
 *      2004/11/04
 *
 * REVISION:
 *      2004/10/23,    Jack Chung,    Adopted from MMM code.
 *      2004/11/04,    Jack Chung,    Revised documentation.
 *      2005/12/29,    yih,           clean useless code/KSI, revised docs
 *
 ***************************************************************************/

#ifndef KJAVA_SYS_FS_HEADER
#define KJAVA_SYS_FS_HEADER

/**
 * @file kjava_sys_fs.h
 * File System KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup file_system_ksi
 *  @{
 */

/** 
 * @addtogroup kjava_sys_fs_io Common File System KSI
 * An interface for performing common file IO operations.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface can be called in multiple threads concurrently. 
 * That is, in the KVE thread, this KSI is called to access the files of AJSC Java application repository, or 
 * to access general files from JSR-75 <code>FileConnection</code> (if supported).
 * In another thread, the AMS may call @ref Application_Repository or 
 * @ref permission_control_system_aci ACIs, which may trigger a call to this KSI. 
 * 
 *
 * @par Include file 
 * \#include kjava_sys_fs.h
 * @{
 */


/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/
/**
 * @name Root Attribute
 * @{
 */
/** Root Attribute: Public */
#define KJAVA_FILE_ROOT_PUBLIC            (0x01)
/** Root Attribute: Private, which cannot be accessed by Java application */
#define KJAVA_FILE_ROOT_PRIVATE           (0x02)
/** 
 * @} 
 */

/**
 * @name File Attribute
 * @{
 */
/** File Attribute: Readable */
#define KJAVA_FILE_ATTR_READABLE           (0x04)
/** File Attribute: Writable */
#define KJAVA_FILE_ATTR_WRITABLE           (0x08) 
/** File Attribute: Hidden from user */
#define KJAVA_FILE_ATTR_HIDDEN             (0x01)
/** File Attribute: Target is a directory */
#define KJAVA_FILE_ATTR_DIRECTORY          (0x02)
/** 
 * @} 
 */

/**
 * @name File Open Mode
 * @{
 */
/** File open mode: Read operation enabled */
#define KJAVA_FILE_OPEN_READ               (0x01)
/** File open mode: Write operation enabled */
#define KJAVA_FILE_OPEN_WRITE              (0x02)
/** File open mode: Read and write operation enabled */
#define KJAVA_FILE_OPEN_RW                 (0x04)
/** File open mode: Create a file, should fail if file already exist */
#define KJAVA_FILE_OPEN_CREATE             (0x10)
/** File open mode: Open a file, should fail if file does not exist. */
#define KJAVA_FILE_OPEN_EXCL               (0x40)
/** 
 * @} 
 */

/**
 * @name File Seek Operation
 * @{
 */
/** Move file position to an absolute position. */
#define KJAVA_FILE_SEEK_SET                (0)
/** Move file position to a position relative to the current file position. */
#define KJAVA_FILE_SEEK_CUR                (1)
/** Move file position to a position relative to the end of file.*/
#define KJAVA_FILE_SEEK_END                (2)
/** 
 * @} 
 */

/**
 * @name Result Code
 * @{
 */
/** Error code: none */
#define KJAVA_FILE_ERR_NONE                (0)
/** Error code: File already exist */
#define KJAVA_FILE_ERR_ALREADY_EXIST       (-1)
/** Error code: File does not exist */
#define KJAVA_FILE_ERR_NOT_EXIST           (-2)
/** Error code: IO Error */
#define KJAVA_FILE_ERR_IO_ERR              (-3)
/** Error code: Directory is not empty */
#define KJAVA_FILE_ERR_DIRECTORY_NOT_EMPTY (-4)
/** Error code: target is not a directory */
#define KJAVA_FILE_ERR_NOT_DIRECTORY       (-5)
/** Error code: reach end of file */
#define KJAVA_FILE_ERR_END_OF_FILE         (-6)
/** Error code: invalid position */
#define KJAVA_FILE_ERR_INVALID_POSITION    (-7)
/** Error code: reach end of directory */
#define KJAVA_FILE_ERR_END_OF_DIRECTORY    (-8)
/** Error code: the result will be passed by asynchronous callback */
#define KJAVA_FILE_ERR_ASYNC_FUNCTION      (-9)
/** Error code: no free root entry could be set */
#define KJAVA_FILE_ERR_ROOT_FULL           (-20)
/** Error code: root already exist */
#define KJAVA_FILE_ERR_ROOT_ALREADY_EXIST  (-21)
/** Error code: root does not exist */
#define KJAVA_FILE_ERR_ROOT_NOT_EXIST      (-22)
/** Error code: root length too long */
#define KJAVA_FILE_ERR_ROOT_TOO_LONG       (-23)
/** 
 * @} 
 */

/**
 * @name Path Name Length
 * @{
 */
/** The maximum length of an authority's name */
#define KJAVA_MAX_AUTHORITY_NAME_LENGTH    (32)
/** The maximum length of an authority's path */
#define KJAVA_MAX_AUTHORITY_PATH_LENGTH    (128)
/** The maximum length of the path of a file in the platform. */
#define KJAVA_MAX_PATH_LENGTH              (256)
/** The maximum length of the name of a file in the platform. */
#define KJAVA_MAX_FILE_NAME_LENGTH         (256)

#ifdef SUPPORT_AMS_EXTENSION_LIBRARY
#define MAX_ABSOLUTE_PATH_LENGTH               1100//MSTAR-129

#define MAX_AUTHORITY_NAME_LENGTH               32
#define MAX_AUTHORITY_PATH_NAME_LENGTH          64
#define MAX_AUTHORITY_COUNT                     8
#endif
/** 
 * KSI file handle type 
 */
typedef const void* KJavaFileHandle;

/** 
 * Callback function type for asynchronous I/O.
 * This is reserved for future use.
 * <!--
 * @param taskId
 *        Pass the value passed to the function for which this callback is called. 
 * @param event
 *        TBD
 * @return 
 *        TBD
 *
 * When asynchronous file I/O operations are supported, 
 * then when kjava_fs_init() is called, a function of this type is passed to the native system for asynchronous I/O. 
 *
 * By default, asynchronous file I/O operations are disabled.
 * To support asynchronous operations, a library customization request needs to be submitted.
 * -->
 */
typedef int (*KJavaFsNotifyEvent)( signed long taskId, unsigned long* event );

/** @} */

/** 
 * @addtogroup kjava_sys_fs_dir Directories Authetication KSI
 * An interface for retrieving path mappings available to AJSC.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface can be called in multiple threads concurrently. 
 * That is, in the KVE thread, this KSI is called to access the files of AJSC Java application repository, or 
 * to access general files from JSR-75 <code>FileConnection</code> (if supported).
 * In another thread, the AMS may call @ref Application_Repository or 
 * @ref permission_control_system_aci ACIs, which may trigger a call to this KSI. 
 * 
 *
 * @par Include file 
 * \#include kjava_sys_fs.h
 * @{
 */

/** 
 * The structure type for storing a path mapping.
 * This structure type is used for passing path mapping information via kjava_fs_getPath().
 */
typedef struct _KJavaPathMappingTag
{
    /** The authority name */
    char    name[KJAVA_MAX_AUTHORITY_NAME_LENGTH];
    /** 
     * The real path name for the authority.
     * The path must end with the value returned by kjava_fs_getPathSeparator().
     */
    char    path[KJAVA_MAX_PATH_LENGTH];
    /** 
     * The root attribute. 
     * The value must be either #KJAVA_FILE_ROOT_PUBLIC or #KJAVA_FILE_ROOT_PRIVATE.
     * For all other values, AJSC treats it as #KJAVA_FILE_ROOT_PRIVATE.
     *
     * When KJavaFsRootChange() is called passing #KJAVA_FILE_ROOT_REMOVED in the 
     * <i>type</i> parameter, this member is ignored.
     */
    int    attr;
}
KJavaPathMappingEntry;

/** @} */

/** 
 * @addtogroup kjava_sys_fs_io
 * @{
 */
/** The structure type for storing a 64bit long variable. */
typedef struct _KJavaLongSizeTag
{
    /** The high 32-bit of the long variable. */
    unsigned long high;
    /** The low 32-bit of the long variable. */
    unsigned long low;
} KJavaLongSize;
#ifdef SUPPORT_AMS_EXTENSION_LIBRARY
typedef struct _AuthorityEntryTag
{
    char        name[MAX_AUTHORITY_NAME_LENGTH];
    int         nameLength;
    char        path[MAX_AUTHORITY_PATH_NAME_LENGTH];
                /** path must end with KJAVA_FILE_PATHSEP */
    int         attr;
}
AuthorityEntry;
#endif

/** The structure type for storing detailed information about a file. */
typedef struct _KJavaStatTag
{
    /** 
     * The file attribute.
     * If the native system does not support <code>FileConnection</code> (JSR75), the value set in this member is ignored. 
     * If the native system supports JSR75, the value set to this member should be a combination of the following bits:
     * - #KJAVA_FILE_ATTR_READABLE
     * - #KJAVA_FILE_ATTR_WRITABLE
     * - #KJAVA_FILE_ATTR_HIDDEN
     * - #KJAVA_FILE_ATTR_DIRECTORY
     */
    int     attr;

    /** 
     * The last modified date of the file or directory as elapsed milliseconds from 0:00:00.000, January 1, 1970 (GMT).
     * If the native system does not support <code>FileConnection</code> (JSR75), the value set in this member is ignored. 
     */
    KJavaLongSize lastModify;

    /** 
     * The file size.
     * When the connection is a directory, this member is ignored and
     * AJSC uses kjava_fs_sizedir() or kjava_fs_available() to query the directory size.
     */
    KJavaLongSize size;
}
KJavaStat;

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/
#ifdef SUPPORT_AMS_EXTENSION_LIBRARY
const char* uri2path(const char *uri, char *pathBuffer, int bufferLength, AuthorityEntry **entry_pp);
#endif
/**
 *        Initializes the native file system component.
 * @param callback
 *        This parameter is reserved for future use. Pass #AJ_NULL in this parameter.
 *        <!--
 *        The callback function to notify the asynchronous IO result. 
 *        Pass #AJ_NULL in this parameter when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 *
 * The function needs to:
 *  - prepare path mappings.
 *  - allocate necessary resources.
 *  - create a directory for the AJSC Java application repository if the
 *    directory doesn't exist.
 *  .
 *
 * This function is called in the function context of ajms_init().
 */
void kjava_fs_init( KJavaFsNotifyEvent callback );

/** 
 * Finalizes the native file system component.
 *
 * The function needs to release file system resources allocated after kjava_fs_init() is called.
 *
 * This function is called in the function context of ajms_fini().
 */
void kjava_fs_fini(void);

/**
 * Opens a file.
 * @param fileName
 *        A pointer to the string containing the name of the file to be opened.
 * @param mode
 *        The file open mode.
 *        One of the following read/write mode bits is set:
 *        - #KJAVA_FILE_OPEN_READ
 *        - #KJAVA_FILE_OPEN_WRITE
 *        - #KJAVA_FILE_OPEN_RW
 *        .
 *        Either of the following file creation mode bits is set:
 *        - #KJAVA_FILE_OPEN_CREATE
 *        - #KJAVA_FILE_OPEN_EXCL
 *        .
 *       
 * @param taskId
 *        Pass 0 in this parameter. This parameter is reserved for future use.
 *        <!--
 *        The task identifier to be passed to the asynchronous callback function passed to kjava_fs_init(). 
 *        The native system should not reference this parameter when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 * @param err
 *        A pointer to the buffer for putting a result code:
 *        - #KJAVA_FILE_ERR_NONE<br>
 *          if the function succeeds. The return value must not be #AJ_NULL.
 *        - #KJAVA_FILE_ERR_ALREADY_EXIST<br>
 *          if the function fails because the open mode is #KJAVA_FILE_OPEN_CREATE but the file already exists.
 *        - #KJAVA_FILE_ERR_IO_ERR<br>
 *          if the function fails due to an I/O error. 
 *        - #KJAVA_FILE_ERR_NOT_EXIST<br>
 *          if the function fails because the open mode is #KJAVA_FILE_OPEN_EXCL but the file does not exist.
 *        . 
 * @retval "The file handle value" if the operation succeeds
 * @retval #AJ_NULL if it fails.
 */
KJavaFileHandle kjava_fs_open(const char *fileName, const int mode, signed long taskId, int* err );

/**
 * Closes a file.
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
int kjava_fs_close(KJavaFileHandle hFile, signed long taskId);

/**
 * Reads from a file
 * @param ptr
 *        A pointer to the buffer for putting the data read.
 * @param size
 *        The size in bytes of the buffer indicated by <i>ptr</i>.
 * @param read
 *        A pointer to the buffer for putting the size in bytes of the data actually read.
 * @param taskId
 *        Pass 0 in this parameter. This parameter is reserved for future use.
 *        <!--
 *        The task identifier to be passed to the asynchronous callback function passed to kjava_fs_init(). 
 *        The native system should not reference this parameter when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_fs_open() is designated.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 * @retval #KJAVA_FILE_ERR_END_OF_FILE if the function fails because the end of file has been reached.
 */
int kjava_fs_read(void* ptr, signed long size, signed long* read,
                             KJavaFileHandle hFile, signed long taskId);

/**
 * Writes to a file.
 * @param ptr
 *        A pointer to the buffer holding the data to be written.
 * @param size
 *        The size in bytes of the data indicated by <i>ptr</i>.
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
 * <p>
 * AJSC expects kjava_fs_write() to write all the data at once. 
 * kjava_fs_write() is allowed to return #KJAVA_FILE_ERR_NONE only if all the data of requested <i>size</i> is written.
 */
int kjava_fs_write(void* ptr, signed long size, KJavaFileHandle hFile, signed long taskId);

/**
 * Moves the file access position to a designated location.
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_fs_open() is designated.
 * @param offset
 *        The target file position.
 * @param whence
 *        The starting point for the file pointer move.
 *        One of the following values is designated.
 *        - #KJAVA_FILE_SEEK_SET<br>
 *          <i>offset</i> is the absolute file position (an offset from the
 *          beginning of the file) desired. <i>offset</i> is a positive value.
 *        - #KJAVA_FILE_SEEK_CUR <br>
 *          <i>offset</i> is a position relative to the current file position.
 *          <i>offset</i> can meaningfully be either positive or negative.
 *        - #KJAVA_FILE_SEEK_END <br>
 *          <i>offset</i> is a position relative to the end of file. <i>offset</i>
 *          can meaningfully be either positive (to increase the size of the file) or
 *          negative.
 *        .
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
 * @retval #KJAVA_FILE_ERR_INVALID_POSITION if an invalid parameter is passed in <i>offset</i> and <i>whence</i>.
 * <p>
 * This function is used to set the file position for the file indicated by
 * <i>hFile</i>. The value of <i>offset</i> determines the new
 * position, in one of three ways selected by the value of <i>whence</i>.
 */
int kjava_fs_seek(KJavaFileHandle hFile, KJavaLongSize* offset, int whence, signed long taskId);

/**
 * Retrieves the access position of a file.
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_fs_open() is designated.
 * @param offset
 *        A pointer to the buffer for putting the current file access position.
 * @param taskId
 *        Pass 0 in this parameter. This parameter is reserved for future use.
 *        <!--
 *        The task identifier to be passed to the asynchronous callback function passed to kjava_fs_init(). 
 *        Pass #AJ_NULL when not supporting asynchronous file I/O.
 *        By default, asynchronous file I/O operations are disabled.
 *        To use asynchronous operations, a library customization request needs to be submitted.
 *        -->
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_fs_tell(KJavaFileHandle hFile, KJavaLongSize* offset, signed long taskId);

/**
 * Truncates the size of a file indicated by file handle
 * @param hFile
 *        The file handle.
 *        The value returned by kjava_fs_open() is designated.
 * @param size
 *        The new file length in bytes.
 *        Only a size smaller than the current file size is designated.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_fs_truncate(KJavaFileHandle hFile, KJavaLongSize* size );

/**
 * Removes a file
 * @param fileName
 *        A pointer to the string containing the name of the file to be removed.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the file <i>fileName</i> does not exist.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 */
int kjava_fs_remove(const char* fileName);

/**
 * Renames a file
 * @param oldName
 *        A pointer to the string containing the original file name.
 * @param newName
 *        A pointer to the string containing the new file name.
 * @retval #KJAVA_FILE_ERR_NONE
 *         if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST
 *         if the file <i>oldName</i> does not exist.
 * @retval #KJAVA_FILE_ERR_ALREADY_EXIST
 *         if the file <i>newName</i> already exists.
 * @retval #KJAVA_FILE_ERR_IO_ERR
 *         if the function fails for any other reason.
 */
int kjava_fs_rename(const char* oldName, const char* newName);

/**
 * Gets information about a file indicated by file name.
 * @param fileName
 *        A pointer to the string containing the file name.
 * @param stat
 *        A pointer to the buffer for putting the obtained information.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST if the file <i>fileName</i> does not exist.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails due to an IO error.
 *
 * @par When not supporting <code>FileConnection</code> (JSR-75)
 *   - This function need not fill <i>{@link KJavaStat#lastModify stat->lastModify}</i> 
 *     and <i>{@link KJavaStat#attr stat->attr}</i>. 
 *   .
 * @par When supporting <code>FileConnection</code> (JSR-75) 
 *   - If the file system does not support "last modified date" attribute, 
 *     0xFFFFFFFF should be set in the 
 *     <i>{@link KJavaLongSize#high high}</i> and <i>{@link KJavaLongSize#low low}</i> members 
 *     of <i>{@link KJavaStat#lastModify stat->lastModify}</i>.
 *   - For the <i>{@link KJavaStat#attr stat->attr}</i> member,
 *     it is mandatory for the native system to set the 
 *     #KJAVA_FILE_ATTR_DIRECTORY flag correctly. 
 *     #KJAVA_FILE_ATTR_READABLE, #KJAVA_FILE_ATTR_WRITABLE and #KJAVA_FILE_ATTR_HIDDEN flags can be left untouched.
 *   .
 *
 *<p>
 * See @ref page_fileconnection for details.
 *
 */
int kjava_fs_stat2(const char *fileName, KJavaStat* stat);

/** @} */

/** 
 * @addtogroup kjava_sys_fs_dir
 * @{
 */

/**
 * Gets the path separator character of the native file system.
 * @return 
 *        Return the path separator character.
 */
unsigned char kjava_fs_getPathSeparator(void);

/**
 * Gets the number of path mappings for the platform.
 * @return 
 *        Return the number of path mappings. It must be 1 or more.
 *
 * At least, there must be one path mapping for java. 
 * The <i>{@link KJavaPathMappingEntry#name name}</i> field of the path mapping #KJavaPathMappingEntry for java should be "java". 
 * AJSC uses the java path mapping for the AJSC Java application repository to store Java applications. 
 */
int kjava_fs_getPathCount(void);

/**
 * Gets a path mapping for the platform.
 * @param index
 *        The index of the path mapping. Its value is in the range between
 *        0 and N-1, where N is the return value of kjava_fs_getPathCount().
 * @param map
 *        A pointer to the #KJavaPathMappingEntry structure for putting the path mapping.
 *        The function should fill members of the designated structure.
 * @retval #KJAVA_FILE_ERR_NONE if the function succeeds.
 * @retval #KJAVA_FILE_ERR_IO_ERR if the function fails.
 */
int kjava_fs_getPath(int index, KJavaPathMappingEntry* map);

/**
 * Gets the available space for a path.
 * @param path
 *        A pointer to the string containing the path.
 * @param total
 *        A pointer to the buffer for putting the total space size (in bytes) available under the path.
 *        This value is not used when <code>FileConnection</code> is not supported.
 * @param free
 *        A pointer to the buffer for putting the free space size (in bytes) available under the path.
 * @retval #KJAVA_FILE_ERR_NONE 
 *         if the function succeeds.
 * @retval #KJAVA_FILE_ERR_NOT_EXIST 
 *         if the function fails because <i>path</i> is a file.
 * @retval #KJAVA_FILE_ERR_IO_ERR 
 *         if the function fails for any other reason.
 */
int kjava_fs_available(const char* path, KJavaLongSize* total,
                                         KJavaLongSize* free );

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_FS_HEADER */

