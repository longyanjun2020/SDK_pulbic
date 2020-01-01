
#include "audiotypedef.h"

#ifndef _AUDIOFIR_STRUCT_H_
#define _AUDIOFIR_STRUCT_H_

//#define _SUPPORT_STEREO_

#define AUDIO_FIR_LENGTH    32

typedef struct audiofir_t
{
    U32     channel_mode;
    S16     coef_lin_1b15[AUDIO_FIR_LENGTH-1];
    S16     gain_lin_12b4;
    S16     pcms_lin_1b15[AUDIO_FIR_LENGTH*2];
}
audiofir_t;

#endif