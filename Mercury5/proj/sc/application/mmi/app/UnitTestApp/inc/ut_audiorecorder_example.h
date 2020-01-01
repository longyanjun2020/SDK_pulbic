/* ut_audiorecorder_example.h */
#ifndef __UT_AUDIORECORDER_EXAMPLE_H__
#define __UT_AUDIORECORDER_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetAudiorecorder_Example(void);
s32   NumAudiorecorder_Example(void);
void  ReleaseAudiorecorder_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIORECORDER_EXAMPLE_H__ */
