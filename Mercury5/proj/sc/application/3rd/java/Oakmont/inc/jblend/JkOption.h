/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkOption.h
 * JBlend Customization Property Acquisition
 */
/**
 * @addtogroup Module_System_Property
 * @{
 */

#ifndef ___SYS_JKOPTION_H
#define ___SYS_JKOPTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * Gets a JBlend customization property.
 * @param key
 *        A pointer to the buffer holding the string used as key for 
 *        obtaining the property
 * @param keylen
 *        The length (number of characters) of the key string
 * @param length
 *        A pointer to the buffer for putting the length 
 *        (number of characters) of the property returned by this function.
 * @return
 *        Return a pointer to the buffer holding the property string indicated by the key.
 *        In either of the following cases, return #JK_NULL.
 *        - Designated key does not exist.
 *        - The property does not need to be changed from the default value that 
 *          JBlend maintains.
 *        - No property is present for the designated key.
 *        .
 *        The string returned by this function should remain valid until the JVM terminates.
 *
 * Details of the property to be returned by this function are given in 
 * the documentation describing JBlend specifications corresponding to the 
 * profiles or optional packages that are implemented in the native system.
 * 
 * This function is called also for JBlend private properties.
 * Return #JK_NULL if the designated property name is not defined in the 
 * specifications of configuration, profiles, and optional packages that 
 * are supported by the native system.
 */
const JKWChar * JkOptionGetString( const JKWChar *key, JKSint keylen, JKSint *length );


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
