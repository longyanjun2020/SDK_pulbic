/* ut_audioplayer_example.h */
#ifndef __UT_AUDIOPLAYER_EXAMPLE_H__
#define __UT_AUDIOPLAYER_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetAudioplayer_Example(void);
s32   NumAudioplayer_Example(void);
void  ReleaseAudioplayer_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIOPLAYER_EXAMPLE_H__ */
