/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMPrecheck.h
 *   Precheck Application (for high-speed starting)
 */
/**
 * @addtogroup Module_Precheck_JBI
 * @{
 */

#ifndef ___AM_PRECHECK_H
#define ___AM_PRECHECK_H

#include "JkTypes.h"
#include "JkTypesJarInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Prechecks a Java application.
 * @param jarInfo
 *   A pointer to the structure holding JAR file information for the application to be checked. 
 * @param heapAddr
 *   A pointer to the memory area that can be used for the check. 
 *   Designate a pointer to an area that the JVM can use as a Java heap.
 *   The designated address value must conform to the memory alignment of the adopted CPU. 
 * @param heapSize
 *   The size (in bytes) of the memory area used for the check. 
 *   A size up to 16 MB may be designated.
 * @return
 *   #JK_PRECHECK_VALID: Valid application<br>
 *   #JK_PRECHECK_INVALID: Invalid application<br>
 *   #JK_PRECHECK_UNKNOWN: Unknown (check failed due to memory lack, etc.)<br>
 *   #JK_PRECHECK_CANCELED: Check canceled<br>
 *
 * The validity of an application is normally checked at the time of execution. 
 * This function can be called to check whether a Java application is valid without 
 * actually starting it. By running the check in advance with this function,
 * it should be possible to start an application more quickly.
 * 
 * A valid pointer must be set in either the <i>jarAddress</i> or <i>jarRead</i> 
 * member of the structure indicated by the <i>jarInfo</i> parameter. 
 * If neither is set correctly, the behavior of this function is not guaranteed.
 * Note that a valid value must be set in the <i>jarSize</i> member as well.
 * If both the <i>jarAddr</i> and <i>jarRead</i> members are set, the value set 
 * in <i>jarAddr</i> is used. 
 * 
 * The native system must store values returned by this function for each application.
 * Pass the stored values as return values of the JkPrecheckValidateApplication()
 * function called by JBlend when the JVM starts.
 *
 * When this function returns #JK_PRECHECK_INVALID, the Java application checked
 * is an invalid application. Prevention of such applications from executing 
 * may be done in the native system.
 *
 * Calling AmPrecheckCancel() while this function is executing cancels the 
 * precheck processing by this function; #JK_PRECHECK_CANCELED is 
 * then returned as a result. #JK_PRECHECK_CANCELED is never returned for 
 * any other reason.
 *
 * This function is not reentrant. Moreover, it cannot be called during Java 
 * execution. Behavior is not guaranteed if this function is called concurrently, 
 * or called while a Java application is running.
 * @see JKT_JAR_INFO, JkPrecheckValidateApplication()
 */
JKSint32 AmPrecheckApplication(JKT_JAR_INFO *jarInfo, void *heapAddr, JKSint32 heapSize);

/**
 *  Cancels application precheck processing.
 *
 * This function cancels the prechecking by #AmPrecheckApplication().
 * The canceled #AmPrecheckApplication() returns #JK_PRECHECK_CANCELED.
 * If this function is called when #AmPrecheckApplication() is not executing,
 * there is no operation.
 */
void AmPrecheckCancel(void);

#ifdef __cplusplus
}
#endif

#endif /* ___AM_PRECHECK_H */

/**
 * @} end of group
 */
