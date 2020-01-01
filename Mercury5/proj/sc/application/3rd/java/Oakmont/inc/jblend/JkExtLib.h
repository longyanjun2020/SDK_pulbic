/*
 * Copyright 2003-2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkExtLib.h
 *  External Class Libraries JSI
 */
/**
 * @addtogroup Class_Extension_JSI
 * @{
 */

#ifndef ___JK_EXTLIB_H
#define ___JK_EXTLIB_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * A structure for holding information about a JAR file containing an
 * external class library.
 *
 * Store a valid pointer in either the <i>JarAddress</i> or
 * <i>JarRead</i> member.
 *
 * The JAR file must have been preverified.
 */
typedef struct {

    /**
     * A pointer to the memory area holding the JAR file image.
     *
     * Set a pointer to the memory area where the JAR file image has been saved.
     * When a pointer is set, it must remain valid until the JVM terminates.
     * Set #JK_NULL if <i>#JarRead</i> is to be used to read the JAR file.
     */
    const void* jarAddress;

    /**
     * The size (in bytes) of the JAR file image.
     *
     */
    JKUint32 jarSize;

    /**
     * A pointer to an input stream function for reading a JAR file.
     *
     * @param buffer A pointer to the memory area for storing the read JAR file.
     * @param offset The offset from the head of the JAR file to the read position.
     *               The initial value of the read position is 0.
     *               A designation of -1 indicates the current position.
     * @param length The size (in bytes) of the read data.
     * @return       Return the actually read number of bytes (0 or above).
     *               Return 0 if the JAR file was read to the end.
     *               Return a negative value if the read operation failed.
     *
     * In <i>jarRead</i>, set a function pointer for reading the JAR file image.
     * This function pointer should remain valid until the JVM terminates.
     *
     * When <i>jarAddress</i> is used to read a JAR file, set #JK_NULL in <i>jarRead</i>.
     */
    JKSint32 (*jarRead)(void *buffer, JKSint32 offset, JKSint32 length);

} JKT_ExtLib_Jar;

/**
 *        Gets information about JAR files containing external class libraries.
 * @param number
 *        A pointer to the buffer for putting the element count of
 *        the JKT_ExtLib_Jar array indicated by the return value.
 * @return
 *        A pointer to the JKT_ExtLib_Jar structure array containing the JAR file information.
 *        Return #JK_NULL if no external class library is used.
 *
 * JBlend calls this function when starting the JVM. The returning of
 * JAR file information makes it possible for Java applications to use the
 * external class libraries in the JAR file.
 *
 * The structure array indicated by the return value and the pointer type members of 
 * the array element structures must remain valid until the JVM terminates.
 *
 * Store a valid pointer in either the <i>JarAddress</i> or <i>JarRead</i>
 * member of individual structures that are held as elements of the array indicated by the 
 * return value of this function.
 * If an element for which neither member is set exists, the JVM aborts in error.
 * And if the number of array is negative or more than 16, the JVM also aborts.
 */
const JKT_ExtLib_Jar* JkExtLibGetJarInfoR2(JKSint32* number);

/**
 *    Gets the name of classes used for external class library initialization processing.
 *
 *   @return
 *    Return a pointer to the buffer holding the class name including package name.
 *    If an initialization class is not used, return #JK_NULL.
 *
 *    Indicate the class name as a UTF-8 character string terminated by '\0'.
 *    Use a period (.) to demarcate package names.
 *
 *      Example: com.jblend.micro.StartUp\0
 *
 *    If you specify multiple classes, delimit them by a semicolon(;).
 *
 *      Example: com.jblend.micro1.StartUp;com.jblend.micro2.StartUp\0
 *
 *    The classes whose name are returned by this function must be classes implementing
 *    the <code>{@link Initializable com.jblend.extlib.Initializable}</code> interface.
 *
 *   Before starting a Java application, JBlend generates instances of the classes
 *   whose name are acquired by this function, and calls the
 *   <code>{@link com.jblend.extlib.Initializable}</code> class
 *   <code>{@link com.jblend.extlib.Initializable#initialize initialize()}</code> method.
 *   If multiple class names are specified, JBlend calls the 
 *   {@link com.jblend.extlib.Initializable#initialize initialize()}
 *   method in the order they are specified.
 *   Using this method to perform initialization processing makes available the functions
 *   (event listener, etc.) provided by external class libraries as soon as a Java
 *   application is launched.
 *
 *   The pointer returned by this function must remain valid until the JVM terminates.
 */
const JKUint8* JkExtLibGetInitializerClassName(void);

/**
 *         Gets the names of packages whose inclusion in a Java application
 *         JAR file is not allowed.
 * @return Return a pointer to a data array having as elements the pointers
 *         to memory areas holding the restricted package names. If no package
 *         names are restricted, return #JK_NULL.
 *
 * Express each package name as a UTF-8 character string terminated by '\0'.
 * Use a period (.) to demarcate package names.
 *
 * Use NULL to terminate the data array elements.
 *
 * Before starting a Java application, JBlend calls this function and
 * registers the acquired package names. If the JAR file of a Java application
 * contains a class name starting with a package name registered by this
 * function, the JVM terminates before the Java application can use that class.
 */
const JKUint8** JkExtLibGetRestrictedPackageNames(void);

/**
 *         Gets the names of packages whose use by a Java application
 *         is not allowed.
 * @return Return a pointer to a data array having as elements the pointers
 *         to memory areas holding the restricted package names. If no package
 *         names are restricted, return #JK_NULL.
 *
 * Express each package name as a UTF-8 character string terminated by '\0'.
 * Use a period (.) to demarcate package names.
 *
 * Use NULL to terminate the data array elements.
 *
 * Before starting a Java application, JBlend calls this function and
 * registers the acquired package names. JBlend checks if the Java
 * application uses a class name starting with a package name registered
 * by this function. If the application uses that class, the JVM
 * terminates before the Java application can use it.
 */
const JKUint8** JkExtLibGetInternalPublicPackageNames(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ___JK_EXTLIB_H */

/** @} end of group */
