/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaMIDIDrv.h
 *  MIDI Driver Control
 */

/**
 * @addtogroup MediaControl_JSI_MIDIDrv
 *
 * @{
 */

#ifndef __JKMEDIA_MIDIDRV_H__
#define __JKMEDIA_MIDIDRV_H__

/* Aplix header - begin */
#include "JkTypes.h"
#include "JkMediaControl.h"
#include "JkMediaOption.h"
#include "AMMemory.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "MMAPImidiControl.h"
#include "jap_head.h"
#include "jap_media.h"
#include "ven_std.h"
#include "ven_codec.h"
#include "jap_media.h"
/* Mstar header - end */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  A real-time MIDI control player
 *
 *  When the native system wants to acquire MIDI device, 
 *  call #AmMediaBlockPlayers() passing this type as the parameter.
 */
#define JKMEDIA_TYPE_MIDI_DEVICE 1

/**
 * Gets a MIDI data control structure.
 * @return
 *   If the operation succeeds, return a pointer to the control structure; 
 *   if it fails, return JK_NULL.
 *
 *  Return JK_NULL if the native system does not support MIDI driver control.
 */
JKT_Media_MIDIControl const* JkMediaMIDIDrvGetMIDIController( void );

/**
 *  Creates a MIDI driver instance.
 * @return
 *   If the operation succeeds, return an identifier of the created instance;
 *   if it fails, return 0.
 *   This identifier is passed as player ID to the JKT_Media_MIDIControl functions.
 *
 *  When the device manufacturer does not support MIDI driver control, 
 *  implement this function as an empty function that always returns 0.
 */
JKSint32 JkMediaMIDIDrvCreate( void );

/**
 *  Discards the MIDI driver instance.
 * @param id
 *   The MIDI driver ID.
 *   The return value of JkMediaMIDIDrvCreate() is designated.
 * @return
 *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
 *   if it fails, return #JKMEDIA_RESULT_ERROR.
 *
 *  When the device manufacturer does not support MIDI driver control, 
 *  implement this function as an empty function that always returns #JKMEDIA_RESULT_ERROR.
 */
JKSint32 JkMediaMIDIDrvDestroy( JKSint32 id );

/**
 *  Opens MIDI driver.
 * @param id
 *   The MIDI driver ID.
 *   The return value of JkMediaMIDIDrvCreate() is designated.
 * @return
 *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
 *   if it fails, return #JKMEDIA_RESULT_ERROR.
 *
 *  When the device manufacturer does not support MIDI driver control, 
 *  implement this function as an empty function that always returns #JKMEDIA_RESULT_ERROR.
 */
JKSint32 JkMediaMIDIDrvOpen( JKSint32 id );

/**
 *  Closes MIDI driver.
 * @param id
 *   The MIDI driver ID.
 *   The return value of JkMediaMIDIDrvCreate() is designated.
 * @return
 *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
 *   if it fails, return #JKMEDIA_RESULT_ERROR.
 *
 *  When the device manufacturer does not support MIDI driver control, 
 *  implement this function as an empty function that always returns #JKMEDIA_RESULT_ERROR.
 */
JKSint32 JkMediaMIDIDrvClose( JKSint32 id );

/**
 *  Sets the master volume of a MIDI driver.
 * @param id
 *   The MIDI driver ID.
 *   The return value of JkMediaMIDIDrvCreate() is designated.
 * @param volume
 *   The master volume value. (0 to 127)
 * @return
 *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
 *   if it fails, return #JKMEDIA_RESULT_ERROR.
 *
 *  When the device manufacturer does not support control of MIDI driver or master volume, 
 *  implement this function as an empty function that always returns #JKMEDIA_RESULT_OK.
 */
JKSint32 JkMediaMIDIDrvSetMasterVolume( JKSint32 id, JKSint32 volume );

/**
 * Gets the master volume set in a MIDI driver.
 * @param id
 *   The MIDI driver ID.
 *   The return value of JkMediaMIDIDrvCreate() is designated.
 * @return
 *   If the operation succeeds, return the master volume value. 
 *
 *  When the device manufacturer does not support control of MIDI driver or master volume, 
 *  implement this function as an empty function that always returns a fixed value.
 */
JKSint32 JkMediaMIDIDrvGetMasterVolume( JKSint32 id );

#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIA_MIDIDRV_H__ */

/** @} end of group */
