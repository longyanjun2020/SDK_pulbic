/***************************************************************************/
/*                                                                         */
/*       Copyright 2002 Aplix Corporation. All rights reserved.            */
/*                                                                         */
/***************************************************************************/

/**
 * @file JkMediaCustomProtocol.h
 *  Media Input and Output Protocol Extension
 */

/**
 * @addtogroup MediaControl_JSI_CustomProtocol
 *
 * @{
 */

#ifndef __JKMEDIA_CUSTOMPROTOCOL_H__
#define __JKMEDIA_CUSTOMPROTOCOL_H__

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Extending protocol functionality for reading media data
 */
/**
 *          Gets the number of input protocols.
 * @return  Return the number of input protocols.
 */
JKSint32 JkMediaCustomSourceGetCount( void );

/**
 *               Gets the scheme name of an input protocol.
 * @param count  An index number corresponding to the protocol scheme name. 
 *               Index values are designated up to the value returned by
 *               #JkMediaCustomSourceGetCount() minus 1.
 * @param pName  A pointer to the buffer for putting a pointer to the scheme name string.
 *               The stored pointer must remain valid until the JVM terminates.
 * @return       Return the number of characters in the scheme name string.
 */
JKSint32 JkMediaCustomSourceGetScheme( JKSint32 count, JKWChar** pName );

/**
 *               Gets the class name creating <code>DataSource</code>.
 * @param pName  A pointer to the buffer for storing a pointer to the name of the class creating <code>DataSource</code>.
 *               The stored pointer must remain valid until the JVM terminates.
 * @return       Return the number of characters in the name string of the class creating <code>DataSource</code>.
 *
 * Designate the full class name including package name.<br>
 * Example: "<code>jp.co.aplix.protocol.DataSourceFactory</code>"
 */
JKSint32 JkMediaCustomSourceGetCreator( JKWChar** pName );

/**
 * Extending protocol functionality for writing media data
 */
/**
 *          Gets the number of output protocols.
 * @return  Return the number of output protocols.
 */
JKSint32 JkMediaCustomSinkGetCount( void );

/**
 *               Gets the scheme name of an output protocol.
 * @param count  An index number corresponding to the protocol scheme name. 
 *               Index values are designated up to the value returned by
 *               #JkMediaCustomSinkGetCount() minus 1.
 * @param pName  A pointer to the buffer for putting a pointer to the scheme name string.
 *               The stored pointer must remain valid until the JVM terminates.
 * @return       Return the number of characters in the scheme name string.
 */
JKSint32 JkMediaCustomSinkGetScheme( JKSint32 count, JKWChar** pName );

/**
 *               Gets the name of the class creating <code>DataSink</code>.
 * @param pName  A pointer to the buffer for storing a pointer to the name of the class creating <code>DataSink</code>.
 *               The stored pointer must remain valid until the JVM terminates.
 * @return       Return the number of characters in the name string of the class creating <code>DataSink</code>.
 *
 * Designate the full class name including package name.<br>
 * Example: "<code>jp.co.aplix.protocol.DataSinkFactory</code>"
 */
JKSint32 JkMediaCustomSinkGetCreator( JKWChar** pName );

#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIA_CUSTOMPROTOCOL_H__ */

/** @} end of group */
