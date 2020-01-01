/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/**
 * @file AMFileConnectionUtils.h
 *   FileConnection JBI Utilities
 */
/**
 * @addtogroup Module_FileConnection_JBI
 * @{
 */

#ifndef ___AM_FILECONNECTION_UTILS_H
#define ___AM_FILECONNECTION_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include "JkFileConnectionCommon.h"


/**
 * Adds a string to a string array.
 * 
 *   @param  array 
 *           A pointer to the structure holding an array of pointers to strings.
 *   @param  text 
 *           A pointer to the string to be added to the array.
 *   @param  length 
 *           The length of the string (number of characters).
 *   @return 
 * 	         #JK_FILECONNECTION_SUCCESS: The function succeeded. <br>
 * 	         #JK_FILECONNECTION_GENERAL_ERR: The text is #JK_NULL, or the length parmeter is 0 or less. <br>
 * 	         #JK_FILECONNECTION_MEMORY_ERR: Not enough memory.
 * 	
 * 	It is assumed that this function will be called from the following functions. 
 * 	- JkFileConnectionListRoots()
 * 	- JkFileConnectionListFiles()
 * 	.
 * 	If this function returns #JK_FILECONNECTION_MEMORY_ERR, the function (above) that called it
 * 	should fail and return #JK_FILECONNECTION_MEMORY_ERR.
 * 	The behavior is not guaranteed if a function other than the above calls this function. 
 * 	
 * 	This function is not reentrant. 
 * 	
 * 	@see JkFileConnectionListRoots()
 * 	@see JkFileConnectionListFiles()
 */
JKFileConnectionErr AmFileConnectionUtilsAddString(JKFileConnectionStringArray* array,JKWChar* text,JKSint32 length);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ___AM_FILECONNECTION_UTILS_H */

/**
 * @} end of group
 */

