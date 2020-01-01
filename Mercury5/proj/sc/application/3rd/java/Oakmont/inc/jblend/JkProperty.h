/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkProperty.h
 * System Property Acquisition
 */
/**
 * @addtogroup Module_System_Property
 * @{
 */

#ifndef ___SYS_JK_PROPERTY_H
#define ___SYS_JK_PROPERTY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *  Gets a system property to be returned by the
 *  <code>java.lang.System</code> class <code>getProperty</code> method.
 * @param key
 *        A pointer to the buffer holding the string used as key for 
 *        obtaining the property. The key string is the same as the property name
 *        passed to the <code>getProperty</code> method.
 * @param keylen
 *        The length (number of characters) of the key string.
 * @param length
 *        A pointer to the buffer for putting the length 
 *        (number of characters) of the property returned by this function.
 * @return
 *        Return a pointer to the buffer holding the property string indicated by the key.
 *        In any of the following cases, return #JK_NULL.
 *        - The designated key does not exist.
 *        - The property does not need to be changed from the default value that 
 *          JBlend maintains.
 *        - No property is present for the designated key.
 *        .
 * 
 * The string returned by this function should remain valid until the JVM terminates.
 *
 * For details of the property to be returned by this function, see specifications
 * of the configuration, profiles, and optional packages that are implemented in the 
 * native system.
 * 
 * This function is called also for JBlend private properties.
 * Return #JK_NULL if the designated property name is not defined in the 
 * specifications of configuration, profiles, and optional packages that 
 * are supported by the native system.
 */
const JKWChar * JkPropertyGetString( const JKWChar *key, JKSint keylen, JKSint *length );


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
