/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkFileConnectionCommon.h
 *   FileConnection Common Header Files 
 */
/**
 * @addtogroup Module_FileConnection_Data_Types
 * @{
 */

#ifndef ___JK_FILECONNECTION_COMMON_H
#define ___JK_FILECONNECTION_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif



#include "JkTypes.h"


/* ========== ========== ==========
	@: Constants.
   ========== ========== ========== */
/**
 * Error code type
 */
typedef JKSint32	JKFileConnectionErr;

/** 
 *  @name Error Codes
 * These are the error codes returned by the @ref Module_FileConnection_File_JSI, 
 * @ref Module_FileConnection_Stream_JSI, and @ref Module_FileConnection_JBI.
 */
 
/*@{*/
/**
 *   Error code: The function succeeded.
 */
#define JK_FILECONNECTION_SUCCESS			 0
/**
 *   Error code: An event must be waited for since the function 
 *   was implemented as an asynchronous function.
 */
#define JK_FILECONNECTION_ASYNC_FUNCTION	-1
/**
 * Error code: Insufficient memory.\ A <code>java.lang.OutOfMemoryError</code> is thrown.
 */
#define JK_FILECONNECTION_MEMORY_ERR		-2
 /**
 *   Error code: The function failed.
 */
#define JK_FILECONNECTION_GENERAL_ERR		-3
/**
 *   Error code: A security error occurred.
 */
#define JK_FILECONNECTION_SECURITY_ERR		-4
/**
 *   Error code: The request conflicts with the access mode.
 */
#define JK_FILECONNECTION_ILLEGAL_ACCESS_ERR	-5
/**
 *  Error code: The path name contains a character invalid in the native system.
 */
#define JK_FILECONNECTION_INVALID_NAME_ERR	-6
/**
 *   Error code: An I/O error occurred.
 */
#define JK_FILECONNECTION_IO_ERR			-7
/**
 *   Error code: The file operation reached the end of the file.
 */
#define JK_FILECONNECTION_EOF				-8
/**
 *   Error code: The processing was interrupted, because close processing was 
 *               requested during processing by an asynchronous JSI function.
 */
#define JK_FILECONNECTION_INTERRUPTED_ERR	-9
/**
 *   Error code: The target directory is not empty.
 */
#define JK_FILECONNECTION_DIRECTORY_NOT_EMPTY_ERR	-10
/**
 *   Error code: The target does not exist.
 */
#define JK_FILECONNECTION_TARGET_NOT_EXIST_ERR		-11
/**
 *   Error code: The connection was closed.
 */
#define JK_FILECONNECTION_CONNECTION_CLOSED_ERR		-12
/**
 *   Error code: The target already exists.
 */
#define JK_FILECONNECTION_TARGET_ALREADY_EXIST_ERR	-13

/*@}*/

/**
 * 	The file/directory access mode type. 
 */
typedef JKSint32	JKFileConnectionAccessMode;

/** 
 * @name Access Mode
 */
 
/*@{*/
/**
 *  Access mode: read-only
 *   
 */
#define JK_FILECONNECTION_READ_ACCESS		0x01
/**
 *   Access mode: write-only
 */
#define JK_FILECONNECTION_WRITE_ACCESS		0x02
/**
 *   Access mode: read/write
 */
#define JK_FILECONNECTION_READ_WRITE_ACCESS	(JK_FILECONNECTION_READ_ACCESS | JK_FILECONNECTION_WRITE_ACCESS)

/*@}*/

/**
 * 	The file/directory attribute type
 */
typedef JKSint32	JKFileConnectionFileAttribute;

/** 
 * @name File/Directory Attributes
 */
 
/*@{*/
/**
 *   File/directory attribute indicating an existing file/directory.
 *   
 */
#define JK_FILECONNECTION_EXISTS		0x01
/**
 *   File/directory attribute indicating a directory.
 */
#define JK_FILECONNECTION_DIRECTORY		0x02
/**
 *   File/directory attribute indicating a hidden file/directory.
 */
#define JK_FILECONNECTION_HIDDEN		0x04
/**
 *   File/directory attribute indicating a readable file/directory.
 */
#define JK_FILECONNECTION_READABLE		0x08
/**
 *   File/directory attribute indicating a writable file/directory.
 */
#define JK_FILECONNECTION_WRITABLE		0x10

/*@}*/

/** 
 * @name Status of File System Support
 */ 
/*@{*/
/**
 *   A constant indicating file system support.
 */
#define JK_FILECONNECTION_FILESYSTEM_SUPPORTED		0x01
/**
 *   A constant indicating that read access to the file system is permitted.
 */
#define JK_FILECONNECTION_FILESYSTEM_READ_ACCESSIBLE	0x02

/*@}*/


/* ========== ========== ==========
	@: Types
   ========== ========== ========== */
/**
 * 	A structure representing a Unicode string.
 */
