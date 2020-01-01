/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMNativeMethod.h
 *   Native Method Interface JBI
 */

#ifndef ___AM_NATIVEMETHOD_H
#define ___AM_NATIVEMETHOD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * @addtogroup Module_AM_Native_Method
 * @{
 */
/**
 *              Gets a boolean, byte, char, short, or int type argument. 
 * @param index The position of the native method argument whose value is to 
 *              be obtained. 
 *              See @ref module_am_native_method_index "How Arguments are Designated" 
 *              for details.
 * @return      Returns the value of the native method argument at the position 
 *              indicated by the <i>index</i> parameter. If the type is boolean, 
 *              1 means true and 0 means false. The return value is cast to the 
 *              JKSint32 type, so it should be cast in an appropriate size when 
 *              acquired for use. 
 *
 * Call this function to get a boolean, byte, char, short, or int type value 
 * designated as a native method argument.
 */
JKSint32 AmNativeMethodGetParameterAsInt(JKSint32 index);

/**
 *              Gets a long type argument. 
 * @param index The position of the native method argument whose value is to 
 *              be obtained.
 *              See @ref module_am_native_method_index "How Arguments are Designated" 
 *              for details.
 * @return      Returns a pointer to the memory area storing the value 
 *              (64-bit integer) of the native method argument at the position 
 *              indicated by the <i>index</i> parameter. The pointer remains 
 *              valid until a function named starting with "AmNativeMethodReturn"
 *              is called.
 *
 * Call this function to get a long type value designated as a native method 
 * argument. 
 *
 * The native function coding differs depending on whether or not the 
 * development environment (compiler) supports 64-bit integer type, and 
 * on whether the CPU uses big endian or little endian for data representation.
 * For details, see " @ref page_service_nativeif_arg_long."
 */
void* AmNativeMethodGetParameterAsLong(JKSint32 index);

/**
 *               Gets a byte[] type argument. 
 * @param index  The position of the native method argument whose value is 
 *               to be obtained.
 *              See @ref module_am_native_method_index "How Arguments are Designated" 
 *              for details.
 * @param length A pointer to the memory area for receiving the number of 
 *               elements in the native method byte[] argument at the position 
 *               indicated by the <i>index</i> parameter. When this function 
 *               returns JK_NULL, 0 is put in the area. 
 * @return       Either of the following is returned. 
 *               - A pointer to the byte array. <br>
 *                 This pointer remains valid until a function named starting 
 *                 with "AmNativeMethodReturn" is called.
 *               - #JK_NULL if null is designated as the byte[] type argument 
 *                 with the native method.
 *
 * Call this function to get byte array data designated as a native method argument.
 *    
 * When the contents of this array are overwritten at the native function side, 
 * the result is reflected in the byte array. 
 *  
 * The total number of <code>String</code> type arguments and array type arguments that 
 * can be specified for a native method is ten at maximum.
 * If it exceeds ten, the JVM terminates with error.
 * Array type arguments other than <code>byte[]</code> can
 * be used when optional functionality is used. See @ref page_service_nativeif_extend for 
 * details of the options available.
 */
JKSint8* AmNativeMethodGetParameterAsByteArray(JKSint32 index, JKSint32* length);

/**
 *               Gets a String type argument. 
 * @param inxdex The position of the native method argument whose value is to be 
 *               obtained.
 *              See @ref module_am_native_method_index "How Arguments are Designated" 
 *              for details.
 * @return       Either of the following is returned. 
 *               - A pointer to the memory area holding the string. 
 *                 The string here is a character string encoded as UTF-8 and 
 *                 terminated by '\0'. This pointer remains valid until a 
 *                 function named starting with "AmNativeMethodReturn" is called.
 *               - #JK_NULL if null or "" (blank string) is designated as the 
 *                 String type argument with the native method.
 *
 * Call this function to get a String type value designated as a native method 
 * argument.
 * 
 * The total number of <code>String</code> type arguments and array type arguments that 
 * can be specified for a native method is ten at maximum.
 * If it exceeds ten, the JVM terminates with error.
 * Array type arguments other than <code>byte[]</code> can
 * be used when optional functionality is used. See @ref page_service_nativeif_extend for 
 * details of the options available.
 */
JKUint8* AmNativeMethodGetParameterAsString(JKSint32 index);


/**
 *             Sets a boolean, byte, char, short, or int type return value. 
 * @param data The data to be passed as a return value. It must be cast to 
 *             the JKSint32 type. If the native method return value is 
 *             boolean type, designate true as 1 and false as 0.
 *
 * Call this function to set a boolean, byte, char, short, or int type as a 
 * native method return value. 
 * 
 * After this function is called, do not call AmNativeMethodGetParameterAsInt() 
 * or other functions for getting native method argument values.
 */
void AmNativeMethodReturnInt(JKSint32 data);

/**
 *             Sets a long type return value. 
 * @param data A pointer to the memory area holding the 64-bit 
 *             integer to be passed as a return value.
 *
 * Call this function to set a long type as a native method return value. 
 *
 * After this function is called, do not call AmNativeMethodGetParameterAsInt() 
 * or other functions for getting native method argument values.
 *
 * The native function coding differs depending on whether or not the 
 * development environment (compiler) supports 64-bit integer type, and
 * on whether the CPU uses big endian or little endian for data 
 * representation. For details, see " @ref page_service_nativeif_arg_long."
 */
void AmNativeMethodReturnLong(void* data);

/**
 *               Sets a String type return value. 
 * @param string A pointer to the UTF8 character string.
 *               Append '\0' to terminate the character string.
 *
 * Call this function to set a String type as a native method return value.
 * This function creates a Java String object from the character string stored 
 * in the memory area designated by the <i>string</i> parameter, and sets the 
 * created object as a native method String type return value.
 * 
 * If JK_NULL is passed in the str parameter, the native method returns a 
 * <code>null</code> object. 
 *  
 * The <i>string</i> area may be released after this function returns. 
 *
 * After this function is called, do not call AmNativeMethodGetParameterAsInt() 
 * or other functions for getting native method argument values.
 */
void AmNativeMethodReturnString(JKUint8* string);

/**
 * Sets a void type return value. 
 *
 * Call this function to set a void type as a native method return value.
 *
 * After this function is called, do not call AmNativeMethodGetParameterAsInt() 
 * or other functions for getting native method argument values.
 */
void AmNativeMethodReturnVoid(void);

/**
 * @} end of group
 */






#ifdef __cplusplus
}
#endif

#endif /* ___AM_NATIVEMETHOD_H */

