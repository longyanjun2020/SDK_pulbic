/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_ACTION_HEADER
#define KJAVA_ACTION_HEADER

/**
 *  @file kjava_action.h
 *  Action Command
 */

#ifdef __cplusplus
extern "C"{
#endif

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/
 
/** 
 * @addtogroup Inter_Thread_Communication_KSI
 *
 * @par Include file 
 * \#include ajsc_platform.h
 * @{
 */

/** 
 * The length in bytes of the <i>action</i> buffer of the #KJavaActionCommand structure. 
 */
#define KJAVA_ACTION_BUFFER_LENGTH  200

// Action Request Type Identifier
#define  KJAVA_ACTION_TYPE_START_VM   (1)  //Request type: Start the JBlendia JVM. 
#define  KJAVA_ACTION_TYPE_RESUME_VM   (2) //Request type: Resume the JVM. 
#define  KJAVA_ACTION_TYPE_AJMS_MEM   (3)  //Request type: Perform an installation-related processing.
#define  KJAVA_ACTION_TYPE_AMS_NOMEM   (4) //Request type: Reserved for future use. 
#define  KJAVA_ACTION_TYPE_HTTPLIB   (5)   //Request type: Perform an HTTP transaction. 
#define  KJAVA_ACTION_TYPE_TCK   (6)       //Request type: Perform a TCK processing. 
#define  KJAVA_ACTION_TYPE_USER   (100)    //The offset of user-defined action type.

/** 
 * The structure type for representing an action command which is 
 * carried by the carrier of platform inter-thread communication.
 *
 * This documentation is for reference purposes only.
 * In general, the device manufacturer need not care about the values set in this structure members.
 */
typedef struct KJavaActionCommandTag
{
    /** 
     * The source thread that sends the action command.
     * The possible values are as follows:
     * - #KJAVA_AMS_THREAD
     * - #KJAVA_KVE_THREAD
     * - #KJAVA_NET_THREAD
     * - A value greater than or equal to #KJAVA_USER_THREAD can be set.
     */
    int     sourceThread;
    
    /** 
     * The identifier of the action type. 
     * The possible values are as follows:
     * - #KJAVA_ACTION_TYPE_START_VM
     * - #KJAVA_ACTION_TYPE_RESUME_VM
     * - #KJAVA_ACTION_TYPE_AJMS_MEM
     * - #KJAVA_ACTION_TYPE_AMS_NOMEM
     * - #KJAVA_ACTION_TYPE_HTTPLIB
     * - #KJAVA_ACTION_TYPE_TCK
     * - A value greater than or equal to #KJAVA_ACTION_TYPE_USER can be set.
     */
    int     type;
    
    /** 
     * The payload of the action. 
     */
    unsigned char action[KJAVA_ACTION_BUFFER_LENGTH];
}
KJavaActionCommand;

/** @} */

#ifdef __cplusplus
}
#endif 

#endif /* KJAVA_SYS_HEADER */

