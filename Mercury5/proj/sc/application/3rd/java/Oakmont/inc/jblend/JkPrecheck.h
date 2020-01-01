/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkPrecheck.h
 *   Precheck Java Application
 */
/**
 * @addtogroup Module_Precheck_JSI
 * @{
 */

#ifndef ___JKPRECHECK_H
#define ___JKPRECHECK_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Valid application
 */
#define JK_PRECHECK_VALID     (0)

/**
 * Invalid application
 */
#define JK_PRECHECK_INVALID  (-1)

/**
 *  Application validity unknown
 */
#define JK_PRECHECK_UNKNOWN  (-2)

/**
 *  Check canceled
 */
#define JK_PRECHECK_CANCELED (-3)

/**
 *  Gets the result of Java application precheck processing.
 * @param id
 *  The JVM instance ID.
 *  The ID that was passed to
 *  AamsVmStartMIDP()
 * is designated.
 * @return
 *         Return one of the following constants.
 *         - #JK_PRECHECK_VALID: Valid application<br>
 *         - #JK_PRECHECK_INVALID: Invalid application<br>
 *         - #JK_PRECHECK_UNKNOWN: Application validity unknown<br>
 *         - #JK_PRECHECK_CANCELED: Check canceled; application validity unknown<br>
 *         .
 *
 * Return the prechecking result obtained by AmPrecheckApplication().
 * If prechecking by AmPrecheckApplication() was not performed, return
 * #JK_PRECHECK_UNKNOWN.
 * When this function returns #JK_PRECHECK_CANCELED, the JVM treats the result as
 * #JK_PRECHECK_UNKNOWN
 * 
 * If this function returns #JK_PRECHECK_INVALID, the JVM terminates in error.
 * If this function returns #JK_PRECHECK_CANCELED or #JK_PRECHECK_UNKNOWN, 
 * the JVM performs the check during runtime of Java application.
 *
 * This function is called once at most, when the JVM is started. 
 * In some cases it may not be called, for example when a TCK is run, or in other
 * such cases where the JVM determines that checking at the time of execution is
 * necessary.
 * @see AmPrecheckApplication(), AmPrecheckCancel()
 */
JKSint32 JkPrecheckValidateApplication(JKSint32 id);


#ifdef __cplusplus
}
#endif

#endif /* ___JKPRECHECK_H */

/**
 * @} end of group
 */
