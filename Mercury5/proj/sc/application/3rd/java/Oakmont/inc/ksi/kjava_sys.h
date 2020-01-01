/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_SYS_HEADER
#define KJAVA_SYS_HEADER

/**
 * @file kjava_sys.h
 * Inter Thread Communication
 */

#ifdef __cplusplus
extern "C"{
#endif

#include <kjava_action.h>

/** @addtogroup Inter_Thread_Communication_KSI
 *  @{
 */

/*
 *  Interfaces listed in the group is used for inter-thread communication,
 *  including:
 *      - Send an message to another thread/task.
 *      - Receive an message from the queue of thread itself.
 *      .
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/
/**
 * @name Thread Identifier
 * @{
 * This documentation of thread identifiers is for reference purposes only.
 * In general, the device manufacturer need not care about the thread identifiers unless
 * the functions defined here are used for passing information between the 
 * native threads other than the KVE thread.
 */
/** 
 * AMS (MMI) thread 
 */
#define KJAVA_AMS_THREAD (1)
/** 
 * KVE (KJava VM Execution) thread 
 */
#define KJAVA_KVE_THREAD (2)
/** 
 * Reserved thread for network 
 */
#define KJAVA_NET_THREAD (3)
/** 
 * The offset of user-defined thread identifier.
 *
 * The device manufacturer can define own thread identifier 
 * with a value greater than or equal to #KJAVA_USER_THREAD.
 */
#define KJAVA_USER_THREAD (100)
/** @} */
 
/**
 * @name Action Request Type Identifier
 * @{
 * This documentation of action request types is for reference purposes only.
 * In general, the device manufacturer need not care about the action request type identifiers unless
 * the functions defined here are used for passing information between the 
 * native threads other than the KVE thread.
 */
/** 
 * Request type: Start the JBlendia JVM 
 */
#define KJAVA_ACTION_TYPE_START_VM        (1)
/** 
 * Request type: Resume the JVM 
 */
#define KJAVA_ACTION_TYPE_RESUME_VM       (2)
/** 
 * Request type: Perform an installation-related processing
 */
#define KJAVA_ACTION_TYPE_AJMS_MEM        (3)
/** 
 * Request type: Reserved for future use
 */
#define KJAVA_ACTION_TYPE_AMS_NOMEM       (4)
/** 
 * Request type: Perform an HTTP transaction
 */
#define KJAVA_ACTION_TYPE_HTTPLIB         (5)
/** 
 * Request type: Perform a TCK processing
 */
#define KJAVA_ACTION_TYPE_TCK             (6)
/** 
 * The offset of user-defined action type.
 *
 * The device manufacturer can define own request code 
 * with a value greater than or equal to #KJAVA_ACTION_TYPE_USER.
 */
#define KJAVA_ACTION_TYPE_USER            (100)
/** @} */

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 *        Sends an action command to the target thread.
 * @param target
 *        The identifier of the destination thread. 
 *        The possible values are as follows:
 *        - #KJAVA_AMS_THREAD
 *        - #KJAVA_KVE_THREAD
 *        - #KJAVA_NET_THREAD
 *        - A value greater than or equal to #KJAVA_USER_THREAD.
 *        .
 *        For AJSC 1.5, only #KJAVA_KVE_THREAD is passed here.
 * @param actionCommand_p
 *        A pointer to the #KJavaActionCommand structure holding the command information to be sent.
 *
 * AJSC calls this function to send an action command to the destination thread.
 *
 * The function should create a carrier used for the native inter-thread communication,
 * copy the content of given #KJavaActionCommand into the carrier, and send the
 * carrier to the destination thread indicated in <i>target</i>. 
 *
 * Note that this function need not be implemented when implementing a single thread environment. 
 * See @ref page_processing_environment for details.
 */
void kjava_sys_sendAction(int target, KJavaActionCommand *actionCommand_p);

/**
 * Retrieves an action command from the KVE thread queue.
 * @param actionCommand_pp
 *        A pointer to the buffer for putting a pointer to the #KJavaActionCommand 
 *        structure that contains the retrieved action command.
 * @retval 1 if the function succeeds.
 * @retval 0 if the function fails.
 *
 * AJSC calls this function to retrieve an action command from the 
 * message receive queue of the KVE thread.
 *
 * This function should not return until an action command is retrieved or 
 * an error occurs.
 *
 * When this function succeeds, the pointer put in the buffer indicated by 
 * <i>actionCommand_pp</i> must remain valid until next time this function is called.
 *
 * This function is called only in the KVE thread context.
 *
 * This function is usually called when JVM needs to be in idle. In other words, when
 * KVE has been blocked inside this function, platform should make sure the KVE is not
 * in busy loop for waiting the message.
 *
 * Note that this function need not be implemented when implementing a single thread environment. 
 * See @ref page_processing_environment for details.
 *
 * @deprecated This function is deprecated and is linked only by a special AJSC library
 *             with a compatibility reason or customer request.
 */
int kjava_sys_receiveAction(KJavaActionCommand **actionCommand_pp);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_HEADER */

