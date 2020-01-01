/* ut_audioenv_example.h */
#ifndef __UT_AUDIOENV_EXAMPLE_H__
#define __UT_AUDIOENV_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetAudioEnv_Example(void);
s32  NumAudioEnv_Example(void);
void  ReleaseAudioEnv_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIOENV_EXAMPLE_H__ */
