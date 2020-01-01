/**************************************************************************
 * Copyright (c) 2010 MStar Semiconductor, Inc. All Rights Reserved.
 *
 **************************************************************************
 *   $Id: //t1/stack/mainline/tplgsm/media/lowlevel/gas_process.mod/api/inc/audiodrcengine.h#4 $
 *   $Revision: #4 $
 *   $DateTime: 2011/01/11 12:15:53 $
 **************************************************************************/

/**************************************************************************
 * Copyright (c) 2006-2009 MStar Semiconductor, Inc. All Rights Reserved.
 *
 **************************************************************************
 * Unless otherwise stipulated in writing, any and all information
 * vcontained herein regardless in any format shall remain the sole
 * proprietary of MStar Semiconductor Inc. and be kept in strict
 * confidence (!¡±MStar Confidential Information!¡L) by the recipient.
 * Any unauthorized act including without limitation unauthorized
 * disclosure, copying, use, reproduction, sale, distribution,
 * modification, disassembling, reverse engineering and compiling of the
 * contents of MStar Confidential Information is unlawful and strictly
 * prohibited. MStar hereby reserves the rights to any and all damages,
 * losses, costs and expenses resulting therefrom.
 **************************************************************************/
/**
 * \file
 * Types needed for the dynamic range compressor
 */

#ifndef _AUDIODRC_STRUCT_H_
#define _AUDIODRC_STRUCT_H_

/***************************************************************************
 * Include Files
 ***************************************************************************/
//#include <plks_typ.h>
//#include "audiotyp.h"

#include "audiotypedef.h"

/***************************************************************************
 * Manifest Constants
 ***************************************************************************/

/***************************************************************************
 *  Types
 **************************************************************************/

/* audiotyp.h will use AUDIO_DRC_NUM_COMP_POINT to replace THRES_NUM */
/* #define THRES_NUM       4 */

#define AUDIO_DRC_NUM_COMP_POINT    4
#define SEGMENT         (AUDIO_DRC_NUM_COMP_POINT-1)
#define L_FRAME         32
#define L_LOOK_AHEAD    32
#define CHAN_NUM        1

typedef struct audiodrc_t
{
  /* control parameter: */
  S16 drc_enable;
  S16 att_index;                            /* [r/w] attack rate seletion (dB/s) */
  S16 rel_index;                            /* [r/w] release rate seletion (dB/s) */
  S16 ini_gain_db;                          /* [r/w] initial gain (dB) */
  S16 rel_step;                             /* [r/w] release scale factor, 8:1x 16:1/2x 32:1/4x */
  S16 comp_x_db[AUDIO_DRC_NUM_COMP_POINT];  /* [r/w] input XdB point (dB) */
  S16 comp_y_db[AUDIO_DRC_NUM_COMP_POINT];  /* [r/w] output YdB point(dB) */
  S16 clip_level;                           /* [r/w] output clipping level */
  /* private variable: */
  S16 level_det;                            /* [r/ ] value of level detector */
  S32 real_gain;                            /* [r/ ] modulated gain (dB) */
  S16 att_rate, rel_rate;                   /* [r/w] attack rate / release rate (dB/s) */
  S16 step_counter;                         /* [r/ ] counter of release step size */

  S16 comp_x_sect[AUDIO_DRC_NUM_COMP_POINT];
  S16 comp_slope[SEGMENT];
  S16 comp_const[SEGMENT];
}
audiodrc_t;

/***************************************************************************
 *  Variables
 **************************************************************************/

/***************************************************************************
 *  Macros
 **************************************************************************/

/***************************************************************************
 *  Function Prototypes
 **************************************************************************/

#endif/*_AUDIODRC_STRUCT_H_*/

