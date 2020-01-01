/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaTone.h
 *  Monophonic Tone Playing Functions
 */

/**
 * @addtogroup MediaControl_JSI_SingleTone
 * @{
 */

#ifndef ___JKMEDIA_TONE_H
#define ___JKMEDIA_TONE_H

/* Aplix header - begin */
#include <JkMediaControl.h>
#include "JkTypes.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "ven_codec.h"
#include "jap_media.h"
/* Mstar header - end */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *   Plays a monophonic tone.
 * @param note
 *   The pitch, designated by MIDI note numbers (0 to 127).
 * @param duration
 *   The tone duration (in milliseconds).
 * @param volume
 *   The tone volume, designated from 0 (silent) to 127 (maximum).
 * @return
 *   Return #JKMEDIA_RESULT_OK if the operation succeeds, or #JKMEDIA_RESULT_ERROR
 *   if it fails.
 *
 *  Return to the caller of this function as soon as the tone begins playing.
 *
 * @if NEWTXT
 *  At the time this function is called, 
 *  fail this function and return #JKMEDIA_RESULT_ERROR 
 *  if the necessary exclusive 
 *  resources are not available because they are used for an alert 
 *  sound playback by #JkDeviceAlertBySound() or because they are 
 *  already loaded by the #JKT_MediaControl structure 
 *  load() function which requires the same resource. 
 *  For detail of #JkDeviceAlertBySound(), see
 *  <i>JBlend [micro] Interface Reference: CLDC 1.0/1.1--MIDP 2.0</i>.
 * @endif
 */
JKSint32 JkMediaTonePlayNote( JKSint32 note, JKSint32 duration, JKSint32 volume );

/**
 *  Stops a tone started by #JkMediaTonePlayNote().
 *
 *  This function is called at the following times, regardless of whether a tone
 *  is actually being played.
 *  <ul>
 *   <li>When the JVM pauses or terminates.
 *   <li>When #AmMediaBlockPlayers() or #AmMediaTerminatePlayers() is called in the native system.
 *  </ul>
 *  If a tone is playing when this function is called, stop the tone.
 *  If no tone is playing, perform no operation.
 */
void JkMediaToneStopAllNotes( void );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ! ___JKMEDIA_TONE_H */

/** @} end of group */
