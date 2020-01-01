/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file waveStreamControl.h
 * WAV player via data streaming
 */
#ifndef __WAVE_STREAM_CONTROL_H__
#define __WAVE_STREAM_CONTROL_H__

/* Aplix header - begin */
#include "JkMediaControl.h"
#include "JkMediaExtension.h"
#include "JkMediaStream.h"
#include "AMMemory.h"
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

#define JKMEDIA_TYPE_WAV_STREAM ( JKMEDIA_TYPE_USER_BASE + 0x1000 )

extern const JKT_MediaControl waveStreamControl;

#endif /* !__WAVE_STREAM_CONTROL_H__ */
