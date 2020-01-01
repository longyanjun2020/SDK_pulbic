/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 *  Note: Source comments will be filled out later.
 */

/**
 * @file AMPlatformError.h
 * JVM Abnormal Termination JBI
 */
/**
 * @addtogroup JVM_Abnormal_Termination_JBI
 * @{
 */
#ifndef ___AMPLATFORMERROR_H
#define ___AMPLATFORMERROR_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Example 
#define JK_PLATFORM_INVALID_HANDLE   (1)
#define JK_PLATFORM_NO_ENOUGH_MEMORY (2)
#define JK_PLATFORM_PARAMETER_ERROR  (3)
*/

/**
 *    Notifies that the JSI is unable to continue processing.
 * @param err  The error code notified to JBlend. Set a value between 1 and 32767.
 *
 * Call this function when processing cannot continue because an illegal parameter was 
 * passed when an JSI was called from the JVM task context.
 *
 * Use this function only for the purpose described above.
 * It must be called only from the JVM task context.
 *
 * This function does not return to the caller, but manipulates the program stack and
 * returns to the caller of #AamsVmStartMIDP () by which the JVM was started.
 * The value returned by #AamsVmStartMIDP () at this time is the sum of the 
 * err parameter and #JK_VMEXIT_PLATFORMERROR_LOWEST.
 * Since #JK_VMEXIT_PLATFORMERROR_LOWEST is defined as a negative value smaller than 
 * -32767, if the value passed in err is according to specification (within the 
 * range of 1 to 32767), a negative value will be returned indicating abnormal 
 * termination. If err is not according to specification, #AamsVmStartMIDP() 
 * returns #JK_VMEXIT_PLATFORMERROR_LOWEST.
 * 
 * This function simply terminates the JVM, without freeing the resources used by 
 * the JMV. The native system must free the resources used by the JVM.
 *
 */
void AmPlatformNotifyError( const JKSint32 err );


#ifdef __cplusplus
}
#endif

#endif
