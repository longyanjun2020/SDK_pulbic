/**
 * Copyright 2001-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkNativeMethod.h
 *   Native Method Interface JSI
 */
/**
 * @addtogroup Module_Native_Method
 * @{
 */

#ifndef ___JK_NATIVEMETHOD_H
#define ___JK_NATIVEMETHOD_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The type of the C function corresponding to a Java native method.
 *
 * This is the type of native C function that corresponds to 
 * a native method. 
 * The address of a function of this type should be returned by 
 * JkNativeMethodGetCFunction().
 */
typedef void (*JK_NATIVE_FUNC)(void);

/**
 * Gets the C function address corresponding to a native method. 
 *
 * @param className  A pointer to the memory area holding the class name 
 *                   to which the method belongs (the package delimiter is "/"). 
 *                   (ex. com/jblend/micro/Native)
 * @param methodName A pointer to the memory area holding the method name 
 *                   (simple name). 
 * @return           Address of the corresponding native function 
 *                   (pointer to function with void return value and void arguments). 
 *                   If there is no corresponding C function, return #JK_NULL.
 *
 * This function is called for address resolution when the JVM calls a native 
 * method. If JK_NULL is returned, the JVM stops. 
 * 
 * A native function must have no arguments and the return value must be void.
 * 
 * The strings held in the memory areas indicated by the <i>className</i> and 
 * <i>methodName</i> parameters are UTF8 character strings, and are terminated by '\0'.
 *
 */
JK_NATIVE_FUNC JkNativeMethodGetCFunction(const JKUint8* className, const JKUint8* methodName);

#ifdef __cplusplus
}
#endif

#endif /* ___JK_NATIVEMETHOD_H */

/**
 * @} end of group
 */

