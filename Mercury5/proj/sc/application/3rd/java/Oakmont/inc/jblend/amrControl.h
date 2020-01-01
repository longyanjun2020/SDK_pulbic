/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file amrControl.h
 *  AMR
 */

#ifndef __AMR_CONTROL_H
#define __AMR_CONTROL_H

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

#ifdef JAP_AMR_SUPPORT


#define JKMEDIA_TYPE_AMR  ( JKMEDIA_TYPE_USER_BASE + 3 )

/**
 * Structure for AMR control functions.
 */
extern const JKT_MediaControl amrControl;

#endif

#endif /* !__AMR_CONTROL_H */
