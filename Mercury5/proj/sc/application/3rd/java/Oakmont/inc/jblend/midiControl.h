/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file midiControl.h
 * MIDI Sequencer Sample Implementation for Windows
 */

#ifndef __MIDI_CONTROL_H
#define __MIDI_CONTROL_H

/* Aplix header - begin */
#include "JkMediaControl.h"
#include <JkMediaExtension.h>
#include "AMMediaControl.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "ven_codec.h"
#include "jap_media.h"
#include "jap_head.h"
#include "kjava_sys_core.h"
#include "ven_file.h"
#include "util_ucs2.hi"
#include "MMAPImidiControl.h"
#include "protocolStream.h"
#include "fileStream.h"
/* Mstar header - end */


#define JKMEDIA_TYPE_MIDI  ( JKMEDIA_TYPE_USER_BASE + 2 )

/**
 * Structure for MIDI sequencer control functions.
 */
extern const JKT_MediaControl midiControl;


#endif /* !__MIDI_CONTROL_H */
