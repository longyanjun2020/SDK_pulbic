/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesJarInfo.h
 *   Jar file information type
 */
/**
 * @addtogroup Module_Precheck_JBI
 * @{
 */

#ifndef ___JKTYPESJARINFO_H
#define ___JKTYPESJARINFO_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for holding information about a JAR file. 
 */
typedef struct {
   /**
    *  A pointer to the memory area holding a JAR file. 
    *  
    *  Set a pointer to the memory area where the JAR file image has been saved. 
    *  Set an address value conforming to the memory alignment of the CPU used.
    *  Set JK_NULL if <i>jarRead</i> is to be used to read the JAR file. 
    */
    const void *jarAddr;
   /**
    *  The size (in bytes) of the JAR file image.
    *  
    *  A valid value must be set in this member regardless of the file access 
    *  method that is indicated by <i>jarAddr</i> or <i>jarRead</i>.
    */
    JKSint32 jarSize;
   /**
    *  A pointer to an input stream function for reading a JAR file. 
    *  
    *  @param buffer
    *         A pointer to the memory area for storing the read JAR file. 
    *  @param offset
    *         The offset from the head of the JAR file to the read position. 
    *         The initial value of the read position is 0. 
    *  @param size
    *         The size (in bytes) of the read data.
    *  @return
    *         Return the actually read number of bytes (0 or above). 
    *         Return a negative value if the read operation failed.
    *  
    *  In <i>jarRead</i>, set a function pointer for reading the JAR file image. 
    *  
    *  If the size of read data is less than the requested size, 
    *  JBlend retries reading the remaining data. If the size returned as 
    *  read data is greater than the requested size, JBlend treats this 
    *  result as an error. 
    *  
    *  When <i>jarAddress</i> is used to read a JAR file, set JK_NULL in <i>jarRead</i>. 
    */
    JKSint32 (*jarRead) (void *buffer, JKSint32 offset, JKSint32 size);
} JKT_JAR_INFO;

#ifdef __cplusplus
}
#endif

#endif /* ___JKTYPESJARINFO_H */

/**
 * @} end of group
 */
