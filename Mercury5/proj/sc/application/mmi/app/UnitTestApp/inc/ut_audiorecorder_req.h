/* ut_audiorecorder_req.h */
#ifndef __UT_AUDIORECORDER_REQ_H__
#define __UT_AUDIORECORDER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAudiorecorder_UT(void);
int   noAudiorecorder_UT(void);
void  releaseAudiorecorder_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIORECORDER_REQ_H__ */
