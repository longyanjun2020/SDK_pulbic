/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMMediaControl.h
 *  Media Control Service Functions
 */

/**
 * @addtogroup MediaControl_JBI
 *
 * @{
 */

#ifndef __AM_MEDIA_CONTROL_H__
#define __AM_MEDIA_CONTROL_H__

#include "JkTypes.h"
#include "JkMediaControl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  All audio devices
 */
#define JKMEDIA_BLOCK_AUDIO -1

/**
 *  All video devices
 */
#define JKMEDIA_BLOCK_VIDEO -2

/**
 *  All media devices
 */
#define JKMEDIA_BLOCK_ALL -3

/**
 * Makes event notification to JBlend.
 * @param event
 *  A pointer to the JKT_MediaEvent structure storing the event
 * @return
 *   #JKMEDIA_RESULT_OK: The event was accepted by JBlend (succeeded)
 *   #JKMEDIA_RESULT_ERROR: Not accepted (queue full, etc.) (failed)
 */
JKSint32 AmMediaPostEvent( JKT_MediaEvent* pEvent );


/**
 * Pauses all players currently playing and releases the device.
 * @return
 *   Returns #JKMEDIA_RESULT_OK if the function succeeds, or #JKMEDIA_RESULT_ERROR if 
 *   it fails.
 *
 * JBlend calls this function to stop all players when suspending the JVM. <br>
 * The <i>#suspendVM()</i> function in the JKT_MediaControl structure is called for all players. <br>
 * The player cannot be operated after this function is called until 
 * #AmMediaResumePlayers() is called.
 */
JKSint32 AmMediaSuspendPlayers( void );

/**
 *  Restores all players to the state when  #AmMediaSuspendPlayers() was called.
 * @return
 *   Returns #JKMEDIA_RESULT_OK if the function succeeds, or #JKMEDIA_RESULT_ERROR if it 
 *   fails.
 *
 *  JBlend calls this function when it resumes the JVM, restoring the player state to 
 *  that at the time the JVM was suspended. <br>
 *  The <i>#resumeVM()</i> function in the JKT_MediaControl structure is called for all players. <br>
 */
JKSint32 AmMediaResumePlayers( void );

/**
 *  Terminates all currently running players.
 * @return
 *   Returns #JKMEDIA_RESULT_OK if the function succeeds, or #JKMEDIA_RESULT_ERROR if it 
 *   fails.
 *
 *  JBlend calls this function to dispose of all players when terminating the JVM. <br>
 *  The <i>#destroy()</i> function in the JKT_MediaControl structure is called for all players.
 *  When the JVM is terminated forcibly, call this function after the JVM thread is stopped.
 */
JKSint32 AmMediaTerminatePlayers( void );

/**
 *  Notifies the JVM of the initiation or termination of using the device.
 * @param mediaType
 *   The media type number of the device.
 *   In addition to individual media types, the following designations are possible.
 *   <br>
 *    #JKMEDIA_BLOCK_AUDIO<br>
 *    #JKMEDIA_BLOCK_VIDEO<br>
 *    #JKMEDIA_BLOCK_ALL
 * @param isBlock
 *   Designate JK_TRUE to indicate that the native system wants to use devices. <br>
 *   Designate JK_FALSE to indicate that the native system is finished using the 
 *   devices and is releasing them for use by the JVM.
 * @return
 *   Returns #JKMEDIA_RESULT_OK if the function succeeds, or 
 *   #JKMEDIA_RESULT_ERROR if it fails.
 *
 *  When the native system notifies of the start of device use by this function, then after 
 *  the JVM has released devices indicated in the mediaType parameter, 
 *  JkMediaControlNotifyDeviceReleased() is called from the JVM task context.
 */
JKSint32 AmMediaBlockPlayers( JKSint32 mediaType, JKBool isBlock );

/**
 * @if NOT_READY
 * @param pData
 * @param length
 * @param pType
 * @return
 *
 * @endif
 */
JKSint32 AmMediaDetectMimeType( JKUint8* pData, JKSint32 length, JKWChar** pType );

/**
 * @if NOT_READY
 * @param pData
 * @param length
 * @return
 *
 * @endif
 */
JKSint32 AmMediaDetectMediaType( JKUint8* pData, JKSint32 length );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__AM_MEDIA_CONTROL_H__ */

/** @} end of group */