typedef struct {
   /**
    *  A pointer to a Unicode string (not including the termination code.)
    */
	JKWChar*	text;

   /**
    *   The length (number of characters) of the Unicode string.
    */
	JKSint32	length;
} JKFileConnectionString;


/**
 *  A structure representing a variable-length array of pointers to strings.
 *
 * 	This is a structure that contains a Unicode string structure array whose size
 *      changes dynamically.
 */
typedef struct {
   /**
    *   A pointer to an array of pointers to structures containing Unicode string data.
    */
	JKFileConnectionString**	data;

   /**
    *   The number of elements in the array of pointers to structures containing Unicode string data.
    */
	JKSint32					size;
} JKFileConnectionStringArray;


/**
 * 	A structure of long type values.
 * 	
 *      This structure contains 64-bit data corresponding to the Java <code>long</code> type.
 *      It is used for time and file size data, etc.
 */
typedef struct {
   /**
    * The high 32 bits of the long type value.
    */
	JKUint32	high;

   /**
    * The low 32 bits of the long type value.
    */
	JKUint32	low;
} JKFileConnectionLong;


/**
 * 	A structure containing file/directory connection information.
 *
 *      The JBlend JVM library creates this structure and sets its values
 *      when a connection is opened to a file or directory.
 * 	The contents of this structure must not be altered by any function.
 */
typedef struct {
   /**
    * A structure containing the host name to which connection is to be made. 
    * @htmlonly
    * The host name string is the &lt;host&gt; part of the
    * file://&lt;host&gt;/&lt;path&gt;
    * URL name passed as a parameter in the <code>open</code> method of the <code>javax.microedition.io.Connector</code> class.
    * @endhtmlonly
    */
	JKFileConnectionString		host;

   /**
    *  A structure containing the path name of a file or directory.  
    *  
    * @htmlonly
    * The path name string is the &lt;path&gt; part of the
    * file://&lt;host&gt;/&lt;path&gt;
    * URL name passed as a parameter in the <code>open</code> method of the <code>javax.microedition.io.Connector</code> class.
    * @endhtmlonly
    *  The path name does not include a trailing '/' even if the connection is to a directory.
    */
	JKFileConnectionString		path;

   /**
    * #JK_TRUE if the connection is to a directory, or #JK_FALSE if it is to a file.
    * 
    * If JBlend treats the connection as a directory, #JK_TRUE is set; 
    * if JBlend treats the connection as a file, #JK_FALSE is set.
    * 
    * The value set in this member may not be correct for the file or directory 
    * actually existing in the native system.
    * See the description of @ref Module_FileConnection_File_JSI for details.
    */
	JKBool						dir;

   /**
    *   The file or directory access mode.
    * 
    *   One of the following values:
    * - #JK_FILECONNECTION_READ_ACCESS
    * - #JK_FILECONNECTION_WRITE_ACCESS 
    * - #JK_FILECONNECTION_READ_WRITE_ACCESS
    * .
    */
	JKFileConnectionAccessMode	mode;

   /**
    *  A file ID. This ID is for use by the native system as a file/directory identifier, and is never referenced by JBlend.
    */
	JKSint32					id;
} JKFileConnectionConnectionInfo;


/**
 * 	A structure for putting file/directory information.
 */
typedef struct {
   /**
    *   File/directory attributes.  
    *  
    *   The logical sum of one or more of the following values.
    * - #JK_FILECONNECTION_EXISTS  
    * - #JK_FILECONNECTION_DIRECTORY 
    * - #JK_FILECONNECTION_HIDDEN 
    * - #JK_FILECONNECTION_READABLE
    * - #JK_FILECONNECTION_WRITABLE
    * .
    */
	JKSint32				attributes;

   /**
    *   A structure for putting the size of the file or directory.
    *   If a directory, this size does not include the size of subdirectories 
    *   in the directory.
    */
	JKFileConnectionLong	size1;

   /**
    *   If a directory, a structure for putting the total size including 
    *   the files and subdirectories in the directory.  
    *   Not used if a file.
    */
	JKFileConnectionLong	size2;

   /**
    *   A structure for putting the date and time the file/directory was last modified.  
    *   Date and time are given as the number of elapsed milliseconds since 0:00:00.000, 
    *   January 1, 1970 (GMT).
    */
	JKFileConnectionLong	lastModifiedDate;
} JKFileConnectionFileInfo;


/**
 * 	A structure representing the file system volume size.
 */
typedef struct {
   /**
    *   The total size of the volume (in bytes).
    */
	JKFileConnectionLong	totalSize;

   /**
    *   The size of unused space in the volume (in bytes).
    */
	JKFileConnectionLong	freeSize;

   /**
    *   The size of used space in the volume (in bytes).
    */
	JKFileConnectionLong	usedSize;
} JKFileConnectionVolumeSize;



#ifdef __cplusplus
}
#endif

#endif /* ___JK_FILECONNECTION_COMMON_H */

/**
 * @} end of group
 */
