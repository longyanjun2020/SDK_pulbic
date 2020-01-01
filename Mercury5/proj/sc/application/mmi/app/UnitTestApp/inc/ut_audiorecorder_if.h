/* ut_audiorecorder_if.h */
#ifndef __UT_AUDIORECORDER_IF_H__
#define __UT_AUDIORECORDER_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAudiorecorder_If_UT(void);
int   noAudiorecorder_If_UT(void);
void  releaseAudiorecorder_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIORECORDER_IF_H__ */
