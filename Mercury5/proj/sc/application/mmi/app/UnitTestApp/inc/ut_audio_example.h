/* ut_audio_example.h */
#ifndef __UT_AUDIO_EXAMPLE_H__
#define __UT_AUDIO_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetAudio_Example(void);
s32   NumAudio_Example(void);
void  ReleaseAudio_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIO_EXAMPLE_H__ */
