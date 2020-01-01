/*
 * Copyright 2007 Aplix Corporation. All rights reserved.
 */
 
/**
 * @file AMFiberService.h
 * Fiber Service JBI
 */
 
#ifndef __AM_FIBERSERVICE_H
#define __AM_FIBERSERVICE_H

#include "JkTypesFiber.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_Service_JBI Fiber Service JBI
 * @{
 *  An interface for interrogating the JBlend Fiber Service component.
 *
 *  The function in this interface can be used to gather information about
 *  the version and configuration of the JBlend Fiber Service component.
 */

/**
 * @name Fiber Service Version Macros
 * @{
 */

/**
 *  Retrieve the major version of the JBlend Fiber Service from <i>v</i>.
 */
#define JFS_GET_VERSION_MAJOR(v)        ((0xFF000000 & (v)) >> 24)

/**
 *  Retrieve the minor version of the JBlend Fiber Service from <i>v</i>.
 */
#define JFS_GET_VERSION_MINOR(v)        ((0x00FF0000 & (v)) >> 16)

/**
 *  Retrieve the revision stamp of the JBlend Fiber Service from <i>v</i>.
 */
#define JFS_GET_VERSION_REVISION(v)     ((0x0000FF00 & (v)) >>  8)

/**
 * @}
 */

/**
 *  Returns the JBlend Fiber Service version and configuration information.
 * 
 *  @param pulVersion
 *   Upon function success, the version of the JBlend Fiber Service is
 *   returned. This value may _not_ be set to #JK_NULL.
 *  @param pulConfiguration
 *   Upon function success, the build-time configuration of the JBlend Fiber 
 *   Service is returned. This parameter may be set to #JK_NULL.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  This function can be used to retrieve the version and build configuration
 *  for the JBlend Fiber Service through the <i>pulVersion</i> and 
 *  <i>pulConfiguration</i> pointers respectively. The build configuration may 
 *  be set to #JK_NULL if not needed.
 * 
 *  Use the @ref JFS_GET_VERSION_MAJOR "version macros" to retrieve the 
 *  individual major, minor and revision portions of the version information 
 *  returned in <i>pulVersion</i>.
 * 
 *  If requested by Aplix staff, please report the value returned by 
 *  <i>pulConfiguration</i>. The method to analyse the configuration value is
 *  not documented. 
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberServiceGetVersion( unsigned long *pulVersion, unsigned long *pulConfiguration );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_FIBERSERVICE_H */
